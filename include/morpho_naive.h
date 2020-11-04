/* --------------------- */
/* --- morpho_naive.h --- */
/* --------------------- */

#ifndef __MORPHO_NAIVE__
#define __MORPHO_NAIVE__


#define MAX3(a,b,c) ((((a) > (b)) ? (a) : (b)) > (c) ? (((a) > (b)) ? (a) : (b)) : c)
#define MIN3(a,b,c) ((((a) < (b)) ? (a) : (b)) < (c) ? (((a) > (b)) ? (a) : (b)) : c)

#define MAX5(a,b,c,d,e) MAX3(MAX3(a,b,c),d,e)
#define MIN5(a,b,c,d,e) MIN3(MIN3(a,b,c),d,e) 

#endif
