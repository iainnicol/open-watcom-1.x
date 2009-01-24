		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		INCLUDE	'REGS.INC'
		CODESEG
 		EXTRN	FrameBufferFillRectangle_	: PROC
		EXTRN	FrameBufferCopyRectangle_	: PROC
		EXTRN	FrameBufferDrawImage_		: PROC
		EXTRN	FrameBufferCursorOn_		: PROC
		EXTRN	FrameBufferCursorOff_		: PROC
		EXTRN	FrameBufferCursorShape_		: PROC
		EXTRN	FrameBufferCursorPosition_	: PROC
		EXTRN	FrameBufferSetPalette_		: PROC
		EXTRN	FrameBufferWaitEngine2D_	: PROC
		PUBLIC	DosFrameBufferInstallDriver_
;
; DECLARATION	int DosFrameBufferInstallDriver( void );
;
PROC		DosFrameBufferInstallDriver_	STDCALL
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
; PROCEDURE	FrameBufferFillRectangle
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
PROC		FrameBufferFillRectangle
		pushad					; Save context
		mov	ecx,edx				; ECX = X coordinate
		mov	edx,eax				; EDX = color
		mov	eax,ebx				; EAX = raster operation
		mov	ebx,[(REGS esp).EDX]		; EBX = Y coordinate
		;
		; Invoke function handler
		;
		call	FrameBufferFillRectangle_ STDCALL,esi,edi
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
; PROCEDURE	FrameBufferCopyRectangle
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
PROC		FrameBufferCopyRectangle
		pushad					; Save context
		xchg	eax,ebp				; EAX = raster operation, EBP = destination X coordinate
		mov	ebx,edx				; EBX = source Y coordinate
		mov	edx,ecx				; EDX = source X coordinate
		mov	ecx,esi				; ECX = height
		mov	esi,[(REGS esp).EBX]		; ESI = destination Y coordinate
		;
		; Invoke function handler
		;
		call	FrameBufferCopyRectangle_ STDCALL,edi,ebp,esi
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
; PROCEDURE	FrameBufferDrawImage
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
PROC		FrameBufferDrawImage
		pushad					; Save context
		mov	ebx,edx				; EBX = Y coordinate
		mov	edx,ecx				; EDX = X coodinate
		mov	ecx,esi				; ECX = height
		mov	esi,[(REGS esp).EBX]		; ESI = pointer to image
		;
		; Invoke function handler
		;
		call	FrameBufferDrawImage_ STDCALL,edi,esi
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
; PROCEDURE	FrameBufferCursorOn
;
; INPUT		NONE
;
; OUTPUT	 CF = 0: cursor enabled
;		 CF = 1: AH = error code
;
; DESCRIPTION	Enables the cursor.
;
PROC		FrameBufferCursorOn
		pushad					; Save context
		call	FrameBufferCursorOn_		; Invoke function handler
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
; PROCEDURE	FrameBufferCursorOff
;
; INPUT		NONE
;
; OUTPUT	 CF = 0: cursor disabled
;		 CF = 1: AH = error code
;
; DESCRIPTION	Disables the cursor.
;
PROC		FrameBufferCursorOff
		pushad					; Save context
		call	FrameBufferCursorOff_		; Invoke function handler
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
; PROCEDURE	FrameBufferCursorShape
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
PROC		FrameBufferCursorShape
		pushad					; Save context
		movzx	edx,bh				; EDX = hotspot Y
		movzx	eax,bl				; EAX = hotspot X
		mov	ebx,ecx				; EBX = color 0
		mov	ecx,[(REGS esp).EDX]		; ECX = color 1
		;
		; Invoke function handler
		;
		call	FrameBufferCursorShape_ STDCALL,esi,edi
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
; PROCEDURE	FrameBufferCursorPosition
;
; INPUT		ECX = X coordinate
;		EDX = Y coordinate
;
; OUTPUT	CF = 0: cursor position updated
;		CF = 1: AH = error code
;
; DESCRIPTION	Sets cursor position.
;
PROC		FrameBufferCursorPosition
		pushad					; Save context
		mov	eax,ecx				; EAX = X coordinate
		call	FrameBufferCursorPosition_	; Invoke function handler
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
; PROCEDURE	FrameBufferSetPalette
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
PROC		FrameBufferSetPalette
		pushad					; Save context
		call	FrameBufferSetPalette_		; Invoke function handler
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
; PROCEDURE	FrameBufferWaitEngine2D
;
; INPUT		NONE
;
; OUTPUT	CF = 0: 2D engine ready
;		CF = 1: AH = error code
;
; DESCRIPTION	Waits for 2D engine to go ready.
;
PROC		FrameBufferWaitEngine2D
		pushad					; Save context
		call	FrameBufferWaitEngine2D_	; Invoke function handler
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
Fill		DD	FrameBufferFillRectangle
Copy		DD	FrameBufferCopyRectangle
Draw		DD	FrameBufferDrawImage
Enable		DD	FrameBufferCursorOn
Disable		DD	FrameBufferCursorOff
Shape		DD	FrameBufferCursorShape
Position	DD	FrameBufferCursorPosition
Palette		DD	FrameBufferSetPalette
Engine2D	DD	FrameBufferWaitEngine2D
		END
