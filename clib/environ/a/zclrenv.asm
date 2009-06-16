;
; ZDOS run time library function.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		PUBLIC	clearenv
;
; DECLARATION	int clearenv( void );
;
PROC		clearenv		WATCOM_C
		push	edi				; Save context
		xor	eax,eax				; Clear EAX
		or	eax,[_Envptr]			; Environment buffer available ?
		jz	SHORT @@Exit			; No, we are done
		mov	ah,DOS_RESET_ENVIRONMENT	; Yes, AH = DOS function
		;
		; Call DOS services
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosApi]
ELSE
		int	DOS
ENDIF
		mov	edi,[environ]			; EDI = pointer to environment array
		xor	eax,eax				; Clear EAX
		add	edi,4				; EDI = new sentinel position
		mov	[_Envlength],eax		; Clear environment length
		stosd					; Mark end of array
		mov	[_STACKLOW],edi			; Save new stack low value
		mov	[BYTE _Envlength],2		; Environment length = 2
@@Exit:		pop	edi				; Restore context
		ret
ENDP
		UDATASEG
		EXTRN	WATCOM_C _Envptr		: DWORD
		EXTRN	WATCOM_C _Envlength		: DWORD
		EXTRN	WATCOM_C environ		: DWORD
		EXTRN	WATCOM_C _STACKLOW		: DWORD
		END
