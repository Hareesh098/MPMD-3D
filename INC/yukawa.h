/*------------------------------------*/
/*-- yukawa.h (Uses Ewald summation)--*/
/*------------------------------------*/
#ifndef	_YUKAWA_H
#define	_YUKAWA_H_

double	kappa;                 // SCREENING PARAMETER a/lambdaD
double  beta;                  // GAUSSIAN WIDTH OF CANCELLING DISTRIBUTION
double	SelfEnergy;	       // SELF ENERGY
#define	maxk 	700	       // MAXIMUM POSSIBLE NUMBER OF K-VECTORS
#define	kmax	5	       // MAXIMUM INTEGER COMPONENT OF THE K-VECTOR 	
#define	ksqmax	25	       // MAXIMUM SQUARE MOD OF THE K-VECTOR REQUIRED

double	*kvec;		       // ARRAY USED TO STORE K-VECTORS

#ifndef _DCOMPLEX_DECLARE_T_
typedef struct DCOMPLEX {double r,i;} dcomplex;
#define _DCOMPLEX_DECLARE_T_
#endif

dcomplex **eikx;		// COMPLEX EXPONENTS OF SIZE(N, kmax)
dcomplex **eiky;		// COMPLEX EXPONENTS OF SIZE (N, 2*kmax)
dcomplex **eikz; 		// COMPLEX EXPONENTS OF SIZE (N, 2*kmax)
dcomplex *eikr;			// COMPLEX EXPONENTS OF SIZE (N)
#endif

