// ---------------- //
// --- dcycle.c --- //
// ---------------- //

// Copyright (c) Daniel Etiemble, LRI, Univ Paris-Sud www.lri.fr/~de
// Copyright (c)  Lionel Lacassagne, LRI, Univ Paris-Sud www.lri.fr/~lacas

#if defined(__INTEL_COMPILER) || defined(__ICC)
#include "ia32intrin.h" // chrono Intel
#else

#ifdef __GNUC__
// car ICC definie aussi GNUC dans certains cas (?)
#include "x86intrin.h" // chrono GCC
#endif

#endif

// ----------------
double dcycle(void)
// ----------------
{
    //return (double) readTSC();
    return _rdtsc();
}

/********************************************************************/
/*  MIPS SGI's Processor routine                                    */
/*  Provided by: Xavier Cavin                                       */
/********************************************************************/
#if defined(TIMER_MIPS) || defined(TIMER_SGI)
#include <time.h>
__uint64_t readTSC (void)
{
    struct timespec tp;
    clock_gettime (CLOCK_SGI_CYCLE, &tp);
    return (__uint64_t)(tp.tv_sec * (__uint64_t)1000000000) + (__uint64_t)tp.tv_nsec;
}
/* ------------ */
double dtime(void)
/* ------------ */
{
    return (double) (readTSC()/1000000.0);
}
#endif

/********************************************************************/
/* PowerPC cycle                                                    */
/* Provided by: Kazutomo Yoshii  kazutomo at mcs.anl.gov            */
/* http://www.mcs.anl.gov/~kazutomo/rdtsc.html                      */
/*                                                                  */
/********************************************************************/
#if defined(_ARCH_PPC)
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// keyword "static" has been removed

#define PPC_TB 75
//#define PPC_TB 1
/* ------------------------------------- */
__inline__ unsigned long long readTSC(void)
/* ------------------------------------- */
{
    unsigned long long int result=0;
    unsigned long int upper, lower,tmp;
    __asm__ volatile(
                     "0:                  \n"
                     "\tmftbu   %0           \n"
                     "\tmftb    %1           \n"
                     "\tmftbu   %2           \n"
                     "\tcmpw    %2,%0        \n"
                     "\tbne     0b         \n"
                     : "=r"(upper),"=r"(lower),"=r"(tmp)
                     );
    result = upper;
    result = result<<32;
    result = result|lower;
    
    return(result*PPC_TB);
}

/* -------------------------------------- */
__inline__ unsigned long long i64cycle(void)
/* -------------------------------------- */
{
    unsigned long long int result=0;
    unsigned long int upper, lower,tmp;
    __asm__ volatile(
                     "0:                  \n"
                     "\tmftbu   %0           \n"
                     "\tmftb    %1           \n"
                     "\tmftbu   %2           \n"
                     "\tcmpw    %2,%0        \n"
                     "\tbne     0b         \n"
                     : "=r"(upper),"=r"(lower),"=r"(tmp)
                     );
    result = upper;
    result = result<<32;
    result = result|lower;
    
    return(75*result*PPC_TB);
}
/* ------------- */
double dcycle(void)
/* ------------- */
{
    unsigned long long int result=0;
    unsigned long int upper, lower,tmp;
    __asm__ volatile(
                     "0:                  \n"
                     "\tmftbu   %0           \n"
                     "\tmftb    %1           \n"
                     "\tmftbu   %2           \n"
                     "\tcmpw    %2,%0        \n"
                     "\tbne     0b         \n"
                     : "=r"(upper),"=r"(lower),"=r"(tmp)
                     );
    result = upper;
    result = result<<32;
    result = result|lower;
    
    return (double)(75*result*PPC_TB);
}
#undef PPC_TB
#endif


