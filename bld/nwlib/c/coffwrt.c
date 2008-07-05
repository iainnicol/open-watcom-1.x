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
* Description:  Write COFF style imports.
*
****************************************************************************/


#include "wlib.h"
#include "walloca.h"
#include <assert.h>
#include <error.h>

//IMPORT_DESCRIPT optional header

static unsigned_8       CoffImportDescriptorHeader[] = {
 0x0b,0x01,0x02,0x32,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
 0x00,0x10,0x00,0x00,0x00,0x02,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x00,0x00,0x10,0x00,0x00,
 0x00,0x00,0x10,0x00,0x00,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x00,0x00,0x00,
 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};

static unsigned_8       CoffImportAxpText[] = {
 0x00,0x00,0x7F,0x27,0x00,0x00,0x7B,0xA3,0x00,0x00,0xFB,0x6B
};

static unsigned_8       CoffImportPpcText[] = {
 0x00,0x00,0x62,0x81,0x00,0x00,0x8B,0x81,0x04,0x00,0x41,0x90,0xA6,0x03,0x89,0x7D,
 0x04,0x00,0x4B,0x80,0x20,0x04,0x80,0x4E
};

static unsigned_8       CoffImportPpcPdata[] = {
 0x00,0x00,0x00,0x00,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x00,0x00,0x00,
 0x0D,0x00,0x00,0x00
};

static unsigned_8       CoffImportX86Text[] = {
 0xFF,0x25,0x00,0x00,0x00,0x00
};

static void InitCoffFile( coff_lib_file *c_file )
{
    c_file->string_table = MemAlloc( INIT_MAX_SIZE_COFF_STRING_TABLE );
    c_file->max_string_table_size = INIT_MAX_SIZE_COFF_STRING_TABLE;

}
static void SetCoffFile( coff_lib_file *c_file, short processor,
     unsigned_32 time_stamp, unsigned_16 opt_hdr_size)
{
    switch( processor ) {
    case WL_PROC_PPC:
        c_file->header.cpu_type = IMAGE_FILE_MACHINE_POWERPC;
        break;
    case WL_PROC_AXP:
        c_file->header.cpu_type = IMAGE_FILE_MACHINE_ALPHA;
        break;
    case WL_PROC_X86:
    default:
        c_file->header.cpu_type = IMAGE_FILE_MACHINE_I386;
        break;
    }
    c_file->header.num_sections = 0;
    c_file->header.time_stamp = time_stamp;
    c_file->header.num_symbols = 0;
    c_file->header.opt_hdr_size = opt_hdr_size;
    c_file->header.flags = IMAGE_FILE_32BIT_MACHINE;
    c_file->string_table_size = 0;
}

static void FiniCoffLibFile( coff_lib_file *c_file )
{
    MemFree( c_file->string_table );
}

static void AddCoffString( coff_lib_file  *c_file, char *name, int len )
{
    len++;
    if( ( c_file->string_table_size + len ) >= c_file->max_string_table_size ) {
        c_file->max_string_table_size *= 2;
        c_file->string_table = (char *)MemRealloc( c_file->string_table, c_file->max_string_table_size );
    }
    memcpy( c_file->string_table + c_file->string_table_size, name, len );
    c_file->string_table_size += len;
}

static void AddCoffSection( coff_lib_file *c_file, char *name, unsigned_32 size,
    unsigned_16 num_relocs, unsigned_32 flags )
{
    coff_section_header     *section;
    int                     len;

    section = c_file->section + c_file->header.num_sections;
    len = strlen( name );
    memset( section, 0, COFF_SECTION_HEADER_SIZE );
    if( len > COFF_SEC_NAME_LEN ) {
        section->name[0] = '/';
        ultoa( c_file->string_table_size + 4, section->name + 1, 10 );
        AddCoffString( c_file, name, len );
    } else {
        memcpy( section->name, name, len );
    }
    section->size = size;
    section->num_relocs = num_relocs;
    section->flags = flags;
    c_file->header.num_sections++;
}

static void AddCoffSymbol( coff_lib_file *c_file, char *name, unsigned_32 value,
    signed_16 sec_num,  unsigned_16 type, unsigned_8 class, unsigned_8 num_aux )
{
    coff_symbol _WCUNALIGNED    *sym;
    int                         len;

    sym = c_file->symbol + c_file->header.num_symbols;
    len = strlen( name );
    if( len > COFF_SYM_NAME_LEN ) {
        sym->name.non_name.zeros = 0;
        sym->name.non_name.offset = c_file->string_table_size + 4;
        AddCoffString( c_file, name, len );
    } else {
        memset( sym->name.name_string, 0, COFF_SYM_NAME_LEN );
        memcpy( sym->name.name_string, name, len );
    }
    sym->value = value;
    sym->sec_num = sec_num;
    sym->type = type;
    sym->storage_class = class;
    sym->num_aux = num_aux;
    c_file->header.num_symbols++;
}

static void AddCoffSymSec( coff_lib_file *c_file, unsigned_8 selection )
{
    coff_sym_section _WCUNALIGNED   *sym;
    char                            name[9];
    coff_section_header             *section;

    section = c_file->section + c_file->header.num_sections - 1;
    memcpy( name, section->name, 8 );
    name[8]='\0';
    AddCoffSymbol( c_file, name, 0x0, c_file->header.num_sections, IMAGE_SYM_TYPE_NULL,
        IMAGE_SYM_CLASS_STATIC, 1 );
    sym = (coff_sym_section *) (c_file->symbol + c_file->header.num_symbols);
    sym->length = section->size;
    sym->num_relocs = section->num_relocs;
    sym->num_line_numbers = 0;
    sym->checksum = 0;
    if( selection == IMAGE_COMDAT_SELECT_ASSOCIATIVE ) {
        sym->number = c_file->header.num_sections -1;
                                //according to docs this should be one based
                                //index but test on microsoft lib shows zero
                                //based. so if you want one based add one here
    } else {
        sym->number = 0;
    }
    sym->selection = selection;
    c_file->header.num_symbols++;
}



static void WriteCoffFileHeader( libfile io, coff_lib_file *c_file )
{
    unsigned            i;
    unsigned_32         d_ptr;

    d_ptr = COFF_FILE_HEADER_SIZE + c_file->header.opt_hdr_size
            + c_file->header.num_sections * COFF_SECTION_HEADER_SIZE;
    for( i = 0; i < c_file->header.num_sections; i++ ) {
        c_file->section[i].rawdata_ptr = d_ptr;
        d_ptr += c_file->section[i].size;
        c_file->section[i].reloc_ptr = d_ptr;
        d_ptr += c_file->section[i].num_relocs * COFF_RELOC_SIZE;
    }
    c_file->header.sym_table = d_ptr;
    LibWrite( io, &( c_file->header ), COFF_FILE_HEADER_SIZE );
}

static void WriteCoffSections( libfile io, coff_lib_file *c_file )
{
    LibWrite( io, c_file->section, c_file->header.num_sections * COFF_SECTION_HEADER_SIZE );
}

static void WriteCoffSymbols( libfile io, coff_lib_file *c_file )
{
    LibWrite( io, c_file->symbol, c_file->header.num_symbols * COFF_SYM_SIZE );
}

static void WriteCoffReloc( libfile io, unsigned_32 offset, unsigned_32 sym_tab_index, unsigned_16 type )
{
    //output is buffered so no point in putting COFF_RELOC struct
    LibWrite( io, &offset, sizeof( offset ) );
    LibWrite( io, &sym_tab_index, sizeof( sym_tab_index ) );
    LibWrite( io, &type, sizeof( type ) );
}

static void WriteCoffStringTable( libfile io, coff_lib_file *c_file )
{
    c_file->string_table_size += 4;
    LibWrite( io, &( c_file->string_table_size ), 4 );
    LibWrite( io, c_file->string_table, c_file->string_table_size - 4 );
}


void CoffWriteImport( libfile io, sym_file *file )
{
    unsigned                dll_name_len;
    unsigned                sym_name_len;
    unsigned                exported_name_len;
    unsigned_16             type;
    coff_lib_file           c_file;
    unsigned_16             ordinal;
    unsigned_32             sym_idx;
    signed_16               sec_num;
    char                    *buffer;
    char                    *dllName;
    char                    *symName;
    char                    *exportedName;

    InitCoffFile( &c_file );
    // We are being extremely cautious in the following lines of code
    // up to the switch statement.
    dll_name_len = 0;
    dllName = file->import->DLLName;
    if( dllName != NULL ) {
        dll_name_len = strlen( dllName);
    }
    sym_name_len = 0;
    symName = file->import->symName;
    if( symName != NULL ) {
        sym_name_len = strlen( symName );
    }
    exported_name_len = 0;
    exportedName = file->import->exportedName;
    if( exportedName == NULL ) {
        exportedName = symName; // use this instead
    }
    if( exportedName != NULL ) {
        exported_name_len = strlen( exportedName );
    }
    switch( file->import->type ) {
    case IMPORT_DESCRIPTOR:
        switch( file->import->processor ) {
        case WL_PROC_PPC:
            CoffImportDescriptorHeader[3] = 0x3c;
            type = IMAGE_REL_PPC_IFGLUE;
            break;
        case WL_PROC_AXP:
            CoffImportDescriptorHeader[3] = 0x32;
            type = IMAGE_REL_ALPHA_REFLONGNB;
            break;
        default:
            file->import->processor = WL_PROC_X86;
        case WL_PROC_X86:
            CoffImportDescriptorHeader[3] = 0x32;
            type = IMAGE_REL_I386_DIR32NB;
            break;
        }
        SetCoffFile( &c_file, file->import->processor, file->arch.date, 0xe0 );
        AddCoffSection( &c_file, ".idata$2", 0x14, 3, IMAGE_SCN_ALIGN_1BYTES
            | IMAGE_SCN_CNT_INITIALIZED_DATA | IMAGE_SCN_MEM_READ | IMAGE_SCN_MEM_WRITE );
        assert( dll_name_len != 0 );
        if( dll_name_len == 0 ) FatalError( ERR_CANT_DO_IMPORT, "AR", "NO DLL NAME" );
        buffer = alloca( dll_name_len + 64 );
        AddCoffSection( &c_file, ".idata$6", ( dll_name_len | 1 ) + 5, 0, IMAGE_SCN_ALIGN_2BYTES
            | IMAGE_SCN_CNT_INITIALIZED_DATA | IMAGE_SCN_MEM_READ | IMAGE_SCN_MEM_WRITE );
        strcpy( buffer, "__IMPORT_DESCRIPTOR_" );
        strcat( buffer, dllName );
        AddCoffSymbol( &c_file, buffer, 0x0, 1, IMAGE_SYM_TYPE_NULL,
            IMAGE_SYM_CLASS_EXTERNAL, 0 );
        AddCoffSymbol( &c_file, ".idata$2", 0xC0000040, 1, IMAGE_SYM_TYPE_NULL,
            IMAGE_SYM_CLASS_STATIC, 0 );
        AddCoffSymbol( &c_file, ".idata$6", 0x0, 2, IMAGE_SYM_TYPE_NULL,
            IMAGE_SYM_CLASS_SECTION, 0 );
        AddCoffSymbol( &c_file, ".idata$4", 0xC0000040, 0, IMAGE_SYM_TYPE_NULL,
            IMAGE_SYM_CLASS_SECTION, 0 );
        AddCoffSymbol( &c_file, ".idata$5", 0xC0000040, 0, IMAGE_SYM_TYPE_NULL,
            IMAGE_SYM_CLASS_SECTION, 0 );
        AddCoffSymbol( &c_file, "__NULL_IMPORT_DESCRIPTOR", 0x0, 0, IMAGE_SYM_TYPE_NULL,
            IMAGE_SYM_CLASS_EXTERNAL, 0 );
        buffer[0] = 0x7f;
        strcpy( buffer + 1, dllName );
        strcpy( buffer + 1 + dll_name_len, "_NULL_THUNK_DATA" );
        AddCoffSymbol( &c_file, buffer, 0x0, 0, IMAGE_SYM_TYPE_NULL,
            IMAGE_SYM_CLASS_EXTERNAL, 0 );
        WriteCoffFileHeader( io, &c_file );
        LibWrite( io, CoffImportDescriptorHeader, 0xe0 );
        WriteCoffSections( io, &c_file );
        memset( buffer, 0, 0x14 );
        LibWrite( io, buffer, 0x14 );
        WriteCoffReloc( io, 0xc, 2, type );
        WriteCoffReloc( io, 0x0, 3, type );
        WriteCoffReloc( io, 0x10, 4, type );
        LibWrite( io, dllName, dll_name_len );
        LibWrite( io, ".dll", 5 );
        if( !( dll_name_len & 1 ) ) {
            LibWrite( io, "\0", 1 );
        }
        break;
    case NULL_IMPORT_DESCRIPTOR:
        SetCoffFile( &c_file, file->import->processor, file->arch.date, 0 );
        AddCoffSection( &c_file, ".idata$3", 0x14, 0, IMAGE_SCN_ALIGN_1BYTES
            | IMAGE_SCN_CNT_INITIALIZED_DATA | IMAGE_SCN_MEM_READ | IMAGE_SCN_MEM_WRITE );
        AddCoffSymbol( &c_file,"__NULL_IMPORT_DESCRIPTOR", 0x0, 1, IMAGE_SYM_TYPE_NULL,
            IMAGE_SYM_CLASS_EXTERNAL, 0 );
        WriteCoffFileHeader( io, &c_file );
        WriteCoffSections( io, &c_file );
        buffer = alloca( 0x14 );
        memset( buffer, 0 , 0x14 );
        LibWrite( io, buffer, 0x14 );
        break;
    case NULL_THUNK_DATA:
        SetCoffFile( &c_file, file->import->processor, file->arch.date, 0 );
        AddCoffSection( &c_file, ".idata$5", 0x4, 0, IMAGE_SCN_ALIGN_4BYTES
            | IMAGE_SCN_CNT_INITIALIZED_DATA | IMAGE_SCN_MEM_READ | IMAGE_SCN_MEM_WRITE );
        AddCoffSection( &c_file, ".idata$4", 0x4, 0, IMAGE_SCN_ALIGN_4BYTES
            | IMAGE_SCN_CNT_INITIALIZED_DATA | IMAGE_SCN_MEM_READ | IMAGE_SCN_MEM_WRITE );
        assert( dll_name_len != 0 );
        if( dll_name_len == 0 ) FatalError( ERR_CANT_DO_IMPORT, "AR", "NO DLL NAME" );
        buffer = alloca( dll_name_len + 64 );
        buffer[0] = 0x7f;
        strcpy( buffer + 1, dllName );
        strcpy( buffer + 1 + dll_name_len, "_NULL_THUNK_DATA" );
        AddCoffSymbol( &c_file, buffer, 0x0, 1, IMAGE_SYM_TYPE_NULL,
            IMAGE_SYM_CLASS_EXTERNAL, 0 );
        WriteCoffFileHeader( io, &c_file );
        WriteCoffSections( io, &c_file );
        memset( buffer, 0 , 0x8 );
        LibWrite( io, buffer, 0x8 );
        break;
    case ORDINAL:
        SetCoffFile( &c_file, file->import->processor, file->arch.date, 0 );
        assert( dll_name_len != 0 );
        if( dll_name_len == 0 ) FatalError( ERR_CANT_DO_IMPORT, "AR", "NO DLL NAME" );
        assert( sym_name_len != 0 );
        if( sym_name_len == 0 ) FatalError( ERR_CANT_DO_IMPORT, "AR", "NO SYMBOL NAME" );
        buffer = alloca( max( dll_name_len, sym_name_len ) + 64 );
        switch( file->import->processor ) {
        case WL_PROC_AXP:
            AddCoffSection( &c_file, ".text", 0xc, 3, IMAGE_SCN_ALIGN_16BYTES
                | IMAGE_SCN_LNK_COMDAT | IMAGE_SCN_CNT_CODE
                | IMAGE_SCN_MEM_READ | IMAGE_SCN_MEM_EXECUTE );
            type = 0x20;
            sec_num = 1;
            break;
        case WL_PROC_PPC:
            AddCoffSection( &c_file, ".text", 0x18, 1, IMAGE_SCN_ALIGN_4BYTES
                | IMAGE_SCN_LNK_COMDAT | IMAGE_SCN_CNT_CODE
                | IMAGE_SCN_MEM_READ | IMAGE_SCN_MEM_EXECUTE );
            AddCoffSymSec( &c_file, IMAGE_COMDAT_SELECT_NODUPLICATES );
            strcpy( buffer, ".." );
            strcpy( buffer + 2, symName );
            AddCoffSymbol( &c_file, buffer, 0x0, 1, 0x20,
                IMAGE_SYM_CLASS_EXTERNAL, 0 );
            AddCoffSection( &c_file, ".pdata", 0x14, 4, IMAGE_SCN_ALIGN_1BYTES
                | IMAGE_SCN_LNK_COMDAT | IMAGE_SCN_CNT_INITIALIZED_DATA
                | IMAGE_SCN_MEM_READ );
            AddCoffSymSec( &c_file, IMAGE_COMDAT_SELECT_ASSOCIATIVE );
            AddCoffSection( &c_file, ".reldata", 0x8, 2, IMAGE_SCN_ALIGN_8BYTES
                | IMAGE_SCN_LNK_COMDAT | IMAGE_SCN_CNT_INITIALIZED_DATA
                | IMAGE_SCN_MEM_READ |  IMAGE_SCN_MEM_WRITE );
            type = IMAGE_SYM_TYPE_NULL;
            sec_num = 3;
            break;
        default:
            file->import->processor = WL_PROC_X86;
        case WL_PROC_X86:
            AddCoffSection( &c_file, ".text", 0x6, 1, IMAGE_SCN_ALIGN_2BYTES
                | IMAGE_SCN_LNK_COMDAT | IMAGE_SCN_CNT_CODE
                | IMAGE_SCN_MEM_READ | IMAGE_SCN_MEM_EXECUTE );
            type = 0x20;
            sec_num = 1;
            break;
        }
        AddCoffSymSec( &c_file, IMAGE_COMDAT_SELECT_NODUPLICATES );
        AddCoffSymbol( &c_file, symName, 0x0, sec_num, type,
                IMAGE_SYM_CLASS_EXTERNAL, 0 );
        AddCoffSection( &c_file, ".idata$5", 0x4, 0, IMAGE_SCN_ALIGN_4BYTES
            | IMAGE_SCN_LNK_COMDAT | IMAGE_SCN_CNT_INITIALIZED_DATA
            | IMAGE_SCN_MEM_READ |  IMAGE_SCN_MEM_WRITE );
        AddCoffSymSec( &c_file, IMAGE_COMDAT_SELECT_NODUPLICATES );
        strcpy( buffer, "__imp_" );
        strcat( buffer, symName );
        AddCoffSymbol( &c_file, buffer, 0x0, c_file.header.num_sections,
            IMAGE_SYM_TYPE_NULL, IMAGE_SYM_CLASS_EXTERNAL, 0 );
        AddCoffSection( &c_file, ".idata$4", 0x4, 0, IMAGE_SCN_ALIGN_4BYTES
            | IMAGE_SCN_LNK_COMDAT | IMAGE_SCN_CNT_INITIALIZED_DATA
            | IMAGE_SCN_MEM_READ |  IMAGE_SCN_MEM_WRITE );
        AddCoffSymSec( &c_file, IMAGE_COMDAT_SELECT_ASSOCIATIVE );
        if( file->import->processor == WL_PROC_PPC ) {
            AddCoffSymbol( &c_file, ".toc", 0x0, 0,
                IMAGE_SYM_TYPE_NULL, IMAGE_SYM_CLASS_EXTERNAL, 0 );
        }
        strcpy( buffer, "__IMPORT_DESCRIPTOR_" );
        strcat( buffer, dllName );
        AddCoffSymbol( &c_file, buffer, 0x0, 0,
            IMAGE_SYM_TYPE_NULL, IMAGE_SYM_CLASS_EXTERNAL, 0 );
        WriteCoffFileHeader( io, &c_file );
        WriteCoffSections( io, &c_file );
        switch( file->import->processor ) {
        case WL_PROC_AXP:
            LibWrite( io, CoffImportAxpText, 0x0c );
            WriteCoffReloc( io, 0x0, 5, IMAGE_REL_ALPHA_REFHI );
            WriteCoffReloc( io, 0x0, 2, IMAGE_REL_ALPHA_PAIR );
            WriteCoffReloc( io, 0x4, 5, IMAGE_REL_ALPHA_REFLO );
            break;
        case WL_PROC_PPC:
            LibWrite( io, CoffImportPpcText, 0x18 );
            WriteCoffReloc( io, 0x0, 0xa, IMAGE_REL_PPC_TOCREL14 | IMAGE_REL_PPC_TOCDEFN );
            LibWrite( io, CoffImportPpcPdata, 0x14 );
            WriteCoffReloc( io, 0x0, 2, IMAGE_REL_PPC_ADDR32 );
            WriteCoffReloc( io, 0x4, 2, IMAGE_REL_PPC_ADDR32 );
            WriteCoffReloc( io, 0x10, 2, IMAGE_REL_PPC_ADDR32 );
            WriteCoffReloc( io, 0x80410004, 2, IMAGE_REL_PPC_SECTION );
            memset( buffer, 0, 8 );
            LibWrite( io, buffer, 8 );
            WriteCoffReloc( io, 0x0, 2, IMAGE_REL_PPC_ADDR32 );
            WriteCoffReloc( io, 0x4, 0xF, IMAGE_REL_PPC_ADDR32 );
            break;
        default:
            file->import->processor = WL_PROC_X86;
        case WL_PROC_X86:
            LibWrite( io, CoffImportX86Text, 0x6 );
            WriteCoffReloc( io, 0x2, 5, IMAGE_REL_I386_DIR32 );
            break;
        }
        memset( buffer, 0, 4 );
        ordinal = file->import->ordinal;
        LibWrite( io, &ordinal, 2 );
        type = 0x8000;
        LibWrite( io, &type, 2 );
        LibWrite( io, &ordinal, 2 );
        LibWrite( io, &type, 2 );
        break;
    case NAMED:
        SetCoffFile( &c_file, file->import->processor, file->arch.date, 0 );
        assert( dll_name_len != 0 );
        if( dll_name_len == 0 ) FatalError( ERR_CANT_DO_IMPORT, "AR", "NO DLL NAME" );
        assert( exported_name_len != 0 );
        if( exported_name_len == 0 ) FatalError( ERR_CANT_DO_IMPORT, "AR", "NO EXPORTED NAME" );
        buffer = alloca( max( dll_name_len, exported_name_len ) + 64 );
        switch( file->import->processor ) {
        case WL_PROC_AXP:
            AddCoffSection( &c_file, ".text", 0xc, 3, IMAGE_SCN_ALIGN_16BYTES
                | IMAGE_SCN_LNK_COMDAT | IMAGE_SCN_CNT_CODE
                | IMAGE_SCN_MEM_READ | IMAGE_SCN_MEM_EXECUTE );
            type = 0x20;
            sec_num = 1;
            break;
        case WL_PROC_PPC:
            AddCoffSection( &c_file, ".text", 0x18, 1, IMAGE_SCN_ALIGN_4BYTES
                | IMAGE_SCN_LNK_COMDAT | IMAGE_SCN_CNT_CODE
                | IMAGE_SCN_MEM_READ | IMAGE_SCN_MEM_EXECUTE );
            AddCoffSymSec( &c_file, IMAGE_COMDAT_SELECT_NODUPLICATES );
            strcpy( buffer, ".." );
            strcpy( buffer + 2, exportedName );
            AddCoffSymbol( &c_file, buffer, 0x0, 1, 0x20,
                IMAGE_SYM_CLASS_EXTERNAL, 0 );
            AddCoffSection( &c_file, ".pdata", 0x14, 4, IMAGE_SCN_ALIGN_1BYTES
                | IMAGE_SCN_LNK_COMDAT | IMAGE_SCN_CNT_INITIALIZED_DATA
                | IMAGE_SCN_MEM_READ );
            AddCoffSymSec( &c_file, IMAGE_COMDAT_SELECT_ASSOCIATIVE );
            AddCoffSection( &c_file, ".reldata", 0x8, 2, IMAGE_SCN_ALIGN_8BYTES
                | IMAGE_SCN_LNK_COMDAT | IMAGE_SCN_CNT_INITIALIZED_DATA
                | IMAGE_SCN_MEM_READ |  IMAGE_SCN_MEM_WRITE );
            AddCoffSymSec( &c_file, IMAGE_COMDAT_SELECT_NODUPLICATES );
            sec_num = 3;
            type = IMAGE_SYM_TYPE_NULL;
            break;
        default:
            file->import->processor = WL_PROC_X86;
        case WL_PROC_X86:
            AddCoffSection( &c_file, ".text", 0x6, 1, IMAGE_SCN_ALIGN_2BYTES
                | IMAGE_SCN_LNK_COMDAT | IMAGE_SCN_CNT_CODE
                | IMAGE_SCN_MEM_READ | IMAGE_SCN_MEM_EXECUTE );
            type = 0x20;        // JBS 99/12/21 a wild guess
            sec_num = 1;        // JBS 99/12/21 also a wild guess
            break;
        }
        AddCoffSymSec( &c_file, IMAGE_COMDAT_SELECT_NODUPLICATES );
        AddCoffSymbol( &c_file, exportedName, 0x0, sec_num, type,
                IMAGE_SYM_CLASS_EXTERNAL, 0 );
        AddCoffSection( &c_file, ".idata$5", 0x4, 1, IMAGE_SCN_ALIGN_4BYTES
            | IMAGE_SCN_LNK_COMDAT | IMAGE_SCN_CNT_INITIALIZED_DATA
            | IMAGE_SCN_MEM_READ |  IMAGE_SCN_MEM_WRITE );
        AddCoffSymSec( &c_file, IMAGE_COMDAT_SELECT_NODUPLICATES );
        strcpy( buffer, "__imp_" );
        strcat( buffer, exportedName );
        AddCoffSymbol( &c_file, buffer, 0x0, c_file.header.num_sections,
            IMAGE_SYM_TYPE_NULL, IMAGE_SYM_CLASS_EXTERNAL, 0 );
        AddCoffSection( &c_file, ".idata$4", 0x4, 1, IMAGE_SCN_ALIGN_4BYTES
            | IMAGE_SCN_LNK_COMDAT | IMAGE_SCN_CNT_INITIALIZED_DATA
            | IMAGE_SCN_MEM_READ |  IMAGE_SCN_MEM_WRITE );
        AddCoffSymSec( &c_file, IMAGE_COMDAT_SELECT_ASSOCIATIVE );
        assert( sym_name_len != 0 );
        if( sym_name_len == 0 ) FatalError( ERR_CANT_DO_IMPORT, "AR", "NO SYMBOL NAME" );
        AddCoffSection( &c_file, ".idata$6", ( sym_name_len | 1 ) + 3, 0, IMAGE_SCN_ALIGN_2BYTES
            | IMAGE_SCN_LNK_COMDAT | IMAGE_SCN_CNT_INITIALIZED_DATA
            | IMAGE_SCN_MEM_READ |  IMAGE_SCN_MEM_WRITE );
        AddCoffSymSec( &c_file, IMAGE_COMDAT_SELECT_ASSOCIATIVE );
        if( file->import->processor == WL_PROC_PPC ) {
            AddCoffSymbol( &c_file, ".toc", 0x0, 0,
                IMAGE_SYM_TYPE_NULL, IMAGE_SYM_CLASS_EXTERNAL, 0 );
        }
        strcpy( buffer, "__IMPORT_DESCRIPTOR_" );
        strcat( buffer, dllName );
        AddCoffSymbol( &c_file, buffer, 0x0, 0,
            IMAGE_SYM_TYPE_NULL, IMAGE_SYM_CLASS_EXTERNAL, 0 );
        WriteCoffFileHeader( io, &c_file );
        WriteCoffSections( io, &c_file );
        switch( file->import->processor ) {
        case WL_PROC_AXP:
            LibWrite( io, CoffImportAxpText, 0x0c );
            WriteCoffReloc( io, 0x0, 5, IMAGE_REL_ALPHA_REFHI );
            WriteCoffReloc( io, 0x0, 2, IMAGE_REL_ALPHA_PAIR );
            WriteCoffReloc( io, 0x4, 5, IMAGE_REL_ALPHA_REFLO );
            type = IMAGE_REL_ALPHA_REFLONGNB;
            sym_idx = 0x8;
            break;
        case WL_PROC_PPC:
            LibWrite( io, CoffImportPpcText, 0x18 );
            WriteCoffReloc( io, 0x0, 0xa, IMAGE_REL_PPC_TOCREL14 | IMAGE_REL_PPC_TOCDEFN );
            LibWrite( io, CoffImportPpcPdata, 0x14 );
            WriteCoffReloc( io, 0x0, 2, IMAGE_REL_PPC_ADDR32 );
            WriteCoffReloc( io, 0x4, 2, IMAGE_REL_PPC_ADDR32 );
            WriteCoffReloc( io, 0x10, 2, IMAGE_REL_PPC_ADDR32 );
            WriteCoffReloc( io, 0x80410004, 2, IMAGE_REL_PPC_SECTION );
            memset( buffer, 0, 8 );
            LibWrite( io, buffer, 8 );
            WriteCoffReloc( io, 0x0, 2, IMAGE_REL_PPC_ADDR32 );
            WriteCoffReloc( io, 0x4, 0xF, IMAGE_REL_PPC_ADDR32 );
            type = IMAGE_REL_PPC_ADDR32NB;
            sym_idx = 0xd;
            break;
        default:
            file->import->processor = WL_PROC_X86;
        case WL_PROC_X86:
            LibWrite( io, CoffImportX86Text, 0x6 );
            WriteCoffReloc( io, 0x2, 5, IMAGE_REL_I386_DIR32 );
            type = IMAGE_REL_I386_DIR32NB;
            sym_idx = 0x8;
            break;
        }
        memset( buffer, 0, 4 );
        LibWrite( io, buffer, 4 );
        WriteCoffReloc( io, 0, sym_idx, type );
        LibWrite( io, buffer, 4 );
        WriteCoffReloc( io, 0, sym_idx, type );
        ordinal = file->import->ordinal;
        LibWrite( io, &ordinal, sizeof( ordinal ) );
        LibWrite( io, symName, sym_name_len + 1 );
        if( !( sym_name_len & 1 ) ) {
            LibWrite( io, "\0", 1 );
        }
    default:
        break;
    }


    WriteCoffSymbols( io, &c_file );
    WriteCoffStringTable( io, &c_file );
    FiniCoffLibFile( &c_file );
    //MemFree( buffer );
}