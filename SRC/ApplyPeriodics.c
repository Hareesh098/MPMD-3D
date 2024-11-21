#include<stdio.h>
#include<math.h>
#include"global.h"
void ApplyPeriodics (){
    int n;
    for (n = 1; n <= nAtom; n++){

      // PERIODICS ALONG X
      if ((periodicx) && (r[1][n] >= regionH[1]))	
	r[1][n] -= region[1];
      else if ((periodicx) && (r[1][n] < -regionH[1])) 
	r[1][n] += region[1];

      // PERIODICS ALONG Y
      if ((periodicy) && (r[2][n] >= regionH[2])) 
	r[2][n] -= region[2];
      else if ((periodicy) && (r[2][n] < -regionH[2])) 
	r[2][n] += region[2];

      // PERIODICS ALONG Z
      if ((periodicz) && (r[3][n] >= regionH[3])) 
	r[3][n] -= region[3];
      else if ((periodicz) && (r[3][n] < -regionH[3])) 
	r[3][n] += region[3];
    }
}
