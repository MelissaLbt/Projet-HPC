/* Algorithme Morphologie version SIMD SSE2 avec l'optimisation fusion d'operateur*/

#include <stdio.h>
#include <stdlib.h>

#include "nrdef.h"
#include "nrutil.h"

#include "vnrdef.h"
#include "vnrutil.h"

#include "mymacro.h"
#include "mutil.h"

#include "morpho_SIMD.h"
#include "morpho_fusion.h"



void dilatation_fusion(vuint8 **vE, vuint8 **vOut, int vi0, int vi1, int vj0, int vj1){
    int i, j;
    int r = (vj1-vj0+1)%3;
    vuint8 a0, b0, c0;
    vuint8 a1, b1, c1;
    vuint8 a2, b2, c2;
    vuint8 a3, b3, c3;
    vuint8 a4, b4, c4;


    vuint8 ra, rb, rc;
    vuint8 rl2, rl1, rr1, rr2;
    vuint8 y;

    for(i = vi0; i <= vi1; i++){

        a0 = vec_load2(vE,i-2, vj0-1);
        a1 = vec_load2(vE,i-1, vj0-1);
        a2 = vec_load2(vE,i  , vj0-1);
        a3 = vec_load2(vE,i+1, vj0-1);
        a4 = vec_load2(vE,i+2, vj0-1);
        ra = vec_or5(a0,a1,a2,a3,a4);

        b0 = vec_load2(vE,i-2, vj0);
        b1 = vec_load2(vE,i-1, vj0);
        b2 = vec_load2(vE,i  , vj0);
        b3 = vec_load2(vE,i+1, vj0);
        b4 = vec_load2(vE,i+2, vj0);
        rb = vec_or5(b0,b1,b2,b3,b4);

        for(j = vj0; j <= vj1-r; j+=3){
            c0 = vec_load2(vE,i-2, j+1);
            c1 = vec_load2(vE,i-1, j+1);
            c2 = vec_load2(vE,i  , j+1);
            c3 = vec_load2(vE,i+1, j+1);
            c4 = vec_load2(vE,i+2, j+1);
            rc = vec_or5(c0,c1,c2,c3,c4);

            rl2 = vec_left2(ra,rb);
            rl1 = vec_left1(ra,rb);
            rr1 = vec_right1(rb,rc);
            rr2 = vec_right2(rb,rc);
            y = vec_or5(rl2,rl1,rb,rr1,rr2);

            vec_store2(vOut, i, j, y);

            a0 = vec_load2(vE,i-2, j+2);
            a1 = vec_load2(vE,i-1, j+2);
            a2 = vec_load2(vE,i  , j+2);
            a3 = vec_load2(vE,i+1, j+2);
            a4 = vec_load2(vE,i+2, j+2);
            ra = vec_or5(a0,a1,a2,a3,a4);

            rl2 = vec_left2(rb,rc);
            rl1 = vec_left1(rb,rc);
            rr1 = vec_right1(rc,ra);
            rr2 = vec_right2(rc,ra);
            y = vec_or5(rl2,rl1,rc,rr1,rr2);

            vec_store2(vOut, i, j+1, y);

            b0 = vec_load2(vE,i-2, j+3);
            b1 = vec_load2(vE,i-1, j+3);
            b2 = vec_load2(vE,i  , j+3);
            b3 = vec_load2(vE,i+1, j+3);
            b4 = vec_load2(vE,i+2, j+3);
            rb = vec_or5(b0,b1,b2,b3,b4);

            rl2 = vec_left2(rc,ra);
            rl1 = vec_left1(rc,ra);
            rr1 = vec_right1(ra,rb);
            rr2 = vec_right2(ra,rb);
            y = vec_or5(rl2,rl1,ra,rr1,rr2);

            vec_store2(vOut, i, j+2, y);
        }

        switch (r){
            case 2:
                a0 = vec_load2(vE,i-2, vj1-2);
                a1 = vec_load2(vE,i-1, vj1-2);
                a2 = vec_load2(vE,i  , vj1-2);
                a3 = vec_load2(vE,i+1, vj1-2);
                a4 = vec_load2(vE,i+2, vj1-2);
                ra = vec_or5(a0,a1,a2,a3,a4);

                b0 = vec_load2(vE,i-2, vj1-1);
                b1 = vec_load2(vE,i-1, vj1-1);
                b2 = vec_load2(vE,i  , vj1-1);
                b3 = vec_load2(vE,i+1, vj1-1);
                b4 = vec_load2(vE,i+2, vj1-1);
                rb = vec_or5(b0,b1,b2,b3,b3);

                c0 = vec_load2(vE,i-2, vj1);
                c1 = vec_load2(vE,i-1, vj1);
                c2 = vec_load2(vE,i  , vj1);
                c3 = vec_load2(vE,i+1, vj1);
                c4 = vec_load2(vE,i+2, vj1);
                rc = vec_or5(c0,c1,c2,c3,c4);

                rl2 = vec_left2(ra,rb);
                rl1 = vec_left1(ra,rb);
                rr1 = vec_right1(rb,rc);
                rr2 = vec_right2(rb,rc);
                y = vec_or5(rl2,rl1,rb,rr1,rr2);

                vec_store2(vOut, i, vj1-1, y);
            
            case 1:
                a0 = vec_load2(vE,i-2, vj1-1);
                a1 = vec_load2(vE,i-1, vj1-1);
                a2 = vec_load2(vE,i  , vj1-1);
                a3 = vec_load2(vE,i+1, vj1-1);
                a4 = vec_load2(vE,i+2, vj1-1);
                ra = vec_or5(a0,a1,a2,a3,a4);

                b0 = vec_load2(vE,i-2, vj1);
                b1 = vec_load2(vE,i-1, vj1);
                b2 = vec_load2(vE,i  , vj1);
                b3 = vec_load2(vE,i+1, vj1);
                b4 = vec_load2(vE,i+2, vj1);
                rb = vec_or5(b0,b1,b2,b3,b3);

                c0 = vec_load2(vE,i-2, vj1+1);
                c1 = vec_load2(vE,i-1, vj1+1);
                c2 = vec_load2(vE,i  , vj1+1);
                c3 = vec_load2(vE,i+1, vj1+1);
                c4 = vec_load2(vE,i+2, vj1+1);
                rc = vec_or5(c0,c1,c2,c3,c4);

                rl2 = vec_left2(ra,rb);
                rl1 = vec_left1(ra,rb);
                rr1 = vec_right1(rb,rc);
                rr2 = vec_right2(rb,rc);
                y = vec_or5(rl2,rl1,rb,rr1,rr2);

                vec_store2(vOut, i, vj1, y);       

        }
    }
}

void morpho_fusion(vuint8 **vE, vuint8 **vOut,int vi0, int vi1, int vj0, int vj1, int vi0b, int vi1b, int vj0b, int vj1b){

    vuint8 **vinter1, **vinter2;
    vinter1  = vui8matrix(vi0b, vi1b, vj0b, vj1b);
    vinter2  = vui8matrix(vi0b, vi1b, vj0b, vj1b);
    zero_vui8matrix(vinter1, vi0b, vi1b, vj0b, vj1b);
    zero_vui8matrix(vinter2, vi0b, vi1b, vj0b, vj1b);

    init_bord(vE,vi0,vi1,vj0,vj1,vj0b,vj1b);
    erosion_SIMD_red(vE, vinter1, vi0, vi1, vj0, vj1);
    
    init_bord(vinter1,vi0,vi1,vj0,vj1,vj0b,vj1b);
    dilatation_fusion(vinter1, vinter2, vi0, vi1, vj0, vj1);
    
    init_bord(vinter2,vi0,vi1,vj0,vj1,vj0b,vj1b);
    erosion_SIMD_red(vinter2, vOut, vi0, vi1, vj0, vj1);

    free_vui8matrix(vinter1, vi0b, vi1b, vj0b, vj1b);
    free_vui8matrix(vinter2, vi0b, vi1b, vj0b, vj1b);

}