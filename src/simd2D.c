/* ---------------- */
/* --- simd2D.c --- */
/* ---------------- */

#include <math.h>

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include "nrdef.h"
#include "nrutil.h"

#include "vnrdef.h"
#include "vnrutil.h"

#include "mutil.h"

#include "mymacro.h"
#include "simd_macro.h"


// Opérateur de moyennage sur M3
// --------------------------------------------------------
void avg3_reg_vf32matrix(vfloat32** X, int n, vfloat32 **Y)
// --------------------------------------------------------
{
    int i, j;
    vfloat32 a0, b0, c0;
    vfloat32 a1, b1, c1;
    vfloat32 a2, b2, c2;

    vfloat32 aa0, cc0;
    vfloat32 aa1, cc1;
    vfloat32 aa2, cc2;
    vfloat32 y;
    // CODE A COMPLETER
    //pas besoin de gestion du bord
    for(i=0; i<(n*card_vfloat32()); i++){
        for(j=0; j<n; j++){
            a0 = _mm_load_ps((float32*) &X[i-1][j-1]);
            a1 = _mm_load_ps((float32*) &X[i  ][j-1]);
            a2 = _mm_load_ps((float32*) &X[i+1][j-1]);
            b0 = _mm_load_ps((float32*) &X[i-1][j  ]);
            b1 = _mm_load_ps((float32*) &X[i  ][j  ]);
            b2 = _mm_load_ps((float32*) &X[i+1][j  ]);
            c0 = _mm_load_ps((float32*) &X[i-1][j+1]);
            c1 = _mm_load_ps((float32*) &X[i  ][j+1]);
            c2 = _mm_load_ps((float32*) &X[i+1][j+1]);

            aa0 = vec_left1(a0, b0);
            cc0 = vec_right1(b0, c0);
            b0  = vAVERAGE3(aa0,b0,cc0);

            aa1 = vec_left1(a1, b1);
            cc1 = vec_right1(b1, c1);
            b1  = vAVERAGE3(aa1,b1,cc1);

            aa2 = vec_left1(a2, b2);
            cc2 = vec_right1(b2, c2);
            b2  = vAVERAGE3(aa2,b2,cc2);

            y   = vAVERAGE3(b0,b1,b2);
            /*
            DEBUG(display_vfloat32(b0, "%4.0f", "b0 =")); DEBUG(puts(""));
            DEBUG(display_vfloat32(b1, "%4.0f", "b1 =")); DEBUG(puts(""));
            DEBUG(display_vfloat32(b2, "%4.0f", "b2 =")); DEBUG(puts(""));
            DEBUG(display_vfloat32(y, "%4.0f", "y =")); DEBUG(puts(""));
           */
            _mm_store_ps((float*) &Y[i][j], y);
        }
    }
}


// --------------------------------------------------------
void avg3_rot_vf32matrix(vfloat32** X, int n, vfloat32 **Y)
// --------------------------------------------------------
{
    int i, j;
    vfloat32 a0, b0, c0;
    vfloat32 a1, b1, c1;
    vfloat32 a2, b2, c2;

    vfloat32 aa0, cc0;
    vfloat32 aa1, cc1;
    vfloat32 aa2, cc2;
    vfloat32 y;
    // CODE A COMPLETER
    for(i=0; i<(n*card_vfloat32()); i++){
        //attention!! Il faut mettre les initialisation dans la boucle externe(au debut de chaque ligne)
        j = 0;
        a0 = _mm_load_ps((float32*) &X[i-1][j-1]);
        a1 = _mm_load_ps((float32*) &X[i  ][j-1]);
        a2 = _mm_load_ps((float32*) &X[i+1][j-1]);
        b0 = _mm_load_ps((float32*) &X[i-1][j]);
        b1 = _mm_load_ps((float32*) &X[i  ][j]);
        b2 = _mm_load_ps((float32*) &X[i+1][j]);
        for(j=0; j<n; j++){
            c0 = _mm_load_ps((float32*) &X[i-1][j+1]);
            c1 = _mm_load_ps((float32*) &X[i  ][j+1]);
            c2 = _mm_load_ps((float32*) &X[i+1][j+1]);

            aa0 = vec_left1(a0, b0);
            cc0 = vec_right1(b0, c0);
            b0  = vAVERAGE3(aa0,b0,cc0);

            aa1 = vec_left1(a1, b1);
            cc1 = vec_right1(b1, c1);
            b1  = vAVERAGE3(aa1,b1,cc1);

            aa2 = vec_left1(a2, b2);
            cc2 = vec_right1(b2, c2);
            b2  = vAVERAGE3(aa2,b2,cc2);

            y   = vAVERAGE3(b0,b1,b2);

            DEBUG(display_vfloat32(y, "%4.0f", "y =")); DEBUG(puts(""));

            _mm_store_ps((float*) &Y[i][j], y);
            a0 = b0; b0 = c0;
            a1 = b1; b1 = c1;
            a2 = b2; b2 = c2;
        }
    }
}


// --------------------------------------------------------
void avg3_red_vf32matrix(vfloat32** X, int n, vfloat32 **Y)
// --------------------------------------------------------
{//reduction par colonne et deroulage
    int i, j;
    int r = n%3;
    vfloat32 a0, b0, c0;
    vfloat32 a1, b1, c1;
    vfloat32 a2, b2, c2;

    vfloat32 ra, rb, rc;
    vfloat32 opl, opr;
    vfloat32 y0, y1, y2, y;

    // CODE A COMPLETER
    for(i=0; i<(n*card_vfloat32()); i++){
        //attention!! Il faut mettre les initialisation dans la boucle externe(au debut de chaque ligne)
        j = 0;
        a0 = _mm_load_ps((float32*) &X[i-1][j-1]);
        a1 = _mm_load_ps((float32*) &X[i  ][j-1]);
        a2 = _mm_load_ps((float32*) &X[i+1][j-1]);
        b0 = _mm_load_ps((float32*) &X[i-1][j]);
        b1 = _mm_load_ps((float32*) &X[i  ][j]);
        b2 = _mm_load_ps((float32*) &X[i+1][j]);
        ra = vAVERAGE3(a0, a1, a2);
        rb = vAVERAGE3(b0, b1, b2);//reduction par colonne

        for(j=0; j<(n-r); j+=3){
            // centre: rb
            c0 = _mm_load_ps((float32*) &X[i-1][j+1]);
            c1 = _mm_load_ps((float32*) &X[i  ][j+1]);
            c2 = _mm_load_ps((float32*) &X[i+1][j+1]);
            rc = vAVERAGE3(c0, c1, c2);

            opl = vec_left1(ra, rb); opr = vec_right1(rb, rc);
            y0 = vAVERAGE3(opl, rb, opr);
            DEBUG(display_vfloat32(y0, "%4.0f", "y0 =")); DEBUG(puts(""));
            _mm_store_ps((float*) &Y[i][j], y0);

            // centre: rc
            a0 = _mm_load_ps((float32*) &X[i-1][j+2]);
            a1 = _mm_load_ps((float32*) &X[i  ][j+2]);
            a2 = _mm_load_ps((float32*) &X[i+1][j+2]);
            ra = vAVERAGE3(a0, a1, a2);

            opl = vec_left1(rb, rc); opr = vec_right1(rc, ra);
            y1 = vAVERAGE3(opl, rc, opl);
            DEBUG(display_vfloat32(y1, "%4.0f", "y1 =")); DEBUG(puts(""));
            _mm_store_ps((float*) &Y[i][j+1], y1);

            // centre: ra
            b0 = _mm_load_ps((float32*) &X[i-1][j+3]);
            b1 = _mm_load_ps((float32*) &X[i  ][j+3]);
            b2 = _mm_load_ps((float32*) &X[i+1][j+3]);
            rb = vAVERAGE3(b0, b1, b2);

            opl = vec_left1(rc, ra); opr = vec_right1(ra, rb);
            y2 = vAVERAGE3(opl, ra, opl);
            DEBUG(display_vfloat32(y2, "%4.0f", "y2 =")); DEBUG(puts(""));
            _mm_store_ps((float*) &Y[i][j+2], y2);
        }
        //epilogue 需要么？或者不需要边界
        switch(r){
            case 2:
                a0 = _mm_load_ps((float32*) &X[i-1][n-3]);
                a1 = _mm_load_ps((float32*) &X[i  ][n-3]);
                a2 = _mm_load_ps((float32*) &X[i+1][n-3]);
                b0 = _mm_load_ps((float32*) &X[i-1][n-2]);
                b1 = _mm_load_ps((float32*) &X[i  ][n-2]);
                b2 = _mm_load_ps((float32*) &X[i+1][n-2]);
                c0 = _mm_load_ps((float32*) &X[i-1][n-1]);
                c1 = _mm_load_ps((float32*) &X[i  ][n-1]);
                c2 = _mm_load_ps((float32*) &X[i+1][n-1]);
                ra = vAVERAGE3(a0, a1, a2);
                rb = vAVERAGE3(b0, b1, b2);
                rc = vAVERAGE3(c0, c1, c2);
                opl = vec_left1(ra, rb); opr = vec_right1(rb, rc);
                y = vAVERAGE3(opl, rb, opr);
                DEBUG(display_vfloat32(y, "%4.0f", "y =")); DEBUG(puts(""));
                _mm_store_ps((float*) &Y[i][n-2], y);
            case 1:
                a0 = _mm_load_ps((float32*) &X[i-1][n-2]);
                a1 = _mm_load_ps((float32*) &X[i  ][n-2]);
                a2 = _mm_load_ps((float32*) &X[i+1][n-2]);
                b0 = _mm_load_ps((float32*) &X[i-1][n-1]);
                b1 = _mm_load_ps((float32*) &X[i  ][n-1]);
                b2 = _mm_load_ps((float32*) &X[i+1][n-1]);
                c0 = _mm_load_ps((float32*) &X[i-1][n  ]);
                c1 = _mm_load_ps((float32*) &X[i  ][n  ]);
                c2 = _mm_load_ps((float32*) &X[i+1][n  ]);
                ra = vAVERAGE3(a0, a1, a2);
                rb = vAVERAGE3(b0, b1, b2);
                rc = vAVERAGE3(c0, c1, c2);
                opl = vec_left1(ra, rb); opr = vec_right1(rb, rc);
                y = vAVERAGE3(opl, rb, opr);
                DEBUG(display_vfloat32(y, "%4.0f", "y =")); DEBUG(puts(""));
                _mm_store_ps((float*) &Y[i][n-1], y);
                break;
        }
    }
}


// Opérateur de moyennage sur M5
// --------------------------------------------------------
void avg5_reg_vf32matrix(vfloat32** X, int n, vfloat32 **Y)
// --------------------------------------------------------
{
    int i, j;
    vfloat32 a0, b0, c0;
    vfloat32 a1, b1, c1;
    vfloat32 a2, b2, c2;
    vfloat32 a3, b3, c3;
    vfloat32 a4, b4, c4;
    vfloat32 ra, rb, rc;
    vfloat32 xx0, xx1, xx3, xx4;
    vfloat32 y;

    // CODE A COMPLETER
    for(i=0; i<(n*card_vfloat32()); i++){
        for(j=0; j<n; j++){
            a0 = _mm_load_ps((float32*) &X[i-2][j-1]);
            a1 = _mm_load_ps((float32*) &X[i-1][j-1]);
            a2 = _mm_load_ps((float32*) &X[i  ][j-1]);
            a3 = _mm_load_ps((float32*) &X[i+1][j-1]);
            a4 = _mm_load_ps((float32*) &X[i+2][j-1]);

            b0 = _mm_load_ps((float32*) &X[i-2][j]);
            b1 = _mm_load_ps((float32*) &X[i-1][j]);
            b2 = _mm_load_ps((float32*) &X[i  ][j]);
            b3 = _mm_load_ps((float32*) &X[i+1][j]);
            b4 = _mm_load_ps((float32*) &X[i+2][j]);

            c0 = _mm_load_ps((float32*) &X[i-2][j+1]);
            c1 = _mm_load_ps((float32*) &X[i-1][j+1]);
            c2 = _mm_load_ps((float32*) &X[i  ][j+1]);
            c3 = _mm_load_ps((float32*) &X[i+1][j+1]);
            c4 = _mm_load_ps((float32*) &X[i+2][j+1]);


            ra  = vAVERAGE5(a0, a1, a2, a3, a4);
            rb  = vAVERAGE5(b0, b1, b2, b3, b4);
            rc  = vAVERAGE5(c0, c1, c2, c3, c4);

            xx0 = vec_left2(ra, rb);
            xx1 = vec_left1(ra, rb);
            xx3 = vec_right1(rb, rc);
            xx4 = vec_right2(rb, rc);
            y   = vAVERAGE5(xx0,xx1,rb,xx3,xx4);

            DEBUG(display_vfloat32(y, "%4.0f", "y =")); DEBUG(puts(""));
            _mm_store_ps((float*) &Y[i][j], y);
        }
    }
}
// --------------------------------------------------------
void avg5_rot_vf32matrix(vfloat32** X, int n, vfloat32 **Y)
// --------------------------------------------------------
{
    int i, j;
    vfloat32 a0, b0, c0;
    vfloat32 a1, b1, c1;
    vfloat32 a2, b2, c2;
    vfloat32 a3, b3, c3;
    vfloat32 a4, b4, c4;
    vfloat32 ra, rb, rc;
    vfloat32 xx0, xx1, xx3, xx4;
    vfloat32 y;

    // CODE A COMPLETER
    for(i=0; i<(n*card_vfloat32()); i++){
        j = 0;
        a0 = _mm_load_ps((float32*) &X[i-2][j-1]);
        a1 = _mm_load_ps((float32*) &X[i-1][j-1]);
        a2 = _mm_load_ps((float32*) &X[i  ][j-1]);
        a3 = _mm_load_ps((float32*) &X[i+1][j-1]);
        a4 = _mm_load_ps((float32*) &X[i+2][j-1]);

        b0 = _mm_load_ps((float32*) &X[i-2][j]);
        b1 = _mm_load_ps((float32*) &X[i-1][j]);
        b2 = _mm_load_ps((float32*) &X[i  ][j]);
        b3 = _mm_load_ps((float32*) &X[i+1][j]);
        b4 = _mm_load_ps((float32*) &X[i+2][j]);

        for(j=0; j<n; j++){

            c0 = _mm_load_ps((float32*) &X[i-2][j+1]);
            c1 = _mm_load_ps((float32*) &X[i-1][j+1]);
            c2 = _mm_load_ps((float32*) &X[i  ][j+1]);
            c3 = _mm_load_ps((float32*) &X[i+1][j+1]);
            c4 = _mm_load_ps((float32*) &X[i+2][j+1]);


            ra  = vAVERAGE5(a0, a1, a2, a3, a4);
            rb  = vAVERAGE5(b0, b1, b2, b3, b4);
            rc  = vAVERAGE5(c0, c1, c2, c3, c4);

            xx0 = vec_left2(ra, rb);
            xx1 = vec_left1(ra, rb);
            xx3 = vec_right1(rb, rc);
            xx4 = vec_right2(rb, rc);
            y   = vAVERAGE5(xx0,xx1,rb,xx3,xx4);

            DEBUG(display_vfloat32(y, "%4.0f", "y =")); DEBUG(puts(""));
            _mm_store_ps((float*) &Y[i][j], y);
            //RR
            a0 = b0; b0 = c0;
            a1 = b1; b1 = c1;
            a2 = b2; b2 = c2;
            a3 = b3; b3 = c3;
            a4 = b4; b4 = c4;
        }
    }
}
// --------------------------------------------------------
void avg5_red_vf32matrix(vfloat32** X, int n, vfloat32 **Y)
// --------------------------------------------------------
{
    int i, j;
    vfloat32 a0, b0, c0;
    vfloat32 a1, b1, c1;
    vfloat32 a2, b2, c2;
    vfloat32 a3, b3, c3;
    vfloat32 a4, b4, c4;
    vfloat32 ra, rb, rc;
    vfloat32 xx0, xx1, xx3, xx4;
    vfloat32 y0, y1, y2;

    // CODE A COMPLETER
    for(i=0; i<(n*card_vfloat32()); i++){
        j = 0;
        a0 = _mm_load_ps((float32*) &X[i-2][j-1]);
        a1 = _mm_load_ps((float32*) &X[i-1][j-1]);
        a2 = _mm_load_ps((float32*) &X[i  ][j-1]);
        a3 = _mm_load_ps((float32*) &X[i+1][j-1]);
        a4 = _mm_load_ps((float32*) &X[i+2][j-1]);
        ra = vAVERAGE5(a0, a1, a2, a3, a4); //reduction  par colonne
        b0 = _mm_load_ps((float32*) &X[i-2][j]);
        b1 = _mm_load_ps((float32*) &X[i-1][j]);
        b2 = _mm_load_ps((float32*) &X[i  ][j]);
        b3 = _mm_load_ps((float32*) &X[i+1][j]);
        b4 = _mm_load_ps((float32*) &X[i+2][j]);
        rb = vAVERAGE5(b0, b1, b2, b3, b4);

        for(j=0; j<n; j+=3){
            //centre rb
            c0 = _mm_load_ps((float32*) &X[i-2][j+1]);
            c1 = _mm_load_ps((float32*) &X[i-1][j+1]);
            c2 = _mm_load_ps((float32*) &X[i  ][j+1]);
            c3 = _mm_load_ps((float32*) &X[i+1][j+1]);
            c4 = _mm_load_ps((float32*) &X[i+2][j+1]);
            //ra  = vAVERAGE5(a0, a1, a2, a3, a4);
            //rb  = vAVERAGE5(b0, b1, b2, b3, b4);
            rc  = vAVERAGE5(c0, c1, c2, c3, c4);

            xx0 = vec_left2(ra, rb);
            xx1 = vec_left1(ra, rb);
            xx3 = vec_right1(rb, rc);
            xx4 = vec_right2(rb, rc);
            y0   = vAVERAGE5(xx0,xx1,rb,xx3,xx4);

            DEBUG(display_vfloat32(y0, "%4.0f", "y0 =")); DEBUG(puts(""));
            _mm_store_ps((float*) &Y[i][j], y0);
            //centre rc
            a0 = _mm_load_ps((float32*) &X[i-2][j+2]);
            a1 = _mm_load_ps((float32*) &X[i-1][j+2]);
            a2 = _mm_load_ps((float32*) &X[i  ][j+2]);
            a3 = _mm_load_ps((float32*) &X[i+1][j+2]);
            a4 = _mm_load_ps((float32*) &X[i+2][j+2]);

            ra  = vAVERAGE5(a0, a1, a2, a3, a4);

            xx0 = vec_left2(rb, rc);
            xx1 = vec_left1(rb, rc);
            xx3 = vec_right1(rc, ra);
            xx4 = vec_right2(rc, ra);
            y1   = vAVERAGE5(xx0,xx1,rc,xx3,xx4);

            DEBUG(display_vfloat32(y1, "%4.0f", "y1 =")); DEBUG(puts(""));
            _mm_store_ps((float*) &Y[i][j+1], y1);
            //centre ra
			b0 = _mm_load_ps((float32*) &X[i-2][j+3]);
            b1 = _mm_load_ps((float32*) &X[i-1][j+3]);
            b2 = _mm_load_ps((float32*) &X[i  ][j+3]);
            b3 = _mm_load_ps((float32*) &X[i+1][j+3]);
            b4 = _mm_load_ps((float32*) &X[i+2][j+3]);

            rb  = vAVERAGE5(b0, b1, b2, b3, b4);

            xx0 = vec_left2(rc, ra);
            xx1 = vec_left1(rc, ra);
            xx3 = vec_right1(ra, rb);
            xx4 = vec_right2(ra, rb);
            y2   = vAVERAGE5(xx0,xx1,ra,xx3,xx4);

            DEBUG(display_vfloat32(y2, "%4.0f", "y2 =")); DEBUG(puts(""));
            _mm_store_ps((float*) &Y[i][j+2], y2);

        }
    }
}
/* ============ */
void test2D(int n)
/* ============ */
{
    int card;

    int b; // border
    char *format = "%6.2f ";

    int si0, si1, sj0, sj1; // scalar indices
    int vi0, vi1, vj0, vj1; // vector indices
    int mi0, mi1, mj0, mj1; // memory (bounded) indices

    int si0b, si1b, sj0b, sj1b; // scalar indices with border
    int vi0b, vi1b, vj0b, vj1b; // vector indices with border
    int mi0b, mi1b, mj0b, mj1b; // memory (bounded) indices  with border

    float32  **sX, **sY3, **sY5;
    vfloat32 **vX, **vY3, **vY5;

    // chronometrie
    int iter, niter = 4;
    int run, nrun = 5;
    double t0, t1, dt, tmin, t;
    double cycles;

    puts("===============");
    puts("=== test 2D ===");
    puts("===============");

    printf("n = %d\n\n", n);

    // ------------------------- //
    // -- calculs des indices -- //
    // ------------------------- //

    b = 2; // 1 for 3x3, 2 for 5x5
    card = card = card_vfloat32();

    si0 = 0; si1 = n-1;
    sj0 = 0; sj1 = n-1;

    si0b = si0-b; si1b = si1+b;
    sj0b = sj0-b; sj1b = sj1+b;

    s2v(si0, si1, sj0, sj1, card, &vi0, &vi1, &vj0, &vj1);
    v2m(vi0, vi1, vj0, vj1, card, &mi0, &mi1, &mj0, &mj1);

    s2v(si0b, si1b, sj0b, sj1b, card, &vi0b, &vi1b, &vj0b, &vj1b);
    v2m(vi0b, vi1b, vj0b, vj1b, card, &mi0b, &mi1b, &mj0b, &mj1b);

    // allocation
    vX  = vf32matrix(vi0b, vi1b, vj0b, vj1b);
    vY3 = vf32matrix(vi0,  vi1,  vj0,  vj1);
    vY5 = vf32matrix(vi0,  vi1,  vj0,  vj1);

    // wrappers scalaires
    sX  = (float32**) vX;
    sY3 = (float32**) vY3;
    sY5 = (float32**) vY5;

    // ---------- //
    // -- init -- //
    // ---------- //

    zero_vf32matrix(vX,  vi0b, vi1b, vj0b, vj1b);
    zero_vf32matrix(vY3, vi0, vi1, vj0, vj1);
    zero_vf32matrix(vY5, vi0, vi1, vj0, vj1);

    init_vf32matrix_param(vX, vi0b, vi1b, vj0b, vj1b, 1,1,8);

    // display init data
    DEBUG(display_f32matrix(sX,  0, n-1, 0, n-1, format, "sX"));
    DEBUG(display_f32matrix(sY3, 0, n-1, 0, n-1, format, "sY3"));

    DEBUG(display_vf32matrix(vX,  vi0b, vi1b, vj0b, vj1b, format, "vX"));
    DEBUG(display_vf32matrix(vY3, vi0,  vi1,  vj0,  vj1,  format, "vY3"));
    DEBUG(display_vf32matrix(vY3, vi0,  vi1,  vj0,  vj1,  format, "vY5"));

    // ------------ //
    // -- calcul -- //
    // ------------ //

    CHRONO(avg3_reg_vf32matrix(vX, n/card, vY3),cycles); printf("avg 3x3 reg  "); DEBUG(display_vf32matrix(vY3, vi0, vi1, vj0, vj1, format, "Y3")); BENCH(printf(format, cycles/(n*n))); BENCH(puts(""));
    CHRONO(avg3_rot_vf32matrix(vX, n/card, vY3),cycles); printf("avg 3x3 rot  "); DEBUG(display_vf32matrix(vY3, vi0, vi1, vj0, vj1, format, "Y3")); BENCH(printf(format, cycles/(n*n))); BENCH(puts(""));
    CHRONO(avg3_red_vf32matrix(vX, n/card, vY3),cycles); printf("avg 3x3 red  "); DEBUG(display_vf32matrix(vY3, vi0, vi1, vj0, vj1, format, "Y3")); BENCH(printf(format, cycles/(n*n))); BENCH(puts(""));
    BENCH(puts(""));

    CHRONO(avg5_reg_vf32matrix(vX, n/card, vY5),cycles); printf("avg 5x5 reg  "); DEBUG(display_vf32matrix(vY5, vi0, vi1, vj0, vj1, format, "Y5")); BENCH(printf(format, cycles/(n*n))); BENCH(puts(""));
    CHRONO(avg5_rot_vf32matrix(vX, n/card, vY5),cycles); printf("avg 5x5 rot  "); DEBUG(display_vf32matrix(vY5, vi0, vi1, vj0, vj1, format, "Y5")); BENCH(printf(format, cycles/(n*n))); BENCH(puts(""));
    CHRONO(avg5_red_vf32matrix(vX, n/card, vY5),cycles); printf("avg 5x5 red  "); DEBUG(display_vf32matrix(vY5, vi0, vi1, vj0, vj1, format, "Y5")); BENCH(printf(format, cycles/(n*n))); BENCH(puts(""));
    //CHRONO(avg5_vf32matrix(vX, n/card, vY5),cycles); printf("avg 5x5   "); DEBUG(display_vf32matrix(vY5, vi0, vi1, vj0, vj1, format, "Y5")); BENCH(printf(format, cycles/(n*n))); BENCH(puts(""));
    BENCH(puts(""));

    // ---------- //
    // -- free -- //
    // ---------- //

    free_vf32matrix(vX, vi0b, vi1b, vj0b, vj1b);
    free_vf32matrix(vY3, vi0,  vi1,  vj0,  vj1);
    free_vf32matrix(vY5, vi0,  vi1,  vj0,  vj1);
}
// =================================
void main_2D(int argc, char * argv[])
// =================================
{

    DEBUG(test2D(8));

    BENCH(test2D(100));
    BENCH(test2D(1000));
    BENCH(test2D(2000));
}
