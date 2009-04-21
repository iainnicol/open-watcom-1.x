		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		INCLUDE	'ZPKTDRV.INC'
;
; Receive callback handle
;
STRUC		CALLBACK
Parameter	DD	?				; Parameter to use in receive callback
Handler		DD	?				; Pointer to receive handler
ENDS
		CODESEG
		EXTRN	DosError			: PROC
		PUBLIC	DosPktDrvOpenSession
;
; DECLARATION	int DosPktDrvOpenSession( int InterfaceClass, unsigned ReceiveParameter, int InterfaceNumber,
;                                         int InterfaceTypeLength, char *InterfaceType, PKTDRV_RECEIVE_CALLBACK );
;
PROC		DosPktDrvOpenSession	WATCOM_C
		ARG	InterfaceClass : DWORD, ReceiveParameter : DWORD, \
			InterfaceNumber : DWORD, InterfaceTypeLength : DWORD, \
			InterfaceType : DWORD, Receiver : DWORD
		USES	edi, esi
		mov	edi,[Receiver]			; EDI points to receive handler
		push	edx				; Save context
		push	ecx
		push	eax
		mov	ecx,SIZE CALLBACK		; ECX = number of bytes to allocate
		call	[DWORD AllocateBlock]		; Allocate block
		pop	edx				; Restore context
		pop	ecx
		pop	esi
		jc	SHORT @@Error			; Success ?
		xchg	edx,eax				; Yes, EDX points to callback handle, EAX = interface class
		mov	[(CALLBACK edx).Parameter],esi	; Save parameter
		mov	[(CALLBACK edx).Handler],edi	; Save pointer to handler
		mov	edi,OFFSET ReceiveCallBack	; EDI points to receive callback handler
		mov	esi,[InterfaceType]		; ESI points to interface type
		mov	ah,PKTDRV_OPEN_SESSION		; Open session
		call	[DWORD DosPacketDriver]
		jc	SHORT @@FreeBuffer		; Success ?
		mov	[PktDrvCallBack + eax * 4],edx	; Yes, save pointer to callback handle
		ret
@@FreeBuffer:   xchg	eax,edx				; EAX points to block to free, EDX = error code
		call	[DWORD FreeBlock]		; Free block
		mov	eax,edx				; EAX = error code
		stc					; Set carry flag
@@Error:	call	DosError			; Process return code
		ret
ENDP
;
; PROCEDURE	ReceiveCallBack
;
; INPUT		EAX = pointer to CALLBACK handle
;		ECX = number of bytes received
;		ESI = pointer to buffer
;
; OUTPUT	 CF = 0: packet accepted
;		 CF = 1: packet not accepted
;
; DESCRIPTION	Invokes C handler for recieve callback.
;
PROC		ReceiveCallBack
		mov	edx,ecx				; EDX = length of packet
		mov	ebx,esi				; EBX points to packet
		mov	ecx,eax				; ECX points to CALLBACK handle
		mov	eax,[(CALLBACK ecx).Parameter]	; EAX = parameter
		call	[(CALLBACK ecx).Handler]	; Invoke receive handler
		cmp	eax,1				; Set or clear carry flag
		ret
ENDP
		UDATASEG
		PUBLIC	PktDrvCallBack
PktDrvCallBack	DD	16 DUP(?)			; Pointer to callback handles
		END
