/* ---------------- */
/* --- nrutil.h --- */
/* ---------------- */

/*
 *Copyright(c) 2007 Lionel Lacassagne, all rights reserved
 */

#ifndef __NRUTIL_H__
#define __NRUTIL_H__

//#pragma message("  include  nrutil.h")

#ifdef __cplusplus
#pragma message ("C++")
extern "C" {
#endif

#include <stdint.h>
#include <sys/time.h>
#include <inttypes.h>

#define NR_END 0
#define FREE_ARG char*
#define H 240
#define W 320
#define N 2		// partie SD a verifier: 2/3/4
#define VMIN 1
#define VMAX 254


extern long nr_end;

/* timer: vient du tp histo*/
int64_t clocktime();
/* conversion image code en [0,1] vers [0.255]*/
void convertb2i();
void converti2b();

void generate_filename_k_ndigit                 (            char *filename, int k, int ndigit,                         char *complete_filename);
void generate_filename_k_ndigit_extension       (            char *filename, int k, int ndigit,        char *extension, char *complete_filename);
void generate_path_filename                     (char *path, char *filename,                                            char *complete_filename);
void generate_path_filename_extension           (char *path, char *filename,                           char *extension, char *complete_filename);
void generate_path_filename_k_ndigit_extension  (char *path, char *filename, int k, int ndigit,        char *extension, char *complete_filename);
void generate_path_filename_k_ndigit_l_extension(char *path, char *filename, int k, int ndigit, int l, char *extension, char *complete_filename);
/* ------------------------------- */
/* -- vector & matrix allocator -- */
/* ------------------------------- */
float32* f32vector(long nl, long nh);
float64* f64vector(long nl, long nh);

void free_f32vector(float32 *v, long nl, long nh);
void free_f64vector(float64 *v, long nl, long nh);

uint8**   ui8matrix(long nrl, long nrh, long ncl, long nch);
sint8**   si8matrix(long nrl, long nrh, long ncl, long nch);
uint16** ui16matrix(long nrl, long nrh, long ncl, long nch);
sint16** si16matrix(long nrl, long nrh, long ncl, long nch);
uint32** ui32matrix(long nrl, long nrh, long ncl, long nch);
sint32** qi32matrix(long nrl, long nrh, long ncl, long nch);
float32** f32matrix(long nrl, long nrh, long ncl, long nch);

void free_ui8matrix(uint8   **m, long nrl, long nrh, long ncl, long nch);
void free_si8matrix(sint8   **m, long nrl, long nrh, long ncl, long nch);
void free_ui16matrix(uint16 **m, long nrl, long nrh, long ncl, long nch);
void free_si16matrix(sint16 **m, long nrl, long nrh, long ncl, long nch);
void free_ui32matrix(uint32 **m, long nrl, long nrh, long ncl, long nch);
void free_si32matrix(sint32 **m, long nrl, long nrh, long ncl, long nch);
void free_f32matrix(float32 **m, long nrl, long nrh, long ncl, long nch);

/* ------------ */
/* --- copy --- */
/* ------------ */
void copy_ui8matrix_ui8matrix (uint8   **X, int i0, int i1, int j0, int j1, uint8   **Y);
void copy_ui8matrix_ui16matrix(uint8   **X, int i0, int i1, int j0, int j1, uint16  **Y);
void copy_ui16matrix_ui8matrix(uint16  **X, int i0, int i1, int j0, int j1, uint8   **Y);
void copy_ui8matrix_f32matrix (uint8   **X, int i0, int i1, int j0, int j1, float32 **Y);
void copy_f32matrix_ui8matrix (float32 **X, int i0, int i1, int j0, int j1, uint8   **Y);


/* ----------------------------- */
/* -- display vector & matrix -- */
/* ----------------------------- */

void display_si8vector (sint8  *v,long nl,long nh, char *format, char *name);
void display_ui8vector (uint8  *v,long nl,long nh, char *format, char *name);
void display_si16vector(sint16 *v,long nl,long nh, char *format, char *name);
void display_ui16vector(uint16 *v,long nl,long nh, char *format, char *name);
void display_si32vector(sint32 *v,long nl,long nh, char *format, char *name);
void display_ui32vector(uint32 *v,long nl,long nh, char *format, char *name);
void display_f32vector(float32 *v,long nl,long nh, char *format, char *name);

void display_si8matrix (sint8  **m,long nrl,long nrh,long ncl, long nch, char *format, char *name);
void display_ui8matrix (uint8  **m,long nrl,long nrh,long ncl, long nch, char *format, char *name);
void display_si16matrix(sint16 **m,long nrl,long nrh,long ncl, long nch, char *format, char *name);
void display_ui16matrix(uint16 **m,long nrl,long nrh,long ncl, long nch, char *format, char *name);
void display_si32matrix(sint32 **m,long nrl,long nrh,long ncl, long nch, char *format, char *name);
void display_ui32matrix(uint32 **m,long nrl,long nrh,long ncl, long nch, char *format, char *name);
void display_f32matrix(float32 **m,long nrl,long nrh,long ncl, long nch, char *format, char *name);

/* ------------- */
/* -- wrapper -- */
/* ------------- */

/* ------------------------------- */
/* -- PGM and PNM binary format -- */
/* ------------------------------- */

uint8** LoadPGM_ui8matrix(char *filename, int *nrl, int *nrh, int *ncl, int *nch);
void   MLoadPGM_ui8matrix(char *filename, int  nrl, int  nrh, int  ncl, int nch, uint8 **m);
void    SavePGM_ui8matrix(uint8 **m,      int  nrl, int  nrh, int  ncl, int nch, char *filename);

rgb8 ** LoadPPM_rgb8matrix(char *filename, int *nrl, int *nrh, int *ncl, int *nch);
void    SavePPM_rgb8matrix(rgb8 **m,       int  nrl, int  nrh, int  ncl, int  nch, char *filename);



#ifdef __cplusplus
}
#endif

#endif // __NRUTL_H__
