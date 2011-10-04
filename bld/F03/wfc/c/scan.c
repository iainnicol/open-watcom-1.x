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
* Description:  WHEN YOU FIGURE OUT WHAT THIS FILE DOES, PLEASE
*               DESCRIBE IT HERE!
*
****************************************************************************/


//
// SCAN :       Scanner
//

#include "ftnstd.h"
#include "errcod.h"
#include "extnsw.h"
#include "stmtsw.h"
#include "global.h"
#include "csetinfo.h"
#include "cpopt.h"
#include "ferror.h"
#include "comio.h"
#include "scan.h" 

#include <string.h>
#include <stdlib.h>


extern  character_set   CharSetInfo;

static  void            ScanNum(void);
static  void            LkUpLog(void);

#define COLUMNS 20 // was 17 in F77

// bit 8: Language extension character
// bit 7: Lower case character. This is an extension to standard F77

//#define C_EXT   0x80    //  extension to standard defined character set.
//#define C_LOW   0x40    //  lower case character
//#define C_MASK  ~( C_EXT | C_LOW )

// the character classes known to the scanner
//typedef enum {
//    // primary character classes
//    //
//    C_AL,       // alphabetic characters and '$'
//    C_EX,       // exponent ( 'E', 'D' or 'Q' )
//    C_SG,       // sign ( '+' or '-' )
//    C_DP,       // decimal point
//    C_DI,       // digit ( 0..9 )
//    C_HL,       // hollerith 'H'
//    C_AP,       // apostrophe ( ' )
//    C_OP,       // illegal operators, delimiters
//    C_SP,       // blank
//    C_TC,       // TAB character
//    C_BC,       // illegal source input character
//    C_EL,       // end-of-line
//    C_CM,       // end-of-line comment character
//    C_OL,       // octal constant indicator
//    C_HX,       // hexadecimal constant indicator
//    C_CS,       // C string constant indicator
//    C_DB,       // 1st byte of a double-byte character
//    //
//    //-------------------------------------------------
//    // new for F95
//    //
//    C_QO,       // quote ( " )
//    C_SS,       // statement separator ';'
//    C_CC,       // continuation character '&'
//    //
//    //-------------------------------------------------
//    // extended character classes
//    //
//    XC_AL =  (C_AL | C_EXT),
//    XC_EX =  (C_EX | C_EXT),
//    XC_SG =  (C_SG | C_EXT),
//    XC_DP =  (C_DP | C_EXT),
//    XC_DI =  (C_DI | C_EXT),
//    XC_HL =  (C_HL | C_EXT),
//    XC_AP =  (C_AP | C_EXT),
//    XC_OP =  (C_OP | C_EXT),
//    XC_SP =  (C_SP | C_EXT),
//    XC_TC =  (C_TC | C_EXT),
//    XC_BC =  (C_BC | C_EXT),
//    XC_EL =  (C_EL | C_EXT),
//    XC_CM =  (C_CM | C_EXT),
//    XC_OL =  (C_OL | C_EXT),
//    XC_HX =  (C_HX | C_EXT),
//    XC_CS =  (C_CS | C_EXT),
//    XC_DB =  (C_DB | C_EXT),
//    //
//    //-------------------------------------------------
//    // new for F95
//    //
//    XC_QO =  (C_QO | C_EXT),
//    XC_SS =  (C_SS | C_EXT),
//    XC_CC =  (C_CC | C_EXT),
//    //             
//    //-------------------------------------------------
//    // lower case characters
//    //
//    LC_AL =  (XC_AL | C_LOW),
//    LC_EX =  (XC_EX | C_LOW),
//    LC_HL =  (XC_HL | C_LOW),
//    LC_OL =  (XC_OL | C_LOW),
//    LC_HX =  (XC_HX | C_LOW),
//    LC_CS =  (XC_CS | C_LOW),
//    //
//    //-------------------------------------------------
//    //
//    C_MAX = UCHAR_MAX   // force enum to be unsigned
//    //
//} charClassType;

static  const token_state __FAR StateTable[][COLUMNS] = {

// class {}=new for F95
// AL  EX  SG  DP  DI  HL  AP  OP  SP  TC  BC  EL  CM  OL  HX  CS  DB {QO  SS  CC} // state                           example
  SAN,SAN,SSG,SLL,SNM,SAN,SFQ,SOP,SSP,STC,SBC,SNR,SCM,SAN,SAN,SAN,SDB,SFQ,SNS,SNS, // NS no state determined
  SSO,SEX,SSO,SML,SNM,SHL,SSO,SSO,SSP,STC,SBC,SNR,SCM,SSO,SSO,SSO,SSO,SSO,SNS,SNS, // NM number                       123
  SAN,SAN,SSO,SSO,SAN,SAN,SSO,SSO,SSP,STC,SBC,SNR,SCM,SAN,SAN,SAN,SDB,SSO,SNS,SNS, // AN alpha-numeric                V1Q2
  SSO,SSO,SSO,SML,SNM,SSO,SSO,SSO,SSP,STC,SBC,SNR,SCM,SSO,SSO,SSO,SSO,SSO,SNS,SNS, // SG sign                         + or -
  SSO,SEX,SSO,SSO,SFT,SSO,SSO,SSO,SSP,STC,SBC,SNR,SCM,SSO,SSO,SSO,SSO,SSO,SNS,SNS, // FT floating point number        134.5
  SLG,SLG,SEN,SSO,SEN,SLG,SSO,SSO,SSP,STC,SBC,SNR,SCM,SLG,SLG,SLG,SDB,SSO,SNS,SNS, // LX logical or exponent of float 134.e
  SSO,SSO,SEN,SSO,SEN,SSO,SSO,SSO,SSP,STC,SBC,SNR,SCM,SSO,SSO,SSO,SSO,SSO,SNS,SNS, // EX exponent of float collected  134.5e
  SSO,SSO,SSO,SSO,SEN,SSO,SSO,SSO,SSP,STC,SBC,SNR,SCM,SSO,SSO,SSO,SSO,SSO,SNS,SNS, // EN exp number being collected   134.5e6
  SLG,SLG,SSO,SFL,SSO,SLG,SSO,SSO,SSP,STC,SBC,SNR,SCM,SLG,SLG,SLG,SDB,SSO,SNS,SNS, // LG logical being collected      .tru or .junk
  SLG,SLX,SSO,SSO,SFT,SLG,SSO,SSO,SSP,STC,SBC,SNR,SCM,SLG,SLG,SLG,SDB,SSO,SNS,SNS, // ML may be logical               134.
  SIQ,SIQ,SIQ,SIQ,SIQ,SIQ,SAP,SIQ,SIQ,SIQ,SIQ,SNR,SIQ,SIQ,SIQ,SIQ,SIQ,SAP,SNS,SNS, // IQ in quotes                    'joh or 'jane''
  SSO,SSO,SSO,SSO,SSO,SSO,SIQ,SSO,SSO,STC,SBC,SNR,SCM,SOL,SHX,SCS,SSO,SIQ,SNS,SNS, // AP apostrophe                   'jane'
  SIH,SIH,SIH,SIH,SIH,SIH,SIH,SIH,SIH,SIH,SIH,SNR,SIH,SIH,SIH,SIH,SIH,SIH,SNS,SNS, // IH in hollerith                 35h the cow jum
  SFM,SFM,SFM,SFM,SFM,SFM,SFM,SFM,SFM,SFM,SFM,SNR,SFM,SFM,SFM,SFM,SFM,SFM,SNS,SNS, // FM in FORMAT statement          FORMAT( 1X
  SSO,SSO,SSO,SSO,SSO,SSO,SSO,SSO,SSO,SSO,SBC,SNR,SCM,SSO,SSO,SSO,SSO,SSO,SNS,SNS, // OL octal constant               '777'o
  SSO,SSO,SSO,SSO,SSO,SSO,SSO,SSO,SSO,SSO,SBC,SNR,SCM,SSO,SSO,SSO,SSO,SSO,SNS,SNS, // HX hexadecimal constant         'fff'x
  SSO,SSO,SSO,SSO,SSO,SSO,SSO,SSO,SSO,SSO,SBC,SNR,SCM,SSO,SSO,SSO,SSO,SSO,SNS,SNS, // CS C string (null terminated)   'abc'c
  SLG,SLG,SSO,SSO,SFT,SLG,SSO,SSO,SSP,STC,SBC,SNR,SCM,SLG,SLG,SLG,SDB,SSO,SNS,SNS, // LL likely logical               x.
};

#define BAD_LOG         14

char    *LogTab[] = {
        "EQ",   "NE",    "LT",    "GT",    "LE",     "GE",
        "OR",   "AND",   "NOT",   "EQV",   "NEQV",   "XOR",
        "TRUE", "FALSE", NULL
};

static  char            ExpREA;
static  char            ExpDBL;
static  char            ExpEXT;
static  token_class     TokenREA;
static  token_class     TokenDBL;
static  token_class     TokenEXT;


void    InitScan() {
//==================

// Initialize the scanner.

    if( Options & OPT_EXTEND_REAL ) {
        TokenREA = TO_DBL;
        ExpREA   = 'D';
        TokenDBL = TO_EXT;
        ExpDBL   = 'Q';
    } else {
        TokenREA = TO_REA;
        ExpREA   = 'E';
        TokenDBL = TO_DBL;
        ExpDBL   = 'D';
    }
    TokenEXT = TO_EXT;
    ExpEXT   = 'Q';
    Line     = 0;
    State    = SNS;
    TkCrsr   = &TokenBuff[ 0 ];
    
    LexToken.stop  = TkCrsr;
    LexToken.col   = Column;
    LexToken.flags = 0;
    LexToken.line  = 0;
    
    SrcRecNum = CurrFile->rec;
    // at this point, the line has already been read
    // so just print it with an ISN in front
    LinePrint();
    
    if( StmtType == STMT_CONT ) {
        Error( CC_NOT_INITIAL );
    }
    // examine the statement number if there was one
    ScanNum();
    ExtnSw &= ~XS_CONT_20;
}


void    Scan() {
//==============

// Collect a token.

    token_state     state2;
    char            ch;
    token_state     old_state;
    char            *dpt = NULL;
    byte            tab;
    int             len;
    int             hlen;
    token_class     class;
    charClassType   ch_class;
    charClassType   wasextch;

    if( !(LexToken.flags & TK_LAST) ) {
        wasextch = 0;
        old_state = SNS;
        LexToken.start = LexToken.stop;
        LexToken.col   = Column;
        LexToken.line  = Line;
        for(;;) {
            ch = *Cursor;
            ch_class = CharSetInfo.character_set[ (int)ch ];
            wasextch |= ch_class;
            state2 = StateTable[ State ][ ch_class & C_MASK ];
            switch( state2 ) {
            case SAN :
            case SLG :
                if( ch_class & C_LOW ) { // lower case character
                    ch += 'A' - 'a';
                }
                *TkCrsr = ch;
                TkCrsr++;
                State = state2;
                break;
            case SDB :
                if( CharSetInfo.character_width( Cursor ) != 2 ) {
                    Error( CC_BAD_CHAR );
                } else if( CharSetInfo.is_double_byte_blank( Cursor ) ) {
                    *Cursor = ' ';
                    *( Cursor + 1 ) = ' ';
                    Column--; // compensate for Column++ and Cursor++
                    Cursor--; // after select
                } else {
                    State = StateTable[ State ][ C_AL ];
                    *TkCrsr = ch;
                    TkCrsr++;
                    Cursor++;
                    Column++;
                    *TkCrsr = *Cursor;
                    TkCrsr++;
                }
                break;
            case SNM :
            case SFT :
            case SEN :
                *TkCrsr = ch;
                TkCrsr++;
                State = state2;
                break;
            case SSG :
                *TkCrsr = ch;
                TkCrsr++;
                // 0..71 is the statement area
                // 72..79 is the sequence area
                ++Cursor;
                if( ++Column >= LastColumn ) { // we've just processed column 72
                    *Cursor = NULLCHAR;
                }
                State = SOP;
                class = TO_OPR;
                goto token;
            case SEX :
            case SLX :
                if( LexToken.flags & TK_LENSPEC ) {
                    LexToken.flags &= ~TK_LENSPEC;
                    goto token;
                }
                if( ch_class & C_LOW ) { // lower case character
                    ch += 'A' - 'a';
                }
                State = state2;
                switch( ch ) {
                case( 'Q' ):
                    class = TokenEXT;
                    break;
                case( 'D' ):
                    class = TokenDBL;
                    break;
                case( 'E' ):
                    class = TokenREA;
                    break;
                }
                *TkCrsr = ch;
                TkCrsr++;
                break;
            case SML :
            case SLL :
                dpt = TkCrsr;
                old_state = State;
                *TkCrsr = ch;
                TkCrsr++;
                State = state2;
                break;
            case SFQ :
                State = SIQ;
                break;
            case SIQ :
                state2 = SIQ;
            case SFM :
                if( ch_class == C_TC ) {
                    tab = 8 - Column % 8;
                    // Column gets incremented normally at bottom of loop
                    Column += tab - 1;
                    memset( TkCrsr, ' ', tab );
                    TkCrsr += tab;
                } else {
                    *TkCrsr = ch;
                    TkCrsr++;
                }
                State = state2;
                break;
            case SOL :
            case SHX :
            case SCS :
                *TkCrsr = NULLCHAR; // for conversion routines
                TkCrsr++;
            case SAP :
                State = state2;
                break;
            case SSO :
                goto token;
            case SOP :
                *TkCrsr = ch;
                TkCrsr++;
                // 0..71 is the statement area
                // 72..79 is the sequence area
                ++Cursor;
                if( ++Column >= LastColumn ) { // we've just processed column 72
                    *Cursor = NULLCHAR;
                }
                State = SOP;
                class = TO_OPR;
                goto token;
            case SFL :
                if( old_state == SNS ) {
                    // Consider: i .eq. j
                    LkUpLog();
                    if( LexToken.log != BAD_LOG ) {
                        // if it's a valid logical operator,
                        // set final state to SFL
                        State = state2;
                    } else if( dpt == NULL ) {
                        dpt = LexToken.start;
                    }
                } else {
                    // Consider: 1 .eq. 2
                    State = state2;
                }
                goto token;
            case SHL :
                if( LexToken.flags & TK_LENSPEC ) {
                    LexToken.flags &= ~TK_LENSPEC;
                    goto token;
                }
                *TkCrsr = NULLCHAR;
                len = atoi( LexToken.start );
                LexToken.start = TkCrsr;
                State = SIH;
                class = TO_LIT;
                StmtSw |= SS_HOLLERITH;
                break;
            case SIH :
                if( TkCrsr - LexToken.start >= len ) {
                    TkCrsr = LexToken.start + len; // in case of TABCHAR
                    State = SSO;
                    goto token;
                }
                if( ch_class == C_TC ) {
                    tab = 8 - Column % 8;
                    // Column gets incremented normally at bottom of loop
                    Column += tab - 1;
                    memset( TkCrsr, ' ', tab );
                    TkCrsr += tab;
                } else {
                    *TkCrsr = ch;
                    TkCrsr++;
                }
                break;
            case SSP :
                if( State == SNS ) {
                    LexToken.col = Column;
                }
                break;
            case STC :
                // Column gets incremented normally at bottom of loop
                Column += 7 - Column % 8;
                break;
            case SBC :
                Error( CC_BAD_CHAR );
                break;
            case SCM :
                if( !(ExtnSw & XS_EOL_COMMENT) ) {
                    Extension( CC_EOL_COMMENT );
                    ExtnSw |= XS_EOL_COMMENT;
                }
            case SNR :
                if( LexToken.flags & TK_INCLUDE ) {
                    LexToken.flags |= TK_LAST;
                    goto token;
                }
                // 0..71 is the statement area
                // 72..79 is the sequence area
                // calculate the number of spaces
                // that we may require for filling
                tab = LastColumn - Column;
                ComRead();
                if( StmtType != STMT_CONT ) {
                    LexToken.flags |= TK_LAST;
                    goto token;
                }
                if( ( State == SIQ ) || ( State == SIH ) || ( State == SFM ) ) {
                    memset( TkCrsr, ' ', tab );
                    TkCrsr += tab;
                }
                ++Line;
                ComPrint();
                ScanNum();
                if( Line >= 20 ) {
                    if( !(ExtnSw & XS_CONT_20) ) {
                        Extension( CC_TOO_MANY_CONT );
                        ExtnSw |= XS_CONT_20;
                    }
                    if( (TkCrsr-TokenBuff) + (LastColumn-CONT_COL) > TOKLEN ) {
                        TkCrsr = TokenBuff; // so we don't overflow TokenBuff
                        if( !(StmtSw & SS_CONT_ERROR_ISSUED) ) {
                            Error( CC_CONT_OVERFLOW );
                            StmtSw |= SS_CONT_ERROR_ISSUED;
                        }
                    }
                }
                if( State == SNS ) {
                    LexToken.col = Column;
                }
                Column--; // to offset ++Cursor and ++Column in code
                Cursor--; // after } (must be after ScanNum
                break;    // and Error since Error uses Column)
            }
            // 0..71 is the statement area
            // 72..79 is the sequence area
            ++Cursor;
            if( ++Column >= LastColumn ) { // we've just processed column 72
                *Cursor = NULLCHAR;
            }
        }
token:  LexToken.stop  = TkCrsr;
        state2 = State;                // final state for Scan
        State = SNS;                   // set to no state for next time
        switch( state2 ) {
        case SAN :
            class = TO_NAM;
            break;
        case SNM :
            class = TO_INT;
            break;
        case SFT :
            class = TokenREA;
            break;
        case SOL :
            class = TO_OCT;
            break;
        case SHX :
            class = TO_HEX;
            break;
        case SCS :
        case SAP :
            class = TO_LIT;
            break;
        case SFL :
            if( old_state == SNS ) {
                LexToken.start++;              // skip over starting dot
                // 0..71 is the statement area
                // 72..79 is the sequence area
                ++Cursor;
                if( ++Column >= LastColumn ) { // just processed column 72
                    *Cursor = NULLCHAR;
                }
                class = TO_LGL;
            } else {
                State = SLG;               // remember logical collected
                LexToken.stop = dpt;          // decimal not part of token
                class = TO_INT;
            }
            break;
        case SML :
            if( ( old_state == SNS ) || ( old_state == SSG ) ) {
                class = TO_OPR;
            } else {
                class = TokenREA;
            }
            break;
        case SLX :
        case SLG :
            LexToken.stop = dpt + sizeof( char ); // decimal is part of token
            State = SAN;                       // remember alphanumeric started
            if( old_state == SNS ) {
                class = TO_OPR;
            } else {
                class = TokenREA;
            }
            break;
        case SNS :
            LexToken.flags |= TK_EOL;
        case SLL :
            class = TO_OPR;
            break;
        case SIH :
            // We get here if and only if we are in a hollerith constant
            // and we've reached the end of the line (next line is not a
            // continuation line) and the length of the hollerith constant
            // has not been met.
            // "tab" is how may characters left until column 72
            hlen = TkCrsr - LexToken.start;        // get how many chars so far
            if( tab + hlen < len ) {            // if not enough characters
                Warning( HO_CUT_OFF );          // - say the hollerith cut off
                len = tab + hlen;               // - set length up to col 72
            }                                   // }
            memset( TkCrsr, ' ', len - hlen );  // fill rest of hollerith
            TkCrsr = LexToken.start + len;         // set new collection location
            break;
        case SFM :
            class = TO_FMT;
            break;
        case SIQ :
            Error( SX_QUOTE );
            class = TO_LIT;
            break;
        }
        LexToken.tclass = class;
        if( !(ExtnSw & XS_CHAR_EXTN) && ( class != TO_LIT ) &&
            ( class != TO_FMT ) && ( wasextch & C_EXT ) ) {
            Extension( CC_SET_EXTEND );
            ExtnSw |= XS_CHAR_EXTN;
        }
    } else {
        if( State == SAN ) {
            // Consider:   ... SYM.FIELD
            // ".FIELD" would have been scanned in anticipation of a logical
            // constant or operator but we reached the end of the statement
            // so that last token is "FIELD".
            LexToken.start = LexToken.stop;
            LexToken.stop = TkCrsr;
            LexToken.tclass = TO_NAM;
        } else {
            LexToken.tclass = TO_OPR;
        }
        LexToken.flags |= TK_EOL;
    }
}


static  void    ScanNum() {
//=========================

    if( StmtType != STMT_CONT ) {
        StmtNo = NextStmtNo;
        if( StmtNo == 0 ) {
            if( StmtNoFound ) {
                Error( ST_NUM_ZERO );
            }
        }
    } else {
        if( StmtNoFound ) {
            Error( CC_STMTNO_ON_CONT );
        }
        if( ( ContType == C_BC ) || ( ContType & C_EXT ) ) {
            // non-FORTRAN char or WATFOR-77 extension
            // but issue message only once
            if( !(ExtnSw & XS_CHAR_EXTN) ) {
                Extension( CC_SET_EXTEND );
                ExtnSw |= XS_CHAR_EXTN;
            }
        }
    }
}


static  void    LkUpLog() {
//=========================

    int         index;
    char        *ptr;

    index = 0;
    ptr = LexToken.start + sizeof( char ); // skip over "."
    *TkCrsr = NULLCHAR;
    for(;;) {
        if( strcmp( LogTab[ index ], ptr ) == 0 ) break;
        if( LogTab[ ++index ] == NULL ) break;
    }
    LexToken.log = index;
}
