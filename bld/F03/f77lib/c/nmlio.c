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
// NMLIO        : run-time NAMELIST i/o processing
//

#include "ftnstd.h"
#include "rundat.h"
#include "pgmacc.h"
#include "errcod.h"
#include "symdefs.h"
#include "iotype.h"
#include "lgadv.h"
#include "nmlinfo.h"

#include <stdarg.h>
#include <string.h>
#include <ctype.h>

extern  void            Drop(char);
extern  void            SendStr(char *,uint);
extern  void            SendWSLStr(char *);
extern  void            SendEOR(void);
extern  void            NextRec(void);
extern  void            DoFreeIn(void);
extern  void            CheckEor(void);
extern  void            Blanks(void);
extern  void            BumpComma(void);
extern  void            IOErr(uint,...);
extern  int             Spawn(void (*)());
extern  void            Suicide(void);
extern  bool            DoSubscript(act_dim_list *,intstar4 *,intstar4 *);
extern  bool            DoSubstring(intstar4,intstar4,uint);
extern  intstar4        GetNum(void);
extern  char            *JmpBlanks(char *);

extern  void            (* const __FAR OutRtn[])();
extern  const byte __FAR        SizeVars[];

static  unsigned_32     NmlInCount;
static  PTYPE           NmlInType;
static  void            *NmlInAddr;


char            *Scanner() {
//==========================

// Point to where we are currently scanning.

    ftnfile     *fcb;

    fcb = IOCB->fileinfo;
    return( &fcb->buffer[ fcb->col ] );
}


bool            ScanChar( char chr ) {
//====================================

// Scan a character.

    if( *Scanner() == chr ) {
        IOCB->fileinfo->col++;
        return( TRUE );
    }
    return( FALSE );
}


bool            ScanEOL() {
//=========================

// Check for end-of-line.

    return( *Scanner() == NULLCHAR );
}


char            *ScanName( uint *len ) {
//======================================

// Scan a name.

    char        *name;
    char        *ptr;
    char        chr;

    name = Scanner();
    for( ptr = name; ; ++ptr ) {
        chr = *ptr;
        if( isalnum( chr ) ) continue;
        if( chr == '_' ) continue;
        if( chr == '$' ) continue;
        break;
    }
    *len = ptr - name;
    IOCB->fileinfo->col += *len;
    return( name );
}


bool            ScanSNum( signed_32 *num ) {
//==============================================

// Scan a signed number.

    char        *ptr;

    Blanks();
    ptr = Scanner();
    if( ( *ptr == '+' ) || ( *ptr == '-' ) ) {
        ++ptr;
    }
    if( isdigit( *ptr ) ) {
        *num = GetNum();
        Blanks();
        return( TRUE );
    } else {
        Blanks();
        return( FALSE );
    }
}


static  intstar4        SubScr( int info, char *adv_ss_ptr, int size ) {
//==========================================================================

// Get a subscript list.

    signed_32           ss[MAX_DIM];
    act_dim_list        dim_list;
    intstar4         *dim_ptr;
    signed_32        *ss_ptr;
    intstar4            lo;
    intstar4            offset;
    int                 num_ss;

    dim_list.dim_flags = 0;
    _SetDimCount( dim_list.dim_flags, _GetNMLSubScrs( info ) );
    dim_list.num_elts = 1;
    dim_ptr = &dim_list.subs_1_lo;
    num_ss = _GetNMLSubScrs( info );
    ss_ptr = ss;
    for(;;) {
        if( !ScanSNum( ss_ptr ) ) return( FALSE );
        ++ss_ptr;
        lo = *(intstar4 *)adv_ss_ptr;
        adv_ss_ptr += sizeof( intstar4 );
        dim_list.num_elts *= *(uint *)adv_ss_ptr;
        *dim_ptr = lo;
        ++dim_ptr;
        *dim_ptr = lo + *(uint *)adv_ss_ptr - 1;
        ++dim_ptr;
        adv_ss_ptr += sizeof( uint );
        --num_ss;
        if( num_ss == 0 ) break;
        if( !ScanChar( ',' ) ) break;
    }
    if( !ScanChar( ')' ) ) return( FALSE );
    if( !DoSubscript( &dim_list, ss, &offset ) ) return( FALSE );
    NmlInAddr = (char  *)NmlInAddr + offset * size;
    return( TRUE );
}


static  bool    SubStr( string *scb ) {
//=====================================

// Get a substring list.

    intstar4    ss1;
    intstar4    ss2;

    ss1 = 1;
    ss2 = scb->len;
    if( !ScanChar( ':' ) ) {
        if( !ScanSNum( &ss1 ) ) return( FALSE );
        if( !ScanChar( ':' ) ) return( FALSE );
    }
    if( !ScanChar( ')' ) ) {
        if( !ScanSNum( &ss2 ) ) return( FALSE );
        if( !ScanChar( ')' ) ) return( FALSE );
    }
    if( !DoSubstring( ss1, ss2, scb->len ) ) return( FALSE );
    scb->len = ss2 - ss1 + 1;
    scb->strptr = scb->strptr + ss1 - 1;
    return( TRUE );
}


void    NmlExec() {
//=================

    if( IOCB->flags & IOF_OUTPT ) {
        NmlOut();
    } else {
        NmlIn();
    }
    IOCB->typ = PT_NOTYPE;
}


static  void    NmlOut() {
//========================

    byte        *nml;
    byte        len;
    byte        info;
    PTYPE       typ;
    unsigned_32 num_elts;
    byte        *data;
    string      scb;
    lg_adv      *adv_ptr;

    nml = (char *)(IOCB->fmtptr);
    len = *nml; // get length of NAMELIST name
    ++nml;
    Drop( ' ' );
    Drop( '&' );
    SendStr( nml, len );
    nml += len;
    SendEOR();
    for(;;) {
        len = *nml;
        if( len == 0 ) break;
        ++nml;
        Drop( ' ' );
        SendStr( nml, len );
        nml += len;
        SendWSLStr( " = " );
        info = *nml;
        ++nml;
        typ = _GetNMLType( info );
        IOCB->typ = typ;
        if( _GetNMLSubScrs( info ) ) {
            if( info & NML_LG_ADV ) {
                adv_ptr = *(lg_adv * *)nml;
                num_elts = adv_ptr->num_elts;
                if( typ == PT_CHAR ) {
                    scb.len = adv_ptr->elt_size;
                    scb.strptr = (char *)adv_ptr->origin;
                } else {
                    data = (byte *)adv_ptr->origin;
                }
            } else {
                num_elts = *(unsigned_32  *)nml;
                nml += sizeof( unsigned_32 ) + _GetNMLSubScrs( info ) *
                                   ( sizeof( unsigned_32 ) + sizeof( int ) );
                if( typ == PT_CHAR ) {
                    scb.len = *(uint *)nml;
                    nml += sizeof( uint );
                    scb.strptr = *(byte * *)nml;
                } else {
                    data = *(byte * *)nml;
                }
            }
            while( num_elts != 0 ) {
                if( typ == PT_CHAR ) {
                    IORslt.string = scb;
                    OutRtn[ typ ]();
                    Drop( ' ' );
                    scb.strptr += scb.len;
                } else {
                    pgm_memget( (byte *)(&IORslt), data, SizeVars[typ] );
                    OutRtn[ typ ]();
                    data += SizeVars[ typ ];
                }
                --num_elts;
            }
        } else {
            switch( typ ) {
            case PT_LOG_1:
                IORslt.logstar4 = **(logstar1 *  *)nml;
                break;
            case PT_LOG_4:
                IORslt.logstar4 = **(logstar4  *  *)nml;
                break;
            case PT_INT_1:
                IORslt.intstar4 = **(intstar1  *  *)nml;
                break;
            case PT_INT_2:
                IORslt.intstar4 = **(intstar2  *  *)nml;
                break;
            case PT_INT_4:
                IORslt.intstar4 = **(intstar4  *  *)nml;
                break;
            case PT_REAL_4:
                IORslt.single = **(single  *  *)nml;
                break;
            case PT_REAL_8:
                IORslt.dble = **(double  *  *)nml;
                break;
            case PT_REAL_16:
                IORslt.extended = **(extended  *  *)nml;
                break;
            case PT_CPLX_8:
                IORslt.complex = **(complex  *  *)nml;
                break;
            case PT_CPLX_16:
                IORslt.dcomplex = **(dcomplex  *  *)nml;
                break;
            case PT_CPLX_32:
                IORslt.xcomplex = **(xcomplex  *  *)nml;
                break;
            case PT_CHAR:
                IORslt.string = **(string  *  *)nml;
                break;
            }
            OutRtn[ typ ]();
        }
        nml += sizeof( void  * );
        SendEOR();
    }
    SendWSLStr( " &END" );
    SendEOR();
}


static  byte  *FindNmlEntry( char *name, uint len ) {
//======================================================

// Scan NAMELIST information for given NAMELIST entry.

    uint        nml_len;
    byte     *nml;
    byte        info;

    nml = (char  *)(IOCB->fmtptr);
    nml_len = *nml;
    nml += sizeof( byte ) + nml_len;
    for(;;) {
        nml_len = *nml;
        if( nml_len == 0 ) return( NULL );
        ++nml;
        if( nml_len == len ) {
            if( pgm_memicmp( nml, name, len ) == 0 ) {
                return( nml + len );
            }
        }
        nml += nml_len;
        info = *nml;
        ++nml;
        if( _GetNMLSubScrs( info ) && ( info & NML_LG_ADV ) == 0 ) {
            nml += sizeof( unsigned_32 ) + _GetNMLSubScrs( info ) *
                                    ( sizeof( unsigned_32 ) + sizeof( int ) );
            if( _GetNMLType( info ) == PT_CHAR ) {
                nml += sizeof( int );
            }
        }
        nml += sizeof( byte  * );
    }
}


static  io_type_rtn     NmlIOType;

static PTYPE    NmlIOType() {
//===========================

// Get the type of an input item.

    uint        save_col;
    uint        len;
    char        *ptr;

    // when collecting constants, make sure we haven't encountered the
    // next name in the NAMELIST as in the following case
    //     LOGICAL A(3)
    //     INTEGER T
    //     NAMELIST /NML/ A, T
    //     READ( 1, NML )
    // Unit 1:
    //     &NML
    //     A = T F
    //     T = 4
    //     &END
    // when we are scanning "T = 4", we have to make sure that the T is
    // not interpreted as the value "true" for the 3rd element of A

    if( IOCB->rptnum <= 1 ) {
        Blanks();
        CheckEor();
        BumpComma();    // skip the "," if present
        CheckEor();
        Blanks();
        save_col = IOCB->fileinfo->col;
        ptr = ScanName( &len );
        // Make sure we have seen a name so that we don't confuse the opening
        // parenthesis of a complex number as an array element indicator
        //     COMPLEX A(2)
        //     NAMELIST /NML/ A
        //     READ( 1, NML )
        // Unit 1:
        //     &NML
        //     A = (1,2) (3,4)
        //     &END
        if( len != 0 ) {
            Blanks();
            if( ScanChar( '=' ) ) NmlInCount = 0;
            if( ScanChar( '(' ) ) NmlInCount = 0; // may be an array element
        }
        IOCB->fileinfo->col = save_col;
    }

    if( NmlInCount == 0 ) return( PT_NOTYPE );
    --NmlInCount;
    if( NmlInType == PT_CHAR ) {
        IORslt.string.len = ((string *)NmlInAddr)->len;
        IORslt.string.strptr = ((string *)NmlInAddr)->strptr;
        ((string *)NmlInAddr)->strptr =
            ((char  *)((string *)NmlInAddr)->strptr) +
                                            ((string *)NmlInAddr)->len;
    } else { // numeric or logical
        IORslt.pgm_ptr = NmlInAddr;
        NmlInAddr = (char *)NmlInAddr + SizeVars[ NmlInType ];
    }
    return( NmlInType );
}


static  void    NmlIn() {
//=======================

    char     *nml;
    uint        nml_len;
    char        *ptr;
    uint        len;
    char     *nml_entry;
    byte        info;
    string      scb;
    char        e_chr;
    lg_adv   *adv_ptr;
    char     *adv_ss_ptr;
    uint        size;

    IOTypeRtn = &NmlIOType;
    IOCB->rptnum = -1;  // initialize for first call to NmlIOType()
    nml = (char *)(IOCB->fmtptr);
    nml_len = *nml; // get length of NAMELIST name
    ++nml;
    e_chr = '&'; // assume '&' used
    for(;;) { // find the start of the NAMELIST information
        NextRec();
        Blanks();
        if( !ScanChar( '&' ) ) {
            if( !ScanChar( '$' ) ) continue;
            e_chr = '$'; // a '$' was used instead
        }
        ptr = ScanName( &len );
        if( nml_len != len ) continue;
        if( pgm_memicmp( ptr, nml, len ) != 0 ) continue;
        if( ScanEOL() || ScanChar( ' ' ) || ScanChar( '\t' ) ) break;
    }
    for(;;) {
        Blanks();
        CheckEor();
        Blanks();
        ptr = Scanner();
        if( *ptr == e_chr ) {
            ++ptr;
            if( ( toupper( ptr[0] ) == 'E' ) &&
                ( toupper( ptr[1] ) == 'N' ) &&
                ( toupper( ptr[2] ) == 'D' ) ) ptr += 3;
            if( *JmpBlanks( ptr ) == NULLCHAR ) break;
        }
        ptr = ScanName( &len );
        nml_entry = FindNmlEntry( ptr, len );
        if( nml_entry == NULL ) {
            ptr[len] = NULLCHAR;
            IOErr( IO_NML_NO_SUCH_NAME, ptr );
        }
        info = *nml_entry;
        ++nml_entry;
        NmlInType = _GetNMLType( info );
        if( _GetNMLSubScrs( info ) ) {  // array
            if( info & NML_LG_ADV ) {
                adv_ptr = *(lg_adv *  *)nml_entry;
                NmlInAddr = (byte *)adv_ptr->origin;
                if( NmlInType == PT_CHAR ) {
                    scb.len = adv_ptr->elt_size;
                }
                NmlInCount = adv_ptr->num_elts;
                adv_ss_ptr = ((char *)adv_ptr + ADV_BASE_SIZE);
            } else {
                NmlInCount = *(unsigned_32 *)nml_entry;
                nml_entry += sizeof( unsigned_32 );
                adv_ss_ptr = nml_entry;
                nml_entry += _GetNMLSubScrs( info ) *
                             ( sizeof( unsigned_32 ) + sizeof( int ) );
                if( NmlInType == PT_CHAR ) {
                    scb.len = *(uint *)nml_entry;
                    nml_entry += sizeof( uint );
                }
                NmlInAddr = *(byte *  *)nml_entry;
            }
            if( ScanChar( '(' ) ) {
                if( NmlInType == PT_CHAR ) {
                    size = scb.len;
                } else {
                    size = SizeVars[ NmlInType ];
                }
                if( !SubScr( info, adv_ss_ptr, size ) ) {
                    IOErr( IO_NML_BAD_SUBSCRIPT );
                }
            }
            if( NmlInType == PT_CHAR ) {
                scb.strptr = NmlInAddr;
                if( ScanChar( '(' ) ) {
                    if( !SubStr( &scb ) ) {
                        IOErr( IO_NML_BAD_SUBSTRING );
                    }
                }
                NmlInAddr = &scb;
            }
        } else { // variable
            NmlInCount = 1;
            NmlInAddr = *(byte  *  *)nml_entry;
            if( NmlInType == PT_CHAR ) {
                scb = *(string *)NmlInAddr;
                if( ScanChar( '(' ) ) {
                    if( !SubStr( &scb ) ) {
                        IOErr( IO_NML_BAD_SUBSTRING );
                    }
                }
                NmlInAddr = &scb;
            }
        }
        IOCB->typ = NmlInType;
        Blanks();
        if( !ScanChar( '=' ) ) {
            IOErr( IO_NML_BAD_SYNTAX );
            break;
        }
        Blanks();
        if( Spawn( &DoFreeIn ) != 0 ) {
            // Suicide() was called - make sure it really was an error
            if( IOCB->flags & NML_CONTINUE ) {
                IOCB->flags &= ~NML_CONTINUE;
                continue;
            }
            // we got an error during NAMELIST input
            Suicide();
        }
    }
    IOTypeRtn = &IOType;
}


void    NmlAddrs( va_list args ) {
//================================

// Get addresses of NAMELIST symbols.

    byte     *nml;
    byte        len;
    byte        info;

    nml = (byte *)(IOCB->fmtptr);
    len = *nml;
    nml += sizeof( char ) + len;
    for(;;) {
        len = *nml;
        if( len == 0 ) break;
        nml += sizeof( char ) + len;
        info = *nml;
        ++nml;
        if( _GetNMLSubScrs( info ) && ( info & NML_LG_ADV ) == 0 ) {
            nml += sizeof( unsigned_32 ) + _GetNMLSubScrs( info ) *
                                   ( sizeof( unsigned_32 ) + sizeof( int ) );
            if( _GetNMLType( info ) == PT_CHAR ) {
                nml += sizeof( int );
            }
        }
        *(byte *  *)nml = va_arg( args, byte  * );
        nml += sizeof( byte * );
    }
}
