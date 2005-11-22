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


#include "ftnstd.h"
#include "global.h"
#include "opr.h"

#include <stdio.h>

static  char    *Opn[] = {
    "OPN_PHI",
    "OPN_NAM",
    "OPN_LIT",
    "OPN_HOL",
    "OPN_LGL",
    "OPN_INT",
    "OPN_REA",
    "OPN_DBL"
    "OPN_EXT"
    "OPN_OCT"
    "OPN_HEX"
    "OPN_FMT"
};


static char *Typ(byte typ) {
//===========================
   switch(typ) {
      case TY_LOGICAL_1 :     return( "TY_LOGICAL_1 " );
      case TY_LOGICAL   :     return( "TY_LOGICAL   " );
      case TY_INTEGER_1 :     return( "TY_INTEGER_1 " ); 
      case TY_INTEGER_2 :     return( "TY_INTEGER_2 " ); 
      case TY_INTEGER   :     return( "TY_INTEGER   " ); 
      case TY_REAL      :     return( "TY_REAL      " ); 
      case TY_DOUBLE    :     return( "TY_DOUBLE    " ); 
      case TY_TRUE_EXTENDED:  return( "TY_T_EXTENDED" );  
   // case TY_EXTENDED  :     return( "TY_EXTENDED  " ); same as TY_DOUBLE  
      case TY_COMPLEX   :     return( "TY_COMPLEX   " );  
      case TY_DCOMPLEX  :     return( "TY_DCOMPLEX  " ); 
      case TY_TRUE_XCOMPLEX:  return( "TY_T_XCOMPLEX" ); 
   // case TY_XCOMPLEX  :     return( "TY_XCOMPLEX  " ); same as TY_DCOMPLEX
      case TY_CHAR      :     return( "TY_CHAR      " ); 
      case TY_STRUCTURE :     return( "TY_STRUCTURE " ); 
      case TY_UNION     :     return( "TY_UNION     " ); 
      case TY_HEX       :     return( "TY_HEX       " );  
      case TY_NO_TYPE   :     return( "TY_NO_TYPE   " );
      default           :     return( "UNKNOWN      " );
   }
  
 }


static  char    *Opr( byte opr ) {
//================================

    switch( opr ) {
    case OPR_PHI :
        return( "OPR_PHI " );
    case OPR_TRM :
        return( "OPR_TRM " );
    case OPR_FBR :
        return( "OPR_FBR " );
    case OPR_LBR :
        return( "OPR_LBR " );
    case OPR_COM :
        return( "OPR_COM " );
    case OPR_COL :
        return( "OPR_COL " );
    case OPR_EQU :
        return( "OPR_EQU " );
    case OPR_EQV :
        return( "OPR_EQV " );
    case OPR_NEQV :
        return( "OPR_NEQV" );
    case OPR_OR :
        return( "OPR_OR  " );
    case OPR_AND :
        return( "OPR_AND " );
    case OPR_NOT :
        return( "OPR_NOT " );
    case OPR_EQ :
        return( "OPR_EQ  " );
    case OPR_NE :
        return( "OPR_NE  " );
    case OPR_LT :
        return( "OPR_LT  " );
    case OPR_GE :
        return( "OPR_GE  " );
    case OPR_LE :
        return( "OPR_LE  " );
    case OPR_GT :
        return( "OPR_GT  " );
    case OPR_PLS :
        return( "OPR_PLS " );
    case OPR_MIN :
        return( "OPR_MIN " );
    case OPR_MUL :
        return( "OPR_MUL " );
    case OPR_DIV :
        return( "OPR_DIV " );
    case OPR_EXP :
        return( "OPR_EXP " );
    case OPR_CAT :
        return( "OPR_CAT " );
    case OPR_RBR :
        return( "OPR_RBR " );
    case OPR_DPT :
        return( "OPR_DPT " );
    case OPR_AST :
        return( "OPR_AST " );
    case OPR_FLD :
        return( "OPR_FLD " );
    default :
        return( "UNKNOWN " );
    }
}


void    DumpLex() {
//=================
// Dump the Current Internal Text list to stdout
//

itnode *dumpNode = CITNode;
    LLine();
    while( dumpNode != NULL ) {
        Node(dumpNode);
        LLine();
        dumpNode = dumpNode->link;
    }
}


static  void    Node(itnode * dumpNode ) {
//======================

    printf( "|  %s  |  %s  |  %s  |\n", Opr( dumpNode->opr ), Opn[ dumpNode->opn.ds ],
       Typ(dumpNode->typ));
}


static  void    LLine() {
//=======================

    printf( "+-----------+------------+\n" );
}
