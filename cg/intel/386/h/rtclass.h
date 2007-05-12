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
* Description:  Runtime support routines list for 386. 
*
****************************************************************************/


/*        NB entries up until OK must match typclass.wif */

typedef enum {
        CU1,
        CI1,
        CU2,
        CI2,
        CU4,
        CI4,
        CU8,
        CI8,
        CCP,
        CPT,
        CFS,
        CFD,
        CFL,
        OK,

#undef  pick
#define pick(enum,address) enum,
#include "cvtdef.h"

        LAST_CONV_TABLE = I8TOPT,

#undef  pick
#define pick(enum,name,op,class,left,right,result) enum,
#include "rtidef.h"

        FPOK,
        U4F,
        FU4,
        BAD
} rt_class;

#define ROUNDING        C_S_4
#define BEG_RTNS        C_U4_S
/*  beginning of runtime calls */
#define BEG_ARITH       RT_FSA
