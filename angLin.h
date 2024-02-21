#ifndef ANGLIN_H 
#define ANGLIN_H

#include "tensor.h"

class angLin 
{

	public:
		angLin();
		angLin(float);

		tensor<float> customVel_;
		tensor<float> customAcc_;
};
#endif

