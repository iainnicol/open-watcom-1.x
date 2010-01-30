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
* Description:  Analyze and optimize conditionals.
*
****************************************************************************/


#include "standard.h"
#include "coderep.h"
#include "pattern.h"
#include "opcodes.h"
#include "cgmem.h"
#include "vergen.h"


extern  name            *AllocIntConst( int );
extern  void            DoNothing( instruction * );
extern  bool            VolatileIns( instruction * );
extern  void            ClearBlockBits( block_class );
extern  bool            CondOverlaps( name *result, name *ccop );

extern    block         *HeadBlock;

typedef enum {          /* in order of increasing amount of information */
        UNKNOWN_STATE,
        EQUALITY_CONDITIONS_SET,
        SIGNED_CONDITIONS_SET,
        CONDITIONS_SET
} cc_state;


typedef struct cc_control {
        name            *left_op;
        name            *right_op;
        name            *result_op;
        instruction     *ins;
        type_class_def  op_type;
        cc_state        state;
} cc_control;


static  bool    UselessCompare( instruction *ins, cc_control *cc, name *zero )
/*****************************************************************************
    Return TRUE if the comparison which would be generated by
    instruction "ins" is useless given that fact that condition codes
    "cc" have been set by a previous instruction.  A typical example is
    SUB AX,1 => AX followed by IF_CMP_EQUAL AX,0 goto L1: else L2:.
*/
{
    opcode_defs opcode;

    opcode = ins->head.opcode;

    if( cc->state == UNKNOWN_STATE ) return( FALSE );
#if _TARGET & _TARG_370
    if( opcode != OP_CMP_EQUAL && opcode != OP_CMP_NOT_EQUAL ) {
        if( cc->op_type != ins->type_class ) return( FALSE );
    }
#endif
    if( ins->operands[ 0 ] == cc->left_op
     && ins->operands[ 1 ] == cc->right_op ) {
        if( cc->state == CONDITIONS_SET ) return( TRUE );
        if( opcode == OP_CMP_EQUAL ) return( TRUE );
        if( opcode == OP_CMP_NOT_EQUAL ) return( TRUE );
        if( cc->state == EQUALITY_CONDITIONS_SET ) return( FALSE );
        if( ins->type_class == I1 ) return( TRUE );
        if( ins->type_class == I2 ) return( TRUE );
    } else if( ins->operands[ 0 ] == cc->result_op
            && ins->operands[ 1 ] == zero ) {
#if _TARGET & _TARG_370
        if( cc->state == CONDITIONS_SET ) return( TRUE );
#endif
        if( opcode == OP_CMP_EQUAL ) return( TRUE );
        if( opcode == OP_CMP_NOT_EQUAL ) return( TRUE );
    }
    return( FALSE );
}

static void DoMarkUsedCC( block *blk )
/************************************/
{
    instruction *ins;
    block_edge  *edge;

    ins = ((cc_control *)blk->cc)->ins;
    if( ins != NULL ) {
        ins->ins_flags |= INS_CC_USED;
    } else {
        blk->class |= BLOCK_VISITED;
        for( edge = blk->input_edges; edge != NULL; edge = edge->next_source ) {
            if( !(edge->source->class & BLOCK_VISITED) ) {
                DoMarkUsedCC( edge->source );
            }
        }
    }
}

static void MarkUsedCC( block *blk )
/***********************************
    We have to mark the instructions that set the condition codes
    as INS_CC_USED. If the blk->cc->ins field is non-NULL, that means that
    the instruction pointed at is the one that set the flags, otherwise
    the condition codes were flowed in from other blocks, so we have to
    mark the instructions that set the flags in those blocks.
*/
{
    DoMarkUsedCC( blk );
    ClearBlockBits( BLOCK_VISITED );
}

static  bool    Traverse( block *blk, name *zero )
/*************************************************
    Given a starting condition code setting for "blk" (blk->cc),
    traverse the block, modifying the condition codes accordingly, and
    see if the will suffice for a conditional instruction that we
    encounter, thus eliminating the compare.
*/
{
    instruction         *ins;
    cc_control          *cc;
    operand_types       cc_affect;
    bool                change;
    int                 jumps;

    change = FALSE;
    cc = blk->cc;
    cc->ins = NULL;
    ins = blk->ins.hd.next;
    jumps = 0;
    while( ins->head.opcode != OP_BLOCK ) {
        if( _OpIsJump( ins->head.opcode ) ) {
            ++jumps;
        }
        cc_affect = ins->u.gen_table->op_type & MASK_CC;
        // Compares and setcc instructions go through the same
        // tables - compares set condition code, but setcc does not
        // so we kludge it right here. BBB - June 28, 1995
        if( _OpIsCompare( ins->head.opcode ) && ins->result != NULL ) {
            // we still want to kill off compare for this set instruction if
            // possible
            if( UselessCompare( ins, cc, zero ) ) {
                if( ins->u.gen_table->generate != G_NO ) {
                    change = TRUE;
                    DoNothing( ins );
                    MarkUsedCC( blk );
                }
            }
            cc_affect = NO_CC;
        }
        if( VolatileIns( ins ) || cc_affect == NO_CC ) {
            cc->state = UNKNOWN_STATE;
        } else if( cc_affect == SETS_SC ) { /* sets SIGNED conditions */
#if _TARGET & _TARG_370
            /* SETS_SC means ok for ==, != on 370 */
            cc->state = EQUALITY_CONDITIONS_SET;
#else
            if( !_OpIsBit( ins->head.opcode ) &&
                ( ins->ins_flags & INS_DEMOTED ) ) {
                cc->state = EQUALITY_CONDITIONS_SET;
            } else {
                cc->state = SIGNED_CONDITIONS_SET;
            }
#endif
            cc->result_op = ins->result;
            cc->op_type = ins->type_class;
            if( ins->head.opcode == OP_SUB ) {
                cc->left_op = ins->operands[ 0 ];
                cc->right_op = ins->operands[ 1 ];
            } else {
                cc->left_op = NULL;
                cc->right_op = NULL;
            }
            cc->ins = ins;
        } else if( cc_affect == SETS_CC ) {       /* includes compares*/
            if( _OpIsCompare( ins->head.opcode ) ) {
                if( UselessCompare( ins, cc, zero ) ) {
                    DoNothing( ins );
                    change = TRUE;
                    MarkUsedCC( blk );
                } else if( ins->u.gen_table->generate != G_NO ) {
                    cc->state = CONDITIONS_SET;
                    cc->result_op = NULL;
                    cc->op_type = ins->type_class;
                    cc->left_op = ins->operands[ 0 ];
                    cc->right_op = ins->operands[ 1 ];
                    cc->ins = ins;
                }
            } else {
                if( !_OpIsBit( ins->head.opcode ) &&
                    ( ins->ins_flags & INS_DEMOTED ) ) {
                    cc->state = EQUALITY_CONDITIONS_SET;
                } else {
                    cc->state = CONDITIONS_SET;
                }
                if( ins->head.opcode != OP_BIT_TEST_TRUE
                 && ins->head.opcode != OP_BIT_TEST_FALSE ) {
                    cc->result_op = ins->result;
                } else {
                    cc->result_op = NULL;
                }
                cc->op_type = ins->type_class;
                if( ins->head.opcode == OP_SUB ) {
                    cc->left_op = ins->operands[ 0 ];
                    cc->right_op = ins->operands[ 1 ];
                } else {
                    cc->left_op = NULL;
                    cc->right_op = NULL;
                }
                cc->ins = ins;
            }
        }                       /* for PRESERVE, do nothing*/
        if( ins->result != NULL ) {
            if( CondOverlaps( ins->result, cc->left_op )
              || CondOverlaps( ins->result, cc->right_op ) ) {
                cc->left_op = NULL;
                cc->right_op = NULL;
            }
            if( cc_affect != SETS_CC && cc_affect != SETS_SC ) {
                if( CondOverlaps( ins->result, cc->result_op ) ) {
                    cc->result_op = NULL;
                }
            }
        }
        ins = ins->head.next;
    }
    if( jumps > 1 ) {
        cc->state = UNKNOWN_STATE;
    }
    return( change );
}


static  void    GatherSources( block *blk )
/******************************************
    See what the condition code state is at the end of each of the
    ancestors of "blk", and if they are all the same, use this as the
    initial condition code setting for "blk".

*/
{
    block_edge  *edge;
    cc_control  *source_cc;
    cc_control  *cc;

    edge = blk->input_edges;
    cc = blk->cc;
    if( edge == NULL ) {
        cc->state = UNKNOWN_STATE;
    } else {
        source_cc = edge->source->cc;
        cc->state = source_cc->state;
        cc->left_op = source_cc->left_op;
        cc->right_op = source_cc->right_op;
        cc->result_op = source_cc->result_op;
        cc->op_type = source_cc->op_type;
        for(;;) {
            if( cc->state == UNKNOWN_STATE ) break;
            edge = edge->next_source;
            if( edge == NULL ) break;
            source_cc = edge->source->cc;
            if( source_cc->state == UNKNOWN_STATE ) {
                cc->state = UNKNOWN_STATE;
            } else {
                if( source_cc->state < cc->state ) {
                    cc->state = source_cc->state;
                }
                if( source_cc->left_op != cc->left_op
                  || source_cc->right_op != cc->right_op ) {
                    cc->left_op = NULL;
                    cc->right_op = NULL;
                }
                if( source_cc->result_op != cc->result_op ) {
                    cc->result_op = NULL;
                }
                if( cc->result_op == NULL && cc->left_op == NULL ) {
                    cc->state = UNKNOWN_STATE;
                }
#if _TARGET & _TARG_370
                if( source_cc->op_type != cc->op_type ) {
                    cc->state = UNKNOWN_STATE;
                }
#endif
            }
        }
    }
}

static  void    FlowConditions( void )
/*************************************
    For each block in the program, first "GatherSources" to determine
    what the state of the condition codes are on entry to the routine,
    then "Traverse" the block, to see if there is an instruction that
    sets the condition codes for the conditional branches at the end of
    the block correctly, or if the condition codes from previous blocks
    are unaffected by the block and will suffice for the final branch.
*/
{
    block       *blk;
    name        *zero;
    bool        change;

    zero = AllocIntConst( 0 );
    change = TRUE;
    for( ;; ) {
        blk = HeadBlock;
        while( blk != NULL ) {
            GatherSources( blk );
            change |= Traverse( blk, zero );
            blk = blk->next_block;
        }
        if( change == FALSE ) break;
        change = FALSE;
    }
}


extern  void    Conditions( void )
/*********************************
    Traverse the basic blocks and determine if there are any compare
    instructions that we can eliminate, since the condition codes are
    already set by a subtract instruction or something.  Note that the
    internal instuctions with opcodes like OP_CMP_EQUAL generate both a
    compare and a jump.  If we "DoNothing" them, they will still
    generate the jumps, but not the compare.  In a "cc_control", we keep
    track of "left_op", "right_op" and "result_op" as well as "state".
    If "left_op" and "right_op" are set, it means that we have condition
    codes which would do for a comparison of "left_op" with "right_op"
    (subject to the signed/unsigned constraints in "state").  If
    "result_op" is set, it means we have condition codes set which would
    do for a comparison of "result_op" against zero.  On the 370, which
    has the worlds strangest set of condition codes, we use
    "state"=SIGNED_CONDITIONS_SET to mean that the condition codes are
    alright as long as we are doing a comparison of equality or
    inequality.  This is a misnomer, but I was in a hurry.
*/
{
    block       *blk;
    cc_control  *cc;

    blk = HeadBlock;
    while( blk != NULL ) {
        cc = CGAlloc( sizeof( cc_control ) );
        cc->state = UNKNOWN_STATE;
        cc->left_op = NULL;
        cc->right_op = NULL;
        cc->result_op = NULL;
        cc->ins = NULL;
        cc->op_type = XX;
        blk->cc = cc;
        blk->class &= ~BLOCK_VISITED;
        blk = blk->next_block;
    }
    FlowConditions();
    blk = HeadBlock;
    while( blk != NULL ) {
        CGFree( blk->cc );
        blk = blk->next_block;
    }
}
