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
* Description:  Routines to keep track of loaded modules and address maps.
*
****************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "trpimp.h"
#include "mad.h"
#include "exeelf.h"
#include "linuxcomm.h"

typedef struct lli {
    addr48_off  offset;
    addr48_off  dbg_dyn_sect;
    addr48_off  code_size;
    char        newly_unloaded : 1;
    char        newly_loaded : 1;
    char        filename[257]; // TODO: These should really be dynamic!
    char        modname[128];
} lib_load_info;

static lib_load_info    *moduleInfo;
static int              ModuleTop;

/* At this point, due to the way the Linux trap file is built, we don't have
 * any dynamic memory management routines available. So we just define a big
 * fat static array. This should be redone once the trap file becomes a real
 * shared library.
 */
#define NO_DYN_MEM
#ifdef NO_DYN_MEM
static lib_load_info    module_info_array[32];
#endif

/*
 * FindLib - find a shared lib entry in the list
 */
lib_load_info *FindLib( addr48_off dynsection )
{
    unsigned    i;
    
    for( i = 0; i < ModuleTop; ++i ) {
        if( moduleInfo[i].dbg_dyn_sect == dynsection )
            return( &moduleInfo[i] );
    }
    return( NULL );
}

/*
 * AddProcess - a new process has been created
 */
void AddProcess( void )
{
    lib_load_info       *lli;

#ifdef NO_DYN_MEM
    moduleInfo = &module_info_array[0];
#else    
    moduleInfo = malloc( sizeof( lib_load_info ) );
#endif    
    memset( moduleInfo, 0, sizeof( lib_load_info ) );
    ModuleTop = 1;

    lli = &moduleInfo[0];

    lli->offset = 0;    /* Assume that main executable was not relocated */
    lli->modname[0] = '\0';
    lli->filename[0] = '\0';
}

/*
 * AddLib - a new library has loaded
 */
void AddLib( struct link_map *lmap )
{
    lib_load_info       *lli;

    ModuleTop++;
#ifdef NO_DYN_MEM
    lli = &module_info_array[0];
#else
    /* This code is not terribly efficient */
    lli = malloc( ModuleTop * sizeof( lib_load_info ) );
    memset( lli, 0, ModuleTop * sizeof( lib_load_info ) );
    memcpy( lli, moduleInfo, ( ModuleTop - 1 ) *sizeof( lib_load_info ) );
    free( moduleInfo );
#endif
    moduleInfo = lli;
    lli = &moduleInfo[ModuleTop - 1];

    lli->offset = lmap->l_addr;
    lli->dbg_dyn_sect = (addr48_off)lmap->l_ld;
    lli->modname[0] = 0;
    dbg_strcpy( lli->filename, lmap->l_name );
    lli->newly_loaded = TRUE;
    lli->newly_unloaded = FALSE;
    lli->offset = lmap->l_addr;
    
    Out( "Added library: ofs/dyn = " );
    OutNum( lmap->l_addr );
    Out( "/" );
    OutNum( (addr48_off)lmap->l_ld );
    Out( " " );
    Out( lli->filename );
    Out( "\n" );
}

void DelLib( addr48_off dynsection )
{
    unsigned    i;

    for( i = 0; i < ModuleTop; ++i ) {
        if( moduleInfo[i].dbg_dyn_sect == dynsection ) {
            moduleInfo[i].newly_unloaded = TRUE;
            moduleInfo[i].offset = NULL;
	    moduleInfo[i].dbg_dyn_sect = NULL;
            moduleInfo[i].code_size = 0;
            break;
        }
    }
}

void DelProcess( void )
{
    unsigned    i;

    for( i = 0; i < ModuleTop; ++i ) {
        moduleInfo[i].offset = NULL;
        moduleInfo[i].dbg_dyn_sect = NULL;
        moduleInfo[i].code_size = 0;
    }
}


/*
 * AddInitialLibs - called the first time we can get information
 * about loaded shared libs.
 */
int AddInitialLibs( struct link_map *first_lmap )
{
    struct link_map     lmap;
    struct link_map     *dbg_lmap;
    int                 count = 0;

    dbg_lmap = first_lmap;
    while( dbg_lmap != NULL ) {
        if( !GetLinkMap( dbg_lmap, &lmap ) ) break;
	AddLib( &lmap );
	++count;
        dbg_lmap = lmap.l_next;
    }
    return( count );
}

/*
 * AccMapAddr - map address in image from link-time virtual address to
 * actual linear address as loaded in memory. For executables, this will
 * in effect return the address unchanged (image base 0x08048100 equals
 * linear 0x08048100), for shared libs this will typically add the offset
 * from zero (link time VA) to actual load base.
 */
unsigned ReqMap_addr( void )
{
    map_addr_req    *acc;
    map_addr_ret    *ret;
    unsigned long   val;
    lib_load_info   *lli;
    
    // Note: Info about the process address space is stored in the user register
    //       for GDB, so we can use that to find out what we need to convert these
    //       values in here...
    acc = GetInPtr( 0 );
    ret = GetOutPtr( 0 );
    ret->lo_bound = 0;
    ret->hi_bound = ~(addr48_off)0;
    sys_ptrace( PTRACE_PEEKUSER, pid, offsetof( user_struct, start_code ), &val );
    ret->out_addr.offset = acc->in_addr.offset + val;

    // TODO: sometimes we're called with weird handle - why?
    if( acc->handle > ModuleTop )
        lli = &moduleInfo[0];
    else
        lli = &moduleInfo[acc->handle];

    Out( "ReqMap_addr: addr " );
    OutNum( acc->in_addr.segment );
    Out( ":" );
    OutNum( acc->in_addr.offset );
    Out( " in module " );
    OutNum( acc->handle );
    if( acc->in_addr.segment == MAP_FLAT_DATA_SELECTOR ||
        acc->in_addr.segment == flatDS ) {
        sys_ptrace( PTRACE_PEEKUSER, pid, offsetof( user_struct, u_tsize ), &val );
        ret->out_addr.offset += val;
        ret->out_addr.segment = flatDS;
    } else {
        ret->out_addr.segment = flatCS;
    }
    ret->out_addr.offset += lli->offset;
    Out( " to " );
    OutNum( ret->out_addr.offset );
    Out( "\n" );
    return( sizeof( *ret ) );
}

/*
 * AccGetLibName - get lib name of current module
 */
unsigned ReqGet_lib_name( void )
{
    get_lib_name_req    *acc;
    get_lib_name_ret    *ret;
    char                *name;
    unsigned            i;

    acc = GetInPtr( 0 );
    ret = GetOutPtr( 0 );
    name = GetOutPtr( sizeof( *ret ) );

    ret->handle = 0;
    name[0] = '\0';

    for( i = 0; i < ModuleTop; ++i ) {
        if( moduleInfo[i].newly_unloaded ) {
            ret->handle = i;
            name[0] = '\0';
            moduleInfo[i].newly_unloaded = FALSE;
            return( sizeof( *ret ) );
        } else if( moduleInfo[i].newly_loaded ) {
            ret->handle = i;
            strcpy( name, moduleInfo[i].filename );
            moduleInfo[i].newly_loaded = FALSE;
            return( sizeof( *ret ) + strlen( name ) + 1 );
        }
    }
    Out( "ReqGet_lib_name: in handle " );
    OutNum( acc->handle );
    Out( " out handle " );
    OutNum( ret->handle );
    Out( "\n" );
    return( sizeof( *ret ) );
}
