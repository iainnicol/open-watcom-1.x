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


extern void DwarfDebugInit( void );
extern dbg_type DwarfDebugType( TYPE type );
extern dbg_type DwarfDebugSym( SYMBOL sym );
extern void DwarfDebugFini( void );
extern void DwarfDebugEmit( void );
extern void DwarfDebugGenSymbol( SYMBOL sym, boolean scoped );
extern void DwarfDebugMemberFunc( SYMBOL func, SYMBOL this_sym );
extern void DwarfDebugNameSpaceEnclosed( SYMBOL sym );
extern uint_32 DwarfDebugOffset( uint_32 handle );
extern void DwarfSymDebugGenSymbol( SYMBOL sym, boolean scoped, boolean by_ref );
