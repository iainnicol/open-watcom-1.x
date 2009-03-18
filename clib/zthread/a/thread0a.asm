;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	DosError			: PROC
		PUBLIC	DosCloneThread_
;
; DECLARATION	int DosCloneThread( int priority, unsigned ESP );
;
PROC		DosCloneThread_		STDCALL
		sub	edx,4				; Make room for return address
		xchg	eax,[esp]			; EAX = return address, [ESP] = priority
		mov	[edx],eax			; Put return address on top of new threads stack
		xchg	eax,[esp]			; EAX = priority, [ESP] = return address
IFDEF __ZDOSDRV__
		call	[DWORD ThreadClone]		; Clone thread
ELSE
		xchg	ecx,edx				; ECX = new threads ESP, EDX = previous ECX
		mov	ah,THREAD_CLONE			; Clone thread
		int	THREAD
		xchg	ecx,edx				; Restore ECX, EDX = new threads ESP
ENDIF
		jc	DosError			; Success ?
		ret					; Yes, return thread ID or 0
ENDP
		END
