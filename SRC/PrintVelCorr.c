#include<stdio.h>
#include<errno.h>
#include"global.h"
void PrintVelCorr(){
  char VELCORR[256];
  FILE *fpVELCORR;
  sprintf(VELCORR,"%s.VELCORR",PREFIX);
  if((fpVELCORR = fopen(VELCORR,"w"))==NULL){
    perror ("Error opening file out/PREFIX.VELCORR ");
  }	    
  
  fprintf(fpVELCORR,"NDIM %d\n", NDIM);
  fprintf(fpVELCORR,"nAtom %d\n", nAtom);
  fprintf(fpVELCORR,"limitAcfAv %d\n", limitAcfAv);
  fprintf(fpVELCORR,"stepAcf %d\n", stepAcf);
  fprintf(fpVELCORR,"nValAcf %d\n", nValAcf);
  fprintf(fpVELCORR,"deltaT %lf\n", deltaT);
  fprintf(fpVELCORR,"\n");

  double  tVal;
  int j;
  for( j = 1 ; j <= nValAcf ; j ++){
    tVal = (j-1)*stepAcf*deltaT;
    fprintf(fpVELCORR,"%lf\t %lf\n", tVal, rvAcfAv[j]/(nAtom*limitAcfAv));
  }
  fclose(fpVELCORR);
}
