/* Algorithme Sigma-Delta version naïve */

#include <stdio.h>
#include <stdlib.h>

#include "nrdef.h"
#include "nrutil.h"

#include "vnrdef.h"
#include "vnrutil.h"

#include "mutil.h"

#include "sd_naive.h"


// initialisation du M0 et V0 pour la methode SD
void init_SDtabs(uint8 **I, uint8 **M, uint8 **V){
	//il faut que I[0] est deja rempli

	copy_ui8matrix_ui8matrix(I, 0, 240-1, 0, 320-1, M);

	for(int i=0; i<H; i++){
		for(int j=0; j<W; j++){
			//M[i][j] = I[i][j];
			V[i][j] = VMIN;
		}
	}
}

// methode SD pour une image
void Sigma_Delta(uint8 **I, uint8 **M0, uint8 **M1, uint8 **O, uint8 **V0, uint8 **V1, uint8 **E){

	//step 1: Mt estimation
	for(int i=0; i<H; i++){
		for(int j=0; j<W; j++){
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

	//step 2: Ot difference computation
	for(int i=0; i<H; i++){
		for(int j=0; j<W; j++){
			O[i][j] = (int32_t) abs((int) (M1[i][j]-I[i][j]) );
		}
	}

	//step 3: Vt update
	for(int i=0; i<H; i++){
		for(int j=0; j<W; j++){
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

	//step 4 : Et estimation
	for(int i=0; i<H; i++){
		for(int j=0; j<W; j++){
			if(O[i][j] < V1[i][j]){
				E[i][j] = 0;
			}
			else{
				E[i][j] = 255;
			}
		}
	}

	// update M0,V0
	copy_ui8matrix_ui8matrix(M1, 0, 240-1, 0, 320-1, M0);
	copy_ui8matrix_ui8matrix(V1, 0, 240-1, 0, 320-1, V0);
}

