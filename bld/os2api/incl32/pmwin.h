/*
    OS/2 Presentation Manager window manager include file
    for 32-bit development.
*/


#define INCL_WININCLUDED

#ifdef INCL_WIN
    #define INCL_WINATOM
    #define INCL_WINBUTTONS
    #define INCL_WINCLIPBOARD
    #define INCL_WINCOUNTRY
    #define INCL_WINCURSORS
    #define INCL_WINDDE
    #define INCL_WINDIALOGS
    #define INCL_WINENTRYFIELDS
    #define INCL_WINERRORS
    #define INCL_WINFRAMECTLS
    #define INCL_WINFRAMEMGR
    #define INCL_WINHELP
    #define INCL_WINHOOKS
    #define INCL_WININPUT
    #define INCL_WINLISTBOXES
    #define INCL_WINMENUS
    #define INCL_WINMESSAGEMGR
    #define INCL_WINMLE
    #define INCL_WINPOINTERS
    #define INCL_WINPROGRAMLIST
    #define INCL_WINRECTANGLES
    #define INCL_WINSCROLLBARS
    #define INCL_WINSHELLDATA
    #define INCL_WINSTATICS
    #define INCL_WINSTDDLGS
    #define INCL_WINSWITCHLIST
    #define INCL_WINSYS
    #define INCL_WINTIMER
    #define INCL_WINTRACKRECT
    #define INCL_WINWINDOWMGR
#else
  #ifdef RC_INVOKED
    #define INCL_WININPUT
    #define INCL_WINDIALOGS
    #define INCL_WINSTATICS
    #define INCL_WINBUTTONS
    #define INCL_WINENTRYFIELDS
    #define INCL_WINLISTBOXES
    #define INCL_WINMENUS
    #define INCL_WINSCROLLBARS
    #define INCL_WINFRAMEMGR
    #define INCL_WINFRAMECTLS
    #define INCL_WINACCELERATORS
    #define INCL_WINPOINTERS
    #define INCL_WINMESSAGEMGR
    #define INCL_WINMLE
    #define INCL_WINHELP
    #define INCL_WINSTDDLGS
    #define INCL_WINSYS
  #endif
#endif

#ifdef INCL_ERRORS
  #define INCL_WINERRORS
#endif

#define MPVOID              ((MPARAM)0)
#define MPFROMP(p)          ((MPARAM)(VOID *)(p))
#define MPFROMHWND(hwnd)    ((MPARAM)(HWND)(hwnd))
#define MPFROMCHAR(ch)      ((MPARAM)(USHORT)(ch))
#define MPFROMSHORT(s)      ((MPARAM)(USHORT)(s))
#define MPFROM2SHORT(s1, s2)((MPARAM)MAKELONG(s1, s2))
#define MPFROMSH2CH(s, uch1, uch2)   ((MPARAM)MAKELONG(s, MAKESHORT(uch1, uch2)))
#define MPFROMLONG(l)       ((MPARAM)(ULONG)(l))
#define PVOIDFROMMP(mp)     ((VOID *)(mp))
#define HWNDFROMMP(mp)      ((HWND)(mp))
#define CHAR1FROMMP(mp)     ((UCHAR)(mp))
#define CHAR2FROMMP(mp)     ((UCHAR)((ULONG)mp >> 8))
#define CHAR3FROMMP(mp)     ((UCHAR)((ULONG)mp >> 16))
#define CHAR4FROMMP(mp)     ((UCHAR)((ULONG)mp >> 24))
#define SHORT1FROMMP(mp)    ((USHORT)(ULONG)(mp))
#define SHORT2FROMMP(mp)    ((USHORT)((ULONG)mp >> 16))
#define LONGFROMMP(mp)      ((ULONG)(mp))
#define MRFROMP(p)          ((MRESULT)(VOID *)(p))
#define MRFROMSHORT(s)      ((MRESULT)(USHORT)(s))
#define MRFROM2SHORT(s1, s2)((MRESULT)MAKELONG(s1, s2))
#define MRFROMLONG(l)       ((MRESULT)(ULONG)(l))
#define PVOIDFROMMR(mr)     ((VOID *)(mr))
#define SHORT1FROMMR(mr)    ((USHORT)((ULONG)mr))
#define SHORT2FROMMR(mr)    ((USHORT)((ULONG)mr >> 16))
#define LONGFROMMR(mr)      ((ULONG)(mr))

#define HWND_DESKTOP       (HWND)1
#define HWND_OBJECT        (HWND)2
#define HWND_TOP           (HWND)3
#define HWND_BOTTOM        (HWND)4
#define HWND_THREADCAPTURE (HWND)5

#define WC_FRAME           ((PSZ)0xffff0001)
#define WC_COMBOBOX        ((PSZ)0xffff0002)
#define WC_BUTTON          ((PSZ)0xffff0003)
#define WC_MENU            ((PSZ)0xffff0004)
#define WC_STATIC          ((PSZ)0xffff0005)
#define WC_ENTRYFIELD      ((PSZ)0xffff0006)
#define WC_LISTBOX         ((PSZ)0xffff0007)
#define WC_SCROLLBAR       ((PSZ)0xffff0008)
#define WC_TITLEBAR        ((PSZ)0xffff0009)
#define WC_MLE             ((PSZ)0xffff000A)
#define WC_APPSTAT         ((PSZ)0xffff0010)
#define WC_KBDSTAT         ((PSZ)0xffff0011)
#define WC_PECIC           ((PSZ)0xffff0012)
#define WC_DBE_KKPOPUP     ((PSZ)0xffff0013)
#define WC_SPINBUTTON      ((PSZ)0xffff0020)
#define WC_CONTAINER       ((PSZ)0xffff0025)
#define WC_SLIDER          ((PSZ)0xffff0026)
#define WC_VALUESET        ((PSZ)0xffff0027)
#define WC_NOTEBOOK        ((PSZ)0xffff0028)
#define WC_PENFIRST        ((PSZ)0xffff0029)
#define WC_PENLAST         ((PSZ)0xffff002C)
#define WC_MMPMFIRST       ((PSZ)0xffff0040)
#define WC_CIRCULARSLIDER  ((PSZ)0xffff0041)
#define WC_MMPMLAST        ((PSZ)0xffff004f)
#define WC_PRISTDDLGFIRST  ((PSZ)0xffff0050)
#define WC_PRISTDDLGLAST   ((PSZ)0xffff0057)
#define WC_PUBSTDDLGFIRST  ((PSZ)0xffff0058)
#define WC_PUBSTDDLGLAST   ((PSZ)0xffff005f)

#define WS_VISIBLE         0x80000000
#define WS_DISABLED        0x40000000
#define WS_CLIPCHILDREN    0x20000000
#define WS_CLIPSIBLINGS    0x10000000
#define WS_PARENTCLIP      0x08000000
#define WS_SAVEBITS        0x04000000
#define WS_SYNCPAINT       0x02000000
#define WS_MINIMIZED       0x01000000
#define WS_MAXIMIZED       0x00800000
#define WS_ANIMATE         0x00400000

#define WS_GROUP           0x00010000
#define WS_TABSTOP         0x00020000
#define WS_MULTISELECT     0x00040000

#define CS_MOVENOTIFY      0x00000001
#define CS_SIZEREDRAW      0x00000004
#define CS_HITTEST         0x00000008
#define CS_PUBLIC          0x00000010
#define CS_FRAME           0x00000020
#define CS_SYNCPAINT       0x02000000
#define CS_SAVEBITS        0x04000000
#define CS_PARENTCLIP      0x08000000
#define CS_CLIPSIBLINGS    0x10000000
#define CS_CLIPCHILDREN    0x20000000

#define FM_TYPE_FIXED     0x0001
#define FM_TYPE_LICENSED  0x0002
#define FM_TYPE_KERNING   0x0004
#define FM_TYPE_DBCS      0x0010
#define FM_TYPE_MBCS      0x0018
#define FM_TYPE_UNICODE   0x0040
#define FM_TYPE_64K       0x8000
#define FM_TYPE_ATOMS     0x4000
#define FM_TYPE_FAMTRUNC  0x2000
#define FM_TYPE_FACETRUNC 0x1000

#define FM_DEFN_OUTLINE   0x0001
#define FM_DEFN_IFI       0x0002
#define FM_DEFN_WIN       0x0004
#define FM_DEFN_GENERIC   0x8000

#define FM_DEFN_LATIN1    0x0010
#define FM_DEFN_PC        0x0020
#define FM_DEFN_LATIN2    0x0040
#define FM_DEFN_CYRILLIC  0x0080
#define FM_DEFN_HEBREW    0x0100
#define FM_DEFN_GREEK     0x0200
#define FM_DEFN_ARABIC    0x0400
#define FM_DEFN_UGLEXT    0x0800
#define FM_DEFN_KANA      0x1000
#define FM_DEFN_THAI      0x2000

#define FM_DEFN_UGL383    0x0070
#define FM_DEFN_UGL504    0x00F0
#define FM_DEFN_UGL767    0x0FF0
#define FM_DEFN_UGL1105   0x3FF0

#define FM_SEL_ITALIC         0x0001
#define FM_SEL_UNDERSCORE     0x0002
#define FM_SEL_NEGATIVE       0x0004
#define FM_SEL_OUTLINE        0x0008
#define FM_SEL_STRIKEOUT      0x0010
#define FM_SEL_BOLD           0x0020
#define FM_SEL_ISO9241_TESTED 0x0040

#define FM_SEL_JAPAN    0x1000
#define FM_SEL_TAIWAN   0x2000
#define FM_SEL_CHINA    0x4000
#define FM_SEL_KOREA    0x8000
#define FM_SEL_DBCSMASK 0xF000

#define FM_ISO_9518_640  0x01
#define FM_ISO_9515_640  0x02
#define FM_ISO_9515_1024 0x04
#define FM_ISO_9517_640  0x08
#define FM_ISO_9517_1024 0x10

#define FM_CAP_NOMIX         0x0001
#define FM_CAP_NO_COLOR      0x0002
#define FM_CAP_NO_MIXEDMODES 0x0004
#define FM_CAP_NO_HOLLOW     0x0008

#define FATTR_SEL_ITALIC          0x0001
#define FATTR_SEL_UNDERSCORE      0x0002
#define FATTR_SEL_OUTLINE         0x0008
#define FATTR_SEL_STRIKEOUT       0x0010
#define FATTR_SEL_BOLD            0x0020
#define FATTR_SEL_MUST_COLOR      0x0100
#define FATTR_SEL_MUST_MIXEDMODES 0x0200
#define FATTR_SEL_MUST_HOLLOW     0x0400

#define FATTR_TYPE_KERNING     0x0004
#define FATTR_TYPE_MBCS        0x0008
#define FATTR_TYPE_DBCS        0x0010
#define FATTR_TYPE_ANTIALIASED 0x0020

#define FATTR_FONTUSE_NOMIX         0x0002
#define FATTR_FONTUSE_OUTLINE       0x0004
#define FATTR_FONTUSE_TRANSFORMABLE 0x0008

#define FACESIZE 32

#define WRECT RECTL

typedef LHANDLE HWND, *PHWND;
typedef LHANDLE HAB, *PHAB;

typedef LONG    FIXED, *PFIXED;
typedef LONG    COLOR, *PCOLOR;
typedef LHANDLE HACCEL;
typedef LHANDLE HBITMAP, *PHBITMAP;
typedef LHANDLE HDC, *PHDC;
typedef LHANDLE HMF, *PHMF;
typedef LHANDLE HPAL, *PHPAL;
typedef LHANDLE HPOINTER, *PHPOINTER;
typedef LHANDLE HPS, *PHPS;
typedef LHANDLE HRGN, *PHRGN;
typedef VOID    *MPARAM, **PMPARAM;
typedef VOID    *MRESULT, **PMRESULT;

typedef CHAR STR8[8];
typedef STR8 *PSTR8;

typedef MRESULT (APIENTRY FNWP)(HWND, ULONG, MPARAM, MPARAM);
typedef FNWP *PFNWP;

typedef struct _MATRIXLF {
    FIXED fxM11;
    FIXED fxM12;
    LONG  lM13;
    FIXED fxM21;
    FIXED fxM22;
    LONG  lM23;
    LONG  lM31;
    LONG  lM32;
    LONG  lM33;
} MATRIXLF, *PMATRIXLF;

typedef struct _POINTL {
    LONG  x;
    LONG  y;
} POINTL, *PPOINTL;

typedef struct _POINTS {
    SHORT x;
    SHORT y;
} POINTS, *PPOINTS;

typedef struct _RECTL {
    LONG xLeft;
    LONG yBottom;
    LONG xRight;
    LONG yTop;
} RECTL, *PRECTL;

typedef struct _FATTRS {
    USHORT usRecordLength;
    USHORT fsSelection;
    LONG   lMatch;
    CHAR   szFacename[FACESIZE];
    USHORT idRegistry;
    USHORT usCodePage;
    LONG   lMaxBaselineExt;
    LONG   lAveCharWidth;
    USHORT fsType;
    USHORT fsFontUse;
} FATTRS, *PFATTRS;

typedef struct _PANOSE {
    BYTE bFamilyType;
    BYTE bSerifStyle;
    BYTE bWeight;
    BYTE bProportion;
    BYTE bContrast;
    BYTE bStrokeVariation;
    BYTE bArmStyle;
    BYTE bLetterform;
    BYTE bMidline;
    BYTE bXHeight;
    BYTE fbPassedISO;
    BYTE fbFailedISO;
} PANOSE, *PPANOSE;

typedef struct _FONTMETRICS {
    CHAR   szFamilyname[FACESIZE];
    CHAR   szFacename[FACESIZE];
    USHORT idRegistry;
    USHORT usCodePage;
    LONG   lEmHeight;
    LONG   lXHeight;
    LONG   lMaxAscender;
    LONG   lMaxDescender;
    LONG   lLowerCaseAscent;
    LONG   lLowerCaseDescent;
    LONG   lInternalLeading;
    LONG   lExternalLeading;
    LONG   lAveCharWidth;
    LONG   lMaxCharInc;
    LONG   lEmInc;
    LONG   lMaxBaselineExt;
    SHORT  sCharSlope;
    SHORT  sInlineDir;
    SHORT  sCharRot;
    USHORT usWeightClass;
    USHORT usWidthClass;
    SHORT  sXDeviceRes;
    SHORT  sYDeviceRes;
    SHORT  sFirstChar;
    SHORT  sLastChar;
    SHORT  sDefaultChar;
    SHORT  sBreakChar;
    SHORT  sNominalPointSize;
    SHORT  sMinimumPointSize;
    SHORT  sMaximumPointSize;
    USHORT fsType;
    USHORT fsDefn;
    USHORT fsSelection;
    USHORT fsCapabilities;
    LONG   lSubscriptXSize;
    LONG   lSubscriptYSize;
    LONG   lSubscriptXOffset;
    LONG   lSubscriptYOffset;
    LONG   lSuperscriptXSize;
    LONG   lSuperscriptYSize;
    LONG   lSuperscriptXOffset;
    LONG   lSuperscriptYOffset;
    LONG   lUnderscoreSize;
    LONG   lUnderscorePosition;
    LONG   lStrikeoutSize;
    LONG   lStrikeoutPosition;
    SHORT  sKerningPairs;
    SHORT  sFamilyClass;
    LONG   lMatch;
    LONG   FamilyNameAtom;
    LONG   FaceNameAtom;
    PANOSE panose;
} FONTMETRICS, *PFONTMETRICS;

#if defined(INCL_WINATOM)

typedef ULONG ATOM;
typedef LHANDLE HATOMTBL;

ATOM   APIENTRY WinAddAtom(HATOMTBL hatomtblAtomTbl, PCSZ AtomName);
ATOM   APIENTRY WinFindAtom(HATOMTBL hatomtblAtomTbl, PCSZ pszAtomName);

#endif

#if defined(INCL_WINBUTTONS)

#define BS_PUSHBUTTON          0
#define BS_CHECKBOX            1
#define BS_AUTOCHECKBOX        2
#define BS_RADIOBUTTON         3
#define BS_AUTORADIOBUTTON     4
#define BS_3STATE              5
#define BS_AUTO3STATE          6
#define BS_USERBUTTON          7
#define BS_NOTEBOOKBUTTON      8
#define BS_PRIMARYSTYLES  0x000F

#define BS_TEXT           0x0010
#define BS_MINIICON       0x0020
#define BS_BITMAP         0x0040
#define BS_ICON           0x0080
#define BS_HELP           0x0100
#define BS_SYSCOMMAND     0x0200
#define BS_DEFAULT        0x0400
#define BS_NOPOINTERFOCUS 0x0800
#define BS_NOBORDER       0x1000
#define BS_NOCURSORSELECT 0x2000
#define BS_AUTOSIZE       0x4000

#define BN_CLICKED    1
#define BN_DBLCLICKED 2
#define BN_PAINT      3

#define BDS_HILITED  0x0100
#define BDS_DISABLED 0x0200
#define BDS_DEFAULT  0x0400

#define BM_CLICK           0x0120
#define BM_QUERYCHECKINDEX 0x0121
#define BM_QUERYHILITE     0x0122
#define BM_SETHILITE       0x0123
#define BM_QUERYCHECK      0x0124
#define BM_SETCHECK        0x0125
#define BM_SETDEFAULT      0x0126
#define BM_AUTOSIZE        0x0128

#pragma pack(2)

typedef struct _BTNCDATA {
    USHORT  cb;
    USHORT  fsCheckState;
    USHORT  fsHiliteState;
    LHANDLE hImage;
} BTNCDATA, *PBTNCDATA;

#pragma pack()

typedef struct _USERBUTTON {
    HWND  hwnd;
    HPS   hps;
    ULONG fsState;
    ULONG fsStateOld;
} USERBUTTON, *PUSERBUTTON;

#endif

#if defined(INCL_WINCLIPBOARD)

#define CF_TEXT         1
#define CF_BITMAP       2
#define CF_DSPTEXT      3
#define CF_DSPBITMAP    4
#define CF_METAFILE     5
#define CF_DSPMETAFILE  6
#define CF_PALETTE      9
#define CF_MMPMFIRST   10
#define CF_MMPMLAST    19

#define CFI_OWNERFREE    0x0001
#define CFI_OWNERDISPLAY 0x0002
#define CFI_POINTER      0x0400
#define CFI_HANDLE       0x0200

#define WM_RENDERFMT        0x0060
#define WM_RENDERALLFMTS    0x0061
#define WM_DESTROYCLIPBOARD 0x0062
#define WM_PAINTCLIPBOARD   0x0063
#define WM_SIZECLIPBOARD    0x0064
#define WM_HSCROLLCLIPBOARD 0x0065
#define WM_VSCROLLCLIPBOARD 0x0066
#define WM_DRAWCLIPBOARD    0x0067

BOOL   APIENTRY WinCloseClipbrd(HAB hab);
BOOL   APIENTRY WinEmptyClipbrd(HAB hab);
BOOL   APIENTRY WinOpenClipbrd(HAB hab);
ULONG  APIENTRY WinQueryClipbrdData(HAB hab, ULONG fmt);
BOOL   APIENTRY WinQueryClipbrdFmtInfo(HAB hab, ULONG fmt, PULONG prgfFmtInfo);
HWND   APIENTRY WinQueryClipbrdOwner(HAB hab);
HWND   APIENTRY WinQueryClipbrdViewer(HAB hab);
BOOL   APIENTRY WinSetClipbrdData(HAB hab, ULONG ulh, ULONG ulfmt, ULONG flFmtInfo);
BOOL   APIENTRY WinSetClipbrdOwner(HAB hab, HWND hwnd);
BOOL   APIENTRY WinSetClipbrdViewer(HAB hab, HWND hwndNewClipViewer);

#endif

#if defined(INCL_WINCURSORS)

BOOL  APIENTRY  WinShowCursor(HWND hwnd, BOOL fShow);

#endif

#if defined(INCL_WINWINDOWMGR) || !defined(INCL_NOCOMMON)

#define QW_NEXT       0
#define QW_PREV       1
#define QW_TOP        2
#define QW_BOTTOM     3
#define QW_OWNER      4
#define QW_PARENT     5
#define QW_NEXTTOP    6
#define QW_PREVTOP    7
#define QW_FRAMEOWNER 8

#define AWP_MINIMIZED  0x00010000
#define AWP_MAXIMIZED  0x00020000
#define AWP_RESTORED   0x00040000
#define AWP_ACTIVATE   0x00080000
#define AWP_DEACTIVATE 0x00100000

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
#define SWP_NOAUTOCLOSE     0x8000

#define DT_LEFT            0x00000000
#define DT_QUERYEXTENT     0x00000002
#define DT_UNDERSCORE      0x00000010
#define DT_STRIKEOUT       0x00000020
#define DT_TEXTATTRS       0x00000040
#define DT_EXTERNALLEADING 0x00000080
#define DT_CENTER          0x00000100
#define DT_RIGHT           0x00000200
#define DT_TOP             0x00000000
#define DT_VCENTER         0x00000400
#define DT_BOTTOM          0x00000800
#define DT_HALFTONE        0x00001000
#define DT_MNEMONIC        0x00002000
#define DT_WORDBREAK       0x00004000
#define DT_ERASERECT       0x00008000

#define PSF_LOCKWINDOWUPDATE 0x0001
#define PSF_CLIPUPWARDS      0x0002
#define PSF_CLIPDOWNWARDS    0x0004
#define PSF_CLIPSIBLINGS     0x0008
#define PSF_CLIPCHILDREN     0x0010
#define PSF_PARENTCLIP       0x0020

#define SW_SCROLLCHILDREN 1
#define SW_INVALIDATERGN  2

#define DBM_NORMAL     0x0000
#define DBM_INVERT     0x0001
#define DBM_HALFTONE   0x0002
#define DBM_STRETCH    0x0004
#define DBM_IMAGEATTRS 0x0008
#define DBM_XOR        0x0010

#define DB_PATCOPY     0x0000
#define DB_PATINVERT   0x0001
#define DB_DESTINVERT  0x0002
#define DB_AREAMIXMODE 0x0003
#define DB_ROP         0x0007
#define DB_INTERIOR    0x0008
#define DB_AREAATTRS   0x0010
#define DB_STANDARD    0x0100
#define DB_DLGBORDER   0x0200

typedef struct _SWP {
    ULONG fl;
    LONG  cy;
    LONG  cx;
    LONG  y;
    LONG  x;
    HWND  hwndInsertBehind;
    HWND  hwnd;
    ULONG ulReserved1;
    ULONG ulReserved2;
} SWP, *PSWP;

HPS     APIENTRY WinBeginPaint(HWND hwnd, HPS hps, PRECTL prclPaint);
BOOL    APIENTRY WinCheckMenuItem(HWND hwndMenu, USHORT usId, BOOL fCheck);
HWND    APIENTRY WinCreateWindow(HWND hwndParent, PCSZ pszClass, PCSZ pszName, ULONG flStyle,
                   LONG x, LONG y, LONG cx, LONG cy, HWND hwndOwner,
                   HWND hwndInsertBehind, ULONG id, PVOID pCtlData, PVOID pPresParams);
MRESULT APIENTRY WinDefWindowProc(HWND hwnd, ULONG ulMsgid, MPARAM mpParam1, MPARAM mpParam2);
BOOL    APIENTRY WinDestroyWindow(HWND hwnd);
BOOL    APIENTRY WinDrawBitmap(HPS hpsDst, HBITMAP hbm, PRECTL pwrcSrc, PPOINTL pptlDst,
                   LONG clrFore, LONG clrBack, ULONG fl);
BOOL    APIENTRY WinDrawBorder(HPS hps, PRECTL prcl, LONG cx, LONG cy, LONG clrFore,
                   LONG clrBack, ULONG flCmd);
LONG    APIENTRY WinDrawText(HPS hps, LONG cchText, PCH lpchText,
                   PRECTL prcl, LONG clrFore, LONG clrBack, ULONG flCmd);
BOOL    APIENTRY WinEnableWindow(HWND hwnd, BOOL fNewEnabled);
BOOL    APIENTRY WinEnableWindowUpdate(HWND hwnd, BOOL fEnable);
BOOL    APIENTRY WinEndPaint(HPS hps);
BOOL    APIENTRY WinFillRect(HPS hps, PRECTL prcl, LONG lColor);
HPS     APIENTRY WinGetClipPS(HWND hwnd, HWND hwndClipWindow, ULONG ulClipflags);
HPS     APIENTRY WinGetPS(HWND hwnd);
HAB     APIENTRY WinInitialize(ULONG fsOptions);
BOOL    APIENTRY WinInvalidateRect(HWND hwnd, PRECTL pwrc, BOOL fIncludeChildren);
BOOL    APIENTRY WinInvalidateRegion(HWND hwnd, HRGN hrgn, BOOL fIncludeChildren);
BOOL    APIENTRY WinInvertRect(HPS hps, PRECTL prclRect);
BOOL    APIENTRY WinIsChild(HWND hwnd, HWND hwndParent);
BOOL    APIENTRY WinIsControlEnabled(HWND hwndDlg, USHORT usId);
BOOL    APIENTRY WinIsMenuItemChecked(HWND hwndMenu, USHORT usId);
BOOL    APIENTRY WinIsMenuItemEnabled(HWND hwndMenu, USHORT usId);
BOOL    APIENTRY WinIsMenuItemValid(HWND hwndMenu, USHORT usId);
BOOL    APIENTRY WinIsThreadActive(HAB hab);
BOOL    APIENTRY WinIsWindow(HAB hab, HWND hwnd);
BOOL    APIENTRY WinIsWindowEnabled(HWND hwnd);
BOOL    APIENTRY WinIsWindowShowing(HWND hwnd);
BOOL    APIENTRY WinIsWindowVisible(HWND hwnd);
LONG    APIENTRY WinLoadMessage(HAB hab, HMODULE hmodMod, ULONG ulId, LONG lcchMax, PSZ pBuffer);
LONG    APIENTRY WinLoadString(HAB hab, HMODULE hmodMod, ULONG ulId, LONG lcchMax, PSZ pBuffer);
LONG    APIENTRY WinMultWindowFromIDs(HWND hwndParent, PHWND prghwnd,
                   ULONG idFirst, ULONG idLast);
HDC     APIENTRY WinOpenWindowDC(HWND hwnd);
BOOL    APIENTRY WinPopupMenu(HWND hwndParent, HWND hwndOwner, HWND hwndMenu,
                   LONG x, LONG y, LONG idItem, ULONG fs);
HAB     APIENTRY WinQueryAnchorBlock(HWND hwnd);
HWND    APIENTRY WinQueryDesktopWindow(HAB hab, HDC hdc);
ULONG   APIENTRY WinQueryVersion(HAB hab);
HWND    APIENTRY WinQueryWindow(HWND hwnd, LONG lCode);
BOOL    APIENTRY WinQueryWindowPos(HWND hwnd, PSWP pswp);
BOOL    APIENTRY WinQueryWindowProcess(HWND hwnd, PPID ppid, PTID ptid);
BOOL    APIENTRY WinQueryWindowRect(HWND hwnd, PRECTL prclDest);
LONG    APIENTRY WinQueryWindowText(HWND hwnd, LONG lLength, PCH pun);
LONG    APIENTRY WinQueryWindowTextLength(HWND hwnd);
BOOL    APIENTRY WinRegisterClass(HAB hab, PCSZ pszClassName, PFNWP pfnWndProc,
                   ULONG flStyle, ULONG cbWindowData);
BOOL    APIENTRY WinReleasePS(HPS hps);
LONG    APIENTRY WinScrollWindow(HWND hwnd, LONG lDx, LONG lDy, PRECTL prclScroll,
                   PRECTL prclClip, HRGN hrgnUpdateRgn, PRECTL prclUpdate, ULONG flOptions);
MRESULT APIENTRY WinSendMsg(HWND hwnd, ULONG ulMsgid, MPARAM mpParam1, MPARAM mpParam2);
BOOL    APIENTRY WinSetActiveWindow(HWND hwndDeskTop, HWND hwnd);
BOOL    APIENTRY WinSetMultWindowPos(HAB hab, PSWP pswp, ULONG cswp);
BOOL    APIENTRY WinSetOwner(HWND hwnd, HWND hwndNewOwner);
BOOL    APIENTRY WinSetParent(HWND hwnd, HWND hwndNewParent, BOOL fRedraw);
BOOL    APIENTRY WinSetSysModalWindow(HWND hwndDesktop, HWND hwnd);
BOOL    APIENTRY WinSetWindowPos(HWND hwnd, HWND hwndInsertBehind, LONG x, LONG y,
                   LONG cx, LONG cy, ULONG fl);
BOOL    APIENTRY WinSetWindowText(HWND hwnd, PCSZ pszString);
BOOL    APIENTRY WinShowWindow(HWND hwnd, BOOL fNewVisibility);
BOOL    APIENTRY WinTerminate(HAB hab);
BOOL    APIENTRY WinUpdateWindow(HWND hwnd);
HWND    APIENTRY WinWindowFromID(HWND hwndParent, ULONG id);

#endif

#if defined(INCL_WINWINDOWMGR)

#define QCRGN_ERROR          0
#define QCRGN_OK             1
#define QCRGN_NO_CLIP_REGION 2

#define QWS_USER 0
#define QWS_ID   (-1)
#define QWS_MIN  (-1)

#define QWL_USER     0
#define QWL_STYLE    (-2)
#define QWP_PFNWP    (-3)
#define QWL_HMQ      (-4)
#define QWL_RESERVED (-5)
#define QWL_PENDATA  (-7)
#define QWL_BD_ATTR  (-9)
#define QWL_BD_STAT  (-10)
#define QWL_KBDLAYER (-11)
#define QWL_MIN      (-11)

#define QWL_HHEAP         0x0004
#define QWL_HWNDFOCUSSAVE 0x0018
#define QWL_DEFBUTTON     0x0040
#define QWL_PSSCBLK       0x0048
#define QWL_PFEPBLK       0x004c
#define QWL_PSTATBLK      0x0050

#define QWS_FLAGS     0x0008
#define QWS_RESULT    0x000a
#define QWS_XRESTORE  0x000c
#define QWS_YRESTORE  0x000e
#define QWS_CXRESTORE 0x0010
#define QWS_CYRESTORE 0x0012
#define QWS_XMINIMIZE 0x0014
#define QWS_YMINIMIZE 0x0016

typedef LHANDLE HENUM;

typedef struct _CLASSINFO {
    ULONG     flClassStyle;
    PFNWP     pfnWindowProc;
    ULONG     cbWindowData;
} CLASSINFO, *PCLASSINFO;

typedef struct _CREATESTRUCT {
    PVOID pPresParams;
    PVOID pCtlData;
    ULONG id;
    HWND  hwndInsertBehind;
    HWND  hwndOwner;
    LONG  cy;
    LONG  cx;
    LONG  y;
    LONG  x;
    ULONG flStyle;
    PSZ   pszText;
    PSZ   pszClass;
    HWND  hwndParent;
} CREATESTRUCT, *PCREATESTRUCT;

HENUM   APIENTRY WinBeginEnumWindows(HWND);
BOOL    APIENTRY WinEndEnumWindows(HENUM);
LONG    APIENTRY WinExcludeUpdateRegion(HPS,HWND);
HWND    APIENTRY WinGetNextWindow(HENUM);
HPS     APIENTRY WinGetScreenPS(HWND);
BOOL    APIENTRY WinLockVisRegions(HWND,BOOL);
BOOL    APIENTRY WinLockWindowUpdate(HWND,HWND);
BOOL    APIENTRY WinMapWindowPoints(HWND,HWND,PPOINTL,LONG);
HWND    APIENTRY WinQueryActiveWindow(HWND);
BOOL    APIENTRY WinQueryClassInfo(HAB,PCSZ,PCLASSINFO);
LONG    APIENTRY WinQueryClassName(HWND,LONG,PCH);
LONG    APIENTRY WinQueryClipRegion(HWND,HRGN);
HWND    APIENTRY WinQuerySysModalWindow(HWND);
BOOL    APIENTRY WinQueryUpdateRect(HWND,PRECTL);
LONG    APIENTRY WinQueryUpdateRegion(HWND,HRGN);
HDC     APIENTRY WinQueryWindowDC(HWND);
PVOID   APIENTRY WinQueryWindowPtr(HWND,LONG);
ULONG   APIENTRY WinQueryWindowULong(HWND,LONG);
USHORT  APIENTRY WinQueryWindowUShort(HWND,LONG);
BOOL    APIENTRY WinSetClipRegion(HWND,HRGN);
BOOL    APIENTRY WinSetSysModalWindow(HWND,HWND);
BOOL    APIENTRY WinSetWindowBits(HWND,LONG,ULONG,ULONG);
BOOL    APIENTRY WinSetWindowPtr(HWND,LONG,PVOID);
BOOL    APIENTRY WinSetWindowULong(HWND,LONG,ULONG);
BOOL    APIENTRY WinSetWindowUShort(HWND,LONG,USHORT);
PFNWP   APIENTRY WinSubclassWindow(HWND,PFNWP);
BOOL    APIENTRY WinValidateRect(HWND,PRECTL,BOOL);
BOOL    APIENTRY WinValidateRegion(HWND,HRGN,BOOL);
HWND    APIENTRY WinWindowFromDC(HDC);
HWND    APIENTRY WinWindowFromPoint(HWND,PPOINTL,BOOL);

#endif

#if defined(INCL_WINMESSAGEMGR) || !defined(INCL_NOCOMMON)

#define PM_REMOVE   1
#define PM_NOREMOVE 0

#define CMDSRC_PUSHBUTTON  1
#define CMDSRC_MENU        2
#define CMDSRC_ACCELERATOR 3
#define CMDSRC_FONTDLG     4
#define CMDSRC_FILEDLG     5
#define CMDSRC_PRINTDLG    6
#define CMDSRC_COLORDLG    7
#define CMDSRC_OTHER       0

#define WM_NULL                 0x0000
#define WM_CREATE               0x0001
#define WM_DESTROY              0x0002
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
#define WM_QUERYDLGCODE         0x003a
#define WM_INITDLG              0x003b
#define WM_SUBSTITUTESTRING     0x003c
#define WM_MATCHMNEMONIC        0x003d
#define WM_SAVEAPPLICATION      0x003e
#define WM_SEMANTICEVENT        0x0490
#define WM_HELPBASE             0x0F00
#define WM_HELPTOP              0x0FFF
#define WM_USER                 0x1000

typedef LHANDLE HMQ, *PHMQ;

typedef struct _QMSG {
    HWND   hwnd;
    ULONG  msg;
    MPARAM mp1;
    MPARAM mp2;
    ULONG  time;
    POINTL ptl;
    ULONG  reserved;
} QMSG, *PQMSG;

HMQ     APIENTRY WinCreateMsgQueue(HAB,LONG);
BOOL    APIENTRY WinDestroyMsgQueue(HMQ);
MRESULT APIENTRY WinDispatchMsg(HAB,PQMSG);
BOOL    APIENTRY WinGetMsg(HAB,PQMSG,HWND,ULONG,ULONG);
BOOL    APIENTRY WinPeekMsg(HAB,PQMSG,HWND,ULONG,ULONG,ULONG);
BOOL    APIENTRY WinPostMsg(HWND,ULONG,MPARAM,MPARAM);

#endif

#if defined(INCL_WINMESSAGEMGR)

BOOL    APIENTRY WinBroadcastMsg(HWND,ULONG,MPARAM,MPARAM,ULONG);
BOOL    APIENTRY WinCancelShutdown(HMQ,BOOL);
APIRET  APIENTRY WinRequestMutexSem(HMTX,ULONG);
APIRET  APIENTRY WinWaitEventSem(HEV,ULONG);
BOOL    APIENTRY WinWaitMsg(HAB,ULONG,ULONG);
APIRET  APIENTRY WinWaitMuxWaitSem(HMUX,ULONG,PULONG);
BOOL    APIENTRY WinPostQueueMsg(HMQ,ULONG,MPARAM,MPARAM);
BOOL    APIENTRY WinQueryMsgPos(HAB,PPOINTL);
BOOL    APIENTRY WinQueryMsgTime(HAB);

#endif

#if defined(INCL_WINCURSORS)

#define CURSOR_SOLID       0x0000
#define CURSOR_HALFTONE    0x0001
#define CURSOR_FRAME       0x0002
#define CURSOR_FLASH       0x0004
#define CURSOR_SETPOS      0x8000
#define CURSOR_BIDI_FIRST  0x0100
#define CURSOR_BIDI_LAST   0x0200

typedef struct _CURSORINFO {
    HWND  hwnd;
    LONG  x;
    LONG  y;
    LONG  cx;
    LONG  cy;
    ULONG fs;
    RECTL rclClip;
} CURSORINFO, *PCURSORINFO;

BOOL   APIENTRY WinCreateCursor(HWND hwnd, LONG lx, LONG ly, LONG lcx, LONG lcy,
                   ULONG ulrgf, PRECTL prclClip);
BOOL   APIENTRY WinDestroyCursor(HWND hwnd);

#endif

#if defined(INCL_WINDDE)

#define DDE_FACK         0x0001
#define DDE_FBUSY        0x0002
#define DDE_FNODATA      0x0004
#define DDE_FACKREQ      0x0008
#define DDE_FRESPONSE    0x0010
#define DDE_NOTPROCESSED 0x0020
#define DDE_FRESERVED    0x00C0
#define DDE_FAPPSTATUS   0xFF00

#define DDEPM_RETRY  1
#define DDEPM_NOFREE 2

#define DDEFMT_TEXT  1

#define DDECTXT_CASESENSITIVE 1

#define DDES_PSZITEMNAME(pddes)  (((PSZ)pddes) + ((PDDESTRUCT)pddes)->offszItemName)
#define DDES_PABDATA(pddes)      (((PBYTE)pddes) + ((PDDESTRUCT)pddes)->offabData)
#define DDEI_PCONVCONTEXT(pddei) ((PCONVCONTEXT)((PBYTE)pddei + pddei->offConvContext))

#define WM_DDE_FIRST       0x00A0
#define WM_DDE_INITIATE    0x00A0
#define WM_DDE_REQUEST     0x00A1
#define WM_DDE_ACK         0x00A2
#define WM_DDE_DATA        0x00A3
#define WM_DDE_ADVISE      0x00A4
#define WM_DDE_UNADVISE    0x00A5
#define WM_DDE_POKE        0x00A6
#define WM_DDE_EXECUTE     0x00A7
#define WM_DDE_TERMINATE   0x00A8
#define WM_DDE_INITIATEACK 0x00A9
#define WM_DDE_LAST        0x00AF

typedef struct _DDESTRUCT {
    ULONG  cbData;
    USHORT fsStatus;
    USHORT usFormat;
    USHORT offszItemName;
    USHORT offabData;
} DDESTRUCT, *PDDESTRUCT;

typedef struct _CONVCONTEXT {
    ULONG  cb;
    ULONG fsContext;
    ULONG idCountry;
    ULONG usCodepage;
    ULONG usLangID;
    ULONG usSubLangID;
} CONVCONTEXT, *PCONVCONTEXT;

typedef struct _DDEINIT {
    ULONG cb;
    PSZ   pszAppName;
    PSZ   pszTopic;
    ULONG offConvContext;
} DDEINIT, *PDDEINIT;

BOOL    APIENTRY WinDdeInitiate(HWND,PCSZ,PCSZ,PCONVCONTEXT);
BOOL    APIENTRY WinDdePostMsg(HWND,HWND,ULONG,PDDESTRUCT,ULONG);
MRESULT APIENTRY WinDdeRespond(HWND,HWND,PCSZ,PCSZ,PCONVCONTEXT);

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

#define MBID_OK             1
#define MBID_CANCEL         2
#define MBID_ABORT          3
#define MBID_RETRY          4
#define MBID_IGNORE         5
#define MBID_YES            6
#define MBID_NO             7
#define MBID_HELP           8
#define MBID_ENTER          9
#define MBID_ERROR          (-1)

#define DID_OK     1
#define DID_CANCEL 2
#define DID_ERROR  0xffff

#define WA_WARNING     0
#define WA_NOTE        1
#define WA_ERROR       2
#define WA_CWINALARMS 13

#define WinCheckButton(hwndDlg, id, usCheckState) \
    ((ULONG)WinSendDlgItemMsg(hwndDlg, id, BM_SETCHECK, MPFROMSHORT(usCheckState), (MPARAM)NULL))
#define WinQueryButtonCheckstate(hwndDlg, id) \
    ((ULONG)WinSendDlgItemMsg(hwndDlg, id, BM_QUERYCHECK, (MPARAM)NULL, (MPARAM)NULL))
#define WinEnableControl(hwndDlg, id, fEnable) \
    WinEnableWindow(WinWindowFromID(hwndDlg, id), fEnable)
#define WinShowControl(hwndDlg, id, fShow) \
    WinShowWindow(WinWindowFromID(hwndDlg, id), fShow)
#define WinIsControlEnabled(hwndDlg, id) \
    ((BOOL)WinIsWindowEnabled(WinWindowFromID(hwndDlg, id)))

BOOL    APIENTRY WinAlarm(HWND,ULONG);
MRESULT APIENTRY WinDefDlgProc(HWND,ULONG,MPARAM,MPARAM);
USHORT  APIENTRY WinMessageBox(HWND,HWND,PSZ,PSZ,USHORT,USHORT);
BOOL    APIENTRY WinDismissDlg(HWND,ULONG);
ULONG   APIENTRY WinDlgBox(HWND,HWND,PFNWP,HMODULE,ULONG,PVOID);
HWND    APIENTRY WinLoadDlg(HWND,HWND,PFNWP,HMODULE,ULONG,PVOID);
BOOL    APIENTRY WinQueryDlgItemShort(HWND,ULONG,PSHORT,BOOL);
ULONG   APIENTRY WinQueryDlgItemText(HWND,ULONG,LONG,PSZ);
LONG    APIENTRY WinQueryDlgItemTextLength(HWND,ULONG);
BOOL    APIENTRY WinSetDlgItemShort(HWND,ULONG,USHORT,BOOL);
BOOL    APIENTRY WinSetDlgItemText(HWND,ULONG,PCSZ);

#endif

#if defined(INCL_WINDIALOGS)

#pragma pack(2)

typedef struct _DLGTITEM {
    USHORT fsItemStatus;
    USHORT cChildren;
    USHORT cchClassName;
    USHORT offClassName;
    USHORT cchText;
    USHORT offText;
    ULONG  flStyle;
    SHORT  x;
    SHORT  y;
    SHORT  cx;
    SHORT  cy;
    USHORT id;
    USHORT offPresParams;
    USHORT offCtlData;
} DLGTITEM, *PDLGTITEM;

typedef struct _DLGTEMPLATE {
    USHORT   cbTemplate;
    USHORT   type;
    USHORT   codepage;
    USHORT   offadlgti;
    USHORT   fsTemplateStatus;
    USHORT   iItemFocus;
    USHORT   coffPresParams;
    DLGTITEM adlgti[1];
} DLGTEMPLATE, *PDLGTEMPLATE;

#pragma pack()

HWND    APIENTRY WinCreateDlg(HWND,HWND,PFNWP,PDLGTEMPLATE,PVOID);
HWND    APIENTRY WinEnumDlgItem(HWND,HWND,ULONG);
BOOL    APIENTRY WinMapDlgPoints(HWND,PPOINTL,ULONG,BOOL);
ULONG   APIENTRY WinProcessDlg(HWND);
MRESULT APIENTRY WinSendDlgItemMsg(HWND,ULONG,ULONG,MPARAM,MPARAM);
LONG    APIENTRY WinSubstituteStrings(HWND,PCSZ,LONG,PCSZ);


#endif

#if defined(INCL_WINENTRYFIELDS)

#define ES_LEFT       0x00000000
#define ES_CENTER     0x00000001
#define ES_RIGHT      0x00000002
#define ES_AUTOSCROLL 0x00000004
#define ES_MARGIN     0x00000008
#define ES_AUTOTAB    0x00000010
#define ES_READONLY   0x00000020
#define ES_COMMAND    0x00000040
#define ES_UNREADABLE 0x00000080
#define ES_AUTOSIZE   0x00000200

#define ES_ANY        0x00000000
#define ES_SBCS       0x00001000
#define ES_DBCS       0x00002000
#define ES_MIXED      0x00003000

#define CBM_SHOWLIST      0x0170
#define CBM_HILITE        0x0171
#define CBM_ISLISTSHOWING 0x0172

#define CBID_LIST 0x029A
#define CBID_EDIT 0x029B

#define CBN_EFCHANGE 1
#define CBN_EFSCROLL 2
#define CBN_MEMERROR 3
#define CBN_LBSELECT 4
#define CBN_LBSCROLL 5
#define CBN_SHOWLIST 6
#define CBN_ENTER    7

#define CBS_SIMPLE       1
#define CBS_DROPDOWN     2
#define CBS_DROPDOWNLIST 4
#define CBS_COMPATIBLE   8

#define EN_SETFOCUS         0x0001
#define EN_KILLFOCUS        0x0002
#define EN_CHANGE           0x0004
#define EN_SCROLL           0x0008
#define EN_MEMERROR         0x0010
#define EN_OVERFLOW         0x0020
#define EN_INSERTMODETOGGLE 0x0040

#define EM_QUERYCHANGED   0x0140
#define EM_QUERYSEL       0x0141
#define EM_SETSEL         0x0142
#define EM_SETTEXTLIMIT   0x0143
#define EM_CUT            0x0144
#define EM_COPY           0x0145
#define EM_CLEAR          0x0146
#define EM_PASTE          0x0147
#define EM_QUERYFIRSTCHAR 0x0148
#define EM_SETFIRSTCHAR   0x0149
#define EM_QUERYREADONLY  0x014a
#define EM_SETREADONLY    0x014b
#define EM_SETINSERTMODE  0x014c

#pragma pack(2)

typedef struct _COMBOCDATA {
    ULONG cbSize;
    ULONG reserved;
    PVOID pHWXCtlData;
} COMBOCDATA, *PCOMBOCDATA;

typedef struct _ENTRYFDATA {
    USHORT cb;
    USHORT cchEditLimit;
    USHORT ichMinSel;
    USHORT ichMaxSel;
    PVOID  pHWXCtlData;
} ENTRYFDATA, *PENTRYFDATA;

#pragma pack()

#endif

#if defined(INCL_WINERRORS)

#include <pmerr.h>

typedef struct _ERRINFO {
    USHORT  cbFixedErrInfo;
    ERRORID idError;
    USHORT  cDetailLevel;
    USHORT  offaoffszMsg;
    USHORT  offBinaryData;
} ERRINFO, *PERRINFO;

BOOL     APIENTRY WinFreeErrorInfo(PERRINFO perrinfo);
PERRINFO APIENTRY WinGetErrorInfo(HAB hab);
ERRORID  APIENTRY WinGetLastError(HAB hab);

#endif

#if defined(INCL_WINFRAMECTLS)

#define TBM_SETHILITE   0x01e3
#define TBM_QUERYHILITE 0x01e4

#endif

#if defined(INCL_WINFRAMEMGR) || !defined(INCL_NOCOMMON)

#define FCF_TITLEBAR        0x00000001
#define FCF_SYSMENU         0x00000002
#define FCF_MENU            0x00000004
#define FCF_SIZEBORDER      0x00000008
#define FCF_MINBUTTON       0x00000010
#define FCF_MAXBUTTON       0x00000020
#define FCF_MINMAX          0x00000030
#define FCF_VERTSCROLL      0x00000040
#define FCF_HORZSCROLL      0x00000080
#define FCF_DLGBORDER       0x00000100
#define FCF_BORDER          0x00000200
#define FCF_SHELLPOSITION   0x00000400
#define FCF_TASKLIST        0x00000800
#define FCF_NOBYTEALIGN     0x00001000
#define FCF_NOMOVEWITHOWNER 0x00002000
#define FCF_ICON            0x00004000
#define FCF_ACCELTABLE      0x00008000
#define FCF_SYSMODAL        0x00010000
#define FCF_SCREENALIGN     0x00020000
#define FCF_MOUSEALIGN      0x00040000
#define FCF_HIDEBUTTON      0x01000000
#define FCF_HIDEMAX         0x01000020
#define FCF_CLOSEBUTTON     0x04000000
#define FCF_AUTOICON        0x40000000
#define FCF_DBE_APPSTAT     0x80000000

#define FCF_STANDARD        0x0000CC3F

#define FS_ICON            0x00000001
#define FS_ACCELTABLE      0x00000002
#define FS_SHELLPOSITION   0x00000004
#define FS_TASKLIST        0x00000008
#define FS_NOBYTEALIGN     0x00000010
#define FS_NOMOVEWITHOWNER 0x00000020
#define FS_SYSMODAL        0x00000040
#define FS_DLGBORDER       0x00000080
#define FS_BORDER          0x00000100
#define FS_SCREENALIGN     0x00000200
#define FS_MOUSEALIGN      0x00000400
#define FS_SIZEBORDER      0x00000800
#define FS_AUTOICON        0x00001000
#define FS_DBE_APPSTAT     0x00008000

#define FS_STANDARD        0x0000000F

#define FF_FLASHWINDOW     0x0001
#define FF_ACTIVE          0x0002
#define FF_FLASHHILITE     0x0004
#define FF_OWNERHIDDEN     0x0008
#define FF_DLGDISMISSED    0x0010
#define FF_OWNERDISABLED   0x0020
#define FF_SELECTED        0x0040
#define FF_NOACTIVATESWP   0x0080
#define FF_DIALOGBOX       0x0100

#define FI_FRAME           1
#define FI_OWNERHIDE       2
#define FI_ACTIVATEOK      4
#define FI_NOMOVEWITHOWNER 8

#define FID_SYSMENU      0x8002
#define FID_TITLEBAR     0x8003
#define FID_MINMAX       0x8004
#define FID_MENU         0x8005
#define FID_VERTSCROLL   0x8006
#define FID_HORZSCROLL   0x8007
#define FID_CLIENT       0x8008
#define FID_DBE_APPSTAT  0x8010
#define FID_DBE_KBDSTAT  0x8011
#define FID_DBE_PECIC    0x8012
#define FID_DBE_KKPOPUP  0x8013

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
#define SC_BEGINDRAG      0x8020
#define SC_ENDDRAG        0x8021
#define SC_SELECT         0x8022
#define SC_OPEN           0x8023
#define SC_CONTEXTMENU    0x8024
#define SC_CONTEXTHELP    0x8025
#define SC_TEXTEDIT       0x8026
#define SC_BEGINSELECT    0x8027
#define SC_ENDSELECT      0x8028
#define SC_WINDOW         0x8029
#define SC_HIDE           0x802a


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
#define WM_OWNERPOSCHANGE     0x0052
#define WM_CALCFRAMERECT      0x0053

#define WM_WINDOWPOSCHANGED   0x0055
#define WM_ADJUSTFRAMEPOS     0x0056
#define WM_QUERYFRAMECTLCOUNT 0x0059

#define WM_QUERYHELPINFO      0x005B
#define WM_SETHELPINFO        0x005C
#define WM_ERROR              0x005D
#define WM_REALIZEPALETTE     0x005E

#pragma pack(2)

typedef struct _FRAMECDATA {
    USHORT cb;
    ULONG  flCreateFlags;
    USHORT hmodResources;
    USHORT idResources;
} FRAMECDATA;

#pragma pack()

BOOL   APIENTRY WinCalcFrameRect(HWND hwndFrame, PRECTL prcl, BOOL fClient);
HWND   APIENTRY WinCreateStdWindow(HWND hwndParent, ULONG flStyle, PULONG pflCreateFlags,
                   PCSZ pszClassClient, PCSZ pszTitle, ULONG flStyleClient, HMODULE Resource,
                   ULONG ulId, PHWND phwndClient);

#endif

#if defined(INCL_WINHELP)

#include <pmhelp.h>

#endif

#if defined(INCL_WINHOOKS)

#define HK_SENDMSG          0
#define HK_INPUT            1
#define HK_MSGFILTER        2
#define HK_JOURNALRECORD    3
#define HK_JOURNALPLAYBACK  4
#define HK_HELP             5
#define HK_LOADER           6
#define HK_REGISTERUSERMSG  7
#define HK_MSGCONTROL       8
#define HK_PLIST_ENTRY      9
#define HK_PLIST_EXIT      10
#define HK_FINDWORD        11
#define HK_CODEPAGECHANGED 12
#define HK_WINDOWDC        15
#define HK_DESTROYWINDOW   16
#define HK_CHECKMSGFILTER  20
#define HK_MSGINPUT        21
#define HK_LOCKUP          23
#define HK_FLUSHBUF        24

#define HMQ_CURRENT ((HMQ)1)

#define PM_MODEL_1X 0
#define PM_MODEL_2X 1

typedef struct _SMHSTRUCT {
    MPARAM mp2;
    MPARAM mp1;
    ULONG  msg;
    HWND   hwnd;
    ULONG  model;
} SMHSTRUCT, *PSMHSTRUCT;

BOOL   APIENTRY WinReleaseHook(HAB hab, HMQ hmq, LONG lHook, PFN pAddress, HMODULE Module);
BOOL   APIENTRY WinSetHook(HAB hab, HMQ hmq, LONG lHookType, PFN pHookProc, HMODULE Module);

#endif

#if defined(INCL_WININPUT) || !defined(INCL_NOCOMMON)

#define FC_NOSETFOCUS            0x0001
#define FC_NOBRINGTOTOP          FC_NOSETFOCUS
#define FC_NOLOSEFOCUS           0x0002
#define FC_NOBRINGTOPFIRSTWINDOW FC_NOLOSEFOCUS
#define FC_NOSETACTIVE           0x0004
#define FC_NOLOSEACTIVE          0x0008
#define FC_NOSETSELECTION        0x0010
#define FC_NOLOSESELECTION       0x0020

#define QFC_NEXTINCHAIN  1
#define QFC_ACTIVE       2
#define QFC_FRAME        3
#define QFC_SELECTACTIVE 4
#define QFC_PARTOFCHAIN  5

BOOL   APIENTRY WinFocusChange(HWND,HWND,ULONG);
BOOL   APIENTRY WinLockupSystem(HAB);
BOOL   APIENTRY WinSetFocus(HWND,HWND);
BOOL   APIENTRY WinUnlockSystem(HAB,PSZ);

#endif

#if defined(INCL_WININPUT)

#define VK_BUTTON1                 0x01
#define VK_BUTTON2                 0x02
#define VK_BUTTON3                 0x03
#define VK_BREAK                   0x04
#define VK_BACKSPACE               0x05
#define VK_TAB                     0x06
#define VK_BACKTAB                 0x07
#define VK_NEWLINE                 0x08
#define VK_SHIFT                   0x09
#define VK_CTRL                    0x0A
#define VK_ALT                     0x0B
#define VK_ALTGRAF                 0x0C
#define VK_PAUSE                   0x0D
#define VK_CAPSLOCK                0x0E
#define VK_ESC                     0x0F
#define VK_SPACE                   0x10
#define VK_PAGEUP                  0x11
#define VK_PAGEDOWN                0x12
#define VK_END                     0x13
#define VK_HOME                    0x14
#define VK_LEFT                    0x15
#define VK_UP                      0x16
#define VK_RIGHT                   0x17
#define VK_DOWN                    0x18
#define VK_PRINTSCRN               0x19
#define VK_INSERT                  0x1A
#define VK_DELETE                  0x1B
#define VK_SCRLLOCK                0x1C
#define VK_NUMLOCK                 0x1D
#define VK_ENTER                   0x1E
#define VK_SYSRQ                   0x1F
#define VK_F1                      0x20
#define VK_F2                      0x21
#define VK_F3                      0x22
#define VK_F4                      0x23
#define VK_F5                      0x24
#define VK_F6                      0x25
#define VK_F7                      0x26
#define VK_F8                      0x27
#define VK_F9                      0x28
#define VK_F10                     0x29
#define VK_F11                     0x2A
#define VK_F12                     0x2B
#define VK_F13                     0x2C
#define VK_F14                     0x2D
#define VK_F15                     0x2E
#define VK_F16                     0x2F
#define VK_F17                     0x30
#define VK_F18                     0x31
#define VK_F19                     0x32
#define VK_F20                     0x33
#define VK_F21                     0x34
#define VK_F22                     0x35
#define VK_F23                     0x36
#define VK_F24                     0x37
#define VK_ENDDRAG                 0x38
#define VK_CLEAR                   0x39
#define VK_EREOF                   0x3A
#define VK_PA1                     0x3B
#define VK_ATTN                    0x3C
#define VK_CRSEL                   0x3D
#define VK_EXSEL                   0x3E
#define VK_COPY                    0x3F
#define VK_BLK1                    0x40
#define VK_BLK2                    0x41
#define VK_MENU                    VK_F10

#define KC_NONE        0x0000
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

#define WM_MOUSEFIRST         0x0070
#define WM_MOUSELAST          0x0079
#define WM_BUTTONCLICKFIRST   0x0071
#define WM_BUTTONCLICKLAST    0x0079
#define WM_MOUSEMOVE          0x0070
#define WM_BUTTON1DOWN        0x0071
#define WM_BUTTON1UP          0x0072
#define WM_BUTTON1DBLCLK      0x0073
#define WM_BUTTON2DOWN        0x0074
#define WM_BUTTON2UP          0x0075
#define WM_BUTTON2DBLCLK      0x0076
#define WM_BUTTON3DOWN        0x0077
#define WM_BUTTON3UP          0x0078
#define WM_BUTTON3DBLCLK      0x0079
#define WM_MOUSEMAP           0x007D
#define WM_EXTMOUSEFIRST      0x0410
#define WM_EXTMOUSELAST       0x0419
#define WM_CHORD              0x0410
#define WM_BUTTON1MOTIONSTART 0x0411
#define WM_BUTTON1MOTIONEND   0x0412
#define WM_BUTTON1CLICK       0x0413
#define WM_BUTTON2MOTIONSTART 0x0414
#define WM_BUTTON2MOTIONEND   0x0415
#define WM_BUTTON2CLICK       0x0416
#define WM_BUTTON3MOTIONSTART 0x0417
#define WM_BUTTON3MOTIONEND   0x0418
#define WM_BUTTON3CLICK       0x0419
#define WM_BEGINDRAG          0x0420
#define WM_ENDDRAG            0x0421
#define WM_SINGLESELECT       0x0422
#define WM_OPEN               0x0423
#define WM_CONTEXTMENU        0x0424
#define WM_CONTEXTHELP        0x0425
#define WM_TEXTEDIT           0x0426
#define WM_BEGINSELECT        0x0427
#define WM_ENDSELECT          0x0428
#define WM_PICKUP             0x0429
#define WM_PENFIRST           0x04C0
#define WM_PENLAST            0x04FF
#define WM_MMPMFIRST          0x0500
#define WM_MMPMLAST           0x05FF
#define WM_STDDLGFIRST        0x0600
#define WM_STDDLGLAST         0x065F
#define WM_BIDI_FIRST         0x0BD0
#define WM_BIDI_LAST          0x0BFF
#define WM_CHAR               0x007A
#define WM_VIOCHAR            0x007B

LONG   APIENTRY WinGetKeyState(HWND,LONG);
LONG   APIENTRY WinGetPhysKeyState(HWND,LONG);
HWND   APIENTRY WinQueryCapture(HWND);
HWND   APIENTRY WinQueryFocus(HWND);
BOOL   APIENTRY WinSetCapture(HWND,HWND);

#endif

#if defined(INCL_WINLISTBOXES)

#define LN_SELECT    1
#define LN_SETFOCUS  2
#define LN_KILLFOCUS 3
#define LN_SCROLL    4
#define LN_ENTER     5

#define LS_MULTIPLESEL 0x0001
#define LS_OWNERDRAW   0x0002
#define LS_NOADJUSTPOS 0x0004
#define LS_HORZSCROLL  0x0008
#define LS_EXTENDEDSEL 0x0010

#define LM_QUERYITEMCOUNT      0x0160
#define LM_INSERTITEM          0x0161
#define LM_SETTOPINDEX         0x0162
#define LM_DELETEITEM          0x0163
#define LM_SELECTITEM          0x0164
#define LM_QUERYSELECTION      0x0165
#define LM_SETITEMTEXT         0x0166
#define LM_QUERYITEMTEXTLENGTH 0x0167
#define LM_QUERYITEMTEXT       0x0168
#define LM_SETITEMHANDLE       0x0169
#define LM_QUERYITEMHANDLE     0x016a
#define LM_SEARCHSTRING        0x016b
#define LM_SETITEMHEIGHT       0x016c
#define LM_QUERYTOPINDEX       0x016d
#define LM_DELETEALL           0x016e
#define LM_INSERTMULTITEMS     0x016f
#define LM_SETITEMWIDTH        0x0660

#define LIT_CURSOR   (-4)
#define LIT_ERROR    (-3)
#define LIT_MEMERROR (-2)
#define LIT_NONE     (-1)
#define LIT_FIRST    (-1)

#define LIT_END            (-1)
#define LIT_SORTASCENDING  (-2)
#define LIT_SORTDESCENDING (-3)

#define LSS_SUBSTRING     1
#define LSS_PREFIX        2
#define LSS_CASESENSITIVE 4

#define WinDeleteLboxItem(hwndLbox, index) \
    ((LONG)WinSendMsg(hwndLbox, LM_DELETEITEM, MPFROMLONG(index), (MPARAM)NULL))
#define WinInsertLboxItem(hwndLbox, index, psz) \
    ((LONG)WinSendMsg(hwndLbox, LM_INSERTITEM, MPFROMLONG(index), MPFROMP(psz)))
#define WinQueryLboxCount(hwndLbox) \
    ((LONG)WinSendMsg(hwndLbox, LM_QUERYITEMCOUNT, (MPARAM)NULL, (MPARAM)NULL))
#define WinQueryLboxItemText(hwndLbox, index, psz, cchMax) \
    ((LONG)WinSendMsg(hwndLbox, LM_QUERYITEMTEXT, MPFROM2SHORT((index), (cchMax)), MPFROMP(psz)))
#define WinQueryLboxItemTextLength(hwndLbox, index) \
    ((SHORT)WinSendMsg(hwndLbox, LM_QUERYITEMTEXTLENGTH, MPFROMSHORT(index), (MPARAM)NULL))
#define WinSetLboxItemText(hwndLbox, index, psz) \
    ((BOOL)WinSendMsg(hwndLbox, LM_SETITEMTEXT, MPFROMLONG(index), MPFROMP(psz)))
#define WinQueryLboxSelectedItem(hwndLbox) \
    ((LONG)WinSendMsg(hwndLbox, LM_QUERYSELECTION, MPFROMLONG(LIT_FIRST), (MPARAM)NULL))

typedef struct _LBOXINFO {
    LONG  lItemIndex;
    ULONG ulItemCount;
    ULONG reserved;
    ULONG reserved2;
} LBOXINFO, *PLBOXINFO;

#endif

#if defined(INCL_WINMLE)

#define MLS_WORDWRAP     0x00000001
#define MLS_BORDER       0x00000002
#define MLS_VSCROLL      0x00000004
#define MLS_HSCROLL      0x00000008
#define MLS_READONLY     0x00000010
#define MLS_IGNORETAB    0x00000020
#define MLS_DISABLEUNDO  0x00000040
#define MLS_LIMITVSCROLL 0x00000080

#define MLM_SETTEXTLIMIT          0x01b0
#define MLM_QUERYTEXTLIMIT        0x01b1
#define MLM_SETFORMATRECT         0x01b2
#define MLM_QUERYFORMATRECT       0x01b3
#define MLM_SETWRAP               0x01b4
#define MLM_QUERYWRAP             0x01b5
#define MLM_SETTABSTOP            0x01b6
#define MLM_QUERYTABSTOP          0x01b7
#define MLM_SETREADONLY           0x01b8
#define MLM_QUERYREADONLY         0x01b9
#define MLM_QUERYCHANGED          0x01ba
#define MLM_SETCHANGED            0x01bb
#define MLM_QUERYLINECOUNT        0x01bc
#define MLM_CHARFROMLINE          0x01bd
#define MLM_LINEFROMCHAR          0x01be
#define MLM_QUERYLINELENGTH       0x01bf
#define MLM_QUERYTEXTLENGTH       0x01c0
#define MLM_FORMAT                0x01c1
#define MLM_SETIMPORTEXPORT       0x01c2
#define MLM_IMPORT                0x01c3
#define MLM_EXPORT                0x01c4
#define MLM_DELETE                0x01c6
#define MLM_QUERYFORMATLINELENGTH 0x01c7
#define MLM_QUERYFORMATTEXTLENGTH 0x01c8
#define MLM_INSERT                0x01c9
#define MLM_SETSEL                0x01ca
#define MLM_QUERYSEL              0x01cb
#define MLM_QUERYSELTEXT          0x01cc
#define MLM_QUERYUNDO             0x01cd
#define MLM_UNDO                  0x01ce
#define MLM_RESETUNDO             0x01cf
#define MLM_QUERYFONT             0x01d0
#define MLM_SETFONT               0x01d1
#define MLM_SETTEXTCOLOR          0x01d2
#define MLM_QUERYTEXTCOLOR        0x01d3
#define MLM_SETBACKCOLOR          0x01d4
#define MLM_QUERYBACKCOLOR        0x01d5
#define MLM_QUERYFIRSTCHAR        0x01d6
#define MLM_SETFIRSTCHAR          0x01d7
#define MLM_CUT                   0x01d8
#define MLM_COPY                  0x01d9
#define MLM_PASTE                 0x01da
#define MLM_CLEAR                 0x01db
#define MLM_ENABLEREFRESH         0x01dc
#define MLM_DISABLEREFRESH        0x01dd
#define MLM_SEARCH                0x01de
#define MLM_QUERYIMPORTEXPORT     0x01df
#define MLN_OVERFLOW              0x0001
#define MLN_PIXHORZOVERFLOW       0x0002
#define MLN_PIXVERTOVERFLOW       0x0003
#define MLN_TEXTOVERFLOW          0x0004
#define MLN_VSCROLL               0x0005
#define MLN_HSCROLL               0x0006
#define MLN_CHANGE                0x0007
#define MLN_SETFOCUS              0x0008
#define MLN_KILLFOCUS             0x0009
#define MLN_MARGIN                0x000a
#define MLN_SEARCHPAUSE           0x000b
#define MLN_MEMERROR              0x000c
#define MLN_UNDOOVERFLOW          0x000d
#define MLN_CLPBDFAIL             0x000f

#define MLFQS_MINMAXSEL 0
#define MLFQS_MINSEL    1
#define MLFQS_MAXSEL    2
#define MLFQS_ANCHORSEL 3
#define MLFQS_CURSORSEL 4

typedef LONG  IPT;
typedef PLONG PIPT;
typedef LONG  PIX;
typedef ULONG LINE;

typedef struct _FORMATRECT {
    LONG cxFormat;
    LONG cyFormat;
} MLEFORMATRECT, *PFORMATRECT;

typedef struct _MLECTLDATA {
    USHORT cbCtlData;
    USHORT afIEFormat;
    ULONG  cchText;
    IPT    iptAnchor;
    IPT    iptCursor;
    LONG   cxFormat;
    LONG   cyFormat;
    ULONG  afFormatFlags;
    PVOID  pHWXCtlData;
} MLECTLDATA, *PMLECTLDATA;

typedef struct _MLEOVERFLOW {
    ULONG afErrInd;
    LONG  nBytesOver;
    LONG  pixHorzOver;
    LONG  pixVertOver;
} MLEOVERFLOW, *POVERFLOW;

typedef struct _MLEMARGSTRUCT {
    USHORT afMargins;
    USHORT usMouMsg;
    IPT    iptNear;
} MLEMARGSTRUCT, *PMARGSTRUCT;

typedef struct _SEARCH {
    USHORT cb;
    PCHAR  pchFind;
    PCHAR  pchReplace;
    SHORT  cchFind;
    SHORT  cchReplace;
    IPT    iptStart;
    IPT    iptStop;
    USHORT cchFound;
} MLE_SEARCHDATA, *PMLE_SEARCHDATA;

#endif

#if defined(INCL_WINMENUS)

#define MIT_END             (-1)
#define MIT_NONE            (-1)
#define MIT_MEMERROR        (-1)
#define MIT_ERROR           (-1)
#define MIT_FIRST           (-2)
#define MIT_LAST            (-3)
#define MID_ERROR           (-1)
#define MID_NONE            MIT_NONE

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

#define MS_ACTIONBAR           0x0001
#define MS_TITLEBUTTON         0x0002
#define MS_VERTICALFLIP        0x0004
#define MS_CONDITIONALCASCADE  0x0040

#define PU_POSITIONONITEM   0x0001
#define PU_HCONSTRAIN       0x0002
#define PU_VCONSTRAIN       0x0004
#define PU_NONE             0x0000
#define PU_MOUSEBUTTON1DOWN 0x0008
#define PU_MOUSEBUTTON2DOWN 0x0010
#define PU_MOUSEBUTTON3DOWN 0x0018
#define PU_SELECTITEM       0x0020
#define PU_MOUSEBUTTON1     0x0040
#define PU_MOUSEBUTTON2     0x0080
#define PU_MOUSEBUTTON3     0x0100
#define PU_KEYBOARD         0x0200

#define MM_INSERTITEM          0x0180
#define MM_DELETEITEM          0x0181
#define MM_QUERYITEM           0x0182
#define MM_SETITEM             0x0183
#define MM_QUERYITEMCOUNT      0x0184
#define MM_STARTMENUMODE       0x0185
#define MM_ENDMENUMODE         0x0186
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
#define MM_QUERYITEMRECT       0x0194
#define MM_QUERYDEFAULTITEMID  0x0431
#define MM_SETDEFAULTITEMID    0x0432

#define WinCheckMenuItem(hwndMenu, id, fcheck) \
    ((BOOL)WinSendMsg(hwndMenu, MM_SETITEMATTR, MPFROM2SHORT(id, TRUE), \
    MPFROM2SHORT(MIA_CHECKED, (USHORT)(fcheck) ? MIA_CHECKED : 0)))
#define WinIsMenuItemChecked(hwndMenu, id) \
    ((BOOL)WinSendMsg(hwndMenu, MM_QUERYITEMATTR, \
    MPFROM2SHORT(id, TRUE), MPFROMLONG(MIA_CHECKED)))
#define WinEnableMenuItem(hwndMenu, id, fEnable) \
    ((BOOL)WinSendMsg(hwndMenu, MM_SETITEMATTR, MPFROM2SHORT(id, TRUE), \
    MPFROM2SHORT(MIA_DISABLED, (USHORT)(fEnable) ? 0 : MIA_DISABLED)))
#define WinIsMenuItemEnabled(hwndMenu, id)  \
    (!(BOOL)WinSendMsg(hwndMenu, MM_QUERYITEMATTR, \
    MPFROM2SHORT(id, TRUE), MPFROMLONG(MIA_DISABLED)))
#define WinSetMenuItemText(hwndMenu, id, psz) \
    ((BOOL)WinSendMsg(hwndMenu, MM_SETITEMTEXT, MPFROMLONG(id), MPFROMP(psz)))
#define WinIsMenuItemValid(hwndMenu, id) \
    ((BOOL)WinSendMsg(hwndMenu, MM_ISITEMVALID, MPFROM2SHORT(id, TRUE), MPFROMLONG(FALSE)))

#pragma pack(2)

typedef struct _MENUITEM {
    SHORT  iPosition;
    USHORT afStyle;
    USHORT afAttribute;
    USHORT id;
    HWND   hwndSubMenu;
    ULONG  hItem;
} MENUITEM, *PMENUITEM;

#pragma pack()

HWND   APIENTRY WinCreateMenu(HWND hwndParent, PVOID lpmt);

HWND   APIENTRY WinLoadMenu(HWND hwndFrame, HMODULE hmod, ULONG idMenu);


#endif

#if defined(INCL_WINPOINTERS)

#define SPTR_ARROW            1
#define SPTR_TEXT             2
#define SPTR_WAIT             3
#define SPTR_SIZE             4
#define SPTR_MOVE             5
#define SPTR_SIZENWSE         6
#define SPTR_SIZENESW         7
#define SPTR_SIZEWE           8
#define SPTR_SIZENS           9
#define SPTR_APPICON         10
#define SPTR_ICONINFORMATION 11
#define SPTR_ICONQUESTION    12
#define SPTR_ICONERROR       13
#define SPTR_ICONWARNING     14
#define SPTR_ILLEGAL         18
#define SPTR_FILE            19
#define SPTR_FOLDER          20
#define SPTR_MULTFILE        21
#define SPTR_PROGRAM         22
#define SPTR_DISPLAY_PTRS    22
#define SPTR_PENFIRST        23
#define SPTR_PENLAST         39
#define SPTR_CPTR            39

#define SBMP_OLD_SYSMENU        1
#define SBMP_OLD_SBUPARROW      2
#define SBMP_OLD_SBDNARROW      3
#define SBMP_OLD_SBRGARROW      4
#define SBMP_OLD_SBLFARROW      5
#define SBMP_MENUCHECK          6
#define SBMP_OLD_CHECKBOXES     7
#define SBMP_BTNCORNERS         8
#define SBMP_OLD_MINBUTTON      9
#define SBMP_OLD_MAXBUTTON     10
#define SBMP_OLD_RESTOREBUTTON 11
#define SBMP_OLD_CHILDSYSMENU  12
#define SBMP_DRIVE             15
#define SBMP_FILE              16
#define SBMP_FOLDER            17
#define SBMP_TREEPLUS          18
#define SBMP_TREEMINUS         19
#define SBMP_PROGRAM           22
#define SBMP_MENUATTACHED      23
#define SBMP_SIZEBOX           24
#define SBMP_SYSMENU           25
#define SBMP_MINBUTTON         26
#define SBMP_MAXBUTTON         27
#define SBMP_RESTOREBUTTON     28
#define SBMP_CHILDSYSMENU      29
#define SBMP_SYSMENUDEP        30
#define SBMP_MINBUTTONDEP      31
#define SBMP_MAXBUTTONDEP      32
#define SBMP_RESTOREBUTTONDEP  33
#define SBMP_CHILDSYSMENUDEP   34
#define SBMP_SBUPARROW         35
#define SBMP_SBDNARROW         36
#define SBMP_SBLFARROW         37
#define SBMP_SBRGARROW         38
#define SBMP_SBUPARROWDEP      39
#define SBMP_SBDNARROWDEP      40
#define SBMP_SBLFARROWDEP      41
#define SBMP_SBRGARROWDEP      42
#define SBMP_SBUPARROWDIS      43
#define SBMP_SBDNARROWDIS      44
#define SBMP_SBLFARROWDIS      45
#define SBMP_SBRGARROWDIS      46
#define SBMP_COMBODOWN         47
#define SBMP_CHECKBOXES        48
#define SBMP_HIDE              50
#define SBMP_HIDEDEP           51
#define SBMP_CLOSE             52
#define SBMP_CLOSEDEP          53

typedef struct _POINTERINFO {
    ULONG   fPointer;
    LONG    xHotSpot;
    LONG    yHotSpot;
    HBITMAP hbmPointer;
    HBITMAP hbmColor;
    HBITMAP hbmMiniPointer;
    HBITMAP hbmMiniColor;
} POINTERINFO, *PPOINTERINFO;

BOOL     APIENTRY WinDestroyPointer(HPOINTER hptrPointer);
HBITMAP  APIENTRY WinGetSysBitmap(HWND hwndDesktop, ULONG ibm);
HPOINTER APIENTRY WinLoadPointer(HWND hwndDeskTop, HMODULE Resource, ULONG idPointer);
HPOINTER APIENTRY WinQueryPointer(HWND hwndDeskTop);
BOOL     APIENTRY WinQueryPointerInfo(HPOINTER hptr, PPOINTERINFO pptriPointerInfo);
BOOL     APIENTRY WinQueryPointerPos(HWND hwndDeskTop, PPOINTL pptlPoint);
HPOINTER APIENTRY WinQuerySysPointer(HWND hwndDeskTop, LONG lIdentifier, BOOL fCopy);
BOOL     APIENTRY WinSetPointer(HWND hwndDeskTop, HPOINTER hptrNewPointer);
BOOL     APIENTRY WinSetPointerOwner(HPOINTER hptr, PID pid, BOOL fDestroy);
BOOL     APIENTRY WinSetPointerPos(HWND hwndDeskTop, LONG lx, LONG ly);
BOOL     APIENTRY WinShowPointer(HWND hwndDeskTop, BOOL fShow);

#endif

#if !defined(SESMGR)

#define HINI_PROFILE       ((HINI)NULL)
#define HINI_USERPROFILE   ((HINI)-1)
#define HINI_SYSTEMPROFILE ((HINI)-2)
#define HINI_USER          HINI_USERPROFILE
#define HINI_SYSTEM        HINI_SYSTEMPROFILE

typedef LHANDLE HPROGRAM, *PHPROGRAM;
typedef LHANDLE HAPP, *PHAPP;
typedef LHANDLE HINI, *PHINI;
typedef LHANDLE HSWITCH, *PHSWITCH;

typedef struct _PRFPROFILE {
    ULONG cchUserName;
    PSZ   pszUserName;
    ULONG cchSysName;
    PSZ   pszSysName;
} PRFPROFILE, *PPRFPROFILE;

#endif

#if defined(INCL_WINPROGRAMLIST)

#define PROG_DEFAULT              (PROGCATEGORY)0
#define PROG_FULLSCREEN           (PROGCATEGORY)1
#define PROG_WINDOWABLEVIO        (PROGCATEGORY)2
#define PROG_PM                   (PROGCATEGORY)3
#define PROG_GROUP                (PROGCATEGORY)5
#define PROG_REAL                 (PROGCATEGORY)4
#define PROG_VDM                  (PROGCATEGORY)4
#define PROG_WINDOWEDVDM          (PROGCATEGORY)7
#define PROG_DLL                  (PROGCATEGORY)6
#define PROG_PDD                  (PROGCATEGORY)8
#define PROG_VDD                  (PROGCATEGORY)9
#define PROG_WINDOW_REAL          (PROGCATEGORY)10
#define PROG_WINDOW_PROT          (PROGCATEGORY)11
#define PROG_30_STD               (PROGCATEGORY)11
#define PROG_WINDOW_AUTO          (PROGCATEGORY)12
#define PROG_SEAMLESSVDM          (PROGCATEGORY)13
#define PROG_30_STDSEAMLESSVDM    (PROGCATEGORY)13
#define PROG_SEAMLESSCOMMON       (PROGCATEGORY)14
#define PROG_30_STDSEAMLESSCOMMON (PROGCATEGORY)14
#define PROG_31_STDSEAMLESSVDM    (PROGCATEGORY)15
#define PROG_31_STDSEAMLESSCOMMON (PROGCATEGORY)16
#define PROG_31_ENHSEAMLESSVDM    (PROGCATEGORY)17
#define PROG_31_ENHSEAMLESSCOMMON (PROGCATEGORY)18
#define PROG_31_ENH               (PROGCATEGORY)19
#define PROG_31_STD               (PROGCATEGORY)20
#define PROG_DOS_GAME             (PROGCATEGORY)21
#define PROG_WIN_GAME             (PROGCATEGORY)22
#define PROG_DOS_MODE             (PROGCATEGORY)23
#define PROG_RESERVED             (PROGCATEGORY)255

#define SHE_VISIBLE     0
#define SHE_INVISIBLE   1
#define SHE_RESERVED    255
#define SHE_UNPROTECTED 0
#define SHE_PROTECTED   0

#define SAF_VALIDFLAGS       0x001F
#define SAF_INSTALLEDCMDLINE 0x0001
#define SAF_STARTCHILDAPP    0x0002
#define SAF_MAXIMIZED        0x0004
#define SAF_MINIMIZED        0x0008
#define SAF_BACKGROUND       0x0010

typedef ULONG PROGCATEGORY, *PPROGCATEGORY;

typedef struct _PROGTYPE {
    PROGCATEGORY progc;
    ULONG        fbVisible;
} PROGTYPE, *PPROGTYPE;

typedef struct _PROGDETAILS {
    ULONG     Length;
    PROGTYPE  progt;
    PSZ       pszTitle;
    PSZ       pszExecutable;
    PSZ       pszParameters;
    PSZ       pszStartupDir;
    PSZ       pszIcon;
    PSZ       pszEnvironment;
    SWP       swpInitial;
} PROGDETAILS, *PPROGDETAILS;

HAPP APIENTRY WinStartApp(HWND hwndNotify, PPROGDETAILS pDetails, PCSZ pszParams,
                   PVOID Reserved, ULONG fbOptions);
BOOL APIENTRY WinTerminateApp(HAPP happ);

#endif

#if defined(INCL_WINRECTANGLES)

BOOL    APIENTRY WinCopyRect(HAB hab, PRECTL prclDst, PRECTL prclSrc);
BOOL    APIENTRY WinEqualRect(HAB hab, PRECTL prcl1, PRECTL prcl2);
BOOL    APIENTRY WinInflateRect(HAB hab, PRECTL prcl, LONG cx, LONG cy);
BOOL    APIENTRY WinIntersectRect(HAB hab, PRECTL pcrlDst, PRECTL pcrlSrc1, PRECTL pcrlSrc2);
BOOL    APIENTRY WinIsRectEmpty(HAB hab, PRECTL prclprc);
BOOL    APIENTRY WinMakePoints(HAB hab, PPOINTL pwpt, ULONG cwpt);
BOOL    APIENTRY WinMakeRect(HAB hab, PRECTL pwrc);
BOOL    APIENTRY WinOffsetRect(HAB hab, PRECTL prcl, LONG cx, LONG cy);
BOOL    APIENTRY WinPtInRect(HAB hab, PRECTL prcl, PPOINTL pptl);
BOOL    APIENTRY WinUnionRect(HAB hab, PRECTL prclDst, PRECTL prclSrc1, PRECTL prclSrc2);
BOOL    APIENTRY WinSetRect(HAB hab, PRECTL prcl, LONG xLeft, LONG yBottom, LONG xRight, LONG yTop);
BOOL    APIENTRY WinSetRectEmpty(HAB hab, PRECTL prcl);
BOOL    APIENTRY WinSubtractRect(HAB hab, PRECTL prclDst, PRECTL prclSrc1, PRECTL prclSrc2);

#endif

#if defined(INCL_WINSCROLLBARS)

#define SBS_HORZ      0x0000
#define SBS_VERT      0x0001
#define SBS_THUMBSIZE 0x0002
#define SBS_AUTOTRACK 0x0004
#define SBS_AUTOSIZE  0x2000

#define SB_LINEUP         1
#define SB_LINEDOWN       2
#define SB_LINELEFT       1
#define SB_LINERIGHT      2
#define SB_PAGEUP         3
#define SB_PAGEDOWN       4
#define SB_PAGELEFT       3
#define SB_PAGERIGHT      4
#define SB_SLIDERTRACK    5
#define SB_SLIDERPOSITION 6
#define SB_ENDSCROLL      7

#define SBM_SETSCROLLBAR  0x01a0
#define SBM_SETPOS        0x01a1
#define SBM_QUERYPOS      0x01a2
#define SBM_QUERYRANGE    0x01a3
#define SBM_SETTHUMBSIZE  0x01a6

#pragma pack(2)

typedef struct _SBCDATA {
    USHORT cb;
    USHORT sHilite;
    SHORT  posFirst;
    SHORT  posLast;
    SHORT  posThumb;
    SHORT  cVisible;
    SHORT  cTotal;
} SBCDATA, *PSBCDATA;

#pragma pack()

#endif

#if defined(INCL_WINSHELLDATA)

#define PL_ALTERED 0x008E

BOOL   APIENTRY PrfCloseProfile(HINI hini);
HINI   APIENTRY PrfOpenProfile(HAB hab, PCSZ pszFileName);
BOOL   APIENTRY PrfQueryProfile(HAB hab, PPRFPROFILE pprfproProfile);
BOOL   APIENTRY PrfQueryProfileData(HINI hini, PCSZ pszApp, PCSZ pszKey,
                   PVOID pBuffer, PULONG pulBufferMax);
LONG   APIENTRY PrfQueryProfileInt(HINI hini, PCSZ pszApp, PCSZ pszKey, LONG lDefault);
BOOL   APIENTRY PrfQueryProfileSize(HINI hini, PCSZ pszApp, PCSZ pszKey, PULONG pulDataLen);
ULONG  APIENTRY PrfQueryProfileString(HINI hini, PCSZ pszApp, PCSZ pszKey, PCSZ pszDefault,
                   PVOID pBuffer, ULONG ulBufferMax);
BOOL   APIENTRY PrfReset(HAB hab, PPRFPROFILE pPrfProfile);
BOOL   APIENTRY PrfWriteProfileData(HINI hini, PCSZ pszApp, PCSZ pszKey,
                   PVOID pData, ULONG ulDataLen);
BOOL   APIENTRY  PrfWriteProfileString(HINI hini, PCSZ pszApp, PCSZ pszKey, PCSZ pszData);

#endif

#if defined(INCL_WINSTATICS)

#define SS_TEXT          0x0001
#define SS_GROUPBOX      0x0002
#define SS_ICON          0x0003
#define SS_BITMAP        0x0004
#define SS_FGNDRECT      0x0005
#define SS_HALFTONERECT  0x0006
#define SS_BKGNDRECT     0x0007
#define SS_FGNDFRAME     0x0008
#define SS_HALFTONEFRAME 0x0009
#define SS_BKGNDFRAME    0x000A
#define SS_SYSICON       0x000B
#define SS_AUTOSIZE      0x0040

#define SM_SETHANDLE     0x0100
#define SM_QUERYHANDLE   0x0101

#define WM_MSGBOXINIT    0x010E
#define WM_MSGBOXDISMISS 0x010F

#endif

#if defined(INCL_WINSWITCHLIST) || !defined(INCL_NOCOMMON)

#define SWL_INVISIBLE 1
#define SWL_GRAYED    2
#define SWL_VISIBLE   4

#define SWL_JUMPABLE    2
#define SWL_NOTJUMPABLE 1

#define MAXNAMEL 60

typedef struct _SWCNTRL {
    HWND     hwnd;
    HWND     hwndIcon;
    HPROGRAM hprog;
    PID      idProcess;
    ULONG    idSession;
    ULONG    uchVisibility;
    ULONG    fbJump;
    CHAR     szSwtitle[MAXNAMEL+4];
    ULONG    bProgType;
} SWCNTRL, *PSWCNTRL;

HSWITCH APIENTRY WinAddSwitchEntry(PSWCNTRL);
ULONG   APIENTRY WinRemoveSwitchEntry(HSWITCH);

#endif

#if defined(INCL_WINSWITCHLIST)

typedef struct _SWENTRY {
    HSWITCH hswitch;
    SWCNTRL swctl;
} SWENTRY, *PSWENTRY;

typedef struct _SWBLOCK {
    ULONG   cswentry;
    SWENTRY aswentry[1];
} SWBLOCK, *PSWBLOCK;

ULONG   APIENTRY WinChangeSwitchEntry(HSWITCH hswitchSwitch, PSWCNTRL pswctlSwitchData);
HSWITCH APIENTRY WinCreateSwitchEntry(HAB hab, PSWCNTRL pswctlSwitchData);
ULONG   APIENTRY WinQuerySessionTitle(HAB hab, ULONG usSession, PCSZ pszTitle, ULONG usTitlelen);
ULONG   APIENTRY WinQuerySwitchEntry(HSWITCH hswitchSwitch, PSWCNTRL pswctlSwitchData);
HSWITCH APIENTRY WinQuerySwitchHandle(HWND hwnd, PID pidProcess);
ULONG   APIENTRY WinQuerySwitchList(HAB hab, PSWBLOCK pswblkSwitchEntries, ULONG usDataLength);
ULONG   APIENTRY WinQueryTaskSizePos(HAB hab, ULONG usScreenGroup, PSWP pswpPositionData);
ULONG   APIENTRY WinQueryTaskTitle(ULONG usSession, PCSZ pszTitle, ULONG usTitlelen);
ULONG   APIENTRY WinSwitchToProgram(HSWITCH hswitchSwHandle);

#endif

#if defined(INCL_WINSYS)

#define SV_SWAPBUTTON           0
#define SV_DBLCLKTIME           1
#define SV_CXDBLCLK             2
#define SV_CYDBLCLK             3
#define SV_CXSIZEBORDER         4
#define SV_CYSIZEBORDER         5
#define SV_ALARM                6
#define SV_RESERVEDFIRST1       7
#define SV_RESERVEDLAST1        8
#define SV_CURSORRATE           9
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
#define SV_CPOINTERBUTTONS     43
#define SV_POINTERLEVEL        44
#define SV_CURSORLEVEL         45
#define SV_TRACKRECTLEVEL      46
#define SV_CTIMERS             47
#define SV_MOUSEPRESENT        48
#define SV_CXBYTEALIGN         49
#define SV_CXALIGN             49
#define SV_CYBYTEALIGN         50
#define SV_CYALIGN             50
#define SV_NOTRESERVED         56
#define SV_EXTRAKEYBEEP        57
#define SV_SETLIGHTS           58
#define SV_INSERTMODE          59
#define SV_MENUROLLDOWNDELAY   64
#define SV_MENUROLLUPDELAY     65
#define SV_ALTMNEMONIC         66
#define SV_TASKLISTMOUSEACCESS 67
#define SV_CXICONTEXTWIDTH     68
#define SV_CICONTEXTLINES      69
#define SV_CHORDTIME           70
#define SV_CXCHORD             71
#define SV_CYCHORD             72
#define SV_CXMOTIONSTART       73
#define SV_CYMOTIONSTART       74
#define SV_BEGINDRAG           75
#define SV_ENDDRAG             76
#define SV_SINGLESELECT        77
#define SV_OPEN                78
#define SV_CONTEXTMENU         79
#define SV_CONTEXTHELP         80
#define SV_TEXTEDIT            81
#define SV_BEGINSELECT         82
#define SV_ENDSELECT           83
#define SV_BEGINDRAGKB         84
#define SV_ENDDRAGKB           85
#define SV_SELECTKB            86
#define SV_OPENKB              87
#define SV_CONTEXTMENUKB       88
#define SV_CONTEXTHELPKB       89
#define SV_TEXTEDITKB          90
#define SV_BEGINSELECTKB       91
#define SV_ENDSELECTKB         92
#define SV_ANIMATION           93
#define SV_ANIMATIONSPEED      94
#define SV_MONOICONS           95
#define SV_KBDALTERED          96
#define SV_PRINTSCREEN         97
#define SV_LOCKSTARTINPUT      98
#define SV_CSYSVALUES         108

#define PP_FOREGROUNDCOLOR                       1
#define PP_FOREGROUNDCOLORINDEX                  2
#define PP_BACKGROUNDCOLOR                       3
#define PP_BACKGROUNDCOLORINDEX                  4
#define PP_HILITEFOREGROUNDCOLOR                 5
#define PP_HILITEFOREGROUNDCOLORINDEX            6
#define PP_HILITEBACKGROUNDCOLOR                 7
#define PP_HILITEBACKGROUNDCOLORINDEX            8
#define PP_DISABLEDFOREGROUNDCOLOR               9
#define PP_DISABLEDFOREGROUNDCOLORINDEX         10
#define PP_DISABLEDBACKGROUNDCOLOR              11
#define PP_DISABLEDBACKGROUNDCOLORINDEX         12
#define PP_BORDERCOLOR                          13
#define PP_BORDERCOLORINDEX                     14
#define PP_FONTNAMESIZE                         15
#define PP_FONTHANDLE                           16
#define PP_RESERVED                             17
#define PP_ACTIVECOLOR                          18
#define PP_ACTIVECOLORINDEX                     19
#define PP_INACTIVECOLOR                        20
#define PP_INACTIVECOLORINDEX                   21
#define PP_ACTIVETEXTFGNDCOLOR                  22
#define PP_ACTIVETEXTFGNDCOLORINDEX             23
#define PP_ACTIVETEXTBGNDCOLOR                  24
#define PP_ACTIVETEXTBGNDCOLORINDEX             25
#define PP_INACTIVETEXTFGNDCOLOR                26
#define PP_INACTIVETEXTFGNDCOLORINDEX           27
#define PP_INACTIVETEXTBGNDCOLOR                28
#define PP_INACTIVETEXTBGNDCOLORINDEX           29
#define PP_SHADOW                               30
#define PP_MENUFOREGROUNDCOLOR                  31
#define PP_MENUFOREGROUNDCOLORINDEX             32
#define PP_MENUBACKGROUNDCOLOR                  33
#define PP_MENUBACKGROUNDCOLORINDEX             34
#define PP_MENUHILITEFGNDCOLOR                  35
#define PP_MENUHILITEFGNDCOLORINDEX             36
#define PP_MENUHILITEBGNDCOLOR                  37
#define PP_MENUHILITEBGNDCOLORINDEX             38
#define PP_MENUDISABLEDFGNDCOLOR                39
#define PP_MENUDISABLEDFGNDCOLORINDEX           40
#define PP_MENUDISABLEDBGNDCOLOR                41
#define PP_MENUDISABLEDBGNDCOLORINDEX           42
#define PP_SHADOWTEXTCOLOR                      43
#define PP_SHADOWTEXTCOLORINDEX                 44
#define PP_SHADOWHILITEFGNDCOLOR                45
#define PP_SHADOWHILITEFGNDCOLORINDEX           46
#define PP_SHADOWHILITEBGNDCOLOR                47
#define PP_SHADOWHILITEBGNDCOLORINDEX           48
#define PP_ICONTEXTBACKGROUNDCOLOR              49
#define PP_ICONTEXTBACKGROUNDCOLORINDEX         50
#define PP_BORDERLIGHTCOLOR                     51
#define PP_BORDERDARKCOLOR                      52
#define PP_BORDER2COLOR                         53
#define PP_BORDER2LIGHTCOLOR                    54
#define PP_BORDER2DARKCOLOR                     55
#define PP_BORDERDEFAULTCOLOR                   56
#define PP_FIELDBACKGROUNDCOLOR                 57
#define PP_BUTTONBACKGROUNDCOLOR                58
#define PP_BUTTONBORDERLIGHTCOLOR               59
#define PP_BUTTONBORDERDARKCOLOR                60
#define PP_ARROWCOLOR                           61
#define PP_ARROWBORDERLIGHTCOLOR                62
#define PP_ARROWBORDERDARKCOLOR                 63
#define PP_ARROWDISABLEDCOLOR                   64
#define PP_CHECKLIGHTCOLOR                      65
#define PP_CHECKMIDDLECOLOR                     66
#define PP_CHECKDARKCOLOR                       67
#define PP_PAGEFOREGROUNDCOLOR                  68
#define PP_PAGEBACKGROUNDCOLOR                  69
#define PP_MAJORTABFOREGROUNDCOLOR              70
#define PP_MAJORTABBACKGROUNDCOLOR              71
#define PP_MINORTABFOREGROUNDCOLOR              72
#define PP_MINORTABBACKGROUNDCOLOR              73
#define PP_BIDI_FIRST                       0x0100
#define PP_BIDI_LAST                        0x012F
#define PP_USER                             0x8000

#define QPF_NOINHERIT     0x0001
#define QPF_ID1COLORINDEX 0x0002
#define QPF_ID2COLORINDEX 0x0004
#define QPF_PURERGBCOLOR  0x0008
#define QPF_VALIDFLAGS    0x000F

#define SYSCLR_SHADOWHILITEBGND      (-50)
#define SYSCLR_SHADOWHILITEFGND      (-49)
#define SYSCLR_SHADOWTEXT            (-48)
#define SYSCLR_ENTRYFIELD            (-47)
#define SYSCLR_MENUDISABLEDTEXT      (-46)
#define SYSCLR_MENUHILITE            (-45)
#define SYSCLR_MENUHILITEBGND        (-44)
#define SYSCLR_PAGEBACKGROUND        (-43)
#define SYSCLR_FIELDBACKGROUND       (-42)
#define SYSCLR_BUTTONLIGHT           (-41)
#define SYSCLR_BUTTONMIDDLE          (-40)
#define SYSCLR_BUTTONDARK            (-39)
#define SYSCLR_BUTTONDEFAULT         (-38)
#define SYSCLR_TITLEBOTTOM           (-37)
#define SYSCLR_SHADOW                (-36)
#define SYSCLR_ICONTEXT              (-35)
#define SYSCLR_DIALOGBACKGROUND      (-34)
#define SYSCLR_HILITEFOREGROUND      (-33)
#define SYSCLR_HILITEBACKGROUND      (-32)
#define SYSCLR_INACTIVETITLETEXTBGND (-31)
#define SYSCLR_ACTIVETITLETEXTBGND   (-30)
#define SYSCLR_INACTIVETITLETEXT     (-29)
#define SYSCLR_ACTIVETITLETEXT       (-28)
#define SYSCLR_OUTPUTTEXT            (-27)
#define SYSCLR_WINDOWSTATICTEXT      (-26)
#define SYSCLR_SCROLLBAR             (-25)
#define SYSCLR_BACKGROUND            (-24)
#define SYSCLR_ACTIVETITLE           (-23)
#define SYSCLR_INACTIVETITLE         (-22)
#define SYSCLR_MENU                  (-21)
#define SYSCLR_WINDOW                (-20)
#define SYSCLR_WINDOWFRAME           (-19)
#define SYSCLR_MENUTEXT              (-18)
#define SYSCLR_WINDOWTEXT            (-17)
#define SYSCLR_TITLETEXT             (-16)
#define SYSCLR_ACTIVEBORDER          (-15)
#define SYSCLR_INACTIVEBORDER        (-14)
#define SYSCLR_APPWORKSPACE          (-13)
#define SYSCLR_HELPBACKGROUND        (-12)
#define SYSCLR_HELPTEXT              (-11)
#define SYSCLR_HELPHILITE            (-10)

#define SYSCLR_CSYSCOLORS 41

typedef struct _PARAM {
    ULONG id;
    ULONG cb;
    BYTE  ab[1];
} PARAM, *PPARAM;

typedef struct _PRESPARAMS {
    ULONG cb;
    PARAM aparam[1];
} PRESPARAMS, *PPRESPARAMS;

ULONG  APIENTRY WinQueryPresParam(HWND hwnd, ULONG idAttrType1, ULONG idAttrType2,
                   PULONG pidAttrTypeFound, ULONG cbAttrValueLen,
                   PPVOID pAttrValue, ULONG flOptions);
LONG   APIENTRY WinQuerySysValue(HWND hwndDeskTop, LONG iSysValue);
BOOL   APIENTRY WinRemovePresParam(HWND hwnd, ULONG idAttrType);
BOOL   APIENTRY WinSetPresParam(HWND hwnd, ULONG idAttrType,
                   ULONG cbAttrValueLen, PVOID pAttrValue);
BOOL   APIENTRY WinSetSysValue(HWND hwndDeskTop, LONG iSysValue, LONG lValue);

#endif

#if defined(INCL_WINTIMER)

#define TID_CURSOR      0xffff
#define TID_SCROLL      0xfffe
#define TID_FLASHWINDOW 0xfffd
#define TID_USERMAX     0x7fff

ULONG  APIENTRY WinGetCurrentTime(HAB);
ULONG  APIENTRY WinStartTimer(HAB,HWND,ULONG,ULONG);
BOOL   APIENTRY WinStopTimer(HAB,HWND,ULONG);

#endif

#if defined(INCL_WINTRACKRECT)

#define TF_LEFT              0x0001
#define TF_TOP               0x0002
#define TF_RIGHT             0x0004
#define TF_BOTTOM            0x0008
#define TF_MOVE              0x000F
#define TF_SETPOINTERPOS     0x0010
#define TF_GRID              0x0020
#define TF_STANDARD          0x0040
#define TF_ALLINBOUNDARY     0x0080
#define TF_VALIDATETRACKRECT 0x0100
#define TF_PARTINBOUNDARY    0x0200

typedef struct _TRACKINFO {
    LONG   cxBorder;
    LONG   cyBorder;
    LONG   cxGrid;
    LONG   cyGrid;
    LONG   cxKeyboard;
    LONG   cyKeyboard;
    RECTL  rclTrack;
    RECTL  rclBoundary;
    POINTL ptlMinTrackSize;
    POINTL ptlMaxTrackSize;
    ULONG  fs;
} TRACKINFO, *PTRACKINFO;

BOOL   APIENTRY WinShowTrackRect(HWND,BOOL);
BOOL   APIENTRY WinTrackRect(HWND,HPS,PTRACKINFO);

#endif

#if defined(INCL_WINCOUNTRY)

PCSZ   APIENTRY WinNextChar(HAB,ULONG,ULONG,PCSZ);
PCSZ   APIENTRY WinPrevChar(HAB,ULONG,ULONG,PCSZ,PCSZ);
ULONG  APIENTRY WinQueryCp(HMQ);
ULONG  APIENTRY WinQueryCpList(HAB,ULONG,PULONG);
BOOL   APIENTRY WinSetCp(HMQ,ULONG);
ULONG  APIENTRY WinUpper(HAB,ULONG,ULONG,PCSZ);
ULONG  APIENTRY WinUpperChar(HAB,ULONG,ULONG,ULONG);

#endif
