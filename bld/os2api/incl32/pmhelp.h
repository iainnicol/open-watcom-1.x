/*
    OS/2 Presentation Manager Help Manager include file
    for 32-bit development.
*/


#ifndef __PMHELP_H__

#define HM_RESOURCEID 0
#define HM_PANELNAME  1

#define HMPANELTYPE_NUMBER 0
#define HMPANELTYPE_NAME   1

#define CMIC_HIDE_PANEL_ID   0
#define CMIC_SHOW_PANEL_ID   1
#define CMIC_TOGGLE_PANEL_ID 2

#define HM_MSG_BASE               0x0220

#define HM_DISMISS_WINDOW             0x0220
#define HM_DISPLAY_HELP               0x0222
#define HM_EXT_HELP                   0x0223
#define HM_GENERAL_HELP               HM_EXT_HELP
#define HM_SET_ACTIVE_WINDOW          0x0224
#define HM_LOAD_HELP_TABLE            0x0225
#define HM_CREATE_HELP_TABLE          0x0226
#define HM_SET_HELP_WINDOW_TITLE      0x0227
#define HM_SET_SHOW_PANEL_ID          0x0228
#define HM_REPLACE_HELP_FOR_HELP      0x0229
#define HM_REPLACE_USING_HELP         HM_REPLACE_HELP_FOR_HELP
#define HM_HELP_INDEX                 0x022a
#define HM_HELP_CONTENTS              0x022b
#define HM_KEYS_HELP                  0x022c
#define HM_SET_HELP_LIBRARY_NAME      0x022d
#define HM_SET_OBJCOM_WINDOW          0x0238
#define HM_UPDATE_OBJCOM_WINDOW_CHAIN 0x0239
#define HM_QUERY_DDF_DATA             0x023a
#define HM_INVALIDATE_DDF_DATA        0x023b
#define HM_QUERY                      0x023c
#define HM_SET_COVERPAGE_SIZE         0x023d

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

#define  HMERR_NO_FRAME_WND_IN_CHAIN     0x00001001
#define  HMERR_INVALID_ASSOC_APP_WND     0x00001002
#define  HMERR_INVALID_ASSOC_HELP_INST   0x00001003
#define  HMERR_INVALID_DESTROY_HELP_INST 0x00001004
#define  HMERR_NO_HELP_INST_IN_CHAIN     0x00001005
#define  HMERR_INVALID_HELP_INSTANCE_HDL 0x00001006
#define  HMERR_INVALID_QUERY_APP_WND     0x00001007
#define  HMERR_HELP_INST_CALLED_INVALID  0x00001008
#define  HMERR_HELPTABLE_UNDEFINE        0x00001009
#define  HMERR_HELP_INSTANCE_UNDEFINE    0x0000100a
#define  HMERR_HELPITEM_NOT_FOUND        0x0000100b
#define  HMERR_INVALID_HELPSUBITEM_SIZE  0x0000100c
#define  HMERR_HELPSUBITEM_NOT_FOUND     0x0000100d
#define  HMERR_INDEX_NOT_FOUND           0x00002001
#define  HMERR_CONTENT_NOT_FOUND         0x00002002
#define  HMERR_OPEN_LIB_FILE             0x00002003
#define  HMERR_READ_LIB_FILE             0x00002004
#define  HMERR_CLOSE_LIB_FILE            0x00002005
#define  HMERR_INVALID_LIB_FILE          0x00002006
#define  HMERR_NO_MEMORY                 0x00002007
#define  HMERR_ALLOCATE_SEGMENT          0x00002008
#define  HMERR_FREE_MEMORY               0x00002009
#define  HMERR_PANEL_NOT_FOUND           0x00002010
#define  HMERR_DATABASE_NOT_OPEN         0x00002011
#define  HMERR_LOAD_DLL                  0x00002013

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

BOOL   APIENTRY WinAssociateHelpInstance(HWND hwndHelpInstance, HWND hwndApp);
HWND   APIENTRY WinCreateHelpInstance(HAB hab, PHELPINIT phinitHMInitStructure);
BOOL   APIENTRY WinCreateHelpTable(HWND hwndHelpInstance, PHELPTABLE phtHelpTable);
BOOL   APIENTRY WinDestroyHelpInstance(HWND hwndHelpInstance);

#endif
