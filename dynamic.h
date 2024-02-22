#ifndef DYNAMIC_H
#define DYNAMIC_H


#include "angLin.h"
#include "tensor.h"

class dynamic
{

	public:
			
		dynamic();
		void setForce		(const tensor<float>&);
		void setMoment		(const tensor<float>&);


		void print() const;

	private:
		uint refFrameLabel_;
		
		tensor<float> force_;
		tensor<float> moment_;
		
};

#endif
