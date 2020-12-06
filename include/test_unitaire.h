/* --------------------- */
/* --- test_unitaire.h --- */
/* --------------------- */

#ifndef __TEST_UNITAIRE_H__
#define __TEST_UNITAIRE_H__


int SigmaDelta_step0_tu();
int SigmaDelta_step1_tu();
int SigmaDelta_step2_tu();
int SigmaDelta_step3_tu();
int SigmaDelta_step4_tu();
int SigmaDelta_integration_tu();

int Morpho_initbord_tu();
int Morpho_erosion_tu();
int Morpho_dilatation_tu();
int Morpho_integration_tu();

int check_results(int i);


#endif
