/*
    Sync Stream Manager Event Control Block include file.
*/

#define EVENT_SYNC 1
#define EVENT_RESERVED 2
#define EVENT_IMPLICIT_TYPE 3
#define EVENT_SYNCOVERRUN 4
#define EVENT_CUE_TIME 5
#define EVENT_CUE_DATA 6
#define EVENT_DATAUNDERRUN 7
#define EVENT_DATAOVERRUN 8
#define EVENT_CUE_TIME_PAUSE 9
#define EVENT_STATUS_LEVEL 10

#define SYNCOVERRUN 1
#define SYNCPOLLING 2

#define EVENT_EOS 1
#define EVENT_ERROR 2
#define EVENT_STREAM_STOPPED 3
#define EVENT_SYNC_PREROLLED 4
#define EVENT_PLAYLISTMESSAGE 5
#define EVENT_PLAYLISTCUEPOINT 6
#define EVENT_QUEUE_OVERFLOW 7
#define EVENT_START 8

#define EVENT_SINGLE 0
#define EVENT_RECURRING 1
#define EVENT_DATAPTR 2

#define SH_TYPE 0x80000000

#pragma pack(4)

typedef struct _SYNC_EVCB {
    ULONG   ulType;
    ULONG   ulSubType;
    ULONG   ulSyncFlags;
    HSTREAM hstream;
    HID     hid;
    ULONG   ulStatus;
    MMTIME  mmtimeStart;
    MMTIME  mmtimeMaster;
    MMTIME  mmtimeSlave;
} SYNC_EVCB, FAR *PSYNC_EVCB;

typedef struct _IMPL_EVCB {
    ULONG   ulType;
    ULONG   ulSubType;
    ULONG   ulFlags;
    HSTREAM hstream;
    HID     hid;
    ULONG   ulStatus;
    ULONG   unused1;
    ULONG   unused2;
    ULONG   unused3;
} IMPL_EVCB, FAR *PIMPL_EVCB;

typedef struct _PLAYL_EVCB {
    ULONG   ulType;
    ULONG   ulSubType;
    ULONG   ulFlags;
    HSTREAM hstream;
    HID     hid;
    ULONG   ulStatus;
    ULONG   ulMessageParm;
    ULONG   unused1;
    ULONG   unused2;
} PLAYL_EVCB, FAR *PPLAYL_EVCB;

typedef struct _OVRU_EVCB {
    ULONG   ulType;
    ULONG   ulSubType;
    ULONG   ulFlags;
    HSTREAM hstream;
    HID     hid;
    ULONG   ulStatus;
    MMTIME  mmtimeSlave;
    MMTIME  mmtimeStart;
    MMTIME  mmtimeMaster;
} OVRU_EVCB, FAR *POVRU_EVCB;

typedef struct _TIME_EVCB {
    ULONG   ulType;
    ULONG   ulSubType;
    ULONG   ulFlags;
    HSTREAM hstream;
    HID     hid;
    ULONG   ulStatus;
    MMTIME  mmtimeStream;
    ULONG   unused1;
    ULONG   unused2;
} TIME_EVCB, FAR *PTIME_EVCB;

typedef struct _DATA_EVCB {
    ULONG   ulType;
    ULONG   ulSubType;
    ULONG   ulFlags;
    HSTREAM hstream;
    HID     hid;
    ULONG   ulStatus;
    MMTIME  mmtimeStream;
    ULONG   ulEventParm1;
    ULONG   ulEventParm2;
} DATA_EVCB, FAR *PDATA_EVCB;

typedef struct _EVCB {
    ULONG   ulType;
    ULONG   ulSubType;
    ULONG   ulFlags;
    HSTREAM hstream;
    HID     hid;
    ULONG   ulStatus;
    ULONG   ulEventParm1;
    ULONG   ulEventParm2;
    ULONG   ulEventParm3;
} EVCB, FAR *PEVCB;

typedef struct _STATUS_LEVEL_EVCB {
    ULONG   ulType;
    ULONG   ulSubType;
    ULONG   pMCDInstance;
    HSTREAM hstream;
    HID     hid;
    ULONG   ulSample[4];
} STATUS_LEVEL_EVCB, FAR *PSTATUS_EVCB;

#pragma pack()

