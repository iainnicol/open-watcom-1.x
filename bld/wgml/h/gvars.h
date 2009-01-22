/****************************************************************************
*
*                            Open Watcom Project
*
*  Copyright (c) 2004-2008 The Open Watcom Contributors. All Rights Reserved.
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
* Description:  wgml global variables.
*
****************************************************************************/


#ifndef GVARS_H_INCLUDED
#define GVARS_H_INCLUDED

#ifndef global
    #define global  extern
#endif

global  jmp_buf     *   environment;    // var for GSuicide()

global  char        *   scan_char_ptr;  // used by character scanning routines
global  bool            scan_err;       // used by character scanning routines
global  int             curr_char;

global  int             switch_char;    // DOS switch character
global  char        *   alt_ext;        // alternate extension
global  char        *   def_ext;        // default extension

global  char        *   master_fname;   // Primary input file name
global  char        *   master_fname_attr;// Primary input file name attributes
global  ulong           print_from;     // first page to print
global  ulong           print_to;       // last page to print

global  inputcb     *   input_cbs;      // GML input stack (files + macros)
global  char        *   out_file;       // output file name
global  char        *   out_file_attr;  // output file attributes (T:2222)
global  unsigned        inc_level;   // include nesting level 1 = MasterFname
global  unsigned        max_inc_level;  // maximum include level depth
global  ulong           line_from;      // starting lineno to process
global  ulong           line_to;        // ending lineno to process
#define LINEFROM_DEFAULT    1
#define LINETO_DEFAULT      (0x1000000) // 16 MiB lines should be enough

global  int             err_count;      // Overall Errorcount
global  int             wng_count;      // Overall warning count

global  char            GML_char;       // GML Keywword start char :
global  char            SCR_char;       // SCRIPT keywword start char .
global  char            CW_sep_char;    // Control Word separator char ;

global  int             CPI;            // chars per inch
global  space_units     CPI_units;      // unit for chars per inch
global  int             LPI;            // lines per inch
global  space_units     LPI_units;      // unit for lines per inch

global  su              bind_odd;       // Bind value for odd pages

global  su              bind_even;      // Bind value for even pages

global  int             passes;         // Max no of passes
global  int             pass;           // current pass no

global  char        *   scan_start;
global  char        *   scan_stop;


global  symvar      *   global_dict;    // global symbol dictionary
global  mac_entry   *   macro_dict;     // macro dictionary


global  struct GlobalFlags {
    unsigned        quiet         : 1;  // show Productinfo?
    unsigned        bannerprinted : 1;  // Productinfo shown
    unsigned        wscript       : 1;  // enable WATCOM script extension
    unsigned        firstpass     : 1;  // first or only pass
    unsigned        lastpass      : 1;  // last pass
    unsigned        inclist       : 1;  // show included files
    unsigned        warning       : 1;  // show warnings
    unsigned        statistics    : 1;  // output statistics at end

    unsigned        free8         : 1;
    unsigned        free9         : 1;
    unsigned        freea         : 1;
    unsigned        freeb         : 1;
    unsigned        freec         : 1;
    unsigned        freed         : 1;
    unsigned        freee         : 1;
    unsigned        research      : 1;  // research mode, minimal formatting
                                        // research mode will eventually go away
} GlobalFlags;                          // Global flags

global struct ProcFlags {
    unsigned        newLevelFile    : 1;// start new include Level (file)
    unsigned        macro_ignore    : 1;// .. in col 1-2
    unsigned        CW_sep_ignore   : 1;// .' in col 1-2
    unsigned        in_macro_define : 1;// macro definition active
    unsigned        suppress_msg    : 1;// suppress error msg (during scanning)
    unsigned        blanks_allowed  : 1;// blanks allowed (during scanning)
    unsigned        free6           : 1;
    unsigned        free7           : 1;

    unsigned        free8           : 1;
    unsigned        free9           : 1;
    unsigned        freea           : 1;
    unsigned        freeb           : 1;
    unsigned        freec           : 1;
    unsigned        freed           : 1;
    unsigned        freee           : 1;
    unsigned        freef           : 1;

} ProcFlags;                            // processing flags


global  size_t          buf_size;       // default buffer size
global  char        *   token_buf;

global char         *   buffout;        // output buffer

global char         *   buff2;          // input buffer
global size_t           buff2_lg;       // input buffer used length
global char         *   arg_start;      // start of arg scan
global char         *   arg_stop;       // end of arg scan area
global size_t           arg_flen;       // arg length
global char         *   err_start;      // in case of error
global char         *   open_paren;     // ( in input
global char         *   clos_paren;     // ) in input

global char             srnm[ SYM_NAME_LENGTH + 1 ];// symbol name for getsym()
global sub_index        srnmsub;        // subscript

/* Reset so can be reused with other headers. */

#undef global

/* ----                 will eventually be deleted
SRNM     DC    CL10' '             WORKING REFERENCE NAME               15760000
SRNMSUB  DC    AL2(*-*,0)          SUBSCRIPT VALUE AND DEFAULT          15780000
SRNMFR   DC    AL2(*-*,1)          FROM SUBLIST VALUE AND DEFAULT       15800000
SRNMTO   DC    AL2(*-*,255)        TO SUBLIST VALUE AND DEFAULT         15820000
SRNMFLG  DC    X'00'               REFERENCE NAME FLAG BYTE             15840000
SRNMALL  EQU   X'80'                    ALL SUBSCRIPT FLAG              15860000
SRNMALLP EQU   X'40'                    ALL BUT POSITIVE                15880000
SRNMALLN EQU   X'20'                    ALL BUT NEGATIVE                15900000
*        EQU   X'10'                    UNUSED                          15920000
SRNMTSYM EQU   X'08'                    ERROR IN REFERENCE SYMBOL       15940000
SRNMTSUB EQU   X'04'                    ERROR IN REFERENCE SUBSCRIPT    15960000
SRNMTFR  EQU   X'02'                    ERROR IN REF SUBLIST FROM       15980000
SRNMTTO  EQU   X'01'                    ERROR IN REF SUBLIST TO         16000000
-------------------------------------------------------- */





#endif  /* GVARS_H_INCLUDED */

