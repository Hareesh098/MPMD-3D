#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define Sqr(x) ((x)*(x))

#define IMUL    314159269
#define IADD    453806245
#define MASK    2147483647
#define SCALE   0.4656612873e-9
double RandR(int *seed);
double RandVec3(double *p, int *seed);

double RandR(int *seed){
  *seed = (*seed * IMUL + IADD) & MASK;
  return (*seed * SCALE);
}

double RandVec3(double *p, int *pSeed){
 double x, y, s;
 s = 2;
 while(s > 1.){
 x = 2. * RandR(pSeed) - 1.; 
 y = 2. * RandR(pSeed) - 1.; 
 s = Sqr(x) + Sqr(y);
 }  
 p[3] = 1. - 2.* s; s = 2. * sqrt(1. - s);
 p[1] = s * x ; p[2] = s * y; 
 return 0;
}

int main(int argc, char **argv){

  int NX, NY, NZ;
  double density;
  double GAMMA;
  
  char dummy[25];
  FILE *fp;
  fp = fopen("STATE-PARAMS","r");
  fscanf(fp, "%s %d", dummy, &NX);
  fscanf(fp, "%s %d", dummy, &NY);
  fscanf(fp, "%s %d", dummy, &NZ);
  fscanf(fp, "%s %lf", dummy, &density);
  fscanf(fp, "%s %lf", dummy, &GAMMA);
  fclose(fp);
  
  // SET THE COORDINATES ON A SQUARE LATTICE
  double *rx, *ry, *rz;
  rx = (double *)malloc((NX*NY*NZ+1)*sizeof(double));
  ry = (double *)malloc((NX*NY*NZ+1)*sizeof(double));
  rz = (double *)malloc((NX*NY*NZ+1)*sizeof(double));
  double c[4], gap[4], region[4], e[4];
  int n;
  double nx, ny, nz;
  
  region[1] = NX/pow(density , (1. / 3.));
  region[2] = NY/pow(density , (1. / 3.));
  region[3] = NZ/pow(density , (1. / 3.));
  
  gap[1] = region[1]/NX;
  gap[2] = region[2]/NY;
  gap[3] = region[3]/NZ;
  n = 0;

for(nz = 1; nz <= NZ; nz++){  
    c[3] = (nz - 0.5) * gap[3] - 0.5*region[3];
 for(ny = 1 ; ny <= NY ; ny++){
    c[2] = (ny - 0.5) * gap[2] - 0.5*region[2];
  for(nx = 1 ; nx <= NX ; nx++){
    c[1] = (nx - 0.5) * gap[1] - 0.5*region[1];
      n ++;
      rx[n] = c[1];
      ry[n] = c[2];
      rz[n] = c[3];
   }
  }
 }
  int nAtom = n;
  // SET THE VELOCITIES FOR ALL PARTICLES
  double *vx, *vy, *vz;		
  vx = (double *)malloc((nAtom+1)*sizeof(double));
  vy = (double *)malloc((nAtom+1)*sizeof(double));
  vz = (double *)malloc((nAtom+1)*sizeof(double));
  double vSum[4];
  int randSeed = 21;
  vSum[1] = vSum[2] = vSum[3] =  0.0;
  double vMag = sqrt(3*(1.-1./nAtom)/GAMMA);
  for(n = 1 ; n <= nAtom ; n++){
    RandVec3(e, &randSeed);
    vx[n] = vMag * e[1];
    vy[n] = vMag * e[2];
    vz[n] = vMag * e[3];
    vSum[1] += vx[n];
    vSum[2] += vy[n];
    vSum[3] += vz[n];
  }
  vSum[1] /= nAtom;
  vSum[2] /= nAtom;
  vSum[3] /= nAtom;
  for(n = 1 ; n <= nAtom ; n++){
    vx[n] -= vSum[1];
    vy[n] -= vSum[2];
    vz[n] -= vSum[3];
  }
char Atom[20] = "nAtom";
  // DUMP THE STATE ON THE 'STATE' FILE
  FILE *fpSTATE;
  fpSTATE = fopen("STATE","w");
 // fprintf(fpSTATE,"timeNow 0\n");
  fprintf(fpSTATE,"%s %d\n", Atom, nAtom);
  fprintf(fpSTATE,"region[1] %E\n", region[1]);
  fprintf(fpSTATE,"region[2] %E\n", region[2]);
  fprintf(fpSTATE,"region[2] %E\n", region[3]);
  for(n = 1 ; n <= nAtom ; n ++)
   fprintf(fpSTATE,"%d %E %E %E %E %E %E \n", n, rx[n], ry[n], rz[n], vx[n], vy[n], vz[n]);
   //fprintf(fpSTATE,"%d %E %E %E\n", 1, rx[n], ry[n], rz[n]);
   fclose(fpSTATE);


  free(rx);
  free(ry);
  free(rz);
  free(vx);
  free(vy);
  free(vz);
  return 0;
  
}
 
