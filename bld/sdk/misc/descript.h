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
* Description:  Intel x86 descriptor prototype.
*
****************************************************************************/


#ifndef __DESCRIPT_INCLUDED__
#define __DESCRIPT_INCLUDED__

typedef struct {
    unsigned short  limit_15_0;
    unsigned short  base_15_0;
    char            base_23_16;
    char            available:1;
    char            writeable_or_readable:1;
    char            expanddown_or_conforming:1;
    char            type:2;
    char            dpl:2;
    char            present:1;
    char            limit_19_16:4;
    char            avl:1;
    char            reserved:1;
    char            big_or_default:1;
    char            granularity:1;
    char            base_31_24;
} descriptor;

#define GET_DESC_BASE( desc ) ((DWORD) (desc).base_15_0 + \
                ((DWORD) (desc).base_23_16 << 16L ) + \
                ((DWORD) (desc).base_31_24 << 24L ))

#define GET_DESC_LIMIT( desc ) \
                ( (desc).granularity ? \
                (( ( (DWORD) (desc).limit_15_0 + \
                ((DWORD) (desc).limit_19_16<< 16L))  \
                        << 12L) + 0xfffL ) \
                : \
                ((DWORD) (desc).limit_15_0 + \
                ((DWORD) (desc).limit_19_16<< 16L)) \
                )
#endif