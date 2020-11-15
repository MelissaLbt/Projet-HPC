/* Algorithme Morphologie version SSE2 , SSE2 avec reduction... , avec fusion*/

#include <stdio.h>
#include <stdlib.h>

#include "nrdef.h"
#include "nrutil.h"

#include "vnrdef.h"
#include "vnrutil.h"

#include "mutil.h"

#include "morpho_SSE2.h"
#include "mymacro.h"

/* --------------------- */
/* E: Image d'entree     */
/* I: Image avec bord    */
/* img: Image de sortie  */
/* --------------------- */
void init_bord(vuint8 **vE,int vi0,int vi1,int vj0,int vj1,int vj0b,int vj1b){//E: deja init avec b=2(4)
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
    //display_vui8matrix(vE,vi0-2,vi0-2,vj0b,vj0b,"%4d","vE_SSE2");
}

//SIMD pour b = 1
void erosion_SSE2_r1(vuint8 **vE, vuint8 **vOut, int vi0, int vi1, int vj0, int vj1){

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

		  vec_store2(vOut, i, j, y);
	  }
  }
}

void dilatation_SSE2_r1(vuint8 **vE, vuint8 **vOut, int vi0, int vi1, int vj0, int vj1){
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

		  vec_store2(vOut, i, j-1, y);
	  }
  }
}

void morpho_SSE2_r1(vuint8 **vE, vuint8 **vOut,int vi0, int vi1, int vj0, int vj1, int vi0b, int vi1b, int vj0b, int vj1b){

    vuint8 **vinter1, **vinter2;
    vinter1  = vui8matrix(vi0b, vi1b, vj0b, vj1b);
    vinter2  = vui8matrix(vi0b, vi1b, vj0b, vj1b);

    zero_vui8matrix(vinter1, vi0b, vi1b, vj0b, vj1b);
    zero_vui8matrix(vinter2, vi0b, vi1b, vj0b, vj1b);

    init_bord(vE,vi0,vi1,vj0,vj1,vj0b,vj1b);
    erosion_SSE2_r1(vE, vinter1, vi0, vi1, vj0, vj1);

    init_bord(vinter1,vi0,vi1,vj0,vj1,vj0b,vj1b);
    dilatation_SSE2_r1(vinter1, vinter2, vi0, vi1, vj0, vj1);

    init_bord(vinter2,vi0,vi1,vj0,vj1,vj0b,vj1b);
    dilatation_SSE2_r1(vinter2, vinter1, vi0, vi1, vj0, vj1);

    init_bord(vinter1,vi0,vi1,vj0,vj1,vj0b,vj1b);
    erosion_SSE2_r1(vinter1, vOut, vi0, vi1, vj0, vj1);

    free_vui8matrix(vinter1, vi0b, vi1b, vj0b, vj1b);
    free_vui8matrix(vinter2, vi0b, vi1b, vj0b, vj1b);
}

//SIMD pour b = 2
//Faire macro vec_and5
void erosion_SSE2_r2(vuint8 **vE, vuint8 **vOut, int vi0, int vi1, int vj0, int vj1){
  int i, j;
  vuint8 a0, a1, a2, a3, a4;
  vuint8 b0, b1, b2, b3, b4;
  vuint8 c0, c1, c2, c3, c4;

  vuint8 aa0, aa1, aa2, aa3, aa4;
  vuint8 bb0, bb1, bb2, bb3, bb4;
  vuint8 cc0, cc1, cc2, cc3, cc4;
  vuint8 dd0, dd1, dd2, dd3, dd4;
  vuint8 y;

  for(i = vi0; i <= vi1; i++){
    for(j = vj0; j <= vj1; j++){
      a0 = vec_load2(vE,i-2, j-1);
      a1 = vec_load2(vE,i-1, j-1);
      a2 = vec_load2(vE,i  , j-1);
      a3 = vec_load2(vE,i+1, j-1);
      a4 = vec_load2(vE,i+2, j-1);

      b0 = vec_load2(vE,i-2, j);
      b1 = vec_load2(vE,i-1, j);
      b2 = vec_load2(vE,i  , j);
      b3 = vec_load2(vE,i+1, j);
      b4 = vec_load2(vE,i+2, j);

      c0 = vec_load2(vE,i-2, j+1);
      c1 = vec_load2(vE,i-1, j+1);
      c2 = vec_load2(vE,i  , j+1);
      c3 = vec_load2(vE,i+1, j-1);
      c4 = vec_load2(vE,i+2, j-1);

      aa0 = vec_left2(a0,b0);
      bb0 = vec_left1(a0,b0);
      cc0 = vec_right1(b0,c0);
      dd0 = vec_right2(b0,c0);

      a0 = vec_and5(aa0,bb0,b0,cc0,dd0);

      aa1 = vec_left2(a1,b1);
      bb1 = vec_left1(a1,b1);
      cc1 = vec_right1(b1,c1);
      dd1 = vec_right2(b1,c1);

      a1 = vec_and5(aa1,bb1,b1,cc1,dd1);


      aa2 = vec_left2(a2,b2);
      bb2 = vec_left1(a2,b2);
      cc2 = vec_right1(b2,c2);
      dd2 = vec_right2(b2,c2);

      a2 = vec_and5(aa2,bb2,b2,cc2,dd2);

      aa3 = vec_left2(a3,b3);
      bb3 = vec_left1(a3,b3);
      cc3 = vec_right1(b3,c3);
      dd3 = vec_right2(b3,c3);

      a3 = vec_and5(aa3,bb3,b3,cc3,dd3);

      aa4 = vec_left2(a4,b4);
      bb4 = vec_left1(a4,b4);
      cc4 = vec_right1(b4,c4);
      dd4 = vec_right2(b4,c4);

      a4 = vec_and5(aa4,bb4,b4,cc4,dd4);

      y = vec_and5(a0,a1,a2,a3,a4);

      vec_store2(vOut, i, j, y);
    }
  }
}

void dilatation_SSE2_r2(vuint8 **vE, vuint8 **vOut, int vi0, int vi1, int vj0, int vj1){
  int i, j;
  vuint8 a0, a1, a2, a3, a4;
  vuint8 b0, b1, b2, b3, b4;
  vuint8 c0, c1, c2, c3, c4;

  vuint8 aa0, aa1, aa2, aa3, aa4;
  vuint8 bb0, bb1, bb2, bb3, bb4;
  vuint8 cc0, cc1, cc2, cc3, cc4;
  vuint8 dd0, dd1, dd2, dd3, dd4;
  vuint8 y;

  for(i = vi0; i <= vi1; i++){
    for(j = vj0; j <= vj1; j++){
      a0 = vec_load2(vE,i-2, j-1);
      a1 = vec_load2(vE,i-1, j-1);
      a2 = vec_load2(vE,i  , j-1);
      a3 = vec_load2(vE,i+1, j-1);
      a4 = vec_load2(vE,i+2, j-1);

      b0 = vec_load2(vE,i-2, j);
      b1 = vec_load2(vE,i-1, j);
      b2 = vec_load2(vE,i  , j);
      b3 = vec_load2(vE,i+1, j);
      b4 = vec_load2(vE,i+2, j);

      c0 = vec_load2(vE,i-2, j+1);
      c1 = vec_load2(vE,i-1, j+1);
      c2 = vec_load2(vE,i  , j+1);
      c3 = vec_load2(vE,i+1, j-1);
      c4 = vec_load2(vE,i+2, j-1);

      aa0 = vec_left2(a0,b0);
      bb0 = vec_left1(a0,b0);
      cc0 = vec_right1(b0,c0);
      dd0 = vec_right2(b0,c0);

      a0 = vec_or5(aa0,bb0,b0,cc0,dd0);

      aa1 = vec_left2(a1,b1);
      bb1 = vec_left1(a1,b1);
      cc1 = vec_right1(b1,c1);
      dd1 = vec_right2(b1,c1);

      a1 = vec_or5(aa1,bb1,b1,cc1,dd1);


      aa2 = vec_left2(a2,b2);
      bb2 = vec_left1(a2,b2);
      cc2 = vec_right1(b2,c2);
      dd2 = vec_right2(b2,c2);

      a2 = vec_or5(aa2,bb2,b2,cc2,dd2);

      aa3 = vec_left2(a3,b3);
      bb3 = vec_left1(a3,b3);
      cc3 = vec_right1(b3,c3);
      dd3 = vec_right2(b3,c3);

      a3 = vec_or5(aa3,bb3,b3,cc3,dd3);

      aa4 = vec_left2(a4,b4);
      bb4 = vec_left1(a4,b4);
      cc4 = vec_right1(b4,c4);
      dd4 = vec_right2(b4,c4);

      a4 = vec_or5(aa4,bb4,b4,cc4,dd4);

      y = vec_or5(a0,a1,a2,a3,a4);

      vec_store2(vOut, i, j, y);
    }
  }
}

void morpho_SSE2_r2(vuint8 **vE, vuint8 **vOut,int vi0, int vi1, int vj0, int vj1, int vi0b, int vi1b, int vj0b, int vj1b){

  vuint8 **vinter1, **vinter2;
  vinter1  = vui8matrix(vi0b, vi1b, vj0b, vj1b);
  vinter2  = vui8matrix(vi0b, vi1b, vj0b, vj1b);

  zero_vui8matrix(vinter1, vi0b, vi1b, vj0b, vj1b);
  zero_vui8matrix(vinter2, vi0b, vi1b, vj0b, vj1b);

  init_bord(vE,vi0,vi1,vj0,vj1,vj0b,vj1b);
  erosion_SSE2_r2(vE, vinter1, vi0, vi1, vj0, vj1);

  init_bord(vinter1,vi0,vi1,vj0,vj1,vj0b,vj1b);
  dilatation_SSE2_r2(vinter1, vinter2, vi0, vi1, vj0, vj1);

  init_bord(vinter2,vi0,vi1,vj0,vj1,vj0b,vj1b);
  dilatation_SSE2_r2(vinter2, vinter1, vi0, vi1, vj0, vj1);

  init_bord(vinter1,vi0,vi1,vj0,vj1,vj0b,vj1b);
  erosion_SSE2_r2(vinter1, vOut, vi0, vi1, vj0, vj1);

  free_vui8matrix(vinter1, vi0b, vi1b, vj0b, vj1b);
  free_vui8matrix(vinter2, vi0b, vi1b, vj0b, vj1b);
}


//Optimisation par rotaton des registre (RR)
void erosion_SSE2_rot(vuint8 **vE, vuint8 **vOut, int vi0, int vi1, int vj0, int vj1){
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

		printf("#################### i = %d ####################\n", i);

		for(j = 1; j <= vj1; j++){

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

			a0 = b0; a1 = b1; a2 = b2;
			b0 = c0; b1 = c1; b2 = c2;

			c0 = vec_load2(vE, i-1, j+1);
			c1 = vec_load2(vE, i, j+1);
			c2 = vec_load2(vE, i+1, j+1);
			printf("j = %d\n", j-1);
			vec_store2(vOut, i, j-1, y);
		}
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
		printf("j = %d\n", j-1);
		vec_store2(vOut, i, j-1, y);
  }
}

void dilatation_SSE2_rot(vuint8 **vE, vuint8 **vOut, int vi0, int vi1, int vj0, int vj1){
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
    //printf("#################### i = %d ####################\n", i);
    for(j = 1; j <= vj1; j++){

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

      a0 = b0; a1 = b1; a2 = b2;
      b0 = c0; b1 = c1; b2 = c2;

      c0 = vec_load2(vE, i-1, j+1);
      c1 = vec_load2(vE, i, j+1);
      c2 = vec_load2(vE, i+1, j+1);
      //printf("j = %d\n", j-1);
      vec_store2(vOut, i, j-1, y);
    }
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
    //printf("j = %d\n", j-1);
    vec_store2(vOut, i, j-1, y);
  }
}

void morpho_SSE2_rot(vuint8 **vE, vuint8 **vOut,int vi0, int vi1, int vj0, int vj1, int vi0b, int vi1b, int vj0b, int vj1b){

    vuint8 **vinter1, **vinter2;
    vinter1  = vui8matrix(vi0b, vi1b, vj0b, vj1b);
    vinter2  = vui8matrix(vi0b, vi1b, vj0b, vj1b);

    zero_vui8matrix(vinter1, vi0b, vi1b, vj0b, vj1b);
    zero_vui8matrix(vinter2, vi0b, vi1b, vj0b, vj1b);

    init_bord(vE,vi0,vi1,vj0,vj1,vj0b,vj1b);
    erosion_SSE2_rot(vE, vinter1, vi0, vi1, vj0, vj1);

    init_bord(vinter1,vi0,vi1,vj0,vj1,vj0b,vj1b);
    dilatation_SSE2_rot(vinter1, vinter2, vi0, vi1, vj0, vj1);

    init_bord(vinter2,vi0,vi1,vj0,vj1,vj0b,vj1b);
    dilatation_SSE2_rot(vinter2, vinter1, vi0, vi1, vj0, vj1);

    init_bord(vinter1,vi0,vi1,vj0,vj1,vj0b,vj1b);
    erosion_SSE2_rot(vinter1, vOut, vi0, vi1, vj0, vj1);

    free_vui8matrix(vinter1, vi0b, vi1b, vj0b, vj1b);
    free_vui8matrix(vinter2, vi0b, vi1b, vj0b, vj1b);
}


//Optimisation par rotation de registre +  reduction par colonne + déroulage de boucle
void erosion_SSE2_red(vuint8 **vE, vuint8 **vOut, int vi0, int vi1, int vj0, int vj1){
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

void dilatation_SSE2_red(vuint8 **vE, vuint8 **vOut, int vi0, int vi1, int vj0, int vj1){
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

void morpho_SSE2_red(vuint8 **vE, vuint8 **vOut,int vi0, int vi1, int vj0, int vj1, int vi0b, int vi1b, int vj0b, int vj1b){

	vuint8 **vinter1, **vinter2;
	vinter1  = vui8matrix(vi0b, vi1b, vj0b, vj1b);
	vinter2  = vui8matrix(vi0b, vi1b, vj0b, vj1b);

	zero_vui8matrix(vinter1, vi0b, vi1b, vj0b, vj1b);
	zero_vui8matrix(vinter2, vi0b, vi1b, vj0b, vj1b);

	init_bord(vE,vi0,vi1,vj0,vj1,vj0b,vj1b);
	erosion_SSE2_red(vE, vinter1, vi0, vi1, vj0, vj1);

  init_bord(vinter1,vi0,vi1,vj0,vj1,vj0b,vj1b);
  dilatation_SSE2_red(vinter1, vinter2, vi0, vi1, vj0, vj1);

  init_bord(vinter2,vi0,vi1,vj0,vj1,vj0b,vj1b);
  dilatation_SSE2_red(vinter2, vinter1, vi0, vi1, vj0, vj1);

  init_bord(vinter1,vi0,vi1,vj0,vj1,vj0b,vj1b);
  erosion_SSE2_red(vinter1, vOut, vi0, vi1, vj0, vj1);

  free_vui8matrix(vinter1, vi0b, vi1b, vj0b, vj1b);
  free_vui8matrix(vinter2, vi0b, vi1b, vj0b, vj1b);
}

//Optimisation fusion des operateur
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

    switch(r){
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
    erosion_SSE2_red(vE, vinter1, vi0, vi1, vj0, vj1);

    init_bord(vinter1,vi0,vi1,vj0,vj1,vj0b,vj1b);
    dilatation_fusion(vinter1, vinter2, vi0, vi1, vj0, vj1);

    init_bord(vinter2,vi0,vi1,vj0,vj1,vj0b,vj1b);
    erosion_SSE2_red(vinter2, vOut, vi0, vi1, vj0, vj1);

    free_vui8matrix(vinter1, vi0b, vi1b, vj0b, vj1b);
    free_vui8matrix(vinter2, vi0b, vi1b, vj0b, vj1b);

}


//Optimisation pipeline en ligne, calcul utilisant erosion_SSE2_red et dilatation_fusion
void morpho_pipeline(vuint8 **vE, vuint8 **vOut,int vi0, int vi1, int vj0, int vj1, int vi0b, int vi1b, int vj0b, int vj1b){

    vuint8 vcst;
    vuint8 **X, **Y;
    X  = vui8matrix(vi0b, vi1b, vj0b, vj1b); //E->erosion->X
    Y  = vui8matrix(vi0b, vi1b, vj0b, vj1b); //X->dila_fusion->Y
    zero_vui8matrix(X, vi0b, vi1b, vj0b, vj1b);
    zero_vui8matrix(Y, vi0b, vi1b, vj0b, vj1b);

    init_bord(vE,vi0,vi1,vj0,vj1,vj0b,vj1b);// bord vertical et orizontal(2)
    #pragma omp for
    //bord haut
    for(int j = vj0b; j <= vj1b; j++){
      vcst = vec_load2(vE,0,j); vec_store2(vE,-3,j,vcst); vec_store2(vE,-4,j,vcst);
    }

    //prologue X[-3~2] Y[-1~0]
    erosion_SSE2_red(vE,X,-3,2,vj0,vj1);
    dilatation_fusion(X,Y,-1,0,vj0,vj1);
    #pragma omp for
    //pipeline en ligne
    for(int i=0;i<=vi1-4;i++){
      erosion_SSE2_red(vE,X,i+3,i+3,vj0,vj1);
      dilatation_fusion(X,Y,i+1,i+1,vj0,vj1);
      erosion_SSE2_red(Y,vOut,i,i,vj0,vj1);
    }
    #pragma omp for
    //bord bas
    for(int j = vj0b; j <= vj1b; j++){
      vcst = vec_load2(vE,vi1,j); vec_store2(vE,vi1+3,j,vcst); vec_store2(vE,vi1+4,j,vcst);
    }

    //epilogue X[vi1~vi1+3] Y[vi1-2~vi1+1] vOut[vi1-3~vi1]
    erosion_SSE2_red(vE,X,vi1,vi1+3,vj0,vj1);
    dilatation_fusion(X,Y,vi1-2,vi1+1,vj0,vj1);
    erosion_SSE2_red(Y,vOut,vi1-3,vi1,vj0,vj1);

    free_vui8matrix(X, vi0b, vi1b, vj0b, vj1b);
    free_vui8matrix(Y, vi0b, vi1b, vj0b, vj1b);
}
