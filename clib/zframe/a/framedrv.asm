		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		INCLUDE	'REGS.INC'
		CODESEG
 		EXTRN	WATCOM_C \
			FrameBufferFillRectangle: PROC
		EXTRN	WATCOM_C \
			FrameBufferCopyRectangle	: PROC
		EXTRN	WATCOM_C FrameBufferDrawImage	: PROC
		EXTRN	WATCOM_C FrameBufferCursorOn	: PROC
		EXTRN	WATCOM_C FrameBufferCursorOff	: PROC
		EXTRN	WATCOM_C FrameBufferCursorShape	: PROC
		EXTRN	WATCOM_C \
			FrameBufferCursorPosition	: PROC
		EXTRN	WATCOM_C FrameBufferSetPalette	: PROC
		EXTRN	WATCOM_C FrameBufferWaitEngine2D: PROC
		PUBLIC	DosFrameBufferInstallDriver
;
; DECLARATION	int DosFrameBufferInstallDriver( void );
;
PROC		DosFrameBufferInstallDriver WATCOM_C
		mov	eax,[Fill]			; EAX = pointer to fill rectangle function
		xchg	eax,[DWORD FillRectangle]	; Replace handler and get pointer to default handler
		mov	[Fill],eax			; Save pointer to default handler
		mov	eax,[Copy]			; EAX = pointer to copy rectangle function
		xchg	eax,[DWORD CopyRectangle]	; Replace handler and get pointer to default handler
		mov	[Copy],eax			; Save pointer to default handler
		mov	eax,[Draw]			; EAX = pointer to draw image function
		xchg	eax,[DWORD DrawImage]		; Replace handler and get pointer to default handler
		mov	[Draw],eax			; Save pointer to default handler
		mov	eax,[Enable]			; EAX = pointer to cursor on function
		xchg	eax,[DWORD CursorOn]		; Replace handler and get pointer to default handler
		mov	[Enable],eax			; Save pointer to default handler
		mov	eax,[Disable]			; EAX = pointer to cursor off function
		xchg	eax,[DWORD CursorOff]		; Replace handler and get pointer to default handler
		mov	[Disable],eax			; Save pointer to default handler
		mov	eax,[Shape]			; EAX = pointer to cursor shape function
		xchg	eax,[DWORD CursorShape]		; Replace handler and get pointer to default handler
		mov	[Shape],eax			; Save pointer to default handler
		mov	eax,[Position]			; EAX = pointer to cursor position function
		xchg	eax,[DWORD CursorPosition]	; Replace handler and get pointer to default handler
		mov	[Position],eax			; Save pointer to default handler
		mov	eax,[Palette]			; EAX = pointer to set palette function
		xchg	eax,[DWORD SetPalette]		; Replace handler and get pointer to default handler
		mov	[Palette],eax			; Save pointer to default handler
		mov	eax,[Engine2D]			; EAX = pointer to wait 2D engine function
		xchg	eax,[DWORD WaitEngine2D]	; Replace handler and get pointer to default handler
		mov	[Engine2D],eax			; Save pointer to default handler
		xor	eax,eax				; Clear EAX
		ret
ENDP
;
; PROCEDURE	DriverFillRectangle
;
; INPUT		EAX = color
;		EBX = raster operation
;		ECX = X coordinate
;		EDX = Y coordinate
;		ESI = height
;		EDI = width
;
; OUTPUT	 CF = 0: rectangle drawn or cleared
;		 CF = 1: AH = error code
;
; DESCRIPTION	Fills a rectangle.
;
PROC		DriverFillRectangle
		pushad					; Save context
		mov	ecx,edx				; ECX = X coordinate
		mov	edx,eax				; EDX = color
		mov	eax,ebx				; EAX = raster operation
		mov	ebx,[(REGS esp).EDX]		; EBX = Y coordinate
		;
		; Invoke function handler
		;
		call	FrameBufferFillRectangle WATCOM_C,?,?,?,?,esi,edi
		or	eax,eax				; Success ?
		jz	SHORT @@Exit			; Yes, we are done
		cmp	eax,-1				; Function supported ?
		jnz	SHORT @@Error			; Yes, error
		popad					; No, restore context
		jmp	[Fill]				; Use default function
@@Error:	neg	eax				; EAX = error code
		mov	[BYTE (REGS esp + 1).EAX],al	; Update callers AH
		stc					; Set carry flag
@@Exit:		popad					; Restore context
		ret
ENDP
;
; PROCEDURE	DriverCopyRectangle
;
; INPUT		EAX = destination X coordinate
;		EBX = destination Y coordinate
;		ECX = source X coordinate
;		EDX = source Y coordinate
;		ESI = height
;		EDI = width
;		EBP = raster operation
;
; OUTPUT	 CF = 0: rectangle copied
;		 CF = 1: AH = error code
;
; DESCRIPTION	Copies a rectangle from one area to another area.
;
PROC		DriverCopyRectangle
		pushad					; Save context
		xchg	eax,ebp				; EAX = raster operation, EBP = destination X coordinate
		mov	ebx,edx				; EBX = source Y coordinate
		mov	edx,ecx				; EDX = source X coordinate
		mov	ecx,esi				; ECX = height
		mov	esi,[(REGS esp).EBX]		; ESI = destination Y coordinate
		;
		; Invoke function handler
		;
		call	FrameBufferCopyRectangle WATCOM_C,?,?,?,?,edi,ebp,esi
		or	eax,eax				; Success ?
		jz	SHORT @@Exit			; Yes, we are done
		cmp	eax,-1				; Function supported ?
		jnz	SHORT @@Error			; Yes, error
		popad					; No, restore context
		jmp	[Copy]				; Use default function
@@Error:	neg	eax				; EAX = error code
		mov	[BYTE (REGS esp + 1).EAX],al	; Update callers AH
		stc					; Set carry flag
@@Exit:		popad					; Restore context
		ret
ENDP
;
; PROCEDURE	DriverDrawImage
;
; INPUT		EAX = raster operation
;		EBX = pointer to image
;		ECX = X coordinate
;		EDX = Y coordinate
;		ESI = height
;		EDI = width
;
; OUTPUT	 CF = 0: image drawn
;		 CF = 1: AH = error code
;
; DESCRIPTION	Draws an image.
;
PROC		DriverDrawImage
		pushad					; Save context
		mov	ebx,edx				; EBX = Y coordinate
		mov	edx,ecx				; EDX = X coodinate
		mov	ecx,esi				; ECX = height
		mov	esi,[(REGS esp).EBX]		; ESI = pointer to image
		;
		; Invoke function handler
		;
		call	FrameBufferDrawImage WATCOM_C,?,?,?,?,edi,esi
		or	eax,eax				; Success ?
		jz	SHORT @@Exit			; Yes, we are done
		cmp	eax,-1				; Function supported ?
		jnz	SHORT @@Error			; Yes, error
		popad					; No, restore context
		jmp	[Draw]				; Use default function
@@Error:	neg	eax				; EAX = error code
		mov	[BYTE (REGS esp + 1).EAX],al	; Update callers AH
		stc					; Set carry flag
@@Exit:		popad					; Restore context
		ret
ENDP
;
; PROCEDURE	DriverCursorOn
;
; INPUT		NONE
;
; OUTPUT	 CF = 0: cursor enabled
;		 CF = 1: AH = error code
;
; DESCRIPTION	Enables the cursor.
;
PROC		DriverCursorOn
		pushad					; Save context
		call	FrameBufferCursorOn WATCOM_C	; Invoke function handler
		or	eax,eax				; Success ?
		jz	SHORT @@Exit			; Yes, we are done
		cmp	eax,-1				; Function supported ?
		jnz	SHORT @@Error			; Yes, error
		popad					; No, restore context
		jmp	[Enable]			; Use default function
@@Error:	neg	eax				; EAX = error code
		mov	[BYTE (REGS esp + 1).EAX],al	; Update callers AH
		stc					; Set carry flag
@@Exit:		popad					; Restore context
		ret
ENDP
;
; PROCEDURE	DriverCursorOff
;
; INPUT		NONE
;
; OUTPUT	 CF = 0: cursor disabled
;		 CF = 1: AH = error code
;
; DESCRIPTION	Disables the cursor.
;
PROC		DriverCursorOff
		pushad					; Save context
		call	FrameBufferCursorOff WATCOM_C	; Invoke function handler
		or	eax,eax				; Success ?
		jz	SHORT @@Exit			; Yes, we are done
		cmp	eax,-1				; Function supported ?
		jnz	SHORT @@Error			; Yes, error
		popad					; No, restore context
		jmp	[Disable]			; Use default function
@@Error:	neg	eax				; EAX = error code
		mov	[BYTE (REGS esp + 1).EAX],al	; Update callers AH
		stc					; Set carry flag
@@Exit:		popad					; Restore context
		ret
ENDP
;
; PROCEDURE	DriverCursorShape
;
; INPUT		 BL = X hotspot
;		 BH = Y hotspot
;		ECX = color 0
;		EDX = color 1
;		ESI = pointer to cursor image
;		EDI = cursor size
;
; OUTPUT	CF = 0: cursor shape updated
;		CF = 1: AH = error code
;
; DESCRIPTION	Sets cursor shape and hot spots.
;
PROC		DriverCursorShape
		pushad					; Save context
		movzx	edx,bh				; EDX = hotspot Y
		movzx	eax,bl				; EAX = hotspot X
		mov	ebx,ecx				; EBX = color 0
		mov	ecx,[(REGS esp).EDX]		; ECX = color 1
		;
		; Invoke function handler
		;
		call	FrameBufferCursorShape WATCOM_C,?,?,?,?,esi,edi
		or	eax,eax				; Success ?
		jz	SHORT @@Exit			; Yes, we are done
		cmp	eax,-1				; Function supported ?
		jnz	SHORT @@Error			; Yes, error
		popad					; No, restore context
		jmp	[Shape]				; Use default function
@@Error:	neg	eax				; EAX = error code
		mov	[BYTE (REGS esp + 1).EAX],al	; Update callers AH
		stc					; Set carry flag
@@Exit:		popad					; Restore context
		ret
ENDP
;
; PROCEDURE	DriverCursorPosition
;
; INPUT		ECX = X coordinate
;		EDX = Y coordinate
;
; OUTPUT	CF = 0: cursor position updated
;		CF = 1: AH = error code
;
; DESCRIPTION	Sets cursor position.
;
PROC		DriverCursorPosition
		pushad					; Save context
		mov	eax,ecx				; EAX = X coordinate
		;
		; Invoke function handler
		;
		call	FrameBufferCursorPosition WATCOM_C,?,?
		or	eax,eax				; Success ?
		jz	SHORT @@Exit			; Yes, we are done
		cmp	eax,-1				; Function supported ?
		jnz	SHORT @@Error			; Yes, error
		popad					; No, restore context
		jmp	[Position]			; Use default function
@@Error:	neg	eax				; EAX = error code
		mov	[BYTE (REGS esp + 1).EAX],al	; Update callers AH
		stc					; Set carry flag
@@Exit:		popad					; Restore context
		ret
ENDP
;
; PROCEDURE	DriverSetPalette
;
; INPUT		EAX = register index
;               EBX = red color
;		ECX = green color
;		EDX = blue color
;
; OUTPUT	CF = 0: palette color updated successfully
;		CF = 1: AH = error code
;
; DESCRIPTION	Sets a single palette register.
;
PROC		DriverSetPalette
		pushad					; Save context
		;
		; Invoke function handler
		;
		call	FrameBufferSetPalette WATCOM_C,?,?,?,?
		or	eax,eax				; Success ?
		jz	SHORT @@Exit			; Yes, we are done
		cmp	eax,-1				; Function supported ?
		jnz	SHORT @@Error			; Yes, error
		popad					; No, restore context
		jmp	[Palette]			; Use default function
@@Error:	neg	eax				; EAX = error code
		mov	[BYTE (REGS esp + 1).EAX],al	; Update callers AH
		stc					; Set carry flag
@@Exit:		popad					; Restore context
		ret
ENDP
;
; PROCEDURE	DriverWaitEngine2D
;
; INPUT		NONE
;
; OUTPUT	CF = 0: 2D engine ready
;		CF = 1: AH = error code
;
; DESCRIPTION	Waits for 2D engine to go ready.
;
PROC		DriverWaitEngine2D
		pushad					; Save context
		call	FrameBufferWaitEngine2D WATCOM_C; Invoke function handler
		or	eax,eax				; Success ?
		jz	SHORT @@Exit			; Yes, we are done
		cmp	eax,-1				; Function supported ?
		jnz	SHORT @@Error			; Yes, error
		popad					; No, restore context
		jmp	[Engine2D]			; Use default function
@@Error:	neg	eax				; EAX = error code
		mov	[BYTE (REGS esp + 1).EAX],al	; Update callers AH
		stc					; Set carry flag
@@Exit:		popad					; Restore context
		ret
ENDP
		DATASEG
Fill		DD	DriverFillRectangle
Copy		DD	DriverCopyRectangle
Draw		DD	DriverDrawImage
Enable		DD	DriverCursorOn
Disable		DD	DriverCursorOff
Shape		DD	DriverCursorShape
Position	DD	DriverCursorPosition
Palette		DD	DriverSetPalette
Engine2D	DD	DriverWaitEngine2D
		END
