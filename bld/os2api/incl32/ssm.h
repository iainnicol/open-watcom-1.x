/*
    Multimedia Extensions Sync Stream Manager include file.
*/

#ifndef __SSM_H__
#define __SSM_H__

#define MAX_SPI_NAME  9

#define RC ULONG

#define NET_ACTIVE_MASK 0x00000FFF
#define NET_RUNNING 0x00000000
#define NET_PAUSED  0x00000001
#define NET_STOPPED 0x00000002
#define NET_PAUSE_PENDING 0x00000004
#define NET_FLUSH_PENDING 0x00000010
#define NET_DISCARD_PENDING 0x00000020
#define NET_CLOSE_PENDING 0x00000040
#define NET_SEEK_PENDING 0x00000040
#define NET_OPEN 0x00001000
#define NET_ASSEMBLED 0x00004000
#define STREAM_ACTIVE 0x00000010
#define STREAM_NOT_ACTIVE 0x00000020
#define SPI_RESOURCE 1
#define SH_DLL_TYPE 0
#define SH_PDD_TYPE 1
#define SPCBSIZE 72

#define SPI_SEEK_ABSOLUTE 0x0000
#define SPI_SEEK_RELATIVE 0x0001
#define SPI_SEEK_FROMEND 0x0002
#define SPI_SEEK_SLAVES 0x0010
#define SPI_SEEK_MMTIME 0x0000
#define SPI_SEEK_BYTES 0x0100
#define SPI_SEEK_IFRAME 0x1000
#define VALIDSEEKFLAGS  (SPI_SEEK_RELATIVE|SPI_SEEK_ABSOLUTE|SPI_SEEK_FROMEND | \
   SPI_SEEK_MMTIME|SPI_SEEK_SLAVES|SPI_SEEK_IFRAME|SPI_SEEK_BYTES)

#define SPI_START_STREAM  0
#define SPI_START_SLAVES  1
#define SPI_START_PREROLL 2
#define VALIDSTARTFLAGS (SPI_START_STREAM|SPI_START_SLAVES|SPI_START_PREROLL)

#define SPI_STOP_STREAM  0
#define SPI_STOP_SLAVES  1
#define SPI_STOP_FLUSH   2
#define SPI_STOP_DISCARD 4
#define SPI_STOP_PAUSE (SPI_STOP_STREAM)
#define VALIDSTOPFLAGS (SPI_STOP_STREAM|SPI_STOP_SLAVES|SPI_STOP_FLUSH|SPI_STOP_DISCARD)

#define SPI_INSTALL_PROTOCOL 0
#define SPI_DEINSTALL_PROTOCOL 1
#define VALIDINSTALLFLAGS (SPI_INSTALL_PROTOCOL|SPI_DEINSTALL_PROTOCOL)

#define SMH_REGISTER 0

#define REGISTER_TGT_HNDLR 1
#define REGISTER_SRC_HNDLR 2
#define REGISTER_NONSTREAMING 4
#define VALIDREGISTERFLAGS (REGISTER_TGT_HNDLR|REGISTER_SRC_HNDLR|REGISTER_NONSTREAMING)

#define BUF_GETEMPTY 0x00000001
#define BUF_RETURNFULL 0x00000002
#define BUF_GETFULL 0x00000004
#define BUF_RETURNEMPTY 0x00000008
#define BUF_GIVEBUF 0x00000010
#define BUF_EOS 0x00000100
#define BUF_RECORDS 0x00004000
#define BUF_LASTRECORD 0x00008000
#define BUF_LINEAR 0x00010000
#define BUF_PHYSICAL 0x00020000
#define BUF_RESERVED 0x00040000
#define BUF_GDT 0x00080000
#define BUF_EXTENDED 0x80000000
#define BUF_EXTENDEDPTR 0x40000000

#define VALIDSOURCEFLAGS (BUF_RETURNFULL|BUF_GETEMPTY|BUF_EOS|BUF_LASTRECORD|BUF_PHYSICAL|BUF_LINEAR|BUF_GDT|BUF_RECORDS|BUF_GIVEBUF|BUF_EXTENDED|BUF_EXTENDEDPTR)
#define VALIDTARGETFLAGS (BUF_RETURNEMPTY|BUF_GETFULL|BUF_PHYSICAL|BUF_LINEAR|BUF_GDT|BUF_EOS|BUF_EXTENDED|BUF_EXTENDEDPTR)

#define SMH_DEREGISTER 1
#define SMH_REPORTEVENT 2
#define SMH_NOTIFY 3
#define SMH_LOCKMEM 4

#define SSM_LOCKMEM 0
#define SSM_UNLOCKMEM 1
#define SSM_CONTIGLOCK 2
#define SSM_LOCKMEM_RESERVED1 0x0100
#define SSM_LOCKMEM_RESERVED2 0x0200

#define SHC_ASSOCIATE 0
#define SHC_CLOSE 1
#define SHC_CREATE 2
#define SHC_DESTROY 3
#define SHC_START 4
#define SHC_STOP 5
#define SHC_SEEK 6
#define SHC_ENABLE_EVENT 7
#define SHC_DISABLE_EVENT 8
#define SHC_ENABLE_SYNC 9
#define SHC_DISABLE_SYNC 10
#define SHC_GET_TIME 11
#define SHC_GET_PROTOCOL 12
#define SHC_INSTALL_PROTOCOL 13
#define SHC_ENUMERATE_PROTOCOLS 14
#define SHC_NEGOTIATE_RESULT 15
#define SHC_SENDMSG 16

#define FLUSH_START 1

#define SYNC_MASTER 0
#define SYNC_SLAVE 1

#define SPCB_MAX_BUF_SIZE (1024L*1024L)
#define VALIDDATAFLAGS (SPCBDATA_CUETIME|SPCBDATA_CUEDATA|SPCBDATA_YIELDTIME|SPCBDATA_NOSEEK)
#define SPCBDATA_CUETIME 0x0002
#define SPCBDATA_CUEDATA 0x0004
#define SPCBDATA_SEEK 0x0000
#define SPCBDATA_NOSEEK 0x0008
#define SPCBDATA_YIELDTIME 0x0010
#define VALIDBUFFLAGS (SPCBBUF_USERPROVIDED|SPCBBUF_FIXEDBUF|SPCBBUF_NONCONTIGUOUS| \
   SPCBBUF_INTERLEAVED|SPCBBUF_16MEG|SPCBBUF_FIXEDBLOCK|SPCBBUF_MAXSIZE)
#define SPCBBUF_USERPROVIDED 0x0001
#define SPCBBUF_FIXEDBUF 0x0002
#define SPCBBUF_NONCONTIGUOUS 0x0004
#define SPCBBUF_INTERLEAVED 0x0008
#define SPCBBUF_MAXSIZE 0x0010
#define SPCBBUF_16MEG 0x0020
#define SPCBBUF_FIXEDBLOCK  0x0040
#define VALIDHANDFLAGS (SPCBHAND_GENSYNC|SPCBHAND_RCVSYNC|SPCBHAND_TIMER| \
     SPCBHAND_NONSTREAM|SPCBHAND_GENTIME|SPCBHAND_NOPREROLL|SPCBHAND_NOSYNC|SPCBHAND_PHYS_SEEK)
#define SPCBHAND_GENSYNC 0x0001
#define SPCBHAND_RCVSYNC 0x0002
#define SPCBHAND_TIMER 0x0004
#define SPCBHAND_NONSTREAM 0x0008
#define SPCBHAND_GENTIME 0x0010
#define SPCBHAND_NOPREROLL 0x0020
#define SPCBHAND_NOSYNC 0x0040
#define SPCBHAND_PHYS_SEEK 0x0080

#pragma pack(4)

typedef ULONG    HSTREAM;
typedef HSTREAM  FAR *PHSTREAM;
typedef ULONG    HNETWORK;
typedef HNETWORK FAR *PHNETWORK;
typedef ULONG    HEVENT;
typedef HEVENT   FAR *PHEVENT;
typedef ULONG    HID;

typedef struct _LOCKH {
    BYTE lock[16];
} LOCKH, FAR *PLOCKH;

typedef struct _SLAVE {
    HSTREAM hstreamSlave;
    MMTIME  mmtimeStart;
} SLAVE, *PSLAVE;

typedef struct _MASTER {
    HSTREAM hstreamMaster;
} MASTER, FAR *PMASTER;

#ifndef  _SPCBKEY_DEFINED

#define  _SPCBKEY_DEFINED
typedef struct _SPCBKEY {
    ULONG ulDataType;
    ULONG ulDataSubType;
    ULONG ulIntKey;
} SPCBKEY, FAR *PSPCBKEY;

#endif

typedef struct _SPCB {
    ULONG   ulSPCBLen;
    SPCBKEY spcbkey;
    ULONG   ulDataFlags;
    ULONG   ulNumRec;
    ULONG   ulBlockSize;
    ULONG   ulBufSize;
    ULONG   ulMinBuf;
    ULONG   ulMaxBuf;
    ULONG   ulSrcStart;
    ULONG   ulTgtStart;
    ULONG   ulBufFlags;
    ULONG   ulHandFlags;
    MMTIME  mmtimeTolerance;
    MMTIME  mmtimeSync;
    ULONG   ulBytesPerUnit;
    MMTIME  mmtimePerUnit;
} SPCB, FAR *PSPCB;

#pragma pack(1)

typedef struct _HAND {
    SZ szHandlerClass[MAX_SPI_NAME];
    SZ szHandlerName[MAX_SPI_NAME];
} HAND, FAR *PHAND;

typedef struct _DCB {
    ULONG ulDCBLen;
    SZ    szDevName[MAX_SPI_NAME];
} DCB, FAR *PDCB;

typedef struct E_DCB {
    ULONG ulDCBLen;
    SZ    szDevName[MAX_SPI_NAME];
    ULONG ulSysFileNum;
} E_DCB, DCB_AUDIOSH;

typedef E_DCB FAR *PE_DCB;
typedef E_DCB FAR *PDCB_AUDIOSH;

typedef struct _VSD_DCB {
    ULONG ulDCBLen;
    SZ    szDevName[MAX_SPI_NAME];
    ULONG ulSysFileNum;
    ULONG hvsd;
    PFN   pfnvsdEntryPoint;
    ULONG ulReserved1;
    ULONG ulReserved2;
} VSD_DCB, *PVSD_DCB;

#pragma pack()

#include <evcb.h>
#include <acb.h>

typedef ULONG (APIENTRY EVFN)(PEVCB);
typedef EVFN *PEVFN;
typedef ULONG (APIENTRY SHCFN)(PVOID);
typedef SHCFN *PSHCFN;
typedef ULONG (APIENTRY SMHFN)(PVOID);
typedef SMHFN *PSMHFN;

typedef struct _MSG_COMMON {
    ULONG ulMsgLen;
} MSG_COMMON;

typedef struct _SMH_COMMON {
    ULONG ulFunction;
    HID   hid;
} SMH_COMMON, FAR *PSMH_COMMON;

typedef struct _PARM_REG {
    ULONG   ulFunction;
    PSZ     pszSHName;
    HID FAR *phidSrc;
    HID FAR *phidTgt;
    PSHCFN  pshcfnEntry;
    ULONG   ulFlags;
    ULONG   ulMaxNumStreams;
    ULONG   ulMaxNumEvents;
} PARM_REG, FAR *PPARM_REG;

typedef struct _PARM_DEREG {
    ULONG ulFunction;
    PSZ   pszSHName;
} PARM_DEREG, FAR *PPARM_DEREG;

typedef struct _PARM_EVENT {
    ULONG  ulFunction;
    HID    hid;
    HEVENT hevent;
    PEVCB  pevcbEvent;
} PARM_EVENT, FAR *PPARM_EVENT;

typedef struct _PARM_NOTIFY {
    ULONG   ulFunction;
    HID     hid;
    HSTREAM hstream;
    ULONG   ulFlags;
    ULONG   ulGetNumEntries;
    ULONG   ulRetNumEntries;
    PVOID   pGetBufTab;
    PVOID   pRetBufTab;
} PARM_NOTIFY, FAR *PPARM_NOTIFY;

typedef struct _SRCBUFTAB {
    PVOID  pBuffer;
    PVOID  pRecord;
    ULONG  ulLength;
    ULONG  ulMessageParm;
    MMTIME mmtimeOffset;
} SRCBUFTAB, FAR *PSRCBUFTAB;

typedef struct _TGTBUFTAB {
    PVOID  pBuffer;
    ULONG  ulBufId;
    ULONG  ulLength;
    ULONG  ulMessageParm;
    MMTIME mmtimeOffset;
} TGTBUFTAB, FAR *PTGTBUFTAB;

typedef struct _PARM_ENOTIFY {
    ULONG   ulFunction;
    HID     hid;
    HSTREAM hstream;
    ULONG   ulFlags;
    ULONG   ulGetNumEntries;
    ULONG   ulRetNumEntries;
    PVOID   pGetBufTab;
    PVOID   pRetBufTab;
    ULONG   ulParm1;
    ULONG   ulParm2;
} PARM_ENOTIFY, FAR *PPARM_ENOTIFY;

typedef struct _ESRCBUFTAB {
    PVOID  pBuffer;
    PVOID  pRecord;
    ULONG  ulLength;
    ULONG  ulMessageParm;
    MMTIME mmtimeOffset;
    ULONG  ulParm1;
    ULONG  ulParm2;
} ESRCBUFTAB, FAR *PESRCBUFTAB;

typedef struct _ETGTBUFTAB {
    PVOID  pBuffer;
    ULONG  ulBufId;
    ULONG  ulLength;
    ULONG  ulMessageParm;
    MMTIME mmtimeOffset;
    ULONG  ulParm1;
    ULONG  ulParm2;
} ETGTBUFTAB, FAR *PETGTBUFTAB;

typedef struct _EPSRCBUFTAB {
    PVOID  pBuffer;
    PVOID  pRecord;
    ULONG  ulLength;
    ULONG  ulMessageParm;
    MMTIME mmtimeOffset;
    ULONG  ulParm1;
    ULONG  ulParm2;
    PVOID  pProcessLin;
} EPSRCBUFTAB, FAR *PEPSRCBUFTAB;

typedef struct _EPTGTBUFTAB {
    PVOID  pBuffer;
    ULONG  ulBufId;
    ULONG  ulLength;
    ULONG  ulMessageParm;
    MMTIME mmtimeOffset;
    ULONG  ulParm1;
    ULONG  ulParm2;
    PVOID  pProcessLin;
} EPTGTBUFTAB, FAR *PEPTGTBUFTAB;

typedef struct _PARM_LOCKM {
    ULONG  ulFunction;
    PVOID  pBuffer;
    ULONG  ulBufSize;
    PLOCKH plockh;
    ULONG  ulFlags;
} PARM_LOCKM, FAR *PPARM_LOCKM;

typedef struct _SHC_COMMON {
    ULONG ulFunction;
    HID   hid;
} SHC_COMMON, FAR *PSHC_COMMON;

typedef struct _PARM_ASSOC {
    ULONG   ulFunction;
    HID     hid;
    HSTREAM hstream;
    PACB    pacb;
} PARM_ASSOC, FAR *PPARM_ASSOC;

typedef struct _PARM_CLOSE {
    ULONG ulFunction;
    HID   hid;
} PARM_CLOSE, FAR *PPARM_CLOSE;

typedef struct _PARM_CREATE {
    ULONG   ulFunction;
    HID     hid;
    HSTREAM hstream;
    SPCBKEY spcbkey;
    PSPCB   pspcb;
    HSTREAM hstreamBuf;
    PDCB    pdcb;
} PARM_CREATE, FAR *PPARM_CREATE;

typedef struct _PARM_DESTROY {
    ULONG   ulFunction;
    HID     hid;
    HSTREAM hstream;
} PARM_DESTROY, FAR *PPARM_DESTROY;

typedef struct _PARM_START {
    ULONG   ulFunction;
    HID     hid;
    HSTREAM hstream;
    ULONG   ulFlags;
} PARM_START, FAR *PPARM_START;

typedef struct _PARM_STOP {
    ULONG   ulFunction;
    HID     hid;
    HSTREAM hstream;
    ULONG   ulFlags;
} PARM_STOP, FAR *PPARM_STOP;

typedef struct _PARM_SEEK {
    ULONG   ulFunction;
    HID     hid;
    HSTREAM hstream;
    ULONG   ulFlags;
    LONG    lSeekPoint;
} PARM_SEEK, FAR *PPARM_SEEK;

typedef struct _PARM_ENEVENT {
    ULONG  ulFunction;
    HID    hid;
    HEVENT hevent;
    PEVCB  pevcbUser;
} PARM_ENEVENT, FAR *PPARM_ENEVENT;

typedef struct _PARM_DISEVENT {
    ULONG   ulFunction;
    HID     hid;
    HSTREAM hstream;
    HEVENT  hevent;
} PARM_DISEVENT, FAR *PPARM_DISEVENT;

typedef struct _PARM_ENSYNC {
    ULONG   ulFunction;
    HID     hid;
    HSTREAM hstream;
    ULONG   ulFlags;
    MMTIME  mmtimeSync;
    PSYNC_EVCB pevcbSyncPulse;
    ULONG   ulSyncPulseSem;
} PARM_ENSYNC, FAR *PPARM_ENSYNC;

typedef struct _PARM_DISSYNC {
    ULONG   ulFunction;
    HID     hid;
    HSTREAM hstream;
} PARM_DISSYNC, FAR *PPARM_DISSYNC;

typedef struct _PARM_GTIME {
    ULONG   ulFunction;
    HID     hid;
    HSTREAM hstream;
    MMTIME  mmtimeCurrent;
} PARM_GTIME, FAR *PPARM_GTIME;

typedef struct _PARM_GPROT {
    ULONG   ulFunction;
    HID     hid;
    SPCBKEY spcbkey;
    PSPCB   pspcb;
} PARM_GPROT, FAR *PPARM_GPROT;

typedef struct _PARM_INSTPROT {
    ULONG   ulFunction;
    HID     hid;
    SPCBKEY spcbkey;
    PSPCB   pspcb;
    ULONG   ulFlags;
} PARM_INSTPROT, FAR *PPARM_INSTPROT;

typedef struct _PARM_ENUMPROT {
    ULONG  ulFunction;
    HID    hid;
    PVOID  paSPCBKeys;
    PULONG pulNumSPCBKeys;
} PARM_ENUMPROT, FAR *PPARM_ENUMPROT;

typedef struct _PARM_NEGOTIATE {
    ULONG   ulFunction;
    HID     hid;
    HSTREAM hstream;
    PSPCB   pspcb;
    ULONG   ulErrorStatus;
} PARM_NEGOTIATE, FAR *PPARM_NEGOTIATE;

typedef struct _PARM_SNDMSG {
    ULONG   ulFunction;
    HID     hid;
    HSTREAM hstream;
    ULONG   ulMsgType;
    PVOID   pMsg;
} PARM_SNDMSG, FAR *PPARM_SNDMSG;

#pragma pack()

ULONG APIENTRY SMHEntryPoint(PVOID);
ULONG APIENTRY SpiAssociate(HSTREAM,HID,PACB);
ULONG APIENTRY SpiCreateStream(HID,HID,PSPCBKEY,PDCB,PDCB,PIMPL_EVCB,PEVFN,HSTREAM,PHSTREAM,PHEVENT);
ULONG APIENTRY SpiDestroyStream(HSTREAM);
ULONG APIENTRY SpiDetermineSyncMaster(PHSTREAM,PMASTER,ULONG);
ULONG APIENTRY SpiDisableEvent(HEVENT);
ULONG APIENTRY SpiDisableSync(HSTREAM);
ULONG APIENTRY SpiEnableEvent(PEVCB,PHEVENT);
ULONG APIENTRY SpiEnableSync(HSTREAM,PSLAVE,ULONG,MMTIME);
ULONG APIENTRY SpiEnumerateHandlers(PHAND,PULONG);
ULONG APIENTRY SpiEnumerateProtocols(HID,PVOID,PULONG);
ULONG APIENTRY SpiGetHandler(PSZ,HID*,HID*);
ULONG APIENTRY SpiGetProtocol(HID,PSPCBKEY,PSPCB);
ULONG APIENTRY SpiGetTime(HSTREAM,PMMTIME);
ULONG APIENTRY SpiInstallProtocol(HID,PSPCBKEY,PSPCB,ULONG);
ULONG APIENTRY SpiSendMsg(HSTREAM,HID,ULONG,PVOID);
ULONG APIENTRY SpiSeekStream(HSTREAM,ULONG,LONG);
ULONG APIENTRY SpiStartStream(HSTREAM,ULONG);
ULONG APIENTRY SpiStopStream(HSTREAM,ULONG);

#endif

