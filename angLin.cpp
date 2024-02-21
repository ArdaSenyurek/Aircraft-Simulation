#include "angLin.h"
angLin::angLin()
	:
		customVel_(3,1,0),
		customAcc_(3,1,0)

{
	
}

angLin::angLin(float val)
	:
		customVel_(3,1, val),
		customAcc_(3,1, val)

{
	
}
