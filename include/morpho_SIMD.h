/* --------------------- */
/* --- morpho_SIMD.h --- */
/* --------------------- */

#ifndef __MORPHO_SIMD_H__
#define __MORPHO_SIMD_H__

#define vec_right1(v1, v2) _mm_shuffle_ps(v1, _mm_shuffle_ps(v1, v2, _MM_SHUFFLE(1,0,3,2)), _MM_SHUFFLE(2,1,2,1))
#define vec_right2(v1, v2) _mm_shuffle_ps(v1, v2, _MM_SHUFFLE(1,0,3,2))

#define vec_left1(v0, v1) _mm_shuffle_ps(_mm_shuffle_ps(v0, v1, _MM_SHUFFLE(1,0,3,2)), v1, _MM_SHUFFLE(2,1,2,1))
#define vec_left2(v0, v1) _mm_shuffle_ps(v0, v1, _MM_SHUFFLE(1,0,3,2))
#define vMIN3(v0, v1, v2) _mm_min_epu8(v0, _mm_min_epu8(v1, v2))
#define vMAX3(v0, v1, v2) _mm_max_epu8(v0, _mm_max_epu8(v1, v2))
#define vMIN5(v0, v1, v2, v3, v4) _mm_min_epu8(v0, _mm_min_epu8(v1, _mm_min_epu8(v2, _mm_min_epu8(v3, v4))))
#define vMAX5(v0, v1, v2, v3, v4) _mm_max_epu8(v0, _mm_max_epu8(v1, _mm_max_epu8(v2, _mm_max_epu8(v3, v4))))

void erosion_r1(vuint8 **vE, int vi1, int vj1, vuint8 **vOut);
void erosion_r2(vuint8 **vE, int vi1, int vj1, vuint8 **vOut);
void dilatation_r1(vuint8 **vE, int vi1, int vj1, vuint8 **vOut);
void dilatation_r2(vuint8 **vE, int vi1, int vj1, vuint8 **vOut);
void ouverture(vuint8 **vE, vuint8 **vOut, int b, int vi0, int vi1, int vj0, int vj1);
void fermeture(vuint8 **vE, vuint8 **vOut, int b, int vi0, int vi1, int vj0, int vj1);
void morpho(vuint8 **vE, vuint8 **vOut, int b, int vi0, int vi1, int vj0, int vj1);

#endif
