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
//#include "morpho_naive.h"
#include "sd_morpho_naive.h"


uint8 I[200][240][320];		// 200 images 320*240(w*h)
uint8 M[200][240][320];		// images de moyenne
uint8 V[200][240][320];		// images de variance
uint8 O[200][240][320];		// image de difference : en gris
uint8 E[200][240][320];		// image d'etiquette : en gris


void read_pgm_test(){

	char *path = "/home/huiling/Projet-HPC/car3/";	
	char *filename = "car_";
	int k = 3000;
	int ndigit = 0;
	char *extension = "pgm";
	char complete_filename[50];
	char *save_filename = "congratulations.pgm";
	long nrl = 0;
	long nrh = 240;
	long ncl = 0;
	long nch = 320;
	uint8 **I;

	I = ui8matrix(nrl, nrh, ncl, nch); 

	generate_path_filename_k_ndigit_extension(path, filename, k, ndigit, extension, complete_filename);
	MLoadPGM_ui8matrix(complete_filename, nrl, nrh, ncl, nch, I);
	SavePGM_ui8matrix(I, nrl, nrh, ncl, nch, save_filename);

	
}

void sd_morpho_naive(){

	char* path = "/home/huiling/Projet-HPC/car3/";	
	char* filename = "car_";
	int k, ndigit = 0;
	char *extension = "pgm";
	char complete_filename[50];
	long nrl = 0;
	long nrh = 240;
	long ncl = 0;
	long nch = 320;
	uint8 ***I;
	int indice;

	for(k=3000; k<3200; k++){

		indice = k - 3000;
		I[indice] = ui8matrix(nrl, nrh, ncl, nch); 

		generate_path_filename_k_ndigit_extension(path, filename, k, ndigit, extension, complete_filename);
		MLoadPGM_ui8matrix(complete_filename, nrl, nrh, ncl, nch, I[indice]);
	}
	
}