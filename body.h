#ifndef BODY_H
#define BODY_H

class body
{

	public:
		body(int);
		
	private:
		tensor<float> 	inertia_;
		frame		frame_;
		tensor<float>	pos_;
		tensor<float>	vel_;
		
		//void 		update(solution*);
};


#endif

