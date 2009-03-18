;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZBIOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	BiosReturnZero			: PROC
		PUBLIC	BiosStartEventWait_
;
; DECLARATION	int BiosStartEventWait( int *flag, unsigned microseconds );
;
PROC		BiosStartEventWait_	STDCALL
		push	ebx				; Save context
		mov	ebx,eax				; EBX points to flag
		mov	eax,MISC_EVENT_WAIT SHL 8	; AH = function number, AL = subfunction number
		;
		; Call BIOS
		;
IFDEF __ZDOSDRV__
		call	[DWORD BiosMisc]
ELSE
		int	BIOS_MISC
ENDIF
		pop	ebx				; Restore context
		jmp	BiosReturnZero			; Process return code
ENDP
		END
