#ifndef	_INC_DDE
#define	_INC_DDE

#ifndef	_INC_WINDOWS
#include <windows.h>
#endif

#ifdef	__cplusplus
extern	"C" {
#endif

#pragma pack(push,1)

#define	WM_DDE_FIRST	0x03E0
#define	WM_DDE_INITIATE	(WM_DDE_FIRST)
#define	WM_DDE_TERMINATE	(WM_DDE_FIRST+1)
#define	WM_DDE_ADVISE	(WM_DDE_FIRST+2)
#define	WM_DDE_UNADVISE	(WM_DDE_FIRST+3)
#define	WM_DDE_ACK	(WM_DDE_FIRST+4)
#define	WM_DDE_DATA	(WM_DDE_FIRST+5)
#define	WM_DDE_REQUEST	(WM_DDE_FIRST+6)
#define	WM_DDE_POKE	(WM_DDE_FIRST+7)
#define	WM_DDE_EXECUTE	(WM_DDE_FIRST+8)
#define	WM_DDE_LAST	(WM_DDE_FIRST+8)

#ifndef	RC_INVOKED
typedef	struct tagDDEACK {
	unsigned short	bAppReturnCode:8,reserved:6,fBusy:1,fAck:1;
} DDEACK;
typedef	struct tagDDEADVISE {
	unsigned short	reserved:14,fDeferUpd:1,fAckReq:1;
	short	cfFormat;
} DDEADVISE;
typedef	struct tagDDEDATA {
	unsigned short	unused:12,fResponse:1,fRelease:1,reserved:1,fAckReq:1;
	short	cfFormat;
	BYTE	Value[1];
} DDEDATA;
typedef	struct tagDDEPOKE {
	unsigned short	unused:13,fRelease:1,fReserved:2;
	short	cfFormat;
	BYTE	Value[1];
} DDEPOKE;
typedef	struct tagDDELN {
	unsigned short	unused:13,fRelease:1,fDeferUpd:1,fAckReq:1;
	short	cfFormat;
} DDELN;
typedef	struct tagDDEUP {
	unsigned short	unused:12,fAck:1,fRelease:1,fReserved:1,fAckReq:1;
	short	cfFormat;
	BYTE	rgb[1];
} DDEUP;
#endif

#pragma pack(pop)

#ifdef	__cplusplus
}
#endif

#endif
