;
; ZDOS run time library function.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		PUBLIC	DosGetCurrentDriveData
;
; DECLARATION	int DosGetCurrentDriveData( DRVDATA *data );
;
PROC		DosGetCurrentDriveData	WATCOM_C
		USES	esi,edx,ecx,ebx
		mov	esi,eax				; ESI points to buffer
		mov	ah,DOS_GET_CURRENT_DRIVE_DATA	; AH = DOS function
		;
		; Call DOS services
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosApi]
ELSE
		int	DOS
ENDIF
		movzx	eax,al				; EAX = sectors/cluster
		mov	[(DRVDATA esi).SPC],eax		; Save sectors/cluster
		mov	[(DRVDATA esi).BPS],ecx		; Save bytes/sector
		mov	[(DRVDATA esi).Clusters],edx	; Save number of clusters
		movzx	ecx,[BYTE ebx]			; ECX = media ID byte
		mov	[(DRVDATA esi).MediaID],ecx	; Save media ID
		ret
ENDP
		END
