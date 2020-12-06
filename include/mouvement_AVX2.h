/* --------------------- */
/* --- mouvement_AVX2.h --- */
/* --------------------- */

#ifndef __MOUVEMENT_AVX2_H__
#define __MOUVEMENT_AVX2_H__


// vnrutil.h
// #define vec256_load2(T,i,j)  _mm256_load_si256((lvuint8*) &T[i][j])
// #define vec256_store2(T,i,j,x) _mm256_store_si256((lvuint8*) &T[i][j], x)
// #define vec256_set(x) 		_mm256_set1_epi8(x)

// #define vec256_or3(v0,v1,v2)	 _mm256_or_si256 (_mm256_or_si256 (v0,v1),v2)
// #define vec256_and3(v0,v1,v2) _mm256_and_si256(_mm256_and_si256(v0,v1),v2)

#define vec256_add2(x,y) 		_mm256_adds_epu8(x,y)
#define vec256_sub2(x,y) 		_mm256_subs_epu8(x,y)
#define vec256_abs(x,y) 		_mm256_subs_epu8(_mm256_max_epu8(x,y),_mm256_min_epu8(x,y))

#define vec256_eq(x,y) 			_mm256_cmpeq_epi8(x,y)
#define vec256_ge(x,y)			vec256_eq(_mm256_max_epu8(x, y), x)
#define vec256_lt(x,y) 			_mm256_xor_si256(vec256_ge(x,y), _mm256_set1_epi8((char)0xff))
#define vec256_gt(x,y) 			vec256_lt(y,x)


#define vec256_sel2(a,b,m)      	_mm256_blendv_epi8(b,a,m)
#define vec256_sel3(a,b,c,m1,m2,m3) vec256_or3(_mm256_and_si256(m1,a),_mm256_and_si256(m2,b),_mm256_and_si256(m3,c))

void SigmaDelta_step0_AVX2(vuint8 **I, vuint8 **M, vuint8 **V, int vi0, int vi1, int vj0, int vj1);
void SigmaDelta_step0_AVX2_omp(vuint8 **I, vuint8 **M, vuint8 **V, int vi0, int vi1, int vj0, int vj1);
void SigmaDelta_1step_AVX2(vuint8 **I, vuint8 **M0, vuint8 **V0, vuint8 **E, int vi0, int vi1, int vj0, int vj1);
void SigmaDelta_1step_AVX2_omp(vuint8 **I, vuint8 **M0, vuint8 **V0, vuint8 **E, int vi0, int vi1, int vj0, int vj1);

#endif
