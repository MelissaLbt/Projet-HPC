/* --------------------- */
/* --- morpho_SIMD.h --- */
/* --------------------- */

#ifndef __MORPHO_SIMD_H__
#define __MORPHO_SIMD_H__

// Attributs seront sûrement modifiés
void copy_duplication(uint8 **E, uint8 **I, int b, long nrl, long nrh, long ncl, long nch);
void erosion_r1(uint8 **E, uint8 **img, int b, long nrl, long nrh, long ncl, long nch);
void erosion_r2(uint8 **E, uint8 **img, int b, long nrl, long nrh, long ncl, long nch);
void dilatation_r1(uint8 **E, uint8 **img, int b, long nrl, long nrh, long ncl, long nch);
void dilatation_r2(uint8 **E, uint8 **img, int b, long nrl, long nrh, long ncl, long nch);
void ouverture_r1(uint8 **E, uint8 **img, int b, long nrl, long nrh, long ncl, long nch);
void ouverture_r2(uint8 **E, uint8 **img, int b, long nrl, long nrh, long ncl, long nch);
void fermeture_r1(uint8 **E, uint8 **img, int b, long nrl, long nrh, long ncl, long nch);
void fermeture_r2(uint8 **E, uint8 **img, int b, long nrl, long nrh, long ncl, long nch);
void morpho(uint8 **E, uint8 **img, int b, long nrl, long nrh, long ncl, long nch);


#endif
