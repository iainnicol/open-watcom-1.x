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


/*
*   COMMENTS: Functions contolling the abstract type "a_dialog_header"
*             The only reference to the FirstDialog is through these
*             functions.
*/

#include <string.h>
#include <stdlib.h>
#include <io.h>
#include <fcntl.h>
#include <stdarg.h>
#include <stdio.h>
#include "gui.h"
#include "guiutil.h"
#include "setupinf.h"
#include "guistr.h"
#include "guidlg.h"
#include "dlgbutn.h"
#include "genvbl.h"
#include "setup.h"
#include "utils.h"
#include "gendlg.h"
#include "dlggen.h"


static a_dialog_header *FirstDialog = NULL;
static a_dialog_header *LastDialog = NULL;
extern int             SkipDialogs;

extern a_dialog_header *FindDialogByName( char *dlg_name )
/********************************************************/
{
    a_dialog_header *d;

    for( d = FirstDialog; d != NULL; d = d->next ){
        if( stricmp( d->name, dlg_name ) == 0 ) {
            break;
        }
    }
    return( d );
}

static void FreeDialog( a_dialog_header *tmp_dialog)
/**************************************************/
{
    int i;

    GUIFree( tmp_dialog->name );

    if( !tmp_dialog->def_dlg ) {            /* free non-default controls */
        for( i=0; i < tmp_dialog->num_controls; i++ ){
            GUIFree(tmp_dialog->controls[i].text);
            if( tmp_dialog->pConditions[i] != NULL ) {
                GUIFree(tmp_dialog->pConditions[i]);
            }
            if( tmp_dialog->pVisibilityConds[i] != NULL ) {
                GUIFree(tmp_dialog->pVisibilityConds[i]);
            }
        }
        GUIFree( tmp_dialog->controls );
    }
                                                 /* free variables */
    GUIFree( tmp_dialog );

}

extern a_dialog_header *AddNewDialog( char *dlg_name )
/****************************************************/
// Add new dialogs to front of linked list.
// Delete default dialogs if specified.
{
    a_dialog_header *tmp_dialog;
    a_dialog_header *new_dialog;

    new_dialog = (a_dialog_header *)GUIAlloc( sizeof( a_dialog_header ) );
    memset( new_dialog, '\0', sizeof( *new_dialog ) );
    new_dialog->controls = GUIAlloc( sizeof(gui_control_info) );
    GUIStrDup( dlg_name, &new_dialog->name );
    new_dialog->adjusted = FALSE;
    new_dialog->def_dlg     = FALSE;
    new_dialog->ret_val = DLG_NEXT;
    new_dialog->any_check = NO_VAR;

    /* check if old dialog existed */
    tmp_dialog = FindDialogByName( dlg_name );
    if( tmp_dialog != NULL ) {
        new_dialog->next = tmp_dialog->next;
        new_dialog->prev = tmp_dialog->prev;
        if( new_dialog->next != NULL ) {
            new_dialog->next->prev = new_dialog;
        }
        if( new_dialog->prev != NULL ) {
            new_dialog->prev->next = new_dialog;
        }
        if( FirstDialog == NULL ) {
            FirstDialog = new_dialog;
            LastDialog = new_dialog;
        }
        if( FirstDialog == tmp_dialog ) {
            FirstDialog = new_dialog;
        }
        if( LastDialog == tmp_dialog ) {
            LastDialog = new_dialog;
        }
        FreeDialog( tmp_dialog );        // replace old default dialog
    } else {
        new_dialog->prev = LastDialog;
        new_dialog->next = NULL;
        if( FirstDialog == NULL ) {
            FirstDialog = new_dialog;
            LastDialog = new_dialog;
        } else {
            LastDialog->next = new_dialog;
        }
        LastDialog = new_dialog;
    }

    return( new_dialog );
}

bool CheckDialog( char *name )
/****************************/
{
    a_dialog_header     *dlg;

    dlg = FindDialogByName( name );
    if( dlg == NULL ) {
        return( FALSE );
    }
    if( dlg->condition == NULL ) return( TRUE );
    return( EvalCondition( dlg->condition ) );
}

dlg_state DoDialogByPointer( gui_window *parent, a_dialog_header *dlg )
/*********************************************************************/
{
    if( dlg->condition != NULL && !EvalCondition( dlg->condition ) ) {
        return( dlg->ret_val );
    }
    return( GenericDialog( parent, dlg ) );
}

dlg_state DoDialogWithParent( void *parent, char *name )
/************************************************************/
{
    a_dialog_header     *dlg;
    dlg_state           return_state;
    #if defined( WSQL ) && ( defined ( WINNT ) || defined( WIN ) ) // Microsoft BackOffice
        int                     i;
        int                     var_handle;
    #endif

    dlg = FindDialogByName( name );
    if( dlg == NULL ) {
        return( DLG_CAN );
    }
    return_state = DoDialogByPointer( parent, dlg );
    #if defined( WSQL ) && ( defined ( WINNT ) || defined( WIN ) ) // Microsoft BackOffice
        // Put variables set in dialogs into the install script file
        // for MSBackOffice packages (with the noted exceptions below)
        if( GetVariableIntVal( "MakePackage" ) == 1 ) {
            for( i = 0; dlg->pVariables[ i ] != NO_VAR; i++ ) {
                var_handle = dlg->pVariables[ i ];
                // Exceptions: The values the following variables get in dialogs
                // do not apply to the package being created, so they are not tagged:
                if( stricmp( VarGetName( var_handle ), "Install" ) == 0
                    || stricmp( VarGetName( var_handle ), "UnInstall" ) == 0
                    || stricmp( VarGetName( var_handle ), "MakeDisks" ) == 0
                    || stricmp( VarGetName( var_handle ), "MakePackage" )  == 0
                    || stricmp( VarGetName( var_handle ), "PackageDir" ) == 0
                    || stricmp( VarGetName( var_handle ), "ApplyLicense" ) == 0 ) {
                    continue;
                }
                SetVariableNeedsToBeInScriptFile( dlg->pVariables[ i ] );
            }
        }
    #endif
    if( return_state == DLG_CAN ) {
        // This block is a kludgy hack which allows a dialog to
        // return DLG_DONE when the ESC key is pressed, if it has a
        // DONE button rather than a CANCEL button.
        int                             i;
        bool                            can = FALSE;
        bool                            done = FALSE;

        for( i = 0; i < dlg->num_controls; i++ ) {
            if( dlg->controls[ i ].id == CTL_CANCEL ) {
                can = TRUE;
                break;
            }
            if( dlg->controls[ i ].id == CTL_DONE ) {
                done = TRUE;
            }
        }
        if( can == FALSE && done == TRUE ) return_state = DLG_DONE;
    }

    return( return_state );
}

dlg_state DoDialog( char *name )
/******************************/
{
    dlg_state result;

    if( SkipDialogs ) {
        result = DLG_NEXT;
    } else {
        result = DoDialogWithParent( NULL, name );
    }

    return result;
}

extern void FreeDefaultDialogs( void )
/************************************/
{
    a_dialog_header *d;
    a_dialog_header *next;

    for( d = FirstDialog; d != NULL; d=next ) {
        next = d->next;
        FreeDialog( d );
    }
    FirstDialog = NULL;
    LastDialog = NULL;
}
