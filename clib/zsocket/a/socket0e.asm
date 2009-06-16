;
; ZDOS run time library function.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		INCLUDE	'SOCKET.INC'
		INCLUDE	'ZSOCKET.INC'
		CODESEG
		EXTRN	SocketError			: PROC
		PUBLIC	setsockopt
;
; DECLARATION	int setsockopt( int s, int level, int optname, char *optval,
;                               int optlen );
;
PROC		setsockopt		WATCOM_C
		ARG	s : DWORD, level : DWORD, optname : DWORD, \
			optval : DWORD, optlen : DWORD
		USES	edi
		cmp	[optlen],4			; Valid option length ?
		jnz	SHORT @@BadValue		; No, error
		mov	edi,ecx				; Yes, EDI points to optval
		shl	eax,2				; EAX = socket handle
		mov	ecx,ebx				; ECX optname
		mov	ebx,eax				; EBX = socket handle
		xor	al,al				; Assume SOL_SOCKET level
		cmp	edx,SOL_SOCKET			; Level = SOL_SOCKET ?
		jz	SHORT @@SetOption		; Yes, set option
		inc	al				; Assume SOL_TCP (IPPROTO_TCP)
		cmp	edx,SOL_TCP			; Level = SOL_TCP ?
		jz	SHORT @@SetOption		; Yes, set option
		inc	al				; Assume SOL_IP (IPPROTO_IP)
		cmp	edx,SOL_IP			; Level = SOL_IP ?
		jnz	SHORT @@BadValue		; No, error
@@SetOption:	mov	ah,SOCKET_SET_OPTION		; Yes, AH = function number
		mov	edx,[edi]			; EDX = option value
		;
		; Set option
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosSocketDriver]
ELSE
		int	SOCKET
ENDIF
		jc	SHORT @@Error			; Error ?
		mov	[edi],eax			; No, store option value in callers variable
		xor	eax,eax				; Clear EAX
@@Exit:		ret
@@BadValue:	mov	eax,SOCKET_INVALID_TYPE		; EAX = socket error code
@@Error:	call	SocketError			; Process error code
		jmp	@@Exit				; We are done
ENDP
		END
