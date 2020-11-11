/* ------------------------ */
/* --- mouvement_SIMD.h --- */
/* ------------------------ */

#ifndef __MOUVEMENT_SIMD_H__
#define __MOUVEMENT_SIMD_H__


//#define vec_load2(T,i,j)  	_mm_load_si128((vuint8*) &T[i][j])  mis dans  vnrutil.h
//#define vec_store2(T,i,j,x) _mm_store_si128((vuint8*) &T[i][j], x)

#define vec_set(x)  		_mm_set1_epi8(x)
#define vec_add2(x,y) 		_mm_add_epi8(x,y)
#define vec_sub2(x,y) 		_mm_sub_epi8(x,y)
#define vec_absd(x,y) 		_mm_sub_epi8(_mm_max_epu8(x,y),_mm_min_epu8(x,y))

#define vec_lt(x,y) 		_mm_cmplt_epi8(_mm_add_epi8(x, _mm_set1_epi8((char)0x80)), _mm_add_epi8(y, _mm_set1_epi8((char)0x80)))
#define vec_gt(x,y) 		_mm_cmpgt_epi8(_mm_add_epi8(x, _mm_set1_epi8((char)0x80)), _mm_add_epi8(y, _mm_set1_epi8((char)0x80)))
#define vec_eq(x,y) 		_mm_cmpeq_epi8(x,y)

#define vec_sel2(a,b,m)      _mm_or_si128(_mm_and_si128(m,a),_mm_andnot_si128(m,b))
#define vec_sel3(a,b,c,m1,m2,m3) vec_or3(_mm_and_si128(m1,a),_mm_and_si128(m2,b),_mm_and_si128(m3,c))
#define vec_or3(x1,x2,x3)   _mm_or_si128(_mm_or_si128(x1,x2),x3)


void SigmaDelta_step0_SIMD(vuint8 **I, vuint8 **M, vuint8 **V, int vi0, int vi1, int vj0, int vj1);
void SigmaDelta_1step_SIMD(vuint8 **I, vuint8 **M0, vuint8 **V0, vuint8 **E, int vi0, int vi1, int vj0, int vj1);

#endif
