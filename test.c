/* test du fonction read_pgm */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

int32_t tab[240][320];


void read_pgm(){
	char name[] = "/home/huiling/Projet-HPC/car3/car_3008.pgm";
	FILE *fp;
	char version[3];
	char line_inutile[256];
	int i,j;
	int c;

	fp = fopen(name, "rb");
	if (fp == NULL) {
        perror("cannot open image");
        exit(EXIT_FAILURE);
    }

    fgets(version, 3, fp);
    if (strcmp(version, "P5")) {
        perror("wrong pgm version, need to be P5");
        exit(EXIT_FAILURE);
    }
    fgets(line_inutile, 256, fp);//comment
    fgets(line_inutile, 256, fp);// 320 240
    fgets(line_inutile, 256, fp);// 255

    for (i = 0; i < 240; i++) {
        for (j = 0; j < 320; j++) {
            c = fgetc(fp);
            tab[i][j] = c;
        }
    }

    fclose(fp);
}

int main(){
	

	read_pgm();
	for(int i=0; i<240; i++){
		for(int j=0; j<320; j++){
			printf("%4d",tab[i][j]);
		}
		printf("\n");
	}

	return 0;
}
