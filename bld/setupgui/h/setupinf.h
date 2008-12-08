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
* Description:  Interface to the setupinf module.
*
****************************************************************************/


#include <time.h>
#include <stdarg.h>
#include "vhandle.h"

// Possible timing for Spawn execution
typedef enum {
    WHEN_BEFORE,
    WHEN_AFTER,
    WHEN_END
} when_time;

typedef enum {
    DOING_DEFAULTS,
    PRESCAN_FILE,
    FINAL_SCAN,
} pass_type;

extern void CheckStateVars();
extern char *SimGetDriveLetter( int parm );
extern bool SimFileAdd( int parm );
extern bool SimFileUpToDate( int parm );
extern bool SimFileRemove( int parm );
extern int SimNumSubFiles( int parm );
extern int SimPermanentFile( int parm );
extern int SimSubFileExists( int parm, int subfile );
extern void SimSubFileName( int parm, int subfile, char *buff );
extern bool SimSubFileInNewDir( int parm, int subfile );
extern bool SimSubFileInOldDir( int parm, int subfile );
extern time_t SimSubFileDate( int parm, int subfile );
extern bool SimSubFileNewer( int parm, int subfile );
extern bool SimSubFileReadOnly( int parm, int subfile );
extern long SimSubFileSize( int parm, int subfile );
extern bool SimFileSplit( int parm );
extern bool SimFileLastSplit( int parm );
extern void SaveState(void);
extern long SimInit( char *buff );
extern void SimSetTargTempDisk( int parm, char disk );
extern char *SimGetTargTempDisk( int parm );
extern int SimGetTargNumFiles( int parm );
extern int SimNumTargets(void);
extern long SimTargetSpaceNeeded(int parm);
extern void SimTargetDir( int i, char *buffer );
extern void SimTargetDirName( int i, char *buffer );
extern long SimMaxTmpFile( int i );
extern int SimNumDirs(void);
extern void SimDirNoSlash(int parm,char *buff);
extern unsigned char SimDirUsed(int parm);
extern int SimDirTargNum(int parm);
extern int SimDirParent(int parm);
extern void SimGetDir(int parm,char *buff);
extern int SimNumFiles(void);
extern void SimGetFileDesc(int parm,char *buff);
extern void SimGetFileName(int parm,char *buff);
extern long SimFileSize(int parm);
extern int SimFileDisk(int parm,char *buff);
extern int SimFileDiskNum( int parm );
extern bool SimFileOldDir( int parm, char *buff );
extern void SimFileDir(int parm,char *buff);
extern int SimFileDirNum( int parm );
extern bool SimCheckFileCondition(int parm);
extern bool SimCheckFileInitialCondition(int parm);
extern void SimGetPMGroupFileName(char *buff);
extern void SimGetPMGroupIcon(char *buff);
extern void SimGetPMGroup(char *buff);
extern int SimGetNumPMProgs(void);
extern int SimGetPMProgName(int parm,char *buff);
extern void SimGetPMParms(int parm,char *buff);
extern void SimGetPMDesc(int parm,char *buff);
extern long SimGetPMIconInfo(int parm,char *buff);
extern unsigned char SimCheckPMCondition(int parm);
extern void SimGetPMGroupName( int parm, char *buff );
extern void SimGetPMGroupFName( int parm, char *buff );
extern int SimGetNumPMGroups();
extern int SimNumProfile(void);
extern void SimProfInfo(int parm,char *app_name,char *key_name,char *value,char *file_name,char *hive_name);
extern unsigned char SimCheckProfCondition(int parm);
extern int SimNumAutoExec(void);
extern unsigned char SimGetAutoExecStrings(int parm,char *new_var, char *new_val);
extern unsigned char SimCheckAutoExecCondition(int parm);
extern int SimNumConfig(void);
extern unsigned char SimGetConfigStrings(int parm,char *new_var, char *new_val);
extern unsigned char SimCheckConfigCondition(int parm);
extern int SimNumEnvironment(void);
extern bool SimCheckEnvironmentCondition( int parm );
extern unsigned char SimGetEnvironmentStrings(int parm,char *new_var, char *new_val);
extern void SimGetEnvironmentVal(int parm,char *buff);
extern int SimNumAssociations( void );
extern void SimGetAssociationExt( int parm, char *buff );
extern void SimGetAssociationKeyName( int parm, char *buff );
extern void SimGetAssociationProgram( int parm, char *buff );
extern void SimGetAssociationDescription( int parm, char *buff );
extern int SimGetAssociationIconIndex( int parm );
extern int SimGetAssociationNoOpen( int parm );
extern int SimNumLabels(void);
extern void SimGetLabelDir(int parm,char *buff);
extern void SimGetLabelLabel(int parm,char *buff);
extern bool SimCalcTargetSpaceNeeded(void);
extern void CheckDLLCount( char * );
extern void SimCalcAddRemove(void);
extern void SimSetNeedGetDiskSizes();
extern unsigned char PatchFiles(void );
extern void MsgPut(int resourceid,va_list arglist);
extern void PatchError(int format,... );
extern void FilePatchError(int format,... );
extern void FreeAllStructs(void );
extern int EvalCondition(char *str);
extern  bool SimTargetNeedsUpdate( int parm );
extern vhandle SimSubFileVar( int parm, int subfile );
extern int SimNumSpawns();
extern void SimGetSpawnCommand( char *, int i );
extern when_time SimWhen( int i );
extern bool SimEvalSpawnCondition( int i );
extern int SimGetNumDisks();
extern int SimNumDeletes();
extern char *SimDeleteName( int );
extern bool SimDeleteIsDialog( int );
extern bool SimDeleteIsDir( int );
extern int SimNumUpgrades();
extern char *SimGetUpgradeName( int );
extern char *MakeDummyVar( char *buff );

// Possible return values from sending the SIM_INITIALIZE message.
typedef enum {
    SIM_INIT_NOERROR,
    SIM_INIT_NOMEM,
    SIM_INIT_NOFILE,
} SIM_INITIALIZE_ERROR;

// Fixes bug in 32-bit comparisons... I hate it when
// people mix return codes and out params...
#define SIM_INIT_ERROR          ((unsigned short)(-1))


int                     EvalCondition( char *str );


// Defines used by the SETUP program.
#define MAXBUF          128
#define MAXVALUE        256
#define MAXENVVAR       2048


typedef enum{
    NULL_TYPE,
    STRING_TYPE
} VBL_TYPE;

typedef enum {
    DLG_CAN,
    DLG_NEXT,
    DLG_PREV,
    DLG_START,
    DLG_SAME,
    DLG_SKIP,
    DLG_DONE,
} dlg_state;

#define MAX_VARS 75
typedef struct a_dialog_header {
    char                        *name;              /* name of dlg */
    char                        *condition;
    int                         rows;
    int                         cols;
    int                         num_push_buttons;
    int                         num_controls;
    bool                        def_dlg;
    bool                        defaults_set;
    bool                        adjusted;
    gui_control_info            *controls;          /* controls associated with dlg */
    vhandle                     pVariables[MAX_VARS];     /* pointer to variables */
    char                        *pConditions[MAX_VARS];   /* pointer to initial value */
    char                        *pVisibilityConds[MAX_VARS]; /* conditions for visibility of controls (dynamic) */
    gui_rect                    original_rect; /* original window position (used in UpdateControlVisibility() )*/
    gui_ord                     height_change; /* how much dialog height has changed (used in UpdateControlVisibiliy() ) */
    struct a_dialog_header      *next;              /* next dialog box */
    struct a_dialog_header      *prev;              /* prev dialog box */
    dlg_state                   ret_val;
    char                        *title;
    vhandle                     any_check;
} a_dialog_header;

#define HEIGHT_BORDER  1
#define WIDTH_BORDER   4

#define DUMMY_VAR_SIZE 25