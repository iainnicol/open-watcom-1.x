;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ERRNO.INC'
		CODESEG
		PUBLIC	_dosret0_
		PUBLIC	_dosretax_
		PUBLIC	__set_errno_dos_
;
; DECLARATION	int _dosret0( int ax, int carry );
;
PROC		_dosret0_		STDCALL
		or	edx,edx				; Carry set ?
		jnz	SHORT __set_errno_dos_		; Yes, translate and save error code
		xor	eax,eax				; No, clear EAX
		ret
ENDP
;
; DECLARATION	int _dosretax( int ax, int carry );
;
PROC		_dosretax_		STDCALL
		or	edx,edx				; Carry set ?
		jnz	SHORT __set_errno_dos_		; Yes, translate and save error code
		ret					; No, return value in EAX
ENDP
;
; DECLARATION	int __set_errno_dos( unsigned int errorcode );
;
PROC		__set_errno_dos_	STDCALL
		mov	[BYTE _doserrno],al		; Update _doserrno
		or	ah,ah				; Error code above 256 ?
		jnz	SHORT @@BigErrorCode		; Yes, translate it
		cmp	al,22h				; Error code outside translation table ?
		jbe	SHORT @@Translate		; No, translate error code
		cmp	al,50h				; File does not exist error code ?
		jz	SHORT @@NotExist		; Yes, translate it
		mov	al,22h				; No, EAX = max error code
		jmp	SHORT @@Translate		; Translate error code
@@BigErrorCode:	mov	al,ah				; Get error code in AL
		jmp	SHORT @@Translate		; Translate error code
@@NotExist:	mov	al,14				; AL = index into translation table
@@Translate:	movzx	eax,al				; EAX = index into translation table
		mov	eax,[ErrorTable + eax]		; EAX = translated error code
		mov	[errno],eax			; Update ERRNO
		mov	eax,-1				; EAX = return value
		ret
ENDP
		DATASEG
ErrorTable	DD	EZERO				; 00h
		DD	EINVAL				; 01h
		DD	ENOENT				; 02h
		DD	ENOENT				; 03h
		DD	EMFILE				; 04h
		DD	EACCES				; 05h
		DD	EBADF				; 06h
		DD	ENOMEM				; 07h
		DD	ENOMEM				; 08h
		DD	ENOMEM				; 09h
		DD	E2BIG				; 0ah
		DD	ENOEXEC				; 0bh
		DD	-1				; 0ch
		DD	ERANGE				; 0dh
		DD	EEXIST				; 0eh
		DD	ENODEV				; 0fh
		DD	EACCES				; 10h
		DD	EXDEV				; 11h
		DD	ENOENT				; 12h
		DD	16 DUP (-1)			; 13h - 22h
		UDATASEG
		EXTRN	C _doserrno			: DWORD
		EXTRN	C errno				: DWORD
		END
