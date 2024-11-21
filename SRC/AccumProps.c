#include<stdio.h>
#include<math.h>
#include"global.h"

void AccumProps (int ICODE){
  if (ICODE == 0){
    sPotEnergy = 0.0;
    sTotEnergy = 0.0;
    sKinEnergy = 0.0;
    sEinsteinFreq = 0.0;
  }else if (ICODE == 1){
    sTotEnergy += totEnergy;
    sPotEnergy += potEnergy;
    sKinEnergy += kinEnergy;
    sEinsteinFreq += EinsteinFreq;
  }else if (ICODE == 2){
    sTotEnergy /= stepAvg;
    sPotEnergy /= stepAvg;
    sKinEnergy /= stepAvg;
    sEinsteinFreq /= stepAvg;
  }
}
