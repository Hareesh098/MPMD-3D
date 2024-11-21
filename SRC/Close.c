#include<stdio.h>
#include<stdlib.h>
#include"global.h"
#include"yukawa.h"
void Close (){
  int i;
  // COORDINATES
  for(i = 0 ; i <= NDIM ; i ++){
    free (r[i]);
    free (v[i]);
    free (a[i]);
  }
  free(r);
  free(v);
  free(a);
  
  // SPACETIME CORRELATIONS
  for (i = 0; i < nBuffCorr; i++)
    free (cfOrg[i]);
  free (cfOrg);
  free (cfVal);
  free (indexCorr);
  for (i = 0; i < nBuffCorr; i++)
    free (spacetimeCorr[i]);
  free (spacetimeCorr);
  free (spacetimeCorrAv);

  // COMPLEX EXPONENTIALS IN EWALD SUMS
  free (kvec);
  for (i = 0; i <= nAtom; i++){
    free (eikx[i]);
    free (eiky[i]);
    free (eikz[i]);
  }
  free (eikx);
  free (eiky);
  free (eikz);
  free (eikr);
    
  // VELOCITY AUTOCORRELATION
  for(i = 0 ; i <= nBuffAcf ; i ++){
    free(rvAcf[i]);
    free(rvAcfOrg[i]);
  }
  free(rvAcf);
  free(rvAcfOrg);
  free(indexAcf);
  free(rvAcfAv);

  // FOR DIFFUSION
  for(i = 0 ; i <= nBuffDiffuse ; i ++){
    free(rDiffuse[i]);
    free(xyDiffuse[i]);
    free(zDiffuse[i]);
    free(rDiffuseOrg[i]);
    free(rDiffuseTrue[i]);
  }
  free(rDiffuse);
  free(xyDiffuse);
  free(zDiffuse);
  free(rDiffuseOrg);
  free(rDiffuseTrue);

  free(rDiffuseAv);
  free(xyDiffuseAv);
  free(zDiffuseAv);

  free(indexDiffuse);

  // RADIAL DISTRIBUTION FUNCTION
  free(histRdf);

  // GRID PROFILE
  for(i = 0 ; i <= NHIST ; i ++)
    free(Grid[i]);
  free(Grid);
  free(GridTemp);
  free(GridPop);
}
