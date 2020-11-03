/* --------------------- */
/* --- sd_naive.h --- */
/* --------------------- */

#ifndef __SD_NAIVE_H__
#define __SD_NAIVE_H__

#define H 240
#define W 320
#define N 2		// a verifier: 2/3/4
#define VMIN 1
#define VMAX 254

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))



extern int32_t I[200][240][320];		
extern int32_t M[200][240][320];		
extern int32_t V[200][240][320];		
extern int32_t O[200][240][320];
extern int32_t E[200][240][320];

void init_tabs();
void Sigma_Delta(int *temp);



#endif 