#include<stdio.h>
#include"global.h"
void PrintSpacetimeCorr (){
  char CURRLONG[256], CURRTRANS[256], CURRDENSITY[256];
  FILE *fpCURRLONG, *fpCURRTRANS, *fpCURRDENSITY;
  sprintf (CURRLONG, "%s.CURR-LONG", PREFIX);
  sprintf (CURRTRANS, "%s.CURR-TRANS", PREFIX);
  sprintf (CURRDENSITY, "%s.CURR-DENSITY", PREFIX);
  if((fpCURRLONG = fopen (CURRLONG, "w"))==NULL){
    perror ("Error opening file OUT/PREFIX.CURR-LONG ");
  }
  if((fpCURRTRANS = fopen (CURRTRANS, "w"))==NULL){
    perror ("Error opening file OUT/PREFIX.CURR-TRANS ");
  }
  if((fpCURRDENSITY = fopen (CURRDENSITY, "w"))==NULL){
    perror ("Error opening file OUT/PREFIX.CURR-DENSITY");
  }

  double tVal;
  int j, n, nn;
  fprintf(fpCURRLONG,"NDIM %d\n", NDIM);
  fprintf(fpCURRLONG,"nAtom %d\n", nAtom);
  fprintf(fpCURRLONG,"region %lf\n", region[1]);
  fprintf(fpCURRLONG,"nFunCorr %d\n", nFunCorr);
  fprintf(fpCURRLONG,"limitAcfAv %d\n", limitAcfAv);
  fprintf(fpCURRLONG,"stepAcf %d\n", stepAcf);
  fprintf(fpCURRLONG,"nValAcf %d\n", nValAcf);
  fprintf(fpCURRLONG,"deltaT %lf\n", deltaT);
  for (n = 1; n <= nValCorr; n++){
    tVal = (n-1)*stepCorr*deltaT;
    fprintf (fpCURRLONG, "%e\t", tVal);
    nn = 3*nFunCorr*(n-1);
    for (j = 1; j <= 3*nFunCorr; j += 3)
      fprintf (fpCURRLONG, "%e\t", spacetimeCorrAv[nn + j]);
    fprintf (fpCURRLONG, "\n");
  }

  fprintf(fpCURRTRANS,"NDIM %d\n", NDIM);
  fprintf(fpCURRTRANS,"nAtom %d\n", nAtom);
  fprintf(fpCURRTRANS,"region %lf\n", region[2]);
  fprintf(fpCURRTRANS,"nFunCorr %d\n", nFunCorr);
  fprintf(fpCURRTRANS,"limitCorrAv %d\n", limitCorrAv);
  fprintf(fpCURRTRANS,"stepCorr %d\n", stepCorr);
  fprintf(fpCURRTRANS,"nValCorr %d\n", nValCorr);
  fprintf(fpCURRTRANS,"deltaT %lf\n", deltaT);
  for (n = 1; n <= nValCorr; n++){
    tVal = (n-1)*stepCorr*deltaT;
    fprintf (fpCURRTRANS, "%e\t", tVal);
    nn = 3*nFunCorr*(n-1);
    for (j = 2; j <= 3 * nFunCorr; j += 3)
      fprintf (fpCURRTRANS, "%e\t", spacetimeCorrAv[nn + j]);
    fprintf (fpCURRTRANS, "\n");
  }

  fprintf(fpCURRDENSITY,"NDIM %d\n", NDIM);
  fprintf(fpCURRDENSITY,"nAtom %d\n", nAtom);
  fprintf(fpCURRDENSITY,"region %lf\n", region[3]);
  fprintf(fpCURRDENSITY,"nFunCorr %d\n", nFunCorr);
  fprintf(fpCURRDENSITY,"limitCorrAv %d\n", limitCorrAv);
  fprintf(fpCURRDENSITY,"stepCorr %d\n", stepCorr);
  fprintf(fpCURRDENSITY,"nValCorr %d\n", nValCorr);
  fprintf(fpCURRDENSITY,"deltaT %lf\n", deltaT);
  for (n = 1; n <= nValCorr; n++){
    tVal = (n-1)*stepCorr*deltaT;
    fprintf (fpCURRDENSITY, "%e\t", tVal);
    nn = 3*nFunCorr*(n-1);
    for (j = 3; j <= 3 * nFunCorr; j += 3)
      fprintf (fpCURRDENSITY, "%e\t", spacetimeCorrAv[nn + j]);
    fprintf (fpCURRDENSITY, "\n");
  }

  fclose (fpCURRLONG);
  fclose (fpCURRTRANS);
  fclose (fpCURRDENSITY);
}
