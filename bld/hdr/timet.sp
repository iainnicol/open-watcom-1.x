:segment CNAME
#ifndef _STDTIME_T_DEFINED
#define _STDTIME_T_DEFINED
namespace std {
:segment QNX | LINUX
typedef signed long time_t; /* time value */
:elsesegment
typedef unsigned long time_t; /* time value */
:endsegment
}
#endif
:elsesegment
#ifdef __cplusplus
#ifndef _STDTIME_T_DEFINED
#define _STDTIME_T_DEFINED
namespace std {
:segment QNX | LINUX
typedef signed long time_t; /* time value */
:elsesegment
typedef unsigned long time_t; /* time value */
:endsegment
}
#endif
#ifndef _TIME_T_DEFINED
#define _TIME_T_DEFINED
#define _TIME_T_DEFINED_
using std::time_t;
#endif
#else /* __cplusplus not defined */
#ifndef _TIME_T_DEFINED
#define _TIME_T_DEFINED
#define _TIME_T_DEFINED_
:segment QNX | LINUX
typedef signed long time_t; /* time value */
:elsesegment
typedef unsigned long time_t; /* time value */
:endsegment
#endif
#endif /* __cplusplus */
:endsegment
