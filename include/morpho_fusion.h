/* --------------------- */
/* --- morpho_fusion.h --- */
/* --------------------- */

#ifndef __MORPHO_FUSION_H__
#define __MORPHO_FUSION_H__

#define vec_right2(v1, v2) _mm_or_si128(_mm_slli_si128(v1,2),_mm_srli_si128(v2,14))
#define vec_left2(v0, v1) _mm_or_si128(_mm_slli_si128(v0,14),_mm_srli_si128(v1,2))

#define vec_or5(v0,v1,v2,v3,v4)	 _mm_or_si128 (_mm_or_si128 (_mm_or_si128 (_mm_or_si128 (v0,v1),v2),v3),v4)

void morpho_fusion(vuint8 **vE, vuint8 **vOut,int vi0, int vi1, int vj0, int vj1, int vi0b, int vi1b, int vj0b, int vj1b);

#endif