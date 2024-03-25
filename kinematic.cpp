#include "kinematic.h"

kinematic::kinematic()
	:
		refFrameLabel_(0),
		uvw_	(3,1,0),
		pqr_	(3,1,0),
		eulers_	(3,1,0),
		mapper_	(3,3,0),
		gravity_(3,1,0)

{
       	gravity_ = {0, 0, -9.81};
       
	//uvw_.setInOrder();
	pqr_.setInOrder();
	eulers_.setInOrder();
	mapper_.setInOrder();
}


tensor<float> kinematic::getUvw() const
{
	return uvw_;
}

tensor<float> kinematic::getPqr() const
{

	return pqr_;
}

tensor<float> kinematic::getEulers() const 
{

	return eulers_;
}

tensor<float> kinematic::getMapper() const
{

	return mapper_;
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

