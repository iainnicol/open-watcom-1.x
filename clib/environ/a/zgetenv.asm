;
; ZDOS run time library function.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		CODESEG
		EXTRN	WATCOM_C strlen			: PROC
		EXTRN	WATCOM_C strnicmp		: PROC
		PUBLIC	getenv
;
; DECLARATION	char *getenv ( const char *name );
;
PROC		getenv			WATCOM_C
		USES	edi,esi,edx,ecx,ebx
		mov	edi,[_Envptr]			; EDI points to environment
		or	edi,edi				; Environment block available ?
		jz	SHORT @@Exit			; No, we are done
		mov	esi,eax				; Yes, save pointer to string in ESI
		call	strlen				; Get string length
		mov	ebx,eax				; EBX = string length
		mov	ecx,[environ]			; ECX points to environment pointer array
@@GetString:	mov	edi,[ecx]			; EDI = pointer to next environment string
		or	edi,edi				; End of array ?
		jz	SHORT @@Exit			; Yes, we are done
		mov	eax,esi				; No, EAX points to callers string
		mov	edx,edi				; EDX points to environment string
		push	ecx				; Save context
		push	ebx
		call	strnicmp			; Compare strings
		pop	ebx				; Restore context
		pop	ecx
		or	eax,eax				; Equal ?
		jnz	SHORT @@NextString		; No, get next string
		lea	edi,[edi + ebx + 1]		; Yes, assume a match
		cmp	[BYTE edi - 1],'='		; Really a match ?
		jz	SHORT @@Exit			; Yes, we are done
@@NextString:	add	ecx,4				; No, advance to next pointer
		jmp	@@GetString			; Process next string
@@Exit:		mov	eax,edi				; EAX = return value
		ret
ENDP
		UDATASEG
		EXTRN	WATCOM_C environ		: DWORD
		EXTRN	WATCOM_C _Envptr		: DWORD
		END
