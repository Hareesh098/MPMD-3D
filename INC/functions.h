#ifndef _FUNCTION_H_
#define	_FUNCTION_H_
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

void AccumProps (int ICODE);
void ApplyPeriodics ();
void Close ();
void ComputeForceExternal ();
void ComputeForcesReal ();
void ComputeForcesKSpace ();
void DumpTrajectory ();
void ApplyThermostat ();
void DumpFinalState ();
void EvalDiffusion ();
void EvalLattCorr ();
void EvalProps ();
void EvalRdf ();
void EvalSpacetimeCorr ();
void EvalVelCorr();	
void GridAverage(int);
void Init (int, char **);
void LeapFrog (gsl_rng *);
void printProfile ();
void PrintSpacetimeCorr ();
void PrintVelCorr();	
void Result ();
void SetParams ();
void SetParamsEwald ();
char *Stripline(FILE *, char *);
#endif
