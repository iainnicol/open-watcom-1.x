/****************************************************************************
*
*                            Open Watcom Project
*
*    Portions Copyright (c) 1983-2002 Sybase, Inc. All Rights Reserved.
*
*  ========================================================================
*
*    This file contains Original Code and/or Modifications of Original
*    Code as defined in and that are subject to the Sybase Open Watcom
*    Public License version 1.0 (the 'License'). You may not use this file
*    except in compliance with the License. BY USING THIS FILE YOU AGREE TO
*    ALL TERMS AND CONDITIONS OF THE LICENSE. A copy of the License is
*    provided with the Original Code and Modifications, and is also
*    available at www.sybase.com/developer/opensource.
*
*    The Original Code and all software distributed under the License are
*    distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
*    EXPRESS OR IMPLIED, AND SYBASE AND ALL CONTRIBUTORS HEREBY DISCLAIM
*    ALL SUCH WARRANTIES, INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF
*    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR
*    NON-INFRINGEMENT. Please see the License for the specific language
*    governing rights and limitations under the License.
*
*  ========================================================================
*
* Description:  WHEN YOU FIGURE OUT WHAT THIS FILE DOES, PLEASE
*               DESCRIBE IT HERE!
*
****************************************************************************/


#ifndef _PGCHART_H_INCLUDED
#define _PGCHART_H_INCLUDED
#ifdef __cplusplus
extern "C" {
#endif

#ifndef _COMDEF_H_INCLUDED
 #include <_comdef.h>
#endif

#if defined(_M_IX86)
  #pragma pack(__push,1);
#else
  #pragma pack(__push,8);
#endif

#define _PG_MAXCHARTTYPE        5       /* maximum chart type */

enum {                                  /* chart types */
    _PG_BARCHART=1, _PG_COLUMNCHART,
    _PG_LINECHART, _PG_SCATTERCHART, _PG_PIECHART
};


#define _PG_MAXCHARTSTYLE       2       /* maximum chart style */

enum {                                  /* styles for bar and column charts */
    _PG_PLAINBARS=1, _PG_STACKEDBARS
};

enum {                                  /* styles for line and scatter charts */
    _PG_POINTANDLINE=1, _PG_POINTONLY
};

enum {                                  /* styles for pie charts */
    _PG_PERCENT=1, _PG_NOPERCENT
};


enum {                                  /* title and legend positions */
    _PG_LEFT=1, _PG_CENTER, _PG_RIGHT, _PG_BOTTOM, _PG_OVERLAY
};

enum {                                  /* axis types */
    _PG_LINEARAXIS=1, _PG_LOGAXIS
};

enum {                                  /* tic mark label format */
    _PG_DECFORMAT=1, _PG_EXPFORMAT
};

#define _PG_MISSINGVALUE    (-FLT_MAX)  /* value for missing data elements */


/* Error codes - greater than 100, terminate chart routine
               - less than 100, default values will be used */

#define _PG_NOTINITIALIZED      101     /* library not initialized */
#define _PG_BADSCREENMODE       102     /* not in graphics mode */
#define _PG_BADCHARTTYPE        103     /* invalid chart type */
#define _PG_BADLEGENDWINDOW     104     /* invalid legend window */
#define _PG_BADDATAWINDOW       105     /* invalid data window */
#define _PG_TOOSMALLN           106     /* number of data values <= 0 */
#define _PG_TOOFEWSERIES        107     /* number of series <= 0 */

#define _PG_BADCHARTSTYLE       1       /* invalid chart style */
#define _PG_BADLOGBASE          2       /* log base <= 0 */
#define _PG_BADSCALEFACTOR      3       /* scale factor = 0 */
#define _PG_BADCHARTWINDOW      4       /* invalid chart window */


/* Chart definition */

#define _PG_TITLELEN    70              /* maximum title length */

typedef struct {                        /* chart title definition */
    char        title[ _PG_TITLELEN ];  /* title text */
    short       titlecolor;             /* palette color for title */
    short       justify;                /* _PG_LEFT, _PG_CENTER or _PG_RIGHT */
} titletype;

typedef struct {                        /* chart axes definition */
    short       grid;                   /* if TRUE draw grid lines */
    short       gridstyle;              /* style number for grid lines */
    titletype   axistitle;              /* axis title */
    short       axiscolor;              /* palette color for axis */
    short       labeled;                /* if TRUE draw tic marks and titles */
    short       rangetype;              /* _PG_LINEARAXIS or _PG_LOGAXIS */
    float       logbase;                /* base used for log axis */
    short       autoscale;              /* if TRUE calculate remaining values */
    float       scalemin;               /* minimum value for scale */
    float       scalemax;               /* maximum value for scale */
    float       scalefactor;            /* scale factor for axis */
    titletype   scaletitle;             /* title for scale factor */
    float       ticinterval;            /* interval between tic marks */
    short       ticformat;              /* _PG_EXPFORMAT or _PG_DECFORMAT */
    short       ticdecimals;            /* number of decimals places in tic labels */
} axistype;

typedef struct {                        /* chart and data window definition */
    short       x1;                     /* left side of window */
    short       y1;                     /* top side of window */
    short       x2;                     /* right side of window */
    short       y2;                     /* bottom side of window */
    short       border;                 /* if TRUE draw border */
    short       background;             /* palette color for background */
    short       borderstyle;            /* style number for border */
    short       bordercolor;            /* palette color for border */
} windowtype;

typedef struct {                        /* legend definition */
    short       legend;                 /* if TRUE draw legend */
    short       place;                  /* _PG_RIGHT, _PG_BOTTOM or _PG_OVERLAY */
    short       textcolor;              /* palette color for text */
    short       autosize;               /* if TRUE size is calculated */
    windowtype  legendwindow;           /* window for legend */
} legendtype;

typedef struct {                        /* chart definition */
    short       charttype;              /* _PG_BAR, _PG_COLUMN, _PG_LINE, _PG_SCATTER or _PG_PIE */
    short       chartstyle;             /* chart style for above type */
    windowtype  chartwindow;            /* window containing whole chart */
    windowtype  datawindow;             /* window containing data part of chart */
    titletype   maintitle;              /* chart main title */
    titletype   subtitle;               /* chart sub-title */
    axistype    xaxis;                  /* x-axis description */
    axistype    yaxis;                  /* y-axis description */
    legendtype  legend;                 /* legend description */
} chartenv;


/* Palette and Style-set definition */

#define _PG_PALETTELEN  16              /* size of palette and style-set */

typedef unsigned char   charmap[ 8 ];   /* character bit-map */

typedef unsigned char   fillmap[ 8 ];   /* pattern bit-map */

typedef struct {                        /* palette entry definition */
    unsigned short  color;
    unsigned short  style;
    fillmap         fill;
    char            plotchar;
} paletteentry;

typedef paletteentry    palettetype[ _PG_PALETTELEN ];
typedef unsigned short  styleset[ _PG_PALETTELEN ];


/* Display functions */

short _WCI86FAR      _CGRAPH _pg_initchart( void );
short _WCI86FAR      _CGRAPH _pg_defaultchart( chartenv _WCI86FAR *, short, short );
short _WCI86FAR      _CGRAPH _pg_chart( chartenv _WCI86FAR *, char _WCI86FAR * _WCI86FAR *, float _WCI86FAR *, short );
short _WCI86FAR      _CGRAPH _pg_chartms( chartenv _WCI86FAR *, char _WCI86FAR * _WCI86FAR *, float _WCI86FAR *, short, short, short, char _WCI86FAR * _WCI86FAR * );
short _WCI86FAR      _CGRAPH _pg_chartscatter( chartenv _WCI86FAR *, float _WCI86FAR *, float _WCI86FAR *, short );
short _WCI86FAR      _CGRAPH _pg_chartscatterms( chartenv _WCI86FAR *, float _WCI86FAR *, float _WCI86FAR *, short, short, short, char _WCI86FAR * _WCI86FAR * );
short _WCI86FAR      _CGRAPH _pg_chartpie( chartenv _WCI86FAR *, char _WCI86FAR * _WCI86FAR *, float _WCI86FAR *, short _WCI86FAR *, short );

/* Analyze functions */

short _WCI86FAR      _CGRAPH _pg_analyzechart( chartenv _WCI86FAR *, char _WCI86FAR * _WCI86FAR *, float _WCI86FAR *, short );
short _WCI86FAR      _CGRAPH _pg_analyzechartms( chartenv _WCI86FAR *, char _WCI86FAR * _WCI86FAR *, float _WCI86FAR *, short, short, short, char _WCI86FAR * _WCI86FAR * );
short _WCI86FAR      _CGRAPH _pg_analyzescatter( chartenv _WCI86FAR *, float _WCI86FAR *, float _WCI86FAR *, short );
short _WCI86FAR      _CGRAPH _pg_analyzescatterms( chartenv _WCI86FAR *, float _WCI86FAR *, float _WCI86FAR *, short, short, short, char _WCI86FAR * _WCI86FAR * );
short _WCI86FAR      _CGRAPH _pg_analyzepie( chartenv _WCI86FAR *, char _WCI86FAR * _WCI86FAR *, float _WCI86FAR *, short _WCI86FAR *, short );

/* Utility functions */

short _WCI86FAR      _CGRAPH _pg_hlabelchart( chartenv _WCI86FAR *, short, short, short, char _WCI86FAR * );
short _WCI86FAR      _CGRAPH _pg_vlabelchart( chartenv _WCI86FAR *, short, short, short, char _WCI86FAR * );
short _WCI86FAR      _CGRAPH _pg_getpalette( paletteentry _WCI86FAR * );
short _WCI86FAR      _CGRAPH _pg_setpalette( paletteentry _WCI86FAR * );
short _WCI86FAR      _CGRAPH _pg_resetpalette( void );
void _WCI86FAR       _CGRAPH _pg_getstyleset( unsigned short _WCI86FAR * );
void _WCI86FAR       _CGRAPH _pg_setstyleset( unsigned short _WCI86FAR * );
void _WCI86FAR       _CGRAPH _pg_resetstyleset( void );
short _WCI86FAR      _CGRAPH _pg_getchardef( short, unsigned char _WCI86FAR * );
short _WCI86FAR      _CGRAPH _pg_setchardef( short, unsigned char _WCI86FAR * );

#pragma pack(__pop);
#ifdef __cplusplus
};
#endif
#endif
