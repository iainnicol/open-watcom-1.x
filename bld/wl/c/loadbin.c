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
* Description:  LOADBIN : routines for creating BIN load files.
*
****************************************************************************/

#include <string.h>
#include "linkstd.h"
#include "alloc.h"
#include "msg.h"
#include "reloc.h"
#include "wlnkmsg.h"
#include "proc386.h"
#include "virtmem.h"
#include "objcalc.h"
#include "dbgall.h"
#include "fileio.h"
#include "loadfile.h"

extern void FiniBinLoadFile( void )
/*************************************/
{
    group_entry         *group;
    outfilelist *       fnode;
    bool                repos;

    DEBUG(( DBG_BASE, "Writing data" ));
    OrderGroups( CompareOffsets );
    CurrSect = Root;        // needed for WriteInfo.
    fnode = Root->outfile;
    fnode->file_loc = 0;
    Root->u.file_loc = 0;
    Root->sect_addr = Groups->grp_addr;
    group = Groups;
    while( group != NULL ) {
        repos = WriteDOSGroup( group );
        group = group->next_group;
        if( repos ) {
            SeekLoad( fnode->file_loc );
        }
    }
}
