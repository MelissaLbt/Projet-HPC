/* --------------------- */
/* --- morpho_naive.h --- */
/* --------------------- */

#ifndef __MORPHO_NAIVE__
#define __MORPHO_NAIVE__


#define MAX3(a,b,c) ((((a) > (b)) ? (a) : (b)) > (c) ? (((a) > (b)) ? (a) : (b)) : c)
#define MIN3(a,b,c) ((((a) < (b)) ? (a) : (b)) < (c) ? (((a) < (b)) ? (a) : (b)) : c)

#define MAX5(a,b,c,d,e) MAX3(MAX3(a,b,c),d,e)
#define MIN5(a,b,c,d,e) MIN3(MIN3(a,b,c),d,e) 

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
