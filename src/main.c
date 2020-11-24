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
#include "mymacro.h"

#include "test_unitaire.h"

#include "mouvement.h"
#include "morpho.h"
#include "test_mouvement.h"
#include "test_morpho.h"

#include "mouvement_SSE2.h"
#include "morpho_SSE2.h"
#include "test_mouvement_SSE2.h"
#include "test_morpho_SSE2.h"

#include "mouvement_AVX2.h"
#include "test_mouvement_AVX2.h"
#include "morpho_AVX2.h"
#include "test_morpho_AVX2.h"

#define N_PIXEL (200*320*240)

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
    char *format = "%6.2f ";
    int64_t time;

    // chronometrie
    int iter, niter = 4;
    int run, nrun = 5;
    double t0, t1, dt, tmin, t;
    double cycles;

    info();

//-------- test unitaire pour valider l'algo Sigma_Delta ---------//

    puts("===========================");
    puts("=== Tests unitary begin ===");
    puts("===========================");
<<<<<<< HEAD
    test_morpho_AVX2(0);
    //
    // printf("Validation des algo scalaire:\n");
    // printf(" - %-*s completed     %s\n", 25, "SigmaDelta_step0_tu", SigmaDelta_step0_tu() ? "[OK]" : "[KO]");
    // printf(" - %-*s completed     %s\n", 25, "SigmaDelta_step1_tu", SigmaDelta_step1_tu() ? "[OK]" : "[KO]");
    // printf(" - %-*s completed     %s\n", 25, "SigmaDelta_step2_tu", SigmaDelta_step2_tu() ? "[OK]" : "[KO]");
    // printf(" - %-*s completed     %s\n", 25, "SigmaDelta_step3_tu", SigmaDelta_step3_tu() ? "[OK]" : "[KO]");
    // printf(" - %-*s completed     %s\n", 25, "SigmaDelta_step4_tu", SigmaDelta_step4_tu() ? "[OK]" : "[KO]");
    // printf(" - %-*s completed     %s\n", 25, "Morpho_initbord_tu",  Morpho_initbord_tu()  ? "[OK]" : "[KO]");
    // printf(" - %-*s completed     %s\n", 25, "Morpho_erosion_tu",   Morpho_erosion_tu()   ? "[OK]" : "[KO]");
    // printf(" - %-*s completed     %s\n", 25, "Morpho_dilatation_tu",Morpho_dilatation_tu()? "[OK]" : "[KO]");
    //
    //
    // puts("==========================");
    // puts("=== Tests formal begin ===");
    // puts("==========================");
    //
    // CHRONO(time = test_mouvement(),cycles);
    // printf(" - %-*s completed %7ld ms        ", 25, "Sigma_Delta Naive", time);
    // BENCH(printf("CPP: %6.2f  DEBIT: %6ld M", cycles/N_PIXEL, N_PIXEL/(1000*time))); puts("\n");
    //
    // CHRONO(time = test_morpho(),cycles);
    // printf(" - %-*s completed %7ld ms        ", 25, "Morphologie Naive", time);
    // BENCH(printf("CPP: %6.2f  DEBIT: %6ld M", cycles/N_PIXEL, N_PIXEL/(1000*time))); puts("\n");
    //
    // CHRONO(time = test_mouvement_SSE2(),cycles);
    // printf(" - %-*s completed %7ld ms %s   ", 25, "Sigma_Delta SSE2", time, check_results(1) ? "[OK]" : "[KO]");
    // BENCH(printf("CPP: %6.2f  DEBIT: %6ld M", cycles/N_PIXEL, N_PIXEL/(1000*time))); puts("\n");
    //
    // CHRONO(time = test_mouvement_AVX2(),cycles);
    // printf(" - %-*s completed %7ld ms %s   ", 25, "Sigma_Delta AVX2", time, check_results(1) ? "[OK]" : "[KO]");
    // BENCH(printf("CPP: %6.2f  DEBIT: %6ld M", cycles/N_PIXEL, N_PIXEL/(1000*time))); puts("\n");
    //
    // CHRONO(time = test_morpho_SSE2(0),cycles);
    // printf(" - %-*s completed %7ld ms %s   ", 25, "Morphologie SSE2", time, check_results(2) ? "[OK]" : "[KO]");
    // BENCH(printf("CPP: %6.2f  DEBIT: %6ld M", cycles/N_PIXEL, N_PIXEL/(1000*time))); puts("\n");
    //
    // CHRONO(time = test_morpho_AVX2(0),cycles);
    // printf(" - %-*s completed %7ld ms %s   ", 25, "Morphologie AVX2", time, check_results(2) ? "[OK]" : "[KO]");
    // BENCH(printf("CPP: %6.2f  DEBIT: %6ld M", cycles/N_PIXEL, N_PIXEL/(1000*time))); puts("\n");
    //
    // CHRONO(time = test_morpho_SSE2(1),cycles);
    // printf(" - %-*s completed %7ld ms %s   ", 25, "Morphologie SSE2_rot", time, check_results(2) ? "[OK]" : "[KO]");
    // BENCH(printf("CPP: %6.2f  DEBIT: %6ld M", cycles/N_PIXEL, N_PIXEL/(1000*time))); puts("\n");
    //
    // CHRONO(time = test_morpho_SSE2(2),cycles);
    // printf(" - %-*s completed %7ld ms %s   ", 25, "Morphologie SSE2_red", time, check_results(2) ? "[OK]" : "[KO]");
    // BENCH(printf("CPP: %6.2f  DEBIT: %6ld M", cycles/N_PIXEL, N_PIXEL/(1000*time))); puts("\n");
    //
    // CHRONO(time = test_morpho_AVX2(1),cycles);
    // printf(" - %-*s completed %7ld ms %s   ", 25, "Morphologie AVX2_red", time, check_results(2) ? "[OK]" : "[KO]");
    // BENCH(printf("CPP: %6.2f  DEBIT: %6ld M", cycles/N_PIXEL, N_PIXEL/(1000*time))); puts("\n");
    //
    // CHRONO(time = test_morpho_SSE2(3),cycles);
    // printf(" - %-*s completed %7ld ms %s   ", 25, "Morphologie fusion", time, check_results(2) ? "[OK]" : "[KO]");
    // BENCH(printf("CPP: %6.2f  DEBIT: %6ld M", cycles/N_PIXEL, N_PIXEL/(1000*time))); puts("\n");
    //
    // CHRONO(time = test_morpho_SSE2(4),cycles);
    // printf(" - %-*s completed %7ld ms %s   ", 25, "Morphologie pipeline", time, check_results(2) ? "[OK]" : "[KO]");
    // BENCH(printf("CPP: %6.2f  DEBIT: %6ld M", cycles/N_PIXEL, N_PIXEL/(1000*time))); puts("\n");
    //
    //
    // CHRONO(time = test_morpho_SSE2(5),cycles);
    // printf(" - %-*s completed %7ld ms %s   ", 25, "Morphologie OpenMP", time, check_results(2) ? "[OK]" : "[KO]");
    // BENCH(printf("CPP: %6.2f  DEBIT: %6ld M", cycles/N_PIXEL, N_PIXEL/(1000*time))); puts("\n");
=======

    printf("Validation des algo scalaire:\n");
    printf(" - %-*s completed     %s\n", 30, "SigmaDelta_step0_tu",       SigmaDelta_step0_tu()       ? "[OK]" : "[KO]");
    printf(" - %-*s completed     %s\n", 30, "SigmaDelta_step1_tu",       SigmaDelta_step1_tu()       ? "[OK]" : "[KO]");
    printf(" - %-*s completed     %s\n", 30, "SigmaDelta_step2_tu",       SigmaDelta_step2_tu()       ? "[OK]" : "[KO]");
    printf(" - %-*s completed     %s\n", 30, "SigmaDelta_step3_tu",       SigmaDelta_step3_tu()       ? "[OK]" : "[KO]");
    printf(" - %-*s completed     %s\n", 30, "SigmaDelta_step4_tu",       SigmaDelta_step4_tu()       ? "[OK]" : "[KO]");
    printf(" - %-*s completed     %s\n", 30, "SigmaDelta_integration_tu", SigmaDelta_integration_tu() ? "[OK]" : "[KO]");
    printf(" - %-*s completed     %s\n", 30, "Morpho_initbord_tu",        Morpho_initbord_tu()        ? "[OK]" : "[KO]");
    printf(" - %-*s completed     %s\n", 30, "Morpho_erosion_tu",         Morpho_erosion_tu()         ? "[OK]" : "[KO]");
    printf(" - %-*s completed     %s\n", 30, "Morpho_dilatation_tu",      Morpho_dilatation_tu()      ? "[OK]" : "[KO]");
    printf(" - %-*s completed     %s\n", 30, "Morpho_tu",                 Morpho_tu()                 ? "[OK]" : "[KO]");


    puts("==========================");
    puts("=== Tests formal begin ===");
    puts("==========================");

    CHRONO(time = test_mouvement(),cycles);
    printf(" - %-*s completed %7ld ms        ", 25, "Sigma_Delta Naive", time);
    BENCH(printf("CPP: %6.2f  DEBIT: %6ld M", cycles/N_PIXEL, N_PIXEL/(1000*time))); puts("\n");

    CHRONO(time = test_morpho(),cycles);
    printf(" - %-*s completed %7ld ms        ", 25, "Morphologie Naive", time);
    BENCH(printf("CPP: %6.2f  DEBIT: %6ld M", cycles/N_PIXEL, N_PIXEL/(1000*time))); puts("\n");

    CHRONO(time = test_mouvement_SSE2(),cycles);
    printf(" - %-*s completed %7ld ms %s   ", 25, "Sigma_Delta SSE2", time, check_results(1) ? "[OK]" : "[KO]");
    BENCH(printf("CPP: %6.2f  DEBIT: %6ld M", cycles/N_PIXEL, N_PIXEL/(1000*time))); puts("\n");

    CHRONO(time = test_mouvement_AVX2(),cycles);
    printf(" - %-*s completed %7ld ms %s   ", 25, "Sigma_Delta AVX2", time, check_results(1) ? "[OK]" : "[KO]");
    BENCH(printf("CPP: %6.2f  DEBIT: %6ld M", cycles/N_PIXEL, N_PIXEL/(1000*time))); puts("\n");

    CHRONO(time = test_morpho_SSE2(0),cycles);
    printf(" - %-*s completed %7ld ms %s   ", 25, "Morphologie SSE2", time, check_results(2) ? "[OK]" : "[KO]");
    BENCH(printf("CPP: %6.2f  DEBIT: %6ld M", cycles/N_PIXEL, N_PIXEL/(1000*time))); puts("\n");

    CHRONO(time = test_morpho_AVX2(0),cycles);
    printf(" - %-*s completed %7ld ms %s   ", 25, "Morphologie AVX2", time, check_results(2) ? "[OK]" : "[KO]");
    BENCH(printf("CPP: %6.2f  DEBIT: %6ld M", cycles/N_PIXEL, N_PIXEL/(1000*time))); puts("\n");

    CHRONO(time = test_morpho_SSE2(1),cycles);
    printf(" - %-*s completed %7ld ms %s   ", 25, "Morphologie SSE2_rot", time, check_results(2) ? "[OK]" : "[KO]");
    BENCH(printf("CPP: %6.2f  DEBIT: %6ld M", cycles/N_PIXEL, N_PIXEL/(1000*time))); puts("\n");

    CHRONO(time = test_morpho_SSE2(2),cycles);
    printf(" - %-*s completed %7ld ms %s   ", 25, "Morphologie SSE2_red", time, check_results(2) ? "[OK]" : "[KO]");
    BENCH(printf("CPP: %6.2f  DEBIT: %6ld M", cycles/N_PIXEL, N_PIXEL/(1000*time))); puts("\n");

    CHRONO(time = test_morpho_AVX2(1),cycles);
    printf(" - %-*s completed %7ld ms %s   ", 25, "Morphologie AVX2_red", time, check_results(2) ? "[OK]" : "[KO]");
    BENCH(printf("CPP: %6.2f  DEBIT: %6ld M", cycles/N_PIXEL, N_PIXEL/(1000*time))); puts("\n");

    CHRONO(time = test_morpho_SSE2(3),cycles);
    printf(" - %-*s completed %7ld ms %s   ", 25, "Morphologie fusion", time, check_results(2) ? "[OK]" : "[KO]");
    BENCH(printf("CPP: %6.2f  DEBIT: %6ld M", cycles/N_PIXEL, N_PIXEL/(1000*time))); puts("\n");

    CHRONO(time = test_morpho_SSE2(4),cycles);
    printf(" - %-*s completed %7ld ms %s   ", 25, "Morphologie pipeline", time, check_results(2) ? "[OK]" : "[KO]");
    BENCH(printf("CPP: %6.2f  DEBIT: %6ld M", cycles/N_PIXEL, N_PIXEL/(1000*time))); puts("\n");


    CHRONO(time = test_morpho_SSE2(5),cycles);
    printf(" - %-*s completed %7ld ms %s   ", 25, "Morphologie OpenMP", time, check_results(2) ? "[OK]" : "[KO]");
    BENCH(printf("CPP: %6.2f  DEBIT: %6ld M", cycles/N_PIXEL, N_PIXEL/(1000*time))); puts("\n");
>>>>>>> 483953c59e40b0ab2b572407db0c873912b26060

    // CHRONO(time = test_morpho_SSE2(6),cycles);
    // printf(" - %-*s completed %7ld ms %s   ", 25, "Morphologie fusion OMP", time, check_results(2) ? "[OK]" : "[KO]");
    // BENCH(printf("CPP: %6.2f  DEBIT: %6ld M", cycles/N_PIXEL, N_PIXEL/(1000*time))); puts("\n");


    puts("====================");
    puts("=== End of tests ===");
    puts("====================");


    printf("\nCheck the pictures in the project folder:\n");
    printf("Output of Sigma_Delta              : Projet-HPC/sdout\n");
    printf("Output of Morphologie              : Projet-HPC/morphoout\n");
    printf("Output of Sigma_Delta SSE2         : Projet-HPC/sdout_SSE2\n");
    printf("Output of Morphologie SSE2         : Projet-HPC/morphoout_SSE2\n");
    printf("Output of Morphologie avec fusion  : Projet-HPC/morphoout_SSE2\n");


    return 0;

}
