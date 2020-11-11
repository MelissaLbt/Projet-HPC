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

#include "test_unitaire.h"

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
//-------- test unitaire pour valider l'algo Sigma_Delta ---------//
    puts("===========================");
    puts("=== Tests unitary begin ===");
    puts("===========================");
    
    printf("Validation des algo scalaire:\n");
    printf(" - %-*s completed     %s\n", 25, "SigmaDelta_step0_tu", SigmaDelta_step0_tu() ? "[OK]" : "[KO]");
    printf(" - %-*s completed     %s\n", 25, "SigmaDelta_step1_tu", SigmaDelta_step1_tu() ? "[OK]" : "[KO]");
    printf(" - %-*s completed     %s\n", 25, "SigmaDelta_step2_tu", SigmaDelta_step2_tu() ? "[OK]" : "[KO]");
    printf(" - %-*s completed     %s\n", 25, "SigmaDelta_step3_tu", SigmaDelta_step3_tu() ? "[OK]" : "[KO]");
    printf(" - %-*s completed     %s\n", 25, "SigmaDelta_step4_tu", SigmaDelta_step4_tu() ? "[OK]" : "[KO]");
    printf(" - %-*s completed     %s\n", 25, "Morpho_gesbord",      Morpho_gesbord()    ? "[OK]" : "[KO]");
    printf(" - %-*s completed     %s\n", 25, "Morpho_erosion",      Morpho_erosion()    ? "[OK]" : "[KO]");
    printf(" - %-*s completed     %s\n", 25, "Morpho_dilatation",   Morpho_dilatation() ? "[OK]" : "[KO]");

    
    puts("==========================");
    puts("=== Tests formal begin ===");
    puts("==========================");
    printf(" - %-*s completed %8" PRId64 " ms\n", 25, "Sigma_Delta Naive", test_mouvement());
    printf(" - %-*s completed %8" PRId64 " ms\n", 25, "Morphologie naive", test_morpho());
    printf(" - %-*s completed %8" PRId64 " ms\n", 25, "Sigma_Delta SIMD", test_mouvement_SIMD());
    printf(" - %-*s completed %8" PRId64 " ms\n", 25, "Morphologie SIMD", test_morpho_SIMD());


    puts("====================");
    puts("=== End of tests ===");
    puts("====================");
 

    printf("\nCongratulations!! \n\nCheck the pictures in the project folder:\n");
    printf("Output of Sigma_Delta       : Projet-HPC/sdout\n");
    printf("Output of Morphologie       : Projet-HPC/morphoout\n");
    printf("Output of Sigma_Delta SIMD  : Projet-HPC/sdout_SIMD\n");

    
    return 0;   

}
