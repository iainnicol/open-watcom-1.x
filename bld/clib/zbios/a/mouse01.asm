;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZBIOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	BiosReturnAL			: PROC
		PUBLIC	BiosResetMouse_
;
; DECLARATION	int BiosResetMouse( void );
;
PROC		BiosResetMouse_		STDCALL
		push	ebx				; Save context
		mov	eax,MISC_MOUSE_SERVICES SHL 8 +\; AH = function number
			    MOUSE_RESET			; AL = subfunction number
		;
		; Call BIOS
		;
IFDEF __ZDOSDRV__
		call	[DWORD BiosMisc]
ELSE
		int	BIOS_MISC
ENDIF
		mov	al,bh				; AL = mouse ID
		pop	ebx				; Restore context
		jmp	BiosReturnAL			; Process return code
ENDP
		END
