/* Algorithme lire images + SD_naive + Morpho_naive */

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
//#include "morpho_naive.h"
#include "sd_morpho_naive.h"


uint8 I[200][240][320];		// 200 images 320*240(w*h)
uint8 M[200][240][320];		// images de moyenne
uint8 V[200][240][320];		// images de variance
uint8 O[200][240][320];		// image de difference : en gris
uint8 E[200][240][320];		// image d'etiquette : en gris


void sd_morpho_naive(){

	char* path = "/home/huiling/Projet-HPC/car3/";	
	char* filename = "car_";
	int k;
	
	char name[60] = car_"; //change le path pour vos images
	//load pgm

	LoadPGM_ui8matrix();
}