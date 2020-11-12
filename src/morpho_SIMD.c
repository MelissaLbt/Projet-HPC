/* Algorithme Morphologie version SIMD */

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

void test(vuint8 **vE, int vi1, int vj1){
	vuint8 a;
	for(int i = 0; i <= vi1; i++){
		for(int j=0;j<=vj1;j++){
			a = _mm_load_si128((vuint8*) &vE[i][j]);
			DEBUG(display_vuint8(a, "%4d", "a = ")); DEBUG(puts(""));
		}
	}
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

		    a0 = vMIN3(aa0,b0,cc0);

		    aa1 = vec_left1(a1,b1);
		    cc1 = vec_right1(b1,c1);

		    a1 = vMIN3(aa1,b1,cc1);

		    aa2 = vec_left1(a2,b2);
		    cc2 = vec_right1(b2,c2);

		    a2 = vMIN3(aa2,b2,cc2);

		    y = vMIN3(a0,a1,a2);

		    vec_store2(vOut,i,j, y);
	    }
  	}
}

//Optimisation par rotation de registre
void erosion_SIMD_rot(vuint8 **vE, vuint8 **vOut, int vi0, int vi1, int vj0, int vj1){
	int i, j;
	vuint8 a0, b0, c0;
	vuint8 a1, b1, c1;
	vuint8 a2, b2, c2;

	vuint8 aa0, cc0;
	vuint8 aa1, cc1;
	vuint8 aa2, cc2;
	vuint8 y;

	for(i = vi0; i <= vi1; i++){
		a0 = vec_load2(vE,i-1, -1);
		a1 = vec_load2(vE,i  , -1);
		a2 = vec_load2(vE,i+1, -1);

		b0 = vec_load2(vE,i-1, 0);
		b1 = vec_load2(vE,i  , 0);
		b2 = vec_load2(vE,i+1, 0);

		c0 = vec_load2(vE,i-1, 1);
		c1 = vec_load2(vE,i  , 1);
		c2 = vec_load2(vE,i+1, 1);

		for(j = 1; j <= vj1; j++){

			aa0 = vec_left1(a0,b0);
			cc0 = vec_right1(b0,c0);

			a0 = vMIN3(aa0,b0,cc0);

			aa1 = vec_left1(a1,b1);
			cc1 = vec_right1(b1,c1);

			a1 = vMIN3(aa1,b1,cc1);

			aa2 = vec_left1(a2,b2);
			cc2 = vec_right1(b2,c2);

			a2 = vMIN3(aa2,b2,cc2);

			y = vMIN3(a0,a1,a2);

			a0 = b0; a1 = b1; a2 = b2;
			b0 = c0; b1 = c1; b2 = c2;

			c0 = vec_load2(vE, i-1, j+1);
			a0 = vMIN3(aa0,b0,cc0);
			c1 = vec_load2(vE, i, j+1);
			c2 = vec_load2(vE, i+1, j+1);

			vec_store2(vOut, i, j-1, y);
		}
		aa0 = vec_left1(a0,b0);
		cc0 = vec_right1(b0,c0);


		aa1 = vec_left1(a1,b1);
		cc1 = vec_right1(b1,c1);

		a1 = vMIN3(aa1,b1,cc1);

		aa2 = vec_left1(a2,b2);
		cc2 = vec_right1(b2,c2);

		a2 = vMIN3(aa2,b2,cc2);

		y = vMIN3(a0,a1,a2);
		vec_store2(vOut, i, j, y);
	}
}

//Optimisation par réduction pqr colonne et déroulage de boucle
void erosion_SIMD_red(vuint8 **vE, vuint8 **vOut, int vi0, int vi1, int vj0, int vj1){
    
    int i, j;
    int r = (vj1-vj0+1)%3;
    vuint8 a0, b0, c0;
    vuint8 a1, b1, c1;
    vuint8 a2, b2, c2;

    vuint8 ra, rb, rc;
    vuint8 opl, opr;
    vuint8 y0, y1, y2, y;

    for(i = vi0; i <= vi1; i++){
        j = 0;
        a0 = vec_load2(vE,i-1, j-1);
        a1 = vec_load2(vE,i  , j-1);
        a2 = vec_load2(vE,i+1, j-1);

        b0 = vec_load2(vE,i-1, j);
        b1 = vec_load2(vE,i  , j);
        b2 = vec_load2(vE,i+1, j);

        ra = vMIN3(a0, a1, a2);
        rb = vMIN3(b0, b1, b2);

        for(j = vj0; j <= vj1-r; j+=3){
            // centre: rb
            c0 = vec_load2(vE,i-1, j+1);
            c1 = vec_load2(vE,i  , j+1);
            c2 = vec_load2(vE,i+1, j+1);
            rc = vMIN3(c0, c1, c2);

            opl = vec_left1(ra, rb);
            opr = vec_right1(rb, rc);
            y0 = vMIN3(opl, rb, opr);
            vec_store2(vOut,i,j, y0);

            // centre: rc
            a0 = vec_load2(vE,i-1, j+2);
            a1 = vec_load2(vE,i  , j+2);
            a2 = vec_load2(vE,i+1, j+2);
            ra = vMIN3(a0, a1, a2);

            opl = vec_left1(rb, rc);
            opr = vec_right1(rc, ra);
            y1 = vMIN3(opl, rc, opr);
            vec_store2(vOut,i,j+1, y1);

            // centre: ra
            b0 = vec_load2(vE,i-1, j+3);
            b1 = vec_load2(vE,i  , j+3);
            b2 = vec_load2(vE,i+1, j+3);
            rb = vMIN3(b0, b1, b2);

            opl = vec_left1(rc, ra); 
            opr = vec_right1(ra, rb);
            y2 = vMIN3(opl, ra, opl);

            vec_store2(vOut,i,j+2, y2);
        }
        //epilogue
        switch(r){
            case 2:
                a0 = vec_load2(vE,i-1, vj1-2);
                a1 = vec_load2(vE,i  , vj1-2);
                a2 = vec_load2(vE,i+1, vj1-2);

                b0 = vec_load2(vE,i-1, vj1-1);
                b1 = vec_load2(vE,i  , vj1-1);
                b2 = vec_load2(vE,i+1, vj1-1);

                c0 = vec_load2(vE,i-1, vj1);
                c1 = vec_load2(vE,i  , vj1);
                c2 = vec_load2(vE,i+1, vj1);

                ra = vMIN3(a0, a1, a2);
                rb = vMIN3(b0, b1, b2);
                rc = vMIN3(c0, c1, c2);
                opl = vec_left1(ra, rb); 
                opr = vec_right1(rb, rc);
                y   = vMIN3(opl, rb, opr);
                vec_store2(vOut,i,vj1-1, y);
            
            case 1:
                a0 = vec_load2(vE,i-1, vj1-1);
                a1 = vec_load2(vE,i  , vj1-1);
                a2 = vec_load2(vE,i+1, vj1-1);

                b0 = vec_load2(vE,i-1, vj1);
                b1 = vec_load2(vE,i  , vj1);
                b2 = vec_load2(vE,i+1, vj1);

                c0 = vec_load2(vE,i-1, vj1+1);
                c1 = vec_load2(vE,i  , vj1+1);
                c2 = vec_load2(vE,i+1, vj1+1);

                ra = vMIN3(a0, a1, a2);
                rb = vMIN3(b0, b1, b2);
                rc = vMIN3(c0, c1, c2);
                opl = vec_left1(ra, rb); 
                opr = vec_right1(rb, rc);
                y   = vMIN3(opl, rb, opr);
                vec_store2(vOut,i,vj1, y);
                break;
        }
    }

}


void erosion2_SIMD(vuint8 **vE, int n, vuint8 **vOut){
	/*
  int i, j;
  vuint8 a0, b0, c0, d0, e0;
  vuint8 a1, b1, c1, d1, e1;
  vuint8 a2, b2, c2, d2, e2;
  vuint8 a3, b3, c3, d3, e3;
  vuint8 a4, b4, c4, d4, e4;
  vuint8 xx0,xx1,xx2,xx3,xx4;
  vuint8 ff0,ff1,ff2,ff3,ff4;

  for(i = 0; i < n; i++){
    b0 = vec_load2((uint8*) &vE[i-2][-2]);
    b1 = vec_load2((uint8*) &vE[i-1][-2]);
    b2 = vec_load2((uint8*) &vE[i  ][-2]);
    b3 = vec_load2((uint8*) &vE[i+1][-2]);
    b4 = vec_load2((uint8*) &vE[i+2][-2]);

    c0 = vec_load2((uint8*) &vE[i-2][-1]);
    c1 = vec_load2((uint8*) &vE[i-1][-1]);
    c2 = vec_load2((uint8*) &vE[i  ][-1]);
    c3 = vec_load2((uint8*) &vE[i+1][-1]);
    c4 = vec_load2((uint8*) &vE[i+2][-1]);

    d0 = vec_load2((uint8*) &vE[i-2][0]);
    d1 = vec_load2((uint8*) &vE[i-1][0]);
    d2 = vec_load2((uint8*) &vE[i  ][0]);
    d3 = vec_load2((uint8*) &vE[i+1][0]);
    d4 = vec_load2((uint8*) &vE[i+2][0]);

    for(j = 1; j < n; j++){
      a0 = vec_left2(b0,c0);
      ff0 = vec_left1(b0,c0);
      xx0 = vec_right1(c0,d0);
      e0 = vec_right2(c0,d0);

      b0 = vMIN5(a0,ff0,b0,xx0,e0);

      a1 = vec_left2(b1,c1);
      ff1 = vec_left1(b1,c1);
      xx1 = vec_right1(c1,d1);
      e1 = vec_right2(c1,d1);

      b1 = vMIN5(a1,ff1,b1,xx1,e1);

      a2 = vec_left2(b2,c2);
      ff2 = vec_left1(b2,c2);
      xx2 = vec_right1(c2,d2);
      e2 = vec_right2(c2,d2);

      b2 = vMIN5(a2,ff2,b2,xx2,e2);
      b3 = vMIN5(a3,ff3,b3,xx3,e3);

      a3 = vec_left2(b3,c3);
      ff3 = vec_left1(b3,c3);
      xx3 = vec_right1(c3,d3);
      e3 = vec_right2(c3,d3);


      a4 = vec_left2(b4,c4);
      ff4 = vec_left1(b4,c4);
      xx4 = vec_right1(c4,d4);
      e4 = vec_right2(c4,d4);

      b4 = vMIN5(a4,ff4,b4,xx4,e4);

      y = vMIN5(b0,b1,b2,b3,b4);
      _mm_store_si128((uint8*) &vOut[i][j-1], y);

      b0 = c0; b1 = c1; b2 = c2; b3 = c3; b4 = c4;
      c0 = d0; c1 = d1; c2 = d2; c3 = d3; c4 = d4;

      d0 = vec_load2((uint8*) &vE[i-2][j]);
      d1 = vec_load2((uint8*) &vE[i-1][j]);
      d2 = vec_load2((uint8*) &vE[i  ][j]);
      d3 = vec_load2((uint8*) &vE[i+1][j]);
      d4 = vec_load2((uint8*) &vE[i+2][j]);
    }
    a0 = vec_left2(b0,c0);
    ff0 = vec_left1(b0,c0);
    xx0 = vec_right1(c0,d0);
    e0 = vec_right2(c0,d0);

    b0 = vMIN5(a0,ff0,b0,xx0,e0);

    a1 = vec_left2(b1,c1);
    ff1 = vec_left1(b1,c1);
    xx1 = vec_right1(c1,d1);
    e1 = vec_right2(c1,d1);

    b1 = vMIN5(a1,ff1,b1,xx1,e1);

    a2 = vec_left2(b2,c2);
    ff2 = vec_left1(b2,c2);
    xx2 = vec_right1(c2,d2);
    e2 = vec_right2(c2,d2);

    b2 = vMIN5(a2,ff2,b2,xx2,e2);

    a3 = vec_left2(b3,c3);
    ff3 = vec_left1(b3,c3);
    xx3 = vec_right1(c3,d3);
    e3 = vec_right2(c3,d3);

    b3 = vMIN5(a3,ff3,b3,xx3,e3);


    a4 = vec_left2(b4,c4);
    ff4 = vec_left1(b4,c4);
    xx4 = vec_right1(c4,d4);
    e4 = vec_right2(c4,d4);

    b4 = vMIN5(a4,ff4,b4,xx4,e4);

    y = vMIN5(b0,b1,b2,b3,b4);
    _mm_store_si128((uint8*) &vOut[i][239], y);
  }*/
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

		    a0 = vMAX3(aa0,b0,cc0);

		    aa1 = vec_left1(a1,b1);
		    cc1 = vec_right1(b1,c1);

		    a1 = vMAX3(aa1,b1,cc1);

		    aa2 = vec_left1(a2,b2);
		    cc2 = vec_right1(b2,c2);

		    a2 = vMAX3(aa2,b2,cc2);

		    y = vMAX3(a0,a1,a2);

		    vec_store2(vOut, i, j, y);
	    }
  	}
}

//Optimisation par rotation de registre
void dilatation_SIMD_rot(vuint8 **vE, vuint8 **vOut, int vi0, int vi1, int vj0, int vj1){
	int i, j;
	vuint8 a0, b0, c0;
	vuint8 a1, b1, c1;
	vuint8 a2, b2, c2;

	vuint8 aa0, cc0;
	vuint8 aa1, cc1;
	vuint8 aa2, cc2;
	vuint8 y;

	for(i = vi0; i <= vi1; i++){
		a0 = vec_load2(vE,i-1, -1);
		a1 = vec_load2(vE,i  , -1);
		a2 = vec_load2(vE,i+1, -1);

		b0 = vec_load2(vE,i-1, 0);
		b1 = vec_load2(vE,i  , 0);
		b2 = vec_load2(vE,i+1, 0);

		c0 = vec_load2(vE,i-1, 1);
		c1 = vec_load2(vE,i  , 1);
		c2 = vec_load2(vE,i+1, 1);

		for(j = 1; j <= vj1; j++){

			aa0 = vec_left1(a0,b0);
			cc0 = vec_right1(b0,c0);

			a0 = vMAX3(aa0,b0,cc0);

			aa1 = vec_left1(a1,b1);
			cc1 = vec_right1(b1,c1);

			a1 = vMAX3(aa1,b1,cc1);

			aa2 = vec_left1(a2,b2);
			cc2 = vec_right1(b2,c2);

			a2 = vMAX3(aa2,b2,cc2);

			y = vMAX3(a0,a1,a2);

			a0 = b0; a1 = b1; a2 = b2;
			b0 = c0; b1 = c1; b2 = c2;

			c0 = vec_load2(vE, i-1, j+1);
			a0 = vMAX3(aa0,b0,cc0);
			c1 = vec_load2(vE, i, j+1);
			c2 = vec_load2(vE, i+1, j+1);

			vec_store2(vOut, i, j-1, y);
		}
		aa0 = vec_left1(a0,b0);
		cc0 = vec_right1(b0,c0);


		aa1 = vec_left1(a1,b1);
		cc1 = vec_right1(b1,c1);

		a1 = vMAX3(aa1,b1,cc1);

		aa2 = vec_left1(a2,b2);
		cc2 = vec_right1(b2,c2);

		a2 = vMAX3(aa2,b2,cc2);

		y = vMAX3(a0,a1,a2);
		vec_store2(vOut, i, j, y);
	}
}

void dilatation_SIMD_red(vuint8 **vE, vuint8 **vOut, int vi0, int vi1, int vj0, int vj1){

    int i, j;
    int r = (vj1-vj0+1)%3;
    vuint8 a0, b0, c0;
    vuint8 a1, b1, c1;
    vuint8 a2, b2, c2;

    vuint8 ra, rb, rc;
    vuint8 opl, opr;
    vuint8 y0, y1, y2, y;

    for(i = vi0; i <= vi1; i++){
        j = 0;
        a0 = vec_load2(vE,i-1, j-1);
        a1 = vec_load2(vE,i  , j-1);
        a2 = vec_load2(vE,i+1, j-1);

        b0 = vec_load2(vE,i-1, j);
        b1 = vec_load2(vE,i  , j);
        b2 = vec_load2(vE,i+1, j);

        ra = vMAX3(a0, a1, a2);
        rb = vMAX3(b0, b1, b2);

        for(j = vj0; j <= vj1-r; j+=3){
            // centre: rb
            c0 = vec_load2(vE,i-1, j+1);
            c1 = vec_load2(vE,i  , j+1);
            c2 = vec_load2(vE,i+1, j+1);
            rc = vMAX3(c0, c1, c2);

            opl = vec_left1(ra, rb);
            opr = vec_right1(rb, rc);
            y0 = vMAX3(opl, rb, opr);
            vec_store2(vOut,i,j, y0);

            // centre: rc
            a0 = vec_load2(vE,i-1, j+2);
            a1 = vec_load2(vE,i  , j+2);
            a2 = vec_load2(vE,i+1, j+2);
            ra = vMAX3(a0, a1, a2);

            opl = vec_left1(rb, rc);
            opr = vec_right1(rc, ra);
            y1 = vMAX3(opl, rc, opr);
            vec_store2(vOut,i,j+1, y1);

            // centre: ra
            b0 = vec_load2(vE,i-1, j+3);
            b1 = vec_load2(vE,i  , j+3);
            b2 = vec_load2(vE,i+1, j+3);
            rb = vMAX3(b0, b1, b2);

            opl = vec_left1(rc, ra); 
            opr = vec_right1(ra, rb);
            y2 = vMAX3(opl, ra, opl);

            vec_store2(vOut,i,j+2, y2);
        }
        //epilogue
        switch(r){
            case 2:
                a0 = vec_load2(vE,i-1, vj1-2);
                a1 = vec_load2(vE,i  , vj1-2);
                a2 = vec_load2(vE,i+1, vj1-2);

                b0 = vec_load2(vE,i-1, vj1-1);
                b1 = vec_load2(vE,i  , vj1-1);
                b2 = vec_load2(vE,i+1, vj1-1);

                c0 = vec_load2(vE,i-1, vj1);
                c1 = vec_load2(vE,i  , vj1);
                c2 = vec_load2(vE,i+1, vj1);

                ra = vMAX3(a0, a1, a2);
                rb = vMAX3(b0, b1, b2);
                rc = vMAX3(c0, c1, c2);
                opl = vec_left1(ra, rb); 
                opr = vec_right1(rb, rc);
                y   = vMAX3(opl, rb, opr);
                vec_store2(vOut,i,vj1-1, y);
            
            case 1:
                a0 = vec_load2(vE,i-1, vj1-1);
                a1 = vec_load2(vE,i  , vj1-1);
                a2 = vec_load2(vE,i+1, vj1-1);

                b0 = vec_load2(vE,i-1, vj1);
                b1 = vec_load2(vE,i  , vj1);
                b2 = vec_load2(vE,i+1, vj1);

                c0 = vec_load2(vE,i-1, vj1+1);
                c1 = vec_load2(vE,i  , vj1+1);
                c2 = vec_load2(vE,i+1, vj1+1);

                ra = vMAX3(a0, a1, a2);
                rb = vMAX3(b0, b1, b2);
                rc = vMAX3(c0, c1, c2);
                opl = vec_left1(ra, rb); 
                opr = vec_right1(rb, rc);
                y   = vMAX3(opl, rb, opr);
                vec_store2(vOut,i,vj1, y);
                break;
        }
    }

}

void dilatation2_SIMD(vuint8 **vE, int n, vuint8 **vOut){/*
  int i, j;
  vuint8 a0, b0, c0, d0, e0;
  vuint8 a1, b1, c1, d1, e1;
  vuint8 a2, b2, c2, d2, e2;
  vuint8 a3, b3, c3, d3, e3;
  vuint8 a4, b4, c4, d4, e4;
  vuint8 xx0,xx1,xx2,xx3,xx4;
  vuint8 ff0,ff1,ff2,ff3,ff4;

  for(i = 0; i < n; i++){
    b0 = vec_load2((uint8*) &vE[i-2][-2]);
    b1 = vec_load2((uint8*) &vE[i-1][-2]);
    b2 = vec_load2((uint8*) &vE[i  ][-2]);
    b3 = vec_load2((uint8*) &vE[i+1][-2]);
    b4 = vec_load2((uint8*) &vE[i+2][-2]);

    c0 = vec_load2((uint8*) &vE[i-2][-1]);
    c1 = vec_load2((uint8*) &vE[i-1][-1]);
    c2 = vec_load2((uint8*) &vE[i  ][-1]);
    c3 = vec_load2((uint8*) &vE[i+1][-1]);
    c4 = vec_load2((uint8*) &vE[i+2][-1]);

    d0 = vec_load2((uint8*) &vE[i-2][0]);
    d1 = vec_load2((uint8*) &vE[i-1][0]);
    d2 = vec_load2((uint8*) &vE[i  ][0]);
    d3 = vec_load2((uint8*) &vE[i+1][0]);
    d4 = vec_load2((uint8*) &vE[i+2][0]);

    for(j = 1; j < n; j++){
      a0 = vec_left2(b0,c0);
      ff0 = vec_left1(b0,c0);
      xx0 = vec_right1(c0,d0);
      e0 = vec_right2(c0,d0);

      b0 = vMAX5(a0,ff0,b0,xx0,e0);

      a1 = vec_left2(b1,c1);
      ff1 = vec_left1(b1,c1);
      xx1 = vec_right1(c1,d1);
      e1 = vec_right2(c1,d1);

      b1 = vMAX5(a1,ff1,b1,xx1,e1);

      a2 = vec_left2(b2,c2);
      ff2 = vec_left1(b2,c2);
      xx2 = vec_right1(c2,d2);
      e2 = vec_right2(c2,d2);

      b2 = vMAX5(a2,ff2,b2,xx2,e2);

      a3 = vec_left2(b3,c3);
      ff3 = vec_left1(b3,c3);
      xx3 = vec_right1(c3,d3);
      e3 = vec_right2(c3,d3);

      b3 = vMIN5(a3,ff3,b3,xx3,e3);

      a4 = vec_left2(b4,c4);
      ff4 = vec_left1(b4,c4);
      xx4 = vec_right1(c4,d4);
      e4 = vec_right2(c4,d4);

      b4 = vMAX5(a4,ff4,b4,xx4,e4);

      y = vMAX5(b0,b1,b2,b3,b4);
      _mm_store_si128((uint8*) &vOut[i][j-1], y);

      b0 = c0; b1 = c1; b2 = c2; b3 = c3; b4 = c4;
      c0 = d0; c1 = d1; c2 = d2; c3 = d3; c4 = d4;

      d0 = vec_load2((uint8*) &vE[i-2][j]);
      d1 = vec_load2((uint8*) &vE[i-1][j]);
      d2 = vec_load2((uint8*) &vE[i  ][j]);
      d3 = vec_load2((uint8*) &vE[i+1][j]);
      d4 = vec_load2((uint8*) &vE[i+2][j]);
    }
    a0 = vec_left2(b0,c0);
    ff0 = vec_left1(b0,c0);
    xx0 = vec_right1(c0,d0);
    e0 = vec_right2(c0,d0);

    b0 = vMAX5(a0,ff0,b0,xx0,e0);

    a1 = vec_left2(b1,c1);
    ff1 = vec_left1(b1,c1);
    xx1 = vec_right1(c1,d1);
    e1 = vec_right2(c1,d1);

    b1 = vMAX5(a1,ff1,b1,xx1,e1);

    a2 = vec_left2(b2,c2);
    ff2 = vec_left1(b2,c2);
    xx2 = vec_right1(c2,d2);
    e2 = vec_right2(c2,d2);

    b2 = vMAX5(a2,ff2,b2,xx2,e2);

    a3 = vec_left2(b3,c3);
    ff3 = vec_left1(b3,c3);
    xx3 = vec_right1(c3,d3);
    e3 = vec_right2(c3,d3);

    b3 = vMAX5(a3,ff3,b3,xx3,e3);

    a4 = vec_left2(b4,c4);
    ff4 = vec_left1(b4,c4);
    xx4 = vec_right1(c4,d4);
    e4 = vec_right2(c4,d4);

    b4 = vMAX5(a4,ff4,b4,xx4,e4);

    y = vMAX5(b0,b1,b2,b3,b4);
    _mm_store_si128((uint8*) &vOut[i][239], y);
  }*/
}



void morpho_SIMD(vuint8 **vE, vuint8 **vOut,int vi0, int vi1, int vj0, int vj1, int vi0b, int vi1b, int vj0b, int vj1b){

	vuint8 **vinter1, **vinter2;
	vinter1  = vui8matrix(vi0b, vi1b, vj0b, vj1b);
	vinter2  = vui8matrix(vi0b, vi1b, vj0b, vj1b);

	zero_vui8matrix(vinter1, vi0b, vi1b, vj0b, vj1b);
	zero_vui8matrix(vinter2, vi0b, vi1b, vj0b, vj1b);

	init_bord(vE,vi0,vi1,vj0,vj1,vj0b,vj1b);
	//erosion_SIMD_rot(vE, vinter1, vi0, vi1, vj0, vj1);
  erosion_SIMD(vE, vinter1, vi0, vi1, vj0, vj1);

	init_bord(vinter1,vi0,vi1,vj0,vj1,vj0b,vj1b);
	//dilatation_SIMD_rot(vinter1, vinter2, vi0, vi1, vj0, vj1);
  dilatation_SIMD(vinter1, vinter2, vi0, vi1, vj0, vj1);

	init_bord(vinter2,vi0,vi1,vj0,vj1,vj0b,vj1b);
	//dilatation_SIMD_rot(vinter2, vinter1, vi0, vi1, vj0, vj1);
  dilatation_SIMD(vinter2, vinter1, vi0, vi1, vj0, vj1);

	init_bord(vinter1,vi0,vi1,vj0,vj1,vj0b,vj1b);
	//erosion_SIMD_rot(vinter1, vOut, vi0, vi1, vj0, vj1);
  erosion_SIMD(vinter1, vOut, vi0, vi1, vj0, vj1);

  free_vui8matrix(vinter1, vi0b, vi1b, vj0b, vj1b);
  free_vui8matrix(vinter2, vi0b, vi1b, vj0b, vj1b);

}
