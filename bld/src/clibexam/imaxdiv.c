#include <stdio.h>
#include <inttypes.h>

void print_time( intmax_t ticks )
{
    imaxdiv_t sec_ticks;
    imaxdiv_t min_sec;

    sec_ticks = imaxdiv( ticks, 1000000 );
    min_sec   = imaxdiv( sec_ticks.quot, 60 );
    printf( "It took %"PRIdMAX" minutes and %"PRIdMAX" seconds\n",
            min_sec.quot, min_sec.rem );
}

void main()
{
    print_time( 9876543210 );
}
