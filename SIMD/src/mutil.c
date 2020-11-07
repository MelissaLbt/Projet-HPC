
/* --------------- */
/* --- mutil.c --- */
/* --------------- */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "nrdef.h"
#include "nrutil.h"

#include "vnrdef.h"
#include "vnrutil.h"

#include "mutil.h"

double chrono(void)
{
    //return dtime();
    return 0.0;
}

/* ---------------- */
/* --- routines --- */
/* ---------------- */
/* ------------- */
uint8 ui8rand(void)
/* ------------- */
{
    static uint32 x=0;
    x = (11 * x + 13) % 17;
    return (uint8) x;
}
/* --------------- */
uint32 ui32rand(void)
/* --------------- */
{
    static uint32 x=0;
    x = (11 * x + 13) % 17;
    return (uint32) x;
}
/* -------------- */
uint32 f32rand(void)
/* -------------- */
{
    static float32 x=0;
    x = (float32) fmod(11 * x + 13, 17);
    return (float32) x ;
}
/* --------------------------------------- */
void rand_ui8vector(uint8 *X, int i0, int i1)
/* --------------------------------------- */
{
    int i;
    
    for(i=i0; i<=i1; i++) {
        X[i] = ui8rand();
    }
}
/* ----------------------------------------- */
void rand_ui32vector(uint32 *X, int i0, int i1)
/* ----------------------------------------- */
{
    int i;
    
    for(i=i0; i<=i1; i++) {
        X[i] = ui32rand();
    }
}
/* ----------------------------------------- */
void rand_f32vector(float32 *X, int i0, int i1)
/* ----------------------------------------- */
{
    int i;
    
    for(i=i0; i<=i1; i++) {
        X[i] = f32rand();
    }
}
/* --------------- */
int getIter(int size)
/* --------------- */
{
    if(size <   32) return 1024;
    if(size <   64) return 64 ;
    if(size <  128) return 8;
    if(size <  256) return 2;
    if(size <  512) return 2;
    if(size < 1024) return 2;
    if(size < 2048) return 1;
    return 2;
}
/* ----------------- */
int getIterAV(int size)
/* ----------------- */
{
    return 3*getIter(size);
}
/* --------------------------------- */
float32 gauss(float32 sigma, float32 x)
/* --------------------------------- */
{
    float32 pi = 3.1415927;
    float32 y;
    y = 1.0f / (sqrt(2*pi)*sigma) * exp(-(x*x)/(2*sigma*sigma));
    return y;
}
