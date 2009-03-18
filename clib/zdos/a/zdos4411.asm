;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	DosReturnZero			: PROC
		PUBLIC	DosIoctlWriteTrack_
;
; DECLARATION	int DosIoctlWriteTrack( void *buffer, int track, int drive,
;		                        int startsector, int head, int count);
;
PROC		DosIoctlWriteTrack_	STDCALL
		ARG	Head : DWORD, Count : DWORD
		USES	edi
		mov	edi,eax				; EDI points to buffer
		mov	ch,[BYTE Count]			; CH = number of sectors to write
		mov	bh,[BYTE Head]			; BH = head number
		mov	eax,DOS_DEVICE_CONTROL SHL 8 + \; AH = DOS function number
			    IOCTL_WRITE_TRACK		; AL = subfunction number
		;
		; Call DOS services
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosApi]
ELSE
		int	DOS
ENDIF
		call	DosReturnZero			; Process return code
		ret
ENDP
		END
