;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		INCLUDE	'ZIPV4.INC'
		CODESEG
		EXTRN	DosError			: PROC
		PUBLIC	DosSocketSelect_
;
; DECLARATION	int DosSocketSelect( unsigned ticks, unsigned *readset,
;                                    unsigned *writeset, unsigned *exceptset );
;
PROC		DosSocketSelect_	STDCALL
		push	esi				; Save context
		mov	esi,eax				; ESI = time to wait
		mov	ah,SOCKET_SELECT		; AH = function number
		;
		; Do select on socket
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosSocketDriver]
ELSE
		int	SOCKET
ENDIF
		pop	esi				; Restore context
		jc	DosError			; Success ?
		ret
ENDP
		END
