#include<stdio.h>
#include<errno.h>
#include"global.h"

void printProfile(){
  char GRID[256];
  sprintf (GRID, "%s.GRID", PREFIX);
  FILE *fpGRID;
  if((fpGRID = fopen (GRID, "a"))==NULL){
    perror("Cant open file 'out/PREFIX.GRID' for writing");
  }
  int n;
  for(n = 1 ; n <= sizeHistGrid ; n ++)
    fprintf(fpGRID, "timeNow %lf\t GridPos %lf\t Occupation %lf\t Temperature %lf\n", timeNow, -regionH[3]+(n-0.5)*region[3]/sizeHistGrid, Grid[1][n], GridTemp[n]);
  fprintf(fpGRID,"\n");
  fclose(fpGRID);
}
