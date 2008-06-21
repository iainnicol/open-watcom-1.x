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
* Description:  Common stuff for wcl and owcc
*
****************************************************************************/


/* Several char foo[MAX_CMD] arrays are defined. Overflow goes undetected */
#if defined(__OS2__) || defined(__NT__) || defined(__UNIX__)
#define MAX_CMD 10240
#else
#define MAX_CMD 250
#endif

#ifdef __UNIX__
#define OBJ_EXT                 ".o"
#define OBJ_EXT_SECONDARY       ".obj"
#define PATH_SEP    '/'
#define EXE_EXT ""
#else
#define OBJ_EXT                 ".obj"
#define OBJ_EXT_SECONDARY       ".o"
#define PATH_SEP    '\\'
#define EXE_EXT ".exe"
#endif

#define NULLCHAR    '\0'

#define TRUE        1
#define FALSE       0

struct  list {
    char        *filename;
    struct list *next;
};
struct  directives {
    struct directives   *next;
    char                *directive;
};

extern  FILE    *Fp;                /* file pointer for Temp_Link         */
extern  char    Exe_Name[_MAX_PATH];/* name of executable                 */
extern  char    *Map_Name;          /* name of map file                   */
extern  char    *Obj_Name;          /* object file name pattern           */
extern  char    Libs[MAX_CMD];      /* list of libraires from Cmd         */
extern  const char    *WclMsgs[];
extern  struct  list *Obj_List;     /* linked list of object filenames    */

struct  flags {
    unsigned math_8087    : 1;  /* 0 ==> no 8087, otherwise /7 option */
    unsigned map_wanted   : 1;  /* -fm option specified               */
    unsigned two_case     : 1;  /* two case option                    */
    unsigned tiny_model   : 1;  /* tiny memory model                  */
    unsigned be_quiet     : 1;  /* -zq option to be quiet             */
    unsigned no_link      : 1;  /* -c compile only, no link step      */
    unsigned do_link      : 1;  /* flag for link if no .obj in Cmd    */
    unsigned do_disas     : 1;  /* flag to call wdis                  */
    unsigned do_cvpack    : 1;  /* flag for link do codeview cvpack   */
    unsigned link_for_dos : 1;  /* -lr produce DOS executable         */
    unsigned link_for_os2 : 1;  /* -lp produce OS/2 executable        */
    unsigned windows      : 1;  /* -zw specified for Windows          */
    unsigned link_for_sys : 1;  /* -l<system> option given            */
    unsigned is32bit      : 1;  /* 32bit link                         */
    unsigned force_c      : 1;  /* -cc option                         */
    unsigned force_c_plus : 1;  /* -cc++ option                       */
    unsigned strip_all    : 1;  /* -s option for owcc                 */
    unsigned want_errfile : 1;  /* -fr option in owcc                 */
    unsigned keep_exename : 1;  /* verbatim -o name from owcc         */
};

extern  struct flags Flags;

extern  char *DebugOptions[];

void    PrintMsg( const char *fmt, ... );
void    FindPath( char *name, char *buf );
void    BuildLinkFile( void );
void    AddName( char *, FILE * );
void    Fputnl( char *, FILE * );
void    *MemAlloc( int );
char    *MakePath( char * );
char    *GetName( char * );
char    *FindNextWSOrOpt( char *str, char opt, char *Switch_Chars );

enum {
#undef E
#define E(msg)  msg
#define pick(code,msg)  code
#include "wclmsg.h"
};
