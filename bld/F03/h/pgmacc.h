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


#if ( _OPT_CG == _OFF ) && ( _TARGET == _8086 )

#include <string.h>
#define pgm_memget      _fmemcpy
#define pgm_memput      _fmemcpy
#define pgm_memcpy      _fmemcpy
#define pgm_memset      _fmemset
#define pgm_strlen      _fstrlen
#define pgm_memicmp     _fmemicmp
#define pgm_strget(d,s) (char *)_fstrcpy(d,s)
extern  void            pgm_BToHS(char PGM *,uint,char *);

#else

#include <string.h>

#define pgm_memget      memcpy
#define pgm_memput      memcpy
#define pgm_memcpy      memcpy
#define pgm_memset      memset
#define pgm_BToHS       BToHS
#define pgm_memicmp     memicmp
#define pgm_strlen      strlen

#endif
