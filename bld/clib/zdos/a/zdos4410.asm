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
		PUBLIC	DosIoctlReadTrack_
;
; DECLARATION	int DosIoctlReadTrack( void *buffer, int track, int drive,
;		                       int startsector, int head, int count);
;
PROC		DosIoctlReadTrack_	STDCALL
		ARG	Head : DWORD, Count : DWORD
		USES	edi
		mov	edi,eax				; EDI points to buffer
		mov	ch,[BYTE Count]			; CH = number of sectors to read
		mov	bh,[BYTE Head]			; BH = head number
		mov	eax,DOS_DEVICE_CONTROL SHL 8 + \; AH = DOS function number
			    IOCTL_READ_TRACK		; AL = subfunction number
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
