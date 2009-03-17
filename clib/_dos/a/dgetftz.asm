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
		PUBLIC	_dos_getftime_
;
; DECLARATION	unsigned _dos_getftime( int handle, unsigned short *date,
;		                        unsigned short *time );
;
PROC		_dos_getftime_		STDCALL
		push	edi				; Save context
		push	esi
		push	ecx
		push	ebx
		mov	esi,edx				; ESI points to date variable
		mov	edi,ebx				; EDI points to time variable
		mov	ebx,eax				; EBX = handle
		;
		; Get DOS function numbers in AH and AL
		;
		mov	eax,DOS_GET_SET_FILE_TIME_STAMP SHL 8
		;
		; Call DOS services
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosApi]
ELSE
		int	DOS
ENDIF
		jc	SHORT @@Exit			; Success ?
		mov	[edi],cx			; Yes, store time
		shr	ecx,16				; Store date
		mov	[esi],cx
@@Exit:		pop	ebx				; Restore context
		pop	ecx
		pop	esi
		pop	edi
		jmp	__doserror_			; Process return code
ENDP
		END
