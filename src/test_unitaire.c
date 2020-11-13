#include <stdio.h>
#include <stdlib.h>

#include "nrdef.h"
#include "nrutil.h"

#include "vnrdef.h"
#include "vnrutil.h"

#include "mutil.h"

#include "test_unitaire.h"
#include "mouvement.h"
#include "morpho.h"

//********* test unitaire 1/etape *********//
//*** sur des petites matrix predefinie ***//
//********* pour valider sd naive *********//

int SigmaDelta_step0_tu(){

	uint8 **I0 = ui8matrix(0,3,0,3);
	uint8 **M0 = ui8matrix(0,3,0,3);
	uint8 **V0 = ui8matrix(0,3,0,3);

	for(int i=0; i<=3; i++){
		for(int j=0; j<=3; j++){
			I0[i][j] = i+j;
		}
	}
	//display_ui8matrix (I0,0,3,0,3,"%6d ","my I0");

	SigmaDelta_step0(I0,M0,V0,0,3,0,3);

	for(int i=0; i<=3; i++){
		for(int j=0; j<=3; j++){
			if(M0[i][j]!=I0[i][j]){
				return 0;
			}
			if(V0[i][j]!= 1){
				return 0;
			}
		}
	}
	return 1;
}

int SigmaDelta_step1_tu(){
	
	uint8 **I1 = ui8matrix(0,3,0,3);
	uint8 **M0 = ui8matrix(0,3,0,3);
	uint8 **M1 = ui8matrix(0,3,0,3);
	uint8 **M1_ref = ui8matrix(0,3,0,3);

	for(int i=0; i<=3; i++){
		for(int j=0; j<=3; j++){
			I1[i][j] = 3;
			M0[i][j] = i+j;
		}
	}

	M1_ref[0][0] = 1; M1_ref[0][1] = 2; M1_ref[0][2] =    M1_ref[0][3] = 3;
	M1_ref[1][0] = 2; M1_ref[1][1] = 	M1_ref[1][2] =	  M1_ref[1][3] = 3;
	M1_ref[2][0] = 	  M1_ref[2][1] = 	M1_ref[2][2] = 3; M1_ref[2][3] = 4;
	M1_ref[3][0] = 	  M1_ref[3][1] = 3;	M1_ref[3][2] = 4; M1_ref[3][3] = 5;
	//display_ui8matrix (I1,0,3,0,3,"%6d ","I1");
	//display_ui8matrix (M0,0,3,0,3,"%6d ","M0");
	//display_ui8matrix (M1_ref,0,3,0,3,"%6d ","M1_ref");

	SigmaDelta_step1(I1,M0,M1,0,3,0,3);
	//display_ui8matrix (M1,0,3,0,3,"%6d ","M1");

	for(int i=0; i<=3; i++){
		for(int j=0; j<=3; j++){
			if(M1[i][j]!= M1_ref[i][j] || M0[i][j]!= M1_ref[i][j]){
				return 0;
			}
		}
	}
	return 1;	
}

int SigmaDelta_step2_tu(){

	uint8 **I1 = ui8matrix(0,3,0,3);
	uint8 **M1 = ui8matrix(0,3,0,3);
	uint8 **O  = ui8matrix(0,3,0,3);
	uint8 **O_ref = ui8matrix(0,3,0,3);

	for(int i=0; i<=3; i++){
		for(int j=0; j<=3; j++){
			I1[i][j] = 3;
			M1[i][j] = i+j;
		}
	}

	O_ref[0][0] = 3; O_ref[0][1] = 2; O_ref[0][2] = 1; O_ref[0][3] = 0;
	O_ref[1][0] = 2; O_ref[1][1] = 1; O_ref[1][2] =	0; O_ref[1][3] = 1;
	O_ref[2][0] = 1; O_ref[2][1] = 0; O_ref[2][2] = 1; O_ref[2][3] = 2;
	O_ref[3][0] = 0; O_ref[3][1] = 1; O_ref[3][2] = 2; O_ref[3][3] = 3;
	//display_ui8matrix (I1,0,3,0,3,"%6d ","I1");
	//display_ui8matrix (M1,0,3,0,3,"%6d ","M1");
	//display_ui8matrix (O_ref,0,3,0,3,"%6d ","O_ref");

	SigmaDelta_step2(I1,M1,O,0,3,0,3);
	//display_ui8matrix (O,0,3,0,3,"%6d ","O");

	for(int i=0; i<=3; i++){
		for(int j=0; j<=3; j++){
			if(O[i][j]!= O_ref[i][j]){
				return 0;
			}
		}
	}
	return 1;	
	
}

int SigmaDelta_step3_tu(){

	uint8 **O = ui8matrix(0,3,0,3);
	uint8 **V0 = ui8matrix(0,3,0,3);
	uint8 **V1 = ui8matrix(0,3,0,3);
	uint8 **V1_ref = ui8matrix(0,3,0,3);

	for(int i=0; i<=3; i++){
		for(int j=0; j<=3; j++){
			O[i][j] = 1;  //n*O=2
			V0[i][j] = i+j;
		}
	}
	O[0][0] = 0; V0[0][0] = 1; //tester le seuil
	V1_ref[0][0] = 1; V1_ref[0][1] =    V1_ref[0][2] =    V1_ref[0][3] = 2;
	V1_ref[1][0] =    V1_ref[1][1] = 	V1_ref[1][2] = 2; V1_ref[1][3] = 3;
	V1_ref[2][0] = 	  V1_ref[2][1] = 2; V1_ref[2][2] = 3; V1_ref[2][3] = 4;
	V1_ref[3][0] = 2; V1_ref[3][1] = 3;	V1_ref[3][2] = 4; V1_ref[3][3] = 5;
	//display_ui8matrix (O,0,3,0,3,"%6d ","O");
	//display_ui8matrix (V0,0,3,0,3,"%6d ","V0");
	//display_ui8matrix (V1_ref,0,3,0,3,"%6d ","V1_ref");

	SigmaDelta_step3(O,V0,V1,0,3,0,3);
	//display_ui8matrix (V1,0,3,0,3,"%6d ","V1");

	for(int i=0; i<=3; i++){
		for(int j=0; j<=3; j++){
			if(V1[i][j]!= V1_ref[i][j] || V0[i][j]!= V1_ref[i][j]){
				return 0;
			}
		}
	}
	return 1;	
}

int SigmaDelta_step4_tu(){

	uint8 **O  = ui8matrix(0,3,0,3);
	uint8 **V1 = ui8matrix(0,3,0,3);
	uint8 **E  = ui8matrix(0,3,0,3);
	uint8 **E_ref = ui8matrix(0,3,0,3);

	for(int i=0; i<=3; i++){
		for(int j=0; j<=3; j++){
			O[i][j] = 3;
			V1[i][j] = i+j;
		}
	}

	E_ref[0][0] = E_ref[0][1] = E_ref[0][2] = E_ref[0][3] = 255;
	E_ref[1][0] = E_ref[1][1] = E_ref[1][2] = 255; E_ref[1][3] = 0;
	E_ref[2][0] = E_ref[2][1] = 255; E_ref[2][2] = E_ref[2][3] = 0;
	E_ref[3][0] = 255; E_ref[3][1] = E_ref[3][2] = E_ref[3][3] = 0;
	//display_ui8matrix (O,0,3,0,3,"%6d ","O");
	//display_ui8matrix (V1,0,3,0,3,"%6d ","V1");
	//display_ui8matrix (E_ref,0,3,0,3,"%6d ","E_ref");

	SigmaDelta_step4(O,V1,E,0,3,0,3);
	//display_ui8matrix (E,0,3,0,3,"%6d ","E");

	for(int i=0; i<=3; i++){
		for(int j=0; j<=3; j++){
			if(E[i][j]!= E_ref[i][j]){
				return 0;
			}
		}
	}
	return 1;	
}

//************* Test Unitaire ***************//
//*** Gestion du bord, erosion, dilataion ***//
//******** Pour valider Morpho naive ********//

int Morpho_gesbord(){

	uint8 **E 		= ui8matrix(0,1,0,1);
	uint8 **I1 		= ui8matrix(-1,2,-1,2);
	uint8 **I2 		= ui8matrix(-2,3,-2,3);

	E[0][0] = 1; E[0][1] = 2;
	E[1][0] = 3; E[1][1] = 4;

	//display_ui8matrix (E,0,1,0,1,"%6d ","E");
	copy_duplication(E,I1,1,0,1,0,1);
	copy_duplication(E,I2,2,0,1,0,1);
	//display_ui8matrix (I1,-1,2,-1,2,"%6d ","I1");
	//display_ui8matrix (I2,-2,3,-2,3,"%6d ","I2");

	for(int i=0;i<=1;i++){
		for(int j=0;j<=1;j++){
			if(I1[i][j]!=E[i][j] || I2[i][j]!=E[i][j])
				return 0;
		}
	}

	for(int i=-1;i<=2;i+=2){
		for(int j=-1;j<=2;j+=2){
			if(!(I1[i][j]==I1[i+1][j] && I1[i][j]==I1[i][j+1] &&I1[i][j]==I1[i+1][j+1]))
				return 0;
		}
	}
	for(int i=-2;i<=3;i+=3){
		for(int j=-2;j<=3;j+=3){
			if(!(I2[i][j]==I2[i+1][j] && I2[i][j]==I2[i][j+1] && I2[i][j]==I2[i+1][j+1] && I2[i][j]==I2[i+1][j+2]))
				return 0;
			if(!(I2[i][j]==I2[i+2][j] && I2[i][j]==I2[i][j+2] && I2[i][j]==I2[i+2][j+2] && I2[i][j]==I2[i+2][j+1]))
				return 0;
		}
	}
	return 1;
}

int Morpho_erosion(){

	uint8 c = 1;
	uint8 **E 		= ui8matrix(0,3,0,3);
	uint8 **img 	= ui8matrix(0,3,0,3);
	uint8 **img_ref = ui8matrix(0,3,0,3);

	for(int i=0; i<=3; i++){
		for(int j=0; j<=3; j++){
			E[i][j] = c;
			c++;
		}
	}

	img_ref[0][0] = 1; img_ref[0][1] = 1; img_ref[0][2] = 2; img_ref[0][3] = 3;
	img_ref[1][0] = 1; img_ref[1][1] = 1; img_ref[1][2] = 2; img_ref[1][3] = 3;
	img_ref[2][0] = 5; img_ref[2][1] = 5; img_ref[2][2] = 6; img_ref[2][3] = 7;
	img_ref[3][0] = 9; img_ref[3][1] = 9; img_ref[3][2] = 10; img_ref[3][3] = 11;
	
	//display_ui8matrix (E,0,3,0,3,"%6d ","E");

	erosion(E,img,1,0,3,0,3);
	//display_ui8matrix (img,0,3,0,3,"%6d ","img");

	for(int i=0; i<=3; i++){
		for(int j=0; j<=3; j++){
			if(img[i][j]!= img_ref[i][j]){
				return 0;
			}
		}
	}	
	return 1;
}
int Morpho_dilatation(){
	uint8 c = 1;
	uint8 **E 		= ui8matrix(0,3,0,3);
	uint8 **img 	= ui8matrix(0,3,0,3);
	uint8 **img_ref = ui8matrix(0,3,0,3);

	for(int i=0; i<=3; i++){
		for(int j=0; j<=3; j++){
			E[i][j] = c;
			c++;
		}
	}

	img_ref[0][0] = 6; img_ref[0][1] = 7; img_ref[0][2] = 8; img_ref[0][3] = 8;
	img_ref[1][0] = 10; img_ref[1][1] = 11; img_ref[1][2] = 12; img_ref[1][3] = 12;
	img_ref[2][0] = 14; img_ref[2][1] = 15; img_ref[2][2] = 16; img_ref[2][3] = 16;
	img_ref[3][0] = 14; img_ref[3][1] = 15; img_ref[3][2] = 16; img_ref[3][3] = 16;
	
	//display_ui8matrix (E,0,3,0,3,"%6d ","E");

	dilatation(E,img,1,0,3,0,3);
	//display_ui8matrix (img,0,3,0,3,"%6d ","img");

	for(int i=0; i<=3; i++){
		for(int j=0; j<=3; j++){
			if(img[i][j]!= img_ref[i][j]){
				return 0;
			}
		}
	}	
	return 1;
}

//****** Validation d'optimisation ******//
//*******  1:mouvement  2:morpho  *******//

int check_results(int i) {

	long i0 = 0, i1 = 240-1;
	long j0 = 0, j1 = 320-1;

	int k, ndigit = 0;
	int c;
	char *path_ref;
	char *path;
	char *filename = "car_";
	char *extension = "pgm";
	char  complete_filename[50];

	
	uint8 **img_ref, **img;
	img_ref = ui8matrix(i0,i1,j0,j1);
	img 	= ui8matrix(i0,i1,j0,j1);
	
	if(i == 1){ // sd vs sd_simd
		path_ref = "/home/huiling/HPC/Projet-HPC/sdout/";	
		path = "/home/huiling/HPC/Projet-HPC/sdout_SIMD/";	
	}
	else if(i == 2){
		path_ref = "/home/huiling/HPC/Projet-HPC/morphoout/";	
		path = "/home/huiling/HPC/Projet-HPC/morphoout_SIMD/";	
	}

    for(int k=3001; k<=3199; k++){
		generate_path_filename_k_ndigit_extension(path_ref, filename, k, ndigit, extension, complete_filename);
		MLoadPGM_ui8matrix(complete_filename, i0, i1, j0, j1, img_ref); 
		generate_path_filename_k_ndigit_extension(path, filename, k, ndigit, extension, complete_filename);
		MLoadPGM_ui8matrix(complete_filename, i0, i1, j0, j1, img); 
		c = 0;
		for(int i=0; i<240; i++){
			for(int j=0; j<320; j++){
				if(img[i][j] != img_ref[i][j]) {
					c++;
					if(c>=960){  //1.25%
						free_ui8matrix(img_ref,i0,i1,j0,j1);
						free_ui8matrix(img,i0,i1,j0,j1);
						return 0;
					}
					
				}
			}
		}
		// printf("c = %d\n",c);
	}
	free_ui8matrix(img_ref,i0,i1,j0,j1);
	free_ui8matrix(img,i0,i1,j0,j1);
    return 1;
}