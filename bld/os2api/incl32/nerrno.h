/*
    OS/2 socket API error constants
*/


#ifndef _NERRNO_H_
#define _NERRNO_H_

#ifdef KERNEL
#define SOCBASEERR 0
#else
#define SOCBASEERR 10000
#endif

#define SOCEPERM           (SOCBASEERR+1)
#define SOCENOENT          (SOCBASEERR+2)
#define SOCESRCH           (SOCBASEERR+3)
#define SOCEINTR           (SOCBASEERR+4)
#define SOCEIO             (SOCBASEERR+5)
#define SOCENXIO           (SOCBASEERR+6)
#define SOCE2BIG           (SOCBASEERR+7)
#define SOCENOEXEC         (SOCBASEERR+8)
#define SOCEBADF           (SOCBASEERR+9)
#define SOCECHILD          (SOCBASEERR+10)
#define SOCEDEADLK         (SOCBASEERR+11)
#define SOCENOMEM          (SOCBASEERR+12)
#define SOCEACCES          (SOCBASEERR+13)
#define SOCEFAULT          (SOCBASEERR+14)
#define SOCENOTBLK         (SOCBASEERR+15)
#define SOCEBUSY           (SOCBASEERR+16)
#define SOCEEXIST          (SOCBASEERR+17)
#define SOCEXDEV           (SOCBASEERR+18)
#define SOCENODEV          (SOCBASEERR+19)
#define SOCENOTDIR         (SOCBASEERR+20)
#define SOCEISDIR          (SOCBASEERR+21)
#define SOCEINVAL          (SOCBASEERR+22)
#define SOCENFILE          (SOCBASEERR+23)
#define SOCEMFILE          (SOCBASEERR+24)
#define SOCENOTTY          (SOCBASEERR+25)
#define SOCETXTBSY         (SOCBASEERR+26)
#define SOCEFBIG           (SOCBASEERR+27)
#define SOCENOSPC          (SOCBASEERR+28)
#define SOCESPIPE          (SOCBASEERR+29)
#define SOCEROFS           (SOCBASEERR+30)
#define SOCEMLINK          (SOCBASEERR+31)
#define SOCEPIPE           (SOCBASEERR+32)
#define SOCEDOM            (SOCBASEERR+33)
#define SOCERANGE          (SOCBASEERR+34)
#define SOCEAGAIN          (SOCBASEERR+35)
#define SOCEWOULDBLOCK     SOCEAGAIN
#define SOCEINPROGRESS     (SOCBASEERR+36)
#define SOCEALREADY        (SOCBASEERR+37)
#define SOCENOTSOCK        (SOCBASEERR+38)
#define SOCEDESTADDRREQ    (SOCBASEERR+39)
#define SOCEMSGSIZE        (SOCBASEERR+40)
#define SOCEPROTOTYPE      (SOCBASEERR+41)
#define SOCENOPROTOOPT     (SOCBASEERR+42)
#define SOCEPROTONOSUPPORT (SOCBASEERR+43)
#define SOCESOCKTNOSUPPORT (SOCBASEERR+44)
#define SOCEOPNOTSUPP      (SOCBASEERR+45)
#define SOCEPFNOSUPPORT    (SOCBASEERR+46)
#define SOCEAFNOSUPPORT    (SOCBASEERR+47)
#define SOCEADDRINUSE      (SOCBASEERR+48)
#define SOCEADDRNOTAVAIL   (SOCBASEERR+49)
#define SOCENETDOWN        (SOCBASEERR+50)
#define SOCENETUNREACH     (SOCBASEERR+51)
#define SOCENETRESET       (SOCBASEERR+52)
#define SOCECONNABORTED    (SOCBASEERR+53)
#define SOCECONNRESET      (SOCBASEERR+54)
#define SOCENOBUFS         (SOCBASEERR+55)
#define SOCEISCONN         (SOCBASEERR+56)
#define SOCENOTCONN        (SOCBASEERR+57)
#define SOCESHUTDOWN       (SOCBASEERR+58)
#define SOCETOOMANYREFS    (SOCBASEERR+59)
#define SOCETIMEDOUT       (SOCBASEERR+60)
#define SOCECONNREFUSED    (SOCBASEERR+61)
#define SOCELOOP           (SOCBASEERR+62)
#define SOCENAMETOOLONG    (SOCBASEERR+63)
#define SOCEHOSTDOWN       (SOCBASEERR+64)
#define SOCEHOSTUNREACH    (SOCBASEERR+65)
#define SOCENOTEMPTY       (SOCBASEERR+66)
#define SOCEPROCLIM        (SOCBASEERR+67)
#define SOCEUSERS          (SOCBASEERR+68)
#define SOCEDQUOT          (SOCBASEERR+69)
#define SOCESTALE          (SOCBASEERR+70)
#define SOCEREMOTE         (SOCBASEERR+71)
#define SOCEBADRPC         (SOCBASEERR+72)
#define SOCERPCMISMATCH    (SOCBASEERR+73)
#define SOCEPROGUNAVAIL    (SOCBASEERR+74)
#define SOCEPROGMISMATCH   (SOCBASEERR+75)
#define SOCEPROCUNAVAIL    (SOCBASEERR+76)
#define SOCENOLCK          (SOCBASEERR+77)
#define SOCENOSYS          (SOCBASEERR+78)
#define SOCEFTYPE          (SOCBASEERR+79)
#define SOCEAUTH           (SOCBASEERR+80)
#define SOCENEEDAUTH       (SOCBASEERR+81)
#define SOCEOS2ERR         (SOCBASEERR+100)
#define SOCELAST           (SOCBASEERR+100)

#ifndef ENOENT
#define ENOENT                  SOCENOENT
#endif

#ifndef EFAULT
#define EFAULT                  SOCEFAULT
#endif

#ifndef EBUSY
#define EBUSY                   SOCEBUSY
#endif

#ifndef ENXIO
#define ENXIO                   SOCENXIO
#endif

#ifndef EACCES
#define EACCES                  SOCEACCES
#endif

#ifndef ENOMEM
#define ENOMEM                  SOCENOMEM
#endif

#ifndef ENOTDIR
#define ENOTDIR                 SOCENOTDIR
#endif

#ifndef EPERM
#define EPERM                   SOCEPERM
#endif

#ifndef ESRCH
#define ESRCH                   SOCESRCH
#endif

#ifndef EDQUOT
#define EDQUOT                  SOCEDQUOT
#endif

#ifndef EEXIST
#define EEXIST                  SOCEEXIST
#endif

#ifndef EBUSY
#define EBUSY                   SOCEBUSY
#endif

#ifndef EWOULDBLOCK
#define EWOULDBLOCK             SOCEWOULDBLOCK
#endif

#ifndef EINPROGRESS
#define EINPROGRESS             SOCEINPROGRESS
#endif

#ifndef EALREADY
#define EALREADY                SOCEALREADY
#endif

#ifndef ENOTSOCK
#define ENOTSOCK                SOCENOTSOCK
#endif

#ifndef EDESTADDRREQ
#define EDESTADDRREQ            SOCEDESTADDRREQ
#endif

#ifndef EMSGSIZE
#define EMSGSIZE                SOCEMSGSIZE
#endif

#ifndef EPROTOTYPE
#define EPROTOTYPE              SOCEPROTOTYPE
#endif

#ifndef ENOPROTOOPT
#define ENOPROTOOPT             SOCENOPROTOOPT
#endif

#ifndef EPROTONOSUPPORT
#define EPROTONOSUPPORT         SOCEPROTONOSUPPORT
#endif

#ifndef ESOCKTNOSUPPORT
#define ESOCKTNOSUPPORT         SOCESOCKTNOSUPPORT
#endif

#ifndef EOPNOTSUPP
#define EOPNOTSUPP              SOCEOPNOTSUPP
#endif

#ifndef EPFNOSUPPORT
#define EPFNOSUPPORT            SOCEPFNOSUPPORT
#endif

#ifndef EAFNOSUPPORT
#define EAFNOSUPPORT            SOCEAFNOSUPPORT
#endif

#ifndef EADDRINUSE
#define EADDRINUSE              SOCEADDRINUSE
#endif

#ifndef EADDRNOTAVAIL
#define EADDRNOTAVAIL           SOCEADDRNOTAVAIL
#endif

#ifndef ENETDOWN
#define ENETDOWN                SOCENETDOWN
#endif

#ifndef ENETUNREACH
#define ENETUNREACH             SOCENETUNREACH
#endif

#ifndef ENETRESET
#define ENETRESET               SOCENETRESET
#endif

#ifndef ECONNABORTED
#define ECONNABORTED            SOCECONNABORTED
#endif

#ifndef ECONNRESET
#define ECONNRESET              SOCECONNRESET
#endif

#ifndef ENOBUFS
#define ENOBUFS                 SOCENOBUFS
#endif

#ifndef EISCONN
#define EISCONN                 SOCEISCONN
#endif

#ifndef ENOTCONN
#define ENOTCONN                SOCENOTCONN
#endif

#ifndef ESHUTDOWN
#define ESHUTDOWN               SOCESHUTDOWN
#endif

#ifndef ETOOMANYREFS
#define ETOOMANYREFS            SOCETOOMANYREFS
#endif

#ifndef ETIMEDOUT
#define ETIMEDOUT               SOCETIMEDOUT
#endif

#ifndef ECONNREFUSED
#define ECONNREFUSED            SOCECONNREFUSED
#endif

#ifndef ELOOP
#define ELOOP                   SOCELOOP
#endif

#ifndef ENAMETOOLONG
#define ENAMETOOLONG            SOCENAMETOOLONG
#endif

#ifndef EHOSTDOWN
#define EHOSTDOWN               SOCEHOSTDOWN
#endif

#ifndef EHOSTUNREACH
#define EHOSTUNREACH            SOCEHOSTUNREACH
#endif

#ifndef ENOTEMPTY
#define ENOTEMPTY               SOCENOTEMPTY
#endif

#ifndef EINVAL
#define EINVAL                  SOCEINVAL
#endif

#ifndef EINTR
#define EINTR                   SOCEINTR
#endif

#ifndef EMFILE
#define EMFILE                  SOCEMFILE
#endif

#ifndef EPIPE
#define EPIPE                   SOCEPIPE
#endif

#endif
