;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	__doserror_			: PROC
		PUBLIC	_dos_setftime_
;
; DECLARATION	unsigned _dos_setftime( int handle, unsigned short date,
;		                        unsigned short time );
;
PROC		_dos_setftime_		STDCALL
		push	ecx				; Save context
		mov	ecx,edx				; ECX = date
		shl	ecx,16				; Make room for time
		or	ecx,ebx				; ECX = time stamp
		mov	ebx,eax				; EBX = handle
		;
		; Get function numbers in AH and AL
		;
		mov	eax,DOS_GET_SET_FILE_TIME_STAMP SHL 8 + 1
		;
		; Call DOS services
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosApi]
ELSE
		int	DOS
ENDIF
		pop	ecx				; Restore context
		jmp	__doserror_			; Process return code
ENDP
		END
