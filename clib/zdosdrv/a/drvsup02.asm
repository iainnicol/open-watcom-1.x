;
; ZDOS run time library function.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		INCLUDE	'ZDOSDRV.INC'
		CODESEG
		EXTRN	DosReturnZero			: PROC
		PUBLIC	DosHookPciPorts
;
; DECLARATION	int DosHookPciPorts( IOTRAP *iotrap, unsigned iobase );
;
PROC		DosHookPciPorts		WATCOM_C
		push	ecx				; Save context
		push	ebx
		mov	ebx,eax				; EBX points to I/O trap block
		mov	ecx,3				; ECX = number of I/O trap entries to check
@@NextPort:	dec	ecx				; ECX = index
		js	SHORT @@InstallHook		; All entries processed yet ?
		;
		; No, get pointer to callers I/O port read handler in EAX
		;
		mov	eax,[(IOTRAP ebx + ecx * 4).InBYTE]
		or	eax,eax				; Use kernel default I/O read function ?
		jz	SHORT @@SetHandler		; Yes, reset I/O port read handler
		mov	eax,[InPortHandlers + ecx * 4]	; No, use our I/O read handler
		;
		; Set I/O read handler
		;
@@SetHandler:	mov	[(IOTRAP ebx + ecx * 4).Reserved],eax
@@InstallHook:	call	[DWORD HookPciPorts]		; Hook PCI I/O ports
		pop	ebx				; Restore context
		pop	ecx
		jmp	DosReturnZero			; Process return code
ENDP
		DATASEG
		EXTRN	InPortHandlers			: DWORD
		END
