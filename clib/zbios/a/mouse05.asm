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
		PUBLIC	BiosInitializeMouse
;
; DECLARATION	int BiosInitializeMouse( int packetsize );
;
PROC		BiosInitializeMouse	WATCOM_C
		push	ebx				; Save context
		mov	bh,al				; BH = packet size
		mov	eax,MISC_MOUSE_SERVICES SHL 8 +\; AH = function number
			    MOUSE_INITIALIZE		; AL = subfunction number
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
