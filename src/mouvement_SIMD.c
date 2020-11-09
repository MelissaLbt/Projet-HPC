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
		}
	}
}

void SigmaDelta_1step_SIMD(vuint8 **I, vuint8 **M0, vuint8 **V0, vuint8 **E, int vi0, int vi1, int vj0, int vj1){
	
	int i,j;
	vuint8 cst1, mask, N_o;
	vuint8 m0, m1, v0, v1, i1, o, e;
	vuint8 x1, x2, x3;

	cst1 = vec_set(1);

	for(i=vi0;i<=vi1; i++){
		for(j=vj0; j<=vj1; j++){

			m0 = vec_load2(M0, i, j);
			i1 = vec_load2(I, i, j);
			v0  = vec_load2(V0, i, j);

			//---- step 1: Mt estimation ----//

 			mask = vec_lt(m0,i1);
			x1 	 = vec_setmask(vec_add2(m0, cst1),mask);
			mask = vec_gt(m0,i1);
			x2   = vec_setmask(vec_sub2(m0, cst1),mask);
			mask = vec_eq(m0,i1);
			x3   = vec_setmask(m0,mask);
			m1   = _mm_or_si128(_mm_or_si128(x1,x2),x3);

			//---- step 2: Ot difference computation ----//
			o  = vec_absd(m1,i1);

			//---- step 3: Vt update ----//
			N_o = vec_add2(o, o);

			mask = vec_lt(v0,N_o);
			x1   = vec_setmask(vec_add2(v0, cst1),mask);
			mask = vec_gt(v0,N_o);
			x2   = vec_setmask(vec_sub2(v0, cst1),mask);
			mask = vec_eq(v0,N_o);
			x3   = vec_setmask(v0,mask);
			v1   = _mm_or_si128(_mm_or_si128(x1,x2),x3);

			v1 = _mm_max_epu8(_mm_min_epu8(v1,vec_set(VMAX)), vec_set(VMIN));

			//---- step 4 : Et estimation ----//
			mask = vec_lt(o,v1);
			x1   = vec_setmask(vec_set(0),mask);
			mask = vec_ge(o,v1);
			x2   = vec_setmask(vec_set(255),mask);
			e    = _mm_or_si128(x1,x2);
			
			vec_store2(E, i, j, e);
			//vec_store2(V1, i, j, v1);
			vec_store2(V0, i, j, v1);			
			//vec_store2(O, i, j, o);
			//vec_store2(M1, i, j, m1);
			vec_store2(M0, i, j, m1);

		}
	}

}