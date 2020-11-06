/* --------------------- */
/* --- mouvement.h --- */
/* --------------------- */

#ifndef __MOUVEMENT_H__
#define __MOUVEMENT_H__


#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))


void SigmaDelta_step0(uint8 **I, uint8 **M, uint8 **V);
void SigmaDelta_1step(uint8 **I, uint8 **M0, uint8 **M1, uint8 **O, uint8 **V0, uint8 **V1, uint8 **E);



#endif 