/* --------------------- */
/* --- morpho_SIMD.h --- */
/* --------------------- */

#ifndef __MORPHO_SIMD_H__
#define __MORPHO_SIMD_H__

// une partie de macro dans vnrutil.h

#define vec_extractl(v) _mm_extract_epi16(_mm_srli_si128(v,15),0)
#define vec_extractr(v) _mm_extract_epi16(_mm_srli_si128(_mm_slli_si128(v,15),15),0)

#define vec_right1(v1, v2) _mm_or_si128(_mm_slli_si128(v1,1),_mm_srli_si128(v2,15))
#define vec_left1(v0, v1) _mm_or_si128(_mm_slli_si128(v0,15),_mm_srli_si128(v1,1))

void init_bord(vuint8 **vE,int vi0,int vi1,int vj0,int vj1,int vj0b,int vj1b);

void erosion_SIMD(vuint8 **vE, vuint8 **vOut, int vi0, int vi1, int vj0, int vj1);
void erosion_SIMD_red(vuint8 **vE, vuint8 **vOut, int vi0, int vi1, int vj0, int vj1);
void erosion2_SIMD(vuint8 **vE, int n, vuint8 **vOut);


void dilatation_SIMD(vuint8 **vE, vuint8 **vOut, int vi0, int vi1, int vj0, int vj1);
void dilatation_SIMD_red(vuint8 **vE, vuint8 **vOut, int vi0, int vi1, int vj0, int vj1);
void dilatation2_SIMD(vuint8 **vE, int n, vuint8 **vOut);

void morpho_SIMD(vuint8 **vE, vuint8 **vOut,int vi0, int vi1, int vj0, int vj1, int vi0b, int vi1b, int vj0b, int vj1b);

#endif
