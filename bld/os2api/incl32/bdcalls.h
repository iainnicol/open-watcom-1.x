/*
    OS/2 Bidirectional support include file for 32-bit development.
*/

#ifndef __BDCALLS_H__
#define __BDCALLS_H__

#define NlsConvertBidiNumerics Nls16ConvertBidiNumerics
#define NlsConvertBidiString Nls16ConvertBidiString
#define NlsEditShape Nls16EditShape
#define NlsInverseString Nls16InverseString
#define NlsQueryBidiAtt Nls16QueryBidiAtt
#define NlsSetBidiAtt Nls16SetBidiAtt
#define NlsSetBidiPrint Nls16SetBidiPrint
#define NlsShapeBidiString Nls16ShapeBidiString

#define BDHKFLAG_PUSH       0x0004
#define BDHKFLAG_END_PUSH   0x0008
#define BDHKFLAG_AUTO_PUSH  0x0010
#define BDHKFLAG_FIELD_REV  0x0020
#define BDHKFLAG_SCREEN_REV 0x0040
#define BDHKFLAG_BIDI_POPUP 0x0200
#define BDHKFLAG_AUTOMATIC  0x0400
#define BDHKFLAG_INITIAL    0x0800
#define BDHKFLAG_MIDDLE     0x1000
#define BDHKFLAG_FINAL      0x2000
#define BDHKFLAG_ISOLATED   0x4000

#define BDFLAG_AUTOPUSH_RTL 0x0001
#define BDFLAG_AUTOPUSH_LTR 0x0002
#define BDFLAG_PUSHLEVEL    0x0004
#define BDFLAG_LAYER        0x0010
#define BDFLAG_FIELD_REV    0x0020

#define BDCSD_AUTOMATIC 0x00000000
#define BDCSD_PASSTHRU  0x00000001
#define BDCSD_BASE      0x00000010
#define BDCSD_INITIAL   0x00000011
#define BDCSD_MIDDLE    0x00000012
#define BDCSD_FINAL     0x00000013
#define BDCSD_ISOLATED  0x00000014
#define BDNUM_ARABIC    0x00000000
#define BDNUM_PASSTHRU  0x00001000
#define BDNUM_HINDU     0x00002000
#define BDORIENT_LTR    0x00000000
#define BDORIENT_RTL    0x00010000
#define BD_LEVEL        0x30000000
#define BD_SUPPORT      0x00000000

#pragma pack(2)

typedef struct _bdkvcb {
    USHORT BDLength;
    USHORT BDVersionId;
    ULONG  BDAtts;
    ULONG  Reserved;
    USHORT BDHotKeyFlags;
    USHORT BDFlags;
    UCHAR  Reserved2[64];
} BDKVCB;

typedef struct _bdprcb {
    USHORT PRLength;
    ULONG  PRAtts;
    UCHAR  Reserved[14];
} BDPRCB;

typedef struct _csdrec {
    ULONG   RecLength;
    PCHAR16 Buffer;
    ULONG   BufferLength;
    ULONG   BufferIndex;
} CSDRec;

#pragma pack()

typedef CSDRec * _Seg16 PCSDRec;
typedef PBYTE PRETINFO, PSETINFO;

APIRET16 APIENTRY16 NlsConvertBidiNumerics(ULONG,LONG,PUCHAR16,PUCHAR16,ULONG,ULONG);
APIRET16 APIENTRY16 NlsConvertBidiString(PUCHAR16,PUCHAR16,ULONG,ULONG,ULONG,ULONG,ULONG);
APIRET16 APIENTRY16 NlsEditShape(ULONG,LONG,PCSDRec,PCSDRec,PULONG,ULONG);
APIRET16 APIENTRY16 NlsInverseString(PCHAR16,PCHAR16,ULONG,ULONG);
APIRET16 APIENTRY16 NlsQueryBidiAtt(LONG,PRETINFO);
APIRET16 APIENTRY16 NlsSetBidiAtt(LONG,PSETINFO);
APIRET16 APIENTRY16 NlsSetBidiPrint(ULONG,ULONG,USHORT);
APIRET16 APIENTRY16 NlsShapeBidiString(ULONG,ULONG,PCHAR16,PCHAR16,ULONG,ULONG);

#endif
