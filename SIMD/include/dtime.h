/*****************************************************/
/* Various timer routines.                           */
/* Al Aburto, aburto@nosc.mil, 18 Feb 1997           */
/*                                                   */
/* t = dtime() outputs the current time in seconds.  */
/* Use CAUTION as some of these routines will mess   */
/* up when timing across the hour mark!!!            */
/*                                                   */
/* For timing I use the 'user' time whenever         */
/* possible. Using 'user+sys' time is a separate     */
/* issue.                                            */
/*                                                   */
/* Example Usage:                                    */
/* [timer options added here]                        */
/* main()                                            */
/* {                                                 */
/* double starttime,benchtime,dtime();               */
/*                                                   */
/* starttime = dtime();                              */
/* [routine to time]                                 */
/* benchtime = dtime() - starttime;                  */
/* }                                                 */
/*                                                   */
/* [timer code below added here]                     */
/*****************************************************/

#ifndef __TIMERS_B_H__
#define __TIMERS_B_H__
/***************************************************************/
/* Timer options. You MUST uncomment one of the options below  */
/* or compile, for example, with the '-DUNIX' option.          */
/***************************************************************/
/* #define TIMER_Amiga       */
/* #define TIMER_UNIX        */
/* #define TIMER_DEC_ALPHA   */
/* #define TIMER_UNIX_Old    */
/* #define TIMER_VMS         */
/* #define TIMER_BORLAND_C   */
/* #define TIMER_MSC         */
/* #define TIMER_MAC         */
/* #define TIMER_IPSC        */
/* #define TIMER_FORTRAN_SEC */
/* #define TIMER_GTODay      */
/* #define TIMER_CTimer      */
/* #define TIMER_UXPM        */
/* #define TIMER_MAC_TMgr    */
/* #define TIMER_MAC_OSX     */
/* #define TIMER_MACH_OSX    */
/* #define TIMER_PARIX       */
/* #define TIMER_POSIX9      */
/* #define TIMER_POSIX       */
/* #define TIMER_WIN32_Old   */
/* #define TIMER_WIN32       */
/* #define TIMER_POSIX6      */
/* #define TIMER_RISCOS      */
/* #define TIMER_LINUX       */
/*****************************/

#ifdef __cplusplus
#ifdef PRAGMA_VERBOSE
#pragma message ("C++")
#endif
extern "C" {
#endif

double dtime(void);
// dtime is always defined
// dcycle can be defined for only few arch: Power(PC) and Intel/AMD

#ifdef LINUX
double dcycle(void);
#endif // LINUX

#ifdef WIN32
double dcycle(void);
#endif

#if defined(_i386_) || defined(__x86_64__)
double dcycle(void);
#endif
    
#if defined(_ARCH_PPC)
double dcycle(void);
#endif    

#ifdef __cplusplus
}
#endif


#endif /*__TIMERS_B_H__*/
