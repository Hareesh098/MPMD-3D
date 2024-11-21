#include<stdio.h>
#include<errno.h>
#include"global.h"

void DumpFinalState (){
  char STATE[256];
  sprintf (STATE, "%s.STATE", PREFIX);
  FILE *fpSTATE;
  if((fpSTATE = fopen (STATE, "w"))==NULL){
    perror("Cant open file 'out/PREFIX.STATE' for writing");
  }
  fprintf (fpSTATE, "nAtom %d\n", nAtom);
  int k;
  for(k = 1 ; k <= NDIM ; k ++)
    fprintf (fpSTATE, "region[%d] %lf\n", k, region[k]);
  int n;
  for (n = 1; n <= nAtom; n++)
    fprintf (fpSTATE, "%d %lf %lf %lf %lf %lf %lf\n", n, r[1][n], r[2][n], r[3][n], v[1][n], v[2][n], v[3][n]);
  fclose (fpSTATE);
}
