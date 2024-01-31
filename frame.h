#ifndef FRAME_H

#define FRAME_H

class frame
{
	public:
		frame();
		
		//This rotates the frame upon instructed by solve(); (?)
		//frame_update(solution*);


	private:
		tensor<float> eulerAngles_;
		tensor<float> pqr_;

};

#endif
