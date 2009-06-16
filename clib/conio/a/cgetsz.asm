;
; ZDOS run time library function.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		PUBLIC	cgets
;
; DECLARATION	char *cgets( char * buffer );
;
PROC		cgets			WATCOM_C
		USES	edx
		mov	edx,eax				; EDX points to buffer
		mov	ah,DOS_CONSOLE_BUFFERED_INPUT	; AH = DOS function
		;
		; Call DOS services
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosApi]
ELSE
		int	DOS
ENDIF
		movzx	eax,[BYTE edx]			; EAX = length of buffer
		mov	[BYTE edx + eax + 2],0		; Zero terminate buffer
		lea	eax,[edx + 2]			; EAX points to input string
		ret
ENDP
		END
