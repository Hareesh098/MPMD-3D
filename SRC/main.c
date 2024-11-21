#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include"global.h"
#include"functions.h"

const gsl_rng_type * T;
gsl_rng * rnd;

int main (int argc, char **argv){
  Init (argc, argv);
  SetParams ();
  SetParamsEwald ();
  ComputeForcesReal ();
  ComputeForcesKSpace ();

  gsl_rng_env_setup();
  T = gsl_rng_default;
  rnd = gsl_rng_alloc (T);
  gsl_rng_set (rnd, time (0));

  while (stepCount < stepLimit){
    stepCount++;
    timeNow = stepCount*deltaT;
    ComputeForcesReal ();
    ComputeForcesKSpace ();
    // UNCOMMENT IF YOU WANT TO HAVE AN EXTERNAL FORCE
    //ComputeForceExternal ();
    LeapFrog (rnd);
    ApplyPeriodics ();
    EvalProps ();
    EvalLattCorr ();
    AccumProps (1);
    if (stepCount % stepAvg == 0){
      AccumProps (2);
      Result ();
      AccumProps (0);
    }

    /*if(stepCount >= stepEquil && (stepCount - stepEquil)%stepGrid == 0){
      countGrid ++;
      GridAverage(1);
      if(countGrid % limitGrid == 0){
	GridAverage(2);
	printProfile();
	GridAverage(0);
      }
    }*/

    /*if ( (stepCount >= stepEquil) && ((stepCount-stepEquil)%stepDiffuse == 0) )
      EvalDiffusion ();

    if ( (stepCount >= stepEquil) && ((stepCount-stepEquil)%stepCorr == 0) )
      EvalSpacetimeCorr ();

    if ( (stepCount >= stepEquil) && ((stepCount-stepEquil)%stepAcf == 0) )
      EvalVelCorr ();*/

  //  if ( (stepCount >= stepEquil) && ((stepCount-stepEquil)%stepRdf == 0) )
   //   EvalRdf ();

    /*if ( (stepCount >= startTrajec) && ((stepCount-startTrajec)%stepTrajec == 0) && (stepCount - startTrajec <= timeTrajec) )
      DumpTrajectory();*/

    if ( (stepCount >= stepDump) && (stepCount % stepDump == 0) )
      DumpFinalState ();

      
  }
  fclose (fpRESULT);
  Close ();
  return 0;
}
