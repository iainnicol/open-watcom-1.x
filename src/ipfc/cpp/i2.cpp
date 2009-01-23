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
* Description:  Process i2 tags
*
*   :i2
*       refid=[a-zA-z][a-zA-z0-9]*
*       global
*       sortkey='key-text'.index-text
*   Must follow :i1
*
****************************************************************************/

#include <algorithm>
#include "i2.hpp"
#include "document.hpp"
#include "errors.hpp"
#include "gdword.hpp"
#include "i1.hpp"
#include "ptrops.hpp"
#include "util.hpp"

Lexer::Token I2::parse( Lexer* lexer )
{
    Lexer::Token tok( parseAttributes( lexer ) );
    std::wstring txt;
    while( tok != Lexer::END && !( tok == Lexer::TAG && lexer->tagId() == Lexer::EUSERDOC)) {
        if( tok == Lexer::WORD )
            txt += lexer->text();
        else if( tok == Lexer::ENTITY ) {
            try {
                wchar_t ch( document->entity( lexer->text() ) );
                txt += ch;
            }
            catch( Class2Error& e ) {
                document->printError( e.code );
            }
        }
        else if( tok == Lexer::PUNCTUATION )
            txt += lexer->text();
        else if( tok == Lexer::WHITESPACE ) {
            if( lexer->text()[0] == L'\n' ) {
                tok = document->getNextToken();
                break;
            }
            txt+= lexer->text();
        }
        else
            break;
        tok = document->getNextToken();
    }
    if( txt.empty() )
        document->printError( ERR2_INOTEXT );
    index->setText( txt );
    return tok;
}
/*****************************************************************************/
Lexer::Token I2::parseAttributes( Lexer* lexer )
{
    Lexer::Token tok( document->getNextToken() );
    while( tok != Lexer::TAGEND ) {
        if( tok == Lexer::ATTRIBUTE ) {
            std::wstring key;
            std::wstring value;
            splitAttribute( lexer->text(), key, value );
            if( key == L"refid" )
                refid = value;
            else if( key == L"sortkey" )
                index->setSortKey( value );
            else
                printError( ERR1_ATTRNOTDEF );
        }
        else if( tok == Lexer::FLAG ) {
            if( lexer->text() == L"global" )
                index->setGlobal();
            else
                printError( ERR1_ATTRNOTDEF );
        }
        else if( tok == Lexer::ERROR_TAG )
            throw FatalError( ERR_SYNTAX );
        else if( tok == Lexer::END )
            throw FatalError( ERR_EOF );
        else
            document->printError( ERR1_TAGSYNTAX );
        tok = document->getNextToken();
    }
    if( refid.empty() )
        document->printError( ERR1_NOREFID );
    return document->getNextToken(); //consume TAGEND
}
/*****************************************************************************/
void I2::buildIndex()
{
    try {
        if( parentRes )
            index->setTOC( document->tocIndexByRes( parentRes ) );
        else if( parentId )
            index->setTOC( document->tocIndexById( parentId ) );
        I1* i1( document->indexById( refid ) );
        i1->addSecondary( index.get() );
    }
    catch( Class1Error& e ) {
        printError( e.code );
    }
}

