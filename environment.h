#ifndef ENV_H
#define ENV_H
#define EULER 2.71828 
class environment {
  
	public:
		environment(float);
		float 	ppresure();
		float 	ttemperature();
		float 	ddensity();
		void 	setAttr(float);
		void 	interval(float);
	private:
		float pressure_;
		float temperature_;
		float density_;
		int interval_;
			
 };

#endif
