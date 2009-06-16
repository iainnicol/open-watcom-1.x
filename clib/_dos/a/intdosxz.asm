;
; ZDOS run time library function.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	WATCOM_C _dosretax		: PROC
		PUBLIC	intdosx
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
; DECLARATION	unsigned intdosx( const union REGS *i, union REGS *o,
;		                  struct SREGS *s );
;
PROC		intdosx			WATCOM_C
		push	edi				; Save context
		push	esi
		push	ecx
		push	ebp
		xor	ecx,ecx				; Clear ECX
		mov	ebp,edx				; Save pointer to out registers in EBP
		mov	[(REGS edx).CFLAG],ecx		; Clear CFLAG in out registers
		mov	edi,[(REGS eax).EDI]		; Load in registers registers
		mov	esi,[(REGS eax).ESI]
		mov	edx,[(REGS eax).EDX]
		mov	ecx,[(REGS eax).ECX]
		mov	ebx,[(REGS eax).EBX]
		mov	eax,[(REGS eax).EAX]
		clc					; Clear carry flag
		;
		; Call DOS services
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosApi]
ELSE
		int	DOS
ENDIF
		mov	[(REGS ebp).EAX],eax		; Update out registers
		mov	[(REGS ebp).EBX],ebx
		mov	[(REGS ebp).ECX],ecx
		mov	[(REGS ebp).EDX],edx
		mov	[(REGS ebp).ESI],esi
		mov	[(REGS ebp).ESI],edi
		setc	[BYTE (REGS ebp).CFLAG]		; Set or clear carry flag
		mov	edx,[(REGS ebp).CFLAG]		; EDX = carry flag
		pop	ebp				; Restore context
		pop	ecx
		pop	esi
		pop	edi
		jmp	_dosretax			; Set _errno and _doserrno if error
ENDP
		END
