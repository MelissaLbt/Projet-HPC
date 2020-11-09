/* Algorithme Morphologie version SIMD */

#include <stdio.h>
#include <stdlib.h>

#include "nrdef.h"
#include "nrutil.h"

#include "vnrdef.h"
#include "vnrutil.h"

#include "mutil.h"

#include "morpho_SIMD.h"

/* --------------------- */
/* E: Image d'entree     */
/* I: Image avec bord    */
/* img: Image de sortie  */
/* --------------------- */

//SOUCIS AVEC LES FONCTIONS SSE2 --> UTILISER SSE3
void erosion_r1(vuint8 **vE, int n, vuint8 **vOut){
  int i, j;
  vuint8 a0, b0, c0;
  vuint8 a1, b1, c1;
  vuint8 a2, b2, c2;

  vuint8 aa0, cc0;
  vuint8 aa1, cc1;
  vuint8 aa2, cc2;
  vuint8 y;

  for(i = 0; i< n; i++){

    a0 = _mm_load_ps((float*) &vE[i-1][-1]);
    a1 = _mm_load_ps((float*) &vE[i  ][-1]);
    a2 = _mm_load_ps((float*) &vE[i+1][-1]);

    b0 = _mm_load_ps((float*) &vE[i-1][0]);
    b1 = _mm_load_ps((float*) &vE[i  ][0]);
    b2 = _mm_load_ps((float*) &vE[i+1][0]);

    c0 = _mm_load_ps((float*) &vE[i-1][1]);
    c1 = _mm_load_ps((float*) &vE[i  ][1]);
    c2 = _mm_load_ps((float*) &vE[i+1][1]);

    for(j = 2; j < n; j++){
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

      _mm_store_ps((uint8*) &vOut[i][j-2], y);

      a0 = b0;
      a1 = b1;
      a2 = b2;
      b0 = c0;
      b1 = c1;
      b2 = c2;
      c0 = _mm_load_ps((uint8*) &vE[i-1][j]);
      c1 = _mm_load_ps((uint8*) &vE[i  ][j]);
      c2 = _mm_load_ps((uint8*) &vE[i+1][j]);
    }
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
    _mm_store_ps((uint8*) &vOut[i][239], y);
  }
}

void erosion_r2(vuint8 **vE, int n, vuint8 **vOut){
  int i, j;
  vuint8 a0, b0, c0, d0, e0;
  vuint8 a1, b1, c1, d1, e1;
  vuint8 a2, b2, c2, d2, e2;
  vuint8 a3, b3, c3, d3, e3;
  vuint8 a4, b4, c4, d4, e4;
  vuint8 xx0,xx1,xx2,xx3,xx4;
  vuint8 ff0,ff1,ff2,ff3,ff4;

  for(i = 0; i < n; i++){
    b0 = _mm_load_ps((uint8*) &vE[i-2][-2]);
    b1 = _mm_load_ps((uint8*) &vE[i-1][-2]);
    b2 = _mm_load_ps((uint8*) &vE[i  ][-2]);
    b3 = _mm_load_ps((uint8*) &vE[i+1][-2]);
    b4 = _mm_load_ps((uint8*) &vE[i+2][-2]);

    c0 = _mm_load_ps((uint8*) &vE[i-2][-1]);
    c1 = _mm_load_ps((uint8*) &vE[i-1][-1]);
    c2 = _mm_load_ps((uint8*) &vE[i  ][-1]);
    c3 = _mm_load_ps((uint8*) &vE[i+1][-1]);
    c4 = _mm_load_ps((uint8*) &vE[i+2][-1]);

    d0 = _mm_load_ps((uint8*) &vE[i-2][0]);
    d1 = _mm_load_ps((uint8*) &vE[i-1][0]);
    d2 = _mm_load_ps((uint8*) &vE[i  ][0]);
    d3 = _mm_load_ps((uint8*) &vE[i+1][0]);
    d4 = _mm_load_ps((uint8*) &vE[i+2][0]);

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
      _mm_store_ps((uint8*) &vOut[i][j-1], y);

      b0 = c0; b1 = c1; b2 = c2; b3 = c3; b4 = c4;
      c0 = d0; c1 = d1; c2 = d2; c3 = d3; c4 = d4;

      d0 = _mm_load_ps((uint8*) &vE[i-2][j]);
      d1 = _mm_load_ps((uint8*) &vE[i-1][j]);
      d2 = _mm_load_ps((uint8*) &vE[i  ][j]);
      d3 = _mm_load_ps((uint8*) &vE[i+1][j]);
      d4 = _mm_load_ps((uint8*) &vE[i+2][j]);
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
    _mm_store_ps((uint8*) &vOut[i][239], y);
  }
}

void dilatation_r1(vuint8 **vE, int n, vuint8 **vOut){
  int i, j;
  vuint8 a0, b0, c0;
  vuint8 a1, b1, c1;
  vuint8 a2, b2, c2;

  vuint8 aa0, cc0;
  vuint8 aa1, cc1;
  vuint8 aa2, cc2;
  vuint8 y;

  for(i = 0; i< n; i++){

    a0 = _mm_load_ps((uint8*) &vE[i-1][-1]);
    a1 = _mm_load_ps((uint8*) &vE[i  ][-1]);
    a2 = _mm_load_ps((uint8*) &vE[i+1][-1]);

    b0 = _mm_load_ps((uint8*) &vE[i-1][0]);
    b1 = _mm_load_ps((uint8*) &vE[i  ][0]);
    b2 = _mm_load_ps((uint8*) &vE[i+1][0]);

    c0 = _mm_load_ps((uint8*) &vE[i-1][1]);
    c1 = _mm_load_ps((uint8*) &vE[i  ][1]);
    c2 = _mm_load_ps((uint8*) &vE[i+1][1]);

    for(j = 2; j < n; j++){
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

      _mm_store_ps((float*) &vOut[i][j-2], y);

      a0 = b0;
      a1 = b1;
      a2 = b2;
      b0 = c0;
      b1 = c1;
      b2 = c2;
      c0 = _mm_load_ps((uint8*) &vE[i-1][j]);
      c1 = _mm_load_ps((uint8*) &vE[i  ][j]);
      c2 = _mm_load_ps((uint8*) &vE[i+1][j]);
    }
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
    _mm_store_ps((float*) &vOut[i][239], y);
  }
}

void dilatation_r2(vuint8 **vE, int n, vuint8 **vOut){
  int i, j;
  vuint8 a0, b0, c0, d0, e0;
  vuint8 a1, b1, c1, d1, e1;
  vuint8 a2, b2, c2, d2, e2;
  vuint8 a3, b3, c3, d3, e3;
  vuint8 a4, b4, c4, d4, e4;
  vuint8 xx0,xx1,xx2,xx3,xx4;
  vuint8 ff0,ff1,ff2,ff3,ff4;

  for(i = 0; i < n; i++){
    b0 = _mm_load_ps((uint8*) &vE[i-2][-2]);
    b1 = _mm_load_ps((uint8*) &vE[i-1][-2]);
    b2 = _mm_load_ps((uint8*) &vE[i  ][-2]);
    b3 = _mm_load_ps((uint8*) &vE[i+1][-2]);
    b4 = _mm_load_ps((uint8*) &vE[i+2][-2]);

    c0 = _mm_load_ps((uint8*) &vE[i-2][-1]);
    c1 = _mm_load_ps((uint8*) &vE[i-1][-1]);
    c2 = _mm_load_ps((uint8*) &vE[i  ][-1]);
    c3 = _mm_load_ps((uint8*) &vE[i+1][-1]);
    c4 = _mm_load_ps((uint8*) &vE[i+2][-1]);

    d0 = _mm_load_ps((uint8*) &vE[i-2][0]);
    d1 = _mm_load_ps((uint8*) &vE[i-1][0]);
    d2 = _mm_load_ps((uint8*) &vE[i  ][0]);
    d3 = _mm_load_ps((uint8*) &vE[i+1][0]);
    d4 = _mm_load_ps((uint8*) &vE[i+2][0]);

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
      _mm_store_ps((uint8*) &vOut[i][j-1], y);

      b0 = c0; b1 = c1; b2 = c2; b3 = c3; b4 = c4;
      c0 = d0; c1 = d1; c2 = d2; c3 = d3; c4 = d4;

      d0 = _mm_load_ps((uint8*) &vE[i-2][j]);
      d1 = _mm_load_ps((uint8*) &vE[i-1][j]);
      d2 = _mm_load_ps((uint8*) &vE[i  ][j]);
      d3 = _mm_load_ps((uint8*) &vE[i+1][j]);
      d4 = _mm_load_ps((uint8*) &vE[i+2][j]);
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
    _mm_store_ps((uint8*) &vOut[i][239], y);
  }
}

void ouverture(vuint8 **vE, vuint8 **vOut, int n, int b, int vi0, int vi1, int vj0, int vj1){

  vuint8 **vintermediaire;
  zero_vui8matrix(vintermediaire, vi0, vi1, vj0, vj1);

  if(b == 1){
    erosion_r1(vE, n, vintermediaire);
    dilatation_r1(vintermediaire, n, vOut);
  }
  else if(b == 2){
    erosion_r2(vE, n, vintermediaire);
    dilatation_r2(vintermediaire, n, vOut);
  }

  free_vui8matrix(vintermediaire, vi0, vi1, vj0, vj1);
}

void fermeture(vuint8 **vE, vuint8 **vOut, int n, int b, int vi0, int vi1, int vj0, int vj1){

  vuint8 **vintermediaire;
  zero_vui8matrix(vintermediaire, vi0, vi1, vj0, vj1);

  if(b == 1){
    dilatation_r1(vE, n, vintermediaire);
    erosion_r1(vintermediaire, n, vOut);
  }
  else if(b == 2){
    dilatation_r2(vE, n, vintermediaire);
    erosion_r2(vintermediaire, n, vOut);
  }

  free_vui8matrix(vintermediaire, vi0, vi1, vj0, vj1);
}

void morpho(vuint8 **vE, vuint8 **vOut, int n, int b, int vi0, int vi1, int vj0, int vj1){

  vuint8 **vintermediaire;
  zero_vui8matrix(vintermediaire, vi0, vi1, vj0, vj1);

	ouverture(vE, vintermediaire, n, b, vi0, vi1, vj0, vj1);
	fermeture(vintermediaire, vOut, n, b, vi0, vi1, vj0, vj1);


  free_vui8matrix(vintermediaire, vi0, vi1, vj0, vj1);
}
