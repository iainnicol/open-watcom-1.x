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


#ifndef _ERRS_INCLUDED
#define _ERRS_INCLUDED

typedef enum vi_rc {
    GOT_RESPONSE = -100,
    ALIAS_NOT_FOUND,
    RANGE_REQUEST_CANCELLED,
    FGREP_FOUND_STRING,
    FILE_COMPLETE,
    NEW_FILE,
    NO_VALUE_ENTERED,
    GOT_A_SAVEBUF,
    MARK_REQUEST_CANCELLED,
    NO_SPLIT_CREATED_AT_END_LINE,
    COULD_NOT_MERGE_FCBS,
    NO_SPLIT_CREATED_AT_START_LINE,
    DO_NOT_CLEAR_MESSAGE_WINDOW,
    GOT_A_DIGIT,
    NO_NUMBER,
    END_OF_FILE,
    FILE_COMPLETE_ENTER,
    NOT_COMPILEABLE_TOKEN,
    MENU_COMMAND_NOT_HANDLED,

    ERR_NO_ERR = 0,
    ERR_NO_MEMORY,
    ERR_FILE_NOT_FOUND,
    ERR_READ,
    ERR_SWAP_FILE_OPEN,
    ERR_NO_SUCH_DRIVE,
    ERR_DIRECTORY_OP_FAILED,
    ERR_WIND_INVALID,
    ERR_WIND_NO_MORE_WINDOWS,
    ERR_WIND_NO_SUCH_LINE,
    ERR_NO_SUCH_LINE,
    ERR_NO_MORE_LINES,
    ERR_NO_SUCH_COLUMN,
    ERR_SWAP_FILE_READ,
    ERR_SWAP_FILE_WRITE,
    ERR_INVALID_COMMAND,
    ERR_REPEAT_STRING_TOO_LONG,
    ERR_ALREADY_IN_DOT_MODE,
    ERR_CANNOT_DELETE_CHAR,
    ERR_NO_MORE_UNDOS,
    ERR_FILE_EXISTS,
    ERR_FILE_OPEN,
    ERR_FILE_CLOSE,
    ERR_FILE_WRITE,
    ERR_NOT_THAT_MANY_WORDS,
    ERR_INVALID_LINE_RANGE,
    ERR_NO_FILE_SPECIFIED,
    ERR_INVALID_SET_COMMAND,
    ERR_INVALID_VALUE,
    ERR_CHAR_NOT_FOUND,
    ERR_FIND_END_OF_FILE,
    ERR_FIND_NOT_FOUND,
    ERR_NO_PREVIOUS_SEARCH_STRING,
    ERR_LINE_FULL,
    ERR_CANNOT_OPEN_LINENUM_WIND,
    ERR_INVALID_DELETE_CMD,
    ERR_INVALID_YANK_CMD,
    ERR_NO_CHAR_TO_REPLACE,
    ERR_NOTHING_TO_MATCH,
    ERR_MATCH_NOT_FOUND,
    ERR_FIND_TOP_OF_FILE,
    ERR_INVALID_SUBS_CMD,
    ERR_INVALID_MARK_RANGE,
    ERR_MARK_NOT_SET,
    ERR_MARK_NOW_INVALID,
    ERR_INVALID_KEY,
    ERR_INVALID_CHANGE_CMD,
    ERR_INVALID_SAVEBUF,
    ERR_EMPTY_SAVEBUF,
    ERR_WIND_NO_SUCH_COLUMN,
    ERR_RE_NULL_ARGUMENT,
    ERR_RE_TOO_MANY_ROUND_BRACKETS,
    ERR_RE_UNMATCHED_ROUND_BRACKETS,
    ERR_RE_MEMORY_CORRUPTION,
    ERR_RE_CORRUPTED_POINTER,
    ERR_RE_INTERNAL_FOULUP,
    ERR_RE_EMPTY_OPERAND,
    ERR_RE_NESTED_OPERAND,
    ERR_RE_INVALID_SB_RANGE,
    ERR_RE_UNMATCHED_SQUARE_BRACKET,
    ERR_RE_OPERAND_FOLLOWS_NOTHING,
    ERR_RE_TRAILING_SLASH,
    ERR_INVALID_FIND_CMD,
    ERR_FIND_PAST_TERM_LINE,
    ERR_SWAP_FILE_FULL,
    ERR_SRC_INVALID_ASSIGN,
    ERR_SRC_INVALID_IF,
    ERR_SRC_NO_ERROR_DATA,
    ERR_SRC_INVALID_GOTO,
    ERR_SRC_LABEL_NOT_FOUND,
    ERR_SCRIPT_ALREADY_RESIDENT,
    ERR_SRC_INVALID_LABEL,
    ERR_INVALID_ADDRESS,
    ERR_SRC_INVALID_OPEN,
    ERR_SRC_INVALID_READ,
    ERR_SRC_INVALID_WRITE,
    ERR_SRC_FILE_NOT_OPEN,
    ERR_SRC_INVALID_CLOSE,
    ERR_INPUT_KEYMAP_RUNNING,
    ERR_NO_EXTENDED_MEMORY,
    ERR_FILE_SEEK,
    ERR_RE_INVALID_CASETOGGLE,
    ERR_INVALID_DATA_FILE,
    ERR_NO_XMS_MEMORY,
    ERR_NO_WORD_TO_FIND,
    ERR_TAG_NOT_FOUND,
    ERR_READ_ONLY_FILE,
    ERR_INVALID_TAG_FOUND,
    ERR_NO_STRING,
    ERR_INVALID_CASE_CMD,
    ERR_INVALID_RANGE,
    ERR_INTERNAL_NULL_PTR,
    ERR_INVALID_SHIFT_CMD,
    ERR_SRC_INVALID_INPUT,
    ERR_INVALID_GLOBAL_CMD,
    ERR_NO_EMS_MEMORY,
    ERR_INVALID_UNDO,
    ERR_SRC_INVALID_EXPR,
    ERR_INVALID_MAP,
    ERR_TWO_MARKS_ON_LINE,
    ERR_READ_ONLY_FILE_MODIFIED,
    ERR_TTY_FILE,
    ERR_FILE_VIEW_ONLY,
    ERR_FILE_MODIFIED,
    ERR_NO_STACK,
    ERR_INVALID_ALIAS,
    ERR_TOO_MANY_MATCH_STRINGS,
    ERR_INVALID_MATCH,
    ERR_INVALID_SETCOLOR,
    ERR_INVALID_WINDOW_SETUP,
    ERR_NO_FILE_NAME,
    ERR_INVALID_ABBREV,
    ERR_NO_SUCH_ALIAS,
    ERR_NO_SUCH_ABBREV,
    ERR_INVALID_IN_EX_MODE,
    ERR_ONLY_VALID_IN_EX_MODE,
    ERR_SAVEBUF_TOO_BIG,
    ERR_INVALID_REDRAW,
    ERR_INVALID_HIDE_CMD,
    ERR_EXPECTING_COLON,
    ERR_INVALID_MENU,
    ERR_NO_SELECTION,
    ERR_OPEN_UNDO,
    ERR_NO_PREVIOUS_COMMAND,
    ERR_FILE_STACK_EMPTY,
    ERR_INVALID_FONT,
    ERR_INVALID_DDE,
    ERR_DDE_FAIL,
    ERR_SRC_INVALID_NEXTWORD,
    ERR_NO_REGION,
    ERR_INVALID_OP,
    ERR_CLIPBOARD,
    ERR_CLIPBOARD_EMPTY,
    ERR_NO_FILE,
    ERR_PROMPT_TOO_LONG,
    ERR_EXIT_ABORTED,
    ERR_INVALID_LOCATE,
    ERR_NO_MORE_REDOS,
    ERR_SAVE_CANCELED,
} vi_rc;

#endif
