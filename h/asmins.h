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


#include "asmopnds.h"
#include "asmins1.h"

#ifdef M_I86
 #define ASMFAR far
#else
 #define ASMFAR
#endif

#include "asmsym.h"
#define ins(tok,op1,byte1_info,op2,rm_info,opcode,rm_byte,cpu,prefix) \
                {tok,prefix,byte1_info,rm_info,cpu,{op1,op2},opcode,rm_byte},

#ifdef _WASM_
    struct asm_ins {
        unsigned short  token;                  /* T_ADD, etc */
        unsigned        allowed_prefix  : 3;    /* allowed prefix */
        unsigned        byte1_info      : 2;    /* flags for 1st byte */
        unsigned        rm_info         : 2;    /* info on r/m byte */
        enum asm_cpu    cpu;                    /* CPU type */
        unsigned long   opnd_type[2];           /* asm_opnds */
        unsigned char   opcode;                 /* opcode byte */
        unsigned char   rm_byte;                /* mod_rm_byte */
    };
#else
    struct asm_ins {
        unsigned        token           : 10;   /* T_ADD, etc */
        unsigned        allowed_prefix  : 3;    /* allowed prefix */
        unsigned        byte1_info      : 2;    /* flags for 1st byte */
        unsigned        rm_info         : 2;    /* info on r/m byte */
        unsigned        cpu             : 8;    /* CPU type */
        unsigned long   opnd_type[2];           /* asm_opnds */
        unsigned char   opcode;                 /* opcode byte */
        unsigned char   rm_byte;                /* mod_rm_byte */
    };
#endif

struct asm_code {
    struct {
        signed short ins;           // prefix before instruction, e.g. lock
        signed char  seg;           // segment register override
        unsigned     adrsiz:1;      // address size prefix
        unsigned     opsiz:1;       // operand size prefix
    } prefix;
    memtype         mem_type;       // byte / word / etc. NOT near/far
    long            data[2];
    struct asm_ins  info;
    signed char     extended_ins;
    unsigned char   sib;
    memtype         distance;       // short / near / far / empty
    unsigned        use32:1;
    unsigned        indirect:1;     // CALL/JMP indirect jump
    unsigned        mem_type_fixed:1;
};

ins (T_POR,             OP_MMX,      F_0F,   OP_MMX|OP_M,no_WDS, 0xeb,     0x00,                     P_586, NO_PREFIX)

#define PREFIX_ES   0x26
#define PREFIX_CS   0x2E
#define PREFIX_SS   0x36
#define PREFIX_DS   0x3E
#define PREFIX_FS   0x64
#define PREFIX_GS   0x65

ins (T_PSLLD,           OP_MMX,      F_0F,   OP_MMX|OP_M,no_WDS, 0xf2,     0x00,                     P_586, NO_PREFIX)
ins (T_PSLLD,           OP_MMX,      F_0F,   OP_I8_U,    no_WDS, 0x72,     0x30,                     P_586, NO_PREFIX)
ins (T_PSLLQ,           OP_MMX,      F_0F,   OP_MMX|OP_M,no_WDS, 0xf3,     0x00,                     P_586, NO_PREFIX)
ins (T_PSLLQ,           OP_MMX,      F_0F,   OP_I8_U,    no_WDS, 0x73,     0x30,                     P_586, NO_PREFIX)
ins (T_PSLLW,           OP_MMX,      F_0F,   OP_MMX|OP_M,no_WDS, 0xf1,     0x00,                     P_586, NO_PREFIX)
ins (T_PSLLW,           OP_MMX,      F_0F,   OP_I8_U,    no_WDS, 0x71,     0x30,                     P_586, NO_PREFIX)
ins (T_PSRAD,           OP_MMX,      F_0F,   OP_MMX|OP_M,no_WDS, 0xe2,     0x00,                     P_586, NO_PREFIX)
ins (T_PSRAD,           OP_MMX,      F_0F,   OP_I8_U,    no_WDS, 0x72,     0x20,                     P_586, NO_PREFIX)
ins (T_PSRAW,           OP_MMX,      F_0F,   OP_MMX|OP_M,no_WDS, 0xe1,     0x00,                     P_586, NO_PREFIX)
ins (T_PSRAW,           OP_MMX,      F_0F,   OP_I8_U,    no_WDS, 0x71,     0x20,                     P_586, NO_PREFIX)
ins (T_PSRLD,           OP_MMX,      F_0F,   OP_MMX|OP_M,no_WDS, 0xd2,     0x00,                     P_586, NO_PREFIX)
ins (T_PSRLD,           OP_MMX,      F_0F,   OP_I8_U,    no_WDS, 0x72,     0x10,                     P_586, NO_PREFIX)
ins (T_PSRLQ,           OP_MMX,      F_0F,   OP_MMX|OP_M,no_WDS, 0xd3,     0x00,                     P_586, NO_PREFIX)
ins (T_PSRLQ,           OP_MMX,      F_0F,   OP_I8_U,    no_WDS, 0x73,     0x10,                     P_586, NO_PREFIX)
ins (T_PSRLW,           OP_MMX,      F_0F,   OP_MMX|OP_M,no_WDS, 0xd1,     0x00,                     P_586, NO_PREFIX)
ins (T_PSRLW,           OP_MMX,      F_0F,   OP_I8_U,    no_WDS, 0x71,     0x10,                     P_586, NO_PREFIX)
ins (T_PSUBB,           OP_MMX,      F_0F,   OP_MMX|OP_M,no_WDS, 0xf8,     0x00,                     P_586, NO_PREFIX)
ins (T_PSUBD,           OP_MMX,      F_0F,   OP_MMX|OP_M,no_WDS, 0xfa,     0x00,                     P_586, NO_PREFIX)
ins (T_PSUBSB,          OP_MMX,      F_0F,   OP_MMX|OP_M,no_WDS, 0xe8,     0x00,                     P_586, NO_PREFIX)
ins (T_PSUBSW,          OP_MMX,      F_0F,   OP_MMX|OP_M,no_WDS, 0xe9,     0x00,                     P_586, NO_PREFIX)
ins (T_PSUBUSB,         OP_MMX,      F_0F,   OP_MMX|OP_M,no_WDS, 0xd8,     0x00,                     P_586, NO_PREFIX)
ins (T_PSUBUSW,         OP_MMX,      F_0F,   OP_MMX|OP_M,no_WDS, 0xd9,     0x00,                     P_586, NO_PREFIX)
ins (T_PSUBW,           OP_MMX,      F_0F,   OP_MMX|OP_M,no_WDS, 0xf9,     0x00,                     P_586, NO_PREFIX)

ins (T_PTR,             OP_SPECIAL,  0,      0,          0,      0,        OP_RES_ID,                0,     0)
insa(T_PUBLIC,          OP_SPECIAL,  0,      OP_NONE,    0,      0,        OP_DIRECTIVE,             P_86,  0)

ins (T_PUNPCKHBW,       OP_MMX,      F_0F,   OP_MMX|OP_M,no_WDS, 0x68,     0x00,                     P_586, NO_PREFIX)
ins (T_PUNPCKHDQ,       OP_MMX,      F_0F,   OP_MMX|OP_M,no_WDS, 0x6a,     0x00,                     P_586, NO_PREFIX)
ins (T_PUNPCKHWD,       OP_MMX,      F_0F,   OP_MMX|OP_M,no_WDS, 0x69,     0x00,                     P_586, NO_PREFIX)
ins (T_PUNPCKLBW,       OP_MMX,      F_0F,   OP_MMX|OP_M,no_WDS, 0x60,     0x00,                     P_586, NO_PREFIX)
ins (T_PUNPCKLDQ,       OP_MMX,      F_0F,   OP_MMX|OP_M,no_WDS, 0x62,     0x00,                     P_586, NO_PREFIX)
ins (T_PUNPCKLWD,       OP_MMX,      F_0F,   OP_MMX|OP_M,no_WDS, 0x61,     0x00,                     P_586, NO_PREFIX)

insa(T_PURGE,           OP_SPECIAL,  0,      OP_NONE,    0,      0,        OP_DIRECTIVE,             0,     0)
ins (T_PUSH,            OP_R1632,    0,      OP_NONE,    R_in_OP,0x50,     0x00,                     P_86,  NO_PREFIX)
ins (T_PUSH,            OP_SR2,      0,      OP_NONE,    R_in_OP,0x06,     0x00,                     P_86,  NO_PREFIX)
ins (T_PUSH,            OP_SR,       F_0F,   OP_NONE,    R_in_OP,0x80,     0x00,                     P_386, NO_PREFIX)
ins (T_PUSH,            OP_M,        0,      OP_NONE,    0,      0xFF,     0x30,                     P_86,  NO_PREFIX)
ins (T_PUSH,            OP_I8,       0,      OP_NONE,    R_in_OP,0x6A,     0x00,                     P_186, NO_PREFIX)
ins (T_PUSH,            OP_I,        0,      OP_NONE,    R_in_OP,0x68,     0x00,                     P_186, NO_PREFIX)
ins (T_PUSHA,           OP_NONE,     F_16,   OP_NONE,    no_RM,  0x60,     0x00,                     P_186, NO_PREFIX)
ins (T_PUSHAD,          OP_NONE,     F_32,   OP_NONE,    no_RM,  0x60,     0x00,                     P_386, NO_PREFIX)
insa(T_PUSHCONTEXT,     OP_SPECIAL,  0,      OP_NONE,    0,      0,        OP_DIRECTIVE,             0,     0)
ins (T_PUSHF,           OP_NONE,     F_16,   OP_NONE,    no_RM,  0x9C,     0x00,                     P_86,  NO_PREFIX)
ins (T_PUSHFD,          OP_NONE,     F_32,   OP_NONE,    no_RM,  0x9C,     0x00,                     P_386, NO_PREFIX)
ins (T_PWORD,           OP_SPECIAL,  0,      OP_SPECIAL, 0,      0,        OP_RES_ID|OP_PTR_MODIFIER,0,     0)

ins (T_PXOR,            OP_MMX,      F_0F,   OP_MMX|OP_M,no_WDS, 0xef,     0x00,                     P_586, NO_PREFIX)

ins (T_QWORD,           OP_SPECIAL,  0,      OP_SPECIAL, 0,      0,        OP_RES_ID|OP_PTR_MODIFIER,0,     0)
ins (T_RCL,             OP_R,        0,      OP_I_1,     0,      0xD0,     0x10,                     P_86,  NO_PREFIX)
ins (T_RCL,             OP_R,        0,      OP_I8_U,    0,      0xC0,     0x10,                     P_186, NO_PREFIX)
ins (T_RCL,             OP_R,        0,      OP_CL,      0,      0xD2,     0x10,                     P_86,  NO_PREFIX)
ins (T_RCL,             OP_M_B,      0,      OP_I_1,     0,      0xD0,     0x10,                     P_86,  NO_PREFIX)
ins (T_RCL,             OP_M_B,      0,      OP_I8_U,    0,      0xC0,     0x10,                     P_186, NO_PREFIX)
ins (T_RCL,             OP_M_B,      0,      OP_CL,      0,      0xD2,     0x10,                     P_86,  NO_PREFIX)
ins (T_RCL,             OP_M_W,      0,      OP_I_1,     0,      0xD1,     0x10,                     P_86,  NO_PREFIX)
ins (T_RCL,             OP_M_W,      0,      OP_I8_U,    0,      0xC1,     0x10,                     P_186, NO_PREFIX)
ins (T_RCL,             OP_M_W,      0,      OP_CL,      0,      0xD3,     0x10,                     P_86,  NO_PREFIX)
ins (T_RCL,             OP_M_DW,     0,      OP_I_1,     0,      0xD1,     0x10,                     P_386, NO_PREFIX)
ins (T_RCL,             OP_M_DW,     0,      OP_I8_U,    0,      0xC1,     0x10,                     P_386, NO_PREFIX)
ins (T_RCL,             OP_M_DW,     0,      OP_CL,      0,      0xD3,     0x10,                     P_386, NO_PREFIX)
ins (T_RCR,             OP_R,        0,      OP_I_1,     0,      0xD0,     0x18,                     P_86,  NO_PREFIX)
ins (T_RCR,             OP_R,        0,      OP_I8_U,    0,      0xC0,     0x18,                     P_186, NO_PREFIX)
ins (T_RCR,             OP_R,        0,      OP_CL,      0,      0xD2,     0x18,                     P_86,  NO_PREFIX)
ins (T_RCR,             OP_M_B,      0,      OP_I_1,     0,      0xD0,     0x18,                     P_86,  NO_PREFIX)
ins (T_RCR,             OP_M_B,      0,      OP_I8_U,    0,      0xC0,     0x18,                     P_186, NO_PREFIX)
ins (T_RCR,             OP_M_B,      0,      OP_CL,      0,      0xD2,     0x18,                     P_86,  NO_PREFIX)
ins (T_RCR,             OP_M_W,      0,      OP_I_1,     0,      0xD1,     0x18,                     P_86,  NO_PREFIX)
ins (T_RCR,             OP_M_W,      0,      OP_I8_U,    0,      0xC1,     0x18,                     P_186, NO_PREFIX)
ins (T_RCR,             OP_M_W,      0,      OP_CL,      0,      0xD3,     0x18,                     P_86,  NO_PREFIX)
ins (T_RCR,             OP_M_DW,     0,      OP_I_1,     0,      0xD1,     0x18,                     P_386, NO_PREFIX)
ins (T_RCR,             OP_M_DW,     0,      OP_I8_U,    0,      0xC1,     0x18,                     P_386, NO_PREFIX)
ins (T_RCR,             OP_M_DW,     0,      OP_CL,      0,      0xD3,     0x18,                     P_386, NO_PREFIX)

ins (T_RDMPC,           OP_NONE,     F_0F,   OP_NONE,    no_RM,  0x33,     0x00,                     P_686, NO_PREFIX)

int check_override( int *i );
int OperandSize( unsigned long opnd );
int InRange( unsigned long val, unsigned bytes );
int mem2code( char ss, int index, int base );
int cpu_directive( int i );
int AsmParse( void );
void AsmInit( int cpu, int fpu, int use32 );

ins (T_RDMSR,           OP_NONE,     F_0F,   OP_NONE,    no_RM,  0x32,     0x00,                     P_586, NO_PREFIX)
ins (T_RDTSC,           OP_NONE,     F_0F,   OP_NONE,    no_RM,  0x31,     0x00,                     P_586, NO_PREFIX)
insa(T_READONLY,        OP_SPECIAL,  0,      0,          0,      0,        OP_RES_ID,                0,     0)
insa(T_RECORD,          OP_SPECIAL,  0,      OP_NONE,    0,      0,        OP_DIRECTIVE,             0,     0)
ins (T_REP,             OP_NONE,     0,      OP_NONE,    no_RM,  0xF3,     0x00,                     P_86,  NO_PREFIX)
ins (T_REPE,            OP_NONE,     0,      OP_NONE,    no_RM,  0xF3,     0x00,                     P_86,  NO_PREFIX)
ins (T_REPNE,           OP_NONE,     0,      OP_NONE,    no_RM,  0xF2,     0x00,                     P_86,  NO_PREFIX)
ins (T_REPNZ,           OP_NONE,     0,      OP_NONE,    no_RM,  0xF2,     0x00,                     P_86,  NO_PREFIX)
ins (T_REPZ,            OP_NONE,     0,      OP_NONE,    no_RM,  0xF3,     0x00,                     P_86,  NO_PREFIX)
ins (T_RET,             OP_NONE,     0,      OP_NONE,    no_RM,  0xC3,     0x00,                     P_86,  NO_PREFIX)
ins (T_RET,             OP_I16,      0,      OP_NONE,    no_RM,  0xC2,     0x00,                     P_86,  NO_PREFIX)
ins (T_RETD,            OP_NONE,     F_32,   OP_NONE,    no_RM,  0xCB,     0x00,                     P_386, NO_PREFIX)
ins (T_RETD,            OP_I16,      F_32,   OP_NONE,    no_RM,  0xCA,     0x00,                     P_386, NO_PREFIX)
ins (T_RETF,            OP_NONE,     0,      OP_NONE,    no_RM,  0xCB,     0x00,                     P_86,  NO_PREFIX)
ins (T_RETF,            OP_I16,      0,      OP_NONE,    no_RM,  0xCA,     0x00,                     P_86,  NO_PREFIX)
ins (T_RETFD,           OP_NONE,     F_32,   OP_NONE,    no_RM,  0xCB,     0x00,                     P_386, NO_PREFIX)
ins (T_RETFD,           OP_I16,      F_32,   OP_NONE,    no_RM,  0xCA,     0x00,                     P_386, NO_PREFIX)
ins (T_RETN,            OP_NONE,     0,      OP_NONE,    no_RM,  0xC3,     0x00,                     P_86,  NO_PREFIX)
ins (T_RETN,            OP_I16,      0,      OP_NONE,    no_RM,  0xC2,     0x00,                     P_86,  NO_PREFIX)
ins (T_ROL,             OP_R,        0,      OP_I_1,     0,      0xD0,     0x00,                     P_86,  NO_PREFIX)
ins (T_ROL,             OP_R,        0,      OP_I8_U,    0,      0xC0,     0x00,                     P_186, NO_PREFIX)
ins (T_ROL,             OP_R,        0,      OP_CL,      0,      0xD2,     0x00,                     P_86,  NO_PREFIX)
ins (T_ROL,             OP_M_B,      0,      OP_I_1,     0,      0xD0,     0x00,                     P_86,  NO_PREFIX)
ins (T_ROL,             OP_M_B,      0,      OP_I8_U,    0,      0xC0,     0x00,                     P_186, NO_PREFIX)
ins (T_ROL,             OP_M_B,      0,      OP_CL,      0,      0xD2,     0x00,                     P_86,  NO_PREFIX)
ins (T_ROL,             OP_M_W,      0,      OP_I_1,     0,      0xD1,     0x00,                     P_86,  NO_PREFIX)
ins (T_ROL,             OP_M_W,      0,      OP_I8_U,    0,      0xC1,     0x00,                     P_186, NO_PREFIX)
ins (T_ROL,             OP_M_W,      0,      OP_CL,      0,      0xD3,     0x00,                     P_86,  NO_PREFIX)
ins (T_ROL,             OP_M_DW,     0,      OP_I_1,     0,      0xD1,     0x00,                     P_386, NO_PREFIX)
ins (T_ROL,             OP_M_DW,     0,      OP_I8_U,    0,      0xC1,     0x00,                     P_386, NO_PREFIX)
ins (T_ROL,             OP_M_DW,     0,      OP_CL,      0,      0xD3,     0x00,                     P_386, NO_PREFIX)
ins (T_ROR,             OP_R,        0,      OP_I_1,     0,      0xD0,     0x08,                     P_86,  NO_PREFIX)
ins (T_ROR,             OP_R,        0,      OP_I8_U,    0,      0xC0,     0x08,                     P_186, NO_PREFIX)
ins (T_ROR,             OP_R,        0,      OP_CL,      0,      0xD2,     0x08,                     P_86,  NO_PREFIX)
ins (T_ROR,             OP_M_B,      0,      OP_I_1,     0,      0xD0,     0x08,                     P_86,  NO_PREFIX)
ins (T_ROR,             OP_M_B,      0,      OP_I8_U,    0,      0xC0,     0x08,                     P_186, NO_PREFIX)
ins (T_ROR,             OP_M_B,      0,      OP_CL,      0,      0xD2,     0x08,                     P_86,  NO_PREFIX)
ins (T_ROR,             OP_M_W,      0,      OP_I_1,     0,      0xD1,     0x08,                     P_86,  NO_PREFIX)
ins (T_ROR,             OP_M_W,      0,      OP_I8_U,    0,      0xC1,     0x08,                     P_186, NO_PREFIX)
ins (T_ROR,             OP_M_W,      0,      OP_CL,      0,      0xD3,     0x08,                     P_86,  NO_PREFIX)
ins (T_ROR,             OP_M_DW,     0,      OP_I_1,     0,      0xD1,     0x08,                     P_386, NO_PREFIX)
ins (T_ROR,             OP_M_DW,     0,      OP_I8_U,    0,      0xC1,     0x08,                     P_386, NO_PREFIX)
ins (T_ROR,             OP_M_DW,     0,      OP_CL,      0,      0xD3,     0x08,                     P_386, NO_PREFIX)
ins (T_RSM,             OP_NONE,     F_0F,   OP_NONE,    no_RM,  0xAA,     0x00,                     P_586, NO_PREFIX)
ins (T_SAHF,            OP_NONE,     0,      OP_NONE,    no_RM,  0x9E,     0x00,                     P_86,  NO_PREFIX)
ins (T_SAL,             OP_R,        0,      OP_I_1,     0,      0xD0,     0x20,                     P_86,  NO_PREFIX)
ins (T_SAL,             OP_R,        0,      OP_I8_U,    0,      0xC0,     0x20,                     P_186, NO_PREFIX)
ins (T_SAL,             OP_R,        0,      OP_CL,      0,      0xD2,     0x20,                     P_86,  NO_PREFIX)
ins (T_SAL,             OP_M_B,      0,      OP_I_1,     0,      0xD0,     0x20,                     P_86,  NO_PREFIX)
ins (T_SAL,             OP_M_B,      0,      OP_I8_U,    0,      0xC0,     0x20,                     P_186, NO_PREFIX)
ins (T_SAL,             OP_M_B,      0,      OP_CL,      0,      0xD2,     0x20,                     P_86,  NO_PREFIX)
ins (T_SAL,             OP_M_W,      0,      OP_I_1,     0,      0xD1,     0x20,                     P_86,  NO_PREFIX)
ins (T_SAL,             OP_M_W,      0,      OP_I8_U,    0,      0xC1,     0x20,                     P_186, NO_PREFIX)
ins (T_SAL,             OP_M_W,      0,      OP_CL,      0,      0xD3,     0x20,                     P_86,  NO_PREFIX)
ins (T_SAL,             OP_M_DW,     0,      OP_I_1,     0,      0xD1,     0x20,                     P_386, NO_PREFIX)
ins (T_SAL,             OP_M_DW,     0,      OP_I8_U,    0,      0xC1,     0x20,                     P_386, NO_PREFIX)
ins (T_SAL,             OP_M_DW,     0,      OP_CL,      0,      0xD3,     0x20,                     P_386, NO_PREFIX)
ins (T_SAR,             OP_R,        0,      OP_I_1,     0,      0xD0,     0x38,                     P_86,  NO_PREFIX)
ins (T_SAR,             OP_R,        0,      OP_I8_U,    0,      0xC0,     0x38,                     P_186, NO_PREFIX)
ins (T_SAR,             OP_R,        0,      OP_CL,      0,      0xD2,     0x38,                     P_86,  NO_PREFIX)
ins (T_SAR,             OP_M_B,      0,      OP_I_1,     0,      0xD0,     0x38,                     P_86,  NO_PREFIX)
ins (T_SAR,             OP_M_B,      0,      OP_I8_U,    0,      0xC0,     0x38,                     P_186, NO_PREFIX)
ins (T_SAR,             OP_M_B,      0,      OP_CL,      0,      0xD2,     0x38,                     P_86,  NO_PREFIX)
ins (T_SAR,             OP_M_W,      0,      OP_I_1,     0,      0xD1,     0x38,                     P_86,  NO_PREFIX)
ins (T_SAR,             OP_M_W,      0,      OP_I8_U,    0,      0xC1,     0x38,                     P_186, NO_PREFIX)
ins (T_SAR,             OP_M_W,      0,      OP_CL,      0,      0xD3,     0x38,                     P_86,  NO_PREFIX)
ins (T_SAR,             OP_M_DW,     0,      OP_I_1,     0,      0xD1,     0x38,                     P_386, NO_PREFIX)
ins (T_SAR,             OP_M_DW,     0,      OP_I8_U,    0,      0xC1,     0x38,                     P_386, NO_PREFIX)
ins (T_SAR,             OP_M_DW,     0,      OP_CL,      0,      0xD3,     0x38,                     P_386, NO_PREFIX)
ins (T_SBB,             OP_R1632,    0,      OP_I8,      no_WDS, 0x83,     0x18,                     P_86,  NO_PREFIX)
ins (T_SBB,             OP_A,        0,      OP_I,       no_RM,  0x1C,     0x00,                     P_86,  NO_PREFIX)
ins (T_SBB,             OP_R,        0,      OP_R,       0,      0x18,     0x00,                     P_86,  NO_PREFIX)
ins (T_SBB,             OP_R,        0,      OP_M,       0,      0x1A,     0x00,                     P_86,  NO_PREFIX)
ins (T_SBB,             OP_R,        0,      OP_I,       0,      0x80,     0x18,                     P_86,  NO_PREFIX)
ins (T_SBB,             OP_M_W,      0,      OP_I8,      no_WDS, 0x83,     0x18,                     P_86,  LOCK)
ins (T_SBB,             OP_M_DW,     0,      OP_I8,      no_WDS, 0x83,     0x18,                     P_386, LOCK)
ins (T_SBB,             OP_M,        0,      OP_R,       0,      0x18,     0x00,                     P_86,  LOCK)
ins (T_SBB,             OP_M,        0,      OP_I,       0,      0x80,     0x18,                     P_86,  LOCK)
insa(T_SBYTE,           OP_SPECIAL,  0,      OP_SPECIAL, 0,      0,        OP_RES_ID|OP_PTR_MODIFIER,0,     0)
ins (T_SCAS,            OP_M,        0,      OP_NONE,    no_RM,  0xAE,     0x00,                     P_86,  REPxx)
ins (T_SCASB,           OP_NONE,     0,      OP_NONE,    no_RM,  0xAE,     0x00,                     P_86,  REPxx)
ins (T_SCASD,           OP_NONE,     F_32,   OP_NONE,    no_RM,  0xAF,     0x00,                     P_386, REPxx)
ins (T_SCASW,           OP_NONE,     F_16,   OP_NONE,    no_RM,  0xAF,     0x00,                     P_86,  REPxx)
insa(T_SDWORD,          OP_SPECIAL,  0,      OP_SPECIAL, 0,      0,        OP_RES_ID|OP_PTR_MODIFIER,0,     0)
ins (T_SEG2,            OP_SPECIAL,  0,      0,          0,      0,        OP_UNARY_OPERATOR,        0,     0)
insa(T_SEGMENT,         OP_SPECIAL,  0,      OP_NONE,    0,      0,        OP_DIRECTIVE,             P_86,  0)
ins (T_SETA,            OP_M8_R8,    F_0F,   OP_NONE,    no_WDS, 0x97,     0x00,                     P_386, NO_PREFIX)
ins (T_SETAE,           OP_M8_R8,    F_0F,   OP_NONE,    no_WDS, 0x93,     0x00,                     P_386, NO_PREFIX)
ins (T_SETB,            OP_M8_R8,    F_0F,   OP_NONE,    no_WDS, 0x92,     0x00,                     P_386, NO_PREFIX)
ins (T_SETBE,           OP_M8_R8,    F_0F,   OP_NONE,    no_WDS, 0x96,     0x00,                     P_386, NO_PREFIX)
ins (T_SETC,            OP_M8_R8,    F_0F,   OP_NONE,    no_WDS, 0x92,     0x00,                     P_386, NO_PREFIX)
ins (T_SETE,            OP_M8_R8,    F_0F,   OP_NONE,    no_WDS, 0x94,     0x00,                     P_386, NO_PREFIX)
ins (T_SETG,            OP_M8_R8,    F_0F,   OP_NONE,    no_WDS, 0x9F,     0x00,                     P_386, NO_PREFIX)
ins (T_SETGE,           OP_M8_R8,    F_0F,   OP_NONE,    no_WDS, 0x9D,     0x00,                     P_386, NO_PREFIX)
ins (T_SETL,            OP_M8_R8,    F_0F,   OP_NONE,    no_WDS, 0x9C,     0x00,                     P_386, NO_PREFIX)
ins (T_SETLE,           OP_M8_R8,    F_0F,   OP_NONE,    no_WDS, 0x9E,     0x00,                     P_386, NO_PREFIX)
ins (T_SETNA,           OP_M8_R8,    F_0F,   OP_NONE,    no_WDS, 0x96,     0x00,                     P_386, NO_PREFIX)
ins (T_SETNAE,          OP_M8_R8,    F_0F,   OP_NONE,    no_WDS, 0x92,     0x00,                     P_386, NO_PREFIX)
ins (T_SETNB,           OP_M8_R8,    F_0F,   OP_NONE,    no_WDS, 0x93,     0x00,                     P_386, NO_PREFIX)
ins (T_SETNBE,          OP_M8_R8,    F_0F,   OP_NONE,    no_WDS, 0x97,     0x00,                     P_386, NO_PREFIX)
ins (T_SETNC,           OP_M8_R8,    F_0F,   OP_NONE,    no_WDS, 0x93,     0x00,                     P_386, NO_PREFIX)
ins (T_SETNE,           OP_M8_R8,    F_0F,   OP_NONE,    no_WDS, 0x95,     0x00,                     P_386, NO_PREFIX)
ins (T_SETNG,           OP_M8_R8,    F_0F,   OP_NONE,    no_WDS, 0x9E,     0x00,                     P_386, NO_PREFIX)
ins (T_SETNGE,          OP_M8_R8,    F_0F,   OP_NONE,    no_WDS, 0x9C,     0x00,                     P_386, NO_PREFIX)
ins (T_SETNL,           OP_M8_R8,    F_0F,   OP_NONE,    no_WDS, 0x9D,     0x00,                     P_386, NO_PREFIX)
ins (T_SETNLE,          OP_M8_R8,    F_0F,   OP_NONE,    no_WDS, 0x9F,     0x00,                     P_386, NO_PREFIX)
ins (T_SETNO,           OP_M8_R8,    F_0F,   OP_NONE,    no_WDS, 0x91,     0x00,                     P_386, NO_PREFIX)
ins (T_SETNP,           OP_M8_R8,    F_0F,   OP_NONE,    no_WDS, 0x9B,     0x00,                     P_386, NO_PREFIX)
ins (T_SETNS,           OP_M8_R8,    F_0F,   OP_NONE,    no_WDS, 0x99,     0x00,                     P_386, NO_PREFIX)
ins (T_SETNZ,           OP_M8_R8,    F_0F,   OP_NONE,    no_WDS, 0x95,     0x00,                     P_386, NO_PREFIX)
ins (T_SETO,            OP_M8_R8,    F_0F,   OP_NONE,    no_WDS, 0x90,     0x00,                     P_386, NO_PREFIX)
ins (T_SETP,            OP_M8_R8,    F_0F,   OP_NONE,    no_WDS, 0x9A,     0x00,                     P_386, NO_PREFIX)
ins (T_SETPE,           OP_M8_R8,    F_0F,   OP_NONE,    no_WDS, 0x9A,     0x00,                     P_386, NO_PREFIX)
ins (T_SETPO,           OP_M8_R8,    F_0F,   OP_NONE,    no_WDS, 0x9B,     0x00,                     P_386, NO_PREFIX)
ins (T_SETS,            OP_M8_R8,    F_0F,   OP_NONE,    no_WDS, 0x98,     0x00,                     P_386, NO_PREFIX)
ins (T_SETZ,            OP_M8_R8,    F_0F,   OP_NONE,    no_WDS, 0x94,     0x00,                     P_386, NO_PREFIX)
ins (T_SGDT,            OP_M,        F_0F,   OP_NONE,    no_WDS, 0x01,     0x00,                     P_286p,NO_PREFIX)
ins (T_SHL,             OP_R,        0,      OP_I_1,     0,      0xD0,     0x20,                     P_86,  NO_PREFIX)
ins (T_SHL,             OP_R,        0,      OP_I8_U,    0,      0xC0,     0x20,                     P_186, NO_PREFIX)
ins (T_SHL,             OP_R,        0,      OP_CL,      0,      0xD2,     0x20,                     P_86,  NO_PREFIX)
ins (T_SHL,             OP_M_B,      0,      OP_I_1,     0,      0xD0,     0x20,                     P_86,  NO_PREFIX)
ins (T_SHL,             OP_M_B,      0,      OP_I8_U,    0,      0xC0,     0x20,                     P_186, NO_PREFIX)
ins (T_SHL,             OP_M_B,      0,      OP_CL,      0,      0xD2,     0x20,                     P_86,  NO_PREFIX)
ins (T_SHL,             OP_M_W,      0,      OP_I_1,     0,      0xD1,     0x20,                     P_86,  NO_PREFIX)
ins (T_SHL,             OP_M_W,      0,      OP_I8_U,    0,      0xC1,     0x20,                     P_186, NO_PREFIX)
ins (T_SHL,             OP_M_W,      0,      OP_CL,      0,      0xD3,     0x20,                     P_86,  NO_PREFIX)
ins (T_SHL,             OP_M_DW,     0,      OP_I_1,     0,      0xD1,     0x20,                     P_386, NO_PREFIX)
ins (T_SHL,             OP_M_DW,     0,      OP_I8_U,    0,      0xC1,     0x20,                     P_386, NO_PREFIX)
ins (T_SHL,             OP_M_DW,     0,      OP_CL,      0,      0xD3,     0x20,                     P_386, NO_PREFIX)
ins (T_SHLD,            OP_R1632,    F_0F,   OP_R1632,   no_WDS, 0xA5,     0x00,                     P_386, NO_PREFIX)
ins (T_SHLD,            OP_R1632,    F_0F,   OP_I8,      no_WDS, 0xA4,     0x00,                     P_386, NO_PREFIX)
ins (T_SHLD,            OP_M,        F_0F,   OP_I8,      no_WDS, 0xA4,     0x00,                     P_386, NO_PREFIX)
ins (T_SHLD,            OP_M,        F_0F,   OP_R1632,   no_WDS, 0xA5,     0x00,                     P_386, NO_PREFIX)
ins (T_SHORT,           OP_SPECIAL,  0,      0,          0,      0,        OP_RES_ID,                0,     0)
ins (T_SHR,             OP_R,        0,      OP_I_1,     0,      0xD0,     0x28,                     P_86,  NO_PREFIX)
ins (T_SHR,             OP_R,        0,      OP_I8_U,    0,      0xC0,     0x28,                     P_186, NO_PREFIX)
ins (T_SHR,             OP_R,        0,      OP_CL,      0,      0xD2,     0x28,                     P_86,  NO_PREFIX)
ins (T_SHR,             OP_M_B,      0,      OP_I_1,     0,      0xD0,     0x28,                     P_86,  NO_PREFIX)
ins (T_SHR,             OP_M_B,      0,      OP_I8_U,    0,      0xC0,     0x28,                     P_186, NO_PREFIX)
ins (T_SHR,             OP_M_B,      0,      OP_CL,      0,      0xD2,     0x28,                     P_86,  NO_PREFIX)
ins (T_SHR,             OP_M_W,      0,      OP_I_1,     0,      0xD1,     0x28,                     P_86,  NO_PREFIX)
ins (T_SHR,             OP_M_W,      0,      OP_I8_U,    0,      0xC1,     0x28,                     P_186, NO_PREFIX)
ins (T_SHR,             OP_M_W,      0,      OP_CL,      0,      0xD3,     0x28,                     P_86,  NO_PREFIX)
ins (T_SHR,             OP_M_DW,     0,      OP_I_1,     0,      0xD1,     0x28,                     P_386, NO_PREFIX)
ins (T_SHR,             OP_M_DW,     0,      OP_I8_U,    0,      0xC1,     0x28,                     P_386, NO_PREFIX)
ins (T_SHR,             OP_M_DW,     0,      OP_CL,      0,      0xD3,     0x28,                     P_386, NO_PREFIX)
ins (T_SHRD,            OP_R1632,    F_0F,   OP_R1632,   no_WDS, 0xAD,     0x00,                     P_386, NO_PREFIX)
ins (T_SHRD,            OP_R1632,    F_0F,   OP_I8,      no_WDS, 0xAC,     0x00,                     P_386, NO_PREFIX)
ins (T_SHRD,            OP_M,        F_0F,   OP_I8,      no_WDS, 0xAC,     0x00,                     P_386, NO_PREFIX)
ins (T_SHRD,            OP_M,        F_0F,   OP_R1632,   no_WDS, 0xAD,     0x00,                     P_386, NO_PREFIX)
ins (T_SI,              OP_SPECIAL,  0,      OP_R16_GEN, 0,      6,        OP_REGISTER,              P_86,  IREG)
ins (T_SIDT,            OP_M,        F_0F,   OP_NONE,    no_WDS, 0x01,     0x08,                     P_286p,NO_PREFIX)
insa(T_SIZE,            OP_SPECIAL,  0,      OP_NONE,    0,      0,        OP_UNARY_OPERATOR,        0,     0)
insa(T_SIZEOF,          OP_SPECIAL,  0,      OP_NONE,    0,      0,        OP_UNARY_OPERATOR,        0,     0)
ins (T_SLDT,            OP_R16,      F_0F,   OP_NONE,    no_WDS, 0x00,     0x00,                     P_286p,NO_PREFIX)
ins (T_SLDT,            OP_M16,      F_0F,   OP_NONE,    no_WDS, 0x00,     0x00,                     P_286p,NO_PREFIX)
insa(T_SMALL,           OP_SPECIAL,  0,      0,          0,      0,        OP_RES_ID,                0,     0)
ins (T_SMSW,            OP_R16,      F_0F,   OP_NONE,    no_WDS, 0x01,     0x20,                     P_286p,NO_PREFIX)
ins (T_SMSW,            OP_M16,      F_0F,   OP_NONE,    no_WDS, 0x01,     0x20,                     P_286p,NO_PREFIX)
ins (T_SP,              OP_SPECIAL,  0,      OP_R16_GEN, 0,      4,        OP_REGISTER,              P_86,  0)
ins (T_SS,              OP_SPECIAL,  0,      OP_SR2,     0,      PREFIX_SS,OP_REGISTER,              P_86,  0)
ins (T_ST,              OP_SPECIAL,  0,      OP_ST,      0,      0,        OP_REGISTER,              P_87,  0)
ins (T_STC,             OP_NONE,     0,      OP_NONE,    no_RM,  0xF9,     0x00,                     P_86,  NO_PREFIX)
ins (T_STD,             OP_NONE,     0,      OP_NONE,    no_RM,  0xFD,     0x00,                     P_86,  NO_PREFIX)
insa(T_STDCALL,         OP_SPECIAL,  0,      0,          0,      0,        OP_RES_ID,                0,     0)
ins (T_STI,             OP_NONE,     0,      OP_NONE,    no_RM,  0xFB,     0x00,                     P_86,  NO_PREFIX)
ins (T_STOS,            OP_M,        0,      OP_NONE,    no_RM,  0xAA,     0x00,                     P_86,  REPxx)
ins (T_STOSB,           OP_NONE,     0,      OP_NONE,    no_RM,  0xAA,     0x00,                     P_86,  REPxx)
ins (T_STOSD,           OP_NONE,     F_32,   OP_NONE,    no_RM,  0xAB,     0x00,                     P_386, REPxx)
ins (T_STOSW,           OP_NONE,     F_16,   OP_NONE,    no_RM,  0xAB,     0x00,                     P_86,  REPxx)
ins (T_STR,             OP_R16,      F_0F,   OP_NONE,    no_WDS, 0x00,     0x08,                     P_286p,NO_PREFIX)
ins (T_STR,             OP_M16,      F_0F,   OP_NONE,    no_WDS, 0x00,     0x08,                     P_286p,NO_PREFIX)
insa(T_STRUC,           OP_SPECIAL,  0,      0,          0,      0,        OP_DIRECTIVE,             0,     0)
insa(T_STRUCT,          OP_SPECIAL,  0,      0,          0,      0,        OP_DIRECTIVE,             0,     0)
ins (T_SUB,             OP_R1632,    0,      OP_I8,      no_WDS, 0x83,     0x28,                     P_86,  NO_PREFIX)
ins (T_SUB,             OP_A,        0,      OP_I,       no_RM,  0x2C,     0x00,                     P_86,  NO_PREFIX)
ins (T_SUB,             OP_R,        0,      OP_R,       0,      0x28,     0x00,                     P_86,  NO_PREFIX)
ins (T_SUB,             OP_R,        0,      OP_M,       0,      0x2A,     0x00,                     P_86,  NO_PREFIX)
ins (T_SUB,             OP_R,        0,      OP_I,       0,      0x80,     0x28,                     P_86,  NO_PREFIX)
ins (T_SUB,             OP_M_W,      0,      OP_I8,      no_WDS, 0x83,     0x28,                     P_86,  LOCK)
ins (T_SUB,             OP_M_DW,     0,      OP_I8,      no_WDS, 0x83,     0x28,                     P_386, LOCK)
ins (T_SUB,             OP_M,        0,      OP_R,       0,      0x28,     0x00,                     P_86,  LOCK)
ins (T_SUB,             OP_M,        0,      OP_I,       0,      0x80,     0x28,                     P_86,  LOCK)
insa(T_SUBTITLE,        OP_SPECIAL,  0,      OP_NONE,    0,      0,        OP_DIRECTIVE,             0,     0)
insa(T_SUBTTL,          OP_SPECIAL,  0,      OP_NONE,    0,      0,        OP_DIRECTIVE,             0,     0)
insa(T_SWORD,           OP_SPECIAL,  0,      OP_SPECIAL, 0,      0,        OP_RES_ID|OP_PTR_MODIFIER,0,     0)
insa(T_SYSCALL,         OP_SPECIAL,  0,      0,          0,      0,        OP_RES_ID,                0,     0)
ins (T_TBYTE,           OP_SPECIAL,  0,      OP_SPECIAL, 0,      0,        OP_RES_ID|OP_PTR_MODIFIER,0,     0)
ins (T_TEST,            OP_A,        0,      OP_I,       no_RM,  0xA8,     0x00,                     P_86,  NO_PREFIX)
ins (T_TEST,            OP_R,        0,      OP_R,       0,      0x84,     0x00,                     P_86,  NO_PREFIX)
ins (T_TEST,            OP_R,        0,      OP_M,       0,      0x84,     0x00,                     P_86,  NO_PREFIX)
ins (T_TEST,            OP_R,        0,      OP_I,       0,      0xF6,     0x00,                     P_86,  NO_PREFIX)
ins (T_TEST,            OP_M,        0,      OP_R,       0,      0x84,     0x00,                     P_86,  NO_PREFIX)
ins (T_TEST,            OP_M,        0,      OP_I,       0,      0xF6,     0x00,                     P_86,  NO_PREFIX)
insa(T_TEXTEQU,         OP_SPECIAL,  0,      OP_NONE,    0,      0,        OP_DIRECTIVE,             0,     0)
insa(T_THIS,            OP_SPECIAL,  0,      OP_NONE,    0,      0,        OP_DIRECTIVE,             0,     0)
insa(T_TINY,            OP_SPECIAL,  0,      0,          0,      0,        OP_RES_ID,                0,     0)
insa(T_TITLE,           OP_SPECIAL,  0,      OP_NONE,    0,      0,        OP_DIRECTIVE,             0,     0)
ins (T_TR3,             OP_SPECIAL,  0,      OP_TR,      0,      3,        OP_REGISTER,              P_486, 0)
ins (T_TR4,             OP_SPECIAL,  0,      OP_TR,      0,      4,        OP_REGISTER,              P_486, 0)
ins (T_TR5,             OP_SPECIAL,  0,      OP_TR,      0,      5,        OP_REGISTER,              P_486, 0)
ins (T_TR6,             OP_SPECIAL,  0,      OP_TR,      0,      6,        OP_REGISTER,              P_486, 0)
ins (T_TR7,             OP_SPECIAL,  0,      OP_TR,      0,      7,        OP_REGISTER,              P_386, 0)
insa(T_TYPEDEF,         OP_SPECIAL,  0,      OP_NONE,    0,      0,        OP_DIRECTIVE,             0,     0)
insa(T_UNION,           OP_SPECIAL,  0,      OP_NONE,    0,      0,        OP_DIRECTIVE,             0,     0)
insa(T_USE16,           OP_SPECIAL,  0,      0,          0,      0,        OP_RES_ID,                0,     0)
insa(T_USE32,           OP_SPECIAL,  0,      0,          0,      0,        OP_RES_ID,                0,     0)
insa(T_USES,            OP_SPECIAL,  0,      0,          0,      0,        OP_RES_ID,                0,     0)
insa(T_VARARG,          OP_SPECIAL,  0,      0,          0,      0,        OP_RES_ID,                0,     0)
ins (T_VERR,            OP_R16,      F_0F,   OP_NONE,    no_WDS, 0x00,     0x20,                     P_286p,NO_PREFIX)
ins (T_VERR,            OP_M16,      F_0F,   OP_NONE,    no_WDS, 0x00,     0x20,                     P_286p,NO_PREFIX)
ins (T_VERW,            OP_R16,      F_0F,   OP_NONE,    no_WDS, 0x00,     0x28,                     P_286p,NO_PREFIX)
ins (T_VERW,            OP_M16,      F_0F,   OP_NONE,    no_WDS, 0x00,     0x28,                     P_286p,NO_PREFIX)
ins (T_WAIT,            OP_NONE,     0,      OP_NONE,    no_RM,  0x9B,     0x00,                     P_86,  NO_PREFIX)
insa(T_WATCOM_C,        OP_SPECIAL,  0,      0,          0,      0,        OP_RES_ID,                0,     0)
ins (T_WBINVD,          OP_NONE,     F_0F,   OP_NONE,    no_RM,  0x09,     0x00,                     P_486, NO_PREFIX)
insa(T_WIDTH,           OP_SPECIAL,  0,      OP_NONE,    0,      0,        OP_DIRECTIVE,             0,     0)
ins (T_WORD,            OP_SPECIAL,  0,      OP_SPECIAL, 0,      0,        OP_RES_ID|OP_PTR_MODIFIER,0,     0)
ins (T_WRMSR,           OP_NONE,     F_0F,   OP_NONE,    no_RM,  0x30,     0x00,                     P_586, NO_PREFIX)
ins (T_XADD,            OP_R,        F_0F,   OP_R,       0,      0xC0,     0x00,                     P_486, NO_PREFIX)
ins (T_XADD,            OP_M,        F_0F,   OP_R,       0,      0xC0,     0x00,                     P_486, LOCK)
ins (T_XCHG,            OP_A,        0,      OP_R1632,   R_in_OP,0x90,     0x00,                     P_86,  NO_PREFIX)
ins (T_XCHG,            OP_R1632,    0,      OP_A,       R_in_OP,0x90,     0x00,                     P_86,  NO_PREFIX)
ins (T_XCHG,            OP_R,        0,      OP_R,       0,      0x86,     0x00,                     P_86,  NO_PREFIX)
ins (T_XCHG,            OP_R,        0,      OP_M,       0,      0x86,     0x00,                     P_86,  LOCK)
ins (T_XCHG,            OP_M,        0,      OP_R,       0,      0x86,     0x00,                     P_86,  LOCK)
ins (T_XLAT,            OP_M,        0,      OP_NONE,    no_RM,  0xD7,     0x00,                     P_86,  NO_PREFIX)
ins (T_XLAT,            OP_NONE,     0,      OP_NONE,    no_RM,  0xD7,     0x00,                     P_86,  NO_PREFIX)
ins (T_XLATB,           OP_M,        0,      OP_NONE,    no_RM,  0xD7,     0x00,                     P_86,  NO_PREFIX)
ins (T_XLATB,           OP_NONE,     0,      OP_NONE,    no_RM,  0xD7,     0x00,                     P_86,  NO_PREFIX)
ins (T_XOR,             OP_R1632,    0,      OP_I8,      no_WDS, 0x83,     0x30,                     P_86,  NO_PREFIX)
ins (T_XOR,             OP_A,        0,      OP_I,       no_RM,  0x34,     0x00,                     P_86,  NO_PREFIX)
ins (T_XOR,             OP_R,        0,      OP_R,       0,      0x30,     0x00,                     P_86,  NO_PREFIX)
ins (T_XOR,             OP_R,        0,      OP_M,       0,      0x32,     0x00,                     P_86,  NO_PREFIX)
ins (T_XOR,             OP_R,        0,      OP_I,       0,      0x80,     0x30,                     P_86,  NO_PREFIX)
ins (T_XOR,             OP_M_W,      0,      OP_I8,      no_WDS, 0x83,     0x30,                     P_86,  LOCK)
ins (T_XOR,             OP_M_DW,     0,      OP_I8,      no_WDS, 0x83,     0x30,                     P_386, LOCK)
ins (T_XOR,             OP_M,        0,      OP_R,       0,      0x30,     0x00,                     P_86,  LOCK)
ins (T_XOR,             OP_M,        0,      OP_I,       0,      0x80,     0x30,                     P_86,  LOCK)
};
