.func freopen _wfreopen _ufreopen
#include <stdio.h>
FILE *freopen( const char *filename,
               const char *mode,
               FILE *fp );
.ixfunc2 '&StrIo' &func
.if &'length(&wfunc.) ne 0 .do begin
FILE *_wfreopen( const wchar_t *filename,
                 const wchar_t *mode,
                 FILE *fp );
.ixfunc2 '&StrIo' &wfunc
.ixfunc2 '&Wide' &wfunc
.do end
.if &'length(&ufunc.) ne 0 .do begin
FILE *_ufreopen( const wchar_t *filename,
                 const wchar_t *mode,
                 FILE *fp );
.ixfunc2 '&StrIo' &ufunc
.do end
.funcend
.desc begin
The stream located by the
.kw fp
pointer is closed.
The &func function opens the file whose name is the string pointed to
by
.arg filename,
and associates a stream with it.
The stream information is placed in the structure located by the
.arg fp
pointer.
.np
The argument
.arg mode
is described in the description of the
.kw fopen
function.
.if &'length(&wfunc.) ne 0 .do begin
.np
The &wfunc function is identical to &func except that it accepts
wide-character string arguments for
.arg filename
and
.arg mode.
.do end
.if &'length(&ufunc.) ne 0 .do begin
.np
The &ufunc Unicode function is identical to &func except that it
accepts Unicode string arguments for
.arg filename
and
.arg mode.
.do end
.desc end
.return begin
The &func function returns a pointer to the object controlling the
stream.
This pointer must be passed as a parameter to subsequent functions for
performing operations on the file.
If the open operation fails, &func returns
.mono NULL.
.im errnoref
.return end
.see begin
.seelist &function. _dos_open fclose fcloseall fdopen fopen freopen
.seelist &function. _fsopen _grow_handles _hdopen open _open_osfhandle
.seelist &function. _popen sopen
.see end
.exmp begin
#include <stdio.h>

void main()
  {
    FILE *fp;
    int c;
.exmp break
    fp = freopen( "file", "r", stdin );
    if( fp != NULL ) {
      while( (c = fgetchar()) != EOF )
        fputchar(c);
      fclose( fp );
    }
  }
.exmp end
.class ANSI
.system
