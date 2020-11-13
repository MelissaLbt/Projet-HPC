/* --------------------- */
/* --- morpho_SIMD.h --- */
/* --------------------- */

#ifndef __MORPHO_SIMD_H__
#define __MORPHO_SIMD_H__


//#define vec_load2(T,i,j)  	_mm_load_si128 ((vuint8*) &T[i][j])    mis dans  vnrutil.h
//#define vec_store2(T,i,j,x) _mm_store_si128((vuint8*) &T[i][j], x)
#define vec_extractl(v) _mm_extract_epi16(_mm_srli_si128(v,15),0)
#define vec_extractr(v) _mm_extract_epi16(_mm_srli_si128(_mm_slli_si128(v,15),15),0)

#define vec_right1(v1, v2) _mm_or_si128(_mm_slli_si128(v1,1),_mm_srli_si128(v2,15))
#define vec_right2(v1, v2) _mm_or_si128(_mm_slli_si128(v1,2),_mm_srli_si128(v2,14))

#define vec_left1(v0, v1) _mm_or_si128(_mm_slli_si128(v0,15),_mm_srli_si128(v1,1))
#define vec_left2(v0, v1) _mm_or_si128(_mm_slli_si128(v0,14),_mm_srli_si128(v1,2))

#define vec_or3(v0,v1,v2)	 _mm_or_si128 (_mm_or_si128 (v0,v1),v2)
#define vec_and3(v0,v1,v2) _mm_and_si128(_mm_and_si128(v0,v1),v2)

//#define vMIN3(v0, v1, v2) _mm_min_epu8(v0, _mm_min_epu8(v1, v2))
//#define vMAX3(v0, v1, v2) _mm_max_epu8(v0, _mm_max_epu8(v1, v2))
//#define vMIN5(v0, v1, v2, v3, v4) _mm_min_epu8(v0, _mm_min_epu8(v1, _mm_min_epu8(v2, _mm_min_epu8(v3, v4))))
//#define vMAX5(v0, v1, v2, v3, v4) _mm_max_epu8(v0, _mm_max_epu8(v1, _mm_max_epu8(v2, _mm_max_epu8(v3, v4))))

void init_bord(vuint8 **vE,int vi0,int vi1,int vj0,int vj1,int vj0b,int vj1b);

void erosion_SIMD(vuint8 **vE, vuint8 **vOut, int vi0, int vi1, int vj0, int vj1);
void erosion_SIMD_red(vuint8 **vE, vuint8 **vOut, int vi0, int vi1, int vj0, int vj1);
void erosion2_SIMD(vuint8 **vE, int n, vuint8 **vOut);


void dilatation_SIMD(vuint8 **vE, vuint8 **vOut, int vi0, int vi1, int vj0, int vj1);
void dilatation_SIMD_red(vuint8 **vE, vuint8 **vOut, int vi0, int vi1, int vj0, int vj1);
void dilatation2_SIMD(vuint8 **vE, int n, vuint8 **vOut);

void morpho_SIMD(vuint8 **vE, vuint8 **vOut,int vi0, int vi1, int vj0, int vj1, int vi0b, int vi1b, int vj0b, int vj1b);

#endif
