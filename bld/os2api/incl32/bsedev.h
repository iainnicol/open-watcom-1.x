/*
    Description:  OS/2 Base Devices file for 32-bit development.
*/


#ifndef __BSEDEV_H__
#define __BSEDEV_H__

#define IOCTL_ASYNC           0x0001
#define IOCTL_SCR_AND_PTRDRAW 0x0003
#define IOCTL_KEYBOARD        0x0004
#define IOCTL_PRINTER         0x0005
#define IOCTL_LIGHTPEN        0x0006
#define IOCTL_POINTINGDEVICE  0x0007
#define IOCTL_DISK            0x0008
#define IOCTL_PHYSICALDISK    0x0009
#define IOCTL_MONITOR         0x000A
#define IOCTL_GENERAL         0x000B
#define IOCTL_POWER           0x000C
#define IOCTL_OEMHLP          0x0080
#define IOCTL_TESTCFG_SYS     0x0080
#define IOCTL_CDROMDISK       0x0080
#define IOCTL_CDROMAUDIO      0x0081
#define IOCTL_TOUCH_DEVDEP    0x0081
#define IOCTL_TOUCH_DEVINDEP  0x0081

#define ASYNC_SETBAUDRATE          0x0041
#define ASYNC_SETLINECTRL          0x0042
#define ASYNC_EXTSETBAUDRATE       0x0043
#define ASYNC_TRANSMITIMM          0x0044
#define ASYNC_SETBREAKOFF          0x0045
#define ASYNC_SETMODEMCTRL         0x0046
#define ASYNC_SETBREAKON           0x004B
#define ASYNC_STOPTRANSMIT         0x0047
#define ASYNC_STARTTRANSMIT        0x0048
#define ASYNC_SETDCBINFO           0x0053
#define ASYNC_SETENHANCEDMODEPARMS 0x0054
#define ASYNC_GETBAUDRATE          0x0061
#define ASYNC_GETLINECTRL          0x0062
#define ASYNC_EXTGETBAUDRATE       0X0063
#define ASYNC_GETCOMMSTATUS        0x0064
#define ASYNC_GETLINESTATUS        0x0065
#define ASYNC_GETMODEMOUTPUT       0x0066
#define ASYNC_GETMODEMINPUT        0x0067
#define ASYNC_GETINQUECOUNT        0x0068
#define ASYNC_GETOUTQUECOUNT       0x0069
#define ASYNC_GETCOMMERROR         0x006D
#define ASYNC_GETCOMMEVENT         0x0072
#define ASYNC_GETDCBINFO           0x0073
#define ASYNC_GETENHANCEDMODEPARMS 0x0074

#define DEV_FLUSHINPUT      0x0001
#define DEV_FLUSHOUTPUT     0x0002
#define DEV_SYSTEMNOTIFYPDD 0X0041
#define DEV_QUERYMONSUPPORT 0x0060

#endif

