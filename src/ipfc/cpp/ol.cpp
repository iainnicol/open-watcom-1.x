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
* Description:  Process ol/eol tags
*
*   :ol / :eol
*       compact (else blank line between items)
*   If nested, indent 4 spaces
*
****************************************************************************/

#include "ol.hpp"
#include "brcmd.hpp"
#include "dl.hpp"
#include "cell.hpp"
#include "document.hpp"
#include "errors.hpp"
#include "lexer.hpp"
#include "lm.hpp"
#include "lp.hpp"
#include "p.hpp"
#include "parml.hpp"
#include "punct.hpp"
#include "sl.hpp"
#include "ul.hpp"
#include "whtspc.hpp"
#include "word.hpp"

Lexer::Token Ol::parse( Lexer* lexer )
{
    Lexer::Token tok( parseAttributes( lexer ) );
    unsigned int itemCount( 0 );
    while( tok != Lexer::END && !( tok == Lexer::TAG && lexer->tagId() == Lexer::EUSERDOC ) ) {
        if( parseInline( lexer, tok ) ) {
            switch( lexer->tagId() ) {
            case Lexer::DL:
                {
                    Element* elt( new Dl( document, this, document->dataName(),
                        document->dataLine(), document->dataCol(),
                        indent == 1 ? 4 : indent + 3 ) );
                    appendChild( elt );
                    tok = elt->parse( lexer );
                }
                break;
            case Lexer::OL:
                {
                    Element* elt( new Ol( document, this, document->dataName(),
                        document->dataLine(), document->dataCol(),
                        nestLevel + 1, indent == 1 ? 4 : indent + 3 ) );
                    appendChild( elt );
                    tok = elt->parse( lexer );
                }
                break;
            case Lexer::LI:
                {
                    Element* elt( new OlLi( document, this, document->dataName(),
                        document->dataLine(), document->dataCol(),
                        itemCount++, nestLevel, indent, compact ) );
                    appendChild( elt );
                    tok = elt->parse( lexer );
                }
                break;
            case Lexer::LP:
                {
                    Element* elt( new Lp( document, this, document->dataName(),
                        document->dataLine(), document->dataCol(), indent + 3 ) );
                    appendChild( elt );
                    tok = elt->parse( lexer );
                }
                break;
            case Lexer::EOL:
                {
                    Element* elt( new EOl( document, this, document->dataName(),
                        document->dataLine(), document->dataCol() ) );
                    appendChild( elt );
                    return elt->parse( lexer );
                }
            case Lexer::PARML:
                {
                    Element* elt( new Parml( document, this, document->dataName(),
                        document->dataLine(), document->dataCol(),
                        indent == 1 ? 4 : indent + 3 ) );
                    appendChild( elt );
                    tok = elt->parse( lexer );
                }
                break;
            case Lexer::SL:
                {
                    Element* elt( new Sl( document, this, document->dataName(),
                        document->dataLine(), document->dataCol(),
                        0, indent == 1 ? 4 : indent + 3 ) );
                    appendChild( elt );
                    tok = elt->parse( lexer );
                }
                break;
            case Lexer::UL:
                {
                    Element* elt( new Ul( document, this, document->dataName(),
                        document->dataLine(), document->dataCol(),
                        0, indent == 1 ? 4 : indent + 3 ) );
                    appendChild( elt );
                    tok = elt->parse( lexer );
                }
                break;
            default:
                document->printError( ERR1_NOENDLIST );
                while( tok != Lexer::TAGEND )
                    tok = document->getNextToken();
                tok = document->getNextToken();
            }
        }
    }
    return tok;
}
/***************************************************************************/
Lexer::Token Ol::parseAttributes( Lexer* lexer )
{
    Lexer::Token tok( document->getNextToken() );
    lexer = lexer;
    while( tok != Lexer::TAGEND ) {
        if( tok == Lexer::ATTRIBUTE )
            document->printError( ERR1_ATTRNOTDEF );
        else if( tok == Lexer::FLAG ) {
            if( lexer->text() == L"compact" )
                compact = true;
            else
                document->printError( ERR1_ATTRNOTDEF );
        }
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
void EOl::buildText( Cell* cell )
{
    cell->addByte( 0xFF );  //esc
    cell->addByte( 0x03 );  //size
    cell->addByte( 0x02 );  //set left margin
    cell->addByte( 1 );
}
/***************************************************************************/
Lexer::Token OlLi::parse( Lexer* lexer )
{
    Lexer::Token tok( parseAttributes( lexer ) );
    appendChild( new Lm( document, this, document->dataName(), document->dataLine(),
        document->dataCol(), indent ) );
    if( compact )
        appendChild( new BrCmd( document, this, document->dataName(), document->dataLine(),
            document->dataCol() ) );
    else
        appendChild( new P( document, this, document->dataName(), document->dataLine(),
            document->dataCol() ) );
    if( nestLevel & 1 ) {
        std::wstring txt;
        txt.push_back( document->olChar( itemNumber ) );
        appendChild( new LiteralWhiteSpace( document, this, document->dataName(),
            document->dataLine(), document->dataCol(), true ) );
        appendChild( new Word( document, this, document->dataName(),
            document->dataLine(), document->dataCol(), txt, false ) );
        appendChild( new Punctuation( document, this, document->dataName(),
            document->dataLine(), document->dataCol(), document->olClose( 0 ), true ) );
    }
    else {
        wchar_t tmp[ 4 ];
        _utow( itemNumber + 1, tmp, 10 );
        std::wstring txt( tmp );
        if( itemNumber < 9 )
            appendChild( new LiteralWhiteSpace( document, this, document->dataName(),
                document->dataLine(), document->dataCol(), true ) );
        appendChild( new Word( document, this, document->dataName(),
            document->dataLine(), document->dataCol(), txt, itemNumber >= 9 ) );
        appendChild( new Punctuation( document, this, document->dataName(),
            document->dataLine(), document->dataCol(), document->olClose( 0 ), true ) );
    }
    appendChild( new Lm( document, this, document->dataName(), document->dataLine(),
        document->dataCol(), indent + 3 ) );
    while( tok != Lexer::END && !( tok == Lexer::TAG && lexer->tagId() == Lexer::EUSERDOC ) ) {
        if( parseInline( lexer, tok ) ) {
            if( lexer->tagId() == Lexer::DL ||
                lexer->tagId() == Lexer::PARML ||
                lexer->tagId() == Lexer::OL ||
                lexer->tagId() == Lexer::LI ||
                lexer->tagId() == Lexer::EOL ||
                lexer->tagId() == Lexer::SL ||
                lexer->tagId() == Lexer::UL ) {
                break;
            }
            else if( lexer->tagId() == Lexer::LP ) {
                Element* elt( new P( document, this, document->dataName(),
                    document->dataLine(), document->dataCol() ) );
                appendChild( elt );
                tok = elt->parse( lexer );
            }
            else
                parseCleanup( tok );
        }
    }
    return tok;
}

