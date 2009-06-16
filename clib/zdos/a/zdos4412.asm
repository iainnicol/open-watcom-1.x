;
; ZDOS run time library function.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	DosReturnZero			: PROC
		PUBLIC	DosIoctlVerifyTrack
;
; DECLARATION	int DosIoctlVerifyTrack( int head, int track, int drive );
;
PROC		DosIoctlVerifyTrack	WATCOM_C
		mov	bh,al				; BH = head number
		mov	eax,DOS_DEVICE_CONTROL SHL 8 + \; AH = DOS function number
			    IOCTL_VERIFY_TRACK		; AL = subfunction number
		;
		; Call DOS services
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosApi]
ELSE
		int	DOS
ENDIF
		jmp	DosReturnZero			; Process return code
ENDP
		END
