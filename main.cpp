#include <iostream>
#include "environment.h"
#include "tensor.h"
#include "frame.h"
#include "body.h"
#include "uint.h"


int main()
{
	tensor<float> debug(2,3);
	debug.setInOrder();
	debug.print();
	std::cout << "-----" << std::endl;
	tensor<float> transposed_debug = ~debug;
	transposed_debug.print();
	std::cout << "-----" << std::endl;
  	return 0;
 }
