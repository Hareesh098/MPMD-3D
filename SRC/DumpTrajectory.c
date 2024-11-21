#include<stdio.h>
#include"global.h"

void DumpTrajectory(){
  char TRAJECTORY[256];
  sprintf (TRAJECTORY, "%s.TRAJECTORY", PREFIX);
  FILE *fpTRAJECTORY;
  if((fpTRAJECTORY = fopen (TRAJECTORY, "a"))==NULL){
    perror("Cant open file 'out/PREFIX.TRAJECTORY' for writing");
  }
  int n, k;
  for(n = 1 ; n <= nAtom ; n ++){
    for(k = 1 ; k <= NDIM ; k ++)
      fprintf(fpTRAJECTORY, "%lf\t", r[k][n]);
  }
  fprintf(fpTRAJECTORY,"\n");
  fclose(fpTRAJECTORY);
}
