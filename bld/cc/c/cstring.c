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
* Description:  Source code string literal processing.
*
****************************************************************************/


#include "cvars.h"
#include "cgswitch.h"
#include "scan.h"
#include "asciiout.h"
#include "unicode.h"                                    /* 05-jun-91 */
#include <unistd.h>
#include <fcntl.h>

#ifndef _MAX_PATH
#define _MAX_PATH (PATH_MAX+1)
#endif
#ifndef O_BINARY
#define O_BINARY 0
#endif

extern TREEPTR         CurFuncNode;

static int OpenUnicodeFile( char *filename )
{
    int         handle;
    char        fullpath[ _MAX_PATH ];

#if defined(__UNIX__)
#if defined(__WATCOMC__)
    _searchenv( filename, "ETC_PATH", fullpath );
#else
    fullpath[0] = '\0';
#endif
    if( fullpath[0] == '\0' ) {
        #define ETC "/etc/"
        strcpy( fullpath, ETC );
        strcpy( &fullpath[ sizeof( ETC ) - 1 ], filename );
    }
#else
    _searchenv( filename, "PATH", fullpath );
#endif
    handle = -1;
    if( fullpath[0] != '\0' ) {
        handle = open( fullpath, O_RDONLY | O_BINARY );
    }
    return( handle );
}

static void ReadUnicodeFile( int handle )
{
    int         i;
    unsigned short unicode_table[256];

    read( handle, unicode_table, 256 * sizeof(unsigned short) );
    /* UniCode might be a FAR table */
    for( i = 0; i <= 255; i++ ) {
        UniCode[ i ] = unicode_table[i];
    }
}

void LoadUnicodeTable( long codePage )
{
    int         handle;
    char        filename[8+1+3+1];

    sprintf( filename, "unicode.%3.3ld", codePage );
    handle = OpenUnicodeFile( filename );
    if( handle != -1 ) {
        ReadUnicodeFile( handle );
        close( handle );
    } else {
        CBanner();
        CErr2p( ERR_CANT_OPEN_FILE, filename );
    }
    return;
}

void StringInit()
{
    int i;

    for( i = 0; i < STRING_HASH_SIZE; ++i ) {
        StringHash[i] = 0;
    }
}


STRING_LITERAL *GetLiteral()
{
    unsigned            len, len2;
    STRING_LITERAL      *str_lit;
    STRING_LITERAL      *p;
    int                 is_wide;

    len = RemoveEscapes( NULL );
    str_lit = (STRING_LITERAL *)CMemAlloc( sizeof( STRING_LITERAL ) + len );
    RemoveEscapes( str_lit->literal );
    is_wide = CompFlags.wide_char_string;
    NextToken();
    while( CurToken == T_STRING ) {
        /* if one component is wide then the whole string is wide */
        if (is_wide)
	    CompFlags.wide_char_string = 1;
        len2 = RemoveEscapes( NULL );
        --len;
        if( CompFlags.wide_char_string ) {
            if( len != 0 ) --len;
            is_wide = 1;
        }
        p = (STRING_LITERAL *)CMemAlloc( sizeof( STRING_LITERAL )
                                     + len + len2 );
        memcpy( p->literal, str_lit->literal, len );
        RemoveEscapes( &p->literal[len] );
        len += len2;
        CMemFree( str_lit );
        str_lit = p;
        NextToken();
    }
    CompFlags.wide_char_string = is_wide;
    CLitLength = len;
    str_lit->length = len;
    str_lit->flags = 0;
    str_lit->cg_back_handle = 0;
    str_lit->ref_count = 0;
    return( str_lit );
}

int RemoveEscapes( char *buf )
{
    unsigned int        c;
    int                 j;
    unsigned int        saved_length;
    char                error;

    j = 0;
    saved_length = CLitLength;
    CLitLength = 0;
    error = 0;
    while( CLitLength < saved_length ) {
        c = Buffer[CLitLength];
        if( c == '\\' ) {
            ++CLitLength;
            c = ESCChar( Buffer[CLitLength], RTN_NEXT_BUF_CHAR, &error );
            if( CompFlags.wide_char_string ) {
                if( buf ) buf[j] = c;
                ++j;
                c = c >> 8;                     /* 31-may-91 */
            }
        } else {
            ++CLitLength;
            if( CharSet[c] & C_DB ) {       /* if double-byte character */
                if( CompFlags.jis_to_unicode &&
                    CompFlags.wide_char_string ) {      /* 15-jun-93 */
                    c = (c << 8) + Buffer[CLitLength];
                    c = JIS2Unicode( c );
                    if( buf ) buf[j] = c;
                    c = c >> 8;
                } else {
                    if( buf ) buf[j] = c;
                    c = Buffer[CLitLength];
                }
                ++j;
                ++CLitLength;
            } else if( CompFlags.wide_char_string ) {
                if( CompFlags.use_unicode ) {   /* 05-jun-91 */
                    c = UniCode[ c ];
                } else if( CompFlags.jis_to_unicode ) {
                    c = JIS2Unicode( c );
                }
                if( buf ) buf[j] = c;
                ++j;
                c = c >> 8;
            } else {
                _ASCIIOUT( c );
            }
        }
        if( buf )  buf[j] = c;
        ++j;
    }
    if( error != 0 && buf != NULL ) {                   /* 16-nov-94 */
        if( NestLevel == SkipLevel ) {
            CErr1( ERR_INVALID_HEX_CONSTANT );
        }
    }
    return( j );
}

static TYPEPTR StringLeafType()
{
    TYPEPTR     typ;

    if( CompFlags.wide_char_string ) {          /* 01-aug-91 */
        typ = ArrayNode( GetType( TYPE_USHORT ) );
        typ->u.array->dimension = CLitLength >> 1;
    } else if( StringArrayType != NULL ) {
        typ = StringArrayType;
        StringArrayType->u.array->dimension = CLitLength;
        StringArrayType = NULL;
    } else {
        typ = ArrayNode( GetType( TYPE_PLAIN_CHAR ) );  /* 25-nov-94 */
        typ->u.array->dimension = CLitLength;
    }
    return( typ );
}


static unsigned CalcStringHash( STRING_LITERAL *lit )
{
    return( hashpjw( lit->literal ) % STRING_HASH_SIZE );
}

TREEPTR StringLeaf( int flags )
{
    STRING_LITERAL      *new_lit;
    STRING_LITERAL      *strlit;
    TREEPTR             leaf_index;
    unsigned            hash;

    strlit = 0;
    new_lit = GetLiteral();
    if( TargetSwitches & BIG_DATA ) {          /* 06-oct-88 */
        if( ! CompFlags.strings_in_code_segment ) {         /* 01-sep-89 */
            if( new_lit->length > DataThreshold ) {
                flags |= FLAG_FAR;
            }
        }
    }
    if( CompFlags.wide_char_string )
        flags |= STRLIT_WIDE;
    if( flags & FLAG_FAR )
        CompFlags.far_strings = 1;
    hash = CalcStringHash( new_lit );
    if( Toggles & TOGGLE_REUSE_DUPLICATE_STRINGS ) {    /* 24-mar-92 */
        strlit = StringHash[ hash ];
        while( strlit != 0 ) {
            if( strlit->length == new_lit->length  &&
                strlit->flags == flags ) {
                if( memcmp(strlit->literal, new_lit->literal,
                                 new_lit->length) == 0 )
                    break;
            }
            strlit = strlit->next_string;
        }
    }
    if( strlit == 0 ) {
        new_lit->flags = flags;
        ++LitCount;
        LitPoolSize += CLitLength;
        new_lit->next_string = StringHash[ hash ];
        StringHash[ hash ] = new_lit;
    } else {            // we found a duplicate
        CMemFree( new_lit );
        new_lit = strlit;
    }

    leaf_index = LeafNode( OPR_PUSHSTRING );
    leaf_index->op.string_handle = new_lit;
    // set op.flags field
    leaf_index->expr_type = StringLeafType();

    if( CurFunc != NULL ) {                             /* 22-feb-92 */
        CurFuncNode->op.func.flags &= ~FUNC_OK_TO_INLINE;
    }

    return( leaf_index );
}
