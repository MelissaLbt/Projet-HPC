/* -------------- */
/* --- main.c --- */
/* -------------- */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "nrdef.h"
#include "nrutil.h"

#include "vnrdef.h"
#include "vnrutil.h"

#include "mutil.h"


#include "mouvement.h"
#include "morpho.h"
#include "test_mouvement.h"
#include "test_morpho.h"
#include "mouvement_SIMD.h"
#include "morpho_SIMD.h"
#include "test_mouvement_SIMD.h"
#include "test_morpho_SIMD.h"


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
    
	//test_mouvement();
    //test_morpho();
    test_mouvement_SIMD();
    test_morpho();
    
    return 0;   
}
