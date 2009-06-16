;
; ZDOS run time library function.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
;
; ZDOS file opening modes
;
ALLOW_READ	=	1				; Allow reading for owner
ALLOW_WRITE	=	2				; Allow writing for owner
DENY_READ	=	4				; Others can't read
DENY_WRITE	=	8				; Others can't write
		CODESEG
		PUBLIC	ConvertOpenFlags
;
; DECLARATION	int ConvertOpenFlags( int modeflags );
;
PROC		ConvertOpenFlags	WATCOM_C
		push	ebx				; Save context
		movzx	ebx,al				; Get copy of flags in EBX
		and	al,11110000b			; Clear bits to modify
		and	ebx,3				; EBX = index into table
		or	al,[OpenModes + ebx]		; Convert mode flags
		movzx	ebx,al				; Get copy of flags in EBX
		and	al,10000011b			; Clear bits to modify
		shr	ebx,4				; Move bits to proper position
		and	ebx,7				; EBX = index into table
		or	al,[ShareModes + ebx]		; Convert share flags
		pop	ebx				; Restore context
		ret
ENDP
		DATASEG
OpenModes	DB	ALLOW_READ			; 0 = O_RDONLY
		DB	ALLOW_WRITE			; 1 = O_WRONLY
		DB	ALLOW_READ + ALLOW_WRITE	; 2 = O_RDWR
		DB	ALLOW_READ + ALLOW_WRITE	; 3 = undefined
ShareModes	DB	DENY_READ + DENY_WRITE		; 0 = SH_COMPAT
		DB	DENY_READ + DENY_WRITE		; 1 = SH_DENYRW
		DB	DENY_WRITE			; 2 = SH_DENYWR
		DB	DENY_READ			; 3 = SH_DENYRD
		DB	0				; 4 = SH_DENYNO
		DB	DENY_READ + DENY_WRITE		; 5 = undefined
		DB	DENY_READ + DENY_WRITE		; 6 = undefined
		DB	DENY_READ + DENY_WRITE		; 7 = undefined
		END
