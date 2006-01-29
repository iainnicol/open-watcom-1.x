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

//#include "targdef.h"
// Define character sets:
// ======================

#define _ASCII  0

// Define CPU targets ( _CPU macro ):
// ==================================

#define _AXP    1
#define _PPC    2
#define _SPARC  3
#define _MIPS   4
#define _80286  286     // >= 286 running 16-bit protected-mode ( OS/2 or DOS/16M )
#define _80386  386     // >= 386 running 32-bit
#define _8086   8086    // >= 8086 machine 16-bit real-mode

#define _INTEL_CPU      ( _CPU == 8086 || _CPU == 386 )
#define _RISC_CPU       ( _CPU == _AXP || _CPU == _PPC || _CPU == _MIPS )


// Define feature switch settings:
// ===============================

//#define _OFF   0 temporary changed to 2
#define _OFF   2
#define _ON    1


//#include "sdmacro.h"
#include "switch.h"

// Define multi-language constants:
// ================================

#if !defined( MSG_LANG_SPACING )
#define MSG_LANG_SPACING 16000
#endif
#include "wreslang.h"
