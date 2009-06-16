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
		PUBLIC	DosSocketAccept
;
; DECLARATION	int DosSocketAccept( unsigned listenhandle,
;		                     unsigned *newhandle );
;
PROC		DosSocketAccept		WATCOM_C
		push	ebx				; Save context
		mov	ebx,eax				; EBX = listen handle
		mov	ah,SOCKET_ACCEPT		; AH = function number
		;
		; Accept a new connection
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosSocketDriver]
ELSE
		int	SOCKET
ENDIF
		pop	ebx				; Restore context
		jc	DosError			; Success ?
		mov	[edx],eax			; Yes, save handle in callers variable
		xor	eax,eax				; Clear EAX
		ret
ENDP
		END
