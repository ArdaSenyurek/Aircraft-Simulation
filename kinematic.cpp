#include "kinematic.h"

kinematic::kinematic()
	:
		refFrameLabel_(0),
		linear_(0),
		angular_(0)
{
}


void kinematic::setLinVel(const tensor<float>& newT)
{

	linear_.customVel_ = newT;
}

void kinematic::setLinAcc(const tensor<float>& newT)
{

	linear_.customAcc_ = newT;
}


void kinematic::setAngVel(const tensor<float>& newT)
{

	angular_.customVel_ = newT;
}

void kinematic::setAngAcc(const tensor<float>& newT)
{

	angular_.customAcc_ = newT;
}

void kinematic::print() const
{

	std::cout << "linear velocity: "     << std::endl;	linear_.customVel_.print();
	std::cout << "linear Acceleration: " << std::endl;	linear_.customAcc_.print();
	std::cout << "Angular velocity: "    << std::endl;	angular_.customVel_.print();
	std::cout << "Angular Acceleration: "<< std::endl;	angular_.customAcc_.print();
}

