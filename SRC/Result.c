#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"global.h"
#include"yukawa.h"
void Result (){
  fprintf (fpRESULT,"Count %d\t vSum %lf\t TE %lf\t KE %lf\t PE %lf\t We %lf\n",stepCount, vSum[1]+vSum[2]+vSum[3], sTotEnergy, sKinEnergy, sPotEnergy, sEinsteinFreq);
  fflush(fpRESULT);
}
