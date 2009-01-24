;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ERRNO.INC'
		CODESEG
		EXTRN	getenv_				: PROC
		EXTRN	putenv_				: PROC
		EXTRN	strlen_				: PROC
		EXTRN	malloc_				: PROC
		EXTRN	free_				: PROC
		EXTRN	__set_errno_			: PROC
		PUBLIC	setenv_
;
; DECLARATION	int setenv( const char *name, const char *value, int ow );
;
PROC		setenv_			STDCALL
		USES	edi,esi,ecx,ebp
		test	[_Envptr],-1			; Environment buffer available ?
		jz	@@Error				; No, error
		mov	esi,eax				; Yes, save pointer to name in ESI
		mov	edi,edx				; Save pointer to value in EDI
		call	getenv_				; Find environment variable
		or	eax,eax				; Environment variable found ?
		jz	SHORT @@GetBuffer		; No, ignore overwrite flag
		or	ebx,ebx				; Overwrite flag active ?
		jnz	SHORT @@OverWrite		; Yes, we need to overwrite current value
		mov	ebp,eax				; No, save pointer current value in EBP
		call	strlen_				; Get length of current assignment
		jmp	SHORT @@GetBuffer		; Allocate buffer
@@OverWrite:	xor	eax,eax				; Clear EAX
@@GetBuffer:	push	edi				; Save context
		push	esi
		push	eax
		lea	ebx,[eax + 2]			; EBX = initial size of buffer needed
		mov	eax,esi				; EAX points to name
		call	strlen_				; Get length of name
		add	ebx,eax				; Add to total length
		xchg	eax,edi				; EAX points to value string, EDI = length of name
		call	strlen_				; Get length of value string
		add	eax,ebx				; EAX = total space needed
		call	malloc_				; Allocate space for buffer
		mov	ebx,eax				; EBX points to buffer
		mov	ecx,edi				; ECX = length of name
		pop	eax				; Restore context
		pop	esi
		pop	edi
		or	ebx,ebx				; Allocation succeeded ?
		jz	SHORT @@Error			; No, error
		mov	edx,ebx				; Yes, save copy in EDX
		xchg	edx,edi				; EDX points to new value string, EDI points to buffer
		rep	movsb				; Copy name
		mov	ecx,eax				; ECX = number of bytes to copy from previous value
		mov	al,'='				; We need an assignment operator
		stosb					; Add assignment operator
		or	ecx,ecx				; Append to previous value ?
		jz	SHORT @@AppendNew		; No, append new value
		mov	esi,ebp				; Yes, ESI points to previous setting
		rep	movsb				; Append previous setting
@@AppendNew:	mov	esi,edx				; ESI points to new value
@@CopyNextChar:	lodsb					; Get next character in AL
		stosb					; Store in buffer and advance pointer
		or	al,al				; End of string ?
		jnz	@@CopyNextChar			; No, copy next character
		mov	eax,ebx				; Yes, EAX points to buffer
		call	putenv_				; Update environment
		xchg	eax,ebx				; EAX points to buffer, EBX = return status from putenv_
		call	free_				; Free buffer
		mov	eax,ebx				; Restore return status
@@Exit:		ret
@@Error:	mov	eax,ENOMEM			; EAX = error code
		call	__set_errno_			; Set _errno
		mov	eax,-1				; EAX = return value
		jmp	@@Exit
ENDP
		UDATASEG
		EXTRN	C _Envptr			: DWORD
		END
