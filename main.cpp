#include <iostream>
#include "environment.h"
#include "tensor.h"
#include "frame.h"
#include "body.h"
#include "uint.h"


int main()
{
	/*
	tensor<float> debug(2,3);
	debug.setInOrder();
	debug.print();
	std::cout << "-----" << std::endl;
	tensor<float> transposed_debug = ~debug;
	transposed_debug.print();
	std::cout << "*****" << std::endl;

	tensor<float> a = transposed_debug[1];
	a.print();

	std::cout << "/////" << std::endl;
	debug[1].print();
	
	*/
	tensor<float> debug_first(2,3);
	debug_first.setInOrder();
	debug_first.print();

	tensor<float> debug_second(3,2, 13);
	debug_second.print();
	
	 
  	return 0;
 }
