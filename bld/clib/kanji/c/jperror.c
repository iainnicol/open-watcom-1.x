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


#include "variety.h"
#include <jstring.h>
#include <stddef.h>
#include <stdio.h>
#include <errno.h>
#include "rtdata.h"
#include "seterrno.h"

/**
*
*  Name:        jperror -- �G���[���b�Z�[�W�̕\��
*
*  Synopsis:    void jperror( msg );
*
*               unsigned char *msg;     ���[�U�[���b�Z�[�W�̕�����
*
*  Description: ���̊֐��͕ϐ� errno �ɂ���G���[�R�[�h�ɑΉ�����G���[
*               ���b�Z�[�W��\�����܂��B���� msg �ŗ^�����镶����
*               �܂��A�n�߂ɕ\������܂��B����ɂÂ��ăR�����i�F�j�ƁA
*               �G���[���b�Z�[�W���\������܂��B�����G���[�ԍ����s�K�i
*               �Ȕԍ��ł��邠�鎞�ɂ́A�G���[�R�[�h�O�̃��b�Z�[�W��
*               �\������܂��B
*
*
*  Name:        jperror -- print error message
*
*  Synopsis:    void jperror( msg );
*
*               unsigned char *msg;
*
*  Description: This function prints an error message corresponding to the
*               error code stored in errno.  The string supplied as the
*               msg argument is printed first, followed by a colon and
*               the error message.  If the error number is invalid, the
*               message for error code 0 is used.
*
**/

_WCRTLINK void jperror( const char *s )
{
    if( s != NULL && *s != '\0' ) {
        fputs( s, stderr );
        fputs( ": ", stderr );
    }
    fputs( jstrerror( _RWD_errno ), stderr );
    fputc( '\n', stderr );
}