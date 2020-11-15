/* Algorithme Sigma-Delta version SSE2 */

#include <stdio.h>
#include <stdlib.h>

#include "nrdef.h"
#include "nrutil.h"

#include "vnrdef.h"
#include "vnrutil.h"

#include "mutil.h"

#include "mouvement_SSE2.h"

void SigmaDelta_step0_SSE2(vuint8 **I, vuint8 **M, vuint8 **V, int vi0, int vi1, int vj0, int vj1){

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

void SigmaDelta_1step_SSE2(vuint8 **I, vuint8 **M0, vuint8 **V0, vuint8 **E, int vi0, int vi1, int vj0, int vj1){

	int i,j;

	vuint8 cst1, vmax, vmin;
	vuint8 mask, ma, mb, mc;
	vuint8 m0, m1, v0, v1, i1, o, e;
	vuint8 x1, x2, x3;
	vuint8  N_o;

	cst1 = vec_set(1);
	vmax = vec_set(VMAX);
	vmin = vec_set(VMIN);

	for(i=vi0;i<=vi1; i++){
		for(j=vj0; j<=vj1; j++){

			i1  = vec_load2(I, i, j);
			m0  = vec_load2(M0, i, j);
			v0  = vec_load2(V0, i, j);

			//---- step 1: Mt estimation ----//

 			ma = vec_lt(m0,i1);
			mb = vec_gt(m0,i1);
			mc = vec_eq(m0,i1);

			m1   = vec_sel3(vec_add2(m0, cst1),vec_sub2(m0, cst1),m0,ma,mb,mc);

			vec_store2(M0, i, j, m1);

			//---- step 2: Ot difference computation ----//
			o  = vec_absd(m1,i1);

			//---- step 3: Vt update ----//
			N_o = vec_add2(o, o);

			ma = vec_lt(v0,N_o);
			mb = vec_gt(v0,N_o);
			mc = vec_eq(v0,N_o);

			v1   = vec_sel3(vec_add2(v0, cst1),vec_sub2(v0, cst1),v0,ma,mb,mc);
			v1 = _mm_max_epu8(_mm_min_epu8(v1,vmax), vmin);

			vec_store2(V0, i, j, v1);


			//---- step 4 : Et estimation ----//
			mask = vec_lt(o,v1);
			e = vec_sel2(vec_set(0),vec_set(255),mask);

			vec_store2(E, i, j, e);

		}
	}
}
