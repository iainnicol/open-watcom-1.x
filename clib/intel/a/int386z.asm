;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		CODESEG
		EXTRN	C _do_interrupt			: PROC
		PUBLIC	int386_
;
; Assembler variant of REGS structure
;
STRUC		REGS
EAX		DD	?
EBX		DD	?
ECX		DD	?
EDX		DD	?
ESI		DD	?
EDI		DD	?
CFLAG		DD	?
ENDS
;
; DECLARATION	int int386( int n, const union REGS *i, union REGS *o );
;
PROC		int386			WATCOM_C
		USES	edi,esi,ecx,ebp
		xor	ecx,ecx				; Clear ECX
		mov	ebp,ebx				; Save pointer to out registers in EBP
		push	eax				; Save interrupt number on top of stack
		mov	[(REGS ebx).CFLAG],ecx		; Clear CFLAG in out registers
		mov	edi,[(REGS edx).EDI]		; Load in registers registers
		mov	esi,[(REGS edx).ESI]
		mov	ecx,[(REGS edx).ECX]
		mov	ebx,[(REGS edx).EBX]
		mov	eax,[(REGS edx).EAX]
		mov	edx,[(REGS edx).EDX]
		clc					; Clear carry flag
		call	_do_interrupt			; Do interrupt
		mov	[(REGS ebp).EAX],eax		; Update out registers
		mov	[(REGS ebp).EBX],ebx
		mov	[(REGS ebp).ECX],ecx
		mov	[(REGS ebp).EDX],edx
		mov	[(REGS ebp).ESI],esi
		mov	[(REGS ebp).ESI],edi
		setc	[BYTE (REGS ebp).CFLAG]		; Set or clear carry flag
		pop	ecx				; Remove parameter to _do_interrupt
		ret
ENDP
		END
