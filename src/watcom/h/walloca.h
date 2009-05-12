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
* Description:  Include appropriate header defining alloca().
*
****************************************************************************/


#ifndef WALLOCA_H_INCLUDED
#define WALLOCA_H_INCLUDED

#if defined(__WATCOMC__) || defined(_MSC_VER)
    #include <malloc.h>
#else
  #if defined(__SUNPRO_C)
    #include <alloca.h>
  #else
    #include <stdlib.h>
  #endif
  /* __alloca() in the Watcom runtime is a special version with no stack
   * checking. It is needed in some code built for DOS and similar funny
   * environments, but on UNIX we can safely map it to alloca().
   */
  #define __alloca      alloca
#endif

#endif
