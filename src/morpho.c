/* Algorithme Morphologie version naïve */
// erosion-dilatation-dilatation-erosion
#include <stdio.h>
#include <stdlib.h>

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
void copy_duplication(uint8 **E, uint8 **I, int b, long nrl, long nrh, long ncl, long nch){
	
	copy_ui8matrix_ui8matrix(E,(int)nrl,(int)nrh,(int)ncl,(int)nch,I);
	
	if(b==1){
		I[-1][-1] = I[0][0];
	    I[-1][W] = I[0][W-1];
	   	I[H][-1] = I[H-1][0];
	    I[H][W] = I[H-1][W-1];
	    for(int j = 0; j < W; j++){
	        I[-1][j] = I[0][j];
	       	I[H][j] = I[H-1][j];
	   	}
	   	for(int i = 0; i < H; i++){
	     	I[i][-1] = I[i][0];
	     	I[i][W] = I[i][W-1];
	   }
	}
	else if(b==2){
	    I[-2][-2] = I[-2][-1] = I[-1][-2] = I[-1][-1] = I[0][0];
	    I[-2][W + 1] = I[-2][W] = I[-1][W + 1] = I[-1][W] = I[0][W-1];
	    I[H + 1][-2] = I[H][-2] = I[H + 1][-1] = I[H][-1] = I[H-1][0];
	    I[H + 1][W + 1] = I[H + 1][W] = I[H][W + 1] = I[H][W] = I[H-1][W-1];
	    for(int j = 0; j < W; j++){
	      I[-1][j] = I[0][j];
	      I[-2][j] = I[0][j];
	      I[H + 1][j] = I[H-1][j];
	      I[H][j] = I[H-1][j];
	    }
	    for(int i = 0; i < H; i++){
	      I[i][-1] = I[i][0];
	      I[i][-2] = I[i][0];
	      I[i][W] = I[i][W-1];
	      I[i][W + 1] = I[i][W-1];
	    }
	}
}


// Erosion dans le cas B de taille 3*3
void erosion_r1(uint8 **E, uint8 **img, int b, long nrl, long nrh, long ncl, long nch){
   	uint8 x0, x1, x2;
   	uint8 **I;
  	I = ui8matrix(nrl-b, nrh+b, ncl-b, nch+b);
  	copy_duplication(E,I,b,nrl,nrh,ncl,nch);
   //Erosion
 	for (int i = 0; i < H; i++) {
 	   	for(int j = 0; j < W; j++){
 		    x0 = MIN3(I[i-1][j-1], I[i-1][j], I[i-1][j+1]);
 		    x1 = MIN3(I[i  ][j-1], I[i  ][j], I[i  ][j+1]);
 			x2 = MIN3(I[i+1][j-1], I[i+1][j], I[i+1][j+1]);
 			img[i][j] = MIN3(x0, x1, x2);
     	}
 	}
 	free_ui8matrix(I, nrl-b, nrh+b, ncl-b, nch+b);
}

// Erosion dans le cas B de taille 5*5
void erosion_r2(uint8 **E, uint8 **img, int b, long nrl, long nrh, long ncl, long nch){

    uint8 x0, x1, x2, x3, x4;

   	uint8 **I;
  	I = ui8matrix(nrl-b, nrh+b, ncl-b, nch+b);
  	copy_duplication(E,I,b,nrl,nrh,ncl,nch);

    //Erosion
  	for (int i = 0; i < H; i++) {
  	   	for(int j = 0; j < W; j++){
          	x0 = MIN5(I[i - 2][j - 2], I[i - 2][j - 1], I[i - 2][j], I[i - 2][j + 1], I[i - 2][j + 2]);
  		    x1 = MIN5(I[i - 1][j - 2], I[i - 1][j - 1], I[i - 1][j], I[i - 1][j + 1], I[i - 1][j + 2]);
  		    x2 = MIN5(I[i    ][j - 2], I[i    ][j - 1], I[i    ][j], I[i    ][j + 1], I[i    ][j + 2]);
  			x3 = MIN5(I[i + 1][j - 2], I[i + 1][j - 1], I[i + 1][j], I[i + 1][j + 1], I[i + 1][j + 2]);
          	x4 = MIN5(I[i + 2][j - 2], I[i + 2][j - 1], I[i + 2][j], I[i + 2][j + 1], I[i + 2][j + 2]);
  			img[i][j] = MIN5(x0, x1, x2, x3, x4);
      	}
  	}
  	free_ui8matrix(I, nrl-b, nrh+b, ncl-b, nch+b);
}

// Dilatation dans le cas B de taille 3*3
void dilatation_r1(uint8 **E, uint8 **img, int b, long nrl, long nrh, long ncl, long nch){

   	uint8 x0, x1, x2;

   	uint8 **I;
  	I = ui8matrix(nrl-b, nrh+b, ncl-b, nch+b);
  	copy_duplication(E,I,b,nrl,nrh,ncl,nch);

 	for (int i = 0; i < H; i++) {
 		for(int j = 0; j < W; j++){
 			x0 = MAX3(I[i-1][j-1], I[i-1][j], I[i-1][j+1]);
 		    x1 = MAX3(I[i  ][j-1], I[i  ][j], I[i  ][j+1]);
 		    x2 = MAX3(I[i+1][j-1], I[i+1][j], I[i+1][j+1]);
 		    img[i][j] = MAX3(x0, x1, x2);
      	}
 	}
 	free_ui8matrix(I, nrl-b, nrh+b, ncl-b, nch+b);
}

// Erosion dans le cas B de taille 5*5
void dilatation_r2(uint8 **E, uint8 **img, int b, long nrl, long nrh, long ncl, long nch){
    uint8 x0, x1, x2, x3, x4;
    
    uint8 **I;
  	I = ui8matrix(nrl-b, nrh+b, ncl-b, nch+b);
  	copy_duplication(E,I,b,nrl,nrh,ncl,nch);

    //Erosion
  	for (int i = 0; i < H; i++) {
  	   for(int j = 0; j < W; j++){
          	x0 = MAX5(I[i - 2][j - 2], I[i - 2][j - 1], I[i - 2][j], I[i - 2][j + 1], I[i - 2][j + 2]);
  		    x1 = MAX5(I[i - 1][j - 2], I[i - 1][j - 1], I[i - 1][j], I[i - 1][j + 1], I[i - 1][j + 2]);
  		    x2 = MAX5(I[i][j - 2], I[i  ][j - 1], I[i  ][j], I[i  ][j + 1], I[i][j + 2]);
  			x3 = MAX5(I[i + 1][j - 2], I[i + 1][j - 1], I[i + 1][j], I[i + 1][j + 1], I[i + 1][j + 2]);
          	x4 = MAX5(I[i + 2][j - 2], I[i + 2][j - 1], I[i + 2][j], I[i + 2][j + 1], I[i + 2][j + 2]);
  			img[i][j] = MAX5(x0, x1, x2, x3, x4);
      	}
  	}
  	free_ui8matrix(I, nrl-b, nrh+b, ncl-b, nch+b);
}

void ouverture_r1(uint8 **E, uint8 **res, int b, long nrl, long nrh, long ncl, long nch){
  	uint8 **intermediaire;
  	intermediaire = ui8matrix(nrl,nrh,ncl,nch); 

  	erosion_r1(E,intermediaire,b,nrl,nrh,ncl,nch);
  	dilatation_r1(intermediaire,res,b,nrl,nrh,ncl,nch);

  	free_ui8matrix(intermediaire,nrl,nrh,ncl,nch);
}

void ouverture_r2(uint8 **E, uint8 **res, int b, long nrl, long nrh, long ncl, long nch){
	uint8 **intermediaire;
  	intermediaire = ui8matrix(nrl,nrh,ncl,nch);

    erosion_r2(E,intermediaire,b,nrl,nrh,ncl,nch);
  	dilatation_r2(intermediaire,res,b,nrl,nrh,ncl,nch);

  	free_ui8matrix(intermediaire,nrl,nrh,ncl,nch);

}

void fermeture_r1(uint8 **E, uint8 **res, int b, long nrl, long nrh, long ncl, long nch){
	uint8 **intermediaire;
  	intermediaire = ui8matrix(nrl,nrh,ncl,nch); 

  	dilatation_r1(E,intermediaire,b,nrl,nrh,ncl,nch);
  	erosion_r1(intermediaire,res,b,nrl,nrh,ncl,nch);

  	free_ui8matrix(intermediaire,nrl,nrh,ncl,nch);

}

void fermeture_r2(uint8 **E, uint8 **res, int b, long nrl, long nrh, long ncl, long nch){
	uint8 **intermediaire;
  	intermediaire = ui8matrix(nrl,nrh,ncl,nch); 

  	dilatation_r2(E,intermediaire,b,nrl,nrh,ncl,nch);
  	erosion_r2(intermediaire,res,b,nrl,nrh,ncl,nch);

  	free_ui8matrix(intermediaire,nrl,nrh,ncl,nch);

}

void morpho(uint8 **E, uint8 **res, int b, long nrl, long nrh, long ncl, long nch){
	uint8 **intermediaire;
  	intermediaire = ui8matrix(nrl,nrh,ncl,nch); 

	ouverture_r1(E,intermediaire,b,nrl,nrh,ncl,nch);
	fermeture_r1(intermediaire,res,b,nrl,nrh,ncl,nch);

  	free_ui8matrix(intermediaire,nrl,nrh,ncl,nch);

}
