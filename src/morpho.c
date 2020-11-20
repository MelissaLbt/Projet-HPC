/* Algorithme Morphologie version naïve */
// erosion-dilatation-dilatation-erosion
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#include "nrdef.h"
#include "nrutil.h"

#include "vnrdef.h"
#include "vnrutil.h"

#include "mutil.h"

#include "morpho.h"

/* --------------------- */
/* E: Image d'entree     */
/* I: Image avec bord    */
/* img: Image de sortie  */
/* --------------------- */

//Copy dans un tableau plus grand et duplication des bords
void init_bord(uint8 **I, int b, long i0, long i1, long j0, long j1){

	if(b==1){
		I[i0-1][j0-1] = I[i0][j0];
	  I[i0-1][j1+1] = I[i0][j1];
	  I[i1+1][j0-1] = I[i1][j0];
	  I[i1+1][j1+1] = I[i1][j1];
	  for(int j = j0; j <= j1; j++){
	  	I[i0-1][j] = I[i0][j];
	    I[i1+1][j] = I[i1][j];
	  }
	  for(int i = i0; i <= i1; i++){
	  	I[i][j0-1] = I[i][j0];
	    I[i][j1+1] = I[i][j1];
	  }
	}
	else if(b==2){
		I[i0-2][j0-2] = I[i0-2][j0-1] = I[i0-1][j0-2] = I[i0-1][j0-1] = I[i0][j0];
		I[i0-2][j1+2] = I[i0-2][j1+1] = I[i0-1][j1+2] = I[i0-1][j1+1] = I[i0][j1];
		I[i1+2][j0-2] = I[i1+2][j0-1] = I[i1+1][j0-2] = I[i1+1][j0-1] = I[i1][j0];
		I[i1+2][j1+2] = I[i1+2][j1+1] = I[i1+1][j1+2] = I[i1+1][j1+1] = I[i1][j1];
		for(int j = j0; j <= j1; j++){
		  	I[i0-2][j] = I[i0-1][j] = I[i0][j];
		    I[i1+2][j] = I[i1+1][j] = I[i1][j];
	  	}
	  	for(int i = i0; i <= i1; i++){
			I[i][j0-2] = I[i][j0-1] = I[i][j0];
			I[i][j1+2] = I[i][j1+1] = I[i][j1];
	  	}
	}
}


// Erosion dans le cas B de taille 3*3
void erosion(uint8 **I, uint8 **img, int b, long i0, long i1, long j0, long j1){

	uint8 x0, x1, x2;
  
 	for(int i = 0; i <= i1; i++){
 		for(int j = 0; j <= j1; j++){
 			x0 = MIN3(I[i-1][j-1], I[i-1][j], I[i-1][j+1]);
 		  	x1 = MIN3(I[i  ][j-1], I[i  ][j], I[i  ][j+1]);
 			x2 = MIN3(I[i+1][j-1], I[i+1][j], I[i+1][j+1]);
 			img[i][j] = MIN3(x0, x1, x2);
    	}
 	}
}

// Dilatation dans le cas B de taille 3*3
void dilatation(uint8 **I, uint8 **img, int b, long i0, long i1, long j0, long j1){

	uint8 x0, x1, x2;
 	for (int i = 0; i <= i1; i++) {
 		for(int j = 0; j <= j1; j++){
 			x0 = MAX3(I[i-1][j-1], I[i-1][j], I[i-1][j+1]);
			x1 = MAX3(I[i  ][j-1], I[i  ][j], I[i  ][j+1]);
			x2 = MAX3(I[i+1][j-1], I[i+1][j], I[i+1][j+1]);
			img[i][j] = MAX3(x0, x1, x2);
    	}
 	}
}

void morpho(uint8 **E, uint8 **res, int b, long i0, long i1, long j0, long j1){

	uint8 **inter1, **inter2;
	inter1 = ui8matrix(i0-b,i1+b,j0-b,j1+b);
	inter2 = ui8matrix(i0-b,i1+b,j0-b,j1+b);

	zero_ui8matrix(inter1,i0-b,i1+b,j0-b,j1+b);
	zero_ui8matrix(inter2,i0-b,i1+b,j0-b,j1+b);

	init_bord(E,b,i0,i1,j0,j1);
	erosion(E,inter1,b,i0,i1,j0,j1);

	init_bord(inter1,b,i0,i1,j0,j1);
	dilatation(inter1,inter2,b,i0,i1,j0,j1);

	init_bord(inter2,b,i0,i1,j0,j1);
	dilatation(inter2,inter1,b,i0,i1,j0,j1);

	init_bord(inter1,b,i0,i1,j0,j1);
	erosion(inter1,res,b,i0,i1,j0,j1);

	free_ui8matrix(inter1,i0-b,i1+b,j0-b,j1+b);
	free_ui8matrix(inter2,i0-b,i1+b,j0-b,j1+b);
}
