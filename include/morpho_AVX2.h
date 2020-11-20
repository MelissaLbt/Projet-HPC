/* --------------------- */
/* --- morpho_AVX2.h --- */
/* --------------------- */

#ifndef __MORPHO_AVX2_H__
#define __MORPHO_AVX2_H__


#define vec256_extractl(v) 	_mm256_extract_epi8(v,31)
#define vec256_extractr(v) 	_mm256_extract_epi8(v,0)

#define vec256_right1(v1, v2) _mm256_or_si256(_mm256_slli_si256(v1,1),_mm256_srli_si256(v2,31))
#define vec256_right2(v1, v2) _mm256_or_si256(_mm256_slli_si256(v1,2),_mm256_srli_si256(v2,30))

#define vec256_left1(v0, v1) _mm256_or_si256(_mm256_slli_si256(v0,31),_mm256_srli_si256(v1,1))
#define vec256_left2(v0, v1) _mm256_or_si256(_mm256_slli_si256(v0,30),_mm256_srli_si256(v1,2))

#define vec256_or5(v0,v1,v2,v3,v4)	 _mm256_or_si256 (_mm256_or_si256 (_mm256_or_si256 (_mm256_or_si256 (v0,v1),v2),v3),v4)
#define vec256_and5(v0,v1,v2,v3,v4) _mm256_and_si256 (_mm256_and_si256 (_mm256_and_si256 (_mm256_and_si256 (v0,v1),v2),v3),v4)

void init_bord_AVX2(vuint8 **vE,int vi0,int vi1,int vj0,int vj1,int vj0b,int vj1b);
void erosion_AVX2(vuint8 **vE, vuint8 **vOut, int vi0, int vi1, int vj0, int vj1);
void dilatation_AVX2(vuint8 **vE, vuint8 **vOut, int vi0, int vi1, int vj0, int vj1);
void morpho_AVX2(vuint8 **vE, vuint8 **vOut,int vi0, int vi1, int vj0, int vj1, int vi0b, int vi1b, int vj0b, int vj1b);

void erosion_AVX2_red(vuint8 **vE, vuint8 **vOut, int vi0, int vi1, int vj0, int vj1);
void dilatation_AVX2_red(vuint8 **vE, vuint8 **vOut, int vi0, int vi1, int vj0, int vj1);
void morpho_AVX2_red(vuint8 **vE, vuint8 **vOut,int vi0, int vi1, int vj0, int vj1, int vi0b, int vi1b, int vj0b, int vj1b);

#endif
