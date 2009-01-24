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
		PUBLIC	DosUnlockFileRegion_
;
; DECLARATION	int DosUnlockFileRegion( unsigned length, unsigned offset,
;		                         int handle );
;
PROC		DosUnlockFileRegion_	STDCALL
		push	ecx				; Save context
		mov	ecx,eax				; ECX = region length
		;
		; Get DOS function numbers in AH and AL
		;
		mov	eax,DOS_LOCK_UNLOCK_FILE_REGION SHL 8 + 1
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
