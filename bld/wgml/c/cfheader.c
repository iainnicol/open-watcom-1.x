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
* Description:  Implements function parse_header(), which verifies the
*               correctness of a .COP file header.
*
****************************************************************************/

#include <stdio.h>
#include <string.h>
#include "common.h"

/*
 *  Determine if the current position of the input stream points to the
 *  start of a valid .COP file and, if it does, advance the stream to the
 *  first byte following the header.
 *
 *  Parameters:
 *      in_file points the input stream
 *      type points to a char intended to hold the file type byte
 *
 *  Modified
 *      type is set to the file type byte if SUCCESS is returned
 *      type is either the same as on entry or is set to EOF if FAILURE
 *          is returned (depending on where the return occurs)
 *
 *  Returns:
 *      FAILURE if in_file does not point to the start of a valid .COP
 *          file header
 *      FAILURE on any file error or on EOF, since a valid .COP file has
 *          data after the header
 *      SUCCESS otherwise
 */

int parse_header( FILE * in_file, char * type )
{
    char magic[4];

    /* Get the "magic number" and the version length byte */

    fread( &magic, 4, 1, in_file );
    if( ferror( in_file ) || feof( in_file ) ) return( FAILURE );

    /* If neither a version 3 or a version 4 header, it is not a COP file */
    /* Check for a version 3 header */

    if( memcmp( magic, "\x02\x0a\x00", 3 ) ) {

        /* Check for a version 4 header */
        
        if( memcmp( magic, "\x02\x0c\x00", 3 ) ) return( FAILURE );
    }

    /* Skip the version text */
    
    fseek( in_file, magic[3], SEEK_CUR );
    if( ferror( in_file ) || feof( in_file ) ) return( FAILURE );

    /* Get the file type byte */

    *type = fgetc( in_file );

    /* If there is no more data, this is not a valid .COP file */
    
    if( ferror( in_file ) || feof( in_file ) ) return( FAILURE );

    /* Valid header, more data exists, return the file type byte */
    
    return( SUCCESS );
}
