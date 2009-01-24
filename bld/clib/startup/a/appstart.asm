;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		INCLUDE	'SEGMENTS.INC'
SEGMENT		BEGTEXT
		ASSUME	cs:BEGTEXT,ds:DGROUP,es:DGROUP,ss:DGROUP
		PUBLIC	___begtext
		PUBLIC	MemoryStart
		PUBLIC	C cstart_
		ORG	3
LABEL		___begtext		BYTE
		DB	13 DUP (90h)			; Fill unused part of segment with NOPs
		ORG	0
LABEL		cstart_			BYTE
LABEL		MemoryStart		BYTE
		mov	eax,OFFSET NullCodeMessage	; EAX points to message
		jmp	Abort				; Display message and terminate application
ENDS
SEGMENT		_NULL
		PUBLIC	__nullarea
__nullarea	DB	01h,01h,01h,00h			; Needed by WATCOM debugger
ENDS
SEGMENT		_TEXT
		ASSUME	cs:_TEXT,ds:DGROUP,es:DGROUP,ss:DGROUP
		EXTRN	__CMain				: PROC
		EXTRN	__InitRtns			: PROC
		EXTRN	__FiniRtns			: PROC
		PUBLIC	__exit_
		PUBLIC	__do_exit_with_msg__
		PUBLIC	InitializeEnvironment
;
; PROCEDURE	Start
;
; INPUT		EAX = PID
;		EBX = command line length (excluding length byte and CR)
;		ECX = environment size
;
; OUTPUT	NONE
;
; DESCRIPTION	Initializes runtime library.
;
PROC		Start
		push	ecx				; Save context
		push	eax
		mov	ecx,OFFSET StartOfStack		; ECX points past end of BSS segment
		mov	edi,OFFSET StartOfBSS		; EDI points to start of BSS
		sub	ecx,edi				; ECX = number of bytes to initialize
		shr	ecx,2				; ECX = number of DWORDs to initialize
		xor	eax,eax				; EAX = filler
		rep	stosd				; Fill with zeros
		pop	eax				; Restore context
		pop	ecx
		mov	[_PID],eax			; Save process ID
		mov	[_curbrk],OFFSET StartOfStack	; Set first available memory location
		mov	ebx,OFFSET MemoryStart		; EBX points to start of memory
		mov	edx,esp				; EDX = initial ESP
		and	edx,NOT (4 SHL 20 - 1)		; EDX = lowest ESP
		lea	edi,[edx + 1]			; EDI = pointer to C command line
		mov	ah,DOS_GET_COMMAND_LINE		; Copy command line to buffer
		int	DOS
		mov	[_LpCmdLine],edi		; Save pointer to C command line buffer
		mov	[BYTE edx + eax - 1],0		; Zero terminate command line
		add	edx,eax				; EDX points to buffer for program name
		mov	[_LpPgmName],edx		; Save pointer to program name (for argv[0])
		mov	ah,DOS_GET_PROCESS_PATH		; Copy program name to buffer
		int	DOS
		add	edx,eax				; EDX points to buffer for environment
		sub	ecx,eax				; ECX = environment size
		mov	[_Envptr],edx			; Save pointer to environment
		mov	[_Envsize],ecx			; Save environment size
		mov	[_STACKTOP],esp			; Set stack top
		mov	ah,DOS_GET_VERSION		; Get DOS version
		int	DOS
		mov	[_osmajor],ah			; Save version numbers
		mov	[_osminor],al
		call	InitializeEnvironment		; Copy environment and initialize pointer array
		mov	eax,0ffh			; Run all initializers
		call	__InitRtns			; Call initializer routines
		xor	ebp,ebp				; EBP = 0 indicates end of EBP chain
		call	__CMain				; Invoke main
LABEL		__exit_			PROC
		push	eax				; Save exit code
		xor	eax,eax				; Run finalizers
		mov	edx,0fh				; Less than exit
		call	__FiniRtns			; Call finalizer routines
LABEL		Exit			PROC
		pop	eax				; EAX = exit code
		mov	ah,DOS_EXIT_PROCESS		; Exit to DOS
		int	DOS
LABEL		Abort			PROC
		mov	dl,4				; DL = error code
LABEL		__do_exit_with_msg__	PROC
		push	edx				; Save error code
		push	eax				; Save pointer to message
		mov	edx,OFFSET ConsoleName		; EDX points to DOS console device name
		mov	eax,DOS_OPEN_FILE SHL 8 + 1110b	; Open with write only access
		int	DOS
		mov	ebx,eax				; EBX = file handle
		pop	edx				; EDX points to message
		xor	ecx,ecx				; Clear ECX
		mov	esi,edx				; ESI points to message
		xor	al,al				; AL = character to search for
		cld					; Assure forward direction of string instructions
@@Again:	lodsb					; Get next character in AL
		inc	ecx				; Advance character counter
		or	al,al				; Terminating zero ?
		jnz	@@Again				; No, process next character
		dec	ecx				; Yes, ECX = number of characters to write
		mov	ah,DOS_WRITE_FILE		; Write string to STDOUT
		int	DOS
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
		int	DOS
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
ENDS

SEGMENT		_DATA
		EXTRN	C _curbrk			: DWORD
	        EXTRN	C _STACKLOW			: DWORD
        	EXTRN	C _STACKTOP			: DWORD
		EXTRN	C _LpCmdLine			: DWORD
		EXTRN	C _LpPgmName			: DWORD
		EXTRN	C _Envptr			: DWORD
		EXTRN	C _osmajor			: BYTE
        	EXTRN	C _osminor			: BYTE
		PUBLIC	C environ
		PUBLIC	C _init_387_emulator
environ		DD	0				; Holds first pointer in environment pointer array
ConsoleName	DB	'CON'				; DOS console name
LABEL		_init_387_emulator	BYTE
		DB	0				; To prevent emulator from coming in with -fpi
NullCodeMessage	DB	13,10,'Null code pointer called',0
ENDS

SEGMENT		_BSS
		PUBLIC	C _Envsize
		PUBLIC	C _Envlength
		PUBLIC	C _PID
LABEL		StartOfBSS		BYTE
_Envsize	DD	?				; Environment size
_Envlength	DD	?				; Environment length
_PID		DD	?				; Process ID
ENDS

SEGMENT		STACK
LABEL		StartOfStack		BYTE
ENDS
		END	Start
