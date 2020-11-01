/* Algorithme Sigma-Delta version naïve */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define N 2		// a verifier: 2/3/4
#define VMIN 1
#define VMAX 254
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

int32_t I[200][320][240];		// 200 images 320*240
int32_t M[200][320][240];		// images de moyenne
int32_t V[200][320][240];		// images de variance
int32_t O[200][320][240];		// image de difference : en gris
int32_t E[200][320][240];		// image d'etiquette : en gris

void init_tabs(){
	//comment import les images?
	//***** a remplir*****

	//init SD
	for(int i=0; i<320; i++){
		for(int j=0; j<240; j++){
			M[0][i][j] = I[0][i][j];
			V[0][i][j] = VMIN;
		}
	}
	
}
void Sigma_Delta(int *temp){

	int t = *temp;
	//pseudo-code

	//step 1: Mt estimation
	for(int i=0; i<320; i++){
		for(int j=0; j<240; j++){
			if (M[t-1][i][j] < I[t][i][j]){
				M[t][i][j] = M[t-1][i][j] + 1;
			}
			else if (M[t-1][i][j] > I[t][i][j]){
				M[t][i][j] = M[t-1][i][j] - 1;
			}
			else{
				M[t][i][j] = M[t-1][i][j];
			}
		}
	}

	//step 2: Ot difference computation
	for(int i=0; i<320; i++){
		for(int j=0; j<240; j++){
			O[t][i][j] = (int32_t) abs((int) (M[t][i][j]-I[t][i][j]) );
		}
	}

	//step 3: Vt update
	for(int i=0; i<320; i++){
		for(int j=0; j<240; j++){
			if (V[t-1][i][j] < N*O[t][i][j]){
				V[t][i][j] = V[t-1][i][j] + 1;
			}
			else if (V[t-1][i][j] > N*O[t][i][j]){
				V[t][i][j] = V[t-1][i][j] - 1;
			}
			else {
				V[t][i][j] = V[t-1][i][j];
			}

			V[t][i][j] = MAX(MIN(V[t][i][j], VMAX), VMIN);
		}
	}

	//step 4 : Et estimation
	for(int i=0; i<320; i++){
		for(int j=0; j<240; j++){
			if(O[t][i][j] < V[t][i][j]){
				E[t][i][j] = 0;
			}
			else{
				E[t][i][j] = 1;
			}
		}
	}
}

int main(){
	//Initialisation 
	
	init_tabs();
	Sigma_Delta();

	return 0;
}
