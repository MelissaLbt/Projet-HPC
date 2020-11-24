/* Algorithme Sigma-Delta version naïve */

#include <stdio.h>
#include <stdlib.h>

#include "nrdef.h"
#include "nrutil.h"

#include "vnrdef.h"
#include "vnrutil.h"

#include "mutil.h"

#include "mouvement.h"


// initialisation du M0 et V0 pour la methode SD
void SigmaDelta_step0(uint8 **I, uint8 **M, uint8 **V, int i0, int i1, int j0, int j1){

	copy_ui8matrix_ui8matrix(I, i0, i1, j0, j1, M);

	for(int i=i0; i<=i1; i++){
		for(int j=j0; j<=j1; j++){
			V[i][j] = VMIN;
		}
	}
}

// methode SD pour une image

//step 1: Mt estimation

void SigmaDelta_step1(uint8 **I, uint8 **M0, uint8 **M1, int i0, int i1, int j0, int j1){

	for(int i=i0; i<=i1; i++){
		for(int j=j0; j<=j1; j++){
			if (M0[i][j] < I[i][j]){
				M1[i][j] = M0[i][j] + 1;
			}
			else if (M0[i][j] > I[i][j]){
				M1[i][j] = M0[i][j] - 1;
			}
			else{
				M1[i][j] = M0[i][j];
			}
		}
	}
	copy_ui8matrix_ui8matrix(M1, i0, i1, j0, j1, M0);

}

//step 2: Ot difference computation
void SigmaDelta_step2(uint8 **I, uint8 **M1, uint8 **O, int i0, int i1, int j0, int j1){

	
	for(int i=i0; i<=i1; i++){
		for(int j=j0; j<=j1; j++){
			O[i][j] = (uint8) abs((int) (M1[i][j]-I[i][j]) );
		}
	}
}

//step 3: Vt update

void SigmaDelta_step3(uint8 **O, uint8 **V0, uint8 **V1, int i0, int i1, int j0, int j1){

	for(int i=i0; i<=i1; i++){
		for(int j=j0; j<=j1; j++){
			if (V0[i][j] < N*O[i][j]){
				V1[i][j] = V0[i][j] + 1;
			}
			else if (V0[i][j] > N*O[i][j]){
				V1[i][j] = V0[i][j] - 1;
			}
			else {
				V1[i][j] = V0[i][j];
			}

			V1[i][j] = MAX(MIN(V1[i][j], VMAX), VMIN);
		}
	}
	copy_ui8matrix_ui8matrix(V1, i0, i1, j0, j1, V0);

}

//step 4 : Et estimation

void SigmaDelta_step4(uint8 **O, uint8 **V1, uint8 **E, int i0, int i1, int j0, int j1){

	for(int i=i0; i<=i1; i++){
		for(int j=j0; j<=j1; j++){
			if(O[i][j] < V1[i][j]){
				E[i][j] = 0;
			}
			else{
				E[i][j] = 255;
			}
		}
	}
}

void SigmaDelta_integre(uint8 **I1, uint8 **M0, uint8 **M1, uint8 **O, uint8 **V0, uint8 **V1, uint8 **E, int i0, int i1, int j0, int j1)
{
	SigmaDelta_step1(I1,M0,M1,i0,i1,j0,j1);
	SigmaDelta_step2(I1,M1,O,i0,i1,j0,j1);
	SigmaDelta_step3(O,V0,V1,i0,i1,j0,j1);
	SigmaDelta_step4(O,V1,E,i0,i1,j0,j1);
}