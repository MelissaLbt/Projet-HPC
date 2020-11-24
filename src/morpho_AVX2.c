/* Algorithme Morphologie version AVX2 , AVX2 avec reduction... , avec fusion*/

#include <stdio.h>
#include <stdlib.h>

#include "nrdef.h"
#include "nrutil.h"

#include "vnrdef.h"
#include "vnrutil.h"

#include "mutil.h"

#include "morpho_AVX2.h"
#include "mymacro.h"

void init_bord_AVX2(vuint8 **vE,int vi0,int vi1,int vj0,int vj1,int vj0b,int vj1b){//E: deja init avec b=2(4)
  int cst;
  lvuint8 vcst;

  vcst = vec256_load2(vE,vi0,vj0); cst = vec256_extractl(vcst); vec256_store2(vE,vi0,vj0b,vec256_set(cst));
  vcst = vec256_load2(vE,vi0,vj1-1); cst = vec256_extractr(vcst); vec256_store2(vE,vi0,vj1b-1,vec256_set(cst));
  vcst = vec256_load2(vE,vi1,vj0); cst = vec256_extractl(vcst); vec256_store2(vE,vi1,vj0b,vec256_set(cst));
  vcst = vec256_load2(vE,vi1,vj1-1); cst = vec256_extractr(vcst); vec256_store2(vE,vi1,vj1b-1,vec256_set(cst));
  for(int j = vj0b; j <= vj1b-1; j+=2){
    vcst = vec256_load2(vE,vi0,j); vec256_store2(vE,vi0-1,j,vcst); vec256_store2(vE,vi0-2,j,vcst);
    vcst = vec256_load2(vE,vi1,j); vec256_store2(vE,vi1+1,j,vcst); vec256_store2(vE,vi1+2,j,vcst);
  }
  for(int i = vi0; i <= vi1; i++){
    vcst = vec256_load2(vE,i,vj0); cst = vec256_extractl(vcst); vec256_store2(vE,i,vj0b,vec256_set(cst));
    vcst = vec256_load2(vE,i,vj1-1); cst = vec256_extractr(vcst); vec256_store2(vE,i,vj1b-1,vec256_set(cst));
  }
  //   //display_vui8matrix(vE,vi0-2,vi0-2,vj0b,vj0b,"%4d","vE_AVX2");
}

//SIMD pour b = 1
void erosion_AVX2(vuint8 **vE, vuint8 **vOut, int vi0, int vi1, int vj0, int vj1){

  int i, j;
  lvuint8 a0, b0, c0;
  lvuint8 a1, b1, c1;
  lvuint8 a2, b2, c2;

  lvuint8 aa0, cc0;
  lvuint8 aa1, cc1;
  lvuint8 aa2, cc2;
  lvuint8 y;

  vuint8 x0, x1, x2;
  vuint8 z0, z1, z2;

  for(i = vi0; i <= vi1; i++){
        for(j = vj0; j <= vj1; j+=2){
            a0 = vec256_load2(vE,i-1, j-2);
            x0 = _mm256_extracti128_si256(a0,1);
            z0 = _mm256_extracti128_si256(a0,0);
            DEBUG(display_vuint8(x0, "%4d", "a0[255:128] =")); DEBUG(puts(""));
            DEBUG(display_vuint8(z0, "%4d", " a0[127:0] =")); DEBUG(puts(""));

            a1 = vec256_load2(vE,i  , j-2);
            x1 = _mm256_extracti128_si256(a1,1);
            z1 = _mm256_extracti128_si256(a1,0);
            DEBUG(display_vuint8(x1, "%4d", "a1[255:128] =")); DEBUG(puts(""));
            DEBUG(display_vuint8(z1, "%4d", " a1[127:0] =")); DEBUG(puts(""));

            a2 = vec256_load2(vE,i+1, j-2);
            x2 = _mm256_extracti128_si256(a2,1);
            z2 = _mm256_extracti128_si256(a2,0);
            DEBUG(display_vuint8(x2, "%4d", "a2[255:128] =")); DEBUG(puts(""));
            DEBUG(display_vuint8(z2, "%4d", " a2[127:0] =")); DEBUG(puts(""));

            b0 = vec256_load2(vE,i-1, j);
            b1 = vec256_load2(vE,i  , j);
            b2 = vec256_load2(vE,i+1, j);

            c0 = vec256_load2(vE,i-1, j+2);
            c1 = vec256_load2(vE,i  , j+2);
            c2 = vec256_load2(vE,i+1, j+2);

            aa0 = vec256_left1(a0,b0);
            cc0 = vec256_right1(b0,c0);

            a0 = vec256_and3(aa0,b0,cc0);

            aa1 = vec256_left1(a1,b1);
            cc1 = vec256_right1(b1,c1);

            a1 = vec256_and3(aa1,b1,cc1);

            aa2 = vec256_left1(a2,b2);
            cc2 = vec256_right1(b2,c2);

            a2 = vec256_and3(aa2,b2,cc2);

            y = vec256_and3(a0,a1,a2);

            vec256_store2(vOut, i, j, y);
    }
  }
}

void dilatation_AVX2(vuint8 **vE, vuint8 **vOut, int vi0, int vi1, int vj0, int vj1){
  int i, j;
  lvuint8 a0, b0, c0;
  lvuint8 a1, b1, c1;
  lvuint8 a2, b2, c2;

  lvuint8 aa0, cc0;
  lvuint8 aa1, cc1;
  lvuint8 aa2, cc2;
  lvuint8 y;

  for(i = vi0; i<= vi1; i++){
        for(j = vj0; j <= vj1; j+=2){
            a0 = vec256_load2(vE,i-1, j-2);
            a1 = vec256_load2(vE,i  , j-2);
            a2 = vec256_load2(vE,i+1, j-2);

            b0 = vec256_load2(vE,i-1, j);
            b1 = vec256_load2(vE,i  , j);
            b2 = vec256_load2(vE,i+1, j);

            c0 = vec256_load2(vE,i-1, j+2);
            c1 = vec256_load2(vE,i  , j+2);
            c2 = vec256_load2(vE,i+1, j+2);

            aa0 = vec256_left1(a0,b0);
            cc0 = vec256_right1(b0,c0);

            a0 = vec256_or3(aa0,b0,cc0);

            aa1 = vec256_left1(a1,b1);
            cc1 = vec256_right1(b1,c1);

            a1 = vec256_or3(aa1,b1,cc1);

            aa2 = vec256_left1(a2,b2);
            cc2 = vec256_right1(b2,c2);

            a2 = vec256_or3(aa2,b2,cc2);

            y = vec256_or3(a0,a1,a2);

            vec256_store2(vOut, i, j, y);
    }
  }
}

void morpho_AVX2(vuint8 **vE, vuint8 **vOut,int vi0, int vi1, int vj0, int vj1, int vi0b, int vi1b, int vj0b, int vj1b){

    vuint8 **vinter1, **vinter2;
    vinter1  = vui8matrix(vi0b, vi1b, vj0b, vj1b);
    vinter2  = vui8matrix(vi0b, vi1b, vj0b, vj1b);

    zero_vui8matrix(vinter1, vi0b, vi1b, vj0b, vj1b);
    zero_vui8matrix(vinter2, vi0b, vi1b, vj0b, vj1b);

    init_bord_AVX2(vE,vi0,vi1,vj0,vj1,vj0b,vj1b);
    erosion_AVX2(vE, vinter1, vi0, vi1, vj0, vj1);

    init_bord_AVX2(vinter1,vi0,vi1,vj0,vj1,vj0b,vj1b);
    dilatation_AVX2(vinter1, vinter2, vi0, vi1, vj0, vj1);

    init_bord_AVX2(vinter2,vi0,vi1,vj0,vj1,vj0b,vj1b);
    dilatation_AVX2(vinter2, vinter1, vi0, vi1, vj0, vj1);

    init_bord_AVX2(vinter1,vi0,vi1,vj0,vj1,vj0b,vj1b);
    erosion_AVX2(vinter1, vOut, vi0, vi1, vj0, vj1);

    free_vui8matrix(vinter1, vi0b, vi1b, vj0b, vj1b);
    free_vui8matrix(vinter2, vi0b, vi1b, vj0b, vj1b);
}


//Optimisation par rotation de registre +  reduction par colonne + déroulage de boucle
void erosion_AVX2_red(vuint8 **vE, vuint8 **vOut, int vi0, int vi1, int vj0, int vj1){
    int i, j;
    int r = (vj1-vj0+1)/2%3;
    lvuint8 a0, b0, c0;
    lvuint8 a1, b1, c1;
    lvuint8 a2, b2, c2;

    lvuint8 ra, rb, rc;
    lvuint8 raa, rcc;
    lvuint8 y;

    for(i = vi0; i <= vi1; i++){

        a0 = vec256_load2(vE,i-1, vj0-2);
        a1 = vec256_load2(vE,i  , vj0-2);
        a2 = vec256_load2(vE,i+1, vj0-2);
        ra = vec256_and3(a0,a1,a2);

        b0 = vec256_load2(vE,i-1, vj0);
        b1 = vec256_load2(vE,i  , vj0);
        b2 = vec256_load2(vE,i+1, vj0);
        rb = vec256_and3(b0,b1,b2);

        for(j = vj0; j <= vj1-2*r; j+=6){
            c0 = vec256_load2(vE,i-1, j+2);
            c1 = vec256_load2(vE,i  , j+2);
            c2 = vec256_load2(vE,i+1, j+2);
            rc = vec256_and3(c0,c1,c2);

            raa = vec256_left1(ra,rb);
            rcc = vec256_right1(rb,rc);
            y = vec256_and3(raa,rb,rcc);

            vec256_store2(vOut, i, j, y);

            a0 = vec256_load2(vE,i-1, j+4);
            a1 = vec256_load2(vE,i  , j+4);
            a2 = vec256_load2(vE,i+1, j+4);
            ra = vec256_and3(a0,a1,a2);

            raa = vec256_left1(rb,rc);
            rcc = vec256_right1(rc,ra);
            y = vec256_and3(raa,rc,rcc);

            vec256_store2(vOut, i, j+2, y);

            b0 = vec256_load2(vE,i-1, j+6);
            b1 = vec256_load2(vE,i  , j+6);
            b2 = vec256_load2(vE,i+1, j+6);
            rb = vec256_and3(b0,b1,b2);

            raa = vec256_left1(rc,ra);
            rcc = vec256_right1(ra,rb);
            y = vec256_and3(raa,ra,rcc);

            vec256_store2(vOut, i, j+4, y);
        }

        switch (r){
            case 2:
                a0 = vec256_load2(vE,i-1, vj1-5);
                a1 = vec256_load2(vE,i  , vj1-5);
                a2 = vec256_load2(vE,i+1, vj1-5);
                ra = vec256_and3(a0,a1,a2);

                b0 = vec256_load2(vE,i-1, vj1-3);
                b1 = vec256_load2(vE,i  , vj1-3);
                b2 = vec256_load2(vE,i+1, vj1-3);
                rb = vec256_and3(b0,b1,b2);

                c0 = vec256_load2(vE,i-1, vj1-1);
                c1 = vec256_load2(vE,i  , vj1-1);
                c2 = vec256_load2(vE,i+1, vj1-1);
                rc = vec256_and3(c0,c1,c2);

                raa = vec256_left1(ra,rb);
                rcc = vec256_right1(rb,rc);
                y = vec256_and3(raa,rb,rcc);

                vec256_store2(vOut, i, vj1-3, y);

            case 1:
                a0 = vec256_load2(vE,i-1, vj1-3);
                a1 = vec256_load2(vE,i  , vj1-3);
                a2 = vec256_load2(vE,i+1, vj1-3);
                ra = vec256_and3(a0,a1,a2);

                b0 = vec256_load2(vE,i-1, vj1-1);
                b1 = vec256_load2(vE,i  , vj1-1);
                b2 = vec256_load2(vE,i+1, vj1-1);
                rb = vec256_and3(b0,b1,b2);

                c0 = vec256_load2(vE,i-1, vj1+1);
                c1 = vec256_load2(vE,i  , vj1+1);
                c2 = vec256_load2(vE,i+1, vj1+1);
                rc = vec256_and3(c0,c1,c2);

                raa = vec256_left1(ra,rb);
                rcc = vec256_right1(rb,rc);
                y = vec256_and3(raa,rb,rcc);

                vec256_store2(vOut, i, vj1-1, y);

        }
    }
}

void dilatation_AVX2_red(vuint8 **vE, vuint8 **vOut, int vi0, int vi1, int vj0, int vj1){
    int i, j;
    int r = (vj1-vj0+1)/2%3;
    lvuint8 a0, b0, c0;
    lvuint8 a1, b1, c1;
    lvuint8 a2, b2, c2;

    lvuint8 ra, rb, rc;
    lvuint8 raa, rcc;
    lvuint8 y;

    for(i = vi0; i <= vi1; i++){

        a0 = vec256_load2(vE,i-1, vj0-2);
        a1 = vec256_load2(vE,i  , vj0-2);
        a2 = vec256_load2(vE,i+1, vj0-2);
        ra = vec256_or3(a0,a1,a2);

        b0 = vec256_load2(vE,i-1, vj0);
        b1 = vec256_load2(vE,i  , vj0);
        b2 = vec256_load2(vE,i+1, vj0);
        rb = vec256_or3(b0,b1,b2);

        for(j = vj0; j <= vj1-2*r; j+=6){
            c0 = vec256_load2(vE,i-1, j+2);
            c1 = vec256_load2(vE,i  , j+2);
            c2 = vec256_load2(vE,i+1, j+2);
            rc = vec256_or3(c0,c1,c2);

            raa = vec256_left1(ra,rb);
            rcc = vec256_right1(rb,rc);
            y = vec256_or3(raa,rb,rcc);

            vec256_store2(vOut, i, j, y);

            a0 = vec256_load2(vE,i-1, j+4);
            a1 = vec256_load2(vE,i  , j+4);
            a2 = vec256_load2(vE,i+1, j+4);
            ra = vec256_or3(a0,a1,a2);

            raa = vec256_left1(rb,rc);
            rcc = vec256_right1(rc,ra);
            y = vec256_or3(raa,rc,rcc);

            vec256_store2(vOut, i, j+2, y);

            b0 = vec256_load2(vE,i-1, j+6);
            b1 = vec256_load2(vE,i  , j+6);
            b2 = vec256_load2(vE,i+1, j+6);
            rb = vec256_or3(b0,b1,b2);

            raa = vec256_left1(rc,ra);
            rcc = vec256_right1(ra,rb);
            y = vec256_or3(raa,ra,rcc);

            vec256_store2(vOut, i, j+4, y);
        }

        switch (r){
            case 2:
                a0 = vec256_load2(vE,i-1, vj1-5);
                a1 = vec256_load2(vE,i  , vj1-5);
                a2 = vec256_load2(vE,i+1, vj1-5);
                ra = vec256_or3(a0,a1,a2);

                b0 = vec256_load2(vE,i-1, vj1-3);
                b1 = vec256_load2(vE,i  , vj1-3);
                b2 = vec256_load2(vE,i+1, vj1-3);
                rb = vec256_or3(b0,b1,b2);

                c0 = vec256_load2(vE,i-1, vj1-1);
                c1 = vec256_load2(vE,i  , vj1-1);
                c2 = vec256_load2(vE,i+1, vj1-1);
                rc = vec256_or3(c0,c1,c2);

                raa = vec256_left1(ra,rb);
                rcc = vec256_right1(rb,rc);
                y = vec256_or3(raa,rb,rcc);

                vec256_store2(vOut, i, vj1-3, y);

            case 1:
                a0 = vec256_load2(vE,i-1, vj1-3);
                a1 = vec256_load2(vE,i  , vj1-3);
                a2 = vec256_load2(vE,i+1, vj1-3);
                ra = vec256_or3(a0,a1,a2);

                b0 = vec256_load2(vE,i-1, vj1-1);
                b1 = vec256_load2(vE,i  , vj1-1);
                b2 = vec256_load2(vE,i+1, vj1-1);
                rb = vec256_or3(b0,b1,b2);

                c0 = vec256_load2(vE,i-1, vj1+1);
                c1 = vec256_load2(vE,i  , vj1+1);
                c2 = vec256_load2(vE,i+1, vj1+1);
                rc = vec256_or3(c0,c1,c2);

                raa = vec256_left1(ra,rb);
                rcc = vec256_right1(rb,rc);
                y = vec256_or3(raa,rb,rcc);

                vec256_store2(vOut, i, vj1-1, y);

        }
    }
}

void morpho_AVX2_red(vuint8 **vE, vuint8 **vOut,int vi0, int vi1, int vj0, int vj1, int vi0b, int vi1b, int vj0b, int vj1b){

    vuint8 **vinter1, **vinter2;
    vinter1  = vui8matrix(vi0b, vi1b, vj0b, vj1b);
    vinter2  = vui8matrix(vi0b, vi1b, vj0b, vj1b);

    zero_vui8matrix(vinter1, vi0b, vi1b, vj0b, vj1b);
    zero_vui8matrix(vinter2, vi0b, vi1b, vj0b, vj1b);

    init_bord_AVX2(vE,vi0,vi1,vj0,vj1,vj0b,vj1b);
    erosion_AVX2_red(vE, vinter1, vi0, vi1, vj0, vj1);

    init_bord_AVX2(vinter1,vi0,vi1,vj0,vj1,vj0b,vj1b);
    dilatation_AVX2_red(vinter1, vinter2, vi0, vi1, vj0, vj1);

    init_bord_AVX2(vinter2,vi0,vi1,vj0,vj1,vj0b,vj1b);
    dilatation_AVX2_red(vinter2, vinter1, vi0, vi1, vj0, vj1);

    init_bord_AVX2(vinter1,vi0,vi1,vj0,vj1,vj0b,vj1b);
    erosion_AVX2_red(vinter1, vOut, vi0, vi1, vj0, vj1);

    free_vui8matrix(vinter1, vi0b, vi1b, vj0b, vj1b);
    free_vui8matrix(vinter2, vi0b, vi1b, vj0b, vj1b);
}
