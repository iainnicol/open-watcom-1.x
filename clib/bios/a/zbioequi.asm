;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		PUBLIC	_bios_equiplist_
;
; DECLARATION	unsigned _bios_equiplist( void );
;
PROC		_bios_equiplist_		STDCALL
		;
		; Call BIOS get equipment list service
		;
IFDEF __ZDOSDRV__
		call	[DWORD BiosEquipment]
ELSE
		int	BIOS_EQUIPMENT
ENDIF
		ret
ENDP
		END
