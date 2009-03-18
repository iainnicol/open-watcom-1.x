;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		CODESEG
;
; PROCEDURE	Service00h
;
; DESCRIPTION	Handles service vector 00h
;
PROC		Service00h
		xor	ebx,ebx				; EBX = service vector number
;
; PROCEDURE	InvokeHandler
;
; INPUT		EBX = service vector number
; 		EBP = pointer to EXCEPTION stack frame
;
; OUTPUT	EXCEPTION stack frame updated.
;
; DESCRIPTION	Sets up parameters and calls the user INT function handler.
;
LABEL		InvokeHandler		PROC
		mov	eax,ebp				; EAX points to EXCEPTION stack frame
		jmp	[UserApiVector + ebx * 4]	; Invoke C service handler
ENDP
;
; PROCEDURE	Service01h
;
; DESCRIPTION	Handles service vector 01h
;
PROC		Service01h
		mov	ebx,01h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service02h
;
; DESCRIPTION	Handles service vector 02h
;
PROC		Service02h
		mov	ebx,02h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service03h
;
; DESCRIPTION	Handles service vector 03h
;
PROC		Service03h
		mov	ebx,03h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service04h
;
; DESCRIPTION	Handles service vector 04h
;
PROC		Service04h
		mov	ebx,04h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service05h
;
; DESCRIPTION	Handles service vector 05h
;
PROC		Service05h
		mov	ebx,05h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service06h
;
; DESCRIPTION	Handles service vector 06h
;
PROC		Service06h
		mov	ebx,06h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service07h
;
; DESCRIPTION	Handles service vector 07h
;
PROC		Service07h
		mov	ebx,07h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service08h
;
; DESCRIPTION	Handles service vector 08h
;
PROC		Service08h
		mov	ebx,08h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service09h
;
; DESCRIPTION	Handles service vector 09h
;
PROC		Service09h
		mov	ebx,09h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0ah
;
; DESCRIPTION	Handles service vector 0ah
;
PROC		Service0ah
		mov	ebx,0ah				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0bh
;
; DESCRIPTION	Handles service vector 0bh
;
PROC		Service0bh
		mov	ebx,0bh				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0ch
;
; DESCRIPTION	Handles service vector 0ch
;
PROC		Service0ch
		mov	ebx,0ch				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0dh
;
; DESCRIPTION	Handles service vector 0dh
;
PROC		Service0dh
		mov	ebx,0dh				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0eh
;
; DESCRIPTION	Handles service vector 0eh
;
PROC		Service0eh
		mov	ebx,0eh				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0fh
;
; DESCRIPTION	Handles service vector 0fh
;
PROC		Service0fh
		mov	ebx,0fh				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service10h
;
; DESCRIPTION	Handles service vector 10h
;
PROC		Service10h
		mov	ebx,10h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service11h
;
; DESCRIPTION	Handles service vector 11h
;
PROC		Service11h
		mov	ebx,11h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service12h
;
; DESCRIPTION	Handles service vector 12h
;
PROC		Service12h
		mov	ebx,12h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service13h
;
; DESCRIPTION	Handles service vector 13h
;
PROC		Service13h
		mov	ebx,13h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service14h
;
; DESCRIPTION	Handles service vector 14h
;
PROC		Service14h
		mov	ebx,14h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service15h
;
; DESCRIPTION	Handles service vector 15h
;
PROC		Service15h
		mov	ebx,15h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service16h
;
; DESCRIPTION	Handles service vector 16h
;
PROC		Service16h
		mov	ebx,16h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service17h
;
; DESCRIPTION	Handles service vector 17h
;
PROC		Service17h
		mov	ebx,17h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service18h
;
; DESCRIPTION	Handles service vector 18h
;
PROC		Service18h
		mov	ebx,18h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service19h
;
; DESCRIPTION	Handles service vector 19h
;
PROC		Service19h
		mov	ebx,19h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service1ah
;
; DESCRIPTION	Handles service vector 1ah
;
PROC		Service1ah
		mov	ebx,1ah				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service1bh
;
; DESCRIPTION	Handles service vector 1bh
;
PROC		Service1bh
		mov	ebx,1bh				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service1ch
;
; DESCRIPTION	Handles service vector 1ch
;
PROC		Service1ch
		mov	ebx,1ch				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service1dh
;
; DESCRIPTION	Handles service vector 1dh
;
PROC		Service1dh
		mov	ebx,1dh				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service1eh
;
; DESCRIPTION	Handles service vector 1eh
;
PROC		Service1eh
		mov	ebx,1eh				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service1fh
;
; DESCRIPTION	Handles service vector 1fh
;
PROC		Service1fh
		mov	ebx,1fh				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service20h
;
; DESCRIPTION	Handles service vector 20h
;
PROC		Service20h
		mov	ebx,20h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service21h
;
; DESCRIPTION	Handles service vector 21h
;
PROC		Service21h
		mov	ebx,21h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service22h
;
; DESCRIPTION	Handles service vector 22h
;
PROC		Service22h
		mov	ebx,22h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service23h
;
; DESCRIPTION	Handles service vector 23h
;
PROC		Service23h
		mov	ebx,23h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service24h
;
; DESCRIPTION	Handles service vector 24h
;
PROC		Service24h
		mov	ebx,24h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service25h
;
; DESCRIPTION	Handles service vector 25h
;
PROC		Service25h
		mov	ebx,25h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service26h
;
; DESCRIPTION	Handles service vector 26h
;
PROC		Service26h
		mov	ebx,26h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service27h
;
; DESCRIPTION	Handles service vector 27h
;
PROC		Service27h
		mov	ebx,27h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service28h
;
; DESCRIPTION	Handles service vector 28h
;
PROC		Service28h
		mov	ebx,28h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service29h
;
; DESCRIPTION	Handles service vector 29h
;
PROC		Service29h
		mov	ebx,29h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service2ah
;
; DESCRIPTION	Handles service vector 2ah
;
PROC		Service2ah
		mov	ebx,2ah				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service2bh
;
; DESCRIPTION	Handles service vector 2bh
;
PROC		Service2bh
		mov	ebx,2bh				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service2ch
;
; DESCRIPTION	Handles service vector 2ch
;
PROC		Service2ch
		mov	ebx,2ch				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service2dh
;
; DESCRIPTION	Handles service vector 2dh
;
PROC		Service2dh
		mov	ebx,2dh				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service2eh
;
; DESCRIPTION	Handles service vector 2eh
;
PROC		Service2eh
		mov	ebx,2eh				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service2fh
;
; DESCRIPTION	Handles service vector 2fh
;
PROC		Service2fh
		mov	ebx,2fh				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service30h
;
; DESCRIPTION	Handles service vector 30h
;
PROC		Service30h
		mov	ebx,30h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service31h
;
; DESCRIPTION	Handles service vector 31h
;
PROC		Service31h
		mov	ebx,31h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service32h
;
; DESCRIPTION	Handles service vector 32h
;
PROC		Service32h
		mov	ebx,32h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service33h
;
; DESCRIPTION	Handles service vector 33h
;
PROC		Service33h
		mov	ebx,33h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service34h
;
; DESCRIPTION	Handles service vector 34h
;
PROC		Service34h
		mov	ebx,34h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service35h
;
; DESCRIPTION	Handles service vector 35h
;
PROC		Service35h
		mov	ebx,35h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service36h
;
; DESCRIPTION	Handles service vector 36h
;
PROC		Service36h
		mov	ebx,36h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service37h
;
; DESCRIPTION	Handles service vector 37h
;
PROC		Service37h
		mov	ebx,37h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service38h
;
; DESCRIPTION	Handles service vector 38h
;
PROC		Service38h
		mov	ebx,38h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service39h
;
; DESCRIPTION	Handles service vector 39h
;
PROC		Service39h
		mov	ebx,39h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service3ah
;
; DESCRIPTION	Handles service vector 3ah
;
PROC		Service3ah
		mov	ebx,3ah				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service3bh
;
; DESCRIPTION	Handles service vector 3bh
;
PROC		Service3bh
		mov	ebx,3bh				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service3ch
;
; DESCRIPTION	Handles service vector 3ch
;
PROC		Service3ch
		mov	ebx,3ch				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service3dh
;
; DESCRIPTION	Handles service vector 3dh
;
PROC		Service3dh
		mov	ebx,3dh				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service3eh
;
; DESCRIPTION	Handles service vector 3eh
;
PROC		Service3eh
		mov	ebx,3eh				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service3fh
;
; DESCRIPTION	Handles service vector 3fh
;
PROC		Service3fh
		mov	ebx,3fh				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service40h
;
; DESCRIPTION	Handles service vector 40h
;
PROC		Service40h
		mov	ebx,40h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service41h
;
; DESCRIPTION	Handles service vector 41h
;
PROC		Service41h
		mov	ebx,41h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service42h
;
; DESCRIPTION	Handles service vector 42h
;
PROC		Service42h
		mov	ebx,42h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service43h
;
; DESCRIPTION	Handles service vector 43h
;
PROC		Service43h
		mov	ebx,43h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service44h
;
; DESCRIPTION	Handles service vector 44h
;
PROC		Service44h
		mov	ebx,44h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service45h
;
; DESCRIPTION	Handles service vector 45h
;
PROC		Service45h
		mov	ebx,45h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service46h
;
; DESCRIPTION	Handles service vector 46h
;
PROC		Service46h
		mov	ebx,46h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service47h
;
; DESCRIPTION	Handles service vector 47h
;
PROC		Service47h
		mov	ebx,47h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service48h
;
; DESCRIPTION	Handles service vector 48h
;
PROC		Service48h
		mov	ebx,48h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service49h
;
; DESCRIPTION	Handles service vector 49h
;
PROC		Service49h
		mov	ebx,49h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service4ah
;
; DESCRIPTION	Handles service vector 4ah
;
PROC		Service4ah
		mov	ebx,4ah				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service4bh
;
; DESCRIPTION	Handles service vector 4bh
;
PROC		Service4bh
		mov	ebx,4bh				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service4ch
;
; DESCRIPTION	Handles service vector 4ch
;
PROC		Service4ch
		mov	ebx,4ch				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service4dh
;
; DESCRIPTION	Handles service vector 4dh
;
PROC		Service4dh
		mov	ebx,4dh				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service4eh
;
; DESCRIPTION	Handles service vector 4eh
;
PROC		Service4eh
		mov	ebx,4eh				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service4fh
;
; DESCRIPTION	Handles service vector 4fh
;
PROC		Service4fh
		mov	ebx,4fh				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service50h
;
; DESCRIPTION	Handles service vector 50h
;
PROC		Service50h
		mov	ebx,50h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service51h
;
; DESCRIPTION	Handles service vector 51h
;
PROC		Service51h
		mov	ebx,51h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service52h
;
; DESCRIPTION	Handles service vector 52h
;
PROC		Service52h
		mov	ebx,52h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service53h
;
; DESCRIPTION	Handles service vector 53h
;
PROC		Service53h
		mov	ebx,53h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service54h
;
; DESCRIPTION	Handles service vector 54h
;
PROC		Service54h
		mov	ebx,54h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service55h
;
; DESCRIPTION	Handles service vector 55h
;
PROC		Service55h
		mov	ebx,55h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service56h
;
; DESCRIPTION	Handles service vector 56h
;
PROC		Service56h
		mov	ebx,56h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service57h
;
; DESCRIPTION	Handles service vector 57h
;
PROC		Service57h
		mov	ebx,57h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service58h
;
; DESCRIPTION	Handles service vector 58h
;
PROC		Service58h
		mov	ebx,58h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service59h
;
; DESCRIPTION	Handles service vector 59h
;
PROC		Service59h
		mov	ebx,59h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service5ah
;
; DESCRIPTION	Handles service vector 5ah
;
PROC		Service5ah
		mov	ebx,5ah				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service5bh
;
; DESCRIPTION	Handles service vector 5bh
;
PROC		Service5bh
		mov	ebx,5bh				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service5ch
;
; DESCRIPTION	Handles service vector 5ch
;
PROC		Service5ch
		mov	ebx,5ch				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service5dh
;
; DESCRIPTION	Handles service vector 5dh
;
PROC		Service5dh
		mov	ebx,5dh				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service5eh
;
; DESCRIPTION	Handles service vector 5eh
;
PROC		Service5eh
		mov	ebx,5eh				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service5fh
;
; DESCRIPTION	Handles service vector 5fh
;
PROC		Service5fh
		mov	ebx,5fh				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service60h
;
; DESCRIPTION	Handles service vector 60h
;
PROC		Service60h
		mov	ebx,60h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service61h
;
; DESCRIPTION	Handles service vector 61h
;
PROC		Service61h
		mov	ebx,61h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service62h
;
; DESCRIPTION	Handles service vector 62h
;
PROC		Service62h
		mov	ebx,62h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service63h
;
; DESCRIPTION	Handles service vector 63h
;
PROC		Service63h
		mov	ebx,63h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service64h
;
; DESCRIPTION	Handles service vector 64h
;
PROC		Service64h
		mov	ebx,64h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service65h
;
; DESCRIPTION	Handles service vector 65h
;
PROC		Service65h
		mov	ebx,65h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service66h
;
; DESCRIPTION	Handles service vector 66h
;
PROC		Service66h
		mov	ebx,66h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service67h
;
; DESCRIPTION	Handles service vector 67h
;
PROC		Service67h
		mov	ebx,67h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service68h
;
; DESCRIPTION	Handles service vector 68h
;
PROC		Service68h
		mov	ebx,68h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service69h
;
; DESCRIPTION	Handles service vector 69h
;
PROC		Service69h
		mov	ebx,69h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service6ah
;
; DESCRIPTION	Handles service vector 6ah
;
PROC		Service6ah
		mov	ebx,6ah				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service6bh
;
; DESCRIPTION	Handles service vector 6bh
;
PROC		Service6bh
		mov	ebx,6bh				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service6ch
;
; DESCRIPTION	Handles service vector 6ch
;
PROC		Service6ch
		mov	ebx,6ch				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service6dh
;
; DESCRIPTION	Handles service vector 6dh
;
PROC		Service6dh
		mov	ebx,6dh				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service6eh
;
; DESCRIPTION	Handles service vector 6eh
;
PROC		Service6eh
		mov	ebx,6eh				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service6fh
;
; DESCRIPTION	Handles service vector 6fh
;
PROC		Service6fh
		mov	ebx,6fh				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service70h
;
; DESCRIPTION	Handles service vector 70h
;
PROC		Service70h
		mov	ebx,70h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service71h
;
; DESCRIPTION	Handles service vector 71h
;
PROC		Service71h
		mov	ebx,71h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service72h
;
; DESCRIPTION	Handles service vector 72h
;
PROC		Service72h
		mov	ebx,72h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service73h
;
; DESCRIPTION	Handles service vector 73h
;
PROC		Service73h
		mov	ebx,73h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service74h
;
; DESCRIPTION	Handles service vector 74h
;
PROC		Service74h
		mov	ebx,74h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service75h
;
; DESCRIPTION	Handles service vector 75h
;
PROC		Service75h
		mov	ebx,75h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service76h
;
; DESCRIPTION	Handles service vector 76h
;
PROC		Service76h
		mov	ebx,76h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service77h
;
; DESCRIPTION	Handles service vector 77h
;
PROC		Service77h
		mov	ebx,77h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service78h
;
; DESCRIPTION	Handles service vector 78h
;
PROC		Service78h
		mov	ebx,78h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service79h
;
; DESCRIPTION	Handles service vector 79h
;
PROC		Service79h
		mov	ebx,79h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service7ah
;
; DESCRIPTION	Handles service vector 7ah
;
PROC		Service7ah
		mov	ebx,7ah				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service7bh
;
; DESCRIPTION	Handles service vector 7bh
;
PROC		Service7bh
		mov	ebx,7bh				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service7ch
;
; DESCRIPTION	Handles service vector 7ch
;
PROC		Service7ch
		mov	ebx,7ch				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service7dh
;
; DESCRIPTION	Handles service vector 7dh
;
PROC		Service7dh
		mov	ebx,7dh				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service7eh
;
; DESCRIPTION	Handles service vector 7eh
;
PROC		Service7eh
		mov	ebx,7eh				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service7fh
;
; DESCRIPTION	Handles service vector 7fh
;
PROC		Service7fh
		mov	ebx,7fh				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service80h
;
; DESCRIPTION	Handles service vector 80h
;
PROC		Service80h
		mov	ebx,80h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service81h
;
; DESCRIPTION	Handles service vector 81h
;
PROC		Service81h
		mov	ebx,81h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service82h
;
; DESCRIPTION	Handles service vector 82h
;
PROC		Service82h
		mov	ebx,82h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service83h
;
; DESCRIPTION	Handles service vector 83h
;
PROC		Service83h
		mov	ebx,83h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service84h
;
; DESCRIPTION	Handles service vector 84h
;
PROC		Service84h
		mov	ebx,84h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service85h
;
; DESCRIPTION	Handles service vector 85h
;
PROC		Service85h
		mov	ebx,85h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service86h
;
; DESCRIPTION	Handles service vector 86h
;
PROC		Service86h
		mov	ebx,86h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service87h
;
; DESCRIPTION	Handles service vector 87h
;
PROC		Service87h
		mov	ebx,87h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service88h
;
; DESCRIPTION	Handles service vector 88h
;
PROC		Service88h
		mov	ebx,88h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service89h
;
; DESCRIPTION	Handles service vector 89h
;
PROC		Service89h
		mov	ebx,89h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service8ah
;
; DESCRIPTION	Handles service vector 8ah
;
PROC		Service8ah
		mov	ebx,8ah				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service8bh
;
; DESCRIPTION	Handles service vector 8bh
;
PROC		Service8bh
		mov	ebx,8bh				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service8ch
;
; DESCRIPTION	Handles service vector 8ch
;
PROC		Service8ch
		mov	ebx,8ch				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service8dh
;
; DESCRIPTION	Handles service vector 8dh
;
PROC		Service8dh
		mov	ebx,8dh				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service8eh
;
; DESCRIPTION	Handles service vector 8eh
;
PROC		Service8eh
		mov	ebx,8eh				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service8fh
;
; DESCRIPTION	Handles service vector 8fh
;
PROC		Service8fh
		mov	ebx,8fh				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service90h
;
; DESCRIPTION	Handles service vector 90h
;
PROC		Service90h
		mov	ebx,90h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service91h
;
; DESCRIPTION	Handles service vector 91h
;
PROC		Service91h
		mov	ebx,91h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service92h
;
; DESCRIPTION	Handles service vector 92h
;
PROC		Service92h
		mov	ebx,92h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service93h
;
; DESCRIPTION	Handles service vector 93h
;
PROC		Service93h
		mov	ebx,93h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service94h
;
; DESCRIPTION	Handles service vector 94h
;
PROC		Service94h
		mov	ebx,94h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service95h
;
; DESCRIPTION	Handles service vector 95h
;
PROC		Service95h
		mov	ebx,95h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service96h
;
; DESCRIPTION	Handles service vector 96h
;
PROC		Service96h
		mov	ebx,96h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service97h
;
; DESCRIPTION	Handles service vector 97h
;
PROC		Service97h
		mov	ebx,97h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service98h
;
; DESCRIPTION	Handles service vector 98h
;
PROC		Service98h
		mov	ebx,98h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service99h
;
; DESCRIPTION	Handles service vector 99h
;
PROC		Service99h
		mov	ebx,99h				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service9ah
;
; DESCRIPTION	Handles service vector 9ah
;
PROC		Service9ah
		mov	ebx,9ah				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service9bh
;
; DESCRIPTION	Handles service vector 9bh
;
PROC		Service9bh
		mov	ebx,9bh				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service9ch
;
; DESCRIPTION	Handles service vector 9ch
;
PROC		Service9ch
		mov	ebx,9ch				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service9dh
;
; DESCRIPTION	Handles service vector 9dh
;
PROC		Service9dh
		mov	ebx,9dh				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service9eh
;
; DESCRIPTION	Handles service vector 9eh
;
PROC		Service9eh
		mov	ebx,9eh				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service9fh
;
; DESCRIPTION	Handles service vector 9fh
;
PROC		Service9fh
		mov	ebx,9fh				; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0a0h
;
; DESCRIPTION	Handles service vector 0a0h
;
PROC		Service0a0h
		mov	ebx,0a0h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0a1h
;
; DESCRIPTION	Handles service vector 0a1h
;
PROC		Service0a1h
		mov	ebx,0a1h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0a2h
;
; DESCRIPTION	Handles service vector 0a2h
;
PROC		Service0a2h
		mov	ebx,0a2h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0a3h
;
; DESCRIPTION	Handles service vector 0a3h
;
PROC		Service0a3h
		mov	ebx,0a3h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0a4h
;
; DESCRIPTION	Handles service vector 0a4h
;
PROC		Service0a4h
		mov	ebx,0a4h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0a5h
;
; DESCRIPTION	Handles service vector 0a5h
;
PROC		Service0a5h
		mov	ebx,0a5h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0a6h
;
; DESCRIPTION	Handles service vector 0a6h
;
PROC		Service0a6h
		mov	ebx,0a6h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0a7h
;
; DESCRIPTION	Handles service vector 0a7h
;
PROC		Service0a7h
		mov	ebx,0a7h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0a8h
;
; DESCRIPTION	Handles service vector 0a8h
;
PROC		Service0a8h
		mov	ebx,0a8h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0a9h
;
; DESCRIPTION	Handles service vector 0a9h
;
PROC		Service0a9h
		mov	ebx,0a9h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0aah
;
; DESCRIPTION	Handles service vector 0aah
;
PROC		Service0aah
		mov	ebx,0aah			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0abh
;
; DESCRIPTION	Handles service vector 0abh
;
PROC		Service0abh
		mov	ebx,0abh			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0ach
;
; DESCRIPTION	Handles service vector 0ach
;
PROC		Service0ach
		mov	ebx,0ach			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0adh
;
; DESCRIPTION	Handles service vector 0adh
;
PROC		Service0adh
		mov	ebx,0adh			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0aeh
;
; DESCRIPTION	Handles service vector 0aeh
;
PROC		Service0aeh
		mov	ebx,0aeh			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0afh
;
; DESCRIPTION	Handles service vector 0afh
;
PROC		Service0afh
		mov	ebx,0afh			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0b0h
;
; DESCRIPTION	Handles service vector 0b0h
;
PROC		Service0b0h
		mov	ebx,0b0h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0b1h
;
; DESCRIPTION	Handles service vector 0b1h
;
PROC		Service0b1h
		mov	ebx,0b1h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0b2h
;
; DESCRIPTION	Handles service vector 0b2h
;
PROC		Service0b2h
		mov	ebx,0b2h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0b3h
;
; DESCRIPTION	Handles service vector 0b3h
;
PROC		Service0b3h
		mov	ebx,0b3h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0b4h
;
; DESCRIPTION	Handles service vector 0b4h
;
PROC		Service0b4h
		mov	ebx,0b4h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0b5h
;
; DESCRIPTION	Handles service vector 0b5h
;
PROC		Service0b5h
		mov	ebx,0b5h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0b6h
;
; DESCRIPTION	Handles service vector 0b6h
;
PROC		Service0b6h
		mov	ebx,0b6h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0b7h
;
; DESCRIPTION	Handles service vector 0b7h
;
PROC		Service0b7h
		mov	ebx,0b7h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0b8h
;
; DESCRIPTION	Handles service vector 0b8h
;
PROC		Service0b8h
		mov	ebx,0b8h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0b9h
;
; DESCRIPTION	Handles service vector 0b9h
;
PROC		Service0b9h
		mov	ebx,0b9h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0bah
;
; DESCRIPTION	Handles service vector 0bah
;
PROC		Service0bah
		mov	ebx,0bah			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0bbh
;
; DESCRIPTION	Handles service vector 0bbh
;
PROC		Service0bbh
		mov	ebx,0bbh			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0bch
;
; DESCRIPTION	Handles service vector 0bch
;
PROC		Service0bch
		mov	ebx,0bch			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0bdh
;
; DESCRIPTION	Handles service vector 0bdh
;
PROC		Service0bdh
		mov	ebx,0bdh			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0beh
;
; DESCRIPTION	Handles service vector 0beh
;
PROC		Service0beh
		mov	ebx,0beh			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0bfh
;
; DESCRIPTION	Handles service vector 0bfh
;
PROC		Service0bfh
		mov	ebx,0bfh			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0c0h
;
; DESCRIPTION	Handles service vector 0c0h
;
PROC		Service0c0h
		mov	ebx,0c0h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0c1h
;
; DESCRIPTION	Handles service vector 0c1h
;
PROC		Service0c1h
		mov	ebx,0c1h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0c2h
;
; DESCRIPTION	Handles service vector 0c2h
;
PROC		Service0c2h
		mov	ebx,0c2h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0c3h
;
; DESCRIPTION	Handles service vector 0c3h
;
PROC		Service0c3h
		mov	ebx,0c3h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0c4h
;
; DESCRIPTION	Handles service vector 0c4h
;
PROC		Service0c4h
		mov	ebx,0c4h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0c5h
;
; DESCRIPTION	Handles service vector 0c5h
;
PROC		Service0c5h
		mov	ebx,0c5h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0c6h
;
; DESCRIPTION	Handles service vector 0c6h
;
PROC		Service0c6h
		mov	ebx,0c6h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0c7h
;
; DESCRIPTION	Handles service vector 0c7h
;
PROC		Service0c7h
		mov	ebx,0c7h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0c8h
;
; DESCRIPTION	Handles service vector 0c8h
;
PROC		Service0c8h
		mov	ebx,0c8h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0c9h
;
; DESCRIPTION	Handles service vector 0c9h
;
PROC		Service0c9h
		mov	ebx,0c9h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0cah
;
; DESCRIPTION	Handles service vector 0cah
;
PROC		Service0cah
		mov	ebx,0cah			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0cbh
;
; DESCRIPTION	Handles service vector 0cbh
;
PROC		Service0cbh
		mov	ebx,0cbh			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0cch
;
; DESCRIPTION	Handles service vector 0cch
;
PROC		Service0cch
		mov	ebx,0cch			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0cdh
;
; DESCRIPTION	Handles service vector 0cdh
;
PROC		Service0cdh
		mov	ebx,0cdh			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0ceh
;
; DESCRIPTION	Handles service vector 0ceh
;
PROC		Service0ceh
		mov	ebx,0ceh			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0cfh
;
; DESCRIPTION	Handles service vector 0cfh
;
PROC		Service0cfh
		mov	ebx,0cfh			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0d0h
;
; DESCRIPTION	Handles service vector 0d0h
;
PROC		Service0d0h
		mov	ebx,0d0h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0d1h
;
; DESCRIPTION	Handles service vector 0d1h
;
PROC		Service0d1h
		mov	ebx,0d1h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0d2h
;
; DESCRIPTION	Handles service vector 0d2h
;
PROC		Service0d2h
		mov	ebx,0d2h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0d3h
;
; DESCRIPTION	Handles service vector 0d3h
;
PROC		Service0d3h
		mov	ebx,0d3h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0d4h
;
; DESCRIPTION	Handles service vector 0d4h
;
PROC		Service0d4h
		mov	ebx,0d4h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0d5h
;
; DESCRIPTION	Handles service vector 0d5h
;
PROC		Service0d5h
		mov	ebx,0d5h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0d6h
;
; DESCRIPTION	Handles service vector 0d6h
;
PROC		Service0d6h
		mov	ebx,0d6h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0d7h
;
; DESCRIPTION	Handles service vector 0d7h
;
PROC		Service0d7h
		mov	ebx,0d7h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0d8h
;
; DESCRIPTION	Handles service vector 0d8h
;
PROC		Service0d8h
		mov	ebx,0d8h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0d9h
;
; DESCRIPTION	Handles service vector 0d9h
;
PROC		Service0d9h
		mov	ebx,0d9h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0dah
;
; DESCRIPTION	Handles service vector 0dah
;
PROC		Service0dah
		mov	ebx,0dah			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0dbh
;
; DESCRIPTION	Handles service vector 0dbh
;
PROC		Service0dbh
		mov	ebx,0dbh			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0dch
;
; DESCRIPTION	Handles service vector 0dch
;
PROC		Service0dch
		mov	ebx,0dch			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0ddh
;
; DESCRIPTION	Handles service vector 0ddh
;
PROC		Service0ddh
		mov	ebx,0ddh			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0deh
;
; DESCRIPTION	Handles service vector 0deh
;
PROC		Service0deh
		mov	ebx,0deh			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0dfh
;
; DESCRIPTION	Handles service vector 0dfh
;
PROC		Service0dfh
		mov	ebx,0dfh			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0e0h
;
; DESCRIPTION	Handles service vector 0e0h
;
PROC		Service0e0h
		mov	ebx,0e0h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0e1h
;
; DESCRIPTION	Handles service vector 0e1h
;
PROC		Service0e1h
		mov	ebx,0e1h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0e2h
;
; DESCRIPTION	Handles service vector 0e2h
;
PROC		Service0e2h
		mov	ebx,0e2h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0e3h
;
; DESCRIPTION	Handles service vector 0e3h
;
PROC		Service0e3h
		mov	ebx,0e3h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0e4h
;
; DESCRIPTION	Handles service vector 0e4h
;
PROC		Service0e4h
		mov	ebx,0e4h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0e5h
;
; DESCRIPTION	Handles service vector 0e5h
;
PROC		Service0e5h
		mov	ebx,0e5h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0e6h
;
; DESCRIPTION	Handles service vector 0e6h
;
PROC		Service0e6h
		mov	ebx,0e6h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0e7h
;
; DESCRIPTION	Handles service vector 0e7h
;
PROC		Service0e7h
		mov	ebx,0e7h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0e8h
;
; DESCRIPTION	Handles service vector 0e8h
;
PROC		Service0e8h
		mov	ebx,0e8h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0e9h
;
; DESCRIPTION	Handles service vector 0e9h
;
PROC		Service0e9h
		mov	ebx,0e9h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0eah
;
; DESCRIPTION	Handles service vector 0eah
;
PROC		Service0eah
		mov	ebx,0eah			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0ebh
;
; DESCRIPTION	Handles service vector 0ebh
;
PROC		Service0ebh
		mov	ebx,0ebh			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0ech
;
; DESCRIPTION	Handles service vector 0ech
;
PROC		Service0ech
		mov	ebx,0ech			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0edh
;
; DESCRIPTION	Handles service vector 0edh
;
PROC		Service0edh
		mov	ebx,0edh			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0eeh
;
; DESCRIPTION	Handles service vector 0eeh
;
PROC		Service0eeh
		mov	ebx,0eeh			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0efh
;
; DESCRIPTION	Handles service vector 0efh
;
PROC		Service0efh
		mov	ebx,0efh			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0f0h
;
; DESCRIPTION	Handles service vector 0f0h
;
PROC		Service0f0h
		mov	ebx,0f0h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0f1h
;
; DESCRIPTION	Handles service vector 0f1h
;
PROC		Service0f1h
		mov	ebx,0f1h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0f2h
;
; DESCRIPTION	Handles service vector 0f2h
;
PROC		Service0f2h
		mov	ebx,0f2h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0f3h
;
; DESCRIPTION	Handles service vector 0f3h
;
PROC		Service0f3h
		mov	ebx,0f3h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0f4h
;
; DESCRIPTION	Handles service vector 0f4h
;
PROC		Service0f4h
		mov	ebx,0f4h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0f5h
;
; DESCRIPTION	Handles service vector 0f5h
;
PROC		Service0f5h
		mov	ebx,0f5h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0f6h
;
; DESCRIPTION	Handles service vector 0f6h
;
PROC		Service0f6h
		mov	ebx,0f6h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0f7h
;
; DESCRIPTION	Handles service vector 0f7h
;
PROC		Service0f7h
		mov	ebx,0f7h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0f8h
;
; DESCRIPTION	Handles service vector 0f8h
;
PROC		Service0f8h
		mov	ebx,0f8h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0f9h
;
; DESCRIPTION	Handles service vector 0f9h
;
PROC		Service0f9h
		mov	ebx,0f9h			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0fah
;
; DESCRIPTION	Handles service vector 0fah
;
PROC		Service0fah
		mov	ebx,0fah			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0fbh
;
; DESCRIPTION	Handles service vector 0fbh
;
PROC		Service0fbh
		mov	ebx,0fbh			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0fch
;
; DESCRIPTION	Handles service vector 0fch
;
PROC		Service0fch
		mov	ebx,0fch			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0fdh
;
; DESCRIPTION	Handles service vector 0fdh
;
PROC		Service0fdh
		mov	ebx,0fdh			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0feh
;
; DESCRIPTION	Handles service vector 0feh
;
PROC		Service0feh
		mov	ebx,0feh			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
;
; PROCEDURE	Service0ffh
;
; DESCRIPTION	Handles service vector 0ffh
;
PROC		Service0ffh
		mov	ebx,0ffh			; EBX = service vector number
		jmp	InvokeHandler			; Invoke service handler
ENDP
		DATASEG
		PUBLIC	OurApiVector
OurApiVector	DD	Service00h
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
		PUBLIC	UserApiVector
UserApiVector	DD	256 DUP (?)
		END
