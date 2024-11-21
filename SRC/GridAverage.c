#include<stdio.h>
#include"global.h"

void GridAverage(int opCode){
  int c, j, n;
  if(opCode == 0){
    for(j = 1 ; j <= NHIST ; j ++){
      for(n = 1 ; n <= sizeHistGrid ; n ++){
  	Grid[j][n] = 0.;
	GridTemp[n] = 0.;
	GridPop[n] = 0.;
      }
    }
  }else if(opCode == 1){
    for(n = 1 ; n <= nAtom ; n ++){
      c = (int)((r[3][n]+regionH[3])*sizeHistGrid/region[3]) + 1;
      GridPop[c] ++;
      Grid[1][c] ++;
      Grid[2][c] += Sqr(v[1][n]) + Sqr(v[2][n]) + Sqr(v[3][n]);
      Grid[3][c] += v[1][n];
      Grid[4][c] += v[2][n];
      Grid[5][c] += v[3][n];
    }
    for(n = 1 ; n <= sizeHistGrid ; n ++){
      if(GridPop[n] > 0)
	GridTemp[n] += (Grid[2][n] - Sqr(Grid[3][n]) + Sqr(Grid[4][n]) + Sqr(Grid[5][n]))/(3*GridPop[n]);
      Grid[2][n] = 0.;
      Grid[3][n] = 0.;
      Grid[4][n] = 0.;
      Grid[5][n] = 0.;
      GridPop[n] = 0.;
    }
  }else if(opCode == 2){
    for(n = 1 ; n <= sizeHistGrid ; n ++){
      GridTemp[n] /= limitGrid;
      Grid[1][n]  /= limitGrid;
    }
  }
}
