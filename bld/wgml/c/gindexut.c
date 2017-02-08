/****************************************************************************
*
*                            Open Watcom Project
*
*  Copyright (c) 2004-2012 The Open Watcom Contributors. All Rights Reserved.
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
* Description: WGML helper functions for index processing
*                   for  .ix control word
*                   and  :I1 :I2 :I3 :IH1 :IH2 :IH3 :IREF tags
*
****************************************************************************/

#define __STDC_WANT_LIB_EXT1__  1      /* use safer C library              */

#include "wgml.h"
#include "gvars.h"

/***************************************************************************/
/*  allocate and fill a new index entry                                    */
/*  with pageno reference or supplied text                                 */
/*                                                                         */
/*  return ptr to entry                                                    */
/***************************************************************************/

ix_e_blk *  fill_ix_e_blk( ix_e_blk * * anchor, ix_h_blk * ref, ereftyp ptyp,
                    char * text, int text_len )
{
    ix_e_blk    * ixewk;

    ixewk = mem_alloc( sizeof( ix_e_blk ) );
    ixewk->next      = NULL;
    ixewk->corr      = ref;
    if( ptyp == pgnone ) {
        ptyp = pgpageno;                // set default if necessary
    }
    ixewk->entry_typ = ptyp;
    if( ptyp >= pgstring ) {
        ixewk->page_text = mem_alloc( text_len + 1);
        strcpy_s( ixewk->page_text, text_len + 1, text );
    } else {
        ixewk->page_text = NULL;
//      if( ProcFlags.page_started ) {
//          ixewk->page_no = page;
//      } else {
            ixewk->page_no = page + 1;  // + 1 ??  TBD
//      }
    }
    *anchor = ixewk;
    return( ixewk );
}


/***************************************************************************/
/*  free ix_e_blk chain                                                    */
/***************************************************************************/

static  void    free_ix_e_entries( ix_e_blk * e )
{
    ix_e_blk    *   ewk;
    ix_e_blk    *   ew  = e;

    while( ew != NULL ) {
        ewk = ew->next;
        if( ew->entry_typ >= pgstring ) {
            mem_free( ew->page_text );
        }
        mem_free( ew );
        ew = ewk;
    }
}


/***************************************************************************/
/*  free ix_h_blk   header entry                                           */
/***************************************************************************/

static  void    free_ix_h_entry( ix_h_blk * h )
{
    if( h->prt_term != NULL ) {         // free different display txt
        mem_free( h->prt_term );
    }
    mem_free( h->ix_term );             // free index term
    mem_free( h );                      // and the entry itself
}


/***************************************************************************/
/*  free all entries in index_dict                                         */
/***************************************************************************/

void    free_index_dict( ix_h_blk * * dict )
{
    ix_h_blk    *   ixh1;
    ix_h_blk    *   ixh2;
    ix_h_blk    *   ixh3;
    ix_h_blk    *   ixhw;

    ixh1 = *dict;
    while( ixh1 != NULL ) {             // level 1 entries

        free_ix_e_entries( ixh1->entry );

        ixh2 = ixh1->lower;
        while( ixh2 != NULL ) {         // level 2 entries
            free_ix_e_entries( ixh2->entry );

            ixh3 = ixh2->lower;
            while( ixh3 != NULL ) {     // level 3 entries
                free_ix_e_entries( ixh3->entry );

                ixhw = ixh3->next;
                free_ix_h_entry( ixh3 );
                ixh3 = ixhw;
            }
            ixhw = ixh2->next;
            free_ix_h_entry( ixh2 );
            ixh2 = ixhw;
        }
        ixhw = ixh1->next;
        free_ix_h_entry( ixh1 );
        ixh1 = ixhw;
    }
    *dict = NULL;                       // dict is now empty
}


/***************************************************************************/
/*  free only ix_e entries in index_dict                                   */
/***************************************************************************/

void    free_ix_e_index_dict( ix_h_blk * * dict )
{
    ix_h_blk    *   ixh1;
    ix_h_blk    *   ixh2;
    ix_h_blk    *   ixh3;

    ixh1 = *dict;
    while( ixh1 != NULL ) {             // level 1 entries

        free_ix_e_entries( ixh1->entry );

        ixh2 = ixh1->lower;
        while( ixh2 != NULL ) {         // level 2 entries
            free_ix_e_entries( ixh2->entry );

            ixh3 = ixh2->lower;
            while( ixh3 != NULL ) {     // level 3 entries
                free_ix_e_entries( ixh3->entry );

//                ixh3->lower = NULL;
                ixh3->entry = NULL;
                ixh3        = ixh3->next;
            }
//            ixh2->lower = NULL;
            ixh2->entry = NULL;
            ixh2        = ixh2->next;
        }
//        ixh1->lower = NULL;
        ixh1->entry = NULL;
        ixh1        = ixh1->next;
    }
//    *dict = NULL;                       // dict is now empty
}

