#include<stdio.h>
#include<math.h>
#include"global.h"
#include"functions.h"
void EvalSpacetimeCorr (){
  // EVALUATE SPACETIME CORRELATIONS
  double cosV=0., cosV0=0., cosV1=0., cosV2=0., sinV=0., sinV1=0., sinV2=0.;
  double rw, vw, kw;
  double COSA, SINA, COSV, SINV;
  int j, k, m, n, nb, nc, ni, nv;
  double kMin = 2. * M_PI / region[1];
  double kMax = M_PI;
  double deltaK = (kMax - kMin) / nFunCorr;
  for (j = 1; j <= 24 * nFunCorr; j++)
    cfVal[j] = 0.;
  for (n = 1; n <= nAtom; n++){
    j = 1;
    for(k = 1 ; k <= NDIM ; k ++){
      rw = r[k][n] - 0.5*deltaT*v[k][n];
      COSA = cos(kMin*rw);
      SINA = sin(kMin*rw);
      for (m = 1; m <= nFunCorr; m++){
	if(m == 1){
	  cosV = cos(deltaK*rw);
	  sinV = sin(deltaK*rw);
	  cosV0 = cosV;
	}else if(m == 2){
	  cosV1 = cosV;
	  sinV1 = sinV;
	  cosV = 2.*cosV0*cosV1-1;
	  sinV = 2.*cosV0*sinV1;
	}else{
	  cosV2 = cosV1;
	  sinV2 = sinV1;
	  cosV1 = cosV;
	  sinV1 = sinV;
	  cosV = 2.*cosV0*cosV1-cosV2;
	  sinV = 2.*cosV0*sinV1-sinV2;
	}
	COSV = COSA*cosV - SINA*sinV;
	SINV = SINA*cosV + COSA*sinV;
	for(nc = 1 ; nc <= 4 ; nc ++){
	  if(nc <= 3)	
	    vw = v[nc][n];
	  else 
	    vw = 1.;
	  cfVal[j] += vw*COSV;
	  cfVal[j+1] += vw*SINV;
	  j += 2;
	}
      }
    }
  }
  for (nb = 1; nb <= nBuffCorr; nb++){
    indexCorr[nb] += 1;
    if (indexCorr[nb] <= 0) continue;
    ni = 3 * nFunCorr * (indexCorr[nb] - 1);
    if (indexCorr[nb] == 1){
      for (j = 1; j <= 24 * nFunCorr; j++)
	cfOrg[nb][j] = cfVal[j];
    }
    for (j = 1; j <= 3 * nFunCorr; j++)
      spacetimeCorr[nb][ni + j] = 0.;
    j = 1;
    for(k = 1 ; k <= NDIM ; k ++){
      for (m = 1; m <= nFunCorr; m++){
	for (nc = 1; nc <= 4; nc++){
	  nv = 3 * m + ni;
	  if (nc <= 3){
	    kw = Sqr (kMin + m*deltaK);
	    if (nc == k)
	      nv -= 2;
	    else{
	      nv -= 1;
	      kw *= 0.5;
	    }
	  }else
	    kw = 1;
	  spacetimeCorr[nb][nv] += kw * (cfVal[j] * cfOrg[nb][j] + cfVal[j + 1] * cfOrg[nb][j + 1]);
	  j += 2;
	}
      }
    }
  }
  // ACCUMULATE SPACETIME CORRELATIONS
  for (nb = 1; nb <= nBuffCorr; nb++){
   if (indexCorr[nb] == nValCorr){
     for (j = 1; j <= 3*nFunCorr*nValCorr; j++)
       spacetimeCorrAv[j] += spacetimeCorr[nb][j];
     indexCorr[nb] = 0.;
     countCorrAv ++;
     if (countCorrAv == limitCorrAv){
       for (j = 1; j <= 3*nFunCorr*nValCorr; j++)
	 spacetimeCorrAv[j] /= (3.*nAtom*limitCorrAv);
       PrintSpacetimeCorr ();
       countCorrAv = 0.;
       for (j = 1; j <= 3 * nFunCorr * nValCorr; j++)
	 spacetimeCorrAv[j] = 0.;
     }
   }
  }
}
