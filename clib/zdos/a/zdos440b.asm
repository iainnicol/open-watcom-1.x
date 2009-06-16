;
; ZDOS run time library function.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	DosReturnZero			: PROC
		PUBLIC	DosIoctlSetRetryCount
;
; DECLARATION	int DosIoctlSetRetryCount( int pause, int retries );
;
PROC		DosIoctlSetRetryCount	WATCOM_C
		push	ecx				; Save context
		mov	ecx,eax				; ECX = pause between retries
		mov	eax,DOS_DEVICE_CONTROL SHL 8 + \; AH = DOS function number, AL = subfunction number
			    IOCTL_SET_SHARING_RETRY_COUNT
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
