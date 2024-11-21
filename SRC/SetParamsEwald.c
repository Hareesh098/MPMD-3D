#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<errno.h>
#include"complex.h"
#include"global.h"
#include"yukawa.h"

void SetParamsEwald (){
  // WIDTH OF GAUSSIAN CHARGE DISTRIBUTION                        
  beta = 5.6 / region[1];
  kvec = (double *) malloc ((maxk + 1) * sizeof (double));

  // CALCULATE SELF ENERGY OF THE SYSTEM
  SelfEnergy = nAtom * ( (beta/sqrt(M_PI))*exp(-Sqr(kappa/(2.*beta))) - (kappa/2.)*erfc(kappa/(2.*beta)) );
  
  // ALLOCATE MEMORY FOR COMPLEX EXPONENTS
  eikx = (dcomplex **) malloc ((nAtom + 1) * sizeof (dcomplex *));
  eiky = (dcomplex **) malloc ((nAtom + 1) * sizeof (dcomplex *));
  eikz = (dcomplex **) malloc ((nAtom + 1) * sizeof (dcomplex *));
  eikr = (dcomplex *) malloc ((nAtom + 1) * sizeof (dcomplex));
  int i;
  for (i = 0; i <= nAtom; i++){
    eikx[i] = (dcomplex *) malloc ((kmax + 1) * sizeof (dcomplex));
    eiky[i] = (dcomplex *) malloc ((2 * kmax + 1) * sizeof (dcomplex));
    eikz[i] = (dcomplex *) malloc ((2 * kmax + 1) * sizeof (dcomplex));
  }
  
  // STORE THE K - VECTORS ON THE DISK FILE 'OUTput/$PREFIX.EWALD'
  char EWALD[256];
  sprintf (EWALD, "%s.EWALD", PREFIX);
  FILE *fpEWALD;
  if((fpEWALD = fopen (EWALD, "w"))==NULL){
    perror ("Error opening file 'OUT/PREFIX.EWALD' ");
  }
  fprintf(fpEWALD, "kx\t ky\t kz\t ksq\t Sqr(k)+Sqr(kappa)\t kvec[k]\n");
  int totk = 0;
  int kx, ky, kz, ksq;
  double rkx, rky, rkz, rksq;
  double vol = Cube (region[1]);
  double twopiByL = 2*M_PI/region[1];
  double twopiByvol = 2*M_PI/vol;
  double B = 1. / (4 * Sqr (beta));
  for (kx = 0; kx <= kmax; kx++){
    rkx = twopiByL*kx;
    for (ky = -kmax; ky <= kmax; ky++){
      rky = twopiByL * ky;
      for (kz = -kmax; kz <= kmax; kz++){
	rkz = twopiByL*kz;
	ksq = Sqr (kx) + Sqr (ky) + Sqr (kz);
	if ((ksq <= ksqmax) && (ksq != 0)){
	  totk++;
	  if (totk > maxk){
	    fprintf (stdout, "\nArray 'kvec[]' is too small\n");
	    exit (1);
	  }
	  rksq =  Sqr (rkx) + Sqr (rky) + Sqr (rkz) + Sqr (kappa);
	  kvec[totk] = twopiByvol*exp(-B * rksq) / rksq;
	  fprintf(fpEWALD, "%d\t %d\t %d\t %d\t %lf\t %lf\n", kx, ky, kz, ksq, rksq, kvec[totk]);
	}
      }
    }
  }
  fprintf (fpEWALD, "No. of wavevectors is %d\n", totk);
  fprintf (fpEWALD, "Self Energy %lf\n",SelfEnergy);
  fclose (fpEWALD);
}
