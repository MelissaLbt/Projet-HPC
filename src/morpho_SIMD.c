/* Algorithme Morphologie version SIMD SSE2*/

#include <stdio.h>
#include <stdlib.h>

#include "nrdef.h"
#include "nrutil.h"

#include "vnrdef.h"
#include "vnrutil.h"

#include "mutil.h"

#include "morpho_SIMD.h"
#include "mymacro.h"

/* --------------------- */
/* E: Image d'entree     */
/* I: Image avec bord    */
/* img: Image de sortie  */
/* --------------------- */
void init_bord(vuint8 **vE,int vi0,int vi1,int vj0,int vj1,int vj0b,int vj1b){//E: deja init avec b=2
  int cst;
	vuint8 vcst;

	vcst = vec_load2(vE,vi0,vj0); cst = vec_extractl(vcst); vec_store2(vE,vi0,vj0b,vec_set(cst));
	vcst = vec_load2(vE,vi0,vj1); cst = vec_extractr(vcst); vec_store2(vE,vi0,vj1b,vec_set(cst));
	vcst = vec_load2(vE,vi1,vj0); cst = vec_extractl(vcst); vec_store2(vE,vi1,vj0b,vec_set(cst));
	vcst = vec_load2(vE,vi1,vj1); cst = vec_extractr(vcst); vec_store2(vE,vi1,vj1b,vec_set(cst));

	for(int j = vj0b; j <= vj1b; j++){
		vcst = vec_load2(vE,vi0,j); vec_store2(vE,vi0-1,j,vcst); vec_store2(vE,vi0-2,j,vcst);
		vcst = vec_load2(vE,vi1,j); vec_store2(vE,vi1+1,j,vcst); vec_store2(vE,vi1+2,j,vcst);
	}
	for(int i = vi0; i <= vi1; i++){
		vcst = vec_load2(vE,i,vj0); cst = vec_extractl(vcst); vec_store2(vE,i,vj0-1,vec_set(cst));
		vcst = vec_load2(vE,i,vj1); cst = vec_extractr(vcst); vec_store2(vE,i,vj1+1,vec_set(cst));
	}
    //display_vui8matrix(vE,vi0-2,vi0-2,vj0b,vj0b,"%4d","vE_simd");
}

void erosion_SIMD(vuint8 **vE, vuint8 **vOut, int vi0, int vi1, int vj0, int vj1){

  int i, j;
  vuint8 a0, b0, c0;
  vuint8 a1, b1, c1;
  vuint8 a2, b2, c2;

  vuint8 aa0, cc0;
  vuint8 aa1, cc1;
  vuint8 aa2, cc2;
  vuint8 y;

	for(i = vi0; i <= vi1; i++){

	    for(j = vj0; j <= vj1; j++){

	    	a0 = vec_load2(vE,i-1, j-1);
		    a1 = vec_load2(vE,i  , j-1);
		    a2 = vec_load2(vE,i+1, j-1);

		    b0 = vec_load2(vE,i-1, j);
		    b1 = vec_load2(vE,i  , j);
		    b2 = vec_load2(vE,i+1, j);

		    c0 = vec_load2(vE,i-1, j+1);
		    c1 = vec_load2(vE,i  , j+1);
		    c2 = vec_load2(vE,i+1, j+1);

		    aa0 = vec_left1(a0,b0);
		    cc0 = vec_right1(b0,c0);

		    a0 = vec_and3(aa0,b0,cc0);

		    aa1 = vec_left1(a1,b1);
		    cc1 = vec_right1(b1,c1);

		    a1 = vec_and3(aa1,b1,cc1);

		    aa2 = vec_left1(a2,b2);
		    cc2 = vec_right1(b2,c2);

		    a2 = vec_and3(aa2,b2,cc2);

		    y = vec_and3(a0,a1,a2);

		    vec_store2(vOut,i,j, y);
	    }
  	}
}

//Optimisation par rotation de registre +  reduction par colonne + déroulage de boucle
void erosion_SIMD_red(vuint8 **vE, vuint8 **vOut, int vi0, int vi1, int vj0, int vj1){
	int i, j;
    int r = (vj1-vj0+1)%3;
	vuint8 a0, b0, c0;
	vuint8 a1, b1, c1;
	vuint8 a2, b2, c2;

    vuint8 ra, rb, rc;
	vuint8 raa, rcc;
	vuint8 y;

	for(i = vi0; i <= vi1; i++){

		a0 = vec_load2(vE,i-1, vj0-1);
		a1 = vec_load2(vE,i  , vj0-1);
		a2 = vec_load2(vE,i+1, vj0-1);
        ra = vec_and3(a0,a1,a2);

		b0 = vec_load2(vE,i-1, vj0);
		b1 = vec_load2(vE,i  , vj0);
		b2 = vec_load2(vE,i+1, vj0);
        rb = vec_and3(b0,b1,b2);

		for(j = vj0; j <= vj1-r; j+=3){
            c0 = vec_load2(vE,i-1, j+1);
            c1 = vec_load2(vE,i  , j+1);
            c2 = vec_load2(vE,i+1, j+1);
            rc = vec_and3(c0,c1,c2);

			raa = vec_left1(ra,rb);
			rcc = vec_right1(rb,rc);
			y = vec_and3(raa,rb,rcc);

            vec_store2(vOut, i, j, y);

            a0 = vec_load2(vE,i-1, j+2);
            a1 = vec_load2(vE,i  , j+2);
            a2 = vec_load2(vE,i+1, j+2);
            ra = vec_and3(a0,a1,a2);

            raa = vec_left1(rb,rc);
            rcc = vec_right1(rc,ra);
            y = vec_and3(raa,rc,rcc);

            vec_store2(vOut, i, j+1, y);

            b0 = vec_load2(vE,i-1, j+3);
            b1 = vec_load2(vE,i  , j+3);
            b2 = vec_load2(vE,i+1, j+3);
            rb = vec_and3(b0,b1,b2);

            raa = vec_left1(rc,ra);
            rcc = vec_right1(ra,rb);
            y = vec_and3(raa,ra,rcc);

            vec_store2(vOut, i, j+2, y);
		}

        switch (r){
            case 2:
                a0 = vec_load2(vE,i-1, vj1-2);
                a1 = vec_load2(vE,i  , vj1-2);
                a2 = vec_load2(vE,i+1, vj1-2);
                ra = vec_and3(a0,a1,a2);

                b0 = vec_load2(vE,i-1, vj1-1);
                b1 = vec_load2(vE,i  , vj1-1);
                b2 = vec_load2(vE,i+1, vj1-1);
                rb = vec_and3(b0,b1,b2);

                c0 = vec_load2(vE,i-1, vj1);
                c1 = vec_load2(vE,i  , vj1);
                c2 = vec_load2(vE,i+1, vj1);
                rc = vec_and3(c0,c1,c2);

                raa = vec_left1(ra,rb);
                rcc = vec_right1(rb,rc);
                y = vec_and3(raa,rb,rcc);

                vec_store2(vOut, i, vj1-1, y);
            
            case 1:
                a0 = vec_load2(vE,i-1, vj1-1);
                a1 = vec_load2(vE,i  , vj1-1);
                a2 = vec_load2(vE,i+1, vj1-1);
                ra = vec_and3(a0,a1,a2);

                b0 = vec_load2(vE,i-1, vj1);
                b1 = vec_load2(vE,i  , vj1);
                b2 = vec_load2(vE,i+1, vj1);
                rb = vec_and3(b0,b1,b2);

                c0 = vec_load2(vE,i-1, vj1+1);
                c1 = vec_load2(vE,i  , vj1+1);
                c2 = vec_load2(vE,i+1, vj1+1);
                rc = vec_and3(c0,c1,c2);

                raa = vec_left1(ra,rb);
                rcc = vec_right1(rb,rc);
                y = vec_and3(raa,rb,rcc);

                vec_store2(vOut, i, vj1, y);        

        }
	}
}

void dilatation_SIMD(vuint8 **vE, vuint8 **vOut, int vi0, int vi1, int vj0, int vj1){
	int i, j;
	vuint8 a0, b0, c0;
	vuint8 a1, b1, c1;
	vuint8 a2, b2, c2;

	vuint8 aa0, cc0;
	vuint8 aa1, cc1;
	vuint8 aa2, cc2;
	vuint8 y;

	for(i = vi0; i<= vi1; i++){

	    for(j = vj0; j < vj1; j++){

	    	a0 = vec_load2(vE,i-1, j-1);
		    a1 = vec_load2(vE,i  , j-1);
		    a2 = vec_load2(vE,i+1, j-1);

		    b0 = vec_load2(vE,i-1, j);
		    b1 = vec_load2(vE,i  , j);
		    b2 = vec_load2(vE,i+1, j);

		    c0 = vec_load2(vE,i-1, j+1);
		    c1 = vec_load2(vE,i  , j+1);
		    c2 = vec_load2(vE,i+1, j+1);

		    aa0 = vec_left1(a0,b0);
		    cc0 = vec_right1(b0,c0);

		    a0 = vec_or3(aa0,b0,cc0);

		    aa1 = vec_left1(a1,b1);
		    cc1 = vec_right1(b1,c1);

		    a1 = vec_or3(aa1,b1,cc1);

		    aa2 = vec_left1(a2,b2);
		    cc2 = vec_right1(b2,c2);

		    a2 = vec_or3(aa2,b2,cc2);

		    y = vec_or3(a0,a1,a2);

		    vec_store2(vOut, i, j, y);
	    }
  	}
}

//Optimisation par rotation de registre +  reduction par colonne + déroulage de boucle
void dilatation_SIMD_red(vuint8 **vE, vuint8 **vOut, int vi0, int vi1, int vj0, int vj1){
	int i, j;
    int r = (vj1-vj0+1)%3;
    vuint8 a0, b0, c0;
    vuint8 a1, b1, c1;
    vuint8 a2, b2, c2;

    vuint8 ra, rb, rc;
    vuint8 raa, rcc;
    vuint8 y;

    for(i = vi0; i <= vi1; i++){

        a0 = vec_load2(vE,i-1, vj0-1);
        a1 = vec_load2(vE,i  , vj0-1);
        a2 = vec_load2(vE,i+1, vj0-1);
        ra = vec_or3(a0,a1,a2);

        b0 = vec_load2(vE,i-1, vj0);
        b1 = vec_load2(vE,i  , vj0);
        b2 = vec_load2(vE,i+1, vj0);
        rb = vec_or3(b0,b1,b2);

        for(j = vj0; j <= vj1-r; j+=3){
            c0 = vec_load2(vE,i-1, j+1);
            c1 = vec_load2(vE,i  , j+1);
            c2 = vec_load2(vE,i+1, j+1);
            rc = vec_or3(c0,c1,c2);

            raa = vec_left1(ra,rb);
            rcc = vec_right1(rb,rc);
            y = vec_or3(raa,rb,rcc);

            vec_store2(vOut, i, j, y);

            a0 = vec_load2(vE,i-1, j+2);
            a1 = vec_load2(vE,i  , j+2);
            a2 = vec_load2(vE,i+1, j+2);
            ra = vec_or3(a0,a1,a2);

            raa = vec_left1(rb,rc);
            rcc = vec_right1(rc,ra);
            y = vec_or3(raa,rc,rcc);

            vec_store2(vOut, i, j+1, y);

            b0 = vec_load2(vE,i-1, j+3);
            b1 = vec_load2(vE,i  , j+3);
            b2 = vec_load2(vE,i+1, j+3);
            rb = vec_or3(b0,b1,b2);

            raa = vec_left1(rc,ra);
            rcc = vec_right1(ra,rb);
            y = vec_or3(raa,ra,rcc);

            vec_store2(vOut, i, j+2, y);
        }

        switch (r){
            case 2:
                a0 = vec_load2(vE,i-1, vj1-2);
                a1 = vec_load2(vE,i  , vj1-2);
                a2 = vec_load2(vE,i+1, vj1-2);
                ra = vec_or3(a0,a1,a2);

                b0 = vec_load2(vE,i-1, vj1-1);
                b1 = vec_load2(vE,i  , vj1-1);
                b2 = vec_load2(vE,i+1, vj1-1);
                rb = vec_or3(b0,b1,b2);

                c0 = vec_load2(vE,i-1, vj1);
                c1 = vec_load2(vE,i  , vj1);
                c2 = vec_load2(vE,i+1, vj1);
                rc = vec_or3(c0,c1,c2);

                raa = vec_left1(ra,rb);
                rcc = vec_right1(rb,rc);
                y = vec_or3(raa,rb,rcc);

                vec_store2(vOut, i, vj1-1, y);
            
            case 1:
                a0 = vec_load2(vE,i-1, vj1-1);
                a1 = vec_load2(vE,i  , vj1-1);
                a2 = vec_load2(vE,i+1, vj1-1);
                ra = vec_or3(a0,a1,a2);

                b0 = vec_load2(vE,i-1, vj1);
                b1 = vec_load2(vE,i  , vj1);
                b2 = vec_load2(vE,i+1, vj1);
                rb = vec_or3(b0,b1,b2);

                c0 = vec_load2(vE,i-1, vj1+1);
                c1 = vec_load2(vE,i  , vj1+1);
                c2 = vec_load2(vE,i+1, vj1+1);
                rc = vec_or3(c0,c1,c2);

                raa = vec_left1(ra,rb);
                rcc = vec_right1(rb,rc); 
                y = vec_or3(raa,rb,rcc);

                vec_store2(vOut, i, vj1, y);       

        }
    }
}

void morpho_SIMD(vuint8 **vE, vuint8 **vOut,int vi0, int vi1, int vj0, int vj1, int vi0b, int vi1b, int vj0b, int vj1b){

	vuint8 **vinter1, **vinter2;
	vinter1  = vui8matrix(vi0b, vi1b, vj0b, vj1b);
	vinter2  = vui8matrix(vi0b, vi1b, vj0b, vj1b);

	zero_vui8matrix(vinter1, vi0b, vi1b, vj0b, vj1b);
	zero_vui8matrix(vinter2, vi0b, vi1b, vj0b, vj1b);

	init_bord(vE,vi0,vi1,vj0,vj1,vj0b,vj1b);
	erosion_SIMD_red(vE, vinter1, vi0, vi1, vj0, vj1);
    // erosion_SIMD(vE, vinter1, vi0, vi1, vj0, vj1);

    init_bord(vinter1,vi0,vi1,vj0,vj1,vj0b,vj1b);
    dilatation_SIMD_red(vinter1, vinter2, vi0, vi1, vj0, vj1);
    // dilatation_SIMD(vinter1, vinter2, vi0, vi1, vj0, vj1);

    init_bord(vinter2,vi0,vi1,vj0,vj1,vj0b,vj1b);
    dilatation_SIMD_red(vinter2, vinter1, vi0, vi1, vj0, vj1);
    // dilatation_SIMD(vinter2, vinter1, vi0, vi1, vj0, vj1);

    init_bord(vinter1,vi0,vi1,vj0,vj1,vj0b,vj1b);
    erosion_SIMD_red(vinter1, vOut, vi0, vi1, vj0, vj1);
    // erosion_SIMD(vinter1, vOut, vi0, vi1, vj0, vj1);

    free_vui8matrix(vinter1, vi0b, vi1b, vj0b, vj1b);
    free_vui8matrix(vinter2, vi0b, vi1b, vj0b, vj1b);

}
