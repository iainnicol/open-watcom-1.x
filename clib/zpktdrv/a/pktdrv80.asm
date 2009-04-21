		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		INCLUDE	'ZPKTDRV.INC'
		INCLUDE	'REGS.INC'
		CODESEG
		EXTRN	DosReturnAL			: PROC
		EXTRN	WATCOM_C PktDrvInformation	: PROC
		EXTRN	WATCOM_C PktDrvOpenSession	: PROC
		EXTRN	WATCOM_C PktDrvCloseSession	: PROC
		EXTRN	WATCOM_C PktDrvSendPacket	: PROC
		EXTRN	WATCOM_C PktDrvGetAddress	: PROC
		EXTRN	WATCOM_C PktDrvSetAddress	: PROC
		EXTRN	WATCOM_C PktDrvGetReceiveMode	: PROC
		EXTRN	WATCOM_C PktDrvSetReceiveMode	: PROC
		EXTRN	WATCOM_C PktDrvGetMulticastList	: PROC
		EXTRN	WATCOM_C PktDrvSetMulticastList	: PROC
		EXTRN	WATCOM_C PktDrvGetParameters	: PROC
		EXTRN	WATCOM_C PktDrvGetStatistics	: PROC
		PUBLIC	DosPktDrvInstallInterface
;
; DECLARATION	int DosPktDrvInstallInterface( void );
;
PROC		DosPktDrvInstallInterface WATCOM_C
		push	ebx				; Save context
		mov	ebx,OFFSET DriverDispatcher	; EBX = pointer to function dispatcher
		mov	ah,PKTDRV_INSTALL_INTERFACE	; Install packet driver interface
		call	[DWORD DosPacketDriver]
		pop	ebx				; Restore context
		jmp	DosReturnAL			; Process return code
ENDP
;
; PROCEDURE	DriverDispatcher
;
; INPUT		 AH = function number
;	        EBX = interface number
;		EBP = pointer to stack frame
;		Other registers depends on function
;
; OUTPUT	Depends on function
;
; DESCRIPTION	Packet driver services function dispatcher.
;
PROC		DriverDispatcher
		movzx	eax,ah				; EAX = function number
		jmp	[DriverFunctions + eax * 4]	; Invoke function handler
ENDP
;
; PROCEDURE	DriverInformation
;
; INPUT		EBX = interface number
;		EDX = handle
;		EBP = pointer to stack frame
;
; OUTPUT	 CF = 0: callers EAX = driver version number
;		         callers EBX = pointer to driver name
;		         callers ECX = interface class
;		 CF = 1: callers EAX = error code
;
; DESCRIPTION	Returns packet driver information.
;
PROC		DriverInformation
		sub	esp,12				; Make room for packet driver information
		mov	eax,esp                 	; EAX points to packet driver information structure
		call	PktDrvInformation WATCOM_C,?,?;?; Invoke handler
		or	eax,eax				; Success ?
		jnz	SHORT @@Error			; No, error
		pop	[(REGS ebp).ECX]		; Yes, ECX = interface class
		pop	[(REGS ebp).EBX]		; EBX = pointer to driver name
		pop	[(REGS ebp).EAX]		; EAX = version number
		ret
@@Error:	add     esp,12				; Restore ESP
LABEL		DriverError		PROC
		neg	eax				; Invert error code
		mov	[(REGS ebp).EAX],eax		; Update callers EAX
		stc					; Set carry flag
		ret
ENDP
;
; PROCEDURE	DriverOpenSession
;
; INPUT		 AL = interface class (on stack)
;		EBX = interface number
;		ECX = interface type length
;		EDX = value to use in EAX on receiver call
;               ESI = pointer to interface type buffer
; 		EDI = pointer to receiver
;		EBP = pointer to stack frame
;
; OUTPUT	 CF = 0: callers EAX = session handle
;		 CF = 1: callers EAX = error code
;
; DESCRIPTION	Starts receiving packets with the specified interface class
;		and type.
;
PROC		DriverOpenSession
		movzx	eax,[BYTE (REGS ebp).EAX]	; EAX = interface class
		;
		; Invoke handler
		;
		call	PktDrvOpenSession WATCOM_C,?,?,?,?,esi,edi
		or	eax,eax				; Success ?
		js	DriverError			; No, exit with carry flag set
		mov	[(REGS ebp).EAX],eax		; Yes, callers EAX = session handle
		ret
ENDP
;
; PROCEDURE	DriverCloseSession
;
; INPUT		EBX = interface number
;               EDX = session handle
;		EBP = pointer to stack frame
;
; OUTPUT	 CF = 0: session closed successfully
;		 CF = 1: callers EAX = error code
;
; DESCRIPTION	Ends receiving packets with the interface class	and type
;		specified by session handle.
;
PROC		DriverCloseSession
		mov	eax,ebx				; EAX = interface number
		call	PktDrvCloseSession WATCOM_C,?,?	; Invoke handler
		or	eax,eax				; Success ?
		js	DriverError			; No, exit with carry flag set
		ret					; Yes, exit with carry flag clear
ENDP
;
; PROCEDURE	DriverSendPacket
;
; INPUT		EBX = interface number
;               ECX = number of bytes to send
;		ESI = pointer to buffer
;		EBP = pointer to stack frame
;
; OUTPUT	 CF = 0: packet sent
;		 CF = 1: callers EAX = error code
;
; DESCRIPTION	Sends a packet.
;
PROC		DriverSendPacket
		mov	eax,ecx				; EAX = packet length
		mov	edx,esi				; EDX = pointer to packet
		call	PktDrvSendPacket WATCOM_C,?,?,?	; Invoke handler
		or	eax,eax				; Success ?
		js	DriverError			; No, exit with carry flag set
		ret					; Yes, exit with carry flag clear
ENDP
;
; PROCEDURE	DriverGetAddress
;
; INPUT		EBX = interface number
;		ECX = length of buffer
;		EDI = pointer to buffer
;		EBP = pointer to stack frame
;
; OUTPUT	 CF = 0: callers EAX = number of bytes copied
;		 CF = 1: callers EAX = error code
;
; DESCRIPTION	Copies the current local address of the interface to callers
;		buffer.
;
PROC		DriverGetAddress
		mov	eax,ecx				; EAX = packet length
		mov	edx,edi				; EDX = pointer to buffer
		call	PktDrvGetAddress WATCOM_C,?,?,?	; Invoke handler
		or	eax,eax				; Success ?
		js	DriverError			; No, exit with carry flag set
		mov	[(REGS ebp).EAX],eax		; Yes, callers EAX = number of bytes copied
		ret
ENDP
;
; PROCEDURE	DriverSetAddress
;
; INPUT		EBX = interface number
;		ECX = length of buffer
;		ESI = pointer to buffer
;		EBP = pointer to stack frame
;
; OUTPUT	 CF = 0: address set succesfully
;		 CF = 1: callers EAX = error code
;
; DESCRIPTION	Sets the current local address of the interface to the address
;		in callers buffer.
;
PROC		DriverSetAddress
		mov	eax,ecx				; EAX = packet length
		mov	edx,esi				; EDX = pointer to buffer
		call	PktDrvSetAddress WATCOM_C,?,?,?	; Invoke handler
		or	eax,eax				; Success ?
		js	DriverError			; No, exit with carry flag set
		ret					; Yes, exit with carry flag clear
ENDP
;
; PROCEDURE	DriverGetReceiveMode
;
; INPUT		EBX = interface number
;		EBP = pointer to stack frame
;
; OUTPUT	 CF = 0: callers EAX = mode
;		 CF = 1: callers EAX = error code
;
; DESCRIPTION	Returns current receive mode.
;
PROC		DriverGetReceiveMode
		mov	eax,ebx				; EAX = interface number
		call	PktDrvGetReceiveMode WATCOM_C,?	; Invoke handler
		or	eax,eax				; Success ?
		js	DriverError			; No, exit with carry flag set
		mov	[(REGS ebp).EAX],eax		; Yes, callers EAX = receive mode
		ret
ENDP
;
; PROCEDURE	DriverSetReceiveMode
;
; INPUT		EBX = interface number
;		ECX = new receive mode
;		EBP = pointer to stack frame
;
; OUTPUT	 CF = 0: new receive mode set
;		 CF = 1: EAX = error code
;
; DESCRIPTION	Sets the receive mode.
;
PROC		DriverSetReceiveMode
		mov	eax,ecx				; EAX = receive mode
		;
		; Invoke handler
		;
		call	PktDrvSetReceiveMode WATCOM_C,?,?
		or	eax,eax				; Success ?
		js	DriverError			; No, exit with carry flag set
		ret					; Yes, exit with carry flag clear
ENDP
;
; PROCEDURE	DriverGetMulticastList
;
; INPUT		EBX = interface number
;		EDI = pointer to buffer
;		EBP = pointer to stack frame
;
; OUTPUT	 CF = 0: EAX = number of multicast list entries
;		 CF = 1: EAX = error code
;
; DESCRIPTION	Returns current multicast list.
;
PROC		DriverGetMulticastList
		mov	eax,ebx				; EAX = interface number
		mov	edx,edi				; EDX = pointer to buffer
		;
		; Invoke handler
		;
		call	PktDrvGetMulticastList WATCOM_C,?,?
		or	eax,eax				; Success ?
		js	DriverError			; No, exit with carry flag set
		mov	[(REGS ebp).EAX],eax		; Yes, callers EAX = number of multicast list entries
		ret
ENDP
;
; PROCEDURE	DriverSetMulticastList
;
; INPUT		EBX = interface number
;		ECX = number of addresses in multicast list
;		ESI = pointer to multicast list
;		EBP = pointer to stack frame
;
; OUTPUT	 CF = 0: multicast list updated
;		 CF = 1: EAX = error code
;
; DESCRIPTION	Updates multicast list.
;
PROC		DriverSetMulticastList
		mov	eax,ecx				; EAX = number of multicast entries
		mov	edx,esi				; EDX = pointer to buffer
		;
		; Invoke handler
		;
		call	PktDrvSetMulticastList WATCOM_C,?,?,?
		or	eax,eax				; Success ?
		js	DriverError			; No, exit with carry flag set
		ret					; Yes, exit with carry flag clear
ENDP
;
; PROCEDURE	DriverGetParameters
;
; INPUT		EBX = interface number
;		EBP = pointer to stack frame
;
; OUTPUT	 CF = 0: callers EAX = pointer to parameter structure
;		 CF = 1: EAX = error code
;
; DESCRIPTION	Returns pointer to parameter structure.
;
PROC		DriverGetParameters
		mov	eax,ebx				; EAX = interface number
		lea	edx,[(REGS ebp).EAX]		; EDX points to buffer variable
		call	PktDrvGetParameters WATCOM_C,?,?; Invoke handler
		or	eax,eax				; Success ?
		js	DriverError			; No, exit with carry flag set
		ret					; Yes, exit with carry flag clear
ENDP
;
; PROCEDURE	DriverGetStatistics
;
; INPUT		EBX = interface number
;		EDI = pointer to STAT structure
;		EBP = pointer to stack frame
;
; OUTPUT	 CF = 0: structure copied to callers buffer
;		 CF = 1: callers EAX = error code
;
; DESCRIPTION	Returns copy of statistics structure.
;
PROC		DriverGetStatistics
		mov	eax,ebx				; EAX = interface number
		mov	edx,edi				; EDX = pointer to buffer
		call	PktDrvGetStatistics WATCOM_C,?,?; Invoke handler
		or	eax,eax				; Success ?
		js	DriverError			; No, exit with carry flag set
		ret					; Yes, exit with carry flag clear
ENDP
		DATASEG
DriverFunctions	DD	DriverInformation
		DD	DriverOpenSession
		DD	DriverCloseSession
		DD	DriverSendPacket
		DD	DriverGetAddress
		DD	DriverSetAddress
		DD	DriverGetReceiveMode
		DD	DriverSetReceiveMode
		DD	DriverGetMulticastList
		DD	DriverSetMulticastList
		DD	DriverGetParameters
		DD	DriverGetStatistics
		END
