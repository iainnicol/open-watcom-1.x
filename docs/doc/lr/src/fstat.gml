.func fstat _fstat _fstati64 _wfstat _wfstati64
#include <sys&pc.types.h>
#include <sys&pc.stat.h>
int fstat( int &fd, struct stat *buf );
.ixfunc2 '&OsIo' &func
.if &'length(&_func.) ne 0 .do begin
int _fstat( int &fd, struct stat *buf );
.ixfunc2 '&OsIo' &_func
.do end
int _fstati64( int handle, struct _stati64 *buf );
.ixfunc2 '&OsIo' _&func.i64
int _wfstat( int handle, struct _stat *buf );
.ixfunc2 '&OsIo' _w&func
.ixfunc2 '&Wide' _w&func
int _wfstati64( int handle, struct _stati64 *buf );
.ixfunc2 '&OsIo' _w&func.i64
.ixfunc2 '&Wide' _w&func.i64
.funcend
.desc begin
The &func functions obtain information about an open file whose file
&handle is
.arg &fd..
This information is placed in the structure located at the address
indicated by
.arg buf.
.im statdesc
.if &'length(&_func.) ne 0 .do begin
.np
The &_func function is identical to &func..
Use &_func for ANSI/ISO naming conventions.
.do end
The
.kw _fstati64,
.kw _wfstat,
and
.kw _wfstati64
functions differ from &func in the type of structure that they are
asked to fill in.
The
.kw _wfstat
and
.kw _wfstati64
functions deal with wide character strings.
The differences in the structures are described above.
.desc end
.im statrtn
.error begin
.begterm 12
.termhd1 Constant
.termhd2 Meaning
.term EBADF
The
.arg &fd
argument is not a valid file &handle..
.endterm
.error end
.see begin
.seelist fstat creat dup dup2 fcntl fsys_stat fsys_fstat
.seelist fstat open sopen stat pipe
.see end
.exmp begin
#include <stdio.h>
#include <sys&pc.types.h>
#include <sys&pc.stat.h>
#include <fcntl.h>
#include <&iohdr>
.exmp break
void main()
{
    int &fd, rc;
    struct stat buf;
.exmp break
    &fd = open( "file", O_RDONLY );
    if( &fd != -1 ) {
        rc = fstat( &fd, &buf );
        if( rc != -1 )
            printf( "File size = %d\n", buf.st_size );
        close( &fd );
    }
}
.exmp end
.class begin POSIX
.ansiname &_func
.class end
.system
