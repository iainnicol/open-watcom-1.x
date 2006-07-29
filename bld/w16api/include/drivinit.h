#ifndef	_INC_DRIVINIT
#define	_INC_DRIVINIT

#ifndef	_INC_WINDOWS
#include <windows.h>
#endif

#ifdef	__cplusplus
extern	"C"	{
#endif

#pragma pack(push,1)

/* mode selections for the device mode function */
#define DM_UPDATE           1
#define DM_COPY             2
#define DM_PROMPT           4
#define DM_MODIFY           8

#define DM_IN_BUFFER        DM_MODIFY
#define DM_IN_PROMPT        DM_PROMPT
#define DM_OUT_BUFFER       DM_COPY
#define DM_OUT_DEFAULT      DM_UPDATE

/* size of a device name string */
#define CCHDEVICENAME 32
#define CCHPAPERNAME  64

typedef struct tagDEVMODE
{
    char  dmDeviceName[CCHDEVICENAME];
    UINT  dmSpecVersion;
    UINT  dmDriverVersion;
    UINT  dmSize;
    UINT  dmDriverExtra;
    DWORD dmFields;
    int   dmOrientation;
    int   dmPaperSize;
    int   dmPaperLength;
    int   dmPaperWidth;
    int   dmScale;
    int   dmCopies;
    int   dmDefaultSource;
    int   dmPrintQuality;
    int   dmColor;
    int   dmDuplex;
    int   dmYResolution;
    int   dmTTOption;
} DEVMODE,*PDEVMODE,NEAR *NPDEVMODE,FAR *LPDEVMODE;


#pragma pack(pop)

#ifdef	__cplusplus
}
#endif

#endif

