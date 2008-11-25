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


#include "spy.h"
#include <stdio.h>
#include <string.h>
#include <dde.h>

#ifdef __NT__
    #include <commctrl.h>
    #define NT_MSGS
#endif


#ifndef MCM_FIRST
    #define MCM_FIRST                       0x1000
#endif
#ifndef DTM_FIRST
    #define DTM_FIRST                       0x1000
#endif

/* PenWindows specific messages */
#ifndef WM_PENWINFIRST
    #define WM_PENWINFIRST                  0x0380
#endif
#ifndef WM_PENWINLAST
    #define WM_PENWINLAST                   0x038F
#endif
#ifndef WM_COALESCE_FIRST
    #define WM_COALESCE_FIRST               0x0390
#endif
#ifndef WM_COALESCE_LAST
    #define WM_COALESCE_LAST                0x039F
#endif
#ifndef WM_CTLCOLOR
    #define WM_CTLCOLOR                     0x0019
#endif
#ifndef WM_GETHOTKEY
    #define WM_GETHOTKEY                    0x0033
#endif
#ifndef WM_SETHOTKEY
    #define WM_SETHOTKEY                    0x0032
#endif
#ifndef WM_PAINTICON
    #define WM_PAINTICON                    0x0026
#endif
#ifndef WM_OTHERWINDOWCREATED
    #define WM_OTHERWINDOWCREATED           0x0042
#endif
#ifndef WM_OTHERWINDOWDESTROYED
    #define WM_OTHERWINDOWDESTROYED         0x0043
#endif

// Messages undocumented for WINDOWS but documented for NT
#ifndef WM_ENTERMENULOOP
    #define WM_ENTERMENULOOP                0x0211
#endif
#ifndef WM_EXITMENULOOP
    #define WM_EXITMENULOOP                 0x0212
#endif

// Windows 95 specific messages
#ifndef WM_NOTIFY
    #define WM_NOTIFY                       0x004E
#endif
#ifndef WM_INPUTLANGCHANGEREQUEST
    #define WM_INPUTLANGCHANGEREQUEST       0x0050
#endif
#ifndef WM_INPUTLANGCHANGE
    #define WM_INPUTLANGCHANGE              0x0051
#endif
#ifndef WM_TCARD
    #define WM_TCARD                        0x0052
#endif
#ifndef WM_HELP
    #define WM_HELP                         0x0053
#endif
#ifndef WM_USERCHANGED
    #define WM_USERCHANGED                  0x0054
#endif
#ifndef WM_CONTEXTMENU
    #define WM_CONTEXTMENU                  0x007B
#endif
#ifndef WM_STYLECHANGING
    #define WM_STYLECHANGING                0x007C
#endif
#ifndef WM_STYLECHANGED
    #define WM_STYLECHANGED                 0x007D
#endif
#ifndef WM_DISPLAYCHANGE
    #define WM_DISPLAYCHANGE                0x007E
#endif
#ifndef WM_GETICON
    #define WM_GETICON                      0x007F
#endif
#ifndef WM_SETICON
    #define WM_SETICON                      0x0080
#endif

// Messages introduced after Windows 95
#ifndef WM_NCXBUTTONDOWN
    #define WM_NCXBUTTONDOWN                0x00AB
#endif
#ifndef WM_NCXBUTTONUP
    #define WM_NCXBUTTONUP                  0x00AC
#endif
#ifndef WM_NCXBUTTONDBLCLK
    #define WM_NCXBUTTONDBLCLK              0x00AD
#endif
#ifndef WM_INPUT_DEVICE_CHANGE
    #define WM_INPUT_DEVICE_CHANGE          0x00FE
#endif
#ifndef WM_INPUT
    #define WM_INPUT                        0x00FF
#endif
#ifndef WM_UNICHAR
    #define WM_UNICHAR                      0x0108
#endif
#ifndef WM_MENURBUTTONUP
    #define WM_MENURBUTTONUP                0x0122
#endif
#ifndef WM_MENUDRAG
    #define WM_MENUDRAG                     0x0123
#endif
#ifndef WM_MENUGETOBJECT
    #define WM_MENUGETOBJECT                0x0124
#endif
#ifndef WM_UNINITMENUPOPUP
    #define WM_UNINITMENUPOPUP              0x0125
#endif
#ifndef WM_MENUCOMMAND
    #define WM_MENUCOMMAND                  0x0126
#endif
#ifndef WM_CHANGEUISTATE
    #define WM_CHANGEUISTATE                0x0127
#endif
#ifndef WM_UPDATEUISTATE
    #define WM_UPDATEUISTATE                0x0128
#endif
#ifndef WM_QUERYUISTATE
    #define WM_QUERYUISTATE                 0x0129
#endif
#ifndef WM_MOUSEWHEEL
    #define WM_MOUSEWHEEL                   0x020A
#endif
#ifndef WM_XBUTTONDOWN
    #define WM_XBUTTONDOWN                  0x020B
#endif
#ifndef WM_XBUTTONUP
    #define WM_XBUTTONUP                    0x020C
#endif
#ifndef WM_XBUTTONDBLCLK
    #define WM_XBUTTONDBLCLK                0x020D
#endif
#ifndef WM_MOUSEHWHEEL
    #define WM_MOUSEHWHEEL                  0x020E
#endif
#ifndef WM_IME_REQUEST
    #define WM_IME_REQUEST                  0x0288
#endif
#ifndef WM_MOUSEHOVER
    #define WM_MOUSEHOVER                   0x02A1
#endif
#ifndef WM_MOUSELEAVE
    #define WM_MOUSELEAVE                   0x02A3
#endif
#ifndef WM_NCMOUSEHOVER
    #define WM_NCMOUSEHOVER                 0x02A0
#endif
#ifndef WM_NCMOUSELEAVE
    #define WM_NCMOUSELEAVE                 0x02A2
#endif
#ifndef WM_WTSSESSION_CHANGE
    #define WM_WTSSESSION_CHANGE            0x02B1
#endif
#ifndef WM_APPCOMMAND
    #define WM_APPCOMMAND                   0x0319
#endif
#ifndef WM_THEMECHANGED
    #define WM_THEMECHANGED                 0x031A
#endif
#ifndef WM_CLIPBOARDUPDATE
    #define WM_CLIPBOARDUPDATE              0x031D
#endif
#ifndef WM_DWMCOMPOSITIONCHANGED
    #define WM_DWMCOMPOSITIONCHANGED        0x031E
#endif
#ifndef WM_DWMNCRENDERINGCHANGED
    #define WM_DWMNCRENDERINGCHANGED        0x031F
#endif
#ifndef WM_DWMCOLORIZATIONCOLORCHANGED
    #define WM_DWMCOLORIZATIONCOLORCHANGED  0x0320
#endif
#ifndef WM_DWMWINDOWMAXIMIZEDCHANGE
    #define WM_DWMWINDOWMAXIMIZEDCHANGE     0x0321
#endif
#ifndef WM_GETTITLEBARINFOEX
    #define WM_GETTITLEBARINFOEX            0x033F
#endif

// Control messages
#ifndef EM_SETIMESTATUS
    #define EM_SETIMESTATUS                 0x00D8
#endif
#ifndef EM_GETIMESTATUS
    #define EM_GETIMESTATUS                 0x00D9
#endif
#ifndef BM_SETDONTCLICK
    #define BM_SETDONTCLICK                 0x00F8
#endif
#ifndef LB_GETLISTBOXINFO
    #define LB_GETLISTBOXINFO               0x01B2
#endif
#ifndef CB_GETCOMBOBOXINFO
    #define CB_GETCOMBOBOXINFO              0x0164
#endif
#ifndef SBM_GETSCROLLBARINFO
    #define SBM_GETSCROLLBARINFO            0x00EB
#endif

// Common control messages
#ifndef HDM_SETBITMAPMARGIN
    #define HDM_SETBITMAPMARGIN             (HDM_FIRST + 20)
#endif
#ifndef HDM_GETBITMAPMARGIN
    #define HDM_GETBITMAPMARGIN             (HDM_FIRST + 21)
#endif
#ifndef HDM_SETFILTERCHANGETIMEOUT
    #define HDM_SETFILTERCHANGETIMEOUT      (HDM_FIRST + 22)
#endif
#ifndef HDM_EDITFILTER
    #define HDM_EDITFILTER                  (HDM_FIRST + 23)
#endif
#ifndef HDM_CLEARFILTER
    #define HDM_CLEARFILTER                 (HDM_FIRST + 24)
#endif
#ifndef HDM_GETITEMDROPDOWNRECT
    #define HDM_GETITEMDROPDOWNRECT         (HDM_FIRST + 25)
#endif
#ifndef HDM_GETOVERFLOWRECT
    #define HDM_GETOVERFLOWRECT             (HDM_FIRST + 26)
#endif
#ifndef HDM_GETFOCUSEDITEM
    #define HDM_GETFOCUSEDITEM              (HDM_FIRST + 27)
#endif
#ifndef HDM_SETFOCUSEDITEM
    #define HDM_SETFOCUSEDITEM              (HDM_FIRST + 28)
#endif


#ifndef TB_GETMETRICS
    #define TB_GETMETRICS                   (WM_USER + 101)
#endif
#ifndef TB_SETMETRICS
    #define TB_SETMETRICS                   (WM_USER + 102)
#endif
#ifndef TB_SETPRESSEDIMAGELIST
    #define TB_SETPRESSEDIMAGELIST          (WM_USER + 104)
#endif
#ifndef TB_GETPRESSEDIMAGELIST
    #define TB_GETPRESSEDIMAGELIST          (WM_USER + 105)
#endif
#ifndef RB_GETBANDINFO_IE3
    #define RB_GETBANDINFO_IE3              (WM_USER + 5)
#endif
#ifndef RB_GETBANDMARGINS
    #define RB_GETBANDMARGINS               (WM_USER + 40)
#endif
#ifndef RB_SETEXTENDEDSTYLE
    #define RB_SETEXTENDEDSTYLE             (WM_USER + 41)
#endif
#ifndef RB_GETEXTENDEDSTYLE
    #define RB_GETEXTENDEDSTYLE             (WM_USER + 42)
#endif
#ifndef RB_PUSHCHEVRON
    #define RB_PUSHCHEVRON                  (WM_USER + 43)
#endif
#ifndef RB_SETBANDWIDTH
    #define RB_SETBANDWIDTH                 (WM_USER + 44)
#endif
#ifndef TTM_POPUP
    #define TTM_POPUP                       (WM_USER + 34)
#endif
#ifndef TTM_GETTITLE
    #define TTM_GETTITLE                    (WM_USER + 35)
#endif
#ifndef PBM_SETMARQUEE
    #define PBM_SETMARQUEE                  (WM_USER + 10)
#endif
#ifndef PBM_GETSTEP
    #define PBM_GETSTEP                     (WM_USER + 11)
#endif
#ifndef PBM_GETBKCOLOR
    #define PBM_GETBKCOLOR                  (WM_USER + 12)
#endif
#ifndef PBM_GETBARCOLOR
    #define PBM_GETBARCOLOR                 (WM_USER + 13)
#endif
#ifndef PBM_SETSTATE
    #define PBM_SETSTATE                    (WM_USER + 14)
#endif
#ifndef PBM_GETSTATE
    #define PBM_GETSTATE                    (WM_USER + 15)
#endif
#ifndef LVM_GETGROUPSTATE
    #define LVM_GETGROUPSTATE               (LVM_FIRST + 92)
#endif
#ifndef LVM_GETFOCUSEDGROUP
    #define LVM_GETFOCUSEDGROUP             (LVM_FIRST + 93)
#endif
#ifndef LVM_GETGROUPRECT
    #define LVM_GETGROUPRECT                (LVM_FIRST + 98)
#endif
#ifndef LVM_SETSELECTEDCOLUMN
    #define LVM_SETSELECTEDCOLUMN           (LVM_FIRST + 140)
#endif
#ifndef LVM_SETVIEW
    #define LVM_SETVIEW                     (LVM_FIRST + 142)
#endif
#ifndef LVM_GETVIEW
    #define LVM_GETVIEW                     (LVM_FIRST + 143)
#endif
#ifndef LVM_INSERTGROUP
    #define LVM_INSERTGROUP                 (LVM_FIRST + 145)
#endif
#ifndef LVM_SETGROUPINFO
    #define LVM_SETGROUPINFO                (LVM_FIRST + 147)
#endif
#ifndef LVM_GETGROUPINFO
    #define LVM_GETGROUPINFO                (LVM_FIRST + 149)
#endif
#ifndef LVM_REMOVEGROUP
    #define LVM_REMOVEGROUP                 (LVM_FIRST + 150)
#endif
#ifndef LVM_MOVEGROUP
    #define LVM_MOVEGROUP                   (LVM_FIRST + 151)
#endif
#ifndef LVM_GETGROUPCOUNT
    #define LVM_GETGROUPCOUNT               (LVM_FIRST + 152)
#endif
#ifndef LVM_GETGROUPINFOBYINDEX
    #define LVM_GETGROUPINFOBYINDEX         (LVM_FIRST + 153)
#endif
#ifndef LVM_MOVEITEMTOGROUP
    #define LVM_MOVEITEMTOGROUP             (LVM_FIRST + 154)
#endif
#ifndef LVM_SETGROUPMETRICS
    #define LVM_SETGROUPMETRICS             (LVM_FIRST + 155)
#endif
#ifndef LVM_GETGROUPMETRICS
    #define LVM_GETGROUPMETRICS             (LVM_FIRST + 156)
#endif
#ifndef LVM_ENABLEGROUPVIEW
    #define LVM_ENABLEGROUPVIEW             (LVM_FIRST + 157)
#endif
#ifndef LVM_SORTGROUPS
    #define LVM_SORTGROUPS                  (LVM_FIRST + 158)
#endif
#ifndef LVM_INSERTGROUPSORTED
    #define LVM_INSERTGROUPSORTED           (LVM_FIRST + 159)
#endif
#ifndef LVM_REMOVEALLGROUPS
    #define LVM_REMOVEALLGROUPS             (LVM_FIRST + 160)
#endif
#ifndef LVM_HASGROUP
    #define LVM_HASGROUP                    (LVM_FIRST + 161)
#endif
#ifndef LVM_SETTILEVIEWINFO
    #define LVM_SETTILEVIEWINFO             (LVM_FIRST + 162)
#endif
#ifndef LVM_GETTILEVIEWINFO
    #define LVM_GETTILEVIEWINFO             (LVM_FIRST + 163)
#endif
#ifndef LVM_SETTILEINFO
    #define LVM_SETTILEINFO                 (LVM_FIRST + 164)
#endif
#ifndef LVM_GETTILEINFO
    #define LVM_GETTILEINFO                 (LVM_FIRST + 165)
#endif
#ifndef LVM_SETINSERTMARK
    #define LVM_SETINSERTMARK               (LVM_FIRST + 166)
#endif
#ifndef LVM_GETINSERTMARK
    #define LVM_GETINSERTMARK               (LVM_FIRST + 167)
#endif
#ifndef LVM_INSERTMARKHITTEST
    #define LVM_INSERTMARKHITTEST           (LVM_FIRST + 168)
#endif
#ifndef LVM_GETINSERTMARKRECT
    #define LVM_GETINSERTMARKRECT           (LVM_FIRST + 169)
#endif
#ifndef LVM_SETINSERTMARKCOLOR
    #define LVM_SETINSERTMARKCOLOR          (LVM_FIRST + 170)
#endif
#ifndef LVM_GETINSERTMARKCOLOR
    #define LVM_GETINSERTMARKCOLOR          (LVM_FIRST + 171)
#endif
#ifndef LVM_SETINFOTIP
    #define LVM_SETINFOTIP                  (LVM_FIRST + 173)
#endif
#ifndef LVM_GETSELECTEDCOLUMN
    #define LVM_GETSELECTEDCOLUMN           (LVM_FIRST + 174)
#endif
#ifndef LVM_ISGROUPVIEWENABLED
    #define LVM_ISGROUPVIEWENABLED          (LVM_FIRST + 175)
#endif
#ifndef LVM_GETOUTLINECOLOR
    #define LVM_GETOUTLINECOLOR             (LVM_FIRST + 176)
#endif
#ifndef LVM_SETOUTLINECOLOR
    #define LVM_SETOUTLINECOLOR             (LVM_FIRST + 177)
#endif
#ifndef LVM_CANCELEDITLABEL
    #define LVM_CANCELEDITLABEL             (LVM_FIRST + 179)
#endif
#ifndef LVM_MAPINDEXTOID
    #define LVM_MAPINDEXTOID                (LVM_FIRST + 180)
#endif
#ifndef LVM_MAPIDTOINDEX
    #define LVM_MAPIDTOINDEX                (LVM_FIRST + 181)
#endif
#ifndef LVM_ISITEMVISIBLE
    #define LVM_ISITEMVISIBLE               (LVM_FIRST + 182)
#endif
#ifndef LVM_GETEMPTYTEXT
    #define LVM_GETEMPTYTEXT                (LVM_FIRST + 204)
#endif
#ifndef LVM_GETFOOTERRECT
    #define LVM_GETFOOTERRECT               (LVM_FIRST + 205)
#endif
#ifndef LVM_GETFOOTERINFO
    #define LVM_GETFOOTERINFO               (LVM_FIRST + 206)
#endif
#ifndef LVM_GETFOOTERITEMRECT
    #define LVM_GETFOOTERITEMRECT           (LVM_FIRST + 207)
#endif
#ifndef LVM_GETFOOTERITEM
    #define LVM_GETFOOTERITEM               (LVM_FIRST + 208)
#endif
#ifndef LVM_GETITEMINDEXRECT
    #define LVM_GETITEMINDEXRECT            (LVM_FIRST + 209)
#endif
#ifndef LVM_SETITEMINDEXSTATE
    #define LVM_SETITEMINDEXSTATE           (LVM_FIRST + 210)
#endif
#ifndef LVM_GETNEXTITEMINDEX
    #define LVM_GETNEXTITEMINDEX            (LVM_FIRST + 211)
#endif
#ifndef TVM_MAPACCIDTOHTREEITEM
    #define TVM_MAPACCIDTOHTREEITEM         (TV_FIRST + 42)
#endif
#ifndef TVM_MAPHTREEITEMTOACCID
    #define TVM_MAPHTREEITEMTOACCID         (TV_FIRST + 43)
#endif
#ifndef TVM_SETEXTENDEDSTYLE
    #define TVM_SETEXTENDEDSTYLE            (TV_FIRST + 44)
#endif
#ifndef TVM_GETEXTENDEDSTYLE
    #define TVM_GETEXTENDEDSTYLE            (TV_FIRST + 45)
#endif
#ifndef TVM_SETAUTOSCROLLINFO
    #define TVM_SETAUTOSCROLLINFO           (TV_FIRST + 59)
#endif
#ifndef TVM_GETSELECTEDCOUNT
    #define TVM_GETSELECTEDCOUNT            (TV_FIRST + 70)
#endif
#ifndef TVM_SHOWINFOTIP
    #define TVM_SHOWINFOTIP                 (TV_FIRST + 71)
#endif
#ifndef TVM_GETITEMPARTRECT
    #define TVM_GETITEMPARTRECT             (TV_FIRST + 72)
#endif
#ifndef MCM_GETCURRENTVIEW
    #define MCM_GETCURRENTVIEW              (MCM_FIRST + 22)
#endif
#ifndef MCM_GETCALENDARCOUNT
    #define MCM_GETCALENDARCOUNT            (MCM_FIRST + 23)
#endif
#ifndef MCM_GETCALENDARGRIDINFO
    #define MCM_GETCALENDARGRIDINFO         (MCM_FIRST + 24)
#endif
#ifndef MCM_GETCALID
    #define MCM_GETCALID                    (MCM_FIRST + 25)
#endif
#ifndef MCM_SETCALID
    #define MCM_SETCALID                    (MCM_FIRST + 26)
#endif
#ifndef MCM_SIZERECTTOMIN
    #define MCM_SIZERECTTOMIN               (MCM_FIRST + 27)
#endif
#ifndef MCM_SETCALENDARBORDER
    #define MCM_SETCALENDARBORDER           (MCM_FIRST + 28)
#endif
#ifndef MCM_GETCALENDARBORDER
    #define MCM_GETCALENDARBORDER           (MCM_FIRST + 29)
#endif
#ifndef MCM_SETCURRENTVIEW
    #define MCM_SETCURRENTVIEW              (MCM_FIRST + 30)
#endif
#ifndef DTM_SETMCSTYLE
    #define DTM_SETMCSTYLE                  (DTM_FIRST + 11)
#endif
#ifndef DTM_GETMCSTYLE
    #define DTM_GETMCSTYLE                  (DTM_FIRST + 12)
#endif
#ifndef DTM_CLOSEMONTHCAL
    #define DTM_CLOSEMONTHCAL               (DTM_FIRST + 13)
#endif
#ifndef DTM_GETDATETIMEPICKERINFO
    #define DTM_GETDATETIMEPICKERINFO       (DTM_FIRST + 14)
#endif
#ifndef DTM_GETIDEALSIZE
    #define DTM_GETIDEALSIZE                (DTM_FIRST + 15)
#endif

#ifndef ACM_ISPLAYING
    #define ACM_ISPLAYING                   (WM_USER + 104)
#endif


#define msgpick( a, b, c, d, e, f )     { a, b, c, d, e, f }

message near MessageArray[] =  {
    #include "spyarray.h"
};

WORD MessageArraySize = sizeof( MessageArray ) / sizeof( message );

message near EditMessageArray[] = {
    msgpick( 1, 0, EM_GETSEL,               "EM_GETSEL",                MC_CONTROL, 0L ),
    msgpick( 1, 0, EM_SETSEL,               "EM_SETSEL",                MC_CONTROL, 0L ),
    msgpick( 1, 0, EM_GETRECT,              "EM_GETRECT",               MC_CONTROL, 0L ),
    msgpick( 1, 0, EM_SETRECT,              "EM_SETRECT",               MC_CONTROL, 0L ),
    msgpick( 1, 0, EM_SETRECTNP,            "EM_SETRECTNP",             MC_CONTROL, 0L ),
#ifdef NT_MSGS
    msgpick( 1, 0, EM_SCROLL,               "EM_SCROLL",                MC_CONTROL, 0L ),
#endif
    msgpick( 1, 0, EM_LINESCROLL,           "EM_LINESCROLL",            MC_CONTROL, 0L ),
#ifdef NT_MSGS
    msgpick( 1, 0, EM_SCROLLCARET,          "EM_SCROLLCARET",           MC_CONTROL, 0L ),
#endif
    msgpick( 1, 0, EM_GETMODIFY,            "EM_GETMODIFY",             MC_CONTROL, 0L ),
    msgpick( 1, 0, EM_SETMODIFY,            "EM_SETMODIFY",             MC_CONTROL, 0L ),
    msgpick( 1, 0, EM_GETLINECOUNT,         "EM_GETLINECOUNT",          MC_CONTROL, 0L ),
    msgpick( 1, 0, EM_LINEINDEX,            "EM_LINEINDEX",             MC_CONTROL, 0L ),
    msgpick( 1, 0, EM_SETHANDLE,            "EM_SETHANDLE",             MC_CONTROL, 0L ),
    msgpick( 1, 0, EM_GETHANDLE,            "EM_GETHANDLE",             MC_CONTROL, 0L ),
#ifdef NT_MSGS
    msgpick( 1, 0, EM_GETTHUMB,             "EM_GETTHUMB",              MC_CONTROL, 0L ),
#endif
    msgpick( 1, 0, EM_LINELENGTH,           "EM_LINELENGTH",            MC_CONTROL, 0L ),
    msgpick( 1, 0, EM_REPLACESEL,           "EM_REPLACESEL",            MC_CONTROL, 0L ),
    msgpick( 1, 0, EM_GETLINE,              "EM_GETLINE",               MC_CONTROL, 0L ),
    msgpick( 1, 0, EM_LIMITTEXT,            "EM_LIMITTEXT",             MC_CONTROL, 0L ),
    msgpick( 1, 0, EM_CANUNDO,              "EM_CANUNDO",               MC_CONTROL, 0L ),
    msgpick( 1, 0, EM_UNDO,                 "EM_UNDO",                  MC_CONTROL, 0L ),
    msgpick( 1, 0, EM_FMTLINES,             "EM_FMTLINES",              MC_CONTROL, 0L ),
    msgpick( 1, 0, EM_LINEFROMCHAR,         "EM_LINEFROMCHAR",          MC_CONTROL, 0L ),
    msgpick( 1, 0, EM_SETTABSTOPS,          "EM_SETTABSTOPS",           MC_CONTROL, 0L ),
    msgpick( 1, 0, EM_SETPASSWORDCHAR,      "EM_SETPASSWORDCHAR",       MC_CONTROL, 0L ),
    msgpick( 1, 0, EM_EMPTYUNDOBUFFER,      "EM_EMPTYUNDOBUFFER",       MC_CONTROL, 0L ),
    msgpick( 1, 0, EM_GETFIRSTVISIBLELINE,  "EM_GETFIRSTVISIBLELINE",   MC_CONTROL, 0L ),
    msgpick( 1, 0, EM_SETREADONLY,          "EM_SETREADONLY",           MC_CONTROL, 0L ),
    msgpick( 1, 0, EM_SETWORDBREAKPROC,     "EM_SETWORDBREAKPROC",      MC_CONTROL, 0L ),
    msgpick( 1, 0, EM_GETWORDBREAKPROC,     "EM_GETWORDBREAKPROC",      MC_CONTROL, 0L ),
#ifndef NT_MSGS
    msgpick( 1, 0, EM_GETPASSWORDCHAR,      "EM_GETPASSWORDCHAR",       MC_CONTROL, 0L )
#else
    msgpick( 1, 0, EM_GETPASSWORDCHAR,      "EM_GETPASSWORDCHAR",       MC_CONTROL, 0L ),
    msgpick( 1, 0, EM_SETMARGINS,           "EM_SETMARGINS",            MC_CONTROL, 0L ),
    msgpick( 1, 0, EM_GETMARGINS,           "EM_GETMARGINS",            MC_CONTROL, 0L ),
    msgpick( 1, 0, EM_GETLIMITTEXT,         "EM_GETLIMITTEXT",          MC_CONTROL, 0L ),
    msgpick( 1, 0, EM_POSFROMCHAR,          "EM_POSFROMCHAR",           MC_CONTROL, 0L ),
    msgpick( 1, 0, EM_CHARFROMPOS,          "EM_CHARFROMPOS",           MC_CONTROL, 0L ),
    msgpick( 1, 0, EM_SETIMESTATUS,         "EM_SETIMESTATUS",          MC_CONTROL, 0L ),
    msgpick( 1, 0, EM_GETIMESTATUS,         "EM_GETIMESTATUS",          MC_CONTROL, 0L )
#endif
};

WORD EditMessageArraySize = sizeof( EditMessageArray ) / sizeof( message );

message near ButtonMessageArray[] = {
    msgpick( 1, 0, BM_GETCHECK,     "BM_GETCHECK",      MC_CONTROL, 0L ),
    msgpick( 1, 0, BM_SETCHECK,     "BM_SETCHECK",      MC_CONTROL, 0L ),
    msgpick( 1, 0, BM_GETSTATE,     "BM_GETSTATE",      MC_CONTROL, 0L ),
    msgpick( 1, 0, BM_SETSTATE,     "BM_SETSTATE",      MC_CONTROL, 0L ),
#ifndef NT_MSGS
    msgpick( 1, 0, BM_SETSTYLE,     "BM_SETSTYLE",      MC_CONTROL, 0L )
#else
    msgpick( 1, 0, BM_SETSTYLE,     "BM_SETSTYLE",      MC_CONTROL, 0L ),
    msgpick( 1, 0, BM_CLICK,        "BM_CLICK",         MC_CONTROL, 0L ),
    msgpick( 1, 0, BM_GETIMAGE,     "BM_GETIMAGE",      MC_CONTROL, 0L ),
    msgpick( 1, 0, BM_SETIMAGE,     "BM_SETIMAGE",      MC_CONTROL, 0L ),
    msgpick( 1, 0, BM_SETDONTCLICK, "BM_SETDONTCLICK",  MC_CONTROL, 0L ),
#endif
};

WORD ButtonMessageArraySize = sizeof( ButtonMessageArray ) / sizeof( message );

message near StaticMessageArray[] = {
    msgpick( 1, 0, STM_SETICON,     "STM_SETICON",  MC_CONTROL, 0L ),
#ifndef NT_MSGS
    msgpick( 1, 0, STM_GETICON,     "STM_GETICON",  MC_CONTROL, 0L )
#else
    msgpick( 1, 0, STM_GETICON,     "STM_GETICON",  MC_CONTROL, 0L ),
    msgpick( 1, 0, STM_SETIMAGE,    "STM_SETIMAGE", MC_CONTROL, 0L ),
    msgpick( 1, 0, STM_GETIMAGE,    "STM_GETIMAGE", MC_CONTROL, 0L )
#endif
};

WORD StaticMessageArraySize = sizeof( StaticMessageArray ) / sizeof( message );

message near ListBoxMessageArray[] = {
    msgpick( 1, 0, LB_ADDSTRING,            "LB_ADDSTRING",             MC_CONTROL, 0L ),
    msgpick( 1, 0, LB_INSERTSTRING,         "LB_INSERTSTRING",          MC_CONTROL, 0L ),
    msgpick( 1, 0, LB_DELETESTRING,         "LB_DELETESTRING",          MC_CONTROL, 0L ),
#ifdef NT_MSGS
    msgpick( 1, 0, LB_SELITEMRANGEEX,       "LB_SELITEMRANGEEX",        MC_CONTROL, 0L ),
#endif
    msgpick( 1, 0, LB_RESETCONTENT,         "LB_RESETCONTENT",          MC_CONTROL, 0L ),
    msgpick( 1, 0, LB_SETSEL,               "LB_SETSEL",                MC_CONTROL, 0L ),
    msgpick( 1, 0, LB_SETCURSEL,            "LB_SETCURSEL",             MC_CONTROL, 0L ),
    msgpick( 1, 0, LB_GETSEL,               "LB_GETSEL",                MC_CONTROL, 0L ),
    msgpick( 1, 0, LB_GETCURSEL,            "LB_GETCURSEL",             MC_CONTROL, 0L ),
    msgpick( 1, 0, LB_GETTEXT,              "LB_GETTEXT",               MC_CONTROL, 0L ),
    msgpick( 1, 0, LB_GETTEXTLEN,           "LB_GETTEXTLEN",            MC_CONTROL, 0L ),
    msgpick( 1, 0, LB_GETCOUNT,             "LB_GETCOUNT",              MC_CONTROL, 0L ),
    msgpick( 1, 0, LB_SELECTSTRING,         "LB_SELECTSTRING",          MC_CONTROL, 0L ),
    msgpick( 1, 0, LB_DIR,                  "LB_DIR",                   MC_CONTROL, 0L ),
    msgpick( 1, 0, LB_GETTOPINDEX,          "LB_GETTOPINDEX",           MC_CONTROL, 0L ),
    msgpick( 1, 0, LB_FINDSTRING,           "LB_FINDSTRING",            MC_CONTROL, 0L ),
    msgpick( 1, 0, LB_GETSELCOUNT,          "LB_GETSELCOUNT",           MC_CONTROL, 0L ),
    msgpick( 1, 0, LB_GETSELITEMS,          "LB_GETSELITEMS",           MC_CONTROL, 0L ),
    msgpick( 1, 0, LB_SETTABSTOPS,          "LB_SETTABSTOPS",           MC_CONTROL, 0L ),
    msgpick( 1, 0, LB_GETHORIZONTALEXTENT,  "LB_GETHORIZONTALEXTENT",   MC_CONTROL, 0L ),
    msgpick( 1, 0, LB_SETHORIZONTALEXTENT,  "LB_SETHORIZONTALEXTENT",   MC_CONTROL, 0L ),
    msgpick( 1, 0, LB_SETCOLUMNWIDTH,       "LB_SETCOLUMNWIDTH",        MC_CONTROL, 0L ),
#ifdef NT_MSGS
    msgpick( 1, 0, LB_ADDFILE,              "LB_ADDFILE",               MC_CONTROL, 0L ),
#endif
    msgpick( 1, 0, LB_SETTOPINDEX,          "LB_SETTOPINDEX",           MC_CONTROL, 0L ),
    msgpick( 1, 0, LB_GETITEMRECT,          "LB_GETITEMRECT",           MC_CONTROL, 0L ),
    msgpick( 1, 0, LB_GETITEMDATA,          "LB_GETITEMDATA",           MC_CONTROL, 0L ),
    msgpick( 1, 0, LB_SETITEMDATA,          "LB_SETITEMDATA",           MC_CONTROL, 0L ),
    msgpick( 1, 0, LB_SELITEMRANGE,         "LB_SELITEMRANGE",          MC_CONTROL, 0L ),
#ifdef NT_MSGS
    msgpick( 1, 0, LB_SETANCHORINDEX,       "LB_SETANCHORINDEX",        MC_CONTROL, 0L ),
    msgpick( 1, 0, LB_GETANCHORINDEX,       "LB_GETANCHORINDEX",        MC_CONTROL, 0L ),
#endif
    msgpick( 1, 0, LB_SETCARETINDEX,        "LB_SETCARETINDEX",         MC_CONTROL, 0L ),
    msgpick( 1, 0, LB_GETCARETINDEX,        "LB_GETCARETINDEX",         MC_CONTROL, 0L ),
    msgpick( 1, 0, LB_SETITEMHEIGHT,        "LB_SETITEMHEIGHT",         MC_CONTROL, 0L ),
    msgpick( 1, 0, LB_GETITEMHEIGHT,        "LB_GETITEMHEIGHT",         MC_CONTROL, 0L ),
#ifndef NT_MSGS
    msgpick( 1, 0, LB_FINDSTRINGEXACT,      "LB_FINDSTRINGEXACT",       MC_CONTROL, 0L )
#else
    msgpick( 1, 0, LB_FINDSTRINGEXACT,      "LB_FINDSTRINGEXACT",       MC_CONTROL, 0L ),
    msgpick( 1, 0, LB_SETLOCALE,            "LB_SETLOCALE",             MC_CONTROL, 0L ),
    msgpick( 1, 0, LB_GETLOCALE,            "LB_GETLOCALE",             MC_CONTROL, 0L ),
    msgpick( 1, 0, LB_SETCOUNT,             "LB_SETCOUNT",              MC_CONTROL, 0L ),
    msgpick( 1, 0, LB_INITSTORAGE,          "LB_INITSTORAGE",           MC_CONTROL, 0L ),
    msgpick( 1, 0, LB_ITEMFROMPOINT,        "LB_ITEMFROMPOINT",         MC_CONTROL, 0L ),
    msgpick( 1, 0, LB_GETLISTBOXINFO,       "LB_GETLISTBOXINFO",        MC_CONTROL, 0L )
#endif
};

WORD ListBoxMessageArraySize = sizeof( ListBoxMessageArray ) / sizeof( message );

message near ComboBoxMessageArray[] = {
    msgpick( 1, 0, CB_GETEDITSEL,           "CB_GETEDITSEL",            MC_CONTROL, 0L ),
    msgpick( 1, 0, CB_LIMITTEXT,            "CB_LIMITTEXT",             MC_CONTROL, 0L ),
    msgpick( 1, 0, CB_SETEDITSEL,           "CB_SETEDITSEL",            MC_CONTROL, 0L ),
    msgpick( 1, 0, CB_ADDSTRING,            "CB_ADDSTRING",             MC_CONTROL, 0L ),
    msgpick( 1, 0, CB_DELETESTRING,         "CB_DELETESTRING",          MC_CONTROL, 0L ),
    msgpick( 1, 0, CB_DIR,                  "CB_DIR",                   MC_CONTROL, 0L ),
    msgpick( 1, 0, CB_GETCOUNT,             "CB_GETCOUNT",              MC_CONTROL, 0L ),
    msgpick( 1, 0, CB_GETCURSEL,            "CB_GETCURSEL",             MC_CONTROL, 0L ),
    msgpick( 1, 0, CB_GETLBTEXT,            "CB_GETLBTEXT",             MC_CONTROL, 0L ),
    msgpick( 1, 0, CB_GETLBTEXTLEN,         "CB_GETLBTEXTLEN",          MC_CONTROL, 0L ),
    msgpick( 1, 0, CB_INSERTSTRING,         "CB_INSERTSTRING",          MC_CONTROL, 0L ),
    msgpick( 1, 0, CB_RESETCONTENT,         "CB_RESETCONTENT",          MC_CONTROL, 0L ),
    msgpick( 1, 0, CB_FINDSTRING,           "CB_FINDSTRING",            MC_CONTROL, 0L ),
    msgpick( 1, 0, CB_SELECTSTRING,         "CB_SELECTSTRING",          MC_CONTROL, 0L ),
    msgpick( 1, 0, CB_SETCURSEL,            "CB_SETCURSEL",             MC_CONTROL, 0L ),
    msgpick( 1, 0, CB_SHOWDROPDOWN,         "CB_SHOWDROPDOWN",          MC_CONTROL, 0L ),
    msgpick( 1, 0, CB_GETITEMDATA,          "CB_GETITEMDATA",           MC_CONTROL, 0L ),
    msgpick( 1, 0, CB_SETITEMDATA,          "CB_SETITEMDATA",           MC_CONTROL, 0L ),
    msgpick( 1, 0, CB_GETDROPPEDCONTROLRECT, "CB_GETDROPPEDCONTROLRECT",
             MC_CONTROL, 0L ),
    msgpick( 1, 0, CB_SETITEMHEIGHT,        "CB_SETITEMHEIGHT",         MC_CONTROL, 0L ),
    msgpick( 1, 0, CB_GETITEMHEIGHT,        "CB_GETITEMHEIGHT",         MC_CONTROL, 0L ),
    msgpick( 1, 0, CB_SETEXTENDEDUI,        "CB_SETEXTENDEDUI",         MC_CONTROL, 0L ),
    msgpick( 1, 0, CB_GETEXTENDEDUI,        "CB_GETEXTENDEDUI",         MC_CONTROL, 0L ),
    msgpick( 1, 0, CB_GETDROPPEDSTATE,      "CB_GETDROPPEDSTATE",       MC_CONTROL, 0L ),
#ifndef NT_MSGS
    msgpick( 1, 0, CB_FINDSTRINGEXACT,      "CB_FINDSTRINGEXACT",       MC_CONTROL, 0L )
#else
    msgpick( 1, 0, CB_FINDSTRINGEXACT,      "CB_FINDSTRINGEXACT",       MC_CONTROL, 0L ),
    msgpick( 1, 0, CB_SETLOCALE,            "CB_SETLOCALE",             MC_CONTROL, 0L ),
    msgpick( 1, 0, CB_GETLOCALE,            "CB_GETLOCALE",             MC_CONTROL, 0L ),
    msgpick( 1, 0, CB_GETTOPINDEX,          "CB_GETTOPINDEX",           MC_CONTROL, 0L ),
    msgpick( 1, 0, CB_SETTOPINDEX,          "CB_SETTOPINDEX",           MC_CONTROL, 0L ),
    msgpick( 1, 0, CB_GETHORIZONTALEXTENT,  "CB_GETHORIZONTALEXTENT",   MC_CONTROL, 0L ),
    msgpick( 1, 0, CB_SETHORIZONTALEXTENT,  "CB_SETHORIZONTALEXTENT",   MC_CONTROL, 0L ),
    msgpick( 1, 0, CB_GETDROPPEDWIDTH,      "CB_GETDROPPEDWIDTH",       MC_CONTROL, 0L ),
    msgpick( 1, 0, CB_SETDROPPEDWIDTH,      "CB_SETDROPPEDWIDTH",       MC_CONTROL, 0L ),
    msgpick( 1, 0, CB_INITSTORAGE,          "CB_INITSTORAGE",           MC_CONTROL, 0L ),
    msgpick( 1, 0, CB_GETCOMBOBOXINFO,      "CB_GETCOMBOBOXINFO",       MC_CONTROL, 0L )
#endif
};

WORD ComboBoxMessageArraySize = sizeof( ComboBoxMessageArray ) / sizeof( message );

#ifdef NT_MSGS
message near ScrollBarMessageArray[] = {
    msgpick( 1, 0, SBM_SETPOS,              "SBM_SETPOS",           MC_CONTROL, 0L ),
    msgpick( 1, 0, SBM_GETPOS,              "SBM_GETPOS",           MC_CONTROL, 0L ),
    msgpick( 1, 0, SBM_SETRANGE,            "SBM_SETRANGE",         MC_CONTROL, 0L ),
    msgpick( 1, 0, SBM_SETRANGEREDRAW,      "SBM_SETRANGEREDRAW",   MC_CONTROL, 0L ),
    msgpick( 1, 0, SBM_GETRANGE,            "SBM_GETRANGE",         MC_CONTROL, 0L ),
    msgpick( 1, 0, SBM_ENABLE_ARROWS,       "SBM_ENABLE_ARROWS",    MC_CONTROL, 0L ),
    msgpick( 1, 0, SBM_SETSCROLLINFO,       "SBM_SETSCROLLINFO",    MC_CONTROL, 0L ),
    msgpick( 1, 0, SBM_GETSCROLLINFO,       "SBM_GETSCROLLINFO",    MC_CONTROL, 0L ),
    msgpick( 1, 0, SBM_GETSCROLLBARINFO,    "SBM_GETSCROLLBARINFO", MC_CONTROL, 0L )
};

WORD ScrollBarMessageArraySize = sizeof( ScrollBarMessageArray ) / sizeof( message );

message near HeaderMessageArray[] = {
    msgpick( 1, 0, HDM_GETITEMCOUNT,        "HDM_GETITEMCOUNT",         MC_CONTROL, 0L ),
    msgpick( 1, 0, HDM_INSERTITEMA,         "HDM_INSERTITEM",           MC_CONTROL, 0L ),
    msgpick( 1, 0, HDM_DELETEITEM,          "HDM_DELETEITEM",           MC_CONTROL, 0L ),
    msgpick( 1, 0, HDM_GETITEMA,            "HDM_GETITEM",              MC_CONTROL, 0L ),
    msgpick( 1, 0, HDM_SETITEMA,            "HDM_SETITEM",              MC_CONTROL, 0L ),
    msgpick( 1, 0, HDM_LAYOUT,              "HDM_LAYOUT",               MC_CONTROL, 0L ),
    msgpick( 1, 0, HDM_HITTEST,             "HDM_HITTEST",              MC_CONTROL, 0L ),
    msgpick( 1, 0, HDM_GETITEMRECT,         "HDM_GETITEMRECT",          MC_CONTROL, 0L ),
    msgpick( 1, 0, HDM_SETIMAGELIST,        "HDM_SETIMAGELIST",         MC_CONTROL, 0L ),
    msgpick( 1, 0, HDM_GETIMAGELIST,        "HDM_GETIMAGELIST",         MC_CONTROL, 0L ),
    msgpick( 1, 0, HDM_INSERTITEMW,         "HDM_INSERTITEM",           MC_CONTROL, 0L ),
    msgpick( 1, 0, HDM_GETITEMW,            "HDM_GETITEM",              MC_CONTROL, 0L ),
    msgpick( 1, 0, HDM_SETITEMW,            "HDM_SETITEM",              MC_CONTROL, 0L ),
    msgpick( 1, 0, HDM_ORDERTOINDEX,        "HDM_ORDERTOINDEX",         MC_CONTROL, 0L ),
    msgpick( 1, 0, HDM_CREATEDRAGIMAGE,     "HDM_CREATEDRAGIMAGE",      MC_CONTROL, 0L ),
    msgpick( 1, 0, HDM_GETORDERARRAY,       "HDM_GETORDERARRAY",        MC_CONTROL, 0L ),
    msgpick( 1, 0, HDM_SETORDERARRAY,       "HDM_SETORDERARRAY",        MC_CONTROL, 0L ),
    msgpick( 1, 0, HDM_SETHOTDIVIDER,       "HDM_SETHOTDIVIDER",        MC_CONTROL, 0L ),
    msgpick( 1, 0, HDM_SETBITMAPMARGIN,     "HDM_SETBITMAPMARGIN",      MC_CONTROL, 0L ),
    msgpick( 1, 0, HDM_GETBITMAPMARGIN,     "HDM_GETBITMAPMARGIN",      MC_CONTROL, 0L ),
    msgpick( 1, 0, HDM_SETFILTERCHANGETIMEOUT, "HDM_SETFILTERCHANGETIMEOUT",
             MC_CONTROL, 0L ),
    msgpick( 1, 0, HDM_EDITFILTER,          "HDM_EDITFILTER",           MC_CONTROL, 0L ),
    msgpick( 1, 0, HDM_CLEARFILTER,         "HDM_CLEARFILTER",          MC_CONTROL, 0L ),
    msgpick( 1, 0, HDM_GETITEMDROPDOWNRECT, "HDM_GETITEMDROPDOWNRECT",  MC_CONTROL, 0L ),
    msgpick( 1, 0, HDM_GETOVERFLOWRECT,     "HDM_GETOVERFLOWRECT",      MC_CONTROL, 0L ),
    msgpick( 1, 0, HDM_GETFOCUSEDITEM,      "HDM_GETFOCUSEDITEM",       MC_CONTROL, 0L ),
    msgpick( 1, 0, HDM_SETFOCUSEDITEM,      "HDM_SETFOCUSEDITEM",       MC_CONTROL, 0L ),
};

WORD HeaderMessageArraySize = sizeof( HeaderMessageArray ) / sizeof( message );

message near ToolbarMessageArray[] = {
    msgpick( 1, 0, TB_ENABLEBUTTON,         "TB_ENABLEBUTTON",          MC_CONTROL, 0L ),
    msgpick( 1, 0, TB_CHECKBUTTON,          "TB_CHECKBUTTON",           MC_CONTROL, 0L ),
    msgpick( 1, 0, TB_PRESSBUTTON,          "TB_PRESSBUTTON",           MC_CONTROL, 0L ),
    msgpick( 1, 0, TB_HIDEBUTTON,           "TB_HIDEBUTTON",            MC_CONTROL, 0L ),
    msgpick( 1, 0, TB_INDETERMINATE,        "TB_INDETERMINATE",         MC_CONTROL, 0L ),
    msgpick( 1, 0, TB_MARKBUTTON,           "TB_MARKBUTTON",            MC_CONTROL, 0L ),
    msgpick( 1, 0, TB_ISBUTTONENABLED,      "TB_ISBUTTONENABLED",       MC_CONTROL, 0L ),
    msgpick( 1, 0, TB_ISBUTTONCHECKED,      "TB_ISBUTTONCHECKED",       MC_CONTROL, 0L ),
    msgpick( 1, 0, TB_ISBUTTONPRESSED,      "TB_ISBUTTONPRESSED",       MC_CONTROL, 0L ),
    msgpick( 1, 0, TB_ISBUTTONHIDDEN,       "TB_ISBUTTONHIDEEN",        MC_CONTROL, 0L ),
    msgpick( 1, 0, TB_ISBUTTONINDETERMINATE, "TB_ISBUTTONINDETERMINATE",
             MC_CONTROL, 0L ),
    msgpick( 1, 0, TB_ISBUTTONHIGHLIGHTED,  "TB_ISBUTTONHIGHLIGHTED",   MC_CONTROL, 0L ),
    msgpick( 1, 0, TB_SETSTATE,             "TB_SETSTATE",              MC_CONTROL, 0L ),
    msgpick( 1, 0, TB_GETSTATE,             "TB_GETSTATE",              MC_CONTROL, 0L ),
    msgpick( 1, 0, TB_ADDBITMAP,            "TB_ADDBITMAP",             MC_CONTROL, 0L ),
    msgpick( 1, 0, TB_ADDBUTTONSA,          "TB_ADDBUTTONS",            MC_CONTROL, 0L ),
    msgpick( 1, 0, TB_INSERTBUTTONA,        "TB_INSERTBUTTON",          MC_CONTROL, 0L ),
    msgpick( 1, 0, TB_DELETEBUTTON,         "TB_DELETEBUTTON",          MC_CONTROL, 0L ),
    msgpick( 1, 0, TB_GETBUTTON,            "TB_GETBUTTON",             MC_CONTROL, 0L ),
    msgpick( 1, 0, TB_BUTTONCOUNT,          "TB_BUTTONCOUNT",           MC_CONTROL, 0L ),
    msgpick( 1, 0, TB_COMMANDTOINDEX,       "TB_COMMANDTOINDEX",        MC_CONTROL, 0L ),
    msgpick( 1, 0, TB_SAVERESTOREA,         "TB_SAVERESTORE",           MC_CONTROL, 0L ),
    msgpick( 1, 0, TB_CUSTOMIZE,            "TB_CUSTOMIZE",             MC_CONTROL, 0L ),
    msgpick( 1, 0, TB_ADDSTRINGA,           "TB_ADDSTRING",             MC_CONTROL, 0L ),
    msgpick( 1, 0, TB_GETITEMRECT,          "TB_GETITEMRECT",           MC_CONTROL, 0L ),
    msgpick( 1, 0, TB_BUTTONSTRUCTSIZE,     "TB_BUTTONSTRUCTSIZE",      MC_CONTROL, 0L ),
    msgpick( 1, 0, TB_SETBUTTONSIZE,        "TB_SETBUTTONSIZE",         MC_CONTROL, 0L ),
    msgpick( 1, 0, TB_SETBITMAPSIZE,        "TB_SETBITMAPSIZE",         MC_CONTROL, 0L ),
    msgpick( 1, 0, TB_AUTOSIZE,             "TB_AUTOSIZE",              MC_CONTROL, 0L ),
    msgpick( 1, 0, TB_GETTOOLTIPS,          "TB_GETTOOLTIPS",           MC_CONTROL, 0L ),
    msgpick( 1, 0, TB_SETTOOLTIPS,          "TB_SETTOOLTIPS",           MC_CONTROL, 0L ),
    msgpick( 1, 0, TB_SETPARENT,            "TB_SETPARENT",             MC_CONTROL, 0L ),
    msgpick( 1, 0, TB_SETROWS,              "TB_SETROWS",               MC_CONTROL, 0L ),
    msgpick( 1, 0, TB_GETROWS,              "TB_GETROWS",               MC_CONTROL, 0L ),
    msgpick( 1, 0, TB_GETBITMAPFLAGS,       "TB_GETBITMAPFLAGS",        MC_CONTROL, 0L ),
    msgpick( 1, 0, TB_SETCMDID,             "TB_SETCMDID",              MC_CONTROL, 0L ),
    msgpick( 1, 0, TB_CHANGEBITMAP,         "TB_CHANGEBITMAP",          MC_CONTROL, 0L ),
    msgpick( 1, 0, TB_GETBITMAP,            "TB_GETBITMAP",             MC_CONTROL, 0L ),
    msgpick( 1, 0, TB_GETBUTTONTEXTA,       "TB_GETBUTTONTEXT",         MC_CONTROL, 0L ),
    msgpick( 1, 0, TB_REPLACEBITMAP,        "TB_REPLACEBITMAP",         MC_CONTROL, 0L ),
    msgpick( 1, 0, TB_SETINDENT,            "TB_SETINDENT",             MC_CONTROL, 0L ),
    msgpick( 1, 0, TB_SETIMAGELIST,         "TB_SETIMAGELIST",          MC_CONTROL, 0L ),
    msgpick( 1, 0, TB_GETIMAGELIST,         "TB_GETIMAGELIST",          MC_CONTROL, 0L ),
    msgpick( 1, 0, TB_LOADIMAGES,           "TB_LOADIMAGES",            MC_CONTROL, 0L ),
    msgpick( 1, 0, TB_GETRECT,              "TB_GETRECT",               MC_CONTROL, 0L ),
    msgpick( 1, 0, TB_SETHOTIMAGELIST,      "TB_SETHOTIMAGELIST",       MC_CONTROL, 0L ),
    msgpick( 1, 0, TB_GETHOTIMAGELIST,      "TB_GETHOTIMAGELIST",       MC_CONTROL, 0L ),
    msgpick( 1, 0, TB_SETDISABLEDIMAGELIST, "TB_SETDISABLEDIMAGELIST",  MC_CONTROL, 0L ),
    msgpick( 1, 0, TB_GETDISABLEDIMAGELIST, "TB_GETDISABLEDIMAGELIST",  MC_CONTROL, 0L ),
    msgpick( 1, 0, TB_SETSTYLE,             "TB_SETSTYLE",              MC_CONTROL, 0L ),
    msgpick( 1, 0, TB_GETSTYLE,             "TB_GETSTYLE",              MC_CONTROL, 0L ),
    msgpick( 1, 0, TB_GETBUTTONSIZE,        "TB_GETBUTTONSIZE",         MC_CONTROL, 0L ),
    msgpick( 1, 0, TB_SETBUTTONWIDTH,       "TB_SETBUTTONWIDTH",        MC_CONTROL, 0L ),
    msgpick( 1, 0, TB_SETMAXTEXTROWS,       "TB_SETMAXTEXTROWS",        MC_CONTROL, 0L ),
    msgpick( 1, 0, TB_GETTEXTROWS,          "TB_GETTEXTROWS",           MC_CONTROL, 0L ),
    msgpick( 1, 0, TB_GETOBJECT,            "TB_GETOBJECT",             MC_CONTROL, 0L ),
    msgpick( 1, 0, TB_GETBUTTONINFOW,       "TB_GETBUTTONINFO",         MC_CONTROL, 0L ),
    msgpick( 1, 0, TB_SETBUTTONINFOW,       "TB_SETBUTTONINFO",         MC_CONTROL, 0L ),
    msgpick( 1, 0, TB_GETBUTTONINFOA,       "TB_GETBUTTONINFO",         MC_CONTROL, 0L ),
    msgpick( 1, 0, TB_SETBUTTONINFOA,       "TB_SETBUTTONINFO",         MC_CONTROL, 0L ),
    msgpick( 1, 0, TB_INSERTBUTTONW,        "TB_INSERTBUTTON",          MC_CONTROL, 0L ),
    msgpick( 1, 0, TB_ADDBUTTONSW,          "TB_ADDBUTTONS",            MC_CONTROL, 0L ),
    msgpick( 1, 0, TB_HITTEST,              "TB_HITTEST",               MC_CONTROL, 0L ),
    msgpick( 1, 0, TB_SETDRAWTEXTFLAGS,     "TB_SETDRAWTEXTFLAGS",      MC_CONTROL, 0L ),
    msgpick( 1, 0, TB_SETHOTITEM,           "TB_SETHOTITEM",            MC_CONTROL, 0L ),
    msgpick( 1, 0, TB_GETHOTITEM,           "TB_GETHOTITEM",            MC_CONTROL, 0L ),
    msgpick( 1, 0, TB_SETANCHORHIGHLIGHT,   "TB_SETANCHORHIGHLIGHT",    MC_CONTROL, 0L ),
    msgpick( 1, 0, TB_GETANCHORHIGHLIGHT,   "TB_GETANCHORHIGHLIGHT",    MC_CONTROL, 0L ),
    msgpick( 1, 0, TB_GETBUTTONTEXTW,       "TB_GETBUTTONTEXT",         MC_CONTROL, 0L ),
    msgpick( 1, 0, TB_SAVERESTOREW,         "TB_SAVERESTORE",           MC_CONTROL, 0L ),
    msgpick( 1, 0, TB_ADDSTRINGW,           "TB_ADDSTRING",             MC_CONTROL, 0L ),
    msgpick( 1, 0, TB_MAPACCELERATORA,      "TB_MAPACCELERATOR",        MC_CONTROL, 0L ),
    msgpick( 1, 0, TB_GETINSERTMARK,        "TB_GETINSERTMARK",         MC_CONTROL, 0L ),
    msgpick( 1, 0, TB_SETINSERTMARK,        "TB_SETINSERTMARK",         MC_CONTROL, 0L ),
    msgpick( 1, 0, TB_INSERTMARKHITTEST,    "TB_INSERTMARKHITTEST",     MC_CONTROL, 0L ),
    msgpick( 1, 0, TB_MOVEBUTTON,           "TB_MOVEBUTTON",            MC_CONTROL, 0L ),
    msgpick( 1, 0, TB_GETMAXSIZE,           "TB_GETMAXSIZE",            MC_CONTROL, 0L ),
    msgpick( 1, 0, TB_SETEXTENDEDSTYLE,     "TB_SETEXTENDEDSTYLE",      MC_CONTROL, 0L ),
    msgpick( 1, 0, TB_GETEXTENDEDSTYLE,     "TB_GETEXTENDEDSTYLE",      MC_CONTROL, 0L ),
    msgpick( 1, 0, TB_GETPADDING,           "TB_GETPADDING",            MC_CONTROL, 0L ),
    msgpick( 1, 0, TB_SETPADDING,           "TB_SETPADDING",            MC_CONTROL, 0L ),
    msgpick( 1, 0, TB_SETINSERTMARKCOLOR,   "TB_SETINSERTMARKCOLOR",    MC_CONTROL, 0L ),
    msgpick( 1, 0, TB_GETINSERTMARKCOLOR,   "TB_GETINSERTMARKCOLOR",    MC_CONTROL, 0L ),
    msgpick( 1, 0, TB_MAPACCELERATORW,      "TB_MAPACCELERATOR",        MC_CONTROL, 0L ),
    msgpick( 1, 0, TB_GETSTRINGW,           "TB_GETSTRING",             MC_CONTROL, 0L ),
    msgpick( 1, 0, TB_GETSTRINGA,           "TB_GETSTRING",             MC_CONTROL, 0L ),
    msgpick( 1, 0, TB_GETMETRICS,           "TB_GETMETRICS",            MC_CONTROL, 0L ),
    msgpick( 1, 0, TB_SETMETRICS,           "TB_SETMETRICS",            MC_CONTROL, 0L ),
    msgpick( 1, 0, TB_SETPRESSEDIMAGELIST,  "TB_SETPRESSEDIMAGELIST",   MC_CONTROL, 0L ),
    msgpick( 1, 0, TB_GETPRESSEDIMAGELIST,  "TB_GETPRESSEDIMAGELIST",   MC_CONTROL, 0L ),
};

WORD ToolbarMessageArraySize = sizeof( ToolbarMessageArray ) / sizeof( message );

message near RebarMessageArray[] = {
    msgpick( 1, 0, RB_INSERTBANDA,      "RB_INSERTBAND",        MC_CONTROL, 0L ),
    msgpick( 1, 0, RB_DELETEBAND,       "RB_DELETEBAND",        MC_CONTROL, 0L ),
    msgpick( 1, 0, RB_GETBARINFO,       "RB_GETBARINFO",        MC_CONTROL, 0L ),
    msgpick( 1, 0, RB_SETBARINFO,       "RB_SETBARINFO",        MC_CONTROL, 0L ),
    msgpick( 1, 0, RB_GETBANDINFO_IE3,  "RB_GETBANDINFO",       MC_CONTROL, 0L ),
    msgpick( 1, 0, RB_SETBANDINFOA,     "RB_SETBANDINFO",       MC_CONTROL, 0L ),
    msgpick( 1, 0, RB_SETPARENT,        "RB_SETPARENT",         MC_CONTROL, 0L ),
    msgpick( 1, 0, RB_HITTEST,          "RB_HITTEST",           MC_CONTROL, 0L ),
    msgpick( 1, 0, RB_GETRECT,          "RB_GETRECT",           MC_CONTROL, 0L ),
    msgpick( 1, 0, RB_INSERTBANDW,      "RB_INSERTBAND",        MC_CONTROL, 0L ),
    msgpick( 1, 0, RB_SETBANDINFOW,     "RB_SETBANDINFO",       MC_CONTROL, 0L ),
    msgpick( 1, 0, RB_GETBANDCOUNT,     "RB_GETBANDCOUNT",      MC_CONTROL, 0L ),
    msgpick( 1, 0, RB_GETROWCOUNT,      "RB_GETROWCOUNT",       MC_CONTROL, 0L ),
    msgpick( 1, 0, RB_GETROWHEIGHT,     "RB_GETROWHEIGHT",      MC_CONTROL, 0L ),
    msgpick( 1, 0, RB_IDTOINDEX,        "RB_IDTOINDEX",         MC_CONTROL, 0L ),
    msgpick( 1, 0, RB_GETTOOLTIPS,      "RB_GETTOOLTIPS",       MC_CONTROL, 0L ),
    msgpick( 1, 0, RB_SETTOOLTIPS,      "RB_SETTOOLTIPS",       MC_CONTROL, 0L ),
    msgpick( 1, 0, RB_SETBKCOLOR,       "RB_SETBKCOLOR",        MC_CONTROL, 0L ),
    msgpick( 1, 0, RB_GETBKCOLOR,       "RB_GETBKCOLOR",        MC_CONTROL, 0L ),
    msgpick( 1, 0, RB_SETTEXTCOLOR,     "RB_SETTEXTCOLOR",      MC_CONTROL, 0L ),
    msgpick( 1, 0, RB_GETTEXTCOLOR,     "RB_GETTEXTCOLOR",      MC_CONTROL, 0L ),
    msgpick( 1, 0, RB_SIZETORECT,       "RB_SIZETORECT",        MC_CONTROL, 0L ),
    msgpick( 1, 0, RB_BEGINDRAG,        "RB_BEGINDRAG",         MC_CONTROL, 0L ),
    msgpick( 1, 0, RB_ENDDRAG,          "RB_ENDDRAG",           MC_CONTROL, 0L ),
    msgpick( 1, 0, RB_DRAGMOVE,         "RB_DRAGMOVE",          MC_CONTROL, 0L ),
    msgpick( 1, 0, RB_GETBARHEIGHT,     "RB_GETBARHEIGHT",      MC_CONTROL, 0L ),
    msgpick( 1, 0, RB_GETBANDINFOW,     "RB_GETBANDINFO",       MC_CONTROL, 0L ),
    msgpick( 1, 0, RB_GETBANDINFOA,     "RB_GETBANDINFO",       MC_CONTROL, 0L ),
    msgpick( 1, 0, RB_MINIMIZEBAND,     "RB_MINIMIZEBAND",      MC_CONTROL, 0L ),
    msgpick( 1, 0, RB_MAXIMIZEBAND,     "RB_MAXIMIZEBAND",      MC_CONTROL, 0L ),
    msgpick( 1, 0, RB_GETBANDBORDERS,   "RB_GETBANDBORDERS",    MC_CONTROL, 0L ),
    msgpick( 1, 0, RB_SHOWBAND,         "RB_SHOWBAND",          MC_CONTROL, 0L ),
    msgpick( 1, 0, RB_SETPALETTE,       "RB_SETPALETTE",        MC_CONTROL, 0L ),
    msgpick( 1, 0, RB_GETPALETTE,       "RB_GETPALETTE",        MC_CONTROL, 0L ),
    msgpick( 1, 0, RB_MOVEBAND,         "RB_MOVEBAND",          MC_CONTROL, 0L ),
    msgpick( 1, 0, RB_GETBANDMARGINS,   "RB_GETBANDMARGINS",    MC_CONTROL, 0L ),
    msgpick( 1, 0, RB_SETEXTENDEDSTYLE, "RB_SETEXTENDEDSTYLE",  MC_CONTROL, 0L ),
    msgpick( 1, 0, RB_GETEXTENDEDSTYLE, "RB_GETEXTENDEDSTYLE",  MC_CONTROL, 0L ),
    msgpick( 1, 0, RB_PUSHCHEVRON,      "RB_PUSHCHEVRON",       MC_CONTROL, 0L ),
    msgpick( 1, 0, RB_SETBANDWIDTH,     "RB_SETBANDWIDTH",      MC_CONTROL, 0L ),
};

WORD RebarMessageArraySize = sizeof( RebarMessageArray ) / sizeof( message );

message near ToolTipsMessageArray[] = {
    msgpick( 1, 0, TTM_ACTIVATE,        "TTM_ACTIVATE",         MC_CONTROL, 0L ),
    msgpick( 1, 0, TTM_SETDELAYTIME,    "TTM_SETDELAYTIME",     MC_CONTROL, 0L ),
    msgpick( 1, 0, TTM_ADDTOOLA,        "TTM_ADDTOOL",          MC_CONTROL, 0L ),
    msgpick( 1, 0, TTM_DELTOOLA,        "TTM_DELTOOL",          MC_CONTROL, 0L ),
    msgpick( 1, 0, TTM_NEWTOOLRECTA,    "TTM_NEWTOOLRECT",      MC_CONTROL, 0L ),
    msgpick( 1, 0, TTM_RELAYEVENT,      "TTM_RELAYEVENT",       MC_CONTROL, 0L ),
    msgpick( 1, 0, TTM_GETTOOLINFOA,    "TTM_GETTOOLINFO",      MC_CONTROL, 0L ),
    msgpick( 1, 0, TTM_SETTOOLINFOA,    "TTM_SETTOOLINFO",      MC_CONTROL, 0L ),
    msgpick( 1, 0, TTM_HITTESTA,        "TTM_HITTEST",          MC_CONTROL, 0L ),
    msgpick( 1, 0, TTM_GETTEXTA,        "TTM_GETTEXT",          MC_CONTROL, 0L ),
    msgpick( 1, 0, TTM_UPDATETIPTEXTA,  "TTM_UPDATETIPTEXT",    MC_CONTROL, 0L ),
    msgpick( 1, 0, TTM_GETTOOLCOUNT,    "TTM_GETTOOLCOUNT",     MC_CONTROL, 0L ),
    msgpick( 1, 0, TTM_ENUMTOOLSA,      "TTM_ENUMTOOLS",        MC_CONTROL, 0L ),
    msgpick( 1, 0, TTM_GETCURRENTTOOLA, "TTM_GETCURRENTTOOL",   MC_CONTROL, 0L ),
    msgpick( 1, 0, TTM_WINDOWFROMPOINT, "TTM_WINDOWFROMPOINT",  MC_CONTROL, 0L ),
    msgpick( 1, 0, TTM_TRACKACTIVATE,   "TTM_TRACKACTIVATE",    MC_CONTROL, 0L ),
    msgpick( 1, 0, TTM_TRACKPOSITION,   "TTM_TRACKPOSITION",    MC_CONTROL, 0L ),
    msgpick( 1, 0, TTM_SETTIPBKCOLOR,   "TTM_SETTIPBKCOLOR",    MC_CONTROL, 0L ),
    msgpick( 1, 0, TTM_SETTIPTEXTCOLOR, "TTM_SETTIPTEXTCOLOR",  MC_CONTROL, 0L ),
    msgpick( 1, 0, TTM_GETDELAYTIME,    "TTM_GETDELAYTIME",     MC_CONTROL, 0L ),
    msgpick( 1, 0, TTM_GETTIPBKCOLOR,   "TTM_GETTIPBKCOLOR",    MC_CONTROL, 0L ),
    msgpick( 1, 0, TTM_GETTIPTEXTCOLOR, "TTM_GETTIPTEXTCOLOR",  MC_CONTROL, 0L ),
    msgpick( 1, 0, TTM_SETMAXTIPWIDTH,  "TTM_SETMAXTIPWIDTH",   MC_CONTROL, 0L ),
    msgpick( 1, 0, TTM_GETMAXTIPWIDTH,  "TTM_GETMAXTIPWIDTH",   MC_CONTROL, 0L ),
    msgpick( 1, 0, TTM_SETMARGIN,       "TTM_SETMARGIN",        MC_CONTROL, 0L ),
    msgpick( 1, 0, TTM_GETMARGIN,       "TTM_GETMARGIN",        MC_CONTROL, 0L ),
    msgpick( 1, 0, TTM_POP,             "TTM_POP",              MC_CONTROL, 0L ),
    msgpick( 1, 0, TTM_UPDATE,          "TTM_UPDATE",           MC_CONTROL, 0L ),
    msgpick( 1, 0, TTM_GETBUBBLESIZE,   "TTM_GETBUBBLESIZE",    MC_CONTROL, 0L ),
    msgpick( 1, 0, TTM_ADJUSTRECT,      "TTM_ADJUSTRECT",       MC_CONTROL, 0L ),
    msgpick( 1, 0, TTM_SETTITLEA,       "TTM_SETTITLE",         MC_CONTROL, 0L ),
    msgpick( 1, 0, TTM_SETTITLEW,       "TTM_SETTITLE",         MC_CONTROL, 0L ),
    msgpick( 1, 0, TTM_POPUP,           "TTM_POPUP",            MC_CONTROL, 0L ),
    msgpick( 1, 0, TTM_GETTITLE,        "TTM_GETTITLE",         MC_CONTROL, 0L ),
    msgpick( 1, 0, TTM_ADDTOOLW,        "TTM_ADDTOOL",          MC_CONTROL, 0L ),
    msgpick( 1, 0, TTM_DELTOOLW,        "TTM_DELTOOL",          MC_CONTROL, 0L ),
    msgpick( 1, 0, TTM_NEWTOOLRECTW,    "TTM_NEWTOOLRECT",      MC_CONTROL, 0L ),
    msgpick( 1, 0, TTM_GETTOOLINFOW,    "TTM_GETTOOLINFO",      MC_CONTROL, 0L ),
    msgpick( 1, 0, TTM_SETTOOLINFOW,    "TTM_SETTOOLINFO",      MC_CONTROL, 0L ),
    msgpick( 1, 0, TTM_HITTESTW,        "TTM_HITTEST",          MC_CONTROL, 0L ),
    msgpick( 1, 0, TTM_GETTEXTW,        "TTM_GETTEXT",          MC_CONTROL, 0L ),
    msgpick( 1, 0, TTM_UPDATETIPTEXTW,  "TTM_UPDATETIPTEXT",    MC_CONTROL, 0L ),
    msgpick( 1, 0, TTM_ENUMTOOLSW,      "TTM_ENUMTOOLS",        MC_CONTROL, 0L ),
    msgpick( 1, 0, TTM_GETCURRENTTOOLW, "TTM_GETCURRENTTOOL",   MC_CONTROL, 0L ),
};

WORD ToolTipsMessageArraySize = sizeof( ToolTipsMessageArray ) / sizeof( message );

message near StatusBarMessageArray[] = {
    msgpick( 1, 0, SB_SETTEXTA,         "SB_SETTEXT",       MC_CONTROL, 0L ),
    msgpick( 1, 0, SB_GETTEXTA,         "SB_GETTEXT",       MC_CONTROL, 0L ),
    msgpick( 1, 0, SB_GETTEXTLENGTHA,   "SB_GETTEXTLENGTH", MC_CONTROL, 0L ),
    msgpick( 1, 0, SB_SETPARTS,         "SB_SETPARTS",      MC_CONTROL, 0L ),
    msgpick( 1, 0, SB_GETPARTS,         "SB_GETPARTS",      MC_CONTROL, 0L ),
    msgpick( 1, 0, SB_GETBORDERS,       "SB_GETBORDERS",    MC_CONTROL, 0L ),
    msgpick( 1, 0, SB_SETMINHEIGHT,     "SB_SETMINHEIGHT",  MC_CONTROL, 0L ),
    msgpick( 1, 0, SB_SIMPLE,           "SB_SIMPLE",        MC_CONTROL, 0L ),
    msgpick( 1, 0, SB_GETRECT,          "SB_GETRECT",       MC_CONTROL, 0L ),
    msgpick( 1, 0, SB_SETTEXTW,         "SB_SETTEXT",       MC_CONTROL, 0L ),
    msgpick( 1, 0, SB_GETTEXTLENGTHW,   "SB_GETTEXTLENGTH", MC_CONTROL, 0L ),
    msgpick( 1, 0, SB_GETTEXTW,         "SB_GETTEXT",       MC_CONTROL, 0L ),
    msgpick( 1, 0, SB_ISSIMPLE,         "SB_ISSIMPLE",      MC_CONTROL, 0L ),
    msgpick( 1, 0, SB_SETICON,          "SB_SETICON",       MC_CONTROL, 0L ),
    msgpick( 1, 0, SB_SETTIPTEXTA,      "SB_SETTIPTEXT",    MC_CONTROL, 0L ),
    msgpick( 1, 0, SB_SETTIPTEXTW,      "SB_SETTIPTEXT",    MC_CONTROL, 0L ),
    msgpick( 1, 0, SB_GETTIPTEXTA,      "SB_GETTIPTEXT",    MC_CONTROL, 0L ),
    msgpick( 1, 0, SB_GETTIPTEXTW,      "SB_GETTIPTEXT",    MC_CONTROL, 0L ),
    msgpick( 1, 0, SB_GETICON,          "SB_GETICON",       MC_CONTROL, 0L ),
};

WORD StatusBarMessageArraySize = sizeof( StatusBarMessageArray ) / sizeof( message );

message near TrackBarMessageArray[] = {
    msgpick( 1, 0, TBM_GETPOS,          "TBM_GETPOS",           MC_CONTROL, 0L ),
    msgpick( 1, 0, TBM_GETRANGEMIN,     "TBM_GETRANGEMIN",      MC_CONTROL, 0L ),
    msgpick( 1, 0, TBM_GETRANGEMAX,     "TBM_GETRANGEMAX",      MC_CONTROL, 0L ),
    msgpick( 1, 0, TBM_GETTIC,          "TBM_GETTIC",           MC_CONTROL, 0L ),
    msgpick( 1, 0, TBM_SETTIC,          "TBM_SETTIC",           MC_CONTROL, 0L ),
    msgpick( 1, 0, TBM_SETPOS,          "TBM_SETPOS",           MC_CONTROL, 0L ),
    msgpick( 1, 0, TBM_SETRANGE,        "TBM_SETRANGE",         MC_CONTROL, 0L ),
    msgpick( 1, 0, TBM_SETRANGEMIN,     "TBM_SETRANGEMIN",      MC_CONTROL, 0L ),
    msgpick( 1, 0, TBM_SETRANGEMAX,     "TBM_SETRANGEMAX",      MC_CONTROL, 0L ),
    msgpick( 1, 0, TBM_CLEARTICS,       "TBM_CLEARTICS",        MC_CONTROL, 0L ),
    msgpick( 1, 0, TBM_SETSEL,          "TBM_SETSEL",           MC_CONTROL, 0L ),
    msgpick( 1, 0, TBM_SETSELSTART,     "TBM_SETSELSTART",      MC_CONTROL, 0L ),
    msgpick( 1, 0, TBM_SETSELEND,       "TBM_SETSELEND",        MC_CONTROL, 0L ),
    msgpick( 1, 0, TBM_GETPTICS,        "TBM_GETPTICS",         MC_CONTROL, 0L ),
    msgpick( 1, 0, TBM_GETTICPOS,       "TBM_GETTICPOS",        MC_CONTROL, 0L ),
    msgpick( 1, 0, TBM_GETNUMTICS,      "TBM_GETNUMTICS",       MC_CONTROL, 0L ),
    msgpick( 1, 0, TBM_GETSELSTART,     "TBM_GETSELSTART",      MC_CONTROL, 0L ),
    msgpick( 1, 0, TBM_GETSELEND,       "TBM_GETSELEND",        MC_CONTROL, 0L ),
    msgpick( 1, 0, TBM_CLEARSEL,        "TBM_CLEARSEL",         MC_CONTROL, 0L ),
    msgpick( 1, 0, TBM_SETTICFREQ,      "TBM_SETTICFREQ",       MC_CONTROL, 0L ),
    msgpick( 1, 0, TBM_SETPAGESIZE,     "TBM_SETPAGESIZE",      MC_CONTROL, 0L ),
    msgpick( 1, 0, TBM_GETPAGESIZE,     "TBM_GETPAGESIZE",      MC_CONTROL, 0L ),
    msgpick( 1, 0, TBM_SETLINESIZE,     "TBM_SETLINESIZE",      MC_CONTROL, 0L ),
    msgpick( 1, 0, TBM_GETLINESIZE,     "TBM_GETLINESIZE",      MC_CONTROL, 0L ),
    msgpick( 1, 0, TBM_GETTHUMBRECT,    "TBM_GETTHUMBRECT",     MC_CONTROL, 0L ),
    msgpick( 1, 0, TBM_GETCHANNELRECT,  "TBM_GETCHANNELRECT",   MC_CONTROL, 0L ),
    msgpick( 1, 0, TBM_SETTHUMBLENGTH,  "TBM_SETTHUMBLENGTH",   MC_CONTROL, 0L ),
    msgpick( 1, 0, TBM_GETTHUMBLENGTH,  "TBM_GETTHUMBLENGTH",   MC_CONTROL, 0L ),
    msgpick( 1, 0, TBM_SETTOOLTIPS,     "TBM_SETTOOLTIPS",      MC_CONTROL, 0L ),
    msgpick( 1, 0, TBM_GETTOOLTIPS,     "TBM_GETTOOLTIPS",      MC_CONTROL, 0L ),
    msgpick( 1, 0, TBM_SETTIPSIDE,      "TBM_SETTIPSIDE",       MC_CONTROL, 0L ),
    msgpick( 1, 0, TBM_SETBUDDY,        "TBM_SETBUDDY",         MC_CONTROL, 0L ),
    msgpick( 1, 0, TBM_GETBUDDY,        "TBM_GETBUDDY",         MC_CONTROL, 0L )
};

WORD TrackBarMessageArraySize = sizeof( TrackBarMessageArray ) / sizeof( message );

message near UpDownMessageArray[] = {
    msgpick( 1, 0, UDM_SETRANGE,    "UDM_SETRANGE",     MC_CONTROL, 0L ),
    msgpick( 1, 0, UDM_GETRANGE,    "UDM_GETRANGE",     MC_CONTROL, 0L ),
    msgpick( 1, 0, UDM_SETPOS,      "UDM_SETPOS",       MC_CONTROL, 0L ),
    msgpick( 1, 0, UDM_GETPOS,      "UDM_GETPOS",       MC_CONTROL, 0L ),
    msgpick( 1, 0, UDM_SETBUDDY,    "UDM_SETBUDDY",     MC_CONTROL, 0L ),
    msgpick( 1, 0, UDM_GETBUDDY,    "UDM_GETBUDDY",     MC_CONTROL, 0L ),
    msgpick( 1, 0, UDM_SETACCEL,    "UDM_SETACCEL",     MC_CONTROL, 0L ),
    msgpick( 1, 0, UDM_GETACCEL,    "UDM_GETACCEL",     MC_CONTROL, 0L ),
    msgpick( 1, 0, UDM_SETBASE,     "UDM_SETBASE",      MC_CONTROL, 0L ),
    msgpick( 1, 0, UDM_GETBASE,     "UDM_GETBASE",      MC_CONTROL, 0L ),
    msgpick( 1, 0, UDM_SETRANGE32,  "UDM_SETRANGE32",   MC_CONTROL, 0L ),
    msgpick( 1, 0, UDM_GETRANGE32,  "UDM_GETRANGE32",   MC_CONTROL, 0L ),
    msgpick( 1, 0, UDM_SETPOS32,    "UDM_SETPOS32",     MC_CONTROL, 0L ),
    msgpick( 1, 0, UDM_GETPOS32,    "UDM_GETPOS32",     MC_CONTROL, 0L ),
};

WORD UpDownMessageArraySize = sizeof( UpDownMessageArray ) / sizeof( message );

message near ProgressBarMessageArray[] = {
    msgpick( 1, 0, PBM_SETRANGE,    "PBM_SETRANGE",     MC_CONTROL, 0L ),
    msgpick( 1, 0, PBM_SETPOS,      "PBM_SETPOS",       MC_CONTROL, 0L ),
    msgpick( 1, 0, PBM_DELTAPOS,    "PBM_DELTAPOS",     MC_CONTROL, 0L ),
    msgpick( 1, 0, PBM_SETSTEP,     "PBM_SETSTEP",      MC_CONTROL, 0L ),
    msgpick( 1, 0, PBM_STEPIT,      "PBM_STEPIT",       MC_CONTROL, 0L ),
    msgpick( 1, 0, PBM_SETRANGE32,  "PBM_SETRANGE32",   MC_CONTROL, 0L ),
    msgpick( 1, 0, PBM_GETRANGE,    "PBM_GETRANGE",     MC_CONTROL, 0L ),
    msgpick( 1, 0, PBM_GETPOS,      "PBM_GETPOS",       MC_CONTROL, 0L ),
    msgpick( 1, 0, PBM_SETBARCOLOR, "PBM_SETBARCOLOR",  MC_CONTROL, 0L ),
    msgpick( 1, 0, PBM_SETMARQUEE,  "PBM_SETMARQUEE",   MC_CONTROL, 0L ),
    msgpick( 1, 0, PBM_GETSTEP,     "PBM_GETSTEP",      MC_CONTROL, 0L ),
    msgpick( 1, 0, PBM_GETBKCOLOR,  "PBM_GETBKCOLOR",   MC_CONTROL, 0L ),
    msgpick( 1, 0, PBM_GETBARCOLOR, "PBM_GETBARCOLOR",  MC_CONTROL, 0L ),
    msgpick( 1, 0, PBM_SETSTATE,    "PBM_SETSTATE",     MC_CONTROL, 0L ),
    msgpick( 1, 0, PBM_GETSTATE,    "PBM_GETSTATE",     MC_CONTROL, 0L )
};

WORD ProgressBarMessageArraySize = sizeof( ProgressBarMessageArray ) / sizeof( message );

message near HotKeyMessageArray[] = {
    msgpick( 1, 0, HKM_SETHOTKEY,   "HKM_SETHOTKEY",    MC_CONTROL, 0L ),
    msgpick( 1, 0, HKM_GETHOTKEY,   "HKM_GETHOTKEY",    MC_CONTROL, 0L ),
    msgpick( 1, 0, HKM_SETRULES,    "HKM_SETRULES",     MC_CONTROL, 0L )
};

WORD HotKeyMessageArraySize = sizeof( HotKeyMessageArray ) / sizeof( message );

message near ListViewMessageArray[] = {
    msgpick( 1, 0, LVM_GETBKCOLOR,          "LVM_GETBKCOLOR",           MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_SETBKCOLOR,          "LVM_SETBKCOLOR",           MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_GETIMAGELIST,        "LVM_GETIMAGELIST",         MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_SETIMAGELIST,        "LVM_SETIMAGELIST",         MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_GETITEMCOUNT,        "LVM_GETITEMCOUNT",         MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_GETITEMA,            "LVM_GETITEMA",             MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_SETITEMA,            "LVM_SETITEMA",             MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_INSERTITEMA,         "LVM_INSERTITEMA",          MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_DELETEITEM,          "LVM_DELETEITEM",           MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_DELETEALLITEMS,      "LVM_DELETEALLITEMS",       MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_GETCALLBACKMASK,     "LVM_GETCALLBACKMASK",      MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_SETCALLBACKMASK,     "LVM_SETCALLBACKMASK",      MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_GETNEXTITEM,         "LVM_GETNEXTITEM",          MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_FINDITEMA,           "LVM_FINDITEMA",            MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_GETITEMRECT,         "LVM_GETITEMRECT",          MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_SETITEMPOSITION,     "LVM_SETITEMPOSITION",      MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_GETITEMPOSITION,     "LVM_GETITEMPOSITION",      MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_GETSTRINGWIDTHA,     "LVM_GETSTRINGWIDTHA",      MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_HITTEST,             "LVM_HITTEST",              MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_ENSUREVISIBLE,       "LVM_ENSUREVISIBLE",        MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_SCROLL,              "LVM_SCROLL",               MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_REDRAWITEMS,         "LVM_REDRAWITEMS",          MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_ARRANGE,             "LVM_ARRANGE",              MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_EDITLABELA,          "LVM_EDITLABEL",            MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_GETEDITCONTROL,      "LVM_GETEDITCONTROL",       MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_GETCOLUMNA,          "LVM_GETCOLUMN",            MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_SETCOLUMNA,          "LVM_SETCOLUMN",            MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_INSERTCOLUMNA,       "LVM_INSERTCOLUMN",         MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_DELETECOLUMN,        "LVM_DELETECOLUMN",         MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_GETCOLUMNWIDTH,      "LVM_GETCOLUMNWIDTH",       MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_SETCOLUMNWIDTH,      "LVM_SETCOLUMNWIDTH",       MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_GETHEADER,           "LVM_GETHEADER",            MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_CREATEDRAGIMAGE,     "LVM_CREATEDRAGIMAGE",      MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_GETVIEWRECT,         "LVM_GETVIEWRECT",          MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_GETTEXTCOLOR,        "LVM_GETTEXTCOLOR",         MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_SETTEXTCOLOR,        "LVM_SETTEXTCOLOR",         MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_GETTEXTBKCOLOR,      "LVM_GETTEXTBKCOLOR",       MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_SETTEXTBKCOLOR,      "LVM_SETTEXTBKCOLOR",       MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_GETTOPINDEX,         "LVM_GETTOPINDEX",          MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_GETCOUNTPERPAGE,     "LVM_GETCOUNTPERPAGE",      MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_GETORIGIN,           "LVM_GETORIGIN",            MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_UPDATE,              "LVM_UPDATE",               MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_SETITEMSTATE,        "LVM_SETITEMSTATE",         MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_GETITEMSTATE,        "LVM_GETITEMSTATE",         MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_GETITEMTEXTA,        "LVM_GETITEMTEXT",          MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_SETITEMTEXTA,        "LVM_SETITEMTEXT",          MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_SETITEMCOUNT,        "LVM_SETITEMCOUNT",         MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_SORTITEMS,           "LVM_SORTITEMS",            MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_SETITEMPOSITION32,   "LVM_SETITEMPOSITION32",    MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_GETSELECTEDCOUNT,    "LVM_GETSELECTEDCOUNT",     MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_GETITEMSPACING,      "LVM_GETITEMSPACING",       MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_GETISEARCHSTRINGA,   "LVM_GETISEARCHSTRING",     MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_SETICONSPACING,      "LVM_SETICONSPACING",       MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_SETEXTENDEDLISTVIEWSTYLE, "LVM_SETEXTENDEDLISTVIEWSTYLE",
             MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_GETEXTENDEDLISTVIEWSTYLE, "LVM_GETEXTENDEDLISTVIEWSTYLE",
             MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_GETSUBITEMRECT,      "LVM_GETSUBITEMRECT",       MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_SUBITEMHITTEST,      "LVM_SUBITEMHITTEST",       MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_SETCOLUMNORDERARRAY, "LVM_SETCOLUMNORDERARRAY",  MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_GETCOLUMNORDERARRAY, "LVM_GETCOLUMNORDERARRAY",  MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_SETHOTITEM,          "LVM_SETHOTITEM",           MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_GETHOTITEM,          "LVM_GETHOTITEM",           MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_SETHOTCURSOR,        "LVM_SETHOTCURSOR",         MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_GETHOTCURSOR,        "LVM_GETHOTCURSOR",         MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_APPROXIMATEVIEWRECT, "LVM_APPROXIMATEVIEWRECT",  MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_SETWORKAREAS,        "LVM_SETWORKAREAS",         MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_GETSELECTIONMARK,    "LVM_GETSELECTIONMARK",     MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_SETSELECTIONMARK,    "LVM_SETSELECTIONMARK",     MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_SETBKIMAGEA,         "LVM_SETBKIMAGE",           MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_GETBKIMAGEA,         "LVM_GETBKIMAGE",           MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_GETWORKAREAS,        "LVM_GETWORKAREAS",         MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_SETHOVERTIME,        "LVM_SETHOVERTIME",         MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_GETHOVERTIME,        "LVM_GETHOVERTIME",         MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_GETNUMBEROFWORKAREAS, "LVM_GETNUMBEROFWORKAREAS",
             MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_SETTOOLTIPS,         "LVM_SETTOOLTIPS",          MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_GETITEMW,            "LVM_GETITEM",              MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_SETITEMW,            "LVM_SETITEM",              MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_INSERTITEMW,         "LVM_INSERTITEM",           MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_GETTOOLTIPS,         "LVM_GETTOOLTIPS",          MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_SORTITEMSEX,         "LVM_SORTITEMSEX",          MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_FINDITEMW,           "LVM_FINDITEM",             MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_GETSTRINGWIDTHW,     "LVM_GETSTRINGWIDTH",       MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_GETGROUPSTATE,       "LVM_GETGROUPSTATE",        MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_GETFOCUSEDGROUP,     "LVM_GETFOCUSEDGROUP",      MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_GETCOLUMNW,          "LVM_GETCOLUMN",            MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_SETCOLUMNW,          "LVM_SETCOLUMN",            MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_INSERTCOLUMNW,       "LVM_INSERTCOLUMN",         MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_GETGROUPRECT,        "LVM_GETGROUPRECT",         MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_GETITEMTEXTW,        "LVM_GETITEMTEXT",          MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_SETITEMTEXTW,        "LVM_SETITEMTEXT",          MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_GETISEARCHSTRINGW,   "LVM_GETISEARCHSTRING",     MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_EDITLABELW,          "LVM_EDITLABEL",            MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_SETBKIMAGEW,         "LVM_SETBKIMAGE",           MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_GETBKIMAGEW,         "LVM_GETBKIMAGE",           MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_SETSELECTEDCOLUMN,   "LVM_SETSELECTEDCOLUMN",    MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_SETVIEW,             "LVM_SETVIEW",              MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_GETVIEW,             "LVM_GETVIEW",              MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_INSERTGROUP,         "LVM_INSERTGROUP",          MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_SETGROUPINFO,        "LVM_SETGROUPINFO",         MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_GETGROUPINFO,        "LVM_GETGROUPINFO",         MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_REMOVEGROUP,         "LVM_REMOVEGROUP",          MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_MOVEGROUP,           "LVM_MOVEGROUP",            MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_GETGROUPCOUNT,       "LVM_GETGROUPCOUNT",        MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_GETGROUPINFOBYINDEX, "LVM_GETGROUPINFOBYINDEX",  MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_MOVEITEMTOGROUP,     "LVM_MOVEITEMTOGROUP",      MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_SETGROUPMETRICS,     "LVM_SETGROUPMETRICS",      MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_GETGROUPMETRICS,     "LVM_GETGROUPMETRICS",      MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_ENABLEGROUPVIEW,     "LVM_ENABLEGROUPVIEW",      MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_SORTGROUPS,          "LVM_SORTGROUPS",           MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_INSERTGROUPSORTED,   "LVM_INSERTGROUPSORTED",    MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_REMOVEALLGROUPS,     "LVM_REMOVEALLGROUPS",      MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_HASGROUP,            "LVM_HASGROUP",             MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_SETTILEVIEWINFO,     "LVM_SETTILEVIEWINFO",      MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_GETTILEVIEWINFO,     "LVM_GETTILEVIEWINFO",      MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_SETTILEINFO,         "LVM_SETTILEINFO",          MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_GETTILEINFO,         "LVM_GETTILEINFO",          MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_SETINSERTMARK,       "LVM_SETINSERTMARK",        MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_GETINSERTMARK,       "LVM_GETINSERTMARK",        MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_INSERTMARKHITTEST,   "LVM_INSERTMARKHITTEST",    MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_GETINSERTMARKRECT,   "LVM_GETINSERTMARKRECT",    MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_SETINSERTMARKCOLOR,  "LVM_SETINSERTMARKCOLOR",   MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_GETINSERTMARKCOLOR,  "LVM_GETINSERTMARKCOLOR",   MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_SETINFOTIP,          "LVM_SETINFOTIP",           MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_GETSELECTEDCOLUMN,   "LVM_GETSELECTEDCOLUMN",    MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_ISGROUPVIEWENABLED,  "LVM_ISGROUPVIEWENABLED",   MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_GETOUTLINECOLOR,     "LVM_GETOUTLINECOLOR",      MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_SETOUTLINECOLOR,     "LVM_SETOUTLINECOLOR",      MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_CANCELEDITLABEL,     "LVM_CANCELEDITLABEL",      MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_MAPINDEXTOID,        "LVM_MAPINDEXTOID",         MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_MAPIDTOINDEX,        "LVM_MAPIDTOINDEX",         MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_ISITEMVISIBLE,       "LVM_ISITEMVISIBLE",        MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_GETEMPTYTEXT,        "LVM_GETEMPTYTEXT",         MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_GETFOOTERRECT,       "LVM_GETFOOTERRECT",        MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_GETFOOTERINFO,       "LVM_GETFOOTERINFO",        MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_GETFOOTERITEMRECT,   "LVM_GETFOOTERITEMRECT",    MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_GETFOOTERITEM,       "LVM_GETFOOTERITEM",        MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_GETITEMINDEXRECT,    "LVM_GETITEMINDEXRECT",     MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_SETITEMINDEXSTATE,   "LVM_SETITEMINDEXSTATE",    MC_CONTROL, 0L ),
    msgpick( 1, 0, LVM_GETNEXTITEMINDEX,    "LVM_GETNEXTITEMINDEX",     MC_CONTROL, 0L ),
};

WORD ListViewMessageArraySize = sizeof( ListViewMessageArray ) / sizeof( message );

message near TreeViewMessageArray[] = {
    msgpick( 1, 0, TVM_INSERTITEMA,         "TVM_INSERTITEM",           MC_CONTROL, 0L ),
    msgpick( 1, 0, TVM_DELETEITEM,          "TVM_DELETEITEM",           MC_CONTROL, 0L ),
    msgpick( 1, 0, TVM_EXPAND,              "TVM_EXPAND",               MC_CONTROL, 0L ),
    msgpick( 1, 0, TVM_GETITEMRECT,         "TVM_GETITEMRECT",          MC_CONTROL, 0L ),
    msgpick( 1, 0, TVM_GETCOUNT,            "TVM_GETCOUNT",             MC_CONTROL, 0L ),
    msgpick( 1, 0, TVM_GETINDENT,           "TVM_GETINDENT",            MC_CONTROL, 0L ),
    msgpick( 1, 0, TVM_SETINDENT,           "TVM_SETINDENT",            MC_CONTROL, 0L ),
    msgpick( 1, 0, TVM_GETIMAGELIST,        "TVM_GETIMAGELIST",         MC_CONTROL, 0L ),
    msgpick( 1, 0, TVM_SETIMAGELIST,        "TVM_SETIMAGELIST",         MC_CONTROL, 0L ),
    msgpick( 1, 0, TVM_GETNEXTITEM,         "TVM_GETNEXTITEM",          MC_CONTROL, 0L ),
    msgpick( 1, 0, TVM_SELECTITEM,          "TVM_SELECTITEM",           MC_CONTROL, 0L ),
    msgpick( 1, 0, TVM_GETITEMA,            "TVM_GETITEM",              MC_CONTROL, 0L ),
    msgpick( 1, 0, TVM_SETITEMA,            "TVM_SETITEM",              MC_CONTROL, 0L ),
    msgpick( 1, 0, TVM_EDITLABELA,          "TVM_EDITLABEL",            MC_CONTROL, 0L ),
    msgpick( 1, 0, TVM_GETEDITCONTROL,      "TVM_GETEDITCONTROL",       MC_CONTROL, 0L ),
    msgpick( 1, 0, TVM_GETVISIBLECOUNT,     "TVM_GETVISIBLECOUNT",      MC_CONTROL, 0L ),
    msgpick( 1, 0, TVM_HITTEST,             "TVM_HITTEST",              MC_CONTROL, 0L ),
    msgpick( 1, 0, TVM_CREATEDRAGIMAGE,     "TVM_CREATEDRAGIMAGE",      MC_CONTROL, 0L ),
    msgpick( 1, 0, TVM_SORTCHILDREN,        "TVM_SORTCHILDREN",         MC_CONTROL, 0L ),
    msgpick( 1, 0, TVM_ENSUREVISIBLE,       "TVM_ENSUREVISIBLE",        MC_CONTROL, 0L ),
    msgpick( 1, 0, TVM_SORTCHILDRENCB,      "TVM_SORTCHILDRENCB",       MC_CONTROL, 0L ),
    msgpick( 1, 0, TVM_ENDEDITLABELNOW,     "TVM_ENDEDITLABELNOW",      MC_CONTROL, 0L ),
    msgpick( 1, 0, TVM_GETISEARCHSTRINGA,   "TVM_GETISEARCHSTRING",     MC_CONTROL, 0L ),
    msgpick( 1, 0, TVM_SETTOOLTIPS,         "TVM_SETTOOLTIPS",          MC_CONTROL, 0L ),
    msgpick( 1, 0, TVM_GETTOOLTIPS,         "TVM_GETTOOLTIPS",          MC_CONTROL, 0L ),
    msgpick( 1, 0, TVM_SETINSERTMARK,       "TVM_SETINSERTMARK",        MC_CONTROL, 0L ),
    msgpick( 1, 0, TVM_SETITEMHEIGHT,       "TVM_SETITEMHEIGHT",        MC_CONTROL, 0L ),
    msgpick( 1, 0, TVM_GETITEMHEIGHT,       "TVM_GETITEMHEIGHT",        MC_CONTROL, 0L ),
    msgpick( 1, 0, TVM_SETBKCOLOR,          "TVM_SETBKCOLOR",           MC_CONTROL, 0L ),
    msgpick( 1, 0, TVM_SETTEXTCOLOR,        "TVM_SETTEXTCOLOR",         MC_CONTROL, 0L ),
    msgpick( 1, 0, TVM_GETBKCOLOR,          "TVM_GETBKCOLOR",           MC_CONTROL, 0L ),
    msgpick( 1, 0, TVM_GETTEXTCOLOR,        "TVM_GETTEXTCOLOR",         MC_CONTROL, 0L ),
    msgpick( 1, 0, TVM_SETSCROLLTIME,       "TVM_SETSCROLLTIME",        MC_CONTROL, 0L ),
    msgpick( 1, 0, TVM_GETSCROLLTIME,       "TVM_GETSCROLLTIME",        MC_CONTROL, 0L ),
    msgpick( 1, 0, TVM_SETINSERTMARKCOLOR,  "TVM_SETINSERTMARKCOLOR",   MC_CONTROL, 0L ),
    msgpick( 1, 0, TVM_GETINSERTMARKCOLOR,  "TVM_GETINSERTMARKCOLOR",   MC_CONTROL, 0L ),
    msgpick( 1, 0, TVM_GETITEMSTATE,        "TVM_GETITEMSTATE",         MC_CONTROL, 0L ),
    msgpick( 1, 0, TVM_SETLINECOLOR,        "TVM_SETLINECOLOR",         MC_CONTROL, 0L ),
    msgpick( 1, 0, TVM_GETLINECOLOR,        "TVM_GETLINECOLOR",         MC_CONTROL, 0L ),
    msgpick( 1, 0, TVM_MAPACCIDTOHTREEITEM, "TVM_MAPACCIDTOHTREEITEM",  MC_CONTROL, 0L ),
    msgpick( 1, 0, TVM_MAPHTREEITEMTOACCID, "TVM_MAPHTREEITEMTOACCID",  MC_CONTROL, 0L ),
    msgpick( 1, 0, TVM_SETEXTENDEDSTYLE,    "TVM_SETEXTENDEDSTYLE",     MC_CONTROL, 0L ),
    msgpick( 1, 0, TVM_GETEXTENDEDSTYLE,    "TVM_GETEXTENDEDSTYLE",     MC_CONTROL, 0L ),
    msgpick( 1, 0, TVM_INSERTITEMW,         "TVM_INSERTITEM",           MC_CONTROL, 0L ),
    msgpick( 1, 0, TVM_SETAUTOSCROLLINFO,   "TVM_SETAUTOSCROLLINFO",    MC_CONTROL, 0L ),
    msgpick( 1, 0, TVM_GETITEMW,            "TVM_GETITEM",              MC_CONTROL, 0L ),
    msgpick( 1, 0, TVM_SETITEMW,            "TVM_SETITEM",              MC_CONTROL, 0L ),
    msgpick( 1, 0, TVM_GETISEARCHSTRINGW,   "TVM_GETISEARCHSTRING",     MC_CONTROL, 0L ),
    msgpick( 1, 0, TVM_EDITLABELW,          "TVM_EDITLABEL",            MC_CONTROL, 0L ),
    msgpick( 1, 0, TVM_GETSELECTEDCOUNT,    "TVM_GETSELECTEDCOUNT",     MC_CONTROL, 0L ),
    msgpick( 1, 0, TVM_SHOWINFOTIP,         "TVM_SHOWINFOTIP",          MC_CONTROL, 0L ),
    msgpick( 1, 0, TVM_GETITEMPARTRECT,     "TVM_GETITEMPARTRECT",      MC_CONTROL, 0L )
};

WORD TreeViewMessageArraySize = sizeof( TreeViewMessageArray ) / sizeof( message );

message near ComboBoxExMessageArray[] = {
    msgpick( 1, 0, CBEM_INSERTITEMA,        "CBEM_INSERTITEM",          MC_CONTROL, 0L ),
    msgpick( 1, 0, CBEM_SETIMAGELIST,       "CBEM_SETIMAGELIST",        MC_CONTROL, 0L ),
    msgpick( 1, 0, CBEM_GETIMAGELIST,       "CBEM_GETIMAGELIST",        MC_CONTROL, 0L ),
    msgpick( 1, 0, CBEM_GETITEMA,           "CBEM_GETITEM",             MC_CONTROL, 0L ),
    msgpick( 1, 0, CBEM_SETITEMA,           "CBEM_SETITEM",             MC_CONTROL, 0L ),
    msgpick( 1, 0, CBEM_GETCOMBOCONTROL,    "CBEM_GETCOMBOCONTROL",     MC_CONTROL, 0L ),
    msgpick( 1, 0, CBEM_GETEDITCONTROL,     "CBEM_GETEDITCONTROL",      MC_CONTROL, 0L ),
    msgpick( 1, 0, CBEM_SETEXSTYLE,         "CBEM_SETEXSTYLE",          MC_CONTROL, 0L ),
    msgpick( 1, 0, CBEM_GETEXSTYLE,         "CBEM_GETEXSTYLE",          MC_CONTROL, 0L ),
    msgpick( 1, 0, CBEM_HASEDITCHANGED,     "CBEM_HASEDITCHANGED",      MC_CONTROL, 0L ),
    msgpick( 1, 0, CBEM_INSERTITEMW,        "CBEM_INSERTITEM",          MC_CONTROL, 0L ),
    msgpick( 1, 0, CBEM_SETITEMW,           "CBEM_SETITEM",             MC_CONTROL, 0L ),
    msgpick( 1, 0, CBEM_GETITEMW,           "CBEM_GETITEM",             MC_CONTROL, 0L ),
    msgpick( 1, 0, CBEM_SETEXTENDEDSTYLE,   "CBEM_SETEXTENDEDSTYLE",    MC_CONTROL, 0L )
};

WORD ComboBoxExMessageArraySize = sizeof( ComboBoxExMessageArray ) / sizeof( message );

message near TabControlMessageArray[] = {
    msgpick( 1, 0, TCM_GETIMAGELIST,        "TCM_GETIMAGELIST",     MC_CONTROL, 0L ),
    msgpick( 1, 0, TCM_SETIMAGELIST,        "TCM_SETIMAGELIST",     MC_CONTROL, 0L ),
    msgpick( 1, 0, TCM_GETITEMCOUNT,        "TCM_GETITEMCOUNT",     MC_CONTROL, 0L ),
    msgpick( 1, 0, TCM_GETITEMA,            "TCM_GETITEM",          MC_CONTROL, 0L ),
    msgpick( 1, 0, TCM_SETITEMA,            "TCM_SETITEM",          MC_CONTROL, 0L ),
    msgpick( 1, 0, TCM_INSERTITEMA,         "TCM_INSERTITEMA",      MC_CONTROL, 0L ),
    msgpick( 1, 0, TCM_DELETEITEM,          "TCM_DELETEITEM",       MC_CONTROL, 0L ),
    msgpick( 1, 0, TCM_DELETEALLITEMS,      "TCM_DELETEALLITEMS",   MC_CONTROL, 0L ),
    msgpick( 1, 0, TCM_GETITEMRECT,         "TCM_GETITEMRECT",      MC_CONTROL, 0L ),
    msgpick( 1, 0, TCM_GETCURSEL,           "TCM_GETCURSEL",        MC_CONTROL, 0L ),
    msgpick( 1, 0, TCM_SETCURSEL,           "TCM_SETCURSEL",        MC_CONTROL, 0L ),
    msgpick( 1, 0, TCM_HITTEST,             "TCM_HITTEST",          MC_CONTROL, 0L ),
    msgpick( 1, 0, TCM_SETITEMEXTRA,        "TCM_SETITEMEXTRA",     MC_CONTROL, 0L ),
    msgpick( 1, 0, TCM_ADJUSTRECT,          "TCM_ADJUSTRECT",       MC_CONTROL, 0L ),
    msgpick( 1, 0, TCM_SETITEMSIZE,         "TCM_SETITEMSIZE",      MC_CONTROL, 0L ),
    msgpick( 1, 0, TCM_REMOVEIMAGE,         "TCM_REMOVEIMAGE",      MC_CONTROL, 0L ),
    msgpick( 1, 0, TCM_SETPADDING,          "TCM_SETPADDING",       MC_CONTROL, 0L ),
    msgpick( 1, 0, TCM_GETROWCOUNT,         "TCM_GETROWCOUNT",      MC_CONTROL, 0L ),
    msgpick( 1, 0, TCM_GETTOOLTIPS,         "TCM_GETTOOLTIPS",      MC_CONTROL, 0L ),
    msgpick( 1, 0, TCM_SETTOOLTIPS,         "TCM_SETTOOLTIPS",      MC_CONTROL, 0L ),
    msgpick( 1, 0, TCM_GETCURFOCUS,         "TCM_GETCURFOCUS",      MC_CONTROL, 0L ),
    msgpick( 1, 0, TCM_SETCURFOCUS,         "TCM_SETCURFOCUS",      MC_CONTROL, 0L ),
    msgpick( 1, 0, TCM_SETMINTABWIDTH,      "TCM_SETMINTABWIDTH",   MC_CONTROL, 0L ),
    msgpick( 1, 0, TCM_DESELECTALL,         "TCM_DESELECTALL",      MC_CONTROL, 0L ),
    msgpick( 1, 0, TCM_HIGHLIGHTITEM,       "TCM_HIGHLIGHTITEM",    MC_CONTROL, 0L ),
    msgpick( 1, 0, TCM_SETEXTENDEDSTYLE,    "TCM_SETEXTENDEDSTYLE", MC_CONTROL, 0L ),
    msgpick( 1, 0, TCM_GETEXTENDEDSTYLE,    "TCM_GETEXTENDEDSTYLE", MC_CONTROL, 0L ),
    msgpick( 1, 0, TCM_GETITEMW,            "TCM_GETITEM",          MC_CONTROL, 0L ),
    msgpick( 1, 0, TCM_SETITEMW,            "TCM_SETITEM",          MC_CONTROL, 0L ),
    msgpick( 1, 0, TCM_INSERTITEMW,         "TCM_INSERTITEM",       MC_CONTROL, 0L )
};

WORD TabControlMessageArraySize = sizeof( TabControlMessageArray ) / sizeof( message );

message near AnimateMessageArray[] = {
    msgpick( 1, 0, ACM_OPENA,       "ACM_OPEN",         MC_CONTROL, 0L ),
    msgpick( 1, 0, ACM_PLAY,        "ACM_PLAY",         MC_CONTROL, 0L ),
    msgpick( 1, 0, ACM_STOP,        "ACM_STOP",         MC_CONTROL, 0L ),
    msgpick( 1, 0, ACM_OPENW,       "ACM_OPEN",         MC_CONTROL, 0L ),
    msgpick( 1, 0, ACM_ISPLAYING,   "ACM_ISPLAYING",    MC_CONTROL, 0L )
};

WORD AnimateMessageArraySize = sizeof( AnimateMessageArray ) / sizeof( message );

message near MonthCalMessageArray[] = {
    msgpick( 1, 0, MCM_GETCURSEL,           "MCM_GETCURSEL",            MC_CONTROL, 0L ),
    msgpick( 1, 0, MCM_SETCURSEL,           "MCM_SETCURSEL",            MC_CONTROL, 0L ),
    msgpick( 1, 0, MCM_GETMAXSELCOUNT,      "MCM_GETMAXSELCOUNT",       MC_CONTROL, 0L ),
    msgpick( 1, 0, MCM_SETMAXSELCOUNT,      "MCM_SETMAXSELCOUNT",       MC_CONTROL, 0L ),
    msgpick( 1, 0, MCM_GETSELRANGE,         "MCM_GETSELRANGE",          MC_CONTROL, 0L ),
    msgpick( 1, 0, MCM_SETSELRANGE,         "MCM_SETSELRANGE",          MC_CONTROL, 0L ),
    msgpick( 1, 0, MCM_GETMONTHRANGE,       "MCM_GETMONTHRANGE",        MC_CONTROL, 0L ),
    msgpick( 1, 0, MCM_SETDAYSTATE,         "MCM_SETDAYSTATE",          MC_CONTROL, 0L ),
    msgpick( 1, 0, MCM_GETMINREQRECT,       "MCM_GETMINREQRECT",        MC_CONTROL, 0L ),
    msgpick( 1, 0, MCM_SETCOLOR,            "MCM_SETCOLOR",             MC_CONTROL, 0L ),
    msgpick( 1, 0, MCM_GETCOLOR,            "MCM_GETCOLOR",             MC_CONTROL, 0L ),
    msgpick( 1, 0, MCM_SETTODAY,            "MCM_SETTODAY",             MC_CONTROL, 0L ),
    msgpick( 1, 0, MCM_GETTODAY,            "MCM_GETTODAY",             MC_CONTROL, 0L ),
    msgpick( 1, 0, MCM_HITTEST,             "MCM_HITTEST",              MC_CONTROL, 0L ),
    msgpick( 1, 0, MCM_SETFIRSTDAYOFWEEK,   "MCM_SETFIRSTDAYOFWEEK",    MC_CONTROL, 0L ),
    msgpick( 1, 0, MCM_GETFIRSTDAYOFWEEK,   "MCM_GETFIRSTDAYOFWEEK",    MC_CONTROL, 0L ),
    msgpick( 1, 0, MCM_GETRANGE,            "MCM_GETRANGE",             MC_CONTROL, 0L ),
    msgpick( 1, 0, MCM_SETRANGE,            "MCM_SETRANGE",             MC_CONTROL, 0L ),
    msgpick( 1, 0, MCM_GETMONTHDELTA,       "MCM_GETMONTHDELTA",        MC_CONTROL, 0L ),
    msgpick( 1, 0, MCM_SETMONTHDELTA,       "MCM_SETMONTHDELTA",        MC_CONTROL, 0L ),
    msgpick( 1, 0, MCM_GETMAXTODAYWIDTH,    "MCM_GETMAXTODAYWIDTH",     MC_CONTROL, 0L ),
    msgpick( 1, 0, MCM_GETCURRENTVIEW,      "MCM_GETCURRENTVIEW",       MC_CONTROL, 0L ),
    msgpick( 1, 0, MCM_GETCALENDARCOUNT,    "MCM_GETCALENDARCOUNT",     MC_CONTROL, 0L ),
    msgpick( 1, 0, MCM_GETCALENDARGRIDINFO, "MCM_GETCALENDARGRIDINFO",  MC_CONTROL, 0L ),
    msgpick( 1, 0, MCM_GETCALID,            "MCM_GETCALID",             MC_CONTROL, 0L ),
    msgpick( 1, 0, MCM_SETCALID,            "MCM_SETCALID",             MC_CONTROL, 0L ),
    msgpick( 1, 0, MCM_SIZERECTTOMIN,       "MCM_SIZERECTTOMIN",        MC_CONTROL, 0L ),
    msgpick( 1, 0, MCM_SETCALENDARBORDER,   "MCM_SETCALENDARBORDER",    MC_CONTROL, 0L ),
    msgpick( 1, 0, MCM_GETCALENDARBORDER,   "MCM_GETCALENDARBORDER",    MC_CONTROL, 0L ),
    msgpick( 1, 0, MCM_SETCURRENTVIEW,      "MCM_SETCURRENTVIEW",       MC_CONTROL, 0L )
};

WORD MonthCalMessageArraySize = sizeof( MonthCalMessageArray ) / sizeof( message );

message near DateTimeMessageArray[] = {
    msgpick( 1, 0, DTM_GETSYSTEMTIME,   "DTM_GETSYSTEMTIME",    MC_CONTROL, 0L ),
    msgpick( 1, 0, DTM_SETSYSTEMTIME,   "DTM_SETSYSTEMTIME",    MC_CONTROL, 0L ),
    msgpick( 1, 0, DTM_GETRANGE,        "DTM_GETRANGE",         MC_CONTROL, 0L ),
    msgpick( 1, 0, DTM_SETRANGE,        "DTM_SETRANGE",         MC_CONTROL, 0L ),
    msgpick( 1, 0, DTM_SETFORMATA,      "DTM_SETFORMAT",        MC_CONTROL, 0L ),
    msgpick( 1, 0, DTM_SETMCCOLOR,      "DTM_SETMCCOLOR",       MC_CONTROL, 0L ),
    msgpick( 1, 0, DTM_GETMCCOLOR,      "DTM_GETMCCOLOR",       MC_CONTROL, 0L ),
    msgpick( 1, 0, DTM_GETMONTHCAL,     "DTM_GETMONTHCAL",      MC_CONTROL, 0L ),
    msgpick( 1, 0, DTM_SETMCFONT,       "DTM_SETMCFONT",        MC_CONTROL, 0L ),
    msgpick( 1, 0, DTM_GETMCFONT,       "DTM_GETMCFONT",        MC_CONTROL, 0L ),
    msgpick( 1, 0, DTM_SETMCSTYLE,      "DTM_SETMCSTYLE",       MC_CONTROL, 0L ),
    msgpick( 1, 0, DTM_GETMCSTYLE,      "DTM_GETMCSTYLE",       MC_CONTROL, 0L ),
    msgpick( 1, 0, DTM_CLOSEMONTHCAL,   "DTM_CLOSEMONTHCAL",    MC_CONTROL, 0L ),
    msgpick( 1, 0, DTM_GETDATETIMEPICKERINFO,   "DTM_GETDATETIMEPICKERINFO",
             MC_CONTROL, 0L ),
    msgpick( 1, 0, DTM_GETIDEALSIZE,    "DTM_GETIDEALSIZE",     MC_CONTROL, 0L ),
    msgpick( 1, 0, DTM_SETFORMATW,      "DTM_SETFORMAT",        MC_CONTROL, 0L ),
};

WORD DateTimeMessageArraySize = sizeof( DateTimeMessageArray ) / sizeof( message );

#endif
