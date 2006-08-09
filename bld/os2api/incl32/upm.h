/*
    OS/2 User Profile Management include file for 32-bit development.
*/

#ifndef __UPM_H__
#define __UPM_H__

#include <os2def.h>

#define LSFAR
#define LSPAS
#define LSPTR
#define LSINT  short
#define FARPASCAL
#define ANY_32_BIT

#define UPM_UIDLEN 10
#define UPM_PWDLEN 10
#define UPM_REMLEN 17

#define UPM_LOCAL            1
#define UPM_DNODE            2
#define UPM_DOMAIN           3
#define UPM_DOMAIN_MAX_FORCE 4
#define UPM_DOMAIN_VERBOSE   5

#define UPM_LOCAL_HPFS 21
#define UPM_ALL        22

#define UPM_FL_LOCVER 1
#define UPM_FL_NOVER  2
#define UPM_FL_DOMVER 3

#define UPM_CONFIG 1
#define UPM_ADMIN  2
#define UPM_USER   3

#define UPM_PRIV_USER        1
#define UPM_PRIV_ADMIN       2
#define UPM_PRIV_LOCAL_ADMIN 9

#define UPM_OK                 0
#define UPM_LOG_INPROC         0xFB01
#define UPM_BAD_TYPE           0xFB02
#define UPM_NOMEM              0xFB03
#define UPM_LOG_FILE_NOT_FOUND 0xFB04
#define UPM_FAIL_SECURITY      0xFB05
#define UPM_BAD_PARAMETER      0xFB06
#define UPM_BAD_AUTHCHECK      0xFB07
#define UPM_LOG_CANCEL         0xFB08
#define UPM_NOT_LOGGED         0xFB10
#define UPM_LOGGED             0xFB12
#define UPM_SYS_ERROR          0xFB13
#define UPM_OPEN_SESSIONS      0xFB14
#define UPM_ULP_LOADED         0xFB15
#define UPM_LOGGED_ELSEWHERE   0xFB16
#define UPM_PASSWORD_EXP       0xFB17
#define UPM_UNAVAIL            0xFB18
#define UPM_ACTIVE             0xFB19
#define UPM_SS_PWDEXPWARNING   0xFB20
#define UPM_SS_BUSY            0xFB21
#define UPM_SS_DEAD            0xFB22
#define UPM_ERROR_MORE_DATA    0xFB23
#define UPM_MAX_ENT_EXCEEDED   0xFB24
#define UPM_DUP_ULP_ENTRY      0xFB25
#define UPM_MAX_ULP_EXCEEDED   0xFB26
#define UPM_NODISK             0xFB27
#define UPM_PROF_NOT_FOUND     0xFB28
#define UPM_ERROR_NONVAL_LOGON 0xFB29

#define u32elgn  U32ELGN
#define u32elgff U32ELGFF
#define u32elocu U32ELOCU
#define u32elocl U32ELOCL
#define u32eulgn U32EULGN
#define u32eulgf U32EULGF
#define u32eusrl U32EUSRL
#define u32esetp U32ESETP
#define u32egetp U32EGETP

#pragma pack(1)

struct UPM_G_USER_LOGON {
    USHORT useridlen;
    USHORT remotelen;
    USHORT remotetype;
    LSINT  sessionid;
    CHAR   userid[UPM_UIDLEN+1];
    CHAR   remotename[UPM_REMLEN+1];
};

struct UPM_USER_LOGON {
    CHAR  userid[UPM_UIDLEN+1];
    SHORT remotetype;
    CHAR  remotename[UPM_REMLEN+1];
    LSINT sessionid;
};

struct UPM_USER_LOGON_PROF_0 {
    UCHAR  userid[UPM_UIDLEN+1];
    UCHAR  password[UPM_PWDLEN+1];
    UCHAR  remotename[UPM_REMLEN+1];
    USHORT remotetype;
};

#pragma pack()

LSINT APIENTRY U32ELGN(PUCHAR,PUCHAR,PUCHAR,ULONG,ULONG);
LSINT APIENTRY U32ELGFF(PUCHAR,PUCHAR,ULONG);
LSINT APIENTRY U32ELOCU(PUCHAR,PULONG);
LSINT APIENTRY U32ELOCL(PUCHAR,PULONG);
LSINT APIENTRY U32EULGN(PUCHAR,PUCHAR,PUCHAR,ULONG,ULONG);
LSINT APIENTRY U32EULGF(PUCHAR,PUCHAR,ULONG);
LSINT APIENTRY U32EUSRL(PUCHAR,ULONG,PUCHAR,ULONG,PULONG,PULONG);
LSINT APIENTRY U32ESETP(PUCHAR,PUCHAR,ULONG,ULONG);
LSINT APIENTRY U32EGETP(PUCHAR,PUCHAR,ULONG,PULONG,PULONG,ULONG);

#endif
