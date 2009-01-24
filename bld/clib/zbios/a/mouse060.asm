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
		PUBLIC	BiosMouseStatus_
;
; DECLARATION	int BiosMouseStatus( MOUSE_INFO *info );
;
PROC		BiosMouseStatus_	STDCALL
		push	esi				; Save context
		push	edx
		push	ecx
		push	ebx
		mov	esi,eax				; ESI points to MOUSE_STATUS block
		xor	bh,bh				; BH = get mouse status indicator
		mov	eax,MISC_MOUSE_SERVICES SHL 8 +\; AH = function number
			    MOUSE_STATUS		; AL = subfunction number
		;
		; Call BIOS
		;
IFDEF __ZDOSDRV__
		call	[DWORD BiosMisc]
ELSE
		int	BIOS_MISC
ENDIF
		;
		; Store mouse status in callers buffer
		;
		mov	[(MOUSE_INFO esi).Status],bl
		mov	[(MOUSE_INFO esi).Resolution],cl
		mov	[(MOUSE_INFO esi).Rate],dl
		pop	ebx				; Restore context
		pop	ecx
		pop	edx
		pop	esi
		jmp	BiosReturnZero			; Process return code
ENDP
		END
