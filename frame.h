#ifndef FRAME_H
#define FRAME_H

#define _USE_MATH_DEFINES

#include "tensor.h"
#include <cmath>
#include <math.h>


class frame
{
	public:
		frame();
		void rotate(float, const unsigned char);

		// make data_ be in the same basis as arg frame.
		void rotate(frame);
		char getState();
		
		


	private:
		tensor<float> 	data_;
		char		state_;

};

#endif
