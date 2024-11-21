vpath   %.h INC
INCLUDE = -I INC -I /home/ashwin/Softwares/gsl-1.15/include
VPATH   = SRC
CC      = gcc
CFLAGS  = -g -Wall -O3
LFLAGS  = -lm -lgsl -lgslcblas
LIBS	= -L /home/ashwin/Softwares/gsl-1.15/lib
OBJS    = main.o Init.o SetParams.o SetParamsEwald.o Complex.o ComputeForcesReal.o        \
	  ComputeForcesKSpace.o LeapFrog.o ApplyPeriodics.o EvalProps.o AccumProps.o      \
	  Result.o EvalSpacetimeCorr.o	PrintSpacetimeCorr.o EvalVelCorr.o PrintVelCorr.o \
	  DumpFinalState.o Close.o Stripline.o EvalLattCorr.o EvalRdf.o EvalDiffusion.o   \
	  DumpTrajectory.o ComputeForceExternal.o GridAverage.o printProfile.o

main : $(OBJS)
	$(CC) -o main $(addprefix SRC/, $(OBJS)) $(LIBS) $(LFLAGS)  

%.o : %.c 
	$(CC) -c $(CFLAGS) $(INCLUDE) $< -o $(addprefix SRC/, $@)

main.o : global.h functions.h 

ApplyPeriodics.o : global.h
Close.o : global.h
Complex.o :
ComputeForceExternal.o : global.h
ComputeForcesKSpace.o : global.h yukawa.h complex.h
ComputeForcesReal.o : global.h yukawa.h
DumpFinalState.o : global.h
DumpTrajectory.o : global.h
EvalDiffusion.o : global.h
EvalLattCorr.o : EvalLattCorr.c global.h functions.h
EvalVelCorr.o : global.h functions.h
EvalRdf.o : global.h functions.h
EvalSpacetimeCorr.o : global.h functions.h
GridAverage.o : global.h functions.h
Init.o : global.h yukawa.h
LeapFrog.o : global.h
printProfile.o : global.h
PrintSpacetimeCorr.o : global.h
PrintVelCorr.o : global.h
Result.o : global.h
SetParams.o : global.h yukawa.h
SetParamsEwald.o : global.h yukawa.h complex.h
Stripline.o : functions.h

.PHONY : clean

clean :
	rm -rf SRC/*.o main










       	

