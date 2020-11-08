/* --------------------- */
/* --- mouvement_SIMD.h --- */
/* --------------------- */

#ifndef __MOUVEMENT_SIMD_H__
#define __MOUVEMENT_SIMD_H__

#define vec_set(x)  		_mm_set1_epi8(x)
#define vec_cset(x,m,y)   	_mm_maskmoveu_si128(x,m,(char*)&y)
#define vec_load2(T,i,j)  	_mm_load_si128((vuint8*) &T[i][j])
#define vec_store2(T,i,j,x) _mm_store_si128((vuint8*) &T[i][j], x)

#define vec_add2(x,y) 		_mm_add_epi8(x,y)
#define vec_sub2(x,y) 		_mm_sub_epi8(x,y)
#define vec_absd(x,y) 		_mm_sub_epi8(_mm_max_epu8(x,y),_mm_min_epu8(x,y))

#define vec_lt(x,y) 		_mm_xor_si128(_mm_cmpeq_epi8(_mm_max_epu8(x, y), x), _mm_set1_epi8(-1))
#define vec_gt(x,y) 		_mm_xor_si128(_mm_cmpeq_epi8(_mm_min_epu8(x, y), x), _mm_set1_epi8(-1))
#define vec_notmask(x)  	_mm_xor_si128(x, _mm_set1_epi8(-1))
#define vec_eq(x,y) 		_mm_cmpeq_epi8(x,y)

void SigmaDelta_step0_SIMD(vuint8 **I, vuint8 **M, vuint8 **V, int vi0, int vi1, int vj0, int vj1);
void SigmaDelta_1step_SIMD(vuint8 **I, vuint8 **M0, vuint8 **M1, vuint8 **O, vuint8 **V0, vuint8 **V1, vuint8 **E, int vi0, int vi1, int vj0, int vj1);

#endif
