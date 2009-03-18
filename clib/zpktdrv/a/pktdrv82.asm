		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		INCLUDE	'ZPKTDRV.INC'
		CODESEG
		EXTRN	DosError			: PROC
		PUBLIC	DosPktDrvNumberOfInterfaces_
;
; DECLARATION	int DosPktDrvNumberOfInterfaces( void );
;
PROC		DosPktDrvNumberOfInterfaces_	STDCALL
		mov	ah,PKTDRV_NUMBER_OF_INTERFACES	; Get number of installed packet driver interfaces
		call	[DWORD DosPacketDriver]
		jc	DosError			; Success ?
		ret					; Yes, return number of interfaces installed
ENDP
		END
