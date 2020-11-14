/* --------------------- */
/* --- morpho_SSE2.h --- */
/* --------------------- */

#ifndef __MORPHO_SSE2_H__
#define __MORPHO_SSE2_H__

// une partie de macro dans vnrutil.h

#define vec_extractl(v) _mm_extract_epi16(_mm_srli_si128(v,15),0)
#define vec_extractr(v) _mm_extract_epi16(_mm_srli_si128(_mm_slli_si128(v,15),15),0)

#define vec_right1(v1, v2) _mm_or_si128(_mm_slli_si128(v1,1),_mm_srli_si128(v2,15))
#define vec_right2(v1, v2) _mm_or_si128(_mm_slli_si128(v1,2),_mm_srli_si128(v2,14))

#define vec_left1(v0, v1) _mm_or_si128(_mm_slli_si128(v0,15),_mm_srli_si128(v1,1))
#define vec_left2(v0, v1) _mm_or_si128(_mm_slli_si128(v0,14),_mm_srli_si128(v1,2))

#define vec_or5(v0,v1,v2,v3,v4)	 _mm_or_si128 (_mm_or_si128 (_mm_or_si128 (_mm_or_si128 (v0,v1),v2),v3),v4)



void init_bord(vuint8 **vE,int vi0,int vi1,int vj0,int vj1,int vj0b,int vj1b);

void erosion_SSE2(vuint8 **vE, vuint8 **vOut, int vi0, int vi1, int vj0, int vj1);
void dilatation_SSE2(vuint8 **vE, vuint8 **vOut, int vi0, int vi1, int vj0, int vj1);
void morpho_SSE2(vuint8 **vE, vuint8 **vOut,int vi0, int vi1, int vj0, int vj1, int vi0b, int vi1b, int vj0b, int vj1b);

void erosion_SSE2_red(vuint8 **vE, vuint8 **vOut, int vi0, int vi1, int vj0, int vj1);
void dilatation_SSE2_red(vuint8 **vE, vuint8 **vOut, int vi0, int vi1, int vj0, int vj1);
void morpho_SSE2_red(vuint8 **vE, vuint8 **vOut,int vi0, int vi1, int vj0, int vj1, int vi0b, int vi1b, int vj0b, int vj1b);

void dilatation_fusion(vuint8 **vE, vuint8 **vOut, int vi0, int vi1, int vj0, int vj1);
void morpho_fusion(vuint8 **vE, vuint8 **vOut,int vi0, int vi1, int vj0, int vj1, int vi0b, int vi1b, int vj0b, int vj1b);


#endif
