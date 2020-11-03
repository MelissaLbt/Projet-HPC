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


void init_tabs();
void Sigma_Delta(int *temp);



#endif 