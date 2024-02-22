#include "dynamic.h"

dynamic::dynamic()
	:
		refFrameLabel_(0),
		force_(3,1,0),
		moment_(3,1,0)
{
}




tensor<float>& dynamic::getForce() const
{
	return force_;
}
tensor<float>& dynamic::getmoment() const
{
	return moment_;
}
void dynamic::setForce(const tensor<float>& newt)
{

	force_ = newt;
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
