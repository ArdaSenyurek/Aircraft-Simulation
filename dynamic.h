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
		uint refFrameLabel_;
		
		tensor<float> force_;
		tensor<float> moment_;
		
};

#endif
