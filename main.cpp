#include <iostream>
#include "environment.h"
#include "tensor.h"
/*
#include "frame.h"
#include "body.h"
*/
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
	
	body	tHandle;
	tHandle.print();
	*/

	tensor<float> asd1(2,3);
	asd1.setInOrder();
	asd1.print();
	
	tensor<float> asd2(3,2, 13);
	asd2.print();
	tensor<float> asd3(2,2, 15);
	asd3.print();

	tensor<float> res(2,2);

	tensor<float>* Adress_asd1 = &asd1;
	tensor<float>* Adress_asd2 = &asd2;
	tensor<float>* Adress_asd3 = &asd3;
	tensor<float>* Adress_res  = &res;
	res = asd1 * asd2 * asd3;
	res.print();
	asd1.print();
	asd2.print();
	asd3.print();
	/*
	*/
	 
  	return 0;
 }
