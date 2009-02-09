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
* Description:  ZDOS specific debug core.
*
****************************************************************************/

#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <zbios.h>
#include <zdos.h>
#include <ztrace.h>
#include "trpimp.h"
#include "madx86.h"
#include "madregs.h"
#include "dbg386.h"
#include "trperr.h"
#include "ioports.h"

#define MAX_WP 32

typedef struct
{
   unsigned int   linear;
   unsigned int   value;
   unsigned short len;
   short          dregs;
} watch;

watch    WatchPoints[ MAX_WP ];
int      WatchCount, Exception;
TCPU     Context;
TDEBUG   Debug;
int      ProcessPID, ProcessTID, CurrentTID;

unsigned int GetLinearAddress( unsigned int offset, unsigned int segment )
{
   if( Context.EFLAGS & 0x20000 )   /* V86 task ? */
      return( ( segment << 4 ) + offset );
   return( offset );
}

unsigned ReqGet_sys_config( void )
{
   get_sys_config_ret   *ret;
   int                  version;
   CPU                  cpu;

   version = DosGetVersion( );
   BiosCpuInformation( &cpu );

   ret = GetOutPtr( 0 );
   ret->sys.mad = MAD_X86;
   ret->sys.os  = OS_ZDOS;
   ret->sys.osmajor = version >> 8;
   ret->sys.osminor = version & 0xff;
   ret->sys.fpu = ret->sys.cpu = cpu.Family;
   ret->sys.huge_shift = 3;
   return( sizeof( *ret ) );
}

unsigned ReqMap_addr( void )     /* obsolete */
{
   map_addr_req   *acc;
   map_addr_ret   *ret;

   acc = GetInPtr(0);
   ret = GetOutPtr(0);
   if( acc->in_addr.segment == MAP_FLAT_DATA_SELECTOR )
      ret->out_addr.segment = Context.DS;
   else
      ret->out_addr.segment = Context.CS;
   ret->out_addr.offset = acc->in_addr.offset;
   ret->lo_bound = 0;
   ret->hi_bound = ~( addr48_off ) 0;
   return( sizeof( *ret ) );
}

unsigned ReqAddr_info( void )
{
   addr_info_ret *ret = GetOutPtr( 0 );
   if( Context.EFLAGS & 0x20000 )   /* V86 task ? */
      ret->is_32 = 0;
   else
      ret->is_32 = 1;
   return( sizeof( *ret ) );
}

unsigned ReqChecksum_mem( void )
{
   checksum_mem_req  *acc;
   checksum_mem_ret  *ret;
   char              buffer[512];
   addr_off          offset;
   int               length, size, i;
   unsigned long     sum;

   acc = GetInPtr( 0 );
   ret = GetOutPtr( 0 );
   sum = 0;
   length = acc->len;
   offset = acc->in_addr.offset;
   while( length )
   {
      size = ( length > sizeof( buffer ) ) ? sizeof( buffer ) : length;
      if( DosTraceCopyFromClient( size, ( unsigned ) offset, buffer ) )
         break;
      for( i = 0; i < size; i++ )
         sum += buffer[i];
      offset += size;
      length -= size;
   }
   ret->result = sum;
   return( sizeof( *ret ) );
}

unsigned ReqRead_mem( void )
{
   read_mem_req   *acc;

   acc = GetInPtr( 0 );
   if( DosTraceCopyFromClient( acc->len, ( unsigned ) acc->mem_addr.offset,
                               GetOutPtr( 0 ) ) )
      return( 0 );
   return( acc->len );
}

unsigned ReqWrite_mem( void )
{
   write_mem_req  *acc;
   write_mem_ret  *ret;
   int            len;

   acc = GetInPtr( 0 );
   ret = GetOutPtr( 0 );
   len = GetTotalSize( ) - sizeof( *acc );
   if( DosTraceCopyToClient( len, GetInPtr( sizeof( *acc ) ),
       ( unsigned ) acc->mem_addr.offset ) )
      ret->len = 0;
   ret->len = len;
   return( sizeof( *ret ) );
}

unsigned ReqRead_io( void )
{
   read_io_req *acc;
   void        *data;

   acc = GetInPtr( 0 );
   data = GetOutPtr( 0 );
   switch( acc->len )
   {
      case 1:
         *( ( unsigned char * ) data ) = In_b( acc->IO_offset );
         return 1;
      case 2:
         *( ( unsigned short * ) data ) = In_w( acc->IO_offset );
         return 2;
      case 4:
         *( ( unsigned int * ) data ) = In_d( acc->IO_offset );
         return 4;
      default:
         return 0;
   }
}

unsigned ReqWrite_io( void )
{
   write_io_req   *acc;
   write_io_ret   *ret;
   void           *data;
   unsigned       len;

   acc = GetInPtr( 0 );
   data = GetInPtr( sizeof( *acc ) );
   len = GetTotalSize( ) - sizeof( *acc );
   ret = GetOutPtr( 0) ;
   switch( len )
   {
      case 1:
         Out_b( acc->IO_offset, *( ( unsigned char * ) data ) );
         return 1;
      case 2:
         Out_w( acc->IO_offset, *( ( unsigned short * ) data ) );
         return 2;
      case 4:
         Out_d( acc->IO_offset, *( ( unsigned int * ) data ) );
         return 4;
      default:
         return 0;
   }
}

unsigned ReqRead_cpu( void )     /* obsolete */
{
   struct x86_cpu *data;

   data = GetOutPtr( 0 );
   data->eax = Context.EAX;
   data->ebx = Context.EBX;
   data->ecx = Context.ECX;
   data->edx = Context.EDX;
   data->esi = Context.ESI;
   data->edi = Context.EDI;
   data->ebp = Context.EBP;
   data->esp = Context.ESP;
   data->eip = Context.EIP;
   data->efl = Context.EFLAGS;
   data->cr0 = data->cr2 = data->cr3 = 0;
   data->ds  = Context.DS;
   data->es  = Context.ES;
   data->ss  = Context.SS;
   data->cs  = Context.CS;
   data->fs  = Context.FS;
   data->gs  = Context.GS;
   return( sizeof( struct x86_cpu ) );
}

unsigned ReqRead_fpu( void )     /* obsolete */
{
   struct x86_fpu *data = GetOutPtr( 0 );
   if( DosTraceGetFpuContext( ( TFPU * ) data ) )
      memset( data, 0, sizeof( TFPU ) );
   return( sizeof( struct x86_fpu ) );
}

unsigned ReqWrite_cpu( void )    /* obsolete */
{
   struct x86_cpu *data = GetInPtr( sizeof( write_cpu_req ) );

   Context.EDI    = data->edi;
   Context.ESI    = data->esi;
   Context.EBP    = data->ebp;
   Context.EBX    = data->ebx;
   Context.EDX    = data->edx;
   Context.ECX    = data->ecx;
   Context.EAX    = data->eax;
   Context.EIP    = data->eip;
   Context.CS     = data->cs;
   Context.EFLAGS = data->efl;
   Context.ESP    = data->esp;
   Context.SS     = data->ss;
   Context.ES     = data->es;
   Context.DS     = data->ds;
   Context.FS     = data->fs;
   Context.GS     = data->gs;
   DosTraceSetCpuContext( &Context );
   return( 0 );
}

unsigned ReqWrite_fpu( void )    /* obsolete */
{
   struct x86_cpu *data = GetInPtr( sizeof( write_fpu_req ) );

   DosTraceSetFpuContext( ( TFPU * ) data );
   return( 0 );
}

unsigned SetDRn( int i, unsigned linear, int type )
{
   switch( i )
   {
      case 0:
         Debug.DR0 = linear;
        break;
      case 1:
         Debug.DR1 = linear;
        break;
      case 2:
         Debug.DR2 = linear;
         break;
      case 3:
         Debug.DR3 = linear;
         break;
   }
   return( ( type << DR7_RWLSHIFT( i ) ) |
           ( DR7_LEMASK << DR7_GLSHIFT(i) ) | DR7_LE );
}

void ClearDebugRegs( void )
{
   Debug.DR7 = 0;
   DosTraceSetDebugContext( &Debug );
}

int SetDebugRegs( void )
{
   int      i, needed, dr;
   watch    *wp;
   unsigned dr7;

   needed = 0;
   for( i = WatchCount, wp = WatchPoints; i != 0; --i, ++wp )
      needed += wp->dregs;
   if( needed > 4 )
      return( 0 );

   dr = 0;
   dr7 = 0;
   for( i = WatchCount, wp = WatchPoints; i != 0; --i, ++wp )
   {
      dr7 |= SetDRn( dr, wp->linear, DRLen( wp->len ) | DR7_BWR );
      ++dr;
      if( wp->dregs == 2 )
      {
         dr7 |= SetDRn( dr, wp->linear+4, DRLen( wp->len ) | DR7_BWR );
         ++dr;
      }
   }
   Debug.DR7 = dr7;
   DosTraceSetDebugContext( &Debug );
   return( 1 );
}

unsigned DoRun( int step )
{
  int   event;

   if( step )
      CurrentTID = DosTraceSingleStep( &event, &Context );
   else
      CurrentTID = DosTraceRun( &event, &Context );
   switch( event )
   {
      case TRACE_BREAKPOINT0:
      case TRACE_BREAKPOINT1:
      case TRACE_BREAKPOINT2:
      case TRACE_BREAKPOINT3:
         return( COND_WATCH );
      case TRACE_ENTER:
      case TRACE_EXIT:
         return( COND_THREAD );
      case TRACE_DEBUG_TRAP:
         return( COND_TRACE );
      case TRACE_BREAKPOINT_TRAP:
         return( COND_BREAK );
      default:
         Exception = event;
         return COND_EXCEPTION;
   }
}

int CheckWatchPoints( void )
{
   unsigned int   value;
   watch          *wp;

   for( wp = WatchPoints; wp < WatchPoints + WatchCount; ++wp )
   {
      if( DosTraceCopyFromClient( 4, wp->linear, &value ) )
         value = 0;
      if( value != wp->value )
         return( 1 );
   }
   return( 0 );
}

unsigned ProgRun( int step )
{
   prog_go_ret *ret;

   ret = GetOutPtr( 0 );
   if( step )
   {
      ret->conditions = DoRun( 1 );
   }
   else if( WatchCount )
   {
      if( SetDebugRegs( ) )
      {
         ret->conditions = DoRun( 0 );
         ClearDebugRegs( );
      }
      else
      {
         for( ; ; )
         {
            ret->conditions = DoRun( 1 );
            if( ret->conditions & ( COND_TRACE | COND_BREAK ) )
            {
               if( CheckWatchPoints() )
               {
                  ret->conditions |= COND_WATCH;
                  ret->conditions &= ~( COND_TRACE | COND_BREAK );
                  break;
               }
            }
            else
               break;
         }
      }
   }
   else
      ret->conditions = DoRun( 0 );
   ret->conditions |= COND_CONFIG;
   ret->program_counter.offset  = Context.EIP;
   ret->program_counter.segment = Context.CS;
   ret->stack_pointer.offset    = Context.ESP;
   ret->stack_pointer.segment   = Context.SS;
   return( sizeof( *ret ) );
}

unsigned ReqProg_go( void )
{
   return( ProgRun( 0 ) );
}

unsigned ReqProg_step( void )
{
   return( ProgRun( 1 ) );
}

unsigned ReqProg_load( void )
{
   char           *src, *dst, *name, ch, buffer[256];
   prog_load_ret  *ret;
   unsigned       len;
   int            i;

   dst = buffer;
   src = name = GetInPtr( sizeof( prog_load_req ) );
   ret = GetOutPtr( 0 );
   while( *src != '\0' )
      ++src;
   ++src;
   len = GetTotalSize( ) - ( src - name ) - sizeof( prog_load_req );
   for( i = 0; i < len; i++ )
   {
      if( i == 255 )
         break;
      ch = *src;
      if( ch == '\0' )
         ch = ' ';
      buffer[i++] = ch;
      src++;
   }
   buffer[i] = '\0';
   ProcessPID = DosExecuteProcess( PRIORITY_DEFAULT, name, 0,
                                   PROCESS_FORGROUND, PROCESS_TRACE_ON,
                                   buffer );
   if( ProcessPID < 0 )
   {
      ret->err = ProcessPID;
      ret->task_id = 0;
      ProcessPID = 0;
   }
   else
   {
      ret->err = 0;
      ret->task_id = ProcessPID;
      ProcessTID = DosTraceOpenSession( &Context );
      if( ProcessTID < 0 )
         ProcessTID = 0;
   }
   ret->mod_handle = 0;
   return( sizeof( *ret ) );
}

unsigned ReqProg_kill( void )
{
   prog_kill_ret  *ret;

   if( ProcessPID != 0 )
      DosAbortProcess( ProcessPID );
    ret = GetOutPtr( 0 );
    ret->err = 0;
    return( sizeof( *ret ) );
}

unsigned ReqSet_watch( void )
{
   watch          *curr;
   set_watch_req  *acc;
   set_watch_ret  *ret;
   int            i;
   int            needed;

   acc = GetInPtr( 0 );
   ret = GetOutPtr( 0 );
   ret->multiplier = 5000;
   ret->err = 0;
   curr = WatchPoints + WatchCount;
   curr->linear = GetLinearAddress( acc->watch_addr.offset,
                                    acc->watch_addr.segment );
   curr->len = acc->size;
   curr->dregs = ( curr->linear & (curr->len - 1 ) ) ? 2 : 1;
   DosTraceCopyFromClient( curr->len, curr->linear, &curr->value );
   WatchCount++;
   needed = 0;
   for( i = 0; i < WatchCount; i++ )
      needed += WatchPoints[i].dregs;
   if( needed <= 4 )
      ret->multiplier |= USING_DEBUG_REG;
   return( sizeof( *ret ) );
}

unsigned ReqClear_watch( void )
{
   WatchCount = 0;
   return( 0 );
}

unsigned ReqSet_break( void )
{
   set_break_req  *acc;
   set_break_ret  *ret;
   unsigned int   linear;

   acc = GetInPtr( 0 );
   ret = GetOutPtr( 0 );
   linear = GetLinearAddress( acc->break_addr.offset,
                              acc->break_addr.segment );
   DosTraceSetBreakPoints( 1, ( unsigned char * ) &ret->old, &linear );
   return( sizeof( *ret ) );
}

unsigned ReqClear_break( void )
{
   clear_break_req   *acc;
   unsigned int      linear;

   acc = GetInPtr( 0 );
   linear = GetLinearAddress( acc->break_addr.offset,
                              acc->break_addr.segment );
   DosTraceClearBreakPoints( 1, ( unsigned char * ) &acc->old, &linear );
   return( 0 );
}

unsigned ReqGet_next_alias( void )
{
   get_next_alias_ret   *ret;

   ret = GetOutPtr( 0 );
   ret->seg = 0;
   ret->alias = 0;
   return( sizeof( *ret ) );
}

unsigned ReqSet_user_screen( void )
{
   return( 0 );
}

unsigned ReqSet_debug_screen( void )
{
   return( 0 );
}

unsigned ReqRead_user_keyboard( void )
{
   read_user_keyboard_req  *acc;
   read_user_keyboard_ret  *ret;

   acc = GetInPtr( 0 );
   ret = GetOutPtr( 0 );
   ret->key = 0;
   return( sizeof( *ret ) );
}

unsigned ReqGet_lib_name( void )
{
   char              *name;
   get_lib_name_ret  *ret;

   ret = GetOutPtr( 0 );
   ret->handle = 0;
   name = GetOutPtr( sizeof( *ret ) );
   *name = '\0';
   return( sizeof( *ret ) + 1 );
}

unsigned ReqGet_err_text( void )
{
   get_err_text_req  *acc;
   char              *err_txt;

   acc = GetInPtr( 0 );
   err_txt = GetOutPtr( 0 );
   strcpy( err_txt, strerror( acc->err ) );
   return( strlen( err_txt ) + 1 );
}

const char * const ExceptionMsgs[] =
{
   TRP_EXC_divide_overflow
   "",
   TRP_EXC_non_maskable_interrupt
   "",
   TRP_EXC_integer_overflow
   TRP_EXC_bounds_check
   TRP_EXC_invalid_opcode
   TRP_EXC_coprocessor_not_available
   TRP_EXC_double_fault
   TRP_EXC_coprocessor_segment_overrun
   TRP_EXC_invalid_TSS
   TRP_EXC_segment_not_present
   TRP_EXC_stack_exception
   TRP_EXC_general_protection_fault
   TRP_EXC_page_fault
   "",
   TRP_EXC_coprocessor_error
};

unsigned ReqGet_message_text( void )
{
   get_message_text_ret *ret;
   char                 *err_txt;

   ret     = GetOutPtr( 0 );
   err_txt = GetOutPtr( sizeof(*ret) );
   if( Exception > ( ( sizeof( ExceptionMsgs ) / sizeof( char * ) - 1 ) ) )
      strcpy( err_txt, TRP_EXC_unknown );
   else
      strcpy( err_txt, ExceptionMsgs[Exception] );
   ret->flags = MSG_NEWLINE | MSG_ERROR;
   return( sizeof( *ret ) + strlen( err_txt ) + 1 );
}

unsigned ReqRedirect_stdin( void  )
{
   redirect_stdin_ret   *ret;

   ret = GetOutPtr( 0 );
   ret->err = 1;
   return( sizeof( *ret ) );
}

unsigned ReqRedirect_stdout( void  )
{
   redirect_stdout_ret  *ret;

   ret = GetOutPtr( 0 );
   ret->err = 1;
   return( sizeof( *ret ) );
}

unsigned ReqSplit_cmd( void )
{
   char           *cmd;
   char           *start;
   split_cmd_ret  *ret;
   unsigned       len;

   cmd = GetInPtr( sizeof( split_cmd_req ) );
   len = GetTotalSize( ) - sizeof( split_cmd_req );
   start = cmd;
   ret = GetOutPtr( 0 );
   ret->parm_start = 0;
   for( ;; )
   {
      if( len == 0 )
         goto done;
      switch( *cmd )
      {
         case '/':
         case '=':
         case '(':
         case ';':
         case ',':
            goto done;
         case '\0':
         case ' ':
         case '\t':
            ret->parm_start = 1;
            goto done;
      }
      ++cmd;
      --len;
   }
done:
   ret->parm_start += cmd - start;
   ret->cmd_end = cmd - start;
   return( sizeof( *ret ) );
}

unsigned ReqRead_regs( void )
{
   mad_registers  *mr;
   struct x86_cpu *cpu;

   mr = GetOutPtr(0);
   cpu = &mr->x86.cpu;
   cpu->eax = Context.EAX;
   cpu->ebx = Context.EBX;
   cpu->ecx = Context.ECX;
   cpu->edx = Context.EDX;
   cpu->esi = Context.ESI;
   cpu->edi = Context.EDI;
   cpu->ebp = Context.EBP;
   cpu->esp = Context.ESP;
   cpu->eip = Context.EIP;
   cpu->efl = Context.EFLAGS;
   cpu->cr0 = cpu->cr2 = cpu->cr3 = 0;
   cpu->ds  = Context.DS;
   cpu->es  = Context.ES;
   cpu->ss  = Context.SS;
   cpu->cs  = Context.CS;
   cpu->fs  = Context.FS;
   cpu->gs  = Context.GS;
   if( DosTraceGetFpuContext( ( TFPU * ) &mr->x86.fpu ) )
      memset( &mr->x86.fpu, 0, sizeof( TFPU ) );
   return( sizeof( mr->x86 ) );
}

unsigned ReqWrite_regs( void )
{
   mad_registers  *mr;
   struct x86_cpu *cpu;

   mr = GetInPtr(sizeof(write_regs_req));
   cpu = &mr->x86.cpu;
   Context.EDI    = cpu->edi;
   Context.ESI    = cpu->esi;
   Context.EBP    = cpu->ebp;
   Context.EBX    = cpu->ebx;
   Context.EDX    = cpu->edx;
   Context.ECX    = cpu->ecx;
   Context.EAX    = cpu->eax;
   Context.EIP    = cpu->eip;
   Context.CS     = cpu->cs;
   Context.EFLAGS = cpu->efl;
   Context.ESP    = cpu->esp;
   Context.SS     = cpu->ss;
   Context.ES     = cpu->es;
   Context.DS     = cpu->ds;
   Context.FS     = cpu->fs;
   Context.GS     = cpu->gs;
   DosTraceSetCpuContext( &Context );
   DosTraceSetFpuContext( ( TFPU * ) &mr->x86.fpu );
   return( 0 );
}

unsigned ReqMachine_data( void )
{
   machine_data_req  *acc;
   machine_data_ret  *ret;
   unsigned_8        *data;

   acc = GetInPtr( 0 );
   ret = GetOutPtr( 0 );
   data = GetOutPtr( sizeof( *ret ) );
   ret->cache_start = 0;
   ret->cache_end = ~( addr_off )0;
   if( Context.EFLAGS & 0x20000 )   /* V86 task ? */
      *data = X86AC_REAL;
   else
      *data = X86AC_BIG;
   return( sizeof( *ret ) + sizeof( *data ) );
}

trap_version TRAPENTRY TrapInit( char *parm, char *err, bool remote )
{
   trap_version   ver;

   parm = parm;
   remote = remote;
   ver.major  = TRAP_MAJOR_VERSION;
   ver.minor  = TRAP_MINOR_VERSION;
   ver.remote = FALSE;
   WatchCount = ProcessTID = CurrentTID = ProcessPID = 0;
   return( ver );
}

void TRAPENTRY TrapFini( void )
{
   if( ProcessPID != 0 )
      DosTraceCloseSession( );
}
