;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZBIOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	BiosReturnZero			: PROC
		PUBLIC	BiosScrollWindowDown
;
; DECLARATION	int BiosScrollWindowDown( int lowerY, int lowerX,
;                                         int upperY, int upperX,
;                                         int rows, int blankingattr );
;
PROC		BiosScrollWindowDown	WATCOM_C
		ARG	LowerY : DWORD, LowerX : DWORD, UpperY : DWORD, \
			UpperX : DWORD, Rows : DWORD, Attribute : DWORD
		mov	dh,al				; DH = lower Y
		mov	ch,bl				; CH = upper Y
		mov	al,[BYTE Rows]			; AL = number of rows to scroll
		mov	bh,[BYTE Attribute]		; BH = attribute to use for blanking
		mov	ah,VIDEO_SCROLL_DOWN		; AH = video function
		;
		; Call BIOS
		;
IFDEF __ZDOSDRV__
		mov	bl,[VideoPage]			; BH = console number
		call	[DWORD DosVideo]
ELSE
		int	BIOS_VIDEO
ENDIF
		call	BiosReturnZero			; Process return code
		ret
ENDP
IFDEF __ZDOSDRV__
		UDATASEG
		EXTRN	WATCOM_C VideoPage		: BYTE
ENDIF
		END
