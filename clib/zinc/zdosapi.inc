IFDEF __ZDOSDRV__
KERNEL_BASE	=	0c0000000h
		;
		; Misc. kernel functions
		;
BiosPrintScreen	=	KERNEL_BASE + 4 * 05h
		;
		; Hooks
		;
TaskDeleteHook	=	KERNEL_BASE + 4 * 06h
TaskIdleHook	=	KERNEL_BASE + 4 * 07h
ResetHook	=	KERNEL_BASE + 4 * 08h
KeyboardHook	=	KERNEL_BASE + 4 * 09h
MicroSecondWait	=	KERNEL_BASE + 4 * 0ah
ElapsedTime	=	KERNEL_BASE + 4 * 0bh
ElapsedTicks	=	KERNEL_BASE + 4 * 0ch
		;
		; BIOS API vectors
		;
BiosVideo	=	KERNEL_BASE + 4 * 10h
BiosEquipment	=	KERNEL_BASE + 4 * 11h
BiosBaseMemory	=	KERNEL_BASE + 4 * 12h
BiosDisk	=	KERNEL_BASE + 4 * 13h
BiosCom		=	KERNEL_BASE + 4 * 14h
BiosMisc	=	KERNEL_BASE + 4 * 15h
BiosKeyboard	=	KERNEL_BASE + 4 * 16h
BiosPrinter	=	KERNEL_BASE + 4 * 17h
BiosRomBasic	=	KERNEL_BASE + 4 * 18h
BiosBootStrap	=	KERNEL_BASE + 4 * 19h
BiosTimer	=	KERNEL_BASE + 4 * 1ah
BiosBreak	=	KERNEL_BASE + 4 * 1bh
BiosTick	=	KERNEL_BASE + 4 * 1ch
		;
		; DOS API vectors
		;
DosException	=	KERNEL_BASE + 4 * 20h
DosApi		=	KERNEL_BASE + 4 * 21h
DosTerminate	=	KERNEL_BASE + 4 * 22h
DosControlBreak	=	KERNEL_BASE + 4 * 23h
DosCritical	=	KERNEL_BASE + 4 * 24h
DosDiskRead	=	KERNEL_BASE + 4 * 25h
DosDiskWrite	=	KERNEL_BASE + 4 * 26h
DosFileSystem	=	KERNEL_BASE + 4 * 27h
DosIdle		=	KERNEL_BASE + 4 * 28h
DosFastOutput	=	KERNEL_BASE + 4 * 29h
DosVideo	=	KERNEL_BASE + 4 * 2ah
DosKeyboard	=	KERNEL_BASE + 4 * 2bh
DosConsole	=	KERNEL_BASE + 4 * 2ch
DosPacketDriver	=	KERNEL_BASE + 4 * 2dh
DosCommand	=	KERNEL_BASE + 4 * 2eh
DosMultiplex	=	KERNEL_BASE + 4 * 2fh
DosSocketDriver	=	KERNEL_BASE + 4 * 30h
DosFrameBuffer	=	KERNEL_BASE + 4 * 31h
DosEOI		=	KERNEL_BASE + 4 * 32h
DosSetIrqMask	=	KERNEL_BASE + 4 * 33h
		;
		; Misc. BIOS vectors
		;
BiosSecondTick	=	KERNEL_BASE + 4 * 49h
BiosAlarm	=	KERNEL_BASE + 4 * 4ah
BiosFastTick	=	KERNEL_BASE + 4 * 4bh
		;
		; Frame buffer accelerator functions
		;
FillRectangle	=	KERNEL_BASE + 4 * 80h
CopyRectangle	=	KERNEL_BASE + 4 * 81h
DrawImage	=	KERNEL_BASE + 4 * 82h
CursorOn	=	KERNEL_BASE + 4 * 83h
CursorOff	=	KERNEL_BASE + 4 * 84h
CursorShape	=	KERNEL_BASE + 4 * 85h
CursorPosition	=	KERNEL_BASE + 4 * 86h
SetPalette	=	KERNEL_BASE + 4 * 87h
WaitEngine2D	=	KERNEL_BASE + 4 * 88h
MpegAccelerator	=	KERNEL_BASE + 4 * 89h
		;
		; Memory functions for use by drivers
		;
AllocateBlock	=	KERNEL_BASE + 4 * 0a0h
AllocateBlocks	=	KERNEL_BASE + 4 * 0a1h
FreeBlock	=	KERNEL_BASE + 4 * 0a2h
ReallocateBlock	=	KERNEL_BASE + 4 * 0a3h
AllocatePages	=	KERNEL_BASE + 4 * 0a4h
FreePages	=	KERNEL_BASE + 4 * 0a5h
ReallocatePages	=	KERNEL_BASE + 4 * 0a6h
ValidateBlock	=	KERNEL_BASE + 4 * 0a7h
AllocPciBlock	=	KERNEL_BASE + 4 * 0a8h
FreePciBlock	=	KERNEL_BASE + 4 * 0a9h
PhysicalAddress	=	KERNEL_BASE + 4 * 0aah
CopyBytes	=	KERNEL_BASE + 4 * 0abh
CopyWords	=	KERNEL_BASE + 4 * 0ach
		;
		; Misc. system functions
		;
HookIsaPorts	=	KERNEL_BASE + 4 * 0b0h
UnhookIsaPorts	=	KERNEL_BASE + 4 * 0b1h
HookPciPorts	=	KERNEL_BASE + 4 * 0b2h
UnhookPciPorts	=	KERNEL_BASE + 4 * 0b3h
GetVector	=	KERNEL_BASE + 4 * 0b4h
SetVector	=	KERNEL_BASE + 4 * 0b5h
GetUserVector	=	KERNEL_BASE + 4 * 0b6h
SetUserVector	=	KERNEL_BASE + 4 * 0b7h
GetIvtVector	=	KERNEL_BASE + 4 * 0b8h
SetIvtVector	=	KERNEL_BASE + 4 * 0b9h
AllocV86FarTrap	=	KERNEL_BASE + 4 * 0bah
AllocV86IntTrap	=	KERNEL_BASE + 4 * 0bbh
FreeV86Trap	=	KERNEL_BASE + 4 * 0bch
AllocUserTrap	=	KERNEL_BASE + 4 * 0bdh
FreeUserTrap	=	KERNEL_BASE + 4 * 0beh
TrapPageFault	=	KERNEL_BASE + 4 * 0bfh
		;
		; Driver support functions
		;
DmaAllocBuffer	=	KERNEL_BASE + 4 * 0c0h
DmaFreeBuffer	=	KERNEL_BASE + 4 * 0c1h
DmaLockBuffer	=	KERNEL_BASE + 4 * 0c2h
DmaOpenChannel	=	KERNEL_BASE + 4 * 0c3h
DmaCloseChannel	=	KERNEL_BASE + 4 * 0c4h
DmaStart	=	KERNEL_BASE + 4 * 0c5h
DmaFinish	=	KERNEL_BASE + 4 * 0c6h
DeviceMap	=	KERNEL_BASE + 4 * 0c7h
DeviceUnmap	=	KERNEL_BASE + 4 * 0c8h
AllocateIrq	=	KERNEL_BASE + 4 * 0c9h
FreeIrq		=	KERNEL_BASE + 4 * 0cah
ShareIrq	=	KERNEL_BASE + 4 * 0cbh
LockDevice	=	KERNEL_BASE + 4 * 0cch
UnlockDevice	=	KERNEL_BASE + 4 * 0cdh
ConsoleMessage	=	KERNEL_BASE + 4 * 0ceh
ConsolePrint	=	KERNEL_BASE + 4 * 0cfh
		;
		; IPC functions
		;
MutexOpen	=	KERNEL_BASE + 4 * 0d0h
MutexClose	=	KERNEL_BASE + 4 * 0d1h
MutexLock	=	KERNEL_BASE + 4 * 0d2h
MutexLockTO	=	KERNEL_BASE + 4 * 0d3h
MutexUnlock	=	KERNEL_BASE + 4 * 0d4h
SemaphoreOpen	=	KERNEL_BASE + 4 * 0d5h
SemaphoreClose	=	KERNEL_BASE + 4 * 0d6h
SemaphoreLock	=	KERNEL_BASE + 4 * 0d7h
SemaphoreLockTO	=	KERNEL_BASE + 4 * 0d8h
SemaphoreUnlock	=	KERNEL_BASE + 4 * 0d9h
EventOpen	=	KERNEL_BASE + 4 * 0dah
EventClose	=	KERNEL_BASE + 4 * 0dbh
EventSet	=	KERNEL_BASE + 4 * 0dch
EventClear	=	KERNEL_BASE + 4 * 0ddh
EventWait	=	KERNEL_BASE + 4 * 0deh
EventWaitTO	=	KERNEL_BASE + 4 * 0dfh
PipeOpen	=	KERNEL_BASE + 4 * 0e0h
PipeClose	=	KERNEL_BASE + 4 * 0e1h
PipeRead	=	KERNEL_BASE + 4 * 0e2h
PipeReadTO	=	KERNEL_BASE + 4 * 0e3h
PipeWrite	=	KERNEL_BASE + 4 * 0e4h
PipeWriteTO	=	KERNEL_BASE + 4 * 0e5h
LockCpu		=	KERNEL_BASE + 4 * 0e6h
UnlockCpu	=	KERNEL_BASE + 4 * 0e7h
		;
		; Thread support functions
		;
ThreadCreate	=	KERNEL_BASE + 4 * 0f0h
ThreadDelete	=	KERNEL_BASE + 4 * 0f1h
ThreadID	=	KERNEL_BASE + 4 * 0f2h
ThreadSleep	=	KERNEL_BASE + 4 * 0f3h
ThreadWakeUp	=	KERNEL_BASE + 4 * 0f4h
ThreadDelayTick	=	KERNEL_BASE + 4 * 0f5h
ThreadDelayMS	=	KERNEL_BASE + 4 * 0f6h
ThreadDelayTime	=	KERNEL_BASE + 4 * 0f7h
ThreadGetPrio	=	KERNEL_BASE + 4 * 0f8h
ThreadSetPrio	=	KERNEL_BASE + 4 * 0f9h
ThreadClone	=	KERNEL_BASE + 4 * 0fah
ThreadWait	=	KERNEL_BASE + 4 * 0fbh
ELSE
		;
		; BIOS APIs
		;
BIOS_VIDEO	=	10h
BIOS_EQUIPMENT	=	11h
BIOS_BASE_MEM	=	12h
BIOS_DISK	=	13h
BIOS_COM	=	14h
BIOS_MISC	=	15h
BIOS_KEYBOARD	=	16h
BIOS_PRINTER	=	17h
BIOS_ROM_BASIC	=	18h
BIOS_BOOT_STRAP	=	19h
BIOS_TIMER	=	1ah
BIOS_PCI	=	1ah
		;
		; DOS APIs
		;
DOS		=	21h
LOCAL_IPC	=	22h
GLOBAL_IPC	=	23h
THREAD		=	24h
ABS_DISK_READ	=	25h
ABS_DISK_WRITE	=	26h
TRACE		=	27h
IDLE		=	28h
FAST_OUTPUT	=	29h
PKTDRV_CAPTURE	=	2dh
COMMAND		=	2eh
SOCKET		=	30h
FRAME_BUFFER	=	31h
ENDIF
