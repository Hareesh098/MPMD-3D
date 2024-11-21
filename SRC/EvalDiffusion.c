#include<stdio.h>
#include<math.h>
#include<errno.h>
#include"global.h"

void EvalDiffusion(){
  int k, n, nb, ni, nk;
  for(nb = 1 ; nb <= nBuffDiffuse ; nb ++){
    indexDiffuse[nb] ++;
    if(indexDiffuse[nb] <= 0)
      continue;
    if(indexDiffuse[nb] == 1){
      for(n = 1 ; n <= nAtom ; n ++){
	for(k = 1 ; k <= NDIM ; k ++){
	  nk = NDIM * (n-1) + k;
	  rDiffuseTrue[nb][nk] = r[k][n];
	  rDiffuseOrg[nb][nk] = r[k][n];
	}
      }
    }
    ni = indexDiffuse[nb];
    rDiffuse[nb][ni] = 0;
    xyDiffuse[nb][ni] = 0;
    zDiffuse[nb][ni] = 0;
    double rrdx, rrdy, rrdz;
    for(n = 1 ; n <= nAtom ; n ++){

      // ACCUMULATE X COMPONENT OF DIFFUSION
      nk = NDIM * (n-1) + 1;
      rDiffuseTrue[nb][nk] = r[1][n] + rint((rDiffuseTrue[nb][nk] - r[1][n])/region[1])*region[1];
      rrdx = Sqr(rDiffuseTrue[nb][nk] - rDiffuseOrg[nb][nk]);
      xyDiffuse[nb][ni] += rrdx;
      rDiffuse[nb][ni] += rrdx;

      // ACCUMULATE Y COMPONENT OF DIFFUSION
      nk = NDIM * (n-1) + 2;
      rDiffuseTrue[nb][nk] = r[2][n] + rint((rDiffuseTrue[nb][nk] - r[2][n])/region[2])*region[2];
      rrdy = Sqr(rDiffuseTrue[nb][nk] - rDiffuseOrg[nb][nk]);
      xyDiffuse[nb][ni] += rrdy;
      rDiffuse[nb][ni] += rrdy;

      // ACCUMULATE Z COMPONENT OF DIFFUSION
      nk = NDIM * (n-1) + 3;
      rDiffuseTrue[nb][nk] = r[3][n] + rint((rDiffuseTrue[nb][nk] - r[3][n])/region[3])*region[3];
      rrdz = Sqr(rDiffuseTrue[nb][nk] - rDiffuseOrg[nb][nk]);
      zDiffuse[nb][ni] += rrdz;
      rDiffuse[nb][ni] += rrdz;
    }
  }
  
  // ACCUMULATE DIFFUSION
  double r_fac, xy_fac, z_fac;
  int j;
  for(nb = 1 ; nb <= nBuffDiffuse ; nb ++){
    if(indexDiffuse[nb] == nValDiffuse){
      for(j = 1 ; j <= nValDiffuse ; j ++){
	rDiffuseAv[j] += rDiffuse[nb][j];
	xyDiffuseAv[j] += xyDiffuse[nb][j];
	zDiffuseAv[j] += zDiffuse[nb][j];
      }

      indexDiffuse[nb] = 0.;
      countDiffuseAv ++;
      if(countDiffuseAv == limitDiffuseAv){
	r_fac  =  1./(3*2*nAtom*stepDiffuse*deltaT*limitDiffuseAv);
	xy_fac =  1./(2*2*nAtom*stepDiffuse*deltaT*limitDiffuseAv);
	z_fac  =  1./(1*2*nAtom*stepDiffuse*deltaT*limitDiffuseAv);

	for(j = 2 ; j <= nValDiffuse ; j ++){
	  rDiffuseAv[j]  *= r_fac/(j-1);
	  xyDiffuseAv[j] *= xy_fac/(j-1);
	  zDiffuseAv[j]  *= z_fac/(j-1);
	}
	
	// PRINT DIFFUSION DATA ON TO DISK FILE 
	double tVal;
	char DIFFUSION[256];
	FILE *fpDIFFUSION;
	sprintf(DIFFUSION,"%s.DIFFUSION",PREFIX);
	if((fpDIFFUSION = fopen(DIFFUSION,"w"))==NULL){
	  perror ("Error opening file out/PREFIX.DIFFUSION ");
	}
	for(j = 1 ; j <= nValDiffuse ; j ++){
	  tVal = (j-1)*stepDiffuse*deltaT;
	  fprintf(fpDIFFUSION, "%lf\t %lf\t %lf\t %lf\n", tVal, xyDiffuseAv[j], zDiffuseAv[j], rDiffuseAv[j]);
	}
	fclose(fpDIFFUSION);

	// ZERO DIFFUSION BUFFERS
	countDiffuseAv = 0.;
	for(j = 1 ; j <= nValDiffuse ; j ++){
	  xyDiffuseAv[j] = 0.;
	  zDiffuseAv[j] = 0.;
	  rDiffuseAv[j] = 0.;
	}
      }
    }
  }
}

