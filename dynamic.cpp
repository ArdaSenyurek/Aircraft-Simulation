#include "dynamic.h"

dynamic::dynamic()
	:
		refFrameLabel_(0),
		force_(3,1,0),
		moment_(3,1,0)
{
}


void dynamic::setForce(const	tensor<float>& newT)
{

	force_ = newT;
}


void dynamic::setMoment(const tensor<float>& newT)
{

	moment_ = newT;
}

void dynamic::print() const
{

	std::cout << "linear force: "		<< std::endl; force_.print(); 
	std::cout << "Angular moment: " 	<< std::endl; moment_.print();
}
