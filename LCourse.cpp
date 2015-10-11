#include "LCourse.h"

LCourse::LCourse(LineTracer *lt, Curve *cv, Observer *ob, STwinBridge *st, LineReturn *lr, SBarcode *bar, SUndetermined *und, Drive *dr){
	lineTracer = lt;
	curve = cv;
	observer = ob;
	bridge = st;
	barcode = bar;
	undetermined = und;
	lineReturn = lr;
	drive = dr;
	distance = 0;
	phase = 0;
}

bool LCourse::run(){
	switch(phase){
		case 0:
			// lineTracer->changeGain(0.2, 0.01, 0.25);
            // lineTracer->fastrace(95, RIGHT, 0);
	

			// lineTracer->changeGain(0.14, 0.032, 0.4);
            // lineTracer->fastrace(40, RIGHT, 0);

   			// lineTracer->changeGain(0.125, 0.025, 0.5);
            // lineTracer->changeGain(0.28, 0.032, 0.4);
            // lineTracer->fastrace(25, RIGHT, 0);

			lineTracer->changeGain(0.9, 0, 0.02);
			lineTracer->trace(20, RIGHT, 0);

			if(observer->getDistance() - distance > LSTART){
				changeScenario();
			}
		break;

		case 1:
			lineTracer->changeGain(0.9, 0, 0.02);
			lineTracer->trace(20, RIGHT, 0);
			// lineTracer->changeGain(0.125, 0.025, 0.5);
            // lineTracer->changeGain(0.28, 0.032, 0.4);
            // lineTracer->fastrace(25, RIGHT, 0);
            if(observer->getDistance() - distance > LBC1){
				changeScenario();
			}
		break;

		case 2:
		// return true;
				curve->changeGain(1.5, 0, 0);
			if(curve->curve(5, 60, LC1, R, 9, R)){
				changeScenario();
				lineTracer->changeGain(1.5, 0, 0.02);
				distance = observer->getDistance();
			}
		break;

		case 3:
			if(lineReturn->run(RIGHT)){
				changeScenario();	
			}
		break;

		case 4:
			lineTracer->changeGain(0.9, 0, 0.02);
			lineTracer->trace(20, RIGHT, 0);
			if(observer->getDistance() - distance > LAC1){
				changeScenario();
			}
		break;

		case 5:
			if(bridge->run()){
				changeScenario();
				drive->init(true);
			}
		break;

		case 6:

			// drive->curve(-5, -5);
			// if(observer->getDistance() - distance > LACC){
				changeScenario();
			// }
		break;

		case 7:
			curve->changeGain(1.5, 0, 0);
			if(curve->curve(3, 30, LCC, L, 7, R)){
				changeScenario();
				drive->curve(0, 0);
				drive->init(true);
			}
		break;

		case 8:
			if(lineReturn->run2(1)){
				changeScenario();
			}
		break;

		case 9:
			if(barcode->run()){
				changeScenario();
			}
		break;

		case 10:
			if(undetermined->run()){
				changeScenario();
			}
		break;

		case 11:
			return true;
		break;
	}

	return false;

}

void LCourse::changeScenario(){
	phase++;
	distance = observer->getDistance();
}
