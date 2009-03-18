;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSINT.INC'
		CODESEG
		PUBLIC	_chain_intr_
;
; DECLARATION	void _chain_intr( register void
;		                  (__cdecl *h) (struct context_t) );
;
; ASSUMPTIONS	[ESP]		= return address to C interrupt handler
;		[EBP]		= EBP saved by C interrupt handler
;		[EBP + 4]	= return address to our interrupt handler
; RING0         [EBP + 8]	= flags
;		[EBP + 12]	= EDI saved by our interrupt handler
;		[EBP + 16]	= ESI saved by our interrupt handler
;		[EBP + 20]	= EBP saved by our interrupt handler
;		[EBP + 24]	= Dummy ESP saved by our interrupt handler
;		[EBP + 28]	= EBX saved by our interrupt handler
;		[EBP + 32]	= EDX saved by our interrupt handler
;		[EBP + 36]	= ECX saved by our interrupt handler
;		[EBP + 40]	= EAX saved by our interrupt handler
;		[EBP + 44]	= EIP
; RING3		[EBP + 8]	= GS saved by our interrupt handler
;		[EBP + 12]	= FS saved by our interrupt handler
;		[EBP + 16]	= ES saved by our interrupt handler
;		[EBP + 20]	= DS saved by our interrupt handler
;		[EBP + 24]	= EDI saved by our interrupt handler
;		[EBP + 28]	= ESI saved by our interrupt handler
;		[EBP + 32]	= EBP saved by our interrupt handler
;		[EBP + 36]	= Dummy ESP saved by our interrupt handler
;		[EBP + 40]	= EBX saved by our interrupt handler
;		[EBP + 44]	= EDX saved by our interrupt handler
;		[EBP + 48]	= ECX saved by our interrupt handler
;		[EBP + 52]	= EAX saved by our interrupt handler
;		[EBP + 56]	= Error code
;		[EBP + 60]	= EIP
;		[EBP + 64]	= CS
;		[EBP + 68]	= EFLAGS
;
PROC		_chain_intr_		STDCALL
		lea	esp,[ebp + 8]			; Restore ESP
IFDEF __ZDOSDRV__
		pop	ebx				; Remove flags
ELSE
		movzx	ebx,[(CONTEXT esp).Exception]	; EBX = exception number
		bt	[ErrorCodeMask],ebx		; Set carry flag if error code is pushed
		pop	gs				; Restore context
		pop	fs
		pop	es
		pop	ds
ENDIF
		pop	edi				; Restore EDI
		pop	esi				; Restore ESI
		pop	ebp				; Restore EBP
		pop	ebx				; Remove dummy ESP
		pop	ebx				; Restore EBX
		pop	edx				; Restore EDX
		pop	ecx				; Restore ECX
IFNDEF __ZDOSDRV__
		jc	SHORT @@ErrorCode		; Error code pushed ?
		mov	[esp + 4],eax			; No, save pointer to handler in error code position
		pop	eax				; Restore EAX
		ret					; Chain to old handler
@@ErrorCode:	and	[DWORD esp + 4],0ffffh		; Reset exception number
ENDIF
		xchg	eax,[esp]			; Restore EAX and put chain address on top of stack
		ret					; Chain to old handler
ENDP
IFNDEF __ZDOSDRV__
		DATASEG
		;
		; Bit mask over exceptions that pushes error code
		;
ErrorCodeMask	DD	1 SHL DOUBLE_FAULT + \
			1 SHL TSS_FAULT + \
			1 SHL SEGMENT_FAULT + \
			1 SHL STACK_FAULT + \
			1 SHL GENERAL_FAULT + \
			1 SHL PAGE_FAULT + \
			1 SHL ALIGNMENT_FAULT
ENDIF
		END
