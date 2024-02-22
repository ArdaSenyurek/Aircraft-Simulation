#ifndef ODESOLVER_H
#define ODESOLVER_H

#include "uint.h"


// This takes a handful of parameters and updates them
// given a set of differential equations.

class odeSolver
{
	public:
		// body, timestep, and simulation time.
		odeSolver(body*, float, uint);
		void solve();
	private:
		uint timeStep_;
		uint simTime_;
		solution solution_;
		body*	body_;
		
		
};


#endif

