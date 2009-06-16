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
		PUBLIC	DosExtendedCountryInfo
;
; DECLARATION	int DosExtendedCountryInfo( int subfunction, int country,
;		                            int codepage, int length,
;		                            void *buffer );
;
PROC		DosExtendedCountryInfo	WATCOM_C
		ARG	SubFunction : DWORD, Country : DWORD, CodePage : DWORD, \
			BufferLength : DWORD, Buffer : DWORD
		USES	edi
		mov	edi,[Buffer]			; EDI points to buffer
		mov	ah,DOS_EXTENDED_COUNTRY_INFO	; AH = DOS function
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
