;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		INCLUDE	'ERRNO.INC'
;
; Assembly variant of utimbuf structure
;
STRUC		UTIME
AcTime		DD	?
ModTime		DD	?
ENDS
;
; Assembly variant of tm structure
;
STRUC		TM
Seconds		DD	?
Minutes		DD	?
Hours		DD	?
Days		DD	?
Months		DD	?
Years		DD	?
DayOfWeek	DD	?
DayOfYear	DD	?
DayLightFlag	DD	?
ENDS
		CODESEG
		EXTRN	__set_errno_			: PROC
		EXTRN	_localtime_			: PROC
		PUBLIC	utime_
;
; DECLARATION	int utime( char * path, struct utimbuf *times );
;
PROC		utime_		STDCALL
		USES	esi,ecx,ebx
		LOCAL	CurrentTime : DWORD, Time : TM
		mov	esi,edx				; ESI points to buffer
		mov	edx,eax				; EDX points to path
		mov	eax,DOS_OPEN_FILE SHL 8 + 1110b	; AH = DOS function number, AL = access mode
		;
		; Call DOS services
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosApi]
ELSE
		int	DOS
ENDIF
		jc	SHORT @@CheckError		; Success ?
		mov	ebx,eax				; Yes, EBX = file handle
		lea	eax,[(UTIME esi).ModTime]	; EAX points to modtime
		or	esi,esi				; Set time to current time ?
		jnz	SHORT @@GetTime			; No, use modification time
		mov	[CurrentTime],esi		; Yes, reset current time
		lea	eax,[CurrentTime]		; EAX points to current time
@@GetTime:	lea	edx,[Time]			; EDX points to TIME structure
		call	_localtime_			; Get local time
		cmp	[Time.Years],80			; Before 1980 ?
		jc	SHORT @@BadValue		; Yes, error
		xor	ecx,ecx				; No, clear ECX
		mov	eax,[Time.Years]		; EAX = years after 1900
		sub	eax,80				; EAX = years after 1980
		shl	eax,16 + 9			; Get year in proper position
		or	ecx,eax				; Add year
		mov	eax,[Time.Months]		; EAX = months after january
		inc	eax				; EAX = month
		shl	eax,16 + 5			; Get month in proper position
		or	ecx,eax				; Add month
		mov	eax,[Time.Days]			; EAX = days
		shl	eax,16				; Get days in proper position
		or	ecx,eax				; Add days
		mov	eax,[Time.Hours]		; EAX = hours
		shl	eax,11				; Get hours in proper position
		or	ecx,eax				; Add hours
		mov	eax,[Time.Minutes]		; EAX = minutes
		shl	eax,5				; Get minuts in proper position
		or	ecx,eax				; Add minutes
		mov	eax,[Time.Seconds]		; EAX = seconds
		shr	eax,1				; Divide by 2
		or	ecx,eax				; ECX = time stamp
		;
		; Set file time stamp
		;
		mov	eax,DOS_GET_SET_FILE_TIME_STAMP SHL 8 + 1
		;
		; Call DOS services
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosApi]
ELSE
		int	DOS
ENDIF
		jc	SHORT @@AccessError		; Success ?
		mov	ah,DOS_CLOSE_FILE		; Yes, close file
		;
		; Call DOS services
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosApi]
ELSE
		int	DOS
ENDIF
		jc	SHORT @@AccessError		; Success ?
		xor	eax,eax				; Yes, clear EAX
@@Exit:		ret
@@BadValue:	mov	eax,EINVAL			; EAX = error code
		jmp	SHORT @@Error			; Set _errno
@@CheckError:	mov	ecx,eax				; ECX = DOS error code
		mov	eax,ENOENT			; Assume file not found
		cmp	cl,2				; File not found ?
		jz	SHORT @@Error			; Yes, error
		cmp	cl,3				; Path not found ?
		jz	SHORT @@Error			; No, error
		mov	eax,EMFILE			; Yes, assume to many open files
		cmp	cl,4				; Too many open files ?
		jz	SHORT @@Error			; Yes, error
@@AccessError:	mov	eax,EACCES			; No, EAX = error code
@@Error:	call	__set_errno_			; Set _errno
		mov	eax,-1				; EAX = return code
		jmp	@@Exit				; Restore ESP and exit
ENDP
		END
