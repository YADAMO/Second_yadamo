#include "LCourse.h"

LCourse::LCourse(LineTracer *lt, Curve *cv, Observer *ob, STwinBridge *st, SBarcode *bar, SUndetermined *und){
	lineTracer = lt;
	curve = cv;
	observer = ob;
	bridge = st;
	barcode = bar;
	undetermined = und;
	phase = 5;
	distance = 0;
}

bool LCourse::run(){
	switch(phase){
		case 0:
			lineTracer->changeGain(0.5, 0.04, 0.03);
            lineTracer->fastrace(30, RIGHT, 0);
			if(observer->getDistance() - distance > LSTART){
				changeScenario();
				distance = observer->getDistance();
			}
		break;

		case 1:
			// lineTracer->changeGain(0.8, 0.045, 0.08);
            lineTracer->fastrace(15, RIGHT, 0);
            if(observer->getDistance() - distance > LBC1){
				changeScenario();
				distance = observer->getDistance();
			}
		break;

		case 2:
			if(curve->runPid(10, -465, LC1, R)){
				changeScenario();
				lineTracer->changeGain(1.5, 0, 0.02);
				distance = observer->getDistance();
			}
		break;

		case 3:
			lineTracer->traceReturn(20, RIGHT, 0);
			if(observer->getDistance() > LAC1){
				changeScenario();
			}
		break;

		case 4:
			if(bridge->run()){
				changeScenario();
			}
		break;

		case 5:
			if(barcode->run()){
				changeScenario();
			}
		break;

		case 6:
			if(undetermined->run()){
				changeScenario();
			}
		break;

		case 7:
			return true;
		break;
	}

	return false;

}
