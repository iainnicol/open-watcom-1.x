#include <stdio.h>
#include <jstring.h>

JMOJI chars[] = {
    0x8340,
    0x8364,
    0x8396
};

#define SIZE sizeof( chars ) / sizeof( JMOJI )

void main()
  {
    int   i;
    JMOJI c1, c2;

    for( i = 0; i < SIZE; i++ ) {
        c1 = chars[ i ];
        c2 = jtohira( c1 );
        printf( "%c%c - %c%c\n", c1>>8, c1, c2>>8, c2 );
    }
  }
