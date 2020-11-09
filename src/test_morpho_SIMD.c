/* test de la detection du mouvement : Morphologie Math */

#include <stdio.h>
#include <stdlib.h>

#include "nrdef.h"
#include "nrutil.h"

#include "vnrdef.h"
#include "vnrutil.h"

#include "mutil.h"

#include "morpho_SIMD.h"
#include "test_morpho_SIMD.h"
#include "mymacro.h"



void test_morpho_SIMD(){

  int b = 1; // border // pour 3*3
  char *format = "%6.2f ";

  int si0, si1, sj0, sj1; // scalar indices
  int vi0, vi1, vj0, vj1; // vector indices
  int mi0, mi1, mj0, mj1; // memory (bounded) indices

  int si0b, si1b, sj0b, sj1b; // scalar indices with border
  int vi0b, vi1b, vj0b, vj1b; // vector indices with border
  int mi0b, mi1b, mj0b, mj1b; // memory (bounded) indices  with border

  si0 = 0; si1 = 240 - 1;
  sj0 = 0; sj1 = 320 - 1;

  si0b = si0 - b; si1b = si1 + b;
  sj0b = sj0 - b; sj1b = sj1 + b;

  uint8  **sE, **sOut;
  vuint8 **vE, **vOut;

  int64_t start, end;
  int64_t timer_morpho = 0;

  int card = card_vuint8(); //Peut-être card = card_vuint8   240

  s2v(si0, si1, sj0, sj1, card, &vi0, &vi1, &vj0, &vj1);
  v2m(vi0, vi1, vj0, vj1, card, &mi0, &mi1, &mj0, &mj1);

  s2v(si0b, si1b, sj0b, sj1b, card, &vi0b, &vi1b, &vj0b, &vj1b);
  v2m(vi0b, vi1b, vj0b, vj1b, card, &mi0b, &mi1b, &mj0b, &mj1b);

  // allocation
  vE  = vui8matrix(vi0b, vi1b, vj0b, vj1b);
  vOut = vui8matrix(vi0,  vi1,  vj0,  vj1);

  // wrappers scalaires
  sE  = (uint8**) vE;
  sOut = (uint8**) vOut;

  // ---------- //
  // -- init -- //
  // ---------- //

  zero_vui8matrix(vE,  vi0b, vi1b, vj0b, vj1b);
  zero_vui8matrix(vOut, vi0, vi1, vj0, vj1);


  // display init data
  /*DEBUG(display_ui8matrix(sE,  0, 240-1, 0, 320-1, format, "sE"));
  DEBUG(display_ui8matrix(sOut, 0, 240-1, 0, 320-1, format, "sOut"));

  DEBUG(display_vui8matrix(vE,  vi0b, vi1b, vj0b, vj1b, format, "vE"));
  DEBUG(display_vui8matrix(vOut, vi0,  vi1,  vj0,  vj1,  format, "vOut"));
  */

  // --> Vérifier initialisation des tableaux après chargement d'une image

	int k, ndigit=0;

  char *sdout_path = "/home/melissa/Documents/HPC/Projet-HPC/sdout_SIMD/"; 
	char *morout_path = "/home/melissa/Documents/HPC/Projet/Projet-HPC/morphoout_SIMD/";

	char *filename = "car_";
	char *extension = "pgm";
	char  complete_filename[50];

  printf("\n***  Démarrage de la chaîne de traitement SIMD: Morphologie Mathématique  ***\n\n");

  for(int i=1; i<200; i++){
    k = i+3000;
    generate_path_filename_k_ndigit_extension(sdout_path, filename, k, ndigit, extension, complete_filename);
    MLoadPGM_ui8matrix(complete_filename, si0, si1, sj0, sj1, sE);

    start  = clocktime();
    morpho(vE, vOut, n, b, vi0, vi1, vj0, vj1);
    end = clocktime();
    timer_morpho += (end-start);

    generate_path_filename_k_ndigit_extension(morout_path, filename, i+3000, ndigit, extension, complete_filename);
    SavePGM_ui8matrix(sOut, si0, si1, sj0, sj1, complete_filename);
  }
  printf(" - %-*s completed %8" PRId64 " ms\n", 20, "Morphologie SIMD", timer_morpho);
	printf("\n***  Fin de la chaîne de traitement SIMD: Morphologie Mathématique ***\n\n");

	printf("Congratulations!! \n\nCheck the pictures in the project folder:\n");
	printf("Output of Morphologie : Projet-HPC/morphoout_SIMD\n");

}
