#include<stdio.h>
#include"global.h"
#include"functions.h"
void EvalVelCorr(){
  // EVALUATE SPACETIME CORRELATIONS
  int n, k, nb, ni;
  for(nb = 1 ; nb <= nBuffAcf ; nb ++){
    indexAcf[nb] ++;
    if(indexAcf[nb] <= 0) continue;
    if(indexAcf[nb] == 1){
      for(n = 1 ; n <= nAtom ; n ++){
	for(k = 1 ; k <= NDIM ; k ++)
	  rvAcfOrg[nb][NDIM*(n-1)+k] = v[k][n] - 0.5*a[k][n]*deltaT;
      }
    }
    ni = indexAcf[nb]; rvAcf[nb][ni] = 0.;
    for(n = 1 ; n <= nAtom ; n++){
      for(k = 1 ; k <= NDIM ; k ++)
	rvAcf[nb][ni] += rvAcfOrg[nb][NDIM*(n-1)+k] * (v[k][n]-0.5*a[k][n]*deltaT);
    }
  }

  // ACCUMULATE SPACETIME CORRELATIONS
  for(nb = 1 ; nb <= nBuffAcf ; nb ++){
    if(indexAcf[nb] == nValAcf){
      int j;
      for(j = 1 ; j <= nValAcf ; j++)
	rvAcfAv[j] += rvAcf[nb][j];
      indexAcf[nb] = 0;
      countAcfAv ++;
      if(countAcfAv == limitAcfAv){
	PrintVelCorr();
	countAcfAv = 0;
	for(n = 1 ; n <= nValAcf ; n++)
	  rvAcfAv[n] = 0.;
      }
    }
  }
}
