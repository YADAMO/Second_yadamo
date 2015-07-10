#include "UI.h"

UI::UI(LightSensor *light, TouchJudgement *touchJ, LineTracer *lineT, Clock *clk, Speaker *spk, OffsetHolder *oH){
	lightSensor = light;
	touchJudgement = touchJ;
	lineTracer = lineT;
	clock = clk;
	speaker = spk;
	touchCount = 0;
	judge = false;
	white_bright = 0;
	black_bright = 0;
	white_dark = 0;
	black_dark = 0;
	oHolder = oH;
}

UI::~UI(){

}

void UI::calibration(void){

	while(true){
		judge = touchJudgement->judge();
		if(judge){
			touchCount++;
			if(touchCount == 1){
				white_bright = lightSensor->getBrightness();
				oHolder->setWhite(white_bright,BRIGHT_PLACE);
				speaker->playTone(442, 10, 100);
				judge = false;
			}else if(touchCount == 2){
				black_bright = lightSensor->getBrightness();
				oHolder->setBlack(black_bright,BRIGHT_PLACE);
				speaker->playTone(442, 100, 100);
				judge = false;
			}else if(touchCount == 3){
				white_dark = lightSensor->getBrightness();
				oHolder->setWhite(white_dark,DARK_PLACE);
				speaker->playTone(884, 10, 100);
				judge = false;
			}else if(touchCount == 4){
				black_dark = lightSensor->getBrightness();
				oHolder->setBlack(black_dark,DARK_PLACE);
				speaker->playTone(884, 100, 100);
				judge = false;
			}else if(touchCount == 5){
				lineTracer->setTarget(((float)white_dark + (float)black_dark) / 2);
				lineTracer->calcAllTarget();
				speaker->playTone(1326, 100, 100);
				judge = false;
				break;
			}
		}
		clock->wait(10);
	}
	
}