;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZSOCKET.INC'
		CODESEG
		PUBLIC	fdclr_
		PUBLIC	fdset_
		PUBLIC	fdzero_
		PUBLIC	fdisset_
;
; DECLARATION	fdclr( int fd, fd_set *set );
;
PROC		fdclr_			STDCALL
		push	edi				; Save context
		push	esi
		push	ecx
		push	eax
		mov	ecx,[(FDSET edx).Count]		; ECX = number of handles installed
		or	ecx,ecx				; Any handles installed ?
		jz	SHORT @@Exit			; No, we are done
		lea	esi,[(FDSET edx).Handle]	; Yes, ESI points to array of handles
		mov	edi,eax				; EDI = value to compare with
@@Again:	lodsd					; Get next handle
		cmp	eax,edi				; Match ?
		loopnz	@@Again				; No, try again
		jnz	SHORT @@Exit			; Did we find it ?
		dec	[(FDSET edx).Count]		; Yes, count down number of handles
		lea	edi,[esi - 4]			; EDI points to storage location
		rep	movsd				; Copy remaining handles
@@Exit:		pop	eax				; Restore context
		pop	ecx
		pop	esi
		pop	edi
		ret
ENDP
;
; DECLARATION	fdset( int fd, fd_set *set, int maxcount );
;
PROC		fdset_			STDCALL
		push	ecx				; Save context
		mov	ecx,[(FDSET edx).Count]		; ECX = number of handles installed
		cmp	ecx,ebx				; Array full ?
		jz	SHORT @@Exit			; Yes, we are done
		;
		; No, insert handle in array
		;
		mov	[(FDSET edx + ecx * 4).Handle],eax
		inc	[(FDSET edx).Count]		; Advance number of handles
@@Exit:		pop	ecx				; Restore context
		ret
ENDP
;
; DECLARATION	fdzero( fd_set *set );
;
PROC		fdzero_			STDCALL
		mov	[(FDSET eax).Count],0		; Reset handle count
		ret
ENDP
;
; DECLARATION	fdisset( int fd, fd_set *set );
;
PROC		fdisset_		STDCALL
		push	edx				; Save context
		push	ecx
		mov	ecx,[(FDSET edx).Count]		; ECX = number of handles installed
		or	ecx,ecx				; Any handles installed ?
		jz	SHORT @@Exit			; No, we are done
@@Again:	cmp	eax,[edx]			; Match ?
		jz	SHORT @@Exit			; Yes, we are done
		add	edx,4				; No, advance to next handle
		dec	ecx				; ECX = number of handles left to check
		jnz	@@Again				; Try again
@@Exit:		mov	eax,ecx				; EAX = value to return
		pop	ecx				; Restore context
		pop	edx
		ret
ENDP
		END
