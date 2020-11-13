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

#include "morpho_fusion.h"
#include "test_morpho_fusion.h"

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
    int64_t time;
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
    printf(" - %-*s completed %8ld ms  \n", 30, "Sigma_Delta Naive", test_mouvement());
    printf(" - %-*s completed %8ld ms  \n", 30, "Morphologie Naive", test_morpho());


    printf(" - %-*s completed %8ld ms  %s\n", 30, "Sigma_Delta SIMD", test_mouvement_SIMD(), check_results(1) ? "[OK]" : "[KO]");
    printf(" - %-*s completed %8ld ms  %s\n", 30, "Morphologie SIMD", test_morpho_SIMD(), check_results(2) ? "[OK]" : "[KO]");
    printf(" - %-*s completed %8ld ms  %s\n", 30, "Morphologie fusion", test_morpho_fusion(), check_results(3) ? "[OK]" : "[KO]");


    puts("====================");
    puts("=== End of tests ===");
    puts("====================");
 

    printf("\nCheck the pictures in the project folder:\n");
    printf("Output of Sigma_Delta              : Projet-HPC/sdout\n");
    printf("Output of Morphologie              : Projet-HPC/morphoout\n");
    printf("Output of Sigma_Delta SIMD         : Projet-HPC/sdout_SIMD\n");
    printf("Output of Morphologie SIMD         : Projet-HPC/morphoout_SIMD\n");
    printf("Output of Morphologie avec fusion  : Projet-HPC/fusion\n");

    
    return 0;   

}
