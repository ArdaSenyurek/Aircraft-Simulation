#include "tensor.h"
#include "frame.h"
#include "body.h"

body::body(int label)
	:	
	inertia_(3, 3),
	frame_(),
	pos_(1,3),
	vel_(1,3)
	
{
	
}
