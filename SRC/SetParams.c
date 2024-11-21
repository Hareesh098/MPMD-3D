#include<stdio.h>
#include<errno.h>
#include"global.h"
#include"yukawa.h"
void SetParams (){
  // SIZE & DENSITY OF THE SYSTEM
  regionH[1] = region[1] / 2;
  regionH[2] = region[2] / 2;
  regionH[3] = region[3] / 2;
  density = nAtom / (region[1] * region[2] * region[3]);

  // PRINT THE PARAMETERS TO THE OUTPUT FILE 'OUTput/$PREFIX.PARAMS'
  char PARAMS[256];
  sprintf (PARAMS, "%s.PARAMS", PREFIX);
  FILE *fpPARAMS;
  if((fpPARAMS = fopen (PARAMS, "w"))==NULL){
    perror ("Error opening file OUT/PREFIX.PARAMS ");
  }
  fprintf (fpPARAMS, "nAtom %d\n", nAtom);
  fprintf (fpPARAMS, "region[1] %lf\n", region[1]);
  fprintf (fpPARAMS, "region[2] %lf\n", region[2]);
  fprintf (fpPARAMS, "region[3] %lf\n", region[3]);
  fprintf (fpPARAMS, "density %lf\n", density);
  fclose (fpPARAMS);
}
