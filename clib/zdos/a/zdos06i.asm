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
		PUBLIC	DosDirectConsoleInput
;
; DECLARATION	int DosDirectConsoleInput( void );
;
PROC		DosDirectConsoleInput	WATCOM_C
		push	edx				; Save context
		mov	dl,-1				; DL = direct input flag
		mov	ah,DOS_DIRECT_CONSOLEIO		; AH = DOS function
		;
		; Call DOS services
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosApi]
ELSE
		int	DOS
ENDIF
		pop	edx				; Restore context
		jc	DosError			; Success ?
		jnz	SHORT @@Exit			; Character available ?
		xor	al,al				; No, clear AL
@@Exit:		movzx	eax,al				; Yes, EAX = character or 0
		ret
ENDP
		END
