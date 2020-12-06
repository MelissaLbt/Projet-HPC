#include <stdio.h>
#include <stdlib.h>

#include "nrdef.h"
#include "nrutil.h"

#include "vnrdef.h"
#include "vnrutil.h"

#include "mutil.h"

#include "mymacro.h"
#include "test_unitaire.h"
#include "mouvement.h"
#include "morpho.h"

//********     Test unitaire pour Sigma Delta	    ********//
//********     1 test par étape + test intégré      ********//
//******** 	  sur des petites matrix prédefinies 	********//
//******** comparer les résultats avec la référence ********//


//	Test unitaire 
//	Entrée: 	I0, matrix 4x4 
//	Méthode:	SigmaDelta_step0
//	Sortie: 	M0,V0

int SigmaDelta_step0_tu(){

	uint8 **I0 = ui8matrix(0,3,0,3);
	uint8 **M0 = ui8matrix(0,3,0,3);
	uint8 **V0 = ui8matrix(0,3,0,3);

	for(int i=0; i<=3; i++){
		for(int j=0; j<=3; j++){
			I0[i][j] = i+j;

		}
	}
	DEBUG(display_ui8matrix (I0,0,3,0,3,"%6d ","my I0")); DEBUG("");

	SigmaDelta_step0(I0,M0,V0,0,3,0,3);

	for(int i=0; i<=3; i++){
		for(int j=0; j<=3; j++){
			if(M0[i][j]!=I0[i][j]){
				free_ui8matrix(I0,0,3,0,3);
				free_ui8matrix(M0,0,3,0,3);
				free_ui8matrix(V0,0,3,0,3);
				return 0;
			}
			if(V0[i][j]!= 1){
				free_ui8matrix(I0,0,3,0,3);
				free_ui8matrix(M0,0,3,0,3);
				free_ui8matrix(V0,0,3,0,3);
				return 0;
			}
		}
	}
	free_ui8matrix(I0,0,3,0,3);
	free_ui8matrix(M0,0,3,0,3);
	free_ui8matrix(V0,0,3,0,3);
	return 1;
}

//	Test unitaire 
//	Entrée: 	I0,M0, matrix 4x4 
//	Méthode:	SigmaDelta_step1
//	Sortie: 	M1

int SigmaDelta_step1_tu(){

	uint8 **I1 = ui8matrix(0,3,0,3);
	uint8 **M0 = ui8matrix(0,3,0,3);
	uint8 **M1 = ui8matrix(0,3,0,3);
	uint8 **M1_ref = ui8matrix(0,3,0,3);

	for(int i=0; i<=3; i++){
		for(int j=0; j<=3; j++){
			I1[i][j] = 3;
			M0[i][j] = i+j;
		}
	}

	M1_ref[0][0] = 1; M1_ref[0][1] = 2; M1_ref[0][2] = M1_ref[0][3] = 3;
	M1_ref[1][0] = 2; M1_ref[1][1] = 	M1_ref[1][2] = M1_ref[1][3] = 3;
	M1_ref[2][0] = M1_ref[2][1] = M1_ref[2][2] = 3; M1_ref[2][3] = 4;
	M1_ref[3][0] = M1_ref[3][1] = 3;	M1_ref[3][2] = 4; M1_ref[3][3] = 5;
	DEBUG(display_ui8matrix (I1,0,3,0,3,"%6d ","I1")); DEBUG("");
	DEBUG(display_ui8matrix (M0,0,3,0,3,"%6d ","M0")); DEBUG("");
	DEBUG(display_ui8matrix (M1_ref,0,3,0,3,"%6d ","M1_ref")); DEBUG("");

	SigmaDelta_step1(I1,M0,M1,0,3,0,3);
	DEBUG(display_ui8matrix (M1,0,3,0,3,"%6d ","M1")); DEBUG("");

	for(int i=0; i<=3; i++){
		for(int j=0; j<=3; j++){
			if(M1[i][j]!= M1_ref[i][j] || M0[i][j]!= M1_ref[i][j]){
				free_ui8matrix(I1,0,3,0,3);
				free_ui8matrix(M0,0,3,0,3);
				free_ui8matrix(M1,0,3,0,3);
				free_ui8matrix(M1_ref,0,3,0,3);
				return 0;
			}
		}
	}
	free_ui8matrix(I1,0,3,0,3);
	free_ui8matrix(M0,0,3,0,3);
	free_ui8matrix(M1,0,3,0,3);
	free_ui8matrix(M1_ref,0,3,0,3);
	return 1;
}

//	Test unitaire 
//	Entrée: 	I1,M1, matrix 4x4 
//	Méthode:	SigmaDelta_step2
//	Sortie: 	O

int SigmaDelta_step2_tu(){

	uint8 **I1 = ui8matrix(0,3,0,3);
	uint8 **M1 = ui8matrix(0,3,0,3);
	uint8 **O  = ui8matrix(0,3,0,3);
	uint8 **O_ref = ui8matrix(0,3,0,3);

	for(int i=0; i<=3; i++){
		for(int j=0; j<=3; j++){
			I1[i][j] = 3;
			M1[i][j] = i+j;
		}
	}
	DEBUG(display_ui8matrix (I1,0,3,0,3,"%6d ","I1")); DEBUG("");
	DEBUG(display_ui8matrix (M1,0,3,0,3,"%6d ","M1")); DEBUG("");

	O_ref[0][0] = 3; O_ref[0][1] = 2; O_ref[0][2] = 1; O_ref[0][3] = 0;
	O_ref[1][0] = 2; O_ref[1][1] = 1; O_ref[1][2] =	0; O_ref[1][3] = 1;
	O_ref[2][0] = 1; O_ref[2][1] = 0; O_ref[2][2] = 1; O_ref[2][3] = 2;
	O_ref[3][0] = 0; O_ref[3][1] = 1; O_ref[3][2] = 2; O_ref[3][3] = 3;
	DEBUG(display_ui8matrix (O_ref,0,3,0,3,"%6d ","O_ref")); DEBUG("");

	SigmaDelta_step2(I1,M1,O,0,3,0,3);
	DEBUG(display_ui8matrix (O,0,3,0,3,"%6d ","O")); DEBUG("");

	for(int i=0; i<=3; i++){
		for(int j=0; j<=3; j++){
			if(O[i][j]!= O_ref[i][j]){
				free_ui8matrix(I1,0,3,0,3);
				free_ui8matrix(M1,0,3,0,3);
				free_ui8matrix(O,0,3,0,3);
				free_ui8matrix(O_ref,0,3,0,3);
				return 0;
			}
		}
	}
	free_ui8matrix(I1,0,3,0,3);
	free_ui8matrix(M1,0,3,0,3);
	free_ui8matrix(O,0,3,0,3);
	free_ui8matrix(O_ref,0,3,0,3);
	return 1;
}

//	Test unitaire 
//	Entrée: 	O,V0, matrix 4x4 
//	Méthode:	SigmaDelta_step3
//	Sortie: 	V1

int SigmaDelta_step3_tu(){

	uint8 **O = ui8matrix(0,3,0,3);
	uint8 **V0 = ui8matrix(0,3,0,3);
	uint8 **V1 = ui8matrix(0,3,0,3);
	uint8 **V1_ref = ui8matrix(0,3,0,3);

	for(int i=0; i<=3; i++){
		for(int j=0; j<=3; j++){
			O[i][j] = 1;  //n*O=2
			V0[i][j] = i+j;
		}
	}
	DEBUG(display_ui8matrix (O,0,3,0,3,"%6d ","O")); DEBUG("");
	DEBUG(display_ui8matrix (V0,0,3,0,3,"%6d ","V0")); DEBUG("");

	O[0][0] = 0; V0[0][0] = 1; //tester le seuil
	DEBUG(display_ui8matrix (O,0,3,0,3,"%6d ","O")); DEBUG("");
	DEBUG(display_ui8matrix (V0,0,3,0,3,"%6d ","V0")); DEBUG("");

	V1_ref[0][0] = 1; V1_ref[0][1] =    V1_ref[0][2] =    V1_ref[0][3] = 2;
	V1_ref[1][0] =    V1_ref[1][1] = 	V1_ref[1][2] = 2; V1_ref[1][3] = 3;
	V1_ref[2][0] = 	  V1_ref[2][1] = 2; V1_ref[2][2] = 3; V1_ref[2][3] = 4;
	V1_ref[3][0] = 2; V1_ref[3][1] = 3;	V1_ref[3][2] = 4; V1_ref[3][3] = 5;
	DEBUG(display_ui8matrix (V1_ref,0,3,0,3,"%6d ","V1_ref")); DEBUG("");

	SigmaDelta_step3(O,V0,V1,0,3,0,3);
	DEBUG(display_ui8matrix (V1,0,3,0,3,"%6d ","V1")); DEBUG("");

	for(int i=0; i<=3; i++){
		for(int j=0; j<=3; j++){
			if(V1[i][j]!= V1_ref[i][j] || V0[i][j]!= V1_ref[i][j]){
				free_ui8matrix(O,0,3,0,3);
				free_ui8matrix(V0,0,3,0,3);
				free_ui8matrix(V1,0,3,0,3);
				free_ui8matrix(V1_ref,0,3,0,3);
				return 0;
			}
		}
	}
	free_ui8matrix(O,0,3,0,3);
	free_ui8matrix(V0,0,3,0,3);
	free_ui8matrix(V1,0,3,0,3);
	free_ui8matrix(V1_ref,0,3,0,3);
	return 1;
}

//	Test unitaire 
//	Entrée: 	O,V1, matrix 4x4 
//	Méthode:	SigmaDelta_step4
//	Sortie: 	E

int SigmaDelta_step4_tu(){

	uint8 **O  = ui8matrix(0,3,0,3);
	uint8 **V1 = ui8matrix(0,3,0,3);
	uint8 **E  = ui8matrix(0,3,0,3);
	uint8 **E_ref = ui8matrix(0,3,0,3);

	for(int i=0; i<=3; i++){
		for(int j=0; j<=3; j++){
			O[i][j] = 3;
			V1[i][j] = i+j;
		}
	}
	DEBUG(display_ui8matrix (O,0,3,0,3,"%6d ","O")); DEBUG("");
	DEBUG(display_ui8matrix (V1,0,3,0,3,"%6d ","V1"));

	E_ref[0][0] = E_ref[0][1] = E_ref[0][2] = E_ref[0][3] = 255;
	E_ref[1][0] = E_ref[1][1] = E_ref[1][2] = 255; E_ref[1][3] = 0;
	E_ref[2][0] = E_ref[2][1] = 255; E_ref[2][2] = E_ref[2][3] = 0;
	E_ref[3][0] = 255; E_ref[3][1] = E_ref[3][2] = E_ref[3][3] = 0;
	DEBUG(display_ui8matrix (E_ref,0,3,0,3,"%6d ","E_ref")); DEBUG("");

	SigmaDelta_step4(O,V1,E,0,3,0,3);
	DEBUG(display_ui8matrix (E,0,3,0,3,"%6d ","E")); DEBUG("");

	for(int i=0; i<=3; i++){
		for(int j=0; j<=3; j++){
			if(E[i][j]!= E_ref[i][j]){
				free_ui8matrix(O,0,3,0,3);
				free_ui8matrix(V1,0,3,0,3);
				free_ui8matrix(E,0,3,0,3);
				free_ui8matrix(E_ref,0,3,0,3);
				return 0;
			}
		}
	}
	free_ui8matrix(O,0,3,0,3);
	free_ui8matrix(V1,0,3,0,3);
	free_ui8matrix(E,0,3,0,3);
	free_ui8matrix(E_ref,0,3,0,3);
	return 1;
}

//	Test intégré pour l'algorithme Sigma Delta 
//	Entrée: 	I1,M0,M1,O,V0,V1, matrix 4x4 
//	Méthode:	SigmaDelta_integre
//	Sortie: 	E

int SigmaDelta_integration_tu(){
	uint8 **I1, **M0, **M1, **V0, **V1, **O, **E, **E_ref;

	I1 = ui8matrix(0,3,0,3); zero_ui8matrix(I1,0,3,0,3);
	M0 = ui8matrix(0,3,0,3); zero_ui8matrix(M0,0,3,0,3);
	M1 = ui8matrix(0,3,0,3); zero_ui8matrix(M1,0,3,0,3);
	V0 = ui8matrix(0,3,0,3); zero_ui8matrix(V0,0,3,0,3);
	V1 = ui8matrix(0,3,0,3); zero_ui8matrix(V1,0,3,0,3);
	O  = ui8matrix(0,3,0,3); zero_ui8matrix(O,0,3,0,3);
	E  = ui8matrix(0,3,0,3); zero_ui8matrix(E,0,3,0,3);
	E_ref  = ui8matrix(0,3,0,3); zero_ui8matrix(E_ref,0,3,0,3);

	I1[0][0]=3; I1[0][1]=2;
	I1[1][0]=2; I1[1][1]=1;
	I1[2][0]=2; I1[2][1]=1;
	I1[3][0]=1;
	DEBUG(display_ui8matrix(I1,0,3,0,3,"%6d ","I1")); DEBUG("");

	M0[0][0]=5;
	M0[1][0]=1; M0[1][1]=4;
	M0[2][0]=1; M0[2][1]=3;
	M0[3][0]=1; M0[3][1]=2;
	DEBUG(display_ui8matrix(M0,0,3,0,3,"%6d ","M0")); DEBUG("");

	for(int i=0;i<=3;i++){
		for(int j=0;j<=3;j++){
			V0[i][j]=1;
		}
	}
	DEBUG(display_ui8matrix(V0,0,3,0,3,"%6d ","V0")); DEBUG("");

	E_ref[1][1] = 255;
 	DEBUG(display_ui8matrix(E_ref,0,3,0,3,"%6d ","E_ref")); DEBUG("");

	SigmaDelta_integre(I1,M0,M1,O,V0,V1,E,0,3,0,3);
	DEBUG(display_ui8matrix(M1,0,3,0,3,"%6d ","M1")); DEBUG("");
	DEBUG(display_ui8matrix(O,0,3,0,3,"%6d ","O")); DEBUG("");
	DEBUG(display_ui8matrix(V1,0,3,0,3,"%6d ","V1")); DEBUG("");
	DEBUG(display_ui8matrix(E,0,3,0,3,"%6d ","E")); DEBUG("");


	for(int i=0;i<=3;i++){
		for(int j=0;j<=3;j++){
			if(E_ref[i][j] != E[i][j]){
				free_ui8matrix(I1,0,3,0,3);
				free_ui8matrix(M0,0,3,0,3);
				free_ui8matrix(M1,0,3,0,3);
				free_ui8matrix(V0,0,3,0,3);
				free_ui8matrix(V1,0,3,0,3);
				free_ui8matrix(O,0,3,0,3);
				free_ui8matrix(E,0,3,0,3);
				free_ui8matrix(E_ref,0,3,0,3);
				return 0;

			}
		}
	}
	free_ui8matrix(I1,0,3,0,3);
	free_ui8matrix(M0,0,3,0,3);
	free_ui8matrix(M1,0,3,0,3);
	free_ui8matrix(V0,0,3,0,3);
	free_ui8matrix(V1,0,3,0,3);
	free_ui8matrix(O,0,3,0,3);
	free_ui8matrix(E,0,3,0,3);
	free_ui8matrix(E_ref,0,3,0,3);
	return 1;
}

//********  Test unitaire pour Morpho Mathémathique	********//
//********Init du bord/erosion/dilataion et integre ********//
//******** 	  sur des petites matrix prédefinies 	********//
//******** comparer les résultats avec la référence ********//


//	Test unitaire 
//	Entrée: 	E, matrix initialisé en 2x2, alloué en 6x6 
//	Méthode:	init_bord
//	Sortie: 	E1, matrix attribué en 4x4, avec bord supplémentaire de 1
//              E2, matrix attribué en 6x6, avec bord supplémentaire de 2
int Morpho_initbord_tu(){

	uint8 **E = ui8matrix(-2,3,-2,3);
	uint8 **E1_ref = ui8matrix(-2,3,-2,3);
	uint8 **E2_ref = ui8matrix(-2,3,-2,3);

	zero_ui8matrix(E,-2,3,-2,3);
	zero_ui8matrix(E1_ref,-2,3,-2,3);
	zero_ui8matrix(E2_ref,-2,3,-2,3);

	E[0][0] = 1; E[0][1] = 2;
	E[1][0] = 3; E[1][1] = 4;
	DEBUG(display_ui8matrix(E,-2,3,-2,3,"%6d ","E")); DEBUG("");

	E1_ref[-2][-2] = 0; E1_ref[-2][-1] = 0; E1_ref[-2][0] = 0; E1_ref[-2][1] = 0; E1_ref[-2][2] = 0; E1_ref[-2][3] = 0;
	E1_ref[-1][-2] = 0; E1_ref[-1][-1] = 1; E1_ref[-1][0] = 1; E1_ref[-1][1] = 2; E1_ref[-1][2] = 2; E1_ref[-1][3] = 0;
	E1_ref[0][-2] = 0; E1_ref[0][-1] = 1; E1_ref[0][0] = 1; E1_ref[0][1] = 2; E1_ref[0][2] = 2; E1_ref[0][3] = 0;
	E1_ref[1][-2] = 0; E1_ref[1][-1] = 3; E1_ref[1][0] = 3; E1_ref[1][1] = 4; E1_ref[1][2] = 4; E1_ref[1][3] = 0;
	E1_ref[2][-2] = 0; E1_ref[2][-1] = 3; E1_ref[2][0] = 3; E1_ref[2][1] = 4; E1_ref[2][2] = 4; E1_ref[2][3] = 0;
	E1_ref[3][-2] = 0; E1_ref[3][-1] = 0; E1_ref[3][0] = 0; E1_ref[3][1] = 0; E1_ref[3][2] = 0; E1_ref[3][3] = 0;
	DEBUG(display_ui8matrix(E1_ref,-2,3,-2,3,"%6d ","E1_ref")); DEBUG("");

	E2_ref[-2][-2] = 1; E2_ref[-2][-1] = 1; E2_ref[-2][0] = 1; E2_ref[-2][1] = 2; E2_ref[-2][2] = 2; E2_ref[-2][3] = 2;
	E2_ref[-1][-2] = 1; E2_ref[-1][-1] = 1; E2_ref[-1][0] = 1; E2_ref[-1][1] = 2; E2_ref[-1][2] = 2; E2_ref[-1][3] = 2;
	E2_ref[0][-2] = 1; E2_ref[0][-1] = 1; E2_ref[0][0] = 1; E2_ref[0][1] = 2; E2_ref[0][2] = 2; E2_ref[0][3] = 2;
	E2_ref[1][-2] = 3; E2_ref[1][-1] = 3; E2_ref[1][0] = 3; E2_ref[1][1] = 4; E2_ref[1][2] = 4; E2_ref[1][3] = 4;
	E2_ref[2][-2] = 3; E2_ref[2][-1] = 3; E2_ref[2][0] = 3; E2_ref[2][1] = 4; E2_ref[2][2] = 4; E2_ref[2][3] = 4;
	E2_ref[3][-2] = 3; E2_ref[3][-1] = 3; E2_ref[3][0] = 3; E2_ref[3][1] = 4; E2_ref[3][2] = 4; E2_ref[3][3] = 4;
	DEBUG(display_ui8matrix(E2_ref,-2,3,-2,3,"%6d ","E2_ref")); DEBUG("");

	init_bord(E,1,0,1,0,1);
	DEBUG(display_ui8matrix(E,-2,3,-2,3,"%6d ","E")); DEBUG("");

	for(int i=-2;i<=3;i++){
		for(int j=-2;j<=3;j++){
			if(E1_ref[i][j]!=E[i][j]){
				free_ui8matrix(E,-2,3,-2,3);
				free_ui8matrix(E1_ref,-2,3,-2,3);
				free_ui8matrix(E2_ref,-2,3,-2,3);
				return 0;
			}
		}
	}

	init_bord(E,2,0,1,0,1);
	DEBUG(display_ui8matrix(E,-2,3,-2,3,"%6d ","E")); DEBUG("");

	for(int i=-2;i<=3;i++){
		for(int j=-2;j<=3;j++){
			if(E2_ref[i][j]!=E[i][j]){
				free_ui8matrix(E,-2,3,-2,3);
				free_ui8matrix(E1_ref,-2,3,-2,3);
				free_ui8matrix(E2_ref,-2,3,-2,3);
				return 0;
			}
		}
	}


	free_ui8matrix(E,-2,3,-2,3);
	free_ui8matrix(E1_ref,-2,3,-2,3);
	free_ui8matrix(E2_ref,-2,3,-2,3);
	return 1;
}

//	Test unitaire 
//	Entrée: 	E, matrix initialisé en 4x4, alloué en 8x8 pour init_bord
//	Méthode:	erosion
//	Sortie: 	img, matrix 4x4

int Morpho_erosion_tu(){

	uint8 c = 1;
	uint8 **E 		= ui8matrix(-2,5,-2,5);
	uint8 **img 	= ui8matrix(0,3,0,3);
	uint8 **img_ref = ui8matrix(0,3,0,3);

	for(int i=0; i<=3; i++){
		for(int j=0; j<=3; j++){
			E[i][j] = c;
			c++;
		}
	}
	DEBUG(display_ui8matrix(E,-2,5,-2,5,"%6d ","E")); DEBUG("");

	init_bord(E,2,0,3,0,3);
	DEBUG(display_ui8matrix(E,-2,5,-2,5,"%6d ","E")); DEBUG("");

	img_ref[0][0] = 1; img_ref[0][1] = 1; img_ref[0][2] = 2; img_ref[0][3] = 3;
	img_ref[1][0] = 1; img_ref[1][1] = 1; img_ref[1][2] = 2; img_ref[1][3] = 3;
	img_ref[2][0] = 5; img_ref[2][1] = 5; img_ref[2][2] = 6; img_ref[2][3] = 7;
	img_ref[3][0] = 9; img_ref[3][1] = 9; img_ref[3][2] = 10; img_ref[3][3] = 11;
	DEBUG(display_ui8matrix (E,-2,5,-2,5,"%6d ","E")); DEBUG("");

	erosion(E,img,1,0,3,0,3);
	DEBUG(display_ui8matrix(img,0,3,0,3,"%6d ","img")); DEBUG("");

	for(int i=0; i<=3; i++){
		for(int j=0; j<=3; j++){
			if(img[i][j]!= img_ref[i][j]){
				free_ui8matrix(E,-2,5,-2,5);
				free_ui8matrix(img,0,3,0,3);
				free_ui8matrix(img_ref,0,3,0,3);
				return 0;
			}
		}
	}
	free_ui8matrix(E,-2,5,-2,5);
	free_ui8matrix(img,0,3,0,3);
	free_ui8matrix(img_ref,0,3,0,3);
	return 1;
}

//	Test unitaire 
//	Entrée: 	E, matrix initialisé en 4x4, alloué en 8x8 pour init_bord
//	Méthode:	dilatation
//	Sortie: 	img, matrix 4x4

int Morpho_dilatation_tu(){
	uint8 c = 1;
	uint8 **E 		= ui8matrix(-2,5,-2,5);
	uint8 **img 	= ui8matrix(0,3,0,3);
	uint8 **img_ref = ui8matrix(0,3,0,3);

	for(int i=0; i<=3; i++){
		for(int j=0; j<=3; j++){
			E[i][j] = c;
			c++;
		}
	}
	DEBUG(display_ui8matrix(E,-2,5,-2,5,"%6d ","E")); DEBUG("");

	init_bord(E,2,0,3,0,3);
	DEBUG(display_ui8matrix(E,-2,5,-2,5,"%6d ","E")); DEBUG("");

	img_ref[0][0] = 6; img_ref[0][1] = 7; img_ref[0][2] = 8; img_ref[0][3] = 8;
	img_ref[1][0] = 10; img_ref[1][1] = 11; img_ref[1][2] = 12; img_ref[1][3] = 12;
	img_ref[2][0] = 14; img_ref[2][1] = 15; img_ref[2][2] = 16; img_ref[2][3] = 16;
	img_ref[3][0] = 14; img_ref[3][1] = 15; img_ref[3][2] = 16; img_ref[3][3] = 16;

	DEBUG(display_ui8matrix(img_ref,0,3,0,3,"%6d ","img_ref")); DEBUG("");

	dilatation(E,img,1,0,3,0,3);
	DEBUG(display_ui8matrix(img,0,3,0,3,"%6d ","img")); DEBUG("");

	for(int i=0; i<=3; i++){
		for(int j=0; j<=3; j++){
			if(img[i][j]!= img_ref[i][j]){
				free_ui8matrix(E,-2,5,-2,5);
				free_ui8matrix(img,0,3,0,3);
				free_ui8matrix(img_ref,0,3,0,3);
				return 0;
			}
		}
	}
	free_ui8matrix(E,-2,5,-2,5);
	free_ui8matrix(img,0,3,0,3);
	free_ui8matrix(img_ref,0,3,0,3);
	return 1;
}

//	Test intégré pour l'algorithme Morphologie 
//	Entrée: 	E, matrix 50x50, alloué en 52x52 
//	Méthode:	morpho
//	Sortie: 	res, matrix 50x50

int Morpho_integration_tu(){

	uint8 **E 		= ui8matrix(-2,51,-2,51);
	uint8 **res 	= ui8matrix(0,49,0,49);
	uint8 **res_ref = ui8matrix(0,49,0,49);

	for(int i=0;i<=49;i++){
		for(int j=0;j<=49;j++){
			E[i][j] = 1;
			res_ref[i][j] = 1;
		}
	}
	for(int i=12;i<=30;i++){
		for(int j=12;j<=30;j++){
			E[i][j] = 0;
			res_ref[i][j] = 0;
		}
	}
	// des trous
	E[14][15] = E[15][15] = E[15][14] = 1;
	E[20][25] = E[19][25] = E[21][24] = 1;
	E[28][17] = E[28][16] = E[27][17] = 1;

	morpho(E,res,1,0,49,0,49);

	for(int i=0;i<=49;i++){
		for(int j=0;j<=49;j++){
			if(res_ref[i][j]!=res[i][j]){
				free_ui8matrix(E,-2,51,-2,51);
				free_ui8matrix(res,0,49,0,49);
				free_ui8matrix(res_ref,0,49,0,49);
				return 0;
			}
		}
	}

	free_ui8matrix(E,-2,51,-2,51);
	free_ui8matrix(res,0,49,0,49);
	free_ui8matrix(res_ref,0,49,0,49);			
	return 1;
}

//******* Validation d'optimisation    *******//
//******* SSE2  1:mouvement  2:morpho  *******//
//******* AVX2  3:mouvement  4:morpho  *******//


int check_results(int i) {

	long i0 = 0, i1 = 240-1;
	long j0 = 0, j1 = 320-1;

	int k, ndigit = 0;
	int c;
	char *path_ref;
	char *path;
	char *filename = "car_";
	char *extension = "pgm";
	char  complete_filename[50];

	int max=0;
	uint8 **img_ref, **img;
	img_ref = ui8matrix(i0,i1,j0,j1);
	img 	= ui8matrix(i0,i1,j0,j1);

	if(i == 1){ 
		path_ref = "/home/huiling/HPC/Projet-HPC/sdout/";
		path = "/home/huiling/HPC/Projet-HPC/sdout_SSE2/";
	}
	else if(i == 2){
		path_ref = "/home/huiling/HPC/Projet-HPC/morphoout/";
		path = "/home/huiling/HPC/Projet-HPC/morphoout_SSE2/";
	}
	else if(i == 3){ 
		path_ref = "/home/huiling/HPC/Projet-HPC/sdout/";
		path = "/home/huiling/HPC/Projet-HPC/sdout_AVX2/";
	}
	else if(i == 4){
		path_ref = "/home/huiling/HPC/Projet-HPC/morphoout/";
		path = "/home/huiling/HPC/Projet-HPC/morphoout_AVX2/";
	}

  	for(int k=3001; k<=3199; k++){
		generate_path_filename_k_ndigit_extension(path_ref, filename, k, ndigit, extension, complete_filename);
		MLoadPGM_ui8matrix(complete_filename, i0, i1, j0, j1, img_ref);
		generate_path_filename_k_ndigit_extension(path, filename, k, ndigit, extension, complete_filename);
		MLoadPGM_ui8matrix(complete_filename, i0, i1, j0, j1, img);
		c = 0;
		for(int i=0; i<240; i++){
			for(int j=0; j<320; j++){
				if(img[i][j] != img_ref[i][j]) {
					c++;
					if(c>=1152){  //1.5%

						free_ui8matrix(img_ref,i0,i1,j0,j1);
						free_ui8matrix(img,i0,i1,j0,j1);
						return 0;
					}

				}
			}
		}
	}
	free_ui8matrix(img_ref,i0,i1,j0,j1);
	free_ui8matrix(img,i0,i1,j0,j1);
  return 1;
}
