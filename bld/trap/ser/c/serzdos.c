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

#include <stddef.h>
#include <zbios.h>
#include <zdos.h>
#include <zthread.h>
#include "trpimp.h"
#include "trperr.h"

extern  void   NothingToDo( void );
static int     CurrentBaud, Break, Port, Stop, BaudRate, Parity, Data;
unsigned int   Ticks;

void ZeroWaitCount( void )
{
   Ticks = DosElapsedPeriodicTicks( 0 );
}

unsigned WaitCount( void )
{
   return( DosElapsedPeriodicTicks( Ticks ) );
}

char *InitSys( void )
{

   if( BiosOpenUart( Port ) < 0 )
      return( "BiosOpenUart() failed" );
   return( NULL );
}

void ResetSys( void )
{
   BiosCloseUart( Port );
}

void SendByte( int value )
{
   BiosUartOutput( value, Port );
}

void StartBlockTrans( void )
{
}

void StopBlockTrans( void )
{
}

int GetByte( void )
{
   return( BiosUartInput( Port ) );
}

void ClearCom( void )
{
   BiosCloseUart( Port );
   BiosOpenUart( Port );
   BiosExtendedUartSetup( Break, Port, Stop, BaudRate, Parity, Data );
}

int BaudRates[] =
{
   X_BAUDRATE_115200,
   X_BAUDRATE_56000,
   X_BAUDRATE_38400,
   X_BAUDRATE_19200,
   X_BAUDRATE_9600,
   X_BAUDRATE_4800,
   X_BAUDRATE_2400,
   X_BAUDRATE_1200,
   X_BAUDRATE_600
};

bool Baud( int index )
{
   if( index == CurrentBaud )
      return( TRUE );
   CurrentBaud = index;
   BaudRate = BaudRates[index];
   ClearCom( );
   return( TRUE );
}

char *ParsePortSpec( char **spec )
{
   char  *parm;

   parm = ( spec == NULL ) ? "" : *spec;

   switch( *parm )
   {
      case '1':
         ++parm;
         /* fall through */
      case '.':
      case '\0':
         Port = 0;
         break;
      case '2':
         ++parm;
         Port = 1;
         break;
      default:
         return( TRP_ERR_invalid_serial_port_number );
   }
   if( *parm != '\0' && *parm != '.' )
      return( TRP_ERR_invalid_serial_port_number );
   if( spec != NULL )
      *spec = parm;
   return( NULL );
}

void DonePort( void )
{
}

bool CheckPendingError( void )
{
   return( FALSE );
}

void ClearLastChar( void )
{
}


 void Wait( unsigned timer_ticks )
{
   DosSleepThread( timer_ticks );
}

int WaitByte( unsigned int ticks )
{
   unsigned int   wait_time;  /* timer variable for testing time-out */
   int            data;       /* storing data from receive buffer */

   ZeroWaitCount();
   wait_time = WaitCount() + ticks;
   for( ;; )
   {
      data = GetByte();
      if( data >= 0 )
         break;               /* character received */
      if( WaitCount() >= wait_time )
         break;
      NothingToDo();
   }
   return( data );
}
