;
; ZDOS run time library function.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	DosReturnZero			: PROC
		PUBLIC	DosQueryFileSystemName
;
; DECLARATION	int DosQueryFileSystemName( int id, char **name );
;
PROC		DosQueryFileSystemName	WATCOM_C
		push	ebx				; Save context
		mov	ebx,edx				; EBX points to name pointer
		mov	edx,eax				; EDX = file system ID
		mov	ah,2				; Query file system name
		call	[DWORD DosFileSystem]
		mov	[ebx],eax			; Update name pointer variable
		pop	ebx				; Restore context
		jmp	DosReturnZero			; Process return code
ENDP
		END
