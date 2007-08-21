;
; BIOS Video API function numbers
;
VIDEO_SET_MODE		=	00h			; Set Video Mode
VIDEO_SET_CURSOR_TYPE	=	01h			; Set Cursor Type
VIDEO_SET_CURSOR	=	02h			; Set Cursor Position
VIDEO_GET_CURSOR	=	03h			; Get Cursor Position
VIDEO_GET_LIGHT_PEN	=	04h			; Get Light Pen Position
VIDEO_SET_DISPLAY_PAGE	=	05h			; Set Display Page
VIDEO_SCROLL_UP		=	06h			; Scroll Window Up
VIDEO_SCROLL_DOWN	=	07h			; Scroll Window Down
VIDEO_READ_CHAR_ATTRIB	=	08h			; Read Character And Attribut At Cursor
VIDEO_WRITE_CHAR_ATTRIB	=	09h			; Write Character And Attribute At Cursor
VIDEO_WRITE_CHAR	=	0ah			; Write Character At Cursor
VIDEO_SET_BORDER	=	0bh			; Set Border, Palette Or Background
VIDEO_WRITE_PIXEL	=	0ch			; Write Graphics Pixel
VIDEO_READ_PIXEL	=	0dh			; Read Graphics Pixel
VIDEO_WRITE_TELETYPE	=	0eh			; Write Character In Teletype Mode
VIDEO_GET_MODE		=	0fh			; Get Video Mode
VIDEO_SUBFUNCTIONS	=	10h			; Misc. Video Subfunctions
;
; BIOS Video API misc. subfunction numbers
;
VIDEO_SET_PALETTE	=	VIDEO_SUBFUNCTIONS SHL 8; Set Palette Register
VIDEO_SET_OVERSCAN	=	VIDEO_SET_PALETTE + 1	; Set Overscan Register
VIDEO_SET_COLORS	=	VIDEO_SET_PALETTE + 2	; Set All Palette Registers And Overscan Register
VIDEO_CHANGE_BLINK_BIT	=	VIDEO_SET_PALETTE + 3	; Change Blinking Bit
VIDEO_GET_PALETTE	=	VIDEO_SET_PALETTE + 7	; Get Palette Register
VIDEO_GET_OVERSCAN	=	VIDEO_SET_PALETTE + 8	; Get Overscan Register
VIDEO_GET_COLORS	=	VIDEO_SET_PALETTE + 9	; Get All Palette Registers And Overscan Register
;
; BIOS Disk API function numbers
;
DISK_RESET		=	00h			; Reset Disk System function number
DISK_SYSTEM_STATUS	=	01h			; Get Disk System Status function number
DISK_READ_SECTOR	=	02h			; Read Sector function number
DISK_WRITE_SECTOR	=	03h			; Write Sector function number
DISK_VERIFY_SECTOR	=	04h			; Verify Sector function number
DISK_FORMAT_TRACK	=	05h			; Format Track function number
DISK_DRIVE_PARAMETERS	=	08h			; Get Drive Parameters function number
DISK_INITIALIZE		=	09h			; Initialize Fixed Disk Characteristics function number
DISK_READ_SECTOR_LONG	=	0ah			; Read Sector Long function number
DISK_WRITE_SECTOR_LONG	=	0bh			; Write Sector Long function number
DISK_SEEK		=	0ch			; Seek
DISK_ALTERNATE_RESET	=	0dh			; Reset Fixed Disk System function number
DISK_DRIVE_STATUS	=	10h			; Get Drive Status function number
DISK_RECALIBRATE_DRIVE	=	11h			; Recalibrate Drive function number
DISK_EMULATOR_PRESENT	=	12h			; Disk emulation installation check function number
DISK_EMULATOR_CONNECT	=	13h			; Disk emulation connect API for drive function
DISK_DIAGNOSTICS	=	14h			; Controller Internal Diagnostic function number
DISK_GET_DRIVE_TYPE	=	15h			; Get Disk Type function number
DISK_CHANGE_LINE_STATUS	=	16h			; Get Disk Change Line Status function number
DISK_GET_SET_DRIVE_TYPE	=	17h			; Get/Set Disk Type function number
DISK_SET_MEDIA_TYPE	=	18h			; Set Media Type For Format function number
DISK_EXTENSION_PRESENT	=	20h			; Extended Services Present
DISK_DEVICE_TYPE	=	21h			; Get Device Type
DISK_READ_SECTOR_LBA	=	22h			; Read Sector(s) Using LBA Translation
DISK_WRITE_SECTOR_LBA	=	23h			; Write Sector(s) Using LBA Translation
DISK_VERIFY_SECTOR_LBA	=	24h			; Verify Sector(s) Using LBA Translation
DISK_DEVICE_INFORMATION	=	25h			; Get Device Information
DISK_PACKET_COMMAND	=	26h			; Send ATAPI Packet Command
DISK_SEEK_LBA		=	27h			; Seek Using LBA
DISK_DEVICE_PARAMETERS	=	28h			; Get Device Parameters
DISK_DEVICE_RESET	=	29h			; Reset ATAPI Device
DISK_MEDIA_LOCK_STATUS	=	2ah			; Get Media Lock Status
DISK_LOCK_MEDIA		=	2bh			; Lock Media
DISK_UNLOCK_MEDIA	=	2ch			; Unlock Media
DISK_EJECT_MEDIA	=	2dh			; Eject Media
;
; BIOS Serial Communication API function numbers
;
UART_SETUP		=	00h			; Initialize Serial Port function number
UART_OUTPUT		=	01h			; Write Byte To Serial Port function number
UART_INPUT		=	02h			; Read Byte From Serial Port function nuber
UART_STATUS		=	03h			; Get Serial Port Status
UART_EXTENDED_SETUP	=	04h			; Extended Initialize Serial Port function number
UART_GET_SET_CONTROL	=	05h			; Extended Serial Port Control function number
UART_OPEN		=	06h			; Open Serial Port function number
UART_CLOSE		=	07h			; Close serial Port function number
UART_BUFFERED_OUTPUT	=	08h			; Send Buffer To Serial Port function number
UART_BUFFERED_INPUT	=	09h			; Receive Buffer From Serial Port function number
;
; BIOS Misc. API function numbers
;
MISC_MEDIA_EJECT	=	52h			; Removable media eject
MISC_DEVICE_OPEN	=	80h			; Open device
MISC_DEVICE_CLOSE	=	81h			; Close device
MISC_PROCESS_TERMINATE	=	82h			; Process termination
MISC_EVENT_WAIT		=	83h			; Event wait start/cancel request
MISC_SYSTEM_REQUEST	=	85h			; Process system request key
MISC_WAIT		=	86h			; Wait (sleep) for some micro seconds
MISC_EXTENDED_MEMSIZE	=	88h			; Return extended memory size in KB
MISC_DEVICE_BUSY	=	90h			; Device is busy
MISC_DEVICE_READY	=	91h			; Device is ready
MISC_SYSTEM_CONFIG	=	0c0h			; Return pointer to system configuration
MISC_MOUSE_SERVICES	=	0c2h			; Mouse services
MISC_CPU_STEPPING	=	0c9h			; Return CPU stepping information
MISC_ENHANCED_MEMSIZE	=	0e8h			; Return memory size
;
; BIOS Keyboard API function numbers
;
KEYBOARD_WAIT_KEY	=	00h			; Read Keyboard Input
KEYBOARD_STATUS		=	01h			; Return Keyboard Status
KEYBOARD_FLAGS		=	02h			; Return Keyboard Flags
KEYBOARD_RATE		=	03h			; Set Keyboard Typematic Rate And Delay
KEYBOARD_FLUSH		=	04h			; Flush Keyboard Buffer
KEYBOARD_PUT_KEY	=	05h			; Stuff Key Code Into Keyboard Buffer
KEYBOARD_CAPABILITIES	=	09h			; Return Keyboard Typematic Capabilities
KEYBOARD_WAIT_FULL_KEY	=	10h			; Read Enhanced Keyboard Input
KEYBOARD_FULL_STATUS	=	11h			; Return Enhanced Keyboard Status
KEYBOARD_FULL_FLAGS	=	12h			; Return Enhanced Keyboard Flags
;
; BIOS Printer API function numbers
;
PRINTER_OUTPUT		=	00h			; Send Character To Printer function number
PRINTER_INITIALIZE	=	01h			; Initialize Printer function number
PRINTER_STATUS		=	02h			; Get Printer Status function number
PRINTER_OPEN		=	03h			; Open Printer function number
PRINTER_CLOSE		=	04h			; Close Printer function number
;
; BIOS Timer API function numbers
;
TIMER_GET_TICK_COUNT	=	00h			; Get timer tick count
TIMER_SET_TICK_COUNT	=	01h			; Set timer tick count
TIMER_GET_CMOS_TIME	=	02h			; Get CMOS time
TIMER_SET_CMOS_TIME	=	03h			; Set CMOS time
TIMER_GET_CMOS_DATE	=	04h			; Get CMOS date
TIMER_SET_CMOS_DATE	=	05h			; Set CMOS date
TIMER_SET_CMOS_ALARM	=	06h			; Set CMOS alarm
TIMER_RESET_CMOS_ALARM	=	07h			; Reset CMOS alarm
;
; BIOS PCI API function numbers
;
PCI_SERVICES		=	0b1h			; PCI services function number
PCI_INSTALLATION_CHECK	=	01h			; Installation check
PCI_FIND_DEVICE		=	02h			; Find PCI device
PCI_FIND_CLASS		=	03h			; Find PCI class code
PCI_GENERATE_CYCLE	=	06h			; Generate PCI special cycle
PCI_READ_CONFIG_BYTE	=	08h			; Read PCI configuration byte
PCI_READ_CONFIG_WORD	=	09h			; Read PCI configuration word
PCI_READ_CONFIG_DWORD	=	0ah			; Read PCI configuration dword
PCI_WRITE_CONFIG_BYTE	=	0bh			; Read PCI configuration byte
PCI_WRITE_CONFIG_WORD	=	0ch			; Read PCI configuration word
PCI_WRITE_CONFIG_DWORD	=	0dh			; Read PCI configuration dword
PCI_GET_ROUTING_OPTIONS	=	0eh			; Get PCI interrupt routing options
PCI_CONNECT_INTERRUPT	=	0fh			; Connect PCI interrupt pin to interrupt line
;
; BIOS Mouse API function numbers
;
MOUSE_ENABLE_DISABLE	=	00h			; Enable or disble mouse
MOUSE_RESET		=	01h			; Reset mouse
MOUSE_SET_SAMPLE_RATE	=	02h			; Set mouse sample rate
MOUSE_SET_RESOLUTION	=	03h			; Set mouse resolution
MOUSE_GET_DEVICE_ID	=	04h			; Get mouse device ID
MOUSE_INITIALIZE	=	05h			; Initialize mouse
MOUSE_STATUS		=	06h			; Get mouse status or set mouse scaling factor
MOUSE_SET_HANDLER	=	07h			; Set mouse handler address
;
;  Cursor info structure
;
STRUC		CURSOR
Column		DB	?				; Current column position
Row		DB	?				; Current row position
StartLine	DB	?				; Cursor starting scan line
EndLine		DB	?				; Cursor ending scan line
ENDS
;
; Video mode structure
;
STRUC		VMODE
Mode		DB	?				; Current video mode
Columns		DB	?				; Number of video columns
Rows		DB	?				; Number of video rows
Page		DB	?				; Current video page
ENDS
;
; Disk parameters structure
;
STRUC		DISK
MaxSector	DB	?				; Maximum sector number
MaxHead		DB	?				; Maximum head number
MaxTrack	DW	?				; Maximum track number
DPT		DD	?				; Pointer to disk parameter table (only floppy drives)
ENDS
;
; Structure returned by extended disk parameters function
;
STRUC		EDPT
Length		DW	?				; Length of buffer
Information	DW	?				; Information flags
Cylinders	DD	?				; Number of physical cylinders
Heads		DD	?				; Number of physical heads
Sectors		DD	?				; Number of physical sectors/track
TotalSectors	DQ	?				; Number of total sectors
Bytes		DW	?				; Bytes/sector
Pointer		DD	?				; Pointer to DCB
ENDS
;
; Structure used by BiosCpuInformation() function
;
STRUC		CPU
Coprocessor	DB	?				; Coprocessor type
Family		DB	?				; CPU family
Stepping	DB	?				; CPU stepping number
		DB	?				; For alignment
Features	DD	?				; CPU features
ENDS
;
; Structure used by BiosGetTime() and BiosSetTime() functions
;
STRUC		TIME
Hour		DB	?				; Current hour in BCD format
Minute		DB	?				; Current minute in BCD format
Second		DB	?				; Current second in BCD format
Daylight	DB	?				; Daylight saving time flag (0 = standard, 1 = daylight)
ENDS
;
; Structure used by BiosGetDate() and BiosSetDate() functions
;
STRUC		DATE
Century		DB	?				; Current century in BCD format
Year		DB	?				; Current year in BCD format
Month		DB	?				; Current month in BCD format
Day		DB	?				; Current day in BCD format
ENDS
;
; Structure filled in by BiosPciInformation() function
;
STRUC		PCIDATA
Hardware	DW	?				; Hardware characteristics bits
Major		DB	?				; Major version number
Minor		DB	?				; Minor version number
LastBus		DD	?				; Last bus number
ID		DD	?				; The string 'PCI '
ENDS
;
; Structure filled in by BiosPciFindDevice() and BiosPicFindClass() functions
;
STRUC		PCIFIND
Bus		DB	?				; Bus number
Device		DB	?				; Device number
Function	DB	?				; Function number
		DB	?				; For alignment
ENDS
;
; Mouse packet
;
STRUC		MOUSE_PACKET
PositionZ	DW	?
PositionY	DW	?
PositionX	DW	?
Status		DW	?
ENDS
;
; Mouse status
;
STRUC		MOUSE_INFO
Status		DB	?				; Mouse status bits
Resolution	DB	?				; Mouse resolution
Rate		DB	?				; Mouse sample rate
		DB	?				; For alignment
ENDS
