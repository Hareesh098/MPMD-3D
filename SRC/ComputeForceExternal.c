/////////////////////////////////////////////////
// THIS SUBROUTINE PROVIDES THE EXTERNAL FIELD //
/////////////////////////////////////////////////

// THE VALUE OF FLAG 'CASE' MUST BE PROPERLY CHOSEN

#include<stdio.h>
#include<math.h>
#include"global.h"

void ComputeForceExternal (){
  int CASE = 1;
  switch(CASE){
    case 1 :{
	      //////////////
  	      // CASE : 1 //
  	      //////////////
  	      // ELECTRIC  POTENTIAL V = Vo cos (K z) 
  	      // CORRESPONDING FORCE : -Vo K sin(K z)
  	      // K = 2*M_PI/Lz
  	      // Vo in units of Q^2 / (4 PI epsilon a)
	      double Vo = 0.180625;
	      double K = 2*M_PI/region[3];
	      int n;
	      for (n = 1; n <= nAtom; n++){
	    	uSum += Vo*cos(K*r[3][n]);
	    	a[3][n] += Vo*K*sin(K*r[3][n]);
	      }
	      break;
	    }
    case 2 :{
	      //////////////
	      // CASE : 2 //
	      //////////////
	      // ELECTRIC  POTENTIAL V = 0.5 K z^2
	      // CORRESPONDING FORCE : -K z
	      // K in units of Q^ / (4 PI epsilon a ^3)
	      double K = 1;
	      int n;
	      for (n = 1; n <= nAtom; n++){
		uSum += 0.5*K*Sqr(r[3][n]);
		a[3][n] += -K*r[3][n];
	      }
	      break;
	    }
    default :
	    break;
  }
}
