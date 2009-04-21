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
		PUBLIC	DosSetFileTimeStamp
;
; DECLARATION	int DosSetFileTimeStamp( int handle, unsigned int time );
;
PROC		DosSetFileTimeStamp	WATCOM_C
		push	ecx				; Save context
		push	ebx
		mov	ebx,eax				; EBX = file handle
		mov	ecx,edx				; ECX = new time stamp
		;
		; Get DOS function numbers in AH and AL
		;
		mov	eax,DOS_GET_SET_FILE_TIME_STAMP SHL 8 + 1
		;
		; Call DOS services
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosApi]
ELSE
		int	DOS
ENDIF
		pop	ebx				; Restore context
		pop	ecx
		jmp	DosReturnZero			; Process return code
ENDP
		END
