/* test de la detection du mouvement : SigmaDelta avec implementation du SIMD SSE2 */
#include <stdio.h>
#include <stdlib.h>

#include "nrdef.h"
#include "nrutil.h"
#include "vnrdef.h"
#include "vnrutil.h"

#include "mutil.h"

#include "mouvement_AVX2.h"
#include "test_mouvement_AVX2.h"

int64_t test_mouvement_AVX2(){

	int card;
	int k, ndigit = 0;

	char *format = "%6.2f ";

	int si0, si1, sj0, sj1; // scalar indices
	int vi0, vi1, vj0, vj1; // vector indices
	int mi0, mi1, mj0, mj1; // memory (bounded) indices

	char *path = "./car3/";
	char *sdout_path = "./sdout_AVX2/";

	char *filename = "car_";
	char *extension = "pgm";
	char  complete_filename[50];

	int64_t start, end;
	int64_t timer_sd = 0;

	uint8  **sI0, **sI1, **sM, **sV, **sE;
	vuint8 **vI0, **vI1, **vM, **vV, **vE;



  // ------------------------- //
  // -- calculs des indices -- //
  // ------------------------- //


  card = card_vuint8();

  si0 = 0; si1 = 240-1;
  sj0 = 0; sj1 = 320-1;

  s2v(si0, si1, sj0, sj1, card, &vi0, &vi1, &vj0, &vj1);
  v2m(vi0, vi1, vj0, vj1, card, &mi0, &mi1, &mj0, &mj1);


  // allocation
	vI0 = vui8matrix(vi0, vi1, vj0, vj1);
	vI1 = vui8matrix(vi0, vi1, vj0, vj1);
	vM = vui8matrix(vi0, vi1, vj0, vj1);
	vV = vui8matrix(vi0, vi1, vj0, vj1);
	vE  = vui8matrix(vi0, vi1, vj0, vj1);

    // wrappers scalaires

	sI0 = (uint8**) vI0;
	sI1 = (uint8**) vI1;
	sM  = (uint8**) vM;
	sV  = (uint8**) vV;
	sE  = (uint8**) vE;

	// ---------- //
  // -- init -- //
  // ---------- //

	generate_path_filename_k_ndigit_extension(path, filename, 3000, ndigit, extension, complete_filename);
	MLoadPGM_ui8matrix(complete_filename, si0, si1, sj0, sj1, sI0);

	zero_vui8matrix(vI1, vi0, vi1, vj0, vj1);
  zero_vui8matrix(vM, vi0, vi1, vj0, vj1);
  zero_vui8matrix(vV, vi0, vi1, vj0, vj1);
  zero_vui8matrix(vE, vi0, vi1, vj0, vj1);

	// ------------ //
  // -- calcul -- //
  // ------------ //

	start = clocktime();
	SigmaDelta_step0_AVX2(vI0,vM,vV,vi0,vi1,vj0,vj1);
	for(int i=1; i<200; i++){   //traitement a partir de 1

		k = i + 3000;
		generate_path_filename_k_ndigit_extension(path, filename, k, ndigit, extension, complete_filename);
		MLoadPGM_ui8matrix(complete_filename, si0, si1, sj0, sj1, sI1);

		SigmaDelta_1step_AVX2(vI1,vM,vV,vE,vi0,vi1,vj0,vj1);
		generate_path_filename_k_ndigit_extension(sdout_path, filename, k, ndigit, extension, complete_filename);
		SavePGM_ui8matrix(sE, si0, si1, sj0, sj1, complete_filename);
	}
	end = clocktime();
	timer_sd += (end-start);

	// ------------------- //
  // -- Desallocation -- //
  // ------------------- //

	free_vui8matrix(vI0, vi0, vi1, vj0, vj1);
	free_vui8matrix(vI1, vi0, vi1, vj0, vj1);
	free_vui8matrix(vM, vi0, vi1, vj0, vj1);
	free_vui8matrix(vV, vi0, vi1, vj0, vj1);
	free_vui8matrix(vE , vi0, vi1, vj0, vj1);

	return timer_sd;
}

int64_t test_mouvement_AVX2_omp(){

	int card;
	int k, ndigit = 0;

	char *format = "%6.2f ";

	int si0, si1, sj0, sj1; // scalar indices
	int vi0, vi1, vj0, vj1; // vector indices
	int mi0, mi1, mj0, mj1; // memory (bounded) indices

	char *path = "./car3/";
	char *sdout_path = "./sdout_AVX2/";
	
	char *filename = "car_";
	char *extension = "pgm";
	char  complete_filename[50];

	int64_t start, end;
	int64_t timer_sd = 0;

	uint8  **sI0, **sI1, **sM, **sV, **sE;
	vuint8 **vI0, **vI1, **vM, **vV, **vE;

  // chronometrie
  //int iter, niter = 4;
  //int run, nrun = 5;
  //double t0, t1, dt, tmin, t;
  //double cycles;

  // ------------------------- //
  // -- calculs des indices -- //
  // ------------------------- //


  card = card_vuint8();

  si0 = 0; si1 = 240-1;
  sj0 = 0; sj1 = 320-1;

  s2v(si0, si1, sj0, sj1, card, &vi0, &vi1, &vj0, &vj1);
  v2m(vi0, vi1, vj0, vj1, card, &mi0, &mi1, &mj0, &mj1);


  // allocation
	vI0 = vui8matrix(vi0, vi1, vj0, vj1);
	vI1 = vui8matrix(vi0, vi1, vj0, vj1);
	vM = vui8matrix(vi0, vi1, vj0, vj1);
	vV = vui8matrix(vi0, vi1, vj0, vj1);
	vE  = vui8matrix(vi0, vi1, vj0, vj1);

    // wrappers scalaires

	sI0 = (uint8**) vI0;
	sI1 = (uint8**) vI1;
	sM  = (uint8**) vM;
	sV  = (uint8**) vV;
	sE  = (uint8**) vE;

	// ---------- //
  // -- init -- //
  // ---------- //

	generate_path_filename_k_ndigit_extension(path, filename, 3000, ndigit, extension, complete_filename);
	MLoadPGM_ui8matrix(complete_filename, si0, si1, sj0, sj1, sI0);

	zero_vui8matrix(vI1, vi0, vi1, vj0, vj1);
	zero_vui8matrix(vM, vi0, vi1, vj0, vj1);
	zero_vui8matrix(vV, vi0, vi1, vj0, vj1);
	zero_vui8matrix(vE, vi0, vi1, vj0, vj1);

	// ------------ //
	// -- calcul -- //
	// ------------ //

	start = clocktime();
	SigmaDelta_step0_AVX2_omp(vI0,vM,vV,vi0,vi1,vj0,vj1);

	for(int i=1; i<200; i++){   //traitement a partir de 1

		k = i + 3000;
		generate_path_filename_k_ndigit_extension(path, filename, k, ndigit, extension, complete_filename);
		MLoadPGM_ui8matrix(complete_filename, si0, si1, sj0, sj1, sI1);

		SigmaDelta_1step_AVX2_omp(vI1,vM,vV,vE,vi0,vi1,vj0,vj1);

		generate_path_filename_k_ndigit_extension(sdout_path, filename, k, ndigit, extension, complete_filename);
		SavePGM_ui8matrix(sE, si0, si1, sj0, sj1, complete_filename);
	}
	end = clocktime();
	timer_sd += (end-start);

	// ------------------- //
  // -- Desallocation -- //
  // ------------------- //

	free_vui8matrix(vI0, vi0, vi1, vj0, vj1);
	free_vui8matrix(vI1, vi0, vi1, vj0, vj1);
	free_vui8matrix(vM, vi0, vi1, vj0, vj1);
	free_vui8matrix(vV, vi0, vi1, vj0, vj1);
	free_vui8matrix(vE , vi0, vi1, vj0, vj1);

	return timer_sd;
}
