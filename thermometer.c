#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <errno.h>

#define BLK "\e[1;30m"
#define RED "\e[1;31m"
#define GRN "\e[32m"
#define YEL "\e[33m"
#define BLU "\e[34m"
#define MAG "\e[35m"
#define CYN "\e[36m"
#define WHT "\e[37m"
#define NRM "\e[0m"

static bool
parse_fail( const char *s, unsigned long *pd )
{
    *pd = strtoul( s, 0, 10 );

    if ( *pd == ULONG_MAX && errno == ERANGE ) {
        fprintf( stderr, RED "Error: \"%s\" is too large: %s\n" NRM, s, strerror(errno) );
        return true;
    }
    else if ( (long)(*pd) < 0 ) {
        fprintf( stderr, RED "Error with %ld:  values must be positive.\n" NRM, (long)(*pd) );
        return true;
    }
    else if ( *pd == 0 && errno == EINVAL ) {
        fprintf( stderr, RED "Error parsing \"%s\": %s\n" NRM, s, strerror(errno) );
        return true;
    }
    else
        return false;

}

int main(int argc, char *argv[])
{
    unsigned long cur, max;

    if ( argc != 3 ) {
        fprintf( stderr, YEL "Usage: %s <current> <max>\n" NRM, argv[0] );
        return EXIT_FAILURE;
    }

    if ( parse_fail( argv[1], &cur ))
        return EXIT_FAILURE;

    if (parse_fail( argv[2], &max ))
        return EXIT_FAILURE;

    if ( max == 0 ) {
        fprintf( stderr, YEL "Error: Max cannot be zero\n" NRM );
        return EXIT_FAILURE;
    }

    // Going over just maxes to 100%
    if ( cur > max )
        cur = max;

    double percent = (double)(cur)/(double)(max) * 100.0;

    printf( "%s[%s", CYN, ( percent < 80.0 ? GRN : (percent < 90.0 ? YEL : RED ) ) );

    for (int i=0; i<(int)(percent); ++i )
        putchar( '*' );

    fputs( NRM, stdout );
    for (int j=(int)(percent); j<100; ++j )
        putchar( '-' );

    printf( CYN "]" NRM "%3.2f%%\n", percent );

    return EXIT_SUCCESS;
}
