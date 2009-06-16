;
; ZDOS run time library function.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		PUBLIC	DosExecuteProcess
;
; DECLARATION	int DosExecuteProcess( int priority, char *path, void *env,
;		                       int flags, int trace, char *cmdline );
;
PROC		DosExecuteProcess	WATCOM_C
		ARG	Priority : DWORD, Path : DWORD, Environment : DWORD, \
			Flags : DWORD, Trace : DWORD, CommandLine : DWORD
		USES	esi
		mov	ch,[BYTE Trace]			; CH = trace flag
		mov	esi,[CommandLine]		; ESI points to command line
		mov	ah,DOS_EXECUTE_PROCESS		; AH = DOS function number
		;
		; Call DOS services
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosApi]
ELSE
		int	DOS
ENDIF
		jnc	SHORT @@Exit			; Error ?
		neg	eax				; Yes, negate error code
@@Exit:		ret
ENDP
		END
