/* --------------- */
/* --- mutil.h --- */
/* --------------- */

/*
 * Misc util
 */


#ifndef __MUTIL_H__
#define __MUTIL_H__

#ifdef __cplusplus
#pragma message ("C++")
extern "C" {
#endif  

   
//#define CHRONO(X,t) tmin = 1e10; for(r=0; r<run; r++) { t0 = chrono(); for(i=0;i<iter;i++) X;  t1 = chrono(); dt = t1-t0; if(dt<tmin) tmin = dt; } t=tmin/iter

double chrono(void);
    
uint8 ui8rand(void);
uint32 ui32rand(void);
uint32 f32rand(void);

void rand_ui8vector(uint8 *X, int i0, int i1);
void rand_ui32vector(uint32 *X, int i0, int i1);
void rand_f32vector(float32 *X, int i0, int i1);

int getIter(int size);
int getIterAV(int size);

float32 gauss(float32 sigma, float32 x);


#ifdef __cplusplus
}
#endif

#endif /* __MUTIL_H__ */
