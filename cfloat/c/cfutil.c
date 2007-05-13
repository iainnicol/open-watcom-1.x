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


#include "cfloat.h"

extern  long_double  CFToF(cfloat*);

/*
 * For now we can just cheese out - if we ever port to a non IEEE machine
 * this will have to be abstracted.
 */
extern  void    CFCnvTarget( cfloat *f, flt *buffer, int size ) {
/****************************************************************/

    long_double  ld;

    ld = CFToF( f );
    switch( size ) {
    case 4:
#ifdef _LONG_DOUBLE_
        __LDFS( (long_double _WCNEAR *)&ld, (void _WCNEAR *)&buffer->sngl );
#else
        buffer->sngl = (float)ld.value;
#endif
        break;
    case 8:
#ifdef _LONG_DOUBLE_
        __LDFD( (long_double _WCNEAR *)&ld, (void _WCNEAR *)&buffer->dble );
#else
        buffer->dble = (double)ld.value;
#endif
        break;
    case 10:
#ifdef _LONG_DOUBLE_
        buffer->ldble = ld;
#else
        buffer->ldble = (double)ld.value;
#endif
        break;
    }
}
