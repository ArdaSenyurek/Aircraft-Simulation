#include <iostream>

#include "uint.h"
#include "environment.h"
#include "tensor.h"
#include "frame.h"
#include "body.h"
#include "odeSolver.h"


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
	
	tensor<float> asd2(3,1);
	asd2 = {2, 
		4, 
		5};
	asd2.print();
	tensor<float> asd3(3,1);
	asd3 = {13, 
		7, 
		9};


	asd3.print();
	tensor<float> asd4(3,3);
	asd4 = {0, 	-5,	6,
		5, 	0,	-2,
      		-3, 	2,	0};
	asd4.print();
	tensor<float> res(3,1);


	tensor<float> deneme(1,3, 13);

	tensor<float>* Adress_asd1 = &asd2;
	tensor<float>* Adress_asd2 = &asd3;
	tensor<float>* Adress_asd3 = &asd4;
	tensor<float>* Adress_res  = &res;
	res = ~(asd4 * asd2) / 3  - (deneme * asd4);
	res.print();
	tensor<float> asd2(3,2, 13);
	asd2.print();
	tensor<float> asd3(3,2, 15);
	asd3.print();
	std::cout << "-----------------------------------------------------------------" << std::endl;
	asd2 * asd3; 

	*/
	body		t;
	t.print();

	odeSolver	solver1(&t, 0.001, 1);
	solver1.solve();

  	return 0;
 }
