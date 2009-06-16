;
; ZDOS run time library function.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
IFDEF __ZDOSDRV__
		CODESEG
;
; PROCEDURE	Service00h
;
; DESCRIPTION	Handles service vector 00h
;
PROC		Service00h
		pushad					; Save context
		xor	ebx,ebx				; EBX = service vector number
LABEL		InvokeHandler		PROC
		push	0				; Initialize flags
		call	[UserVector + ebx * 4]		; Invoke C service handler
		pop	eax				; AL = flags
		mov	ah,al				; AH = flags
		sahf					; Update flags
		popad					; Restore context
		ret
ENDP
;
; PROCEDURE	Service01h
;
; DESCRIPTION	Handles service vector 01h
;
PROC		Service01h
		pushad					; Save context
		mov	ebx,01h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service02h
;
; DESCRIPTION	Handles service vector 02h
;
PROC		Service02h
		pushad					; Save context
		mov	ebx,02h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service03h
;
; DESCRIPTION	Handles service vector 03h
;
PROC		Service03h
		pushad					; Save context
		mov	ebx,03h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service04h
;
; DESCRIPTION	Handles service vector 04h
;
PROC		Service04h
		pushad					; Save context
		mov	ebx,04h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service05h
;
; DESCRIPTION	Handles service vector 05h
;
PROC		Service05h
		pushad					; Save context
		mov	ebx,05h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service06h
;
; DESCRIPTION	Handles service vector 06h
;
PROC		Service06h
		pushad					; Save context
		mov	ebx,06h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service07h
;
; DESCRIPTION	Handles service vector 07h
;
PROC		Service07h
		pushad					; Save context
		mov	ebx,07h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service08h
;
; DESCRIPTION	Handles service vector 08h
;
PROC		Service08h
		pushad					; Save context
		mov	ebx,08h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service09h
;
; DESCRIPTION	Handles service vector 09h
;
PROC		Service09h
		pushad					; Save context
		mov	ebx,09h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0ah
;
; DESCRIPTION	Handles service vector 0ah
;
PROC		Service0ah
		pushad					; Save context
		mov	ebx,0ah				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0bh
;
; DESCRIPTION	Handles service vector 0bh
;
PROC		Service0bh
		pushad					; Save context
		mov	ebx,0bh				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0ch
;
; DESCRIPTION	Handles service vector 0ch
;
PROC		Service0ch
		pushad					; Save context
		mov	ebx,0ch				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0dh
;
; DESCRIPTION	Handles service vector 0dh
;
PROC		Service0dh
		pushad					; Save context
		mov	ebx,0dh				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0eh
;
; DESCRIPTION	Handles service vector 0eh
;
PROC		Service0eh
		pushad					; Save context
		mov	ebx,0eh				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0fh
;
; DESCRIPTION	Handles service vector 0fh
;
PROC		Service0fh
		pushad					; Save context
		mov	ebx,0fh				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service10h
;
; DESCRIPTION	Handles service vector 10h
;
PROC		Service10h
		pushad					; Save context
		mov	ebx,10h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service11h
;
; DESCRIPTION	Handles service vector 11h
;
PROC		Service11h
		pushad					; Save context
		mov	ebx,11h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service12h
;
; DESCRIPTION	Handles service vector 12h
;
PROC		Service12h
		pushad					; Save context
		mov	ebx,12h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service13h
;
; DESCRIPTION	Handles service vector 13h
;
PROC		Service13h
		pushad					; Save context
		mov	ebx,13h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service14h
;
; DESCRIPTION	Handles service vector 14h
;
PROC		Service14h
		pushad					; Save context
		mov	ebx,14h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service15h
;
; DESCRIPTION	Handles service vector 15h
;
PROC		Service15h
		pushad					; Save context
		mov	ebx,15h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service16h
;
; DESCRIPTION	Handles service vector 16h
;
PROC		Service16h
		pushad					; Save context
		mov	ebx,16h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service17h
;
; DESCRIPTION	Handles service vector 17h
;
PROC		Service17h
		pushad					; Save context
		mov	ebx,17h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service18h
;
; DESCRIPTION	Handles service vector 18h
;
PROC		Service18h
		pushad					; Save context
		mov	ebx,18h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service19h
;
; DESCRIPTION	Handles service vector 19h
;
PROC		Service19h
		pushad					; Save context
		mov	ebx,19h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service1ah
;
; DESCRIPTION	Handles service vector 1ah
;
PROC		Service1ah
		pushad					; Save context
		mov	ebx,1ah				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service1bh
;
; DESCRIPTION	Handles service vector 1bh
;
PROC		Service1bh
		pushad					; Save context
		mov	ebx,1bh				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service1ch
;
; DESCRIPTION	Handles service vector 1ch
;
PROC		Service1ch
		pushad					; Save context
		mov	ebx,1ch				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service1dh
;
; DESCRIPTION	Handles service vector 1dh
;
PROC		Service1dh
		pushad					; Save context
		mov	ebx,1dh				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service1eh
;
; DESCRIPTION	Handles service vector 1eh
;
PROC		Service1eh
		pushad					; Save context
		mov	ebx,1eh				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service1fh
;
; DESCRIPTION	Handles service vector 1fh
;
PROC		Service1fh
		pushad					; Save context
		mov	ebx,1fh				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service20h
;
; DESCRIPTION	Handles service vector 20h
;
PROC		Service20h
		pushad					; Save context
		mov	ebx,20h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service21h
;
; DESCRIPTION	Handles service vector 21h
;
PROC		Service21h
		pushad					; Save context
		mov	ebx,21h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service22h
;
; DESCRIPTION	Handles service vector 22h
;
PROC		Service22h
		pushad					; Save context
		mov	ebx,22h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service23h
;
; DESCRIPTION	Handles service vector 23h
;
PROC		Service23h
		pushad					; Save context
		mov	ebx,23h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service24h
;
; DESCRIPTION	Handles service vector 24h
;
PROC		Service24h
		pushad					; Save context
		mov	ebx,24h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service25h
;
; DESCRIPTION	Handles service vector 25h
;
PROC		Service25h
		pushad					; Save context
		mov	ebx,25h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service26h
;
; DESCRIPTION	Handles service vector 26h
;
PROC		Service26h
		pushad					; Save context
		mov	ebx,26h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service27h
;
; DESCRIPTION	Handles service vector 27h
;
PROC		Service27h
		pushad					; Save context
		mov	ebx,27h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service28h
;
; DESCRIPTION	Handles service vector 28h
;
PROC		Service28h
		pushad					; Save context
		mov	ebx,28h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service29h
;
; DESCRIPTION	Handles service vector 29h
;
PROC		Service29h
		pushad					; Save context
		mov	ebx,29h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service2ah
;
; DESCRIPTION	Handles service vector 2ah
;
PROC		Service2ah
		pushad					; Save context
		mov	ebx,2ah				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service2bh
;
; DESCRIPTION	Handles service vector 2bh
;
PROC		Service2bh
		pushad					; Save context
		mov	ebx,2bh				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service2ch
;
; DESCRIPTION	Handles service vector 2ch
;
PROC		Service2ch
		pushad					; Save context
		mov	ebx,2ch				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service2dh
;
; DESCRIPTION	Handles service vector 2dh
;
PROC		Service2dh
		pushad					; Save context
		mov	ebx,2dh				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service2eh
;
; DESCRIPTION	Handles service vector 2eh
;
PROC		Service2eh
		pushad					; Save context
		mov	ebx,2eh				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service2fh
;
; DESCRIPTION	Handles service vector 2fh
;
PROC		Service2fh
		pushad					; Save context
		mov	ebx,2fh				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service30h
;
; DESCRIPTION	Handles service vector 30h
;
PROC		Service30h
		pushad					; Save context
		mov	ebx,30h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service31h
;
; DESCRIPTION	Handles service vector 31h
;
PROC		Service31h
		pushad					; Save context
		mov	ebx,31h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service32h
;
; DESCRIPTION	Handles service vector 32h
;
PROC		Service32h
		pushad					; Save context
		mov	ebx,32h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service33h
;
; DESCRIPTION	Handles service vector 33h
;
PROC		Service33h
		pushad					; Save context
		mov	ebx,33h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service34h
;
; DESCRIPTION	Handles service vector 34h
;
PROC		Service34h
		pushad					; Save context
		mov	ebx,34h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service35h
;
; DESCRIPTION	Handles service vector 35h
;
PROC		Service35h
		pushad					; Save context
		mov	ebx,35h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service36h
;
; DESCRIPTION	Handles service vector 36h
;
PROC		Service36h
		pushad					; Save context
		mov	ebx,36h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service37h
;
; DESCRIPTION	Handles service vector 37h
;
PROC		Service37h
		pushad					; Save context
		mov	ebx,37h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service38h
;
; DESCRIPTION	Handles service vector 38h
;
PROC		Service38h
		pushad					; Save context
		mov	ebx,38h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service39h
;
; DESCRIPTION	Handles service vector 39h
;
PROC		Service39h
		pushad					; Save context
		mov	ebx,39h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service3ah
;
; DESCRIPTION	Handles service vector 3ah
;
PROC		Service3ah
		pushad					; Save context
		mov	ebx,3ah				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service3bh
;
; DESCRIPTION	Handles service vector 3bh
;
PROC		Service3bh
		pushad					; Save context
		mov	ebx,3bh				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service3ch
;
; DESCRIPTION	Handles service vector 3ch
;
PROC		Service3ch
		pushad					; Save context
		mov	ebx,3ch				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service3dh
;
; DESCRIPTION	Handles service vector 3dh
;
PROC		Service3dh
		pushad					; Save context
		mov	ebx,3dh				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service3eh
;
; DESCRIPTION	Handles service vector 3eh
;
PROC		Service3eh
		pushad					; Save context
		mov	ebx,3eh				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service3fh
;
; DESCRIPTION	Handles service vector 3fh
;
PROC		Service3fh
		pushad					; Save context
		mov	ebx,3fh				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service40h
;
; DESCRIPTION	Handles service vector 40h
;
PROC		Service40h
		pushad					; Save context
		mov	ebx,40h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service41h
;
; DESCRIPTION	Handles service vector 41h
;
PROC		Service41h
		pushad					; Save context
		mov	ebx,41h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service42h
;
; DESCRIPTION	Handles service vector 42h
;
PROC		Service42h
		pushad					; Save context
		mov	ebx,42h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service43h
;
; DESCRIPTION	Handles service vector 43h
;
PROC		Service43h
		pushad					; Save context
		mov	ebx,43h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service44h
;
; DESCRIPTION	Handles service vector 44h
;
PROC		Service44h
		pushad					; Save context
		mov	ebx,44h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service45h
;
; DESCRIPTION	Handles service vector 45h
;
PROC		Service45h
		pushad					; Save context
		mov	ebx,45h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service46h
;
; DESCRIPTION	Handles service vector 46h
;
PROC		Service46h
		pushad					; Save context
		mov	ebx,46h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service47h
;
; DESCRIPTION	Handles service vector 47h
;
PROC		Service47h
		pushad					; Save context
		mov	ebx,47h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service48h
;
; DESCRIPTION	Handles service vector 48h
;
PROC		Service48h
		pushad					; Save context
		mov	ebx,48h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service49h
;
; DESCRIPTION	Handles service vector 49h
;
PROC		Service49h
		pushad					; Save context
		mov	ebx,49h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service4ah
;
; DESCRIPTION	Handles service vector 4ah
;
PROC		Service4ah
		pushad					; Save context
		mov	ebx,4ah				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service4bh
;
; DESCRIPTION	Handles service vector 4bh
;
PROC		Service4bh
		pushad					; Save context
		mov	ebx,4bh				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service4ch
;
; DESCRIPTION	Handles service vector 4ch
;
PROC		Service4ch
		pushad					; Save context
		mov	ebx,4ch				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service4dh
;
; DESCRIPTION	Handles service vector 4dh
;
PROC		Service4dh
		pushad					; Save context
		mov	ebx,4dh				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service4eh
;
; DESCRIPTION	Handles service vector 4eh
;
PROC		Service4eh
		pushad					; Save context
		mov	ebx,4eh				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service4fh
;
; DESCRIPTION	Handles service vector 4fh
;
PROC		Service4fh
		pushad					; Save context
		mov	ebx,4fh				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service50h
;
; DESCRIPTION	Handles service vector 50h
;
PROC		Service50h
		pushad					; Save context
		mov	ebx,50h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service51h
;
; DESCRIPTION	Handles service vector 51h
;
PROC		Service51h
		pushad					; Save context
		mov	ebx,51h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service52h
;
; DESCRIPTION	Handles service vector 52h
;
PROC		Service52h
		pushad					; Save context
		mov	ebx,52h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service53h
;
; DESCRIPTION	Handles service vector 53h
;
PROC		Service53h
		pushad					; Save context
		mov	ebx,53h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service54h
;
; DESCRIPTION	Handles service vector 54h
;
PROC		Service54h
		pushad					; Save context
		mov	ebx,54h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service55h
;
; DESCRIPTION	Handles service vector 55h
;
PROC		Service55h
		pushad					; Save context
		mov	ebx,55h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service56h
;
; DESCRIPTION	Handles service vector 56h
;
PROC		Service56h
		pushad					; Save context
		mov	ebx,56h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service57h
;
; DESCRIPTION	Handles service vector 57h
;
PROC		Service57h
		pushad					; Save context
		mov	ebx,57h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service58h
;
; DESCRIPTION	Handles service vector 58h
;
PROC		Service58h
		pushad					; Save context
		mov	ebx,58h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service59h
;
; DESCRIPTION	Handles service vector 59h
;
PROC		Service59h
		pushad					; Save context
		mov	ebx,59h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service5ah
;
; DESCRIPTION	Handles service vector 5ah
;
PROC		Service5ah
		pushad					; Save context
		mov	ebx,5ah				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service5bh
;
; DESCRIPTION	Handles service vector 5bh
;
PROC		Service5bh
		pushad					; Save context
		mov	ebx,5bh				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service5ch
;
; DESCRIPTION	Handles service vector 5ch
;
PROC		Service5ch
		pushad					; Save context
		mov	ebx,5ch				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service5dh
;
; DESCRIPTION	Handles service vector 5dh
;
PROC		Service5dh
		pushad					; Save context
		mov	ebx,5dh				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service5eh
;
; DESCRIPTION	Handles service vector 5eh
;
PROC		Service5eh
		pushad					; Save context
		mov	ebx,5eh				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service5fh
;
; DESCRIPTION	Handles service vector 5fh
;
PROC		Service5fh
		pushad					; Save context
		mov	ebx,5fh				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service60h
;
; DESCRIPTION	Handles service vector 60h
;
PROC		Service60h
		pushad					; Save context
		mov	ebx,60h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service61h
;
; DESCRIPTION	Handles service vector 61h
;
PROC		Service61h
		pushad					; Save context
		mov	ebx,61h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service62h
;
; DESCRIPTION	Handles service vector 62h
;
PROC		Service62h
		pushad					; Save context
		mov	ebx,62h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service63h
;
; DESCRIPTION	Handles service vector 63h
;
PROC		Service63h
		pushad					; Save context
		mov	ebx,63h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service64h
;
; DESCRIPTION	Handles service vector 64h
;
PROC		Service64h
		pushad					; Save context
		mov	ebx,64h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service65h
;
; DESCRIPTION	Handles service vector 65h
;
PROC		Service65h
		pushad					; Save context
		mov	ebx,65h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service66h
;
; DESCRIPTION	Handles service vector 66h
;
PROC		Service66h
		pushad					; Save context
		mov	ebx,66h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service67h
;
; DESCRIPTION	Handles service vector 67h
;
PROC		Service67h
		pushad					; Save context
		mov	ebx,67h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service68h
;
; DESCRIPTION	Handles service vector 68h
;
PROC		Service68h
		pushad					; Save context
		mov	ebx,68h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service69h
;
; DESCRIPTION	Handles service vector 69h
;
PROC		Service69h
		pushad					; Save context
		mov	ebx,69h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service6ah
;
; DESCRIPTION	Handles service vector 6ah
;
PROC		Service6ah
		pushad					; Save context
		mov	ebx,6ah				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service6bh
;
; DESCRIPTION	Handles service vector 6bh
;
PROC		Service6bh
		pushad					; Save context
		mov	ebx,6bh				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service6ch
;
; DESCRIPTION	Handles service vector 6ch
;
PROC		Service6ch
		pushad					; Save context
		mov	ebx,6ch				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service6dh
;
; DESCRIPTION	Handles service vector 6dh
;
PROC		Service6dh
		pushad					; Save context
		mov	ebx,6dh				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service6eh
;
; DESCRIPTION	Handles service vector 6eh
;
PROC		Service6eh
		pushad					; Save context
		mov	ebx,6eh				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service6fh
;
; DESCRIPTION	Handles service vector 6fh
;
PROC		Service6fh
		pushad					; Save context
		mov	ebx,6fh				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service70h
;
; DESCRIPTION	Handles service vector 70h
;
PROC		Service70h
		pushad					; Save context
		mov	ebx,70h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service71h
;
; DESCRIPTION	Handles service vector 71h
;
PROC		Service71h
		pushad					; Save context
		mov	ebx,71h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service72h
;
; DESCRIPTION	Handles service vector 72h
;
PROC		Service72h
		pushad					; Save context
		mov	ebx,72h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service73h
;
; DESCRIPTION	Handles service vector 73h
;
PROC		Service73h
		pushad					; Save context
		mov	ebx,73h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service74h
;
; DESCRIPTION	Handles service vector 74h
;
PROC		Service74h
		pushad					; Save context
		mov	ebx,74h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service75h
;
; DESCRIPTION	Handles service vector 75h
;
PROC		Service75h
		pushad					; Save context
		mov	ebx,75h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service76h
;
; DESCRIPTION	Handles service vector 76h
;
PROC		Service76h
		pushad					; Save context
		mov	ebx,76h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service77h
;
; DESCRIPTION	Handles service vector 77h
;
PROC		Service77h
		pushad					; Save context
		mov	ebx,77h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service78h
;
; DESCRIPTION	Handles service vector 78h
;
PROC		Service78h
		pushad					; Save context
		mov	ebx,78h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service79h
;
; DESCRIPTION	Handles service vector 79h
;
PROC		Service79h
		pushad					; Save context
		mov	ebx,79h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service7ah
;
; DESCRIPTION	Handles service vector 7ah
;
PROC		Service7ah
		pushad					; Save context
		mov	ebx,7ah				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service7bh
;
; DESCRIPTION	Handles service vector 7bh
;
PROC		Service7bh
		pushad					; Save context
		mov	ebx,7bh				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service7ch
;
; DESCRIPTION	Handles service vector 7ch
;
PROC		Service7ch
		pushad					; Save context
		mov	ebx,7ch				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service7dh
;
; DESCRIPTION	Handles service vector 7dh
;
PROC		Service7dh
		pushad					; Save context
		mov	ebx,7dh				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service7eh
;
; DESCRIPTION	Handles service vector 7eh
;
PROC		Service7eh
		pushad					; Save context
		mov	ebx,7eh				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service7fh
;
; DESCRIPTION	Handles service vector 7fh
;
PROC		Service7fh
		pushad					; Save context
		mov	ebx,7fh				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service80h
;
; DESCRIPTION	Handles service vector 80h
;
PROC		Service80h
		pushad					; Save context
		mov	ebx,80h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service81h
;
; DESCRIPTION	Handles service vector 81h
;
PROC		Service81h
		pushad					; Save context
		mov	ebx,81h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service82h
;
; DESCRIPTION	Handles service vector 82h
;
PROC		Service82h
		pushad					; Save context
		mov	ebx,82h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service83h
;
; DESCRIPTION	Handles service vector 83h
;
PROC		Service83h
		pushad					; Save context
		mov	ebx,83h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service84h
;
; DESCRIPTION	Handles service vector 84h
;
PROC		Service84h
		pushad					; Save context
		mov	ebx,84h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service85h
;
; DESCRIPTION	Handles service vector 85h
;
PROC		Service85h
		pushad					; Save context
		mov	ebx,85h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service86h
;
; DESCRIPTION	Handles service vector 86h
;
PROC		Service86h
		pushad					; Save context
		mov	ebx,86h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service87h
;
; DESCRIPTION	Handles service vector 87h
;
PROC		Service87h
		pushad					; Save context
		mov	ebx,87h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service88h
;
; DESCRIPTION	Handles service vector 88h
;
PROC		Service88h
		pushad					; Save context
		mov	ebx,88h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service89h
;
; DESCRIPTION	Handles service vector 89h
;
PROC		Service89h
		pushad					; Save context
		mov	ebx,89h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service8ah
;
; DESCRIPTION	Handles service vector 8ah
;
PROC		Service8ah
		pushad					; Save context
		mov	ebx,8ah				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service8bh
;
; DESCRIPTION	Handles service vector 8bh
;
PROC		Service8bh
		pushad					; Save context
		mov	ebx,8bh				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service8ch
;
; DESCRIPTION	Handles service vector 8ch
;
PROC		Service8ch
		pushad					; Save context
		mov	ebx,8ch				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service8dh
;
; DESCRIPTION	Handles service vector 8dh
;
PROC		Service8dh
		pushad					; Save context
		mov	ebx,8dh				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service8eh
;
; DESCRIPTION	Handles service vector 8eh
;
PROC		Service8eh
		pushad					; Save context
		mov	ebx,8eh				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service8fh
;
; DESCRIPTION	Handles service vector 8fh
;
PROC		Service8fh
		pushad					; Save context
		mov	ebx,8fh				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service90h
;
; DESCRIPTION	Handles service vector 90h
;
PROC		Service90h
		pushad					; Save context
		mov	ebx,90h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service91h
;
; DESCRIPTION	Handles service vector 91h
;
PROC		Service91h
		pushad					; Save context
		mov	ebx,91h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service92h
;
; DESCRIPTION	Handles service vector 92h
;
PROC		Service92h
		pushad					; Save context
		mov	ebx,92h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service93h
;
; DESCRIPTION	Handles service vector 93h
;
PROC		Service93h
		pushad					; Save context
		mov	ebx,93h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service94h
;
; DESCRIPTION	Handles service vector 94h
;
PROC		Service94h
		pushad					; Save context
		mov	ebx,94h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service95h
;
; DESCRIPTION	Handles service vector 95h
;
PROC		Service95h
		pushad					; Save context
		mov	ebx,95h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service96h
;
; DESCRIPTION	Handles service vector 96h
;
PROC		Service96h
		pushad					; Save context
		mov	ebx,96h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service97h
;
; DESCRIPTION	Handles service vector 97h
;
PROC		Service97h
		pushad					; Save context
		mov	ebx,97h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service98h
;
; DESCRIPTION	Handles service vector 98h
;
PROC		Service98h
		pushad					; Save context
		mov	ebx,98h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service99h
;
; DESCRIPTION	Handles service vector 99h
;
PROC		Service99h
		pushad					; Save context
		mov	ebx,99h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service9ah
;
; DESCRIPTION	Handles service vector 9ah
;
PROC		Service9ah
		pushad					; Save context
		mov	ebx,9ah				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service9bh
;
; DESCRIPTION	Handles service vector 9bh
;
PROC		Service9bh
		pushad					; Save context
		mov	ebx,9bh				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service9ch
;
; DESCRIPTION	Handles service vector 9ch
;
PROC		Service9ch
		pushad					; Save context
		mov	ebx,9ch				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service9dh
;
; DESCRIPTION	Handles service vector 9dh
;
PROC		Service9dh
		pushad					; Save context
		mov	ebx,9dh				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service9eh
;
; DESCRIPTION	Handles service vector 9eh
;
PROC		Service9eh
		pushad					; Save context
		mov	ebx,9eh				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service9fh
;
; DESCRIPTION	Handles service vector 9fh
;
PROC		Service9fh
		pushad					; Save context
		mov	ebx,9fh				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0a0h
;
; DESCRIPTION	Handles service vector 0a0h
;
PROC		Service0a0h
		pushad					; Save context
		mov	ebx,0a0h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0a1h
;
; DESCRIPTION	Handles service vector 0a1h
;
PROC		Service0a1h
		pushad					; Save context
		mov	ebx,0a1h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0a2h
;
; DESCRIPTION	Handles service vector 0a2h
;
PROC		Service0a2h
		pushad					; Save context
		mov	ebx,0a2h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0a3h
;
; DESCRIPTION	Handles service vector 0a3h
;
PROC		Service0a3h
		pushad					; Save context
		mov	ebx,0a3h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0a4h
;
; DESCRIPTION	Handles service vector 0a4h
;
PROC		Service0a4h
		pushad					; Save context
		mov	ebx,0a4h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0a5h
;
; DESCRIPTION	Handles service vector 0a5h
;
PROC		Service0a5h
		pushad					; Save context
		mov	ebx,0a5h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0a6h
;
; DESCRIPTION	Handles service vector 0a6h
;
PROC		Service0a6h
		pushad					; Save context
		mov	ebx,0a6h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0a7h
;
; DESCRIPTION	Handles service vector 0a7h
;
PROC		Service0a7h
		pushad					; Save context
		mov	ebx,0a7h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0a8h
;
; DESCRIPTION	Handles service vector 0a8h
;
PROC		Service0a8h
		pushad					; Save context
		mov	ebx,0a8h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0a9h
;
; DESCRIPTION	Handles service vector 0a9h
;
PROC		Service0a9h
		pushad					; Save context
		mov	ebx,0a9h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0aah
;
; DESCRIPTION	Handles service vector 0aah
;
PROC		Service0aah
		pushad					; Save context
		mov	ebx,0aah			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0abh
;
; DESCRIPTION	Handles service vector 0abh
;
PROC		Service0abh
		pushad					; Save context
		mov	ebx,0abh			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0ach
;
; DESCRIPTION	Handles service vector 0ach
;
PROC		Service0ach
		pushad					; Save context
		mov	ebx,0ach			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0adh
;
; DESCRIPTION	Handles service vector 0adh
;
PROC		Service0adh
		pushad					; Save context
		mov	ebx,0adh			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0aeh
;
; DESCRIPTION	Handles service vector 0aeh
;
PROC		Service0aeh
		pushad					; Save context
		mov	ebx,0aeh			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0afh
;
; DESCRIPTION	Handles service vector 0afh
;
PROC		Service0afh
		pushad					; Save context
		mov	ebx,0afh			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0b0h
;
; DESCRIPTION	Handles service vector 0b0h
;
PROC		Service0b0h
		pushad					; Save context
		mov	ebx,0b0h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0b1h
;
; DESCRIPTION	Handles service vector 0b1h
;
PROC		Service0b1h
		pushad					; Save context
		mov	ebx,0b1h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0b2h
;
; DESCRIPTION	Handles service vector 0b2h
;
PROC		Service0b2h
		pushad					; Save context
		mov	ebx,0b2h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0b3h
;
; DESCRIPTION	Handles service vector 0b3h
;
PROC		Service0b3h
		pushad					; Save context
		mov	ebx,0b3h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0b4h
;
; DESCRIPTION	Handles service vector 0b4h
;
PROC		Service0b4h
		pushad					; Save context
		mov	ebx,0b4h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0b5h
;
; DESCRIPTION	Handles service vector 0b5h
;
PROC		Service0b5h
		pushad					; Save context
		mov	ebx,0b5h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0b6h
;
; DESCRIPTION	Handles service vector 0b6h
;
PROC		Service0b6h
		pushad					; Save context
		mov	ebx,0b6h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0b7h
;
; DESCRIPTION	Handles service vector 0b7h
;
PROC		Service0b7h
		pushad					; Save context
		mov	ebx,0b7h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0b8h
;
; DESCRIPTION	Handles service vector 0b8h
;
PROC		Service0b8h
		pushad					; Save context
		mov	ebx,0b8h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0b9h
;
; DESCRIPTION	Handles service vector 0b9h
;
PROC		Service0b9h
		pushad					; Save context
		mov	ebx,0b9h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0bah
;
; DESCRIPTION	Handles service vector 0bah
;
PROC		Service0bah
		pushad					; Save context
		mov	ebx,0bah			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0bbh
;
; DESCRIPTION	Handles service vector 0bbh
;
PROC		Service0bbh
		pushad					; Save context
		mov	ebx,0bbh			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0bch
;
; DESCRIPTION	Handles service vector 0bch
;
PROC		Service0bch
		pushad					; Save context
		mov	ebx,0bch			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0bdh
;
; DESCRIPTION	Handles service vector 0bdh
;
PROC		Service0bdh
		pushad					; Save context
		mov	ebx,0bdh			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0beh
;
; DESCRIPTION	Handles service vector 0beh
;
PROC		Service0beh
		pushad					; Save context
		mov	ebx,0beh			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0bfh
;
; DESCRIPTION	Handles service vector 0bfh
;
PROC		Service0bfh
		pushad					; Save context
		mov	ebx,0bfh			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0c0h
;
; DESCRIPTION	Handles service vector 0c0h
;
PROC		Service0c0h
		pushad					; Save context
		mov	ebx,0c0h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0c1h
;
; DESCRIPTION	Handles service vector 0c1h
;
PROC		Service0c1h
		pushad					; Save context
		mov	ebx,0c1h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0c2h
;
; DESCRIPTION	Handles service vector 0c2h
;
PROC		Service0c2h
		pushad					; Save context
		mov	ebx,0c2h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0c3h
;
; DESCRIPTION	Handles service vector 0c3h
;
PROC		Service0c3h
		pushad					; Save context
		mov	ebx,0c3h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0c4h
;
; DESCRIPTION	Handles service vector 0c4h
;
PROC		Service0c4h
		pushad					; Save context
		mov	ebx,0c4h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0c5h
;
; DESCRIPTION	Handles service vector 0c5h
;
PROC		Service0c5h
		pushad					; Save context
		mov	ebx,0c5h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0c6h
;
; DESCRIPTION	Handles service vector 0c6h
;
PROC		Service0c6h
		pushad					; Save context
		mov	ebx,0c6h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0c7h
;
; DESCRIPTION	Handles service vector 0c7h
;
PROC		Service0c7h
		pushad					; Save context
		mov	ebx,0c7h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0c8h
;
; DESCRIPTION	Handles service vector 0c8h
;
PROC		Service0c8h
		pushad					; Save context
		mov	ebx,0c8h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0c9h
;
; DESCRIPTION	Handles service vector 0c9h
;
PROC		Service0c9h
		pushad					; Save context
		mov	ebx,0c9h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0cah
;
; DESCRIPTION	Handles service vector 0cah
;
PROC		Service0cah
		pushad					; Save context
		mov	ebx,0cah			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0cbh
;
; DESCRIPTION	Handles service vector 0cbh
;
PROC		Service0cbh
		pushad					; Save context
		mov	ebx,0cbh			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0cch
;
; DESCRIPTION	Handles service vector 0cch
;
PROC		Service0cch
		pushad					; Save context
		mov	ebx,0cch			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0cdh
;
; DESCRIPTION	Handles service vector 0cdh
;
PROC		Service0cdh
		pushad					; Save context
		mov	ebx,0cdh			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0ceh
;
; DESCRIPTION	Handles service vector 0ceh
;
PROC		Service0ceh
		pushad					; Save context
		mov	ebx,0ceh			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0cfh
;
; DESCRIPTION	Handles service vector 0cfh
;
PROC		Service0cfh
		pushad					; Save context
		mov	ebx,0cfh			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0d0h
;
; DESCRIPTION	Handles service vector 0d0h
;
PROC		Service0d0h
		pushad					; Save context
		mov	ebx,0d0h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0d1h
;
; DESCRIPTION	Handles service vector 0d1h
;
PROC		Service0d1h
		pushad					; Save context
		mov	ebx,0d1h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0d2h
;
; DESCRIPTION	Handles service vector 0d2h
;
PROC		Service0d2h
		pushad					; Save context
		mov	ebx,0d2h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0d3h
;
; DESCRIPTION	Handles service vector 0d3h
;
PROC		Service0d3h
		pushad					; Save context
		mov	ebx,0d3h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0d4h
;
; DESCRIPTION	Handles service vector 0d4h
;
PROC		Service0d4h
		pushad					; Save context
		mov	ebx,0d4h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0d5h
;
; DESCRIPTION	Handles service vector 0d5h
;
PROC		Service0d5h
		pushad					; Save context
		mov	ebx,0d5h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0d6h
;
; DESCRIPTION	Handles service vector 0d6h
;
PROC		Service0d6h
		pushad					; Save context
		mov	ebx,0d6h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0d7h
;
; DESCRIPTION	Handles service vector 0d7h
;
PROC		Service0d7h
		pushad					; Save context
		mov	ebx,0d7h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0d8h
;
; DESCRIPTION	Handles service vector 0d8h
;
PROC		Service0d8h
		pushad					; Save context
		mov	ebx,0d8h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0d9h
;
; DESCRIPTION	Handles service vector 0d9h
;
PROC		Service0d9h
		pushad					; Save context
		mov	ebx,0d9h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0dah
;
; DESCRIPTION	Handles service vector 0dah
;
PROC		Service0dah
		pushad					; Save context
		mov	ebx,0dah			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0dbh
;
; DESCRIPTION	Handles service vector 0dbh
;
PROC		Service0dbh
		pushad					; Save context
		mov	ebx,0dbh			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0dch
;
; DESCRIPTION	Handles service vector 0dch
;
PROC		Service0dch
		pushad					; Save context
		mov	ebx,0dch			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0ddh
;
; DESCRIPTION	Handles service vector 0ddh
;
PROC		Service0ddh
		pushad					; Save context
		mov	ebx,0ddh			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0deh
;
; DESCRIPTION	Handles service vector 0deh
;
PROC		Service0deh
		pushad					; Save context
		mov	ebx,0deh			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0dfh
;
; DESCRIPTION	Handles service vector 0dfh
;
PROC		Service0dfh
		pushad					; Save context
		mov	ebx,0dfh			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0e0h
;
; DESCRIPTION	Handles service vector 0e0h
;
PROC		Service0e0h
		pushad					; Save context
		mov	ebx,0e0h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0e1h
;
; DESCRIPTION	Handles service vector 0e1h
;
PROC		Service0e1h
		pushad					; Save context
		mov	ebx,0e1h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0e2h
;
; DESCRIPTION	Handles service vector 0e2h
;
PROC		Service0e2h
		pushad					; Save context
		mov	ebx,0e2h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0e3h
;
; DESCRIPTION	Handles service vector 0e3h
;
PROC		Service0e3h
		pushad					; Save context
		mov	ebx,0e3h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0e4h
;
; DESCRIPTION	Handles service vector 0e4h
;
PROC		Service0e4h
		pushad					; Save context
		mov	ebx,0e4h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0e5h
;
; DESCRIPTION	Handles service vector 0e5h
;
PROC		Service0e5h
		pushad					; Save context
		mov	ebx,0e5h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0e6h
;
; DESCRIPTION	Handles service vector 0e6h
;
PROC		Service0e6h
		pushad					; Save context
		mov	ebx,0e6h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0e7h
;
; DESCRIPTION	Handles service vector 0e7h
;
PROC		Service0e7h
		pushad					; Save context
		mov	ebx,0e7h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0e8h
;
; DESCRIPTION	Handles service vector 0e8h
;
PROC		Service0e8h
		pushad					; Save context
		mov	ebx,0e8h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0e9h
;
; DESCRIPTION	Handles service vector 0e9h
;
PROC		Service0e9h
		pushad					; Save context
		mov	ebx,0e9h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0eah
;
; DESCRIPTION	Handles service vector 0eah
;
PROC		Service0eah
		pushad					; Save context
		mov	ebx,0eah			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0ebh
;
; DESCRIPTION	Handles service vector 0ebh
;
PROC		Service0ebh
		pushad					; Save context
		mov	ebx,0ebh			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0ech
;
; DESCRIPTION	Handles service vector 0ech
;
PROC		Service0ech
		pushad					; Save context
		mov	ebx,0ech			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0edh
;
; DESCRIPTION	Handles service vector 0edh
;
PROC		Service0edh
		pushad					; Save context
		mov	ebx,0edh			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0eeh
;
; DESCRIPTION	Handles service vector 0eeh
;
PROC		Service0eeh
		pushad					; Save context
		mov	ebx,0eeh			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0efh
;
; DESCRIPTION	Handles service vector 0efh
;
PROC		Service0efh
		pushad					; Save context
		mov	ebx,0efh			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0f0h
;
; DESCRIPTION	Handles service vector 0f0h
;
PROC		Service0f0h
		pushad					; Save context
		mov	ebx,0f0h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0f1h
;
; DESCRIPTION	Handles service vector 0f1h
;
PROC		Service0f1h
		pushad					; Save context
		mov	ebx,0f1h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0f2h
;
; DESCRIPTION	Handles service vector 0f2h
;
PROC		Service0f2h
		pushad					; Save context
		mov	ebx,0f2h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0f3h
;
; DESCRIPTION	Handles service vector 0f3h
;
PROC		Service0f3h
		pushad					; Save context
		mov	ebx,0f3h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0f4h
;
; DESCRIPTION	Handles service vector 0f4h
;
PROC		Service0f4h
		pushad					; Save context
		mov	ebx,0f4h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0f5h
;
; DESCRIPTION	Handles service vector 0f5h
;
PROC		Service0f5h
		pushad					; Save context
		mov	ebx,0f5h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0f6h
;
; DESCRIPTION	Handles service vector 0f6h
;
PROC		Service0f6h
		pushad					; Save context
		mov	ebx,0f6h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0f7h
;
; DESCRIPTION	Handles service vector 0f7h
;
PROC		Service0f7h
		pushad					; Save context
		mov	ebx,0f7h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0f8h
;
; DESCRIPTION	Handles service vector 0f8h
;
PROC		Service0f8h
		pushad					; Save context
		mov	ebx,0f8h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0f9h
;
; DESCRIPTION	Handles service vector 0f9h
;
PROC		Service0f9h
		pushad					; Save context
		mov	ebx,0f9h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0fah
;
; DESCRIPTION	Handles service vector 0fah
;
PROC		Service0fah
		pushad					; Save context
		mov	ebx,0fah			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0fbh
;
; DESCRIPTION	Handles service vector 0fbh
;
PROC		Service0fbh
		pushad					; Save context
		mov	ebx,0fbh			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0fch
;
; DESCRIPTION	Handles service vector 0fch
;
PROC		Service0fch
		pushad					; Save context
		mov	ebx,0fch			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0fdh
;
; DESCRIPTION	Handles service vector 0fdh
;
PROC		Service0fdh
		pushad					; Save context
		mov	ebx,0fdh			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0feh
;
; DESCRIPTION	Handles service vector 0feh
;
PROC		Service0feh
		pushad					; Save context
		mov	ebx,0feh			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0ffh
;
; DESCRIPTION	Handles service vector 0ffh
;
PROC		Service0ffh
		pushad					; Save context
		mov	ebx,0ffh			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
		DATASEG
		PUBLIC	OurVector
OurVector	DD	Service00h
		DD	Service01h
		DD	Service02h
		DD	Service03h
		DD	Service04h
		DD	Service05h
		DD	Service06h
		DD	Service07h
		DD	Service08h
		DD	Service09h
		DD	Service0ah
		DD	Service0bh
		DD	Service0ch
		DD	Service0dh
		DD	Service0eh
		DD	Service0fh
		DD	Service10h
		DD	Service11h
		DD	Service12h
		DD	Service13h
		DD	Service14h
		DD	Service15h
		DD	Service16h
		DD	Service17h
		DD	Service18h
		DD	Service19h
		DD	Service1ah
		DD	Service1bh
		DD	Service1ch
		DD	Service1dh
		DD	Service1eh
		DD	Service1fh
		DD	Service20h
		DD	Service21h
		DD	Service22h
		DD	Service23h
		DD	Service24h
		DD	Service25h
		DD	Service26h
		DD	Service27h
		DD	Service28h
		DD	Service29h
		DD	Service2ah
		DD	Service2bh
		DD	Service2ch
		DD	Service2dh
		DD	Service2eh
		DD	Service2fh
		DD	Service30h
		DD	Service31h
		DD	Service32h
		DD	Service33h
		DD	Service34h
		DD	Service35h
		DD	Service36h
		DD	Service37h
		DD	Service38h
		DD	Service39h
		DD	Service3ah
		DD	Service3bh
		DD	Service3ch
		DD	Service3dh
		DD	Service3eh
		DD	Service3fh
		DD	Service40h
		DD	Service41h
		DD	Service42h
		DD	Service43h
		DD	Service44h
		DD	Service45h
		DD	Service46h
		DD	Service47h
		DD	Service48h
		DD	Service49h
		DD	Service4ah
		DD	Service4bh
		DD	Service4ch
		DD	Service4dh
		DD	Service4eh
		DD	Service4fh
		DD	Service50h
		DD	Service51h
		DD	Service52h
		DD	Service53h
		DD	Service54h
		DD	Service55h
		DD	Service56h
		DD	Service57h
		DD	Service58h
		DD	Service59h
		DD	Service5ah
		DD	Service5bh
		DD	Service5ch
		DD	Service5dh
		DD	Service5eh
		DD	Service5fh
		DD	Service60h
		DD	Service61h
		DD	Service62h
		DD	Service63h
		DD	Service64h
		DD	Service65h
		DD	Service66h
		DD	Service67h
		DD	Service68h
		DD	Service69h
		DD	Service6ah
		DD	Service6bh
		DD	Service6ch
		DD	Service6dh
		DD	Service6eh
		DD	Service6fh
		DD	Service70h
		DD	Service71h
		DD	Service72h
		DD	Service73h
		DD	Service74h
		DD	Service75h
		DD	Service76h
		DD	Service77h
		DD	Service78h
		DD	Service79h
		DD	Service7ah
		DD	Service7bh
		DD	Service7ch
		DD	Service7dh
		DD	Service7eh
		DD	Service7fh
		DD	Service80h
		DD	Service81h
		DD	Service82h
		DD	Service83h
		DD	Service84h
		DD	Service85h
		DD	Service86h
		DD	Service87h
		DD	Service88h
		DD	Service89h
		DD	Service8ah
		DD	Service8bh
		DD	Service8ch
		DD	Service8dh
		DD	Service8eh
		DD	Service8fh
		DD	Service90h
		DD	Service91h
		DD	Service92h
		DD	Service93h
		DD	Service94h
		DD	Service95h
		DD	Service96h
		DD	Service97h
		DD	Service98h
		DD	Service99h
		DD	Service9ah
		DD	Service9bh
		DD	Service9ch
		DD	Service9dh
		DD	Service9eh
		DD	Service9fh
		DD	Service0a0h
		DD	Service0a1h
		DD	Service0a2h
		DD	Service0a3h
		DD	Service0a4h
		DD	Service0a5h
		DD	Service0a6h
		DD	Service0a7h
		DD	Service0a8h
		DD	Service0a9h
		DD	Service0aah
		DD	Service0abh
		DD	Service0ach
		DD	Service0adh
		DD	Service0aeh
		DD	Service0afh
		DD	Service0b0h
		DD	Service0b1h
		DD	Service0b2h
		DD	Service0b3h
		DD	Service0b4h
		DD	Service0b5h
		DD	Service0b6h
		DD	Service0b7h
		DD	Service0b8h
		DD	Service0b9h
		DD	Service0bah
		DD	Service0bbh
		DD	Service0bch
		DD	Service0bdh
		DD	Service0beh
		DD	Service0bfh
		DD	Service0c0h
		DD	Service0c1h
		DD	Service0c2h
		DD	Service0c3h
		DD	Service0c4h
		DD	Service0c5h
		DD	Service0c6h
		DD	Service0c7h
		DD	Service0c8h
		DD	Service0c9h
		DD	Service0cah
		DD	Service0cbh
		DD	Service0cch
		DD	Service0cdh
		DD	Service0ceh
		DD	Service0cfh
		DD	Service0d0h
		DD	Service0d1h
		DD	Service0d2h
		DD	Service0d3h
		DD	Service0d4h
		DD	Service0d5h
		DD	Service0d6h
		DD	Service0d7h
		DD	Service0d8h
		DD	Service0d9h
		DD	Service0dah
		DD	Service0dbh
		DD	Service0dch
		DD	Service0ddh
		DD	Service0deh
		DD	Service0dfh
		DD	Service0e0h
		DD	Service0e1h
		DD	Service0e2h
		DD	Service0e3h
		DD	Service0e4h
		DD	Service0e5h
		DD	Service0e6h
		DD	Service0e7h
		DD	Service0e8h
		DD	Service0e9h
		DD	Service0eah
		DD	Service0ebh
		DD	Service0ech
		DD	Service0edh
		DD	Service0eeh
		DD	Service0efh
		DD	Service0f0h
		DD	Service0f1h
		DD	Service0f2h
		DD	Service0f3h
		DD	Service0f4h
		DD	Service0f5h
		DD	Service0f6h
		DD	Service0f7h
		DD	Service0f8h
		DD	Service0f9h
		DD	Service0fah
		DD	Service0fbh
		DD	Service0fch
		DD	Service0fdh
		DD	Service0feh
		DD	Service0ffh
		UDATASEG
		PUBLIC	UserVector
UserVector	DD	256 DUP (?)
ELSE
		INCLUDE	'ZDOSINT.INC'
		CODESEG
;
; PROCEDURE	Exception00h
;
; DESCRIPTION	Handles exception 00h (divide fault)
;
PROC		Exception00h
		push	DIVIDE_FAULT SHL 16		; Put fake error code and exception number on stack
;
; PROCEDURE	ExceptionHandler
;
; INPUT		[ESP] = error code and exception number
;
; OUTPUT	NONE
;
; DESCRIPTION	Main exception handler dispatcher.
;
LABEL		ExceptionHandler	PROC
		sti					; Enable interrupts if not already enabled
		cld					; Assure forward direction of string instructions
		pushad					; Save context
		push	ds
		push	es
		push	fs
		push	gs
		movzx	eax,[(CONTEXT esp).Exception]	; EAX = exception number
		call	[UserVector + eax * 4]		; Do exception handling
		pop	gs				; Restore context
		pop	fs
		pop	es
		pop	ds
		popad
		add	esp,4				; Remove error code/exception number
		iretd
ENDP
;
; PROCEDURE	Exception01h
;
; DESCRIPTION	Handles exception 01h (debug fault/trap)
;
PROC		Exception01h
		push	DEBUG_TRAP SHL 16		; Put fake error code and exception number on stack
		jmp	ExceptionHandler		; Handle exception
ENDP
;
; PROCEDURE	Exception02h
;
; DESCRIPTION	Handles exception 02h (NMI)
;
PROC		Exception02h
		push	NMI_TRAP SHL 16			; Put fake error code and exception number on stack
		jmp	ExceptionHandler		; Handle exception
ENDP
;
; PROCEDURE	Exception03h
;
; DESCRIPTION	Handles exception 03h (breakpoint trap)
;
PROC		Exception03h
		push	BREAKPOINT_TRAP SHL 16		; Put fake error code and exception number on stack
		jmp	ExceptionHandler		; Handle exception
ENDP
;
; PROCEDURE	Exception04h
;
; DESCRIPTION	Handles exception 04h (overflow trap)
;
PROC		Exception04h
		push	OVERFLOW_TRAP SHL 16		; Put fake error code and exception number on stack
		jmp	ExceptionHandler		; Handle exception
ENDP
;
; PROCEDURE	Exception05h
;
; DESCRIPTION	Handles exception 05h (bound fault)
;
PROC		Exception05h
		push	BOUND_FAULT SHL 16		; Put fake error code and exception number on stack
		jmp	ExceptionHandler		; Handle exception
ENDP
;
; PROCEDURE	Exception06h
;
; DESCRIPTION	Handles exception 06h (invalid opcode fault)
;
PROC		Exception06h
		push	OPCODE_FAULT SHL 16		; Put fake error code and exception number on stack
		jmp	ExceptionHandler		; Handle exception
ENDP
;
; PROCEDURE	Exception07h
;
; DESCRIPTION	Handles exception 07h (device not available fault)
;
PROC		Exception07h
		push	NO_FPU_FAULT SHL 16		; Put fake error code and exception number on stack
		jmp	ExceptionHandler		; Handle exception
ENDP
;
; PROCEDURE	Exception08h
;
; DESCRIPTION	Handles exception 08h (double fault)
;
PROC		Exception08h
		mov	[WORD esp + 2],DOUBLE_FAULT	; Add exeption number to upper word of error code
		jmp	ExceptionHandler		; Handle exception
ENDP
;
; PROCEDURE	Exception09h
;
; DESCRIPTION	Handles exception 09h (coprocessor segment overrun abort)
;
PROC		Exception09h
		push	OVERRUN_FAULT SHL 16		; Put fake error code and exeption number on stack
		jmp	ExceptionHandler		; Handle exception
ENDP
;
; PROCEDURE	Exception0ah
;
; DESCRIPTION	Handles exception 0ah (invalid TSS fault)
;
PROC		Exception0ah
		mov	[WORD esp + 2],TSS_FAULT	; Add exeption number to upper word of error code
		jmp	ExceptionHandler		; Handle exception
ENDP
;
; PROCEDURE	Exception0bh
;
; DESCRIPTION	Handles exception 0bh (segment not present fault)
;
PROC		Exception0bh
		mov	[WORD esp + 2],SEGMENT_FAULT	; Add exeption number to upper word of error code
		jmp	ExceptionHandler		; Handle exception
ENDP
;
; PROCEDURE	Exception0ch
;
; DESCRIPTION	Handles exception 0ch (stack fault)
;
PROC		Exception0ch
 		mov	[WORD esp + 2],STACK_FAULT	; Add exeption number to upper word of error code
		jmp	ExceptionHandler		; Handle exception
ENDP
;
; PROCEDURE	Exception0dh
;
; DESCRIPTION	Handles exception 0dh (general protection fault)
;
PROC		Exception0dh
		mov	[WORD esp + 2],GENERAL_FAULT	; Add exeption number to upper word of error code
		jmp	ExceptionHandler		; Handle exception
ENDP
;
; PROCEDURE	Exception0eh
;
; DESCRIPTION	Handles exception 0eh (page fault)
;
PROC		Exception0eh
		mov	[WORD esp + 2],PAGE_FAULT	; Add exeption number to upper word of error code
		jmp	ExceptionHandler		; Handle exception
ENDP
;
; PROCEDURE	Exception0fh
;
; DESCRIPTION	Handles exception 0fh (reserved trap)
;
PROC		Exception0fh
		push	EXCEPTION_0F SHL 16		; Put fake error code and exception number on stack
		jmp	ExceptionHandler		; Handle exception
ENDP
;
; PROCEDURE	Exception10h
;
; DESCRIPTION	Handles exception 10h (coprocessor fault)
;
PROC		Exception10h
		push	FPU_FAULT SHL 16		; Put fake error code and exception number on stack
		jmp	ExceptionHandler		; Handle exception
ENDP
;
; PROCEDURE	Exception11h
;
; DESCRIPTION	Handles exception 11h (alignment check fault)
;
PROC		Exception11h
		mov	[WORD esp + 2],ALIGNMENT_FAULT	; Add exeption number to upper word of error code
		jmp	ExceptionHandler		; Handle exception
ENDP
;
; PROCEDURE	Exception12h
;
; DESCRIPTION	Handles exception 12h (machine check fault/trap)
;
PROC		Exception12h
		push	MACHINE_TRAP SHL 16		; Put fake error code and exception number on stack
		jmp	ExceptionHandler		; Handle exception
ENDP
;
; PROCEDURE	Exception13h
;
; DESCRIPTION	Handles exception 13h (reserved)
;
PROC		Exception13h
		push	EXCEPTION_13 SHL 16		; Put fake error code and exception number on stack
		jmp	ExceptionHandler		; Handle exception
ENDP
;
; PROCEDURE	Exception14h
;
; DESCRIPTION	Handles exception 14h (reserved)
;
PROC		Exception14h
		push	EXCEPTION_14 SHL 16		; Put fake error code and exception number on stack
		jmp	ExceptionHandler		; Handle exception
ENDP
;
; PROCEDURE	Exception15h
;
; DESCRIPTION	Handles exception 15h (reserved)
;
PROC		Exception15h
		push	EXCEPTION_15 SHL 16		; Put fake error code and exception number on stack
		jmp	ExceptionHandler		; Handle exception
ENDP
;
; PROCEDURE	Exception16h
;
; DESCRIPTION	Handles exception 16h (reserved)
;
PROC		Exception16h
		push	EXCEPTION_16 SHL 16		; Put fake error code and exception number on stack
		jmp	ExceptionHandler		; Handle exception
ENDP
;
; PROCEDURE	Exception17h
;
; DESCRIPTION	Handles exception 17h (reserved)
;
PROC		Exception17h
		push	EXCEPTION_17 SHL 16		; Put fake error code and exception number on stack
		jmp	ExceptionHandler		; Handle exception
ENDP
;
; PROCEDURE	Exception18h
;
; DESCRIPTION	Handles exception 18h (reserved)
;
PROC		Exception18h
		push	EXCEPTION_18 SHL 16		; Put fake error code and exception number on stack
		jmp	ExceptionHandler		; Handle exception
ENDP
;
; PROCEDURE	Exception19h
;
; DESCRIPTION	Handles exception 19h (reserved)
;
PROC		Exception19h
		push	EXCEPTION_19 SHL 16		; Put fake error code and exception number on stack
		jmp	ExceptionHandler		; Handle exception
ENDP
;
; PROCEDURE	Exception1ah
;
; DESCRIPTION	Handles exception 1ah (reserved)
;
PROC		Exception1ah
		push	EXCEPTION_1A SHL 16		; Put fake error code and exception number on stack
		jmp	ExceptionHandler		; Handle exception
ENDP
;
; PROCEDURE	Exception1bh
;
; DESCRIPTION	Handles exception 1bh (reserved)
;
PROC		Exception1bh
		push	EXCEPTION_1B SHL 16		; Put fake error code and exception number value on stack
		jmp	ExceptionHandler		; Handle exception
ENDP
;
; PROCEDURE	Exception1ch
;
; DESCRIPTION	Handles exception 1ch (reserved)
;
PROC		Exception1ch
		push	EXCEPTION_1C SHL 16		; Put fake error code and exception number on stack
		jmp	ExceptionHandler		; Handle exception
ENDP
;
; PROCEDURE	Exception1dh
;
; DESCRIPTION	Handles exception 1dh (reserved)
;
PROC		Exception1dh
		push	EXCEPTION_1D SHL 16		; Put fake error code and exception number on stack
		jmp	ExceptionHandler		; Handle exception
ENDP
;
; PROCEDURE	Exception1eh
;
; DESCRIPTION	Handles exception 1eh (control break)
;
PROC		Exception1eh
		push	EXCEPTION_1E SHL 16		; Put fake error code and exception number on stack
		jmp	ExceptionHandler		; Handle exception
ENDP
;
; PROCEDURE	Exception1fh
;
; DESCRIPTION	Handles exception 1fh (RTC alarm)
;
PROC		Exception1fh
		push	EXCEPTION_1F SHL 16		; Put fake error code and exception number on stack
		jmp	ExceptionHandler		; Handle exception
ENDP
		DATASEG
		PUBLIC	OurVector
OurVector	DD	Exception00h
		DD	Exception01h
		DD	Exception02h
		DD	Exception03h
		DD	Exception04h
		DD	Exception05h
		DD	Exception06h
		DD	Exception07h
		DD	Exception08h
		DD	Exception09h
		DD	Exception0ah
		DD	Exception0bh
		DD	Exception0ch
		DD	Exception0dh
		DD	Exception0eh
		DD	Exception0fh
		DD	Exception10h
		DD	Exception11h
		DD	Exception12h
		DD	Exception13h
		DD	Exception14h
		DD	Exception15h
		DD	Exception16h
		DD	Exception17h
		DD	Exception18h
		DD	Exception19h
		DD	Exception1ah
		DD	Exception1bh
		DD	Exception1ch
		DD	Exception1dh
		DD	Exception1eh
		DD	Exception1fh
		UDATASEG
		PUBLIC	UserVector
UserVector	DD	32 DUP (?)
ENDIF
		END
