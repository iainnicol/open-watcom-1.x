/*
    OS/2 Presentation Manager window manager include file
    for 16-bit development.
*/


#define INCL_WININCLUDED

#ifdef INCL_WIN
    #define INCL_WINCLIPBOARD
    #define INCL_WINDIALOGS
    #define INCL_WINWINDOWMGR
    #define INCL_WINERRORS
    #define INCL_WINFRAMEMGR
    #define INCL_WINHOOKS
    #define INCL_WININPUT
    #define INCL_WINMENUS
    #define INCL_WINMESSAGEMGR
    #define INCL_WINSYS
#endif

#define MPFROMP(p)          ((MPARAM)(VOID FAR *)(p))
#define MPFROMHWND(hwnd)    ((MPARAM)(HWND)(hwnd))
#define MPFROMCHAR(ch)      ((MPARAM)(USHORT)(ch))
#define MPFROMSHORT(s)      ((MPARAM)(USHORT)(s))
#define MPFROM2SHORT(s1, s2)((MPARAM)MAKELONG(s1, s2))
#define MPFROMSH2CH(s, uch1, uch2) \
    ((MPARAM)MAKELONG(s, MAKESHORT(uch1, uch2)))
#define MPFROMLONG(l)       ((MPARAM)(ULONG)(l))
#define PVOIDFROMMP(mp)     ((VOID FAR *)(mp))
#define HWNDFROMMP(mp)      ((HWND)(mp))
#define CHAR1FROMMP(mp)     ((UCHAR)(mp))
#define CHAR2FROMMP(mp)     ((UCHAR)((ULONG)mp >> 8))
#define CHAR3FROMMP(mp)     ((UCHAR)((ULONG)mp >> 16))
#define CHAR4FROMMP(mp)     ((UCHAR)((ULONG)mp >> 24))
#define SHORT1FROMMP(mp)    ((USHORT)(ULONG)(mp))
#define SHORT2FROMMP(mp)    ((USHORT)((ULONG)mp >> 16))
#define LONGFROMMP(mp)      ((ULONG)(mp))
#define MRFROMP(p)          ((MRESULT)(VOID FAR *)(p))
#define MRFROMSHORT(s)      ((MRESULT)(USHORT)(s))
#define MRFROM2SHORT(s1, s2)((MRESULT)MAKELONG(s1, s2))
#define MRFROMLONG(l)       ((MRESULT)(ULONG)(l))
#define PVOIDFROMMR(mr)     ((VOID FAR *)(mr))
#define SHORT1FROMMR(mr)    ((USHORT)((ULONG)mr))
#define SHORT2FROMMR(mr)    ((USHORT)((ULONG)mr >> 16))
#define LONGFROMMR(mr)      ((ULONG)(mr))

#define HWND_DESKTOP        (HWND)1
#define HWND_OBJECT         (HWND)2
#define HWND_TOP            (HWND)3
#define HWND_BOTTOM         (HWND)4
#define HWND_THREADCAPTURE  (HWND)5

#define WS_VISIBLE          0x80000000L
#define WS_DISABLED         0x40000000L
#define WS_CLIPCHILDREN     0x20000000L
#define WS_CLIPSIBLINGS     0x10000000L
#define WS_PARENTCLIP       0x08000000L
#define WS_SAVEBITS         0x04000000L
#define WS_SYNCPAINT        0x02000000L
#define WS_MINIMIZED        0x01000000L
#define WS_MAXIMIZED        0x00800000L

#define WS_GROUP            0x00010000L
#define WS_TABSTOP          0x00020000L
#define WS_MULTISELECT      0x00040000L

#define CS_MOVENOTIFY       0x00000001L
#define CS_SIZEREDRAW       0x00000004L
#define CS_HITTEST          0x00000008L
#define CS_PUBLIC           0x00000010L
#define CS_FRAME            0x00000020L
#define CS_CLIPCHILDREN     0x20000000L
#define CS_CLIPSIBLINGS     0x10000000L
#define CS_PARENTCLIP       0x08000000L
#define CS_SAVEBITS         0x04000000L
#define CS_SYNCPAINT        0x02000000L

typedef LHANDLE HWND, FAR *PHWND;
typedef LHANDLE HAB;

typedef VOID FAR    *MPARAM;
typedef MPARAM FAR  *PMPARAM;
typedef VOID FAR    *MRESULT;
typedef MRESULT FAR *PMRESULT;

typedef MRESULT (PASCAL FAR *PFNWP)(HWND,USHORT,MPARAM,MPARAM);

#if defined(INCL_WINWINDOWMGR) || !defined(INCL_NOCOMMON)

#define PSF_LOCKWINDOWUPDATE       0x0001
#define PSF_CLIPUPWARDS            0x0002
#define PSF_CLIPDOWNWARDS          0x0004
#define PSF_CLIPSIBLINGS           0x0008
#define PSF_CLIPCHILDREN           0x0010
#define PSF_PARENTCLIP             0x0020

#define SW_SCROLLCHILDREN          0x0001
#define SW_INVALIDATERGN           0x0002

#define QV_OS2      0x0000
#define QV_CMS      0x0001
#define QV_TSO      0x0002
#define QV_TSOBATCH 0x0003
#define QV_OS400    0x0004

typedef struct _QVERSDATA {
    USHORT   environment;
    USHORT   version;
} QVERSDATA, FAR *PQVERSDATA;

HPS     APIENTRY WinBeginPaint(HWND,HPS,PRECTL);
MRESULT APIENTRY WinDefWindowProc(HWND,USHORT,MPARAM,MPARAM);
BOOL    APIENTRY WinDestroyWindow(HWND);
BOOL    APIENTRY WinEndPaint(HPS);
BOOL    APIENTRY WinFillRect(HPS,PRECTL,LONG);
HPS     APIENTRY WinGetClipPS(HWND,HWND,USHORT);
HPS     APIENTRY WinGetPS(HWND);
HAB     APIENTRY WinInitialize(USHORT);
BOOL    APIENTRY WinIsWindowShowing(HWND);
HDC     APIENTRY WinOpenWindowDC(HWND);
HAB     APIENTRY WinQueryAnchorBlock(HWND);
ULONG   APIENTRY WinQueryVersion(HAB);
BOOL    APIENTRY WinQueryWindowRect(HWND,PRECTL);
BOOL    APIENTRY WinRegisterClass(HAB,PSZ,PFNWP,ULONG,USHORT);
BOOL    APIENTRY WinReleasePS(HPS);
SHORT   APIENTRY WinScrollWindow(HWND,SHORT,SHORT,PRECTL,PRECTL,HRGN,PRECTL,USHORT);
BOOL    APIENTRY WinShowWindow(HWND,BOOL);
BOOL    APIENTRY WinTerminate(HAB);

#endif

#define QW_NEXT         0
#define QW_PREV         1
#define QW_TOP          2
#define QW_BOTTOM       3
#define QW_OWNER        4
#define QW_PARENT       5
#define QW_NEXTTOP      6
#define QW_PREVTOP      7
#define QW_FRAMEOWNER   8

#define AWP_MINIMIZED  0x00010000L
#define AWP_MAXIMIZED  0x00020000L
#define AWP_RESTORED   0x00040000L
#define AWP_ACTIVATE   0x00080000L
#define AWP_DEACTIVATE 0x00100000L

#define SWP_SIZE            0x0001
#define SWP_MOVE            0x0002
#define SWP_ZORDER          0x0004
#define SWP_SHOW            0x0008
#define SWP_HIDE            0x0010
#define SWP_NOREDRAW        0x0020
#define SWP_NOADJUST        0x0040
#define SWP_ACTIVATE        0x0080
#define SWP_DEACTIVATE      0x0100
#define SWP_EXTSTATECHANGE  0x0200
#define SWP_MINIMIZE        0x0400
#define SWP_MAXIMIZE        0x0800
#define SWP_RESTORE         0x1000
#define SWP_FOCUSACTIVATE   0x2000
#define SWP_FOCUSDEACTIVATE 0x4000

#define DBM_NORMAL          0x0000
#define DBM_INVERT          0x0001
#define DBM_HALFTONE        0x0002
#define DBM_STRETCH         0x0004
#define DBM_IMAGEATTRS      0x0008

#define DT_LEFT             0x0000
#define DT_EXTERNALLEADING  0x0080
#define DT_CENTER           0x0100
#define DT_RIGHT            0x0200
#define DT_TOP              0x0000
#define DT_VCENTER          0x0400
#define DT_BOTTOM           0x0800
#define DT_HALFTONE         0x1000
#define DT_MNEMONIC         0x2000
#define DT_WORDBREAK        0x4000
#define DT_ERASERECT        0x8000
#define DT_QUERYEXTENT      0x0002
#define DT_TEXTATTRS        0x0040

#define DB_PATCOPY          0x0000
#define DB_PATINVERT        0x0001
#define DB_DESTINVERT       0x0002
#define DB_AREAMIXMODE      0x0003

#define DB_ROP              0x0007
#define DB_INTERIOR         0x0008
#define DB_AREAATTRS        0x0010
#define DB_STANDARD         0x0100
#define DB_DLGBORDER        0x0200

typedef struct _SWP {
    USHORT fs;
    SHORT  cy;
    SHORT  cx;
    SHORT  y;
    SHORT  x;
    HWND   hwndInsertBehind;
    HWND   hwnd;
} SWP, FAR *PSWP;

HWND  APIENTRY WinCreateWindow(HWND,PSZ,PSZ,ULONG,SHORT,SHORT,SHORT,
                  SHORT,HWND,HWND,USHORT,PVOID,PVOID);
BOOL  APIENTRY WinDrawBitmap(HPS,HBITMAP,PRECTL,PPOINTL,LONG,LONG,USHORT);
BOOL  APIENTRY WinDrawBorder(HPS,PRECTL,SHORT,SHORT,LONG,LONG,USHORT);
SHORT APIENTRY WinDrawText(HPS,SHORT,PCH,PRECTL,LONG,LONG,USHORT);
BOOL  APIENTRY WinEnableWindow(HWND,BOOL);
BOOL  APIENTRY WinEnableWindowUpdate(HWND,BOOL);
SHORT APIENTRY WinLoadMessage(HAB,HMODULE,USHORT,SHORT,PSZ);
SHORT APIENTRY WinLoadString(HAB,HMODULE,USHORT,SHORT,PSZ);
BOOL  APIENTRY WinInvalidateRect(HWND,PRECTL,BOOL);
BOOL  APIENTRY WinInvalidateRegion(HWND,HRGN,BOOL);
BOOL  APIENTRY WinInvertRect(HPS,PRECTL);
BOOL  APIENTRY WinIsChild(HWND,HWND);
BOOL  APIENTRY WinIsWindow(HAB,HWND);
BOOL  APIENTRY WinIsWindowEnabled(HWND);
BOOL  APIENTRY WinIsWindowVisible(HWND);
SHORT APIENTRY WinMultWindowFromIDs(HWND,PHWND,USHORT,USHORT);
HWND  APIENTRY WinQueryWindow(HWND,SHORT,BOOL);
BOOL  APIENTRY WinQueryWindowPos(HWND,PSWP);
SHORT APIENTRY WinQueryWindowText(HWND,SHORT,PCH);
SHORT APIENTRY WinQueryWindowTextLength(HWND);
BOOL  APIENTRY WinSetMultWindowPos(HAB,PSWP,USHORT);
BOOL  APIENTRY WinSetOwner(HWND,HWND);
BOOL  APIENTRY WinSetParent(HWND,HWND,BOOL);
BOOL  APIENTRY WinSetWindowPos(HWND,HWND,SHORT,SHORT,SHORT,SHORT,USHORT);
BOOL  APIENTRY WinSetWindowText(HWND,PSZ);
HWND  APIENTRY WinQueryDesktopWindow(HAB,HDC);
HWND  APIENTRY WinQueryObjectWindow(HWND);
BOOL  APIENTRY WinQueryWindowProcess(HWND,PPID,PTID);
BOOL  APIENTRY WinUpdateWindow(HWND);
HWND  APIENTRY WinWindowFromID(HWND,USHORT);

#if defined(INCL_WINWINDOWMGR) || !defined(INCL_NOCOMMON)

BOOL APIENTRY WinSetActiveWindow(HWND,HWND);

#endif

#ifdef INCL_WINWINDOWMGR

#define QWS_USER  0
#define QWS_ID    (-1)
#define QWS_MIN   (-1)

#define QWL_USER  0
#define QWL_STYLE (-2)
#define QWP_PFNWP (-3)
#define QWL_HMQ   (-4)
#define QWL_MIN   (-4)

#define QWL_HHEAP         0x0004
#define QWL_HWNDFOCUSSAVE 0x0018

#define QWS_FLAGS     0x0008
#define QWS_RESULT    0x000a
#define QWS_XRESTORE  0x000c
#define QWS_YRESTORE  0x000e
#define QWS_CXRESTORE 0x0010
#define QWS_CYRESTORE 0x0012
#define QWS_XMINIMIZE 0x0014
#define QWS_YMINIMIZE 0x0016

typedef LHANDLE HENUM;

typedef struct _CREATESTRUCT {
    PVOID  pPresParams;
    PVOID  pCtlData;
    USHORT id;
    HWND   hwndInsertBehind;
    HWND   hwndOwner;
    SHORT  cy;
    SHORT  cx;
    SHORT  y;
    SHORT  x;
    ULONG  flStyle;
    PSZ    pszText;
    PSZ    pszClass;
    HWND   hwndParent;
} CREATESTRUCT, FAR *PCREATESTRUCT;

typedef struct _CLASSINFO {
    ULONG  flClassStyle;
    PFNWP  pfnWindowProc;
    USHORT cbWindowData;
} CLASSINFO, FAR *PCLASSINFO;

HENUM  APIENTRY WinBeginEnumWindows(HWND);
BOOL   APIENTRY WinEndEnumWindows(HENUM);
SHORT  APIENTRY WinExcludeUpdateRegion(HPS,HWND);
HWND   APIENTRY WinGetNextWindow(HENUM);
HPS    APIENTRY WinGetScreenPS(HWND);
BOOL   APIENTRY WinIsThreadActive(HAB);
BOOL   APIENTRY WinLockVisRegions(HWND,BOOL);
HWND   APIENTRY WinLockWindow(HWND,BOOL);
BOOL   APIENTRY WinLockWindowUpdate(HWND,HWND);
BOOL   APIENTRY WinMapWindowPoints(HWND,HWND,PPOINTL,SHORT);
HWND   APIENTRY WinQueryActiveWindow(HWND,BOOL);
BOOL   APIENTRY WinQueryClassInfo(HAB,PSZ,PCLASSINFO);
SHORT  APIENTRY WinQueryClassName(HWND,SHORT,PCH);
HWND   APIENTRY WinQuerySysModalWindow(HWND,BOOL);
BOOL   APIENTRY WinQueryUpdateRect(HWND,PRECTL);
SHORT  APIENTRY WinQueryUpdateRegion(HWND,HRGN);
HDC    APIENTRY WinQueryWindowDC(HWND);
SHORT  APIENTRY WinQueryWindowLockCount(HWND);
PVOID  APIENTRY WinQueryWindowPtr(HWND,SHORT);
USHORT APIENTRY WinQueryWindowUShort(HWND,SHORT);
ULONG  APIENTRY WinQueryWindowULong(HWND,SHORT);
BOOL   APIENTRY WinRegisterWindowDestroy(HWND,BOOL);
BOOL   APIENTRY WinSetSysModalWindow(HWND,HWND);
BOOL   APIENTRY WinSetWindowBits(HWND,SHORT,ULONG,ULONG);
BOOL   APIENTRY WinSetWindowPtr(HWND,SHORT,PVOID);
BOOL   APIENTRY WinSetWindowULong(HWND,SHORT,ULONG);
BOOL   APIENTRY WinSetWindowUShort(HWND,SHORT,USHORT);
PFNWP  APIENTRY WinSubclassWindow(HWND,PFNWP);
BOOL   APIENTRY WinValidateRect(HWND,PRECTL,BOOL);
BOOL   APIENTRY WinValidateRegion(HWND,HRGN,BOOL);
HWND   APIENTRY WinWindowFromPoint(HWND,PPOINTL,BOOL,BOOL);
HWND   APIENTRY WinWindowFromDC(HDC);

#endif

#if defined(INCL_WINMESSAGEMGR) || !defined(INCL_NOCOMMON)

#define CMDSRC_PUSHBUTTON  1
#define CMDSRC_MENU        2
#define CMDSRC_ACCELERATOR 3
#define CMDSRC_OTHER       0

#define PM_REMOVE   1
#define PM_NOREMOVE 0

#define RUM_IN    1
#define RUM_OUT   2
#define RUM_INOUT 3

#define SMD_DELAYED   1
#define SMD_IMMEDIATE 2

#define SSM_SYNCHRONOUS  1
#define SSM_ASYNCHRONOUS 2
#define SSM_MIXED        3

#define WM_NULL                 0x0000
#define WM_CREATE               0x0001
#define WM_DESTROY              0x0002
#define WM_OTHERWINDOWDESTROYED 0x0003
#define WM_ENABLE               0x0004
#define WM_SHOW                 0x0005
#define WM_MOVE                 0x0006
#define WM_SIZE                 0x0007
#define WM_ADJUSTWINDOWPOS      0x0008
#define WM_CALCVALIDRECTS       0x0009
#define WM_SETWINDOWPARAMS      0x000a
#define WM_QUERYWINDOWPARAMS    0x000b
#define WM_HITTEST              0x000c
#define WM_ACTIVATE             0x000d
#define WM_SETFOCUS             0x000f
#define WM_SETSELECTION         0x0010
#define WM_PPAINT               0x0011
#define WM_PSETFOCUS            0x0012
#define WM_PSYSCOLORCHANGE      0x0013
#define WM_PSIZE                0x0014
#define WM_PACTIVATE            0x0015
#define WM_PCONTROL             0x0016
#define WM_COMMAND              0x0020
#define WM_SYSCOMMAND           0x0021
#define WM_HELP                 0x0022
#define WM_PAINT                0x0023
#define WM_TIMER                0x0024
#define WM_SEM1                 0x0025
#define WM_SEM2                 0x0026
#define WM_SEM3                 0x0027
#define WM_SEM4                 0x0028
#define WM_CLOSE                0x0029
#define WM_QUIT                 0x002a
#define WM_SYSCOLORCHANGE       0x002b
#define WM_SYSVALUECHANGED      0x002d
#define WM_APPTERMINATENOTIFY   0x002e
#define WM_PRESPARAMCHANGED     0x002f
#define WM_CONTROL              0x0030
#define WM_VSCROLL              0x0031
#define WM_HSCROLL              0x0032
#define WM_INITMENU             0x0033
#define WM_MENUSELECT           0x0034
#define WM_MENUEND              0x0035
#define WM_DRAWITEM             0x0036
#define WM_MEASUREITEM          0x0037
#define WM_CONTROLPOINTER       0x0038
#define WM_CONTROLHEAP          0x0039
#define WM_QUERYDLGCODE         0x003a
#define WM_INITDLG              0x003b
#define WM_SUBSTITUTESTRING     0x003c
#define WM_MATCHMNEMONIC        0x003d
#define WM_SAVEAPPLICATION      0x003e
#define WM_HELPBASE             0x0F00 /* Start of msgs for help manager   */
#define WM_HELPTOP              0x0FFF /* End of msgs for help manager     */
#define WM_USER                 0x1000

#define COMMANDMSG(pmsg) ((struct _COMMANDMSG FAR *)((PBYTE)pmsg - sizeof(MPARAM) * 2))

typedef LHANDLE HMQ;

typedef struct _COMMANDMSG {
    USHORT source;
    BOOL   fMouse;
    USHORT cmd;
    USHORT unused;
} CMDMSG;

typedef struct _MQINFO {
    USHORT cb;
    PID    pid;
    TID    tid;
    USHORT cmsgs;
    PVOID  pReserved;
} MQINFO, FAR *PMQINFO;

typedef struct _QMSG {
    HWND   hwnd;
    USHORT msg;
    MPARAM mp1;
    MPARAM mp2;
    ULONG  time;
    POINTL ptl;
} QMSG, FAR *PQMSG;

BOOL    APIENTRY WinCancelShutdown(HMQ,BOOL);
HMQ     APIENTRY WinCreateMsgQueue(HAB,SHORT);
BOOL    APIENTRY WinDestroyMsgQueue(HMQ);
MRESULT APIENTRY WinDispatchMsg(HAB,PQMSG);
BOOL    APIENTRY WinGetMsg(HAB,PQMSG,HWND,USHORT,USHORT);
BOOL    APIENTRY WinPeekMsg(HAB,PQMSG,HWND,USHORT,USHORT,USHORT);
BOOL    APIENTRY WinPostMsg(HWND,USHORT,MPARAM,MPARAM);
BOOL    APIENTRY WinQueryQueueInfo(HMQ,PMQINFO,USHORT);
BOOL    APIENTRY WinRegisterUserDatatype(HAB,SHORT,SHORT,PSHORT);
BOOL    APIENTRY WinRegisterUserMsg(HAB,USHORT,SHORT,SHORT,SHORT,SHORT,SHORT);
MRESULT APIENTRY WinSendMsg(HWND,USHORT,MPARAM,MPARAM);
BOOL    APIENTRY WinSetMsgMode(HAB,PSZ,SHORT);
BOOL    APIENTRY WinSetSynchroMode(HAB,SHORT);

#endif

#if defined(INCL_WINFRAMEMGR) || !defined(INCL_NOCOMMON)

#define FCF_TITLEBAR          0x00000001L
#define FCF_SYSMENU           0x00000002L
#define FCF_MENU              0x00000004L
#define FCF_SIZEBORDER        0x00000008L
#define FCF_MINBUTTON         0x00000010L
#define FCF_MAXBUTTON         0x00000020L
#define FCF_MINMAX            0x00000030L
#define FCF_VERTSCROLL        0x00000040L
#define FCF_HORZSCROLL        0x00000080L
#define FCF_DLGBORDER         0x00000100L
#define FCF_BORDER            0x00000200L
#define FCF_SHELLPOSITION     0x00000400L
#define FCF_TASKLIST          0x00000800L
#define FCF_NOBYTEALIGN       0x00001000L
#define FCF_NOMOVEWITHOWNER   0x00002000L
#define FCF_ICON              0x00004000L
#define FCF_ACCELTABLE        0x00008000L
#define FCF_SYSMODAL          0x00010000L
#define FCF_SCREENALIGN       0x00020000L
#define FCF_MOUSEALIGN        0x00040000L
#define FCF_PALETTE_NORMAL    0x00080000L
#define FCF_PALETTE_HELP      0x00100000L
#define FCF_PALETTE_POPUPODD  0x00200000L
#define FCF_PALETTE_POPUPEVEN 0x00400000L
#define FCF_DBE_APPSTAT       0x80000000L
#define FCF_STANDARD          0x0008CC3FL

#define FS_ICON            0x00000001L
#define FS_ACCELTABLE      0x00000002L
#define FS_SHELLPOSITION   0x00000004L
#define FS_TASKLIST        0x00000008L
#define FS_NOBYTEALIGN     0x00000010L
#define FS_NOMOVEWITHOWNER 0x00000020L
#define FS_SYSMODAL        0x00000040L
#define FS_DLGBORDER       0x00000080L
#define FS_BORDER          0x00000100L
#define FS_SCREENALIGN     0x00000200L
#define FS_MOUSEALIGN      0x00000400L
#define FS_SIZEBORDER      0x00000800L
#define FS_DBE_APPSTAT     0x00008000L
#define FS_STANDARD        0x0000000FL

#define FF_FLASHWINDOW   0x0001
#define FF_ACTIVE        0x0002
#define FF_FLASHHILITE   0x0004
#define FF_OWNERHIDDEN   0x0008
#define FF_DLGDISMISSED  0x0010
#define FF_OWNERDISABLED 0x0020
#define FF_SELECTED      0x0040
#define FF_NOACTIVATESWP 0x0080

typedef struct _FRAMECDATA {
    USHORT  cb;
    ULONG   flCreateFlags;
    HMODULE hmodResources;
    USHORT  idResources;
} FRAMECDATA, FAR *PFRAMECDATA;

HWND  APIENTRY WinCreateStdWindow(HWND,ULONG,PULONG,PSZ,PSZ,ULONG,HMODULE,USHORT,PHWND);

#endif

#ifdef INCL_WINFRAMEMGR

#define WM_FLASHWINDOW        0x0040
#define WM_FORMATFRAME        0x0041
#define WM_UPDATEFRAME        0x0042
#define WM_FOCUSCHANGE        0x0043
#define WM_SETBORDERSIZE      0x0044
#define WM_TRACKFRAME         0x0045
#define WM_MINMAXFRAME        0x0046
#define WM_SETICON            0x0047
#define WM_QUERYICON          0x0048
#define WM_SETACCELTABLE      0x0049
#define WM_QUERYACCELTABLE    0x004a
#define WM_TRANSLATEACCEL     0x004b
#define WM_QUERYTRACKINFO     0x004c
#define WM_QUERYBORDERSIZE    0x004d
#define WM_NEXTMENU           0x004e
#define WM_ERASEBACKGROUND    0x004f
#define WM_QUERYFRAMEINFO     0x0050
#define WM_QUERYFOCUSCHAIN    0x0051
#define WM_CALCFRAMERECT      0x0053
#define WM_WINDOWPOSCHANGED   0x0055
#define WM_QUERYFRAMECTLCOUNT 0x0059
#define WM_QUERYHELPINFO      0x005B
#define WM_SETHELPINFO        0x005C
#define WM_ERROR              0x005D

#define FI_FRAME           0x00000001L
#define FI_OWNERHIDE       0x00000002L
#define FI_ACTIVATEOK      0x00000004L
#define FI_NOMOVEWITHOWNER 0x00000008L

#define FID_SYSMENU       0x8002
#define FID_TITLEBAR      0x8003
#define FID_MINMAX        0x8004
#define FID_MENU          0x8005
#define FID_VERTSCROLL    0x8006
#define FID_HORZSCROLL    0x8007
#define FID_CLIENT        0x8008
#define FID_DBE_APPSTAT   0x8010
#define FID_DBE_KBDSTAT   0x8011
#define FID_DBE_PECIC     0x8012
#define FID_DBE_KKPOPUP   0x8013

#define SC_SIZE           0x8000
#define SC_MOVE           0x8001
#define SC_MINIMIZE       0x8002
#define SC_MAXIMIZE       0x8003
#define SC_CLOSE          0x8004
#define SC_NEXT           0x8005
#define SC_APPMENU        0x8006
#define SC_SYSMENU        0x8007
#define SC_RESTORE        0x8008
#define SC_NEXTFRAME      0x8009
#define SC_NEXTWINDOW     0x8010
#define SC_TASKMANAGER    0x8011
#define SC_HELPKEYS       0x8012
#define SC_HELPINDEX      0x8013
#define SC_HELPEXTENDED   0x8014
#define SC_SWITCHPANELIDS 0x8015
#define SC_DBE_FIRST      0x8018
#define SC_DBE_LAST       0x801F

#define WC_FRAME ((PSZ)0xffff0001L)

BOOL  APIENTRY WinCalcFrameRect(HWND,PRECTL,BOOL);
BOOL  APIENTRY WinCreateFrameControls(HWND,PFRAMECDATA,PSZ);
BOOL  APIENTRY WinFlashWindow(HWND,BOOL);
BOOL  APIENTRY WinGetMaxPosition(HWND,PSWP);
BOOL  APIENTRY WinGetMinPosition(HWND,PSWP,PPOINTL);

#endif

#ifdef INCL_WINHOOKS

#define HK_SENDMSG         0
#define HK_INPUT           1
#define HK_MSGFILTER       2
#define HK_JOURNALRECORD   3
#define HK_JOURNALPLAYBACK 4
#define HK_HELP            5
#define HK_LOADER          6
#define HK_REGISTERUSERMSG 7
#define HK_MSGCONTROL      8
#define HK_PLIST_ENTRY     9
#define HK_PLIST_EXIT      10
#define HK_FINDWORD        11
#define HK_CODEPAGECHANGED 12
#define HMQ_CURRENT  ((HMQ)1)

#define MSGF_DIALOGBOX  1
#define MSGF_MESSAGEBOX 2
#define MSGF_TRACK      8

#define HLPM_FRAME  (-1)
#define HLPM_WINDOW (-2)
#define HLPM_MENU   (-3)

#define LHK_DELETEPROC 1
#define LHK_DELETELIB  2
#define LHK_LOADPROC   3
#define LHK_LOADLIB    4

#define MCHK_MSGINTEREST      1
#define MCHK_CLASSMSGINTEREST 2
#define MCHK_SYNCHRONISATION  3
#define MCHK_MSGMODE          4

#define RUMHK_DATATYPE 1
#define RUMHK_MSG      2

typedef struct _SMHSTRUCT {
    MPARAM mp2;
    MPARAM mp1;
    USHORT msg;
    HWND   hwnd;
} SMHSTRUCT, FAR *PSMHSTRUCT;

BOOL APIENTRY WinCallMsgFilter(HAB,PQMSG,USHORT);
BOOL APIENTRY WinReleaseHook(HAB,HMQ,SHORT,PFN,HMODULE);
BOOL APIENTRY WinSetHook(HAB,HMQ,SHORT,PFN,HMODULE);

#endif

#if defined(INCL_WINDIALOGS) || !defined(INCL_NOCOMMON)

#define MB_OK               0x0000
#define MB_OKCANCEL         0x0001
#define MB_RETRYCANCEL      0x0002
#define MB_ABORTRETRYIGNORE 0x0003
#define MB_YESNO            0x0004
#define MB_YESNOCANCEL      0x0005
#define MB_CANCEL           0x0006
#define MB_ENTER            0x0007
#define MB_ENTERCANCEL      0x0008
#define MB_NOICON           0x0000
#define MB_CUANOTIFICATION  0x0000
#define MB_ICONQUESTION     0x0010
#define MB_ICONEXCLAMATION  0x0020
#define MB_CUAWARNING       0x0020
#define MB_ICONASTERISK     0x0030
#define MB_ICONHAND         0x0040
#define MB_CUACRITICAL      0x0040
#define MB_QUERY            MB_ICONQUESTION
#define MB_WARNING          MB_CUAWARNING
#define MB_INFORMATION      MB_ICONASTERISK
#define MB_CRITICAL         MB_CUACRITICAL
#define MB_ERROR            MB_CRITICAL
#define MB_DEFBUTTON1       0x0000
#define MB_DEFBUTTON2       0x0100
#define MB_DEFBUTTON3       0x0200
#define MB_APPLMODAL        0x0000
#define MB_SYSTEMMODAL      0x1000
#define MB_HELP             0x2000
#define MB_MOVEABLE         0x4000

#define MBID_OK     1
#define MBID_CANCEL 2
#define MBID_ABORT  3
#define MBID_RETRY  4
#define MBID_IGNORE 5
#define MBID_YES    6
#define MBID_NO     7
#define MBID_HELP   8
#define MBID_ENTER  9
#define MBID_ERROR  0xffff

#define DID_OK     1
#define DID_CANCEL 2
#define DID_ERROR  0xffff

#define WA_WARNING                 0
#define WA_NOTE                    1
#define WA_ERROR                   2
#define WA_CWINALARMS              3

BOOL    APIENTRY WinAlarm(HWND,USHORT);
MRESULT APIENTRY WinDefDlgProc(HWND,USHORT,MPARAM,MPARAM);
BOOL    APIENTRY WinDismissDlg(HWND hwndDlg, USHORT usResult);
USHORT  APIENTRY WinDlgBox(HWND,HWND,PFNWP,HMODULE,USHORT,PVOID);
BOOL    APIENTRY WinGetDlgMsg(HWND,PQMSG);
HWND    APIENTRY WinLoadDlg(HWND,HWND,PFNWP,HMODULE,USHORT,PVOID);
USHORT  APIENTRY WinMessageBox(HWND,HWND,PSZ,PSZ,USHORT,USHORT);
BOOL    APIENTRY WinQueryDlgItemShort(HWND,USHORT,PSHORT,BOOL);
USHORT  APIENTRY WinQueryDlgItemText(HWND,USHORT,SHORT,PSZ);
SHORT   APIENTRY WinQueryDlgItemTextLength(HWND,USHORT);
BOOL    APIENTRY WinSetDlgItemShort(HWND,USHORT,USHORT,BOOL);
BOOL    APIENTRY WinSetDlgItemText(HWND,USHORT,PSZ);

#endif

#if defined(INCL_WININPUT) || !defined(INCL_NOCOMMON)

#define FC_NOSETFOCUS            0x0001
#define FC_NOBRINGTOTOP          FC_NOSETFOCUS
#define FC_NOLOSEFOCUS           0x0002
#define FC_NOBRINGTOPFIRSTWINDOW FC_NOLOSEFOCUS
#define FC_NOSETACTIVEFOCUS      0x0003
#define FC_NOSETACTIVE           0x0004
#define FC_NOLOSEACTIVE          0x0008
#define FC_NOSETSELECTION        0x0010
#define FC_NOLOSESELECTION       0x0020

#define QFC_NEXTINCHAIN  1
#define QFC_ACTIVE       2
#define QFC_FRAME        3
#define QFC_SELECTACTIVE 4

BOOL  APIENTRY WinFocusChange(HWND,HWND,USHORT);
BOOL  APIENTRY WinSetFocus(HWND,HWND);

#endif

#ifdef INCL_WININPUT

#define JRN_QUEUESTATUS            0x00000001L
#define JRN_PHYSKEYSTATE           0x00000002L

#define KC_CHAR        0x0001
#define KC_VIRTUALKEY  0x0002
#define KC_SCANCODE    0x0004
#define KC_SHIFT       0x0008
#define KC_CTRL        0x0010
#define KC_ALT         0x0020
#define KC_KEYUP       0x0040
#define KC_PREVDOWN    0x0080
#define KC_LONEKEY     0x0100
#define KC_DEADKEY     0x0200
#define KC_COMPOSITE   0x0400
#define KC_INVALIDCOMP 0x0800
#define KC_TOGGLE      0x1000
#define KC_INVALIDCHAR 0x2000
#define KC_DBCSRSRVD1  0x4000
#define KC_DBCSRSRVD2  0x8000

#define VK_BUTTON1   0x01
#define VK_BUTTON2   0x02
#define VK_BUTTON3   0x03
#define VK_BREAK     0x04
#define VK_BACKSPACE 0x05
#define VK_TAB       0x06
#define VK_BACKTAB   0x07
#define VK_NEWLINE   0x08
#define VK_SHIFT     0x09
#define VK_CTRL      0x0A
#define VK_ALT       0x0B
#define VK_ALTGRAF   0x0C
#define VK_PAUSE     0x0D
#define VK_CAPSLOCK  0x0E
#define VK_ESC       0x0F
#define VK_SPACE     0x10
#define VK_PAGEUP    0x11
#define VK_PAGEDOWN  0x12
#define VK_END       0x13
#define VK_HOME      0x14
#define VK_LEFT      0x15
#define VK_UP        0x16
#define VK_RIGHT     0x17
#define VK_DOWN      0x18
#define VK_PRINTSCRN 0x19
#define VK_INSERT    0x1A
#define VK_DELETE    0x1B
#define VK_SCRLLOCK  0x1C
#define VK_NUMLOCK   0x1D
#define VK_ENTER     0x1E
#define VK_SYSRQ     0x1F
#define VK_F1        0x20
#define VK_F2        0x21
#define VK_F3        0x22
#define VK_F4        0x23
#define VK_F5        0x24
#define VK_F6        0x25
#define VK_F7        0x26
#define VK_F8        0x27
#define VK_F9        0x28
#define VK_F10       0x29
#define VK_F11       0x2A
#define VK_F12       0x2B
#define VK_F13       0x2C
#define VK_F14       0x2D
#define VK_F15       0x2E
#define VK_F16       0x2F
#define VK_F17       0x30
#define VK_F18       0x31
#define VK_F19       0x32
#define VK_F20       0x33
#define VK_F21       0x34
#define VK_F22       0x35
#define VK_F23       0x36
#define VK_F24       0x37
#define VK_MENU      VK_F10
#define VK_DBCSFIRST 0x0080
#define VK_DBCSLAST  0x00ff
#define VK_USERFIRST 0x0100
#define VK_USERLAST  0x01ff

#define WM_MOUSEFIRST       0x0070
#define WM_MOUSELAST        0x0079
#define WM_BUTTONCLICKFIRST 0x0071
#define WM_BUTTONCLICKLAST  0x0079
#define WM_MOUSEMOVE        0x0070
#define WM_BUTTON1DOWN      0x0071
#define WM_BUTTON1UP        0x0072
#define WM_BUTTON1DBLCLK    0x0073
#define WM_BUTTON2DOWN      0x0074
#define WM_BUTTON2UP        0x0075
#define WM_BUTTON2DBLCLK    0x0076
#define WM_BUTTON3DOWN      0x0077
#define WM_BUTTON3UP        0x0078
#define WM_BUTTON3DBLCLK    0x0079
#define WM_CHAR             0x007a
#define WM_VIOCHAR          0x007b
#define WM_JOURNALNOTIFY    0x007c

#define CHARMSG(pmsg)  ((struct _CHARMSG FAR *)((PBYTE)pmsg - sizeof(MPARAM) * 2))
#define MOUSEMSG(pmsg) ((struct _MOUSEMSG FAR *)((PBYTE)pmsg - sizeof(MPARAM) * 2))

typedef struct _CHARMSG {
    USHORT chr;
    USHORT vkey;
    USHORT fs;
    UCHAR  cRepeat;
    UCHAR  scancode;
} CHRMSG;

typedef struct _MOUSEMSG {
    USHORT codeHitTest;
    USHORT unused;
    SHORT  x;
    SHORT  y;
} MSEMSG;

BOOL  APIENTRY WinIsPhysInputEnabled(HWND);
SHORT APIENTRY WinGetKeyState(HWND,SHORT);
SHORT APIENTRY WinGetPhysKeyState(HWND,SHORT);
BOOL  APIENTRY WinEnablePhysInput(HWND,BOOL);
HWND  APIENTRY WinQueryCapture(HWND,BOOL);
HWND  APIENTRY WinQueryFocus(HWND,BOOL);
BOOL  APIENTRY WinSetCapture(HWND,HWND);
BOOL  APIENTRY WinSetKeyboardStateTable(HWND,PBYTE,BOOL);

#endif

#ifdef INCL_WINCLIPBOARD

#define CF_TEXT        1
#define CF_BITMAP      2
#define CF_DSPTEXT     3
#define CF_DSPBITMAP   4
#define CF_METAFILE    5
#define CF_DSPMETAFILE 6

#define CFI_OWNERFREE    0x0001
#define CFI_OWNERDISPLAY 0x0002
#define CFI_SELECTOR     0x0100
#define CFI_HANDLE       0x0200

#define WM_RENDERFMT        0x0060
#define WM_RENDERALLFMTS    0x0061
#define WM_DESTROYCLIPBOARD 0x0062
#define WM_PAINTCLIPBOARD   0x0063
#define WM_SIZECLIPBOARD    0x0064
#define WM_HSCROLLCLIPBOARD 0x0065
#define WM_VSCROLLCLIPBOARD 0x0066
#define WM_DRAWCLIPBOARD    0x0067

BOOL   APIENTRY WinCloseClipbrd(HAB);
BOOL   APIENTRY WinEmptyClipbrd(HAB);
USHORT APIENTRY WinEnumClipbrdFmts(HAB,USHORT);
BOOL   APIENTRY WinOpenClipbrd(HAB);
ULONG  APIENTRY WinQueryClipbrdData(HAB,USHORT);
BOOL   APIENTRY WinQueryClipbrdFmtInfo(HAB,USHORT,PUSHORT);
HWND   APIENTRY WinQueryClipbrdOwner(HAB,BOOL);
HWND   APIENTRY WinQueryClipbrdViewer(HAB,BOOL);
BOOL   APIENTRY WinSetClipbrdData(HAB,ULONG,USHORT,USHORT);
BOOL   APIENTRY WinSetClipbrdOwner(HAB,HWND);
BOOL   APIENTRY WinSetClipbrdViewer(HAB,HWND);

#endif

#ifdef INCL_WINMENUS

#define MIT_END      (-1)
#define MIT_NONE     (-1)
#define MIT_MEMERROR (-1)
#define MIT_ERROR    (-1)
#define MID_NONE     MIT_NONE
#define MID_ERROR    (-1)

#define MIS_TEXT            0x0001
#define MIS_BITMAP          0x0002
#define MIS_SEPARATOR       0x0004
#define MIS_OWNERDRAW       0x0008
#define MIS_SUBMENU         0x0010
#define MIS_MULTMENU        0x0020
#define MIS_SYSCOMMAND      0x0040
#define MIS_HELP            0x0080
#define MIS_STATIC          0x0100
#define MIS_BUTTONSEPARATOR 0x0200
#define MIS_BREAK           0x0400
#define MIS_BREAKSEPARATOR  0x0800
#define MIS_GROUP           0x1000
#define MIS_SINGLE          0x2000

#define MIA_NODISMISS 0x0020
#define MIA_FRAMED    0x1000
#define MIA_CHECKED   0x2000
#define MIA_DISABLED  0x4000
#define MIA_HILITED   0x8000

#define MS_ACTIONBAR    0x00000001L
#define MS_TITLEBUTTON  0x00000002L
#define MS_VERTICALFLIP 0x00000004L

#define WC_MENU ((PSZ)0xffff0004L)

#define MM_INSERTITEM          0x0180
#define MM_DELETEITEM          0x0181
#define MM_QUERYITEM           0x0182
#define MM_SETITEM             0x0183
#define MM_QUERYITEMCOUNT      0x0184
#define MM_STARTMENUMODE       0x0185
#define MM_ENDMENUMODE         0x0186
#define MM_DISMISSMENU         0x0187
#define MM_REMOVEITEM          0x0188
#define MM_SELECTITEM          0x0189
#define MM_QUERYSELITEMID      0x018a
#define MM_QUERYITEMTEXT       0x018b
#define MM_QUERYITEMTEXTLENGTH 0x018c
#define MM_SETITEMHANDLE       0x018d
#define MM_SETITEMTEXT         0x018e
#define MM_ITEMPOSITIONFROMID  0x018f
#define MM_ITEMIDFROMPOSITION  0x0190
#define MM_QUERYITEMATTR       0x0191
#define MM_SETITEMATTR         0x0192
#define MM_ISITEMVALID         0x0193

typedef struct _MENUITEM {
    SHORT  iPosition;
    USHORT afStyle;
    USHORT afAttribute;
    USHORT id;
    HWND   hwndSubMenu;
    ULONG  hItem;
} MENUITEM, FAR *PMENUITEM;

typedef struct _OWNERITEM {
    HWND   hwnd;
    HPS    hps;
    USHORT fsState;
    USHORT fsAttribute;
    USHORT fsStateOld;
    USHORT fsAttributeOld;
    RECTL  rclItem;
    SHORT  idItem;
    ULONG  hItem;
} OWNERITEM, FAR *POWNERITEM;

HWND APIENTRY WinCreateMenu(HWND,PVOID);
HWND APIENTRY WinLoadMenu(HWND,HMODULE,USHORT);

#endif

#ifdef INCL_WINSYS

#define SV_SWAPBUTTON          0
#define SV_DBLCLKTIME          1
#define SV_CXDBLCLK            2
#define SV_CYDBLCLK            3
#define SV_CXSIZEBORDER        4
#define SV_CYSIZEBORDER        5
#define SV_ALARM               6
#define SV_RESERVEDFIRST1      7
#define SV_RESERVEDLAST1       8
#define SV_CURSORRATE          9
#define SV_FIRSTSCROLLRATE     10
#define SV_SCROLLRATE          11
#define SV_NUMBEREDLISTS       12
#define SV_WARNINGFREQ         13
#define SV_NOTEFREQ            14
#define SV_ERRORFREQ           15
#define SV_WARNINGDURATION     16
#define SV_NOTEDURATION        17
#define SV_ERRORDURATION       18
#define SV_RESERVEDFIRST       19
#define SV_RESERVEDLAST        19
#define SV_CXSCREEN            20
#define SV_CYSCREEN            21
#define SV_CXVSCROLL           22
#define SV_CYHSCROLL           23
#define SV_CYVSCROLLARROW      24
#define SV_CXHSCROLLARROW      25
#define SV_CXBORDER            26
#define SV_CYBORDER            27
#define SV_CXDLGFRAME          28
#define SV_CYDLGFRAME          29
#define SV_CYTITLEBAR          30
#define SV_CYVSLIDER           31
#define SV_CXHSLIDER           32
#define SV_CXMINMAXBUTTON      33
#define SV_CYMINMAXBUTTON      34
#define SV_CYMENU              35
#define SV_CXFULLSCREEN        36
#define SV_CYFULLSCREEN        37
#define SV_CXICON              38
#define SV_CYICON              39
#define SV_CXPOINTER           40
#define SV_CYPOINTER           41
#define SV_DEBUG               42
#define SV_CMOUSEBUTTONS       43
#define SV_POINTERLEVEL        44
#define SV_CURSORLEVEL         45
#define SV_TRACKRECTLEVEL      46
#define SV_CTIMERS             47
#define SV_MOUSEPRESENT        48
#define SV_CXBYTEALIGN         49
#define SV_CYBYTEALIGN         50
#define SV_NOTRESERVED         56
#define SV_EXTRAKEYBEEP        57
#define SV_SETLIGHTS           58
#define SV_INSERTMODE          59
#define SV_MENUROLLDOWNDELAY   64
#define SV_MENUROLLUPDELAY     65
#define SV_ALTMNEMONIC         66
#define SV_TASKLISTMOUSEACCESS 67
#define SV_CSYSVALUES          68
#define SV_CPOINTERBUTTONS     69
#define SV_CXALIGN             70
#define SV_CYALIGN             71
#define SV_MNEMONICSENABLED    72

#define SYSCLR_BUTTONLIGHT           (-41L)
#define SYSCLR_BUTTONMIDDLE          (-40L)
#define SYSCLR_BUTTONDARK            (-39L)
#define SYSCLR_BUTTONDEFAULT         (-38L)
#define SYSCLR_TITLEBOTTOM           (-37L)
#define SYSCLR_SHADOW                (-36L)
#define SYSCLR_ICONTEXT              (-35L)
#define SYSCLR_DIALOGBACKGROUND      (-34L)
#define SYSCLR_HILITEFOREGROUND      (-33L)
#define SYSCLR_HILITEBACKGROUND      (-32L)
#define SYSCLR_INACTIVETITLETEXTBGND (-31L)
#define SYSCLR_ACTIVETITLETEXTBGND   (-30L)
#define SYSCLR_INACTIVETITLETEXT     (-29L)
#define SYSCLR_ACTIVETITLETEXT       (-28L)
#define SYSCLR_OUTPUTTEXT            (-27L)
#define SYSCLR_WINDOWSTATICTEXT      (-26L)
#define SYSCLR_SCROLLBAR             (-25L)
#define SYSCLR_BACKGROUND            (-24L)
#define SYSCLR_ACTIVETITLE           (-23L)
#define SYSCLR_INACTIVETITLE         (-22L)
#define SYSCLR_MENU                  (-21L)
#define SYSCLR_WINDOW                (-20L)
#define SYSCLR_WINDOWFRAME           (-19L)
#define SYSCLR_MENUTEXT              (-18L)
#define SYSCLR_WINDOWTEXT            (-17L)
#define SYSCLR_TITLETEXT             (-16L)
#define SYSCLR_ACTIVEBORDER          (-15L)
#define SYSCLR_INACTIVEBORDER        (-14L)
#define SYSCLR_APPWORKSPACE          (-13L)
#define SYSCLR_HELPBACKGROUND        (-12L)
#define SYSCLR_HELPTEXT              (-11L)
#define SYSCLR_HELPHILITE            (-10L)
#define SYSCLR_CSYSCOLORS            32L

#define PP_FOREGROUNDCOLOR              1L
#define PP_FOREGROUNDCOLORINDEX         2L
#define PP_BACKGROUNDCOLOR              3L
#define PP_BACKGROUNDCOLORINDEX         4L
#define PP_HILITEFOREGROUNDCOLOR        5L
#define PP_HILITEFOREGROUNDCOLORINDEX   6L
#define PP_HILITEBACKGROUNDCOLOR        7L
#define PP_HILITEBACKGROUNDCOLORINDEX   8L
#define PP_DISABLEDFOREGROUNDCOLOR      9L
#define PP_DISABLEDFOREGROUNDCOLORINDEX 10L
#define PP_DISABLEDBACKGROUNDCOLOR      11L
#define PP_DISABLEDBACKGROUNDCOLORINDEX 12L
#define PP_BORDERCOLOR                  13L
#define PP_BORDERCOLORINDEX             14L
#define PP_FONTNAMESIZE                 15L
#define PP_FONTHANDLE                   16L

#define QPF_NOINHERIT     0x0001
#define QPF_ID1COLORINDEX 0x0002
#define QPF_ID2COLORINDEX 0x0004
#define QPF_PURERGBCOLOR  0x0008
#define QPF_VALIDFLAGS    0x000F

typedef struct _PARAM {
    ULONG id;
    ULONG cb;
    BYTE  ab[1];
} PARAM, FAR  *PPARAM, NEAR *NPPARAM;

typedef struct _PRESPARAMS {
    ULONG   cb;
    PARAM   aparam[1];
} PRESPARAMS, FAR  *PPRESPARAMS, NEAR *NPPRESPARAMS;

ULONG APIENTRY WinQueryPresParam(HWND,ULONG,ULONG,PULONG,ULONG,PVOID,USHORT);
LONG  APIENTRY WinQuerySysColor(HWND,LONG,LONG);
LONG  APIENTRY WinQuerySysValue(HWND,SHORT);
BOOL  APIENTRY WinRemovePresParam(HWND,ULONG);
BOOL  APIENTRY WinSetPresParam(HWND,ULONG,ULONG,PVOID);
BOOL  APIENTRY WinSetSysValue(HWND,SHORT,LONG);
BOOL  APIENTRY WinSetSysColors(HWND,ULONG,ULONG,LONG,ULONG,PLONG);

#endif


#ifdef INCL_WINERRORS

#include <pmerr.h>

typedef ULONG   ERRORID;
typedef ERRORID FAR *PERRORID;

typedef struct _ERRINFO {
    USHORT  cbFixedErrInfo;
    ERRORID idError;
    USHORT  cDetailLevel;
    USHORT  offaoffszMsg;
    USHORT  offBinaryData;
} ERRINFO, FAR *PERRINFO;

BOOL     APIENTRY WinFreeErrorInfo(PERRINFO);
PERRINFO APIENTRY WinGetErrorInfo(HAB);
ERRORID  APIENTRY WinGetLastError(HAB);

#endif
