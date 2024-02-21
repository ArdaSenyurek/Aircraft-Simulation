#ifndef BODY_H
#define BODY_H

#include "kinematic.h"
#include "dynamic.h"

class body
{

	public:
		void print() const;
		body();
	private:
		kinematic 	kinematics_;
		dynamic		dynamics_;
		tensor<float>	MoI;
		float		mass_;
		
};


#endif

