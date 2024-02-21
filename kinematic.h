#ifndef KINEMATIC_H
#define KINEMATIC_H

#include "angLin.h"
#include "tensor.h"

class kinematic
{

	public:
			
		kinematic();

		void setLinVel(const tensor<float>&);
		void setLinAcc(const tensor<float>&);
		void setAngVel(const tensor<float>&);
		void setAngAcc(const tensor<float>&);


		void print() const;

	private:
		uint refFrameLabel_;
		
		angLin linear_;
		angLin angular_;

		
};

#endif
