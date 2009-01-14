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
* Description:  main() for the OS/2 help compiler
*
****************************************************************************/

#include <cstdlib>
#include <cstring>
#include <iostream>
#include "banner.h"
#include "compiler.hpp"
#include "env.hpp"
#include "errors.hpp"

static void processCommandLine(int argc, char **argv, Compiler& c);
static void usage();

Env Environment;

int main(int argc, char **argv)
{
    int retval( EXIT_FAILURE );
    std::cout << "Open Watcom OS/2 Help Compiler Version " << BAN_VER_STR << std::endl;
    std::cout << "Copyright (c) " << CURR_YEAR << " Open Watcom Contributors. All Rights Reserved." << std::endl;
    std::cout << "Source code is available under the Sybase Open Watcom Public License." << std::endl;
    std::cout << "See http://www.openwatcom.org/ for details." << std::endl;
    Environment.add( "IPFC" );
    if( Environment.value( "IPFC" ).empty() ) {
        std::cout << "The 'IPFC' environment variable needs to be set. ";
        std::cout << "It should contain the name of the directory containing .nls and entity.txt" << std::endl;
        return retval;
    }
    Environment.add( "IPFCARTWORK" );
    Environment.add( "IPFCIMBED" );
    Environment.add( "TMP" );
    Compiler c;
    try {
        processCommandLine(argc, argv, c);
        retval = c.compile();
    }
    catch( FatalError& e ) {
        c.printError( e.code );
    }
    return retval;
}
/*****************************************************************************/
/*
ipfc 1.0 flags are:
    /INF -- generate an *.inf file
    /S ---- suppress search table generation
    /X ---- generate cross-reference list
    /Wn --- warning level n
    /COUNTRY=nnn
    /CODEPAGE=nnn
    /LANGUAGE=XYZse
ipfc 2.0 flags are:
    -i ------- generate an *.inf file
    -s ------- suppress search table generation
    -x ------- generate cross-reference list
    -W:n ----- set warning level
    -d:nnn --- set 3 digit country code
    -c:nnnn -- set 4 digit code page
    -l:xyz  -- set 3 letter language identifier
    -X:? ----- help on option '?'

We support the version 2 flags
*/
static void processCommandLine(int argc, char **argv, Compiler& c)
{
    if (argc < 2)
        usage();
    char fullpath[ _MAX_PATH ];
    char drive[ _MAX_DRIVE ];
    char dir[ _MAX_DIR ];
    char fname[ _MAX_FNAME ];
    char ext[ _MAX_EXT ];
    bool isInFile( true );
    bool setOut( true );
    bool info( false );
    for( int count = 1; count < argc; ++count ) {
        if( argv[count][0] == '-' || argv[count][0] == '/' ) {
            switch( argv[count][1] ) {
                case 'C':
                case 'c':
                case 'd':
                    std::cout << "Country code and code page selection are not supported." << std::endl;
                    std::cout << "Use the 'l' option to select a localization file instead." << std::endl;
                    if (argv[count][3] == '?')
                        info = true;
                    break;
                case 'I':
                case 'i':
                    c.setOutputType( Compiler::INF );
                    break;
                case 'L':
                case 'l':
                    if (argv[count][3] == '?') {
                        std::cout << "xx_YY is the root name of a localization file" << std::endl;
                        std::cout << "with the full name xx_YY.nls\nSee en_US.nls for an example." << std::endl;
                        info = true;
                    }
                    else
                        c.setLocalization( argv[count] + 3 );
                    break;
                case 'S':
                case 's':
                    c.noSearch();
                    break;
                case 'w':
                case 'W':
                    if (argv[count][3] == '?') {
                        std::cout << "-wN where N is one of 1, 2, or 3" << std::endl;
                        info = true;
                    }
                    else
                        c.setWarningLevel( std::atoi( argv[count] + 3 ));
                    break;
                case 'X':
                case 'x':
                    //This doesn't actually do anything
                    c.setXRef( true );
                    break;
                default:
                    usage();
                    break;
            }
        }
        else {
            _fullpath( fullpath, argv[count], _MAX_PATH );
            c.setBasePath( fullpath );
            if( isInFile ) {
                c.setInputFile( fullpath );
                _splitpath(fullpath, drive, dir, fname, ext);
                isInFile = false;
            }
            else {
                setOut = false;
                c.setOutputFile( fullpath );
            }
        }
    }
    if( setOut ) {
        if( c.outputType() == Compiler::INF )
            std::strncpy( ext, "inf", _MAX_EXT );
        else
            std::strncpy( ext, "hlp", _MAX_EXT );
        _makepath(fullpath, drive, dir, fname, ext);
        c.setOutputFile( fullpath );
    }
    if( info )
        std::exit( EXIT_SUCCESS );
}
/*****************************************************************************/
static void usage()
{
    std::cout << "Usage:" << std::endl;
    std::cout << "wipfc [-switches] [-options] infile [outfile]" << std::endl;
    std::cout << std::endl;
    std::cout << "Switches" << std::endl;
    std::cout << "-i  generate outfile.inf instead of outfile.hlp" << std::endl;
    std::cout << "-s  do not generate full text search tables" << std::endl;
    std::cout << "-x  generate and display cross-reference list" << std::endl;
    std::cout <<  std::endl;
    std::cout << "Options\n" << std::endl;
    std::cout << "-l:xx_YY localization code (default: en_US)" << std::endl;
    std::cout << "-w:n     1 digit warning level  (default: 3)" << std::endl;
    std::cout << "-X:?     display help on option X" << std::endl;
    std::exit( EXIT_FAILURE );
}

