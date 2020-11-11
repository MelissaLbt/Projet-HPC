/* --------------------- */
/* --- morpho.h --- */
/* --------------------- */

#ifndef __MORPHO_H__
#define __MORPHO_H__


#define MAX3(a,b,c) ((((a) > (b)) ? (a) : (b)) > (c) ? (((a) > (b)) ? (a) : (b)) : c)
#define MIN3(a,b,c) ((((a) < (b)) ? (a) : (b)) < (c) ? (((a) < (b)) ? (a) : (b)) : c)

void copy_duplication(uint8 **E, uint8 **I, int b, long nrl, long nrh, long ncl, long nch);
void erosion(uint8 **E, uint8 **img, int b, long nrl, long nrh, long ncl, long nch);
void dilatation(uint8 **E, uint8 **img, int b, long nrl, long nrh, long ncl, long nch);
void ouverture(uint8 **E, uint8 **img, int b, long nrl, long nrh, long ncl, long nch);
void fermeture(uint8 **E, uint8 **img, int b, long nrl, long nrh, long ncl, long nch);
void morpho(uint8 **E, uint8 **img, int b, long nrl, long nrh, long ncl, long nch);


#endif
