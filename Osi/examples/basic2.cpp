// Bare bones example of using COIN-OR OSI

#include <iostream>
#include "OsiClpSolverInterface.hpp"
//#include "OsiGlpkSolverInterface.hpp"

int
main(void)
{
   // Create a problem pointer.  We use the base class here.
   OsiSolverInterface *si;

   // When we instantiate the object, we need a specific derived class.
   si = new OsiClpSolverInterface;
   //   si = new OsiGlpkSolverInterface;  

   // Read in an mps file.  This one's from the MIPLIB library.
   si->readMps("../../Data/Sample/p0033");

   // Solve the (relaxation of the) problem
   si->initialSolve();

   // Check the solution
   if ( si->isProvenOptimal() ) { 
      std::cout << "Found optimal solution!" << std::endl; 
      std::cout << "Objective value is " << si->getObjValue() << std::endl;

      int n = si->getNumCols();
      const double *solution;
      solution = si->getColSolution();
      // We could then print the solution or examine it.
   } else {
      std::cout << "Didn't find optimal solution." << std::endl;
      // Could then check other status functions.
   }

   return 0;
}
