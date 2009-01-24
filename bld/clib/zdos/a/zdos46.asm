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
		PUBLIC	DosForceDuplicateHandle_
;
; DECLARATION	int DosForceDuplicateHandle( int filehandle, int redirecthandle );
;
PROC		DosForceDuplicateHandle_ STDCALL
		push	ecx				; Save context
		push	ebx
		mov	ebx,eax				; EBX = file or device handle
		mov	ecx,edx				; ECX = handle to redirect
		mov	ah,DOS_FORCE_DUPLICATE_HANDLE	; AH = DOS function number
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
