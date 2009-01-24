;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		PUBLIC	sound_
		PUBLIC	nosound_
;
; DECLARATION	void sound( unsigned frequency );
;
PROC		sound_			STDCALL
		USES	edx,eax
		mov	[Frequency],eax			; Save frequency
		xor	edx,edx				; EDX = reference time
		mov	ah,DOS_ELAPSED_PERIODIC_TICKS	; Get elapsed time
IFDEF __ZDOSDRV__
		call	[DWORD DosApi]
ELSE
		int	DOS
ENDIF
		mov	[ReferenceTime],eax		; Save elapsed time as reference time
		ret					; Chain to previous handler
ENDP
;
; DECLARATION	void nosound( void );
;
PROC		nosound_		STDCALL
		USES	edx,ecx,eax
		mov	edx,[ReferenceTime]		; EDX = reference time
		mov	ah,DOS_ELAPSED_PERIODIC_TICKS	; Get elapsed time
IFDEF __ZDOSDRV__
		call	[DWORD DosApi]
ELSE
		int	DOS
ENDIF
		mov	edx,eax				; EDX = elapsed time
		xor	ecx,ecx				; Clear ECX
		xchg	ecx,[Frequency]			; Get and clear frequency
		or	ecx,ecx				; Frequency set by sound call ?
		jz	SHORT @@Exit			; No, we are done
		mov	ah,DOS_SOUND			; Yes, generate sound
IFDEF __ZDOSDRV__
		call	[DWORD DosApi]
ELSE
		int	DOS
ENDIF
@@Exit:		ret
ENDP
		UDATASEG
Frequency	DD	?
ReferenceTime	DD	?
		END
