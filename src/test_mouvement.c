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
	long nrl = 0;
	long nrh = 240-1;
	long ncl = 0;
	long nch = 320-1;

	int b = 1; // pour 3*3
	int k, ndigit=0;
	
	char *path = "/home/huiling/HPC/Projet-HPC/car3/";	
	char *sdout_path = "/home/huiling/HPC/Projet-HPC/sdout/";	
		
	char *filename = "car_";
	char *extension = "pgm";
	char  complete_filename[50];

	uint8 **I[2];
	uint8 **M[2];
	uint8 **V[2];
	uint8 **O;
	uint8 **E;
	
	int64_t start, end;
	int64_t timer_sd = 0;

	//------------ Allocation des tableaux et Initialisation du I[0]----------
	for(int i=0; i<2; i++){	
		
		if(i==0){
			O = ui8matrix(nrl,nrh,ncl,nch);
			E = ui8matrix(nrl,nrh,ncl,nch);
		}
		I[i] = ui8matrix(nrl,nrh,ncl,nch);
		M[i] = ui8matrix(nrl,nrh,ncl,nch);
		V[i] = ui8matrix(nrl,nrh,ncl,nch);
	}

	generate_path_filename_k_ndigit_extension(path, filename, 3000, ndigit, extension, complete_filename);
	MLoadPGM_ui8matrix(complete_filename, nrl, nrh, ncl, nch, I[0]); 
	

	//-------------Sigma_Delta-------------

	printf("\n***  Démarrage de la chaîne de traitement naïve  ***\n\n");

	start = clocktime();
	SigmaDelta_step0(I[0],M[0],V[0]);
	end = clocktime();
	timer_sd += (end-start);

	for(int i=1; i<200; i++){   //traitement a partir de 1

		k = i + 3000;
		generate_path_filename_k_ndigit_extension(path, filename, k, ndigit, extension, complete_filename);
		MLoadPGM_ui8matrix(complete_filename, nrl, nrh, ncl, nch, I[1]);
		
		start  = clocktime();
		SigmaDelta_1step(I[1],M[0],M[1],O,V[0],V[1],E);
		end = clocktime();
		timer_sd += (end-start);

		generate_path_filename_k_ndigit_extension(sdout_path, filename, k, ndigit, extension, complete_filename);
		SavePGM_ui8matrix(E, nrl, nrh, ncl, nch, complete_filename);
		
	}

	printf(" - %-*s completed %8" PRId64 " ms\n", 20, "Sigma_Delta naive", timer_sd);
	
	// Desallocation
	for(int i=0; i<2; i++){	

		if(i==0){
			free_ui8matrix(O,nrl,nrh,ncl,nch);
			free_ui8matrix(E,nrl,nrh,ncl,nch);
		}
		free_ui8matrix(I[i],nrl,nrh,ncl,nch);
		free_ui8matrix(M[i],nrl,nrh,ncl,nch);
		free_ui8matrix(V[i],nrl,nrh,ncl,nch);
	}

	

}
