/****************************************************************************
*
*                            Open Watcom Project
*
*  Copyright (c) 2004-2006 The Open Watcom Contributors. All Rights Reserved.
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
* Description: This file contains the functional tests for the utilites.
*
****************************************************************************/

#include <utility>
#include <iostream>

bool pair_test( )
{
  bool rc = true;

  std::pair< int, char > object( 1, 'H' );
  if( !( object == std::make_pair( 1, 'H' ) ) ) {
    std::cout << "pair FAIL 0001\n"; rc = false;
  }

  return rc;
}

int main()
{
  int rc = 0;
  try {
    if( !pair_test( ) ) rc = 1;
  }
  catch( ... ) {
    std::cout << "Unexpected exception of unexpected type.\n";
    rc = 1;
  }

  return rc;
}
