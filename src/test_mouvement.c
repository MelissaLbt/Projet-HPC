/* test de la detection du mouvement : SigmaDelta */

#include <stdio.h>
#include <stdlib.h>

#include "nrdef.h"
#include "nrutil.h"

#include "vnrdef.h"
#include "vnrutil.h"

#include "mutil.h"

#include "mouvement.h"
#include "test_mouvement.h"


void test_mouvement(){

	long i0 = 0, i1 = 240-1;
	long j0 = 0, j1 = 320-1;

	int k, ndigit = 0;
	
	char *path = "/home/huiling/HPC/Projet-HPC/car3/";	
	char *sdout_path = "/home/huiling/HPC/Projet-HPC/sdout/";	
		
	char *filename = "car_";
	char *extension = "pgm";
	char  complete_filename[50];

	uint8 **I0, **I1, **M0, **M1, **V0, **V1, **O, **E;
	
	int64_t start, end;
	int64_t timer_sd = 0;

	//------------ Allocation des tableaux et Initialisation du I[0]----------
	I0 = ui8matrix(i0,i1,j0,j1);
	I1 = ui8matrix(i0,i1,j0,j1);
	M0 = ui8matrix(i0,i1,j0,j1);
	M1 = ui8matrix(i0,i1,j0,j1);
	V0 = ui8matrix(i0,i1,j0,j1);
	V1 = ui8matrix(i0,i1,j0,j1);
	O  = ui8matrix(i0,i1,j0,j1);
	E  = ui8matrix(i0,i1,j0,j1);
	

	generate_path_filename_k_ndigit_extension(path, filename, 3000, ndigit, extension, complete_filename);
	MLoadPGM_ui8matrix(complete_filename, i0, i1, j0, j1, I0); 
	

	//-------------Sigma_Delta-------------

	printf("\n***  Démarrage du Sigma_Delta naïve  ***\n\n");

	start = clocktime();
	SigmaDelta_step0(I0,M0,V0);
	end = clocktime();
	timer_sd += (end-start);

	for(int i=1; i<200; i++){   //traitement a partir de 1

		k = i + 3000;
		generate_path_filename_k_ndigit_extension(path, filename, k, ndigit, extension, complete_filename);
		MLoadPGM_ui8matrix(complete_filename, i0, i1, j0, j1, I1);
		
		start  = clocktime();
		SigmaDelta_1step(I1,M0,M1,O,V0,V1,E);
		end = clocktime();
		timer_sd += (end-start);

		generate_path_filename_k_ndigit_extension(sdout_path, filename, k, ndigit, extension, complete_filename);
		SavePGM_ui8matrix(E, i0, i1, j0, j1, complete_filename);
		
	}

	printf(" - %-*s completed %8" PRId64 " ms\n", 20, "Sigma_Delta naive", timer_sd);
	
	// Desallocation
	free_ui8matrix(I0,i0,i1,j0,j1);
	free_ui8matrix(I1,i0,i1,j0,j1);
	free_ui8matrix(M0,i0,i1,j0,j1);
	free_ui8matrix(M1,i0,i1,j0,j1);
	free_ui8matrix(V0,i0,i1,j0,j1);
	free_ui8matrix(V1,i0,i1,j0,j1);	
	free_ui8matrix(O,i0,i1,j0,j1);
	free_ui8matrix(E,i0,i1,j0,j1);

		
	

	

}
