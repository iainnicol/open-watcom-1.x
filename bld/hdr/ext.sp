:segment QNX
#if defined(_QNX_SOURCE) || !defined(NO_EXT_KEYS) /*extensions enabled*/
:elsesegment
#if !defined(NO_EXT_KEYS) /* extensions enabled */
:endsegment
