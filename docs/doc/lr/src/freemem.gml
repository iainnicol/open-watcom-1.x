.func _dos_freemem
#include <&doshdr>
#if defined(__NT__) || \
  ( defined(__OS2__) && \
        (defined(__386__) || defined(__PPC__)) )
unsigned _dos_freemem( void *   segment );
#else
unsigned _dos_freemem( unsigned segment );
#endif
.ixfunc2 '&DosFunc' &func
.funcend
.desc begin
The &func function uses system call 0x49 to release memory that was
previously allocated by
.kw _dos_allocmem.
The value contained in
.arg segment
is the one returned by a previous call to
.kw _dos_allocmem.
.np
For 32-bit DOS applications, it is recommended that the corresponding
DPMI services be used.
.desc end
.return begin
The &func function returns zero if successful.
Otherwise, it returns an OS error code and sets
.kw errno
accordingly.
.return end
.see begin
.seelist _dos_freemem _dos_allocmem _dos_setblock free hfree
.see end
.exmp begin
#include <stdio.h>
#include <&doshdr>
.exmp break
void main()
  {
#if defined(__NT__) || \
  ( defined(__OS2__) && \
        (defined(__386__) || defined(__PPC__)) )
    void *segment;
#else
    unsigned short segment;
#endif
.exmp break
    /* Try to allocate 100 paragraphs, then free them */
    if( _dos_allocmem( 100, &segment ) != 0 ) {
      printf( "_dos_allocmem failed\n" );
      printf( "Only %u paragraphs available\n",
               segment );
    } else {
      printf( "_dos_allocmem succeeded\n" );
      if( _dos_freemem( segment ) != 0 ) {
        printf( "_dos_freemem failed\n" );
      } else {
        printf( "_dos_freemem succeeded\n" );
      }
    }
  }
.exmp end
.class DOS
.system
