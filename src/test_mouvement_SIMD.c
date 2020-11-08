/* test de la detection du mouvement : SigmaDelta avec implementation du SIMD */
#include <stdio.h>
#include <stdlib.h>

#include "nrdef.h"
#include "nrutil.h"

#include "vnrdef.h"
#include "vnrutil.h"

#include "mutil.h"

#include "mouvement_SIMD.h"
#include "test_mouvement_SIMD.h"

void test_mouvement_SIMD(){

	int h,w;
	int card;
	int k, ndigit = 0;

    char *format = "%6.2f ";

    int si0, si1, sj0, sj1; // scalar indices
    int vi0, vi1, vj0, vj1; // vector indices
    int mi0, mi1, mj0, mj1; // memory (bounded) indices
    
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

	uint8  **sI0, **sI1, **sM0, **sM1, **sV0, **sV1, **sO, **sE;
	vuint8 **vI0, **vI1, **vM0, **vM1, **vV0, **vV1, **vO, **vE;

    // chronometrie
    //int iter, niter = 4;
    //int run, nrun = 5;
    //double t0, t1, dt, tmin, t;
    //double cycles;
      
    puts("===========================");
    puts("=== test_mouvement_SIMD ===");
    puts("===========================");
 
 	h = 240;
    w = 320;
    printf("h = %d\nw = %d\n\n", h, w);

    // ------------------------- //
    // -- calculs des indices -- //
    // ------------------------- //
    
    //b = 2; // 1 for 3x3, 2 for 5x5
    
    card = card = card_vuint8();
    
    si0 = 0; si1 = h-1;
    sj0 = 0; sj1 = w-1;
     
    s2v(si0, si1, sj0, sj1, card, &vi0, &vi1, &vj0, &vj1);
    v2m(vi0, vi1, vj0, vj1, card, &mi0, &mi1, &mj0, &mj1);
    
    // allocation
	vI0 = vui8matrix(vi0, vi1, vj0, vj1);
	vI1 = vui8matrix(vi0, vi1, vj0, vj1);
	vM0 = vui8matrix(vi0, vi1, vj0, vj1);
	vM1 = vui8matrix(vi0, vi1, vj0, vj1);
	vV0 = vui8matrix(vi0, vi1, vj0, vj1);
	vV1 = vui8matrix(vi0, vi1, vj0, vj1);
	vO  = vui8matrix(vi0, vi1, vj0, vj1);
	vE  = vui8matrix(vi0, vi1, vj0, vj1);
    
    // wrappers scalaires
  
	sI0 = (uint8**) vI0;
	sI1 = (uint8**) vI1;
	sM0 = (uint8**) vM0;
	sM1 = (uint8**) vM1;
	sV0 = (uint8**) vV0;
	sV1 = (uint8**) vV1;
	sO  = (uint8**) vO;
	sE  = (uint8**) vE;
		
	// ---------- //
    // -- init -- //
    // ---------- //
    
	generate_path_filename_k_ndigit_extension(path, filename, 3000, ndigit, extension, complete_filename);
	MLoadPGM_ui8matrix(complete_filename, si0, si1, sj0, sj1, sI0);
	
	zero_vui8matrix(vI1, vi0, vi1, vj0, vj1);
    zero_vui8matrix(vM0, vi0, vi1, vj0, vj1);
    zero_vui8matrix(vM1, vi0, vi1, vj0, vj1);
    zero_vui8matrix(vV0, vi0, vi1, vj0, vj1);
    zero_vui8matrix(vV1, vi0, vi1, vj0, vj1);
    zero_vui8matrix(vO , vi0, vi1, vj0, vj1);
    zero_vui8matrix(vE , vi0, vi1, vj0, vj1);

    // ------------ //
    // -- calcul -- //
    // ------------ //

    //-- Sigma_Delta --//

	printf("\n***  Démarrage du Sigma_Delta en SIMD  ***\n\n");

	start = clocktime();
	SigmaDelta_step0_SIMD(vI0,vM0,vV0,vi0,vi1,vj0,vj1);
	end = clocktime();
	timer_sd += (end-start);

	for(int i=1; i<200; i++){   //traitement a partir de 1

		k = i + 3000;
		generate_path_filename_k_ndigit_extension(path, filename, k, ndigit, extension, complete_filename);
		MLoadPGM_ui8matrix(complete_filename, si0, si1, sj0, sj1, sI1);
		
		start  = clocktime();
		SigmaDelta_1step_SIMD(vI1,vM0,vM1,vO,vV0,vV1,vE,vi0,vi1,vj0,vj1);
		// update M0,V0
		copy_ui8matrix_ui8matrix(sM1, si0, si1, sj0, sj1, sM0);
		copy_ui8matrix_ui8matrix(sV1, si0, si1, sj0, sj1, sV0);

		end = clocktime();
		timer_sd += (end-start);

		generate_path_filename_k_ndigit_extension(sdout_path, filename, k, ndigit, extension, complete_filename);
		SavePGM_ui8matrix(sE, si0, si1, sj0, sj1, complete_filename);
		
	}

	printf(" - %-*s completed %8" PRId64 " ms\n", 20, "Sigma_Delta SIMD", timer_sd);
	
	// ------------------- //
    // -- Desallocation -- //
    // ------------------- //
	free_vui8matrix(vI0, vi0, vi1, vj0, vj1);
	free_vui8matrix(vI1, vi0, vi1, vj0, vj1);
	free_vui8matrix(vM0, vi0, vi1, vj0, vj1);
	free_vui8matrix(vM1, vi0, vi1, vj0, vj1);
	free_vui8matrix(vV0, vi0, vi1, vj0, vj1);
	free_vui8matrix(vV1, vi0, vi1, vj0, vj1);
	free_vui8matrix(vO , vi0, vi1, vj0, vj1);
	free_vui8matrix(vE , vi0, vi1, vj0, vj1);
}