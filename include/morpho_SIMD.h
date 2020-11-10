/* --------------------- */
/* --- morpho_SIMD.h --- */
/* --------------------- */

#ifndef __MORPHO_SIMD_H__
#define __MORPHO_SIMD_H__


//#define vec_load2(T,i,j)  	_mm_load_si128 ((vuint8*) &T[i][j])    mis dans  vnrutil.h
//#define vec_store2(T,i,j,x) _mm_store_si128((vuint8*) &T[i][j], x)


#define vec_right1(v1, v2) v1
#define vec_right2(v1, v2) v1

#define vec_left1(v0, v1) v1
#define vec_left2(v0, v1) v1
#define vMIN3(v0, v1, v2) _mm_min_epu8(v0, _mm_min_epu8(v1, v2))
#define vMAX3(v0, v1, v2) _mm_max_epu8(v0, _mm_max_epu8(v1, v2))
#define vMIN5(v0, v1, v2, v3, v4) _mm_min_epu8(v0, _mm_min_epu8(v1, _mm_min_epu8(v2, _mm_min_epu8(v3, v4))))
#define vMAX5(v0, v1, v2, v3, v4) _mm_max_epu8(v0, _mm_max_epu8(v1, _mm_max_epu8(v2, _mm_max_epu8(v3, v4))))

void test(vuint8 **vE, int vi1, int vj1);
void erosion_SIMD(vuint8 **vE, vuint8 **vOut, int vi0, int vi1, int vj0, int vj1);
void erosion2_SIMD(vuint8 **vE, int n, vuint8 **vOut);
void dilatation_SIMD(vuint8 **vE, vuint8 **vOut, int vi0, int vi1, int vj0, int vj1);
void dilatation2_SIMD(vuint8 **vE, int n, vuint8 **vOut);
void ouverture_SIMD(vuint8 **vE, vuint8 **vOut, int n, int b, int vi0, int vi1, int vj0, int vj1);
void fermeture_SIMD(vuint8 **vE, vuint8 **vOut, int n, int b, int vi0, int vi1, int vj0, int vj1);
void morpho_SIMD(vuint8 **vE, vuint8 **vOut, int n, int b, int vi0, int vi1, int vj0, int vj1);

#endif
