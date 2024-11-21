#include<stdio.h>
#include<math.h>
#include<errno.h>
#include"global.h"
void EvalRdf(){    
  double dr[NDIM+1], deltaR, normFac, rr, rrRange;
  int j1, j2, k, n;
  countRdf ++;
  if(countRdf == 1){
    for(n = 1 ; n <= sizeHistRdf ; n ++)
      histRdf[n] = 0.;
  }
  rangeRdf = 0.5*region[1];
  rrRange = Sqr(rangeRdf);
  deltaR = rangeRdf / sizeHistRdf;
  for(j1 = 1 ; j1 <= nAtom - 1 ; j1 ++){
    for(j2 = j1 + 1 ; j2 <= nAtom ; j2 ++){
      for(k = 1 ; k <= NDIM ; k ++){
	dr[k] = r[k][j1] - r[k][j2];
	if(fabs(dr[k]) > regionH[k])
	  dr[k] -= SignR(region[k], dr[k]);
      }
      rr = 0.;
      for(k = 1 ; k <= NDIM ; k ++)
	rr += Sqr(dr[k]);
      if(rr < rrRange){
	n = (int)(sqrt(rr)/deltaR) + 1;
	histRdf[n] ++;
      }
    }
  }
  if(countRdf == limitRdf){
    normFac = region[1]*region[2]*region[3] / (2.*M_PI*pow(deltaR, 3.)*nAtom*nAtom*countRdf );
    for(n = 1 ; n <= sizeHistRdf ; n ++)
      histRdf[n] *= normFac/Sqr(n-0.5);
    // PRINT THE RADIAL DISTRIBUTION DATA ON TO DISK FILE
    double rBin;
    int n;
    char RDF[256];
    FILE *fpRDF;
    sprintf(RDF,"%s.RDF",PREFIX);
    if((fpRDF = fopen(RDF,"w"))==NULL){
      perror ("Error opening file out/PREFIX.RDF ");
    }
    fprintf(fpRDF,"RDF\n");
    for(n = 1 ; n <= sizeHistRdf ; n ++){
      rBin = (n - 0.5)*rangeRdf/sizeHistRdf;
      fprintf(fpRDF, "%lf %lf\n", rBin, histRdf[n]);
    }
    fclose(fpRDF);
  }
}

