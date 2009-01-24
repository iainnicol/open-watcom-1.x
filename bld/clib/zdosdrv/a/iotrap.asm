;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSDRV.INC'
		CODESEG
;
; PROCEDURE	InBYTE
;
; INPUT		EDX = I/O port address
;		ESI = pointer to IOTRAP structure
;
; OUTPUT	EAX = I/O data
;
; DESCRIPTION	General handler for BYTE reads from virtual ports.
;
PROC		InBYTE
		mov	eax,edx				; EAX = I/O address
		jmp	[(IOTRAP esi).InBYTE]		; Return virtual port value
ENDP
;
; PROCEDURE	InWORD
;
; INPUT		EDX = I/O port address
;		ESI = pointer to IOTRAP structure
;
; OUTPUT	EAX = I/O data
;
; DESCRIPTION	General handler for WORD reads from virtual ports.
;
PROC		InWORD
		mov	eax,edx				; EAX = I/O address
		jmp	[(IOTRAP esi).InWORD]		; Return virtual port value
ENDP
;
; PROCEDURE	InDWORD
;
; INPUT		EDX = I/O port address
;		ESI = pointer to IOTRAP structure
;
; OUTPUT	EAX = I/O data
;
; DESCRIPTION	General handler for DWORD reads from virtual ports.
;
PROC		InDWORD
		mov	eax,edx				; EAX = I/O address
		jmp	[(IOTRAP esi).InDWORD]		; Return virtual port value
ENDP
		DATASEG
		PUBLIC	InPortHandlers
InPortHandlers	DD	InBYTE, InWORD, InDWORD		; List of virtual port read handlers
		END
