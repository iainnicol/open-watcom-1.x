;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		INCLUDE	'ZDOSDRV.INC'
		INCLUDE	'SEGMENTS.INC'
		MODEL	USE32 SMALL
SEGMENT		_TEXT
		ASSUME	cs:_TEXT,ds:DGROUP,es:DGROUP,ss:DGROUP
		EXTRN	InitializeDriver		: PROC
		EXTRN	DeviceInitialization_		: PROC
		EXTRN	DeviceMediaCheck_		: PROC
		EXTRN	DeviceBuildBPB_			: PROC
		EXTRN	DeviceIoctlInput_		: PROC
		EXTRN	DeviceInput_			: PROC
		EXTRN	DeviceNonDestructiveInput_	: PROC
		EXTRN	DeviceInputStatus_		: PROC
		EXTRN	DeviceInputFlush_		: PROC
		EXTRN	DeviceOutput_			: PROC
		EXTRN	DeviceOutputWithVerify_		: PROC
		EXTRN	DeviceOutputStatus_		: PROC
		EXTRN	DeviceOutputFlush_		: PROC
		EXTRN	DeviceIoctlOutput_		: PROC
		EXTRN	DeviceOpen_			: PROC
		EXTRN	DeviceClose_			: PROC
		EXTRN	DeviceRemovableMedia_		: PROC
		EXTRN	DeviceOutputUntilBusy_		: PROC
		EXTRN	DeviceGenericIoctl_		: PROC
		EXTRN	DeviceGetLogicalUnit_		: PROC
		EXTRN	DeviceSetLogicalUnit_		: PROC
		EXTRN	DeviceIoctlQuery_		: PROC
		PUBLIC	C cstart_
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
; PROCEDURE	DeviceInitialization
;
; INPUT		EAX = pointer to IO_INIT request block
;		EBX = pointer to IO_INIT request block
;		ESI = pointer to command line
;
; OUTPUT	EAX = command status
;
; DESCRIPTION	Initializes a device.
;
PROC		DeviceInitialization
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
		mov	eax,ebx				; Yes, EBX points to IO_INIT request block
		call	DeviceInitialization_		; Initialize device
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
DeviceCommands	DD	DeviceInitialization		; 00h
		DD	DeviceMediaCheck_		; 01h
		DD	DeviceBuildBPB_			; 02h
		DD	DeviceIoctlInput_		; 03h
		DD	DeviceInput_			; 04h
		DD	DeviceNonDestructiveInput_	; 05h
		DD	DeviceInputStatus_		; 06h
		DD	DeviceInputFlush_		; 07h
		DD	DeviceOutput_			; 08h
		DD	DeviceOutputWithVerify_		; 09h
		DD	DeviceOutputStatus_		; 0ah
		DD	DeviceOutputFlush_		; 0bh
		DD	DeviceIoctlOutput_		; 0ch
		DD	DeviceOpen_			; 0dh
		DD	DeviceClose_			; 0eh
		DD	DeviceRemovableMedia_		; 0fh
		DD	DeviceOutputUntilBusy_		; 10h
		DD	DeviceGenericIoctl_		; 11h
		DD	DeviceGetLogicalUnit_		; 12h
		DD	DeviceSetLogicalUnit_		; 13h
		DD	DeviceIoctlQuery_		; 14h
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
