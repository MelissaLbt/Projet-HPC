/* Algorithme Sigma-Delta version naïve */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "nrdef.h"
#include "nrutil.h"

#include "vnrdef.h"
#include "vnrutil.h"

#include "mutil.h"

#include "sd_naive.h"


/*// read pgm(P5) image to table I[t][][]
void read_pgm(int *temp){
	int t = *temp-1; //temp start from 1
	FILE *fp;
	char name[60] = "/home/huiling/Projet-HPC/car3/car_"; //change le path pour vos images
	int  imgint;
	char imgstr[5];
    char version[3];
    char line_inutile[256];
    int i, j, c;


    imgint = 3000+t;
    sprintf(imgstr,"%d",imgint);
    strcat(name, imgstr);
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

}*/

// initialisation du M0 et V0 pour la methode SD
void init_tabs(){/*
	//il faut que I[0][][] est deja rempli
	//init SD
	for(int i=0; i<H; i++){
		for(int j=0; j<W; j++){
			M[0][i][j] = I[0][i][j];
			V[0][i][j] = VMIN;
		}
	}
*/
}

// methode SD pour une image
void Sigma_Delta(int *temp){
/*
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
	}*/
}

