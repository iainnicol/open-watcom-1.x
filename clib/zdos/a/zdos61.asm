;
; ZDOS run time library function.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	DosError			: PROC
		PUBLIC	DosCreateUniqueFile
;
; DECLARATION	int DosCreateUniqueFile(int attr, char *path, char *buffer);
;
PROC		DosCreateUniqueFile	WATCOM_C
		push	edi				; Save context
		push	ecx
		mov	ecx,eax				; ECX = file attributes
		mov	edi,ebx				; EDI points to buffer
		mov	ah,DOS_CREATE_UNIQUE_FILE	; AH = DOS function
		;
		; Call DOS services
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosApi]
ELSE
		int	DOS
ENDIF
		pop	ecx				; Restore context
		pop	edi
		jc	DosError			; Success ?
		ret					; Yes, return file handle
ENDP
		END
