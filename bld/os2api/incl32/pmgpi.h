/*
    OS/2 Graphics Programming Interface include file
    for 32-bit development.
*/


#define INCL_GPIINCLUDED

#ifdef INCL_GPI
    #define INCL_GPIBITMAPS
    #define INCL_GPICONTROL
    #define INCL_GPILCIDS
    #define INCL_GPILOGCOLORTABLE
    #define INCL_GPIPATHS
    #define INCL_GPIPOLYGON
    #define INCL_GPIPRIMITIVES
    #define INCL_GPIREGIONS
    #define INCL_GPITRANSFORMS
#endif

#define GPI_ERROR      0
#define GPI_OK         1
#define GPI_ALTERROR (-1)

#define CLR_NOINDEX (-254)

#define FIXEDINT(fx)                 ((SHORT)HIUSHORT(fx))
#define MAKEFIXED(intpart,fractpart) MAKELONG(fractpart,intpart)

typedef struct _SIZEL {
    LONG cx;
    LONG cy;
} SIZEL, *PSIZEL;

#if defined(INCL_GPIBITMAPS)

#define CBM_INIT 4

#define ROP_SRCCOPY     0x00CC
#define ROP_SRCPAINT    0x00EE
#define ROP_SRCAND      0x0088
#define ROP_SRCINVERT   0x0066
#define ROP_SRCERASE    0x0044
#define ROP_NOTSRCCOPY  0x0033
#define ROP_NOTSRCERASE 0x0011
#define ROP_MERGECOPY   0x00C0
#define ROP_MERGEPAINT  0x00BB
#define ROP_PATCOPY     0x00F0
#define ROP_PATPAINT    0x00FB
#define ROP_PATINVERT   0x005A
#define ROP_DSTINVERT   0x0055
#define ROP_ZERO        0x0000
#define ROP_ONE         0x00FF

#define BBO_OR            0
#define BBO_AND           1
#define BBO_IGNORE        2
#define BBO_PAL_COLORS    4
#define BBO_NO_COLOR_INFO 8

#define FF_BOUNDARY 0
#define FF_SURFACE  1

#define BCA_UNCOMP         0
#define BCA_HUFFMAN1D      3
#define BCA_RLE4           2
#define BCA_RLE8           1
#define BCA_RLE24          4
#define BRU_METRIC         0
#define BRA_BOTTOMUP       0
#define BRH_NOTHALFTONED   0
#define BRH_ERRORDIFFUSION 1
#define BRH_PANDA          2
#define BRH_SUPERCIRCLE    3
#define BCE_PALETTE      (-1)
#define BCE_RGB            0

#define BFT_ICON         0x4349
#define BFT_BMAP         0x4d42
#define BFT_POINTER      0x5450
#define BFT_COLORICON    0x4943
#define BFT_COLORPOINTER 0x5043
#define BFT_BITMAPARRAY  0x4142

#define BMB_ERROR (-1)

#pragma pack(1)

typedef struct _RGB {
    BYTE bBlue;
    BYTE bGreen;
    BYTE bRed;
} RGB;

typedef struct _RGB2 {
    BYTE bBlue;
    BYTE bGreen;
    BYTE bRed;
    BYTE fcOptions;
} RGB2;

typedef struct _BITMAPINFO {
    ULONG  cbFix;
    USHORT cx;
    USHORT cy;
    USHORT cPlanes;
    USHORT cBitCount;
    RGB    argbColor[1];
} BITMAPINFO, *PBITMAPINFO;

typedef struct _BITMAPINFO2 {
    ULONG  cbFix;
    ULONG  cx;
    ULONG  cy;
    USHORT cPlanes;
    USHORT cBitCount;
    ULONG  ulCompression;
    ULONG  cbImage;
    ULONG  cxResolution;
    ULONG  cyResolution;
    ULONG  cclrUsed;
    ULONG  cclrImportant;
    USHORT usUnits;
    USHORT usReserved;
    USHORT usRecording;
    USHORT usRendering;
    ULONG  cSize1;
    ULONG  cSize2;
    ULONG  ulColorEncoding;
    ULONG  ulIdentifier;
    RGB2   argbColor[1];
} BITMAPINFO2, *PBITMAPINFO2;

typedef struct _BITMAPINFOHEADER {
    ULONG  cbFix;
    USHORT cx;
    USHORT cy;
    USHORT cPlanes;
    USHORT cBitCount;
} BITMAPINFOHEADER, *PBITMAPINFOHEADER;

typedef struct _BITMAPINFOHEADER2 {
    ULONG  cbFix;
    ULONG  cx;
    ULONG  cy;
    USHORT cPlanes;
    USHORT cBitCount;
    ULONG  ulCompression;
    ULONG  cbImage;
    ULONG  cxResolution;
    ULONG  cyResolution;
    ULONG  cclrUsed;
    ULONG  cclrImportant;
    USHORT usUnits;
    USHORT usReserved;
    USHORT usRecording;
    USHORT usRendering;
    ULONG  cSize1;
    ULONG  cSize2;
    ULONG  ulColorEncoding;
    ULONG  ulIdentifier;
} BITMAPINFOHEADER2, *PBITMAPINFOHEADER2;

typedef struct _BITMAPFILEHEADER {
    USHORT usType;
    ULONG  cbSize;
    SHORT  xHotspot;
    SHORT  yHotspot;
    ULONG  offBits;
    BITMAPINFOHEADER bmp;
} BITMAPFILEHEADER, *PBITMAPFILEHEADER;

typedef struct _BITMAPARRAYFILEHEADER {
    USHORT usType;
    ULONG  cbSize;
    ULONG  offNext;
    USHORT cxDisplay;
    USHORT cyDisplay;
    BITMAPFILEHEADER bfh;
} BITMAPARRAYFILEHEADER, *PBITMAPARRAYFILEHEADER;

typedef struct _BITMAPFILEHEADER2 {
    USHORT usType;
    ULONG  cbSize;
    SHORT  xHotspot;
    SHORT  yHotspot;
    ULONG  offBits;
    BITMAPINFOHEADER2 bmp2;
} BITMAPFILEHEADER2, *PBITMAPFILEHEADER2;

typedef struct _BITMAPARRAYFILEHEADER2 {
    USHORT usType;
    ULONG  cbSize;
    ULONG  offNext;
    USHORT cxDisplay;
    USHORT cyDisplay;
    BITMAPFILEHEADER2 bfh2;
} BITMAPARRAYFILEHEADER2, *PBITMAPARRAYFILEHEADER2;

#pragma pack()

LONG    APIENTRY GpiBitBlt(HPS hpsTarget, HPS hpsSource, LONG lCount,
                    PPOINTL aptlPoints, LONG lRop, ULONG flOptions);
HBITMAP APIENTRY GpiCreateBitmap(HPS hps, PBITMAPINFOHEADER2 pbmpNew, ULONG flOptions,
                   PBYTE pbInitData, PBITMAPINFO2 pbmiInfoTable);
BOOL    APIENTRY GpiDeleteBitmap(HBITMAP hbm);
LONG    APIENTRY GpiFloodFill(HPS hps, LONG lOptions, LONG lColor);
HBITMAP APIENTRY GpiLoadBitmap(HPS hps, HMODULE Resrc, ULONG idBmp, LONG lWidth, LONG lHeight);
LONG    APIENTRY GpiQueryBitmapBits(HPS hps, LONG lScanStart, LONG lScans,
                   PBYTE pbBuffer, PBITMAPINFO2 pbmiInfoTable);
BOOL    APIENTRY GpiQueryBitmapDimension(HBITMAP hbm, PSIZEL psizlBitmapDimension);
HBITMAP APIENTRY GpiQueryBitmapHandle(HPS hps, LONG lLcid);
BOOL    APIENTRY GpiQueryBitmapInfoHeader(HBITMAP hbm, PBITMAPINFOHEADER2 pbmpData);
BOOL    APIENTRY GpiQueryBitmapParameters(HBITMAP hbm, PBITMAPINFOHEADER pbmpData);
BOOL    APIENTRY GpiQueryDeviceBitmapFormats(HPS hps, LONG lCount, PLONG alArray);
LONG    APIENTRY GpiQueryPel(HPS hps, PPOINTL pptlPoint);
HBITMAP APIENTRY GpiSetBitmap(HPS hps, HBITMAP hbm);
LONG    APIENTRY GpiSetBitmapBits(HPS hps, LONG lScanStart, LONG lScans,
                   PBYTE pbBuffer, PBITMAPINFO2 pbmiInfoTable);
BOOL    APIENTRY GpiSetBitmapDimension(HBITMAP hbm, PSIZEL psizlBitmapDimension);
BOOL    APIENTRY GpiSetBitmapId(HPS hps, HBITMAP hbm, LONG lLcid);
LONG    APIENTRY GpiSetPel(HPS hps, PPOINTL pptlPoint);
LONG    APIENTRY GpiWCBitBlt(HPS hpsTarget, HBITMAP hbmSource, LONG lCount,
                   PPOINTL aptlPoints, LONG lRop, ULONG flOptions);

#endif

#if defined(INCL_GPICONTROL)

#define GRES_ATTRS    0x0001
#define GRES_SEGMENTS 0x0002
#define GRES_ALL      0x0004

#define PS_UNITS      0x00FC
#define PS_FORMAT     0x0F00
#define PS_TYPE       0x1000
#define PS_MODE       0x2000
#define PS_ASSOCIATE  0x4000
#define PS_NORESET    0x8000

#define GPIE_SEGMENT     0
#define GPIE_ELEMENT     1
#define GPIE_DATA        2

#define DM_ERROR         0
#define DM_DRAW          1
#define DM_RETAIN        2
#define DM_DRAWANDRETAIN 3

BOOL   APIENTRY GpiAssociate(HPS hps, HDC hdc);
HPS    APIENTRY GpiCreatePS(HAB hab, HDC hdc, PSIZEL psizlSize, ULONG flOptions);
BOOL   APIENTRY GpiDestroyPS(HPS hps);
BOOL   APIENTRY GpiErase(HPS hps);
HDC    APIENTRY GpiQueryDevice(HPS hps);
ULONG  APIENTRY GpiQueryPS(HPS hps, PSIZEL psizlSize);
BOOL   APIENTRY GpiResetPS(HPS hps, ULONG flOptions);
BOOL   APIENTRY GpiRestorePS(HPS hps, LONG lPSid);
LONG   APIENTRY GpiSavePS(HPS hps);

#endif

#if defined(INCL_GPILCIDS) || !defined(INCL_NOCOMMON)

#define PU_ARBITRARY  0x0004
#define PU_PELS       0x0008
#define PU_LOMETRIC   0x000C
#define PU_HIMETRIC   0x0010
#define PU_LOENGLISH  0x0014
#define PU_HIENGLISH  0x0018
#define PU_TWIPS      0x001C

#define GPIF_DEFAULT       0
#define GPIF_SHORT    0x0100
#define GPIF_LONG     0x0200

#define GPIT_NORMAL        0
#define GPIT_MICRO    0x1000
#define GPIT_INK      0x2000

#define GPIA_NOASSOC       0
#define GPIA_ASSOC    0x4000

#define GPIM_AREAEXCL 0x8000

#endif

#if defined(INCL_GPILCIDS)

#define QF_PUBLIC     1
#define QF_PRIVATE    2
#define QF_NO_GENERIC 4
#define QF_NO_DEVICE  8

#define FONT_DEFAULT   1
#define FONT_MATCH     2
#define LCIDT_FONT     6
#define LCIDT_BITMAP   7
#define LCID_ALL     (-1)

LONG   APIENTRY GpiCreateLogFont(HPS hps, PSTR8 pName, LONG lLcid, PFATTRS pfatAttrs);
BOOL   APIENTRY GpiDeleteSetId(HPS hps, LONG lLcid);
ULONG  APIENTRY GpiQueryCp(HPS hps);
LONG   APIENTRY GpiQueryFonts(HPS hps, ULONG flOptions, PCSZ pszFacename, PLONG plReqFonts,
                   LONG lMetricsLength, PFONTMETRICS afmMetrics);
BOOL   APIENTRY GpiQueryFontMetrics(HPS hps, LONG lMetricsLength, PFONTMETRICS pfmMetrics);

#endif

#if defined(INCL_GPILOGCOLORTABLE)

#define LCOL_RESET                   0x0001
#define LCOL_REALIZABLE              0x0002
#define LCOL_PURECOLOR               0x0004
#define LCOL_OVERRIDE_DEFAULT_COLORS 0x0008
#define LCOL_REALIZED                0x0010

#define LCOLF_DEFAULT   0
#define LCOLF_INDRGB    1
#define LCOLF_CONSECRGB 2
#define LCOLF_RGB       3
#define LCOLF_PALETTE   4

#define LCOLOPT_REALIZED 1
#define LCOLOPT_INDEX    2

#define PC_RESERVED   0x01
#define PC_EXPLICIT   0x02
#define PC_NOCOLLAPSE 0x04

LONG   APIENTRY GpiAnimatePalette(HPAL hpal, ULONG ulFormat, ULONG ulStart, ULONG ulCount,
                   PULONG aulTable);
BOOL   APIENTRY GpiCreateLogColorTable(HPS hps, ULONG flOptions, LONG lFormat,
                   LONG lStart, LONG lCount, PLONG alTable);
HPAL   APIENTRY GpiCreatePalette(HAB hab, ULONG flOptions, ULONG ulFormat,
                   ULONG ulCount, PULONG aulTable);
BOOL   APIENTRY GpiDeletePalette(HPAL hpal);
BOOL   APIENTRY GpiQueryColorData(HPS hps, LONG lCount, PLONG alArray);
LONG   APIENTRY GpiQueryColorIndex(HPS hps, ULONG flOptions, LONG lRgbColor);
LONG   APIENTRY GpiQueryLogColorTable(HPS hps, ULONG flOptions, LONG lStart,
                   LONG lCount, PLONG alArray);
LONG   APIENTRY GpiQueryNearestColor(HPS hps, ULONG flOptions, LONG lRgbIn);
LONG   APIENTRY GpiQueryNearestPaletteIndex(HPAL hpal, ULONG color);
HPAL   APIENTRY GpiQueryPalette(HPS hps);
LONG   APIENTRY GpiQueryPaletteInfo(HPAL hpal, HPS hps, ULONG flOptions, ULONG ulStart,
                   ULONG ulCount, PULONG aulArray);
LONG   APIENTRY GpiQueryRealColors(HPS hps, ULONG flOptions, LONG lStart,
                   LONG lCount, PLONG alColors);
LONG   APIENTRY GpiQueryRGBColor(HPS hps, ULONG flOptions, LONG lColorIndex);
HPAL   APIENTRY GpiSelectPalette(HPS hps, HPAL hpal);
BOOL   APIENTRY GpiSetPaletteEntries(HPAL hpal, ULONG ulFormat, ULONG ulStart,
                   ULONG ulCount, PULONG aulTable);
ULONG  APIENTRY GpiResizePalette(HPAL hpal, ULONG newsize);

#endif

#if defined(INCL_GPIPATHS)

#define FPATH_ALTERNATE 0
#define FPATH_WINDING   2
#define FPATH_INCL      0
#define FPATH_EXCL      8

#define MPATH_STROKE 6

#define SCP_ALTERNATE 0
#define SCP_WINDING   2
#define SCP_AND       4
#define SCP_RESET     0
#define SCP_INCL      0
#define SCP_EXCL      8

BOOL   APIENTRY GpiBeginPath(HPS hps, LONG lPath);
BOOL   APIENTRY GpiCloseFigure(HPS hps);
BOOL   APIENTRY GpiEndPath(HPS hps);
LONG   APIENTRY GpiFillPath(HPS hps, LONG lPath, LONG lOptions);
BOOL   APIENTRY GpiModifyPath(HPS hps, LONG lPath, LONG lMode);
LONG   APIENTRY GpiOutlinePath(HPS hps, LONG lPath, LONG lOptions);
HRGN   APIENTRY GpiPathToRegion(HPS GpiH, LONG lPath, LONG lOptions);
BOOL   APIENTRY GpiSetClipPath(HPS hps, LONG lPath, LONG lOptions);
LONG   APIENTRY GpiStrokePath(HPS hps, LONG lPath, ULONG flOptions);

#endif

#if defined(INCL_GPIPOLYGON)

#define POLYGON_NOBOUNDARY  0
#define POLYGON_BOUNDARY    1
#define POLYGON_ALTERNATE   0
#define POLYGON_WINDING     2
#define POLYGON_INCL        0
#define POLYGON_EXCL        8
#define POLYGON_FILL        0
#define POLYGON_NOFILL     16

typedef struct _POLYGON {
    ULONG   ulPoints;
    PPOINTL aPointl;
} POLYGON, *PPOLYGON;

typedef struct _POLYSET {
    ULONG   ulPolys;
    POLYGON aPolygon[1];
} POLYSET, *PPOLYSET;

LONG   APIENTRY GpiPolygons(HPS hps, ULONG ulCount, PPOLYGON paplgn, ULONG flOpts, ULONG flMdl);

#endif

#if defined(INCL_GPIPRIMITIVES) || !defined(INCL_NOCOMMON)

#define BA_NOBOUNDARY 0
#define BA_BOUNDARY   1
#define BA_ALTERNATE  0
#define BA_WINDING    2
#define BA_INCL       0
#define BA_EXCL       8

#define CHS_OPAQUE     0x0001
#define CHS_VECTOR     0x0002
#define CHS_LEAVEPOS   0x0008
#define CHS_CLIP       0x0010
#define CHS_UNDERSCORE 0x0200
#define CHS_STRIKEOUT  0x0400

#define CLR_ERROR      (-255)
#define CLR_FALSE        (-5)
#define CLR_TRUE         (-4)
#define CLR_DEFAULT      (-3)
#define CLR_WHITE        (-2)
#define CLR_BLACK        (-1)
#define CLR_BACKGROUND     0
#define CLR_BLUE           1
#define CLR_RED            2
#define CLR_PINK           3
#define CLR_GREEN          4
#define CLR_CYAN           5
#define CLR_YELLOW         6
#define CLR_NEUTRAL        7
#define CLR_DARKGRAY       8
#define CLR_DARKBLUE       9
#define CLR_DARKRED       10
#define CLR_DARKPINK      11
#define CLR_DARKGREEN     12
#define CLR_DARKCYAN      13
#define CLR_BROWN         14
#define CLR_PALEGRAY      15

#define DRO_FILL        1
#define DRO_OUTLINE     2
#define DRO_OUTLINEFILL 3
#define DRO_EXCLUSIVE   0x10000000

#define FM_ERROR         (-1)
#define FM_DEFAULT         0
#define FM_OR              1
#define FM_OVERPAINT       2
#define FM_XOR             4
#define FM_LEAVEALONE      5
#define FM_AND             6
#define FM_SUBTRACT        7
#define FM_MASKSRCNOT      8
#define FM_ZERO            9
#define FM_NOTMERGESRC    10
#define FM_NOTXORSRC      11
#define FM_INVERT         12
#define FM_MERGESRCNOT    13
#define FM_NOTCOPYSRC     14
#define FM_MERGENOTSRC    15
#define FM_NOTMASKSRC     16
#define FM_ONE            17

#define BM_ERROR          (-1)
#define BM_DEFAULT          0
#define BM_OR               1
#define BM_OVERPAINT        2
#define BM_XOR              4
#define BM_LEAVEALONE       5
#define BM_AND              6
#define BM_SUBTRACT         7
#define BM_MASKSRCNOT       8
#define BM_ZERO             9
#define BM_NOTMERGESRC     10
#define BM_NOTXORSRC       11
#define BM_INVERT          12
#define BM_MERGESRCNOT     13
#define BM_NOTCOPYSRC      14
#define BM_MERGENOTSRC     15
#define BM_NOTMASKSRC      16
#define BM_ONE             17
#define BM_SRCTRANSPARENT  18
#define BM_DESTTRANSPARENT 19

#define LCID_ERROR   (-1)
#define LCID_DEFAULT   0

#define PATSYM_ERROR    (-1)
#define PATSYM_DEFAULT    0
#define PATSYM_DENSE1     1
#define PATSYM_DENSE2     2
#define PATSYM_DENSE3     3
#define PATSYM_DENSE4     4
#define PATSYM_DENSE5     5
#define PATSYM_DENSE6     6
#define PATSYM_DENSE7     7
#define PATSYM_DENSE8     8
#define PATSYM_VERT       9
#define PATSYM_HORIZ     10
#define PATSYM_DIAG1     11
#define PATSYM_DIAG2     12
#define PATSYM_DIAG3     13
#define PATSYM_DIAG4     14
#define PATSYM_NOSHADE   15
#define PATSYM_SOLID     16
#define PATSYM_HALFTONE  17
#define PATSYM_HATCH     18
#define PATSYM_DIAGHATCH 19
#define PATSYM_BLANK     64

#define RGB_ERROR       (-255)
#define RGB_BLACK  0x00000000
#define RGB_BLUE   0x000000FF
#define RGB_GREEN  0x0000FF00
#define RGB_CYAN   0x0000FFFF
#define RGB_RED    0x00FF0000
#define RGB_PINK   0x00FF00FF
#define RGB_YELLOW 0x00FFFF00
#define RGB_WHITE  0x00FFFFFF

#define TXTBOX_TOPLEFT     0
#define TXTBOX_BOTTOMLEFT  1
#define TXTBOX_TOPRIGHT    2
#define TXTBOX_BOTTOMRIGHT 3
#define TXTBOX_CONCAT      4
#define TXTBOX_COUNT       5

BOOL   APIENTRY GpiBeginArea(HPS hps, ULONG flOptions);
LONG   APIENTRY GpiEndArea(HPS hps);
LONG   APIENTRY GpiBox(HPS hps, LONG lControl, PPOINTL pptlPoint, LONG lHRound, LONG lVRound);
LONG   APIENTRY GpiLine(HPS hps, PPOINTL pptlEndPoint);
BOOL   APIENTRY GpiMove(HPS hps, PPOINTL pptlPoint);
LONG   APIENTRY GpiPolyLine(HPS hps, LONG lCount, PPOINTL aptlPoints);
LONG   APIENTRY GpiPolyLineDisjoint(HPS hps, LONG lCount, PPOINTL aptlPoints);
LONG   APIENTRY GpiQueryColor(HPS hps);
LONG   APIENTRY GpiQueryPattern(HPS hps);
BOOL   APIENTRY GpiSetColor(HPS hps, LONG lColor);
BOOL   APIENTRY GpiSetPattern(HPS hps, LONG lPatternSymbol);
LONG   APIENTRY GpiCharString(HPS hps, LONG lCount, PCH pchString);
LONG   APIENTRY GpiCharStringAt(HPS hps, PPOINTL pptlPoint, LONG lCount, PCH pchString);

#endif

#if defined(INCL_GPIPRIMITIVES)

#define CM_ERROR   (-1)
#define CM_DEFAULT   0
#define CM_MODE1     1
#define CM_MODE2     2
#define CM_MODE3     3

#define LINETYPE_ERROR       (-1)
#define LINETYPE_DEFAULT       0
#define LINETYPE_DOT           1
#define LINETYPE_SHORTDASH     2
#define LINETYPE_DASHDOT       3
#define LINETYPE_DOUBLEDOT     4
#define LINETYPE_LONGDASH      5
#define LINETYPE_DASHDOUBLEDOT 6
#define LINETYPE_SOLID         7
#define LINETYPE_INVISIBLE     8
#define LINETYPE_ALTERNATE     9

#define LINEWIDTH_ERROR          (-1)
#define LINEWIDTH_DEFAULT          0
#define LINEWIDTH_NORMAL  0x00010000
#define LINEWIDTH_THICK   0x00020000

#define LINEWIDTHGEOM_ERROR (-1)

#define LINEEND_ERROR     (-1)
#define LINEEND_DEFAULT     0
#define LINEEND_FLAT        1
#define LINEEND_SQUARE      2
#define LINEEND_ROUND       3

#define LINEJOIN_ERROR    (-1)
#define LINEJOIN_DEFAULT    0
#define LINEJOIN_BEVEL      1
#define LINEJOIN_ROUND      2
#define LINEJOIN_MITRE      3

#define CHDIRN_ERROR      (-1)
#define CHDIRN_DEFAULT      0
#define CHDIRN_LEFTRIGHT    1
#define CHDIRN_TOPBOTTOM    2
#define CHDIRN_RIGHTLEFT    3
#define CHDIRN_BOTTOMTOP    4

#define PRIM_LINE   1
#define PRIM_CHAR   2
#define PRIM_MARKER 3
#define PRIM_AREA   4
#define PRIM_IMAGE  5

#define LBB_COLOR         0x0001
#define LBB_BACK_COLOR    0x0002
#define LBB_MIX_MODE      0x0004
#define LBB_BACK_MIX_MODE 0x0008
#define LBB_WIDTH         0x0010
#define LBB_GEOM_WIDTH    0x0020
#define LBB_TYPE          0x0040
#define LBB_END           0x0080
#define LBB_JOIN          0x0100

#define CBB_COLOR         0x0001
#define CBB_BACK_COLOR    0x0002
#define CBB_MIX_MODE      0x0004
#define CBB_BACK_MIX_MODE 0x0008
#define CBB_SET           0x0010
#define CBB_MODE          0x0020
#define CBB_BOX           0x0040
#define CBB_ANGLE         0x0080
#define CBB_SHEAR         0x0100
#define CBB_DIRECTION     0x0200
#define CBB_TEXT_ALIGN    0x0400
#define CBB_EXTRA         0x0800
#define CBB_BREAK_EXTRA   0x1000

#define MBB_COLOR         0x0001
#define MBB_BACK_COLOR    0x0002
#define MBB_MIX_MODE      0x0004
#define MBB_BACK_MIX_MODE 0x0008
#define MBB_SET           0x0010
#define MBB_SYMBOL        0x0020
#define MBB_BOX           0x0040

#define ABB_COLOR         0x0001
#define ABB_BACK_COLOR    0x0002
#define ABB_MIX_MODE      0x0004
#define ABB_BACK_MIX_MODE 0x0008
#define ABB_SET           0x0010
#define ABB_SYMBOL        0x0020
#define ABB_REF_POINT     0x0040

#define IBB_COLOR         0x0001
#define IBB_BACK_COLOR    0x0002
#define IBB_MIX_MODE      0x0004
#define IBB_BACK_MIX_MODE 0x0008

#define TA_NORMAL_HORIZ   0x0001
#define TA_LEFT           0x0002
#define TA_CENTER         0x0003
#define TA_RIGHT          0x0004
#define TA_STANDARD_HORIZ 0x0005
#define TA_NORMAL_VERT    0x0100
#define TA_TOP            0x0200
#define TA_HALF           0x0300
#define TA_BASE           0x0400
#define TA_BOTTOM         0x0500
#define TA_STANDARD_VERT  0x0600

typedef PVOID PBUNDLE;

typedef struct _SIZEF {
    FIXED  cx;
    FIXED  cy;
} SIZEF, *PSIZEF;

typedef struct _ARCPARAMS {
    LONG lP;
    LONG lQ;
    LONG lR;
    LONG lS;
} ARCPARAMS, *PARCPARAMS;

typedef struct _AREABUNDLE {
    LONG   lColor;
    LONG   lBackColor;
    USHORT usMixMode;
    USHORT usBackMixMode;
    USHORT usSet;
    USHORT usSymbol;
    POINTL ptlRefPoint;
} AREABUNDLE, *PAREABUNDLE;

typedef struct _CHARBUNDLE {
    LONG   lColor;
    LONG   lBackColor;
    USHORT usMixMode;
    USHORT usBackMixMode;
    USHORT usSet;
    USHORT usPrecision;
    SIZEF  sizfxCell;
    POINTL ptlAngle;
    POINTL ptlShear;
    USHORT usDirection;
    USHORT usTextAlign;
    FIXED  fxExtra;
    FIXED  fxBreakExtra;
} CHARBUNDLE, *PCHARBUNDLE;

typedef struct _IMAGEBUNDLE {
    LONG   lColor;
    LONG   lBackColor;
    USHORT usMixMode;
    USHORT usBackMixMode;
} IMAGEBUNDLE, *PIMAGEBUNDLE;

typedef struct _LINEBUNDLE {
    LONG   lColor;
    LONG   lBackColor;
    USHORT usMixMode;
    USHORT usBackMixMode;
    FIXED  fxWidth;
    LONG   lGeomWidth;
    USHORT usType;
    USHORT usEnd;
    USHORT usJoin;
    USHORT usReserved;
} LINEBUNDLE, *PLINEBUNDLE;

typedef struct _MARKERBUNDLE {
    LONG   lColor;
    LONG   lBackColor;
    USHORT usMixMode;
    USHORT usBackMixMode;
    USHORT usSet;
    USHORT usSymbol;
    SIZEF  sizfxCell;
} MARKERBUNDLE, *PMARKERBUNDLE;

typedef struct _GRADIENTL {
    LONG     x;
    LONG     y;
} GRADIENTL, *PGRADIENTL;

LONG   APIENTRY GpiCharStringPos(HPS hps, PRECTL prclRect, ULONG flOptions, LONG lCount,
                   PCH pchString, PLONG alAdx);
LONG   APIENTRY GpiCharStringPosAt(HPS hps, PPOINTL pptlStart, PRECTL prclRect,
                   ULONG flOptions, LONG lCount, PCH pchString, PLONG alAdx);
BOOL   APIENTRY GpiComment(HPS hps, LONG lLength, PBYTE pbData);
LONG   APIENTRY GpiFullArc(HPS hps, LONG lControl, FIXED fxMultiplier);
LONG   APIENTRY GpiPartialArc(HPS hps, PPOINTL pptlCenter, FIXED fxMultiplier,
                   FIXED fxStartAngle, FIXED fxSweepAngle);
LONG   APIENTRY GpiQueryAttrs(HPS hps, LONG lPrimType, ULONG flAttrMask, PBUNDLE ppbunAttrs);
LONG   APIENTRY GpiQueryBackColor(HPS hps);
LONG   APIENTRY GpiQueryBackMix(HPS hps);
BOOL   APIENTRY GpiQueryCharAngle(HPS hps, PGRADIENTL pgradlAngle);
BOOL   APIENTRY GpiQueryCharBox(HPS hps, PSIZEF sizfxSize);
BOOL   APIENTRY GpiQueryCharBreakExtra(HPS hps, PFIXED BreakExtra);
LONG   APIENTRY GpiQueryCharDirection(HPS hps);
BOOL   APIENTRY GpiQueryCharExtra(HPS hps, PFIXED Extra);
LONG   APIENTRY GpiQueryCharMode(HPS hps);
LONG   APIENTRY GpiQueryCharSet(HPS hps);
BOOL   APIENTRY GpiQueryCharShear(HPS hps, PPOINTL pptlShear);
BOOL   APIENTRY GpiQueryCharStringPos(HPS hps, ULONG flOptions, LONG lCount,
                   PCH pchString, PLONG alXincrements, PPOINTL aptlPositions);
BOOL   APIENTRY GpiQueryCharStringPosAt(HPS hps, PPOINTL pptlStart, ULONG flOptions, LONG lCount,
                   PCH pchString, PLONG alXincrements, PPOINTL aptlPositions);
LONG   APIENTRY GpiQueryClipBox(HPS hps, PRECTL prclBound);
HRGN   APIENTRY GpiQueryClipRegion(HPS hps);
BOOL   APIENTRY GpiQueryCurrentPosition(HPS hps, PPOINTL pptlPoint);
BOOL   APIENTRY GpiQueryDefCharBox(HPS hps, PSIZEL psizlSize);
LONG   APIENTRY GpiQueryLineEnd(HPS hps);
LONG   APIENTRY GpiQueryLineJoin(HPS hps);
LONG   APIENTRY GpiQueryLineType(HPS hps);
FIXED  APIENTRY GpiQueryLineWidth(HPS hps);
LONG   APIENTRY GpiQueryLineWidthGeom(HPS hps);
LONG   APIENTRY GpiQueryMix(HPS hps);
BOOL   APIENTRY GpiQueryTextAlignment(HPS hps, PLONG plHoriz, PLONG plVert);
BOOL   APIENTRY GpiQueryTextBox(HPS hps, LONG lCount1, PCH pchString,
                   LONG lCount2, PPOINTL aptlPoints);
LONG   APIENTRY GpiRectVisible(HPS hps, PRECTL prclRectangle);
BOOL   APIENTRY GpiSetArcParams(HPS hps, PARCPARAMS parcpArcParams);
BOOL   APIENTRY GpiSetAttrs(HPS hps, LONG lPrimType, ULONG flAttrMask,
                   ULONG flDefMask, PBUNDLE ppbunAttrs);
BOOL   APIENTRY GpiSetBackColor(HPS hps, LONG lColor);
BOOL   APIENTRY GpiSetBackMix(HPS hps, LONG lMixMode);
BOOL   APIENTRY GpiSetCharBox(HPS hps, PSIZEF psizfxBox);
BOOL   APIENTRY GpiSetCharBreakExtra(HPS hps, FIXED BreakExtra);
BOOL   APIENTRY GpiSetCharDirection(HPS hps, LONG lDirection);
BOOL   APIENTRY GpiSetCharExtra(HPS hps, FIXED Extra);
BOOL   APIENTRY GpiSetCharMode(HPS hps, LONG lMode);
BOOL   APIENTRY GpiSetCharSet(HPS hps, LONG llcid);
BOOL   APIENTRY GpiSetCharShear(HPS hps, PPOINTL pptlAngle);
BOOL   APIENTRY GpiSetCurrentPosition(HPS hps, PPOINTL pptlPoint);
BOOL   APIENTRY GpiSetLineEnd(HPS hps, LONG lLineEnd);
BOOL   APIENTRY GpiSetLineJoin(HPS hps, LONG lLineJoin);
BOOL   APIENTRY GpiSetLineType(HPS hps, LONG lLineType);
BOOL   APIENTRY GpiSetLineWidth(HPS hps, FIXED fxLineWidth);
BOOL   APIENTRY GpiSetLineWidthGeom(HPS hps, LONG lLineWidth);
BOOL   APIENTRY GpiSetMarker(HPS hps, LONG lSymbol);
BOOL   APIENTRY GpiSetMarkerBox(HPS hps, PSIZEF psizfxSize);
BOOL   APIENTRY GpiSetMarkerSet(HPS hps, LONG lSet);
BOOL   APIENTRY GpiSetMix(HPS hps, LONG lMixMode);
BOOL   APIENTRY GpiSetPatternRefPoint(HPS hps, PPOINTL pptlRefPoint);
BOOL   APIENTRY GpiSetPatternSet(HPS hps, LONG lSet);
BOOL   APIENTRY GpiSetTextAlignment(HPS hps, LONG lHoriz, LONG lVert);

#endif

#if defined(INCL_GPIREGIONS)

#define CRGN_OR   1
#define CRGN_COPY 2
#define CRGN_XOR  4
#define CRGN_AND  6
#define CRGN_DIFF 7

#define EQRGN_ERROR    0
#define EQRGN_NOTEQUAL 1
#define EQRGN_EQUAL    2

#define HRGN_ERROR ((HRGN)-1)

#define PRGN_ERROR   0
#define PRGN_OUTSIDE 1
#define PRGN_INSIDE  2

#define RECTDIR_LFRT_TOPBOT 1
#define RECTDIR_RTLF_TOPBOT 2
#define RECTDIR_LFRT_BOTTOP 3
#define RECTDIR_RTLF_BOTTOP 4

#define RGN_ERROR   0
#define RGN_NULL    1
#define RGN_RECT    2
#define RGN_COMPLEX 3

#define RRGN_ERROR   0
#define RRGN_OUTSIDE 1
#define RRGN_PARTIAL 2
#define RRGN_INSIDE  3

typedef struct _RGNRECT {
    ULONG ircStart;
    ULONG crc;
    ULONG crcReturned;
    ULONG ulDirection;
} RGNRECT, *PRGNRECT;

LONG   APIENTRY GpiCombineRegion(HPS hps, HRGN hrgnDest, HRGN hrgnSr1, HRGN hrgnSr2, LONG lMode);
HRGN   APIENTRY GpiCreateEllipticRegion(HPS hps, PRECTL prclRect);
HRGN   APIENTRY GpiCreateRegion(HPS hps, LONG lCount, PRECTL arclRectangles);
HRGN   APIENTRY GpiCreateRoundRectRegion(HPS hps, PPOINTL pptlPt, LONG lHround, LONG lVRound);
BOOL   APIENTRY GpiDestroyRegion(HPS hps, HRGN hrgn);
LONG   APIENTRY GpiEqualRegion(HPS hps, HRGN hrgnSrc1, HRGN hrgnSrc2);
LONG   APIENTRY GpiExcludeClipRectangle(HPS hps, PRECTL prclRectangle);
LONG   APIENTRY GpiIntersectClipRectangle(HPS hps, PRECTL prclRectangle);
LONG   APIENTRY GpiFrameRegion(HPS hps, HRGN hrgn, PSIZEL thickness);
LONG   APIENTRY GpiOffsetClipRegion(HPS hps, PPOINTL pptlPoint);
BOOL   APIENTRY GpiOffsetRegion(HPS hps, HRGN Hrgn, PPOINTL pptlOffset);
LONG   APIENTRY GpiPaintRegion(HPS hps, HRGN hrgn);
LONG   APIENTRY GpiPtInRegion(HPS hps, HRGN hrgn, PPOINTL pptlPoint);
LONG   APIENTRY GpiQueryClipBox(HPS hps, PRECTL prclBound);
HRGN   APIENTRY GpiQueryClipRegion(HPS hps);
LONG   APIENTRY GpiQueryRegionBox(HPS hps, HRGN hrgn, PRECTL prclBound);
BOOL   APIENTRY GpiQueryRegionRects(HPS hps, HRGN hrgn, PRECTL prclBound,
                   PRGNRECT prgnrcControl, PRECTL prclRect);
LONG   APIENTRY GpiRectInRegion(HPS hps, HRGN hrgn, PRECTL prclRect);
LONG   APIENTRY GpiSetClipRegion(HPS hps, HRGN hrgn, PHRGN phrgnOld);
BOOL   APIENTRY GpiSetRegion(HPS hps, HRGN hrgn, LONG lcount, PRECTL arclRectangles);

#endif

#if defined(INCL_GPITRANSFORMS)

#define CVTC_WORLD        1
#define CVTC_MODEL        2
#define CVTC_DEFAULTPAGE  3
#define CVTC_PAGE         4
#define CVTC_DEVICE       5

#define TRANSFORM_REPLACE 0
#define TRANSFORM_ADD     1
#define TRANSFORM_PREEMPT 2

BOOL   APIENTRY GpiConvert(HPS hps, LONG lSrc, LONG lTarg, LONG lCount, PPOINTL aptlPoints);
BOOL   APIENTRY GpiConvertWithMatrix(HPS hps, LONG lCountp, PPOINTL aptlPoints, LONG lCount,
                   PMATRIXLF pmatlfArray);
BOOL   APIENTRY GpiQueryGraphicsField(HPS hps, PRECTL prclField);
BOOL   APIENTRY GpiQueryModelTransformMatrix(HPS hps, LONG lCount, PMATRIXLF pmatlfArray);
BOOL   APIENTRY GpiQueryPageViewport(HPS hps, PRECTL prclViewport);
BOOL   APIENTRY GpiQuerySegmentTransformMatrix(HPS hps, LONG lSegid, LONG lCount,
                   PMATRIXLF pmatlfArray);
BOOL   APIENTRY GpiQueryViewingLimits(HPS hps, PRECTL prclLimits);
BOOL   APIENTRY GpiRotate(HPS, PMATRIXLF, LONG, FIXED, PPOINTL);
BOOL   APIENTRY GpiScale(HPS, PMATRIXLF, LONG, PFIXED, PPOINTL);
BOOL   APIENTRY GpiSetGraphicsField(HPS hps, PRECTL prclField);
BOOL   APIENTRY GpiSetModelTransformMatrix(HPS hps, LONG lCount,
                   PMATRIXLF pmatlfArray, LONG lOptions);
BOOL   APIENTRY GpiSetPageViewport(HPS hps, PRECTL prclViewport);
BOOL   APIENTRY GpiSetSegmentTransformMatrix(HPS hps, LONG lSegid, LONG lCount,
                   PMATRIXLF pmatlfarray, LONG lOptions);
BOOL   APIENTRY GpiSetViewingLimits(HPS hps, PRECTL prclLimits);
BOOL   APIENTRY GpiTranslate(HPS, PMATRIXLF, LONG, PPOINTL);

#endif
