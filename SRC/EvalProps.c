#include<stdio.h>
#include<math.h>
#include"global.h"
void EvalProps (){
  double V;
  int n, k;
  double vvSum = 0.0;
  double halfdt = 0.5*deltaT;
  for(k = 1 ; k <= NDIM ; k ++)
    vSum[k] = 0.;
  for (n = 1; n <= nAtom; n++){
    for(k = 1 ; k <= NDIM ; k ++){
      V = v[k][n] - halfdt * a[k][n];
      vSum[k] += V;
      vvSum += Sqr(V);
    }
  }
  for(k = 1 ; k <= NDIM ; k ++)
    vSum[k] /= nAtom;
  kinEnergy = 0.5 * vvSum / nAtom;
  potEnergy = uSum / nAtom;
  totEnergy = kinEnergy + potEnergy;
}
