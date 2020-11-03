/* Algorithme Sigma-Delta version naïve */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define H 240
#define W 320
#define N 2		// a verifier: 2/3/4   //Ecart-Type
#define VMIN 1  
#define VMAX 254
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

int32_t I[200][H][W];		// 200 images 320*240(w*h)
int32_t M[200][H][W];		// images de moyenne
int32_t V[200][H][W];		// images de variance
int32_t O[200][H][W];		// image de difference : en gris
int32_t E[200][H][W];		// image d'etiquette : en gris

// read pgm(P5) image to table I[t][][]
void read_pgm(int *temp){
	int t = *temp-1; //temp start from 1
	FILE *fp;
	char name[60] = "/home/huiling/Projet-HPC/car3/car_"; //change le path pour vos images
	int  nbint;
	char nbstr[5];
    char version[3];
    char line_inutile[256];
    int i, j, c;


    nbint = 3000+t;
    sprintf(nbstr,"%d",nbint);
    strcat(name, nbstr);
    strcat(name,".pgm");


	fp = fopen(name, "rb");
	if (fp == NULL) {
        perror("cannot open image");
        exit(EXIT_FAILURE);
    }
    printf("here3\n");
    fgets(version, 3, fp);
    if (strcmp(version, "P5")) {
        perror("wrong pgm version, need to be P5");
        exit(EXIT_FAILURE);
    }
    fgets(line_inutile, 256, fp);//comment
    fgets(line_inutile, 256, fp);// W H
    fgets(line_inutile, 256, fp);// 255

    for (i = 0; i < H; i++) {
        for (j = 0; j < W; j++) {
            c = fgetc(fp);
            I[t][i][j] = c;
        }
    }

    fclose(fp);

}

// initialisation du M0 et V0 pour la methode SD
void init_tabs(){
	//comment import les images?
	//***** a remplir*****

	//init SD
	for(int i=0; i<H; i++){
		for(int j=0; j<W; j++){
			M[0][i][j] = I[0][i][j];
			V[0][i][j] = VMIN;
		}
	}

}

// methode SD
void Sigma_Delta(int *temp){

	int t = *temp;
	//pseudo-code
	if (t < 1){
		perror("Error(T start from 1):");
        exit(EXIT_FAILURE);
	}
	//step 1: Mt estimation
	for(int i=0; i<H; i++){
		for(int j=0; j<W; j++){
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
	for(int i=0; i<H; i++){
		for(int j=0; j<W; j++){
			O[t][i][j] = (int32_t) abs((int) (M[t][i][j]-I[t][i][j]) );
		}
	}

	//step 3: Vt update
	for(int i=0; i<H; i++){
		for(int j=0; j<W; j++){
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
	for(int i=0; i<H; i++){
		for(int j=0; j<W; j++){
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
	int temp = 1;
	read_pgm(&temp);

	for(int i=0; i<H; i++){
		for(int j=0; j<W; j++){
			printf("%4d",I[0][i][j]);
		}
		printf("\n");
	}

	init_tabs();
	Sigma_Delta(&temp);

	return 0;
}
