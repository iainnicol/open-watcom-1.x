/*
    OS/2 Presentation Manager Advanced VIO include file
    for 32-bit development.
*/


#ifndef __PMAVIO_H__
#define __PMAVIO_H__

#define VioAssociate           VIO16ASSOCIATE
#define VioCreateLogFont       VIO16CREATELOGFONT
#define VioCreatePS            VIO16CREATEPS
#define VioDeleteSetId         VIO16DELETESETID
#define VioDestroyPS           VIO16DESTROYPS
#define VioGetDeviceCellSize   VIO16GETDEVICECELLSIZE
#define VioGetOrg              VIO16GETORG
#define VioQueryFonts          VIO16QUERYFONTS
#define VioQuerySetIds         VIO16QUERYSETIDS
#define VioSetDeviceCellSize   VIO16SETDEVICECELLSIZE
#define VioSetOrg              VIO16SETORG
#define VioShowPS              VIO16SHOWPS
#define WinDefAVioWindowProc   WIN16DEFAVIOWINDOWPROC

typedef USHORT  HVPS, *PHVPS;

USHORT  APIENTRY16 VioAssociate(HDC hdc, HVPS hvps);
USHORT  APIENTRY16 VioCreateLogFont(PFATTRS pfatattrs, LONG llcid, PSTR8 pName, HVPS hvps);
USHORT  APIENTRY16 VioCreatePS(PHVPS phvps, SHORT sdepth, SHORT swidth, SHORT sFormat,
                      SHORT sAttrs, HVPS hvpsReserved);
USHORT  APIENTRY16 VioDeleteSetId(LONG llcid, HVPS hvps);
USHORT  APIENTRY16 VioDestroyPS(HVPS hvps);
USHORT  APIENTRY16 VioGetDeviceCellSize(PSHORT psHeight, PSHORT psWidth, HVPS hvps);
USHORT  APIENTRY16 VioGetOrg(PSHORT psRow, PSHORT psColumn, HVPS hvps);
USHORT  APIENTRY16 VioQueryFonts(PLONG plRemfonts, PFONTMETRICS afmMetrics, LONG lMetricsLength,
                      PLONG plFonts, PSZ pszFacename, ULONG flOptions, HVPS hvps);
USHORT  APIENTRY16 VioQuerySetIds(PLONG allcids, PSTR8 pNames, PLONG alTypes, LONG lcount, HVPS hvps);
USHORT  APIENTRY16 VioSetDeviceCellSize(SHORT sHeight, SHORT sWidth, HVPS hvps);
USHORT  APIENTRY16 VioSetOrg(SHORT sRow, SHORT sColumn, HVPS hvps);
USHORT  APIENTRY16 VioShowPS(SHORT sDepth, SHORT sWidth, SHORT soffCell, HVPS hvps);

MRESULT APIENTRY16 WinDefAVioWindowProc(HWND hwnd, USHORT msg, ULONG mp1, ULONG mp2);

#endif

