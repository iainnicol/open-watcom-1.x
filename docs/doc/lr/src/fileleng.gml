.func filelength _filelengthi64
#include <&iohdr>
long filelength( int &fd );
.ixfunc2 '&OsIo' &func
__int64 _filelengthi64( int &fd );
.ixfunc2 '&OsIo' _&func.i64
.funcend
.desc begin
The &func function returns, as a 32-bit long integer, the number of
bytes in the opened file indicated by the file &handle
.arg &fd..
.np
The _&func.i64 function returns, as a 64-bit integer, the number of
bytes in the opened file indicated by the file &handle
.arg &fd..
.desc end
.return begin
If an error occurs in &func, (&minus.1L) is returned.
.np
If an error occurs in _&func.i64, (&minus.1I64) is returned.
.np
.im errnoref
.np
Otherwise, the number of bytes written to the file is returned.
.return end
.see begin
.seelist filelength fstat lseek tell
.see end
.exmp begin
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <&iohdr>

void main()
  {
    int &fd;
.exmp break
    /* open a file for input              */
.if '&machsys' eq 'PP' .do begin
    &fd = open( "file", O_RDONLY );
.do end
.el .if '&machsys' eq 'QNX' .do begin
    &fd = open( "file", O_RDONLY );
.do end
.el .do begin
    &fd = open( "file", O_RDONLY | O_TEXT );
.do end
    if( &fd != -1 ) {
      printf( "Size of file is %ld bytes\n",
              filelength( &fd ) );
      close( &fd );
    }
  }
.exmp output
Size of file is 461 bytes
.exmp end
.class WATCOM
.system
