.func memchr _fmemchr _umemchr
#include <string.h>
void *memchr( const void *buf, int ch, size_t length );
.ixfunc2 '&Search' &func
.if &farfnc eq 1 .do begin
void __far *_fmemchr( const void __far *buf,
                      int ch,
                      size_t length );
.ixfunc2 '&Search' &ffunc
.do end
:cmt. .if &'length(&ufunc.) ne 0 .do begin
:cmt. void *_umemchr( const void *buf, int ch, size_t length );
:cmt. .ixfunc2 '&Search' &ufunc
:cmt. .do end
.funcend
.desc begin
The &func function locates the first occurrence of
.arg ch
(converted to an unsigned char) in the first
.arg length
characters of the object pointed to by
.arg buf.
.im farfunc
:cmt. .if &'length(&ufunc.) ne 0 .do begin
:cmt. .np
:cmt. The &ufunc Unicode function is identical to &func except that it
:cmt. operates on 16-bit Unicode characters.
:cmt. The argument
:cmt. .arg length
:cmt. is interpreted to mean the number of Unicode characters.
:cmt. .do end
.desc end
.return begin
The &func function returns a pointer to the located character, or
.mono NULL
if the character does not occur in the object.
.return end
.see begin
.seelist &function. memchr memcmp memcpy memicmp memset
.see end
.exmp begin
#include <stdio.h>
#include <string.h>

void main()
  {
    char buffer[80];
    char *where;
.exmp break
    strcpy( buffer, "video x-rays" );
    where = (char *) memchr( buffer, 'x', 6 );
    if( where == NULL )
      printf( "'x' not found\n" );
    else
      printf( "%s\n", where );
    where = (char *) memchr( buffer, 'r', 9 );
    if( where == NULL )
      printf( "'r' not found\n" );
    else
      printf( "%s\n", where );
  }
.exmp end
.class ANSI
.system
