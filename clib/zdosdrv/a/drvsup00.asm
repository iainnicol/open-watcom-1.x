;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		INCLUDE	'ZDOSDRV.INC'
		CODESEG
		EXTRN	DosReturnZero			: PROC
		PUBLIC	DosHookIsaPorts
;
; DECLARATION	int DosHookIsaPorts( unsigned ioend, unsigned iobase,
;                                    IOTRAP *iotrap );
;
PROC		DosHookIsaPorts		WATCOM_C
		push	esi				; Save context
		push	ecx
		mov	ecx,eax				; ECX = ending I/O address
		mov	esi,3				; ESI = number of I/O trap entries to check
@@NextPort:	dec	esi				; ESI = index
		js	SHORT @@InstallHook		; All entries processed yet ?
		;
		; No, get pointer to callers I/O port read handler in EAX
		;
		mov	eax,[(IOTRAP ebx + esi * 4).InBYTE]
		or	eax,eax				; Use kernel default I/O read function ?
		jz	SHORT @@SetHandler		; Yes, reset I/O port read handler
		mov	eax,[InPortHandlers + esi * 4]	; No, use our I/O read handler
		;
		; Set I/O read handler
		;
@@SetHandler:	mov	[(IOTRAP ebx + esi * 4).Reserved],eax
		jmp	@@NextPort			; Install next port
@@InstallHook:	call	[DWORD HookIsaPorts]		; Hook ISA I/O ports
		pop	ecx				; Restore context
		pop	esi
		jmp	DosReturnZero			; Process return code
ENDP
		DATASEG
		EXTRN	InPortHandlers			: DWORD
		END
