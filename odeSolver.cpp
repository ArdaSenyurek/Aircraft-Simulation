
#include "odeSolver.h"

odeSolver::odeSolver(body* myBody, float timeStep, uint time)
	:
		body_(myBody),
		timeStep_(timeStep),
		simTime_(time)
{
}


void odeSolver::solve()
{
	float time = 0.0;

	tensor<float> gravity(3,1) = {0, 0, -9.81};

	while(time < simTime_)
	{
		// TODO: These below lines demand copy constructor. I haven't write one.
		tensor<float> moi	= myBody -> getMoI();
		tensor<float> mass	= myBody -> getMass();

		tensor<float> pqr 	= myBody -> kinematics_ -> getPqr();
		tensor<float> uvw 	= myBody -> kinematics_ -> getUvw();
		tensor<float> eulers	= myBody -> kinematics_ -> getEuler();
		tensor<float> mapper 	= myBody -> kinematics_ -> getMapper();

		tensor<float> force     = myBody -> dynamics_ -> getForce();
		tensor<float> moment	= myBody -> dynamics_ -> getMoment();

		tensor<float> uvwDot(3, 1, 0);

		uvwDot = (force + moment) / mass + (mapper * gravity) - (pqr << uvw);

		pqrDot = ~moi * (moment - pqr << (moi * pqr));




		
		
			
		
		time += simTime_;
	}
}
