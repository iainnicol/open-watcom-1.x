#ifndef	__CUSTCNTL_H
#define	__CUSTCNTL_H

#ifndef	__WINDOWS_H
#include <windows.h>
#endif

#pragma	pack(push,1)

#ifdef	__cplusplus
extern	"C" {
#endif

#define	CCINFOORD	2
#define	CCSTYLEORD	3
#define	CCFLAGSORD	4
#define	CTLTYPES	12
#define	CTLDESCR	22
#define	CTLCLASS	20
#define	CTLTITLE	94

typedef	struct tagCTLSTYLE {
	UINT	wX;
	UINT	wY;
	UINT	wCx;
	UINT	wCy;
	UINT	wId;
	DWORD	dwStyle;
	char	szClass[CTLCLASS];
	char	szTitle[CTLTITLE];
} CTLSTYLE;
typedef	struct tagCTLTYPE {
	UINT	wType;
	UINT	wWidth;
	UINT	wHeight;
	DWORD	dwStyle;
	char	szDescr[CTLDESCR];
} CTLTYPE;
typedef	struct tagCTLINFO {
	UINT	wVersion;
	UINT	wCtlTypes;
	char	szClass[CTLCLASS];
	char	szTitle[CTLTITLE];
	char	szReserved[10];
	CTLTYPE	Type[CTLTYPES];
} CTLINFO;
typedef	CTLSTYLE *PCTLSTYLE;
typedef	CTLSTYLE FAR *LPCTLSTYLE;
typedef	CTLINFO *PCTLINFO;
typedef	CTLINFO FAR *LPCTLINFO;

#ifdef STRICT
typedef	DWORD (CALLBACK *LPFNSTRTOID)(LPCSTR);
#else
typedef	DWORD (CALLBACK *LPFNSTRTOID)(LPSTR);
#endif
typedef	UINT (CALLBACK *LPFNIDTOSTR)(UINT,LPSTR,UINT);

#ifdef	__cplusplus
}
#endif

#pragma	pack(pop)

#endif
