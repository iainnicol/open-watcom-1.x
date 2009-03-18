;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		CODESEG
		PUBLIC	DosReturnZero
		PUBLIC	DosReturnAL
		PUBLIC	DosError
;
; PROCEDURE	DosReturnZero
;
; INPUT		EAX = code returned from DOS
;		 CF = 0 or 1
;
; OUTPUT	EAX = 0 if CF was 0 on entry
;		EAX = negated error code if CF was 1 on entry
;
; DESCRIPTION	Returns 0 or negated DOS error code.
;
PROC		DosReturnZero
		jc	SHORT DosError			; Error ?
		xor	eax,eax				; No, clear EAX
		ret
ENDP
;
; PROCEDURE	DosReturnAL
;
; INPUT		EAX = code returned from DOS
;		 CF = 0 or 1
;
; OUTPUT	EAX = zero extended AL if CF was 0 on entry
;		EAX = negated error code if CF was 1 on entry
;
; DESCRIPTION	Returns unsigned char or negated DOS error code.
;
PROC		DosReturnAL
		jc	SHORT DosError			; Error ?
		movzx	eax,al				; No, zero extend AL
		ret
ENDP
;
; PROCEDURE	DosError
;
; INPUT		EAX = ZDOS error code
;
; OUTPUT	EAX = negated ZDOS error code
;
; DESCRIPTION	Negates DOS error code.
;
PROC		DosError
		neg	eax				; Negate error code
		ret
ENDP
		END
