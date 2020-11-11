/* --------------------- */
/* --- mouvement.h --- */
/* --------------------- */

#ifndef __MOUVEMENT_H__
#define __MOUVEMENT_H__


#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))


void SigmaDelta_step0(uint8 **I, uint8 **M, uint8 **V, int i0, int i1, int j0, int j1);
//void SigmaDelta_1step(uint8 **I, uint8 **M0, uint8 **M1, uint8 **O, uint8 **V0, uint8 **V1, uint8 **E);
void SigmaDelta_step1(uint8 **I, uint8 **M0, uint8 **M1,int i0, int i1, int j0, int j1);
void SigmaDelta_step2(uint8 **I, uint8 **M1, uint8 **O, int i0, int i1, int j0, int j1);
void SigmaDelta_step3(uint8 **O, uint8 **V0, uint8 **V1, int i0, int i1, int j0, int j1);
void SigmaDelta_step4(uint8 **O, uint8 **V1, uint8 **E, int i0, int i1, int j0, int j1);



#endif 
