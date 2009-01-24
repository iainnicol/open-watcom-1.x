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
		PUBLIC	BiosCpuInformation_
;
; DECLARATION	int BiosCpuInformation( CPU *cpu );
;
PROC		BiosCpuInformation_	STDCALL
		push	edx				; Save context
		push	ebx
		mov	ebx,eax				; EBX points to CPU block
		mov	ah,MISC_CPU_STEPPING		; AH = function number
		;
		; Call BIOS
		;
IFDEF __ZDOSDRV__
		call	[DWORD BiosMisc]
ELSE
		int	BIOS_MISC
ENDIF
		mov	[(CPU ebx).Coprocessor],al	; Store coprocessor type
		mov	[(CPU ebx).Family],ch		; Store processor family
		mov	[(CPU ebx).Stepping],cl		; Store processor stepping information
		mov	[(CPU ebx).Features],edx	; Store processor feature flags
		pop	ebx				; Restore context
		pop	edx
		jmp	BiosReturnZero			; Process return code
ENDP
		END
