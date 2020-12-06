/* Algorithme Morphologie version AVX2 , AVX22 avec reduction... , avec fusion*/

#include <stdio.h>
#include <stdlib.h>

#include "nrdef.h"
#include "nrutil.h"

#include "vnrdef.h"
#include "vnrutil.h"

#include "mutil.h"

#include "mouvement_AVX2.h"
#include "mymacro.h"

void SigmaDelta_step0_AVX2(vuint8 **I, vuint8 **M, vuint8 **V, int vi0, int vi1, int vj0, int vj1){

	int i,j;
	lvuint8 tmp,vmin;

	vmin = vec256_set(VMIN);
	for(i=vi0;i<=vi1; i++){
		for(j=vj0; j<=vj1; j+=2){
			tmp = vec256_load2(I, i, j);
			vec256_store2(M, i, j, tmp);
			vec256_store2(V, i, j, vmin);
		}
	}
}

void SigmaDelta_step0_AVX2_omp(vuint8 **I, vuint8 **M, vuint8 **V, int vi0, int vi1, int vj0, int vj1){

	int i,j;
	lvuint8 tmp,vmin;

	vmin = vec256_set(VMIN);

	#pragma omp parallel for num_threads(8)
	for(i=vi0;i<=vi1; i++){
		for(j=vj0; j<=vj1; j+=2){
			tmp = vec256_load2(I, i, j);
			vec256_store2(M, i, j, tmp);
			vec256_store2(V, i, j, vmin);
		}
	}
}


//------------- SIMD(AVX2)+calcule par registre, fusion des 4 steps
void SigmaDelta_1step_AVX2(vuint8 **I, vuint8 **M0, vuint8 **V0, vuint8 **E, int vi0, int vi1, int vj0, int vj1){

	int i,j;

	lvuint8 cst1, vmax, vmin;
	lvuint8 mask, ma, mb, mc;
	lvuint8 m0, m1, v0, v1, i1, o, e;
	lvuint8 x1, x2, x3;
	lvuint8  N_o;

	cst1 = vec256_set(1);
	vmax = vec256_set(VMAX);
	vmin = vec256_set(VMIN);
	
	#pragma omp parallel for num_threads(8)
	for(i=vi0;i<=vi1; i++){
		for(j=vj0; j<=vj1; j+=2){

			i1  = vec256_load2(I, i, j);
			m0  = vec256_load2(M0, i, j);
			v0  = vec256_load2(V0, i, j);

			//---- step 1: Mt estimation ----//

 			ma = vec256_lt(m0,i1);
			mb = vec256_gt(m0,i1);
			mc = vec256_eq(m0,i1);

			m1   = vec256_sel3(vec256_add2(m0, cst1),vec256_sub2(m0, cst1),m0,ma,mb,mc);

			vec256_store2(M0, i, j, m1);

			//---- step 2: Ot difference computation ----//
			o  = vec256_abs(m1,i1);

			//---- step 3: Vt update ----//
			N_o = vec256_add2(o, o);

			ma = vec256_lt(v0,N_o);
			mb = vec256_gt(v0,N_o);
			mc = vec256_eq(v0,N_o);

			v1   = vec256_sel3(vec256_add2(v0, cst1),vec256_sub2(v0, cst1),v0,ma,mb,mc);
			v1 = _mm256_max_epu8(_mm256_min_epu8(v1,vmax), vmin);

			vec256_store2(V0, i, j, v1);


			//---- step 4 : Et estimation ----//
			mask = vec256_lt(o,v1);
			e = vec256_sel2(vec256_set(0),vec256_set(255),mask);

			vec256_store2(E, i, j, e);

		}
	}
}


void SigmaDelta_1step_AVX2_omp(vuint8 **I, vuint8 **M0, vuint8 **V0, vuint8 **E, int vi0, int vi1, int vj0, int vj1){

	int i,j;

	lvuint8 cst1, vmax, vmin;
	lvuint8 mask, ma, mb, mc;
	lvuint8 m0, m1, v0, v1, i1, o, e;
	lvuint8 x1, x2, x3;
	lvuint8  N_o;

	cst1 = vec256_set(1);
	vmax = vec256_set(VMAX);
	vmin = vec256_set(VMIN);

	for(i=vi0;i<=vi1; i++){
		for(j=vj0; j<=vj1; j+=2){

			i1  = vec256_load2(I, i, j);
			m0  = vec256_load2(M0, i, j);
			v0  = vec256_load2(V0, i, j);

			//---- step 1: Mt estimation ----//

 			ma = vec256_lt(m0,i1);
			mb = vec256_gt(m0,i1);
			mc = vec256_eq(m0,i1);

			m1   = vec256_sel3(vec256_add2(m0, cst1),vec256_sub2(m0, cst1),m0,ma,mb,mc);

			vec256_store2(M0, i, j, m1);

			//---- step 2: Ot difference computation ----//
			o  = vec256_abs(m1,i1);

			//---- step 3: Vt update ----//
			N_o = vec256_add2(o, o);

			ma = vec256_lt(v0,N_o);
			mb = vec256_gt(v0,N_o);
			mc = vec256_eq(v0,N_o);

			v1   = vec256_sel3(vec256_add2(v0, cst1),vec256_sub2(v0, cst1),v0,ma,mb,mc);
			v1 = _mm256_max_epu8(_mm256_min_epu8(v1,vmax), vmin);

			vec256_store2(V0, i, j, v1);


			//---- step 4 : Et estimation ----//
			mask = vec256_lt(o,v1);
			e = vec256_sel2(vec256_set(0),vec256_set(255),mask);

			vec256_store2(E, i, j, e);

		}
	}
}
