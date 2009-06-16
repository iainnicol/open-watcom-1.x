;
; ZDOS run time library function.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		CODESEG
		PUBLIC	BiosReturnZero
		PUBLIC	BiosReturnAL
		PUBLIC	BiosError
;
; PROCEDURE	BiosReturnZero
;
; INPUT		 AH = code returned from BIOS
;		 CF = 0 or 1
;
; OUTPUT	EAX = 0 if CF was 0 on entry
;		EAX = negated error code if CF was 1 on entry
;
; DESCRIPTION	Returns 0 or negated BIOS error code.
;
PROC		BiosReturnZero
		jc	SHORT BiosError			; Error ?
		xor	eax,eax				; No, clear EAX
		ret
ENDP
;
; PROCEDURE	BiosReturnAL
;
; INPUT		EAX = code returned from BIOS
;		 CF = 0 or 1
;
; OUTPUT	EAX = zero extended AL if CF was 0 on entry
;		EAX = negated error code if CF was 1 on entry
;
; DESCRIPTION	Returns unsigned char or negated BIOS error code.
;
PROC		BiosReturnAL
		jc	SHORT BiosError			; Error ?
		movzx	eax,al				; No, zero extend AL
		ret
ENDP
;
; PROCEDURE	BiosError
;
; INPUT		 AH = BIOS error code
;
; OUTPUT	EAX = negated BIOS error code
;
; DESCRIPTION	Negates BIOS error code.
;
PROC		BiosError
		movzx	eax,ah				; EAX = BIOS error code
		neg	eax				; Negate error code
		ret
ENDP
		END
