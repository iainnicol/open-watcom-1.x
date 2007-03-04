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
* Description:  Manage the frr list of intenal text nodes
*
****************************************************************************/

//#include "global.h"
#include "ftnstd.h"
#include "fmemmgr.h"
#include "itdefn.h"
#include "frl.h"

static itnode *        ITPool;         // head of free list of intern text nodes

//===========================================
static itnode*  FrlAlloc(itnode * &head)
{
    // Get node from the free list if possible.
    itnode* next;

    // something in the list
    if(0 != head)
    {
        //get it
        next = head;
        head = head->link;
    }else
    {   //allocate a new node 
        next = static_cast<itnode*>(FMemAlloc(sizeof(itnode)));
    }
    return next ;
}

//=================================================
void    FrlFree(itnode* &head, itnode* node)
{
   // Add item to the list head pointer head.

    itnode*     tempHead;

    tempHead = head;
    node->link = tempHead;
    head = node;
}

//==============================
static void FrlInit(itnode * &head )
{
   // Initialize for free list manipulations.

   head = NULL;
}

//==============================
void FrlFini(itnode* &head)
{
    // Throw away the free list of it nodes
    itnode*  curr;
    itnode*  junk;

    curr = head;
    head = 0;
    // release list
    while(0!= curr)
    {
        junk = curr;
        curr = curr->link;
        //release single list element
        FMemFree(junk);
    }
}

////////////////////////////////
//
// Allocate an empty IT Node
//
///////////////////////////////
itnode  *AllocITNode(void)
{
    return FrlAlloc(ITPool);
}

///////////////////////////////
//
// free IT List
//
//////////////////////////////
void FiniITNode()
{
    FrlFini(ITPool);
}

///////////////////////////////
//
// Initialize IT Pool root
//
///////////////////////////////
void InitITPoolRoot()
{
    ITPool = NULL;
}

////////////////////////////////////
//
// Initialize IT Pool
//
///////////////////////////////////
void InitITPool()
{
    FrlInit(ITPool);
}

////////////////////////////////////
//
// free an IT node
//
////////////////////////////////////
void FreeITNode(itnode* node)
{
   //release the node into free list
   FrlFree(ITPool, node);
}
