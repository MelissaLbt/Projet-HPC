/* -------------- */
/* --- main.c --- */
/* -------------- */

#include <stdio.h>
#include <stdlib.h>

#include "nrdef.h"
#include "nrutil.h"

#include "vnrdef.h"
#include "vnrutil.h"

#include "mutil.h"

#include "simd1D.h"
#include "simd2D.h"

void info(void)
{
#ifdef ENABLE_BENCHMARK
    puts("mode Benchmark ON");
    puts("DEBUG OFF");
#else
    puts("mode Benchmark OFF");
    puts("DEBUG ON");
#endif
}
int main(int argc, char *argv[])
{
    info();
    main_1D(argc, argv);
    main_2D(argc, argv);
    return 0;   
}