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
		PUBLIC	DosReadFile
;
; DECLARATION	int DosReadFile( int bytes, void *buffer, int handle );
;
PROC		DosReadFile		WATCOM_C
		push	ecx				; Save context
		mov	ecx,eax				; ECX = number of bytes to read
		mov	ah,DOS_READ_FILE		; AH = DOS function number
		;
		; Call DOS services
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosApi]
ELSE
		int	DOS
ENDIF
		pop	ecx				; Restore context
		jc	DosError			; Success ?
		ret					; Yes, return number of bytes read
ENDP
		END
