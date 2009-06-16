;
; ZDOS run time library function.
;
		IDEAL
		P486
		INCLUDE	'ZDOSDRV.INC'
		INCLUDE	'SEGMENTS.INC'
		DOSSEG
;
; Driver stack frame
;
STRUC		REGS
EDI		DD	?
ESI		DD	?
EBP		DD	?
ESP		DD	?
EBX		DD	?
EDX		DD	?
ECX		DD	?
EAX		DD	?
ENDS

SEGMENT		_TEXT
		ASSUME	cs:_TEXT,ds:DGROUP,es:DGROUP,ss:DGROUP
		EXTRN	InitializeDriver		: PROC
		PUBLIC	WATCOM_C cstart_
LABEL		cstart_			BYTE
Header		HWD	<0, '_NONAME_'>
;
; PROCEDURE	DriverStart
;
; INPUT		ESI = pointer to command line
;
; OUTPUT	EAX = break address
;
; DESCRIPTION	Invokes driver initialization routine.
;
PROC		DriverStart
		mov	eax,OFFSET StartOfStack		; EAX = break address on success
		pushad					; Save context
		lea	ebx,[Header.DriverName]		; EBX points to driver name
		call	InitializeDriver		; Initialize C runtime
		or	eax,eax				; Success ?
		jz	SHORT @@Exit			; Yes, we are done
		mov	[(REGS esp).EAX],OFFSET cstart_	; No, we need to remove the driver from memory
@@Exit:		popad					; Restore context
		ret
ENDP
ENDS

SEGMENT		_BSS
		PUBLIC	StartOfBSS
LABEL		StartOfBSS		BYTE
ENDS

SEGMENT		STACK
		PUBLIC	StartOfStack
LABEL		StartOfStack		BYTE
ENDS
		END	DriverStart
