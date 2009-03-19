;*****************************************************************************
;*
;*                            Open Watcom Project
;*
;*    Portions Copyright (c) 1983-2002 Sybase, Inc. All Rights Reserved.
;*
;*  ========================================================================
;*
;*    This file contains Original Code and/or Modifications of Original
;*    Code as defined in and that are subject to the Sybase Open Watcom
;*    Public License version 1.0 (the 'License'). You may not use this file
;*    except in compliance with the License. BY USING THIS FILE YOU AGREE TO
;*    ALL TERMS AND CONDITIONS OF THE LICENSE. A copy of the License is
;*    provided with the Original Code and Modifications, and is also
;*    available at www.sybase.com/developer/opensource.
;*
;*    The Original Code and all software distributed under the License are
;*    distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
;*    EXPRESS OR IMPLIED, AND SYBASE AND ALL CONTRIBUTORS HEREBY DISCLAIM
;*    ALL SUCH WARRANTIES, INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF
;*    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR
;*    NON-INFRINGEMENT. Please see the License for the specific language
;*    governing rights and limitations under the License.
;*
;*  ========================================================================
;*
;* Description:  WHEN YOU FIGURE OUT WHAT THIS FILE DOES, PLEASE
;*               DESCRIBE IT HERE!
;*
;*****************************************************************************
		IDEAL
		P486
		MODEL	USE32 SMALL
		DOSSEG
		CODESEG
		EXTRN	TrapInit_			: PROC
		EXTRN	TrapRequest_			: PROC
		EXTRN	TrapFini_			: PROC
		PUBLIC	__do_exit_with_msg__
		DB	'TRAP'
		DD	TrapInit_
		DD	TrapRequest_
		DD	TrapFini_
Message		DB	'Can not be run from the command line$'
PROC		Start
		mov	edx,OFFSET Message		; Display message
		mov	ah,09h
		int	21h
		mov	eax,4ffh			; Exit to ZDOS
		int	21h
LABEL		__do_exit_with_msg__	PROC
		jmp	__do_exit_with_msg__
ENDP
		STACK	0
		END	Start
