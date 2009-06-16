;
; ZDOS run time library function.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		INCLUDE	'ZIPV4.INC'
		CODESEG
		EXTRN	DosError			: PROC
		PUBLIC	DosSocketLocalAddress
;
; DECLARATION	int DosSocketLocalAddress( unsigned *ip, int *port,
;                                          unsigned handle );
;
PROC		DosSocketLocalAddress	WATCOM_C
		push	edi				; Save context
		push	esi
		push	ecx
		mov	esi,edx				; ESI points to port variable
		mov	edi,eax				; EDI points to ip variable
		mov	ah,SOCKET_LOCAL_ADDRESS		; AH = function number
		;
		; Get local IP address and port
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosSocketDriver]
ELSE
		int	SOCKET
ENDIF
		mov	[esi],ecx			; Update callers port variable
		mov	[edi],edx			; Update caller ip variable
		pop	ecx				; Restore context
		pop	esi
		pop	edi
		jc	DosError			; Success ?
		ret
ENDP
		END
