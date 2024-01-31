#include "equation.h"


equation::equation(char* eq, uint varNumber)
:
	equationStr_(eq),
	Nvar_(varNumber)
{

	float* vars_ = (float*) malloc(varNumber * sizeof(float));
	char temp = 0;
	uint cter = 0;
	while(temp != '\0') 
	{
		equationStr_ = eq + cter;
		length_++;
		cter++;
	}
	
	


}


float equation::evaluate()
{
	float evaulated = 0;
	
	return 0;
}

void equation::update(float* newVars)
{
	
	
}


// I expect the following:
// 				equation in the polynmoial form, i.e. a1x + a2x + a3x + b1y + b2y + b3y
// 				or coefficient can be function of variable also. f(x)x + g(x)x + b(y)y
// 				or it can be mixed, b(y)x + g(x)x + f(x)y
// 				provide only summation signs in between, i.e. a1x + -a2x + a3x + ...
// 				Seperate coefficients' dependicies with * sign, i.e. f(x)*x+g(x)*x+ ...
// 				dont include space in between i.e. f(x)*x+g(x)*x+...

void equation::parse() const
{
	uint counter = 0;
	uint* plus_array = (uint*)malloc(length_ * sizeof(uint));
	if (plus_array == nullptr) {
		throw std::runtime_error("cant alloc for plus signs in equation::parse");
	}
	
	for(uint iter = 0; iter < length_; iter++)
	{
		if (equationStr_[iter] == '+')
		{
			plus_array[counter] = iter;
			counter++;
		}
	}
	uint* compact_plus = (uint*)realloc(plus_array, counter * sizeof(uint));
	if (compact_plus == nullptr) 
	{
		free(plus_array);
		throw std::runtime_error("cant realloc for plus signs in equation::parse");
		
	}
		
	else plus_array = compact_plus;
	
	// I get the expressions in between. And tuck them to an expression array.	
	for(uint cterExp = 0; cterExp < counter; cterExp++)
	{
		uint startIndex = plus_array[cterExp];
		uint endIndex 	= plus_array[cterExp + 1];
		char** expression_raw;
		for(uint expressionCtr = startIndex; expressionCtr <= endIndex; expressionCtr++)
		{
			// This is supposed to create an array in the form {'f1(x)' ,'f2(x)', 'f3(x)', ...};
			expression_raw[cterExp][expressionCtr - startIndex] = equationStr_[expressionCtr];
			
		}	
	}
	// This modifies the expression array of the object.
	//expression_array(expression_raw);

	
		
		//char* trigonometric_check = (char*)malloc(11 * sizeof(char));
}
