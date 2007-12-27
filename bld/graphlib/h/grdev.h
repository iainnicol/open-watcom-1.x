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
* Description:  Graphics device function vectors.
*
****************************************************************************/


#pragma pack(push, 1);
typedef struct graphics_device {
    short           (*init)( short );                           // initialization
    void            (*finish)( void );                          // finish up device
    void            (*set)( void );                             // set device
    void            (*reset)( void );                           // reset device
    void            (*setup)( short, short, short );            // setup routine
    void pascal     (near *up)( void );                         // move up routine (ASM)
    void pascal     (near *left)( void );                       // move left routine
    void pascal     (near *down)( void );                       // move down routine
    void pascal     (near *right)( void );                      // move right routine
    void            (near *plot[4])( char far *, int, int );    // plot-replace
    short           (near *getdot)( char far *, int, int );     // get pixel color
    void            (near *zap)( char far *, int,
                                 int, int, int );               // zap routine
    void            (near *fill)( char far *, int,
                                  int, int, int );              // fill style routine
    void            (near *pixcopy)( char far *, char far *,
                                     int, int, int );           // copy pixels
    void            (near *readrow)( char far *, char far *,
                                     int, int, int );           // read a row of pixels
    short pascal    (near *scanleft)( char far *, int, int,
                                      int, int, int );          // left scan in paint
    short pascal    (near *scanright)( char far *, int, int,
                                       int, int, int );         // right scan in paint
} gr_device;
#pragma pack (pop);