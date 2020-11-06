/* Algorithme lire images + SD_naive + Morpho_naive */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "nrdef.h"
#include "nrutil.h"

#include "vnrdef.h"
#include "vnrutil.h"

#include "mutil.h"

#include "sd_naive.h"
#include "morpho_naive.h"
#include "sd_morpho_naive.h"


void read_pgm_test(){

	char *path = "/home/huiling/HPC/Projet-HPC/car3/";	
	char *filename = "car_";
	int k = 3000;
	int ndigit = 0;
	char *extension = "pgm";
	char complete_filename[50];
	char *save_filename = "congratulations.pgm";
	long nrl = 0;
	long nrh = 240-1;
	long ncl = 0;
	long nch = 320-1;
	uint8 **I;

	I = ui8matrix(nrl, nrh, ncl, nch); 
	generate_path_filename_k_ndigit_extension(path, filename, k, ndigit, extension, complete_filename);
	MLoadPGM_ui8matrix(complete_filename, nrl, nrh, ncl, nch, I);
	SavePGM_ui8matrix(I, nrl, nrh, ncl, nch, save_filename);

	
}

void sd_morpho_naive(){

	long nrl = 0;
	long nrh = 240-1;
	long ncl = 0;
	long nch = 320-1;
	int indice;
	int b = 1; // pour 3*3
	
	char* path = "/home/huiling/HPC/Projet-HPC/car3/";	
	char* sdout_path = "/home/huiling/HPC/Projet-HPC/sdout/";	
	char* morout_path = "/home/huiling/HPC/Projet-HPC/morphoout/";	

	char* filename = "car_";
	int k, ndigit=0;
	char *extension = "pgm";
	char complete_filename[50];
	char* sdoutname = "car_";

	// SD
	uint8 **I[200];
	uint8 **E[200];
	uint8 **M[2];
	uint8 **V[2];
	uint8 **O;
	
	// Morpho
	uint8 **out; //sortie du Morpho


	//------------Initialisation des tableaux et charger les images----------

	for(k=3000; k<3200; k++){   //traitement a partir de 1
		indice = k - 3000;

		I[indice] = ui8matrix(nrl, nrh, ncl, nch); //allocation du I
		E[indice] = ui8matrix(nrl, nrh, ncl, nch); //allocation du E
		generate_path_filename_k_ndigit_extension(path, filename, k, ndigit, extension, complete_filename);
		MLoadPGM_ui8matrix(complete_filename, nrl, nrh, ncl, nch, I[indice]);//lire et stoker
		
	}

	M[0] = ui8matrix(nrl, nrh, ncl, nch); 
	M[1] = ui8matrix(nrl, nrh, ncl, nch); 
	V[0] = ui8matrix(nrl, nrh, ncl, nch); 
	V[1] = ui8matrix(nrl, nrh, ncl, nch); 
	O    = ui8matrix(nrl, nrh, ncl, nch); 
	out  = ui8matrix(nrl, nrh, ncl, nch); 


	//--------Sigma_Delta----------

	init_SDtabs(I[0],M[0],V[0]);

	for(int i=1; i<200; i++){
		
		Sigma_Delta(I[i],M[0],M[1],O,V[0],V[1],E[i]);
		generate_path_filename_k_ndigit_extension(sdout_path, filename, i+3000, ndigit, extension, complete_filename);
		SavePGM_ui8matrix(E[i], nrl, nrh, ncl, nch, complete_filename);
	}
	

	//--------Morphologie Mathematique--------
	for(int i=1; i<200; i++){

		morpho(E[i],out,b,nrl,nrh,ncl,nch);
	
		generate_path_filename_k_ndigit_extension(morout_path, filename, i+3000, ndigit, extension, complete_filename);
		SavePGM_ui8matrix(out, nrl, nrh, ncl, nch, complete_filename);
	}


	printf("Congratulations!! \nCheck the pictures in the project folder:\n");
	printf("Output of Sigma_Delta : Projet-HPC/sdout\n");
	printf("Output of Morphologie : Projet-HPC/morphoout\n");
	// Desallocation
	for(int i=0; i<200; i++){
		if(i<2){
			if(i==0)
				free_ui8matrix(O,nrl,nrh,ncl,nch);
			free_ui8matrix(M[i],nrl,nrh,ncl,nch);
			free_ui8matrix(V[i],nrl,nrh,ncl,nch);
		}
		free_ui8matrix(I[i],nrl,nrh,ncl,nch);
		free_ui8matrix(E[i],nrl,nrh,ncl,nch);
	}

	free_ui8matrix(out, nrl, nrh, ncl, nch);

}