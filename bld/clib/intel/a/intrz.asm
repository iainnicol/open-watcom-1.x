;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
;
; Assembler variant of REGPACK structure
;
STRUC		REGS
EAX		DD	?
EBX		DD	?
ECX		DD	?
EDX		DD	?
EBP		DD	?
ESI		DD	?
EDI		DD	?
DS		DW	?
ES		DW	?
FS		DW	?
GS		DW	?
FLAGS		DD	?
ENDS
		CODESEG
		EXTRN	C _do_interrupt			: PROC
		PUBLIC	intr_
;
; DECLARATION	void intr( int n, union REGPACK *r );
;
PROC		intr_			STDCALL
		USES	edi,esi,ecx,ebx,ebp
		xor	ecx,ecx				; Clear ECX
		push	edx				; Save pointer to registers
		push	eax				; Save interrupt number
		mov	[(REGS ebx).FLAGS],ecx		; Clear FLAGS member
		mov	edi,[(REGS edx).EDI]		; Load in registers registers
		mov	esi,[(REGS edx).ESI]
		mov	ebp,[(REGS edx).EBP]
		mov	ecx,[(REGS edx).ECX]
		mov	ebx,[(REGS edx).EBX]
		mov	eax,[(REGS edx).EAX]
		mov	edx,[(REGS edx).EDX]
		clc					; Clear carry flag
		call	_do_interrupt			; Do interrupt
		xchg	eax,[esp + 4]			; Save EAX and get pointer to registers
		mov	[(REGS eax).EBX],ebx		; Update register members
		mov	[(REGS eax).ECX],ecx
		mov	[(REGS eax).EDX],edx
		mov	[(REGS eax).ESI],esi
		mov	[(REGS eax).ESI],edi
		setc	[BYTE (REGS eax).FLAGS]		; Set or clear carry flag
		pop	ebx				; Remove parameters to _do_interrupt
		pop	[(REGS eax).EAX]		; Update EAX register member
		ret
ENDP
		END
