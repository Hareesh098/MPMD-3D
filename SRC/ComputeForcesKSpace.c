// COMPUTES THE FOURIER SPACE PART OF POTENTIAL ENERGY AND FORCES
// Salin & Calilol, J. Chem. Phys. (113), 23, 2000

#include<stdio.h>
#include<math.h>
#include"complex.h"
#include"yukawa.h"
#include"global.h"

// KX(kx) GIVES X COMPONENT OF SOME K VECTOR (kx^2 + ky^2 + kz^2 <= ksqmax)
// KY(ky) GIVES Y COMPONENT OF SOME K VECTOR (kx^2 + ky^2 + kz^2 <= ksqmax)
// KZ(kz) GIVES Z COMPONENT OF SOME K VECTOR (kx^2 + ky^2 + kz^2 <= ksqmax)
#define	KX(kx)		((kx))
#define	KY(ky)		((ky)+(kmax))
#define	KZ(kz)		((kz)+(kmax))
void ComputeForcesKSpace (){
  double twopiByL = 2*M_PI/region[1]; 
  int kx, ky, kz;
  // CALCULATE kx, ky, kz = 0, -1 AND 1 EXPLICITLY
  int n;
  for (n = 1; n <= nAtom; n++){
    eikx[n][KX (0)] = Complex (1.0, 0.0);
    eiky[n][KY (0)] = Complex (1.0, 0.0);
    eikz[n][KZ (0)] = Complex (1.0, 0.0);
    
    eikx[n][KX (1)] = Complex (cos (twopiByL * r[1][n]), sin (twopiByL * r[1][n]));
    eiky[n][KY (1)] = Complex (cos (twopiByL * r[2][n]), sin (twopiByL * r[2][n]));
    eikz[n][KZ (1)] = Complex (cos (twopiByL * r[3][n]), sin (twopiByL * r[3][n]));

    eiky[n][KY (-1)] = Conjg (eiky[n][KY (1)]);
    eikz[n][KZ (-1)] = Conjg (eikz[n][KZ (1)]);      
  }
  // CALCULATE REMAINING kx, ky, kz BY RECURRENCE
  for (kx = 2; kx <= kmax; kx++){
    for (n = 1; n <= nAtom; n++)
      eikx[n][KX (kx)] = Cmul (eikx[n][KX (kx - 1)], eikx[n][KX (1)]);
  }
  for (ky = 2; ky <= kmax; ky++){
    for (n = 1; n <= nAtom; n++){
      eiky[n][KY (ky)] = Cmul (eiky[n][KY (ky - 1)], eiky[n][KY (1)]);
      eiky[n][KY (-ky)] = Conjg (eiky[n][KY (ky)]);
    }
  }

  for (kz = 2; kz <= kmax; kz++){
    for (n = 1; n <= nAtom; n++){
      eikz[n][KZ (kz)] = Cmul (eikz[n][KZ (kz - 1)], eikz[n][KZ (1)]);
      eikz[n][KZ (-kz)] = Conjg (eikz[n][KZ (kz)]);
    }
  }

  // SUM OVER ALL K - VECTORS
  double Vk = 0.;
  int totk = 0, ksq;
  double factor;
  for (kx = 0; kx <= kmax; kx++){
    if (kx == 0)
      factor = 1.;
    else
      factor = 2.;
    for (ky = -kmax; ky <= kmax; ky++){
      for (kz = -kmax; kz <= kmax; kz++){
	ksq = Sqr (kx) + Sqr (ky) + Sqr (kz);
	if (ksq <= ksqmax && ksq != 0){
	  totk++;
	  dcomplex sum = Complex (0., 0.);
	  for (n = 1; n <= nAtom; n++){
	    eikr[n] = Cmul3 (eikx[n][KX (kx)], eiky[n][KY (ky)], eikz[n][KZ (kz)]);
	    sum = Cadd (sum, eikr[n]);
	  }
	  Vk += factor * kvec[totk] * CSqr(sum);
	  // CALCULATE FORCE ON EACH PARTICLE
	  for (n = 1; n <= nAtom; n++){
	    double KForce = -2. * factor * kvec[totk] * Cmul(sum, Conjg(eikr[n])).i;
	    a[1][n] += twopiByL * kx * KForce;
	    a[2][n] += twopiByL * ky * KForce;
	    a[3][n] += twopiByL * kz * KForce;					
	  }
	}
      }
    }
  }

  // CONSTRUCT THE TOTAL POTENTIAL ENERGY 
  // AND SUBTRACT SELF ENERGY
  uSum = uSum + Vk - SelfEnergy;
}
