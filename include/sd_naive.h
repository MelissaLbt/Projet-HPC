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


void init_SDtabs(uint8 **I, uint8 **M, uint8 **V);
void Sigma_Delta(uint8 **I, uint8 **M0, uint8 **M1, uint8 **O, uint8 **V0, uint8 **V1, uint8 **E);



#endif 