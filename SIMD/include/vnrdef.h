/* -------------- */
/* --- vdef.h --- */
/* -------------- */

/*
 * Copyright (c) 2004, Lionel Lacassagne IEF-UPSUD
 * Creation: 15/11/2004
 */

#ifndef __VDEF_H__
#define __VDEF_H__

#ifdef __cplusplus
#pragma message ("C++")
extern "C" {
#endif
    
#ifdef __APPLE__
#define SWAR(altivecCode, intelCode) altivecCode
#define ALTIVEC(x) x
#define SSE2(x)
#else
#define SWAR(altivecCode, intelCode) altivecCode
#define ALTIVEC(x)
#define SSE2(x) x
#endif
    
    
#ifdef __MMX__
#include <mmintrin.h>
#endif
    
#ifdef __SSE__
#include <xmmintrin.h>
#endif
    
#ifdef __SSE2__
#include <emmintrin.h>
#endif
    
#ifdef __SSE3__
#include <pmmintrin.h>
#endif
    
#ifdef __SSSE3__
#include <tmmintrin.h>
#endif
    
#ifdef __SSE4a__
#include <ammintrin.h>
#endif
    
#if defined (__SSE4_2__) || defined (__SSE4_1__)
#include <smmintrin.h>
#endif
    
    typedef __m128i vuint8;
    typedef __m128i vsint8;
    
    typedef __m128i vuint16;
    typedef __m128i vsint16;
    
    typedef __m128i vuint32;
    typedef __m128i vsint32;
    
    typedef __m128 vfloat32;
    
    typedef __m128i vbool;    
    
    typedef __m128i  vchar;
    typedef __m128i vschar;
    typedef __m128i vuchar;
    
    typedef __m128i  vshort;
    typedef __m128i vsshort;
    typedef __m128i vushort;
    
    typedef __m128i  vint;
    typedef __m128i vsint;
    typedef __m128i vuint;
    
    typedef __m128 vfloat;
    
    
#ifdef __cplusplus
}
#endif

#endif // __VDEF_H__
