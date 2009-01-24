;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	DosReturnZero			: PROC
		PUBLIC	DosCommand_
;
; DECLARATION	void DosCommand( char *commandline );
;
PROC		DosCommand_		STDCALL
		push	esi				; Save context
		mov	esi,eax				; ESI points to command line
		;
		; Execute command line
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosCommand]
ELSE
		int	COMMAND
		pop	esi				; Restore context
		jmp	DosReturnZero			; Process return code
ENDIF
ENDP
		END
