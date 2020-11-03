/* ---------------- */
/* --- simd1D.c --- */
/* ---------------- */

#include <stdio.h>
#include <stdlib.h>

#include "nrdef.h"
#include "nrutil.h"

#include "vnrdef.h"
#include "vnrutil.h"

#include "mutil.h"

#include "mymacro.h"
#include "simd_macro.h"

// -------------------------------------------------------------------
void add_vf32vector(vfloat32 *vX1, vfloat32 *vX2, int n, vfloat32 *vY)
// -------------------------------------------------------------------
{
    int i;
    vfloat32 x1, x2, y;
    
    for(i=0; i<n; i++) {
        x1 = _mm_load_ps((float32*) &vX1[i]);
        x2 = _mm_load_ps((float32*) &vX2[i]);
        
        y = _mm_add_ps(x1, x2);
        
        DEBUG(display_vfloat32(x1, "%4.0f", "x1 =")); DEBUG(puts(""));
        DEBUG(display_vfloat32(x2, "%4.0f", "x2 =")); DEBUG(puts(""));
        DEBUG(display_vfloat32(y,  "%4.0f", "y  =")); DEBUG(puts(""));

        _mm_store_ps((float*) &vY[i], y);
    }
}
// ---------------------------------------------------------
vfloat32 dot_vf32vector(vfloat32 *vX1, vfloat32 *vX2, int n)
// ---------------------------------------------------------
{
    int i;
    vfloat32 x1, x2, p, s, r1;
    s = _mm_setzero_ps();

    // CODE A COMPLETER EN SSE1
    for(i=0; i<n; i++){
        x1 = _mm_load_ps((float32*) &vX1[i]);
        x2 = _mm_load_ps((float32*) &vX2[i]);
        p = _mm_mul_ps(x1, x2);
        s = _mm_add_ps(s, p); //0| a b c d |127

        DEBUG(display_vfloat32(x1, "%4.0f", "x1 =")); DEBUG(puts(""));
        DEBUG(display_vfloat32(x2, "%4.0f", "x2 =")); DEBUG(puts(""));
        DEBUG(display_vfloat32(p,  "%4.0f", "p  =")); DEBUG(puts(""));
        DEBUG(display_vfloat32(s,  "%4.0f", "s  =")); DEBUG(puts(""));

    }  
    r1 = _mm_shuffle_ps(s,s,_MM_SHUFFLE(2,3,0,1)); //0| b a d c |127
    s =  _mm_add_ps(s, r1); //ab ab cd cd
    DEBUG(display_vfloat32(r1, "%4.0f", "r1 =")); DEBUG(puts(""));
    DEBUG(display_vfloat32(s, "%4.0f", "s =")); DEBUG(puts(""));
    r1 = _mm_shuffle_ps(s,s,_MM_SHUFFLE(1,0,3,2));// cd cd ab ab
    s =  _mm_add_ps(s, r1);// abcd abcd abcd abcd
    DEBUG(display_vfloat32(r1, "%4.0f", "r1 =")); DEBUG(puts(""));
    DEBUG(display_vfloat32(s,  "%4.0f", "s  =")); DEBUG(puts(""));

    return s; // attention il faut retourner un registre SIMD et non un scalaire
    
}
// ----------------------------------------------------
void avg3_vf32vector(vfloat32 *vX, int n, vfloat32 *vY)
// ----------------------------------------------------
{   //n=3
    int i;
    vfloat32 x0, x1, x2; // registres alignes
    vfloat32 xx0, xx2; // registres non alignes
    vfloat32 y;
    vfloat32 cst = _mm_set_ps1(3);
    // CODE A COMPLETER EN SSE1
    for(i=0; i<n; i++){
        x1 = _mm_load_ps((float32*) &vX[i]);
        if(i==0)
            x0 = _mm_shuffle_ps(x1, x1, _MM_SHUFFLE(0,0,0,0));
        else
            x0 = _mm_load_ps((float32*) &vX[i-1]);
        
        if(i==(n-1))
            x2 = _mm_shuffle_ps(x1, x1, _MM_SHUFFLE(3,3,3,3));
        else
            x2 = _mm_load_ps((float32*) &vX[i+1]);

        xx0 = vec_left1(x0, x1);    
        xx2 = vec_right1(x1, x2);

        y   = vAVERAGE3(xx0,x1,xx2);
        DEBUG(display_vfloat32(y,  "%4.0f", "y  =")); DEBUG(puts(""));

        _mm_store_ps((float*) &vY[i], y);
    }
    
}
// ----------------------------------------------------
void avg5_vf32vector(vfloat32 *vX, int n, vfloat32 *vY)
// ----------------------------------------------------
{
    int i;
    vfloat32 x1, x2, x3; // registres alignes
    vfloat32 xx0, xx1, xx3, xx4; // registres non alignes
    vfloat32 y;
    vfloat32 cst = _mm_set_ps1(5);
    // CODE A COMPLETER EN SSE1
    for(i=0; i<n; i++){
        x2 = _mm_load_ps((float32*) &vX[i]);
        if(i==0)
            x1 = _mm_shuffle_ps(x2, x2, _MM_SHUFFLE(0,0,0,0));
        else
            x1 = _mm_load_ps((float32*) &vX[i-1]);
        
        if(i==(n-1))
            x3 = _mm_shuffle_ps(x2, x2, _MM_SHUFFLE(3,3,3,3));
        else
            x3 = _mm_load_ps((float32*) &vX[i+1]);

        xx0 = vec_left2(x1, x2);  
        xx1 = vec_left1(x1, x2);   
        //xx2 = x2;  
        xx3 = vec_right1(x2, x3);
        xx4 = vec_right2(x2, x3);
        y   = vAVERAGE5(xx0,xx1,x2,xx3,xx4);

        //DEBUG(display_vfloat32(y,  "%4.0f", "y  =")); DEBUG(puts(""));

        _mm_store_ps((float*) &vY[i], y);
    }
}
// --------------------------------------------------------
void avg3_rot_vf32vector(vfloat32 *vX, int n, vfloat32 *vY)
// --------------------------------------------------------
{
    int i;
    vfloat32 x0, x1, x2; // registres alignes
    vfloat32 xx0, xx2; // registres non alignes
    vfloat32 y;
    // CODE A COMPLETER EN SSE1
    x1 = _mm_load_ps((float32*) &vX[0]);
    x0 = _mm_shuffle_ps(x1, x1, _MM_SHUFFLE(0,0,0,0));
    for(i=0; i<n; i++){
        if(i==(n-1))
            x2 = _mm_shuffle_ps(x1, x1, _MM_SHUFFLE(3,3,3,3));
        else
            x2 = _mm_load_ps((float32*) &vX[i+1]);

        xx0 = vec_left1(x0, x1); 
        //xx1 = x1      
        xx2 = vec_right1(x1, x2);
        y =  vAVERAGE3(xx0,x1,xx2);

        DEBUG(display_vfloat32(xx0, "%4.0f", "xx0=")); DEBUG(puts(""));
        DEBUG(display_vfloat32(x1, "%4.0f", "x1 =")); DEBUG(puts(""));
        DEBUG(display_vfloat32(xx2,  "%4.0f", "xx2=")); DEBUG(puts(""));
        DEBUG(display_vfloat32(y,  "%4.0f", "y  =")); DEBUG(puts(""));
        
        _mm_store_ps((float*) &vY[i], y);
        x0 = x1;  //RR
        x1 = x2;  

    }
}

// --------------------------------------------------------
void avg5_rot_vf32vector(vfloat32 *vX, int n, vfloat32 *vY)
// --------------------------------------------------------
{
    int i;
    vfloat32 x1, x2, x3; // registres alignes
    vfloat32 xx0, xx1, xx3, xx4; // registres non alignes
    vfloat32 y;
    vfloat32 cst = _mm_set_ps1(5);
    // CODE A COMPLETER EN SSE1 
    x2 = _mm_load_ps((float32*) &vX[0]);
    x1 = _mm_shuffle_ps(x2, x2, _MM_SHUFFLE(0,0,0,0));
    for(i=0; i<n; i++){
        if(i==(n-1))
            x3 = _mm_shuffle_ps(x2, x2, _MM_SHUFFLE(3,3,3,3));
        else
            x3 = _mm_load_ps((float32*) &vX[i+1]);

        xx0 = vec_left2(x1, x2);  
        xx1 = vec_left1(x1, x2);   
        //xx2 = x2;  
        xx3 = vec_right1(x2, x3);
        xx4 = vec_right2(x2, x3); //possible de faire RR ,rendement?
        y   = vAVERAGE5(xx0,xx1,x2,xx3,xx4);

        //DEBUG(display_vfloat32(y,  "%4.0f", "y  =")); DEBUG(puts(""));
        _mm_store_ps((float*) &vY[i], y);
        x1 = x2;
        x2 = x3;
    }
}
/* ========================== */
/* === Fonctions de tests === */
/* ========================== */


// ---------------
void test1D(int n)
// ---------------
{
    int b = 2; // border
    int card; // cardinal of vector type

    int si0, si1; // scalar indices
    int vi0, vi1; // vector indices
    int mi0, mi1; // memory (bounded) indices

    int si0b, si1b; // scalar indices with border
    int vi0b, vi1b; // vector indices with border
    int mi0b, mi1b; // memory (bounded) indices  with border

    
    vfloat32 *vX1, *vX2, *vY, *vY3, *vY5;
    vfloat32 d;

    char* format = "%6.2f ";
    
    // chronometrie
    int iter, niter = 4;
    int run, nrun = 5;
    double t0, t1, dt, tmin, t;
    double cycles;
    
    puts("===============");
    puts("=== test 1D ===");
    puts("===============");

    // ------------------------- //
    // -- calculs des indices -- //
    // ------------------------- //

    printf("n = %d\n", n);
    
    card = card_vfloat32();

    si0 = 0;
    si1 = n-1;
    
    s2v1D(si0, si1, card, &vi0, &vi1);
    v2m1D(vi0, vi1, card, &mi0, &mi1);
    
    si0b = si0-b;
    si1b = si1+b;

    s2v1D(si0b, si1b, card, &vi0b, &vi1b);
    v2m1D(vi0b, vi1b, card, &mi0b, &mi1b);

    // ------------------------------------------- //
    // -- allocation des tableaux 1D vectoriels -- //
    // ------------------------------------------- //

    vX1 = vf32vector(vi0b, vi1b);
    vX2 = vf32vector(vi0b, vi1b);
    
    vY  = vf32vector(vi0, vi1);
    vY3 = vf32vector(vi0, vi1);
    vY5 = vf32vector(vi0, vi1);

    // ---------- //
    // -- init -- //
    // ---------- //

    zero_vf32vector(vX1, vi0b, vi1b);
    zero_vf32vector(vX2, vi0b, vi1b);
    zero_vf32vector(vY,  vi0, vi1);
    zero_vf32vector(vY3, vi0, vi1);
    zero_vf32vector(vY5, vi0, vi1);

    init_vf32vector_param(vX1, vi0, vi1, 1, 1);
    init_vf32vector_param(vX2, vi0, vi1, 1, 2);
    
    // --------------- //
    // -- affichage -- //
    // --------------- //

    // affichage classique sur une ligne: appel de la fonction scalaire
    DEBUG(display_f32vector((float32*) vX1, si0, si1, "%4.0f", "sX1"));

    // affichage par bloc SIMD: appel de la fonction SIMD
    DEBUG(display_vf32vector(vX1, vi0, vi1, "%4.0f", "vX1"));
    DEBUG(puts(""));

    // affichage classique sur une ligne: appel de la fonction scalaire
    DEBUG(display_f32vector((float32*) vX2, si0, si1, "%4.0f", "sX2"));

    // affichage par bloc SIMD: appel de la fonction SIMD
    DEBUG(display_vf32vector(vX2, vi0, vi1, "%4.0f", "vX2"));
    DEBUG(puts(""));

    // ------------ //
    // -- calcul -- //
    // ------------ //
    
    puts("----------------");
    puts("--- addition ---");
    puts("----------------");
    
    CHRONO(add_vf32vector(vX1, vX2, n/card, vY),cycles); printf("add: "); DEBUG(display_vf32vector(vY, vi0, vi1, format, "Y")); BENCH(printf(format, cycles/n)); BENCH(puts(""));
    
    // affichage classique sur une ligne: appel de la fonction scalaire
    DEBUG(display_f32vector((float32*) vY, si0, si1, "%4.0f", "sY"));
    DEBUG(puts(""));
    
    puts("-------------------");
    puts("--- dot product ---");
    puts("-------------------");

    CHRONO(d = dot_vf32vector(vX1, vX2, n/card),cycles); printf("dot product: "); DEBUG(display_vfloat32(d, "%6.0f ", "d")); BENCH(printf(format, cycles/n)); BENCH(puts(""));
    display_vfloat32(d, "%6.0f ", "d"); puts(""); // laisser sinon dead-code-elimination enleve tout le calcul ...
    
    puts("-----------");
    puts("--- avg ---");
    puts("-----------");
    
    CHRONO(avg3_vf32vector(vX1, n/card, vY3),cycles); printf("avg 3   "); DEBUG(display_vf32vector(vY3, vi0, vi1, format, "Y3")); BENCH(printf(format, cycles/n)); BENCH(puts(""));
    CHRONO(avg5_vf32vector(vX1, n/card, vY5),cycles); printf("avg 5   "); DEBUG(display_vf32vector(vY5, vi0, vi1, format, "Y5")); BENCH(printf(format, cycles/n)); BENCH(puts(""));
    BENCH(puts(""));
    
    CHRONO(avg3_rot_vf32vector(vX1, n/card, vY3),cycles); printf("avg 3 rot"); DEBUG(display_vf32vector(vY3, vi0, vi1, format, "Y3")); BENCH(printf(format, cycles/n)); BENCH(puts(""));
    CHRONO(avg5_rot_vf32vector(vX1, n/card, vY5),cycles); printf("avg 5 rot"); DEBUG(display_vf32vector(vY5, vi0, vi1, format, "Y5")); BENCH(printf(format, cycles/n)); BENCH(puts(""));
    BENCH(puts(""));
    

    // ---------- //
    // -- free -- //
    // ---------- //

    free_vf32vector(vX1, vi0b, vi1b);
    free_vf32vector(vX2, vi0b, vi1b);
    
    free_vf32vector(vY,  vi0, vi1);
    free_vf32vector(vY3, vi0, vi1);
    free_vf32vector(vY5, vi0, vi1);

    
}
// ================================
void main_1D(int argc, char *argv[])
// ================================
{
    DEBUG(test1D(12));
    
    BENCH(test1D(100 * 100));
    BENCH(test1D(1000 * 1000));


}
