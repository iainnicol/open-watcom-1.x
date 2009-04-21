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
		PUBLIC	BiosSystemConfiguration
;
; DECLARATION	int BiosSystemConfiguration( BIOSINFO **biosinfo );
;
PROC		BiosSystemConfiguration	WATCOM_C
		push	edx				; Save context
		push	ebx
		mov	edx,eax				; EDX points to pointer variable
		mov	ah,MISC_SYSTEM_CONFIG		; AH = function number
		;
		; Call BIOS
		;
IFDEF __ZDOSDRV__
		call	[DWORD BiosMisc]
ELSE
		int	BIOS_MISC
ENDIF
		mov	[edx],ebx			; Store pointer to system configuration
		pop	ebx				; Restore context
		pop	edx
		jmp	BiosReturnZero			; Process return code
ENDP
		END
