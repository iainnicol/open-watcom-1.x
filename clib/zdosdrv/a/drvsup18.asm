;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	DosReturnZero			: PROC
		PUBLIC	DosFreeDeviceBlock
;
; DECLARATION	int DosFreeDeviceBlock( void *block );
;
PROC		DosFreeDeviceBlock	WATCOM_C
		call	[DWORD DeviceUnmap]		; Unmap device block
		jmp	DosReturnZero			; Process return code
ENDP
		END
