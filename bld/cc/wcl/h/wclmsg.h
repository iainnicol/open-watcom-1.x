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
* Description:  wcl error names and texts
*
****************************************************************************/

// " is a good file delimiter in non-UNIX systems. ' works better in UNIX
#ifndef __UNIX__
#define DELIM "\""
#else
#define DELIM "\'"
#endif
#define FILEREF DELIM "%s" DELIM

// No \n on messages followed by exit() or on "pause" message
pick( UNABLE_TO_OPEN_DIRECTIVE_FILE,  "Error: Unable to open directive file " FILEREF ),
pick( UNABLE_TO_OPEN_TEMPORARY_FILE,  "Error: Unable to open temporary file " FILEREF " - %s" ),
pick( UNABLE_TO_INVOKE_EXE,           "Error: Unable to invoke " FILEREF ),
pick( COMPILER_RETURNED_A_BAD_STATUS, "Error: Compiler returned a bad status compiling " FILEREF "\n" ),
pick( LINKER_RETURNED_A_BAD_STATUS,   "Error: Linker returned a bad status" ),
pick( CVPACK_RETURNED_A_BAD_STATUS,   "Error: cvpack returned a bad status" ),
pick( UNABLE_TO_OPEN,                 "Unable to open " FILEREF ),
pick( UNABLE_TO_FIND,                 "Error: Unable to find " FILEREF ),
pick( OUT_OF_MEMORY,                  "Out of memory" ),
pick( PRESS_ANY_KEY_TO_CONTINUE,      "Press any key to continue:" ),

#undef FILEREF
#undef DELIM
