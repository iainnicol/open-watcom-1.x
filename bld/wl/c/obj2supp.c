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
 *  OBJ2SUPP : utilities for wlink specific parts of objpass2
 *
 */

#include <string.h>
#include "linkstd.h"
#include "reloc.h"
#include "pcobj.h"
#include "newmem.h"
#include "msg.h"
#include "alloc.h"
#include "mapio.h"
#include "exeos2.h"
#include "exeqnx.h"
#include "exeelf.h"
#include "loadfile.h"
#include "loados2.h"
#include "loadnov.h"
#include "loadqnx.h"
#include "loadelf.h"
#include "wlnkmsg.h"
#include "virtmem.h"
#include "objpass2.h"
#include "objstrip.h"
#include "objcalc.h"
#include "impexp.h"
#include "overlays.h"
#include "strtab.h"
#include "carve.h"
#include "permdata.h"
#include "dbgcv.h"
#include "dbgall.h"
#include "toc.h"
#include "ring.h"
#include "obj2supp.h"

typedef struct fix_data {
    byte *      data;
    unsigned_32 value;              /* value at location being patched */
    targ_addr   loc_addr;
    targ_addr   tgt_addr;
    fix_type    type;
    unsigned    ffix        : 3;
    unsigned    additive    : 1;
    unsigned    done        : 1;
    unsigned    imported    : 1;
    unsigned    os2_selfrel : 1;
} fix_data;

// static offset        LastOptimized;  // offset last optimized.
// static fix_type      LastOptType;
static segdata *        LastSegData;
static offset           FixupOverflow;

static unsigned         MapOS2FixType( unsigned type );

#define MAX_ADDEND_SIZE (2 * sizeof(unsigned_32))

extern void ResetObj2Supp( void )
/*******************************/
{
    FixupOverflow = 0;
//    LastOptimized = 0xFFFFFFFF;
}

static void DCERelocRef( symbol *sym, bool isdata )
/*************************************************/
{
    if( isdata ) {
        if( !(sym->info & SYM_VF_REFS_DONE) ) {
            DataRef( sym );
        }
    } else {
        if( CurrRec.seg->ispdata || CurrRec.seg->isreldata ) {
            if( !IsTocSym( sym ) ) {       // make sure that if symbol goes,
                AddSymSegEdge(sym, CurrRec.seg); // .pdata and .reldata go too
            }
        } else {
            AddEdge( CurrRec.seg, sym );
        }
    }
}

static void TraceFixup( fix_type type, frame_spec *targ )
/*******************************************************/
{
    bool        isovldata;          // TRUE if data and overlaying.
    bool        overlay;            // TRUE if doing overlays;

    overlay  = (FmtData.type & MK_OVERLAYS) && !FmtData.u.dos.noindirect;
    if( LinkFlags & STRIP_CODE || overlay ) {
        isovldata = !(CurrRec.seg->u.leader->info & SEG_OVERLAYED);
        if( ObjFormat & FMT_UNSAFE_FIXUPP ) isovldata = TRUE;
        if( targ->type == FIX_FRAME_SEG ) {
            if( LinkFlags & STRIP_CODE ) {
                if( targ->u.sdata->iscode && targ->u.sdata != CurrRec.seg ) {
                    RefSeg( targ->u.sdata );
                }
            }
        } else if( targ->type == FIX_FRAME_EXT ) {
            if( LinkFlags & STRIP_CODE ) {
                DCERelocRef( targ->u.sym, !CurrRec.seg->iscode );
            }
            if( !(type & FIX_REL) && overlay ) {
                switch( type & (FIX_OFFSET_MASK|FIX_BASE|FIX_HIGH) ) {
                case FIX_OFFSET_16:
                    if( FmtData.u.dos.ovl_short ) {
                        IndirectCall( targ->u.sym );
                    }
                    break;
                case FIX_BASE:
                    IndirectCall( targ->u.sym );
                    break;
                case FIX_BASE_OFFSET_16:
                    if( isovldata ) {
                        IndirectCall( targ->u.sym );
                    }
                    break;
                }
            }  /* end if (notrelative && overlay) */
        } /* end if (a symbol/segment) */
    }
}

extern void RelocStartMod( void )
/*******************************/
{
    LastSegData = NULL;
}

static byte     OffsetSizes[] = { 0, 1, 2, 4, 4, 4 };

static unsigned CalcFixupSize( fix_type type )
/********************************************/
{
    unsigned value;

    value = OffsetSizes[ FIX_GET_OFFSET(type) ];
    if( type &  FIX_BASE ) {
        value += sizeof(unsigned_16);
    }
    return value;
}

static unsigned CalcAddendSize( fix_type fixtype )
/************************************************/
{
    if( fixtype & FIX_ADDEND_ZERO ) {
        return 0;
    } else if( fixtype & FIX_BASE
        && (fixtype & FIX_OFFSET_MASK) == FIX_OFFSET_32 ) {
        return MAX_ADDEND_SIZE;
    }
    return sizeof(unsigned_32);
}

static unsigned CalcSavedFixSize( fix_type fixtype )
/**************************************************/
{
    unsigned    retval;

    if( fixtype & FIX_CHANGE_SEG ) {
        retval = sizeof(unsigned_32);
    } else {
        retval = sizeof(save_fixup) + CalcAddendSize( fixtype );
        if( FRAME_HAS_DATA(FIX_GET_FRAME(fixtype)) ) {
            retval += sizeof(unsigned_32);
        }
    }
    return retval;
}

static void UpdateFramePtr( frame_spec *frame )
/*********************************************/
/* do any necessary work to get frame pointing to the right place */
{
    switch( frame->type ) {
    case FIX_FRAME_GRP:
        if( IS_FMT_INCREMENTAL(CurrMod->modinfo) ) {
            DbgAssert( frame->u.val != 0 );
            frame->u.group = IncGroups[frame->u.val - 1];
        }
        break;
    case FIX_FRAME_EXT:
        frame->u.sym = UnaliasSym( ST_FIND, frame->u.sym );
        DbgAssert( frame->u.sym != NULL );
        break;
    }
}

static void GetFrameAddr( frame_spec *frame, targ_addr *addr,
                          targ_addr *tgt_addr, unsigned_32 off )
/**************************************************************/
{
    switch( frame->type ) {
    case FIX_FRAME_SEG:
        *addr = frame->u.sdata->u.leader->seg_addr;
        addr->off += frame->u.sdata->a.delta;
        break;
    case FIX_FRAME_GRP:
        *addr = frame->u.group->grp_addr;
        break;
    case FIX_FRAME_EXT:
        *addr = frame->u.sym->addr;
        break;
    case FIX_FRAME_ABS:
        addr->seg = frame->u.abs;
        break;
    case FIX_FRAME_LOC:
        *addr = CurrRec.addr;
        addr->off += off;
        break;
    case FIX_FRAME_TARG:
    case FIX_FRAME_FLAT:
        *addr = *tgt_addr;
        break;
    }
}

static void MapFramePtr( frame_spec *frame, void **targ )
/*******************************************************/
{
    switch( frame->type ) {
    case FIX_FRAME_SEG:
        *targ = CarveGetIndex( CarveSegData, *targ );
        break;
    case FIX_FRAME_GRP:
        *targ = (void *) frame->u.group->num;
        break;
    case FIX_FRAME_EXT:
        *targ = CarveGetIndex( CarveSymbol, *targ );
        break;
    }
}

static segdata * GetFrameSegData( frame_spec *targ )
/**************************************************/
{
    segdata *   sdata;
    seg_leader *leader;

    sdata = NULL;
    switch( targ->type ) {
    case FIX_FRAME_SEG:
         sdata = targ->u.sdata;
        break;
    case FIX_FRAME_GRP:
        leader = Ring2First( targ->u.group->leaders );
        if( leader != NULL ) {
            sdata = Ring2First( leader->pieces );
        }
        break;
    case FIX_FRAME_EXT:
        sdata = targ->u.sym->p.seg;
        break;
    }
    return sdata;
}

static bool IsReadOnly( segdata *sdata )
/**************************************/
{
    return sdata->iscode ||
        (sdata->u.leader->group != NULL &&
         sdata->u.leader->group->segflags & SEG_READ_ONLY);
}

static void CheckRWData( frame_spec *targ, targ_addr *addr )
/**********************************************************/
{
    if( FmtData.type & MK_WINDOWS && FmtData.u.os2.chk_seg_relocs
                                  && IsReadOnly( LastSegData ) ) {
        if( !IsReadOnly( GetFrameSegData( targ ) ) ) {
            LnkMsg( LOC+WRN+MSG_RELOC_TO_RWDATA_SEG, "a", addr );
        }
    }
}

static bool IsTargAbsolute( frame_spec *targ )
/********************************************/
{
    return (targ->type == FIX_FRAME_SEG && targ->u.sdata->isabs)
        || (targ->type == FIX_FRAME_EXT && targ->u.sym->info & SYM_ABSOLUTE);
}

static void BuildReloc( save_fixup *save, frame_spec *targ, frame_spec *frame )
/*****************************************************************************/
{
    fix_data    fix;
    targ_addr   faddr;
    char        addbuf[MAX_ADDEND_SIZE];
    unsigned    datasize;

    memset( &fix, 0, sizeof(fix_data) );        // to get all bitfields 0
    GetFrameAddr( targ, &fix.tgt_addr, NULL, save->off );
    GetFrameAddr( frame, &faddr, &fix.tgt_addr, save->off );
    fix.type = save->flags;
    fix.loc_addr = CurrRec.addr;
    fix.loc_addr.off += save->off;
    if( targ->type == FIX_FRAME_EXT ) {
        if( targ->u.sym->info & SYM_TRACE ) {
            RecordTracedSym( targ->u.sym );
        }
        if( !(targ->u.sym->info & SYM_DEFINED) ) {
            ProcUndefined( targ->u.sym );
            return;
        }
        fix.ffix = GET_FFIX_VALUE(targ->u.sym);
        if( IS_SYM_IMPORTED(targ->u.sym ) ) {
            if( frame->type < FIX_FRAME_LOC && targ->u.sym != frame->u.sym ) {
                if( FmtData.type & (MK_NOVELL | MK_OS2_FLAT | MK_PE) ) {
                    fix.tgt_addr.seg = faddr.seg;
                    fix.tgt_addr.off = 0;
                } else {
                    LnkMsg( LOC+ERR+MSG_FRAME_EQ_TARGET, "a",&fix.loc_addr);
                }
            }
            fix.imported = TRUE;
        } else if( !(targ->u.sym->info & SYM_DEFINED) ) {
            ProcUndefined( targ->u.sym );
            return;
        }
    }
    if( save->flags & FIX_BASE ) {
        if( FmtData.type & (MK_PROT_MODE & ~(MK_OS2_FLAT | MK_PE)) ) {
            if( faddr.seg != fix.tgt_addr.seg ) {
                if( FmtData.type & MK_ID_SPLIT ) {
                    LnkMsg( LOC+ERR+MSG_NOV_NO_CODE_DATA_RELOC, "a",
                                                            &fix.loc_addr );
                } else {
                    LnkMsg( LOC+ERR+MSG_FRAME_EQ_TARGET, "a", &fix.loc_addr );
                }
            }
        }
        if( !fix.imported ) {
            CheckRWData( targ, &fix.loc_addr );
        }
    }
    if( !fix.imported ) {
        if( ((save->flags & FIX_OFFSET_MASK) > FIX_OFFSET_16) || fix.ffix != 0){
            fix.tgt_addr.seg = faddr.seg;
        } else {
            ConvertToFrame( &fix.tgt_addr, faddr.seg );
        }
    }
    if( (save->flags & (FIX_OFFSET_MASK|FIX_HIGH)) == FIX_HIGH_OFFSET_16 ) {
        fix.tgt_addr.off += FixupOverflow << 16;
    }
    if( IsTargAbsolute( targ ) ) {
        fix.type |= FIX_ABS;
    }
    datasize = CalcFixupSize( fix.type );
    ReadInfo( CurrRec.seg->data + save->off, addbuf, datasize );
    fix.data = addbuf;
    Relocate( &fix, targ );
    PutInfo( CurrRec.seg->data + save->off, fix.data, datasize );
}

extern unsigned IncExecRelocs( void *_save )
/******************************************/
{
    save_fixup *save = _save;
    segdata *   sdata;
    frame_spec  targ;
    frame_spec  frame;

    if( save->flags & FIX_CHANGE_SEG ) {
        sdata = (segdata *) (save->flags & ~FIX_CHANGE_SEG);
        if( LinkFlags & INC_LINK_FLAG ) {
            save->flags = (unsigned_32) CarveGetIndex( CarveSegData, sdata );
            save->flags |= FIX_CHANGE_SEG;
        }
        if( !sdata->isdead ) {
            LoadObj( sdata );
            LastSegData = sdata;
        } else {
            LastSegData = NULL;
        }
    } else {
        targ.type = FIX_GET_TARGET(save->flags);
        targ.u.ptr = save->target;
        frame.type = FIX_GET_FRAME(save->flags);
        if( FRAME_HAS_DATA( frame.type ) ) {
            frame.u.ptr = *((void **)(save + 1));
        }
        UpdateFramePtr( &targ );
        UpdateFramePtr( &frame );
        if( LastSegData != NULL ) {
            BuildReloc( save, &targ, &frame );
        }
        if( LinkFlags & INC_LINK_FLAG ) {
            MapFramePtr( &targ, &save->target );
            MapFramePtr( &frame, (void **)(save + 1) );
        }
    }
    return CalcSavedFixSize( save->flags );
}

static void FixFrameValue( frame_type type, void **target )
/*********************************************************/
{
    switch( type ) {
    case FIX_FRAME_SEG:
        *target = CarveMapIndex( CarveSegData, *target );
        break;
    case FIX_FRAME_EXT:
        *target = CarveMapIndex( CarveSymbol, *target );
        break;
    }
}

extern unsigned RelocMarkSyms( void *_fix )
/*****************************************/
{
    save_fixup *fix = _fix;
    segdata *   sdata;
    frame_type  frame;
    symbol *    sym;

    if( fix->flags & FIX_CHANGE_SEG ) {
        sdata = CarveMapIndex( CarveSegData,
                                (void *) (fix->flags & ~FIX_CHANGE_SEG) );
        fix->flags = (unsigned_32) sdata | FIX_CHANGE_SEG;
    } else {
        frame = FIX_GET_FRAME(fix->flags);
        if( FRAME_HAS_DATA(frame) ) {
            FixFrameValue( frame, (void **) (fix + 1) );
        }
        frame = FIX_GET_TARGET(fix->flags);
        FixFrameValue( frame, &fix->target );
        if( frame == FIX_FRAME_EXT ) {
            sym = (symbol *)fix->target;
            sym->info |= SYM_RELOC_REFD;
            sym = UnaliasSym( ST_FIND, sym );
            sym->info |= SYM_RELOC_REFD;
        }
    }
    return CalcSavedFixSize( fix->flags );
}

static bool MemIsZero( char *mem, unsigned size )
/***********************************************/
{
    while( size > 0 ) {
        if( *mem != '\0' ) return FALSE;
        mem++;
        size--;
    }
    return TRUE;
}

extern void StoreFixup( offset off, fix_type type, frame_spec *frame,
                        frame_spec *targ, offset addend )
/*******************************************************************/
{
    save_fixup  save;
    fix_data    fix;
    unsigned    size;
    char        buff[2 * sizeof(unsigned_32)];

    if( LastSegData != CurrRec.seg ) {
        DbgAssert( CurrRec.seg != NULL );
        LastSegData = CurrRec.seg;
        save.flags = (unsigned_32) CurrRec.seg;
        save.flags |= FIX_CHANGE_SEG;   // DANGER! assume pointers word aligned
        PermSaveFixup( &save, sizeof(unsigned_32) );
    }
    save.flags = type;
    save.flags |= (unsigned_32)targ->type << FIX_TARGET_SHIFT;
    save.flags |= (unsigned_32)frame->type << FIX_FRAME_SHIFT;
    save.off = off + CurrRec.obj_offset;
    save.target = targ->u.ptr;
    if( ObjFormat & FMT_UNSAFE_FIXUPP ) {
        save.flags |= FIX_UNSAFE;
    }
    size = CalcFixupSize( type );
    if( CurrRec.data != NULL ) {
        memcpy( buff, CurrRec.data + off, size );
    } else {
        ReadInfo( CurrRec.seg->data + save.off, buff, size );
    }
    fix.type = type;
    fix.data = buff;
    if( (type & (FIX_OFFSET_MASK|FIX_HIGH)) == FIX_HIGH_OFFSET_16 ) {
        addend += FixupOverflow << 16;
    }
    PatchOffset( &fix, addend, TRUE );
    if( MemIsZero( buff, size ) ) {
        save.flags |= FIX_ADDEND_ZERO;
    }
    PermSaveFixup( &save, sizeof(save_fixup) );
    if( FRAME_HAS_DATA( frame->type ) ) {
        PermSaveFixup( &frame->u.abs, sizeof(unsigned_32) );
    }
    if( !(save.flags & FIX_ADDEND_ZERO) )  {
        PermSaveFixup( buff, CalcAddendSize( save.flags ) );
    }
    TraceFixup( save.flags, targ );
    if( CurrRec.data != NULL ) {
        memcpy( CurrRec.data + off, buff, size );
    } else {
        PutInfo( CurrRec.seg->data + save.off, buff, size );
    }
}

extern unsigned IncSaveRelocs( void *_save )
/******************************************/
{
    save_fixup *save = _save;
    segdata *   sdata;
    frame_spec  targ;
    unsigned    fixsize;
    unsigned    datasize;
    char *      data;

    fixsize = CalcSavedFixSize( save->flags );
    if( save->flags & FIX_CHANGE_SEG ) {
        sdata = (segdata *) (save->flags & ~FIX_CHANGE_SEG);
        if( !sdata->isdead ) {
            LastSegData = sdata;
        } else {
            LastSegData = NULL;
        }
    } else if( LastSegData != NULL ) {
        targ.type = FIX_GET_TARGET(save->flags);
        targ.u.ptr = save->target;
        datasize = CalcFixupSize( save->flags );
        if( save->flags & FIX_ADDEND_ZERO ) {
            PutNulls( LastSegData->data + save->off, datasize  );
        } else {
            data = (char *)save + (fixsize - CalcAddendSize(save->flags));
            PutInfo( LastSegData->data + save->off, data, datasize  );
        }
        TraceFixup( save->flags, &targ );
    }
    PermSaveFixup( save, fixsize );
    return fixsize;
}

static void DumpReloc( base_reloc *curr )
/***************************************/
{
    if( curr->isfloat ) {
        FloatReloc( &curr->item );
    } else if( curr->isqnxlinear ) {
        QNXLinearReloc( CurrRec.seg->u.leader->group, &curr->item );
    } else {
        WriteReloc( CurrRec.seg->u.leader->group, curr->fix_off,
                    &curr->item, curr->rel_size );
        if( FmtData.type & MK_OS2_FLAT ) {
            if( OSF_PAGE_SIZE - (curr->fix_off & OSF_PAGE_MASK)
                < curr->fix_size ) {
                /* stupid relocation has been split across two
                    pages, have to duplicate the entry */
                curr->item.os2f.fmt.r32_soff -= OSF_PAGE_SIZE;
                WriteReloc( CurrRec.seg->u.leader->group,
                            curr->fix_off + OSF_PAGE_SIZE, &curr->item,
                            curr->rel_size );
            }
        }
    }
}

static void InitReloc( base_reloc *reloc )
/****************************************/
{
    reloc->isfloat = FALSE;
    reloc->isqnxlinear = FALSE;
    reloc->rel_size = FmtRelocSize;
}

static unsigned FindGroupIdx( segment seg )
/******************************************/
{
    group_entry *group;
    unsigned    index;

    index = 1;
    for( group = Groups; group != NULL; group = group->next_group ) {
        if( group->grp_addr.seg == seg ) {
            return index;
        }
        index++;
    }
    return 0;
}

static void PatchOffset( fix_data *fix, unsigned_32 val, bool isdelta )
/*********************************************************************/
/* patch offsets into the loaded object */
{
    byte *      code;
    unsigned_32 oldval;
    signed_32   sval;

    FixupOverflow = 0;
    if( val == 0 ) return;
    code = fix->data;
    if( fix->type & FIX_SHIFT ) {
        if( val & 3 ) {
            LnkMsg( LOC+WRN+MSG_REL_NOT_ALIGNED, "a", &fix->loc_addr );
        }
        val >>= 2;
    }
    switch( fix->type & FIX_OFFSET_MASK ) {
    case FIX_OFFSET_8:
        if( fix->type & FIX_HIGH ) {
            val >>= 8;
        }
        PUT_U8( code, GET_U8( code ) + val );
        break;
    case FIX_OFFSET_16:
        if( fix->type & FIX_HIGH ) {
            val >>= 16;
        }                       // NOTE the fall through
    case FIX_NO_OFFSET:         // used for FIX_BASE
        if( fix->type & FIX_SIGNED ) {
            if( isdelta ) {
                sval = (signed_32)(*((signed_16 *)code)) + val;
                val = sval;
                if( sval > 0x7FFF ) {
                    val = val & 0xFFFF;
                    if( val > 0x7FFF ) {
                        FixupOverflow = 1;
                        val -= 0x10000;
                    }
                }
            } else {
                oldval = val;
                sval = (signed_32)(*((signed_16 *)code));
                val += sval;
                if( (oldval >> 16) < (val >> 16) ) {
                    FixupOverflow = 1;
                } else if( fix->type & FIX_SIGNED
                                && (oldval >> 16) == (val >> 16)
                                && ((signed_16) (val & 0xFFFF)) < 0 ) {
                    FixupOverflow = 1;
                }
            }
        } else {
            val += GET_U16( code );
        }
        PUT_U16( code, val );
        break;
    case FIX_OFFSET_21:
        oldval = GET_U32( code );
        val += oldval;
        oldval &= 0xFFE00000;
        val &= 0x001FFFFF;
        PUT_U32( code, oldval | val );
        break;
    case FIX_OFFSET_24:
        oldval = GET_U32( code );
        val += oldval;
        oldval &= 0xFC000000;
        val &= 0x03FFFFFF;
        PUT_U32( code, oldval | val );
        break;
    case FIX_OFFSET_32:
        PUT_U32( code, GET_U32( code ) + val );
        break;
    default:
        LnkMsg( LOC+ERR+MSG_BAD_RELOC_TYPE, NULL );
    }
}

static void MakeQNXFloatReloc( fix_data *fix )
/********************************************/
{
    base_reloc  new_reloc;

    if( FmtData.u.qnx.gen_seg_relocs ) {
        InitReloc( &new_reloc );
        new_reloc.isfloat = TRUE;
        new_reloc.item.qnx.reloc_offset = fix->loc_addr.off
                               | ((unsigned_32)fix->ffix << 28);
        new_reloc.item.qnx.segment = ToQNXIndex( fix->loc_addr.seg );
        DumpReloc( &new_reloc );
    }
}

static byte WinFFixMap[] = {
    0,
    WIN_FFIX_WR_SYMBOL,
    WIN_FFIX_DR_SYMBOL,
    WIN_FFIX_ES_OVERRIDE,
    WIN_FFIX_CS_OVERRIDE,
    WIN_FFIX_SS_OVERRIDE,
    WIN_FFIX_DS_OVERRIDE
};

static void MakeWindowsFloatReloc( fix_data *fix )
/************************************************/
{
    base_reloc          new_reloc;
    os2_reloc_item *    os2item;

    InitReloc( &new_reloc );
    os2item = &new_reloc.item.os2;
    os2item->addr_type = MapOS2FixType( fix->type );
    os2item->reloc_offset = fix->loc_addr.off
                        - CurrRec.seg->u.leader->group->grp_addr.off;
    os2item->reloc_type = OSFIXUP | ADDITIVE;
    os2item->put.fltpt = WinFFixMap[ fix->ffix ];
    DumpReloc( &new_reloc );
}

static offset GetSegOff( segdata *sdata )
/***************************************/
{
    return sdata->a.delta + sdata->u.leader->seg_addr.off;
}

static void CheckPartialRange( fix_data *fix, signed_32 off,
                               unsigned_32 mask, unsigned_32 topbit )
/*******************************************************************/
{
    unsigned_32 utemp;
    signed_32   temp;

    utemp = GET_U32( fix->data ) & mask;
    if( utemp & topbit ) {      // it is negative
        utemp |= ~mask; // do a bogus sign extension
    }
    temp = utemp;
    if( fix->type & FIX_SHIFT ) {
        temp += off / 4;
    } else {
        temp += off;
    }
    if( temp < -topbit || temp >= topbit ) {
        LnkMsg( LOC+ERR+MSG_FIXUP_OFF_RANGE, "a", &fix->loc_addr );
    }
}

static bool CheckSpecials( fix_data *fix, frame_spec *targ )
/**********************************************************/
{
    signed_32   off;
    unsigned_32 uoff;
    signed_32   temp;
    signed_16   pos;
    unsigned    fixsize;
    group_entry *group;
    segdata  *  sdata;
    fix_type    special;

    if( FmtData.type & MK_ELF ) {
        if( !(fix->type & FIX_REL) ) return FALSE;
        if( fix->loc_addr.seg != fix->tgt_addr.seg ) return FALSE;
    }
    if( FmtData.type & (MK_QNX|MK_WINDOWS) && fix->ffix != FFIX_NOT_A_FLOAT ) {
        if( fix->ffix != FFIX_IGNORE ) {
            if( FmtData.type & MK_QNX ) {
                MakeQNXFloatReloc( fix );
            } else {
                MakeWindowsFloatReloc( fix );
            }
        }
        return TRUE;
    }
    special = fix->type & FIX_SPECIAL_MASK;
    if( special == FIX_TOC || special == FIX_TOCV) {
        if( special == FIX_TOCV ) {
            DbgAssert( targ->type == FIX_FRAME_EXT );
            pos = FindSymPosInTocv( targ->u.sym );
        } else {
            if( targ->type  == FIX_FRAME_EXT ) {
                pos = FindSymPosInToc( targ->u.sym );
            } else {
                sdata = GetFrameSegData( targ );
                uoff = fix->tgt_addr.off - GetSegOff( sdata );
                pos = FindSdataOffPosInToc( sdata, uoff );
            }
        }
        DbgVerify( (pos % 4) == 0, "symbol not in toc" );
        PUT_U16(fix->data, pos);
        return TRUE;
    } else if( special == FIX_IFGLUE ) {
        if( targ->type == FIX_FRAME_EXT && IS_SYM_IMPORTED(targ->u.sym) ) {
            enum { TOC_RESTORE_INSTRUCTION = 0x804b0004 };
            PUT_U32( fix->data, TOC_RESTORE_INSTRUCTION );
        }
        return TRUE;
    }
    if( !(fix->type & FIX_REL) ) return FALSE;
    if( FmtData.type & MK_OS2_FLAT ) {
        /* OS/2 V2 relative fixups to imported items or other objects
            require special handling */
        if( fix->imported ) return FALSE;
        if( fix->loc_addr.seg != fix->tgt_addr.seg ) return FALSE;
    }
    if( fix->type & FIX_ABS && !(FmtData.type & MK_QNX) ) {
        LnkMsg( LOC+ERR+MSG_BAD_ABS_FIXUP, "a", &fix->loc_addr );
        return TRUE;
    }
    if( fix->type & FIX_BASE ) {
        LnkMsg( LOC+ERR+MSG_BAD_REL_FIXUP, "a", &fix->loc_addr );
        return TRUE;
    }
    if( fix->imported ) {
        if( FmtData.type & MK_OS2_16BIT ) {  // can not get at a DLL relatively
            LnkMsg( LOC+ERR+MSG_DLL_IN_REL_RELOC, "a", &fix->loc_addr );
        } else if( FmtData.type & MK_ELF ) {
            return FALSE;
        } else if( FmtData.type & MK_NOVELL ) {
            if( (fix->type & FIX_OFFSET_MASK) != FIX_OFFSET_32
                        || fix->type & FIX_BASE ) {
                LnkMsg( LOC+ERR+MSG_BAD_IMP_REL_RELOC, "a", &fix->loc_addr);
            } else {                           // TRUE == isrelative.
                AddNovImpReloc( targ->u.sym, fix->loc_addr.off, TRUE,
                                fix->loc_addr.seg == DATA_SEGMENT );
// I don't know why the novell linker does this, but it does.
                PatchOffset( fix, -4, TRUE );
            }
        }
        return TRUE;
    }
    if( FmtData.type & (MK_PROT_MODE & ~(MK_OS2_FLAT|MK_PE)) ) {
        if( fix->loc_addr.seg != fix->tgt_addr.seg && !(fix->type & FIX_ABS) ) {
            //must have same file segment.
            if( FmtData.type & MK_ID_SPLIT ) {
                LnkMsg( LOC+ERR+MSG_NOV_NO_CODE_DATA_RELOC, "a",
                                                        &fix->loc_addr );
            } else {
                LnkMsg( LOC+ERR+MSG_REL_NOT_SAME_SEG, "a", &fix->loc_addr );
            }
            return TRUE;
        }
    }
    if( FmtData.type & MK_LINEARIZE ) {
        group = FindGroup( fix->tgt_addr.seg );
        if( group == NULL ) {           // can happen for IAT symbols.
            off = 0;
        } else {
            off = group->linear;
        }
        group = FindGroup( fix->loc_addr.seg );
        if( group != NULL ) {
            off -= group->linear;
        }
        off += fix->tgt_addr.off - fix->loc_addr.off;
    } else if( FmtData.type & (MK_386|MK_QNX) ) {
        off = fix->tgt_addr.off - fix->loc_addr.off;
        if( fix->type & FIX_ABS ) {
            off -= FindGroup( fix->loc_addr.seg )->linear;
        }
    } else {
        off = SUB_ADDR( fix->tgt_addr, fix->loc_addr );
    }
    fixsize = CalcFixupSize( fix->type );
    off -= fixsize;
    if( fix->type == FIX_OFFSET_16 ) {
        temp = off + (fix->loc_addr.off + fixsize);
        if( temp < 0 || temp >= 0x10000 ) {
            LnkMsg( LOC+ERR+MSG_FIXUP_OFF_RANGE, "a", &fix->loc_addr );
        }
    } else if( fix->type == FIX_OFFSET_21 ) {
        CheckPartialRange( fix, off, 0x001FFFFF, 0x00100000 );
    } else if( fix->type == FIX_OFFSET_24 ) {   // NYI: repair PPC damage here
        CheckPartialRange( fix, off, 0x03FFFFFF, 0x02000000 );
    }
    PatchOffset( fix, off, TRUE );
    fix->os2_selfrel = FmtData.type & MK_OS2_LX && FmtData.u.os2.gen_rel_relocs;
    return !(fix->os2_selfrel || fix->type & FIX_ABS);
}

static offset FindRealAddr( fix_data *fix )
/*****************************************/
{
    group_entry *group;
    offset      off;
    bool        dbiflat;

    off = fix->tgt_addr.off;
    dbiflat = DBINoReloc( CurrRec.seg->u.leader->dbgtype );
    if( fix->type & FIX_ABS
                || (dbiflat && !(CurrMod->modinfo & MOD_FLATTEN_DBI)) ) {
        return off;
    }
    if( FmtData.type & (MK_OS2_FLAT|MK_LINEARIZE|MK_QNX_FLAT)
                && !(fix->type & FIX_SEC_REL) ) {
        if( FmtData.type & MK_OS2_LE && !dbiflat ) return off;
       /*
            put the correct value in so that internal fixups
            don't have to be applied if everything loads in the
            right spot.
        */
        group = FindGroup( fix->tgt_addr.seg );
        if( group == NULL ) return off;         // can happen with dbi relocs
        off += (group->linear - group->grp_addr.off);
        if( FmtData.type & MK_LINEARIZE ) {
            if( !(fix->type & FIX_NO_BASE) ) {
                off += FmtData.base;
            }
            if( dbiflat ) {     // want dbi addresses relative to 0
                off -= Groups->linear;
            }
        }
        if( dbiflat ) {
            off -= FmtData.base;
        }
    }
    return( off );
}

static void PatchData( fix_data *fix )
/************************************/
{
    byte *      data;
    segment     segval;
    bool        isdbi;

    data = fix->data;
    fix->additive = FALSE;
    if( fix->imported && (FmtData.type & MK_OS2_FLAT) ) {
        fix->value = fix->tgt_addr.off;
    } else {
        fix->value = 0;
    }
    switch( fix->type & FIX_OFFSET_MASK ) {
    case FIX_OFFSET_8:
        fix->value += GET_U8( data );
        break;
    case FIX_OFFSET_16:
        fix->value += GET_U16( data );
        break;
    case FIX_OFFSET_32:
        fix->value += GET_U32( data );
        break;
    }
    if( fix->value != 0 ) fix->additive = TRUE;
    if( fix->type & FIX_REL ) return;
    isdbi = DBINoReloc( CurrRec.seg->u.leader->dbgtype );
    if( fix->imported ) {
        if( isdbi ) {
            fix->tgt_addr.off = 0;      // crazy person has imports in the dbi
            fix->tgt_addr.seg = 0;
        } else {
            return;
        }
    }
    if( (fix->type & FIX_ABS && !(FmtData.type & MK_QNX)) || isdbi ) {
        fix->done = TRUE;
    }
    if( !(fix->type & FIX_BASE) ) {     // it's offset only
        if( !((FmtData.type & MK_WINDOWS) && fix->type & FIX_LOADER_RES) ) {
            PatchOffset( fix, FindRealAddr( fix ), FALSE );
            if( !(FmtData.type & (MK_ELF|MK_QNX|MK_PE|MK_OS2_FLAT|MK_NOVELL|MK_PHAR_REX))
                || (FmtData.type & MK_OS2_LX && !FmtData.u.os2.gen_int_relocs) ){
                fix->done = TRUE;
            }
        }
    } else {    // its a seg reloc and maybe an offset as well.
        if( (fix->type & FIX_OFFSET_MASK) != FIX_NO_OFFSET ) {
            if( !fix->done && (FmtData.type & MK_OS2) ) return;
            PatchOffset( fix, FindRealAddr( fix ), FALSE );
            data += OffsetSizes[ FIX_GET_OFFSET(fix->type) ];
        }
        if( FmtData.type & MK_PROT_MODE ) {
            PUT_U16( data, 0 );
        }
        if( FmtData.type & MK_PHAR_MULTISEG ) {
            PUT_U16( data, fix->tgt_addr.seg );
        } else if( fix->done || (FmtData.type & (MK_QNX | MK_DOS) ) ) {
            if( isdbi && LinkFlags & CV_DBI_FLAG ) {    // FIXME
                segval = FindGroupIdx( fix->tgt_addr.seg );
            } else {
                segval = GET_U16( data ) + fix->tgt_addr.seg;
            }
            PUT_U16( data, segval );
        }
    }
}

// NYI: re-enable far call optimization some time.  Problem is with
// the manipulation of the stored code
#if 0
#define FAR_CALL_ID     0x9A
#define FAR_JMP_ID      0xEA
#define NOP_ID          0x90
#define SS_OVERRIDE     0x36
#define CS_OVERRIDE     0x3e
#define PUSHCS_ID       0x0e
#define NEAR_CALL_ID    0xe8
#define NEAR_JMP_ID     0xE9
#define MOV_AXAX_ID     0xC089

static bool FarCallOpt( fix_data *fix )
/*************************************/
{
    byte *      code;
    unsigned_16 temp16;
    unsigned_32 temp32;
    byte        instruction;
    bool        is32bit;

/*
 * the sequence of instructions NOP  PUSH CS (near)CALL offset is much
 * faster than (far)CALL segment:offset. So whenever a far call ends up in
 * the same segment as the thing that it is calling, replace the far call
 * with the near call sequence. Note this can potentially wreck jump tables,
 * so rely on the code generator to say when it is safe to do so.
 * this also positions the call so that it returns on an even address
 * to make things go slightly faster. This uses segment overrides rather than
 * NOP's where possible since they are faster, and if there are two far
 * calls in a row, it detects this and uses segment overrides on both the
 * push and the call to avoid the pair of NOP's
 * this also replaces far JMP's with (near) JMP MOV AX,AX
 */
    if( fix->type & FIX_UNSAFE ) return FALSE;
    if( fix->imported ) return FALSE;
    if( fix->type & FIX_ABS ) return FALSE;
    if( fix->type == FIX_BASE_OFFSET_16 ) {
        is32bit = FALSE;
    } else if( fix->type == FIX_BASE_OFFSET_32 ) {
        is32bit = TRUE;
    } else {
        return FALSE;
    }
    if( fix->data == CurrRec.buffer ) return( FALSE );  can we assume this?
    if( fix->loc_addr.seg != fix->tgt_addr.seg ) return( FALSE );
    if( !CurrRec.seg->canfarcall ) return( FALSE );
    code = fix->data - 1;
    instruction = GET_U8( code );
    if( instruction == FAR_CALL_ID || instruction == FAR_JMP_ID ) {
        if( is32bit ) {
            temp32 = GET_U32( code + 1 );
        } else {
            temp16 = GET_U16( code + 1 );
        }
        if( FmtData.type & MK_OS2 ) {
            if( is32bit ) {
                temp32 += fix->tgt_addr.off;     // haven't done this for OS/2
            } else {
                temp16 += fix->tgt_addr.off;     // haven't done this for OS/2
            }
        }
        if( instruction == FAR_JMP_ID ) {
            PUT_U8(  code    , NEAR_JMP_ID );
            if( is32bit ) {
                temp32 -= fix->loc_addr.off + 4;   //fix the offset
                PUT_U32( code + 1, temp32 );
                PUT_U16( code + 5, MOV_AXAX_ID );
            } else {
                temp16 -= fix->loc_addr.off + 2;   //fix the offset
                PUT_U16( code + 1, temp16 );
                PUT_U16( code + 3, MOV_AXAX_ID );
            }
        } else {
            PUT_U8( code, PUSHCS_ID );
            if( is32bit ) {
                temp32 -= fix->loc_addr.off + 6; //fix the offset
            } else {
                temp16 -= fix->loc_addr.off + 4; //fix the offset
            }
            if( fix->loc_addr.off & 0x1 ) {  // odd address, so put nop last
                PUT_U8( code + 1, NEAR_CALL_ID );
                if( is32bit ) {
                    PUT_U8( code + 6, NOP_ID );
                    temp32 += 1;            // adjust for different call loc.
                } else {
                    PUT_U8( code + 4, NOP_ID );
                    temp16 += 1;            // adjust for different call loc.
                }
                code -= 1;
                LastOptimized = fix->loc_addr.off;
                LastOptType = fix->type;
            } else {
                if( (LastOptType == FIX_BASE_OFFSET_16 && fix->loc_addr.off >= 5
                        && LastOptimized == fix->loc_addr.off - 5)
                 || (LastOptType == FIX_BASE_OFFSET_32 && fix->loc_addr.off >= 7
                        && LastOptimized == fix->loc_addr.off - 7) ) {
                    PUT_U8( code - 1, SS_OVERRIDE );
                }
                PUT_U8( code + 1, CS_OVERRIDE );
                PUT_U8( code + 2, NEAR_CALL_ID );
            }
            if( is32bit ) {
                PUT_U32( code + 3, temp32 );
            } else {
                PUT_U16( code + 3, temp16 );
            }
        }
        return( TRUE );
    }
    return( FALSE );
}
#endif

static void MakeBase( fix_data *fix )
/***********************************/
{
    unsigned size;

    if( fix->type & FIX_BASE ) {
        size = OffsetSizes[ FIX_GET_OFFSET(fix->type) ];
        fix->loc_addr.off += size;
    }
}

/* 00h = Byte fixup (8-bits).
   01h = (undefined).
   02h = 16-bit Selector fixup (16-bits).
   03h = 16:16 Pointer fixup (32-bits).
   04h = (undefined).
   05h = 16-bit Offset fixup (16-bits).
   06h = 16:32 Pointer fixup (48-bits).
   07h = 32-bit Offset fixup (32-bits).
*/

static byte OS2OffsetFixTypeMap[] = { 1, 0, 5, 1, 7, 1};
static byte OS2SegmentedFixTypeMap[] = { 2, 1, 3, 1, 6, 1};

static unsigned MapOS2FixType( unsigned type )
/********************************************/
{
    unsigned    off;

    off = FIX_GET_OFFSET(type);
    if( type & FIX_BASE ) {
        return OS2SegmentedFixTypeMap[ off ];
    }
    return OS2OffsetFixTypeMap[ off ];
}

static void FmtReloc( fix_data *fix, frame_spec *tthread )
/********************************************************/
{
    offset              off;
    base_reloc          new_reloc;
    targ_addr           targ;
    group_entry *       grp;
    segdata *           seg;
    bool                save;
    byte *              fixptr;
    dll_sym_info *      dll;
    bool                freedll;
    fix_type            ftype;

    if( fix->done ) return;
    if( fix->type & FIX_ABS && !(FmtData.type & MK_QNX)
                             && !fix->imported ) return;
    ftype = fix->type & (FIX_OFFSET_MASK | FIX_BASE);
    if( FmtData.type & (MK_PHAR_SIMPLE|MK_PHAR_FLAT)
        || ((FmtData.type & (MK_NOVELL|MK_ELF)) && (ftype != FIX_OFFSET_32))
        || (FmtData.type & MK_PE  && (ftype & FIX_BASE || ftype == FIX_OFFSET_8
                                || ftype == FIX_HIGH_OFFSET_8))
        || (FmtData.type & MK_PHAR_REX &&
              (ftype != FIX_OFFSET_16 && ftype != FIX_OFFSET_32)) ) {
        LnkMsg( LOC+ERR+MSG_INVALID_FLAT_RELOC, "a", &fix->loc_addr );
        return;
    }
    if( !(LinkState & MAKE_RELOCS) ) return;
    if( FmtData.type & MK_QNX ) {
        if( ftype == FIX_OFFSET_32 ) {
            if( !FmtData.u.qnx.gen_linear_relocs ) return;
        } else if( ftype == FIX_BASE || ftype == FIX_BASE_OFFSET_16 ) {
            if( !FmtData.u.qnx.gen_seg_relocs ) return;
        } else if( ftype != FIX_BASE_OFFSET_32 ) {
            return;
        }
    }
    if( fix->type & FIX_HIGH && !(FmtData.type & MK_PE) ) {
        LnkMsg( LOC+ERR+MSG_BAD_RELOC_TYPE, NULL );
        return;
    }
    DEBUG(( DBG_OLD, "relocation record being output" ));
    save = TRUE;                /* NOTE: copycat code in QNX section ! */
    InitReloc( &new_reloc );
    new_reloc.fix_size = CalcFixupSize( fix->type );
    new_reloc.fix_off = fix->loc_addr.off;
    off = fix->loc_addr.off;
    seg = CurrRec.seg;
    targ = fix->tgt_addr;
    if( FmtData.type & MK_PE ) {
        unsigned_32     reltype;

        off += seg->u.leader->group->linear;
        if( fix->type & FIX_HIGH ) {
            reltype = PE_FIX_HIGHADJ;   // NYI: can be high when objalign ==
            new_reloc.rel_size = sizeof(high_pe_reloc_item);    // 0x10000
            new_reloc.item.hpe.low_off = (unsigned_16) targ.off;
        } else if( ftype == FIX_OFFSET_16 ) {
            if( !(FmtData.objalign & 0xFFFF) ) {
                save = FALSE;
            }
            reltype = PE_FIX_LOW;
        } else {
            reltype = PE_FIX_HIGHLOW;
        }
        new_reloc.item.pe = (off & OSF_PAGE_MASK) | reltype;
    } else if( FmtData.type & MK_OS2_16BIT ) {
        os2_reloc_item * os2item;

        fixptr = fix->data;
        os2item = &new_reloc.item.os2;
        os2item->addr_type = MapOS2FixType( fix->type );
        os2item->reloc_offset = off - seg->u.leader->group->grp_addr.off;
        if( !fix->imported ) {
            os2item->reloc_type = INTERNAL_REFERENCE;
            os2item->put.internal.rsrvd = 0;
            for( grp = Groups; grp != NULL; grp = grp->next_group ) {
                if( grp->grp_addr.seg == targ.seg ) break;
            }
            if( grp != NULL && grp->segflags & SEG_MOVABLE ) {
                os2item->put.internal.grp_num = (signed_8)MOVABLE_ENTRY_PNT;
                os2item->put.internal.off = FindEntryOrdinal( targ, grp );
            } else {
                os2item->put.internal.grp_num = targ.seg;
                os2item->put.internal.off = targ.off;
            }
        } else {
            dll = tthread->u.sym->p.import;
            if( !dll->isordinal ) {
                os2item->reloc_type = IMPORTED_NAME;
                os2item->put.name.impnam_off = dll->u.entry->num;
                os2item->put.name.modref_idx = dll->m.modnum->num;
            } else {
                os2item->reloc_type = IMPORTED_ORDINAL;
                os2item->put.ordinal.ord_num = dll->u.ordinal;
                os2item->put.ordinal.modref_idx = dll->m.modnum->num;
            }
        }
        if( fix->additive ) {
            os2item->reloc_type |= ADDITIVE;
        } else {
            PUT_U16( fixptr, 0xffff );          // end of chain indicator
        }
    } else if( FmtData.type & MK_OS2_FLAT )  {
        segdata *targseg;
        byte    flags;
        byte    fixtype;

        fixptr = new_reloc.item.os2f.buff;
        freedll = FALSE;
        dll = NULL;
        if( fix->type & FIX_REL ) {
            fixtype = OSF_32BIT_SELF_REL;
            if( fix->os2_selfrel && tthread->type & FIX_FRAME_EXT ) {
                freedll = FindOS2ExportSym( tthread->u.sym, &dll );
                if( dll != NULL ) fix->imported = TRUE;
            }
        } else {
            fixtype = MapOS2FixType( fix->type );
        }
        targseg = GetFrameSegData( tthread );
        if( targseg != NULL && !targseg->is32bit ) {
            switch( fixtype ) {
            case 2:     // 16-bit selector
            case 6:     // 16:32 pointer
                if( FIX_GET_FRAME(fix->type) == FIX_FRAME_FLAT ) break;
            case 3:     // 16:16 pointer           NOTE the fall through
                fixtype |= OSF_FIXUP_TO_ALIAS;  // YET more fall through
            case 5:     // 16-bit offset
                for( grp = Groups; grp != NULL; grp = grp->next_group ) {
                    if( grp->grp_addr.seg == targ.seg ) break;
                }
                if( grp != NULL ) {
                    grp->u.miscflags |= SEG_16_ALIAS;
                }
                break;
            }
        }
    // ALWAYS set the alias flag for 16:16 pointers!
    if (fixtype == 3)
        fixtype |= OSF_FIXUP_TO_ALIAS;

        PUT_U8( fixptr, fixtype );
        flags = 0;
        fixptr += 2;       /* skip flags for now */
        grp = seg->u.leader->group;
        PUT_U16( fixptr, (fix->loc_addr.off-grp->grp_addr.off) & OSF_PAGE_MASK);
        fixptr += 2;
        if( !fix->imported ) {
            if( !fix->os2_selfrel ) {
                targ.off += fix->value;
            }
            flags = INTERNAL_REFERENCE;
            if( targ.seg > 0xFF ) {
                flags |= OSF_OBJMOD_16BITS;
                PUT_U16( fixptr, targ.seg );
                fixptr += 1;
            } else {
                PUT_U8( fixptr, targ.seg );
            }
            fixptr += 1;
            grp = FindGroup( targ.seg );
            targ.off -= grp->grp_addr.off;
            if( ftype != FIX_BASE ) {
                if( targ.off > 0xFFFF ) {
                    flags |= OSF_TARGOFF_32BITS;
                    PUT_U32( fixptr, targ.off );
                    fixptr += 2;
                } else {
                    PUT_U16( fixptr, targ.off );
                }
                fixptr += 2;
            }
        } else {
            if( dll == NULL ) {
                dll = tthread->u.sym->p.import;
            }
            if( !dll->isordinal ) {
                flags = IMPORTED_NAME;
            } else {
                flags = IMPORTED_ORDINAL;
            }
            if( dll->m.modnum == NULL ) {
                PUT_U8( fixptr, 0 );
            } else if( dll->m.modnum->num > 0xFF ) {
                flags |= OSF_OBJMOD_16BITS;
                PUT_U16( fixptr, dll->m.modnum->num );
                fixptr += 1;
            } else {
                PUT_U8( fixptr, dll->m.modnum->num );
            }
            fixptr += 1;
            if( !dll->isordinal ) {
                if( dll->u.entry->num > 0xFFFF ) {
                    flags |= OSF_TARGOFF_32BITS;
                    PUT_U32( fixptr, dll->u.entry->num );
                    fixptr += 3;
                } else {
                    PUT_U16( fixptr, dll->u.entry->num );
                    fixptr += 1;
                }
            } else if( dll->u.ordinal > 0xFF ) {
                PUT_U16( fixptr, dll->u.ordinal );
                fixptr += 1;
            } else {
                flags |= OSF_IMPORD_8BITS;
                PUT_U8( fixptr, dll->u.ordinal );
            }
            fixptr += 1;
            if( fix->additive ) {
                flags |= OSF_ADDITIVE;
                switch( fix->type & FIX_OFFSET_MASK ) {
                case FIX_OFFSET_8:
                    PUT_U8( fix->data, 0 );
                    break;
                case FIX_OFFSET_16:
                    PUT_U16( fix->data, 0 );
                    break;
                case FIX_OFFSET_32:
                    PUT_U32( fix->data, 0 );
                    break;
                }
                if( fix->value > 0x7fff ) {
                    flags |= OSF_ADDITIVE32;
                    PUT_U32( fixptr, fix->value );
                    fixptr += 2;
                } else {
                    PUT_U16( fixptr, fix->value );
                }
                fixptr += 2;
            }
        }
        if( freedll ) _LnkFree( dll );
        new_reloc.rel_size = fixptr - new_reloc.item.os2f.buff;
        new_reloc.item.os2f.fmt.nr_flags = flags;
    } else if( FmtData.type & MK_NOVELL ) {
        if( fix->imported ) {
            save = FALSE;
            AddNovImpReloc( tthread->u.sym, off, (fix->type & FIX_REL) != 0,
                             fix->loc_addr.seg == DATA_SEGMENT );
        } else {
            if( fix->loc_addr.seg != DATA_SEGMENT ) {
                off |= NOV_OFFSET_CODE_RELOC;
            }
            if( targ.seg != DATA_SEGMENT ) {
                off |= NOV_TARGET_CODE_RELOC;
            }
            new_reloc.item.novell.reloc_offset = off;
        }
    } else if( FmtData.type & MK_QNX ) {
        bool    done;

        done = FALSE;
        if( ftype == FIX_OFFSET_32 || ftype == FIX_BASE_OFFSET_32 ) {
            if( FmtData.u.qnx.gen_linear_relocs ) {
                new_reloc.isqnxlinear = TRUE;
                new_reloc.item.qnxl.reloc_offset = fix->loc_addr.off;
                seg = GetFrameSegData( tthread );
                if( seg->iscode ) {
                    new_reloc.item.qnxl.reloc_offset |= 0x80000000;
                }
                if( fix->type & FIX_ABS && fix->type & FIX_REL ) {
                    new_reloc.item.qnxl.reloc_offset |= 0x40000000;
                }
                if( fix->type == FIX_BASE_OFFSET_32 ) {
                    DumpReloc( &new_reloc );
                    InitReloc( &new_reloc );
                    new_reloc.fix_size = CalcFixupSize( fix->type );
                    new_reloc.fix_off   = fix->loc_addr.off;
                } else {
                    done = TRUE;
                }
            }
        }
        if( !done ) {
            MakeBase( fix );
            new_reloc.item.qnx.reloc_offset = fix->loc_addr.off;
            new_reloc.item.qnx.segment = ToQNXIndex( fix->loc_addr.seg );
        }
    } else if( FmtData.type & MK_ELF ) {
        symbol *sym;

        if( fix->type & FIX_REL ) {
            new_reloc.item.elf.info = R_386_PC32;
        } else {
            new_reloc.item.elf.info = R_386_32;
        }
        if( tthread->type & FIX_FRAME_EXT && IsSymElfImpExp(tthread->u.sym) ) {
            sym = tthread->u.sym;
            new_reloc.item.elf.addend = 0;
        } else {
            seg = GetFrameSegData( tthread );
            if( seg == NULL ) {
                save = FALSE;
            } else {
                grp = seg->u.leader->group;
                sym = grp->sym;
                new_reloc.item.elf.addend = targ.off - grp->grp_addr.off;
            }
        }
        if( save ) {
            new_reloc.item.elf.info |= FindElfSymIdx( sym ) << 8;
            new_reloc.item.elf.reloc_offset = off;
        }
    } else if( FmtData.type & MK_PHAR_REX ) {
        if( ftype == FIX_OFFSET_32 ) {
            off |= 0x80000000;
        }
        new_reloc.item.rex.reloc_offset = off;
    } else if( FmtData.type & MK_COM ) {
        save = FALSE;
        LnkMsg( LOC+WRN+MSG_SEG_RELOC_OUT, "a", &fix->loc_addr );
    } else if( FmtData.type & MK_PHAR_MULTISEG ) {
        MakeBase( fix );
        new_reloc.item.pms.offset = fix->loc_addr.off;
        grp = seg->u.leader->group;
        new_reloc.item.pms.segment = grp->grp_addr.seg;
    } else {
        MakeBase( fix );
        new_reloc.item.dos.addr.off = fix->loc_addr.off;
        grp = seg->u.leader->group;
        new_reloc.item.dos.addr.seg = grp->grp_addr.seg;
        if( grp->section != Root ) {
            new_reloc.item.dos.addr.seg -= grp->section->sect_addr.seg;
        }
    }
    if( save ) {
        DumpReloc( &new_reloc );
    }
}

static void Relocate( fix_data *fix, frame_spec *targ )
/*****************************************************/
{
    fix->done = FALSE;
    fix->os2_selfrel = FALSE;
    if( (FmtData.type & MK_PE) && fix->imported ) {
        /*
            Under PE, the imported symbol address is set to the
            transfer code (JMP [xxxxx]) that is generated by the linker.
        */
        fix->tgt_addr = targ->u.sym->addr;
        fix->imported = FALSE;
    }
    if( CheckSpecials( fix, targ ) ) return;
    PatchData( fix );
//  if( FarCallOpt( fix, targ ) ) return;       NYI
    FmtReloc( fix, targ );
}
