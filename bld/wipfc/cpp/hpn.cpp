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
* Description:  Process hpn/ehpn tags
*
*   :hp1-:hp9 / :ehp1-:ehp9
*   Cannot nest
*
****************************************************************************/

#include "hpn.hpp"
#include "cell.hpp"
#include "document.hpp"
#include "errors.hpp"
#include "util.hpp"


unsigned int Hpn::nestLevel( 0 );

Hpn::Hpn( Document* d, Element *p, const std::wstring* f, unsigned int r,
          unsigned int c, unsigned int l ) : Element( d, p, f, r, c ), lvl( l )
{
    if( nestLevel )
        d->printError( ERR2_NEST );
    else
        nestLevel = l;
}
/***************************************************************************/
Lexer::Token Hpn::parse( Lexer* lexer )
{
    Lexer::Token tok( document->getNextToken() );
    lexer = lexer;
    while( tok != Lexer::TAGEND ) {
        if( tok == Lexer::ATTRIBUTE )
            document->printError( ERR1_ATTRNOTDEF );
        else if( tok == Lexer::FLAG )
            document->printError( ERR1_ATTRNOTDEF );
        else if( tok == Lexer::ERROR_TAG )
            throw FatalError( ERR_SYNTAX );
        else if( tok == Lexer::END )
            throw FatalError( ERR_EOF );
        else
            document->printError( ERR1_TAGSYNTAX );
        tok = document->getNextToken();
    }
    return document->getNextToken();    //consume TAGEND
}
/***************************************************************************/
void Hpn::buildText( Cell* cell )
{
    if( lvl != 4 && lvl < 8 ) {
        cell->addByte( 0xFF );  //esc
        cell->addByte( 0x03 );  //size
        cell->addByte( 0x04 );  //change style
        if( lvl < 4 )
            cell->addByte( static_cast< std::uint8_t >( lvl ) );
        else
            cell->addByte( static_cast< std::uint8_t >( lvl - 1) );
    }
    else {
        cell->addByte( 0xFF );  //esc
        cell->addByte( 0x03 );  //size
        cell->addByte( 0x0D );  //change style
        if( lvl == 4 )
            cell->addByte( 0x01 );  //default
        else
            cell->addByte( static_cast< std::uint8_t >( lvl - 6) );
    }
    if( cell->textFull() )
        printError( ERR1_LARGEPAGE );
}
/***************************************************************************/
EHpn::EHpn( Document* d, Element *p, const std::wstring* f, unsigned int r,
            unsigned int c, unsigned int l ) : Element ( d, p, f, r, c ), level( l )
{
    if( Hpn::level() == l )
        Hpn::setLevel( 0 );
    else
        d->printError( ERR1_TAGCONTEXT );
}
/***************************************************************************/
Lexer::Token EHpn::parse( Lexer* lexer )
{
    Lexer::Token tok( document->getNextToken() );
    lexer = lexer;
    while( tok != Lexer::TAGEND ) {
        if( tok == Lexer::ATTRIBUTE )
            document->printError( ERR1_ATTRNOTDEF );
        else if( tok == Lexer::FLAG )
            document->printError( ERR1_ATTRNOTDEF );
        else if( tok == Lexer::ERROR_TAG )
            throw FatalError( ERR_SYNTAX );
        else if( tok == Lexer::END )
            throw FatalError( ERR_EOF );
        else
            document->printError( ERR1_TAGSYNTAX );
        tok = document->getNextToken();
    }
    return document->getNextToken();    //consume TAGEND
}
/***************************************************************************/
void EHpn::buildText( Cell* cell )
{
    if( level != 4 && level < 8 ) {
        cell->addByte( 0xFF );  //esc
        cell->addByte( 0x03 );  //size
        cell->addByte( 0x04 );  //change style
        cell->addByte( 0x00 );  //default
    }
    else {
        cell->addByte( 0xFF );  //esc
        cell->addByte( 0x03 );  //size
        cell->addByte( 0x0D );  //change style
        cell->addByte( 0x00 );  //default
    }
    if( cell->textFull() )
        printError( ERR1_LARGEPAGE );
}
