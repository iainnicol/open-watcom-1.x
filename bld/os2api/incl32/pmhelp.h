/*
    OS/2 Presentation Manager Help Manager include file
    for 32-bit development.
*/


#ifndef PMHELP_INCLUDED
#define PMHELP_INCLUDED

#define HM_RESOURCEID 0
#define HM_PANELNAME  1

#define HMPANELTYPE_NUMBER 0
#define HMPANELTYPE_NAME   1

#define CMIC_HIDE_PANEL_ID   0
#define CMIC_SHOW_PANEL_ID   1
#define CMIC_TOGGLE_PANEL_ID 2

#define HM_MSG_BASE 0x0220

#define HM_DISMISS_WINDOW             HM_MSG_BASE+0x0001
#define HM_DISPLAY_HELP               HM_MSG_BASE+0x0002
#define HM_EXT_HELP                   HM_MSG_BASE+0x0003
#define HM_GENERAL_HELP               HM_EXT_HELP
#define HM_SET_ACTIVE_WINDOW          HM_MSG_BASE+0x0004
#define HM_LOAD_HELP_TABLE            HM_MSG_BASE+0x0005
#define HM_CREATE_HELP_TABLE          HM_MSG_BASE+0x0006
#define HM_SET_HELP_WINDOW_TITLE      HM_MSG_BASE+0x0007
#define HM_SET_SHOW_PANEL_ID          HM_MSG_BASE+0x0008
#define HM_REPLACE_HELP_FOR_HELP      HM_MSG_BASE+0x0009
#define HM_REPLACE_USING_HELP         HM_REPLACE_HELP_FOR_HELP
#define HM_HELP_INDEX                 HM_MSG_BASE+0x000a
#define HM_HELP_CONTENTS              HM_MSG_BASE+0x000b
#define HM_KEYS_HELP                  HM_MSG_BASE+0x000c
#define HM_SET_HELP_LIBRARY_NAME      HM_MSG_BASE+0x000d

#define HM_SET_OBJCOM_WINDOW          HM_MSG_BASE+0x0018
#define HM_UPDATE_OBJCOM_WINDOW_CHAIN HM_MSG_BASE+0x0019
#define HM_QUERY_DDF_DATA             HM_MSG_BASE+0x001a
#define HM_INVALIDATE_DDF_DATA        HM_MSG_BASE+0x001b
#define HM_QUERY                      HM_MSG_BASE+0x001c
#define HM_SET_COVERPAGE_SIZE         HM_MSG_BASE+0x001d

#define OPEN_COVERPAGE       1
#define OPEN_PAGE            2
#define SWAP_PAGE            3
#define OPEN_TOC             4
#define OPEN_INDEX           5
#define OPEN_HISTORY         6
#define OPEN_SEARCH_HIT_LIST 7
#define OPEN_LIBRARY         8
#define HELP_REQUESTED       9

#define HM_ERROR                  HM_MSG_BASE+0x000e
#define HM_HELPSUBITEM_NOT_FOUND  HM_MSG_BASE+0x000f
#define HM_QUERY_KEYS_HELP        HM_MSG_BASE+0x0010
#define HM_TUTORIAL               HM_MSG_BASE+0x0011
#define HM_EXT_HELP_UNDEFINED     HM_MSG_BASE+0x0012
#define HM_GENERAL_HELP_UNDEFINED HM_EXT_HELP_UNDEFINED
#define HM_ACTIONBAR_COMMAND      HM_MSG_BASE+0x0013
#define HM_INFORM                 HM_MSG_BASE+0x0014
#define HM_NOTIFY                 HM_MSG_BASE+0x0022
#define HM_SET_USERDATA           HM_MSG_BASE+0x0023
#define HM_CONTROL                HM_MSG_BASE+0x0024

#define HMQW_COVERPAGE      1
#define HMQW_INDEX          2
#define HMQW_TOC            3
#define HMQW_SEARCH         4
#define HMQW_VIEWPAGES      5
#define HMQW_LIBRARY        6
#define HMQW_VIEWPORT       7
#define HMQW_OBJCOM_WINDOW  8
#define HMQW_INSTANCE       9
#define HMQW_ACTIVEVIEWPORT 10
#define CONTROL_SELECTED    11

#define HMQW_GROUP_VIEWPORT 0x00f1
#define HMQW_RES_VIEWPORT   0x00f2
#define USERDATA            0x00f3

#define HMQVP_NUMBER 1
#define HMQVP_NAME   2
#define HMQVP_GROUP  3

#define CTRL_PREVIOUS_ID  1
#define CTRL_SEARCH_ID    2
#define CTRL_PRINT_ID     3
#define CTRL_INDEX_ID     4
#define CTRL_CONTENTS_ID  5
#define CTRL_BACK_ID      6
#define CTRL_FORWARD_ID   7
#define CTRL_TUTORIAL_ID  256
#define CTRL_USER_ID_BASE 257

#define HMERR_NO_FRAME_WND_IN_CHAIN     0x00001001
#define HMERR_INVALID_ASSOC_APP_WND     0x00001002
#define HMERR_INVALID_ASSOC_HELP_INST   0x00001003
#define HMERR_INVALID_DESTROY_HELP_INST 0x00001004
#define HMERR_NO_HELP_INST_IN_CHAIN     0x00001005
#define HMERR_INVALID_HELP_INSTANCE_HDL 0x00001006
#define HMERR_INVALID_QUERY_APP_WND     0x00001007
#define HMERR_HELP_INST_CALLED_INVALID  0x00001008
#define HMERR_HELPTABLE_UNDEFINE        0x00001009
#define HMERR_HELP_INSTANCE_UNDEFINE    0x0000100a
#define HMERR_HELPITEM_NOT_FOUND        0x0000100b
#define HMERR_INVALID_HELPSUBITEM_SIZE  0x0000100c
#define HMERR_HELPSUBITEM_NOT_FOUND     0x0000100d
#define HMERR_INDEX_NOT_FOUND           0x00002001
#define HMERR_CONTENT_NOT_FOUND         0x00002002
#define HMERR_OPEN_LIB_FILE             0x00002003
#define HMERR_READ_LIB_FILE             0x00002004
#define HMERR_CLOSE_LIB_FILE            0x00002005
#define HMERR_INVALID_LIB_FILE          0x00002006
#define HMERR_NO_MEMORY                 0x00002007
#define HMERR_ALLOCATE_SEGMENT          0x00002008
#define HMERR_FREE_MEMORY               0x00002009
#define HMERR_PANEL_NOT_FOUND           0x00002010
#define HMERR_DATABASE_NOT_OPEN         0x00002011
#define HMERR_LOAD_DLL                  0x00002013

typedef USHORT HELPSUBTABLE, *PHELPSUBTABLE;

#pragma pack(2)

typedef struct _HELPTABLE {
    USHORT        idAppWindow;
    PHELPSUBTABLE phstHelpSubTable;
    USHORT        idExtPanel;
} HELPTABLE, *PHELPTABLE;

typedef struct _HELPINIT {
    ULONG      cb;
    ULONG      ulReturnCode;
    PSZ        pszTutorialName;
    PHELPTABLE phtHelpTable;
    HMODULE    hmodHelpTableModule;
    HMODULE    hmodAccelActionBarModule;
    ULONG      idAccelTable;
    ULONG      idActionBar;
    PSZ        pszHelpWindowTitle;
    ULONG      fShowPanelId;
    PSZ        pszHelpLibraryName;
} HELPINIT, *PHELPINIT;

#pragma pack()

typedef struct _ACVP {
    ULONG cb;
    HAB   hAB;
    HMQ   hmq;
    ULONG ObjectID;
    HWND  hWndParent;
    HWND  hWndOwner;
    HWND  hWndACVP;
} ACVP, *PACVP;

BOOL APIENTRY WinAssociateHelpInstance(HWND,HWND);
HWND APIENTRY WinCreateHelpInstance(HAB,PHELPINIT);
BOOL APIENTRY WinCreateHelpTable(HWND,PHELPTABLE);
BOOL APIENTRY WinDestroyHelpInstance(HWND);
BOOL APIENTRY WinLoadHelpTable(HWND,ULONG,HMODULE);
HWND APIENTRY WinQueryHelpInstance(HWND);

#endif
