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
* Description:  A searchable word entry in the Dictionary (vocabulary) data
*
****************************************************************************/

#include <algorithm>
#include <cstdlib>
#include "fts.hpp"
#include "errors.hpp"

#pragma pack(push, 1)
    struct FTS8Header {
        std::uint8_t    size;
        std::uint8_t    compression;
        //variable length data follows
        //bitstring: 1 bit per panel
    };
    struct FTS16Header {
        std::uint16_t   size;
        std::uint8_t    compression;
        //variable length data follows
        //bitstring: 1 bit per panel
    };
#pragma pack(pop)

void FTSElement::setPages( size_t count )
{
    size_t elements( ( count + 7 ) / 8 );
    pages.resize(elements );
    maxPage = count;
}
/***************************************************************************/
void FTSElement::onPage( size_t i )
{
    size_t index( i / 8 );
    std::uint8_t mask( 0x80 >> ( i % 8 ) );
    if( !( pages[ index ] & mask ) ) {
        ++pageCount;
        pages[ index ] |= mask;
    }
}
/***************************************************************************/
void FTSElement::build()
{
    if( pageCount == 0 )
        comp = NONE;
    else if( pageCount == maxPage )
        comp = ALL;
    else {
        size_t score[ 5 ];
        //find the last non-zero byte
        PageIter itr( pages.end() - 1 );
        while( itr != pages.begin() && *itr == 0 )
            --itr;
        pages.erase( itr + 1, pages.end() );    //remove bytes containing 0's from end
        score[ 3 ] = pages.size() * sizeof( std::uint8_t );
        //find first non-zero byte
        PageIter fnz( pages.begin() );
        while( fnz != pages.end() && *fnz == 0 ) {
            ++fnz;
            ++firstPage;
        }
        score[ 4 ] = ( score[3] - firstPage ) * sizeof( std::uint8_t ) + sizeof( std::uint16_t );
        //run length encode the truncated bitstring
        std::vector< std::uint8_t > rle;
        encode( rle );
        score[ 0 ] = ( rle.size() + 1 ) * sizeof( std::uint8_t );
        score[ 1 ] = pageCount * sizeof( std::uint16_t );
        score[ 2 ] = ( maxPage - pageCount ) * sizeof( std::uint16_t );
        size_t index = 0;
        size_t value = score[ 0 ];
        for( size_t count = 1; count < sizeof( score ) / sizeof( size_t ); ++count ) {
            if( score[ count ] < value ) {
                value = score[ count ];
                index = count;
            }
        }
        if( index == 0 ) {
            comp = RLE;
            pages = rle;
        }
        else if( index == 1 )
            comp = PRESENT;
        else if( index == 2 )
            comp = ABSENT;
        else if( index == 3 )
            comp = TRUNC;
        else if( index == 4 ) {
            comp = DBL_TRUNC;
            pages.erase( pages.begin(), fnz );  //truncate front
        }
    }
}
/***************************************************************************/
//The number of pages can never exceed 65535 because the count is stored in
//an std::uint16_t (unsigned short int)
void FTSElement::encode( std::vector< std::uint8_t >& rle )
{
    std::vector< std::uint8_t > dif;
    size_t sameCount( 0 );
    ConstPageIter tst( pages.begin() );
    ConstPageIter itr( pages.begin() + 1 );
    bool same( *itr == *tst );
    while( itr != pages.end() ) {
        if( same ) {
            if( *itr != *tst ) {
                --sameCount;
                if( sameCount < 0x80 ) {
                    rle.push_back( static_cast< std::uint8_t >( sameCount ) | 0x80 );
                    rle.push_back( *tst );
                }
                else {
/*
                    while( sameCount > 65536 ) {
                        rle.push_back( 0x80 );
                        rle.push_back( *tst );
                        rle.push_back( 0xFF );
                        rle.push_back( 0xFF );
                        sameCount -= 65536;
                    }
*/
                    rle.push_back( 0x80 );
                    rle.push_back( *tst );
                    rle.push_back( static_cast< std::uint8_t >( sameCount ) );
                    rle.push_back( static_cast< std::uint8_t >( sameCount >> 8 ) );
                }
                tst = itr;
                sameCount = 0;
                same = false;
            }
            else
                ++sameCount;
        }
        else {
            if( *itr == *tst ) {
                std::vector< std::uint8_t >::const_iterator byte( dif.begin() );
                size_t difSize( dif.size() );
                std::uint8_t code( 0xFF );
                while( difSize > 128 ) {
                    rle.push_back( code );
                    for( size_t count = 0; count <= 128; ++count ) {
                        rle.push_back( *byte );
                        ++byte;
                    }
                    difSize -= 128;
                }
                code = static_cast< std::uint8_t >( difSize - 1 ) | 0x80;
                rle.push_back( code );
                for( size_t count = 0; count < difSize; ++count ) {
                    rle.push_back( *byte );
                    ++byte;
                }
                dif.clear();
                same = true;
            }
            else {
                dif.push_back( *tst );
                tst = itr;
            }
        }
        ++itr;
    }
    if( same ) {
        --sameCount;
        if( sameCount < 0x80 ) {
            rle.push_back( static_cast< std::uint8_t >( sameCount ) | 0x80 );
            rle.push_back( *tst );
        }
        else {
/*
            while( sameCount > 65536 ) {
                rle.push_back( 0x80 );
                rle.push_back( *tst );
                rle.push_back( 0xFF );
                rle.push_back( 0xFF );
                sameCount -= 65536;
            }
*/
            rle.push_back( 0x80 );
            rle.push_back( *tst );
            rle.push_back( static_cast< std::uint8_t >( sameCount ) );
            rle.push_back( static_cast< std::uint8_t >( sameCount >> 8 ) );
        }
    }
    else {
        dif.push_back( *tst );
        std::vector< std::uint8_t >::const_iterator byte( dif.begin() );
        size_t difSize( dif.size() );
        std::uint8_t code( 0xFF );
        while( difSize > 128 ) {
            rle.push_back( code );
            for( size_t count = 0; count <= 128; ++count ) {
                rle.push_back( *byte );
                ++byte;
            }
            difSize -= 128;
        }
        code = static_cast< std::uint8_t >( difSize - 1 ) | 0x80;
        rle.push_back( code );
        for( size_t count = 0; count < difSize; ++count ) {
            rle.push_back( *byte );
            ++byte;
        }
    }
}
/***************************************************************************/
size_t FTSElement::write( std::FILE *out, bool big ) const
{
    size_t written( 0 );
    if( big ) {
        FTS16Header hdr;
        hdr.size = sizeof( FTS16Header );
        hdr.compression = comp;
        if( comp == NONE || comp == ALL ) {
            if( std::fwrite( &hdr, sizeof( FTS16Header ), 1, out ) != 1 )
                throw FatalError( ERR_WRITE );
            written = hdr.size; 
        }
        else if( comp == RLE ) {
            hdr.size += static_cast< std::uint16_t >( pages.size() + 1 );
            if( std::fwrite( &hdr, sizeof( FTS16Header ), 1, out ) != 1 ||
                std::fputc( 0x01, out ) != EOF &&
                std::fwrite( &pages[0], sizeof( std::uint8_t ), pages.size(), out ) != pages.size() )
                throw FatalError( ERR_WRITE );
            written = hdr.size; 
        }
        else if( comp == PRESENT ) {
            std::vector< std::uint16_t > pg;
            pg.reserve( pageCount );
            std::uint16_t index( 0 );
            for( ConstPageIter itr = pages.begin(); itr != pages.end(); ++itr ) {
                for( std::uint8_t mask = 0x80; mask != 0; mask >>= 1, ++index ) {
                    if( *itr & mask )
                        pg.push_back( index );
                }
            }
            hdr.size += static_cast< std::uint16_t >( pg.size() * sizeof( std::uint16_t ) );
            if( std::fwrite( &hdr, sizeof( FTS16Header ), 1, out ) != 1 ||
                std::fwrite( &pg[0], sizeof( std::uint16_t ), pg.size(), out ) != pg.size() )
                throw FatalError( ERR_WRITE );
            written = hdr.size; 
        }
        else if ( comp == ABSENT ) {
            std::vector< std::uint16_t > pg;
            pg.reserve( maxPage - pageCount );
            std::uint16_t index( 0 );
            for( ConstPageIter itr = pages.begin(); itr != pages.end(); ++itr ) {
                for( std::uint8_t mask = 0x80; mask != 0; mask >>= 1, ++index ) {
                    if( !( *itr & mask ) )
                        pg.push_back( index );
                }
            }
            hdr.size += static_cast< std::uint16_t >( pg.size() * sizeof( std::uint16_t ) );
            if( std::fwrite( &hdr, sizeof( FTS16Header ), 1, out ) != 1 ||
                std::fwrite( &pg[0], sizeof( std::uint16_t ), pg.size(), out ) != pg.size() )
                throw FatalError( ERR_WRITE );
            written = hdr.size; 
        }
        else if ( comp ==  TRUNC ) {
            hdr.size += static_cast< std::uint16_t >( pages.size() * sizeof( std::uint8_t ) );
            if( std::fwrite( &hdr, sizeof( FTS16Header ), 1, out ) != 1 ||
                std::fwrite( &pages[0], sizeof( std::uint8_t ), pages.size(), out ) != pages.size() )
                throw FatalError( ERR_WRITE );
            written = hdr.size; 
        }
        else if ( comp == DBL_TRUNC ) {
            hdr.size += static_cast< std::uint16_t >( pages.size() * sizeof( std::uint8_t ) +
                        sizeof( std::uint16_t ));
            if( std::fwrite( &hdr, sizeof( FTS16Header ), 1, out ) != 1 ||
                std::fwrite( &firstPage, sizeof( std::uint16_t ), 1, out ) != 1 ||
                std::fwrite( &pages[0], sizeof( std::uint8_t ), pages.size(), out ) != pages.size() )
                throw FatalError( ERR_WRITE );
            written = hdr.size; 
        } 
    }
    else {
        FTS8Header hdr;
        hdr.size = sizeof( FTS8Header );
        hdr.compression = comp;
        if( comp == NONE || comp == ALL ) {
            if( std::fwrite( &hdr, sizeof( FTS8Header ), 1, out ) != 1 )
                throw FatalError( ERR_WRITE );
            written = hdr.size; 
        }
        else if( comp == RLE ) {
            hdr.size += static_cast< std::uint8_t >( ( pages.size() + 1 ) * sizeof( std::uint8_t ) );
            if( std::fwrite( &hdr, sizeof( FTS8Header ), 1, out ) != 1 ||
                std::fputc( 0x01, out ) != EOF &&
                std::fwrite( &pages[0], sizeof( std::uint8_t ), pages.size(), out ) != pages.size() )
                throw FatalError( ERR_WRITE );
            written = hdr.size; 
        }
        else if( comp == PRESENT ) {
            std::vector< std::uint16_t > pg;
            pg.reserve( pageCount );
            std::uint16_t index( 0 );
            for( ConstPageIter itr = pages.begin(); itr != pages.end(); ++itr ) {
                for( std::uint8_t mask = 0x80; mask != 0; mask >>= 1, ++index ) {
                    if( *itr & mask )
                        pg.push_back( index );
                }
            }
            hdr.size += static_cast< std::uint8_t >( pg.size() * sizeof( std::uint16_t ) );
            if( std::fwrite( &hdr, sizeof( FTS8Header ), 1, out ) != 1 ||
                std::fwrite( &pg[0], sizeof( std::uint16_t ), pg.size(), out ) != pg.size() )
                throw FatalError( ERR_WRITE );
            written = hdr.size; 
        }
        else if ( comp == ABSENT ) {
            std::vector< std::uint16_t > pg;
            pg.reserve( maxPage - pageCount );
            std::uint16_t index( 0 );
            for( ConstPageIter itr = pages.begin(); itr != pages.end(); ++itr ) {
                for( std::uint8_t mask = 0x80; mask != 0; mask >>= 1, ++index ) {
                    if( !( *itr & mask ) )
                        pg.push_back( index );
                }
            }
            hdr.size += static_cast< std::uint8_t >( pg.size() * sizeof( std::uint16_t ) );
            if( std::fwrite( &hdr, sizeof( FTS8Header ), 1, out ) != 1 ||
                std::fwrite( &pg[0], sizeof( std::uint16_t ), pg.size(), out ) != pg.size() )
                throw FatalError( ERR_WRITE );
            written = hdr.size; 
        }
        else if ( comp ==  TRUNC ) {
            hdr.size += static_cast< std::uint8_t >( pages.size() * sizeof( std::uint8_t ) );
            if( std::fwrite( &hdr, sizeof( FTS8Header ), 1, out ) != 1 ||
                std::fwrite( &pages[0], sizeof( std::uint8_t ), pages.size(), out ) != pages.size() )
                throw FatalError( ERR_WRITE );
            written = hdr.size;
        }
        else if ( comp == DBL_TRUNC ) {
            hdr.size += static_cast< std::uint8_t >( pages.size() * sizeof( std::uint8_t ) +
                        sizeof( std::uint16_t ) );
            if( std::fwrite( &hdr, sizeof( FTS8Header ), 1, out ) != 1 ||
                std::fwrite( &firstPage, sizeof( std::uint16_t ), 1, out ) != 1 ||
                std::fwrite( &pages[0], sizeof( std::uint8_t ), pages.size(), out ) != pages.size() )
                throw FatalError( ERR_WRITE );
            written = hdr.size; 
        } 
    }
    return written;
}

