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
		PUBLIC	BiosProcessTermination
;
; DECLARATION	int BiosProcessTermination( int process );
;
PROC		BiosProcessTermination	WATCOM_C
		push	ebx				; Save context
		mov	ebx,eax				; EBX = process ID
		mov	ah,MISC_PROCESS_TERMINATE	; AH = function number
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
