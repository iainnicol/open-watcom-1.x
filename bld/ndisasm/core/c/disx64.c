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
* Description:  Instruction decoding for AMD64 architecture.
*
****************************************************************************/


#include <string.h>
#include <ctype.h>
#include "distypes.h"
#include "dis.h"
#include <stdio.h>

extern long SEX( unsigned long v, unsigned bit );

#pragma disable_message ( 202 )

extern const dis_range          X64RangeTable[];
extern const int                X64RangeTablePos[];
extern const unsigned char      X64MaxInsName;
extern const dis_ins_descript   DisInstructionTable[];
extern const unsigned short     DisRefTypeTable[];

typedef union {
    unsigned_8 full;
    struct {
        unsigned_8  base  : 3;
        unsigned_8  index : 3;
        unsigned_8  scale : 2;
    } split;
} SIB;

typedef union {
    unsigned_8 full;
    struct{
        unsigned_8  b     : 1;
        unsigned_8  x     : 1;
        unsigned_8  r     : 1;
        unsigned_8  w     : 1;
        unsigned_8  pr    : 4;
    } split;
} REX;

//#define PREFIX_MASK ( DIF_X64_REPNE | DIF_X64_REPE | DIF_X64_OPND_SIZE | DIF_X64_REX_B | DIF_X64_REX_R | DIF_X64_REX_W | DIF_X64_REX_X )

#define PREFIX_MASK ( DIF_X64_OPND_SIZE | DIF_X64_ADDR_SIZE | DIF_X64_REX_B | DIF_X64_REX_R | DIF_X64_REX_W | DIF_X64_REX_X | DIF_X64_PEX_PR )

//#define X64XMMResetPrefixes() ins->flags &= ~PREFIX_MASK

// for REX prefix decoding
#define X64_EXTENDED_REG_OFFSET     8

/*=====================================================================*/
/*                        ENUMERATED TYPES                             */
/*=====================================================================*/
typedef enum {
    MOD_0 = 0x0,
    MOD_1 = 0x1,
    MOD_2 = 0X2,
    MOD_3 = 0X3
} MOD;

typedef enum {
    RM_0 = 0x0,
    RM_1 = 0x1,
    RM_2 = 0X2,
    RM_3 = 0X3,
    RM_4 = 0x4,
    RM_5 = 0X5,
    RM_6 = 0X6,
    RM_7 = 0X7,
    RM_8 = 0x8,
    RM_9 = 0x9,
    RM_A = 0xA,
    RM_B = 0xB,
    RM_C = 0xC,
    RM_D = 0xD,
    RM_E = 0xE,
    RM_F = 0xF,
    
    REG_RAX = 0x0,
    REG_RCX = 0x1,
    REG_RDX = 0x2,
    REG_RBX = 0x3,
    REG_RSP = 0x4,
    REG_RBP = 0x5,
    REG_RSI = 0x6,
    REG_RDI = 0x7,
    REG_R8  = 0x8,
    REG_R9  = 0x9,
    REG_R10 = 0xA,
    REG_R11 = 0xB,
    REG_R12 = 0xC,
    REG_R13 = 0xD,
    REG_R14 = 0xE,
    REG_R15 = 0xF,
    REG_RIP = 0x10,     // Special value for RIP-Relative addresing

    REG_ES  = 0x0,
    REG_CS  = 0x1,
    REG_SS  = 0x2,
    REG_DS  = 0x3,
    REG_FS  = 0x4,
    REG_GS  = 0x5,

    REG_CR0 = 0x0,
    REG_CR2 = 0X2,
    REG_CR3 = 0X3,
    REG_CR4 = 0X4,
    REG_DR0 = 0X0,
    REG_DR1 = 0x1,
    REG_DR2 = 0x2,
    REG_DR3 = 0x3,
    REG_DR6 = 0x6,
    REG_DR7 = 0x7,
    REG_TR3 = 0x3,
    REG_TR4 = 0x4,
    REG_TR5 = 0x5,
    REG_TR6 = 0x6,
    REG_TR7 = 0x7,
} RM;

typedef enum {
    SC_0 = 0x0,
    SC_1 = 0x1,
    SC_2 = 0X2,
    SC_3 = 0X3
} SCALE;

typedef enum {
    W_DEFAULT = 0x1,
    W_FULL    = 0x1,    // Full Size Operand
    W_BYTE    = 0x0     // Byte Size Operand
} WBIT;

typedef enum {
    RW_64BIT     = 0x0,
    RW_32BIT     = 0x1,
    RW_16BIT     = 0x2,
    RW_8BIT      = 0x3,
    RW_DEFAULT   = RW_64BIT
} REGWIDTH;

typedef enum {
    S_DEFAULT = 0x0,
    S_FULL    = 0x0,    // Full Mode for Immediate Value Fetch
    S_BYTE    = 0x1     // Byte Mode for Immediate Value Fetch
} SBIT;

typedef enum {
    D_RM_REG = 0x0,     // normal operand order r/m is first and reg is second
    D_REG_RM = 0x1      // reverse operand order reg is first and r/m is second
} DBIT;

typedef enum {
    MF_0 = 0x0,
    MF_1 = 0x1,
    MF_2 = 0x2,
    MF_3 = 0X3
} MF_BITS;

typedef enum {
    FB    = 0x0,
    FE    = 0x1,
    FBE   = 0x2,
    FU    = 0x3,
} COND;

/*=====================================================================*/
/*                FUNCTIONS TO FETCH BYTE/WORD/DWORD                   */
/*=====================================================================*/



static unsigned_8 GetUByte( void *d, unsigned off )
/**************************************************
 * Get Unsigned Byte
 */
{
    unsigned_8  data;

    //NYI: have to error check return code
    DisCliGetData( d, off, sizeof( data ), &data );
    return( data );
}

static unsigned_16 GetUShort( void *d, unsigned off )
/****************************************************
 * Get Unsigned Word ( 2 bytes )
 */
{
    struct {
        unsigned_8 lo;
        unsigned_8 hi;
    }   data;

    //NYI: have to error check return code
    DisCliGetData( d, off, sizeof( data ), &data );
    return( ( data.hi << 8 ) | data.lo );
}

static unsigned_32 GetULong( void *d, unsigned off )
/***************************************************
 * Get Double Word
 */
{
    struct {
        unsigned_8 lo;
        unsigned_8 mid_lo;
        unsigned_8 mid_hi;
        unsigned_8 hi;
    }   data;

    //NYI: have to error check return code
    DisCliGetData( d, off, sizeof( data ), &data );
    return( ( (unsigned long)data.hi << 24 )
        |   ( (unsigned long)data.mid_hi << 16 )
        |   ( data.mid_lo << 8 )
        |    data.lo );
}


static int GetSByte( void *d, unsigned off )
/*******************************************
 * Get Signed Byte
 */
{
    return( SEX( GetUByte( d, off ), 7 ) );
}

static int GetSShort( void *d, unsigned off )
/********************************************
 * Get Signed Word
 */
{
    return( SEX( GetUShort( d, off ), 15 ) );
}



/*=====================================================================*/
/*                PREFIX HANDLERS                                      */
/*=====================================================================*/


dis_handler_return X64PrefixOpnd( dis_handle *h, void *d, dis_dec_ins *ins )
/***************************************************************************
 * Operand Size Override
 */
{
    ins->size += 1;
    
    // if REX.W set then ignore 66h prefix
    // if REX.W clear then instruction size is 16-Bit!
    if( (ins->flags & DIF_X64_REX_W) == 0)
        ins->flags |= DIF_X64_OPND_SIZE;
        
    return( DHR_CONTINUE );
}

dis_handler_return X64PrefixRex( dis_handle *h, void *d, dis_dec_ins *ins )
/***************************************************************************
 * Extended Register Override
 */
{
    REX rex_pr;
        
    rex_pr.full = GetUByte( d, ins->size );
    ins->size += 1;
    
    
    // Clear all REX stuff (to be sure)
    ins->flags &= ~( DIF_X64_REX_B | DIF_X64_REX_X | DIF_X64_REX_R | DIF_X64_REX_W | DIF_X64_PEX_PR );
    
    // REX.B is an extension to the ModRM's SIB base field
    if(rex_pr.split.b)
        ins->flags |= DIF_X64_REX_B;

    // REX.X is an extension to the ModRM's SIB index field
    if(rex_pr.split.x)
        ins->flags |= DIF_X64_REX_X;
    
    // REX.R is an extension to the ModRM's Register field
    if(rex_pr.split.r)
        ins->flags |= DIF_X64_REX_R;

    // REX.W is an operand size prefix (like 66h)
    //  if 1 then use 64-Bit operand size
    //  if 0 then use default operand size
    if(rex_pr.split.w)
        ins->flags |= DIF_X64_REX_W;
    
    // Flag REX prefix, sometime useful...
    ins->flags |= DIF_X64_PEX_PR;
    
    return( DHR_CONTINUE );
}

dis_handler_return X64PrefixCS( dis_handle *h, void *d, dis_dec_ins *ins )
/*************************************************************************
 * CS Segment Override
 */
{
    ins->size += 1;
    ins->flags |= DIF_X64_CS;
    return( DHR_CONTINUE );
}
dis_handler_return X64PrefixFS( dis_handle *h, void *d, dis_dec_ins *ins )
/*************************************************************************
 * FS Segment Override
 */
{
    ins->size += 1;
    ins->flags |= DIF_X64_FS;
    return( DHR_CONTINUE );
}

dis_handler_return X64PrefixGS( dis_handle *h, void *d , dis_dec_ins *ins )
/**************************************************************************
 * GS Segment Override
 */
{
    ins->size += 1;
    ins->flags |= DIF_X64_GS;
    return( DHR_CONTINUE );
}


//dis_handler_return X64PrefixFwait( dis_handle *h, void *d, dis_dec_ins *ins )
/****************************************************************************
 * FWait
 */
/*{
    unsigned    code;
    unsigned    instruct_size;

    ins->size += 1;
    instruct_size = ins->size;

    for( ;; ) {
        code = GetUByte( d, instruct_size );
        if( ( code & 0xf8 ) == 0xd8 ) break;
        // Look Ahead for Prefixes
        switch( code ) {
        case 0x67:
        case 0x66:
        case 0x2e:
        case 0x3e:
        case 0x26:
        case 0x64:
        case 0x65:
        case 0x36:
            break;
        default:
            // A non-floating point instruction is found so quit
            ins->num_ops = 0;
            ins->type = DI_X64_fwait;
            return( DHR_DONE );
        }
        ++instruct_size;
    }
    ins->flags ^= DIF_X64_FWAIT;
    return( DHR_CONTINUE );
}*/

dis_handler_return X64PrefixAddr( dis_handle *h, void *d, dis_dec_ins *ins )
/***************************************************************************
 * Address Size Override
 */
{
    ins->size += 1;
    
    if( ( ins->flags & DIF_X64_ADDR_SIZE ) == 0 )
        ins->flags |= DIF_X64_ADDR_SIZE;
    
    return( DHR_CONTINUE );
}

//dis_handler_return X64PrefixRepe( dis_handle *h, void *d, dis_dec_ins *ins )
/***************************************************************************
 * REP/REPE/REPZ Override
 */
/*{
    ins->size += 1;
    ins->flags |= DIF_X64_REPE;
    return( DHR_CONTINUE );
}
*/

//dis_handler_return X64PrefixRepne( dis_handle *h, void *d, dis_dec_ins *ins )
/****************************************************************************
 * REPNE/REPNZ
 */
/*{
    ins->size += 1;
    ins->flags |= DIF_X64_REPNE;
    return( DHR_CONTINUE );
}
*/

//dis_handler_return X64PrefixLock( dis_handle *h, void *d, dis_dec_ins *ins )
/***************************************************************************
 * Lock Prefix
 */
/*{
    ins->size += 1;
    ins->flags |= DIF_X64_LOCK;
    return( DHR_CONTINUE );
}*/


dis_handler_return X64PrefixSS( dis_handle *h, void *d, dis_dec_ins *ins )
/*************************************************************************
 * SS Segment Override
 */
{
    ins->size += 1;
    ins->flags |= DIF_X64_SS;
    return( DHR_CONTINUE );
}

dis_handler_return X64PrefixDS( dis_handle *h, void *d, dis_dec_ins *ins )
/*************************************************************************
 * DS Segment Override
 */
{
    ins->size += 1;
    ins->flags |= DIF_X64_DS;
    return( DHR_CONTINUE );
}

dis_handler_return X64PrefixES( dis_handle *h, void *d, dis_dec_ins *ins )
/*************************************************************************
 * ES Segment Override
 */
{
    ins->size += 1;
    ins->flags |= DIF_X64_ES;
    return( DHR_CONTINUE );
}



/*=====================================================================*/
/*                UTILITY FUNCTIONS                                    */
/*=====================================================================*/

/*
 * Returns true if a segment override prefix has been encountered
 */
#define SEGOVER ( DIF_X64_CS | DIF_X64_FS | DIF_X64_GS | DIF_X64_DS | DIF_X64_ES | DIF_X64_SS )
#define X64SegmentOverride( ins )       ( (ins)->flags & SEGOVER )


dis_register X64GetRegister_Q( REGWIDTH rw, RM reg, dis_dec_ins *ins )
{
    switch( reg ) {
    case REG_RAX: return( DR_X64_rax );
    case REG_RCX: return( DR_X64_rcx );
    case REG_RDX: return( DR_X64_rdx );
    case REG_RBX: return( DR_X64_rbx );
    case REG_RSP: return( DR_X64_rsp );
    case REG_RBP: return( DR_X64_rbp );
    case REG_RSI: return( DR_X64_rsi );
    case REG_RDI: return( DR_X64_rdi );
    case REG_R8: return( DR_X64_r8 );
    case REG_R9: return( DR_X64_r9 );
    case REG_R10: return( DR_X64_r10 );
    case REG_R11: return( DR_X64_r11 );
    case REG_R12: return( DR_X64_r12 );
    case REG_R13: return( DR_X64_r13 );
    case REG_R14: return( DR_X64_r14 );
    case REG_R15: return( DR_X64_r15 );
    case REG_RIP: return( DR_X64_rip );
    default:     return( DR_NONE );
    }
}

dis_register X64GetRegister_D( REGWIDTH rw, RM reg, dis_dec_ins *ins )
{
    switch( reg ) {
    case REG_RAX: return( DR_X64_eax );
    case REG_RCX: return( DR_X64_ecx );
    case REG_RDX: return( DR_X64_edx );
    case REG_RBX: return( DR_X64_ebx );
    case REG_RSP: return( DR_X64_esp );
    case REG_RBP: return( DR_X64_ebp );
    case REG_RSI: return( DR_X64_esi );
    case REG_RDI: return( DR_X64_edi );
    case REG_R8:  return( DR_X64_r8d );
    case REG_R9:  return( DR_X64_r9d );
    case REG_R10: return( DR_X64_r10d );
    case REG_R11: return( DR_X64_r11d );
    case REG_R12: return( DR_X64_r12d );
    case REG_R13: return( DR_X64_r13d );
    case REG_R14: return( DR_X64_r14d );
    case REG_R15: return( DR_X64_r15d );
    case REG_RIP: return( DR_X64_eip );
    default:     return( DR_NONE );
    }
}

dis_register X64GetRegister_W( REGWIDTH rw, RM reg, dis_dec_ins *ins )
{
    switch( reg ) {
    case REG_RAX: return( DR_X64_ax );
    case REG_RCX: return( DR_X64_cx );
    case REG_RDX: return( DR_X64_dx );
    case REG_RBX: return( DR_X64_bx );
    case REG_RSP: return( DR_X64_sp );
    case REG_RBP: return( DR_X64_bp );
    case REG_RSI: return( DR_X64_si );
    case REG_RDI: return( DR_X64_di );
    case REG_R8:  return( DR_X64_r8w );
    case REG_R9:  return( DR_X64_r9w );
    case REG_R10: return( DR_X64_r10w );
    case REG_R11: return( DR_X64_r11w );
    case REG_R12: return( DR_X64_r12w );
    case REG_R13: return( DR_X64_r13w );
    case REG_R14: return( DR_X64_r14w );
    case REG_R15: return( DR_X64_r15w );
    default:     return( DR_NONE );
    }
}

dis_register X64GetRegister_B( REGWIDTH rw, RM reg, dis_dec_ins *ins )
{
    // If a REX prefix is present then AH, BH, CH, CH are not accessible
    // they represent the new SIL/DIL/BPL/SPL registers!
    if( ins->flags & DIF_X64_PEX_PR )
    {
        switch( reg ) {
        case REG_RSI: return( DR_X64_sil );
        case REG_RDI: return( DR_X64_dil );
        case REG_RBP: return( DR_X64_bpl );
        case REG_RSP: return( DR_X64_spl );
        }
    }
    
    // If no REX prefix present, process normally
    switch( reg ) {
    case REG_RAX: return( DR_X64_al );
    case REG_RCX: return( DR_X64_cl );
    case REG_RDX: return( DR_X64_dl );
    case REG_RBX: return( DR_X64_bl );
    case REG_RSI: return( DR_X64_dh );
    case REG_RDI: return( DR_X64_bh );
    case REG_RBP: return( DR_X64_ch );
    case REG_RSP: return( DR_X64_ah );
    case REG_R8:  return( DR_X64_r8b );
    case REG_R9:  return( DR_X64_r9b );
    case REG_R10: return( DR_X64_r10b );
    case REG_R11: return( DR_X64_r11b );
    case REG_R12: return( DR_X64_r12b );
    case REG_R13: return( DR_X64_r13b );
    case REG_R14: return( DR_X64_r14b );
    case REG_R15: return( DR_X64_r15b );
    default:     return( DR_NONE );
    }
}

//dis_register X64FGetSTReg(WBIT w, RM reg, dis_dec_ins *ins )
/**********************************************************************
 *  Get ST  (Floating Point) Register  w - not used
 */
/*{
    switch( reg ) {
    case RM_0: return( DR_X64_st  );
    case RM_1: return( DR_X64_st1 );
    case RM_2: return( DR_X64_st2 );
    case RM_3: return( DR_X64_st3 );
    case RM_4: return( DR_X64_st4 );
    case RM_5: return( DR_X64_st5 );
    case RM_6: return( DR_X64_st6 );
    case RM_7: return( DR_X64_st7 );
    default:   return( DR_NONE );
    }
}*/

//dis_register X64GetMMReg(WBIT w, RM reg, dis_dec_ins *ins )
/**********************************************************************
 *  Get MM  (Multimedia) Register  w - not used
 */
/*{
    switch( reg ) {
    case RM_0: return( DR_X64_mm0 );
    case RM_1: return( DR_X64_mm1 );
    case RM_2: return( DR_X64_mm2 );
    case RM_3: return( DR_X64_mm3 );
    case RM_4: return( DR_X64_mm4 );
    case RM_5: return( DR_X64_mm5 );
    case RM_6: return( DR_X64_mm6 );
    case RM_7: return( DR_X64_mm7 );
    default:   return( DR_NONE );
    }
}*/

//dis_register X64GetXMMReg(WBIT w, RM reg, dis_dec_ins *ins )
/**********************************************************************
 *  Get SSE  (Streaming SIMD Extensions) Register  w - not used
 */
/*{
    switch( reg ) {
    case RM_0: return( DR_X64_xmm0 );
    case RM_1: return( DR_X64_xmm1 );
    case RM_2: return( DR_X64_xmm2 );
    case RM_3: return( DR_X64_xmm3 );
    case RM_4: return( DR_X64_xmm4 );
    case RM_5: return( DR_X64_xmm5 );
    case RM_6: return( DR_X64_xmm6 );
    case RM_7: return( DR_X64_xmm7 );
    default:   return( DR_NONE );
    }
}*/

//dis_register X64GetCRegister( WBIT w, RM reg, dis_dec_ins *ins )
/**********************************************************************
 *  Get Control Register
 */
/*{
    switch( reg ) {
    case REG_CR0: return( DR_X64_cr0 );
    case REG_CR2: return( DR_X64_cr2 );
    case REG_CR3: return( DR_X64_cr3 );
    case REG_CR4: return( DR_X64_cr4 );
    default     : return( DR_NONE );
    }
}*/

//dis_register X64GetDRegister( WBIT w, RM reg, dis_dec_ins *ins )
/**********************************************************************
 *  Get Debug Register
 */
/*{
    switch( reg ) {
    case REG_DR0: return( DR_X64_dr0 );
    case REG_DR1: return( DR_X64_dr1 );
    case REG_DR2: return( DR_X64_dr2 );
    case REG_DR3: return( DR_X64_dr3 );
    case REG_DR6: return( DR_X64_dr6 );
    case REG_DR7: return( DR_X64_dr7 );
    default     : return( DR_NONE );
    }
}*/

//dis_register X64GetTRegister( WBIT w, RM reg, dis_dec_ins *ins )
/**********************************************************************
 *  Get Test Register 80486
 */
/*{
    switch( reg ) {
    case REG_TR3: return( DR_X64_tr3 );
    case REG_TR4: return( DR_X64_tr4 );
    case REG_TR5: return( DR_X64_tr5 );
    case REG_TR6: return( DR_X64_tr6 );
    case REG_TR7: return( DR_X64_tr7 );
    default     : return( DR_NONE );
    }
}*/

dis_register X64GetSRegister( REGWIDTH rw, RM reg, dis_dec_ins *ins )
/**********************************************************************
 *  Get Segment Register
 */
{
    switch( reg ) {
    case REG_CS: return( DR_X64_cs );
    case REG_DS: return( DR_X64_ds );
    case REG_ES: return( DR_X64_es );
    case REG_FS: return( DR_X64_fs );
    case REG_GS: return( DR_X64_gs );
    case REG_SS: return( DR_X64_ss );
    default     : return( DR_NONE );
    }
}

dis_register X64GetRegister( REGWIDTH rw, RM reg, dis_dec_ins *ins )
/**********************************************************************
 *  Get Register
 *                 rw   =  0  (default) use 64-Bit operand
 *                      =  1            use 32-Bit operand
 *                      =  2            use 16-Bit operand
 *                      =  3            use 8-Bit operand
 */
{
    switch( rw ) {
    case RW_64BIT:
        return( X64GetRegister_Q( rw, reg, ins ) );
    case RW_32BIT:
        return( X64GetRegister_D( rw, reg, ins ) );
    case RW_16BIT:
        return( X64GetRegister_W( rw, reg, ins ) );
    case RW_8BIT:
        return( X64GetRegister_B( rw, reg, ins ) );
    }
    
    // default case
    return( X64GetRegister_Q( rw, reg, ins ) );
}


//dis_register X64GetRegisterAddr( WBIT w, RM reg, dis_dec_ins *ins )
/**********************************************************************
 *  Get Register
 *                 w   =  1  (default) use full width of operand
 *                     =  0            use byte size operand
 */
/*{
    switch(ins->type) {
    default:
        if( w != W_FULL ) {
            return( X64GetRegister_B ( w, reg, ins ) );
        } else if( DIF_X64_ADDR_LONG & ins->flags ) {
            return( X64GetRegister_D( w, reg, ins ) );
        } else {
            return( X64GetRegister_W( w, reg, ins ) );
        }
    }
}*/

static void X64GetSIB( REGWIDTH rw, unsigned_8 scale, RM base, RM index,
                       dis_dec_ins *ins, unsigned oper )
/**********************************************************************
 * Get SIB
 */
{
    if( DIF_X64_REX_B & ins->flags ) {
        base += X64_EXTENDED_REG_OFFSET;
    }
    
    if( DIF_X64_REX_X & ins->flags ) {
        index += X64_EXTENDED_REG_OFFSET;
    }
    
    ins->op[oper].base = X64GetRegister( rw, base, ins );
    
    if( index == REG_RSP || index == REG_R12 ) {
        ins->op[oper].scale = 1;
        ins->op[oper].index = DR_NONE;
    } else {
        ins->op[oper].scale = 1 << scale;
        ins->op[oper].index = X64GetRegister( rw, index, ins );
    }
}

/*=====================================================================*/
/*               Get MOD/RM as Operand                                 */
/*=====================================================================*/
static void X64GetModRM( REGWIDTH rw, MOD mod, REGWIDTH rw_rm, RM rm, void * d,
                         dis_dec_ins *ins, dis_ref_type ref_type )
/**********************************************************************
 */
{
    SIB sib;
    int oper;

    oper = ins->num_ops;
    ++ins->num_ops;

    ins->op[oper].type = DO_MEMORY_ABS;
    ins->op[oper].ref_type = ref_type;
    ins->op[oper].value = 0;
    ins->op[oper].scale = 1;
    ins->op[oper].index = DR_NONE;
    ins->op[oper].base  = DR_NONE;
    
    // fixup rm for extended registers if REX.B present
    if( DIF_X64_REX_B & ins->flags )
        rm += X64_EXTENDED_REG_OFFSET;
    
    // for rm == REG_RSP/REG_R12 SIB byte is required
    if( rm == REG_RSP || rm == REG_R12 ) {
        if( mod != MOD_3) {
            sib.full = GetUByte( d, ins->size );
            ins->size += 1;
            // base and index fixup is in X64GetSIB
            X64GetSIB( rw,
                       sib.split.scale,
                       sib.split.base,
                       sib.split.index,
                       ins,
                       oper );
            if( mod == MOD_0 ) {
                // I can use REG_RBP here because base is not fixed up
                if( sib.split.base == REG_RBP ) {
                    ins->op[oper].base = DR_NONE;
                    ins->op[oper].op_position = ins->size;
                    ins->op[oper].value = GetULong( d, ins->size );
                    ins->size += 4;
                }
            }
        }
    } else {
        ins->op[oper].base = X64GetRegister(rw, rm, ins);
    }

    switch( mod ) {
    case MOD_0:
        // Yeaaahhh.. in x86 was this disp32, now it's rip+disp32!!!
        // at the moment it's displaying as ex: adc rax, qword ptr [asdf]
        // sould it be adc rax, qword ptr asdf[rip] ?
        // maybe the orl need additional work for rip-based addressing?
        // the following code assembled with yasm: adc bl,  [asdf wrt rip]
        // will product the follwing disassembly: 12 1D E6 FF FF FF         adc    bl,byte ptr ds:[0xffffffe6]
        if( rm == REG_RBP || rm == REG_R13 ) {
            //ins->op[oper].type = DO_MEMORY_REL;
            ins->op[oper].base = DR_NONE;
            //ins->op[oper].base = X64GetRegister(rw, REG_RIP, ins);
            ins->op[oper].op_position = ins->size;
            ins->op[oper].value = GetULong( d, ins->size );
            ins->size += 4;
        }
        break;
    case MOD_1:
        ins->op[oper].op_position = ins->size;
        ins->op[oper].value = GetSByte( d, ins->size );
        ins->size += 1;
        break;
    case MOD_2:
        ins->op[oper].op_position = ins->size;
        ins->op[oper].value = GetULong( d, ins->size );
        ins->size += 4;
        break;
    case MOD_3:
        ins->op[oper].type = DO_REG;
        ins->op[oper].base = X64GetRegister(rw_rm, rm, ins);
        break;
    }
}

/*static void X64FGetModRM( WBIT w, MOD mod, RM rm, void * d,
                         dis_dec_ins *ins, dis_ref_type ref_type )*/
/**********************************************************************
 * Gets the Floating Point MOD/RM
 * NOT the same with X64GetModRM it returns ST instead of a register
 * if MOD = MOD_3
 */
/*{
    if( DIF_X64_ADDR_LONG & ins->flags ) {
        X64GetModRM_L( w, mod, rm, d ,ins, ref_type, X64FGetSTReg );
    } else {
        X64GetModRM_S( w, mod, rm, d ,ins, ref_type, X64FGetSTReg );
    }
}
*/
/*static void X64MMGetModRM( WBIT w, MOD mod, RM rm, void * d,
                         dis_dec_ins *ins, dis_ref_type ref_type )*/
/**********************************************************************
 * Gets the Floating Point MOD/RM
 * NOT the same with X64GetModRM it returns MM instead of a register
 * if MOD = MOD_3
 */
/*{
    if( DIF_X64_ADDR_LONG & ins->flags ) {
        X64GetModRM_L( w, mod, rm, d ,ins, ref_type, X64GetMMReg );
    } else {
        X64GetModRM_S( w, mod, rm, d ,ins, ref_type, X64GetMMReg );
    }
}*/

/*static void X64XMMGetModRM( WBIT w, MOD mod, RM rm, void * d,
                         dis_dec_ins *ins, dis_ref_type ref_type )*/
/**********************************************************************
 * Gets the Floating Point MOD/RM
 * NOT the same with X64GetModRM it returns XMM instead of a register
 * if MOD = MOD_3
 */
/*{
    if( DIF_X64_ADDR_LONG & ins->flags ) {
        X64GetModRM_L( w, mod, rm, d ,ins, ref_type, X64GetXMMReg );
    } else {
        X64GetModRM_S( w, mod, rm, d ,ins, ref_type, X64GetXMMReg );
    }
}*/

/*=====================================================================*/
/*               Get Register as Operands                              */
/*=====================================================================*/

static dis_ref_type X64RegRefType( dis_register reg )
{
    if( reg <= DR_X64_bh )
        return( DRT_X64_BYTE );

    if( reg <= DR_X64_r15w )
        return( DRT_X64_WORD );

    if( reg <= DR_X64_eip )
        return( DRT_X64_DWORD );

    if( reg <= DR_X64_rip )
        return( DRT_X64_QWORD );

    if( reg <= DR_X64_st7 )
        return( DRT_X64_TBYTE );
    
    if( reg <= DR_X64_mm7 )
        return( DRT_X64_MM64 );
    
    if( reg <= DR_X64_xmm7 )
        return( DRT_X64_XMM128 );
    
    if( reg <= DR_X64_dr7 )
        return( DRT_X64_DWORD );
    
    return( DRT_X64_QWORD );
}

//static void X64FGetST( RM reg, dis_dec_ins *ins )
/**********************************************************************
 *  Get ST - Floating Point Stack Register
 */
/*{
    int oper;

    oper = ins->num_ops;
    ins->op[oper].type = DO_REG;
    ins->op[oper].base = X64FGetSTReg( W_DEFAULT, reg, ins );
    ins->op[oper].ref_type = DRT_X64_TBYTE;
    ++ins->num_ops;
}*/

//static void X64GetMM( RM reg, dis_dec_ins *ins )
/**********************************************************************
 *  Get MM  Register
 */
/*{
    int oper;

    oper = ins->num_ops;
    ins->op[oper].type = DO_REG;
    ins->op[oper].base = X64GetMMReg( W_DEFAULT, reg, ins );
    ins->op[oper].ref_type = DRT_X64_MM64;
    ++ins->num_ops;
}*/

//static void X64GetXMM( RM reg, dis_dec_ins *ins )
/**********************************************************************
 *  Get XMM Register
 */
/*{
    int oper;

    oper = ins->num_ops;
    ins->op[oper].type = DO_REG;
    ins->op[oper].base = X64GetXMMReg( W_DEFAULT, reg, ins );
    ins->op[oper].ref_type = DRT_X64_XMM128;
    ++ins->num_ops;
}*/

static void X64GetReg( REGWIDTH rw, RM reg, dis_dec_ins *ins )
/**********************************************************************
 *  Get Register
 */
{
    int oper;
    
    oper = ins->num_ops;
    ins->op[oper].type = DO_REG;
    ins->op[oper].base = X64GetRegister( rw, reg, ins );
    ins->op[oper].ref_type = X64RegRefType( ins->op[oper].base );
    ++ins->num_ops;
}

//static void X64GetReg32( WBIT w, RM reg, dis_dec_ins *ins )
/**********************************************************************
 *  Get Register
 */
/*{
    int oper;

    oper = ins->num_ops;
    ins->op[oper].type = DO_REG;
    ins->op[oper].base = X64GetRegister_D( w, reg, ins );
    ins->op[oper].ref_type = DRT_X64_DWORD;
    ++ins->num_ops;
}*/

static void X64GetSReg( REGWIDTH rw, RM reg, dis_dec_ins *ins )
/**********************************************************************
 *  Get S Registers
 */
{
    int oper;

    oper = ins->num_ops;
    ins->op[oper].type = DO_REG;
    ins->op[oper].base = X64GetSRegister( rw, reg, ins );
    ins->op[oper].ref_type = DRT_X64_WORD;
    ++ins->num_ops;
}

static void X64GetSRegSpecial( REGWIDTH rw, RM reg_default, dis_dec_ins *ins )
/**********************************************************************
 *  Get S Registers Special (From Segment override prefixes)
 */
{
    int oper;

    oper = ins->num_ops;
    ins->op[oper].type = DO_REG;
    
    if( !(reg_default & ins->flags) )
    {
        if( DIF_X64_CS & ins->flags )
            ins->op[oper].base = X64GetSRegister( rw, DIF_X64_CS, ins );
        
        if( DIF_X64_DS & ins->flags )
            ins->op[oper].base = X64GetSRegister( rw, DIF_X64_DS, ins );

        if( DIF_X64_ES & ins->flags )
            ins->op[oper].base = X64GetSRegister( rw, DIF_X64_ES, ins );

        if( DIF_X64_FS & ins->flags )
            ins->op[oper].base = X64GetSRegister( rw, DIF_X64_FS, ins );

        if( DIF_X64_GS & ins->flags )
            ins->op[oper].base = X64GetSRegister( rw, DIF_X64_GS, ins );

        if( DIF_X64_SS & ins->flags )
            ins->op[oper].base = X64GetSRegister( rw, DIF_X64_SS, ins );

    }
    
    ins->op[oper].ref_type = DRT_X64_WORD;
    ++ins->num_ops;
}

/*=====================================================================*/
/*               Get Immediate Value                                   */
/*=====================================================================*/


static void X64GetImmedVal( SBIT s, WBIT w, void *d, dis_dec_ins *ins )
/*********************************************************************
 * Get Immediate Value
 *                   s = 0  (S_FULL / S_DEFAULT)
 *                   s = 1  (S_BYTE)
 */
{
    int oper;

    oper                      = ins->num_ops;
    ins->op[oper].op_position = ins->size;
    ins->op[oper].type        = DO_IMMED;
    ++ins->num_ops;
    
    if( w == W_FULL && s == S_FULL )
    {
        if ( w && (ins->flags & DIF_X64_OPND_SIZE) ) {
        // w and OpSize prefix: 16-Bit immediate
            ins->op[oper].value = GetSShort( d, ins->size );
            ins->op[oper].ref_type = DRT_X64_WORD;
            ins->size   += 2;
        } else if ( w ) {
        // w = 1 then 32-Bit immediate
            ins->op[oper].value = GetULong( d, ins->size );
            ins->op[oper].ref_type = DRT_X64_DWORD;
            ins->size   += 4;
        } else {
        // w = 0 then 8-Bit immediate
            ins->op[oper].value = GetSByte( d, ins->size );
            ins->op[oper].ref_type = DRT_X64_BYTE;
            ins->size   += 1;
        }
    } else {
        ins->op[oper].value = GetSByte( d, ins->size );
        if( w == W_BYTE ) {
            ins->op[oper].ref_type = DRT_X64_BYTE;
        } else if( ins->flags & DIF_X64_OPND_SIZE ) {
            ins->op[oper].ref_type = DRT_X64_DWORD;
        } else {
            ins->op[oper].ref_type = DRT_X64_WORD;
        }
        ins->size   += 1;
    }
}

/*=====================================================================*/
/*               Get Absolute Value                                    */
/*=====================================================================*/

//static void X64GetAbsVal( void *d, dis_dec_ins *ins )
/*********************************************************************
 * Get Absolute Value
 */
/*{
    int oper;

    oper = ins->num_ops;
    ins->op[oper].op_position = ins->size;
    ins->op[oper].type = DO_ABSOLUTE;
    ++ins->num_ops;
    if( ins->flags & DIF_X64_OPND_LONG ) {
        ins->op[oper].value = GetULong( d, ins->size );
        ins->size += 4;
    } else {
        ins->op[oper].value = GetUShort( d, ins->size );
        ins->size   += 2;
    }

    // Get Segment Value
    ins->op[oper].extra = GetUShort( d, ins->size );
    ins->size += 2;
    ins->op[oper].type |= DO_EXTRA;

}*/

/*=====================================================================*/
/*               Get Relative Value                                    */
/*=====================================================================*/

//static void X64GetRelVal_8( void *d, dis_dec_ins *ins )
/*********************************************************************
 * Get Relative Value   - 1 byte
 */
/*{
    int oper;

    oper = ins->num_ops;
    ins->op[oper].op_position = ins->size;
    ins->op[oper].type = DO_RELATIVE;
    ++ins->num_ops;
    ins->op[oper].value = GetSByte( d, ins->size );
    ins->size += 1;
    ins->op[oper].value += ins->size;
}

static void X64GetRelVal( void *d, dis_dec_ins *ins )*/
/*********************************************************************
 * Get Relative Value
 */
/*{
    int oper;

    oper = ins->num_ops;
    ins->op[oper].op_position = ins->size;
    ins->op[oper].type = DO_RELATIVE;
    ++ins->num_ops;
    if( ins->flags & DIF_X64_ADDR_LONG ) {
        ins->op[oper].value = GetULong( d, ins->size );
        ins->size += 4;
    } else {
        ins->op[oper].value = GetSShort( d, ins->size );
        ins->size += 2;
    }
    ins->op[oper].value += ins->size;
}*/

/*=====================================================================*/
/*               Get Reference Type                                    */
/*=====================================================================*/

dis_ref_type  X64GetRefType( REGWIDTH rw, dis_dec_ins *ins )
/*********************************************************************
 * Get Reference Type
 */
{
    // Instructions that have default ref type
    
    switch( rw ) {
        case RW_64BIT:
            return DRT_X64_QWORD;
            break;
        
        case RW_32BIT:
            return DRT_X64_DWORD;
            break;
        
        case RW_16BIT:
            return DRT_X64_WORD;
            break;
        
        case RW_8BIT:
            return DRT_X64_BYTE;
            break;
    }
    
    return( DRT_X64_BYTE );
}

//dis_ref_type X64FGetRefType( MF_BITS mf, dis_dec_ins * ins )
/*********************************************************************
 * Get Reference Type - Floating Point Instructions
 */
/*{
    switch( mf ) {
    case MF_0: return( DRT_X64_DWORDF );
    case MF_1: return( DRT_X64_DWORD );
    case MF_2: return( DRT_X64_QWORDF );
    case MF_3: return( DRT_X64_WORD );
    default:   return( DRT_X64_WORD );
    }
}*/

//dis_ref_type X64FGetRefTypeEnv( dis_dec_ins * ins )
/*********************************************************************
 * Get Reference Type - Floating Point Environment Instructions
 */
/*{
    if( ins->flags & DIF_X64_OPND_LONG ) {
        switch( ins->type ) {
        case DI_X64_fnsave00:
        case DI_X64_fnsave01:
        case DI_X64_fnsave10:
        case DI_X64_frstor00:
        case DI_X64_frstor01:
        case DI_X64_frstor10:
            return( DRT_X64_BYTE108 );
        case DI_X64_fnstenv00:
        case DI_X64_fnstenv01:
        case DI_X64_fldenv00:
        case DI_X64_fldenv01:
        case DI_X64_fldenv10:
            return( DRT_X64_BYTE28 );
        default:
            return( DRT_X64_DWORD );
        }
    } else {
        switch( ins->type ) {
        case DI_X64_fnsave00:
        case DI_X64_fnsave01:
        case DI_X64_fnsave10:
        case DI_X64_frstor00:
        case DI_X64_frstor01:
        case DI_X64_frstor10:
            return( DRT_X64_BYTE94 );
        case DI_X64_fnstenv00:
        case DI_X64_fnstenv01:
        case DI_X64_fnstenv10:
        case DI_X64_fldenv00:
        case DI_X64_fldenv01:
        case DI_X64_fldenv10:
            return( DRT_X64_BYTE14 );
        default:
            return( DRT_X64_WORD );
        }
    }
}*/


/*=====================================================================*/
/*               GET REGISTER AND MOD/RM FUNCTIONS                     */
/*=====================================================================*/


static REGWIDTH X64DecodeWDef32Bit( WBIT w, dis_dec_ins *ins )
/**********************************************************************/
// Decode w for 32 Bit default size
//
{
    REGWIDTH rw = RW_32BIT;
    
    //  w   REX.W   OPND_SIZE (66h)   =>  REGWIDTH
    //  --  ------  ----------------      --------------
    //  0   x       ignored           =>  RW_8BIT
    //  1   1       ignored           =>  RW_64BIT
    //  1   x       present           =>  RW_16BIT
    
    // reg is 64-bit if w and rex.w present
    if( w && ( DIF_X64_REX_W & ins->flags ) )
        rw = RW_64BIT;
    
    // reg is 16-bit if w and opcode override is present
    if( w && ( DIF_X64_OPND_SIZE & ins->flags ) )
        rw = RW_16BIT;
    
    // reg is 8-bit if w=0
    if( !w )
        rw = RW_8BIT;
    
    return( rw );
}


static void X64GetRegModRM( DBIT dir, WBIT w, MOD mod, RM rm, RM reg,
                     void * d, dis_dec_ins *ins )
/**********************************************************************/
//    dir                   1                 0
//   Destination           Reg              MODRM
//   Source               MODRM              Reg
{
    REGWIDTH rw_mod = RW_64BIT;
    REGWIDTH rw_reg = X64DecodeWDef32Bit( w, ins );
    
    // modrm is 32 bit if addr size prefix is present
    if( DIF_X64_ADDR_SIZE & ins->flags )
        rw_mod = RW_32BIT;

    // REX.R modifies reg to access r8-r15
    if( DIF_X64_REX_R & ins->flags ) {
        reg += X64_EXTENDED_REG_OFFSET;
    }
    
    if( dir ) {
        X64GetReg( rw_reg, reg, ins );
        X64GetModRM( rw_mod, mod, rw_reg, rm, d, ins, X64GetRefType( rw_reg, ins ) );
    } else {
        X64GetModRM( rw_mod, mod, rw_reg, rm, d, ins, X64GetRefType( rw_reg, ins ) );
        X64GetReg( rw_reg, reg, ins );
    }
}

/*static void X64GetMMRegModRM( DBIT dir, WBIT w, MOD mod, RM rm, RM reg,
                     dis_ref_type ref_type, void * d, dis_dec_ins *ins )*/
/**********************************************************************/
//    dir                   1                 0
//   Destination           Reg              MODRM
//   Source               MODRM              Reg
/*{

    if( dir ) {
        X64GetMM( reg, ins );
        X64MMGetModRM( w, mod, rm, d, ins, ref_type );
    } else {
        X64MMGetModRM( w, mod, rm, d, ins, ref_type );
        X64GetMM( reg, ins );
    }
}*/

/*static void X64GetXMMRegModRM( DBIT dir, WBIT w, MOD mod, RM rm, RM reg,
                     dis_ref_type ref_type, void * d, dis_dec_ins *ins )*/
/**********************************************************************/
//    dir                   1                 0
//   Destination           Reg              MODRM
//   Source               MODRM              Reg
/*{

    if( dir ) {
        X64GetXMM( reg, ins );
        X64XMMGetModRM( w, mod, rm, d, ins, ref_type );
    } else {
        X64XMMGetModRM( w, mod, rm, d, ins, ref_type );
        X64GetXMM( reg, ins );
    }
}*/

//void X64GetRegModRM_B( DBIT dir, MOD mod, RM rm, RM reg, void *d, dis_dec_ins *ins )
/**********************************************************************/
//    dir                   1                 0
//   Destination           Reg              MODRM
//   Source               MODRM              Reg
/*{
    if( dir ) {
        X64GetReg( W_DEFAULT, reg, ins );
        X64GetModRM( W_DEFAULT, mod, W_DEFAULT, rm, d, ins, X64GetRefType( W_DEFAULT ,ins ) );
    } else {
        X64GetModRM( W_DEFAULT, mod, W_DEFAULT, rm, d, ins, X64GetRefType( W_DEFAULT ,ins ) );
        X64GetReg( W_DEFAULT, reg, ins );
    }
}*/



/*=====================================================================*/
/*                8-BIT OPCODE FUNCTIONS                               */
/*=====================================================================*/



typedef union {
    unsigned_32 full;
    struct {
        unsigned_32 w  : 1;
        unsigned_32 dir: 1;
        unsigned_32 op1: 6;
    } type1;
    struct {
        unsigned_32 reg: 3;
        unsigned_32 w  : 1;
        unsigned_32 op1: 4;
    } type2;
    struct {
        unsigned_32 w  : 1;
        unsigned_32 s  : 1;
        unsigned_32 op1: 6;
    } type3;
    struct {
        unsigned_32 op2: 3;
        unsigned_32 sreg:2;
        unsigned_32 op1: 3;
    } sreg;
} code_8;


//dis_handler_return X64SReg_8( dis_handle *h, void *d, dis_dec_ins *ins )
/*********************************************************************
 *  OOO SS OOO
 *     sreg
 */
/*{
    code_8 code;

    code.full = ins->opcode;
    ins->size    += 1;
    ins->num_ops = 0;

    switch( ins->type ) {
    case DI_X64_push3:
        ins->op[ins->num_ops].base = X64GetRegister( W_DEFAULT, REG_SP, ins );
        ins->op[ins->num_ops].type = DO_MEMORY_ABS | DO_HIDDEN;
        ins->op[ins->num_ops].ref_type = X64GetRefType( W_DEFAULT, ins );
        ++ins->num_ops;
        break;
    default:
        break;
    }
    X64GetSReg(W_DEFAULT, code.sreg.sreg, ins);
    switch( ins->type ) {
    case DI_X64_pop3d:
    case DI_X64_pop3e:
    case DI_X64_pop3s:
        ins->op[ins->num_ops].base = X64GetRegister( W_DEFAULT, REG_SP, ins );
        ins->op[ins->num_ops].type = DO_MEMORY_ABS | DO_HIDDEN;
        ins->op[ins->num_ops].ref_type = X64GetRefType( W_DEFAULT, ins );
        ++ins->num_ops;
        break;
    default:
        break;
    }
#if 0
    if( DIF_X64_OPND_SIZE & ins->flags ) {
        if( DIF_X64_OPND_LONG & ins->flags ) {
            switch( ins->type ) {
            case DI_X64_push3:
                ins->type = DI_X64_pushd;
                break;
            default:
                break;
            }
        } else {
            switch( ins->type ) {
            case DI_X64_push3:
                ins->type = DI_X64_pushw;
                break;
            default:
                break;
            }
        }
    }
#endif
    return( DHR_DONE );
}*/

dis_handler_return X64NoOp_8( dis_handle *h, void *d, dis_dec_ins *ins )
/*********************************************************************
 *  OOOO OOOW
 */
{
    code_8 code;

    code.full = ins->opcode;
    ins->size    += 1;
    ins->num_ops = 0;

    switch( ins->type ) {
    case DI_X64_pushfq:
    case DI_X64_popfq:
        ins->op[ins->num_ops].base = X64GetRegister( RW_DEFAULT, REG_RSP, ins );
        ins->op[ins->num_ops].type = DO_MEMORY_ABS | DO_HIDDEN;
        ins->op[ins->num_ops].ref_type = X64GetRefType( RW_DEFAULT, ins );
        ++ins->num_ops;
        break;
    case DI_X64_xlat:
        if( DIF_X64_ADDR_SIZE & ins->flags ) {
            ins->op[ins->num_ops].base = X64GetRegister_D( RW_DEFAULT, REG_RBX, ins );
        } else {
            ins->op[ins->num_ops].base = X64GetRegister_Q( RW_DEFAULT, REG_RBX, ins );
        }
        ins->op[ins->num_ops].type = DO_MEMORY_ABS;
        ins->op[ins->num_ops].ref_type = X64GetRefType( RW_DEFAULT, ins );
        ++ins->num_ops;
        break;
    default:
        break;
    }
    
    if( ins->flags & DIF_X64_OPND_SIZE )
    {
        switch( ins->type ) {
        case DI_X64_cwde:
            ins->type = DI_X64_cbw;
            break;
        case DI_X64_cdq:
            ins->type = DI_X64_cwd;
            break;
        case DI_X64_popfq:
            ins->type = DI_X64_popf;
            break;
        case DI_X64_pushfq:
            ins->type = DI_X64_pushf;
            break;
        case DI_X64_iretd:
            ins->type = DI_X64_iret;
            break;
        }
    }
    
    if( ins->flags & DIF_X64_REX_W )
    {
        switch( ins->type ) {
        case DI_X64_cwde:
            ins->type = DI_X64_cdqe;
            break;
        case DI_X64_cdq:
            ins->type = DI_X64_cqo;
            break;
        case DI_X64_iretd:
            ins->type = DI_X64_iretq;
            break;
        }
    }

    return( DHR_DONE );
}

//dis_handler_return X64String_8( dis_handle *h, void *d, dis_dec_ins *ins )
/**********************************************************************
 * String Functions
 *  OOOO OOOW
 */
/*{
    code_8 code;

    code.full = ins->opcode;
    ins->size += 1;
    ins->num_ops = 2;

    switch( ins->type ) {
    case DI_X64_cmps:
        ins->op[0].base = X64GetRegisterAddr( W_DEFAULT, REG_SI, ins );
        ins->op[0].type = DO_MEMORY_ABS;
        ins->op[0].ref_type = X64GetRefType( code.type1.w, ins );
        ins->op[1].base = X64GetRegisterAddr( W_DEFAULT, REG_DI, ins );
        ins->op[1].type = DO_MEMORY_ABS | DO_NO_SEG_OVR;
        ins->op[1].ref_type = X64GetRefType( code.type1.w, ins );
        break;
    case DI_X64_movs:
        ins->op[0].base = X64GetRegisterAddr( W_DEFAULT, REG_DI, ins );
        ins->op[0].type = DO_MEMORY_ABS | DO_NO_SEG_OVR;
        ins->op[0].ref_type = X64GetRefType( code.type1.w, ins );
        ins->op[1].base = X64GetRegisterAddr( W_DEFAULT, REG_SI, ins );
        ins->op[1].type = DO_MEMORY_ABS;
        ins->op[1].ref_type = X64GetRefType( code.type1.w, ins );
        break;
    case DI_X64_ins:
        ins->op[0].base = X64GetRegisterAddr( W_DEFAULT, REG_DI, ins );
        ins->op[0].type = DO_MEMORY_ABS | DO_NO_SEG_OVR;
        ins->op[0].ref_type = X64GetRefType( code.type1.w, ins );
        ins->op[1].base = DR_X64_dx;
        ins->op[1].type = DO_REG;
        ins->op[1].ref_type = X64GetRefType( code.type1.w, ins );
        break;
    case DI_X64_lods:
        ins->op[0].base = X64GetRegisterAddr( W_DEFAULT, REG_SI, ins );
        ins->op[0].type = DO_MEMORY_ABS;
        ins->op[0].ref_type = X64GetRefType( code.type1.w, ins );
        ins->num_ops = 1;
        break;
    case DI_X64_outs:
        ins->op[0].base = DR_X64_dx;
        ins->op[0].type = DO_REG;
        ins->op[0].ref_type = X64GetRefType( code.type1.w, ins );
        ins->op[1].base = X64GetRegisterAddr( W_DEFAULT, REG_SI, ins );
        ins->op[1].type = DO_MEMORY_ABS;
        ins->op[1].ref_type = X64GetRefType( code.type1.w, ins );
        break;
    case DI_X64_stos:
    case DI_X64_scas:
        ins->op[0].base = X64GetRegisterAddr( W_DEFAULT, REG_DI, ins );
        ins->op[0].type = DO_MEMORY_ABS | DO_NO_SEG_OVR;
        ins->op[0].ref_type = X64GetRefType( code.type1.w, ins );
        ins->num_ops = 1;
        break;
    default:
        break;
    }
    return( DHR_DONE );
}
*/
dis_handler_return X64ImmAcc_8( dis_handle *h, void *d, dis_dec_ins *ins )
/**********************************************************************
 * Immediate to Accumulator EAX, AX, or AL
 * Format:    OOOO OOOW
 */
{
    code_8 code;
    REGWIDTH rw_reg;
    //REGWIDTH rw_reg = RW_32BIT;

    code.full    = ins->opcode;
    ins->num_ops = 0;
    ins->size   += 1;
    
    rw_reg = X64DecodeWDef32Bit( code.type1.w, ins );
    
/*    if( !code.type1.w ) {
        rw_reg = RW_8BIT;
    } else if( code.type1.w && (DIF_X64_OPND_SIZE & ins->flags) ) {
        rw_reg = RW_16BIT;
    } else if( code.type1.w && (DIF_X64_REX_W & ins->flags) ) {
        rw_reg = RW_64BIT;
    }*/
    
    switch( ins->type ) {
/*    case DI_X64_in:
        X64GetReg( code.type1.w, REG_AX, ins );
        X64GetImmedVal( S_DEFAULT, W_BYTE, d, ins );
        break;
    case DI_X64_out:
        X64GetImmedVal( S_DEFAULT, W_BYTE, d, ins );
        X64GetReg(code.type1.w, REG_AX, ins);
        break;*/
    default:
        X64GetReg(rw_reg, REG_RAX, ins);
        X64GetImmedVal( S_DEFAULT, code.type1.w, d, ins  );
        break;
    }
    return( DHR_DONE );
}

/*
dis_handler_return X64MemAbsAcc_8( dis_handle *h, void *d, dis_dec_ins *ins )*/
/**********************************************************************
 * Absolute Memory to Accumulator
 * Format:    OOOO OODW
 */
/*{
    code_8 code;

    code.full    = ins->opcode;
    ins->num_ops = 0;
    ins->size   += 1;
    if( code.type1.dir ) {
        ins->op[0].type = DO_MEMORY_ABS;
        ins->op[0].ref_type = X64GetRefType( code.type1.w , ins );
        ins->op[0].op_position = ins->size;
        if( ins->flags & DIF_X64_ADDR_LONG ) {
            ins->op[0].value = GetULong( d, ins->size );
            ins->size += 4;
        } else {
            ins->op[0].value = GetUShort( d, ins->size );
            ins->size   += 2;
        }
        ++ins->num_ops;
        X64GetReg(code.type1.w, REG_AX, ins);
    } else {
        X64GetReg(code.type1.w, REG_AX, ins);
        ins->op[1].type  = DO_MEMORY_ABS;
        ins->op[1].ref_type = X64GetRefType( code.type1.w , ins );
        ins->op[1].op_position = ins->size;
        if( ins->flags & DIF_X64_ADDR_LONG ) {
            ins->op[1].value = GetULong( d, ins->size );
            ins->size += 4;
        } else {
            ins->op[1].value = GetUShort( d, ins->size );
            ins->size += 2;
        }
        ++ins->num_ops;
    }
    return( DHR_DONE );
}


dis_handler_return X64Abs_8( dis_handle *h, void *d, dis_dec_ins *ins )*/
/**********************************************************************/
/*{
    ins->size   += 1;
    ins->num_ops = 0;
    X64GetAbsVal( d, ins );
    return( DHR_DONE );
}


dis_handler_return X64Rel_8( dis_handle *h, void *d, dis_dec_ins *ins )*/
/**********************************************************************/
/*{
    ins->size   += 1;
    ins->num_ops = 0;
    X64GetRelVal( d, ins );
    return( DHR_DONE );
}

dis_handler_return X64Imm_8( dis_handle *h, void *d, dis_dec_ins *ins )*/
/**********************************************************************/
//  Byte      OOOO OOSW
/*{
    code_8 code;

    code.full = ins->opcode;

    ins->size   += 1;
    ins->num_ops = 0;
    ins->op[0].type = DO_IMMED;
    switch( ins->type ) {
    case DI_X64_int:
        if( code.type3.w ) {

            char intno = GetUByte( d, ins->size );

            if( ( intno >= 0x34 ) && ( intno <= 0x3D ) ) {
                ins->flags |= DIF_X64_EMU_INT;
                ins->op[ MAX_NUM_OPERANDS - 1 ].value = intno;
                ins->op[ MAX_NUM_OPERANDS - 1 ].type = DO_IMMED;
                ins->op[ MAX_NUM_OPERANDS - 1 ].ref_type = DRT_X64_BYTE;
                if( intno == 0x3C ) {
                    ins->size += 1;
                    ins->flags ^= DIF_X64_FWAIT;
                } else if( intno == 0x3D ) {
                } else {
                    ins->flags ^= DIF_X64_FWAIT;
                }
                return( DHR_CONTINUE );
            }
            ins->op[0].value = intno;
            ins->size += 1;
        } else {
            ins->op[0].value = 3;
        }
        ins->op[0].ref_type = DRT_X64_BYTE;
        ++ins->num_ops;
        break;
    case DI_X64_ret2:
    case DI_X64_retf2:
        ins->op[0].value = GetUShort( d, ins->size );
        ins->op[0].ref_type = DRT_X64_WORD;
        ins->size += 2;
        ++ins->num_ops;
        break;
    case DI_X64_push5:
        X64GetImmedVal( code.type3.s, W_DEFAULT, d, ins );
        if( code.type3.s ) {
            if( ( DIF_X64_OPND_LONG & ins->flags ) == 0 ) {
                ins->op[0].value &= 0xffff;
            }
        }
        if( DIF_X64_OPND_SIZE & ins->flags ) {
            if( DIF_X64_OPND_LONG & ins->flags ) {
                if( ( ins->op[0].value & 0xffff0000 ) == 0 ) {
                    ins->type = DI_X64_pushd;
                }
            } else {
                ins->type = DI_X64_pushw;
            }
        }
        break;
    default:
        X64GetImmedVal( code.type3.s, W_DEFAULT, d, ins );
        break;
    }
    return( DHR_DONE );
}


dis_handler_return X64ImmReg_8( dis_handle *h, void *d, dis_dec_ins *ins )*/
/**********************************************************************/
//  8-bit   OOOO WRRR : Imm
/*{
    code_8 code;

    code.full = ins->opcode;
    ins->num_ops = 0;
    ++ins->size;
    X64GetReg( code.type2.w, code.type2.reg, ins );
    X64GetImmedVal( S_DEFAULT, code.type2.w, d, ins );
    return( DHR_DONE );
}

dis_handler_return X64ImmImm_8( dis_handle *h, void *d, dis_dec_ins *ins )*/
/**********************************************************************/
//  8-bit   OOOO OOOO : Imm16 Imm8
/*{
    ins->num_ops = 2;
    ins->size   += 1;
    ins->op[0].value = GetUShort( d, ins->size );
    ins->op[0].type = DO_IMMED;
    ins->op[0].ref_type = DRT_X64_WORD;
    ins->size   += 2;
    ins->op[1].value = GetUByte( d, ins->size );
    ins->op[1].type = DO_IMMED;
    ins->op[1].ref_type = DRT_X64_BYTE;
    ins->size   += 1;
    return( DHR_DONE );
}
*/
dis_handler_return X64Reg_8( dis_handle *h, void *d , dis_dec_ins *ins )
/**********************************************************************/
//  Byte       OOOO  ORRR
{
    code_8   code;
    REGWIDTH rw = RW_64BIT;

    ins->size      += 1;
    ins->num_ops    = 0;
    code.full       = ins->opcode;
    
    if( ins->flags & DIF_X64_OPND_SIZE ) {
        rw = RW_16BIT;
    }

    switch( ins->type ) {
    /*case DI_X64_xchg2:
        if( code.type2.reg == REG_AX ) {
            if( ins->flags & DIF_X64_REPE ) {
                ins->type = DI_X64_pause;
                ins->flags &= ~DIF_X64_REPE;
            } else {
                ins->type = DI_X64_nop;
            }
        } else {
            X64GetReg( W_DEFAULT, REG_AX, ins );
            X64GetReg( W_DEFAULT, code.type2.reg, ins );
        }
        return( DHR_DONE );*/
        
    case DI_X64_push:
        ins->op[ins->num_ops].base = X64GetRegister( RW_DEFAULT, REG_RSP, ins );
        ins->op[ins->num_ops].type = DO_MEMORY_ABS | DO_HIDDEN;
        ins->op[ins->num_ops].ref_type = X64GetRefType( RW_DEFAULT, ins );
        ++ins->num_ops;
        break;
    
    default:
        break;
    }
    
    X64GetReg( rw, code.type2.reg, ins );
    
    switch( ins->type ) {
    case DI_X64_pop:
        ins->op[ins->num_ops].base = X64GetRegister( RW_DEFAULT, REG_RSP, ins );
        ins->op[ins->num_ops].type = DO_MEMORY_ABS | DO_HIDDEN;
        ins->op[ins->num_ops].ref_type = X64GetRefType( RW_DEFAULT, ins );
        ++ins->num_ops;
        break;
    default:
        break;
    }
    return( DHR_DONE );
}

/*
dis_handler_return X64AccAcc_8( dis_handle *h, void *d, dis_dec_ins *ins )*/
/**********************************************************************/
// Accum to Accumulator EAX, AX, or AL to DX
// Format:    0000 000 W
//              op1    w
/*{
    code_8 code;

    code.full    = ins->opcode;
    ins->size   += 1;
    ins->num_ops = 0;
    switch( ins->type ) {
    case DI_X64_in2:
        X64GetReg( code.type1.w, REG_AX, ins );
        ins->op[1].type = DO_REG;
        ins->op[1].base = DR_X64_dx;
        ++ins->num_ops;
        break;
    case DI_X64_out2:
        ins->op[0].type = DO_REG;
        ins->op[0].base = DR_X64_dx;
        ++ins->num_ops;
        X64GetReg( code.type1.w, REG_AX, ins );
        break;
    default:
        break;
    }
    return( DHR_DONE );
}


dis_handler_return X64JmpCC_8( dis_handle *h, void *d, dis_dec_ins *ins )*/
/**********************************************************************
 *  Jump Handler
 */
/*{
    code_8 code;

    code.full = ins->opcode;
    ins->size += 1;
    ins->num_ops = 0;

    X64GetRelVal_8( d, ins );
    switch( ins->type ) {
    case DI_X64_jcxz:
        if( ins->flags & DIF_X64_ADDR_LONG ){
            ins->type = DI_X64_jecxz;
        }
        return( DHR_DONE );
    default:
        break;
    }

    if( ins->flags & DIF_X64_ADDR_SIZE ) {
        if( ins->flags & DIF_X64_ADDR_LONG ) {
            switch( ins->type ) {
            case DI_X64_loop:
                ins->type = DI_X64_loopd;
                break;
            case DI_X64_loopz:
                ins->type = DI_X64_loopzd;
                break;
            case DI_X64_loopnz:
                ins->type = DI_X64_loopnzd;
                break;
            default:
                break;
            }
        } else {
            switch( ins->type ) {
            case DI_X64_loop:
                ins->type = DI_X64_loopw;
                break;
            case DI_X64_loopz:
                ins->type = DI_X64_loopzw;
                break;
            case DI_X64_loopnz:
                ins->type = DI_X64_loopnzw;
                break;
            default:
                break;
            }
        }
    }
    return( DHR_DONE );
}
*/

/*=====================================================================*/
/*                16-BIT OPCODE FUNCTIONS                              */
/*=====================================================================*/

typedef union {
    unsigned_32 full;
    struct {
        unsigned_32 w  : 1;
        unsigned_32 s  : 1; //  SBIT
        unsigned_32 op1: 6;
        unsigned_32 rm : 3;
        unsigned_32 reg: 3;
        unsigned_32 mod: 2;
    } type1;
    struct {
        unsigned_32 w  : 1;
        unsigned_32 dir: 1; // direction
        unsigned_32 op1: 6;
        unsigned_32 rm : 3;
        unsigned_32 reg: 3;
        unsigned_32 mod: 2;
    } type2;
    struct {
        unsigned_32 op1: 8;
        unsigned_32 op2: 3;
        unsigned_32 sreg:3;
    } sreg;
    struct {
        unsigned_32 w  : 1;
        unsigned_32 cl : 1;
        unsigned_32 op1: 6;
        unsigned_32 rm : 3;
        unsigned_32 reg: 3;
        unsigned_32 mod: 2;
    } shift;
} code_16;

dis_handler_return X64RegModRM_16( dis_handle *h, void *d, dis_dec_ins *ins )
/**********************************************************************/
// Format:    OOOO OO   D         W MM   REG RRR
//              op1    direction  w mod reg1 rm/reg2
{
    code_16 code;

    code.full    = ins->opcode;
    ins->num_ops = 0;
    ins->size   += 2;
    
    X64GetRegModRM( code.type2.dir, code.type2.w, code.type2.mod,
                    code.type2.rm, code.type2.reg, d, ins );
    
    return( DHR_DONE );
}

dis_handler_return X64ModRMImm_16( dis_handle *h, void *d, dis_dec_ins *ins )
/**********************************************************************/
// Format:    OOOO OOO W MM  OOO RRR
//              op1    w mod op2 rm
{
    code_16 code;
    REGWIDTH rw_mod = RW_64BIT;
    REGWIDTH rw_reg;

    code.full     = ins->opcode;
    ins->num_ops  = 0;
    ins->size    += 2;
    
    rw_reg = X64DecodeWDef32Bit( code.type1.w, ins );
    
    // modrm is 32 bit if addr size prefix is present
    if( DIF_X64_ADDR_SIZE & ins->flags )
        rw_mod = RW_32BIT;
    
    X64GetModRM( rw_mod, code.type1.mod, rw_reg, code.type1.rm, d, ins, X64GetRefType( rw_reg, ins ) );
    
    switch(ins->type ) {
/*    case DI_X86_rcl2:
    case DI_X86_rcr2:
    case DI_X86_ror2:
    case DI_X86_rol2:
    case DI_X86_sar2:
    case DI_X86_shr2:
    case DI_X86_shl2:
        X86GetImmedVal( S_DEFAULT, W_BYTE, d, ins );
        break;
    case DI_X86_mov2:
    case DI_X86_test3:
        X86GetImmedVal( S_DEFAULT, code.type1.w, d, ins );
        break;*/
    default:
        X64GetImmedVal( code.type1.s, code.type1.w, d, ins );
        break;
    }
    return( DHR_DONE );
}

/*=====================================================================*/
/*                HOOK FUNCTIONS                                       */
/*=====================================================================*/


static unsigned AddRefType( char *p, unsigned len, dis_ref_type ref_type )
{
    switch( ref_type ) {
    case DRT_X64_BYTE:
        p[len++] = 'b';
        break;
    case DRT_X64_WORD:
        p[len++] = 'w';
        break;
    case DRT_X64_DWORD:
    case DRT_X64_DWORDF:
        p[len++] = 'l';
        break;
    default:
        break;
    }
    return( len );
}

static dis_ref_type GetRefType( dis_dec_ins *ins, unsigned op )
{
    unsigned    reg;

    switch( ins->op[op].type & DO_MASK ) {
    case DO_REG:
        reg = ins->op[op].base;
        if(                      reg <= DR_X64_bh ) return( DRT_X64_BYTE );
        if( reg >= DR_X64_ax  && reg <= DR_X64_r15w ) return( DRT_X64_WORD );
        if( reg >= DR_X64_eax && reg <= DR_X64_eflags ) return( DRT_X64_DWORD );
        if( reg >= DR_X64_rax && reg <= DR_X64_rip ) return( DRT_X64_QWORD );
        if( reg >= DR_X64_cr0 && reg <= DR_X64_dr7 ) return( DRT_X64_DWORD );
        if( reg >= DR_X64_es  && reg <= DR_X64_gs ) return( DRT_X64_WORD );
        break;
    case DO_MEMORY_ABS:
        return( ins->op[op].ref_type );
    default:
        break;
    }
    return( DRT_NONE );
}

static unsigned UnixMangleName( dis_dec_ins *ins, char *p, unsigned len )
{
    dis_ref_type        ref_type = DRT_NONE;
    unsigned            i;

    switch( ins->type ) {
/*
    case DI_X64_arpl:
    case DI_X64_bound:
    case DI_X64_bswap:
    case DI_X64_call:
    case DI_X64_call2:
    case DI_X64_cmpxchg:
    case DI_X64_cmpxchg8b:
    //NYI: conditional move instructions?
    case DI_X64_cpuid:
    case DI_X64_invlpg:
    case DI_X64_jmp:
    case DI_X64_jmp2:
    case DI_X64_lgdt:
    case DI_X64_lidt:
    case DI_X64_lldt:
    case DI_X64_lmsw:
    case DI_X64_ltr:
    case DI_X64_pushw:
    case DI_X64_pushd:
    case DI_X64_rdmsr:
    case DI_X64_rdpmc:
    case DI_X64_seto:
    case DI_X64_setno:
    case DI_X64_setb:
    case DI_X64_setae:
    case DI_X64_sete:
    case DI_X64_setne:
    case DI_X64_setbe:
    case DI_X64_seta:
    case DI_X64_sets:
    case DI_X64_setns:
    case DI_X64_setp:
    case DI_X64_setpo:
    case DI_X64_setl:
    case DI_X64_setge:
    case DI_X64_setle:
    case DI_X64_setg:
    case DI_X64_sgdt:
    case DI_X64_sidt00:
    case DI_X64_sidt01:
    case DI_X64_sidt10:
    case DI_X64_sldt:
    case DI_X64_str:
    case DI_X64_verr:
    case DI_X64_verw:
    case DI_X64_wbinvd:
    case DI_X64_wrmsr:
        return( len );
    case DI_X64_movsx:
    case DI_X64_movzx:
        len = AddRefType( p, len, GetRefType( ins, 0 ) );
        ref_type = GetRefType( ins, 1 );
        break;
    case DI_X64_call3:
    case DI_X64_call4:
        strcpy( p, "lcall" );
        return( 5 );
    case DI_X64_jmp3:
    case DI_X64_jmp4:
        strcpy( p, "ljmp" );
        return( 4 );
    case DI_X64_retf:
    case DI_X64_retf2:
        strcpy( p, "lret" );
        return( 4 );
    case DI_X64_cbw:
        strcpy( p, "cbtw" );
        return( 4 );
    case DI_X64_cwde:
        strcpy( p, "ctwl" );
        return( 4 );
    case DI_X64_cwd:
        strcpy( p, "ctwd" );
        return( 4 );
    case DI_X64_cdq:
        strcpy( p, "cltd" );
        return( 4 );*/
    default:
        for( i = 0; i < ins->num_ops; ++i ) {
            ref_type = GetRefType( ins, i );
            if( ref_type != DRT_NONE ) break;
        }
        break;
    }
    return( AddRefType( p, len, ref_type ) );
}

static unsigned X64InsHook( dis_handle *h, void *d, dis_dec_ins *ins,
        dis_format_flags flags, char *name )
/**********************************************************************/
{
    unsigned    len;
    char        *p;
    unsigned    op;
    dis_operand save;
    char        temp_buff[40];

    if( name == NULL ) name = temp_buff;
    p = name;
/*    if( ins->flags & DIF_X64_LOCK ) {
        p += DisGetString( DisInstructionTable[DI_X64_lock_pr].name, p, 0 );
        if( flags & DFF_X86_UNIX ) *p++ = ';';
        *p++ = ' ';
    }
    if( ins->flags & DIF_X64_REPNE ) {
        p += DisGetString( DisInstructionTable[DI_X64_repne_pr].name, p, 0 );
        if( flags & DFF_X86_UNIX ) *p++ = ';';
        *p++ = ' ';
    }
    if( ins->flags & DIF_X64_REPE ) {
        switch( ins->type ) {
        case DI_X64_cmps:
        case DI_X64_scas:
            p += DisGetString( DisInstructionTable[DI_X64_repe_pr].name, p, 0 );
            break;
        default:
            p += DisGetString( DisInstructionTable[DI_X64_rep_pr].name, p, 0 );
            break;
        }
        if( flags & DFF_X86_UNIX ) *p++ = ';';
        *p++ = ' ';
    }*/
    len = DisGetString( DisInstructionTable[ins->type].name, p, 0 );
    if( flags & DFF_X86_UNIX ) {
        if( ins->num_ops >= 2 ) {
            op = ins->num_ops - 1;
            save = ins->op[op];
            ins->op[op] = ins->op[0];
            ins->op[0] = save;
        }
        len = UnixMangleName( ins, p, len );
    }
    p += len;
    if( !X64SegmentOverride( ins ) /*&& ( ( ins->flags & DIF_X64_ADDR_SIZE ) == 0 )*/ ) {
        switch( ins->type ) {
/*        case DI_X64_cmps:
        case DI_X64_ins:
        case DI_X64_lods:
        case DI_X64_movs:
        case DI_X64_outs:
        case DI_X64_scas:
        case DI_X64_stos:*/
            /* UnixMangleName will have already taken care of this */
/*            if( !( flags & DFF_X86_UNIX ) ) {
                op = 0;
                if( ( ins->op[op].type & DO_MASK ) != DO_MEMORY_ABS )
                    op = 1;
                switch( ins->op[op].ref_type ) {
                case DRT_X64_BYTE:
                    *p++ = 'b';
                    break;
                case DRT_X64_WORD:
                    *p++ = 'w';
                    break;
                case DRT_X64_DWORD:
                    *p++ = 'd';
                    break;
                default:
                    break;
                }
            }
            ins->op[0].type |= DO_HIDDEN;
            ins->op[1].type |= DO_HIDDEN;
            break;*/
        case DI_X64_xlat:
            *p++ = 'b';
            ins->op[0].type |= DO_HIDDEN;
            break;
        default:
            break;
        }
    }
    *p = '\0';
    return( p - name );
}

static unsigned X64FlagHook( dis_handle *h, void *d, dis_dec_ins *ins,
        dis_format_flags flags, char *name )
/**********************************************************************/
{
    return( 0 );
}

char *DisAddUnixRegX64( dis_register reg, char *p, dis_format_flags flags )
{
    if( reg == DR_NONE )
        return( p );
    *p++ = '%';
    return( DisAddReg( reg, p, flags ) );
}

static char *DisOpUnixFormat( void *d, dis_dec_ins *ins, dis_format_flags flags,
                        unsigned i, char *p )
{
/*    switch( ins->type ) {
    case DI_X64_call2:
    case DI_X64_call4:
    case DI_X64_jmp2:
    case DI_X64_jmp4:*/
        /* indirect call/jump instructions */
/*        *p++ = '*';
        break;
    default:
        break;
    }*/
    switch( ins->op[i].type & DO_MASK ) {
    case DO_IMMED:
        *p++ = '$';
    }
    p += DisCliValueString( d, ins, i, p );
    switch( ins->op[i].type & DO_MASK ) {
    case DO_REG:
        p = DisAddUnixRegX64( ins->op[i].base, p, flags );
        break;
    case DO_ABSOLUTE:
    case DO_RELATIVE:
    case DO_MEMORY_ABS:
    case DO_MEMORY_REL:
        if( ins->op[i].base != DR_NONE || ins->op[i].index != DR_NONE ) {
            *p++ = '(';
            p = DisAddUnixRegX64( ins->op[i].base, p, flags );
            if( ins->op[i].index != DR_NONE ) {
                *p++ = ',';
                p = DisAddUnixRegX64( ins->op[i].index, p, flags );
                if( ins->op[i].scale != 1 ) {
                    *p++ = ',';
                    *p++ = '0' + ins->op[i].scale;
                }
            }
            *p++ = ')';
        }
        break;
    }
    return( p );
}

static char *DisOpMasmFormat( void *d, dis_dec_ins *ins, dis_format_flags flags,
                        unsigned i, char *p )
{
    unsigned    len;

    if( !( flags & DFF_X86_ALT_INDEXING ) ||
        ( ( ins->op[i].base == DR_NONE ) && ( ins->op[i].index == DR_NONE ) ) ) {
        p += DisCliValueString( d, ins, i, p );
    }
    switch( ins->op[i].type & DO_MASK ) {
    case DO_REG:
        p = DisAddReg( ins->op[i].base, p, flags );
        break;
    case DO_ABSOLUTE:
    case DO_RELATIVE:
    case DO_MEMORY_ABS:
    case DO_MEMORY_REL:
        if( ins->op[i].base != DR_NONE || ins->op[i].index != DR_NONE ) {
            *p++ = '[';
            p = DisAddReg( ins->op[i].base, p, flags );
            if( ins->op[i].index != DR_NONE ) {
                if( ins->op[i].base != DR_NONE ) *p++ = '+';
                p = DisAddReg( ins->op[i].index, p, flags );
                if( ins->op[i].scale != 1 ) {
                    *p++ = '*';
                    *p++ = '0' + ins->op[i].scale;
                }
            }
            if( flags & DFF_X86_ALT_INDEXING ) {
                *p++ = '+';
                len = DisCliValueString( d, ins, i, p );
                switch( *p ) {
                case '-':
                    memmove( p - 1, p, len );
                    --p;
                    break;
                case '\0':
                    --p;
                    break;
                }
                p += len;
            }
            *p++ = ']';
        }
        break;
    }
    return( p );
}

static int NeedSizing( dis_dec_ins *ins, dis_format_flags flags, unsigned op_num )
{
    unsigned    i;

    if( flags & DFF_X86_UNIX ) return( FALSE );
    if( flags & DFF_ASM ) return( TRUE );
/*    switch( ins->type ) {
    case DI_X64_movsx:
    case DI_X64_movzx:
    case DI_X64_outs:*/
        /* these always need sizing */
/*        return( TRUE );
    default:
        break;
    }*/
    for( i = 0; i < ins->num_ops; ++i ) {
        switch( ins->op[i].type & DO_MASK ) {
        case DO_REG:
            if( ( ins->op[i].base <= DR_X64_gs ) ) {
                return( TRUE );
            } else {
                /* if you've got a reg, you know the size */
                return( FALSE );
            }
        }
    }
    return( TRUE );
}

static unsigned X64OpHook( dis_handle *h, void *d, dis_dec_ins *ins,
        dis_format_flags flags, unsigned op_num, char *op_buff )
/**********************************************************************/
{
    char        over;
    char        *p;
    unsigned    len;
    unsigned    ins_flags;

    ins_flags = ins->flags;
    p = op_buff;
    switch( ins->op[op_num].type & DO_MASK ) {
    case DO_MEMORY_ABS:
        if( NeedSizing( ins, flags, op_num ) ) {
            len = DisGetString( DisRefTypeTable[ins->op[op_num].ref_type], p, 0 );
            if( len != 0 ) {
                p += len;
                #define SUFFIX " ptr "
                memcpy( p, SUFFIX, sizeof( SUFFIX ) - 1 );
                p += sizeof( SUFFIX ) - 1;
            }
        }
        if( ( ( ins_flags & SEGOVER ) != 0 )
            && ( ( ins->op[op_num].type & DO_NO_SEG_OVR ) == 0 ) ) {
            switch( ins_flags & SEGOVER ) {
            case DIF_X64_CS:
                over = 'c';
                break;
            case DIF_X64_DS:
                over = 'd';
                break;
            case DIF_X64_ES:
                over = 'e';
                break;
            case DIF_X64_FS:
                over = 'f';
                break;
            case DIF_X64_GS:
                over = 'g';
                break;
            case DIF_X64_SS:
                over = 's';
                break;
            default:
                over = '\0';
            }
            ins_flags &= ~SEGOVER;
            if( flags & DFF_X86_UNIX ) *p++ = '%';
            if( flags & DFF_REG_UP ) {
                *p++ = toupper( over );
                *p++= 'S';
            } else {
                *p++ = over;
                *p++ = 's';
            }
            *p++ = ':';
        }
        break;
    case DO_ABSOLUTE:
    case DO_RELATIVE:
        if( ( flags & DFF_ASM ) && !( flags & DFF_X86_UNIX ) ) {
/*            switch( ins->type ) {
            case DI_X64_call:
            case DI_X64_jmp1:
                #define NEAR_PTR        "near ptr "
                memcpy( p, NEAR_PTR, sizeof( NEAR_PTR ) - 1 );
                p += sizeof( NEAR_PTR ) - 1;
                break;
            case DI_X64_call3:
            case DI_X64_jmp3:
                #define FAR_PTR "far ptr "
                memcpy( p, FAR_PTR, sizeof( FAR_PTR ) - 1 );
                p += sizeof( FAR_PTR ) - 1;
                break;
            default:
                break;
            }*/
        }
        break;
    }
    if( flags & DFF_X86_UNIX ) {
        p = DisOpUnixFormat( d, ins, flags, op_num, p );
    } else {
        p = DisOpMasmFormat( d, ins, flags, op_num, p );
    }
    ins->flags = ins_flags;
    *p = '\0';
    return( p - op_buff );
}

static dis_handler_return X64DecodeTableCheck( int page, dis_dec_ins *ins )
/*************************************************************************/
{
    //printf("X64DecodeTableCheck: page = %ld\n", page);
    switch( page ) {
    case 0:
        return( DHR_DONE );
    case 1:
        if( ( ins->flags & PREFIX_MASK ) == 0 ) {
            return( DHR_DONE );
        } else {
            return ( DHR_INVALID );
        }
    case 2:
        if( ( ins->flags & PREFIX_MASK ) == DIF_X64_OPND_SIZE ) {
            return( DHR_DONE );
        } else {
            return ( DHR_INVALID );
        }
/*    case 3:
        if( ( ins->flags & PREFIX_MASK ) == DIF_X64_REPNE ) {
            return( DHR_DONE );
        } else {
            return ( DHR_INVALID );
        }
    case 4:
        if( ( ins->flags & PREFIX_MASK ) == DIF_X64_REPE ) {
            return( DHR_DONE );
        } else {
            return ( DHR_INVALID );
        }*/
    default:
        return( DHR_DONE );
    }
}

static void process87EMUIns( dis_dec_ins *ins )
/*********************************************/
{
    if( ins->op[ MAX_NUM_OPERANDS - 1 ].value == 0x3C ) {
        switch( ins->opcode & 0xC0 ) {
        case 0xC0:
            ins->flags |= DIF_X64_ES;
            break;
        case 0x80:
            ins->flags |= DIF_X64_CS;
            break;
        case 0x40:
            ins->flags |= DIF_X64_SS;
            break;
        case 0:
            ins->flags |= DIF_X64_DS;
            break;
        }
        ins->opcode |= 0xC0;  // restore FP opcode D8-DF
    } else if( ins->op[ MAX_NUM_OPERANDS - 1 ].value == 0x3D ) {
        ins->opcode = 0x90;   // NOP
    } else {
        ins->opcode += 0xA4;  // restore FP opcode D8-DF
    }
}

static void ByteSwap( dis_handle *h, void *d, dis_dec_ins *ins )
/**************************************************************/
{
    // Nothing to do here - instruction will be decoded byte by byte
}

static void X64PreprocHook( dis_handle *h, void *d, dis_dec_ins *ins )
/********************************************************************/
{
    ByteSwap( h, d, ins );
    if( ins->flags & DIF_X64_EMU_INT ) {
        process87EMUIns( ins );
    }
}

static unsigned X64PostOpHook( dis_handle *h, void *d, dis_dec_ins *ins,
        dis_format_flags flags, unsigned op_num, char *op_buff )
/**********************************************************************/
{
    unsigned len = 0;

/*    if( ins->flags & DIF_X64_EMU_INT ) {
        #define EMU_INT        "; int "
        memcpy( op_buff, EMU_INT, sizeof( EMU_INT ) - 1 );
        len += sizeof( EMU_INT ) - 1;
        op_buff[ len ] = 0;
        if( flags & DFF_INS_UP )
            strupr( op_buff );
        len += DisCliValueString( d, ins, MAX_NUM_OPERANDS - 1, op_buff + len );
    }*/
    return( len );
}

const dis_cpu_data X64Data = {
    X64RangeTable, X64RangeTablePos, X64PreprocHook, X64DecodeTableCheck, X64InsHook, X64FlagHook, X64OpHook, X64PostOpHook, &X64MaxInsName, 1
};
