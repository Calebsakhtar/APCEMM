/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/*                                                                  */
/*     Aircraft Plume Chemistry, Emission and Microphysics Model    */
/*                             (APCEMM)                             */
/*                                                                  */
/* Interface Header File                                            */
/*                                                                  */
/* Author               : Thibaud M. Fritz                          */
/* Time                 : 8/12/2018                                 */
/* File                 : Interface.hpp                             */
/* Working directory    : /home/fritzt/APCEMM-SourceCode            */
/*                                                                  */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

#ifndef INTERFACE_H_INCLUDED
#define INTERFACE_H_INCLUDED

/* TRANSPORT */
#define DIFFUSION               1    /* Is diffusion turned on? */
#define ADVECTION               1    /* Is advection turned on? */

/* FFTW */
#define FFTW_WISDOM             0    /* Find most efficient algorithm through FFTW_wisdom. Takes ~ 10s */
const char* const WISDOMFILE = "../SANDS/data/FFTW_Wisdom.out"; 

/* OUTPUT */
#define DOSAVEPL                1    /* Save chemical rates */

/* DEBUG */
#define DEBUG_AC_INPUT          0    /* Debug AC Input? */
#define DEBUG_BG_INPUT          0    /* Debug Background Input? */
#define DEBUG_EI_INPUT          0    /* Debug Emission Input? */
#define DEBUG_RINGS             0    /* Debug Rings? */

#endif /* INTERFACE_H_INCLUDED */