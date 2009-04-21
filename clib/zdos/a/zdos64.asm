;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		PUBLIC	DosSound
;
; DECLARATION	void DosSound( int frequency, int periodic ticks );
;
PROC		DosSound		WATCOM_C
		USES	ecx
		mov	ecx,eax				; ECX = frequency in Hz
		mov	ah,DOS_SOUND			; AH = DOS function
		;
		; Call DOS services
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosApi]
ELSE
		int	DOS
ENDIF
		ret					; Return elapsed time
ENDP
		END
