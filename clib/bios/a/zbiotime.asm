;
; ZDOS run time library function.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		PUBLIC	_bios_timeofday
;
; DECLARATION	int _bios_timeofday( unsigned service, long *timeval );
;
PROC		_bios_timeofday		WATCOM_C
		USES	ecx,edx
		mov	ah,al				; AH = BIOS function
		mov	ecx,edx				; Assume get time of day function
		or	al,al				; Get time of day ?
		jz	SHORT @@DoFunction		; Yes, do it
		mov	edx,[ecx]			; No, EDX = new time
		xor	ecx,ecx				; Reset status
		cmp	al,1				; Valid function ?
		ja	SHORT @@UpdateStatus		; No, update status
		;
		; Yes, call BIOS timer services
		;
IFDEF __ZDOSDRV__
@@DoFunction:	call	[DWORD BiosTimer]
ELSE
@@DoFunction:	int	BIOS_TIMER
ENDIF
		or	ecx,ecx				; Set time of day function ?
		jz	SHORT @@Exit			; Yes, we are done
		mov	[ecx],edx			; No, store time
		mov	ecx,1				; ECX = status
		or	eax,eax				; Midnight passed since last read or set ?
		jnz	SHORT @@Exit			; Yes, we are done
@@UpdateStatus:	dec	ecx				; No, decrement status
@@Exit:		mov	eax,ecx				; EAX = status
		ret
ENDP
		END
