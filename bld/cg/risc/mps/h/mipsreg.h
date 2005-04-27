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
* Description:  Register definitions for MIPS32 architecture.
*
****************************************************************************/


#ifndef HWREG_INCLUDED
#define HWREG_INCLUDED

#define HW_NEED_160
#include "cghwreg.h"

/*       Target dependent set of hardware registers available */

/* Due to some strange assumptions in the code generator about register
   names being tightly linked to the size of data contained therein, we
   have to give each register a unique name to correspond to each of the
   data types which can be held within it.
*/

/* Note that HW_Rxx registers are aliases for HW_Dxx on MIPS32. The x86
   register definition can be shared between 16-bit and 32-bit codegen
   because AX/EAX, DX/EDX etc. disambiguate between 16-bit and 32-bit
   registers. On MIPS the register size depends on the architecture,
   hence if we want to use generic register names wherever possible,
   we need to have different definition of HW_Rxx for MIPS32 vs. MIPS64.
*/

/* low bytes of the integer registers - byte 0 */
HW_DEFINE_SIMPLE( HW_B0,     0x0001U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_B1,     0x0002U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_B2,     0x0004U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_B3,     0x0008U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_B4,     0x0010U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_B5,     0x0020U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_B6,     0x0040U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_B7,     0x0080U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_B8,     0x0100U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_B9,     0x0200U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_B10,    0x0400U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_B11,    0x0800U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_B12,    0x1000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_B13,    0x2000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_B14,    0x4000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_B15,    0x8000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_B16,    0x0000U, 0x0001U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_B17,    0x0000U, 0x0002U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_B18,    0x0000U, 0x0004U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_B19,    0x0000U, 0x0008U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_B20,    0x0000U, 0x0010U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_B21,    0x0000U, 0x0020U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_B22,    0x0000U, 0x0040U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_B23,    0x0000U, 0x0080U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_B24,    0x0000U, 0x0100U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_B25,    0x0000U, 0x0200U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_B26,    0x0000U, 0x0400U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_B27,    0x0000U, 0x0800U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_B28,    0x0000U, 0x1000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_B29,    0x0000U, 0x2000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_B30,    0x0000U, 0x4000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_B31,    0x0000U, 0x8000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );

/* high bytes of lower word registers - byte 1 */
HW_DEFINE_SIMPLE( HW_hb0,    0x0000U, 0x0000U, 0x0001U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_hb1,    0x0000U, 0x0000U, 0x0002U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_hb2,    0x0000U, 0x0000U, 0x0004U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_hb3,    0x0000U, 0x0000U, 0x0008U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_hb4,    0x0000U, 0x0000U, 0x0010U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_hb5,    0x0000U, 0x0000U, 0x0020U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_hb6,    0x0000U, 0x0000U, 0x0040U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_hb7,    0x0000U, 0x0000U, 0x0080U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_hb8,    0x0000U, 0x0000U, 0x0100U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_hb9,    0x0000U, 0x0000U, 0x0200U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_hb10,   0x0000U, 0x0000U, 0x0400U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_hb11,   0x0000U, 0x0000U, 0x0800U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_hb12,   0x0000U, 0x0000U, 0x1000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_hb13,   0x0000U, 0x0000U, 0x2000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_hb14,   0x0000U, 0x0000U, 0x4000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_hb15,   0x0000U, 0x0000U, 0x8000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_hb16,   0x0000U, 0x0000U, 0x0000U, 0x0001U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_hb17,   0x0000U, 0x0000U, 0x0000U, 0x0002U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_hb18,   0x0000U, 0x0000U, 0x0000U, 0x0004U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_hb19,   0x0000U, 0x0000U, 0x0000U, 0x0008U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_hb20,   0x0000U, 0x0000U, 0x0000U, 0x0010U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_hb21,   0x0000U, 0x0000U, 0x0000U, 0x0020U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_hb22,   0x0000U, 0x0000U, 0x0000U, 0x0040U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_hb23,   0x0000U, 0x0000U, 0x0000U, 0x0080U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_hb24,   0x0000U, 0x0000U, 0x0000U, 0x0100U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_hb25,   0x0000U, 0x0000U, 0x0000U, 0x0200U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_hb26,   0x0000U, 0x0000U, 0x0000U, 0x0400U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_hb27,   0x0000U, 0x0000U, 0x0000U, 0x0800U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_hb28,   0x0000U, 0x0000U, 0x0000U, 0x1000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_hb29,   0x0000U, 0x0000U, 0x0000U, 0x2000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_hb30,   0x0000U, 0x0000U, 0x0000U, 0x4000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_hb31,   0x0000U, 0x0000U, 0x0000U, 0x8000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );

/* upper word of dword registers - bytes 2 and 3 */
HW_DEFINE_SIMPLE( HW_hw0,    0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0001U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_hw1,    0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0002U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_hw2,    0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0004U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_hw3,    0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0008U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_hw4,    0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0010U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_hw5,    0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0020U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_hw6,    0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0040U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_hw7,    0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0080U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_hw8,    0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0100U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_hw9,    0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0200U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_hw10,   0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0400U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_hw11,   0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0800U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_hw12,   0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x1000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_hw13,   0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x2000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_hw14,   0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x4000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_hw15,   0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x8000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_hw16,   0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0001U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_hw17,   0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0002U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_hw18,   0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0004U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_hw19,   0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0008U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_hw20,   0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0010U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_hw21,   0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0020U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_hw22,   0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0040U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_hw23,   0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0080U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_hw24,   0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0100U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_hw25,   0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0200U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_hw26,   0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0400U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_hw27,   0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0800U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_hw28,   0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x1000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_hw29,   0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x2000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_hw30,   0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x4000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_hw31,   0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x8000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );

/* upper dword of qword registers - bytes 4 through 7 */
HW_DEFINE_SIMPLE( HW_hd0,    0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0001U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_hd1,    0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0002U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_hd2,    0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0004U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_hd3,    0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0008U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_hd4,    0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0010U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_hd5,    0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0020U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_hd6,    0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0040U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_hd7,    0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0080U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_hd8,    0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0100U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_hd9,    0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0200U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_hd10,   0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0400U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_hd11,   0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0800U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_hd12,   0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x1000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_hd13,   0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x2000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_hd14,   0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x4000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_hd15,   0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x8000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_hd16,   0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0001U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_hd17,   0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0002U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_hd18,   0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0004U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_hd19,   0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0008U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_hd20,   0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0010U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_hd21,   0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0020U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_hd22,   0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0040U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_hd23,   0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0080U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_hd24,   0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0100U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_hd25,   0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0200U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_hd26,   0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0400U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_hd27,   0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0800U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_hd28,   0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x1000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_hd29,   0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x2000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_hd30,   0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x4000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_hd31,   0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x8000U, 0x0000U, 0x0000U );

/* floating point registers */
HW_DEFINE_SIMPLE( HW_F0,     0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0001U, 0x0000U );
HW_DEFINE_SIMPLE( HW_F1,     0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0002U, 0x0000U );
HW_DEFINE_SIMPLE( HW_F2,     0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0004U, 0x0000U );
HW_DEFINE_SIMPLE( HW_F3,     0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0008U, 0x0000U );
HW_DEFINE_SIMPLE( HW_F4,     0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0010U, 0x0000U );
HW_DEFINE_SIMPLE( HW_F5,     0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0020U, 0x0000U );
HW_DEFINE_SIMPLE( HW_F6,     0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0040U, 0x0000U );
HW_DEFINE_SIMPLE( HW_F7,     0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0080U, 0x0000U );
HW_DEFINE_SIMPLE( HW_F8,     0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0100U, 0x0000U );
HW_DEFINE_SIMPLE( HW_F9,     0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0200U, 0x0000U );
HW_DEFINE_SIMPLE( HW_F10,    0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0400U, 0x0000U );
HW_DEFINE_SIMPLE( HW_F11,    0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0800U, 0x0000U );
HW_DEFINE_SIMPLE( HW_F12,    0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x1000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_F13,    0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x2000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_F14,    0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x4000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_F15,    0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x8000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_F16,    0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0001U );
HW_DEFINE_SIMPLE( HW_F17,    0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0002U );
HW_DEFINE_SIMPLE( HW_F18,    0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0004U );
HW_DEFINE_SIMPLE( HW_F19,    0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0008U );
HW_DEFINE_SIMPLE( HW_F20,    0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0010U );
HW_DEFINE_SIMPLE( HW_F21,    0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0020U );
HW_DEFINE_SIMPLE( HW_F22,    0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0040U );
HW_DEFINE_SIMPLE( HW_F23,    0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0080U );
HW_DEFINE_SIMPLE( HW_F24,    0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0100U );
HW_DEFINE_SIMPLE( HW_F25,    0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0200U );
HW_DEFINE_SIMPLE( HW_F26,    0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0400U );
HW_DEFINE_SIMPLE( HW_F27,    0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0800U );
HW_DEFINE_SIMPLE( HW_F28,    0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x1000U );
HW_DEFINE_SIMPLE( HW_F29,    0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x2000U );
HW_DEFINE_SIMPLE( HW_F30,    0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x4000U );
HW_DEFINE_SIMPLE( HW_F31,    0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x8000U );


HW_DEFINE_SIMPLE( HW_FULL,   0xffffU, 0xffffU, 0xffffU, 0xffffU, 0xffffU, 0xffffU, 0xffffU, 0xffffU, 0xffffU, 0xffffU );
HW_DEFINE_SIMPLE( HW_UNUSED, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_EMPTY,  0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );
HW_DEFINE_SIMPLE( HW_SEGS,   0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U );

/*
 * HW_GPR - general purpose registers - can use for any integer ops
 * HW_IR - integer registers - above plus the R31 sink
 * HW_FPR - floating point registers
 */

#define HW_DEFINE_COMPOUND( x ) \
enum {                                                          \
                                                                \
/* word sized registers (halfword in MIPS parlance) */          \
HW_W0_##x = (hw_reg_part)(HW_B0_##x+HW_hb0_##x),                \
HW_W1_##x = (hw_reg_part)(HW_B1_##x+HW_hb1_##x),                \
HW_W2_##x = (hw_reg_part)(HW_B2_##x+HW_hb2_##x),                \
HW_W3_##x = (hw_reg_part)(HW_B3_##x+HW_hb3_##x),                \
HW_W4_##x = (hw_reg_part)(HW_B4_##x+HW_hb4_##x),                \
HW_W5_##x = (hw_reg_part)(HW_B5_##x+HW_hb5_##x),                \
HW_W6_##x = (hw_reg_part)(HW_B6_##x+HW_hb6_##x),                \
HW_W7_##x = (hw_reg_part)(HW_B7_##x+HW_hb7_##x),                \
HW_W8_##x = (hw_reg_part)(HW_B8_##x+HW_hb8_##x),                \
HW_W9_##x = (hw_reg_part)(HW_B9_##x+HW_hb9_##x),                \
HW_W10_##x = (hw_reg_part)(HW_B10_##x+HW_hb10_##x),             \
HW_W11_##x = (hw_reg_part)(HW_B11_##x+HW_hb11_##x),             \
HW_W12_##x = (hw_reg_part)(HW_B12_##x+HW_hb12_##x),             \
HW_W13_##x = (hw_reg_part)(HW_B13_##x+HW_hb13_##x),             \
HW_W14_##x = (hw_reg_part)(HW_B14_##x+HW_hb14_##x),             \
HW_W15_##x = (hw_reg_part)(HW_B15_##x+HW_hb15_##x),             \
HW_W16_##x = (hw_reg_part)(HW_B16_##x+HW_hb16_##x),             \
HW_W17_##x = (hw_reg_part)(HW_B17_##x+HW_hb17_##x),             \
HW_W18_##x = (hw_reg_part)(HW_B18_##x+HW_hb18_##x),             \
HW_W19_##x = (hw_reg_part)(HW_B19_##x+HW_hb19_##x),             \
HW_W20_##x = (hw_reg_part)(HW_B20_##x+HW_hb20_##x),             \
HW_W21_##x = (hw_reg_part)(HW_B21_##x+HW_hb21_##x),             \
HW_W22_##x = (hw_reg_part)(HW_B22_##x+HW_hb22_##x),             \
HW_W23_##x = (hw_reg_part)(HW_B23_##x+HW_hb23_##x),             \
HW_W24_##x = (hw_reg_part)(HW_B24_##x+HW_hb24_##x),             \
HW_W25_##x = (hw_reg_part)(HW_B25_##x+HW_hb25_##x),             \
HW_W26_##x = (hw_reg_part)(HW_B26_##x+HW_hb26_##x),             \
HW_W27_##x = (hw_reg_part)(HW_B27_##x+HW_hb27_##x),             \
HW_W28_##x = (hw_reg_part)(HW_B28_##x+HW_hb28_##x),             \
HW_W29_##x = (hw_reg_part)(HW_B29_##x+HW_hb29_##x),             \
HW_W30_##x = (hw_reg_part)(HW_B30_##x+HW_hb30_##x),             \
HW_W31_##x = (hw_reg_part)(HW_B31_##x+HW_hb31_##x),             \
                                                                \
/* doubleword sized registers (word in MIPS parlance) */        \
HW_D0_##x = (hw_reg_part)(HW_W0_##x+HW_hw0_##x),                \
HW_D1_##x = (hw_reg_part)(HW_W1_##x+HW_hw1_##x),                \
HW_D2_##x = (hw_reg_part)(HW_W2_##x+HW_hw2_##x),                \
HW_D3_##x = (hw_reg_part)(HW_W3_##x+HW_hw3_##x),                \
HW_D4_##x = (hw_reg_part)(HW_W4_##x+HW_hw4_##x),                \
HW_D5_##x = (hw_reg_part)(HW_W5_##x+HW_hw5_##x),                \
HW_D6_##x = (hw_reg_part)(HW_W6_##x+HW_hw6_##x),                \
HW_D7_##x = (hw_reg_part)(HW_W7_##x+HW_hw7_##x),                \
HW_D8_##x = (hw_reg_part)(HW_W8_##x+HW_hw8_##x),                \
HW_D9_##x = (hw_reg_part)(HW_W9_##x+HW_hw9_##x),                \
HW_D10_##x = (hw_reg_part)(HW_W10_##x+HW_hw10_##x),             \
HW_D11_##x = (hw_reg_part)(HW_W11_##x+HW_hw11_##x),             \
HW_D12_##x = (hw_reg_part)(HW_W12_##x+HW_hw12_##x),             \
HW_D13_##x = (hw_reg_part)(HW_W13_##x+HW_hw13_##x),             \
HW_D14_##x = (hw_reg_part)(HW_W14_##x+HW_hw14_##x),             \
HW_D15_##x = (hw_reg_part)(HW_W15_##x+HW_hw15_##x),             \
HW_D16_##x = (hw_reg_part)(HW_W16_##x+HW_hw16_##x),             \
HW_D17_##x = (hw_reg_part)(HW_W17_##x+HW_hw17_##x),             \
HW_D18_##x = (hw_reg_part)(HW_W18_##x+HW_hw18_##x),             \
HW_D19_##x = (hw_reg_part)(HW_W19_##x+HW_hw19_##x),             \
HW_D20_##x = (hw_reg_part)(HW_W20_##x+HW_hw20_##x),             \
HW_D21_##x = (hw_reg_part)(HW_W21_##x+HW_hw21_##x),             \
HW_D22_##x = (hw_reg_part)(HW_W22_##x+HW_hw22_##x),             \
HW_D23_##x = (hw_reg_part)(HW_W23_##x+HW_hw23_##x),             \
HW_D24_##x = (hw_reg_part)(HW_W24_##x+HW_hw24_##x),             \
HW_D25_##x = (hw_reg_part)(HW_W25_##x+HW_hw25_##x),             \
HW_D26_##x = (hw_reg_part)(HW_W26_##x+HW_hw26_##x),             \
HW_D27_##x = (hw_reg_part)(HW_W27_##x+HW_hw27_##x),             \
HW_D28_##x = (hw_reg_part)(HW_W28_##x+HW_hw28_##x),             \
HW_D29_##x = (hw_reg_part)(HW_W29_##x+HW_hw29_##x),             \
HW_D30_##x = (hw_reg_part)(HW_W30_##x+HW_hw30_##x),             \
HW_D31_##x = (hw_reg_part)(HW_W31_##x+HW_hw31_##x),             \
                                                                \
/* quadword sized registers (doubleword in MIPS parlance) */    \
HW_Q2_##x = (hw_reg_part)(HW_D2_##x+HW_hd2_##x),                \
HW_Q4_##x = (hw_reg_part)(HW_D4_##x+HW_hd4_##x),                \
HW_Q6_##x = (hw_reg_part)(HW_D6_##x+HW_hd6_##x),                \
HW_Q8_##x = (hw_reg_part)(HW_D8_##x+HW_hd8_##x),                \
HW_Q10_##x = (hw_reg_part)(HW_D10_##x+HW_hd10_##x),             \
HW_Q12_##x = (hw_reg_part)(HW_D12_##x+HW_hd12_##x),             \
HW_Q14_##x = (hw_reg_part)(HW_D14_##x+HW_hd14_##x),             \
HW_Q16_##x = (hw_reg_part)(HW_D16_##x+HW_hd16_##x),             \
HW_Q18_##x = (hw_reg_part)(HW_D18_##x+HW_hd18_##x),             \
HW_Q20_##x = (hw_reg_part)(HW_D20_##x+HW_hd20_##x),             \
HW_Q22_##x = (hw_reg_part)(HW_D22_##x+HW_hd22_##x),             \
HW_Q24_##x = (hw_reg_part)(HW_D12_##x+HW_hd24_##x),             \
                                                                \
HW_R0_##x = (hw_reg_part)(HW_W0_##x+HW_hw0_##x),                \
HW_R1_##x = (hw_reg_part)(HW_W1_##x+HW_hw1_##x),                \
HW_R2_##x = (hw_reg_part)(HW_W2_##x+HW_hw2_##x),                \
HW_R3_##x = (hw_reg_part)(HW_W3_##x+HW_hw3_##x),                \
HW_R4_##x = (hw_reg_part)(HW_W4_##x+HW_hw4_##x),                \
HW_R5_##x = (hw_reg_part)(HW_W5_##x+HW_hw5_##x),                \
HW_R6_##x = (hw_reg_part)(HW_W6_##x+HW_hw6_##x),                \
HW_R7_##x = (hw_reg_part)(HW_W7_##x+HW_hw7_##x),                \
HW_R8_##x = (hw_reg_part)(HW_W8_##x+HW_hw8_##x),                \
HW_R9_##x = (hw_reg_part)(HW_W9_##x+HW_hw9_##x),                \
HW_R10_##x = (hw_reg_part)(HW_W10_##x+HW_hw10_##x),             \
HW_R11_##x = (hw_reg_part)(HW_W11_##x+HW_hw11_##x),             \
HW_R12_##x = (hw_reg_part)(HW_W12_##x+HW_hw12_##x),             \
HW_R13_##x = (hw_reg_part)(HW_W13_##x+HW_hw13_##x),             \
HW_R14_##x = (hw_reg_part)(HW_W14_##x+HW_hw14_##x),             \
HW_R15_##x = (hw_reg_part)(HW_W15_##x+HW_hw15_##x),             \
HW_R16_##x = (hw_reg_part)(HW_W16_##x+HW_hw16_##x),             \
HW_R17_##x = (hw_reg_part)(HW_W17_##x+HW_hw17_##x),             \
HW_R18_##x = (hw_reg_part)(HW_W18_##x+HW_hw18_##x),             \
HW_R19_##x = (hw_reg_part)(HW_W19_##x+HW_hw19_##x),             \
HW_R20_##x = (hw_reg_part)(HW_W20_##x+HW_hw20_##x),             \
HW_R21_##x = (hw_reg_part)(HW_W21_##x+HW_hw21_##x),             \
HW_R22_##x = (hw_reg_part)(HW_W22_##x+HW_hw22_##x),             \
HW_R23_##x = (hw_reg_part)(HW_W23_##x+HW_hw23_##x),             \
HW_R24_##x = (hw_reg_part)(HW_W24_##x+HW_hw24_##x),             \
HW_R25_##x = (hw_reg_part)(HW_W25_##x+HW_hw25_##x),             \
HW_R26_##x = (hw_reg_part)(HW_W26_##x+HW_hw26_##x),             \
HW_R27_##x = (hw_reg_part)(HW_W27_##x+HW_hw27_##x),             \
HW_R28_##x = (hw_reg_part)(HW_W28_##x+HW_hw28_##x),             \
HW_R29_##x = (hw_reg_part)(HW_W29_##x+HW_hw29_##x),             \
HW_R30_##x = (hw_reg_part)(HW_W30_##x+HW_hw30_##x),             \
HW_R31_##x = (hw_reg_part)(HW_W31_##x+HW_hw31_##x),             \
                                                                \
/* double precision floating point registers */                 \
HW_FD0_##x = (hw_reg_part)(HW_F0_##x+HW_F1_##x),                \
HW_FD2_##x = (hw_reg_part)(HW_F2_##x+HW_F3_##x),                \
HW_FD4_##x = (hw_reg_part)(HW_F4_##x+HW_F5_##x),                \
HW_FD6_##x = (hw_reg_part)(HW_F6_##x+HW_F7_##x),                \
HW_FD8_##x = (hw_reg_part)(HW_F8_##x+HW_F9_##x),                \
HW_FD10_##x = (hw_reg_part)(HW_F10_##x+HW_F11_##x),             \
HW_FD12_##x = (hw_reg_part)(HW_F12_##x+HW_F13_##x),             \
HW_FD14_##x = (hw_reg_part)(HW_F14_##x+HW_F15_##x),             \
HW_FD16_##x = (hw_reg_part)(HW_F16_##x+HW_F17_##x),             \
HW_FD18_##x = (hw_reg_part)(HW_F18_##x+HW_F19_##x),             \
HW_FD20_##x = (hw_reg_part)(HW_F20_##x+HW_F21_##x),             \
HW_FD22_##x = (hw_reg_part)(HW_F22_##x+HW_F23_##x),             \
HW_FD24_##x = (hw_reg_part)(HW_F24_##x+HW_F25_##x),             \
HW_FD26_##x = (hw_reg_part)(HW_F26_##x+HW_F27_##x),             \
HW_FD28_##x = (hw_reg_part)(HW_F28_##x+HW_F29_##x),             \
HW_FD30_##x = (hw_reg_part)(HW_F30_##x+HW_F31_##x),             \
                                                                \
                                                                \
HW_QREGS_##x  = (hw_reg_part)(HW_Q2_##x+HW_Q4_##x+HW_Q6_##x+HW_Q8_##x+\
        HW_Q10_##x+HW_Q12_##x+HW_Q14_##x+HW_Q16_##x+HW_Q18_##x+ \
        HW_Q20_##x+HW_Q22_##x+HW_Q24_##x ),                     \
                                                                \
HW_DREGS_##x  = (hw_reg_part)(HW_D0_##x+HW_D1_##x+HW_D2_##x+HW_D3_##x+\
        HW_D4_##x+HW_D5_##x+HW_D6_##x+HW_D7_##x+HW_D8_##x+HW_D9_##x+\
        HW_D10_##x+HW_D11_##x+HW_D12_##x+HW_D13_##x+HW_D14_##x+HW_D15_##x+\
        HW_D16_##x+HW_D17_##x+HW_D18_##x+HW_D19_##x+HW_D20_##x+HW_D21_##x+\
        HW_D22_##x+HW_D23_##x+HW_D24_##x+HW_D25_##x+HW_D26_##x+HW_D27_##x+\
        HW_D28_##x+HW_D29_##x+HW_D30_##x ),                     \
                                                                \
HW_WREGS_##x  = (hw_reg_part)(HW_W0_##x+HW_W1_##x+HW_W2_##x+HW_W3_##x+\
        HW_W4_##x+HW_W5_##x+HW_W6_##x+HW_W7_##x+HW_W8_##x+HW_W9_##x+\
        HW_W10_##x+HW_W11_##x+HW_W12_##x+HW_W13_##x+HW_W14_##x+HW_W15_##x+\
        HW_W16_##x+HW_W17_##x+HW_W18_##x+HW_W19_##x+HW_W20_##x+HW_W21_##x+\
        HW_W22_##x+HW_W23_##x+HW_W24_##x+HW_W25_##x+HW_W26_##x+HW_W27_##x+\
        HW_W28_##x+HW_W29_##x+HW_W30_##x ),                     \
                                                                \
HW_BREGS_##x  = (hw_reg_part)(HW_B0_##x+HW_B1_##x+HW_B2_##x+HW_B3_##x+\
        HW_B4_##x+HW_B5_##x+HW_B6_##x+HW_B7_##x+HW_B8_##x+HW_B9_##x+\
        HW_B10_##x+HW_B11_##x+HW_B12_##x+HW_B13_##x+HW_B14_##x+HW_B15_##x+\
        HW_B16_##x+HW_B17_##x+HW_B18_##x+HW_B19_##x+HW_B20_##x+HW_B21_##x+\
        HW_B22_##x+HW_B23_##x+HW_B24_##x+HW_B25_##x+HW_B26_##x+HW_B27_##x+\
        HW_B28_##x+HW_B29_##x+HW_B30_##x ),                         \
                                                                    \
HW_FPR_##x  = (hw_reg_part)(HW_F0_##x+HW_F1_##x+HW_F2_##x+HW_F3_##x+\
        HW_F4_##x+HW_F5_##x+HW_F6_##x+HW_F7_##x+HW_F8_##x+HW_F9_##x+\
        HW_F10_##x+HW_F11_##x+HW_F12_##x+HW_F13_##x+HW_F14_##x+HW_F15_##x+\
        HW_F16_##x+HW_F17_##x+HW_F18_##x+HW_F19_##x+HW_F20_##x+HW_F21_##x+\
        HW_F22_##x+HW_F23_##x+HW_F24_##x+HW_F25_##x+HW_F26_##x+HW_F27_##x+\
        HW_F28_##x+HW_F29_##x+HW_F30_##x+HW_F31_##x ),              \
                                                                    \
HW_DFPR_##x = (hw_reg_part)(HW_FD0_##x+HW_FD2_##x+HW_FD4_##x+HW_FD6_##x+\
        HW_FD8_##x+HW_FD10_##x+HW_FD12_##x+HW_FD14_##x+HW_FD16_##x+HW_FD18_##x+\
        HW_FD20_##x+HW_FD22_##x+HW_FD24_##x+HW_FD26_##x+HW_F28_##x+HW_F30_##x ),\
                                                                    \
HW__COMPOUND_END_##x                                                \
}

HW_ITER( HW_DEFINE_COMPOUND );

HW_DEFINE_GLOBAL_CONST( HW_EMPTY );
HW_DEFINE_GLOBAL_CONST( HW_R0 );
HW_DEFINE_GLOBAL_CONST( HW_R1 );
HW_DEFINE_GLOBAL_CONST( HW_R2 );
HW_DEFINE_GLOBAL_CONST( HW_R3 );
HW_DEFINE_GLOBAL_CONST( HW_R4 );
HW_DEFINE_GLOBAL_CONST( HW_R5 );
HW_DEFINE_GLOBAL_CONST( HW_R6 );
HW_DEFINE_GLOBAL_CONST( HW_R7 );
HW_DEFINE_GLOBAL_CONST( HW_R8 );
HW_DEFINE_GLOBAL_CONST( HW_R9 );
HW_DEFINE_GLOBAL_CONST( HW_R10 );
HW_DEFINE_GLOBAL_CONST( HW_R11 );
HW_DEFINE_GLOBAL_CONST( HW_R12 );
HW_DEFINE_GLOBAL_CONST( HW_R13 );
HW_DEFINE_GLOBAL_CONST( HW_R14 );
HW_DEFINE_GLOBAL_CONST( HW_R15 );
HW_DEFINE_GLOBAL_CONST( HW_R16 );
HW_DEFINE_GLOBAL_CONST( HW_R17 );
HW_DEFINE_GLOBAL_CONST( HW_R18 );
HW_DEFINE_GLOBAL_CONST( HW_R19 );
HW_DEFINE_GLOBAL_CONST( HW_R20 );
HW_DEFINE_GLOBAL_CONST( HW_R21 );
HW_DEFINE_GLOBAL_CONST( HW_R22 );
HW_DEFINE_GLOBAL_CONST( HW_R23 );
HW_DEFINE_GLOBAL_CONST( HW_R24 );
HW_DEFINE_GLOBAL_CONST( HW_R25 );
HW_DEFINE_GLOBAL_CONST( HW_R26 );
HW_DEFINE_GLOBAL_CONST( HW_R27 );
HW_DEFINE_GLOBAL_CONST( HW_R28 );
HW_DEFINE_GLOBAL_CONST( HW_R29 );
HW_DEFINE_GLOBAL_CONST( HW_R30 );
HW_DEFINE_GLOBAL_CONST( HW_R31 );

HW_DEFINE_GLOBAL_CONST( HW_Q2 );
HW_DEFINE_GLOBAL_CONST( HW_Q4 );
HW_DEFINE_GLOBAL_CONST( HW_Q6 );
HW_DEFINE_GLOBAL_CONST( HW_Q8 );
HW_DEFINE_GLOBAL_CONST( HW_Q10 );
HW_DEFINE_GLOBAL_CONST( HW_Q12 );
HW_DEFINE_GLOBAL_CONST( HW_Q14 );
HW_DEFINE_GLOBAL_CONST( HW_Q16 );
HW_DEFINE_GLOBAL_CONST( HW_Q18 );
HW_DEFINE_GLOBAL_CONST( HW_Q20 );
HW_DEFINE_GLOBAL_CONST( HW_Q22 );
HW_DEFINE_GLOBAL_CONST( HW_Q24 );

HW_DEFINE_GLOBAL_CONST( HW_D0 );
HW_DEFINE_GLOBAL_CONST( HW_D1 );
HW_DEFINE_GLOBAL_CONST( HW_D2 );
HW_DEFINE_GLOBAL_CONST( HW_D3 );
HW_DEFINE_GLOBAL_CONST( HW_D4 );
HW_DEFINE_GLOBAL_CONST( HW_D5 );
HW_DEFINE_GLOBAL_CONST( HW_D6 );
HW_DEFINE_GLOBAL_CONST( HW_D7 );
HW_DEFINE_GLOBAL_CONST( HW_D8 );
HW_DEFINE_GLOBAL_CONST( HW_D9 );
HW_DEFINE_GLOBAL_CONST( HW_D10 );
HW_DEFINE_GLOBAL_CONST( HW_D11 );
HW_DEFINE_GLOBAL_CONST( HW_D12 );
HW_DEFINE_GLOBAL_CONST( HW_D13 );
HW_DEFINE_GLOBAL_CONST( HW_D14 );
HW_DEFINE_GLOBAL_CONST( HW_D15 );
HW_DEFINE_GLOBAL_CONST( HW_D16 );
HW_DEFINE_GLOBAL_CONST( HW_D17 );
HW_DEFINE_GLOBAL_CONST( HW_D18 );
HW_DEFINE_GLOBAL_CONST( HW_D19 );
HW_DEFINE_GLOBAL_CONST( HW_D20 );
HW_DEFINE_GLOBAL_CONST( HW_D21 );
HW_DEFINE_GLOBAL_CONST( HW_D22 );
HW_DEFINE_GLOBAL_CONST( HW_D23 );
HW_DEFINE_GLOBAL_CONST( HW_D24 );
HW_DEFINE_GLOBAL_CONST( HW_D25 );
HW_DEFINE_GLOBAL_CONST( HW_D26 );
HW_DEFINE_GLOBAL_CONST( HW_D27 );
HW_DEFINE_GLOBAL_CONST( HW_D28 );
HW_DEFINE_GLOBAL_CONST( HW_D29 );
HW_DEFINE_GLOBAL_CONST( HW_D30 );
HW_DEFINE_GLOBAL_CONST( HW_D31 );

HW_DEFINE_GLOBAL_CONST( HW_W0 );
HW_DEFINE_GLOBAL_CONST( HW_W1 );
HW_DEFINE_GLOBAL_CONST( HW_W2 );
HW_DEFINE_GLOBAL_CONST( HW_W3 );
HW_DEFINE_GLOBAL_CONST( HW_W4 );
HW_DEFINE_GLOBAL_CONST( HW_W5 );
HW_DEFINE_GLOBAL_CONST( HW_W6 );
HW_DEFINE_GLOBAL_CONST( HW_W7 );
HW_DEFINE_GLOBAL_CONST( HW_W8 );
HW_DEFINE_GLOBAL_CONST( HW_W9 );
HW_DEFINE_GLOBAL_CONST( HW_W10 );
HW_DEFINE_GLOBAL_CONST( HW_W11 );
HW_DEFINE_GLOBAL_CONST( HW_W12 );
HW_DEFINE_GLOBAL_CONST( HW_W13 );
HW_DEFINE_GLOBAL_CONST( HW_W14 );
HW_DEFINE_GLOBAL_CONST( HW_W15 );
HW_DEFINE_GLOBAL_CONST( HW_W16 );
HW_DEFINE_GLOBAL_CONST( HW_W17 );
HW_DEFINE_GLOBAL_CONST( HW_W18 );
HW_DEFINE_GLOBAL_CONST( HW_W19 );
HW_DEFINE_GLOBAL_CONST( HW_W20 );
HW_DEFINE_GLOBAL_CONST( HW_W21 );
HW_DEFINE_GLOBAL_CONST( HW_W22 );
HW_DEFINE_GLOBAL_CONST( HW_W23 );
HW_DEFINE_GLOBAL_CONST( HW_W24 );
HW_DEFINE_GLOBAL_CONST( HW_W25 );
HW_DEFINE_GLOBAL_CONST( HW_W26 );
HW_DEFINE_GLOBAL_CONST( HW_W27 );
HW_DEFINE_GLOBAL_CONST( HW_W28 );
HW_DEFINE_GLOBAL_CONST( HW_W29 );
HW_DEFINE_GLOBAL_CONST( HW_W30 );
HW_DEFINE_GLOBAL_CONST( HW_W31 );

HW_DEFINE_GLOBAL_CONST( HW_B0 );
HW_DEFINE_GLOBAL_CONST( HW_B1 );
HW_DEFINE_GLOBAL_CONST( HW_B2 );
HW_DEFINE_GLOBAL_CONST( HW_B3 );
HW_DEFINE_GLOBAL_CONST( HW_B4 );
HW_DEFINE_GLOBAL_CONST( HW_B5 );
HW_DEFINE_GLOBAL_CONST( HW_B6 );
HW_DEFINE_GLOBAL_CONST( HW_B7 );
HW_DEFINE_GLOBAL_CONST( HW_B8 );
HW_DEFINE_GLOBAL_CONST( HW_B9 );
HW_DEFINE_GLOBAL_CONST( HW_B10 );
HW_DEFINE_GLOBAL_CONST( HW_B11 );
HW_DEFINE_GLOBAL_CONST( HW_B12 );
HW_DEFINE_GLOBAL_CONST( HW_B13 );
HW_DEFINE_GLOBAL_CONST( HW_B14 );
HW_DEFINE_GLOBAL_CONST( HW_B15 );
HW_DEFINE_GLOBAL_CONST( HW_B16 );
HW_DEFINE_GLOBAL_CONST( HW_B17 );
HW_DEFINE_GLOBAL_CONST( HW_B18 );
HW_DEFINE_GLOBAL_CONST( HW_B19 );
HW_DEFINE_GLOBAL_CONST( HW_B20 );
HW_DEFINE_GLOBAL_CONST( HW_B21 );
HW_DEFINE_GLOBAL_CONST( HW_B22 );
HW_DEFINE_GLOBAL_CONST( HW_B23 );
HW_DEFINE_GLOBAL_CONST( HW_B24 );
HW_DEFINE_GLOBAL_CONST( HW_B25 );
HW_DEFINE_GLOBAL_CONST( HW_B26 );
HW_DEFINE_GLOBAL_CONST( HW_B27 );
HW_DEFINE_GLOBAL_CONST( HW_B28 );
HW_DEFINE_GLOBAL_CONST( HW_B29 );
HW_DEFINE_GLOBAL_CONST( HW_B30 );
HW_DEFINE_GLOBAL_CONST( HW_B31 );

HW_DEFINE_GLOBAL_CONST( HW_F0 );
HW_DEFINE_GLOBAL_CONST( HW_F1 );
HW_DEFINE_GLOBAL_CONST( HW_F2 );
HW_DEFINE_GLOBAL_CONST( HW_F3 );
HW_DEFINE_GLOBAL_CONST( HW_F4 );
HW_DEFINE_GLOBAL_CONST( HW_F5 );
HW_DEFINE_GLOBAL_CONST( HW_F6 );
HW_DEFINE_GLOBAL_CONST( HW_F7 );
HW_DEFINE_GLOBAL_CONST( HW_F8 );
HW_DEFINE_GLOBAL_CONST( HW_F9 );
HW_DEFINE_GLOBAL_CONST( HW_F10 );
HW_DEFINE_GLOBAL_CONST( HW_F11 );
HW_DEFINE_GLOBAL_CONST( HW_F12 );
HW_DEFINE_GLOBAL_CONST( HW_F13 );
HW_DEFINE_GLOBAL_CONST( HW_F14 );
HW_DEFINE_GLOBAL_CONST( HW_F15 );
HW_DEFINE_GLOBAL_CONST( HW_F16 );
HW_DEFINE_GLOBAL_CONST( HW_F17 );
HW_DEFINE_GLOBAL_CONST( HW_F18 );
HW_DEFINE_GLOBAL_CONST( HW_F19 );
HW_DEFINE_GLOBAL_CONST( HW_F20 );
HW_DEFINE_GLOBAL_CONST( HW_F21 );
HW_DEFINE_GLOBAL_CONST( HW_F22 );
HW_DEFINE_GLOBAL_CONST( HW_F23 );
HW_DEFINE_GLOBAL_CONST( HW_F24 );
HW_DEFINE_GLOBAL_CONST( HW_F25 );
HW_DEFINE_GLOBAL_CONST( HW_F26 );
HW_DEFINE_GLOBAL_CONST( HW_F27 );
HW_DEFINE_GLOBAL_CONST( HW_F28 );
HW_DEFINE_GLOBAL_CONST( HW_F29 );
HW_DEFINE_GLOBAL_CONST( HW_F30 );
HW_DEFINE_GLOBAL_CONST( HW_F31 );

HW_DEFINE_GLOBAL_CONST( HW_FD0 );
HW_DEFINE_GLOBAL_CONST( HW_FD2 );
HW_DEFINE_GLOBAL_CONST( HW_FD4 );
HW_DEFINE_GLOBAL_CONST( HW_FD6 );
HW_DEFINE_GLOBAL_CONST( HW_FD8 );
HW_DEFINE_GLOBAL_CONST( HW_FD10 );
HW_DEFINE_GLOBAL_CONST( HW_FD12 );
HW_DEFINE_GLOBAL_CONST( HW_FD14 );
HW_DEFINE_GLOBAL_CONST( HW_FD16 );
HW_DEFINE_GLOBAL_CONST( HW_FD18 );
HW_DEFINE_GLOBAL_CONST( HW_FD20 );
HW_DEFINE_GLOBAL_CONST( HW_FD22 );
HW_DEFINE_GLOBAL_CONST( HW_FD24 );
HW_DEFINE_GLOBAL_CONST( HW_FD26 );
HW_DEFINE_GLOBAL_CONST( HW_FD28 );
HW_DEFINE_GLOBAL_CONST( HW_FD30 );

// TODO: Shouldn't this be much higher? Like 32?
#define MAX_POSSIBLE_REG        8

#endif
