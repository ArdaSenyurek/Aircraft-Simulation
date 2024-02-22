#ifndef KINEMATIC_H
#define KINEMATIC_H

#include "tensor.h"

class kinematic
{

	public:
			
		kinematic();

		tensor<float>& getUvw	() const;
		tensor<float>& getPqr	() const;
		tensor<float>& getEulers() const;
		tensor<float>& getMapper() const;

		void setUvw(const tensor<float>&);
		void setPqr(const tensor<float>&);
		void setEulers(const tensor<float>&);
		void setMapper(const tensor<float>&);

		void print() const;

	private:
		uint refFrameLabel_;
		
		tensor<float> uvw_;
		tensor<float> pqr_;
		tensor<float> eulers_;
		// Transformation matrix.
		tensor<float> mapper_;

		
};

#endif
