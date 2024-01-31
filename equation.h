#ifndef EQUATION_H
#define EQUATION_H


//#include "expression.h"
#include "uint.h"
#include <cstdlib>
#include <stdexcept>


//TODO: Implement 3D case template.
class equation
{

	public:
		equation(char*, uint);
		
		//updates variables. This is for odeSolver where I need to update the variables and recalculate y.
		void update(float*);
		//this evaluates the equation given the input. i.e. x1,x2,x3 given where y = f(x1,x2,x3,...)
		//it evaluates y.
		float evaluate();
		
		

	private:
		//mutable expression* expressions_;

		const char* equationStr_;
		uint Nvar_;
		float* vars_;
		float res_;
		//length of equation string
		uint length_;

		// I look for + signs. Create an equation array of that size ( = # plus signs).
		void parse() const;

};




#endif
