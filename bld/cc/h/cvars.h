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
* Description:  C compiler global variables.
*
****************************************************************************/


#ifdef __WATCOMC__
    #pragma off( check_stack )
#endif


#define BY_C_FRONT_END

#include <stdio.h>
#include <setjmp.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "target.h"

#ifndef _CPU
    #error _CPU macro not defined
#endif

#if _CPU != 8086
    /* enable Structured Exception Handling for all 32-bit targets */
    #define __SEH__
#endif

typedef char    *MACADDR_T;     /* contains actual pointer to block of memory */
typedef char    *SEGADDR_T;     /* contains actual pointer to block of memory */
typedef char    *MPTR_T;        /* first parm to MacroCopy */
typedef void    *VOIDPTR;

#include "macro.h"
#include "dw.h"
#include "ctypes.h"
#include "cfcb.h"
#include "csegid.h"
#include "ctokens.h"
#include "cerrs.h"
#include "toggle.h"
#include "cmsg.h"
#include "strsave.h"
#include "cmemmgr.h"

#ifndef local
    #define local
#endif

#ifndef global
    #define global  extern
#endif

#define SYM_HASH_SIZE   241
#define ENUM_HASH_SIZE  241
#define MACRO_HASH_SIZE 4093
#define MAX_PARM_LIST_HASH_SIZE  5


global  char    *PCH_Start;     // start of precompiled memory block
global  char    *PCH_End;       // end of precompiled memory block
global  char    *PCH_Macros;    // macros loaded from pre-compiled header
global  char    *PCH_FileName;  // name to use for pre-compiled header
global  INCFILE *IncFileList;   // list of primary include files for PCH
global  SYMPTR  *PCH_SymArray;  // array of symbol table pointers from PCH
global  int     PCH_MaxSymHandle;// number of symbols in PCH_SymArray
global  char    *ScanCharPtr;   // used by character scanning routines
global  int     DebugFlag;
global  TOKEN   CurToken;
global  int     BadTokenInfo;
global  int     TokenLen;
global  int     MTokenLen;      /* macro token length */
global  int     TokenLine;
global  int     SrcFileLineNum; /* duplicate of SrcFile->src_line */
global  int     TokenFno;
global  int     CurrChar;
global  DATA_TYPE  ConstType;
global  unsigned long Constant;
global  uint64  Const64;
global  int     CLitLength;     /* length of string literal */
global  FCB     *MainSrcFile;   /* primary source file being compiled */
global  FCB     *SrcFile;
global  char    *SrcFName;      /* source file name without suffix */
global  char    *DefFName;      /* .def file name (prototypes) */
global  char    *WholeFName;    /* whole file name with suffix */
global  char    *ForceInclude;
global  char    *AuxName;
global  struct  fname_list *FNames;     /* list of file names processed */
global  struct  rdir_list *RDirNames;  /* list of read only directorys */
global  char    *ErrFName;      /* file name to be used in error message */
global  unsigned ErrLine;       /* line number to be used in error msg */
global  FILE    *ErrFile;       /* error file */
global  FILE    *DefFile;       /* output for func prototypes */
global  FILE    *CppFile;       /* output for preprocessor */
global  FILE    *DepFile;       /* make style auto depend file */
global  struct  cpp_info *CppStack; /* #if structure control stack */
global  char    *HFileList;     /* list of path names to try for H files */
global  int     SrcLineNum;
global  int     SrcFno;
global  int     SrcLineCount;   /* # of lines in primary source file */
global  int     IncLineCount;   /* # of lines in all included files  */
global  int     ErrCount;       /* total # of errors encountered     */
global  int     WngCount;       /* total # of warnings encountered   */
global  int     WngLevel;       /* warning severity level */
global  int     TypeCount;      /* total # of type nodes allocated   */
global  int     GblSymCount;    /* total # of global symbols */
global  int     LclSymCount;    /* total # of local and temporary symbols */
global  int     FuncCount;      /* total # of functions defined in module */
global  int     MacroCount;     /* total # of macros defined */
global  int     TagCount;       /* total # of tag entries */
global  int     FieldCount;     /* total # of struct field names */
global  int     EnumCount;      /* total # of enumerated symbols */
global  int     SizeOfCount;    /* # of nested sizeof() expressions  */
global  int     NestLevel;      /* pre-processing level of #if */
global  int     SkipLevel;      /* pre-processing level of #if to skip to */
global  int     SymLevel;       /* current lex level (# of nested {) */
global  int     HashValue;      /* hash value for identifier */
global  TOKEN   KwHashValue;    /* hash value for keyword */
global  int     MacHashValue;   /* hash value for macro name */
global  char    *SavedId;       /* saved id when doing look ahead */
global  int     SavedHash;      /* hash value for saved id */
global  int     SavedTokenLine; /* value of TokenLine when id saved */
global  int     SavedTokenFno;  /* value of TokenFno when id saved */
global  int     LAToken;        /* look ahead token */
global  LABELPTR LabelHead;     /* list of all labels defined in function */
global  TAGPTR  TagHead;        /* list of all struct, union, enum tags */
global  TAGPTR  DeadTags;       /* list of all tags that are out of scope */
global  TYPEPTR TypeHead;       /* list of all type nodes allocated */
global  TYPEPTR FuncTypeHead[ MAX_PARM_LIST_HASH_SIZE + 1 ];
global  TYPEPTR VoidParmList[2];/* function with void parm */
global  char    *SymLoc;        /* file name with defn of symbol */
global  PARMPTR ParmList;       /* list of parms for function */
global  SYM_HANDLE GlobalSym;   /* global symbol table list head */
#if _CPU == 386
global  SYM_HANDLE SymSTOD;     /* builtin symbol for 'rep stosd' */
global  SYM_HANDLE SymSTOSB;    /* builtin symbol for '__STOSB' */
global  SYM_HANDLE SymSTOSD;    /* builtin symbol for '__STOSD' */
#endif
#ifdef __SEH__
global  SYM_HANDLE SymTryInit;  /* builtin symbol for '__TryInit' */
global  SYM_HANDLE SymTryFini;  /* builtin symbol for '__TryFini' */
global  SYM_HANDLE SymExcept;   /* builtin symbol for '__Except' */
global  SYM_HANDLE SymFinally;  /* builtin symbol for '__Finally' */
global  SYM_HANDLE SymTryUnwind;/* builtin symbol for '__TryUnwind' */
global  SYM_HANDLE TrySymHandle;/* builtin symbol for local try block */
global  int     TryScope;       /* current scope of _try blocks */
global  int     TryCount;       /* current number of _try blocks */
#endif
global  SYM_HANDLE SymSTOW;     /* builtin symbol for 'rep stosw' */
global  SYM_HANDLE SymSTOWB;    /* builtin symbol for 'rep stosw, stosb' */
global  SYM_HANDLE SymMIN;      /* builtin symbol for 'min(a,b)' */
global  SYM_HANDLE SymMAX;      /* builtin symbol for 'max(a,b)' */
global  SYM_HANDLE SymMEMCMP;   /* builtin symbol for 'memcmp' func */
global  SYM_HANDLE SpecialSyms; /* builtin symbols (thread linked) */
global  SYM_HANDLE CharSymHandle;/* sym handle for "char" typedef */
global  SYM_HANDLE Sym_CS;      /* sym handle for __segname("_CODE") ie. CS */
global  SYM_HANDLE Sym_SS;      /* sym handle for __segname("_STACK")ie. SS */
global  SYM_HANDLE SymCover;    /* sym handle for '__COVERAGE' */
global  SYM_HANDLE SymDFAbbr;   /* sym handle for '__DFABBREV' */
global  SYM_HANDLE SymChipBug;  /* sym handle for '__chipbug' */
global  FIELDPTR ErrSym;

#if _CPU == 386
global  void     *FunctionProfileBlock; /* handle for profiling data block */
global  int      FunctionProfileSegment; /* segment for profiling data block */
#endif

global  int         MacroDepth;
global  byte        *MacroPtr;
global  MEPTR       NextMacro;
global  MEPTR       UndefMacroList;
global  MEPTR       *MacHash;       /* [ MACRO_HASH_SIZE ] */
global  ENUMPTR     EnumTable[ ENUM_HASH_SIZE ];
global  SYM_HASHPTR *HashTab;
global  TYPEPTR     BaseTypes[TYPE_LAST_ENTRY];
global  int         CTypeCounts[TYPE_LAST_ENTRY];

#define BUF_SIZE 512
global  size_t BufSize;
global  char *Buffer;
global  char *TokenBuf;

global  unsigned long   GenSwitches;    /* target independant switches for code generator */
global  unsigned long   TargetSwitches; /* target specific code generator switches */

global  unsigned      ProcRevision;   /* processor revision for c.g. */
global  char    *GenCodeGroup;        /* pointer to code group name */
global  int     ProEpiDataSize;       /* data to be alloc'd for pro/epi hook */
global  int     Toggles;              /* global toggle flags */
global  int     ErrLimit;

global  unsigned DataThreshold; /* sizeof(obj) > this ==> separate segment */
global  unsigned Inline_Threshold;      /* -oe=num for function inlining */

global  int     DataPtrSize;
global  int     CodePtrSize;
global  int     DeadCode;       /* non-zero => next stmt is unreachable */
global  int     TmpSymCount;
global  int     LitCount;
global  int     LitPoolSize;
global  unsigned MacroSize;
global  struct  comp_flags             CompFlags;
global  struct  global_comp_flags      GlobalCompFlags;
global  int     SegmentNum;     /* next PRIVATE segment number to use */
global  int     FarStringSegment;

global  void    *Environment;   /* var for Suicide() */

#define MAX_LEVEL       1024

/* The following 3 arrays are also used by CGEN for saving _try block info */
global  TREEPTR ValueStack[ MAX_LEVEL ];
global  char    Token[ MAX_LEVEL ];
global  char    Class[ MAX_LEVEL ];
global  int     Level;

global  struct  segment_list *SegListHead;
global  int     SegImport;              /* next segment # for import sym */
global  int     SegData;                /* data segment # for -nd option */

global TREEPTR  FirstStmt;              /* root of expression tree */

global dbug_type ScopeStruct;
global dbug_type ScopeUnion;
global dbug_type ScopeEnum;

global dbug_type B_Int_1;
global dbug_type B_UInt_1;
global dbug_type B_Short;
global dbug_type B_UShort;
global dbug_type B_Int;
global dbug_type B_UInt;
global dbug_type B_Int32;
global dbug_type B_UInt32;
global dbug_type B_Int64;
global dbug_type B_UInt64;

global  int     OptSize;        /* 100 => make pgm small as possible */
global  char    __Time[10];     /* "HH:MM:SS" for __TIME__ macro */
global  char    __Date[12];     /* "MMM DD YYYY" for __DATE__ macro */

global  char    *MsgFlags;      /* Bit mask of disabled messages */

global  struct macro_seg_list {
    struct macro_seg_list *next;
    MACADDR_T segment;
} *MacSegList;                  /* pointer to list of macro segments */

global  MACADDR_T MacroSegment; /* segment for macro definitions */
global  MACADDR_T MacroOffset;  /* first free byte in MacroSegment */
global  MACADDR_T MacroLimit;   /* last  free byte in MacroSegment */

global  int     SwitchChar;     /* DOS switch character */
global  int     LoopDepth;      /* current nesting of loop constructs */
global  char    CLIB_Name[10];   /* "1CLIBMT3x" */
global  char    MATHLIB_Name[10];/* "5MATHx" or "8MATH87x" */
global  char    *EmuLib_Name;   /* "9emu87" for -fpi, "9noemu87" for -fpi */
#define USER_LIB_PRIO '9'

global  struct library_list {
    struct  library_list    *next;
    char                    prio;
    char                    name[1];
} *HeadLibs;

global  SYMPTR  CurFunc;        /* current function being worked on */
global  SYM_ENTRY CurFuncSym;   /* for contents of current function symbol */
global  SYM_HANDLE CurFuncHandle;/* sym_handle for current function */
global  SYM_HANDLE LastFuncOutOfMem; /* cinfo: */
global  SYM_HASHPTR HashFreeList;/* list of available hash entries */

global  unsigned SymBufNum;     /* current buffer in memory */
global  unsigned SymSegNum;     /* segment # containing buffer */
global  unsigned LastSymBuf;    /* # of last symbol table buffer */
global  unsigned SymBufDirty;   /* 1 => buffer has been changed */
global  SEGADDR_T SymSegment;   /* segment # for symbol table buffers */

global  TYPEPTR StringType;     /* "unsigned char *" for use by literals */
global  TYPEPTR ConstCharType;  /* "const char" type */
global  TYPEPTR StringArrayType;/* "unsigned char []" used by literals */
global  struct nested_parm_lists {
        struct nested_parm_lists *prev_list;
        TYPEPTR *next_parm_type;
} *NestedParms;

#ifndef LARGEST_QUAD_INDEX
    #define LARGEST_QUAD_INDEX             0xFFFF
    #define LARGEST_DATA_QUAD_INDEX        0xFFFFF
#else
    #define LARGEST_DATA_QUAD_INDEX        LARGEST_QUAD_INDEX
#endif
#define LARGEST_SYM_INDEX   0xFFFF

#define SYM_BUF_SIZE    1024
#define SYMS_PER_BUF    (SYM_BUF_SIZE/sizeof(SYM_ENTRY))
#define SYMBUFS_PER_SEG 16
#define SYM_SEG_SIZE    (SYM_BUF_SIZE*SYMBUFS_PER_SEG)

#define MAX_SYM_SEGS  (LARGEST_SYM_INDEX/(SYMS_PER_BUF*SYMBUFS_PER_SEG)+1)

global  struct seg_info SymSegs[MAX_SYM_SEGS];  /* segments for symbols */

#define STRING_HASH_SIZE        1024
global  STR_HANDLE StringHash[STRING_HASH_SIZE];    /* string literals */
global  char    *TextSegName;   /* name of the text segment */
global  char    *DataSegName;   /* name of the data segment */
global  char    *CodeClassName; /* name of the code class */
global  char    *ModuleName;    /* name of module */
global  char    *ObjectFileName;/* name of object file */
global  char    *DependFileName;/* name of make style auto depend file */
global  char    *DependHeaderPath;/* path to prepend if included header has none */
global  char    *DependTarget;  /* name of target in make style autodep */
global  char    *SrcDepName;    /* name of first depend (sourcefile)*/
global  char     DependForceSlash;/* type of slash to force to in depend output */
global  int      PackAmount;    /* current packing alignment */
global  int      GblPackAmount; /* packing alignment given on command line */
global  struct textsegment *TextSegList; /* list of #pragma alloc_text segs*/

typedef enum {
    SEGTYPE_CODE       = 1,     /* #pragma code_seg("segname","class") */
    SEGTYPE_DATA       = 2,     /* #pragma data_seg("segname","class") */
    SEGTYPE_BASED      = 3,     /* __based(__segname("segname")) */
    SEGTYPE_INITFINI   = 4,     /* "XI" or "YI" segment */
    SEGTYPE_INITFINITR = 5,     /* thread data */
} seg_type;

struct user_seg;

global struct user_seg  *UserSegments;

#if defined(__386__) && defined(__FLAT__) && defined(__WATCOMC__)

extern  int     far_strcmp( char *, char *, int );
#pragma aux     far_strcmp = 0xf3        /* rep   */\
                             0xa6        /* cmpsb */\
                             0x74 0x01   /* je L1 */\
                             0x41        /* inc ecx */\
         parm caller [edi] [esi] [ecx] value [ecx] modify exact [esi edi ecx];
extern  int     far_strlen_plus1( char * );
#pragma aux     far_strlen_plus1 = 0x29 0xc0    /* sub eax,eax */\
                                   0x4f         /* dec edi */\
                                   0x47         /* L1:inc edi */\
                                   0x40         /* inc eax */\
                                   0x80 0x3f 0x00 /* cmp [edi],0 */\
                                   0x75 0xf9    /* jne L1 */\
        parm caller [edi] value [eax] modify exact [edi eax];
extern  void    far_memcpy( char *, char *, int );
#pragma aux     far_memcpy = 0xf3 0xa4  /* rep movsb */\
        parm caller [edi] [esi] [ecx] modify exact [esi edi ecx];

#else

#define far_strcmp(__p1,__p2,__len)     memcmp( __p1, __p2, __len )
#define far_strlen_plus1( p )           (strlen( p ) + 1)
#define far_memcpy( p1, p2, len )       memcpy( p1, p2, len )

#endif

global  int     (*NextChar)();
global  struct debug_fwd_types *DebugNameList;

global  unsigned Column;        /* skip to Column when reading */
global  unsigned Trunc;         /* stop at Trunc when reading  */
global  int     EnumRecSize;    /* size of largest enum entry */
global  int     PreProcChar;
global  TYPEPTR PrevProtoType;          /* prev func prototype */

global  unsigned SegAlignment[FIRST_PRIVATE_SEGMENT];
global  unsigned TargSys;
global  unsigned DefDataSegment;  /* #pragma data_seg("segname","class") */
global  struct textsegment *DefCodeSegment; /* #pragma code_seg("seg","c") */

global  unsigned        UnrollCount;    /* #pragma unroll(#); */
global  unsigned char   InitialMacroFlag;
global  unsigned char   Stack87;
global  char            *ErrorFileName;

global struct  undef_names {
    struct undef_names  *next;
    char                *name;
} *UndefNames;

//================= Function Prototypes ========================

extern  unsigned char TBreak( void );           /* casmsupp */

extern  void    SetDBChar(int);                 /* casian */

extern  struct aux_entry *AuxLookup( char * );  /* caux.c */
extern  void    PragmaFini( void );             /* caux.c */

extern  int     ChkCompatibleFunction( TYPEPTR typ1, TYPEPTR typ2, int topLevelCheck ); /*ccheck*/
extern  void    TernChk( TYPEPTR typ1, TYPEPTR typ2 ); /*check */
extern  void    ChkCallParms(void);             /* ccheck */
extern  void    ChkRetType(TREEPTR);            /* ccheck */
extern  void    ChkConst(TREEPTR);              /* ccheck */
extern  void    CompatiblePtrType(TYPEPTR,TYPEPTR); /* ccheck */
extern  int     IdenticalType(TYPEPTR,TYPEPTR); /* ccheck */
extern  int     VerifyType(TYPEPTR,TYPEPTR,SYMPTR);/* ccheck */
extern  TYPEPTR SkipTypeFluff( TYPEPTR typ );      /* ccheck */
extern  void    ParmAsgnCheck( TYPEPTR typ1, TREEPTR opnd2, int parm_num ); /* ccheck */

//ccmain.c
extern  void    FreeRDir( void );
extern  void    FrontEndInit( bool reuse );
extern  int     FrontEnd(char **);
extern  void    FrontEndFini( void );
extern  void    CppComment(int);
extern  int     CppPrinting(void);
extern  void    CppPutc(int);
extern  void    CppPrtf(char *,...);
extern  void    SetCppWidth(unsigned);
extern  void    PrtChar(int);
extern  void    PrtToken(void);
extern  int     OpenSrcFile(char *,int);
extern  void    OpenDefFile(void);
extern  FILE    *OpenBrowseFile(void);
extern  void    CloseFiles(void);
extern  void    FreeFNames(void);
extern  char    *ErrFileName(void);
extern  char    *DepFileName(void);
extern  char    *ObjFileName(char *);
extern  char    *ForceSlash(char *, char );
extern  char    *CreateFileName( char *template, char *extension, bool forceext );
extern  char    *GetSourceDepName( void );

extern  FNAMEPTR AddFlist(char const *);
extern  FNAMEPTR FileIndexToFName(unsigned);
extern  char    *FNameFullPath( FNAMEPTR flist );
extern  char    *FileIndexToCorrectName( unsigned file_index );
extern  int     FListSrcQue(void);
extern  void    SrcFileReadOnlyDir( char const *dir );
extern  void    SrcFileReadOnlyFile( char const *file );
extern  bool    SrcFileInRDir( FNAMEPTR flist );
extern  int     SrcFileTime(char const *,time_t *);
extern  void    SetSrcFNameOnce( void );
extern  void    GetNextToken(void);
extern  void    EmitLine(unsigned,char *);
extern  void    EmitPoundLine(unsigned,char *,int);

// cdata.c
extern  void    InitGlobalVars( void );

// from cdebug.c
extern  dbug_type DBType(TYPEPTR);
extern  void    EmitDBType(void);
extern  dbug_type FEDbgType( CGSYM_HANDLE cgsym_handle );
extern  dbug_type FEDbgRetType( CGSYM_HANDLE cgsym_handle );

extern  void    ParsePgm(void);
extern  void    AdjParmType(SYMPTR sym);
extern  void    Chk_Struct_Union_Enum(TYPEPTR);
extern  void    Declarator( SYMPTR sym, type_modifiers mod, TYPEPTR typ, decl_state state );
extern  int     DeclList(SYM_HANDLE *);
extern  FIELDPTR FieldDecl( TYPEPTR typ, type_modifiers mod, decl_state state );
extern  TYPEPTR SkipDummyTypedef(TYPEPTR);
extern  TYPEPTR TypeName(void);

// cdecl2.c
extern  void InvDecl( void );

// cinfo.c
extern  segment_id SymSegId( SYMPTR sym );
extern  void    SetSegSymHandle( SYM_HANDLE sym_handle, int segment );

extern  void    InitDataQuads(void);            /* cdinit */
extern  void    FreeDataQuads(void);            /* cdinit */
extern  int     DataQuadsAvailable(void);       /* cdinit */
extern  int     StartDataQuadAccess(void);      /* cdinit */
extern  DATA_QUAD *NextDataQuad(void);          /* cdinit */
extern  void    InitSymData(TYPEPTR,TYPEPTR,int);       /* cdinit */
extern  void    StaticInit(SYMPTR,SYM_HANDLE);  /* cdinit */
extern  void    VarDeclEquals(SYMPTR,SYM_HANDLE);/* cdinit */

extern  void    DumpFuncDefn(void);             /* cdump */
extern  void    SymDump(void);                  /* cdump */
extern  char *  DiagGetTypeName(TYPEPTR typ);   /* cdump */

extern  SEGADDR_T AccessSegment(struct seg_info *);     /* cems */
extern  SEGADDR_T AllocSegment(struct seg_info *);      /* cems */

extern  TYPEPTR EnumDecl(int);                  /* cenum */
extern  int     EnumLookup(int,char *,ENUM_INFO *); /* cenum */
extern  void    EnumInit(void);                 /* cenum */
extern  void    FreeEnums(void);                /* cenum */

//cerror.c
extern  void    CErr1(int);
extern  void    CErr2(int,int);
extern  void    CErr2p(int,char *);
extern  void    CErr(int,...);
extern  void    SetErrLoc(char *,unsigned);
extern  void    SetSymLoc(SYMPTR);
extern  void    CWarn1(int,int);
extern  void    CWarn2(int,int,int);
extern  void    CWarn(int,int,...);
extern  void    PCHNote( int msgnum, ... );
extern  void    CInfoMsg(int,...);
extern  void    CSuicide(void);
extern  void    OpenErrFile(void);
extern  void    FmtCMsg( char *buff, cmsg_info *info );
extern  void    SetDiagSymbol(SYMPTR sym, SYM_HANDLE handle);
extern  void    SetDiagType2(TYPEPTR typ_source, TYPEPTR typ_target);
extern  void    SetDiagPop(void);

//  cexpr2.c
extern  void    ExprInit(void);
extern  void    ChkCallNode( TREEPTR tree );
extern  TREEPTR Expr(void);
extern  TREEPTR AddrExpr(void);
extern  TREEPTR BoolExpr(TREEPTR);
extern  TREEPTR CommaExpr(void);
extern  long int ConstExpr(void);
typedef struct {
    int64     value;
    DATA_TYPE type;
} const_val;
extern  bool    ConstExprAndType(const_val *);
extern  TREEPTR SingleExpr(void);
extern  TREEPTR IntLeaf(target_int);
extern  TREEPTR RValue(TREEPTR);
extern  TREEPTR LongLeaf(target_long);
extern  TREEPTR UIntLeaf(target_uint);
extern  TREEPTR VarLeaf(SYMPTR,SYM_HANDLE);
extern  TREEPTR BasedPtrNode(TYPEPTR,TREEPTR);
extern  int     IsLValue(TREEPTR);
extern  op_flags OpFlags( type_modifiers  flags );
extern  type_modifiers FlagOps( op_flags ops );
extern  FIELDPTR SearchFields( TYPEPTR *class_typ, unsigned long *field_offset,
                               char *name );

//cfeinfo.c
extern  int     VarFunc(SYMPTR);
extern  int     VarParm(SYMPTR);
extern  void    GetCallClass(SYM_HANDLE);
extern  struct aux_info *FindInfo(SYMPTR,SYM_HANDLE);
extern  int     FunctionAborts(SYMPTR,SYM_HANDLE);
extern  int     ParmsToBeReversed(int,struct aux_info *);
extern  char    *SrcFullPath( char *, char const *, unsigned );

//cfold2.c
extern  void CastFloatValue( TREEPTR leaf, DATA_TYPE newtype );
extern  void CastConstValue(TREEPTR,DATA_TYPE);
extern  void DoConstFold(TREEPTR);
extern  void FoldExprTree(TREEPTR);
extern  bool BoolConstExpr( void );

//cgen2.c
extern  void    DoCompile(void);
extern  void    EmitInit(void);
extern  void    EmitAbort(void);
extern  void    EmitStrPtr(STR_HANDLE,int);
extern  int     EmitBytes(STR_HANDLE);
extern  int     CGenType(TYPEPTR);
extern  void    GenInLineFunc( SYM_HANDLE sym_handle );
extern  bool    IsInLineFunc( SYM_HANDLE sym_handle );
extern  int     PtrType( TYPEPTR typ, type_modifiers flags );

extern  void    EmitDataQuads(void);            /* cgendata */
extern  void    EmitZeros(unsigned long);       /* cgendata */
extern  void    AlignIt(TYPEPTR);               /* cgendata */

extern  int     GetNextChar(void);              /* cgetch */
extern  int     GetCharCheck(int);              /* cgetch */
extern  int     getCharAfterBackSlash(void);    /* cgetch */
extern  void    GetNextCharUndo(int);           /* cgetch */
extern  void    CloseSrcFile(FCB *);            /* cgetch */

// cinfo.c
extern  void    SegInit(void);
extern  fe_attr FEAttr(CGSYM_HANDLE);
extern  back_handle FEBack(CGSYM_HANDLE);
extern  char    *FEName(CGSYM_HANDLE);
extern  int     FEParmType(CGSYM_HANDLE,CGSYM_HANDLE,int);
extern  segment_id FESegID(CGSYM_HANDLE);
extern  int     AddSegName(char *,char *,int);
extern  int     DefThreadSeg( void );
extern  void    EmitSegLabels(void);
extern  void    FiniSegLabels(void);
extern  void    FiniSegBacks(void);
extern  void    SetSegs(void);
extern  SYM_HANDLE SegSymHandle(int);
extern  void    SetFuncSegment(SYMPTR,int);
extern  void    SetFarHuge(SYMPTR,int);
extern  char    *SegClassName(unsigned);
extern  hw_reg_set *SegPeggedReg(unsigned);
extern  void    SetSegment(SYMPTR);
extern  void    SetSegAlign(SYMPTR);
extern  void    AssignSeg(SYMPTR);
// cintmain
extern void     ConsErrMsg( cmsg_info  *info );
extern void     ConsMsg( char const  *line );
extern void     BannerMsg( char const  *line );
extern void     DebugMsg( char const  *line );
extern void     NoteMsg( char const  *line );
extern void     ConBlip( void );
extern bool     ConTTY( void );
extern char    *FEGetEnv( char const  *name );
extern void     FESetCurInc( void );

//cmac1.c
extern  void    EnlargeBuffer(size_t);
extern  void    MacroInit(void);
extern  void    MacroAddComp(void);
extern  void    MacroFini(void);
extern  void    MacroPurge(void);
extern  void    GetMacroToken(void);
extern  int     SpecialMacro(MEPTR);
extern  void    DoMacroExpansion(void);
//cmac2.c
extern  int     ChkControl(void);
extern  bool    MacroDel( char *name );
extern  void    CppStackInit( void );
extern  void    CppStackFini(void);

//cmacadd.c
extern  void    AllocMacroSegment(unsigned);
extern  void    FreeMacroSegments(void);
extern  void    MacLkAdd( MEPTR mentry, int len, enum macro_flags flags );
extern  void    MacroAdd( MEPTR mentry, char *buf, int len, enum macro_flags flags );
extern  int     MacroCompare(MEPTR,MEPTR);
extern  void    MacroCopy(MPTR_T,MACADDR_T,unsigned);
extern  MEPTR   MacroLookup(const char *);
extern  void    MacroOverflow(unsigned,unsigned);
extern  SYM_HASHPTR SymHashAlloc(unsigned);

//cmath2.c
extern  TREEPTR AddOp(TREEPTR,TOKEN,TREEPTR);
extern  TREEPTR InitAsgn( TYPEPTR,TREEPTR );
extern  TREEPTR AsgnOp(TREEPTR,TOKEN,TREEPTR);
extern  TREEPTR BinOp(TREEPTR,TOKEN,TREEPTR);
extern  TREEPTR CnvOp(TREEPTR,TYPEPTR,int);
extern  TREEPTR FlowOp(TREEPTR,int,TREEPTR);
extern  TREEPTR IntOp(TREEPTR,TOKEN,TREEPTR);
extern  TREEPTR RelOp(TREEPTR,TOKEN,TREEPTR);
extern  TREEPTR ShiftOp(TREEPTR,TOKEN,TREEPTR);
extern  TYPEPTR TernType(TREEPTR,TREEPTR);
extern  TYPEPTR TypeOf(TREEPTR);
extern  TREEPTR UComplement(TREEPTR);
extern  TREEPTR UMinus(TREEPTR);
extern  DATA_TYPE DataTypeOf(TYPEPTR);
extern  int     FuncPtr(TYPEPTR);
extern  TREEPTR ParmAss( TREEPTR opnd, TYPEPTR newtyp );
extern  pointer_class   ExprTypeClass( TYPEPTR typ );
extern  TREEPTR LCastAdj(  TREEPTR tree );

extern  char    *BadCmdLine(int,char *);        /* cmodel */
extern  char    *Define_Macro(char *);          /* cmodel */
extern  char    *Define_UserMacro(char *);      /* cmodel */
extern  void    PreDefine_Macro(char *);        /* cmodel */
extern  char    *AddUndefName(char *);          /* cmodel */
extern  void    InitModInfo(void);              /* cmodel */
extern  void    MiscMacroDefs(void);            /* cmodel */
//cmsg.c
extern char const *CGetMsgStr(  msg_codes msgcode );
extern void CGetMsg( char *msgbuf, msg_codes msgnum );
extern void InitMsg( void );
extern void FiniMsg( void );
extern char const * UsageText(void);      // GET INTERNATIONAL USAGE TEXT
extern msgtype CGetMsgType( msg_codes msgcode );
char const *CGetMsgPrefix( msg_codes msgcode );

extern  int     NameCmp(const void *,const void *,int); /* cname */

extern  int     EqualChar(int);                 /* coptions */
extern  void    GenCOptions(char **);           /* coptions */
extern  void    MergeInclude(void);             /* coptions */

extern  void    CPragmaInit( void );            /* cpragma */
extern  int     SetToggleFlag( char const *name, int const value ); /* cpragma */
extern  void    CPragma(void);                  /* cpragma */
extern  struct textsegment *LkSegName(char *,char *);   /* cpragma */
extern  struct textsegment *NewTextSeg(char *,char *,char *);
extern  void    PragmaInit(void);               /* cpragma */
extern  void    PragmaFini(void);               /* cpragma */
extern  void    PragInit(void);                 /* cpragma */
extern  void    PragEnding(void);               /* cpragma */
extern  void    PragObjNameInfo(void);          /* cpragma */
extern  int     PragRecog(char *);              /* cpragma */
extern  hw_reg_set PragRegList(void);           /* cpragma */
extern  void    PragManyRegSets(void);          /* cpragma */
extern  void    PragCurrAlias(void);            /* cpragma */
extern  TOKEN   PragRegSet(void);               /* cpragma */
extern  void    ChkPragmas(void);               /* cpragma */
extern  void    CreateAux(char *);              /* cpragma */
extern  void    SetCurrInfo(void);              /* cpragma */
extern  void    XferPragInfo(char*,char*);      /* cpragma */
extern  void    EnableDisableMessage(int,unsigned);/* cpragma */

extern  void    AsmStmt(void);                  /* cprag??? */
extern  void    PragAux(void);                  /* cprag??? */
extern  hw_reg_set PragRegName(char *);         /* cprag??? */

extern  void    InitPurge(void);                /* cpurge */
extern  void    PurgeMemory(void);              /* cpurge */

extern  void    ScanInit(void);                 /* cscan */
extern  int     InitPPScan(void);               /* cscan */
extern  void    FiniPPScan(int);                /* cscan */
extern  int     CalcHash(char *,int);           /* cscan */
extern  unsigned hashpjw(char *);               /* cscan */
extern  int     ESCChar(int,const char **,char *); /* cscan */
extern  void    SkipAhead(void);                /* cscan */
extern  int     ScanSlash(void);                /* cscan */
extern  int     ScanToken(void);                /* cscan */
extern  void    ReScanInit(char *);             /* cscan */
extern  int     ReScanBuffer(void);             /* cscan */
extern  int     ReScanToken(void);              /* cscan */
extern  char    *ReScanPos(void);               /* cscan */
extern  int     IdLookup(const char *);         /* cscan */
extern  int     KwLookup(const char *);         /* cscan */
extern  int     NextToken(void);                /* cscan */
extern  int     PPNextToken(void);              /* cscan */

extern  unsigned long SizeOfArg(TYPEPTR);       /* csizeof */

extern  void    InitStats(void);                /* cstats */
extern  void    PrintStats(void);               /* cstats */

extern  void    LookAhead(void);                /* cstmt */
extern  void    Statement(void);                /* cstmt */
extern  void    AddStmt(TREEPTR);               /* cstmt */
extern  void    GenFunctionNode(SYM_HANDLE);    /* cstmt */
extern  int     NextLabel(void);                /* cstmt */
extern  void    StmtInit( void );               /* cstmt */

extern  void    FreeLiteral(STRING_LITERAL *);  /* cstring */
extern  STRING_LITERAL  *GetLiteral(void);      /* cstring */
extern  void    LoadUnicodeTable(long);         /* cstring */
extern  void    StringInit(void);               /* cstring */
extern  TREEPTR StringLeaf(int);                /* cstring */

extern  void    SymInit(void);                  /* csym */
extern  void    SpcSymInit(void);               /* csym */
extern  void    SymFini(void);                  /* csym */
extern  void    SymCreate(SYMPTR,char *);       /* csym */
extern  SYM_HANDLE SegSymbol(char *,int);       /* csym */
extern  SYM_HANDLE SpcSymbol(char *,int);       /* csym */
extern  SYM_HANDLE SymAdd(int,SYMPTR);          /* csym */
extern  SYM_HANDLE SymAddL0(int,SYMPTR);        /* csym */
extern  SYM_HANDLE SymLook(int,char *);         /* csym */
extern  SYM_HANDLE Sym0Look(int,char *);        /* csym */
extern  SYM_HANDLE SymLookTypedef(int,char *,SYMPTR);   /* csym */
extern  void    SymGet(SYMPTR,SYM_HANDLE);      /* csym */
extern  SYMPTR  SymGetPtr(SYM_HANDLE);          /* csym */
extern  void    SymReplace(SYMPTR,SYM_HANDLE);  /* csym */
extern  void    EndBlock(void);                 /* csym */
extern  SYM_HANDLE MakeFunction(char *,TYPEPTR);/* csym */
extern  SYM_HANDLE MakeNewSym(SYMPTR,char,TYPEPTR,int); /* csym */
extern  LABELPTR LkLabel(char *);               /* csym */
extern  void    FreeLabels(void);               /* csym */
extern  XREFPTR NewXref(XREFPTR);               /* csym */
extern  void    FreeXrefs(XREFPTR);             /* csym */
extern  unsigned   SymGetNumSyms( void );       /* csym */
extern  unsigned   SymGetNumSpecialSyms( void );/* csym */
extern  SYM_HANDLE SymGetFirst( void );         /* csym */
extern  SYM_HANDLE SymGetNext( SYM_HANDLE sym_handle ); /* csym */


extern  void    TimeInit(void);                 /* ctimepc */
//ctype.c
extern  void    CTypeInit(void);
extern  void    InitTypeHashTables(void);
extern  void    SetSignedChar(void);
extern  TYPEPTR GetType(DATA_TYPE);
extern  TYPEPTR ArrayNode(TYPEPTR);
extern  TYPEPTR FuncNode(TYPEPTR, type_modifiers, TYPEPTR *);
extern  TYPEPTR TypeDefault(void);
extern  TYPEPTR PtrNode(TYPEPTR,type_modifiers,int);
extern  TYPEPTR BPtrNode(TYPEPTR,type_modifiers,int,SYM_HANDLE, BASED_KIND);
extern  TYPEPTR TypeNode(DATA_TYPE,TYPEPTR);
extern  int     TypeQualifier(void);
extern  void    TypeSpecifier( decl_info *info );
extern  void    FullDeclSpecifier( decl_info *info );
extern  TAGPTR  NullTag(void);
extern  TAGPTR  TagLookup(void);
extern  void    FreeTags(void);
extern  unsigned long TypeSize(TYPEPTR);
/* CarlYoung 31-Oct-03 */
extern  unsigned long TypeSizeEx( TYPEPTR, unsigned long * pFieldWidth );
extern  TAGPTR  VfyNewTag( TAGPTR, int );
extern  void    VfyNewSym( int, char * );
extern  unsigned GetTypeAlignment( TYPEPTR );
extern  void    TypesPurge( void );
extern  void    AddTypeHash( TYPEPTR );
extern  void    AddPtrTypeHash( TYPEPTR );

extern  void    CCusage( void );                        /* cusage */

extern  void    CErrSymName( int, SYMPTR,SYM_HANDLE );  /* cutil */
extern  void    Expecting( char * );                    /* cutil */
extern  void    ExpectingAfter( char *, char * );       /* cutil */
extern  void    ExpectConstant( void );                 /* cutil */
extern  void    ExpectEndOfLine( void );                /* cutil */
extern  void    ExpectIdentifier( void );               /* cutil */
extern  void    ExpectString( void );                   /* cutil */
extern  void    ExpectStructUnionTag();                 /* cutil */
extern  void    MustRecog( TOKEN );                     /* cutil */
extern  SYM_NAMEPTR SymName( SYMPTR, SYM_HANDLE );      /* cutil */

extern  void    DwarfBrowseEmit( void );                /* dwarf */
extern  char    *ftoa( FLOATVAL * );                    /* ftoa */
extern  unsigned int JIS2Unicode( unsigned );           /* jis2unic */

// pchdr.c
extern  int     UsePreCompiledHeader( char * );
extern  void    InitBuildPreCompiledHeader( void );
extern  void    BuildPreCompiledHeader( char * );
extern  void    FreePreCompiledHeader( void );

extern  unsigned char     _dos_switch_char( void );     /* swchar */
extern  void    CBanner( void );                        /* watcom */
extern  void    MyExit( int ret );                      /* cintmain */

extern  void    DBSetSymLoc( CGSYM_HANDLE, long );      /* dbsupp */

// cstmt2.c
extern  SYM_HANDLE GetBlockSymList( void );
extern  void    InitStmt( void );
extern  void    SwitchPurge( void );

#ifndef min
    #define min( a, b )  ((a < b ) ? (a) : (b))
#endif

#ifndef max
    #define max( a, b )  ((a > b ) ? (a) : (b))
#endif

/* Macro to skip all typedefs and arrive at the underlying type */
#define SKIP_TYPEDEFS( typeptr )                        \
    while( typeptr->decl_type == TYPE_TYPEDEF ) {       \
        typeptr = typeptr->object;                      \
    }
