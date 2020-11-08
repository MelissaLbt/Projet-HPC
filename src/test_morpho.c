/* test de la detection du mouvement : Morphologie Math */

#include <stdio.h>
#include <stdlib.h>

#include "nrdef.h"
#include "nrutil.h"

#include "vnrdef.h"
#include "vnrutil.h"

#include "mutil.h"

#include "morpho.h"
#include "test_morpho.h"
// Ajouter pour test pour cas 5*5

void test_morpho(){

	long nrl = 0;
	long nrh = 240-1;
	long ncl = 0;
	long nch = 320-1;

	int b = 1; // pour 3*3
	int k, ndigit=0;

	char *sdout_path = "/home/huiling/HPC/Projet-HPC/sdout/";
	char *morout_path = "/home/huiling/HPC/Projet-HPC/morphoout/";

	char *filename = "car_";
	char *extension = "pgm";
	char  complete_filename[50];


	uint8 **E;
	uint8 **out; //sortie du Morpho

	int64_t start, end;
	int64_t timer_morpho = 0;

	E   = ui8matrix(nrl, nrh, ncl, nch);
	out = ui8matrix(nrl, nrh, ncl, nch);

	//--------Morphologie Mathematique--------

	for(int i=0; i<200; i++){

		k = i+3000;
		generate_path_filename_k_ndigit_extension(sdout_path, filename, k, ndigit, extension, complete_filename);
		MLoadPGM_ui8matrix(complete_filename, nrl, nrh, ncl, nch, E);

		start  = clocktime();
		morpho(E,out,b,nrl,nrh,ncl,nch);
		end = clocktime();
		timer_morpho += (end-start);

		generate_path_filename_k_ndigit_extension(morout_path, filename, i+3000, ndigit, extension, complete_filename);
		SavePGM_ui8matrix(out, nrl, nrh, ncl, nch, complete_filename);
	}

	printf(" - %-*s completed %8" PRId64 " ms\n", 20, "Morphologie naive", timer_morpho);
	printf("\n***  Fin de la chaîne de traitement naïve  ***\n\n");

	printf("Congratulations!! \n\nCheck the pictures in the project folder:\n");
	printf("Output of Sigma_Delta : Projet-HPC/sdout\n");
	printf("Output of Morphologie : Projet-HPC/morphoout\n");

	// Desallocation
	free_ui8matrix(E, nrl, nrh, ncl, nch);
	free_ui8matrix(out, nrl, nrh, ncl, nch);
}
