.func stat _stat _stati64 _wstat _wstati64
#include <sys&pc.stat.h>
int stat( const char *path, struct stat *buf );
.ixfunc2 '&FileOp' &func
.if &'length(&_func.) ne 0 .do begin
int _stat( const char *path, struct _stat *buf );
.ixfunc2 '&FileOp' &_func
.do end
int _stati64( const char *path, struct _stati64 *buf );
.ixfunc2 '&FileOp' &_func
.if &'length(&wfunc.) ne 0 .do begin
int _wstat( const wchar_t *path, struct _stat *buf );
.ixfunc2 '&FileOp' &wfunc
.ixfunc2 '&Wide' &wfunc
.do end
int _wstati64( const wchar_t *path, struct _stati64 *buf );
.ixfunc2 '&FileOp' &wfunc.i64
.ixfunc2 '&Wide' &wfunc.i64
.funcend
.desc begin
The &func functions obtain information about the file or directory
referenced in
.arg path.
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
.if '&machsys' ne 'PP' .do begin
.begterm 12
.term EACCES
Search permission is denied for a component of
.arg path.
.if '&machsys' eq 'QNX' .do begin
.term EIO
A physical error occurred on the block device.
.term ENAMETOOLONG
The argument
.arg path
exceeds {PATH_MAX} in length, or a pathname component is longer than
{NAME_MAX}.
.term ENOENT
The named file does not exist or
.arg path
is an empty string.
.term ENOTDIR
A component of
.arg path
is not a directory.
.do end
.endterm
.do end
.error end
.see begin
.seelist stat fstat fsys_stat fsys_fstat lstat
.see end
.exmp begin
#include <stdio.h>
#include <sys&pc.stat.h>

void main()
  {
    struct stat buf;
.exmp break
    if( stat( "file", &buf ) != -1 ) {
      printf( "File size = %d\n", buf.st_size );
    }
  }
.exmp end
.class POSIX 1003.1
.if &'length(&_func.) ne 0 .do begin
.np
&_func conforms to ANSI/ISO naming conventions
.do end
.system
