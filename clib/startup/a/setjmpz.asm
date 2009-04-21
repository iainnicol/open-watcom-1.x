;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		CODESEG
		PUBLIC	_setjmp
		PUBLIC	longjmp
;
; DECLARATION	int _setjmp( jmp_buf env );
;
PROC		_setjmp			WATCOM_C
		pop	[DWORD eax]			; Save return address
		push	[DWORD eax]			; Put return address on top of stack
		mov	[eax + 4],ebx			; Save registers
		mov	[eax + 8],ecx
		mov	[eax + 12],edx
		mov	[eax + 16],esi
		mov	[eax + 20],edi
		mov	[eax + 24],ebp
		mov	[eax + 28],esp
		xor	eax,eax				; Clear EAX
		ret					; Return to caller
ENDP
;
; DECLARATION	void longjmp( jmp_buf env, int returnvalue );
;
PROC		longjmp			WATCOM_C
		xchg	eax,edx				; EAX = return value, EDX = pointer to jmp_buf
		mov	ebx,[edx]			; EBX = return address
		mov	ecx,[edx + 8]			; Restore registers
		mov	esi,[edx + 16]
		mov	edi,[edx + 20]
		mov	ebp,[edx + 24]
		mov	esp,[edx + 28]
		mov	[esp],ebx			; Replace return address
		mov	ebx,[edx + 4]			; Restore EBX and EDX
		mov	edx,[edx + 12]
		ret					; Return to setjmp () caller
ENDP
		END
