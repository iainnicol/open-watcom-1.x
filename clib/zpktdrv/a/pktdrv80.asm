		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		INCLUDE	'ZPKTDRV.INC'
		INCLUDE	'REGS.INC'
		CODESEG
		EXTRN	DosReturnAL			: PROC
		EXTRN	PktDrvInformation_		: PROC
		EXTRN	PktDrvOpenSession_		: PROC
		EXTRN	PktDrvCloseSession_		: PROC
		EXTRN	PktDrvSendPacket_		: PROC
		EXTRN	PktDrvGetAddress_		: PROC
		EXTRN	PktDrvSetAddress_		: PROC
		EXTRN	PktDrvGetReceiveMode_		: PROC
		EXTRN	PktDrvSetReceiveMode_		: PROC
		EXTRN	PktDrvGetMulticastList_		: PROC
		EXTRN	PktDrvSetMulticastList_		: PROC
		EXTRN	PktDrvGetParameters_		: PROC
		EXTRN	PktDrvGetStatistics_		: PROC
		PUBLIC	DosPktDrvInstallInterface_
;
; DECLARATION	int DosPktDrvInstallInterface( void );
;
PROC		DosPktDrvInstallInterface_	STDCALL
		push	ebx				; Save context
		mov	ebx,OFFSET PktDrvDispatcher	; EBX = pointer to function dispatcher
		mov	ah,PKTDRV_INSTALL_INTERFACE	; Install packet driver interface
		call	[DWORD DosPacketDriver]
		pop	ebx				; Restore context
		jmp	DosReturnAL			; Process return code
ENDP
;
; PROCEDURE	PktDrvDispatcher
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
PROC		PktDrvDispatcher
		movzx	eax,ah				; EAX = function number
		jmp	[PktDrvFunctions + eax * 4]	; Invoke function handler
ENDP
;
; PROCEDURE	PktDrvInformation
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
PROC		PktDrvInformation
		sub	esp,12				; Make room for packet driver information
		mov	eax,esp                 	; EAX points to packet driver information structure
		call	PktDrvInformation_		; Invoke handler
		or	eax,eax				; Success ?
		jnz	SHORT @@Error			; No, error
		pop	[(REGS ebp).ECX]		; Yes, ECX = interface class
		pop	[(REGS ebp).EBX]		; EBX = pointer to driver name
		pop	[(REGS ebp).EAX]		; EAX = version number
		ret
@@Error:	add     esp,12				; Restore ESP
LABEL		PktDrvError		PROC
		neg	eax				; Invert error code
		mov	[(REGS ebp).EAX],eax		; Update callers EAX
		stc					; Set carry flag
		ret
ENDP
;
; PROCEDURE	PktDrvOpenSession
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
PROC		PktDrvOpenSession
		movzx	eax,[BYTE (REGS ebp).EAX]	; EAX = interface class
		;
		; Invoke handler
		;
		call	PktDrvOpenSession_ STDCALL,esi,edi
		or	eax,eax				; Success ?
		js	PktDrvError			; No, exit with carry flag set
		mov	[(REGS ebp).EAX],eax		; Yes, callers EAX = session handle
		ret
ENDP
;
; PROCEDURE	PktDrvCloseSession
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
PROC		PktDrvCloseSession
		mov	eax,ebx				; EAX = interface number
		call	PktDrvCloseSession_		; Invoke handler
		or	eax,eax				; Success ?
		js	PktDrvError			; No, exit with carry flag set
		ret					; Yes, exit with carry flag clear
ENDP
;
; PROCEDURE	PktDrvSendPacket
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
PROC		PktDrvSendPacket
		mov	eax,ecx				; EAX = packet length
		mov	edx,esi				; EDX = pointer to packet
		call	PktDrvSendPacket_		; Invoke handler
		or	eax,eax				; Success ?
		js	PktDrvError			; No, exit with carry flag set
		ret					; Yes, exit with carry flag clear
ENDP
;
; PROCEDURE	PktDrvGetAddress
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
PROC		PktDrvGetAddress
		mov	eax,ecx				; EAX = packet length
		mov	edx,edi				; EDX = pointer to buffer
		call	PktDrvGetAddress_		; Invoke handler
		or	eax,eax				; Success ?
		js	PktDrvError			; No, exit with carry flag set
		mov	[(REGS ebp).EAX],eax		; Yes, callers EAX = number of bytes copied
		ret
ENDP
;
; PROCEDURE	PktDrvSetAddress
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
PROC		PktDrvSetAddress
		mov	eax,ecx				; EAX = packet length
		mov	edx,esi				; EDX = pointer to buffer
		call	PktDrvSetAddress_		; Invoke handler
		or	eax,eax				; Success ?
		js	PktDrvError			; No, exit with carry flag set
		ret					; Yes, exit with carry flag clear
ENDP
;
; PROCEDURE	PktDrvGetReceiveMode
;
; INPUT		EBX = interface number
;		EBP = pointer to stack frame
;
; OUTPUT	 CF = 0: callers EAX = mode
;		 CF = 1: callers EAX = error code
;
; DESCRIPTION	Returns current receive mode.
;
PROC		PktDrvGetReceiveMode
		mov	eax,ebx				; EAX = interface number
		call	PktDrvGetReceiveMode_		; Invoke handler
		or	eax,eax				; Success ?
		js	PktDrvError			; No, exit with carry flag set
		mov	[(REGS ebp).EAX],eax		; Yes, callers EAX = receive mode
		ret
ENDP
;
; PROCEDURE	PktDrvSetReceiveMode
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
PROC		PktDrvSetReceiveMode
		mov	eax,ecx				; EAX = receive mode
		call	PktDrvSetReceiveMode_		; Invoke handler
		or	eax,eax				; Success ?
		js	PktDrvError			; No, exit with carry flag set
		ret					; Yes, exit with carry flag clear
ENDP
;
; PROCEDURE	PktDrvGetMulticastList
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
PROC		PktDrvGetMulticastList
		mov	eax,ebx				; EAX = interface number
		mov	edx,edi				; EDX = pointer to buffer
		call	PktDrvGetMulticastList_		; Invoke handler
		or	eax,eax				; Success ?
		js	PktDrvError			; No, exit with carry flag set
		mov	[(REGS ebp).EAX],eax		; Yes, callers EAX = number of multicast list entries
		ret
ENDP
;
; PROCEDURE	PktDrvSetMulticastList
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
PROC		PktDrvSetMulticastList
		mov	eax,ecx				; EAX = number of multicast entries
		mov	edx,esi				; EDX = pointer to buffer
		call	PktDrvSetMulticastList_		; Invoke handler
		or	eax,eax				; Success ?
		js	PktDrvError			; No, exit with carry flag set
		ret					; Yes, exit with carry flag clear
ENDP
;
; PROCEDURE	PktDrvGetParameters
;
; INPUT		EBX = interface number
;		EBP = pointer to stack frame
;
; OUTPUT	 CF = 0: callers EAX = pointer to parameter structure
;		 CF = 1: EAX = error code
;
; DESCRIPTION	Returns pointer to parameter structure.
;
PROC		PktDrvGetParameters
		mov	eax,ebx				; EAX = interface number
		lea	edx,[(REGS ebp).EAX]		; EDX points to buffer variable
		call	PktDrvGetParameters_		; Invoke handler
		or	eax,eax				; Success ?
		js	PktDrvError			; No, exit with carry flag set
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
PROC		PktDrvGetStatistics
		mov	eax,ebx				; EAX = interface number
		mov	edx,edi				; EDX = pointer to buffer
		call	PktDrvGetStatistics_		; Invoke handler
		or	eax,eax				; Success ?
		js	PktDrvError			; No, exit with carry flag set
		ret					; Yes, exit with carry flag clear
ENDP
		DATASEG
PktDrvFunctions	DD	PktDrvInformation
		DD	PktDrvOpenSession
		DD	PktDrvCloseSession
		DD	PktDrvSendPacket
		DD	PktDrvGetAddress
		DD	PktDrvSetAddress
		DD	PktDrvGetReceiveMode
		DD	PktDrvSetReceiveMode
		DD	PktDrvGetMulticastList
		DD	PktDrvSetMulticastList
		DD	PktDrvGetParameters
		DD	PktDrvGetStatistics
		END
