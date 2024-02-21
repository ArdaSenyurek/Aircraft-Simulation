#include "dynamic.h"

dynamic::dynamic()
	:
		refFrameLabel_(0),
		forceAndDot_(0),
		momentAndDot_(0)
{
}


void dynamic::setForce(const	tensor<float>& newT)
{

	forceAndDot_.customVel_ = newT;
}

void dynamic::setForceDot(const tensor<float>& newT)
{

	forceAndDot_.customAcc_ = newT;
}

void dynamic::setMoment(const tensor<float>& newT)
{

	momentAndDot_.customVel_ = newT;
}

void dynamic::setMomentDot(const tensor<float>& newT)
{

	momentAndDot_.customAcc_ = newT;
}

void dynamic::print() const
{

	std::cout << "linear force: "		<< std::endl; forceAndDot_.customVel_.print(); 
	std::cout << "linear forceDot: " 	<< std::endl; forceAndDot_.customAcc_.print(); 
	std::cout << "Angular moment: " 	<< std::endl; momentAndDot_.customVel_.print();
	std::cout << "Angular momentDot: " 	<< std::endl; momentAndDot_.customAcc_.print();
}
