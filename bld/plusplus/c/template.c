/****************************************************************************
*
*                            Open Watcom Project
*
*    Portions Copyright (c) 1983-2002 Sybase, Inc. All Rights Reserved.
*
*  ========================================================================
*
*    This file contains Original Code and/or Modifications of Original
*    Code as defined in and that are subject to the Sybase Open Watcom
*    Public License version 1.0 (the 'License'). You may not use this file
*    except in compliance with the License. BY USING THIS FILE YOU AGREE TO
*    ALL TERMS AND CONDITIONS OF THE LICENSE. A copy of the License is
*    provided with the Original Code and Modifications, and is also
*    available at www.sybase.com/developer/opensource.
*
*    The Original Code and all software distributed under the License are
*    distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
*    EXPRESS OR IMPLIED, AND SYBASE AND ALL CONTRIBUTORS HEREBY DISCLAIM
*    ALL SUCH WARRANTIES, INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF
*    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR
*    NON-INFRINGEMENT. Please see the License for the specific language
*    governing rights and limitations under the License.
*
*  ========================================================================
*
* Description:  WHEN YOU FIGURE OUT WHAT THIS FILE DOES, PLEASE
*               DESCRIBE IT HERE!
*
****************************************************************************/


#include "plusplus.h"
#include "cgfront.h"
#include "errdefns.h"
#include "rewrite.h"
#include "preproc.h"
#include "ring.h"
#include "stack.h"
#include "memmgr.h"
#include "class.h"
#include "name.h"
#include "yydriver.h"
#include "fnovload.h"
#include "context.h"
#include "template.h"
#include "pcheader.h"
#include "initdefs.h"
#include "conpool.h"
#ifndef NDEBUG
#include "pragdefn.h"
#include "dbg.h"
#include "fmttype.h"
#include "fmtsym.h"
#endif

#define BLOCK_TEMPLATE_INFO     16
#define BLOCK_CLASS_INST        32
#define BLOCK_TEMPLATE_MEMBER   32
#define BLOCK_FN_TEMPLATE       16
static carve_t carveTEMPLATE_INFO;
static carve_t carveCLASS_INST;
static carve_t carveTEMPLATE_MEMBER;
static carve_t carveFN_TEMPLATE;

static TEMPLATE_DATA *currentTemplate;
static TEMPLATE_INFO *allClassTemplates;
static FN_TEMPLATE *allFunctionTemplates;
static struct {
    unsigned            max_depth;
    unsigned            curr_depth;
    tc_fn_control       fn_control;
    SYMBOL              translate_fn;
    TYPE                extra_member_class;
    unsigned            keep_going : 1;
    unsigned            extra_members : 1;
    unsigned            depth_diagnosed : 1;
} templateData;

static CNV_DIAG diagTempParm =  // DIAGNOSIS FOR TEMPLATE ARGUMENT CONVERSION
    { ERR_PARM_IMPOSSIBLE
    , ERR_PARM_AMBIGUOUS
    , ERR_CALL_WATCOM
    , ERR_PARM_PRIVATE
    , ERR_PARM_PROTECTED
    };

enum template_context_type {
    TCTX_CLASS_DEFN     = 1,    // instantiating template class defn
    TCTX_FN_DEFN        = 2,    // instantiating template function defn
    TCTX_MEMBER_DEFN    = 3,    // instantiating template class member defn
    TCTX_FN_BIND        = 4,    // binding a function template to arguments
    TCTX_FN_BIND_AND_GEN= 5,    // binding a function template to a fn sym
    TCTX_NULL           = 0
};

typedef struct template_context TEMPLATE_CONTEXT;
struct template_context {
    TEMPLATE_CONTEXT            *prev;
    TOKEN_LOCN                  *locn;
    union {
        SYMBOL                  sym;    // FN_DEFN, FN_BIND
        SCOPE                   scope;  // CLASS_DEFN
        void                    *any;
    } u;
    enum template_context_type  id;
};

static struct {
    NESTED_POST_CONTEXT         registration;
    TEMPLATE_CONTEXT            *inst_stack;
} activeInstantiations;

static SUICIDE_CALLBACK templateSuicide;

static void injectTemplateParm( SCOPE scope, PTREE parm, char *name );


static void templateSuicideHandler( void )
{
    activeInstantiations.inst_stack = NULL;
    templateData.curr_depth = 0;
}

static SYMBOL firstSymbol( SCOPE scope )
{
    SYMBOL first;

    first = ScopeOrderedFirst( scope );
    DbgAssert( first != NULL );
    return( first );
}

static void verifyOKToProceed( TOKEN_LOCN *locn )
{
    templateData.curr_depth++;
    if( templateData.curr_depth > templateData.max_depth ) {
        if( ! templateData.depth_diagnosed ) {
            templateData.depth_diagnosed = TRUE;
            SetErrLoc( locn );
            CErr2( ERR_TEMPLATE_DEPTH_EXHAUSTED, templateData.max_depth * 2 );
            CSuicide();
        }
    }
}

static void pushInstContext( TEMPLATE_CONTEXT *ctx,
                             enum template_context_type id,
                             TOKEN_LOCN *locn, void *extra_info )
{
    verifyOKToProceed( locn );
    ctx->id = id;
    ctx->locn = locn;
    ctx->u.any = extra_info;
    StackPush( &(activeInstantiations.inst_stack), ctx );
}

static void popInstContext( void )
{
    templateData.curr_depth--;
    StackPop( &(activeInstantiations.inst_stack) );
}

boolean IsTemplateInstantiationActive( void )
/*******************************************/
{
    return templateData.curr_depth > 0;
}

static TYPE extractTemplateClass( TEMPLATE_CONTEXT *ctx )
{
    SYMBOL sym;

    sym = firstSymbol( ctx->u.scope );
    if( sym == NULL ) {
        return( TypeError );
    }
    DbgAssert( sym->id == SC_TYPEDEF );
    return( sym->sym_type );
}

static void displayActiveInstantiations( NESTED_POST_CONTEXT *blk )
{
    TEMPLATE_CONTEXT *ctx;

#ifndef NDEBUG
    if( blk != &(activeInstantiations.registration) ) {
        CFatal( "registered call-back for template locations incorrect" );
    }
#else
    blk = blk;
#endif
    Stack_forall( activeInstantiations.inst_stack, ctx ) {
        if( ctx->locn != NULL ) {
            switch( ctx->id ) {
            case TCTX_CLASS_DEFN:
                AddNoteMessage( INF_TEMPLATE_CLASS_DEFN_TRACEBACK,
                                extractTemplateClass( ctx ), ctx->locn );
                break;
            case TCTX_FN_DEFN:
                AddNoteMessage( INF_TEMPLATE_FN_DEFN_TRACEBACK,
                                ctx->u.sym, ctx->locn );
                break;
            case TCTX_MEMBER_DEFN:
                AddNoteMessage( INF_TEMPLATE_MEMBER_DEFN_TRACEBACK,
                                ctx->locn );
                break;
            case TCTX_FN_BIND:
                AddNoteMessage( INF_TEMPLATE_FN_BIND_TRACEBACK,
                                ctx->u.sym, ctx->locn );
                break;
            case TCTX_FN_BIND_AND_GEN:
                AddNoteMessage( INF_TEMPLATE_FN_BIND_AND_GEN_TRACEBACK,
                                ctx->u.sym, ctx->locn );
                break;
            }
        }
    }
}

void TemplateSetDepth( unsigned depth )
/*************************************/
{
    if( depth < 2 ) {
        /* we need at least 2 in order to bind a function */
        depth = 2;
    }
    templateData.max_depth = depth;
}

static void templateInit( INITFINI* defn )
{
    defn = defn;
    if( CompFlags.dll_subsequent ) {
        currentTemplate = NULL;
        allClassTemplates = NULL;
        allFunctionTemplates = NULL;
        memset( &templateData, 0, sizeof( templateData ) );
    }
    templateData.max_depth = TEMPLATE_MAX_DEPTH;
    activeInstantiations.registration.call_back = displayActiveInstantiations;
    CtxRegisterPostContext( &(activeInstantiations.registration) );
    templateSuicide.call_back = templateSuicideHandler;
    RegisterSuicideCallback( &templateSuicide );
    carveTEMPLATE_INFO = CarveCreate( sizeof( TEMPLATE_INFO ), BLOCK_TEMPLATE_INFO );
    carveCLASS_INST = CarveCreate( sizeof( CLASS_INST ), BLOCK_CLASS_INST );
    carveTEMPLATE_MEMBER = CarveCreate( sizeof( TEMPLATE_MEMBER ), BLOCK_TEMPLATE_MEMBER );
    carveFN_TEMPLATE = CarveCreate( sizeof( FN_TEMPLATE ), BLOCK_FN_TEMPLATE );
}

static void templateFini( INITFINI *defn )
{
    defn = defn;
    CarveDestroy( carveTEMPLATE_INFO );
    CarveDestroy( carveCLASS_INST );
    CarveDestroy( carveTEMPLATE_MEMBER );
    CarveDestroy( carveFN_TEMPLATE );
}

INITDEFN( template, templateInit, templateFini )

static TEMPLATE_INFO *classInstTemplateInfo( TYPE cls )
{
    SCOPE scope;

    cls = TypedefRemove( cls );
    DbgAssert( ( cls->id == TYP_CLASS )
            && ( cls->flag & TF1_INSTANTIATION ) );

    scope = cls->u.c.scope;
    DbgAssert( ScopeType( scope, SCOPE_CLASS ) );

    scope = scope->enclosing;
    DbgAssert( ScopeType( scope, SCOPE_TEMPLATE_INST ) );

    scope = scope->enclosing;
    if( ScopeType( scope, SCOPE_TEMPLATE_SPEC_PARM ) ) {
        scope = scope->enclosing;
    }

    DbgAssert( ScopeType( scope, SCOPE_TEMPLATE_PARM ) );

    return scope->owner.tinfo;
}

static TEMPLATE_INFO *classUnboundTemplateInfo( TYPE cls )
{
    SCOPE scope;

    cls = TypedefRemove( cls );
    DbgAssert( ( cls->id == TYP_CLASS )
            && ( cls->flag & TF1_UNBOUND ) );

    scope = cls->u.c.scope;
    DbgAssert( ScopeType( scope, SCOPE_CLASS ) );

    scope = scope->enclosing;
    DbgAssert( ScopeType( scope, SCOPE_TEMPLATE_PARM ) );

    return scope->owner.tinfo;
}

static TYPE setArgIndex( SYMBOL sym, unsigned index )
{
    TYPE type;

    type = sym->sym_type;
    DbgAssert( type->id == TYP_GENERIC );
    DbgAssert( type->next == NULL );
    type->u.g.index = index;
    type = CheckDupType( type );
    sym->sym_type = type;
    return type;
}

void TemplateDeclInit( TEMPLATE_DATA *data )
/***********************************************************/
{
    StackPush( &currentTemplate, data );
    CErrCheckpoint( &(data->errors) );
    data->all_generic = TRUE;
    data->args = NULL;
    data->nr_args = 0;
    data->spec_args = NULL;
    data->unbound_type = NULL;
    data->decl_scope = ScopeBegin( SCOPE_TEMPLATE_DECL );
    data->defn = NULL;
    data->member_defn = NULL;
    data->template_name = NULL;
    data->template_scope = NULL;
    data->locn.src_file = NULL;
    data->defn_found = FALSE;
    data->member_found = FALSE;
    data->defn_added = FALSE;
}

static void validateNonTypeParameterType( TYPE type )
{
    TYPE trimmed_type;

    trimmed_type = TypedefModifierRemoveOnly( type );
    if( ( trimmed_type->id == TYP_POINTER ) // reference is also ok
     || ( trimmed_type->id == TYP_MEMBER_POINTER )
     || ( trimmed_type->id == TYP_GENERIC ) ) {
        return;
    }

    if( IntegralType( trimmed_type ) == NULL ) {
        CErr2p( ERR_INVALID_TEMPLATE_ARG_TYPE, trimmed_type );
    }
}

void TemplateDeclAddArgument( DECL_INFO *new_dinfo )
{
    SYMBOL sym;
    char *name;

    currentTemplate->args = AddArgument( currentTemplate->args, new_dinfo );
    currentTemplate->nr_args++;

    name = new_dinfo->name;
    sym = new_dinfo->generic_sym;

    if( sym != NULL ) {
        /* template type parameter */
        new_dinfo->type = setArgIndex( sym, currentTemplate->nr_args );
        DbgAssert( name != NULL );
        sym = ScopeInsert( GetCurrScope(), sym, name );
    } else if( ( new_dinfo->type != NULL ) ) {
        /* template non-type parameter */
        currentTemplate->all_generic = FALSE;
        if( name != NULL ) {
            sym = ScopeInsert( GetCurrScope(),
                               AllocTypedSymbol( new_dinfo->type ), name );
        }
        validateNonTypeParameterType( new_dinfo->type );
    }
}

static unsigned getArgList( DECL_INFO *args, TYPE *type_list, char **names,
                            REWRITE **defarg_list, boolean allow_defargs )
{
    DECL_INFO *curr;
    unsigned count;
    boolean prev_defarg;

    /*
     * see 14.1 p11:
     * If a template-parameter has a default template-argument, all
     * subsequent template-parameters shall have a default
     * template-argument supplied.
     */
    prev_defarg = FALSE;
    count = 0;

    RingIterBeg( args, curr ) {
        if( type_list != NULL ) {
            type_list[count] = curr->type;
        }
        if( names != NULL ) {
            names[count] = curr->name;
        }
        if( defarg_list != NULL ) {
            //  Ensure that we NULL out curr->defarg_rewrite or else
            //  when we delete the DECL_INFO, the rewrite element gets
            //  freed as well. The rewrite info will be freed when the
            //  the template info is freed.
            if( ( defarg_list[count] != NULL ) && ( curr->has_defarg ) ) {
                CErr2p( ERR_DEFAULT_TEMPLATE_ARG_REDEFINED, curr->name );
                RewriteFree( curr->defarg_rewrite );
            } else if( curr->has_defarg ) {
                defarg_list[count] = curr->defarg_rewrite;
            }
            curr->defarg_rewrite = NULL;

            if( defarg_list[count] != NULL ) {
                prev_defarg = TRUE;
            } else if( prev_defarg ) {
                /* previous parameter had a default argument, but this one
                 * hasn't => error */
                if( curr->generic_sym ) {
                    SetErrLoc( &curr->generic_sym->locn->tl );
                } else {
                    SetErrLoc( &curr->sym->locn->tl );
                }
                CErr1( ERR_DEFAULT_ARGS_MISSING );
            }
        } else if( ! allow_defargs ) {
            if( curr->has_defarg && ! prev_defarg ) {
                CErr1( ERR_DEFAULT_ARG_IN_PARTIAL_SPEC );
                prev_defarg = TRUE;
            }
        }
        ++count;
    } RingIterEnd( curr )
    return( count );
}

static TEMPLATE_SPECIALIZATION *newTemplateSpecialization(
    TEMPLATE_DATA *data, TEMPLATE_INFO *tinfo )
{
    DECL_INFO *args;
    TEMPLATE_SPECIALIZATION *tspec;
    TEMPLATE_SPECIALIZATION *tprimary;
    unsigned arg_count;

    tinfo->nr_specs++;

    args = data->args;
    arg_count = getArgList( args, NULL, NULL, NULL, TRUE );
    tspec = CPermAlloc( sizeof( TEMPLATE_SPECIALIZATION ) );
    RingAppend( &tinfo->specializations, tspec );
    tprimary = RingFirst( tinfo->specializations );

    tspec->tinfo = tinfo;
    tspec->instantiations = NULL;
    tspec->member_defns = NULL;
    tspec->decl_scope = ( arg_count > 0 ) ? data->decl_scope : NULL;
    TokenLocnAssign( tspec->locn, data->locn );
    tspec->num_args = arg_count;
    tspec->type_list = CPermAlloc( arg_count * sizeof( TYPE ) );
    tspec->arg_names = CPermAlloc( arg_count * sizeof( char * ) );
    tspec->spec_args = data->spec_args;
    data->spec_args = NULL;
    tspec->ordering = NULL;
    tspec->defn = NULL;
    tspec->corrupted = FALSE;
    tspec->defn_found = FALSE;

    getArgList( args, tspec->type_list, tspec->arg_names, NULL, TRUE );

    return( tspec );
}

static TEMPLATE_INFO *newTemplateInfo( TEMPLATE_DATA *data )
{
    DECL_INFO *args;
    TEMPLATE_INFO *tinfo;
    TEMPLATE_SPECIALIZATION *tprimary;
    unsigned arg_count;

    args = data->args;
    arg_count = getArgList( args, NULL, NULL, NULL, TRUE );
    if( arg_count == 0 ) {
        CErr1( ERR_TEMPLATE_MUST_HAVE_ARGS );
    }

    tinfo = RingCarveAlloc( carveTEMPLATE_INFO, &allClassTemplates );
    tinfo->specializations = NULL;
    tinfo->unbound_templates = NULL;
    tinfo->nr_specs = 0;
    tprimary = newTemplateSpecialization( data, tinfo );
    /* RingFirst( tinfo->specializations ) is always the primary template */

    tinfo->sym = NULL;
    tinfo->defarg_list = CPermAlloc( arg_count * sizeof( REWRITE * ) );
    tinfo->free = FALSE;

    tprimary->defn = data->defn;
    tprimary->defn_found = data->defn_found;

    memset( tinfo->defarg_list, 0, arg_count * sizeof( REWRITE * ) );
    getArgList( args, NULL, NULL, tinfo->defarg_list, TRUE );
    return( tinfo );
}

static SYMBOL newTemplateSymbol( TEMPLATE_DATA *data )
{
    SYMBOL sym;
    TEMPLATE_INFO *tinfo;

    tinfo = newTemplateInfo( data );
    sym = AllocSymbol();
    sym->id = SC_CLASS_TEMPLATE;
    sym->u.tinfo = tinfo;
    sym->sym_type = TypeGetCache( TYPC_CLASS_TEMPLATE );
    tinfo->sym = sym;
    if( data->locn.src_file != NULL ) {
        SymbolLocnDefine( &(data->locn), sym );
    }
    sym = ScopeInsert( data->template_scope, sym, data->template_name );
    return( sym );
}

void TemplateUsingDecl( SYMBOL sym, TOKEN_LOCN *locn )
/****************************************************/
{
    SYMBOL new_sym;

    DbgAssert( sym->id == SC_CLASS_TEMPLATE );
    new_sym = SymCreateAtLocn( sym->sym_type
                             , SC_CLASS_TEMPLATE
                             , SF_NULL
                             , sym->name->name
                             , GetCurrScope()
                             , locn );
    if( new_sym != NULL ) {
        new_sym->u.tinfo = sym->u.tinfo;
    }
}

SYMBOL ClassTemplateLookup( SCOPE scope, char *name )
/***************************************************/
{
    SCOPE file_scope;
    SEARCH_RESULT *result;
    SYMBOL_NAME sym_name;
    SYMBOL sym;

    file_scope = ScopeNearestFileOrClass( scope );
    result = ScopeFindNaked( file_scope, name );
    if( result != NULL ) {
        sym_name = result->sym_name;
        ScopeFreeResult( result );
        sym = sym_name->name_type;
        if( sym != NULL && SymIsClassTemplateModel( sym ) ) {
            return( sym );
        }
    }

    return( NULL );
}

static boolean templateArgListsSame( DECL_INFO *args, TEMPLATE_INFO *tinfo )
{
    unsigned curr_count;
    unsigned i;
    DECL_INFO *curr;
    TEMPLATE_SPECIALIZATION *tprimary;

    tprimary = RingFirst( tinfo->specializations );
    curr_count = getArgList( args, NULL, NULL, NULL, TRUE );
    if( curr_count != tprimary->num_args ) {
        return( FALSE );
    }
    i = 0;
    RingIterBeg( args, curr ) {
        if( ! TypesIdentical( curr->type, tprimary->type_list[i] ) ) {
            return( FALSE );
        }
        ++i;
    } RingIterEnd( curr )
    return( TRUE );
}

static boolean sameArgNames( DECL_INFO *args, char **names )
{
    DECL_INFO *curr;

    RingIterBeg( args, curr ) {
        if( *names != curr->name ) {
            return( FALSE );
        }
        ++names;
    } RingIterEnd( curr )
    return( TRUE );
}

static char **getUniqueArgNames( DECL_INFO *args,
                                 TEMPLATE_SPECIALIZATION *tspec )
{
    unsigned arg_count;
    char **arg_names;

    arg_names = tspec->arg_names;
    if( ! sameArgNames( args, arg_names ) ) {
        arg_count = getArgList( args, NULL, NULL, NULL, TRUE );
        arg_names = CPermAlloc( arg_count * sizeof( char * ) );
        getArgList( args, NULL, arg_names, NULL, TRUE );
    }
    return( arg_names );
}

static boolean templateArgSame( PTREE left, PTREE right ) {
    if( ( left->op == PT_TYPE ) && ( right->op == PT_TYPE ) ) {
        return TypesIdentical( left->type, right->type );
    } else if( ( left->op == PT_INT_CONSTANT )
            && ( right->op == PT_INT_CONSTANT ) ) {
        // integer constant
        return ! U64Cmp( &left->u.int64_constant, &right->u.int64_constant);
    } else if( ( left->op == PT_SYMBOL ) && ( right->op == PT_SYMBOL ) ) {
        // unbound constant
        return TypesIdentical( left->u.symcg.symbol->sym_type,
                               right->u.symcg.symbol->sym_type );
    } else if( ( left->op == PT_TYPE ) && ( right->op == PT_SYMBOL ) ) {
        // unbound constant
        return TypesIdentical( left->type, right->u.symcg.symbol->sym_type );
    } else if( ( left->op == PT_SYMBOL ) && ( right->op == PT_TYPE ) ) {
        // unbound constant
        return TypesIdentical( left->u.symcg.symbol->sym_type, right->type );
    } else if( ( left->op == PT_SYMBOL )
            && ( right->op == PT_INT_CONSTANT ) ) {
        // left: unbound constant, right: bound constant
        return FALSE;
    } else if( ( left->op == PT_INT_CONSTANT )
            && ( right->op == PT_SYMBOL ) ) {
        // left: unbound constant, right: bound constant
        return FALSE;
    }

    // TODO: add missing cases
#ifndef NDEBUG
    DumpPTree( left );
    DumpPTree( right );
#endif
    CFatal( "not yet implemented: templateArgSame" );

    return FALSE;
}

static TEMPLATE_SPECIALIZATION *findMatchingTemplateSpecialization(
    TEMPLATE_INFO *tinfo, PTREE args )
{
    TEMPLATE_SPECIALIZATION *curr_spec;
    TEMPLATE_SPECIALIZATION *tspec;
    TEMPLATE_SPECIALIZATION *tprimary;
    SCOPE saved_scope;
    PTREE curr_list;
    PTREE spec_list;
    PTREE curr_arg;
    PTREE spec_arg;
    TYPE arg_type;
    SYMBOL curr, stop;
    unsigned i;
    boolean something_went_wrong;
    boolean is_primary;

    /* pre-process args */
    DbgAssert( args != NULL );
    something_went_wrong = FALSE;
    is_primary = TRUE;
    tprimary = RingFirst( tinfo->specializations );

    /* make sure declaration of template parameters are in the current scope */
    saved_scope = GetCurrScope();
    if( currentTemplate->args != NULL ) {
        SetCurrScope( currentTemplate->decl_scope );
        stop = ScopeOrderedStart( currentTemplate->decl_scope );
    } else {
        stop = NULL;
    }
    curr = NULL;

    for( curr_list = args, i = 0;
         curr_list != NULL;
         curr_list = curr_list->u.subtree[0], i++ ) {

        curr_arg = curr_list->u.subtree[1];

        if( ( curr_arg == NULL )
         || ( i >= tprimary->num_args ) ) {
            /* number of parameters don't match */
            /* error message: wrong number of template arguments */
            something_went_wrong = TRUE;
            break;
        }

        arg_type = tprimary->type_list[i];
        if( arg_type->id == TYP_GENERIC || arg_type->id == TYP_CLASS ) {
            arg_type = NULL;
        }

        if( stop != NULL ) {
            curr = ScopeOrderedNext( stop, curr );
            if( curr == NULL ) {
                stop = NULL;
            }
        }

        if( arg_type != NULL ) {
            curr_arg = AnalyseRawExpr( curr_arg );
            if( curr_arg->op == PT_ERROR ) {
                something_went_wrong = TRUE;
                break;
            }

            if( curr_arg->op == PT_SYMBOL ) {
                if( curr_arg->u.symcg.symbol != curr ) {
                    is_primary = FALSE;
                }
            } else {
                is_primary = FALSE;
            }
        } else {
            if( ( curr_arg->op == PT_TYPE )
             && ( curr_arg->type->id == TYP_TYPEDEF ) 
             && ( curr_arg->type->of->id == TYP_GENERIC ) ) {
                if ( curr_arg->type->of->u.g.index != ( i + 1 ) ) {
                    is_primary = FALSE;
                }
            } else {
                is_primary = FALSE;
            }
        }

        curr_list->u.subtree[1] = curr_arg;
    }

    if( currentTemplate->args != NULL ) {
        curr = NULL;
        stop = ScopeOrderedStart( currentTemplate->decl_scope );
        for(;;) {
            curr = ScopeOrderedNext( stop, curr );
            if( curr == NULL ) break;

            if( ( curr->sym_type->id == TYP_TYPEDEF )
             && ( curr->sym_type->of->id == TYP_GENERIC ) ) {
                /* TODO: check for unused symbol */
            } else {
                /* TODO: check for unused symbol */
            }
        }
    }

    SetCurrScope( saved_scope );

    if( something_went_wrong ) {
        if( i >= tprimary->num_args ) {
            CErr2p( ERR_WRONG_NR_TEMPLATE_ARGUMENTS, tinfo->sym );
        } else {
            /* TODO: diagnose error */
            CFatal( "not yet implemented: findMatchingTemplateSpecialization, error message" );
        }
        return NULL;
    }

    if( is_primary ) {
        return tprimary;
    }


    tspec = NULL;
    RingIterBeg( tinfo->specializations, curr_spec ) {
        if( curr_spec->spec_args == NULL ) {
            /* no need to match against the primary template */
            continue;
        }

        for( curr_list = args, spec_list = curr_spec->spec_args;
             ( curr_list != NULL ) && ( spec_list != NULL );
             curr_list = curr_list->u.subtree[0],
                 spec_list = spec_list->u.subtree[0] ) {

            curr_arg = curr_list->u.subtree[1];
            spec_arg = spec_list->u.subtree[1];
            if( ( curr_arg == NULL ) || ( spec_arg == NULL ) ) {
                break;
            }

            if( ! templateArgSame( spec_arg, curr_arg ) ) {
                break;
            }
        }

        if( ( curr_list == NULL ) && ( spec_list == NULL ) ) {
            tspec = curr_spec;
        }
    } RingIterEnd( curr_spec )

    return tspec;
}

static void updateTemplatePartialOrdering( TEMPLATE_INFO *tinfo,
                                           TEMPLATE_SPECIALIZATION *tspec )
{
    TEMPLATE_SPECIALIZATION *curr_spec;
    unsigned i;
    unsigned nr_specs;

    nr_specs = tinfo->nr_specs;
    if( tspec->spec_args != NULL ) {
        tspec->ordering = CMemAlloc( 16 * ( ( nr_specs - 2 ) / 128 + 1 ) );
    }

    i = 0;
    RingIterBeg( tinfo->specializations, curr_spec ) {
        if( curr_spec->spec_args == NULL ) {
        } else if( curr_spec == tspec ) {
            tspec->ordering[ i / 8 ] &= ~ ( 1 << ( i & 7 ) );
            i++;
        } else {
            SCOPE parm_scope;
            unsigned char mask;
            boolean bound;

            if( ( nr_specs - 2 ) & 128 ) {
                /* grow the bitmap as needed */
                unsigned char *old_mem;

                old_mem = curr_spec->ordering;
                curr_spec->ordering =
                    CMemAlloc( 16 * ( ( nr_specs - 2 ) / 128 + 1 ) );
                memcpy( curr_spec->ordering, old_mem,
                        16 * ( ( nr_specs - 2 ) / 128 ) );
                CMemFree( old_mem );
            }

            parm_scope = ScopeCreate( SCOPE_TEMPLATE_SPEC_PARM );
            ScopeSetEnclosing( parm_scope, tspec->decl_scope );
            BindExplicitTemplateArguments( parm_scope, NULL );

            bound = BindGenericTypes( parm_scope, tspec->spec_args,
                                      curr_spec->spec_args, FALSE, 0 );
#ifndef NDEBUG
            if( PragDbgToggle.templ_spec && bound ) {
                VBUF vbuf1, vbuf2;

                FormatPTreeList( curr_spec->spec_args, &vbuf1 );
                FormatPTreeList( tspec->spec_args, &vbuf2 );
                printf( "%s<%s> is at least as specialised as %s<%s>\n",
                        tinfo->sym->name->name, vbuf1.buf,
                        tinfo->sym->name->name, vbuf2.buf );
                VbufFree( &vbuf1 );
                VbufFree( &vbuf2 );
            }
#endif

            /* curr_spec is at least as specialized as tspec if (
             * bindings != NULL)
             */
            mask = 1 << ( ( nr_specs - 2 ) & 7 );
            curr_spec->ordering[ ( nr_specs - 2 ) / 8 ] &= ~ mask;
            curr_spec->ordering[ ( nr_specs - 2 ) / 8 ] |=
                bound ? mask : 0;

            ScopeBurn( parm_scope );

            parm_scope = ScopeCreate( SCOPE_TEMPLATE_SPEC_PARM );
            ScopeSetEnclosing( parm_scope, curr_spec->decl_scope );
            BindExplicitTemplateArguments( parm_scope, NULL );

            bound = BindGenericTypes( parm_scope, curr_spec->spec_args,
                                      tspec->spec_args, FALSE, 0 );
#ifndef NDEBUG
            if( PragDbgToggle.templ_spec && bound ) {
                VBUF vbuf1, vbuf2;

                FormatPTreeList( tspec->spec_args, &vbuf1 );
                FormatPTreeList( curr_spec->spec_args, &vbuf2 );
                printf( "%s<%s> is at least as specialised as %s<%s>\n",
                        tinfo->sym->name->name, vbuf1.buf,
                        tinfo->sym->name->name, vbuf2.buf );
                VbufFree( &vbuf1 );
                VbufFree( &vbuf2 );
            }
#endif

            /* tspec is at least as specialized as curr_spec if (
             * bindings != NULL)
             */
            mask = 1 << ( i & 7 );
            tspec->ordering[ i / 8 ] &= ~ mask;
            tspec->ordering[ i / 8 ] |= bound ? mask : 0;

            ScopeBurn( parm_scope );
            i++;
        }
    } RingIterEnd( curr_spec )
}

static TEMPLATE_SPECIALIZATION *mergeClassTemplates( TEMPLATE_DATA *data,
                                                     SYMBOL old_sym )
{
    DECL_INFO *args;
    TEMPLATE_INFO *tinfo;
    TEMPLATE_SPECIALIZATION *tspec;
    REWRITE *defn;
    REWRITE **defarg_list;
    boolean primary_specialization;
 
    tinfo = old_sym->u.tinfo;
    args = data->args;

    if( data->spec_args != NULL ) {
        primary_specialization = FALSE;
        tspec = findMatchingTemplateSpecialization( tinfo, data->spec_args );
        if( tspec == RingFirst( tinfo->specializations ) ) {
            CErr2p( ERR_TEMPLATE_SPECIALIZATION_MATCHES_PRIMARY, tinfo->sym );
            tspec = NULL;
        }
        if( tspec == NULL ) {
            tspec = newTemplateSpecialization( data, tinfo );
            updateTemplatePartialOrdering( tinfo, tspec );
        }
    } else if( data->unbound_type != NULL ) {
        PTREE parm;
        PTREE parms;
        SYMBOL curr;
        SYMBOL stop;
        SCOPE parm_scope;

        parm_scope = data->unbound_type->u.c.scope->enclosing;
        DbgAssert( ScopeType( parm_scope, SCOPE_TEMPLATE_PARM ) );

        /* TODO: factor out, see fakeUpTemplateParms */
        parms = NULL;
        curr = NULL;
        stop = ScopeOrderedStart( parm_scope );
        for(;;) {
            curr = ScopeOrderedNext( stop, curr );
            if( curr == NULL ) break;

            switch( curr->id ) {
              case SC_TYPEDEF:
                parm = PTreeType( curr->sym_type );
                break;

              case SC_STATIC:
                parm = PTreeIntConstant( curr->u.uval, TYP_SINT );
                parm->type = curr->sym_type;
                break;

              case SC_ADDRESS_ALIAS:
                parm = MakeNodeSymbol( curr->u.alias );
                break;

              default:
#ifndef NDEBUG
                DumpSymbol( curr );
#endif
                CFatal( "not yet implemented: mergeClassTemplates" );
            }
            parms = PTreeBinary( CO_LIST, parms, parm );
        }

        if( parms != NULL ) {
            unsigned num_parms;

            parms = NodeReverseArgs( &num_parms, parms );
            tspec = findMatchingTemplateSpecialization( tinfo, parms );

            if( tspec == NULL ) {
                if( ! ( data->member_found && data->args == NULL ) ) {
                    CErr2p( ERR_UNKNOWN_TEMPLATE_SPECIALIZATION, tinfo->sym );
                }
                primary_specialization = TRUE;
                tspec = RingFirst( tinfo->specializations );
            } else {
                if( data->member_found && data->args == NULL ) {
                    CErr2p( ERR_CANNOT_EXPLICITLY_SPECIALIZE_MEMBER, tinfo->sym );
                }
                primary_specialization = FALSE;
            }
        } else {
            primary_specialization = TRUE;
            tspec = RingFirst( tinfo->specializations );
        }

        PTreeFreeSubtrees( parms );
    } else {
        tspec = RingFirst( tinfo->specializations );
        primary_specialization = TRUE;

        if( ( data->nr_args != tspec->num_args )
         || ! templateArgListsSame( args, tinfo ) ) {
            CErr2p( ERR_CANT_OVERLOAD_CLASS_TEMPLATES, tinfo );
            return NULL;
        }
    }
    if( tspec->corrupted ) {
        return tspec;
    }
    defn = data->defn;
    defarg_list = primary_specialization ? tinfo->defarg_list : NULL;
    if( data->defn_found ) {
        if( tspec->defn_found ) {
            CErr2p( ERR_CANT_REDEFINE_CLASS_TEMPLATES, tinfo );
            RewriteFree( defn );
            data->defn = NULL;
            return( NULL );
        } else {
            RewriteFree( tspec->defn );
            tspec->defn = defn;
            tspec->defn_found = TRUE;
            data->defn_added = TRUE;
            tspec->arg_names = getUniqueArgNames( args, tspec );

            getArgList( args, tspec->type_list, tspec->arg_names,
                        defarg_list, primary_specialization );
        }
    } else {
        getArgList( args, NULL, NULL, defarg_list, primary_specialization );

        if( tspec->defn == NULL ) {
            tspec->defn = defn;
        } else {
            RewriteFree( defn );
        }
        data->defn = NULL;
    }

    return tspec;
}

static void addMemberEntry( TEMPLATE_SPECIALIZATION *tspec, SCOPE scope,
                            REWRITE *r, char **arg_names )
{
    TEMPLATE_MEMBER *extra_defn;

    extra_defn = RingCarveAlloc( carveTEMPLATE_MEMBER
                               , &(tspec->member_defns) );
    extra_defn->scope = scope;
    extra_defn->defn = r;
    extra_defn->arg_names = arg_names;
}

static void addClassTemplateMember( TEMPLATE_DATA *data, SYMBOL sym,
                                    TEMPLATE_SPECIALIZATION *tspec )
{
    char **arg_names;

    if( ( NULL == data) || ( NULL == sym) ){
        return;
    }

    if( ! data->member_found ) {
        return;
    }

    arg_names = getUniqueArgNames( data->args, tspec );
    addMemberEntry( tspec, GetCurrScope(), data->member_defn, arg_names );
}

static TYPE doParseClassTemplate( TEMPLATE_SPECIALIZATION *tspec,
                                  REWRITE *defn, TOKEN_LOCN *locn )
{
    TYPE new_type;
    DECL_SPEC *dspec;
    auto TEMPLATE_CONTEXT context;

    new_type = TypeError;
    if( ! tspec->corrupted ) {
        pushInstContext( &context, TCTX_CLASS_DEFN, locn, GetCurrScope() );
        dspec = ParseClassInstantiation( defn );
        popInstContext();
        if( dspec != NULL ) {
            new_type = dspec->partial;
            PTypeRelease( dspec );
        }
    }
    return( new_type );
}

static SYMBOL dupTemplateParm( SYMBOL old_parm )
{
    SYMBOL sym;

    sym = AllocSymbol();
    sym->id = old_parm->id;
    sym->sym_type = old_parm->sym_type;
    sym->flag = old_parm->flag;
    switch( old_parm->id ) {
    case SC_STATIC:
        if( old_parm->flag & SF_CONSTANT_INT64 ) {
            sym->flag |= SF_CONSTANT_INT64;
            sym->u.pval = old_parm->u.pval;
        } else {
            sym->u.uval = old_parm->u.uval;
        }
        break;
    case SC_ADDRESS_ALIAS:
        sym->u.alias = old_parm->u.alias;
        break;
    }
    return( sym );
}

static void copyWithNewNames( SCOPE old_scope, char **names )
{
    SYMBOL curr;
    SYMBOL stop;
    SYMBOL sym;

    curr = NULL;
    stop = ScopeOrderedStart( old_scope );
    for(;;) {
        curr = ScopeOrderedNext( stop, curr );
        if( curr == NULL ) break;
        sym = dupTemplateParm( curr );
        sym = ScopeInsert( GetCurrScope(), sym, *names );
        ++names;
    }
}

static void defineAllClassDecls( TEMPLATE_SPECIALIZATION *tspec )
{
    /*
        template <class T>
            class F;

        F<int> *p;
        typedef F<double> & REF;
        template <class T>
            class F {
                T x;
            };
             ^ we have to visit F<int> and F<double> to define them with
               this definition
    */
    CLASS_INST *curr;
    SCOPE save_enclosing;
    SCOPE save_scope;
    SCOPE inst_scope;
    SCOPE parm_scope;
    SCOPE old_parm_scope;
    auto TOKEN_LOCN location;

    SrcFileGetTokenLocn( &location );
    save_scope = GetCurrScope();
    ScopeAdjustUsing( save_scope, NULL );
    RingIterBeg( tspec->instantiations, curr ) {
        if( curr->specific ) {
            /* we shouldn't mess around with specific instantiations */
            continue;
        }
        /* we have to splice in the new parm scope under the old
         * INST scope because the parm names may have changed but
         * the class type must be exactly as before (it may have
         * been used in typedefs) */
        inst_scope = curr->scope;
        old_parm_scope = inst_scope->enclosing;

        SetCurrScope( old_parm_scope->enclosing );
        parm_scope = ScopeBegin( ScopeId( old_parm_scope ) );
        if( ScopeType( old_parm_scope, SCOPE_TEMPLATE_PARM ) ) {
            ScopeSetParmCopy( parm_scope, old_parm_scope );
        }
        copyWithNewNames( old_parm_scope, tspec->arg_names );
        save_enclosing = ScopeEstablishEnclosing( inst_scope, parm_scope );

        SetCurrScope( inst_scope );
        ScopeAdjustUsing( NULL, inst_scope );

        doParseClassTemplate( tspec, tspec->defn, &location );

        ScopeAdjustUsing( inst_scope, NULL );
        ScopeSetEnclosing( inst_scope, save_enclosing );
    } RingIterEnd( curr )
    SetCurrScope( save_scope );
    ScopeAdjustUsing( NULL, save_scope );
}

extern int WalkTemplateInst( SYMBOL sym, AInstSCOPE fscope  )
{
    TEMPLATE_INFO *tinfo;
    TEMPLATE_SPECIALIZATION *tspec;
    CLASS_INST *curr;

    tinfo = sym->u.tinfo;
    RingIterBeg( tinfo->specializations, tspec ) {
        RingIterBeg( tspec->instantiations, curr ) {
            if( !fscope( curr->scope ) ){
                return( FALSE );
            }
        } RingIterEnd( curr )
    } RingIterEnd( tspec )
   return( TRUE );
}

void TemplateDeclFini( void )
/***************************/
{
    TEMPLATE_DATA *data;
    TEMPLATE_SPECIALIZATION *tspec;
    char *name;
    SYMBOL sym;

    ScopeEnd( SCOPE_TEMPLATE_DECL );
    data = currentTemplate;
    name = data->template_name;
    sym = NULL;
    tspec = NULL;
    if( ( name != NULL )
     && ( ScopeType( GetCurrScope(), SCOPE_FILE )
       || ScopeType( GetCurrScope(), SCOPE_CLASS ) ) ) {
        DbgAssert( data->template_scope != NULL );
        sym = ClassTemplateLookup( data->template_scope, name );
        if( ( sym != NULL )
         && ( sym->name->containing == data->template_scope ) ) {
            tspec = mergeClassTemplates( data, sym );
        } else if( data->spec_args == NULL ) {
            sym = newTemplateSymbol( data );
            if( sym != NULL ) {
                tspec = RingFirst( sym->u.tinfo->specializations );
            }
        } else {
            /* TODO: error message */
            CFatal( "not yet implemented: TemplateDeclFini" );
        }

        if( ( sym != NULL ) && ( tspec != NULL ) ) {
            addClassTemplateMember( data, sym, tspec );
        }
    }
    if( CErrOccurred( &(data->errors) ) ) {
        if( sym != NULL ) {
            if( tspec == NULL ) {
                tspec = RingFirst( sym->u.tinfo->specializations );
            } else {
                tspec->corrupted = TRUE;
            }
        }
    } else {
        if( data->defn_added && ( tspec != NULL ) ) {
            defineAllClassDecls( tspec );
        }
    }

    FreeTemplateArgs( data->args );
    data->args = NULL;
    PTreeFreeSubtrees( data->spec_args );
    data->spec_args = NULL;

    StackPop( &currentTemplate );
}

static FN_TEMPLATE *newTemplateFunction( SYMBOL sym )
{
    FN_TEMPLATE *fn_defn;

    fn_defn = RingCarveAlloc( carveFN_TEMPLATE, &allFunctionTemplates );
    fn_defn->instantiations = NULL;
    fn_defn->sym = sym;
    fn_defn->decl_scope = GetCurrScope();
    ScopeKeep( fn_defn->decl_scope );
    fn_defn->defn = NULL;
    fn_defn->has_defn = FALSE;
    fn_defn->free = FALSE;
    return( fn_defn );
}

void TemplateFunctionCheck( SYMBOL sym, DECL_INFO *dinfo )
/********************************************************/
{
    if( ! SymIsFunction( sym ) ) {
        CErr1( ERR_NO_VARIABLE_TEMPLATES );
        return;
    }
    if( sym->id != SC_STATIC ) {
        sym->id = SC_FUNCTION_TEMPLATE;
    } else {
        sym->id = SC_STATIC_FUNCTION_TEMPLATE;
    }
    sym->sym_type = MakePlusPlusFunction( sym->sym_type );
}

void TemplateFunctionDeclaration( SYMBOL sym, boolean is_defn )
/*************************************************************/
{
    if( sym->u.defn == NULL ) {
        sym->u.defn = newTemplateFunction( sym );
        if( ! is_defn && ( sym->u.defn != NULL ) ) {
            sym->u.defn->defn = ParseGetRecordingInProgress( NULL );
        }
    }
}

void TemplateFunctionAttachDefn( DECL_INFO *dinfo )
/*************************************************/
{
    SYMBOL sym;
    REWRITE *r;
    FN_TEMPLATE *fn_templ;

    sym = dinfo->sym;
    if( sym == NULL ) {
        return;
    }
    r = dinfo->body;
    dinfo->body = NULL;
    fn_templ = sym->u.defn;
    DbgAssert( fn_templ != NULL );
    DbgAssert( ScopeType( GetCurrScope(), SCOPE_TEMPLATE_DECL ) );

    if( fn_templ->decl_scope != GetCurrScope() ) {
        // replace the decl_scope of function template declarations
        ScopeBurn( fn_templ->decl_scope );
        fn_templ->decl_scope = GetCurrScope();
    }

    if( fn_templ->has_defn ) {
        RewriteFree( r );
        CErr2p( ERR_FUNCTION_TEMPLATE_ALREADY_HAS_DEFN, sym );
    } else {
        FN_TEMPLATE_INST *fn_inst;

        RewriteFree( fn_templ->defn );
        fn_templ->has_defn = TRUE;
        fn_templ->defn = r;

        // if we already tried to instantiate the template function, we
        // will probably have to regenerate the parm_scope as the
        // template parameter names could have changed
        RingIterBeg( fn_templ->instantiations, fn_inst ) {
            SCOPE parm_scope;
            SYMBOL decl_stop, decl_curr;
            SYMBOL parm_stop, parm_curr;

            parm_scope = ScopeCreate( ScopeId( fn_inst->parm_scope ) );
            ScopeSetEnclosing( parm_scope, fn_inst->parm_scope->enclosing );

            decl_stop = ScopeOrderedStart( fn_templ->decl_scope );
            parm_stop = ScopeOrderedStart( fn_inst->parm_scope );
            decl_curr = NULL;
            parm_curr = NULL;

            for(;;) {
                decl_curr = ScopeOrderedNext( decl_stop, decl_curr );
                parm_curr = ScopeOrderedNext( parm_stop, parm_curr );
                if( ( parm_curr == NULL ) || ( decl_curr == NULL ) ) break;

                // reuse the symbol with a new name in a new scope
                parm_curr->name->name_type = NULL;
                parm_curr->name = NULL;

                ScopeInsert( parm_scope, parm_curr, decl_curr->name->name );
            }

            ScopeSetEnclosing( fn_inst->inst_scope, parm_scope );
            ScopeBurn( fn_inst->parm_scope );
            fn_inst->parm_scope = parm_scope;

        } RingIterEnd( fn_inst )
    }
    FreeDeclInfo( dinfo );
}


static DECL_INFO *attemptGen( arg_list *args, SYMBOL fn_templ,
                              PTREE templ_args, TOKEN_LOCN *locn,
                              SCOPE *templ_parm_scope, bgt_control *pcontrol )
{
    TYPE fn_type;
    DECL_INFO *dinfo;
    TEMPLATE_CONTEXT context;
    SCOPE decl_scope;
    SCOPE parm_scope;
    arg_list *parms;
    PTREE pparms, pargs;
    boolean bound;
    unsigned i;
    unsigned num_parms, num_args;
    int num_explicit;

    *templ_parm_scope = NULL;
    num_args = ( args != NULL ) ? args->num_args : 0;
    fn_type = FunctionDeclarationType( fn_templ->sym_type );
    if( fn_type == NULL ) {
        return( NULL );
    }

    dinfo = NULL;
    decl_scope = fn_templ->u.defn->decl_scope;

    pparms = NULL;
    pargs = NULL;
    for( i = 0; i < num_args; i++ ) {
        PTREE arg = PTreeType( args->type_list[i] );
        pargs = PTreeBinary( CO_LIST, pargs, arg );
    }

    pargs = NodeReverseArgs( &num_args, pargs );

    parm_scope = ScopeCreate( SCOPE_TEMPLATE_PARM );
    ScopeSetEnclosing( parm_scope, decl_scope );

#ifndef NDEBUG
    if( PragDbgToggle.templ_function ) {
        VBUF vbuf1, vbuf2;

        FormatPTreeList( templ_args, &vbuf1 );
        FormatPTreeList( pargs, &vbuf2 );
        printf( "attemptGen for %s<%s>(%s)\n",
                fn_templ->name->name, vbuf1.buf, vbuf2.buf );
        VbufFree( &vbuf1 );
        VbufFree( &vbuf2 );
        FormatSym( fn_templ, &vbuf1 );
        printf( "  symbol: %s ", vbuf1.buf );
        DbgDumpTokenLocn( fn_templ->locn );
        printf( "\n" );
        VbufFree( &vbuf1 );
    }
#endif

    num_explicit = BindExplicitTemplateArguments( parm_scope, templ_args );
    if( num_explicit >= 0 ) {
        SCOPE save_scope;

        pushInstContext( &context, TCTX_FN_BIND, locn, fn_templ );

        if( num_explicit >= 1 ) {
            /* reparse the function declaration to get any
             * typenames parsed correctly */
            save_scope = GetCurrScope();
            ScopeAdjustUsing( save_scope, parm_scope );
            SetCurrScope( parm_scope );

            dinfo = ReparseFunctionDeclaration( fn_templ->u.defn->defn );
            if( dinfo != NULL ) {
                VerifySpecialFunction( ScopeNearestNonTemplate( parm_scope ),
                                       dinfo );
                fn_type = dinfo->sym->sym_type;
                FreeDeclInfo( dinfo );
            } else {
                fn_type = NULL;
            }
            dinfo = NULL;

            ScopeAdjustUsing( GetCurrScope(), save_scope );
            SetCurrScope( save_scope );
        }

        if( fn_type != NULL ) {
            parms = fn_type->u.f.args;

            pparms = NULL;
            for( i = 0; i < parms->num_args; i++ ) {
                PTREE parm = PTreeType( parms->type_list[i] );
                pparms = PTreeBinary( CO_LIST, pparms, parm );
            }

            pparms = NodeReverseArgs( &num_parms, pparms );

            bound = BindGenericTypes( parm_scope, pparms, pargs, TRUE,
                                      num_explicit );
        }

        if( ( fn_type != NULL) && bound ) {
            /* just reparse the function declaration once more to get
             * the bound type */
            save_scope = GetCurrScope();
            ScopeAdjustUsing( save_scope, parm_scope );
            SetCurrScope( parm_scope );

            dinfo = ReparseFunctionDeclaration( fn_templ->u.defn->defn );

            if( dinfo != NULL ) {
                VerifySpecialFunction( ScopeNearestNonTemplate( parm_scope ),
                                       dinfo );
                *templ_parm_scope = parm_scope;
            }

            ScopeAdjustUsing( GetCurrScope(), save_scope );
            SetCurrScope( save_scope );
        } else if( fn_type != NULL ) {
#ifndef NDEBUG
            if( PragDbgToggle.templ_function ) {
                printf( "attemptGen: BindGenericTypes failed\n" );
            }
#endif
        }

        popInstContext();
    } else {
#ifndef NDEBUG
        if( PragDbgToggle.templ_function ) {
            printf( "attemptGen: BindExplicitTemplateArguments failed\n" );
        }
#endif
    }

    ScopeSetEnclosing( parm_scope, NULL );

    if( dinfo == NULL ) {
        ScopeBurn( parm_scope );
    }

    PTreeFreeSubtrees( pparms );
    PTreeFreeSubtrees( pargs );

    return( dinfo );
}

static SYMBOL buildTemplateFn( TYPE bound_type, SYMBOL sym, DECL_INFO *dinfo,
                               SCOPE parm_scope, TOKEN_LOCN *locn )
{
    SCOPE inst_scope;
    SYMBOL new_sym;
    FN_TEMPLATE *fn_templ;
    FN_TEMPLATE_INST *fn_inst;
    symbol_flag new_flags;
    symbol_class new_class;

    if( ScopeType( SymScope( sym ), SCOPE_CLASS ) ) {
        new_flags = ( sym->flag & SF_ACCESS );
        new_class = SC_MEMBER;
    } else {
        new_flags = ( sym->flag & SF_PLUSPLUS );
        new_class = SC_PUBLIC;
    }
    if( SymIsStatic( sym ) ) {
        new_class = SC_STATIC;
    }

    inst_scope = ScopeCreate( SCOPE_TEMPLATE_INST );
    ScopeSetEnclosing( inst_scope, parm_scope );
    ScopeSetEnclosing( parm_scope, SymScope( sym ) );

    new_sym = SymCreateAtLocn( bound_type
                             , new_class
                             , new_flags | SF_TEMPLATE_FN
                             , sym->name->name
                             , inst_scope
                             , locn );
    new_sym->u.alias = sym;
    fn_templ = sym->u.defn;

    DeclareDefaultArgs( parm_scope, dinfo );

    if( ( dinfo->proto_sym != NULL ) && SymIsDefArg( dinfo->proto_sym ) ) {
        SYMBOL *prev = &dinfo->proto_sym->thread;

        while ( (*prev)->thread != NULL ) {
            prev = &(*prev)->thread;
        }

        *prev = new_sym;
        new_sym = dinfo->proto_sym;
    }
    FreeDeclInfo( dinfo );

    fn_inst = CPermAlloc( sizeof( FN_TEMPLATE_INST ) );
    RingAppend( &fn_templ->instantiations, fn_inst );
    fn_inst->bound_sym = new_sym;
    SrcFileGetTokenLocn( &fn_inst->locn );
    fn_inst->parm_scope = parm_scope;
    fn_inst->inst_scope = inst_scope;
    fn_inst->processed = FALSE;

    return new_sym;
}

SYMBOL TemplateFunctionGenerate( SYMBOL sym, arg_list *args,
                                 PTREE templ_args, TOKEN_LOCN *locn )
/*******************************************************************/
{
    DECL_INFO *dinfo;
    FN_TEMPLATE *fn_templ;
    FN_TEMPLATE_INST *fn_inst;
    TYPE fn_type;
    SCOPE parm_scope;
    SYMBOL generated_fn;
    bgt_control control;

    control = BGT_TRIVIAL;
    dinfo = attemptGen( args, sym, templ_args, locn, &parm_scope, &control );
    if( dinfo == NULL ) {
        return NULL;
    }

    fn_type = dinfo->sym->sym_type;
    fn_templ = sym->u.defn;

    if( fn_type == NULL ) {
        FreeDeclInfo( dinfo );
        return NULL;
    }

    generated_fn = NULL;

    // check if we have already instantiated this template function
    RingIterBeg( fn_templ->instantiations, fn_inst ) {
        SYMBOL inst_sym;

        inst_sym = SymDefaultBase( fn_inst->bound_sym );

        if( TypeCompareExclude( fn_type, inst_sym->sym_type,
                                TC1_NOT_ENUM_CHAR ) ) {
            SYMBOL curr1 = NULL, curr2 = NULL;
            SYMBOL stop1, stop2;

            // also need to check parameter scopes
            stop1 = ScopeOrderedStart( parm_scope );
            stop2 = ScopeOrderedStart( fn_inst->parm_scope );

            for(;;) {
                curr1 = ScopeOrderedNext( stop1, curr1 );
                curr2 = ScopeOrderedNext( stop2, curr2 );

                if( ( curr1 == NULL ) || ( curr2 == NULL ) ) {
                    if( ( curr1 == NULL ) && ( curr2 == NULL ) ) {
                        // alread instantiated
                        generated_fn = fn_inst->bound_sym;
                    }

                    break;
                }

                if( ( curr1->id == SC_TYPEDEF )
                 && ( curr2->id == SC_TYPEDEF ) ) {
                    if( TypeCompareExclude( curr1->sym_type, curr2->sym_type,
                                            TC1_NULL ) ) {
                        continue;
                    }
                } else if( ( curr1->id == SC_STATIC )
                        && ( curr2->id == SC_STATIC ) ) {
                    if( curr1->u.uval == curr2->u.uval ) {
                        continue;
                    }
                } else if( ( curr1->id == SC_ADDRESS_ALIAS )
                        && (curr2->id == SC_ADDRESS_ALIAS ) ) {
                    if( curr1->u.alias == curr2->u.alias ) {
                        continue;
                    }
                }

                break;
            }
        }
    } RingIterEnd( fn_inst )

#ifndef NDEBUG
    if( PragDbgToggle.templ_function && ( generated_fn == NULL ) ) {
        VBUF vbuf1, vbuf2, vbuf3;
        FormatType( fn_type, &vbuf1, &vbuf2 );
        FormatTemplateParmScope( &vbuf3, parm_scope );
        printf( "TemplateFunctionGenerate: %s%s%s%s\n",
                vbuf1.buf, sym->name->name, vbuf3.buf, vbuf2.buf );
        VbufFree( &vbuf1 );
        VbufFree( &vbuf2 );
        VbufFree( &vbuf3 );
    }
#endif

    if( generated_fn == NULL ) {
        generated_fn = buildTemplateFn( fn_type, sym, dinfo, parm_scope,
                                        locn );
    } else {
        FreeDeclInfo( dinfo );
        ScopeBurn( parm_scope );
    }

    while( generated_fn != NULL ) {
        fn_type = FunctionDeclarationType( generated_fn->sym_type );
        if( fn_type != NULL ) {
            int type_args;
            arg_list *alist;

            alist = TypeArgList( fn_type );
            type_args = alist->num_args;

            if( type_args == args->num_args ) {
                return generated_fn;
            }

            if( type_args != 0 ) {
                if( type_args <= args->num_args+1 ) {
                    if( alist->type_list[type_args-1]->id == TYP_DOT_DOT_DOT ) {
                        return generated_fn;
                    }
                }
            }
        }

        if( ! SymIsDefArg( generated_fn ) ) {
            break;
        }
        generated_fn = generated_fn->thread;
    }

    return NULL;
}

static void commonTemplateClass( TEMPLATE_DATA *data, PTREE id, SCOPE scope, char *name )
{
    data->template_name = name;
    data->template_scope = ScopeType( scope, SCOPE_TEMPLATE_DECL ) ?
        scope->enclosing : scope;

    if( id->locn.src_file != NULL ) {
        TokenLocnAssign( data->locn, id->locn );
    }
}

void TemplateClassDeclaration( PTREE id, SCOPE scope, char *name )
/****************************************************************/
{
    TEMPLATE_DATA *data;
    TOKEN_LOCN *locn;
    REWRITE *r;

    data = currentTemplate;
    r = ParseGetRecordingInProgress( &locn );
    data->defn = r;
    commonTemplateClass( data, id, scope, name );
}

boolean TemplateClassDefinition( PTREE id, SCOPE scope, char *name )
/******************************************************************/
{
    TEMPLATE_DATA *data;
    TOKEN_LOCN *locn;
    REWRITE *r;
    SCOPE template_scope;

    data = currentTemplate;
    r = ParseGetRecordingInProgress( &locn );
    if( r == NULL ) {
        CErr1( ERR_SYNTAX );
        return( TRUE );
    }
    r = RewritePackageClassTemplate( r, locn );
    data->defn = r;
    data->defn_found = TRUE;
    template_scope = ( id->op == PT_ID ) ? GetCurrScope() : scope;
    commonTemplateClass( data, id, template_scope, name );
    return( r == NULL );
}

static boolean okForTemplateParm( PTREE parm )
{
    SYMBOL sym;
    SCOPE scope;

    sym = parm->u.symcg.symbol;
    sym = SymDeAlias( sym );
    parm->u.symcg.symbol = sym;
    if( SymIsStaticMember( sym ) ) {
        return( TRUE );
    }
    scope = SymScope( sym );
    if( ScopeType( scope, SCOPE_FILE ) ) {
        switch( sym->id ) {
        case SC_PUBLIC:
        case SC_EXTERN:
        case SC_NULL:
            return( TRUE );
        }
    }
    return( FALSE );
}

static PTREE templateParmSimpleEnough( TYPE arg_type, PTREE parm )
{
    PTREE sym_parm;

    switch( parm->op ) {
    case PT_ERROR:
    case PT_INT_CONSTANT:
        return( parm );
    case PT_SYMBOL:
        if( okForTemplateParm( parm ) ) {
            if( PointerType( arg_type ) != NULL ) {
                if( SymIsFunction( parm->u.symcg.symbol ) ) {
                    parm->type = arg_type;
                    return( parm );
                }
            } else if( TypeReference( arg_type ) != NULL ) {
                parm->type = arg_type;
                return( parm );
            }
        }
        break;
    case PT_UNARY:
        if( PointerType( arg_type ) != NULL ) {
            if( parm->cgop == CO_ADDR_OF ) {
                sym_parm = parm->u.subtree[0];
                if( sym_parm->op == PT_SYMBOL ) {
                    PTREE oldparm = parm;
                    parm->u.subtree[0] = NULL;
                    /* reduce parm to a PT_SYMBOL */
                    parm = sym_parm;
                    if( okForTemplateParm( parm ) ) {
                        /* Only delete oldparm if we are returning success */
                        PTreeFreeSubtrees( oldparm );
                        parm->type = arg_type;
                        return( parm );
                    }
                }
            }
        } else if( MemberPtrType( arg_type ) != NULL ) {
            /* TODO: handle member function pointers */
            CFatal( "not yet implemented: member function pointer" );
        }
        break;
    case PT_BINARY:
        if( parm->cgop == CO_CONVERT ) {
            sym_parm = parm->u.subtree[1];
            if( sym_parm->op == PT_SYMBOL ) {
                PTREE oldparm = parm;
                parm->u.subtree[1] = NULL;
                /* reduce parm to a PT_SYMBOL */
                parm = sym_parm;
                if( okForTemplateParm( parm ) ) {
                    /* Only delete oldparm if we are returning success */
                    PTreeFreeSubtrees( oldparm );
                    parm->type = arg_type;
                    return( parm );
                }
            }
        }
        break;
    }
    PTreeErrorExpr( parm, ERR_INVALID_TEMPLATE_PARM );
    return( parm );
}

static boolean suitableForIntegralParm( PTREE parm )
{
    switch( parm->op ) {
    case PT_INT_CONSTANT:
        return( TRUE );
    }
    return( FALSE );
}

static boolean suitableForAddressParm( PTREE parm )
{
    switch( parm->op ) {
    case PT_SYMBOL:
        return( TRUE );
    }
    return( FALSE );
}

static PTREE processIndividualParm( TYPE arg_type, PTREE parm )
{
    parm = AnalyseRawExpr( parm );
    if( parm->op == PT_ERROR ) {
        return( parm );
    }
    parm = CastImplicit( parm, arg_type, CNV_FUNC_ARG, &diagTempParm );
    if( parm->op == PT_ERROR ) {
        return( parm );
    }
    parm = templateParmSimpleEnough( arg_type, parm );
    if( IntegralType( arg_type ) != NULL ) {
        if( ! suitableForIntegralParm( parm ) ) {
            PTreeErrorExpr( parm, ERR_TEMPLATE_ARG_NON_CONSTANT );
        }
    } else {
        if( ! suitableForAddressParm( parm ) ) {
            PTreeErrorExpr( parm, ERR_TEMPLATE_ARG_NOT_SYMBOL );
        }
    }
    return( parm );
}

static PTREE processClassTemplateParms( TEMPLATE_INFO *tinfo, PTREE parms,
                                        boolean *is_generic )
{
    SCOPE save_scope;
    SCOPE parm_scope;
    PTREE list;
    PTREE parm;
    TYPE arg_type;
    TEMPLATE_SPECIALIZATION *tprimary;
    unsigned num_parms;
    unsigned i;
    boolean something_went_wrong;
    boolean inside_decl_scope;
    TOKEN_LOCN start_locn;

    something_went_wrong = FALSE;
    *is_generic = FALSE;

    save_scope = GetCurrScope();
    inside_decl_scope = ScopeType( save_scope, SCOPE_TEMPLATE_DECL )
                     && ( save_scope->ordered != NULL ) ;

    parms = NodeReverseArgs( &num_parms, parms );
    tprimary = RingFirst( tinfo->specializations );

    if( tprimary->corrupted ) {
        something_went_wrong = TRUE;
    }
    /* Check for argument overflow */
    if( num_parms > tprimary->num_args ) {
        CErr2p( ERR_TOO_MANY_TEMPLATE_PARAMETERS, tinfo );
        something_went_wrong = TRUE;
    } else if( ! something_went_wrong ) {
        if( ! inside_decl_scope ) {
            parm_scope = ScopeCreate( SCOPE_TEMPLATE_PARM );
            ScopeSetEnclosing( parm_scope, SymScope( tinfo->sym ) );
        }
        SrcFileGetTokenLocn( &start_locn );

        list = parms;
        i = 0;

        for( i = 0; ; list = list->u.subtree[0] ) {
            arg_type = TypedefRemove( tprimary->type_list[i] );
            if( arg_type->id == TYP_GENERIC ) {
                if( ! inside_decl_scope 
                 && ( arg_type->u.g.index - 1 != i ) ) {
                    /* a generic type might have already been bound - we
                     * should take that into account */
                    SEARCH_RESULT *result;

                    result = ScopeFindMember( parm_scope,
                                              tprimary->arg_names[arg_type->u.g.index - 1] );
                    if( result != NULL ) {
                        arg_type = TypedefRemove( result->sym_name->name_type->sym_type );
                        ScopeFreeResult( result );
                    } else {
                        arg_type = NULL;
                    }
                } else {
                    arg_type = NULL;
                }
            } else if( arg_type->id == TYP_CLASS ) {
                arg_type = NULL;
            }

            parm = list->u.subtree[1];
            if( parm == NULL ) {
                if( ! inside_decl_scope ) {
                    SetCurrScope( parm_scope );
                }

                if( tinfo->defarg_list[i] == NULL ) {
                    /* the rewrite stuff would have killed our location so approximate */
                    SetErrLoc( &start_locn );
                    CErr2p( ERR_TOO_FEW_TEMPLATE_PARAMETERS, tinfo );
                    something_went_wrong = TRUE;
                    break;  /* from for loop */
                } else {
                    void (*last_source)( void );
                    REWRITE *save_token;
                    REWRITE *last_rewrite;
                    REWRITE *defarg_rewrite;

                    ParseFlush();
                    save_token = RewritePackageToken();
                    last_source = SetTokenSource( RewriteToken );
                    defarg_rewrite = tinfo->defarg_list[i];
                    last_rewrite = RewriteRewind( defarg_rewrite );

                    if( arg_type != NULL ) {
                        parm = ParseTemplateIntDefArg();
                    } else {
                        parm = ParseTemplateTypeDefArg();
                    }

                    RewriteClose( last_rewrite );
                    ResetTokenSource( last_source );
                    RewriteRestoreToken( save_token );
                }
            }

            if( parm == NULL ) {
                something_went_wrong = TRUE;
                break;
            }

            if( parm->op != PT_TYPE ) {
                if( arg_type != NULL ) {
                    if( inside_decl_scope && ! currentTemplate->all_generic ) {
                        parm = AnalyseRawExpr( parm );
                        if( parm->op == PT_ERROR ) {
                            something_went_wrong = TRUE;
                        }
                    } else {
                        parm = processIndividualParm( arg_type, parm );
                        if( parm->op == PT_ERROR ) {
                            something_went_wrong = TRUE;
                        }
                    }
                } else {
                    /* non-type parameter supplied for type argument */
                    parm = AnalyseRawExpr( parm );
                    if( parm->op != PT_ERROR ) {
                        PTreeErrorExpr( parm, ERR_NON_TYPE_PROVIDED_FOR_TYPE );
                    }
                    something_went_wrong = TRUE;
                }
            } else {
                if( arg_type != NULL ) {
                    /* type parameter supplied for non-type argument */
                    PTreeErrorExpr( parm, ERR_TYPE_PROVIDED_FOR_NON_TYPE );
                    something_went_wrong = TRUE;
                }
            }
            list->u.subtree[1] = parm;

            SetCurrScope( save_scope );
            if( something_went_wrong )
                break;

            if( parm->op == PT_TYPE ) {
                TYPE type;

                type = parm->type;

                while( type != NULL ) {
                    if( type->id == TYP_GENERIC ) {
                        *is_generic = TRUE;
                        break;
                    } else if( type->id == TYP_CLASS ) {
                        *is_generic |= ( type->flag & TF1_GENERIC );
                        break;
                    } else if( type->id == TYP_TYPENAME ) {
                        *is_generic = TRUE;
                        break;
                    }
                    type = type->of;
                }
            } else if( parm->op == PT_SYMBOL ) {
                if( parm->u.symcg.symbol->id == SC_NULL ) {
                    *is_generic = TRUE;
                }
            }

            if( ! inside_decl_scope ) {
                injectTemplateParm( parm_scope, parm, tprimary->arg_names[i] );
                arg_type = TypedefRemove( tprimary->type_list[i] );
            }

            ++i;
            if( i >= tprimary->num_args )
                break;

            if( list->u.subtree[0] == NULL ) {
                list->u.subtree[0] = PTreeBinary( CO_LIST, NULL, NULL );
            }
        }

        SetCurrScope( save_scope );

        if( ! inside_decl_scope ) {
            /* we don't need the parm_scope any more */
            ScopeSetEnclosing( parm_scope, NULL );
            ScopeBurn( parm_scope );
        }
    }

    if( something_went_wrong ) {
        NodeFreeDupedExpr( parms );
        parms = NULL;
    }
    return( parms );
}


static boolean sameConstantInt( SYMBOL s1, SYMBOL s2 )
{
    INT_CONSTANT con1;
    INT_CONSTANT con2;

    SymConstantValue( s1, &con1 );
    SymConstantValue( s2, &con2 );
    return 0 == U64Cmp( &con1.value, &con2.value );
}

boolean TemplateParmEqual( SYMBOL parm1, SYMBOL parm2 )
/*****************************************************/
{
    SYMBOL sym1;
    SYMBOL sym2;

    if( SymIsConstantInt( parm1 ) && SymIsConstantInt( parm2 ) ) {
        return sameConstantInt( parm1, parm2 );
    }
    if( SymIsTypedef( parm1 ) && SymIsTypedef( parm2 ) ) {
        return( TypesIdentical( parm1->sym_type, parm2->sym_type ) );
    }
    sym1 = SymAddressOf( parm1 );
    sym2 = SymAddressOf( parm2 );
    if( sym1 != NULL && sym2 != NULL ) {
        return( sym1 == sym2 );
    }
    return( FALSE );
}

static boolean parmsDifferent( SYMBOL temp_arg, PTREE temp_parm )
{
    SYMBOL sym;

    if( SymIsConstantInt( temp_arg ) ) {
        INT_CONSTANT con;
        switch( temp_parm->op ) {
        case PT_INT_CONSTANT:
            SymConstantValue( temp_arg, &con );
            if( 0 == U64Cmp( &con.value, &temp_parm->u.int64_constant ) ) {
                return( FALSE );
            }
            break;
        }
    } else if( SymIsTypedef( temp_arg ) ) {
        if( temp_parm->op == PT_TYPE ) {
            if( TypeCompareExclude( temp_arg->sym_type, temp_parm->type,
                                    TC1_NOT_ENUM_CHAR ) ) {
                return( FALSE );
            }
        }
    } else {
        sym = SymAddressOf( temp_arg );
        if( sym != NULL ) {
            if( temp_parm->op == PT_SYMBOL ) {
                if( sym == temp_parm->u.symcg.symbol ) {
                    return( FALSE );
                }
            }
        }
    }
    return( TRUE );
}

static boolean sameParms( SCOPE parm_scope, PTREE parms )
{
    SYMBOL curr;
    SYMBOL stop;
    PTREE list;
    PTREE parm;

    list = parms;
    curr = NULL;
    stop = ScopeOrderedStart( parm_scope );
    for(;;) {
        if( list == NULL ) {
            DbgAssert( ScopeOrderedNext( stop, curr ) == NULL );
            return( TRUE );
        }
        curr = ScopeOrderedNext( stop, curr );
        if( curr == NULL ) break;
        parm = list->u.subtree[1];
        if( parmsDifferent( curr, parm ) ) break;
        list = list->u.subtree[0];
    }
    return( FALSE );
}

static SCOPE findInstScope( TEMPLATE_SPECIALIZATION *tspec, PTREE parms,
                            CLASS_INST **inst )
{
    CLASS_INST *curr;
    SCOPE parm_scope;

    RingIterBeg( tspec->instantiations, curr ) {
        parm_scope = curr->scope->enclosing;
        if( ScopeType( parm_scope, SCOPE_TEMPLATE_SPEC_PARM ) ) {
            parm_scope = parm_scope->enclosing;
        }
        if( sameParms( parm_scope, parms ) ) {
            *inst = curr;
            return( curr->scope );
        }
    } RingIterEnd( curr )
    return( NULL );
}

static CLASS_INST *newClassInstantiation( TEMPLATE_SPECIALIZATION *tspec,
                                          TYPE unbound_type, SCOPE scope,
                                          boolean specific )
{
    CLASS_INST *new_inst;

    new_inst = RingCarveAlloc( carveCLASS_INST, &(tspec->instantiations) );
    scope->owner.inst = new_inst;
    new_inst->unbound_type = unbound_type;
    new_inst->scope = scope;
    new_inst->inlines_scope = NULL;
    new_inst->inlines_enclosing = NULL;
    new_inst->inlines = NULL;
    new_inst->members = NULL;
    new_inst->locn.src_file = NULL;
    new_inst->must_process = FALSE;
    new_inst->dont_process = FALSE;
    new_inst->processed = FALSE;
    new_inst->specific = FALSE;
    new_inst->locn_set = FALSE;
    new_inst->free = FALSE;
    new_inst->specific = specific;
    templateData.keep_going = TRUE;
    return( new_inst );
}

static SYMBOL templateArgSym( symbol_class sc, TYPE type )
{
    SYMBOL sym;

    sym = AllocSymbol();
    sym->id = sc;
    sym->sym_type = type;
    return( sym );
}

static SYMBOL templateArgTypedef( TYPE type )
{
    SYMBOL tsym;

    tsym = templateArgSym( SC_TYPEDEF, type );
    return tsym;
}

static void injectTemplateParm( SCOPE scope, PTREE parm, char *name )
{
    SYMBOL addr_sym;
    SYMBOL sym;
    TYPE parm_type;

    parm_type = parm->type;
    switch( parm->op ) {
    case PT_INT_CONSTANT:
        sym = templateArgSym( SC_STATIC, parm_type );
        DgStoreConstScalar( parm, parm_type, sym );
        break;
    case PT_TYPE:
        sym = templateArgTypedef( parm_type );
        break;
    case PT_SYMBOL:
        addr_sym = parm->u.symcg.symbol;
        if( PointerType( parm_type ) != NULL ) {
            parm_type = MakePointerTo( addr_sym->sym_type );
        } else {
            parm_type = addr_sym->sym_type;
        }
        sym = templateArgSym( SC_ADDRESS_ALIAS, parm_type );
        sym->u.alias = addr_sym;
        break;
    DbgDefault( "template parms are corrupted" );
    }
    if( sym != NULL ) {
        if( name == NULL ) {
            name = NameDummy();
        }
        sym = ScopeInsert( scope, sym, name );
    }
}

static void injectTemplateParms( TEMPLATE_SPECIALIZATION *tspec, SCOPE scope,
                                 PTREE parms, boolean unnamed )
{
    PTREE list;
    char **pname;
    char *name;

    pname = NULL;
    if( tspec != NULL ) {
        pname = tspec->arg_names;
    }
    for( list = parms; list != NULL; list = list->u.subtree[0] ) {
        if( ! unnamed && ( pname != NULL ) ) {
            name = *pname;
            ++pname;
        } else {
            name = NameDummy();
        }
        if( list->u.subtree[1] ) {
            injectTemplateParm( scope, list->u.subtree[1], name );
        }
    }
}

static TYPE instantiateClass( TEMPLATE_INFO *tinfo, PTREE parms,
                              TEMPLATE_SPECIALIZATION *tspec,
                              TYPE unbound_type, SCOPE spec_parm_scope,
                              TOKEN_LOCN *locn )
{
    TYPE new_type;
    SCOPE file_scope;
    SCOPE save_scope;
    SCOPE inst_scope;
    SCOPE parm_scope;
    CLASS_INST *curr_instantiation;

    curr_instantiation = NULL;
    save_scope = GetCurrScope();
    ScopeAdjustUsing( save_scope, NULL );
    file_scope = SymScope( tinfo->sym );
    SetCurrScope( file_scope );
    parm_scope = ScopeBegin( SCOPE_TEMPLATE_PARM );
    ScopeSetParmClass( parm_scope, tinfo );
    if( spec_parm_scope != NULL ) {
        /*
         * In the case of a template specialization we have to use
         * two different parameter scopes:
         *
         * SCOPE_TEMPLATE_PARM is only used for mangling symbols
         * names (see fnname.c, appendScopeMangling)
         *
         * SCOPE_TEMPLATE_SPEC_PARM is used for the template parms
         * for the template specialization
         */
        ScopeSetEnclosing( spec_parm_scope, parm_scope );
        SetCurrScope( spec_parm_scope );
    }
    inst_scope = ScopeBegin( SCOPE_TEMPLATE_INST );
    curr_instantiation = newClassInstantiation( tspec, unbound_type,
                                                inst_scope, FALSE );
    if( locn != NULL ) {
        curr_instantiation->locn = *locn;
        curr_instantiation->locn_set = TRUE;
    }

    injectTemplateParms( tspec, parm_scope, parms, spec_parm_scope != NULL );
    ScopeAdjustUsing( NULL, inst_scope );

    new_type = doParseClassTemplate( tspec, tspec->defn, locn );

    ScopeAdjustUsing( inst_scope, save_scope );
    SetCurrScope( save_scope );

    return( new_type );
}

static TYPE createUnboundClass( TEMPLATE_INFO *tinfo,
                                PTREE parms, boolean is_generic )
{
    TYPE new_type;
    SCOPE file_scope;
    SCOPE save_scope;
    SCOPE parm_scope;
    TEMPLATE_SPECIALIZATION *tprimary;

    save_scope = GetCurrScope();
    file_scope = SymScope( tinfo->sym );
    SetCurrScope( file_scope );
    parm_scope = ScopeBegin( SCOPE_TEMPLATE_PARM );
    ScopeSetParmClass( parm_scope, tinfo );
    tprimary = RingFirst( tinfo->specializations );
    injectTemplateParms( tprimary, parm_scope, parms, FALSE );
    new_type = ClassUnboundTemplate( tinfo->sym->name->name );
    new_type->flag |= is_generic ? TF1_GENERIC : 0;
    ScopeOpen( new_type->u.c.scope );
    SetCurrScope( save_scope );

    return( new_type );
}

static TEMPLATE_SPECIALIZATION *
findTemplateClassSpecialization( TEMPLATE_INFO *tinfo, PTREE parms,
                                 SCOPE *parm_scope )
{
    struct candidate_ring {
        struct candidate_ring *next;
        TEMPLATE_SPECIALIZATION *tspec;
        SCOPE parm_scope;
        unsigned idx;
    } *candidate_list;
    struct candidate_ring *candidate_iter;

    TEMPLATE_SPECIALIZATION *curr_spec;
    TEMPLATE_SPECIALIZATION *tspec;
    TEMPLATE_SPECIALIZATION *tprimary;
    PTREE spec_list;
    unsigned num_args;
    unsigned i;
    boolean ambiguous;

    candidate_list = NULL;
    tprimary = RingFirst( tinfo->specializations );
    num_args = tprimary->num_args;
    ambiguous = FALSE;

#ifndef NDEBUG
    if( PragDbgToggle.templ_spec && ( tinfo->nr_specs > 1 )) {
        VBUF vbuf;

        FormatPTreeList( parms, &vbuf );
        printf( "try to find template class specialisation for %s<%s>\n",
                tinfo->sym->name->name, vbuf.buf );
        VbufFree( &vbuf );
    }
#endif

    i = 0;
    RingIterBeg( tinfo->specializations, curr_spec ) {
        spec_list = curr_spec->spec_args;
        if( spec_list != NULL ) {
            SCOPE parm_scope;
            boolean bound;

            parm_scope = ScopeCreate( SCOPE_TEMPLATE_SPEC_PARM );
            ScopeSetEnclosing( parm_scope, curr_spec->decl_scope );

            BindExplicitTemplateArguments( parm_scope, NULL );

            bound = BindGenericTypes( parm_scope, spec_list,
                                      parms, FALSE, 0 );
            if( bound ) {
#ifndef NDEBUG
                if( PragDbgToggle.templ_spec && ( tinfo->nr_specs > 1 )) {
                    VBUF vbuf;

                    FormatPTreeList( spec_list, &vbuf );
                    printf( "found specialisation candidate %s<%s>\n",
                            tinfo->sym->name->name, vbuf.buf );
                    VbufFree( &vbuf );
                }
#endif

                /* we have found a matching specialization, use partial
                 * ordering rules to determine which one to use. */
                if( candidate_list != NULL ) {
                    RingIterBegSafe( candidate_list, candidate_iter ) {
                        boolean curr_at_least_as_specialized;
                        boolean candidate_at_least_as_specialized;

                        curr_at_least_as_specialized =
                            curr_spec->ordering[ candidate_iter->idx / 8 ] & ( 1 << ( candidate_iter->idx & 7 ) );
                        candidate_at_least_as_specialized =
                            candidate_iter->tspec->ordering[ i / 8 ] & ( 1 << ( i & 7 ) );

                        if( curr_at_least_as_specialized
                         && ! candidate_at_least_as_specialized ) {
                            ScopeBurn( candidate_iter->parm_scope );
                            RingPrune( &candidate_list, candidate_iter );
                        } else if( candidate_at_least_as_specialized
                                && ! curr_at_least_as_specialized ) {
                            ScopeBurn( parm_scope );
                            parm_scope = NULL;
                            break;
                        }
                    } RingIterEndSafe( candidate_iter )
                }

                if( parm_scope != NULL ) {
                    candidate_iter =
                        RingAlloc( &candidate_list,
                                   sizeof( struct candidate_ring ) );
                    candidate_iter->tspec = curr_spec;
                    candidate_iter->parm_scope = parm_scope;
                    candidate_iter->idx = i;
                }
            }
            else
            {
                ScopeBurn( parm_scope );
                parm_scope = NULL;
            }

            i++;
        }
    } RingIterEnd( curr_spec );

    if( candidate_list == NULL ) {
        /* no matching specialization found, use primary template */
        tspec = RingFirst( tinfo->specializations );

#ifndef NDEBUG
        if( PragDbgToggle.templ_spec && ( tinfo->nr_specs > 1 )) {
            printf( "chose primary template %s ", tinfo->sym->name->name );
            DbgDumpTokenLocn( tinfo->sym->locn );
            printf( "\n" );
        }
#endif
    } else if( RingFirst( candidate_list ) == RingLast( candidate_list ) ) {
        /* exactly one matching specialization found, use it */

        candidate_iter = RingFirst( candidate_list );
        tspec = candidate_iter->tspec;
        *parm_scope = candidate_iter->parm_scope;

        RingFree( &candidate_list );

#ifndef NDEBUG
        if( PragDbgToggle.templ_spec && ( tinfo->nr_specs > 1 )) {
            VBUF vbuf;

            FormatPTreeList( tspec->spec_args, &vbuf );
            printf( "chose specialisation %s<%s> ",
                    tinfo->sym->name->name, vbuf.buf );
            DbgDumpTokenLocn( &tspec->locn );
            printf( "\n" );
            VbufFree( &vbuf );
        }
#endif

    } else {
        CErr2p( ERR_TEMPLATE_SPECIALIZATION_AMBIGUOUS, tinfo->sym );

        /* free instantiation parameters */
        RingIterBeg( candidate_list, candidate_iter ) {
            AddNoteMessage( INF_CANDIDATE_TEMPLATE_DEFINITION,
                            candidate_iter->tspec,
                            &candidate_iter->tspec->locn );
            ScopeBurn( candidate_iter->parm_scope );
        } RingIterEnd( candidate_iter )

        tspec = tprimary;
    }

    return tspec;
}

TYPE TemplateClassReference( PTREE tid, PTREE parms )
/***************************************************/
{
    char *template_name;
    TYPE typ;
    TEMPLATE_INFO *tinfo;
    SYMBOL sym;
    boolean is_generic;

    typ = TypeError;

    if( ( tid->sym_name == NULL ) && ( tid->flags & PTF_TYPENAME ) ) {
        NodeFreeDupedExpr( parms );
        return typ;
    }

    DbgAssert( tid->sym_name != NULL );
    DbgAssert( tid->sym_name->name_type != NULL );

    sym = tid->sym_name->name_type;
    if( ! SymIsClassTemplateModel( sym ) ) {
        DbgAssert( SymIsTypedef( sym ) );
        sym = classInstTemplateInfo( sym->sym_type )->sym;
    }

    tinfo = sym->u.tinfo;
    template_name = sym->name->name;

    parms = processClassTemplateParms( tinfo, parms, &is_generic );
    if( parms != NULL ) {
        UNBOUND_TEMPLATE *curr;
        unsigned int hash;

#ifndef NDEBUG
        if( PragDbgToggle.templ_inst ) {
            VBUF vbuf;

            FormatPTreeList( parms, &vbuf );
            printf( "referencing template %s<%s>%s\n",
                    template_name, vbuf.buf,
                    is_generic ? " (generic)" : "");
            VbufFree( &vbuf );
        }
#endif

        typ = NULL;
        hash = 0;

        RingIterBeg( tinfo->unbound_templates, curr ) {
            SCOPE parm_scope = curr->unbound_type->u.c.scope->enclosing;

            if( ( curr->hash == hash )
             && sameParms( parm_scope, parms ) ) {
                typ = curr->unbound_type;
                if( typ->of != NULL ) {
                    typ = typ->of;
                }
                break;
            }
        } RingIterEnd( curr )

        if( typ == NULL ) {
            typ = createUnboundClass( tinfo, parms, is_generic );
            if( typ != NULL ) {
                UNBOUND_TEMPLATE *unbound_templ =
                    CPermAlloc( sizeof( UNBOUND_TEMPLATE ) );
                RingAppend( &tinfo->unbound_templates, unbound_templ );
                unbound_templ->unbound_type = typ;
                unbound_templ->hash = 0;
            }
        }

        NodeFreeDupedExpr( parms );
    }
    return( typ );
}

void TemplateClassDirective( TYPE type, TOKEN_LOCN *locn,
                             tc_directive tcd_control )
/*******************************************************/
{
    CLASS_INST *inst;

    type = BindTemplateClass( type, locn, FALSE );
    inst = TypeClassInstantiation( type );

    if( inst != NULL ) {
        if( tcd_control & TCD_INSTANTIATE ) {
            inst->must_process = 1;
        }
        if( tcd_control & TCD_EXTERN ) {
            inst->dont_process = 1;
        }
    }
}

static PTREE fakeUpParm( SYMBOL sym )
{
    PTREE parm;

    parm = NULL;
    switch( sym->id ) {
    case SC_STATIC:
        if( sym->flag & SF_CONSTANT_INT64 ) {
            parm = PTreeInt64Constant( sym->u.pval->int64_constant,
                                       sym->sym_type->id );
        } else {
            parm = PTreeIntConstant( sym->u.uval, TYP_SINT );
            parm->type = sym->sym_type;
        }
        break;
    case SC_ADDRESS_ALIAS:
        parm = MakeNodeSymbol( sym->u.alias );
        if( PointerType( sym->sym_type ) ) {
            parm->type = MakePointerTo( parm->type );
        }
        break;
    }
    DbgAssert( parm != NULL );
    return( parm );
}

static PTREE fakeUpTemplateParms( SCOPE parm_scope, arg_list *type_args )
{
    TYPE *curr_type_arg;
    PTREE parm;
    PTREE parms;
    SYMBOL curr;
    SYMBOL stop;
    unsigned num_parms;

    curr_type_arg = type_args ? type_args->type_list : NULL;
    parms = NULL;
    curr = NULL;
    stop = ScopeOrderedStart( parm_scope );
    for(;;) {
        curr = ScopeOrderedNext( stop, curr );
        if( curr == NULL ) break;
        if( curr->id == SC_TYPEDEF ) {
            if( curr_type_arg ) {
                parm = PTreeType( BindTemplateClass( *curr_type_arg, NULL,
                                                     FALSE ) );
                ++curr_type_arg;
            } else {
                parm = PTreeType( BindTemplateClass( curr->sym_type, NULL,
                                                     FALSE ) );
            }
        } else {
            parm = fakeUpParm( curr );
        }
        parms = PTreeBinary( CO_LIST, parms, parm );
    }
    parms = NodeReverseArgs( &num_parms, parms );
    return( parms );
}

static TYPE makeBoundClass( TYPE unbound_class, SCOPE parm_scope,
                            arg_list *type_args, TOKEN_LOCN *locn )
{
    SCOPE spec_parm_scope = NULL;
    TYPE type_instantiated;
    TEMPLATE_INFO *tinfo;
    TEMPLATE_SPECIALIZATION *tspec;
    PTREE parms;

    type_instantiated = NULL;
    tinfo = classUnboundTemplateInfo( unbound_class );
    parms = fakeUpTemplateParms( parm_scope, type_args );

#ifndef NDEBUG
    if( PragDbgToggle.templ_inst ) {
        VBUF vbuf;

        FormatPTreeList( parms, &vbuf );
        printf( "instantiating template %s<%s>\n",
                tinfo->sym->name->name, vbuf.buf );
        VbufFree( &vbuf );
    }
#endif

    tspec = findTemplateClassSpecialization( tinfo, parms,
                                             &spec_parm_scope );
    type_instantiated =
        instantiateClass( tinfo, parms, tspec, unbound_class,
                          spec_parm_scope, locn );
    PTreeFreeSubtrees( parms );

    return( type_instantiated );
}

TYPE TemplateUnboundInstantiate( TYPE unbound_class, arg_list *type_args,
                                 TOKEN_LOCN *locn )
/***********************************************************************/
{
    SCOPE parm_scope;
    TYPE new_type;

    new_type = NULL;
    parm_scope = TemplateClassParmScope( unbound_class );
    if( parm_scope != NULL ) {
        new_type = makeBoundClass( unbound_class, parm_scope, type_args,
                                   locn );
    }
    return( new_type );
}

TYPE BoundTemplateClass( TYPE typ )
/*********************************/
{
    TYPE unbound = typ;
    TYPE bound = NULL;
    TYPE *tptr = NULL;

    if( unbound != NULL ) {
        const unsigned int mask =
            ( 1 << TYP_MODIFIER ) | ( 1 << TYP_TYPEDEF )
          | ( 1 << TYP_ARRAY ) | ( 1 << TYP_POINTER );
        while( ( 1 << unbound->id ) & mask ) {
            tptr = &unbound->of;
            unbound = *tptr;
        }

        if( ( unbound->id == TYP_CLASS )
         && ( unbound->flag & TF1_UNBOUND )
         && !( unbound->flag & TF1_GENERIC ) ) {
            if( unbound->of != NULL ) {
                bound = unbound->of;

                if( tptr != NULL ) {
                    *tptr = bound;
                }
            }
        }
    }

    return ( ( tptr == NULL ) && ( bound != NULL ) ) ? bound : typ;
}

TYPE BindTemplateClass( TYPE typ, TOKEN_LOCN *locn, boolean deref_ptrs )
/**********************************************************************/
{
    TYPE unbound = typ;
    TYPE bound = NULL;
    TYPE *tptr = NULL;

    if( unbound != NULL ) {
        const unsigned int mask =
            ( 1 << TYP_MODIFIER ) | ( 1 << TYP_TYPEDEF )
          | ( 1 << TYP_ARRAY )
          | ( deref_ptrs ? ( 1 << TYP_POINTER ) : 0 );
        while( ( 1 << unbound->id ) & mask ) {
            tptr = &unbound->of;
            unbound = *tptr;
        }

        if( ( unbound->id == TYP_CLASS )
         && ( unbound->flag & TF1_UNBOUND )
         && !( unbound->flag & TF1_GENERIC ) ) {
            if( unbound->of == NULL ) {
                bound = TemplateUnboundInstantiate( unbound, NULL, locn );
                DbgAssert( ( unbound->of == NULL )
                        || ( unbound->of == bound )
                        || ( bound == TypeError ) );
                unbound->of = bound;
            } else {
                bound = unbound->of;
            }

            if( ( bound != NULL ) && ( tptr != NULL ) ) {
                *tptr = bound;
            }
        }
    }

    return ( ( tptr == NULL ) && ( bound != NULL ) ) ? bound : typ;
}

void TemplateHandleClassMember( DECL_INFO *dinfo )
/************************************************/
{
    TEMPLATE_DATA *data;
    TOKEN_LOCN *locn;
    REWRITE *r;

    DbgAssert( dinfo->template_member );
    r = ParseGetRecordingInProgress( &locn );
    r = RewritePackageClassTemplateMember( r, locn );
    data = currentTemplate;
    data->member_defn = r;
    data->member_found = TRUE;
    data->template_name = SimpleTypeName( dinfo->id->u.subtree[0]->type );
    data->template_scope =
        ScopeNearestFileOrClass( TypeScope( dinfo->id->u.subtree[0]->type )->enclosing );
    data->unbound_type = dinfo->id->u.subtree[0]->type;
    FreeDeclInfo( dinfo );
}

void TemplateMemberAttachDefn( DECL_INFO *dinfo )
{
    CLASS_INST *instance;
    MEMBER_INST *member;
    SCOPE member_scope;

    if( ScopeType( GetCurrScope(), SCOPE_TEMPLATE_INST ) ) {
        member_scope = GetCurrScope();
    } else if( ScopeType( GetCurrScope(), SCOPE_CLASS )
            && ScopeType( GetCurrScope()->enclosing, SCOPE_TEMPLATE_INST ) ) {
        member_scope = GetCurrScope()->enclosing;
    } else {
        member_scope = NULL;
    }

    DbgAssert( member_scope != NULL );
    instance = member_scope->owner.inst;

    member = CPermAlloc( sizeof( MEMBER_INST ) );
    RingAppend( &(instance->members), member );
    member->dinfo = dinfo;
    member->scope = member_scope;
    member->class_parm_scope = instance->scope->enclosing;
    member->class_parm_enclosing = member->class_parm_scope->enclosing;
}

static boolean sameParmArgNames( SCOPE parm_scope, char **arg_names )
{
    SYMBOL curr;
    SYMBOL stop;

    curr = NULL;
    stop = ScopeOrderedStart( parm_scope );
    for(;;) {
        curr = ScopeOrderedNext( stop, curr );
        if( curr == NULL ) break;
        if( curr->name->name != *arg_names ) {
            return( FALSE );
        }
        ++arg_names;
    }
    return( TRUE );
}

/*
 * real instantiation of the template member takes place in
 * TemplateProcessInstantiations (but only if the symbol has been
 * referenced)
 */
static void instantiateMember( TEMPLATE_INFO *tinfo,
                               TEMPLATE_SPECIALIZATION *tspec,
                               CLASS_INST *instance,
                               TEMPLATE_MEMBER *member )
{
    SCOPE save_scope;
    SCOPE inst_scope;
    SCOPE class_parm_scope;
    SCOPE save_parm_enclosing;
    SCOPE parm_scope;
    char **member_arg_names;
    TOKEN_LOCN *locn;
    auto TEMPLATE_CONTEXT context;

    save_scope = GetCurrScope();
    ScopeAdjustUsing( save_scope, NULL );
    save_parm_enclosing = NULL;
    class_parm_scope = instance->scope->enclosing;
    member_arg_names = member->arg_names;

    DbgAssert( ScopeType( class_parm_scope, SCOPE_TEMPLATE_SPEC_PARM )
            || ScopeType( class_parm_scope, SCOPE_TEMPLATE_PARM ) );

    // we might be able to re-use the classes template-parm scope in
    // some cases
    if( ( ScopeType( class_parm_scope, SCOPE_TEMPLATE_SPEC_PARM )
       && ( class_parm_scope->enclosing->enclosing != member->scope ) )
     || ( ScopeType( class_parm_scope, SCOPE_TEMPLATE_PARM )
       && ( class_parm_scope->enclosing != member->scope ) )
     || ( tspec->arg_names != member_arg_names )
     || ! sameParmArgNames( class_parm_scope, member_arg_names ) ) {
        if( ScopeType( class_parm_scope, SCOPE_TEMPLATE_SPEC_PARM ) ) {
            save_parm_enclosing =
                ScopeSetEnclosing( class_parm_scope->enclosing,
                                   member->scope );
            SetCurrScope( class_parm_scope->enclosing );
        } else {
            SetCurrScope( member->scope );
        }
        parm_scope = ScopeBegin( ScopeId( class_parm_scope ) );
        copyWithNewNames( class_parm_scope, member_arg_names );
        if( ScopeType( parm_scope, SCOPE_TEMPLATE_PARM ) ) {
            ScopeSetParmClass( parm_scope, tinfo );
        }
        ScopeSetEnclosing( instance->scope, parm_scope );
    } else {
        parm_scope = class_parm_scope;
        SetCurrScope( parm_scope );
    }

    inst_scope = ScopeBegin( SCOPE_TEMPLATE_INST );
    inst_scope->owner.inst = instance;
    locn = NULL;
    if( instance->locn_set ) {
        locn = &(instance->locn);
    }

    pushInstContext( &context, TCTX_MEMBER_DEFN, locn, NULL );
    ScopeAdjustUsing( NULL, inst_scope );

    ParseClassMemberInstantiation( member->defn );

    ScopeAdjustUsing( inst_scope, NULL );
    popInstContext();

    ScopeSetEnclosing( instance->scope, class_parm_scope );
    if( save_parm_enclosing != NULL ) {
        ScopeSetEnclosing( class_parm_scope->enclosing, save_parm_enclosing );
    }
    SetCurrScope( save_scope );
    ScopeAdjustUsing( NULL, save_scope );
}

static TYPE classTemplateType( CLASS_INST *instance )
{
    SCOPE inst_scope;
    SYMBOL class_sym;

    inst_scope = instance->scope;
    class_sym = firstSymbol( inst_scope );
    return( class_sym->sym_type );
}

static boolean classTemplateWasDefined( CLASS_INST *instance )
{
    return( TypeDefined( classTemplateType( instance ) ) );
}

static boolean makeSureSymIsAMember( SCOPE scope, SYMBOL sym )
{
    if( templateData.extra_members ) {
        if( ScopeClass( scope ) == NULL ) {
            SetErrLoc( &sym->locn->tl );
            CErr2p( ERR_INVALID_TEMPLATE_MEMBER, templateData.extra_member_class );
            return( TRUE );
        }
    }
    return( FALSE );
}

SYMBOL TemplateFunctionTranslate( SYMBOL sym, boolean friend_fn,
                                  SCOPE *parse_scope )
/**************************************************************/
{
    SCOPE sym_scope;
    SYMBOL replace_sym;

    sym_scope = SymScope( sym );
    replace_sym = templateData.translate_fn;
    if( replace_sym != NULL ) {
        /* so any inline functions that are parsed during this function are OK */
        templateData.translate_fn = NULL;
        sym = replace_sym;
        *parse_scope = sym_scope->enclosing;
    } else {
        if( !friend_fn ) {      /* friends don't need to be members */
            makeSureSymIsAMember( sym_scope, sym );
        }
        *parse_scope = sym_scope;
    }
    return( sym );
}

tc_fn_control TemplateFunctionControl( void )
/*******************************************/
{
    tc_fn_control ret;

    ret = templateData.fn_control;
    templateData.fn_control = TCF_NULL;
    return( ret );
}


boolean TemplateVerifyDecl( SYMBOL sym )
/**************************************/
{
    SCOPE sym_scope;

    sym_scope = SymScope( sym );
    return( makeSureSymIsAMember( sym_scope, sym ) );
}

static void templateFunctionInstantiate( FN_TEMPLATE *fn_templ,
                                         FN_TEMPLATE_INST *fn_inst )
{
    SYMBOL save_fn;
    SYMBOL fn_sym;
    SYMBOL bound_sym;
    SCOPE save_scope;
    SCOPE parm_scope;
    auto TEMPLATE_CONTEXT context;

    fn_sym = fn_templ->sym;
    bound_sym = SymDefaultBase( fn_inst->bound_sym );

    save_scope = GetCurrScope();
    ScopeAdjustUsing( save_scope, NULL );
    parm_scope = fn_inst->parm_scope;
    SetCurrScope( fn_inst->inst_scope );
    DbgAssert( parm_scope->enclosing == SymScope( fn_sym ) );
    ScopeSetParmFn( parm_scope, fn_sym->u.defn );

#ifndef NDEBUG
    if( PragDbgToggle.templ_function ) {
        VBUF vbuf1, vbuf2, vbuf3;
        FormatType( bound_sym->sym_type, &vbuf1, &vbuf2 );
        FormatTemplateParmScope( &vbuf3, parm_scope );
        printf( "templateFunctionInstantiate: %s%s%s%s\n",
                vbuf1.buf, fn_sym->name->name, vbuf3.buf, vbuf2.buf );
        VbufFree( &vbuf1 );
        VbufFree( &vbuf2 );
        VbufFree( &vbuf3 );

        FormatSym( fn_sym, &vbuf1 );
        printf( "  symbol: %s ", vbuf1.buf );
        DbgDumpTokenLocn( fn_sym->locn );
        printf( "\n" );
        VbufFree( &vbuf1 );
    }
#endif

    bound_sym->flag |= SF_TEMPLATE_FN;
    bound_sym->u.alias = fn_sym;
    save_fn = templateData.translate_fn;
    templateData.translate_fn = bound_sym;

    pushInstContext( &context, TCTX_FN_DEFN, &fn_inst->locn, bound_sym );

    ScopeAdjustUsing( NULL, fn_inst->inst_scope );
    ParseFunctionInstantiation( fn_templ->defn );
    ScopeAdjustUsing( fn_inst->inst_scope, NULL );

    popInstContext();
    templateData.translate_fn = save_fn;

    ScopeSetParmFn( parm_scope, NULL );
    SetCurrScope( save_scope );
    ScopeAdjustUsing( NULL, save_scope );
}

static void processFunctionTemplateInstantiations( void )
{
    FN_TEMPLATE *curr_defn;
    FN_TEMPLATE_INST *curr_inst;
    SYMBOL sym;

    RingIterBeg( allFunctionTemplates, curr_defn ) {

        if( !curr_defn->has_defn ) {
            continue;
        }

        RingIterBeg( curr_defn->instantiations, curr_inst ) {
            sym = SymDefArgBase( curr_inst->bound_sym );

            if( ! curr_inst->processed && ( sym->flag & SF_REFERENCED ) ) {
                templateData.keep_going = TRUE;
                curr_inst->processed = TRUE;
                templateFunctionInstantiate( curr_defn, curr_inst );
            }

        } RingIterEnd( curr_inst )
    } RingIterEnd( curr_defn )
}

static void freeDefns( void )
{
    unsigned i;
    REWRITE *r;
    TEMPLATE_INFO *tinfo;
    TEMPLATE_SPECIALIZATION *tprimary;
    TEMPLATE_SPECIALIZATION *tspec;
    TEMPLATE_MEMBER *member;
    CLASS_INST *curr_instance;
    MEMBER_INST *curr_member;
    DECL_INFO *curr_inline;
    FN_TEMPLATE *curr_fn;

    RingIterBeg( allClassTemplates, tinfo ) {
        tprimary = RingFirst( tinfo->specializations );
        for( i = 0; i < tprimary->num_args; ++i ) {
            RewriteFree( tinfo->defarg_list[i] );
            tinfo->defarg_list[i] = NULL;
        }
        RingIterBeg( tinfo->specializations, tspec ) {
            RewriteFree( tspec->defn );
            tspec->defn = NULL;
            PTreeFreeSubtrees( tspec->spec_args );
            RingIterBeg( tspec->member_defns, member ) {
                RewriteFree( member->defn );
                member->defn = NULL;
            } RingIterEnd( member )

            RingIterBeg( tspec->instantiations, curr_instance ) {
                for(;;) {
                    curr_inline = RingPop( &(curr_instance->inlines) );
                    if( curr_inline == NULL ) break;
                    FreeDeclInfo( curr_inline );
                }

                for(;;) {
                    curr_member = RingPop( &(curr_instance->members) );
                    if( curr_member == NULL ) break;
                    FreeDeclInfo( curr_member->dinfo );
                }
            } RingIterEnd( curr_instance)
        } RingIterEnd( tspec )
    } RingIterEnd( tinfo )
    RingIterBeg( allFunctionTemplates, curr_fn ) {
        r = curr_fn->defn;
        curr_fn->defn = NULL;
        RewriteFree( r );
    } RingIterEnd( curr_fn )
}

static void processInstantiationInlines( CLASS_INST *instance )
{
    DECL_INFO *curr_inline;
    DECL_INFO *prev_inline;
    SCOPE save_scope;
    SCOPE save_enclosing;
    SYMBOL sym;

    save_scope = GetCurrScope();
    save_enclosing = NULL;
    if( instance->inlines_scope != NULL ) {
        // set up the scopes for instantiating inline member function
        save_enclosing = instance->inlines_scope->enclosing;
        ScopeAdjustUsing( save_scope, NULL );
        instance->inlines_scope->enclosing = instance->inlines_enclosing;
        SetCurrScope( instance->inlines_scope );
        ScopeAdjustUsing( NULL, instance->inlines_scope );
    }
    prev_inline = NULL;

    RingIterBegSafe( instance->inlines, curr_inline ) {

        sym = SymDefArgBase( curr_inline->sym );

        if( instance->must_process
         || ( sym->flag & SF_REFERENCED )
         || ( sym->sym_type->flag & TF1_VIRTUAL ) ) {

#ifndef NDEBUG
            if( PragDbgToggle.member_inst ) {
                printf( "instantiating inline template member: %s\n",
                        DbgSymNameFull( sym ) );
            }
#endif

            templateData.fn_control = TCF_NULL;
            if( instance->must_process ) {
                templateData.fn_control |= TCF_GEN_FUNCTION;
            }

            ClassProcessFunction( curr_inline, TRUE );
            RingPruneWithPrev( &instance->inlines,
                               curr_inline,
                               prev_inline );
            FreeDeclInfo( curr_inline );
            templateData.keep_going = TRUE;
        } else {
            prev_inline = curr_inline;
        }
    } RingIterEndSafe( curr_inline )

    if( instance->inlines_scope != NULL ) {
        ScopeAdjustUsing( instance->inlines_scope, NULL );
        instance->inlines_scope->enclosing = save_enclosing;
        ScopeAdjustUsing( NULL, save_scope );
    }
    SetCurrScope( save_scope );
}

static void processInstantiationMembers( CLASS_INST *instance )
{
    MEMBER_INST *curr_member;
    MEMBER_INST *prev_member;
    SCOPE sym_scope;
    SCOPE save_scope;
    SCOPE save_class_parm_scope;
    SCOPE save_class_parm_enclosing;
    DECL_INFO *dinfo;
    SYMBOL sym;

    ScopeAdjustUsing( GetCurrScope(), NULL );

    prev_member = NULL;
    RingIterBegSafe( instance->members, curr_member ) {

        dinfo = curr_member->dinfo;
        sym = SymDefArgBase( dinfo->sym );

        if( instance->must_process
         || ( sym->flag & SF_REFERENCED )
         || ( sym->sym_type->flag & TF1_VIRTUAL ) ) {

#ifndef NDEBUG
            if( PragDbgToggle.member_inst ) {
                printf( "instantiating template member: %s\n",
                        DbgSymNameFull( sym ) );
            }
#endif

            sym_scope = SymScope( sym );
            save_scope = sym_scope->enclosing;

            save_class_parm_scope = instance->scope->enclosing;
            save_class_parm_enclosing = save_class_parm_scope->enclosing;
            sym_scope->enclosing = curr_member->scope;

            templateData.fn_control = TCF_NULL;
            if( instance->must_process ) {
                templateData.fn_control |= TCF_GEN_FUNCTION;
            }

            ScopeAdjustUsing( NULL, GetCurrScope() );
            ClassProcessFunction( dinfo, FALSE );
            ScopeAdjustUsing( GetCurrScope(), NULL );

            RingPruneWithPrev( &instance->members,
                               curr_member,
                               prev_member );
            FreeDeclInfo( dinfo );
            templateData.keep_going = TRUE;

            save_class_parm_scope->enclosing = save_class_parm_enclosing;
            instance->scope->enclosing = save_class_parm_scope;
            sym_scope->enclosing = save_scope;
        } else {
            prev_member = curr_member;
        }
    } RingIterEndSafe( curr_member )

    ScopeAdjustUsing( NULL, GetCurrScope() );
}

void TemplateProcessInstantiations( void )
/****************************************/
{
    TEMPLATE_INFO *curr_tinfo;
    CLASS_INST *curr_instance;
    TEMPLATE_MEMBER *curr_member;
    TEMPLATE_SPECIALIZATION *tspec;
    TOKEN_LOCN *locn;
    auto TEMPLATE_CONTEXT context;

    for(;;) {
        verifyOKToProceed( NULL );

        CtxSetContext( CTX_FUNC_GEN );
        templateData.keep_going = ClassDefineRefdDefaults();
        CtxSetContext( CTX_SOURCE );

        // instantiate any template functions
        processFunctionTemplateInstantiations();

        // instantiate extra class members
        templateData.extra_members = TRUE;
        RingIterBeg( allClassTemplates, curr_tinfo ) {
            RingIterBeg( curr_tinfo->specializations, tspec ) {
                RingIterBeg( tspec->instantiations, curr_instance ) {

                    if( curr_instance->specific
                     || curr_instance->dont_process ) {
                        continue;
                    }
                    if( ! classTemplateWasDefined( curr_instance ) ) {
                        continue;
                    }
                    templateData.extra_member_class =
                        classTemplateType( curr_instance );

                    if( ! curr_instance->processed ) {
                        curr_instance->processed = TRUE;
                        RingIterBeg( tspec->member_defns, curr_member ) {
                            // loop nesting is critical because extra members cannot be
                            // generated if a class has not been instantiated
                            instantiateMember( curr_tinfo, tspec,
                                               curr_instance, curr_member );
                        } RingIterEnd( curr_member )
                    }

                    locn = NULL;
                    if( curr_instance->locn_set ) {
                        locn = &(curr_instance->locn);
                    }
                    pushInstContext( &context, TCTX_MEMBER_DEFN, locn, NULL );

                    processInstantiationInlines( curr_instance );
                    processInstantiationMembers( curr_instance );

                    popInstContext();

                } RingIterEnd( curr_instance )
            } RingIterEnd( tspec )
        } RingIterEnd( curr_tinfo )
        templateData.extra_members = FALSE;
        if( ! templateData.keep_going ) break;
    }
    templateData.extra_members = FALSE;
    freeDefns();
}

boolean TemplateMemberCanBeIgnored( void )
/****************************************/
{
    return( templateData.extra_members );
}

void TemplateSpecificDefnStart( PTREE tid, TYPE type )
/****************************************************/
{
    CLASS_INST *instance;
    TEMPLATE_INFO *tinfo;
    TEMPLATE_SPECIALIZATION *tprimary;
    SCOPE inst_scope;
    SCOPE parm_scope;
    PTREE parms;

    tinfo = classUnboundTemplateInfo( type );
    tprimary = RingFirst( tinfo->specializations );
    if( tprimary->corrupted ) {
        return;
    }

    parms = fakeUpTemplateParms( type->u.c.scope->enclosing, NULL );

    instance = NULL;
    inst_scope = findInstScope( tprimary, parms, &instance );
    if( inst_scope != NULL ) {
        instance->specific = TRUE;
        SetCurrScope( inst_scope );
    } else {
        parm_scope = ScopeBegin( SCOPE_TEMPLATE_PARM );
        ScopeSetParmClass( parm_scope, tinfo );

        inst_scope = ScopeBegin( SCOPE_TEMPLATE_INST );
        instance = newClassInstantiation( tprimary, type,
                                          inst_scope, TRUE );
        injectTemplateParms( NULL, parm_scope, parms, FALSE );
    }
    DbgAssert( instance->specific );
    NodeFreeDupedExpr( parms );
}

void TemplateSpecificDefnEnd( void )
/**********************************/
{
    if( ScopeType( GetCurrScope(), SCOPE_TEMPLATE_INST ) ) {
        ScopeEnd( SCOPE_TEMPLATE_INST );
        ScopeEnd( SCOPE_TEMPLATE_PARM );
    }
}

void TemplateSpecializationDefn( TYPE type )
/******************************************/
{
    PTREE parms;

    DbgAssert( currentTemplate != NULL );

    parms = fakeUpTemplateParms( type->u.c.scope->enclosing, NULL );
    currentTemplate->spec_args = parms;
}

SCOPE TemplateClassInstScope( TYPE class_type )
/*********************************************/
{
    SCOPE inst_scope;

    inst_scope = NULL;
    if( class_type->flag & TF1_INSTANTIATION ) {
        inst_scope = class_type->u.c.scope->enclosing;
    }
    return( inst_scope );
}

SCOPE TemplateClassParmScope( TYPE class_type )
/*********************************************/
{
    SCOPE inst_scope;
    SCOPE parm_scope;

    parm_scope = NULL;
    if( class_type->flag & TF1_INSTANTIATION ) {
        inst_scope = TemplateClassInstScope( class_type );
        if( inst_scope != NULL ) {
            parm_scope = inst_scope->enclosing;
            if( ScopeType( parm_scope, SCOPE_TEMPLATE_SPEC_PARM ) ) {
                parm_scope = parm_scope->enclosing;
            }
        }
    } else if( class_type->flag & TF1_UNBOUND ) {
        parm_scope = class_type->u.c.scope->enclosing;
    }
    return( parm_scope );
}

SYMBOL TemplateSymFromClass( TYPE class_type )
/********************************************/
{
    SYMBOL sym;
    SCOPE inst_scope;

    sym = NULL;
    inst_scope = TemplateClassInstScope( class_type );
    if( inst_scope != NULL ) {
        sym = firstSymbol( inst_scope );
    }
    return( sym );
}

boolean TemplateUnboundSame( TYPE ub1, TYPE ub2 )
/***********************************************/
{
    SYMBOL ub1_curr;
    SYMBOL ub1_stop;
    SYMBOL ub2_curr;
    SYMBOL ub2_stop;
    CLASSINFO *ub1_info;
    CLASSINFO *ub2_info;
    type_flag uf1;
    type_flag uf2;
    SCOPE ub1_parm_scope;
    SCOPE ub2_parm_scope;

    uf1 = ub1->flag;
    uf2 = ub2->flag;
    if( uf1 != uf2 || ( uf1 & TF1_UNBOUND ) == 0 ) {
        return( FALSE );
    }
    DbgAssert( ub1->of == NULL && ub2->of == NULL );
    ub1_info = ub1->u.c.info;
    ub2_info = ub2->u.c.info;
    if( ub1_info->name != ub2_info->name ) {
        return( FALSE );
    }
    /* both are instantiations of the same class */
    ub1_parm_scope = TemplateClassParmScope( ub1 );
    ub2_parm_scope = TemplateClassParmScope( ub2 );
    if( ub1_parm_scope == NULL || ub2_parm_scope == NULL ) {
        return( FALSE );
    }
    ub1_curr = NULL;
    ub2_curr = NULL;
    ub1_stop = ScopeOrderedStart( ub1_parm_scope );
    ub2_stop = ScopeOrderedStart( ub2_parm_scope );
    for(;;) {
        ub1_curr = ScopeOrderedNext( ub1_stop, ub1_curr );
        ub2_curr = ScopeOrderedNext( ub2_stop, ub2_curr );
        if( ub1_curr == NULL ) break;
        if( ub2_curr == NULL ) break;
        DbgAssert( ub1_curr->id == ub2_curr->id );
        if( ub1_curr->id != SC_TYPEDEF ) {
            if( ! TemplateParmEqual( ub1_curr, ub2_curr ) ) {
                return( FALSE );
            }
        } else {
            if( ! TypeCompareExclude( ub1_curr->sym_type, ub2_curr->sym_type,
                                      TC1_NOT_ENUM_CHAR ) ) {
                return( FALSE );
            }
        }
    }
    DbgAssert( ub1_curr == NULL && ub2_curr == NULL );
    return( TRUE );
}

TEMPLATE_INFO *TemplateClassInfoGetIndex( TEMPLATE_INFO *e )
{
    return( CarveGetIndex( carveTEMPLATE_INFO, e ) );
}

TEMPLATE_INFO *TemplateClassInfoMapIndex( TEMPLATE_INFO *e )
{
    return( CarveMapIndex( carveTEMPLATE_INFO, e ) );
}

FN_TEMPLATE *TemplateFunctionInfoGetIndex( FN_TEMPLATE *e )
{
    return( CarveGetIndex( carveFN_TEMPLATE, e ) );
}

FN_TEMPLATE *TemplateFunctionInfoMapIndex( FN_TEMPLATE *e )
{
    return( CarveMapIndex( carveFN_TEMPLATE, e ) );
}

static void markFreeTemplateInfo( void *p )
{
    TEMPLATE_INFO *s = p;

    s->free = TRUE;
}

static void markFreeClassInst( void *p )
{
    CLASS_INST *s = p;

    s->free = TRUE;
}

static void markFreeFnTemplateDefn( void *p )
{
    FN_TEMPLATE *s = p;

    s->free = TRUE;
}

static void saveUnboundTemplate( UNBOUND_TEMPLATE *s,
                                 UNBOUND_TEMPLATE *stop )
{
    UNBOUND_TEMPLATE *save_next;
    TYPE save_type;

    save_next = s->next;
    s->next = (UNBOUND_TEMPLATE *) ( s != stop );
    save_type = s->unbound_type;
    s->unbound_type = TypeGetIndex( save_type );

    PCHWrite( s, sizeof( *s ) );

    s->next = save_next;
    s->unbound_type = save_type;
}

static void saveTemplateSpecialization( TEMPLATE_SPECIALIZATION *s,
                                        TEMPLATE_SPECIALIZATION *stop )
{
    TEMPLATE_SPECIALIZATION *save_next;
    TEMPLATE_INFO *save_tinfo;
    SCOPE save_decl_scope;
    SRCFILE save_locn_src_file;
    REWRITE *save_defn;
    CLASS_INST *save_instantiations;
    PTREE save_spec_args;
    unsigned char *save_ordering;
    TEMPLATE_MEMBER *member;
    REWRITE *member_defn;
    SCOPE scope;
    void *nti;
    unsigned i;

    save_next = s->next;
    s->next = (TEMPLATE_SPECIALIZATION *) ( s != stop );
    save_tinfo = s->tinfo;
    s->tinfo = TemplateClassInfoGetIndex( save_tinfo );
    save_decl_scope = s->decl_scope;
    s->decl_scope = ScopeGetIndex( save_decl_scope );
    save_locn_src_file = s->locn.src_file;
    s->locn.src_file = SrcFileGetIndex( save_locn_src_file );
    save_defn = s->defn;
    s->defn = RewriteGetIndex( save_defn );
    save_instantiations = s->instantiations;
    s->instantiations = CarveGetIndex( carveCLASS_INST, save_instantiations );
    save_spec_args = s->spec_args;
    s->spec_args = PTreeGetIndex( save_spec_args );
    save_ordering = s->ordering;
    s->ordering = ( save_ordering != NULL ) ? (void *) save_tinfo->nr_specs : NULL;

    PCHWrite( s, sizeof( *s ) );
    for( i = 0; i < s->num_args; ++i ) {
        nti = NameGetIndex( s->arg_names[i] );
        PCHWrite( &nti, sizeof( nti ) );
    }
    for( i = 0; i < s->num_args; ++i ) {
        nti = TypeGetIndex( s->type_list[i] );
        PCHWrite( &nti, sizeof( nti ) );
    }
    RingIterBeg( s->member_defns, member ){
        scope = ScopeGetIndex( member->scope );
        PCHWrite( &scope, sizeof( SCOPE ) );
        member_defn = RewriteGetIndex( member->defn );
        PCHWrite( &member_defn, sizeof( REWRITE * ) );
        if( member->arg_names != s->arg_names ) {
            PCHWrite( &s->num_args, sizeof( int ) );
            for( i = 0; i < s->num_args; ++i ) {
                nti = NameGetIndex( member->arg_names[i] );
                PCHWrite( &nti, sizeof( nti ) );
            }
        } else {
            i = 0;
            PCHWrite( &i, sizeof( int ) );
        }
    } RingIterEnd( member )
    scope = NULL;
    PCHWrite( &scope, sizeof( SCOPE ) );
    if( save_ordering != NULL ) {
        PCHWrite( save_ordering,
                  16 * ( ( save_tinfo->nr_specs - 2 ) / 128 + 1 ) );
    }

    s->next = save_next;
    s->tinfo = save_tinfo;
    s->locn.src_file = save_locn_src_file;
    s->decl_scope = save_decl_scope;
    s->defn = save_defn;
    s->instantiations = save_instantiations;
    s->spec_args = save_spec_args;
    s->ordering = save_ordering;
}

static void saveTemplateInfo( void *p, carve_walk_base *d )
{
    TEMPLATE_INFO *s = p;
    TEMPLATE_INFO *save_next;
    UNBOUND_TEMPLATE *save_unbound_templates;
    UNBOUND_TEMPLATE *unbound;
    TEMPLATE_SPECIALIZATION *save_specializations;
    TEMPLATE_SPECIALIZATION *tprimary;
    TEMPLATE_SPECIALIZATION *tspec;
    SYMBOL save_sym;
    REWRITE **save_defarg_list;
    void *defarg_index;
    unsigned i;

    if( s->free ) {
        return;
    }

    tprimary = RingFirst( s->specializations );

    save_next = s->next;
    s->next = TemplateClassInfoGetIndex( save_next );
    save_unbound_templates = s->unbound_templates;
    s->unbound_templates = (UNBOUND_TEMPLATE *) ( s->unbound_templates != NULL );
    save_specializations = s->specializations;
    s->specializations = (TEMPLATE_SPECIALIZATION *) ( s->specializations != NULL );
    save_sym = s->sym;
    s->sym = SymbolGetIndex( save_sym );
    save_defarg_list = s->defarg_list;
    s->defarg_list = (REWRITE **) tprimary->num_args;

    PCHWriteCVIndex( d->index );
    PCHWrite( s, sizeof( *s ) );

    s->next = save_next;
    s->unbound_templates = save_unbound_templates;
    s->specializations = save_specializations;
    s->sym = save_sym;
    s->defarg_list = save_defarg_list;

    for( i = 0; i < tprimary->num_args; ++i ) {
        defarg_index = RewriteGetIndex( s->defarg_list[i] );
        PCHWrite( &defarg_index, sizeof( defarg_index ) );
    }

    RingIterBeg( s->unbound_templates, unbound ) {
        saveUnboundTemplate( unbound, s->unbound_templates );
    } RingIterEnd( unbound )

    RingIterBeg( s->specializations, tspec ) {
        saveTemplateSpecialization( tspec, s->specializations );
    } RingIterEnd( tspec )
}

static void saveMemberInst( MEMBER_INST *s, MEMBER_INST *stop )
{
    MEMBER_INST *save_next;
    DECL_INFO *save_dinfo;
    SCOPE save_scope;
    SCOPE save_class_parm_scope;
    SCOPE save_class_parm_enclosing;

    save_next = s->next;
    s->next = (MEMBER_INST *) ( s != stop );
    save_dinfo = s->dinfo;
    s->dinfo = (void *) ( s->dinfo != NULL );
    save_scope = s->scope;
    s->scope = ScopeGetIndex( save_scope );
    save_class_parm_scope = s->class_parm_scope;
    s->class_parm_scope = ScopeGetIndex( save_class_parm_scope );
    save_class_parm_enclosing = s->class_parm_enclosing;
    s->class_parm_enclosing = ScopeGetIndex( save_class_parm_enclosing );

    PCHWrite( s, sizeof( *s ) );

    s->next = save_next;
    s->dinfo = save_dinfo;
    s->scope = save_scope;
    s->class_parm_scope = save_class_parm_scope;
    s->class_parm_enclosing = save_class_parm_enclosing;

    if( s->dinfo != NULL ) {
        PCHWriteDeclInfo( s->dinfo );
    }
}

static void saveClassInst( void *p, carve_walk_base *d )
{
    CLASS_INST *s = p;
    CLASS_INST *save_next;
    SCOPE save_scope;
    SCOPE save_inlines_scope;
    SCOPE save_inlines_enclosing;
    DECL_INFO *save_inlines;
    MEMBER_INST *save_members;
    MEMBER_INST *member;
    SRCFILE save_locn_src_file;

    if( s->free ) {
        return;
    }
    save_next = s->next;
    s->next = CarveGetIndex( carveCLASS_INST, save_next );
    save_scope = s->scope;
    s->scope = ScopeGetIndex( save_scope );
    save_inlines_scope = s->inlines_scope;
    s->inlines_scope = ScopeGetIndex( save_inlines_scope );
    save_inlines_enclosing = s->inlines_enclosing;
    s->inlines_enclosing = ScopeGetIndex( save_inlines_enclosing );
    save_inlines = s->inlines;
    s->inlines = (void *) ( s->inlines != NULL );
    save_members = s->members;
    s->members = (MEMBER_INST *) ( s->members != NULL );
    save_locn_src_file = s->locn.src_file;
    s->locn.src_file = SrcFileGetIndex( save_locn_src_file );

    PCHWriteCVIndex( d->index );
    PCHWrite( s, sizeof( *s ) );

    s->next = save_next;
    s->scope = save_scope;
    s->inlines_scope = save_inlines_scope;
    s->inlines_enclosing = save_inlines_enclosing;
    s->inlines = save_inlines;
    s->members = save_members;
    s->locn.src_file = save_locn_src_file;

    if( s->inlines != NULL ) {
        PCHWriteDeclInfo( s->inlines );
    }

    RingIterBeg( s->members, member ) {
        saveMemberInst( member, s->members );
    } RingIterEnd( member )
}

static void saveFnTemplateInst( FN_TEMPLATE_INST *s, FN_TEMPLATE_INST *stop )
{
    FN_TEMPLATE_INST *save_next;
    SYMBOL save_bound_sym;
    SCOPE save_parm_scope;
    SCOPE save_inst_scope;

    save_next = s->next;
    s->next = (FN_TEMPLATE_INST *) ( s != stop );
    save_bound_sym = s->bound_sym;
    s->bound_sym = SymbolGetIndex( save_bound_sym );
    save_parm_scope = s->parm_scope;
    s->parm_scope = ScopeGetIndex( save_parm_scope );
    save_inst_scope = s->inst_scope;
    s->inst_scope = ScopeGetIndex( save_inst_scope );

    PCHWrite( s, sizeof( *s ) );

    s->next = save_next;
    s->bound_sym = save_bound_sym;
    s->parm_scope = save_parm_scope;
    s->inst_scope = save_inst_scope;
}

static void saveFnTemplateDefn( void *p, carve_walk_base *d )
{
    FN_TEMPLATE *s = p;
    FN_TEMPLATE *save_next;
    FN_TEMPLATE_INST *save_instantiations;
    FN_TEMPLATE_INST *inst;
    SYMBOL save_sym;
    REWRITE *save_defn;
    SCOPE save_decl_scope;

    if( s->free ) {
        return;
    }
    save_next = s->next;
    s->next = TemplateFunctionInfoGetIndex( save_next );
    save_instantiations = s->instantiations;
    s->instantiations = (FN_TEMPLATE_INST *) ( s->instantiations != NULL );
    save_sym = s->sym;
    s->sym = SymbolGetIndex( save_sym );
    save_defn = s->defn;
    s->defn = RewriteGetIndex( save_defn );
    save_decl_scope = s->decl_scope;
    s->decl_scope = ScopeGetIndex( save_decl_scope );
    PCHWriteCVIndex( d->index );
    PCHWrite( s, sizeof( *s ) );
    s->next = save_next;
    s->instantiations = save_instantiations;
    s->sym = save_sym;
    s->defn = save_defn;
    s->decl_scope = save_decl_scope;

    RingIterBeg( s->instantiations, inst ) {
        saveFnTemplateInst( inst, s->instantiations );
    } RingIterEnd( inst )
}

pch_status PCHWriteTemplates( void )
{
    cv_index terminator = CARVE_NULL_INDEX;
    TEMPLATE_INFO *all_class_templates;
    FN_TEMPLATE *all_function_templates;
    auto carve_walk_base data;

    PCHWrite( &templateData.max_depth, sizeof( templateData.max_depth ) );
    all_class_templates = TemplateClassInfoGetIndex( allClassTemplates );
    PCHWrite( &all_class_templates, sizeof( all_class_templates ) );
    all_function_templates = TemplateFunctionInfoGetIndex( allFunctionTemplates );
    PCHWrite( &all_function_templates, sizeof( all_function_templates ) );
    CarveWalkAllFree( carveCLASS_INST, markFreeClassInst );
    CarveWalkAll( carveCLASS_INST, saveClassInst, &data );
    PCHWriteCVIndex( terminator );
    CarveWalkAllFree( carveFN_TEMPLATE, markFreeFnTemplateDefn );
    CarveWalkAll( carveFN_TEMPLATE, saveFnTemplateDefn, &data );
    PCHWriteCVIndex( terminator );
    CarveWalkAllFree( carveTEMPLATE_INFO, markFreeTemplateInfo );
    CarveWalkAll( carveTEMPLATE_INFO, saveTemplateInfo, &data );
    PCHWriteCVIndex( terminator );
    return( PCHCB_OK );
}

pch_status PCHReadTemplates( void )
{
    cv_index i;
    unsigned j;
    size_t arg_names_size;
    size_t type_list_size;
    size_t defarg_list_size;
    char **arg_names;
    TYPE *type_list;
    REWRITE **defarg_list;
    MEMBER_INST *mi;
    CLASS_INST *ci;
    FN_TEMPLATE_INST *fti;
    FN_TEMPLATE *ftd;
    TEMPLATE_SPECIALIZATION *ts;
    TEMPLATE_INFO *ti;
    UNBOUND_TEMPLATE *ut;
    SCOPE scope;
    REWRITE *memb_defn;
    char **memb_arg_names;
    boolean cont;
    auto cvinit_t data;

    PCHRead( &templateData.max_depth, sizeof( templateData.max_depth ) );
    PCHRead( &allClassTemplates, sizeof( allClassTemplates ) );
    allClassTemplates = TemplateClassInfoMapIndex( allClassTemplates );
    PCHRead( &allFunctionTemplates, sizeof( allFunctionTemplates ) );
    allFunctionTemplates = TemplateFunctionInfoMapIndex( allFunctionTemplates );

    CarveInitStart( carveCLASS_INST, &data );
    for(;;) {
        i = PCHReadCVIndex();
        if( i == CARVE_NULL_INDEX ) break;
        ci = CarveInitElement( &data, i );
        PCHRead( ci, sizeof( *ci ) );
        ci->next = CarveMapIndex( carveCLASS_INST, ci->next );
        ci->scope = ScopeMapIndex( ci->scope );
        ci->inlines_scope = ScopeMapIndex( ci->inlines_scope );
        ci->inlines_enclosing = ScopeMapIndex( ci->inlines_enclosing );
        ci->locn.src_file = SrcFileMapIndex( ci->locn.src_file );
        if( ci->inlines != NULL ) {
            ci->inlines = PCHReadDeclInfo();
        }

        cont = ci->members != NULL;
        ci->members = NULL;
        while( cont ) {
            mi = CPermAlloc( sizeof( MEMBER_INST ) );
            PCHRead( mi, sizeof( *mi ) );
            cont = mi->next != NULL;

            mi->next = NULL;
            mi->scope = ScopeMapIndex( mi->scope );
            mi->class_parm_scope = ScopeMapIndex( mi->class_parm_scope );
            mi->class_parm_enclosing = ScopeMapIndex( mi->class_parm_enclosing );

            if( mi->dinfo != NULL ) {
                mi->dinfo = PCHReadDeclInfo();
            }
            RingAppend( &ci->members, mi );
        }
    }

    CarveInitStart( carveFN_TEMPLATE, &data );
    for(;;) {
        i = PCHReadCVIndex();
        if( i == CARVE_NULL_INDEX ) break;
        ftd = CarveInitElement( &data, i );
        PCHRead( ftd, sizeof( *ftd ) );
        ftd->next = TemplateFunctionInfoMapIndex( ftd->next );
        ftd->sym = SymbolMapIndex( ftd->sym );
        ftd->decl_scope = ScopeMapIndex( ftd->decl_scope );
        ftd->defn = RewriteMapIndex( ftd->defn );

        cont = ftd->instantiations != NULL;
        ftd->instantiations = NULL;
        while( cont ) {
            fti = CPermAlloc( sizeof( FN_TEMPLATE_INST ) );
            PCHRead( fti, sizeof( *fti ) );
            cont = fti->next != NULL;

            fti->next = NULL;
            fti->bound_sym = SymbolMapIndex( fti->bound_sym );
            fti->parm_scope = ScopeMapIndex( fti->parm_scope );
            fti->inst_scope = ScopeMapIndex( fti->inst_scope );
            RingAppend( &ftd->instantiations, fti );
        }
    }

    CarveInitStart( carveTEMPLATE_INFO, &data );
    for(;;) {
        i = PCHReadCVIndex();
        if( i == CARVE_NULL_INDEX ) break;
        ti = CarveInitElement( &data, i );
        PCHRead( ti, sizeof( *ti ) );
        ti->next = TemplateClassInfoMapIndex( ti->next );
        ti->sym = SymbolMapIndex( ti->sym );

        defarg_list_size = (unsigned int) ti->defarg_list;
        defarg_list = CPermAlloc( defarg_list_size * sizeof( REWRITE * ) );
        ti->defarg_list = defarg_list;
        PCHRead( defarg_list, defarg_list_size * sizeof( REWRITE * ) );
        for( j = 0; j < defarg_list_size; ++j ) {
            defarg_list[j] = RewriteMapIndex( defarg_list[j] );
        }

        cont = ti->unbound_templates != NULL;
        ti->unbound_templates = NULL;
        while( cont ) {
            ut = CPermAlloc( sizeof( UNBOUND_TEMPLATE ) );
            PCHRead( ut, sizeof( *ut ) );
            cont = ut->next != NULL;

            ut->next = NULL;
            ut->unbound_type = TypeMapIndex( ut->unbound_type );

            RingAppend( &ti->unbound_templates, ut );
        }

        cont = ti->specializations != NULL;
        ti->specializations = NULL;
        while( cont ) {
            ts = CPermAlloc( sizeof( TEMPLATE_SPECIALIZATION ) );
            PCHRead( ts, sizeof( *ts ) );
            cont = ts->next != NULL;

            ts->next = NULL;
            ts->tinfo = TemplateClassInfoMapIndex( ts->tinfo );
            ts->locn.src_file = SrcFileMapIndex( ts->locn.src_file );
            ts->decl_scope = ScopeMapIndex( ts->decl_scope );
            ts->defn = RewriteMapIndex( ts->defn );
            ts->instantiations = CarveMapIndex( carveCLASS_INST,
                                                ts->instantiations );
            ts->member_defns = NULL;
            ts->spec_args = PTreeMapIndex( ts->spec_args );
            arg_names_size = ts->num_args * sizeof( char * );
            arg_names = CPermAlloc( arg_names_size );
            ts->arg_names = arg_names;
            type_list_size = ts->num_args * sizeof( TYPE );
            type_list = CPermAlloc( type_list_size );
            ts->type_list = type_list;
            PCHRead( arg_names, arg_names_size );
            PCHRead( type_list, type_list_size );
            for( j = 0; j < ts->num_args; ++j ) {
                arg_names[j] = NameMapIndex( arg_names[j] );
                type_list[j] = TypeMapIndex( type_list[j] );
            }
            for(;;) {
                PCHRead( &scope, sizeof( scope ) );
                if( scope == NULL ) break;
                scope = ScopeMapIndex( scope );
                PCHRead( &memb_defn, sizeof( memb_defn ) );
                memb_defn = RewriteMapIndex( memb_defn );
                PCHRead( &j, sizeof( j ) );
                if( j != 0 ) {
                    memb_arg_names = CPermAlloc( arg_names_size );
                    PCHRead( memb_arg_names, arg_names_size );
                    for( j = 0; j < ts->num_args; ++j ) {
                        memb_arg_names[j] = NameMapIndex( memb_arg_names[j] );
                    }
                } else {
                    memb_arg_names = arg_names;
                }
                addMemberEntry( ts, scope, memb_defn, memb_arg_names );
            }
            if( ts->ordering != NULL ) {
                j = 16 * ( ( ( (unsigned) ts->ordering ) - 2 ) / 128 + 1 );
                ts->ordering = CMemAlloc( j );
                PCHRead( ts->ordering, j );
            }

            RingAppend( &ti->specializations, ts );
        }
    }

    return( PCHCB_OK );
}

pch_status PCHInitTemplates( boolean writing )
{
    cv_index n;

    if( writing ) {
        n = CarveLastValidIndex( carveCLASS_INST );
        PCHWriteCVIndex( n );
        n = CarveLastValidIndex( carveFN_TEMPLATE );
        PCHWriteCVIndex( n );
        n = CarveLastValidIndex( carveTEMPLATE_INFO );
        PCHWriteCVIndex( n );
    } else {
        carveCLASS_INST = CarveRestart( carveCLASS_INST );
        n = PCHReadCVIndex();
        CarveMapOptimize( carveCLASS_INST, n );
        carveFN_TEMPLATE = CarveRestart( carveFN_TEMPLATE );
        n = PCHReadCVIndex();
        CarveMapOptimize( carveFN_TEMPLATE, n );
        carveTEMPLATE_INFO = CarveRestart( carveTEMPLATE_INFO );
        n = PCHReadCVIndex();
        CarveMapOptimize( carveTEMPLATE_INFO, n );
    }
    return( PCHCB_OK );
}

pch_status PCHFiniTemplates( boolean writing )
{
    if( ! writing ) {
        CarveMapUnoptimize( carveCLASS_INST );
        CarveMapUnoptimize( carveFN_TEMPLATE );
        CarveMapUnoptimize( carveTEMPLATE_INFO );
    }
    return( PCHCB_OK );
}
