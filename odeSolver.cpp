
#include "odeSolver.h"

odeSolver::odeSolver(body* myBody, float timeStep, uint time)
	:
		timeStep_(timeStep),
		simTime_(time),
		body_(myBody)
{
}


void odeSolver::solve()
{
	float time = 0.0;

	tensor<float> gravity(3,1);
       gravity = {0, 0, -9.81};


	while(time < simTime_)
	{
		// DID: These below lines demand copy constructor. I haven't write one.
		//
		// TODO: Can't directly access body -> kinematics_. Then I need to write getter which returns by value.
		// This demands copy constructor of kinematic class.
		tensor<float> moi	= body_ -> MoI_;
		float mass	= body_ -> mass_;

		tensor<float> pqr 	= body_ -> kinematics_.getPqr();
		tensor<float> uvw 	= body_ -> kinematics_.getUvw();
		tensor<float> eulers	= body_ -> kinematics_.getEulers();
		tensor<float> mapper 	= body_ -> kinematics_.getMapper();

		tensor<float> force     = body_ -> dynamics_.getForce();
		tensor<float> moment	= body_ -> dynamics_.getMoment();

		tensor<float>* Adress_pqr 	= &pqr;
		tensor<float>* Adress_uvw 	= &uvw;
		tensor<float>* Adress_eulers 	= &eulers;
		tensor<float>* Adress_mapper 	= &mapper;
		tensor<float>* Adress_gravity 	= &gravity;

		tensor<float>uvwDot = (force + moment) / mass + (mapper * gravity) - (pqr % uvw);
                //tensor<float>pqrDot = ~moi * (moment - pqr % (moi * pqr));
		
		std::cout << "uvwDot" << std::endl;
		uvwDot.print();
		/*
		std::cout << "pqrDot" << std::endl;
		pqrDot.print();
*/

		
		
			
		
		time += simTime_;
	}
}
