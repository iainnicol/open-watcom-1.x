;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		INCLUDE	'ZDOSDRV.INC'
		INCLUDE	'SEGMENTS.INC'
		DOSSEG
;
; Driver stack frame
;
STRUC		REGS
EDI		DD	?
ESI		DD	?
EBP		DD	?
ESP		DD	?
EBX		DD	?
EDX		DD	?
ECX		DD	?
EAX		DD	?
ENDS

SEGMENT		_TEXT
		ASSUME	cs:_TEXT,ds:DGROUP,es:DGROUP,ss:DGROUP
		EXTRN	InitializeDriver		: PROC
		EXTRN	DriverCreateDirectory_		: PROC
		EXTRN	DriverDeleteDirectory_		: PROC
		EXTRN	DriverCreateFile_		: PROC
		EXTRN	DriverOpenFile_			: PROC
		EXTRN	DriverCloseFile_		: PROC
		EXTRN	DriverReadFile_			: PROC
		EXTRN	DriverWriteFile_		: PROC
		EXTRN	DriverDeleteFile_		: PROC
		EXTRN	DriverGetFileAttributes_	: PROC
		EXTRN	DriverSetFileAttributes_	: PROC
		EXTRN	DriverFindFirstFile_		: PROC
		EXTRN	DriverFindNextFile_		: PROC
		EXTRN	DriverRenameFile_		: PROC
		EXTRN	DriverGetFreeSpace_		: PROC
		PUBLIC	C cstart_
LABEL		cstart_			BYTE
Header		FSD	<0, FileSystemEntry, '_NONAME_'>
;
; PROCEDURE	FileSystemEntry
;
; INPUT		 AH = file system function
;		EBX = pointer to DPB
;		Other registers depends on function
;
; OUTPUT	CF = 0: function executed successfully
;		        Register settings depends on function
;		CF = 1: EAX = DOS error code
;
; DESCRIPTION	Invokes file system driver command handler.
;
PROC		FileSystemEntry
		pushad					; Save context
		mov	ebp,esp				; Setup stack frame
		movzx	eax,ah				; EAX = driver function number
		jmp	[DriverFunctions + eax * 4]	; Invoke driver function
ENDP
;
; PROCEDURE	FileSystemError
;
; INPUT		EAX = error code
;		EBP = pointer to stack frame
;
; OUTPUT	CF = 1: EAX = error code
;
; DESCRIPTION	Exit with carry set and EAX = error code.
;
PROC		FileSystemError
		mov	[(REGS ebp).EAX],eax		; Update callers EAX
		stc					; Set carry flag
LABEL		FileSystemExit		PROC
		popad					; Restore context
		ret
ENDP
;
; PROCEDURE	CreateDirectory
;
; INPUT		EBX = pointer to DPB
;		ECX = offset of first name to match in optimized search
;		EDX = directory starting cluster in optimized search
;		EDI = pointer to zero terminated pathname
;		EBP = pointer to stack frame
;
; OUTPUT	CF = 0: Directory created
;		CF = 1: EAX = DOS error code
;
; DESCRIPTION	Creates a new directory.
;
PROC		CreateDirectory
		mov	eax,edi				; EAX points to zero terminated path name
		;
		; DriverCreateDirectory( char *path, unsigned cluster,
		;                        DPB *dpb, int nameoffset )
		;
		call	DriverCreateDirectory_
		or	eax,eax				; Success ?
		jnz	FileSystemError			; No, exit with carry flag set and error code in EAX
		jmp	FileSystemExit			; Yes, exit with carry flag clear
ENDP
;
; PROCEDURE	DeleteDirectory
;
; INPUT		EBX = pointer to DPB
;		ECX = offset of first name to match in optimized search
;		EDX = directory starting cluster in optimized search
;		EDI = pointer to zero terminated pathname
;		EBP = pointer to stack frame
;
; OUTPUT	CF = 0: Directory deleted
;		CF = 1: EAX = DOS error code
;
; DESCRIPTION	Deletes a directory.
;
PROC		DeleteDirectory
		mov	eax,edi				; EAX points to zero terminated path name
		;
		; DriverDeleteDirectory( char *path, unsigned cluster,
		;                        DPB *dpb, int nameoffset )
		;
		call	DriverDeleteDirectory_
		or	eax,eax				; Success ?
		jnz	FileSystemError			; No, exit with carry flag set and error code in EAX
		jmp	FileSystemExit			; Yes, exit with carry flag clear
ENDP
;
; PROCEDURE	CreateFile
;
; INPUT		 AL = file attributes (on stack)
;		EBX = pointer to DPB
;		ECX = offset of first name to match in optimized search
;		EDX = directory starting cluster in optimized search
;		ESI = pointer to SFT handle
;		EDI = pointer to zero terminated pathname
;		EBP = pointer to stack frame
;
; OUTPUT	CF = 0: file created
;		CF = 1: EAX = DOS error code
;
; DESCRIPTION	Creates a file.
;
PROC		CreateFile
		movzx	eax,[BYTE (REGS ebp).EAX]	; EAX = file attributes
		;
		; DriverCreateFile( int attributes, unsigned cluster,
		;                   DPB *dpb, int nameoffset,
		;                   SFT *handle, char *path )
		;
		call	DriverCreateFile_ STDCALL,esi,edi
		or	eax,eax				; Success ?
		jnz	FileSystemError			; No, exit with carry flag set and error code in EAX
		jmp	FileSystemExit			; Yes, exit with carry flag clear
ENDP
;
; PROCEDURE	OpenFile
;
; INPUT		 AL = access and sharing mode flags (on stack)
;		EBX = pointer to DPB
;		ECX = offset of first name to match in optimized search
;		EDX = directory starting cluster in optimized search
;		ESI = pointer to SFT handle
;		EDI = pointer to zero terminated pathname
;		EBP = pointer to stack frame
;
; OUTPUT	CF = 0: file opened
;		CF = 1: EAX = DOS error code
;
; DESCRIPTION	Opens a file.
;
PROC		OpenFile
		movzx	eax,[BYTE (REGS ebp).EAX]	; EAX = file access and sharing mode flags
		;
		; DriverOpenFile( int flags, unsigned cluster, DPB *dpb,
		;                 int nameoffset, SFT *handle, char *path )
		;
		call	DriverOpenFile_ STDCALL,esi,edi
		or	eax,eax				; Success ?
		jnz	FileSystemError			; No, exit with carry flag set and error code in EAX
		jmp	FileSystemExit			; Yes, exit with carry flag clear
ENDP
;
; PROCEDURE	CloseFile
;
; INPUT		EBX = pointer to DPB
;		ESI = pointer to SFT handle
;		EBP = pointer to stack frame
;
; OUTPUT	CF = 0: File successfully closed
;		CF = 1: EAX = DOS error code
;
; DESCRIPTION	Closes a file.
;
PROC		CloseFile
		mov	eax,ebx				; EAX = pointer to DPB
		mov	edx,esi				; EDX = pointer to SFT handle
		;
		; DriverCloseFile( DPB *dpb, SFT *handle )
		;
		call	DriverCloseFile_
		or	eax,eax				; Success ?
		jnz	FileSystemError			; No, exit with carry flag set and error code in EAX
		jmp	FileSystemExit			; Yes, exit with carry flag clear

ENDP
;
; PROCEDURE	ReadFile
;
; INPUT		EBX = pointer to DPB
;		ECX = number of bytes to read
;		EDX = pointer to buffer
;		ESI = pointer to SFT handle
;		EBP = pointer to stack frame
;
; OUTPUT	CF = 0: EAX = number of bytes read
;		CF = 1: EAX = DOS error code
;
; DESCRIPTION	Reads from a file.
;
PROC		ReadFile
		lea	eax,[(REGS ebp).EAX]		; EAX points to stack frame EAX
		;
		; DriverReadFile( unsigned *bytes, void *buffer, DBP *dpb,
		;                 unsigned count, SFT *handle )
		;
		call	DriverReadFile_ STDCALL,esi
		or	eax,eax				; Success ?
		jnz	FileSystemError			; No, exit with carry flag set and error code in EAX
		jmp	FileSystemExit			; Yes, exit with carry flag clear
ENDP
;
; PROCEDURE	WriteFile
;
; INPUT		EBX = pointer to DPB
;		ECX = number of bytes to write
;		EDX = pointer to buffer
;		ESI = pointer to SFT handle
;		EBP = pointer to stack frame
;
; OUTPUT	CF = 0: EAX = number of bytes written
;		CF = 1: EAX = DOS error code
;
; DESCRIPTION	Writes to a file.
;
PROC		WriteFile
		lea	eax,[(REGS ebp).EAX]		; EAX points to stack frame EAX
		;
		; DriverWriteFile( unsigned *bytes, void *buffer, DBP *dpb,
		;                  unsigned count, SFT *handle )
		;
		call	DriverWriteFile_ STDCALL,esi
		or	eax,eax				; Success ?
		jnz	FileSystemError			; No, exit with carry flag set and error code in EAX
		jmp	FileSystemExit			; Yes, exit with carry flag clear
ENDP
;
; PROCEDURE	DeleteFile
;
; INPUT		EBX = pointer to DPB
;		ECX = offset of first name to match in optimized search
;		EDX = directory starting cluster in optimized search
;		EDI = pointer to zero terminated pathname
;		EBP = pointer to stack frame
;
; OUTPUT	CF = 0: File successfully deleted
;		CF = 1: EAX = DOS error code
;
; DESCRIPTION	Deletes a file.
;
PROC		DeleteFile
		mov	eax,edi				; EAX points to zero terminated path name
		;
		; DriverDeleteFile( char *path, unsigned cluster,
		;                   DPB *dpb, int nameoffset )
		;
		call	DriverDeleteFile_
		or	eax,eax				; Success ?
		jnz	FileSystemError			; No, exit with carry flag set and error code in EAX
		jmp	FileSystemExit			; Yes, exit with carry flag clear
ENDP
;
; PROCEDURE	GetFileAttributes
;
; INPUT		EBX = pointer to DPB
;		ECX = offset of first name to match in optimized search
;		EDX = directory starting cluster in optimized search
;		EDI = pointer to zero terminated pathname
;		EBP = pointer to stack frame
;
; OUTPUT	CF = 0: EAX = attributes
;		CF = 1: EAX = DOS error code
;
; DESCRIPTION	Returns file attributes.
;
PROC		GetFileAttributes
		lea	eax,[(REGS ebp).EAX]		; EAX points to stack frame EAX
		;
		; DriverGetFileAttributes( int *attributes, unsigned cluster,
		;                          DPB *dpb, int nameoffset,
		;                          char *path )
		;
		call	DriverGetFileAttributes_ STDCALL,edi
		or	eax,eax				; Success ?
		jnz	FileSystemError			; No, exit with carry flag set and error code in EAX
		jmp	FileSystemExit			; Yes, exit with carry flag clear
ENDP
;
; PROCEDURE	SetFileAttributes
;
; INPUT		 AL = new file attributes (on stack)
;		EBX = pointer to DPB
;		ECX = offset of first name to match in optimized search
;		EDX = directory starting cluster in optimized search
;		EDI = pointer to zero terminated pathname
;		EBP = pointer to stack frame
;
; OUTPUT	CF = 0: EAX = attributes
;		CF = 1: EAX = DOS error code
;
; DESCRIPTION	Sets file attributes.
;
PROC		SetFileAttributes
		and	[(REGS ebp).EAX],0ffh		; Convert attribute to integer value
		lea	eax,[(REGS ebp).EAX]		; EAX points to stack frame EAX
		;
		; DriverSetFileAttributes( int *attributes, unsigned cluster,
		;                          DPB *dpb, int nameoffset,
		;                          char *path )
		;
		call	DriverSetFileAttributes_ STDCALL,edi
		or	eax,eax				; Success ?
		jnz	FileSystemError			; No, exit with carry flag set and error code in EAX
		jmp	FileSystemExit			; Yes, exit with carry flag clear
ENDP
;
; PROCEDURE	FindFirstFile
;
; INPUT		 AL = attributes to use in search (on stack)
;		EBX = pointer to DPB
;		ECX = offset of first name to match in optimized search
;		EDX = directory starting cluster in optimized search
;		ESI = pointer to FIND block
;		EDI = pointer to zero terminated pathname
;		EBP = pointer to stack frame
;
; OUTPUT	CF = 0: FIND block is filled with data
;		CF = 1: EAX = DOS error code
;
; DESCRIPTION	Finds first matching file.
;
PROC		FindFirstFile
		movzx	eax,[BYTE (REGS ebp).EAX]	; EAX = search attributes
		;
		; DriverFindFirstFile( int attributes, unsigned cluster,
		;                      DPB *dpb, int nameoffset,
		;                      FIND *find, char *path )
		;
		call	DriverFindFirstFile_ STDCALL,esi,edi
		or	eax,eax				; Success ?
		jnz	FileSystemError			; No, exit with carry flag set and error code in EAX
		jmp	FileSystemExit			; Yes, exit with carry flag clear
ENDP
;
; PROCEDURE	FindNextFile
;
; INPUT		EBX = pointer to DPB
;		ESI = pointer to FIND block
;		EBP = pointer to stack frame
;
; OUTPUT	CF = 0: FIND block is updated
;		CF = 1: EAX = DOS error code
;
; DESCRIPTION	Finds next matching file.
;
PROC		FindNextFile
		mov	eax,ebx				; EAX points to DPB
		mov	edx,esi				; EDX points to FIND block
		;
		; DriverFindNextFile( DPB *dpb, FIND *find )
		;
		call	DriverFindNextFile_
		or	eax,eax				; Success ?
		jnz	FileSystemError			; No, exit with carry flag set and error code in EAX
		jmp	FileSystemExit			; Yes, exit with carry flag clear
ENDP
;
; PROCEDURE	RenameFile
;
; INPUT		EBX = pointer to DPB
;		ESI = pointer to current path FILE block
;		EDI = pointer to new patch FILE block
;		EBP = pointer to stack frame
;
; OUTPUT	CF = 0: File renamed/moved
;		CF = 1: EAX = DOS error code
;
; DESCRIPTION	Renames or moves a file.
;
PROC		RenameFile
		mov	eax,esi				; EAX points to old path
		mov	edx,edi				; EDX points to new path
		;
		; DriverRenameFile( char *oldpath, char *newpath, DPB *dpb )
		;
		call	DriverRenameFile_
		or	eax,eax				; Success ?
		jnz	FileSystemError			; No, exit with carry flag set and error code in EAX
		jmp	FileSystemExit			; Yes, exit with carry flag clear
ENDP
;
; PROCEDURE	GetFreeSpace
;
; INPUT		EBX = pointer to DPB
;		EBP = pointer to stack frame
;
; OUTPUT	CF = 0: EAX = number of free clusters
;		CF = 1: EAX = DOS error code
;
; DESCRIPTION	Returns free space information for the specified drive.
;
PROC		GetFreeSpace
		lea	edx,[(REGS ebp).EAX]		; EDX points to stack frame EAX
		mov	eax,ebx				; EAX points to DPB
		;
		; DriverGetFreeSpace( DPB *dpb, unsigned *clusters )
		;
		call	DriverGetFreeSpace_
		or	eax,eax				; Success ?
		jnz	FileSystemError			; No, exit with carry flag set and error code in EAX
		jmp	FileSystemExit			; Yes, exit with carry flag clear
ENDP
;
; PROCEDURE	DriverStart
;
; INPUT		ESI = pointer to command line
;
; OUTPUT	EAX = break address
;
; DESCRIPTION	Invokes driver initialization routine.
;
PROC		DriverStart
		mov	eax,OFFSET StartOfStack		; EAX = break address on success
		pushad					; Save context
		lea	ebx,[Header.DriverName]		; EBX points to driver name
		call	InitializeDriver		; Initialize C runtime
		or	eax,eax				; Success ?
		jz	SHORT @@Exit			; Yes, we are done
		mov	[(REGS esp).EAX],OFFSET cstart_	; No, we need to remove the driver from memory
@@Exit:		popad					; Restore context
		ret
ENDP
ENDS

SEGMENT		_DATA
DriverFunctions	DD	CreateDirectory			; 00h
		DD	DeleteDirectory			; 01h
		DD	CreateFile			; 02h
		DD	OpenFile			; 03h
		DD	CloseFile			; 04h
		DD	ReadFile			; 05h
		DD	WriteFile			; 06h
		DD	DeleteFile			; 07h
		DD	GetFileAttributes		; 08h
		DD	SetFileAttributes		; 09h
		DD	FindFirstFile			; 0ah
		DD	FindNextFile			; 0bh
		DD	RenameFile			; 0ch
		DD	GetFreeSpace			; 0dh
ENDS

SEGMENT		_BSS
		PUBLIC	StartOfBSS
LABEL		StartOfBSS		BYTE
ENDS

SEGMENT		STACK
		PUBLIC	StartOfStack
LABEL		StartOfStack		BYTE
ENDS
		END	DriverStart
