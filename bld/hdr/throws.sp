#ifndef _WC_EXCEPTION_MACROS_
  #define _WC_EXCEPTION_MACROS_
  #ifdef _CPPUNWIND
    #define _WCTHROWS( __t )   throw __t   // Legacy
    #define _WCTHROW( __t )    throw __t   // Preferred
    #define _WCTRY             try
    #define _WCHANDLERS        1
  #else
    #define _WCTHROWS( __t )
    #define _WCTHROW( __t )
    #define _WCTRY
  #endif
#endif
