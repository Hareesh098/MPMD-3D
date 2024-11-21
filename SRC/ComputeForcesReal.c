/* 
 * COMPUTES R-SPACE PART OF POTENTIAL ENERGY BY EWALD SUMS 
 */
#include<stdio.h>
#include<math.h>
#include"global.h"
#include"yukawa.h"
#define	SqrtOf3 1.732050
void ComputeForcesReal (){
  double dr[NDIM+1];
  uSum = 0.;
  double fcVal;
  double R, RR;
  int i, j;
  double KbyB = kappa / (2. * beta);
  double Ao, Bo, Co, Do = 2 * beta /sqrt(M_PI);
  double A1, B1, C1;
  EinsteinFreq = 0.;

  // INITIALISE ACCELERATIONS
  int n, k;
  for (n = 1; n <= nAtom; n++){
    for(k = 1 ; k <= NDIM ; k ++)
      a[k][n] = 0.0;
  }
  
  // LOOP OVER ATOM PAIRS
  for (i = 1; i < nAtom; i++){
    for (j = i + 1; j <= nAtom; j++){
      RR = 0.;

      dr[1] = r[1][i] - r[1][j];
      if ((periodicx) && (fabs (dr[1]) > regionH[1]))
	dr[1] -= SignR (region[1], dr[1]);

      dr[2] = r[2][i] - r[2][j];
      if ((periodicy) && (fabs (dr[2]) > regionH[2]))
	dr[2] -= SignR (region[2], dr[2]);

      dr[3] = r[3][i] - r[3][j];
      if ((periodicz) && (fabs (dr[3]) > regionH[3]))
	dr[3] -= SignR (region[3], dr[3]);

      RR = Sqr (dr[1]) + Sqr(dr[2]) + Sqr(dr[3]);

      R = sqrt (RR);
      Ao = beta*R + KbyB;
      Bo = beta*R - KbyB;
      Co = exp (kappa*R);
      uSum += (1/(2.*R)) * (erfc (Ao) * Co + erfc (Bo) / Co);
      EinsteinFreq += exp(-kappa*R)/R;
      A1 = (1/R - kappa) * erfc (Ao) * Co;
      B1 = (1/R + kappa) * erfc (Bo) / Co;
      C1 = Do * (exp (-Sqr (Ao)) * Co + exp (-Sqr (Bo)) / Co);
      fcVal = (1./(2.*R)) * (A1+B1+C1);
      // ACCUMULATE R - SPACE COMPONENT OF FORCES
      for(k = 1 ; k <= NDIM ; k ++){
	a[k][i] += fcVal * dr[k] / R;
	a[k][j] -= fcVal * dr[k] / R;
      }
    }
  }
  EinsteinFreq = (kappa/SqrtOf3)*sqrt(2.*EinsteinFreq);
}
