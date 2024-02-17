#include "frame.h"

frame::frame()
	:
		data_(3,3)
{
	state_ = 'n';

}

void frame::rotate(float angle, const unsigned char axis)
{
	float radian 	= angle * M_PI / 180;
	float coss 	= cos(radian);
	float sinn 	= sin(radian);
	tensor<float> rCustom(3,3);
	switch(axis)
	{
	
		case 1:
			rCustom = {	1, 	0, 	0,
					0, 	coss,	-sinn,
					0, 	sinn, 	coss
			};
			break;
		case 2:
			rCustom = {	coss, 	0, 	sinn,
					0, 	1, 	0,
					-sinn, 	0, 	coss
			};
			break;
		case 3:
			rCustom = {	coss, 	-sinn,	0,
					sinn, 	coss,	0,
					0, 	0,	1 
			};
			break;
	}
	// TODO: Move assignment in tensor. Check it.
	data_ = rCustom * &data_;
}
