/*
    ULS API prototypes and typedefs
*/
#ifndef _ULS_UNIDEF
#define _ULS_UNIDEF

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <time.h>
#include <os2def.h>
#include <ulserrno.h>
#include <ulsitem.h>
#include <callconv.h>

#define UNI_TOKEN_POINTER      1
#define UNI_MBS_STRING_POINTER 2
#define UNI_UCS_STRING_POINTER 3

#define UNI_SYSTEM_LOCALES  1
#define UNI_USER_LOCALES    2

#undef LANG
#undef LC_ALL
#undef LC_COLLATE
#undef LC_CTYPE
#undef LC_NUMERIC
#undef LC_MONETARY
#undef LC_TIME
#undef LC_MESSAGES

#define LANG         (-2)
#define LC_ALL       (-1)
#define LC_COLLATE    0
#define LC_CTYPE      1
#define LC_NUMERIC    2
#define LC_MONETARY   3
#define LC_TIME       4
#define LC_MESSAGES   5

#define N_LC_CATEGORIES 6
#define ULS_LNAMEMAX    32

#define CT_UPPER  0x0001
#define CT_LOWER  0x0002
#define CT_DIGIT  0x0004
#define CT_SPACE  0x0008
#define CT_PUNCT  0x0010
#define CT_CNTRL  0x0020
#define CT_BLANK  0x0040
#define CT_XDIGIT 0x0080
#define CT_ALPHA  0x0100
#define CT_ALNUM  0x0200
#define CT_GRAPH  0x0400
#define CT_PRINT  0x0800
#define CT_NUMBER 0x1000
#define CT_SYMBOL 0x2000
#define CT_ASCII  0x8000

#define C1_UPPER    CT_UPPER
#define C1_LOWER    CT_LOWER
#define C1_DIGIT    CT_DIGIT
#define C1_SPACE    CT_SPACE
#define C1_PUNCT    CT_PUNCT
#define C1_CNTRL    CT_CNTRL
#define C1_BLANK    CT_BLANK
#define C1_XDIGIT   CT_XDIGIT
#define C1_ALPHA    CT_ALPHA

#define C2_NOTAPPLICABLE    0x00
#define C2_LEFTTORIGHT      0x01
#define C2_RIGHTTOLEFT      0x02
#define C2_EUROPENUMBER     0x03
#define C2_EUROPESEPARATOR  0x04
#define C2_EUROPETERMINATOR 0x05
#define C2_ARABICNUMBER     0x06
#define C2_COMMONSEPARATOR  0x07
#define C2_BLOCKSEPARATOR   0x08
#define C2_WHITESPACE       0x0A
#define C2_OTHERNEUTRAL     0x0B
#define C2_MIRRORED         0x0C

#define CHS_NONCHAR    0x00
#define CHS_OTHER      0x01
#define CHS_LATIN      0x02
#define CHS_CYRILLIC   0x03
#define CHS_ARABIC     0x04
#define CHS_GREEK      0x05
#define CHS_HEBREW     0x06
#define CHS_THAI       0x07
#define CHS_KATAKANA   0x08
#define CHS_HIRAGANA   0x09
#define CHS_HANGUEL    0x0a
#define CHS_BOPOMOFO   0x0b
#define CHS_DEVANAGARI 0x0c
#define CHS_TELUGU     0x0d
#define CHS_BENGALI    0x0e
#define CHS_GUJARATI   0x0f
#define CHS_GURMUKHI   0x10
#define CHS_TAMIL      0x11
#define CHS_LAO        0x12

#define CHS_PUNCTSTART 0x20
#define CHS_PUNCTEND   0x21
#define CHS_DINGBAT    0x22
#define CHS_MATH       0x23
#define CHS_APL        0x24
#define CHS_ARROW      0x25
#define CHS_BOX        0x26
#define CHS_DASH       0x27
#define CHS_CURRENCY   0x28
#define CHS_FRACTION   0x29
#define CHS_LINESEP    0x2a
#define CHS_USERDEF    0x2b

#define C3_NONSPACING  0x0001
#define C3_DIACRITIC   0x0002
#define C3_NSDIACRITIC 0x0003
#define C3_VOWELMARK   0x0004
#define C3_NSVOWEL     0x0005
#define C3_SYMBOL      0x0008
#define C3_KATAKANA    0x0010
#define C3_HIRAGANA    0x0020
#define C3_HALFWIDTH   0x0040
#define C3_FULLWIDTH   0x0080
#define C3_IDEOGRAPH   0x0100
#define C3_KASHIDA     0x0200
#define C3_ALPHA       0x8000
#define C3_MASK        0x83FF

#define CCP_437  0x0001
#define CCP_850  0x0002
#define CCP_SYMB 0x0004
#define CCP_1252 0x0008
#define CCP_1250 0x0010
#define CCP_1251 0x0020
#define CCP_1254 0x0040
#define CCP_1257 0x0080

#define CT_ITYPE     1
#define CT_BIDI      2
#define CT_CHARSET   3
#define CT_EXTENDED  4
#define CT_CODEPAGE  5
#define CT_INDEX     6
#define CT_CTYPE1    7
#define CT_CTYPE2    8
#define CT_CTYPE3    9

typedef int ulsBool;

#ifndef _ULS_UNICHAR_DEFINED
  #define _ULS_UNICHAR_DEFINED
  typedef unsigned short UniChar;
#endif

typedef void *LocaleObject;
typedef unsigned int LocaleToken;
typedef void *AttrObject;
typedef void *XformObject;

typedef struct UniLconv {
    UniChar *decimal_point;
    UniChar *thousands_sep;
    short   *grouping;
    UniChar *int_curr_symbol;
    UniChar *currency_symbol;
    UniChar *mon_decimal_point;
    UniChar *mon_thousands_sep;
    short   *mon_grouping;
    UniChar *positive_sign;
    UniChar *negative_sign;
    short   int_frac_digits;
    short   frac_digits;
    short   p_cs_precedes;
    short   p_sep_by_space;
    short   n_cs_precedes;
    short   n_sep_by_space;
    short   p_sign_posn;
    short   n_sign_posn;
    short   os2_mondecpt;
    short   reserved;
    UniChar *debit_sign;
    UniChar *credit_sign;
    UniChar *left_parenthesis;
    UniChar *right_parenthesis;
} UNILCONV;

typedef struct {
    USHORT itype;
    CHAR   bidi;
    CHAR   charset;
    USHORT extend;
    USHORT codepage;
} UNICTYPE;

int      CALLCONV UniCreateLocaleObject(int,const void*,LocaleObject*);
int      CALLCONV UniQueryLocaleObject(const LocaleObject,int,int,void**);
int      CALLCONV UniFreeLocaleObject(LocaleObject);
int      CALLCONV UniFreeMem(void*);
int      CALLCONV UniLocaleStrToToken(int,const void*,LocaleToken*);
int      CALLCONV UniLocaleTokenToStr(const LocaleToken,int,void**);
int      CALLCONV UniQueryLocaleInfo(const LocaleObject,struct UniLconv**);
int      CALLCONV UniFreeLocaleInfo(struct UniLconv*);
int      CALLCONV UniQueryLocaleItem(const LocaleObject,LocaleItem,UniChar**);
int      CALLCONV UniQueryLocaleValue(const LocaleObject,LocaleItem,int*);
size_t   CALLCONV UniStrftime(const LocaleObject,UniChar*,size_t,const UniChar*,const struct tm*);
UniChar* CALLCONV UniStrptime(const LocaleObject,const UniChar*,const UniChar*,struct tm*);
int      CALLCONV UniStrfmon(const LocaleObject,UniChar*,size_t,const UniChar*, ... );

UniChar* CALLCONV UniStrcat(UniChar*,const UniChar*);
UniChar* CALLCONV UniStrchr(const UniChar*,UniChar);
int      CALLCONV UniStrcmp(const UniChar*,const UniChar*);
UniChar* CALLCONV UniStrcpy(UniChar*, const UniChar*);
size_t   CALLCONV UniStrcspn(const UniChar*,const UniChar*);
size_t   CALLCONV UniStrlen(const UniChar*);
UniChar* CALLCONV UniStrncat(UniChar*,const UniChar*,size_t);
int      CALLCONV UniStrncmp(const UniChar*,const UniChar*,size_t);
UniChar* CALLCONV UniStrncpy(UniChar *,const UniChar*,size_t);
UniChar* CALLCONV UniStrpbrk(const UniChar*,const UniChar*);
UniChar* CALLCONV UniStrrchr(const UniChar*,UniChar);
size_t   CALLCONV UniStrspn(const UniChar*,const UniChar*);
UniChar* CALLCONV UniStrstr(const UniChar*,const UniChar*);
UniChar* CALLCONV UniStrtok(UniChar*, const UniChar*);

int CALLCONV UniCreateAttrObject(const LocaleObject,const UniChar*,AttrObject*);
int CALLCONV UniQueryCharAttr(AttrObject,UniChar);
int CALLCONV UniScanForAttr(AttrObject,const UniChar*,size_t,ulsBool,size_t*);
int CALLCONV UniFreeAttrObject(AttrObject);
int CALLCONV UniQueryAlnum(const LocaleObject,UniChar);
int CALLCONV UniQueryAlpha(const LocaleObject,UniChar);
int CALLCONV UniQueryBlank(const LocaleObject,UniChar);
int CALLCONV UniQueryCntrl(const LocaleObject,UniChar);
int CALLCONV UniQueryDigit(const LocaleObject,UniChar);
int CALLCONV UniQueryGraph(const LocaleObject,UniChar);
int CALLCONV UniQueryLower(const LocaleObject,UniChar);
int CALLCONV UniQueryPrint(const LocaleObject,UniChar);
int CALLCONV UniQueryPunct(const LocaleObject,UniChar);
int CALLCONV UniQuerySpace(const LocaleObject,UniChar);
int CALLCONV UniQueryUpper(const LocaleObject,UniChar);
int CALLCONV UniQueryXdigit(const LocaleObject,UniChar);

int     CALLCONV UniCreateTransformObject(const LocaleObject,const UniChar*,XformObject*);
int     CALLCONV UniTransformStr(XformObject,const UniChar*,int*,UniChar*,int*);
int     CALLCONV UniFreeTransformObject(XformObject);
UniChar CALLCONV UniTransLower(const LocaleObject,UniChar);
UniChar CALLCONV UniTransUpper(const LocaleObject,UniChar);

int CALLCONV UniStrtod(const LocaleObject,const UniChar*,UniChar**,double*);
int CALLCONV UniStrtol(const LocaleObject,const UniChar*,UniChar**,int,long int*);
int CALLCONV UniStrtoul(const LocaleObject,const UniChar*,UniChar**,int,unsigned long int*);

int      CALLCONV UniStrcoll(const LocaleObject,const UniChar*,const UniChar*);
size_t   CALLCONV UniStrxfrm(const LocaleObject,UniChar*,const UniChar*,size_t);
int      CALLCONV UniStrcmpi(const LocaleObject,const UniChar*,const UniChar*);
int      CALLCONV UniStrncmpi(const LocaleObject,const UniChar*,const UniChar*,const size_t);
UniChar  CALLCONV UniToupper(UniChar);
UniChar  CALLCONV UniTolower(UniChar);
UniChar* CALLCONV UniStrupr(UniChar*);
UniChar* CALLCONV UniStrlwr(UniChar*);

int CALLCONV UniMapCtryToLocale(unsigned long,UniChar*,size_t);

int CALLCONV UniSetUserLocaleItem(UniChar*,int,int,void*);
int CALLCONV UniMakeUserLocale(UniChar*,UniChar*);
int CALLCONV UniDeleteUserLocale(UniChar*);
int CALLCONV UniCompleteUserLocale(void);
int CALLCONV UniQueryLocaleList(int,UniChar*,int);
int CALLCONV UniQueryLanguageName(UniChar*,UniChar*,UniChar**);
int CALLCONV UniQueryCountryName(UniChar*,UniChar*,UniChar**);

int       CALLCONV UniQueryChar(UniChar,ULONG);
ULONG     CALLCONV UniQueryAttr(UniChar*);
ULONG     CALLCONV UniQueryStringType(UniChar*,int,USHORT*,int);
UNICTYPE* CALLCONV UniQueryCharType(UniChar);
ULONG     CALLCONV UniQueryCharTypeTable(ULONG*,UNICTYPE**);
int       CALLCONV UniQueryNumericValue(UniChar);

#ifdef __cplusplus
}
#endif

#endif
