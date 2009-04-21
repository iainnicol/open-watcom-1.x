;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		INCLUDE	'ZDOSDRV.INC'
		INCLUDE	'SEGMENTS.INC'
		DOSSEG
SEGMENT		_TEXT
		ASSUME	cs:_TEXT,ds:DGROUP,es:DGROUP,ss:DGROUP
		EXTRN	InitializeDriver		: PROC
		EXTRN	WATCOM_C DeviceInitialization	: PROC
		EXTRN	WATCOM_C DeviceMediaCheck	: PROC
		EXTRN	WATCOM_C DeviceBuildBPB		: PROC
		EXTRN	WATCOM_C DeviceIoctlInput	: PROC
		EXTRN	WATCOM_C DeviceInput		: PROC
		EXTRN	WATCOM_C \
			DeviceNonDestructiveInput	: PROC
		EXTRN	WATCOM_C DeviceInputStatus	: PROC
		EXTRN	WATCOM_C DeviceInputFlush	: PROC
		EXTRN	WATCOM_C DeviceOutput		: PROC
		EXTRN	WATCOM_C DeviceOutputWithVerify	: PROC
		EXTRN	WATCOM_C DeviceOutputStatus	: PROC
		EXTRN	WATCOM_C DeviceOutputFlush	: PROC
		EXTRN	WATCOM_C DeviceIoctlOutput	: PROC
		EXTRN	WATCOM_C DeviceOpen		: PROC
		EXTRN	WATCOM_C DeviceClose		: PROC
		EXTRN	WATCOM_C DeviceRemovableMedia	: PROC
		EXTRN	WATCOM_C DeviceOutputUntilBusy	: PROC
		EXTRN	WATCOM_C DeviceGenericIoctl	: PROC
		EXTRN	WATCOM_C DeviceGetLogicalUnit	: PROC
		EXTRN	WATCOM_C DeviceSetLogicalUnit	: PROC
		EXTRN	WATCOM_C DeviceIoctlQuery	: PROC
		PUBLIC	WATCOM_C cstart_
LABEL		cstart_			BYTE
Header		DEVICE	<0, 0, InterruptHandler, '_NONAME_'>
;
; PROCEDURE	InterruptHandler
;
; INPUT		EBX = pointer to device driver request header
;		ESI = pointer to command line if command = 0
;
; OUTPUT	NONE
;
; DESCRIPTION	Invokes device driver command handler.
;
PROC		InterruptHandler
		pushad					; Save context
		mov	eax,ebx				; EAX points to request header
		movzx	ecx,[(IO_REQUEST ebx).Command]	; ECX = device driver command
		call	[DeviceCommands + ecx * 4]	; Invoke device driver command handler
		or	ah,DEVICE_DONE SHR 8		; Set command done bit
		mov	[(IO_REQUEST ebx).Status],eax	; Set command status
		popad					; Restore context
		ret
ENDP
;
; PROCEDURE	InitializeDevice
;
; INPUT		EAX = pointer to IO_INIT request block
;		EBX = pointer to IO_INIT request block
;		ESI = pointer to command line
;
; OUTPUT	EAX = command status
;
; DESCRIPTION	Initializes a device.
;
PROC		InitializeDevice
		mov	edx,OFFSET StartOfStack		; EDX = break address on success
		push	edx				; Save context
		push	ebx
		mov	eax,[DeviceAttributes]		; Get device attributes in EAX
		mov	[Header.Attribute],eax		; Initialize device driver attributes
		lea	ebx,[Header.DeviceName]		; EBX points to device name field in header
		call	InitializeDriver		; Initialize C runtime
		pop	ebx				; Restore context
		pop	edx
		or	eax,eax				; Success ?
		jnz	SHORT @@Error			; No, release memory and exit
		mov	eax,ebx				; Yes, EAX points to IO_INIT request block
		call	DeviceInitialization WATCOM_C,?	; Initialize device
		or	eax,eax				; Success ?
		jz	SHORT @@Exit			; Yes, set device driver break address and exit
@@Error:	mov	edx,OFFSET cstart_		; No, EDX = break address
		mov	eax,DEVICE_GENERAL_FAILURE	; EAX = general failure status code
@@Exit:		mov	[(IO_INIT ebx).Break],edx	; Set device driver break address
		ret
ENDP
ENDS

SEGMENT		_DATA
		EXTRN	DeviceAttributes		: DWORD
DeviceCommands	DD	InitializeDevice		; 00h
		DD	DeviceMediaCheck		; 01h
		DD	DeviceBuildBPB			; 02h
		DD	DeviceIoctlInput		; 03h
		DD	DeviceInput			; 04h
		DD	DeviceNonDestructiveInput	; 05h
		DD	DeviceInputStatus		; 06h
		DD	DeviceInputFlush		; 07h
		DD	DeviceOutput			; 08h
		DD	DeviceOutputWithVerify		; 09h
		DD	DeviceOutputStatus		; 0ah
		DD	DeviceOutputFlush		; 0bh
		DD	DeviceIoctlOutput		; 0ch
		DD	DeviceOpen			; 0dh
		DD	DeviceClose			; 0eh
		DD	DeviceRemovableMedia		; 0fh
		DD	DeviceOutputUntilBusy		; 10h
		DD	DeviceGenericIoctl		; 11h
		DD	DeviceGetLogicalUnit		; 12h
		DD	DeviceSetLogicalUnit		; 13h
		DD	DeviceIoctlQuery		; 14h
ENDS

SEGMENT		_BSS
		PUBLIC	StartOfBSS
LABEL		StartOfBSS		BYTE
ENDS

SEGMENT		STACK
		PUBLIC	StartOfStack
LABEL		StartOfStack		BYTE
ENDS
		END	cstart_
