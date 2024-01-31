#include "environment.h"
#include <cmath>  	
environment::environment(float height)
{
	interval(height);
	setAttr(height);
	  
}
void environment::interval(float height)
{
  
	if (25000 < height) 				this -> interval_ = 3;
	if ((11000 < height) && (height < 25000))	this -> interval_ = 2;
	if (11000 > height) 				this -> interval_ = 1;
	  	
}
void environment::setAttr(float height)
{
	
  	switch (this -> interval_)
	{
	  
	  	case 1:
			this -> temperature_ 	= 15.04 - 0.00649 * height;
			this -> pressure_	= 101.29  * std::pow((this -> temperature_ + 273.1) / 288.08, 5.256);
			break;
		case 2:
			this -> temperature_ 	= -56.46;
			this -> pressure_	= 22.65 * std::pow(EULER, 1.73 - 0.000157 * height);
			break;
		case 3:
			this -> temperature_ 	= -131.21 + 0.00299 * height;
			this -> pressure_	= 2.488 * std::pow((this -> temperature_ + 273.1) / 216.6, -11.388);
			break;
	}

	this -> density_ = (this -> pressure_) / (0.2869 * (this -> temperature_ + 273.1));		
}


float environment::ppresure()
{
  	
	return pressure_;


}


float environment::ttemperature()
{
  	
	return temperature_;


}


float environment::ddensity()
{
  	
	return density_;


}


