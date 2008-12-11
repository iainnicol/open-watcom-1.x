/****************************************************************************
*
*                            Open Watcom Project
*
*  Copyright (c) 2004-2007 The Open Watcom Contributors. All Rights Reserved.
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

global  jmp_buf         *environment;   // var for GSuicide()

global  char            *scan_char_ptr;// used by character scanning routines
global  int             curr_char;

global  int             switch_char;    // DOS switch character
global  char            *alt_ext;       // alternate extension
global  char            *def_ext;       // default extension


global  char            *master_fname;  // Primary input file name
global  char            *master_fname_attr;// Primary input file name attributes
global  ulong           print_from;     // first page to print
global  ulong           print_to;       // last page to print

global  filecb          *file_cbs;      // GML input files
global  char            *out_file;      // output file name
global  char            *out_file_attr; // output file attributes (T:2222)
global  unsigned        inc_level;   // include nesting level 1 = MasterFname
global  ulong           line_from;      // starting lineno to process
global  ulong           line_to;        // ending lineno to process
#define LINEFROM_DEFAULT    1
#define LINETO_DEFAULT      (0x1000000) // 16 meg lines should be enough

global  size_t          buf_size;
global  char            *buffer;
global  char            *token_buf;
global  char            *try_file_name;
global  FILE            *try_fp;

global  char            *Pathes;        // content of PATH Envvar
global  char            *GMLlibs;       // content of GMMLIB Envvar
global  char            *GMLincs;       // content of GMLINC Envvar

global  int             err_count;      // Overall Errrorcount
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

global  char            *scan_start;
global  char            *scan_stop;





global struct GlobalFlags {
    unsigned            quiet         : 1;  // show Productinfo?
    unsigned            bannerprinted : 1;  // Productinfo shown
    unsigned            wscript       : 1;  // enable WATCOM script extension
    unsigned            firstpass     : 1;  // first or only pass
    unsigned            lastpass      : 1;  // last pass
    unsigned            inclist       : 1;  // show included files

    unsigned            warning       : 1;  // show warnings
    unsigned            free7         : 1;

    unsigned            free8         : 1;
    unsigned            free9         : 1;
    unsigned            freea         : 1;
    unsigned            freeb         : 1;
    unsigned            freec         : 1;
    unsigned            freed         : 1;
    unsigned            freee         : 1;
    unsigned            research      : 1;  // research mode, no formatting
                                            // research mode will eventually go away
} GlobalFlags;

global struct ProcFlags {
    unsigned            macro_ignore  : 1;  // .. in col 1-2
    unsigned            CW_sep_ignore : 1;  // .' in col 1-2
    unsigned            newLevel      : 1;  // start new include Level

    unsigned            GML_tag_cont  : 1;// tag continued from prev line
    unsigned            nocase        : 1;  // case insensitive switch
    unsigned            free6         : 1;
    unsigned            free7         : 1;

} ProcFlags;

global char            *buff2;          // input buffer
global char            *buff2_lg;       // input buffer used length
global char            *arg_start;      // start of Arg
global char            *arg_stop;       // End of Arg
global char            *open_paren;     // ( in input
global char            *clos_paren;     // ) in input






#endif  /* GVARS_H_INCLUDED */

