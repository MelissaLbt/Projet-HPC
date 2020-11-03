// erosion-dilatation-dilatation-erosion
// min-max-max-min
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "sd_naive.h"
#include "morpho_naive.h"


//(pseudo) code

 void erosion(int32_t **I ){
 	int i,j;
 	int32_t x0, x1, x2
 	int32_t res[H][W];
 	for (i=0; i<H; i++) {
 		for(j=0; j<W; j++)
 			x0 = MIN3(I[i-1][j-1], I[i-1][j], I[i-1][j+1]);
 			x1 = MIN3(I[i  ][j-1], I[i  ][j], I[i  ][j+1]);
 			x2 = MIN3(I[i+1][j-1], I[i+1][j], I[i+1][j+1]);
 			H[i][j] = MIN3(x0, x1, x2);
 	}

 	return ???
 }

 void dilatation(int32_t **I){
 	int i,j;
 	int32_t x0, x1, x2
 	int32_t res[H][W];
 	for (i=0; i<H; i++) {
 		for(j=0; j<W; j++)
 			x0 = MAX3(I[i-1][j-1], I[i-1][j], I[i-1][j+1]);
 			x1 = MAX3(I[i  ][j-1], I[i  ][j], I[i  ][j+1]);
 			x2 = MAX3(I[i+1][j-1], I[i+1][j], I[i+1][j+1]);
 			H[i][j] = MAX3(x0, x1, x2);
 	}
 }

 void ouverture(){
 	dilatation(erosion());
 }

 void fermeture(){
 	erosion(dilatation());
 }