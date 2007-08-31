;
; ZDOS API function numbers (INT 21h)
;
DOS_TERMINATE_PROCESS		=	00h
DOS_CONSOLE_INPUT		=	01h
DOS_CONSOLE_OUTPUT		=	02h
DOS_AUXILIARY_INPUT		=	03h
DOS_AUXILIARY_OUTPUT		=	04h
DOS_PRINTER_OUTPUT		=	05h
DOS_DIRECT_CONSOLEIO		=	06h
DOS_CONSOLE_INPUT_RAW_NO_ECHO	=	07h
DOS_CONSOLE_INPUT_NO_ECHO	=	08h
DOS_CONSOLE_DISPLAY_STRING	=	09h
DOS_CONSOLE_BUFFERED_INPUT	=	0ah
DOS_CHECK_INPUT_STATUS		=	0bh
DOS_FLUSH_BEFORE_INPUT		=	0ch
DOS_DISK_RESET			=	0dh
DOS_SET_CURRENT_DRIVE		=	0eh
DOS_GET_CURRENT_DRIVE		=	19h
DOS_GET_CURRENT_DRIVE_DATA	=	1bh
DOS_GET_DRIVE_DATA		=	1ch
DOS_GET_CURRENT_DRIVE_INFO	=	1fh
DOS_ENVIRONMENT_SIZE		=	21h
DOS_ENVIRONMENT_VARIABLE_LENGTH	=	22h
DOS_GET_ENVIRONMENT_VARIABLE	=	23h
DOS_SET_ENVIRONMENT_VARIABLE	=	24h
DOS_SET_VECTOR			=	25h
DOS_ENVIRONMENT_LENGTH		=	26h
DOS_GET_ENVIRONMENT		=	27h
DOS_GET_PROCESS_PATH		=	28h
DOS_GET_COMMAND_LINE		=	29h
DOS_GET_DATE			=	2ah
DOS_SET_DATE			=	2bh
DOS_GET_TIME			=	2ch
DOS_SET_TIME			=	2dh
DOS_SET_VERIFY_FLAG		=	2eh
DOS_RESET_ENVIRONMENT		=	2fh
DOS_GET_VERSION			=	30h
DOS_TERMINATE_AND_STAY_RESIDENT	=	31h
DOS_GET_DRIVE_INFO		=	32h
DOS_GET_SET_BREAK_FLAG		=	33h
DOS_GET_VECTOR			=	35h
DOS_GET_DRIVE_FREE_SPACE	=	36h
DOS_GET_SET_SWITCH_CHARACTER	=	37h
DOS_GET_SET_COUNTRY_INFORMATION	=	38h
DOS_CREATE_DIRECTORY		=	39h
DOS_DELETE_DIRECTORY		=	3ah
DOS_SET_CURRENT_DIRECTORY	=	3bh
DOS_CREATE_FILE			=	3ch
DOS_OPEN_FILE			=	3dh
DOS_CLOSE_FILE			=	3eh
DOS_READ_FILE			=	3fh
DOS_WRITE_FILE			=	40h
DOS_DELETE_FILE			=	41h
DOS_SET_FILE_POSITION		=	42h
DOS_GET_SET_FILE_ATTRIBUTES	=	43h
DOS_DEVICE_CONTROL		=	44h
DOS_DUPLICATE_HANDLE		=	45h
DOS_FORCE_DUPLICATE_HANDLE	=	46h
DOS_GET_CURRENT_DIRECTORY	=	47h
DOS_ALLOCATE_MEMORY_BLOCK	=	48h
DOS_FREE_MEMORY_BLOCK		=	49h
DOS_RESIZE_MEMORY_BLOCK		=	4ah
DOS_EXECUTE_PROCESS		=	4bh
DOS_EXIT_PROCESS		=	4ch
DOS_GET_CHILD_RETURNCODE	=	4dh
DOS_FIND_FIRST_FILE		=	4eh
DOS_FIND_NEXT_FILE		=	4fh
DOS_GET_VERIFY_FLAG		=	54h
DOS_RENAME_FILE			=	56h
DOS_GET_SET_FILE_TIME_STAMP	=	57h
DOS_CREATE_TEMPORARY_FILE	=	5ah
DOS_CREATE_NEW_FILE		=	5bh
DOS_LOCK_UNLOCK_FILE_REGION	=	5ch
DOS_GET_ACTUAL_FILENAME		=	60h
DOS_CREATE_UNIQUE_FILE		=	61h
DOS_GET_PID			=	62h
DOS_ELAPSED_PERIODIC_TICKS	=	63h
DOS_SOUND			=	64h
DOS_EXTENDED_COUNTRY_INFO	=	65h
DOS_GET_SET_CODE_PAGE		=	66h
DOS_ELAPSED_TIMER_TICKS		=	67h
DOS_COMMIT_FILE			=	68h
;
; ZDOS IOCTL functions
;
IOCTL_GET_DEVICE_INFO		=	00h
IOCTL_SET_DEVICE_INFO		=	01h
IOCTL_READ_CHARACTER_DEVICE	=	02h
IOCTL_WRITE_CHARACTER_DEVICE	=	03h
IOCTL_READ_BLOCK_DEVICE		=	04h
IOCTL_WRITE_BLOCK_DEVICE	=	05h
IOCTL_DEVICE_INPUT_STATUS	=	06h
IOCTL_DEVICE_OUTPUT_STATUS	=	07h
IOCTL_BLOCK_DEVICE_REMOVABLE	=	08h
IOCTL_BLOCK_DEVICE_REMOTE	=	09h
IOCTL_HANDLE_REMOTE		=	0ah
IOCTL_SET_SHARING_RETRY_COUNT	=	0bh
IOCTL_GENERIC_CHARACTER_IO	=	0ch
IOCTL_GENERIC_BLOCK_IO		=	0dh
IOCTL_GET_LOGICAL_DRIVE_MAPPING	=	0eh
IOCTL_SET_LOGICAL_DRIVE_MAPPING	=	0fh
IOCTL_READ_TRACK		=	10h
IOCTL_WRITE_TRACK		=	11h
IOCTL_VERIFY_TRACK		=	12h
IOCTL_FORMAT_TRACK		=	13h
;
; ZDOS local and global IPC function numbers (INT 22h, INT 23h)
;
IPC_CREATE_MUTEX		=	00h
IPC_OPEN_MUTEX			=	01h
IPC_CLOSE_MUTEX			=	02h
IPC_WAIT_MUTEX			=	03h
IPC_WAIT_MUTEX_TIME_OUT		=	04h
IPC_SIGNAL_MUTEX		=	05h
IPC_CREATE_SEMAPHORE		=	06h
IPC_OPEN_SEMAPHORE		=	07h
IPC_CLOSE_SEMAPHORE		=	08h
IPC_WAIT_SEMAPHORE		=	09h
IPC_WAIT_SEMAPHORE_TIME_OUT	=	0ah
IPC_SIGNAL_SEMAPHORE		=	0bh
IPC_CREATE_EVENT		=	0ch
IPC_OPEN_EVENT			=	0dh
IPC_CLOSE_EVENT			=	0eh
IPC_WAIT_EVENT			=	0fh
IPC_WAIT_EVENT_TIME_OUT		=	10h
IPC_SET_EVENT			=	11h
IPC_CLEAR_EVENT			=	12h
IPC_CREATE_PIPE			=	13h
IPC_OPEN_PIPE			=	14h
IPC_CLOSE_PIPE			=	15h
IPC_READ_PIPE			=	16h
IPC_READ_PIPE_TIME_OUT		=	17h
IPC_WRITE_PIPE			=	18h
IPC_WRITE_PIPE_TIME_OUT		=	19h
;
; ZDOS thread function numbers (INT 24h)
;
THREAD_CREATE			=	00h
THREAD_DELETE			=	01h
THREAD_ID			=	02h
THREAD_SLEEP			=	03h
THREAD_WAKE_UP			=	04h
THREAD_DELAY_TICKS		=	05h
THREAD_DELAY_MICRO_SECONDS	=	06h
THREAD_DELAY_TIME		=	07h
THREAD_GET_PRIORITY		=	08h
THREAD_SET_PRIORITY		=	09h
THREAD_CLONE			=	0ah
THREAD_WAIT			=	0bh
;
; ZDOS trace function numbers (INT 27h)
;
TRACE_OPEN_SESSION		=	00h
TRACE_CLOSE_SESSION		=	01h
TRACE_SINGLE_STEP_CLIENT	=	02h
TRACE_RUN_CLIENT		=	03h
TRACE_SET_BREAKPOINTS		=	04h
TRACE_CLEAR_BREAKPOINTS		=	05h
TRACE_COPY_FROM_CLIENT		=	06h
TRACE_COPY_TO_CLIENT		=	07h
TRACE_GET_CPU_CONTEXT		=	08h
TRACE_SET_CPU_CONTEXT		=	09h
TRACE_GET_FPU_CONTEXT		=	0ah
TRACE_SET_FPU_CONTEXT		=	0bh
TRACE_GET_DEBUG_CONTEXT		=	0ch
TRACE_SET_DEBUG_CONTEXT		=	0dh
;
; Data returned by DosGetCurrentDriveData() and DosGetDriveData()
;
STRUC		DRVDATA
SPC		DD	?				; Sectors per cluster
MediaID		DD	?				; Media ID byte
BPS		DD	?				; Bytes per sector
Clusters	DD	?				; Number of clusters
ENDS
;
; Data returned by DosGetCurrentDriveInfo() and DosGetDriveInfo() functions
;
STRUC		DRVINFO
Drive		DB	?				; Logical drive number
Unit		DB	?				; Block device unit number
Flags		DB	?				; Flags
CSS		DB	?				; Cluster Size Shift count
SPC		DB	?				; Sectors Per Cluster
NFAT		DB	?				; Number of FATs (only on FAT file systems)
MD		DB	?				; Media Descriptor
FSID		DB	?				; File System ID
BPS		DD	?				; Bytes Per Sector
MDE		DD	?				; Max Directory Entries (in root directory)
TC		DD	?				; Total Clusters
SPF		DD	?				; Sectors Per Fat (only on FAT file systems)
ClusterSize	DD	?				; Cluster size in bytes
FatSector	DD	?				; First sector of FAT area (on FAT file systems)
RootDirSector	DD	?				; First sector of root directory area (on FAT file systems)
DataSector	DD	?				; First sector of data area (on FAT file systems)
NextCluster	DD	?				; Where to start searching for next free cluster
FreeClusters	DD	?				; Number of free clusters
FileSystem	DB	8 DUP (?)			; File system string
ENDS
;
; Used in DosGetDate() and DosSetData()
;
STRUC		DATE
Year		DD	?
Month		DB	?
Day		DB	?
DayOfWeek	DB	?
		DB	?				; For alignment
ENDS
;
; Used in DosGetTime() and DosSetTime()
;
STRUC		TIME
Hours		DB	?
Minutes		DB	?
Seconds		DB	?
Hundredths	DB	?
ENDS
;
; Data returned by DosGetDriveFreeSpace()
;
STRUC		DRVSPACE
SPC		DD	?				; Sectors per cluster
Free		DD	?				; Number of free clusters
BPS		DD	?				; Bytes per sector
Total		DD	?				; Total number of clusters
ENDS
;
; Data returned by DosGetCountryInformation()
;
STRUC		COUNTRY
DateFormat	DW	?				; Date format
Currency	DB	5 DUP (?)			; Currency symbol string
Thousands	DB	2 DUP (?)			; Thousands separator string
Decimal		DB	2 DUP (?)			; Decimal separator string
DateSeparator	DB	2 DUP (?)			; Date separator string
TimeSeparator	DB	2 DUP (?)			; Time separator string
CurrencyFormat	DB	?				; Currency format bit field
Decimals	DB	?				; Number of digits after decimal in currency
TimeFormat	DB	?				; 12-hour or 24-hour format
DataSeparator	DB	2 DUP (?)			; Datalist separator
CaseMap		DD	?				; Address of case mapping routine
ENDS
