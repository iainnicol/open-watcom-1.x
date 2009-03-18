;
; Device driver commands
;
DEVICE_INITIALIZE	=	0
DEVICE_MEDIA_CHECK	=	1
DEVICE_GET_BPB		=	2
DEVICE_IOCTL_INPUT	=	3
DEVICE_INPUT		=	4
DEVICE_ND_INPUT		=	5
DEVICE_INPUT_STATUS	=	6
DEVICE_INPUT_FLUSH	=	7
DEVICE_OUTPUT		=	8
DEVICE_OUTPUT_VERIFY	=	9
DEVICE_OUTPUT_STATUS	=	10
DEVICE_OUTPUT_FLUSH	=	11
DEVICE_IOCTL_OUTPUT	=	12
DEVICE_OPEN		=	13
DEVICE_CLOSE		=	14
DEVICE_REMOVABLE	=	15
DEVICE_OUTPUT_BUSY	=	16
DEVICE_GENERIC_IOCTL	=	19
DEVICE_GET_LOGICAL	=	23
DEVICE_SET_LOGICAL	=	24
DEVICE_IOCTL_QUERY	=	25
;
; Device definition flags
;
ATTRIBUTE_STDIN		=	01h			; Standard input device
ATTRIBUTE_STDOUT	=	02h			; Standard output device
ATTRIBUTE_SECTOR32	=	02h			; Support 32-bit sector addresses
ATTRIBUTE_NULL		=	04h			; Standard NUL device
ATTRIBUTE_CLOCK		=	08h			; Standard CLOCK device
ATTRIBUTE_FAST_IO	=	10h			; Supports INT 29h fast I/O
ATTRIBUTE_GET_SET	=	40h			; Supports get/set logical device and generic IOCTL
ATTRIBUTE_QUERY		=	80h			; Supports IOCTL queries
ATTRIBUTE_OPEN		=	800h			; Supports open/close/removable media calls
ATTRIBUTE_TO_BUSY	=	2000h			; Supports output until busy
ATTRIBUTE_IOCTL		=	4000h			; Supports IOCTL read/write
ATTRIBUTE_CHAR		=	8000h			; Character mode device
ATTRIBUTE_FAT12		=	10000h			; Supports FAT12
ATTRIBUTE_FAT16		=	20000h			; Supports FAT16
ATTRIBUTE_FAT32		=	40000h			; Supports FAT32
ATTRIBUTE_FIXED_DRIVE	=	400000h			; Non removable block device
ATTRIBUTE_REMOTE_DRIVE	=	800000h			; Remote block device
;
; Device driver status codes
;
DEVICE_ERROR		=	8000h
DEVICE_BUSY		=	200h
DEVICE_DONE		=	100h
;
; Device error codes
;
ENUM DEVICE_ERROR_CODE	{
			DEVICE_WRITE_PROTECTED = DEVICE_ERROR
			DEVICE_UNKNOWN_UNIT
			DEVICE_NOT_READY
			DEVICE_UNKNOWN_COMMAND
			DEVICE_DATA_ERROR
			DEVICE_BAD_REQUEST_LENGTH
			DEVICE_SEEK_ERROR
			DEVICE_UNKNOWN_MEDIA_TYPE
			DEVICE_SECTOR_NOT_FOUND
			DEVICE_OUT_OF_PAPER
			DEVICE_WRITE_FAULT
			DEVICE_READ_FAULT
			DEVICE_GENERAL_FAILURE
			}
;
; File System Driver functions
;
ENUM FILE_FUNCTIONS	{
			FSD_CREATE_DIRECTORY		; Create directory
			FSD_DELETE_DIRECTORY		; Delete directory
			FSD_CREATE_FILE			; Create file
			FSD_OPEN_FILE			; Open file
			FSD_CLOSE_FILE			; Close file
			FSD_READ_FILE			; Read file
			FSD_WRITE_FILE			; Write file
			FSD_DELETE_FILE			; Delete file
			FSD_GET_FILE_ATTRIBUTES		; Get file attributes
			FSD_SET_FILE_ATTRIBUTES		; Set file attributes
			FSD_FIND_FIRST_FILE		; Find first file
			FSD_FIND_NEXT_FILE		; Find next file
			FSD_RENAME_FILE			; Rename file
			FSD_GET_FREE_SPACE		; Get logical drive free space
			}
;
; Interrupt controller equates
;
MASTER_PIC		=	20h
SLAVE_PIC		=	0a0h
EOI_COMMAND		=	20h
;
; Device driver header
;
STRUC		DEVICE
NextDevice	DD	?				; Pointer to next device in chain
Attribute	DD	?				; Device attribute flags
Interrupt	DD	?				; Pointer to interrupt routine
DeviceName	DB	8 DUP (?)			; Device name
ENDS
;
; Generic request header for commands 5,6,7,10,11,13,14,15,23 and 24.
;
STRUC		IO_REQUEST
Length		DB	?				; Request block length
Unit		DB	?				; Unit number if block I/O
Command		DB	?				; Device driver command
Result		DB	?				; Returned BYTE
Status		DD	?				; Device driver return status
ENDS
;
; Request header definition for INITIALIZE command (0)
;
STRUC		IO_INIT
Length		DB	?				; Request block length
Unit		DB	?				; Unit number if block I/O
Command		DB	?				; Device driver command
Units		DB	?				; Number of units supported by device driver
Status		DD	?				; Device driver return status
Break		DD	?				; Device driver break address
PointerBPB	DD	?				; Pointer to an array of BPBs for supported units
ENDS
;
; Request header definition for MEDIA_CHECK command (1)
;
STRUC		IO_MEDIA
Length		DB	?				; Request block length
Unit		DB	?				; Unit number if block I/O
Command		DB	?				; Device driver command
Media		DB	?				; Media status
Status		DD	?				; Device driver return status
Volume		DD	?				; Pointer to volume label
ENDS
;
; Request header definition for BUILD_BPB command (2)
;
STRUC		IO_BUILD
Length		DB	?				; Request block length
Unit		DB	?				; Unit number if block I/O
Command		DB	?				; Device driver command
Reserved	DB	?				; Reserved
Status		DD	?				; Device driver return status
PointerBPB	DD	?				; Pointer to BPB
ENDS
;
; Generic request header definition for commands 3,4,8,9,12 and 16.
;
STRUC		IO_TRANSFER
Length		DB	?				; Request block length
Unit		DB	?				; Unit number if block I/O
Command		DB	?				; Device driver command
Reserved	DB	?				; Reserved
Status		DD	?				; Device driver return status
Buffer		DD	?				; Pointer to buffer
Count		DD	?				; Transfer count
Sector		DD	?				; Start sector if block transfer
ENDS
;
; Generic request header definition for commands 19 and 25.
;
STRUC		IO_IOCTL
Length		DB	?				; Request block length
Unit		DB	?				; Unit number if block I/O
Command		DB	?				; Device driver command
Reserved	DB	?				; Reserved
Status		DD	?				; Device driver return status
Buffer		DD	?				; Pointer to buffer
Major		DB	?				; Major function number
Minor		DB	?				; Minor function number
		DB	2 DUP (?)			; For alignment
ENDS
;
; File System Driver (FSD) header
;
STRUC		FSD
NextDriver	DD	?				; Pointer to next file system driver
Dispatcher	DD	?				; Pointer to dispatcher
DriverName	DB	8 DUP (?)			; Driver name
ENDS
;
; Hardware Driver (HWD) header
;
STRUC		HWD
NextDriver	DD	?				; Pointer to next hardware driver
DriverName	DB	8 DUP (?)			; Driver name
ENDS
;
; Structure used for trapping I/O ports
;
STRUC		IOTRAP
Reserved	DD	3 DUP (?)			; For internal use
OutBYTE		DD	?				; Pointer to handler for 8-bit trapped I/O output
OutWORD		DD	?				; Pointer to handler for 16-bit trapped I/O output
OutDWORD	DD	?				; Pointer to handler for 32-bit trapped I/O output
InBYTE		DD	?				; Pointer to handler for 8-bit trapped I/O input
InWORD		DD	?				; Pointer to handler for 16-bit trapped I/O input
InDWORD		DD	?				; Pointer to handler for 32-bit trapped I/O input
ENDS
;
; Structure used for handling DMA buffers
;
STRUC		DMABUF
Linear		DD	?				; Linear address of buffer
Physical	DD	?				; Physical address of buffer
Size		DD	?				; Size of buffer
ENDS
;
; Exception/interrupt handler stack frame
;
STRUC		EXCEPTION
EDI		DD	?				; Offending task EDI
ESI		DD	?				; Offending task ESI
EBP		DD	?				; Offending task EBP
		DD	?				; Offending task ESP before PUSHAD
EBX		DD	?				; Offending task EBX
EDX		DD	?				; Offending task EDX
ECX		DD	?				; Offending task ECX
EAX		DD	?				; Offending task EAX
SavedES		DD	?				; Offending task ES (if 32-bit task)
SavedDS		DD	?				; Offending task DS (if 32-bit task)
Error		DW	?				; Error code or IRQ number
Exception	DW	?				; Exception number
EIP		DD	?				; Offending task EIP
CS		DD	?				; Offending task CS
EFLAGS		DD	?				; Offending task EFLAGS
ESP		DD	?				; Offending task ESP (if user or V86 task)
SS		DD	?				; Offending task SS (if user or V86 task)
ES		DD	?				; Offending task ES (if V86 task)
DS		DD	?				; Offending task DS (if V86 task)
FS		DD	?				; Offending task FS (if V86 task)
GS		DD	?				; Offending task GS (if V86 task)
ENDS
