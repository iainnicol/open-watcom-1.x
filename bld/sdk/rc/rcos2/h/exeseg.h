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
* Description:  NE segment table manipulation prototypes and structures.
*
****************************************************************************/


#ifndef EXESEG_INCLUDED
#define EXESEG_INCLUDED

#include "rctypes.h"

typedef struct SegTable {
    uint_16             NumSegs;
    segment_record *    Segments;   /* array of size NumSegs */
} SegTable;

typedef enum {
    CPSEG_OK = 0,
    CPSEG_SEG_TOO_BIG,
    CPSEG_ERROR
} CpSegRc;

extern int AllocAndReadSegTables( int *err_code );
extern int AllocAndReadOS2SegTables( int *err_code );
extern uint_32 ComputeSegmentSize( int handle, SegTable *, int shift_count );
extern CpSegRc CopySegments( uint_16 sect2mask, uint_16 sect2bits, bool sect2 );

#endif
