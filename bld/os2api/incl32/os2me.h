/*
    OS/2 Multimedia Extensions top level include file for 32-bit development.
*/

#ifdef __cplusplus
extern "C" {
#endif

#define OS2ME_INCLUDED

#ifdef INCL_OS2MM
  #define INCL_MCIOS2
  #define INCL_MMIOOS2
#endif

#include <os2medef.h>
#include <meerror.h>

#ifdef INCL_MACHDR
  #include <mciapi.h>
#endif

#ifndef _SSM_H_
  #include <ssm.h>
#endif

#ifdef INCL_MCIOS2
  #include <mcios2.h>
  #include <mmdrvos2.h>
#else
//  #include <mmsystem.h>
//  #include <mcidrv.h>
#endif

#ifdef INCL_MMIO
  #include <mmio.h>
  #ifdef INCL_MMIO_CODEC
    #include <codec.h>
  #endif
#else
  #ifdef INCL_MMIOOS2
    #include <mmioos2.h>
    #ifdef INCL_MMIO_CODEC
      #include <codec.h>
    #endif
  #endif
#endif

#ifdef INCL_SW
  #define INCL_SECONDARYWINDOW
  #define INCL_GRAPHICBUTTON
  #define INCL_CIRCULARSLIDER
  #include <sw.h>
#endif

#ifdef __cplusplus
}
#endif
