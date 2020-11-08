/* Algorithme Morphologie version SIMD */

#include <stdio.h>
#include <stdlib.h>

#include "nrdef.h"
#include "nrutil.h"

#include "vnrdef.h"
#include "vnrutil.h"

#include "mutil.h"

#include "morpho_SIMD.h"

/* --------------------- */
/* E: Image d'entree     */
/* I: Image avec bord    */
/* img: Image de sortie  */
/* --------------------- */

/* Idées :
 - Faire des threads pour paralléliser le traitement des images.
 - Utiliser SIMD2D pour écrire morpho_SIMD
 - 1 tableau qui contient l'adresse des lignes du tableau
 - Plusieurs tableaux qui contient les valeurs d'une ligne du tableau

Fonctions à utiliser :
- vuint8   **vui8matrix_map (int nrl, int nrh, int ncl, int nch);
- void free_vui8matrix_map (vuint8   **m, int nrl, int nrh, int ncl, int nch);
- vuint8**    vui8matrix_map_1D_pitch(vuint8   **m, int nrl, int nrh, int ncl, int nch, void *data_1D, int pitch);
- void zero_vui8vector(vuint8 *m, int j0, int j1); (après c'est en 1D)
- void init_vui8matrix_param (vuint8   **m, int i0, int i1, int j0, int j1, uint8   x0, uint8   xstep, uint8   ystep);
- void zero_vui8matrix (vuint8   **m, int i0, int i1, int j0, int j1);

*/



/*Fonctions à écrire
void copy_duplication(uint8 **E, uint8 **I, int b, long nrl, long nrh, long ncl, long nch);
void erosion_r1(uint8 **E, uint8 **img, int b, long nrl, long nrh, long ncl, long nch);
void erosion_r2(uint8 **E, uint8 **img, int b, long nrl, long nrh, long ncl, long nch);
void dilatation_r1(uint8 **E, uint8 **img, int b, long nrl, long nrh, long ncl, long nch);
void dilatation_r2(uint8 **E, uint8 **img, int b, long nrl, long nrh, long ncl, long nch);
void ouverture_r1(uint8 **E, uint8 **img, int b, long nrl, long nrh, long ncl, long nch);
void ouverture_r2(uint8 **E, uint8 **img, int b, long nrl, long nrh, long ncl, long nch);
void fermeture_r1(uint8 **E, uint8 **img, int b, long nrl, long nrh, long ncl, long nch);
void fermeture_r2(uint8 **E, uint8 **img, int b, long nrl, long nrh, long ncl, long nch);
void morpho(uint8 **E, uint8 **img, int b, long nrl, long nrh, long ncl, long nch);
*/
