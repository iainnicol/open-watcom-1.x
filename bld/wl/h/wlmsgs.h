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


#define MSG_LANG_SPACING        1000

#define    MSG_PRODUCT                            0 + MSG_BASE
#define    MSG_COPYRIGHT                          1 + MSG_BASE
#define    MSG_INTERNAL                           2 + MSG_BASE
#define    MSG_LOADING_OBJECT                     3 + MSG_BASE
#define    MSG_SEARCHING_LIBS                     4 + MSG_BASE
#define    MSG_CREATE_MAP                         5 + MSG_BASE
#define    MSG_CREATE_EXE                         6 + MSG_BASE
#define    MSG_USING_SPILL                        7 + MSG_BASE
#define    MSG_CANT_OPEN                          8 + MSG_BASE
#define    MSG_NO_DYN_MEM                         9 + MSG_BASE
#define    MSG_IO_PROBLEM                        10 + MSG_BASE
#define    MSG_OBJ_FILE_ATTR                     11 + MSG_BASE
#define    MSG_LIB_FILE_ATTR                     12 + MSG_BASE
#define    MSG_BREAK_HIT                         13 + MSG_BASE
#define    MSG_STACK_NOT_FOUND                   14 + MSG_BASE
#define    MSG_BAD_RELOC_TYPE                    15 + MSG_BASE
#define    MSG_BAD_ABS_FIXUP                     16 + MSG_BASE
#define    MSG_BAD_REL_FIXUP                     17 + MSG_BASE
#define    MSG_FIXUP_OFF_RANGE                   18 + MSG_BASE
#define    MSG_SEG_RELOC_OUT                     19 + MSG_BASE
#define    MSG_GROUP_TOO_BIG                     20 + MSG_BASE
#define    MSG_SEG_TOO_BIG                       21 + MSG_BASE
#define    MSG_CANT_HAVE_START                   22 + MSG_BASE
#define    MSG_NO_START_ADDR                     23 + MSG_BASE
#define    MSG_NO_OVERLAY_LOADER                 24 + MSG_BASE
#define    MSG_SHORT_VECT_RANGE                  25 + MSG_BASE
#define    MSG_RESERVED_SYM_DEFINED              26 + MSG_BASE
#define    MSG_MULT_DEF                          27 + MSG_BASE
#define    MSG_UNDEF_REF                         28 + MSG_BASE
#define    MSG_EARLY_EOF                         29 + MSG_BASE
#define    MSG_MULT_START_ADDRS                  30 + MSG_BASE
#define    MSG_SEG_IN_TWO_GROUPS                 31 + MSG_BASE
#define    MSG_REC_NOT_DONE                      32 + MSG_BASE
#define    MSG_DIRECTIVE_ERR                     33 + MSG_BASE
#define    MSG_NO_OFFSET_WITH_DLL                34 + MSG_BASE
#define    MSG_EXE_NAME                          35 + MSG_BASE
#define    MSG_CREATED_ON                        36 + MSG_BASE
#define    MSG_UNDEF_SYM                         37 + MSG_BASE
#define    MSG_DEBUG_AFTER_FILES                 38 + MSG_BASE
#define    MSG_ALIGN_TOO_SMALL                   39 + MSG_BASE
#define    MSG_IMPORT_ORD_INVALID                40 + MSG_BASE
#define    MSG_EXPORT_ORD_INVALID                41 + MSG_BASE
#define    MSG_TOO_MANY_IOPL_WORDS               42 + MSG_BASE
#define    MSG_DUP_EXP_ORDINAL                   43 + MSG_BASE
#define    MSG_EXP_SYM_NOT_FOUND                 44 + MSG_BASE
#define    MSG_SEG_FLAG_MULT_DEFD                45 + MSG_BASE
#define    MSG_SEG_NAME_NOT_FOUND                46 + MSG_BASE
#define    MSG_CLASS_NAME_NOT_FOUND              47 + MSG_BASE
#define    MSG_AUTO_SEG_MULT_DEFD                48 + MSG_BASE
#define    MSG_INV_STUB_FILE                     49 + MSG_BASE
#define    MSG_INV_OLD_DLL                       50 + MSG_BASE
#define    MSG_STUB_SAME_AS_LOAD                 51 + MSG_BASE
#define    MSG_REL_NOT_SAME_SEG                  52 + MSG_BASE
#define    MSG_DLL_IN_REL_RELOC                  53 + MSG_BASE
#define    MSG_CANT_USE_LOCALS                   54 + MSG_BASE
#define    MSG_FRAME_EQ_TARGET                   55 + MSG_BASE
#define    MSG_CANT_FIND_MEMBER                  56 + MSG_BASE
#define    MSG_MULTIPLE_MODES_FOUND              57 + MSG_BASE
#define    MSG_FORMAT_BAD_OPTION                 58 + MSG_BASE
#define    MSG_VALUE_TOO_LARGE                   59 + MSG_BASE
#define    MSG_VALUE_INCORRECT                   60 + MSG_BASE
#define    MSG_MULT_REALBREAKS                   61 + MSG_BASE
#define    MSG_DLL_WITH_386                      62 + MSG_BASE
#define    MSG_INVALID_FLAT_RELOC                63 + MSG_BASE
#define    MSG_CANT_COMBINE_32_AND_16            64 + MSG_BASE
#define    MSG_BREAKSYM_NOT_FOUND                65 + MSG_BASE
#define    MSG_BAD_IMP_REL_RELOC                 66 + MSG_BASE
#define    MSG_NOV_NO_CODE_DATA_RELOC            67 + MSG_BASE
#define    MSG_ABS_SEG_FIXUP_BAD                 68 + MSG_BASE
#define    MSG_CHECK_NOT_FOUND                   69 + MSG_BASE
#define    MSG_START_PROC_NOT_FOUND              70 + MSG_BASE
#define    MSG_EXIT_PROC_NOT_FOUND               71 + MSG_BASE
#define    MSG_NO_SECTION_IN_ROOT                72 + MSG_BASE
#define    MSG_BAD_NOV_FILE_TYPE                 73 + MSG_BASE
#define    MSG_CIRCULAR_ALIAS_FOUND              74 + MSG_BASE
#define    MSG_EXPECTING_END                     75 + MSG_BASE
#define    MSG_OPTION_MULTIPLY_DEFD              76 + MSG_BASE
#define    MSG_NOT_MULTIPLE_OF_8                 77 + MSG_BASE
#define    MSG_BOTH_RELOC_OPTIONS                78 + MSG_BASE
#define    MSG_TRANS_RELOCS_NEEDED               79 + MSG_BASE
#define    MSG_FOUND_XXBIT_OBJ                   80 + MSG_BASE
#define    MSG_TOO_MANY_SELECTORS                81 + MSG_BASE
#define    MSG_BAD_REC_TYPE                      82 + MSG_BASE
#define    MSG_FRAME_INVALID                     83 + MSG_BASE
#define    MSG_BAD_TARG_OFF                      84 + MSG_BASE
#define    MSG_PRESS_CTRL_Z                      85 + MSG_BASE
#define    MSG_INV_COM_START_ADDR                86 + MSG_BASE
#define    MSG_STACK_SEG_IGNORED                 87 + MSG_BASE
#define    MSG_NO_VIRT_MEM                       88 + MSG_BASE
#define    MSG_COM_TOO_LARGE                     89 + MSG_BASE
#define    MSG_MULT_DEF_BY                       90 + MSG_BASE
#define    MSG_OVL_GROUP_SPLIT                   91 + MSG_BASE
#define    MSG_NEWSEG_BEFORE_OBJ                 92 + MSG_BASE
#define    MSG_CANT_OPEN_NO_REASON               93 + MSG_BASE
#define    MSG_IO_PROBLEM_NO_REASON              94 + MSG_BASE
#define    MSG_DEBUG_TOO_LARGE                   95 + MSG_BASE
#define    MSG_INCOMPATIBLE_DBI_FOUND            96 + MSG_BASE
#define    MSG_TOO_MANY_LIB_MODS                 97 + MSG_BASE
#define    MSG_OFFSET_MUST_BE_ALIGNED            98 + MSG_BASE
#define    MSG_SYMBOL_NAME_TOO_LONG              99 + MSG_BASE
#define    MSG_MOD_TRACE                        100 + MSG_BASE
#define    MSG_INV_INC_FILE                     101 + MSG_BASE
#define    MSG_TRACE_OBJ_NOT_FOUND              102 + MSG_BASE
#define    MSG_TRACE_LIB_NOT_FOUND              103 + MSG_BASE
#define    MSG_MOD_IND_TRACE                    104 + MSG_BASE
#define    MSG_CANT_RESERVE_SPACE               105 + MSG_BASE
#define    MSG_TRADEMARK                        106 + MSG_BASE
#define    MSG_SYSTEM_UNDEFINED                 107 + MSG_BASE
#define    MSG_SYSTEM_ALREADY_DEFINED           108 + MSG_BASE
#define    MSG_QNX_BASE_LT_STACK                109 + MSG_BASE
#define    MSG_NO_MEMB_IN_LIBFILE               110 + MSG_BASE
#define    MSG_ERROR_IN_SYSTEM_BLOCK            111 + MSG_BASE
#define    MSG_NO_PREVIOUS_INPUT                112 + MSG_BASE
#define    MSG_NO_INPUT_LEFT                    113 + MSG_BASE
#define    MSG_ENV_NAME_INCORRECT               114 + MSG_BASE
#define    MSG_ENV_NOT_FOUND                    115 + MSG_BASE
#define    MSG_AREA_TOO_SMALL                   116 + MSG_BASE
#define    MSG_BAD_MOVABLE_SEG_NUM              117 + MSG_BASE
#define    MSG_HEAP_TOO_BIG                     118 + MSG_BASE
#define    MSG_BAD_WLIB_IMPORT                  119 + MSG_BASE
#define    MSG_APP_TOO_BIG_FOR_DOS              120 + MSG_BASE
#define    MSG_DUP_EXP_NAME                     121 + MSG_BASE
#define    MSG_NO_FILES_FOUND                   122 + MSG_BASE
#define    MSG_OVERLAYS_NOT_SUPPORTED           123 + MSG_BASE
#define    MSG_LAZY_EXTDEF_MISMATCH             124 + MSG_BASE
#define    MSG_MULTIPLE_ALIASES                 125 + MSG_BASE
#define    MSG_EXE_DATE_CHANGED                 126 + MSG_BASE
#define    MSG_CANT_EXPORT_ABSOLUTE             127 + MSG_BASE
#define    MSG_DIRECTIVE_ERR_BEGINNING          128 + MSG_BASE
#define    MSG_ADDR_INFO_TOO_LARGE              129 + MSG_BASE
#define    MSG_INV_SHARED_NLM_FILE              130 + MSG_BASE
#define    MSG_CANT_OPEN_SPILL                  131 + MSG_BASE
#define    MSG_BAD_CURLY_LIST                   132 + MSG_BASE
#define    MSG_NO_REALBREAK_WITH_16BIT          133 + MSG_BASE
#define    MSG_INV_MESSAGE_FILE                 134 + MSG_BASE
#define    MSG_INCORRECT_NUM_AREAS              135 + MSG_BASE
#define    MSG_RELOC_TO_RWDATA_SEG              136 + MSG_BASE
#define    MSG_TOO_MANY_ERRORS                  137 + MSG_BASE
#define    MSG_INV_FILENAME                     138 + MSG_BASE
#define    MSG_CANNOT_HAVE_16_AND_32            139 + MSG_BASE
#define    MSG_INVALID_MSG_NUM                  140 + MSG_BASE
#define    MSG_VF_TABLE_MISMATCH                141 + MSG_BASE
#define    MSG_DEB_NONE_NOT_NECESSARY           142 + MSG_BASE
#define    MSG_CANT_SORT_SYMBOLS                143 + MSG_BASE
#define    MSG_SYMBOL_DEAD                      144 + MSG_BASE
#define    MSG_VF_PURE_MISMATCH                 145 + MSG_BASE
#define    MSG_BAD_OBJECT                       146 + MSG_BASE
#define    MSG_AMBIG_FORMAT                     147 + MSG_BASE
#define    MSG_INVALID_TYPE_DESC                148 + MSG_BASE
#define    MSG_MULT_DBI_FORMATS                 149 + MSG_BASE
#define    MSG_MACHTYPE_DIFFERENT               150 + MSG_BASE
#define    MSG_NO_BIG_ENDIAN                    151 + MSG_BASE
#define    MSG_NO_DICT_FOUND                    152 + MSG_BASE
#define    MSG_ENTRY_PROC_NOT_FOUND             153 + MSG_BASE
#define    MSG_CANT_EXECUTE                     154 + MSG_BASE
#define    MSG_REL_NOT_ALIGNED                  155 + MSG_BASE
#define    MSG_INC_NEAR_START                   156 + MSG_BASE
#define    MSG_NO_CODE_OR_DATA                  157 + MSG_BASE
#define    MSG_PROBLEM_IN_RESOURCE              158 + MSG_BASE
#define    MSG_INC_ONLY_SUPPORTS_DWARF          159 + MSG_BASE
#define    MSG_INC_AND_DCE_NOT_ALLOWED          160 + MSG_BASE
#define    MSG_TOC_TOO_BIG                      161 + MSG_BASE
#define    MSG_REL_IN_LIDATA                    162 + MSG_BASE
#define    MSG_NOT_COMPILED_VF_ELIM             163 + MSG_BASE
#define    MSG_INC_AND_VFR_NOT_ALLOWED          164 + MSG_BASE
#define    MSG_RESOURCE_TOO_BIG                 165 + MSG_BASE
#define    MSG_MULT_START_ADDRS_BY              166 + MSG_BASE
#define    MSG_INTERNAL_MOD_NAME_DIFF_FROM_FILE 167 + MSG_BASE
#define    MSG_VXD_INCORRECT_EXPORT             168 + MSG_BASE
#define    MSG_MAX_ERR_MSG_NUM                  168 + MSG_BASE

#define    MSG_FILE_REC_NAME_0                  227 + MSG_BASE
#define    MSG_FILE_REC_NAME_1                  228 + MSG_BASE
#define    MSG_FILE_REC_NAME_2                  229 + MSG_BASE
#define    MSG_FILE_REC_NAME_3                  230 + MSG_BASE
#define    MSG_FILE_REC_NAME_4                  231 + MSG_BASE
#define    MSG_FILE_REC_NAME_5                  232 + MSG_BASE
#define    MSG_FILE_REC_NAME_6                  233 + MSG_BASE
#define    MSG_ERROR                            234 + MSG_BASE
#define    MSG_WARNING                          235 + MSG_BASE
#define    MSG_SYS_BLK                          236 + MSG_BASE
#define    MSG_ENVIRON                          237 + MSG_BASE
#define    MSG_LINE                             238 + MSG_BASE
/* fill in the gap here... */
#define    MSG_FORMAT_NOT_DECIDED               240 + MSG_BASE
#define    MSG_NO_LEADER_ON_PASS_2              241 + MSG_BASE
#define    MSG_IOERRLIST_0                      242 + MSG_BASE
#define    MSG_IOERRLIST_1                      243 + MSG_BASE
#define    MSG_IOERRLIST_2                      244 + MSG_BASE
#define    MSG_IOERRLIST_3                      245 + MSG_BASE
#define    MSG_IOERRLIST_4                      246 + MSG_BASE
#define    MSG_IOERRLIST_5                      247 + MSG_BASE
#define    MSG_IOERRLIST_6                      248 + MSG_BASE
#define    MSG_IOERRLIST_7                      249 + MSG_BASE
#define    MSG_PRESS_KEY                        250 + MSG_BASE
/* gap here.. */
#define    MSG_FILE_TYPES_0                     252 + MSG_BASE
#define    MSG_FILE_TYPES_1                     253 + MSG_BASE
#define    MSG_FILE_TYPES_2                     254 + MSG_BASE
#define    MSG_FILE_TYPES_3                     255 + MSG_BASE
#define    MSG_FILE_TYPES_4                     256 + MSG_BASE
#define    MSG_FILE_TYPES_5                     257 + MSG_BASE
#define    MSG_FILE_TYPES_6                     258 + MSG_BASE
#define    MSG_FILE_TYPES_7                     259 + MSG_BASE
#define    MSG_FILE_TYPES_8                     260 + MSG_BASE
#define    MSG_FILE_TYPES_9                     261 + MSG_BASE
#define    MSG_FILE_TYPES_10                    262 + MSG_BASE
#define    MSG_FILE_TYPES_11                    263 + MSG_BASE
#define    MSG_FILE_TYPES_12                    264 + MSG_BASE
#define    MSG_FILE_TYPES_13                    265 + MSG_BASE
#define    MSG_FILE_TYPES_14                    266 + MSG_BASE
#define    MSG_FILE_TYPES_15                    267 + MSG_BASE
#define    MSG_FILE_TYPES_16                    268 + MSG_BASE
#define    MSG_CREATE_TYPE_DLL                  269 + MSG_BASE
#define    MSG_CREATE_TYPE_EXE                  270 + MSG_BASE
#define    MSG_IS_A_EXE                         271 + MSG_BASE

#define    MSG_MAP_BOX_GROUP                    276 + MSG_BASE
#define    MSG_MAP_TITLE_GROUP_0                277 + MSG_BASE
#define    MSG_MAP_TITLE_GROUP_1                278 + MSG_BASE
#define    MSG_MAP_BOX_ABS_SEG                  279 + MSG_BASE
#define    MSG_MAP_TITLE_ABS_SEG_0              280 + MSG_BASE
#define    MSG_MAP_TITLE_ABS_SEG_1              281 + MSG_BASE
#define    MSG_MAP_BOX_SEGMENTS                 282 + MSG_BASE
#define    MSG_MAP_TITLE_SEGMENTS_0             283 + MSG_BASE
#define    MSG_MAP_TITLE_SEGMENTS_1             284 + MSG_BASE
#define    MSG_MAP_BOX_MEMORY_MAP               285 + MSG_BASE
#define    MSG_MAP_UNREF_SYM                    286 + MSG_BASE
#define    MSG_MAP_REF_LOCAL_SYM                287 + MSG_BASE
#define    MSG_MAP_TITLE_MEMORY_MAP_0           288 + MSG_BASE
#define    MSG_MAP_TITLE_MEMORY_MAP_1           289 + MSG_BASE
#define    MSG_MAP_BOX_OVERLAY_VECTOR           290 + MSG_BASE
#define    MSG_MAP_BOX_COMMUNAL                 291 + MSG_BASE
#define    MSG_MAP_TITLE_COMMUNAL_0             292 + MSG_BASE
#define    MSG_MAP_TITLE_COMMUNAL_1             293 + MSG_BASE
#define    MSG_MAP_BOX_MOD_SEG                  294 + MSG_BASE
#define    MSG_MAP_ABS_ADDR                     295 + MSG_BASE
#define    MSG_MAP_32BIT_SEG                    296 + MSG_BASE
#define    MSG_MAP_TITLE_MOD_SEG_0              297 + MSG_BASE
#define    MSG_MAP_TITLE_MOD_SEG_1              298 + MSG_BASE
#define    MSG_MAP_BOX_TRACE_SYM                299 + MSG_BASE
#define    MSG_MAP_BOX_IMP_SYM                  300 + MSG_BASE
#define    MSG_MAP_TITLE_IMP_SYM_0              301 + MSG_BASE
#define    MSG_MAP_TITLE_IMP_SYM_1              302 + MSG_BASE
#define    MSG_MAP_TITLE_IMP_SYM_2              303 + MSG_BASE
#define    MSG_MAP_TITLE_IMP_SYM_3              304 + MSG_BASE
#define    MSG_MAP_BOX_UNRES_REF                305 + MSG_BASE
#define    MSG_MAP_TITLE_UNRES_REF_0            306 + MSG_BASE
#define    MSG_MAP_TITLE_UNRES_REF_1            307 + MSG_BASE
#define    MSG_MAP_BOX_LIB_USED                 308 + MSG_BASE
#define    MSG_MAP_BOX_LINKER_STAT              309 + MSG_BASE
#define    MSG_MAP_STACK_SIZE                   310 + MSG_BASE
#define    MSG_MAP_MEM_SIZE                     311 + MSG_BASE
#define    MSG_MAP_OVL_SIZE                     312 + MSG_BASE
#define    MSG_MAP_ENTRY_PT_ADDR                313 + MSG_BASE
#define    MSG_MAP_LINK_TIME                    314 + MSG_BASE
#define    MSG_MAP_COMDAT                       315 + MSG_BASE
#define    MSG_MAP_SYM_STATIC                   316 + MSG_BASE
#define    MSG_MAP_DEFINING_MODULE              317 + MSG_BASE

#define    MSG_GENERAL_HELP_0                   340 + MSG_BASE
#define    MSG_GENERAL_HELP_1                   341 + MSG_BASE
#define    MSG_GENERAL_HELP_2                   342 + MSG_BASE
#define    MSG_GENERAL_HELP_3                   343 + MSG_BASE
#define    MSG_GENERAL_HELP_4                   344 + MSG_BASE
#define    MSG_GENERAL_HELP_5                   345 + MSG_BASE
#define    MSG_GENERAL_HELP_6                   346 + MSG_BASE
#define    MSG_GENERAL_HELP_7                   347 + MSG_BASE
#define    MSG_GENERAL_HELP_8                   348 + MSG_BASE
#define    MSG_GENERAL_HELP_9                   349 + MSG_BASE
#define    MSG_GENERAL_HELP_10                  350 + MSG_BASE
#define    MSG_GENERAL_HELP_11                  351 + MSG_BASE
#define    MSG_GENERAL_HELP_12                  352 + MSG_BASE
#define    MSG_GENERAL_HELP_13                  353 + MSG_BASE
#define    MSG_GENERAL_HELP_14                  354 + MSG_BASE
#define    MSG_GENERAL_HELP_15                  355 + MSG_BASE
#define    MSG_GENERAL_HELP_16                  356 + MSG_BASE
#define    MSG_GENERAL_HELP_17                  357 + MSG_BASE
#define    MSG_GENERAL_HELP_18                  358 + MSG_BASE
#define    MSG_GENERAL_HELP_19                  359 + MSG_BASE
#define    MSG_GENERAL_HELP_20                  360 + MSG_BASE
#define    MSG_GENERAL_HELP_21                  361 + MSG_BASE
#define    MSG_GENERAL_HELP_22                  362 + MSG_BASE
#define    MSG_GENERAL_HELP_23                  363 + MSG_BASE
#define    MSG_GENERAL_HELP_24                  364 + MSG_BASE
#define    MSG_GENERAL_HELP_25                  365 + MSG_BASE
#define    MSG_GENERAL_HELP_26                  366 + MSG_BASE
#define    MSG_GENERAL_HELP_27                  367 + MSG_BASE
#define    MSG_GENERAL_HELP_28                  368 + MSG_BASE
#define    MSG_GENERAL_HELP_29                  369 + MSG_BASE
#define    MSG_GENERAL_HELP_30                  370 + MSG_BASE
#define    MSG_GENERAL_HELP_31                  371 + MSG_BASE
#define    MSG_GENERAL_HELP_32                  372 + MSG_BASE
#define    MSG_GENERAL_HELP_33                  373 + MSG_BASE
#define    MSG_GENERAL_HELP_34                  374 + MSG_BASE
#define    MSG_GENERAL_HELP_35                  375 + MSG_BASE
#define    MSG_GENERAL_HELP_36                  376 + MSG_BASE
#define    MSG_GENERAL_HELP_37                  377 + MSG_BASE
#define    MSG_GENERAL_HELP_38                  378 + MSG_BASE
#define    MSG_GENERAL_HELP_39                  379 + MSG_BASE
#define    MSG_GENERAL_HELP_40                  380 + MSG_BASE
#define    MSG_GENERAL_HELP_41                  381 + MSG_BASE
#define    MSG_GENERAL_HELP_40                  380 + MSG_BASE
#define    MSG_GENERAL_HELP_41                  381 + MSG_BASE
#define    MSG_GENERAL_HELP_42                  382 + MSG_BASE
#define    MSG_GENERAL_HELP_43                  383 + MSG_BASE
#define    MSG_GENERAL_HELP_44                  384 + MSG_BASE
#define    MSG_GENERAL_HELP_45                  385 + MSG_BASE
#define    MSG_GENERAL_HELP_46                  386 + MSG_BASE
#define    MSG_GENERAL_HELP_47                  387 + MSG_BASE
#define    MSG_GENERAL_HELP_48                  388 + MSG_BASE
#define    MSG_GENERAL_HELP_49                  389 + MSG_BASE
#define    MSG_GENERAL_HELP_50                  390 + MSG_BASE
#define    MSG_GENERAL_HELP_51                  391 + MSG_BASE

#define    MSG_DOS_HELP_0                       392 + MSG_BASE
#define    MSG_DOS_HELP_1                       393 + MSG_BASE
#define    MSG_DOS_HELP_2                       394 + MSG_BASE
#define    MSG_DOS_HELP_3                       395 + MSG_BASE
#define    MSG_DOS_HELP_4                       396 + MSG_BASE
#define    MSG_DOS_HELP_5                       397 + MSG_BASE
#define    MSG_DOS_HELP_6                       398 + MSG_BASE
#define    MSG_DOS_HELP_7                       399 + MSG_BASE
#define    MSG_DOS_HELP_8                       400 + MSG_BASE
#define    MSG_DOS_HELP_9                       401 + MSG_BASE
#define    MSG_DOS_HELP_10                      402 + MSG_BASE
#define    MSG_DOS_HELP_11                      403 + MSG_BASE
#define    MSG_DOS_HELP_12                      404 + MSG_BASE
#define    MSG_DOS_HELP_13                      405 + MSG_BASE
#define    MSG_DOS_HELP_14                      406 + MSG_BASE
#define    MSG_DOS_HELP_15                      407 + MSG_BASE

#define    MSG_OS2_HELP_0                       408 + MSG_BASE
#define    MSG_OS2_HELP_1                       409 + MSG_BASE
#define    MSG_OS2_HELP_2                       410 + MSG_BASE
#define    MSG_OS2_HELP_3                       411 + MSG_BASE
#define    MSG_OS2_HELP_4                       412 + MSG_BASE
#define    MSG_OS2_HELP_5                       413 + MSG_BASE
#define    MSG_OS2_HELP_6                       414 + MSG_BASE
#define    MSG_OS2_HELP_7                       415 + MSG_BASE
#define    MSG_OS2_HELP_8                       416 + MSG_BASE
#define    MSG_OS2_HELP_9                       417 + MSG_BASE
#define    MSG_OS2_HELP_10                      418 + MSG_BASE
#define    MSG_OS2_HELP_11                      419 + MSG_BASE
#define    MSG_OS2_HELP_12                      420 + MSG_BASE
#define    MSG_OS2_HELP_13                      421 + MSG_BASE
#define    MSG_OS2_HELP_14                      422 + MSG_BASE
#define    MSG_OS2_HELP_15                      423 + MSG_BASE
#define    MSG_OS2_HELP_16                      424 + MSG_BASE
#define    MSG_OS2_HELP_17                      425 + MSG_BASE
#define    MSG_OS2_HELP_18                      426 + MSG_BASE
#define    MSG_OS2_HELP_19                      427 + MSG_BASE
#define    MSG_OS2_HELP_20                      428 + MSG_BASE
#define    MSG_OS2_HELP_21                      429 + MSG_BASE
#define    MSG_OS2_HELP_22                      430 + MSG_BASE
#define    MSG_OS2_HELP_23                      431 + MSG_BASE
#define    MSG_OS2_HELP_24                      432 + MSG_BASE
#define    MSG_OS2_HELP_25                      433 + MSG_BASE
#define    MSG_OS2_HELP_26                      434 + MSG_BASE
#define    MSG_OS2_HELP_27                      435 + MSG_BASE
#define    MSG_OS2_HELP_28                      436 + MSG_BASE
#define    MSG_OS2_HELP_29                      437 + MSG_BASE
#define    MSG_OS2_HELP_30                      438 + MSG_BASE
#define    MSG_OS2_HELP_31                      439 + MSG_BASE

#define    MSG_WINDOWS_HELP_0                   440 + MSG_BASE
#define    MSG_WINDOWS_HELP_1                   441 + MSG_BASE
#define    MSG_WINDOWS_HELP_2                   442 + MSG_BASE
#define    MSG_WINDOWS_HELP_3                   443 + MSG_BASE
#define    MSG_WINDOWS_HELP_4                   444 + MSG_BASE
#define    MSG_WINDOWS_HELP_5                   445 + MSG_BASE
#define    MSG_WINDOWS_HELP_6                   446 + MSG_BASE
#define    MSG_WINDOWS_HELP_7                   447 + MSG_BASE
#define    MSG_WINDOWS_HELP_8                   448 + MSG_BASE
#define    MSG_WINDOWS_HELP_9                   449 + MSG_BASE
#define    MSG_WINDOWS_HELP_10                  450 + MSG_BASE
#define    MSG_WINDOWS_HELP_11                  451 + MSG_BASE
#define    MSG_WINDOWS_HELP_12                  452 + MSG_BASE
#define    MSG_WINDOWS_HELP_13                  453 + MSG_BASE
#define    MSG_WINDOWS_HELP_14                  454 + MSG_BASE
#define    MSG_WINDOWS_HELP_15                  455 + MSG_BASE
#define    MSG_WINDOWS_HELP_16                  456 + MSG_BASE
#define    MSG_WINDOWS_HELP_17                  457 + MSG_BASE
#define    MSG_WINDOWS_HELP_18                  458 + MSG_BASE
#define    MSG_WINDOWS_HELP_19                  459 + MSG_BASE
#define    MSG_WINDOWS_HELP_20                  460 + MSG_BASE
#define    MSG_WINDOWS_HELP_21                  461 + MSG_BASE
#define    MSG_WINDOWS_HELP_22                  462 + MSG_BASE
#define    MSG_WINDOWS_HELP_23                  463 + MSG_BASE
#define    MSG_WINDOWS_HELP_24                  464 + MSG_BASE
#define    MSG_WINDOWS_HELP_25                  465 + MSG_BASE
#define    MSG_WINDOWS_HELP_26                  466 + MSG_BASE
#define    MSG_WINDOWS_HELP_27                  467 + MSG_BASE
#define    MSG_WINDOWS_HELP_28                  468 + MSG_BASE
#define    MSG_WINDOWS_HELP_29                  469 + MSG_BASE
#define    MSG_WINDOWS_HELP_30                  470 + MSG_BASE
#define    MSG_WINDOWS_HELP_31                  471 + MSG_BASE

#define    MSG_NT_HELP_0                        472 + MSG_BASE
#define    MSG_NT_HELP_1                        473 + MSG_BASE
#define    MSG_NT_HELP_2                        474 + MSG_BASE
#define    MSG_NT_HELP_3                        475 + MSG_BASE
#define    MSG_NT_HELP_4                        476 + MSG_BASE
#define    MSG_NT_HELP_5                        477 + MSG_BASE
#define    MSG_NT_HELP_6                        478 + MSG_BASE
#define    MSG_NT_HELP_7                        479 + MSG_BASE
#define    MSG_NT_HELP_8                        480 + MSG_BASE
#define    MSG_NT_HELP_9                        481 + MSG_BASE
#define    MSG_NT_HELP_10                       482 + MSG_BASE
#define    MSG_NT_HELP_11                       483 + MSG_BASE
#define    MSG_NT_HELP_12                       484 + MSG_BASE
#define    MSG_NT_HELP_13                       485 + MSG_BASE
#define    MSG_NT_HELP_14                       486 + MSG_BASE
#define    MSG_NT_HELP_15                       487 + MSG_BASE
#define    MSG_NT_HELP_16                       488 + MSG_BASE
#define    MSG_NT_HELP_17                       489 + MSG_BASE
#define    MSG_NT_HELP_18                       490 + MSG_BASE
#define    MSG_NT_HELP_19                       491 + MSG_BASE
#define    MSG_NT_HELP_20                       492 + MSG_BASE
#define    MSG_NT_HELP_21                       493 + MSG_BASE
#define    MSG_NT_HELP_22                       494 + MSG_BASE
#define    MSG_NT_HELP_23                       495 + MSG_BASE
#define    MSG_NT_HELP_24                       496 + MSG_BASE
#define    MSG_NT_HELP_25                       497 + MSG_BASE
#define    MSG_NT_HELP_26                       498 + MSG_BASE
#define    MSG_NT_HELP_27                       499 + MSG_BASE
#define    MSG_NT_HELP_28                       500 + MSG_BASE
#define    MSG_NT_HELP_29                       501 + MSG_BASE
#define    MSG_NT_HELP_30                       502 + MSG_BASE
#define    MSG_NT_HELP_31                       503 + MSG_BASE

#define    MSG_PHAR_HELP_0                      504 + MSG_BASE
#define    MSG_PHAR_HELP_1                      505 + MSG_BASE
#define    MSG_PHAR_HELP_2                      506 + MSG_BASE
#define    MSG_PHAR_HELP_3                      507 + MSG_BASE
#define    MSG_PHAR_HELP_4                      508 + MSG_BASE
#define    MSG_PHAR_HELP_5                      509 + MSG_BASE
#define    MSG_PHAR_HELP_6                      510 + MSG_BASE
#define    MSG_PHAR_HELP_7                      511 + MSG_BASE
#define    MSG_PHAR_HELP_8                      512 + MSG_BASE
#define    MSG_PHAR_HELP_9                      513 + MSG_BASE
#define    MSG_PHAR_HELP_10                     514 + MSG_BASE
#define    MSG_PHAR_HELP_11                     515 + MSG_BASE
#define    MSG_PHAR_HELP_12                     516 + MSG_BASE
#define    MSG_PHAR_HELP_13                     517 + MSG_BASE
#define    MSG_PHAR_HELP_14                     518 + MSG_BASE
#define    MSG_PHAR_HELP_15                     519 + MSG_BASE

#define    MSG_NOVELL_HELP_0                    520 + MSG_BASE
#define    MSG_NOVELL_HELP_1                    521 + MSG_BASE
#define    MSG_NOVELL_HELP_2                    522 + MSG_BASE
#define    MSG_NOVELL_HELP_3                    523 + MSG_BASE
#define    MSG_NOVELL_HELP_4                    524 + MSG_BASE
#define    MSG_NOVELL_HELP_5                    525 + MSG_BASE
#define    MSG_NOVELL_HELP_6                    526 + MSG_BASE
#define    MSG_NOVELL_HELP_7                    527 + MSG_BASE
#define    MSG_NOVELL_HELP_8                    528 + MSG_BASE
#define    MSG_NOVELL_HELP_9                    529 + MSG_BASE
#define    MSG_NOVELL_HELP_10                   530 + MSG_BASE
#define    MSG_NOVELL_HELP_11                   531 + MSG_BASE
#define    MSG_NOVELL_HELP_12                   532 + MSG_BASE
#define    MSG_NOVELL_HELP_13                   533 + MSG_BASE
#define    MSG_NOVELL_HELP_14                   534 + MSG_BASE
#define    MSG_NOVELL_HELP_15                   535 + MSG_BASE
#define    MSG_NOVELL_HELP_16                   536 + MSG_BASE
#define    MSG_NOVELL_HELP_17                   537 + MSG_BASE
#define    MSG_NOVELL_HELP_18                   538 + MSG_BASE
#define    MSG_NOVELL_HELP_19                   539 + MSG_BASE
#define    MSG_NOVELL_HELP_20                   540 + MSG_BASE
#define    MSG_NOVELL_HELP_21                   541 + MSG_BASE
#define    MSG_NOVELL_HELP_22                   542 + MSG_BASE
#define    MSG_NOVELL_HELP_23                   543 + MSG_BASE
#define    MSG_NOVELL_HELP_24                   544 + MSG_BASE
#define    MSG_NOVELL_HELP_25                   545 + MSG_BASE
#define    MSG_NOVELL_HELP_26                   546 + MSG_BASE
#define    MSG_NOVELL_HELP_27                   547 + MSG_BASE
#define    MSG_NOVELL_HELP_28                   548 + MSG_BASE
#define    MSG_NOVELL_HELP_29                   549 + MSG_BASE
#define    MSG_NOVELL_HELP_30                   550 + MSG_BASE
#define    MSG_NOVELL_HELP_31                   551 + MSG_BASE

#define    MSG_DOS16_HELP_0                     552 + MSG_BASE
#define    MSG_DOS16_HELP_1                     553 + MSG_BASE
#define    MSG_DOS16_HELP_2                     554 + MSG_BASE
#define    MSG_DOS16_HELP_3                     555 + MSG_BASE
#define    MSG_DOS16_HELP_4                     556 + MSG_BASE
#define    MSG_DOS16_HELP_5                     557 + MSG_BASE
#define    MSG_DOS16_HELP_6                     558 + MSG_BASE
#define    MSG_DOS16_HELP_7                     559 + MSG_BASE
#define    MSG_DOS16_HELP_8                     560 + MSG_BASE
#define    MSG_DOS16_HELP_9                     561 + MSG_BASE
#define    MSG_DOS16_HELP_10                    562 + MSG_BASE
#define    MSG_DOS16_HELP_11                    563 + MSG_BASE
#define    MSG_DOS16_HELP_12                    564 + MSG_BASE
#define    MSG_DOS16_HELP_13                    565 + MSG_BASE
#define    MSG_DOS16_HELP_14                    566 + MSG_BASE
#define    MSG_DOS16_HELP_15                    567 + MSG_BASE

#define    MSG_QNX_HELP_0                       568 + MSG_BASE
#define    MSG_QNX_HELP_1                       569 + MSG_BASE
#define    MSG_QNX_HELP_2                       570 + MSG_BASE
#define    MSG_QNX_HELP_3                       571 + MSG_BASE
#define    MSG_QNX_HELP_4                       572 + MSG_BASE
#define    MSG_QNX_HELP_5                       573 + MSG_BASE
#define    MSG_QNX_HELP_6                       574 + MSG_BASE
#define    MSG_QNX_HELP_7                       575 + MSG_BASE
#define    MSG_QNX_HELP_8                       576 + MSG_BASE
#define    MSG_QNX_HELP_9                       577 + MSG_BASE
#define    MSG_QNX_HELP_10                      578 + MSG_BASE
#define    MSG_QNX_HELP_11                      579 + MSG_BASE
#define    MSG_QNX_HELP_12                      580 + MSG_BASE
#define    MSG_QNX_HELP_13                      581 + MSG_BASE
#define    MSG_QNX_HELP_14                      582 + MSG_BASE
#define    MSG_QNX_HELP_15                      583 + MSG_BASE

#define    MSG_ELF_HELP_0                       584 + MSG_BASE
#define    MSG_ELF_HELP_1                       585 + MSG_BASE
#define    MSG_ELF_HELP_2                       586 + MSG_BASE
#define    MSG_ELF_HELP_3                       587 + MSG_BASE
#define    MSG_ELF_HELP_4                       588 + MSG_BASE
#define    MSG_ELF_HELP_5                       589 + MSG_BASE
#define    MSG_ELF_HELP_6                       590 + MSG_BASE
#define    MSG_ELF_HELP_7                       591 + MSG_BASE
#define    MSG_ELF_HELP_8                       592 + MSG_BASE
#define    MSG_ELF_HELP_9                       593 + MSG_BASE
#define    MSG_ELF_HELP_10                      594 + MSG_BASE
#define    MSG_ELF_HELP_11                      595 + MSG_BASE
#define    MSG_ELF_HELP_12                      596 + MSG_BASE
#define    MSG_ELF_HELP_13                      597 + MSG_BASE
#define    MSG_ELF_HELP_14                      598 + MSG_BASE
#define    MSG_ELF_HELP_15                      599 + MSG_BASE

#define    MSG_WIN_VXD_HELP_0                   600 + MSG_BASE
#define    MSG_WIN_VXD_HELP_1                   601 + MSG_BASE
#define    MSG_WIN_VXD_HELP_2                   602 + MSG_BASE
#define    MSG_WIN_VXD_HELP_3                   603 + MSG_BASE
#define    MSG_WIN_VXD_HELP_4                   604 + MSG_BASE
#define    MSG_WIN_VXD_HELP_5                   605 + MSG_BASE
#define    MSG_WIN_VXD_HELP_6                   606 + MSG_BASE
#define    MSG_WIN_VXD_HELP_7                   607 + MSG_BASE
#define    MSG_WIN_VXD_HELP_8                   608 + MSG_BASE
#define    MSG_WIN_VXD_HELP_9                   609 + MSG_BASE
#define    MSG_WIN_VXD_HELP_10                  610 + MSG_BASE
#define    MSG_WIN_VXD_HELP_11                  611 + MSG_BASE
#define    MSG_WIN_VXD_HELP_12                  612 + MSG_BASE
#define    MSG_WIN_VXD_HELP_13                  613 + MSG_BASE
#define    MSG_WIN_VXD_HELP_14                  614 + MSG_BASE
#define    MSG_WIN_VXD_HELP_15                  615 + MSG_BASE
#define    MSG_WIN_VXD_HELP_16                  616 + MSG_BASE
#define    MSG_WIN_VXD_HELP_17                  617 + MSG_BASE
#define    MSG_WIN_VXD_HELP_18                  618 + MSG_BASE
#define    MSG_WIN_VXD_HELP_19                  619 + MSG_BASE
#define    MSG_WIN_VXD_HELP_20                  620 + MSG_BASE
#define    MSG_WIN_VXD_HELP_21                  621 + MSG_BASE
#define    MSG_WIN_VXD_HELP_22                  622 + MSG_BASE
#define    MSG_WIN_VXD_HELP_23                  623 + MSG_BASE
#define    MSG_WIN_VXD_HELP_24                  624 + MSG_BASE
#define    MSG_WIN_VXD_HELP_25                  625 + MSG_BASE
#define    MSG_WIN_VXD_HELP_26                  626 + MSG_BASE
#define    MSG_WIN_VXD_HELP_27                  627 + MSG_BASE
#define    MSG_WIN_VXD_HELP_28                  628 + MSG_BASE
#define    MSG_WIN_VXD_HELP_29                  629 + MSG_BASE
#define    MSG_WIN_VXD_HELP_30                  630 + MSG_BASE
#define    MSG_WIN_VXD_HELP_31                  631 + MSG_BASE
