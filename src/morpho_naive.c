// erosion-dilatation-dilatation-erosion
// min-max-max-min
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "sd_naive.h"
#include "morpho_naive.h"
#include <unistd.h>

#include "nrdef.h"
#include "nrutil.h"



// Erosion dans le cas B de taille 3*3
void erosion_r1(int32_t I[H][W], int32_t img[H][W]){
   int x0, x1, x2;
   //Duplication des bords
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
   //Erosion
 	 for (int i = 0; i < H; i++) {
 	   for(int j = 0; j < W; j++){
 		    x0 = MIN3(I[i-1][j-1], I[i-1][j], I[i-1][j+1]);
 		    x1 = MIN3(I[i  ][j-1], I[i  ][j], I[i  ][j+1]);
 			x2 = MIN3(I[i+1][j-1], I[i+1][j], I[i+1][j+1]);
 			img[i][j] = MIN3(x0, x1, x2);
     	}
 	 }
 }

// Erosion dans le cas B de taille 5*5
void erosion_r2(int32_t I[H][W], int32_t img[H][W]){
    int x0, x1, x2, x3, x4;
    //Duplication des bords
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
    //Erosion
  	 for (int i = 0; i < H; i++) {
  	   for(int j = 0; j < W; j++){
          x0 = MIN5(I[i - 2][j - 2], I[i - 2][j - 1], I[i - 2][j], I[i - 2][j + 1], I[i - 2][j + 2]);
  		    x1 = MIN5(I[i - 1][j - 2], I[i - 1][j - 1], I[i - 1][j], I[i - 1][j + 1], I[i - 1][j + 2]);
  		    x2 = MIN5(I[i][j - 2], I[i  ][j - 1], I[i  ][j], I[i  ][j + 1], I[i][j + 2]);
  			  x3 = MIN5(I[i + 1][j - 2], I[i + 1][j - 1], I[i + 1][j], I[i + 1][j + 1], I[i + 1][j + 2]);
          x4 = MIN5(I[i + 2][j - 2], I[i + 2][j - 1], I[i + 2][j], I[i + 2][j + 1], I[i + 2][j + 2]);
  			  img[i][j] = MIN5(x0, x1, x2, x3, x4);
      }
  	 }
  }




// Dilatation dans le cas B de taille 3*3
void dilatation_r1(int32_t I[H][W], int32_t img[H][W]){
   int32_t x0, x1, x2;
   //Duplication des bords
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

 	 for (int i = 0; i < H; i++) {
 		  for(int j = 0; j < W; j++){
 			    x0 = MAX3(I[i-1][j-1], I[i-1][j], I[i-1][j+1]);
 			    x1 = MAX3(I[i  ][j-1], I[i  ][j], I[i  ][j+1]);
 			    x2 = MAX3(I[i+1][j-1], I[i+1][j], I[i+1][j+1]);
 			    img[i][j] = MAX3(x0, x1, x2);
      }
 	 }
}

// Erosion dans le cas B de taille 5*5
void dilatation_r2(int32_t I[H][W], int32_t img[H][W]){
    int x0, x1, x2, x3, x4;
    //Duplication des bords
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
  }

void ouverture_r1(int32_t I[H][W], int32_t res[H][W]){
  int32_t intermediaire[H][W];
  erosion_r1(I, intermediaire);
  dilatation_r1(intermediaire, res);
}

void ouverture_r2(int32_t I[H][W], int32_t res[H][W]){
  int32_t intermediaire[H][W];
  erosion_r2(I, intermediaire);
  dilatation_r2(intermediaire, res);
}

void fermeture_r1(int32_t I[H][W], int32_t res[H][W]){
  int32_t intermediaire[H][W];
  dilatation_r1(I, intermediaire);
  erosion_r1(intermediaire, res);
}

void fermeture_r2(int32_t I[H][W], int32_t res[H][W]){
  int32_t intermediaire[H][W];
  dilatation_r2(I, intermediaire);
  erosion_r2(intermediaire, res);
}
/*
 int main(){
   char *path = "~/Documents/CHP/Projet-HPC/car3";
   char *filename = "car_";
   int k = 3000;
   int ndigit = 0;
   char *extension = ".pgm";
   char *complete_filename;
   generate_path_filename_k_ndigit_extension(path, filename, k, ndigit, extension, complete_filename);
   printf("%s\n", complete_filename);
 }*/
