#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<math.h>
#include"global.h"
#include"yukawa.h"
#include"functions.h"
void Init (int argc, char **argv){
  // OPEN OUTPUT FILES WITH GIVEN PREFIX
  if (argc != 2){
    printf ("\nUSAGE : ./main <PREFIX>\n");
    exit (1);
  }
  sprintf(DIRPREFIX,"OUT/");
  PREFIX = strcat(DIRPREFIX, argv[1]);
  sprintf (RESULT, "%s.RESULT", PREFIX);
  if((fpRESULT = fopen (RESULT, "w"))==NULL){
    perror ("Error opening file 'OUT/PREFIX.RESULT' ");
  }

  // OPEN INPUT FILE FOR READING
  FILE *input;
  if ((input = fopen ("INPUT", "r")) == NULL){	
    perror ("Error opening file 'INPUT' ");
    exit (1);
  }
  // FUNCTION 'Stripline' IS USED TO EXTRACT THE FIRST  COLUMN 
  // AND STRIP OFF EVERYTHING AFTER THE SYMBOL '#' FROM INPUT FILE.
  const int BLEN = 300; char BUF[BLEN];
  kappa = atof(Stripline(input, BUF));    
  Gamma = atof(Stripline(input, BUF));
  periodicx = atoi(Stripline(input, BUF));
  periodicy = atoi(Stripline(input, BUF));
  periodicz = atoi(Stripline(input, BUF));
  deltaT = atof(Stripline(input, BUF));
  stepAvg = atoi(Stripline(input, BUF));
  stepEquil = atoi(Stripline(input, BUF));
  stepLimit = atoi(Stripline(input, BUF));
  limitCorrAv = atoi(Stripline(input, BUF));
  nBuffCorr = atoi(Stripline(input, BUF));
  nFunCorr = atoi(Stripline(input, BUF));
  nValCorr = atoi(Stripline(input, BUF));
  stepCorr = atoi(Stripline(input, BUF));
  limitAcfAv = atoi(Stripline(input, BUF));
  nBuffAcf = atoi(Stripline(input, BUF));
  nValAcf = atoi(Stripline(input, BUF));
  stepAcf = atoi(Stripline(input, BUF));
  limitDiffuseAv = atoi(Stripline(input, BUF));
  nBuffDiffuse = atoi(Stripline(input, BUF));
  nValDiffuse = atoi(Stripline(input, BUF));
  stepDiffuse = atoi(Stripline(input, BUF));
  limitRdf = atoi(Stripline(input, BUF));
  sizeHistRdf = atoi(Stripline(input, BUF));
  stepRdf = atoi(Stripline(input, BUF));
  startTrajec = atoi(Stripline(input, BUF));
  stepTrajec = atoi(Stripline(input, BUF));
  timeTrajec = atoi(Stripline(input, BUF));
  limitGrid = atoi(Stripline(input, BUF));
  sizeHistGrid = atoi(Stripline(input, BUF));
  stepGrid = atoi(Stripline(input, BUF));
  stepDump = atoi(Stripline(input, BUF));
  fclose(input);

  // PRINT INPUT DATA TO THE OUTPUT FILE "../OUT/$PREFIX.INPUT"
  char INPUT[256];
  sprintf (INPUT, "%s.INPUT", PREFIX);
  FILE *fpINPUT;
  if((fpINPUT = fopen (INPUT, "w"))==NULL){
    perror ("Error opening file 'OUT/PREFIX.INPUT' ");
  }
  fprintf (fpINPUT, "%lf\t# kappa       : Screening parameter.\n", kappa);
  fprintf (fpINPUT, "%lf\t# Gamma       : Ratio of 'unscreened' P.E. to K.E.\n", Gamma);
  fprintf (fpINPUT, "%d\t# periodicx   : Minimum image convention along x direction.\n", periodicx);
  fprintf (fpINPUT, "%d\t# periodicy   : Minimum image convention along y direction.\n", periodicy);
  fprintf (fpINPUT, "%d\t# periodicz   : Minimum image convention along z direction.\n", periodicz);
  fprintf (fpINPUT, "%lf\t# deltaT      : Time step in units sqrt(3) / plasma frequency.\n", deltaT);
  fprintf (fpINPUT, "%d\t\t# stepAvg     : Steps to generate time average.\n", stepAvg);
  fprintf (fpINPUT, "%d\t\t# stepEquil   : Steps to wait before reaching equilibrium.\n", stepEquil);
  fprintf (fpINPUT, "%d\t\t# stepLimit   : Total number of steps in simulation.\n", stepLimit);
  fprintf (fpINPUT, "%d\t\t# limitCorrAv : No. of ensembles for averaging spacetime correlation.\n", limitCorrAv);
  fprintf (fpINPUT, "%d\t\t# nBuffCorr   : No. of overlapped buffers for recording spacetime correlation data.\n", nBuffCorr);
  fprintf (fpINPUT, "%d\t\t# nFunCorr    : No. of wave modes for studing spacetime correlation.\n", nFunCorr);
  fprintf (fpINPUT, "%d\t\t# nValCorr    : No. of temporal points in a single spacetime correlation data set.\n", nValCorr);
  fprintf (fpINPUT, "%d\t\t# stepCorr    : Sampling rate for spacetime correlation data set.\n", stepCorr);
  fprintf (fpINPUT, "%d\t\t# limitAcfAv  : No. of ensembles for averaging velocity auto-correlation.\n", limitAcfAv);
  fprintf (fpINPUT, "%d\t\t# nBuffAcf    : No. of overlapped buffers for recording velocity auto-correlation data.\n", nBuffAcf);
  fprintf (fpINPUT, "%d\t\t# nValAcf     : No. of temporal points in a single velocity auto-correlation data set.\n", nValAcf);
  fprintf (fpINPUT, "%d\t\t# stepAcf     : Sampling rate for velocity auto-correlation data set.\n", stepAcf);
  fprintf (fpINPUT, "%d\t\t# limitDiffuseAv : No. of ensembles for averaging diffusion.\n", limitDiffuseAv);
  fprintf (fpINPUT, "%d\t\t# nBuffDiffuse: No. of overlapped buffers for recording diffusion data.\n", nBuffDiffuse);
  fprintf (fpINPUT, "%d\t\t# nValDiffuse : No. of temporal points in a single diffusion data set.\n", nValDiffuse);
  fprintf (fpINPUT, "%d\t\t# stepDiffuse : Sampling rate for diffusion data set.\n", stepDiffuse);
  fprintf (fpINPUT, "%d\t\t# limitRdf    : No. of measurements to generate a single averaged RDF data.\n", limitRdf); 
  fprintf (fpINPUT, "%d\t\t# sizeHistRdf : Length of RDF histogram.\n", sizeHistRdf);
  fprintf (fpINPUT, "%d\t\t# stepRdf     : Sampling rate for RDF measurement.\n", stepRdf);
  fprintf (fpINPUT, "%d\t\t# startTrajec : Step from where we start dumping trajectory.\n", startTrajec);
  fprintf (fpINPUT, "%d\t\t# stepTrajec  : No. of steps for which trajectory is recorded after equilibrium.\n", stepTrajec);
  fprintf (fpINPUT, "%d\t\t# timeTrajec  : (x deltaT) Total time for which trajectory is recorded.\n", timeTrajec);
  fprintf (fpINPUT, "%d\t\t# limitGrid   : No. of data sets for generating Grid data.\n", limitGrid);
  fprintf (fpINPUT, "%d\t\t# sizeHistGrid: No. of grid points along z-axis.\n", sizeHistGrid);
  fprintf (fpINPUT, "%d\t\t# stepGrid    : Sampling frequency on the Grid.\n", stepGrid);
  fprintf (fpINPUT, "%d\t\t# stepDump    : Dump configuration snapshot every 'stepDump' step.\n", stepDump);
  fclose (fpINPUT);

  // READ POSITIONS, VELOCITIES FROM STATE FILE 
  FILE *STATE; char dummy[25];
  if ((STATE = fopen ("STATE", "r")) == NULL){
    perror ("Error opening file 'STATE' ");
    exit (1);
  }

  fscanf (STATE, "%s %d", dummy, &nAtom);
  r = (double **) malloc ((NDIM + 1) * sizeof (double *));
  v = (double **) malloc ((NDIM + 1) * sizeof (double *));
  a = (double **) malloc ((NDIM + 1) * sizeof (double *));
  int n, k;
  for (n = 0; n <= NDIM; n++){
    r[n] = (double *) malloc ((nAtom + 1) * sizeof (double ));
    v[n] = (double *) malloc ((nAtom + 1) * sizeof (double ));
    a[n] = (double *) malloc ((nAtom + 1) * sizeof (double ));
  }
  for (n = 1; n <= NDIM; n++)
    fscanf (STATE, "%s %lf", dummy, &region[n]);
  for (n = 1; n <= nAtom; n++){
    fscanf (STATE, "%s %lf %lf %lf %lf %lf %lf", dummy,
	&r[1][n], &r[2][n], &r[3][n], &v[1][n], &v[2][n], &v[3][n]);
  }
  fclose(STATE);

  // CHECK WHETHER HEAT BATH REQUIRED
  // stepEquil != 0 : HEAT BATH REQUIRED
  // stepEquil = 0 : HEAT BATH NOT REQUIRED
  if(stepEquil != 0){
    // CALCULATE HEAT BATH TEMPERATURE FROM THE 
    // VALUE OF GAMMA ENTERED IN THE INPUT FILE 
    temperature = 1./Gamma;
    for(k = 1 ; k <= NDIM ; k ++)
      vSum[k] = 0.;
    // GET THE INITIAL KINETIC ENERGY OF THE SYSTEM
    double vvSum = 0.;
    for (n = 1; n <= nAtom; n++){
      for(k = 1 ; k <= NDIM ; k ++){
	vvSum += Sqr(v[k][n]);
	vSum[k] += v[k][n];
      }
    }
    // GET THE CENTRE OF MASS DRIFT, IF ANY !!
    for(k = 1 ; k <= NDIM ; k ++)
      vSum[k] /= nAtom;
    // AVERAGE KINETIC ENERGY PER PARTICLE
    //vvSum /= nAtom;
    // SCALE FACTOR FOR VELOCITIES
    double sfac = sqrt((3*nAtom-4)*temperature/vvSum);
    // NOW SET THE KINETIC ENERGY TO DESIRED TEMPERATURE
    // AND SET THE VELOCITY CENTER OF MASS TO ZERO
    vvSum = 0.;
    for (n = 1; n <= nAtom; n++){
      for(k = 1 ; k <= NDIM ; k ++){
	v[k][n] = (v[k][n] - vSum[k]) * sfac;
	vvSum += Sqr(v[k][n]);
      }
    }
  }

  // SET ACCELERATIONS TO ZERO 
  for (n = 1; n <= nAtom; n++){
    for(k = 1 ; k <= NDIM ; k ++)
      a[k][n] = 0.0;
  }

  // ALLOCATE MEMORY FOR SPACETIME CORRELATIONS
  cfOrg = (double **) malloc ((nBuffCorr+1)*sizeof(double *));
  for (n = 0; n <= nBuffCorr; n++)	
    cfOrg[n] = (double *) malloc ((24*nFunCorr+1)*sizeof(double));
  cfVal = (double *) malloc ((24*nFunCorr+1)*sizeof(double));
  indexCorr = (int *) malloc ((nBuffCorr+1)*sizeof(int));
  spacetimeCorr = (double **) malloc ((nBuffCorr+1)*sizeof(double));
  for (n = 0; n <= nBuffCorr; n++)
    spacetimeCorr[n] = (double *) malloc ((3*nFunCorr*nValCorr+1)*sizeof(double));
  spacetimeCorrAv = (double *) malloc ((3*nFunCorr*nValCorr+1)*sizeof(double));

  // ALLOCATE MEMORY FOR VELOCITY AUTO CORRELATIONS
  rvAcf = (double **)malloc((nBuffAcf+1)*sizeof(double *));
  for(n = 0 ; n <= nBuffAcf ; n ++)
    rvAcf[n] = (double *)malloc((nValAcf+1)*sizeof(double));
  rvAcfOrg = (double **)malloc((nBuffAcf+1)*sizeof(double *));
  for(n = 0 ; n <= nBuffAcf ; n ++)	
    rvAcfOrg[n] = (double *)malloc((NDIM*nAtom+1)*sizeof(double));
  indexAcf = (int *)malloc((nBuffAcf+1)*sizeof(int));
  rvAcfAv = (double *)malloc((nValAcf+1)*sizeof(double));
 
  // ALLOCATE MEMORY FOR DIFFUSION MEASUREMENTS
  rDiffuse = (double**)malloc((nBuffDiffuse+1)*sizeof(double*));
  xyDiffuse = (double**)malloc((nBuffDiffuse+1)*sizeof(double*));
  zDiffuse = (double**)malloc((nBuffDiffuse+1)*sizeof(double*));
  for(n = 0 ; n <= nBuffDiffuse ; n ++){
    rDiffuse[n] = (double*)malloc((nValDiffuse+1)*sizeof(double));
    xyDiffuse[n] = (double*)malloc((nValDiffuse+1)*sizeof(double));
    zDiffuse[n] = (double*)malloc((nValDiffuse+1)*sizeof(double));
  }

  rDiffuseOrg = (double**)malloc((nBuffDiffuse+1)*sizeof(double*));
  for(n = 0 ; n <= nBuffDiffuse ; n ++)
    rDiffuseOrg[n] = (double*)malloc((NDIM*nAtom+1)*sizeof(double));

  rDiffuseTrue = (double**)malloc((nBuffDiffuse+1)*sizeof(double*));
  for(n = 0 ; n <= nBuffDiffuse ; n ++)
    rDiffuseTrue[n] = (double*)malloc((NDIM*nAtom+1)*sizeof(double));

  rDiffuseAv = (double*)malloc((nValDiffuse+1)*sizeof(double));
  xyDiffuseAv = (double*)malloc((nValDiffuse+1)*sizeof(double));
  zDiffuseAv = (double*)malloc((nValDiffuse+1)*sizeof(double));

  indexDiffuse = (int*)malloc((nBuffDiffuse+1)*sizeof(int));


  // ALLOCATE MEMORY FOR RADIAL DISTRIBUTION MEASUREMENTS
  histRdf = (double *)malloc((sizeHistRdf+1)*sizeof(double));

  // ALLOCATE MEMORY FOR GRID PROFILE
  NHIST = 5;
  Grid = (double **)malloc((NHIST+1)*sizeof(double*));
  for(n = 0 ; n <= NHIST ; n ++)
    Grid[n] = (double *)malloc((sizeHistGrid+1)*sizeof(double));
  GridTemp = (double *)malloc((sizeHistGrid+1)*sizeof(double));
  GridPop = (double *)malloc((sizeHistGrid+1)*sizeof(double));

  // SET ACCUMULATORS TO ZERO
  sPotEnergy = 0.;
  sTotEnergy = 0.0;
  sKinEnergy = 0.0;
  sEinsteinFreq = 0.;

  // INITIALISE THE STEPCOUNT
  stepCount = 0;

  // INITIALISE SPACETIME CORRELATIONS
  for (n = 1; n <= nBuffCorr; n++)
    indexCorr[n] = -(n - 1) * nValCorr / nBuffCorr;
  countCorrAv = 0.;
  for (n = 1; n <= 3 * nFunCorr * nValCorr; n++)
    spacetimeCorrAv[n] = 0.;	

  // INITIALISE VELOCITY AUTO CORRELATIONS
  for(n = 1 ; n <= nBuffAcf ; n ++)
    indexAcf[n] = -(n - 1) * nValAcf / nBuffAcf;
  countAcfAv = 0;
  for(n = 1 ; n <= nValAcf ; n++)
    rvAcfAv[n] = 0.;

  // INITIALISE EISNTEIN'S DIFFUSION
  for(n = 1 ; n <= nBuffDiffuse ; n ++)
    indexDiffuse[n] = -(n - 1)*nValDiffuse/nBuffDiffuse;
  countDiffuseAv = 0.;
  for(n = 1 ; n <= nValDiffuse ; n ++){
    rDiffuseAv[n] = 0.;
    xyDiffuseAv[n] = 0.;
    zDiffuseAv[n] = 0.;
  }

  // INITIALISE RADIAL DISTRIBUTION FUNCTION
  countRdf = 0;

  // INITIALISE LATTICE CORRELATIONS
  slattCorr[1] = 0.0;
  slattCorr[2] = 0.0;
  slattCorr[3] = 0.0;

  // INITIALISE GRID PROFILE
  GridAverage(0);
  countGrid = 0;
}
