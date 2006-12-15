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
* Description:  IBM HLL and pre-CV4 CodeView debug format dump routines.
*
****************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <setjmp.h>

#include "wdglb.h"
#include "dumpwv.h"
#include "wdfunc.h"
#include "hll.h"


static  char    *hll_debug_dirinfo_msg[] = {
    "2cbDirHeader - length of directory header      = ",
    "2cbDirEntry  - lentgh of each entry            = ",
    "4cDir        - number of directory entries     = ",
    NULL
};

static  char    *hll_debug_dir_msg[] = {
    "2subsection  - subsection index                = ",
    "2iMod        - module index (1 based)          = ",
    "4lfo         - offset from base                = ",
    "4cb          - subsection size                 = ",
    NULL
};

static  char    *hll_sstModules_msg[] = {
    "2  Seg          - segment index                = ",
    "4  Off          - code start within segment    = ",
    "4  cbSeg        - size of code in segment      = ",
    "2  ovlNbr       - overlay number               = ",
    "2  iLib         - index into sstLibraries      = ",
    "2  cSeg         - number of segments in module = ",
    "2  Style        - debug info style             = ",
    "2  Version      - debug info version number    = ",
    NULL
};

static  char    *hll_seg_msg[] = {
    "2    Seg      - segment index                  = ",
    "4    Off      - code start within segment      = ",
    "4    cbSeg    - size of code in segment        = ",
    NULL
};

static  char    *cv_sstPublics_msg[] = {
    "2  offset       - symbol offset within segment = ",
    "2  seg          - segment index                = ",
    "2  type         - type index (0 if no data)    = ",
    NULL
};

static  char    *hll_sstPublics_msg[] = {
    "4  offset       - symbol offset within segment = ",
    "2  seg          - segment index                = ",
    "2  type         - type index (0 if no data)    = ",
    NULL
};

static  char    *cv_sstSrcLnSeg_msg[] = {
    "2  seg          - segment index                = ",
    "2  cPair        - number of line/offset pairs  = ",
    NULL
};

static  char    *cv_lnoff16_msg[] = {
    "2  line         - source line number           = ",
    "2  offset       - offset within segment        = ",
    NULL
};

static  char    *cv_dir_entry_msg[] = {
    "2SubSectionType  - subsection type             = ",
    "2ModuleIndex     - module index (1 based)      = ",
    "4lfoStart        - offset from base            = ",
    "2Size            - subsection size             = ",
    NULL
};

static  char    *cv_sstModules_msg[] = {
    "2  Seg          - segment index                = ",
    "2  Off          - code start within segment    = ",
    "2  cbSeg        - size of code in segment      = ",
    "2  ovlNbr       - overlay number               = ",
    "2  iLib         - index into sstLibraries      = ",
    "1  cSeg         - number of segments in module = ",
    "1  reserved     - padding                      = ",
    NULL
};

static  char    *cv_seg_msg[] = {
    "2    Seg      - segment index                  = ",
    "2    Off      - code start within segment      = ",
    "2    cbSeg    - size of code in segment        = ",
    NULL
};

static  char    *hl4_linnum_first_msg[] = {
    "2  lineNum    - line number (must be zero)     = ",
    "1  entryType  - format of entry                = ",
    "1  reserved   - padding                        = ",
    "2  numEntries - number of following entries    = ",
    "2  segNum     - segment number for table       = ",
    "4  offset     - offset/num entries (type 0x03) = ",
    NULL
};

static  char    *hl4_filetab_entry_msg[] = {
    "4  firstChar  - first displayable listing char = ",
    "4  numChars   - displayable chars per line     = ",
    "4  numFiles   - number of files in table       = ",
    NULL
};

static  char    *hl3_linnum_first_msg[] = {
    "2  lineNum    - line number (must be zero)     = ",
    "1  entryType  - format of entry                = ",
    "1  reserved   - padding                        = ",
    "2  numEntries - number of following entries    = ",
    "2  segNum     - segment number for table       = ",
    "4  tableSize  - file names table size          = ",
    NULL
};

static  char    *hl3_filetab_entry_msg[] = {
    "4  srcStart   - start of source                = ",
    "4  numRecords - number of source records       = ",
    "4  numFiles   - number of files in table       = ",
    NULL
};

static  char    *hll_linnum_entry_msg[] = {
    "2    lineNum  - line number                    = ",
    "2    sfi      - source file index              = ",
    "4    offset   - offset within segment          = ",
    NULL
};


static  int     hll_level;

/*
 * read_name - read length-prefixed name into 'buffer'
 */
static int read_name( char *buffer )
/**********************************/
{
    unsigned_8      len;

    Wread( &len, 1 );
    Wread( buffer, len );
    buffer[len] = '\0';
    return( len );
}


/*
 * dump_name - dump length-prefixed name, align to n-byte boundary
 * return number of bytes read
 */
static int dump_name( bool align )
/********************************/
{
    char        name[256];
    unsigned    len, pad = 0;

    len = read_name( name ) + 1;
    Wdputs( name );
    if( align ) {
        pad = align - (len & (align - 1));
    }
    if( pad ) {
        lseek( Handle, pad, SEEK_CUR );
    }
    return( len + pad + 1 );
}


/*
 * dump_cv_sstPublics - dump CV sstPublic at 'offset'
 * from 'base 'containing 'size' bytes
 */
static void dump_cv_sstPublics( unsigned_32 base, unsigned_32 offset,
                                                 unsigned_32 size )
/*******************************************************************/
{
    hll_public_16       pub16;
    unsigned_32         read = 0;
    unsigned_8          name_len;
    char                name[256];

    Wlseek( base + offset );
    Wdputs( "==== sstPublics at offset " );
    Puthex( offset, 8 );
    Wdputslc( "\n" );
    while( read < size ) {
        Wread( &pub16, sizeof( pub16 ) );
        name_len = pub16.name[0];
        Dump_header( &pub16, cv_sstPublics_msg );
        read += sizeof( pub16 );
        Wread( name, name_len );
        name[name_len] = '\0';
        Wdputs( "  symbol name: \"" );
        Wdputs( name );
        read += name_len;
        Wdputslc( "\"\n" );
    }
    Wdputslc( "\n" );
}


/*
 * dump_hll_sstPublics - dump HLL sstPublics at 'offset'
 * from 'base 'containing 'size' bytes
 */
static void dump_hll_sstPublics( unsigned_32 base, unsigned_32 offset,
                                                 unsigned_32 size )
/********************************************************************/
{
    hll_public_32       pub32;
    unsigned_32         read = 0;
    unsigned_8          name_len;
    char                name[256];

    Wlseek( base + offset );
    Wdputs( "==== sstPublics at offset " );
    Puthex( offset, 8 );
    Wdputslc( "\n" );
    while( read < size ) {
        Wread( &pub32, sizeof( pub32 ) );
        name_len = pub32.name[0];
        Dump_header( &pub32, hll_sstPublics_msg );
        read += sizeof( pub32 );
        Wread( name, name_len );
        name[name_len] = '\0';
        Wdputs( "  symbol name: \"" );
        Wdputs( name );
        read += name_len;
        Wdputslc( "\"\n" );
    }
    Wdputslc( "\n" );
}


/*
 * dump_cv_sstLibraries - dump CV sstLibraries at 'offset'
 * from 'base' containing 'size' bytes
 */
static void dump_cv_sstLibraries( unsigned_32 base, unsigned_32 offset,
                                                    unsigned_32 size )
/*********************************************************************/
{
    unsigned        index = 0;
    unsigned_32     read = 0;

    Wlseek( base + offset );
    Wdputs( "==== sstLibraries at offset " );
    Puthex( offset, 8 );
    Wdputslc( "\n" );
    while( read < size ) {
        Wdputs( "  index: " );
        Puthex( index, 4 );
        Wdputs( "H  name: \"" );
        read += dump_name( 0 );
        Wdputslc( "\"\n" );
        ++index;
    }
    Wdputslc( "\n" );
}


/*
 * dump_cv_sstModules - dump CV sstModules at 'offset' from 'base'
 */
static void dump_cv_sstModules( unsigned_32 base, unsigned_32 offset )
/********************************************************************/
{
    cv3_sst_module      mod;
    cv3_seginfo         seg;
    bool                first = TRUE;

    Wlseek( base + offset );
    Wdputs( "==== sstModules at offset " );
    Puthex( offset, 8 );
    Wdputslc( "\n" );
    Wread( &mod, sizeof( mod ) );
    Dump_header( &mod, cv_sstModules_msg );
    Wdputs( "  module name: \"" );
    dump_name( 0 );
    Wdputslc( "\"\n" );
    if( mod.cSeg ) {
        while( --mod.cSeg ) {
            if( !first ) {
                Wdputslc( "    ====\n" );
            }
            Wread( &seg, sizeof( seg ) );
            Dump_header( &seg, cv_seg_msg );
            first = FALSE;
        }
    }
    Wdputslc( "\n" );
}


/*
 * dump_hll_sstModules - dump HLL sstModules at 'offset' from 'base'
 */
static void dump_hll_sstModules( unsigned_32 base, unsigned_32 offset )
/*********************************************************************/
{
    hll_debug_mod_32    mod;
    hll_debug_seg_32    seg;
    bool                first = TRUE;

    Wlseek( base + offset );
    Wdputs( "==== sstModules at offset " );
    Puthex( offset, 8 );
    Wdputslc( "\n" );
    Wread( &mod, sizeof( mod ) );
    Dump_header( &mod, hll_sstModules_msg );
    hll_level = mod.Version >> 8;
    Wdputs( "  module name: \"" );
    dump_name( 0 );
    Wdputslc( "\"\n" );
    if( mod.cSeg ) {
        while( --mod.cSeg ) {
            if( !first ) {
                Wdputslc( "    ====\n" );
            }
            Wread( &seg, sizeof( seg ) );
            Dump_header( &seg, hll_seg_msg );
            first = FALSE;
        }
    }
    Wdputslc( "\n" );
}


/*
 * dump_cv_sstSrcLnSeg - dump sstSrcLnSeg at 'offset' from 'base'
 */
static void dump_cv_sstSrcLnSeg( unsigned_32 base, unsigned_32 offset )
/*********************************************************************/
{
    cv_linnum_seg       src_ln;
    cv_srcln_off_16     lo_16;

    Wlseek( base + offset );
    Wdputs( "==== sstSrcLnSeg at offset " );
    Puthex( offset, 8 );
    Wdputslc( "\n" );
    Wdputs( "  source file: \"" );
    dump_name( 2 );
    Wdputslc( "\"\n" );
    Wread( &src_ln, sizeof( src_ln ) );
    Dump_header( &src_ln, cv_sstSrcLnSeg_msg );
    while( src_ln.cPair-- ) {
        Wread( &lo_16, sizeof( lo_16 ) );
        Dump_header( &lo_16, cv_lnoff16_msg );
    }
    Wdputslc( "\n" );
}


/*
 * dump_hll_sstHLLSrc - dump HLL sstHLLSrc at 'offset' from 'base'
 * containing 'size' bytes
 */
static void dump_hll_sstHLLSrc( unsigned_32 base, unsigned_32 offset,
                                                  unsigned_32 size )
/*******************************************************************/
{
    Wlseek( base + offset );
    Wdputs( "==== sstHLLSrc at offset " );
    Puthex( offset, 8 );
    Wdputslc( "\n" );
    if( hll_level >= 0x04 ) {
        hl4_linnum_first    first_entry;
        unsigned_32         count = 0;

        while( count < size ) {
            Wread( &first_entry, sizeof( first_entry ) );
            Dump_header( &first_entry, hl4_linnum_first_msg );
            count += sizeof( first_entry );
            if( first_entry.entryType == 0x03 ) {
                hl4_filetab_entry   ftab_entry;
                unsigned_32         index;

                Wread( &ftab_entry, sizeof( ftab_entry ) );
                Dump_header( &ftab_entry, hl4_filetab_entry_msg );
                count += sizeof( ftab_entry );

                for( index = 0; index < ftab_entry.numFiles; ++index ) {
                    Wdputs( "  file index: " );
                    Puthex( index, 4 );
                    Wdputs( "H name: \"" );
                    count += dump_name( 0 );
                    Wdputslc( "\"\n" );
                }
                Wdputslc( "\n" );
            } else if( first_entry.entryType == 0x00 ) {
                hll_linnum_entry    lnum_entry;
                unsigned_32         index;

                for( index = 0; index < first_entry.numEntries; ++index ) {
                    Wread( &lnum_entry, sizeof( lnum_entry ) );
                    count += sizeof( lnum_entry );
                    Dump_header( &lnum_entry, hll_linnum_entry_msg );
                }
                Wdputslc( "\n" );
            } else {
                Wdputslc( "unsupported linnum table entry format\n" );
            }
        }
    } else {
        hl3_linnum_first    first_entry;
        unsigned_32         index;

        Wread( &first_entry, sizeof( first_entry ) );
        Dump_header( &first_entry, hl3_linnum_first_msg );
        if( first_entry.entryType == 0x00 ) {
            hl3_filetab_entry   ftab_entry;
            hll_linnum_entry    lnum_entry;

            for( index = 0; index < first_entry.numEntries; ++index ) {
                Wread( &lnum_entry, sizeof( lnum_entry ) );
                Dump_header( &lnum_entry, hll_linnum_entry_msg );
            }

            Wread( &ftab_entry, sizeof( ftab_entry ) );
            Dump_header( &ftab_entry, hl3_filetab_entry_msg );

            for( index = 0; index < ftab_entry.numFiles; ++index ) {
                Wdputs( "  file index: " );
                Puthex( index, 4 );
                Wdputs( "H name: \"" );
                dump_name( 0 );
                Wdputslc( "\"\n" );
            }
            Wdputslc( "\n" );
        } else {
            Wdputslc( "unsupported linnum table entry format\n" );
        }
    }
}


/*
 * dump_cv_subsection - dump any CodeView subsection
 */
static void dump_cv_subsection( unsigned_32 base, cv3_directory_entry *dir )
/**************************************************************************/
{
    hll_sst         sst_index;

    sst_index = dir->subsection;
    switch( sst_index ) {
    case hll_sstModules:
        if( Debug_options & MODULE_INFO ) {
            dump_cv_sstModules( base, dir->lfo );
        }
        break;
    case hll_sstPublics:
        if( Debug_options & GLOBAL_INFO ) {
            dump_cv_sstPublics( base, dir->lfo, dir->cb );
        }
        break;
    case hll_sstLibraries:
        dump_cv_sstLibraries( base, dir->lfo, dir->cb );
        break;
    case hll_sstSrcLnSeg:
        if( Debug_options & LINE_NUMS ) {
            dump_cv_sstSrcLnSeg( base, dir->lfo );
        }
        break;
    }
}


/*
 * dump_hll_subsection - dump any HLL subsection
 */
static void dump_hll_subsection( unsigned_32 base, hll_debug_dir *dir )
/*********************************************************************/
{
    hll_sst         sst_index;

    sst_index = dir->subsection;
    switch( sst_index ) {
    case hll_sstModules:
        if( Debug_options & MODULE_INFO ) {
            dump_hll_sstModules( base, dir->lfo );
        }
        break;
    case hll_sstPublics:
        if( Debug_options & GLOBAL_INFO ) {
            dump_hll_sstPublics( base, dir->lfo, dir->cb );
        }
        break;
    case hll_sstLibraries:
        dump_cv_sstLibraries( base, dir->lfo, dir->cb );
        break;
    case hll_sstHLLSrc:
        if( Debug_options & LINE_NUMS ) {
            dump_hll_sstHLLSrc( base, dir->lfo, dir->cb );
        }
        break;
    }
}


/*
 * dump_cv - dump CV data at offset 'base' from start of file
 */
static void dump_cv( unsigned_32 base )
/*************************************/
{
    hll_trailer                 header;
    cv3_directory_entry         sst_dir_entry;
    unsigned_16                 num_entries;
    int                         i;

    Wlseek( base );
    Wread( &header, sizeof( header ) );
    if( memcmp( header.sig, HLL_NB02, HLL_SIG_SIZE ) != 0 ) {
        return;
    }
    Wlseek( base + header.offset );
    Wread( &num_entries, sizeof( num_entries ) );
    for( i = 0; i < num_entries; ++i ) {
        Wlseek( base + header.offset + 2 + i * sizeof( sst_dir_entry ) );
        Wread( &sst_dir_entry, sizeof( sst_dir_entry ) );
        Dump_header( &sst_dir_entry, cv_dir_entry_msg );
        Wdputslc( "\n" );
        dump_cv_subsection( base, &sst_dir_entry );
    }
}


/*
 * dump_hll - dump HLL data at offset 'base' from start of file
 */
static void dump_hll( unsigned_32 base )
/**************************************/
{
    hll_trailer                 header;
    hll_debug_dirinfo           dir_info;
    hll_debug_dir               dir_entry;
    int                         i;

    Wlseek( base );
    Wread( &header, sizeof( header ) );
    if( memcmp( header.sig, HLL_NB04, HLL_SIG_SIZE ) != 0 ) {
        return;
    }
    Wlseek( base + header.offset );
    Wread( &dir_info, sizeof( dir_info ) );
    Dump_header( &dir_info , hll_debug_dirinfo_msg );
    Wdputslc( "\n" );
    for( i = 0; i < dir_info.cDir; ++i ) {
        Wlseek( base + header.offset + dir_info.cbDirHeader + i * dir_info.cbDirEntry );
        Wread( &dir_entry, sizeof( dir_entry ) );
        Dump_header( &dir_entry, hll_debug_dir_msg );
        Wdputslc( "\n" );
        dump_hll_subsection( base, &dir_entry );
    }
}


/*
 * Dmp_hll_head - dump IBM HLL or MS CodeView debugging information
 */
bool Dmp_hll_head( void )
/**********************/
{
    off_t           end_off;
    off_t           dbg_off;
    hll_trailer     trailer;

    end_off = lseek( Handle, 0, SEEK_END );
    Wlseek( end_off - sizeof( trailer ) );
    Wread( &trailer, sizeof( trailer ) );
    dbg_off = end_off - trailer.offset;
    if( memcmp( trailer.sig, HLL_NB04, HLL_SIG_SIZE ) == 0 ) {
        Banner( "HLL NB04 debugging information" );
        Wdputs( "debugging information base  = " );
        Puthex( dbg_off, 8 );
        Wdputslc( "H\n" );
        Wdputs( "subsection directory offset = " );
        Puthex( trailer.offset, 8 );
        Wdputslc( "H\n\n" );
        dump_hll( dbg_off );
        return( 1 );
    } else if( memcmp( trailer.sig, HLL_NB02, HLL_SIG_SIZE ) == 0 ) {
        Banner( "CodeView NB02 debugging information" );
        Wdputs( "debugging information base  = " );
        Puthex( dbg_off, 8 );
        Wdputslc( "H\n" );
        Wdputs( "subsection directory offset = " );
        Puthex( trailer.offset, 8 );
        Wdputslc( "H\n\n" );
        dump_cv( dbg_off );
        return( 1 );
    }
    return( 0 );
} /* Dmp_hll_head */
