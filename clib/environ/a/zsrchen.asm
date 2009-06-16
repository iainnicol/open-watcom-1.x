;
; ZDOS run time library function.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		CODESEG
		EXTRN	WATCOM_C getcwd			: PROC
		EXTRN	WATCOM_C strlen			: PROC
		EXTRN	WATCOM_C access			: PROC
		EXTRN	WATCOM_C getenv			: PROC
		PUBLIC	_searchenv
;
; DECLARATION	void _searchenv( char *name, char *envname, char *path );
;
PROC		_searchenv		WATCOM_C
		USES	edi,esi,ecx
		test	[_Envptr],-1			; Environment buffer available ?
		jnz	SHORT @@Error			; No, we are done
		mov	esi,eax				; Yes, save pointer to name in ESI
		mov	edi,edx				; Save pointer to envname in EDI
		call	CheckName			; Check name
		jc	SHORT @@Error			; Valid name ?
		call	getcwd				; Yes, get working directory
		call	strlen				; Get string length
		cmp	[BYTE ebx + eax - 1],'\'	; Path ends with backslash ?
		jz	SHORT @@AddName			; Yes, proceed
		mov	[BYTE ebx + eax],'\'		; No, add one
		inc	eax				; Advance character count
@@AddName:	push	edi				; Save context
		push	esi
		lea	edi,[ebx + eax]			; EDI points past last backslash
		mov	eax,esi				; EAX points to name
		call	strlen				; Get string length
		lea	ecx,[eax + 1]			; ECX = number of characters to copy
		rep	movsb				; Append name to path
		pop	esi				; Restore context
		pop	edi
		mov	eax,ebx				; EAX points to path
		xor	edx,edx				; EDX = mode
		call	access				; Try to access the file
		or	eax,eax				; File exist ?
		jz	SHORT @@Exit			; Yes, we are done
		mov	eax,edi				; No, EAX points to environment name
		call	getenv				; Get pointer to environment string
		or	eax,eax				; Environment variable found ?
		jz	SHORT @@ProcessPaths		; Yes, process paths
@@Error:	mov	[BYTE ebx],0			; No, reset path pointer
@@Exit:		ret
@@ProcessPaths:	mov	edi,eax				; EDI points to string of paths
@@NextPath:	call	BuildPath			; Build path
		jc	@@Error				; Success ?
		mov	eax,ebx				; Yes, EAX points to path
		xor	edx,edx				; EDX = mode
		call	access				; Try to access the file
		or	eax,eax				; File exist ?
		jz	@@Exit				; Yes, we are done
		jmp	@@NextPath			; No, build next path and try again
ENDP
;
; PROCEDURE	CheckName
;
; INPUT		ESI = pointer to name
;
; OUTPUT	CF = 0: name valid
;		CF = 1: name not valid
;
; DESCRIPTION	Checks if name pointed by ESI is in DOS 8.3 format.
;
PROC		CheckName
		push	edi				; Save context
		push	esi
		mov	eax,esi				; EAX points to filename
		call	strlen				; Get length of string
		or	eax,eax				; Length = 0 ?
		jz	SHORT @@Error			; Yes, invalid name
		mov	edx,eax				; No, save length in EDX
		xor	eax,eax				; Clear EAX
		cmp	edx,12				; Valid filename length ?
		ja	SHORT @@Error			; No, invalid name
		mov	ecx,edx				; Yes, ECX = length of filename
		mov	edi,esi				; EDI points to filename
		mov	al,'\'				; AL = character to search for
		repnz	scasb				; Find '\'
		jz	SHORT @@Error			; Found it ?
		mov	ecx,edx				; No, ECX = length of filename
		mov	edi,esi				; EDI points to filename
		mov	al,':'				; AL = character to search for
		repnz	scasb				; Find ':'
		jz	SHORT @@Error			; Found it ?
		mov	ecx,308h			; No, CH = extension limit and CL = name limit
@@CheckName:	lodsb					; Get next character in AL
		or	al,al				; End of string ?
		jz	SHORT @@Exit			; Yes, set success flag and exit
		cmp	al,'.'				; Extension separator ?
		jz	SHORT @@CheckExt		; Yes, check extension
		dec	cl				; No, count down name limit
		jnz	@@CheckName			; Process next character
		lodsb					; Get next character in AL
		or	al,al				; End of string ?
		jz	SHORT @@Exit			; Yes, set success flag and exit
		cmp	al,'.'				; Extension field follows ?
		jnz	SHORT @@Error			; No, invalid name
@@CheckExt:	lodsb					; Get next character in AL
		or	al,al				; End of string ?
		jz	SHORT @@Done			; Yes, check extension length
		cmp	al,'.'				; Extension separator ?
		jz	SHORT @@Error			; Yes, error
		dec	ch				; No, count down extension limit
		jnz	@@CheckExt			; Process next character
		cmp	[BYTE esi],ah			; End of string ?
		jnz	SHORT @@Error			; No, error
@@Done:		cmp	ch,3				; Valid extension ?
		jnz	SHORT @@Error			; No, error
@@Exit:		inc	ah				; Yes, set success flag
@@Error:	cmp	ah,1				; Set or clear carry flag
		pop	esi				; Restore context
		pop	edi
		ret
ENDP
;
; PROCEDURE	BuildPath
;
; INPUT		EBX = pointer to path buffer
;		ESI = pointer to name
;		EDI = pointer to string of paths separated with ';'
;
; OUTPUT	CF = 0: path buffer holds valid path
;		        EDI points to next path string
;		CF = 1: no more valid path found
;
; DESCRIPTION	Collects the next path from string of paths and combines it
;		with the name.
;
PROC		BuildPath
		push	esi				; Save context
		push	ebx
		cmp	[BYTE edi],1			; End of string ?
		jc	SHORT @@Exit			; Yes, we are done
@@CopyPath:	mov	al,[edi]			; Get next character from path
		or	al,al				; End of string ?
		jz	SHORT @@EndOfString		; Yes, we are at end of string
		cmp	al,';'				; String separator ?
		jz	SHORT @@EndOfPath		; Yes, we are at end of path component
		mov	[ebx],al			; No, copy character to buffer
		inc	edi				; Advance pointer to strings of paths
		inc	ebx				; Advance pointer to path buffer
		jmp	@@CopyPath			; Copy next character
@@EndOfPath:	inc	edi				; Skip past ';'
@@EndOfString:	cmp	[BYTE ebx - 1],'\'		; Was last stored character a '\' ?
		jz	SHORT @@CopyName		; Yes, copy
		mov	[BYTE ebx],'\'			; No, add a '\'
		inc	ebx				; Advance past '\'
@@CopyName:	lodsb					; Get next character in AL
		mov	[ebx],al			; Store in buffer
		inc	ebx				; Advance pointer to buffer
		or	al,al				; Entire name copied ?
		jnz	@@CopyName			; No, copy next character
@@Exit:		pop	ebx				; Restore context
		pop	esi
		ret
ENDP
		UDATASEG
		EXTRN	WATCOM_C _Envptr		: DWORD
		END
