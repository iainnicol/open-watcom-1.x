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
		PUBLIC	DosGetFileTimeStamp
;
; DECLARATION	int DosGetFileTimeStamp( int handle, unsigned int *time );
;
PROC		DosGetFileTimeStamp	WATCOM_C
		push	ecx				; Save context
		push	ebx
		mov	ebx,eax				; EBX = file handle
		;
		; Get DOS function numbers in AH and AL
		;
		mov	eax,DOS_GET_SET_FILE_TIME_STAMP SHL 8
		;
		; Call DOS services
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosApi]
ELSE
		int	DOS
ENDIF
		mov	[edx],ecx			; Update callers time variable
		pop	ebx				; Restore context
		pop	ecx
		jmp	DosReturnZero			; Process return code
ENDP
		END
