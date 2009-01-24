;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZBIOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	__CMain				: PROC
		EXTRN	__InitRtns			: PROC
		EXTRN	__FiniRtns			: PROC
		EXTRN	_Not_Enough_Memory_		: PROC
		PUBLIC	InitializeDriver
		PUBLIC	__exit_
		PUBLIC	__do_exit_with_msg__
		PUBLIC	InitializeEnvironment
;
; PROCEDURE	InitializeDriver
;
; INPUT		EBX = pointer to driver header name field
;		ESI = pointer to command line
;
; OUTPUT	NONE
;
; DESCRIPTION	Initializes the driver runtime library.
;
PROC		InitializeDriver
		dec	esi				; Point to previous character
		cmp	[BYTE esi],'='			; At end of keyword ?
		jnz	InitializeDriver		; No, go back another character
		inc	esi				; Yes, ESI points to driver path
		mov	ecx,OFFSET StartOfStack		; ECX points past end of BSS segment
		mov	edi,OFFSET StartOfBSS		; EDI points to start of BSS
		sub	ecx,edi				; ECX = number of bytes to initialize
		shr	ecx,2				; ECX = number of DWORDs to initialize
		xor	eax,eax				; EAX = filler
		rep	stosd				; Fill with zeros
		mov	edi,OFFSET DriverPath		; EDI points to buffer
		mov	[_LpPgmName],edi		; Save pointer to program name (for argv[0])
@@CopyPath:	movsb					; Copy next character
		cmp	[BYTE esi],' '			; At end of driver path ?
		ja	@@CopyPath			; No, copy next character
		mov	edi,OFFSET CommandLine		; Yes, EDI points to command line buffer
		inc	edi				; EDI points to first character in command line
		mov	[_LpCmdLine],edi		; Save pointer to command line buffer
@@CopyCommand:	lodsb					; Get next character in AL
		cmp	al,0dh				; CR ?
		jz	SHORT @@HaveLength		; Yes, we are done
		stosb					; No, copy character
		inc	[BYTE CommandLine]		; Advance command line length
@@HaveLength:	mov	[BYTE edi],0			; Zero terminate command line
		mov	edi,ebx				; EDI points to driver header name field
		mov	esi,OFFSET DriverName		; ESI points to driver name
		mov	ecx,2				; ECX = number of DWORDs to copy
		rep	movsd				; Copy driver name
		mov	ah,DOS_ENVIRONMENT_SIZE		; Get environment size
		call	[DWORD DosApi]
		mov	ecx,eax				; ECX = size of environment
		call	[DWORD AllocateBlock]		; Allocate buffer
		jc	_Not_Enough_Memory_		; Success ?
		mov	[_Envptr],eax			; Yes, save pointer to environment
		mov	[_Envsize],ecx			; Save environment size
		mov	eax,OFFSET StartOfStack		; EAX points past _BSS segment
		mov	[_STACKTOP],eax			; Set stack top
		mov	[_curbrk],eax			; Set first available memory location
		mov	ah,DOS_GET_VERSION		; Get DOS version
		call	[DWORD DosApi]
		mov	[_osmajor],ah			; Save version numbers
		mov	[_osminor],al
		mov	ah,VIDEO_GET_MODE		; Get video mode
		call	[DWORD BiosVideo]
		mov	[WORD VideoMode],ax		; Save mode and columns
		mov	[WORD VideoRows],bx		; Save rows and page number
		call	InitializeEnvironment		; Copy environment and initialize pointer array
		mov	eax,0ffh			; Run all initializers
		call	__InitRtns			; Call initializer routines
		xor	ebp,ebp				; EBP = 0 indicates end of EBP chain
		mov	[ExitESP],esp			; Save ESP
		call	__CMain				; Invoke main
LABEL		__exit_			PROC
		push	eax				; Save exit code
		xor	eax,eax				; Run finalizers
		mov	edx,0fh				; Less than exit
		call	__FiniRtns			; Call finalizer routines
LABEL		Exit			PROC
		xor	eax,eax				; Clear EAX
		xchg	eax,[_Envptr]			; Get and clear pointer to environment block
		call	[DWORD FreeBlock]		; Free it
		pop	eax				; EAX = exit code
		mov	esp,[ExitESP]			; Restore ESP
		ret
LABEL		__do_exit_with_msg__	PROC
		push	edx				; Save context
		push	eax
		mov	edx,OFFSET ConsoleName		; EDX points to DOS console device name
		mov	eax,DOS_OPEN_FILE SHL 8 + 1110b	; Open with write only access
		call	[DWORD DosApi]
		mov	ebx,eax				; EBX = file handle
		pop	edx				; EDX points to message
		xor	ecx,ecx				; Clear ECX
		mov	esi,edx				; EDI points to message
		xor	al,al				; AL = character to search for
		cld					; Assure forward direction of string instructions
@@Again:	lodsb					; Get next character in AL
		inc	ecx				; Advance character counter
		or	al,al				; Terminating zero ?
		jnz	@@Again				; No, process next character
		dec	ecx				; Yes, ECX = number of characters to write
		mov	ah,DOS_WRITE_FILE		; Write string to STDOUT
		call	[DWORD DosApi]
		jmp	Exit				; Restore exit code and exit
ENDP
;
; PROCEDURE	InitializeEnvironment
;
; INPUT		NONE
;
; OUTPUT	NONE
;
; DESCRIPTION	Copies environment to uses space and initializes environment
;		pointer array.
;
PROC		InitializeEnvironment
		mov	edx,[_Envptr]			; EDX points to start of environment
		mov	ah,DOS_GET_ENVIRONMENT		; Copy environment
		call	[DWORD DosApi]
		mov	[_Envlength],eax		; Update environment length
		lea	ecx,[edx + eax + 3]		; Calculate start of environment pointer array
		and	cl,NOT 3			; Align to DWORD boundary
		mov	[environ],ecx			; Save pointer to environment pointer array
		mov	edi,ecx				; EDI points to environment pointer array
		mov	esi,edx				; ESI points to start of environment
		add	edx,[_Envsize]			; EDX points past environment buffer
		sub	edx,4				; EDX points to last DWORD in buffer
@@NextString:	cmp	edx,edi				; At end of buffer ?
		jz	SHORT @@MarkEnd			; Yes, mark end of array
		mov	eax,esi				; No, EAX points to environment string
		stosd					; Save and advance to next entry
@@NextChar:	lodsb					; Get next character and advance pointer
		or	al,al				; End of string ?
		jnz	@@NextChar			; No, get next character
		cmp	al,[esi]			; At end of environment ?
		jnz	@@NextString			; No, process next string
@@MarkEnd:	xor	eax,eax				; Yes, clear EAX
		stosd					; Mark end of array
		mov	[_STACKLOW],edi			; Save low address of stack
		ret
ENDP
		DATASEG
		EXTRN	C _curbrk			: DWORD
	        EXTRN	C _STACKLOW			: DWORD
        	EXTRN	C _STACKTOP			: DWORD
		EXTRN	C _LpCmdLine			: DWORD
		EXTRN	C _LpPgmName			: DWORD
		EXTRN	C _Envptr			: DWORD
		EXTRN	C _osmajor			: BYTE
        	EXTRN	C _osminor			: BYTE
		EXTRN	C DriverName			: BYTE
		PUBLIC	C environ
		PUBLIC	C _init_387_emulator
environ		DD	0				; Holds first pointer in environment pointer array
ConsoleName	DB	'CON'				; DOS console name
LABEL		_init_387_emulator	BYTE
		DB	0				; To prevent emulator from coming in with -fpi

		UDATASEG
		EXTRN	StartOfBSS			: BYTE
		PUBLIC	C _Envsize
		PUBLIC	C _Envlength
		PUBLIC	C _PID
		PUBLIC	C VideoMode
		PUBLIC	C VideoColumns
		PUBLIC	C VideoRows
		PUBLIC	C VideoPage
_Envsize	DD	?				; Environment size
_Envlength	DD	?				; Environment length
_PID		DD	?				; Process ID
VideoMode	DB	?				; Video mode
VideoColumns	DB	?				; Video columns
VideoRows	DB	?				; Video rows
VideoPage	DB	?				; Video page number
ExitESP		DD	?				; Holds ESP before call to __CMain
CommandLine	DB	256 DUP (?)			; Driver command line
DriverPath	DB	80 DUP (?)			; Full path of loaded driver
		STACK
		EXTRN	StartOfStack			: BYTE
		END
