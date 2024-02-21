#include "tensor.h"
#include "frame.h"
#include "body.h"
#include <iostream>


body::body()
	:
		MoI(3,3,0),
		mass_(0.0)
{

}



void body::print() const
{

	kinematics_.print();
	std::cout << "---------"	<< std::endl;
	dynamics_.print();
	std::cout << "MOI Tensor: " 	<< std::endl; MoI.print(); 
	std::cout << "Mass: " 		<<  mass_ << std::endl;
}
