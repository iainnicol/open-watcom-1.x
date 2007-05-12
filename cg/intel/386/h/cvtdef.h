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
* Description:  386 type conversion table info
*
****************************************************************************/


/*    enum      address */
pick( C2TO1,	C2to1 )
pick( C4TO1,	C4to1 )
pick( C4TO2,	C4to2 )
pick( C8TO2,	C8to4 )
pick( C8TO4,	C8to4 )
pick( S1TO2,	S1to2 )
pick( S1TO4,	S1to4 )
pick( S1TO8,	S1to8 )
pick( S2TO4,	S2to4 )
pick( S2TO8,	S2to8 )
pick( S4TO8,	S4to8 )
pick( Z1TO2,	Z1to2 )
pick( Z1TO4,	Z1to4 )
pick( Z1TO8,	Z1to8 )
pick( Z2TO4,	Z2to4 )
pick( Z2TO8,	Z2to8 )
pick( Z4TO8,	Z4to8 )
pick( EXT_PT,	ExtPT )
pick( CHP_PT,	ChpPT )
pick( PTTOI8,	PTtoI8 )
pick( I8TOPT,	I8toPT )
