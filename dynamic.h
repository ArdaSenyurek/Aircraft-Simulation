#ifndef DYNAMIC_H
#define DYNAMIC_H


#include "tensor.h"

class dynamic
{

	public:
			
		dynamic();
		tensor<float> getForce()  const;
		tensor<float> getMoment() const;

		void setForce	(const tensor<float>&);
		void setMoment	(const tensor<float>&);


		void print() const;

	private:
		// body = 1, inertial = 0.
		uint refFrameLabel_ = 1;
		
		tensor<float> force_;
		tensor<float> moment_;
		tensor<float> gravity_;

		
};

#endif
