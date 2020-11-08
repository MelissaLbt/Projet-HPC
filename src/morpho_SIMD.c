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

/* Idées :
 - Faire des threads pour paralléliser le traitement des images.
 - Utiliser SIMD2D pour écrire morpho_SIMD
 - 1 tableau qui contient l'adresse des lignes du tableau
 - Plusieurs tableaux qui contient les valeurs d'une ligne du tableau

Fonctions à utiliser :
- vuint8   **vui8matrix_map (int nrl, int nrh, int ncl, int nch);
- void free_vui8matrix_map (vuint8   **m, int nrl, int nrh, int ncl, int nch);
- vuint8**    vui8matrix_map_1D_pitch(vuint8   **m, int nrl, int nrh, int ncl, int nch, void *data_1D, int pitch);
- void zero_vui8vector(vuint8 *m, int j0, int j1); (après c'est en 1D)
- void init_vui8matrix_param (vuint8   **m, int i0, int i1, int j0, int j1, uint8   x0, uint8   xstep, uint8   ystep);
- void zero_vui8matrix (vuint8   **m, int i0, int i1, int j0, int j1);

*/



/*
MACRO vMIN3, vMAX3, vMAX5, VMIN5 à faire !!!
*/

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

      a0 = vMIN3(aa0,b0,cc0);

      aa1 = vec_left1(a1,b1);
      cc1 = vec_right1(b1,c1);

      a1 = vMIN3(aa1,b1,cc1);

      aa2 = vec_left1(a2,b2);
      cc2 = vec_right1(b2,c2);

      a2 = vMIN3(aa2,b2,cc2);

      y = vMIN3(a0,a1,a2);

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

    a0 = vMIN3(aa0,b0,cc0);

    aa1 = vec_left1(a1,b1);
    cc1 = vec_right1(b1,c1);

    a1 = vMIN3(aa1,b1,cc1);

    aa2 = vec_left1(a2,b2);
    cc2 = vec_right1(b2,c2);

    a2 = vMIN3(aa2,b2,cc2);

    y = vMIN3(a0,a1,a2);
    _mm_store_ps((float*) &vOut[i][239], y);
  }
}

void erosion_r2(vuint8 **vE, int n, vuint8 **vOut){
  int i, j;
  vuint8 a0, b0, c0, d0, e0;
  vuint8 a1, b1, c1, d1, e1;
  vuint8 a2, b2, c2, d2, e2;
  vuint8 a3, b3, c3, d3, e3;
  vuint8 a4, b4, c4, d4, e4;
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

void dilatation_r2(vuint8 **vE, int n, vuint8 vOut){
  int i, j;
  vuint8 a0, b0, c0;
  vuint8 a1, b1, c1;
  vuint8 a2, b2, c2;
  vuint8 a3, b3, c3;
  vuint8 a4, b4, c4;
  vuint8 ra, rb, rc;
  vuint8 xx0, xx1, xx3, xx4;
  vuint8 y;
}

void ouverture_r1(vuint8 **vE, vuint8 **vOut, int n, int vi0, int vi1, int vj0, int vj1){

  vuint8 **vintermediaire;
  vintermediaire = zero_vui8matrix(vi0, vi1, vj0, vj1);

  erosion_r1(vE, n, vintermediaire);
  dilatation_r1(vintermediaire, n, vOut);

  free_vui8matrix(intermediaire, vi0, vi1, vj0, vj1);
}

void ouverture_r2(vuint8 **vE, vuint8 **vOut, int n, int vi0, int vi1, int vj0, int vj1){

  vuint8 **vintermediaire;
  vintermediaire = zero_vui8matrix(vi0, vi1, vj0, vj1);

  erosion_r2(vE, n, vintermediaire);
  dilatation_r2(vintermediaire, n, vOut);

  free_vui8matrix(intermediaire, vi0, vi1, vj0, vj1);
}

void fermeture_r1(vuint8 **vE, vuint8 **vOut, int n, int vi0, int vi1, int vj0, int vj1){

  vuint8 **vintermediaire;
  vintermediaire = zero_vui8matrix(vi0, vi1, vj0, vj1);

  dilatation_r1(vE, n, vintermediaire);
  erosion_r1(vintermediaire, n, vOut);

  free_vui8matrix(intermediaire, vi0, vi1, vj0, vj1);
}

void fermeture_r2(vuint8 **vE, vuint8 **vOut, int n, int vi0, int vi1, int vj0, int vj1){

  vuint8 **vintermediaire;
  vintermediaire = zero_vui8matrix(vi0, vi1, vj0, vj1);

  dilatation_r2(vE, n, vintermediaire);
  erosion_r2(vintermediaire, n, vOut);

  free_vui8matrix(intermediaire, vi0, vi1, vj0, vj1);
}

void morpho(vuint8 **vE, vuint8 **vOut, int n, int vi0, int vi1, int vj0, int vj1){

  vuint8 **vintermediaire;
  vintermediaire = zero_vui8matrix(vi0, vi1, vj0, vj1);

  if(b == 1){
		ouverture_r1(vE, vintermediaire, n, vi0, vi1, vj0, vj1);
		fermeture_r1(vintermediaire, vOut, n, vi0, vi1, vj0, vj1);
	}
	else if(b == 2){
		ouverture_r2(vE, vintermediaire, n, vi0, vi1, vj0, vj1);
		fermeture_r2(vintermediaire, vOut, n, vi0, vi1, vj0, vj1);
	}

  free_vui8matrix(vintermediaire, vi0, vi1, vj0, vj1);
}
