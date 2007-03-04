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
* Description:  Mainline for WATFOR-77.
*
****************************************************************************/


#include "ftnstd.h"
#include "global.h"
#include "cpopt.h"
#include "progsw.h"
#include "errcod.h"
#include "fmemmgr.h"
#include "bglobal.h"

#include "boot77.h"

#include "inout.h"

extern  void            SDInitIO(void);
extern  void            FiniProcCmd(void);
extern  void            CLE(void);
extern  void            InitOptions(void);
extern  void            CmdOption(char *);
extern  void            InitMacroProcessor(void);
extern  void            FiniMacroProcessor(void);
extern  void            SetDefaultOpts(void);
extern  void            MsgBuffer(uint,char *,...);
extern  void            ShowOptions(char *);

extern  char            *UsageLines[];

static int  ProcName(char * );


void    InitCompMain() {
//======================

    FMemInit();
    InitCompile();
    ProgSw |= PS_FIRST_COMPILE;
    InitMacroProcessor();
    SetDefaultOpts();
    LastColumn = LAST_COL;
}


void    FiniCompMain() {
//======================

    FiniMacroProcessor();
    FMemFini();
}


int     CompMain( char *parm ) {
//==============================

    if( parm != NULL ){
        Compile( parm );
        parm = NULL;
    }
    return( RetCode );
}


static  bool    ProcCmd() {
//=======================================

	char	*opt_array[MAX_OPTIONS+1] = {NULL};
   
   //TODO: find out what buffer might be good for
   // otherwise just remove parameter
   //buffer = buffer
    RetCode = RET_BADCMDLINE;
    
    //opt_array[0] = NULL;
    RetCode      = ProcName(SrcName);
    if( RetCode == RET_SUCCESSFUL ) {
        ProcOpts( opt_array );
    }
    return( RetCode == RET_SUCCESSFUL );
}


void    Compile() {
//===============================

    InitCompile();
    if(ProcCmd())
    {
        // initialize permanent i/o buffers after memory has been
        // initialized
        InitMemIO();
        // Compile Link and Execute (historic name!)
        CLE();
        if( ( NumErrors != 0 ) && ( RetCode == RET_SUCCESSFUL ) )
        {
            RetCode = NumErrors ;
        }
    } else
    {
        // error in command line
        ShowUsage();
        if( RetCode == RET_REQSYNTAX ) {
            // A specific request for syntax (WATFOR77 ?) should return 0.
            RetCode = RET_SUCCESSFUL;
        }
    }
    FiniComIO();
    FiniProcCmd();
    FiniCompile();
}


#if _CPU == 8086
  #define _CmpName "wfc"
#else
  #define _CmpName "wfc386"
#endif



void    ShowUsage() {
//===================

    char        buff[LIST_BUFF_SIZE+1];

    GetBanner( buff );
    TOutNL( buff );
    GetCopyright( buff );
    TOutNL( buff );
    GetTrademark( buff );
    TOutNL( buff );
    GetMoreInfo( buff );
    TOutNL( buff );
    TOutNL( "" );
    MsgBuffer( MS_USAGE_LINE, buff, _CmpName );
    TOutNL( buff );
    TOutNL( "" );
    ShowOptions( buff );
}


char    *SkipBlanks( char *ptr ) {
//================================

    while( ( *ptr == ' ' ) || ( *ptr == '\f' ) || ( *ptr == '\t' ) ) {
        ptr++;
    }
    return( ptr );
}


static  void    InitComVars() {
//=============================

    ProgSw    = PS_DONT_GENERATE; // so we get command line errors
    NumErrors = 0;
    NumWarns  = 0;
    NumExtens = 0;
    SrcRecNum = 0;
}


void    InitCompile() {
//=====================

// Initialize compiler i/o before we process the command line so we can
// issue errors to the error file. i/o buffers are temporary until memory
// has been initialized.

    if( ProgSw & PS_FIRST_COMPILE ) return; // done in InitCompMain() 1st time
    InitComIO();
    InitComVars();
}


void    FiniCompile() {
//=====================

    ProgSw &= ~PS_FIRST_COMPILE;
}

////////////////////////////////////
//
//  Check existence of src file name
//
////////////////////////////////////
static int  ProcName(char *srcName)
{
	if( NULL == srcName )
		return RET_NOFILENAME;

   if( NULLCHAR == *srcName )
	   return RET_NOFILENAME;

   if( '?' == *srcName  ) 
      return RET_REQSYNTAX;
    
   return RET_SUCCESSFUL ;
}


/////////////////////////////////////
//
// Process compilation options
//
/////////////////////////////////////
void  ProcOpts( char **opt_array )
{
   char *tempOption;  

   InitOptions();
   NewOptions = Options;

   // scan through command line options
   for(tempOption = *opt_array; tempOption != NULL; ++opt_array)
   {
      CmdOption( *opt_array );
   }

   Options = NewOptions;
}
