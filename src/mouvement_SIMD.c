/* Algorithme Sigma-Delta version SIMD */

#include <stdio.h>
#include <stdlib.h>

#include "nrdef.h"
#include "nrutil.h"

#include "vnrdef.h"
#include "vnrutil.h"

#include "mutil.h"

#include "mouvement_SIMD.h"

void SigmaDelta_step0_SIMD(vuint8 **I, vuint8 **M, vuint8 **V, int vi0, int vi1, int vj0, int vj1){
	
	int i,j;
	vuint8 tmp,vmin;

	vmin = vec_set(VMIN);

	for(i=vi0;i<=vi1; i++){
		for(j=vj0; j<=vj1; j++){

			tmp = vec_load2(I, i, j);
			vec_store2(M, i, j, tmp);

			vec_store2(V, i, j, vmin);
			//M[i][j] = I[i][j];
			//V[i][j] = VMIN;
		}
	}
}

void SigmaDelta_1step_SIMD(vuint8 **I, vuint8 **M0, vuint8 **M1, vuint8 **O, vuint8 **V0, vuint8 **V1, vuint8 **E, int vi0, int vi1, int vj0, int vj1){
	
	int i,j;
	vuint8 cst1, mask, N_o;
	vuint8 m0, m1, v0, v1, i1, o, e;

	cst1 = vec_set(1);

	//step 1: Mt estimation
	for(i=vi0;i<=vi1; i++){
		for(j=vj0; j<=vj1; j++){
			m0 = vec_load2(M0, i, j);
			i1 = vec_load2(I, i, j);
 
			mask = vec_lt(m0,i1);
			vec_cset(vec_add2(m0, cst1),mask,m1);

			mask = vec_gt(m0,i1);
			vec_cset(vec_sub2(m0, cst1),mask,m1);
			
			mask = vec_eq(m0,i1);
			vec_cset(m0,mask,m1);
			
			vec_store2(M1, i, j, m1);
		}
	}

	//step 2: Ot difference computation
	for(i=vi0;i<=vi1; i++){
		for(j=vj0; j<=vj1; j++){

			m1 = vec_load2(M1, i, j);
			i1 = vec_load2(I, i, j);
			o  = vec_absd(m1,i1);
			vec_store2(O, i, j, o);
		}
	}

	//step 3: Vt update
	for(i=vi0;i<=vi1; i++){
		for(j=vj0; j<=vj1; j++){

			v0  = vec_load2(V0, i, j);
			o   = vec_load2(O, i, j);
			N_o = vec_add2(o, o);

			mask = vec_lt(v0,N_o);
			vec_cset(vec_add2(v0, cst1),mask,v1);

			mask = vec_gt(v0,N_o);
			vec_cset(vec_sub2(v0, cst1),mask,v1);
			
			mask = vec_eq(v0,N_o);
			vec_cset(v0,mask,v1);


			v1 = _mm_max_epu8(_mm_min_epu8(v1,vec_set(VMAX)), vec_set(VMIN));
			vec_store2(V1, i, j, v1);
		}
	}

	//step 4 : Et estimation
	for(i=vi0;i<=vi1; i++){
		for(j=vj0; j<=vj1; j++){

			v1 = vec_load2(V1, i, j);
			o = vec_load2(O, i, j);

			mask = vec_lt(o,v1);
			vec_cset(vec_set(0),mask,e);

			mask = vec_notmask(mask);
			vec_cset(vec_set(255),mask,e);
			
			vec_store2(E, i, j, e);
		}
	}
}