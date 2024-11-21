#include<stdio.h>
#include<math.h>
#include"global.h"
void EvalLattCorr(){
  double kVec[4][NDIM+1];

  // kVec[1][NDIM+1] : RECIPROCAL LATTICE VECTOR FOR FACE CENTERED CUBIC (F.C.C.)
  kVec[1][1] = 2.*M_PI*pow(density/4., 1./3.);
  kVec[1][2] = -kVec[1][1];
  kVec[1][3] = kVec[1][1];

  // kVec[2][NDIM+1] : RECIPROCAL LATTICE VECTOR FOR BODY CENTERED CUBIC (B.C.C.)
  kVec[2][1] = 2*M_PI*pow(density/2., 1./3.);    
  kVec[2][2] = 0;
  kVec[2][3] = kVec[2][1];

  // kVec[3][NDIM+1] : RECIPROCAL LATTICE VECTOR FOR SIMPLE CUBIC (S.C.)
  kVec[3][1] = 2*M_PI*pow(density, 1./3.);
  kVec[3][2] = 0;
  kVec[3][3] = 0;

  double si[4], sr[4], t[4];
  sr[1] = sr[2] = sr[3] = 0.;
  si[1] = si[2] = si[3] = 0.;
  int k, n;
  for(n = 1 ; n <= nAtom ; n ++){
    t[1] = t[2] = t[3] = 0.;
    for(k = 1 ; k <= NDIM ; k ++){
      t[1] += kVec[1][k]*r[k][n];
      t[2] += kVec[2][k]*r[k][n];
      t[3] += kVec[3][k]*r[k][n];
    }
    sr[1] += cos(t[1]);
    si[1] += sin(t[1]);
    sr[2] += cos(t[2]);
    si[2] += sin(t[2]);
    sr[3] += cos(t[3]);
    si[3] += sin(t[3]);
  }

  // LATTICE CORRELATION FOR FACE CENTERED CUBIC
  lattCorr[1] = sqrt(Sqr(sr[1]) + Sqr(si[1])) / nAtom;
  
  // LATTICE CORRELATION FOR BODY CENTERED CUBIC
  lattCorr[2] = sqrt(Sqr(sr[2]) + Sqr(si[2])) / nAtom;

  // LATTICE CORRELATION FOR SIMPLE CUBIC
  lattCorr[3] = sqrt(Sqr(sr[3]) + Sqr(si[3])) / nAtom;

  // ACCUMULATE THE RESULTS
  slattCorr[1] += lattCorr[1];
  slattCorr[2] += lattCorr[2];
  slattCorr[3] += lattCorr[3];

  if(stepCount % stepAvg == 0){
    char LATCORR[256];
    FILE *fpLATCORR;
    sprintf(LATCORR,"%s.LATCORR",PREFIX);
    if((fpLATCORR = fopen(LATCORR,"a"))==NULL){
      perror ("Error opening file out/PREFIX.LATCORR ");
    }
    slattCorr[1] /= stepAvg;
    slattCorr[2] /= stepAvg;
    slattCorr[3] /= stepAvg;
    fprintf(fpLATCORR,"(time) %lf\t (F.C.C.) %lf\t (B.C.C.) %lf\t (S.C.) %lf\n", stepCount*deltaT, slattCorr[1], slattCorr[2], slattCorr[3]);
    slattCorr[1] = 0.;
    slattCorr[2] = 0.;
    slattCorr[3] = 0.;
    fclose(fpLATCORR);
  }
}



