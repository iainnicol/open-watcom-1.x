;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		INCLUDE	'ZIPV4.INC'
		CODESEG
		EXTRN	DosError			: PROC
		PUBLIC	DosSocketIoctl
;
; DECLARATION	int DosSocketIoctl( unsigned command, unsigned *argument,
;		                    unsigned handle );
;
PROC		DosSocketIoctl		WATCOM_C
		push	esi				; Save context
		push	ecx
		mov	esi,edx				; ESI points to argument
		mov	ecx,eax				; ECX = command
		mov	edx,[esi]			; EDX = argument
		mov	ah,SOCKET_IOCTL			; AH = function number
		;
		; Do IOCTL function
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosSocketDriver]
ELSE
		int	SOCKET
ENDIF
		mov	edx,esi				; EDX points to argument variable
		pop	ecx				; Restore context
		pop	esi
		jc	DosError			; Success ?
		mov	[edx],eax			; Yes, update callers variable
		xor	eax,eax				; Clear EAX
		ret
ENDP
		END
