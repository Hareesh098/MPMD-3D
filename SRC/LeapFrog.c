#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include"global.h"
void LeapFrog (gsl_rng * rnd){
  double nu = 0.0389;
  double var = sqrt(2*nu/(Gamma*deltaT));
  double scale = 1. + nu*deltaT/2.;
  double scale_v = 2./scale - 1.;
  double scale_f = deltaT/scale;
  int n, k;
  for (n = 1; n <= nAtom; n++){
    for(k = 1 ; k <= NDIM ; k ++){
      v[k][n] = scale_v*v[k][n] + scale_f*(a[k][n] + var*gsl_ran_gaussian(rnd,1));
      r[k][n] += v[k][n]*deltaT;
    }
  }
}
