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
		PUBLIC	DosLockFileRegion
;
; DECLARATION	int DosLockFileRegion( unsigned length, unsigned offset,
;		                       int handle );
;
PROC		DosLockFileRegion	WATCOM_C
		push	ecx				; Save context
		mov	ecx,eax				; ECX = region length
		;
		; Get DOS function numbers in AH and AL
		;
		mov	eax,DOS_LOCK_UNLOCK_FILE_REGION SHL 8
		;
		; Call DOS services
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosApi]
ELSE
		int	DOS
ENDIF
		pop	ecx				; Restore context
		jmp	DosReturnZero			; Process return code
ENDP
		END
