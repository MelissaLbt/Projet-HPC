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

int64_t test_morpho(){

	long i0 = 0;
	long i1 = 240-1;
	long j0 = 0;
	long j1 = 320-1;

	int b = 2; // pour 3*3
	int k, ndigit=0;

	// char *sdout_path = "/home/huiling/HPC/Projet-HPC/sdout/";
	// char *morout_path = "/home/huiling/HPC/Projet-HPC/morphoout/";

	char *sdout_path = "/home/melissa/Documents/HPC/Projet/Projet-HPC/sdout/";
	char *morout_path = "/home/melissa/Documents/HPC/Projet/Projet-HPC/morphoout/";

	char *filename = "car_";
	char *extension = "pgm";
	char  complete_filename[50];


	uint8 **E;
	uint8 **out; //sortie du Morpho

	int64_t start, end;
	int64_t timer_morpho = 0;

	E   = ui8matrix(i0, i1, j0, j1);
	out = ui8matrix(i0, i1, j0, j1);

	//--------Morphologie Mathematique--------
	// generate_path_filename_k_ndigit_extension(sdout_path, filename, 3001, ndigit, extension, complete_filename);
	// MLoadPGM_ui8matrix(complete_filename, i0, i1, j0, j1, E);

	// morpho(E,out,b,i0,i1,j0,j1);

	for(int i=1; i<200; i++){

		k = i+3000;
		generate_path_filename_k_ndigit_extension(sdout_path, filename, k, ndigit, extension, complete_filename);
		MLoadPGM_ui8matrix(complete_filename, i0, i1, j0, j1, E);

		start  = clocktime();
		morpho(E,out,b,i0,i1,j0,j1);
		end = clocktime();
		timer_morpho += (end-start);

		generate_path_filename_k_ndigit_extension(morout_path, filename, k, ndigit, extension, complete_filename);
		SavePGM_ui8matrix(out, i0, i1, j0, j1, complete_filename);
	}

	// Desallocation
	free_ui8matrix(E, i0, i1, j0, j1);
	free_ui8matrix(out, i0, i1, j0, j1);

	return timer_morpho;
}
