;
; ZDOS run time library function.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		INCLUDE	'ERRNO.INC'
		CODESEG
		EXTRN	InitializeEnvironment		: PROC
		EXTRN	WATCOM_C __set_errno		: PROC
		PUBLIC	putenv
;
; DECLARATION	int putenv( const char * string );
;
PROC		putenv			WATCOM_C
		USES	edi,esi,edx,ecx
		test	[_Envptr],-1			; Environment buffer available ?
		jz	SHORT @@Error			; No, error
		mov	edx,eax				; Yes, EDX points to string
		mov	ah,DOS_SET_ENVIRONMENT_VARIABLE	; AH = DOS function
		;
		; Call DOS services
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosApi]
ELSE
		int	DOS
ENDIF
		jc	SHORT @@Error			; Success ?
		call	InitializeEnvironment		; Yes, reinitialize environment
		xor	eax,eax				; Clear EAX
		ret
@@Error:	mov	eax,ENOMEM			; EAX = error code
		call	__set_errno			; Set _errno
		mov	eax,-1				; EAX = return value
		ret
ENDP
		UDATASEG
	     	EXTRN	WATCOM_C _Envptr		: DWORD
		END
