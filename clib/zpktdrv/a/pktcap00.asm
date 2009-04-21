		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		INCLUDE	'ZPKTDRV.INC'
		CODESEG
		EXTRN	DosError			: PROC
		PUBLIC	DosPktDrvOpenCapture
;
; DECLARATION	int DosPktDrvOpenCapture( int InterfaceNumber );
;
PROC		DosPktDrvOpenCapture	WATCOM_C
		mov	ah,PKTDRV_OPEN_CAPTURE		; Open capture session
		int	PKTDRV_CAPTURE
		jc	DosError			; Success ?
		shr	eax,1				; Yes, EAX = handle
		ret
ENDP
		END
