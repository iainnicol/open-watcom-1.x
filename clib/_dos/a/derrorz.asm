;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		CODESEG
		EXTRN	__set_errno_dos_		: PROC
		PUBLIC	__doserror_
;
; PROCEDURE	__doserror
;
; INPUT		EAX = DOS error code
;
; OUTPUT	EAX = DOS error code or 0
;
; DESCRIPTION	Sets _doserrno and _errno on error or returns 0 if no error.
;
PROC		__doserror_
		jnc	SHORT @@Success			; Error ?
		push	eax				; Yes, save error code
		call	__set_errno_dos_		; Set _doserrno and _errno
		pop	eax				; Restore error code
		ret
@@Success:	xor	eax,eax				; Clear EAX
		ret
ENDP
		END
