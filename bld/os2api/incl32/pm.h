/*
    OS/2 Presentation Manager top level include file for 32-bit development.
*/


#ifdef INCL_PM
  #define INCL_AVIO
  #define INCL_DEV
  #define INCL_ERRORS
  #define INCL_GPI
  #define INCL_WIN
  #define INCL_SPL
#endif

#include <pmwin.h>
#include <pmgpi.h>
#include <pmdev.h>
#include <pmstddlg.h>

#ifdef INCL_AVIO
  #include <pmavio.h>
#endif

#ifdef INCL_SPL
  #include <pmspl.h>
#endif


