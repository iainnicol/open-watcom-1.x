/***************************************************************************
 * As of Nov 25/94 this file contains 13 shift/reduce conflicts
 *      -3 involving Y_MINUS
 *      -5 involving Y_LANGUAGE
 *      -5 involving Y_CHARACTERISTICS
 ***************************************************************************/

/*** error tokens ***/
%token Y_SCAN_ERROR
/*** non-keyword tokens ***/
%token <string>     Y_NAME
%token <intinfo>    Y_INTEGER
%token <string>     Y_STRING
%token <string>     Y_DOS_FILENAME
/*** operator tokens ***/
%token Y_POUND_SIGN                 /* this token is intercepted by yylex */
%token Y_LPAREN
%token Y_RPAREN
%token Y_LBRACE
%token Y_RBRACE
%token Y_LSQ_BRACKET
%token Y_RSQ_BRACKET
%token Y_PLUS
%token Y_MINUS
%token Y_BITNOT
%token Y_NOT
%token Y_TIMES
%token Y_DIVIDE
%token Y_MOD
%token Y_SHIFTL
%token Y_SHIFTR
%token Y_GT
%token Y_LT
%token Y_GE
%token Y_LE
%token Y_EQ
%token Y_SINGLE_EQ
%token Y_NE
%token Y_BITAND
%token Y_BITXOR
%token Y_BITOR
%token Y_AND
%token Y_OR
%token Y_QUESTION
%token Y_COLON
%token Y_COMMA
/*** keywords tokens ***/
%token Y_ACCELTABLE
%token Y_ALT
%token Y_ASSOCTABLE
%token Y_AUTOCHECKBOX
%token Y_AUTORADIOBUTTON
%token Y_BEGIN
%token Y_BITMAP
%token Y_CHAR
%token Y_CHARTABLE
%token Y_CHECKBOX
%token Y_CODEPAGE
%token Y_COMBOBOX
%token Y_CONTAINER
%token Y_CONTROL
%token Y_CTEXT
%token Y_CURSOR
%token Y_DEFAULTICON
%token Y_DEFPUSHBUTTON
%token Y_DIALOG
%token Y_DISCARDABLE
%token Y_DLGINCLUDE
%token Y_DLGTEMPLATE
%token Y_EDITTEXT
%token Y_END
%token Y_ENTRYFIELD
%token Y_FIXED
%token Y_FKAITEM
%token Y_FKALONG
%token Y_FKAROW
%token Y_FKASHORT
%token Y_FONT
%token Y_FONTDIR
%token Y_FRAME
%token Y_GROUPBOX
%token Y_HELP
%token Y_HELPITEM
%token Y_HELPSUBITEM
%token Y_HELPSUBTABLE
%token Y_HELPTABLE
%token Y_ICON
%token Y_IMPURE
%token Y_KEYTABLE
%token Y_LISTBOX
%token Y_LOADONCALL
%token Y_LONEKEY
%token Y_LTEXT
%token Y_MENU
%token Y_MENUITEM
%token Y_MESSAGETABLE
%token Y_MLE
%token Y_MOVEABLE
%token Y_NONSHARED
%token Y_NOT_KEYWORD
%token Y_NOTEBOOK
%token Y_POINTER
%token Y_POUND_PRAGMA
%token Y_PRELOAD
%token Y_PRESPARAMS
%token Y_PURE
%token Y_PUSHBUTTON
%token Y_RADIOBUTTON
%token Y_RCDATA
%token Y_RCINCLUDE          /* This is an old keyword that should no */
                            /* longer be used, but is used in the sample files*/
                            /* so may be used in some old .RC files. */
                            /* It is intercepted by the scanner */
%token Y_RESOURCE
%token Y_RTEXT
%token Y_SCANCODE
%token Y_SEGALIGN
%token Y_SEPARATOR
%token Y_SHARED
%token Y_SHIFT
%token Y_SLIDER
%token Y_SPINBUTTON
%token Y_STRINGTABLE
%token Y_SUBITEMSIZE
%token Y_SUBMENU
%token Y_SYSCOMMAND
%token Y_VALUESET
%token Y_VIRTUALKEY
%token Y_VKEYTABLE
%token Y_WINDOW
%token Y_WINDOWTEMPLATE

%type <maskint>         constant-expression
%type <maskint>         conditional-exp
%type <maskint>         log-or-exp
%type <maskint>         log-and-exp
%type <maskint>         bit-or-exp
%type <maskint>         bit-xor-exp
%type <maskint>         bit-and-exp
%type <maskint>         equality-exp
%type <maskint>         relational-exp
%type <maskint>         shift-exp
%type <maskint>         additive-exp
%type <maskint>         multiplicative-exp
%type <maskint>         unary-exp
%type <maskint>         primary-exp
%type <token>           keyword-name
%type <resid>           name-id
%type <resid>           type-id
%type <integral>        id-value
%type <fullmemflags>    resource-options
%type <token>           resource-option
%type <string>          file-name
%type <integral>        fontitalic
%type <integral>        fontweight
%type <integral>        fontextra
%type <menuflags>       menu-item-options
%type <token>           menu-item-option
%type <menuptr>         menu-section
%type <menuptr>         menu-items
%type <menuitem>        menu-item
%type <normalmenuitem>  menu-entry-stmt
%type <normalmenuitem>  menu-entry-defn
%type <string>          menu-text
%type <integral>        menu-result
%type <integral>        size-x
%type <integral>        size-y
%type <integral>        size-w
%type <integral>        size-h
%type <sizeinfo>        size-info
%type <string>          string-constant
%type <string>          string-group
%type <diagopts>        menu-stmt
%type <diagopts>        font-stmt
%type <diagopts>        diag-options-stmt
%type <token>           dialog
%type <dataelem>        diag-data-elements
%type <nameorord>       ctl-class-name
%type <integral>        point-size
%type <string>          typeface
%type <diaghead>        diag-options-section
%type <diagctrllist>    diag-control-section
%type <diagctrllist>    diag-control-stmts
%type <diagctrl>        diag-control-stmt
%type <diagctrlopts>    cntl-text-options
%type <diagctrlopts>    cntl-options
%type <diagctrl>        ltext-stmt
%type <diagctrl>        rtext-stmt
%type <diagctrl>        ctext-stmt
%type <diagctrl>        autocheckbox-stmt
%type <diagctrl>        autoradiobutton-stmt
%type <diagctrl>        checkbox-stmt
%type <diagctrl>        pushbutton-stmt
%type <diagctrl>        listbox-stmt
%type <diagctrl>        groupbox-stmt
%type <diagctrl>        defpushbutton-stmt
%type <diagctrl>        radiobutton-stmt
%type <diagctrl>        edittext-stmt
%type <diagctrl>        combobox-stmt
%type <diagctrl>        icon-stmt
%type <diagctrl>        control-stmt
%type <nameorord>       icon-name
%type <diagctrlopts>    icon-parms
%type <integral>        cntl-id
%type <resid>           cntl-text
%type <integral>        string-id
%type <stritem>         string-item
%type <strtable>        string-items
%type <strtable>        string-section
%type <rawitem>         raw-data-item
%type <resloc>          user-defined-data
%type <token>           resource-type
%type <dataelem>        raw-data-section
%type <dataelem>        raw-data-items
%type <dlghelpid>       helpId-opt
%type <integral>        menuId
%type <integral>        menuType
%type <integral>        menuState
%type <integral>        helpId

%start goal-symbol

%%

goal-symbol
    : resources
    | /* nothing */
    ;

resources
    : resource
    | resources resource
    ;

resource
    : normal-resource
    | string-table-resource
    | pragma-statment
    ;

normal-resource
    : single-line-resource
    | rcdata-resource
    | user-defined-resource
    | menu-resource
    | dlg-resource
    | message-table-resource
    ;

name-id
    : Y_NAME
        { $$ = WResIDFromStr( $1.string ); RcMemFree( $1.string ); }
    | string-constant
        { $$ = WResIDFromStr( $1.string ); RcMemFree( $1.string ); }
    | constant-expression
        {
            $$ = WResIDFromNum( $1.Value );
            if( $$ == NULL ) {
                $$ = WResIDFromNum( 0 );
                RcError( ERR_BAD_RES_ID, $1.Value );
                ErrorHasOccured = TRUE;
            }
        }
    | keyword-name
        { $$ = WResIDFromStr( SemTokenToString( $1 ) ); }
    ;

type-id
    : Y_NAME
        { $$ = WResIDFromStr( $1.string ); RcMemFree( $1.string ); }
    | string-constant
        { $$ = WResIDFromStr( $1.string ); RcMemFree( $1.string ); }
    | constant-expression
        { $$ = WResIDFromNum( $1.Value ); }
    ;

pragma-statment
    : Y_POUND_PRAGMA Y_CODEPAGE  Y_LPAREN constant-expression Y_RPAREN
      {}
    ;


keyword-name
    : Y_ACCELTABLE
        { $$ = Y_ACCELTABLE; }
    | Y_ALT
        { $$ = Y_ALT; }
    | Y_ASSOCTABLE
        { $$ = Y_ASSOCTABLE; }
    | Y_AUTOCHECKBOX
        { $$ = Y_AUTOCHECKBOX; }
    | Y_AUTORADIOBUTTON
        { $$ = Y_AUTORADIOBUTTON; }
    | Y_BEGIN
        { $$ = Y_BEGIN; }
    | Y_BITMAP
        { $$ = Y_BITMAP; }
    | Y_CHAR
        { $$ = Y_CHAR; }
    | Y_CHARTABLE
        { $$ = Y_CHARTABLE; }
    | Y_CHECKBOX
        { $$ = Y_CHECKBOX; }
    | Y_CODEPAGE
        { $$ = Y_CODEPAGE; }
    | Y_COMBOBOX
        { $$ = Y_COMBOBOX; }
    | Y_CONTAINER
        { $$ = Y_CONTAINER; }
    | Y_CONTROL
        { $$ = Y_CONTROL; }
    | Y_CTEXT
        { $$ = Y_CTEXT; }
    | Y_CURSOR
        { $$ = Y_CURSOR; }
    | Y_DEFAULTICON
        { $$ = Y_DEFAULTICON; }
    | Y_DEFPUSHBUTTON
        { $$ = Y_DEFPUSHBUTTON; }
    | Y_DIALOG
        { $$ = Y_DIALOG; }
    | Y_DISCARDABLE
        { $$ = Y_DISCARDABLE; }
    | Y_DLGINCLUDE
        { $$ = Y_DLGINCLUDE; }
    | Y_DLGTEMPLATE
        { $$ = Y_DLGTEMPLATE; }
    | Y_EDITTEXT
        { $$ = Y_EDITTEXT; }
    | Y_END
        { $$ = Y_END; }
    | Y_ENTRYFIELD
        { $$ = Y_ENTRYFIELD; }
    | Y_FIXED
        { $$ = Y_FIXED; }
    | Y_FKAITEM
        { $$ = Y_FKAITEM; }
    | Y_FKALONG
        { $$ = Y_FKALONG; }
    | Y_FKAROW
        { $$ = Y_FKASHORT; }
    | Y_FKASHORT
        { $$ = Y_FKASHORT; }
    | Y_FONT
        { $$ = Y_FONT; }
    | Y_FONTDIR
        { $$ = Y_FONTDIR; }
    | Y_FRAME
        { $$ = Y_FRAME; }
    | Y_GROUPBOX
        { $$ = Y_GROUPBOX; }
    | Y_HELP
        { $$ = Y_HELP; }
    | Y_HELPITEM
        { $$ = Y_HELPITEM; }
    | Y_HELPSUBITEM
        { $$ = Y_HELPSUBITEM; }
    | Y_HELPTABLE
        { $$ = Y_HELPTABLE; }
    | Y_ICON
        { $$ = Y_ICON; }
    | Y_IMPURE
        { $$ = Y_IMPURE; }
    | Y_KEYTABLE
        { $$ = Y_KEYTABLE; }
    | Y_LISTBOX
        { $$ = Y_LISTBOX; }
    | Y_LOADONCALL
        { $$ = Y_LOADONCALL; }
    | Y_LONEKEY
        { $$ = Y_LONEKEY; }
    | Y_LTEXT
        { $$ = Y_LTEXT; }
    | Y_MENU
        { $$ = Y_MENU; }
    | Y_MENUITEM
        { $$ = Y_MENUITEM; }
    | Y_MESSAGETABLE
        { $$ = Y_MESSAGETABLE; }
    | Y_MLE
        { $$ = Y_MLE; }
    | Y_MOVEABLE
        { $$ = Y_MOVEABLE; }
    | Y_NONSHARED
        { $$ = Y_NONSHARED; }
    | Y_NOTEBOOK
        { $$ = Y_NOTEBOOK; }
    | Y_POINTER
        { $$ = Y_POINTER; }
    | Y_PRELOAD
        { $$ = Y_PRELOAD; }
    | Y_PRESPARAMS
        { $$ = Y_PRESPARAMS; }
    | Y_PURE
        { $$ = Y_PURE; }
    | Y_PUSHBUTTON
        { $$ = Y_PUSHBUTTON; }
    | Y_RADIOBUTTON
        { $$ = Y_RADIOBUTTON; }
    | Y_RCDATA
        { $$ = Y_RCDATA; }
    | Y_RCINCLUDE
        { $$ = Y_RCINCLUDE; }
    | Y_RESOURCE
        { $$ = Y_RESOURCE; }
    | Y_RTEXT
        { $$ = Y_RTEXT; }
    | Y_SCANCODE
        { $$ = Y_SCANCODE; }
    | Y_SEGALIGN
        { $$ = Y_SEGALIGN; }
    | Y_SEPARATOR
        { $$ = Y_SEPARATOR; }
    | Y_SHARED
        { $$ = Y_SHARED; }
    | Y_SHIFT
        { $$ = Y_SHIFT; }
    | Y_SLIDER
        { $$ = Y_SLIDER; }
    | Y_SPINBUTTON
        { $$ = Y_SPINBUTTON; }
    | Y_STRINGTABLE
        { $$ = Y_STRINGTABLE; }
    | Y_SUBITEMSIZE
        { $$ = Y_SUBITEMSIZE; }
    | Y_SUBMENU
        { $$ = Y_SUBMENU; }
    | Y_SYSCOMMAND
        { $$ = Y_SYSCOMMAND; }
    | Y_VALUESET
        { $$ = Y_VALUESET; }
    | Y_VIRTUALKEY
        { $$ = Y_VIRTUALKEY; }
    | Y_VKEYTABLE
        { $$ = Y_VKEYTABLE; }
    | Y_WINDOW
        { $$ = Y_WINDOW; }
    | Y_WINDOWTEMPLATE
        { $$ = Y_WINDOWTEMPLATE; }
    ;

comma-opt
    : Y_COMMA
    | /* nothing */
    ;

single-line-resource
    : resource-type name-id file-name
        { SemAddSingleLineResource( $2, $1, NULL, $3.string ); }
    | resource-type name-id resource-options file-name
        { SemAddSingleLineResource( $2, $1, &($3), $4.string ); }
    ;

resource-options
    : resource-option
        { $$ = SemAddFirstMemOption( $1 ); }
    | resource-options resource-option
        { $$ = SemAddMemOption( $1, $2 ); }
    ;

resource-option
    : Y_PRELOAD
        { $$ = Y_PRELOAD; }
    | Y_LOADONCALL
        { $$ = Y_LOADONCALL; }
    | Y_FIXED
        { $$ = Y_FIXED; }
    | Y_MOVEABLE
        { $$ = Y_MOVEABLE; }
    | Y_PURE
        { $$ = Y_PURE; }
    | Y_IMPURE
        { $$ = Y_IMPURE; }
    | Y_DISCARDABLE
        { $$ = Y_DISCARDABLE; }
    | Y_SEGALIGN
        { $$ = Y_SEGALIGN; }
    ;

file-name
    : Y_NAME
    | Y_DOS_FILENAME
    | string-constant
    ;

resource-type
    : Y_BITMAP
        { $$ = Y_BITMAP; }
    | Y_DEFAULTICON
        { $$ = Y_DEFAULTICON; }
    | Y_FONT
        { $$ = Y_FONT; }
    | Y_ICON
        { $$ = Y_ICON; }
    | Y_POINTER
        { $$ = Y_POINTER; }
    ;

user-defined-resource
    : name-id comma-opt type-id user-defined-data
        {
            SemAddResourceFree( $1, $3,
                    MEMFLAG_PURE | MEMFLAG_MOVEABLE | MEMFLAG_DISCARDABLE, $4 );
        }
    | name-id comma-opt type-id resource-options user-defined-data
        {
            SemCheckMemFlags( &($4), 0, MEMFLAG_DISCARDABLE | MEMFLAG_MOVEABLE,
                    MEMFLAG_PURE );
            SemAddResourceFree( $1, $3, $4.flags, $5 );
        }
    ;

user-defined-data
    : file-name
        { $$ = SemCopyRawFile( $1.string ); RcMemFree( $1.string ); }
    | raw-data-section
        { $$ = SemFlushDataElemList( $1, TRUE ); }
    ;

raw-data-section
    : Y_BEGIN raw-data-items Y_END
       { $$ = $2; }
    | Y_LBRACE raw-data-items Y_RBRACE
       { $$ = $2; }
    ;

raw-data-items
    : raw-data-item
        { $$ = SemNewDataElemList( $1 ); }
    | raw-data-items raw-data-item
        { $$ = SemAppendDataElem( $1, $2 ); }
    | raw-data-items Y_COMMA
        { $$ = $1; }
    ;

raw-data-item
    : string-constant
        {
            $$.IsString = TRUE;
            $$.TmpStr = TRUE;
            $$.StrLen = $1.length;
            $$.Item.String = $1.string;
            $$.LongString = $1.lstring;
        }
    | constant-expression
        { $$.IsString = FALSE; $$.Item.Num = $1.Value; }
    ;

rcdata-resource
    : Y_RCDATA name-id user-defined-data
        {
            SemAddResourceFree( $2, WResIDFromNum( RT_RCDATA ),
                    MEMFLAG_PURE | MEMFLAG_MOVEABLE | MEMFLAG_DISCARDABLE, $3 );
        }
    | Y_RCDATA name-id resource-options user-defined-data
        {
            SemCheckMemFlags( &($3), 0, MEMFLAG_DISCARDABLE|MEMFLAG_MOVEABLE,
                    MEMFLAG_PURE );
            SemAddResourceFree( $2, WResIDFromNum( RT_RCDATA ), $3.flags, $4 );
        }
    ;

string-table-resource
    : Y_STRINGTABLE string-section
        {
            SemMergeStrTable( $2,
                MEMFLAG_PURE | MEMFLAG_MOVEABLE | MEMFLAG_DISCARDABLE );
        }
    | Y_STRINGTABLE resource-options string-section
        {
            SemCheckMemFlags( &($2), 0, MEMFLAG_MOVEABLE | MEMFLAG_DISCARDABLE,
                            MEMFLAG_PURE );
            SemMergeStrTable( $3, $2.flags );
        }
    ;

message-table-resource
    : name-id Y_MESSAGETABLE file-name
        {
            SemAddMessageTable( $1, &$3 );
        }
    ;

string-section
    : Y_BEGIN string-items Y_END
        { $$ = $2; }
    | Y_LBRACE string-items Y_RBRACE
        { $$ = $2; }
    ;

string-items
    : string-item
        {
            $$ = SemNewStringTable();
            SemAddStrToStringTable( $$, $1.ItemID, $1.String );
            RcMemFree( $1.String );
        }
    | string-items string-item
        {
            SemAddStrToStringTable( $1, $2.ItemID, $2.String );
            $$ = $1;
            RcMemFree( $2.String );
        }
    ;

string-item
    : string-id comma-opt string-constant
        { $$.ItemID = $1; $$.String = $3.string; }
    ;

string-id
    : constant-expression
        { $$ = $1.Value; }
    ;

id-value
    : constant-expression
        { $$ = $1.Value; }
    ;

accel-table-resource
    : Y_ACCELTABLE name-id acc-section
        {
            SemMergeAccTable( $2, $3,
                MEMFLAG_PURE | MEMFLAG_MOVEABLE | MEMFLAG_DISCARDABLE );
        }
    | Y_ACCELTABLE name-id resource-options acc-section
        {
            SemCheckMemFlags( &($3), 0, MEMFLAG_MOVEABLE | MEMFLAG_DISCARDABLE,
                            MEMFLAG_PURE );
            SemMergeAccTable( $2, $4, $3.flags );
        }
    ;

acc-section
    : Y_BEGIN acc-items Y_END
        { $$ = $2; }
    | Y_LBRACE acc-items Y_RBRACE
        { $$ = $2; }
    ;

acc-items
    : acc-item
        {
            $$ = SemNewAccelTable();
            SemAddStrToAccelTable( $$, $1.ItemID, $1.String );
            RcMemFree( $1.String );
        }
    | acc-items acc-item
        {
            SemAddStrToAccelTable( $1, $2.ItemID, $2.String );
            $$ = $1;
            RcMemFree( $2.String );
        }
    ;

acc-item
    : acc-key Y_COMMA acc-cmd Y_COMMA acc-item-options
        { $$ = $1; }    /* TODO */
    ;

acc-key
    : constant-expression
        { $$ = $1.Value; }
    ;
acc-cmd
    : constant-expression
        { $$ = $1.Value; }
    ;

acc-item-options
    : acc-item-option
    | acc-item-options comma-opt acc-item-option
        {
            if ($3.flags == ACCEL_ASCII) {
                $$.flags = $1.flags & ~ACCEL_VIRTKEY;
            } else {
                $$.flags = $1.flags | $3.flags;
            }
            $$.typegiven = $1.typegiven || $3.typegiven;
        }
    ;

acc-item-option
    : Y_ALT
        { $$.flags = ACCEL_ALT; $$.typegiven = FALSE; }
    | Y_CHAR
        { $$.flags = ACCEL_CHAR; $$.typegiven = FALSE; }
    | Y_CONTROL
        { $$.flags = ACCEL_CONTROL; $$.typegiven = FALSE; }
    | Y_HELP
        { $$.flags = ACCEL_HELP; $$.typegiven = FALSE; }
    | Y_LONEKEY
        { $$.flags = ACCEL_LONEKEY; $$.typegiven = FALSE; }
    | Y_SCANCODE
        { $$.flags = ACCEL_SCANCODE; $$.typegiven = FALSE; }
    | Y_SHIFT
        { $$.flags = ACCEL_SHIFT; $$.typegiven = FALSE; }
    | Y_SYSCOMMAND
        { $$.flags = ACCEL_SYSCOMMAND; $$.typegiven = FALSE; }
    | Y_VIRTUALKEY
        { $$.flags = ACCEL_VIRTKEY; $$.typegiven = TRUE; }
    ;

menu-resource
    : name-id Y_MENU menu-section
        { SemWriteMenu( $1, MEMFLAG_PURE|MEMFLAG_MOVEABLE|MEMFLAG_DISCARDABLE,
                    $3, Y_MENU ); }
    | name-id Y_MENU resource-options menu-section
        {
            SemCheckMemFlags( &($3), 0, MEMFLAG_MOVEABLE | MEMFLAG_DISCARDABLE,
                            MEMFLAG_PURE );
            SemWriteMenu( $1, $3.flags, $4, Y_MENU );
        }
    ;

menu-section
    : Y_BEGIN menu-items Y_END
        { $$ = $2; }
    | Y_LBRACE menu-items Y_RBRACE
        { $$ = $2; }
    ;

menu-items
    : menu-item
        { $$ = SemNewMenu( $1 ); }
    | menu-items menu-item
        { $$ = SemAddMenuItem( $1, $2 ); }
    ;

menuId
    : constant-expression
      { $$ = $1.Value; }
    ;

menuType
    : constant-expression
      { $$ = $1.Value; }
    ;

menuState
    : constant-expression
      { $$ = $1.Value; }
    ;

helpId
    : constant-expression
      { $$ = $1.Value; }
    ;

menu-item
    : menu-entry-stmt
        {
            $$.next = NULL;
            $$.prev = NULL;
            $$.UseUnicode = (CmdLineParms.TargetOS == RC_TARGET_OS_WIN32);
            $$.IsPopup = FALSE;
            $$.item.normal = $1;
        }
    ;

menu-entry-stmt
    : Y_MENUITEM menu-entry-defn
        { $$ = $2; }
    ;

menu-entry-defn
    : Y_SEPARATOR comma-opt
        {
            $$.type = MT_SEPARATOR;
            $$.menuData.ItemText = NULL;
            $$.menuData.ItemID = 0;
            $$.menuData.ItemFlags = 0;
            $$.menuExData.ItemType = MENUEX_SEPARATOR;
            $$.menuExData.ItemState = 0;
        }
    | menu-text comma-opt
        {
            $$.type = MT_MENUEX_NO_ID;
            $$.menuData.ItemText = $1.string;
            $$.menuData.ItemID = 0;
            $$.menuData.ItemFlags = 0;
            $$.menuExData.ItemType = 0L;
            $$.menuExData.ItemState = 0L;
        }

    | menu-text comma-opt menu-result comma-opt
        {
            $$.type = MT_EITHER;
            $$.menuData.ItemText = $1.string;
            $$.menuData.ItemID = $3;
            $$.menuData.ItemFlags = 0;
            $$.menuExData.ItemType = 0L;
            $$.menuExData.ItemState = 0L;
        }
    | menu-text comma-opt menu-result comma-opt menuType comma-opt
        {
            $$.type = MT_MENUEX;
            $$.menuData.ItemText = $1.string;
            $$.menuData.ItemID = $3;
            $$.menuData.ItemFlags = 0;
            $$.menuExData.ItemType = $5;
            $$.menuExData.ItemState = 0L;
        }

    | menu-text comma-opt menu-result comma-opt menuType comma-opt
                menuState comma-opt
        {
            $$.type = MT_MENUEX;
            $$.menuData.ItemText = $1.string;
            $$.menuData.ItemID = $3;
            $$.menuData.ItemFlags = 0;
            $$.menuExData.ItemType = $5;
            $$.menuExData.ItemState = $7;
        }

    | menu-text comma-opt menu-result comma-opt menu-item-options comma-opt
        {
            $$.type = MT_MENU;
            $$.menuData.ItemText = $1.string;
            $$.menuData.ItemID = $3;
            $$.menuData.ItemFlags = $5;
        }
    ;

menu-text
    : string-constant
    ;

menu-result
    : constant-expression
        { $$ = $1.Value; }
    ;

menu-item-options
    : menu-item-option
        { $$ = SemAddFirstMenuOption( $1 ); }
    | menu-item-options comma-opt menu-item-option
        { $$ = SemAddMenuOption( $1, $3 ); }
    ;

menu-item-option
    : Y_BITMAP
        { $$ = Y_BITMAP; }
    | Y_HELP
        { $$ = Y_HELP; }
    ;

dialog
    : Y_DIALOG
        { $$ = Y_DIALOG; }
    ;

helpId-opt
    : comma-opt constant-expression
       { $$.HelpId = $2.Value; $$.HelpIdDefined = TRUE; }
    | /* nothing */
       { $$.HelpId = 0; $$.HelpIdDefined = FALSE; }
    ;

dlg-resource
    : name-id dialog size-info helpId-opt diag-options-section
              diag-control-section
        {
            SemWriteDialogBox( $1,
               MEMFLAG_PURE|MEMFLAG_MOVEABLE|MEMFLAG_DISCARDABLE,
               $3, $5, $6, $4, $2 );
        }
    | name-id dialog size-info helpId-opt diag-control-section
        {
            SemWriteDialogBox( $1,
               MEMFLAG_PURE|MEMFLAG_MOVEABLE|MEMFLAG_DISCARDABLE,
               $3, NULL, $5, $4, $2 );
        }
    | name-id dialog resource-options comma-opt size-info helpId-opt
               diag-options-section diag-control-section
        {
            SemCheckMemFlags( &($3), 0, MEMFLAG_MOVEABLE | MEMFLAG_DISCARDABLE,
                            MEMFLAG_PURE );
            SemWriteDialogBox( $1, $3.flags, $5, $7, $8, $6, $2 );
        }
    | name-id dialog resource-options comma-opt size-info helpId-opt
                diag-control-section
        {
            SemCheckMemFlags( &($3), 0, MEMFLAG_MOVEABLE | MEMFLAG_DISCARDABLE,
                            MEMFLAG_PURE );
            SemWriteDialogBox( $1, $3.flags, $5, NULL, $7, $6, $2 );
        }
    ;

size-info
    : size-x comma-opt size-y comma-opt size-w comma-opt size-h
        { $$.x = $1; $$.y = $3; $$.width = $5; $$.height = $7; }
    ;

size-x
    : constant-expression
        { $$ = $1.Value; }
    ;

size-y
    : constant-expression
        { $$ = $1.Value; }
    ;

size-w
    : constant-expression
        { $$ = $1.Value; }
    ;

size-h
    : constant-expression
        { $$ = $1.Value; }
    ;

diag-options-section
    : diag-options-stmt
        { $$ = SemNewDiagOptions( &($1) ); }
    | diag-options-section diag-options-stmt
        { $$ = SemDiagOptions( $1, &($2) ); }
    ;

diag-options-stmt
    : menu-stmt
    | font-stmt
    ;

menu-stmt
    : Y_MENU name-id
        {
            $$.token = Y_MENU;
            $$.Opt.Name = WResIDToNameOrOrd( $2 );
            RcMemFree( $2 );
        }
    ;

ctl-class-name
    : string-constant
        { $$ = ResStrToNameOrOrd( $1.string ); RcMemFree( $1.string ); }
    | Y_PUSHBUTTON
        { $$ = ResStrToNameOrOrd( "PUSHBUTTON" ); }
    | Y_COMBOBOX
        { $$ = ResStrToNameOrOrd( "COMBOBOX" ); }
    | Y_ENTRYFIELD
        { $$ = ResStrToNameOrOrd( "ENTRYFIELD" ); }
    | Y_LISTBOX
        { $$ = ResStrToNameOrOrd( "LISTBOX" ); }
    | constant-expression
        { $$ = ResNumToNameOrOrd( $1.Value ); }
    ;

font-stmt
    : Y_FONT point-size comma-opt typeface
        {
            $$.token = Y_FONT;
            $$.Opt.Font.PointSize = $2;
            $$.Opt.Font.FontName = $4.string;
            $$.Opt.Font.FontWeight = 0;
            $$.Opt.Font.FontItalic = 0;
            $$.Opt.Font.FontExtra = 1;
            $$.Opt.Font.FontWeightDefined = FALSE;
            $$.Opt.Font.FontItalicDefined = FALSE;
        }
    | Y_FONT point-size comma-opt typeface comma-opt fontweight
        {
            $$.token = Y_FONT;
            $$.Opt.Font.PointSize = $2;
            $$.Opt.Font.FontName = $4.string;
            $$.Opt.Font.FontWeight = $6;
            $$.Opt.Font.FontItalic = 0;
            $$.Opt.Font.FontExtra = 1;
            $$.Opt.Font.FontWeightDefined = TRUE;
            $$.Opt.Font.FontItalicDefined = FALSE;
        }
    ;

fontweight
    : constant-expression
      { $$ = $1.Value; }
    ;

point-size
    : constant-expression
        { $$ = $1.Value; }
    ;

typeface
    : string-constant
    ;

diag-control-section
    : Y_BEGIN diag-control-stmts Y_END
        {
            $$ = $2;
        }
    | Y_LBRACE diag-control-stmts Y_RBRACE
        { $$ = $2; }
    | Y_BEGIN Y_END
        { $$ = SemEmptyDiagCtrlList(); }
    | Y_LBRACE Y_RBRACE
        { $$ = SemEmptyDiagCtrlList(); }
    ;

diag-data-elements
    : raw-data-section
    | /* Nothing */
      { $$ = NULL; }
    ;

diag-control-stmts
    : diag-control-stmt diag-data-elements
        { $$ = SemNewDiagCtrlList( $1, $2 ); }
    | diag-control-stmts diag-control-stmt diag-data-elements
        { $$ = SemAddDiagCtrlList( $1, $2, $3 ); }
    ;

diag-control-stmt
    : ltext-stmt
    | rtext-stmt
    | ctext-stmt
    | autocheckbox-stmt
    | autoradiobutton-stmt
    | checkbox-stmt
    | pushbutton-stmt
    | listbox-stmt
    | groupbox-stmt
    | defpushbutton-stmt
    | radiobutton-stmt
    | edittext-stmt
    | combobox-stmt
    | icon-stmt
    | control-stmt
    ;

cntl-text-options
    : string-constant cntl-options
        {
            $2.Text = ResStrToNameOrOrd( $1.string );
            RcMemFree( $1.string );
            $$ = $2;
        }
    ;

cntl-options
    : comma-opt cntl-id comma-opt size-info
        {
            $$.ID = $2;
            $$.Size = $4;
            $$.Style.Mask = 0;
            $$.Text = NULL;
            $$.ExtendedStyle = 0L;
            $$.HelpId = 0L;
            $$.HelpIdDefined = FALSE;
        }
    | comma-opt cntl-id comma-opt size-info comma-opt
        {
            $$.ID = $2;
            $$.Size = $4;
            $$.Style = 0L;
            $$.Text = NULL;
            $$.ExtendedStyle = 0L;
            $$.HelpId = 0L;
            $$.HelpIdDefined = FALSE;
        }
    ;

cntl-id
    : constant-expression
        { $$ = $1.Value; }
    ;

ltext-stmt
    : Y_LTEXT cntl-text-options
        { $$ = SemNewDiagCtrl( Y_LTEXT, $2 ); }
    ;

rtext-stmt
    : Y_RTEXT cntl-text-options
        { $$ = SemNewDiagCtrl( Y_RTEXT, $2 ); }
    ;

ctext-stmt
    : Y_CTEXT cntl-text-options
        { $$ = SemNewDiagCtrl( Y_CTEXT, $2 ); }
    ;

autocheckbox-stmt
    : Y_AUTOCHECKBOX cntl-text-options
        { $$ = SemNewDiagCtrl( Y_AUTOCHECKBOX, $2 ); }
    ;

autoradiobutton-stmt
    : Y_AUTORADIOBUTTON cntl-text-options
        { $$ = SemNewDiagCtrl( Y_AUTORADIOBUTTON, $2 ); }
    ;

checkbox-stmt
    : Y_CHECKBOX cntl-text-options
        { $$ = SemNewDiagCtrl( Y_CHECKBOX, $2 ); }
    ;

pushbutton-stmt
    : Y_PUSHBUTTON cntl-text-options
        { $$ = SemNewDiagCtrl( Y_PUSHBUTTON, $2 ); }
    ;

listbox-stmt
    : Y_LISTBOX cntl-options
        { $$ = SemNewDiagCtrl( Y_LISTBOX, $2 ); }
    ;

groupbox-stmt
    : Y_GROUPBOX cntl-text-options
        { $$ = SemNewDiagCtrl( Y_GROUPBOX, $2 ); }
    ;

defpushbutton-stmt
    : Y_DEFPUSHBUTTON cntl-text-options
        { $$ = SemNewDiagCtrl( Y_DEFPUSHBUTTON, $2 ); }
    ;

radiobutton-stmt
    : Y_RADIOBUTTON cntl-text-options
        { $$ = SemNewDiagCtrl( Y_RADIOBUTTON, $2 ); }
    ;

edittext-stmt
    : Y_EDITTEXT cntl-options
        { $$ = SemNewDiagCtrl( Y_EDITTEXT, $2 ); }
    ;

combobox-stmt
    : Y_COMBOBOX cntl-options
        { $$ = SemNewDiagCtrl( Y_COMBOBOX, $2 ); }
    ;

icon-stmt
    : Y_ICON icon-name comma-opt cntl-id comma-opt icon-parms
        { $6.Text = $2; $6.ID = $4; $$ = SemNewDiagCtrl( Y_ICON, $6 ); }
    ;

icon-name
    : name-id
        { $$ = WResIDToNameOrOrd( $1 ); RcMemFree( $1 ); }
    ;

icon-parms
    : size-x comma-opt size-y
        {
            $$.Size.x = $1;
            $$.Size.y = $3;
            $$.Size.width = 0;          /* ignore width, height, style */
            $$.Size.height = 0;
            $$.Style.Mask = 0;
            $$.ExtendedStyle = 0L;
        }
    | size-x comma-opt size-y comma-opt size-w comma-opt size-h
        {
            $$.Size.x = $1;
            $$.Size.y = $3;
            $$.Size.width = $5;         /* ignore style */
            $$.Size.height = $7;
            $$.Style.Mask = 0;
            $$.ExtendedStyle = 0L;
        }
    ;

control-stmt
    : Y_CONTROL cntl-text comma-opt cntl-id comma-opt ctl-class-name comma-opt
                    comma-opt size-info
        {
            $$ = SemSetControlData( $7, $4, $8, $2, $6, 0L, NULL );
        }

    | Y_CONTROL cntl-text comma-opt cntl-id comma-opt ctl-class-name comma-opt
                    comma-opt size-info comma-opt helpId-opt
        {
            $$ = SemSetControlData( $7, $4, $9, $2, $6, $11.Value, NULL );
        }
    ;

cntl-text
    : name-id
    ;

string-constant
    : Y_STRING
    | Y_LSQ_BRACKET string-group Y_RSQ_BRACKET
        {
            $$ = $2;
        }
    ;

string-group
    : Y_STRING
    | string-group Y_STRING
        {
            $$.lstring = ( $1.lstring | $2.lstring );
            $$.length = $1.length + $2.length;
            $$.string = RcMemMalloc( $$.length + 1 );
            strcpy( $$.string, $1.string );
            strcat( $$.string, $2.string );
            RcMemFree( $1.string );
            RcMemFree( $2.string );
        }
    ;

constant-expression
    : conditional-exp
    ;

conditional-exp
    : log-or-exp
    | log-or-exp Y_QUESTION constant-expression Y_COLON conditional-exp
        { $$ = $1.Value ? $3 : $5; }
    ;

log-or-exp
    : log-and-exp
    | log-or-exp Y_OR log-and-exp
        { $$.Value = $1.Value || $3.Value; $$.Mask = $1.Mask | $3.Mask; }
    ;

log-and-exp
    : bit-or-exp
    | log-and-exp Y_AND bit-or-exp
        { $$.Value = $1.Value && $3.Value; $$.Mask = $1.Mask | $3.Mask; }
    ;

bit-or-exp
    : bit-xor-exp
    | bit-or-exp Y_BITOR bit-xor-exp
        { $$.Value = $1.Value | $3.Value; $$.Mask = $1.Mask | $3.Mask; }
    ;

bit-xor-exp
    : bit-and-exp
    | bit-xor-exp Y_BITXOR bit-and-exp
        { $$.Value = $1.Value ^ $3.Value; $$.Mask = $1.Mask | $3.Mask; }
    ;

bit-and-exp
    : equality-exp
    | bit-and-exp Y_BITAND equality-exp
        { $$.Value = $1.Value & $3.Value; $$.Mask = $1.Mask | $3.Mask; }
    ;

equality-exp
    : relational-exp
    | equality-exp Y_EQ relational-exp
        { $$.Value = $1.Value == $3.Value; $$.Mask = $1.Mask | $3.Mask; }
    | equality-exp Y_NE relational-exp
        { $$.Value = $1.Value != $3.Value; $$.Mask = $1.Mask | $3.Mask; }
    ;

relational-exp
    : shift-exp
    | relational-exp Y_GT shift-exp
        { $$.Value = $1.Value > $3.Value; $$.Mask = $1.Mask | $3.Mask; }
    | relational-exp Y_LT shift-exp
        { $$.Value = $1.Value < $3.Value; $$.Mask = $1.Mask | $3.Mask; }
    | relational-exp Y_GE shift-exp
        { $$.Value = $1.Value >= $3.Value; $$.Mask = $1.Mask | $3.Mask; }
    | relational-exp Y_LE shift-exp
        { $$.Value = $1.Value <= $3.Value; $$.Mask = $1.Mask | $3.Mask; }
    ;

shift-exp
    : additive-exp
    | shift-exp Y_SHIFTL additive-exp
        { $$.Value = $1.Value << $3.Value; $$.Mask = $1.Mask | $3.Mask; }
    | shift-exp Y_SHIFTR additive-exp
        { $$.Value = $1.Value >> $3.Value; $$.Mask = $1.Mask | $3.Mask; }
    ;

additive-exp
    : multiplicative-exp
    | additive-exp Y_PLUS multiplicative-exp
        { $$.Value = $1.Value + $3.Value; $$.Mask = $1.Mask | $3.Mask; }
    | additive-exp Y_MINUS multiplicative-exp
        { $$.Value = $1.Value - $3.Value; $$.Mask = $1.Mask | $3.Mask; }
    ;

multiplicative-exp
    : unary-exp
    | multiplicative-exp Y_TIMES unary-exp
        { $$.Value = $1.Value * $3.Value; $$.Mask = $1.Mask | $3.Mask; }
    | multiplicative-exp Y_DIVIDE unary-exp
        { $$.Value = $1.Value / $3.Value; $$.Mask = $1.Mask | $3.Mask; }
    | multiplicative-exp Y_MOD unary-exp
        { $$.Value = $1.Value % $3.Value; $$.Mask = $1.Mask | $3.Mask; }
    ;

unary-exp
    : primary-exp
    | Y_MINUS unary-exp
        { $$.Value = - $2.Value; $$.Mask = $2.Mask; }
    | Y_BITNOT unary-exp
        { $$.Value = ~ $2.Value; $$.Mask = $2.Mask; }
    | Y_NOT unary-exp
        { $$.Value = ! $2.Value; $$.Mask = $2.Mask; }
    ;

primary-exp
    : Y_INTEGER
        { $$.Mask = $1.val; $$.Value = $1.val; }
    | Y_LPAREN constant-expression Y_RPAREN
        { $$ = $2; }
    ;

%%
