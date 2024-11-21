#ifndef _global_h_
#define _global_h_

#define NDIM 3
#define SignR(x,y) (((y) >= 0) ? (x) : (- (x)))
#define	Sqr(x) 	((x)*(x))
#define	Cube(x)	((x)*(x)*(x))

double  **r;
double  **v;
double  **a;

double  region[NDIM + 1], regionH[NDIM + 1], deltaT, density, kinEnergy,
        potEnergy, sKinEnergy, sTotEnergy, sPotEnergy, temperature, Gamma,
	timeNow, totEnergy, uSum, virSum, vMag, vSum[NDIM+1];

int     nAtom, stepAvg, stepCount, stepEquil, stepLimit, startTrajec, stepTrajec, timeTrajec, stepDump;

// PERIODIC BOUNDARY FLAGS
int	periodicx, periodicy, periodicz;

// EINSTEIN's FREQUENCY
double	EinsteinFreq, sEinsteinFreq;

char    *PREFIX;
char    DIRPREFIX[250];

char    RESULT[250];
FILE    *fpRESULT;

// SPACETIME CORRELATION
double  **cfOrg, **spacetimeCorr, *cfVal, *spacetimeCorrAv;
int     *indexCorr, countCorrAv, limitCorrAv, nBuffCorr, nFunCorr, nValCorr, stepCorr;

// VELOCITY AUTO CORRELATION
double  **rvAcf, **rvAcfOrg, *rvAcfAv;
int     *indexAcf, countAcfAv, limitAcfAv, nBuffAcf, nValAcf, stepAcf;

// EINSTEIN'S DIFFUSION
double	**rDiffuse, **xyDiffuse, **zDiffuse, **rDiffuseOrg, **rDiffuseTrue, *rDiffuseAv, *xyDiffuseAv, *zDiffuseAv;
int	*indexDiffuse, countDiffuseAv, limitDiffuseAv, nBuffDiffuse, nValDiffuse, stepDiffuse;

// LATTICE CORRELATION
// lattCorr[1] = FACE CENTERED CUBIC (F.C.C.)
// lattCorr[1] = BODY CENTERED CUBIC (B.C.C.)
// lattCorr[3] = SIMPLE CUBIC (S.C.)
double	lattCorr[4], slattCorr[4];

// RADIAL DISTRIBUTION FUNCTION
double  *histRdf, rangeRdf;
int 	countRdf, limitRdf, sizeHistRdf, stepRdf;

// GRID PROFILE
int	NHIST;
double 	**Grid, *GridPop, *GridTemp;
int	sizeHistGrid, countGrid, limitGrid, stepGrid;
#endif
