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

#include <string.h>
#include <stdio.h>

static  void    Record(void);
static  void    Node(itnode * dumpNode, int count);
static  void    DLine(void);
static  void    SLine(void);

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


static const char   sline[] = "+------------+-----------+-------------+\n"; 
static const char   dline[] = "+============+===========+=============+\n"; 
//static const size_t slength = sizeof(sline) -1;

static char *Typ(byte typ) {
//===========================
   switch(typ) {
      case FT_LOGICAL_1 :     return( "FT_LOGICAL_1 " );
      case FT_LOGICAL   :     return( "FT_LOGICAL   " );
      case FT_INTEGER_1 :     return( "FT_INTEGER_1 " ); 
      case FT_INTEGER_2 :     return( "FT_INTEGER_2 " ); 
      case FT_INTEGER   :     return( "FT_INTEGER   " ); 
      case FT_REAL      :     return( "FT_REAL      " ); 
      case FT_DOUBLE    :     return( "FT_DOUBLE    " ); 
      case FT_TRUE_EXTENDED:  return( "FT_T_EXTENDED" );  
   // case FT_EXTENDED  :     return( "FT_EXTENDED  " ); same as FT_DOUBLE  
      case FT_COMPLEX   :     return( "FT_COMPLEX   " );  
      case FT_DCOMPLEX  :     return( "FT_DCOMPLEX  " ); 
      case FT_TRUE_XCOMPLEX:  return( "FT_T_XCOMPLEX" ); 
   // case FT_XCOMPLEX  :     return( "FT_XCOMPLEX  " ); same as FT_DCOMPLEX
      case FT_CHAR      :     return( "FT_CHAR      " ); 
      case FT_STRUCTURE :     return( "FT_STRUCTURE " ); 
      case FT_UNION     :     return( "FT_UNION     " ); 
      case FT_HEX       :     return( "FT_HEX       " );  
      case FT_NO_TYPE   :     return( "FT_NO_TYPE   " );
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


///////////////////////////////////////////////////
//
// dump a list of internal text nodes onto the screen
//
///////////////////////////////////////////////////
void    DumpLex(itnode * node)
{   int count = 0;

    itnode *dumpNode = node;
    Record();
    while( dumpNode != NULL ) {
        Node(dumpNode, ++count);
        dumpNode = dumpNode->link;
    }
}


static  void    Node(itnode * dumpNode, int count )
{
    char operand[50] = {0};
    int i;
    int endlength ;

    if (dumpNode == NULL) return;

    DLine();
    printf("+ Address: 0x%p  (%5d)         +\n", dumpNode, count);
    DLine();
    printf("+ Link:    0x%p                  +\n", dumpNode->link);
    printf("+ Arglist: 0x%p                  +\n", dumpNode->list);
    SLine();
   
    printf( "|  %s  |  %s  |%s|\n", 
            Opr( dumpNode->opr ),
            Opn[ dumpNode->opn.ds ],
            Typ(dumpNode->typ));
    printf("|  %4d      |  %4d     |   %4d      |\n",
            dumpNode->opr, dumpNode->opn.ds, dumpNode->typ);
    SLine();
    printf("| Flags: %#06x                        |\n", dumpNode->flags); 
    
    
    if (dumpNode->opnd == NULL){
        operand[0] ='\0';
    } else {
     //   int i;
        for (i = 0; i < dumpNode->opnd_size; ++i){
             operand[i] = *(dumpNode->opnd +i);
        }
        operand[dumpNode->opnd_size] = '\0';
    }
    printf("| Operand: %-s", operand);
   
   
    endlength = strlen(sline) - 13 - dumpNode->opnd_size;
    for (i = 0; i < endlength ;++i){
        printf(" ");
    }
    printf("|\n");

    SLine();
 }


static  void    SLine(void) {
//=======================

    printf( sline );
}

static  void    DLine(void) {
//=======================

    printf( dline);
}

static void Record(void) {
//========================== 
    DLine();
    printf("|| Line : %-8d                    ||\n", SrcRecNum);
  //  DLine();
}
