#include "kinematic.h"

kinematic::kinematic()
	:
		refFrameLabel_(0),
		uvw_	(3,1,0),
		pqr_	(3,1,0),
		eulers_	(3,1,0),
		mapper_	(3,1,0)

{
}


void kinematic::setUvw(const tensor<float>& newT)
{

	uvw_ = newT;
}

void kinematic::setPqr(const tensor<float>& newT)
{

	pqr_ = newT;
}


void kinematic::setEulers(const tensor<float>& newT)
{

	eulers_ = newT;
}

void kinematic::setMapper(const tensor<float>& newT)
{

	mapper_ = newT;
}

void kinematic::print() const
{

	std::cout << "uvw: "		<< std::endl;	uvw_.print();
	std::cout << "pqr: "		<< std::endl;	pqr_.print();
	std::cout << "eulers: "    	<< std::endl;	eulers_.print();
	std::cout << "mapper: "		<< std::endl;	mapper_.print();
}

