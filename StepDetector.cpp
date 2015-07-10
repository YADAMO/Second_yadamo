#include "StepDetector.h"

StepDetector::StepDetector(Motor *rmotor, Motor *lmotor, Speaker *sp){
	Rmotor = rmotor;
	Lmotor = lmotor;
	speaker = sp;
}

StepDetector::~StepDetector(){

}

bool StepDetector::detect(){
	bool result = (Rmotor->isStep() == true && Lmotor->isStep() == true);
	if(result){
		speaker->playTone(442, 600, 20);	
	}

	return result;
}
