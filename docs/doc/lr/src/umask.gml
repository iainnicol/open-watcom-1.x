.func umask
#include <sys&pc.types.h>
#include <sys&pc.stat.h>
.if '&machsys' eq 'PP' .do begin
mode_t umask( mode_t cmask );
.do end
.el .if '&machsys' eq 'QNX' .do begin
mode_t umask( mode_t cmask );
.do end
.el .do begin
#include <fcntl.h>
#include <&iohdr>
int umask( int cmask );
.do end
.ixfunc2 '&OsIo' &func
.funcend
.desc begin
The &func function sets the process's file mode creation mask to
.arg cmask.
The process's file mode creation mask is used during
.if '&machsys' eq 'PP' .do begin
.kw creat
.ct,
.kw mkdir
or
.kw open
.do end
.el .if '&machsys' eq 'QNX' .do begin
.kw creat
.ct,
.kw mkdir
.ct,
.kw mkfifo
.ct,
.kw open
or
.kw sopen
.do end
.el .do begin
.kw creat
.ct,
.kw open
or
.kw sopen
.do end
to turn off permission bits in the
.arg permission
argument supplied.
In other words, if a bit in the mask is on, then the corresponding bit
in the file's requested permission value is disallowed.
.pp
The argument
.arg cmask
is a constant expression involving the constants described below.
.im openperv
.pp
For example, if
.kw S_IRUSR
is specified, then reading is not allowed (i.e., the file is write only).
If
.kw S_IWUSR
is specified, then writing is not allowed (i.e., the file is read only).
.desc end
.return begin
The &func function returns the previous value of
.arg cmask.
.return end
.see begin
.seelist umask chmod creat mkdir mkfifo open sopen
.see end
.exmp begin
#include <sys&pc.types.h>
#include <sys&pc.stat.h>
.if '&machsys' ne 'QNX' .do begin
#include <fcntl.h>
#include <&iohdr>
.do end

void main()
  {
.if '&machsys' eq 'PP' .do begin
    mode_t old_mask;
.do end
.el .if '&machsys' eq 'QNX' .do begin
    mode_t old_mask;
.do end
.el .do begin
    int old_mask;
.do end
.exmp break
    /* set mask to create read-only files */
    old_mask = umask( S_IWUSR | S_IWGRP | S_IWOTH |
                      S_IXUSR | S_IXGRP | S_IXOTH );
  }
.exmp end
.class POSIX 1003.1
.system
