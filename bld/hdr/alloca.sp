#ifndef alloca
 _WCRTLINK extern void  *alloca(__size_t __size);
 _WCRTLINK extern void  *_alloca(__size_t __size);
 _WCRTLINK extern unsigned stackavail( void );
 #if defined(__AXP__) || defined(__PPC__)
  extern void *__builtin_alloca(__size_t __size);
  #pragma intrinsic(__builtin_alloca);

  #define __alloca( s )  (__builtin_alloca(s))

  #define alloca( s )   ((s<stackavail())?__alloca(s):NULL)
  #define _alloca( s )  ((s<stackavail())?__alloca(s):NULL)
 #else
  extern void  *__doalloca(__size_t __size);
  #pragma aux stackavail __modify __nomemory;

  #define __ALLOCA_ALIGN( s )   (((s)+(sizeof(int)-1))&~(sizeof(int)-1))
  #define __alloca( s )         __doalloca(__ALLOCA_ALIGN(s))

:segment !QNX | !LINUX
  #if defined(__386__)
   extern void __GRO(__size_t __size);
   #pragma aux __GRO "*" __parm __routine [];
   #define alloca( s )  ((__ALLOCA_ALIGN(s)<stackavail())?(__GRO(__ALLOCA_ALIGN(s)),__alloca(s)):NULL)
   #define _alloca( s ) ((__ALLOCA_ALIGN(s)<stackavail())?(__GRO(__ALLOCA_ALIGN(s)),__alloca(s)):NULL)
  #else
:endsegment
   #define alloca( s )  ((__ALLOCA_ALIGN(s)<stackavail())?__alloca(s):NULL)
   #define _alloca( s ) ((__ALLOCA_ALIGN(s)<stackavail())?__alloca(s):NULL)
:segment !QNX | !LINUX
  #endif
:endsegment

  #if defined(__386__)
   #pragma aux     __doalloca =              \
            "sub esp,eax"                    \
            __parm __nomemory [__eax] __value [__esp] __modify __exact __nomemory [__esp];
  #elif defined(__SMALL__) || defined(__MEDIUM__) /* small data models */
   #pragma aux __doalloca = \
            "sub sp,ax"     \
            __parm __nomemory [__ax] __value [__sp] __modify __exact __nomemory [__sp];
  #else                                           /* large data models */
   #pragma aux __doalloca = \
            "sub sp,ax"     \
            "mov ax,sp"     \
            "mov dx,ss"     \
            __parm __nomemory [__ax] __value [__dx __ax] __modify __exact __nomemory [__dx __ax __sp];
  #endif
 #endif
#endif
