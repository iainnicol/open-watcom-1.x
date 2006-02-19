/*
    ULS error codes
*/
#ifndef _ULS_ERRNO
#define _ULS_ERRNO

#ifdef __cplusplus
extern "C" {
#endif

#define ULS_API_ERROR_BASE 0x00020400
#define ULS_API_ERROR(x)   (ULS_API_ERROR_BASE|(x))

typedef enum _uls_return_codes {
    ULS_SUCCESS         =  0x00000000,
    ULS_OTHER           =  ULS_API_ERROR(1),
    ULS_ILLEGALSEQUENCE =  ULS_API_ERROR(2),
    ULS_MAXFILESPERPROC =  ULS_API_ERROR(3),
    ULS_MAXFILES        =  ULS_API_ERROR(4),
    ULS_NOOP            =  ULS_API_ERROR(5),
    ULS_TOOMANYKBD      =  ULS_API_ERROR(6),
    ULS_KBDNOTFOUND     =  ULS_API_ERROR(7),
    ULS_BADHANDLE       =  ULS_API_ERROR(8),
    ULS_NODEAD          =  ULS_API_ERROR(9),
    ULS_NOSCAN          =  ULS_API_ERROR(10),
    ULS_INVALIDSCAN     =  ULS_API_ERROR(11),
    ULS_NOTIMPLEMENTED  =  ULS_API_ERROR(12),
    ULS_NOMEMORY        =  ULS_API_ERROR(13),
    ULS_INVALID         =  ULS_API_ERROR(14),
    ULS_BADOBJECT       =  ULS_API_ERROR(15),
    ULS_NOTOKEN         =  ULS_API_ERROR(16),
    ULS_NOMATCH         =  ULS_API_ERROR(17),
    ULS_BUFFERFULL      =  ULS_API_ERROR(18),
    ULS_RANGE           =  ULS_API_ERROR(19),
    ULS_UNSUPPORTED     =  ULS_API_ERROR(20),
    ULS_BADATTR         =  ULS_API_ERROR(21),
    ULS_VERSION         =  ULS_API_ERROR(22)
} uls_error_t;

#ifdef __cplusplus
}
#endif

#endif
