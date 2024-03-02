
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
		tensor<float> moi	= body_ -> MoI;
		tensor<float> mass	= body_ -> Mass;

		tensor<float> pqr 	= body_ -> kinematics_.getPqr();
		tensor<float> uvw 	= body_ -> kinematics_.getUvw();
		tensor<float> eulers	= body_ -> kinematics_.getEuler();
		tensor<float> mapper 	= body_ -> kinematics_.getMapper();

		tensor<float> force     = body_ -> dynamics_ -> getForce();
		tensor<float> moment	= body_ -> dynamics_ -> getMoment();


		tensor<float>uvwDot = (force + moment) / mass + (mapper * gravity) - (pqr << uvw);
                tensor<float>pqrDot = ~moi * (moment - pqr << (moi * pqr));
		




		
		
			
		
		time += simTime_;
	}
}
