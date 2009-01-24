;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	DosReturnZero			: PROC
		PUBLIC	DosFreeDeviceBlock_
;
; DECLARATION	int DosFreeDeviceBlock( void *block );
;
PROC		DosFreeDeviceBlock_	STDCALL
		call	[DWORD DeviceUnmap]		; Unmap device block
		jmp	DosReturnZero			; Process return code
ENDP
		END
