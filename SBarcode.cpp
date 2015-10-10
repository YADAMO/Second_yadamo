
#include "SBarcode.h"

SBarcode::SBarcode(LineTracer *lt, Observer *ob, Drive *dr, Logger *lg, Stepper *st){
	lineTracer = lt;
	observer = ob;
	drive = dr;
	logger = lg;
	stepper = st;
	distance = 0;
	preCol = COLOR_NONE;
	runtime = 0;
	wp = 0;
	bp = 0;
	calcend = false;
	phase = 0;
	startbitdistance = 0;
}

bool SBarcode::run(){
	bool end = false;
	double curDistance = 0;
	switch(phase){
		case 0:
			if(stepper->gRun(RIGHT)){
				changeScenario();
       			ev3_speaker_play_tone(NOTE_C4, 100);
				distance = observer->getDistance();
				drive->opeFRL(0, 0, 0);
			}
			break;
		case 1:
			if(runtime > 2000){
				changeScenario();
     			ev3_speaker_play_tone(NOTE_C4, 100);
				distance = observer->getDistance();
			}
			drive->opeFRL(0, 0, 0);
			runtime++;
			break;
		case 2:
			drive->opeFRL(0, 2, 2);
			if(distance - observer->getDistance() > 3){
				changeScenario();
			}
			break;
		case 3:
			if(lineTracer->getBright() > 47){
				if(runtime > 2000){
					changeScenario();
	     			ev3_speaker_play_tone(NOTE_E4, 100);
					distance = observer->getDistance();
					startbitdistance = distance;
				}
				runtime++;
				drive->opeFRL(0, 0, 0);
			}else{
				lineTracer->trace(8,RIGHT,0);
			}
			break;
		case 4:
			drive->opeFRL(0, 2, 2);
			if(distance - observer->getDistance() > 3){
				changeScenario();
			}
			break;
		case 5:{
			colorid_t curCol = observer->judgeColor();
			drive->opeFRL(0, -4, -4);
			if(curCol == COLOR_WHITE){
				changeScenario();
				preCol = COLOR_WHITE;
     			ev3_speaker_play_tone(NOTE_E4, 100);
				distance = observer->getDistance();
				startbitdistance = distance;
			}
			break;
		}
		case 6:{
			curDistance = observer->getDistance();
			colorid_t curCol = observer->judgeColor();
			if(curCol == COLOR_BROWN && curDistance - distance > 10){
				changeScenario();
   			    ev3_speaker_play_tone(NOTE_E4, 100);
				blackStack[bp] = curDistance - distance;
				barcodedistance = curDistance - startbitdistance;
				distance = curDistance;
				drive->opeFRL(0, 0, 0);
			}else{
				drive->opeFRL(0, -4, -4);
				if(preCol != curCol){
					if(preCol == COLOR_WHITE){
						whiteStack[wp] = curDistance - distance;
						wp++;
					}else{
						blackStack[bp] = curDistance - distance;
						bp++;
					}
					preCol = curCol;
    			    ev3_speaker_play_tone(NOTE_E4, 100);
				}
			}
			logger->addData((double)curDistance);
	    	logger->addData((double)preCol);
    		logger->addData((double)getBitArray());
   			logger->send();
			break;
		}
		case 7:
			curDistance = observer->getDistance();
			if(curDistance - distance > 30){
				if(runtime > 1000){
					changeScenario();
					end = true;
				}
				drive->opeFRL(0, 0, 0);
				if(!calcend){
					calcend = calcBarcode();
				}
				runtime++;
			}else{
				drive->opeFRL(0, -5, -5);
			}
			logger->addData((double)curDistance);
	    	logger->addData((double)preCol);
    		logger->addData((double)getBitArray());
			logger->addData((double)barcodedistance);
	    	logger->addData((double)startbitdistance);
   			logger->send();
			
			break;
		case 8:
			drive->opeFRL(0, 0, 0);
			end = true;
			logger->addData((double)curDistance);
	    	logger->addData((double)preCol);
    		logger->addData((double)getBitArray());
			logger->addData((double)barcodedistance);
	    	logger->addData((double)startbitdistance);
   			logger->send();
			break;
		default:
			break;
	}
	
	return end;
}

void SBarcode::changeScenario(){
	phase++;
	runtime = 0;
}

bool SBarcode::calcBarcode(){
	int stackp = 0;
	int curbp = 0;
	char end = 0;
	char pcolor = 0;
	for(int b = 0; b < 15; b++){
		blackStack[b] = blackStack[b] / (barcodedistance / 10);
		whiteStack[b] = whiteStack[b] / (barcodedistance / 10);
	}
	while(!end){
		int dis = 0;
		if(pcolor){
			dis = (int)(blackStack[stackp-1] + 0.5);
		}else{
			dis = (int)(whiteStack[stackp] + 0.5);
			stackp++;
		}
		switch(dis){
			case 1:
				pcolor = ~pcolor & 0x01;
				break;
			case 2:
				for(; curbp < 1; curbp++){
					bitArray[curbp] = pcolor;
				}
				pcolor = ~pcolor & 0x01;
				break;
			case 3:
				for(; curbp < 2; curbp++){
					bitArray[curbp] = pcolor;
				}
				pcolor = ~pcolor & 0x01;
				break;
			case 4:
				for(; curbp < 3; curbp++){
					bitArray[curbp] = pcolor;
				}
				pcolor = ~pcolor & 0x01;
				break;
			case 5:
				for(; curbp < 4; curbp++){
					bitArray[curbp] = pcolor;
				}
				pcolor = ~pcolor & 0x01;
				break;
			case 6:
				for(; curbp < 5; curbp++){
					bitArray[curbp] = pcolor;
				}
				pcolor = ~pcolor & 0x01;
				break;
			case 7:
				for(; curbp < 6; curbp++){
					bitArray[curbp] = pcolor;
				}
				pcolor = ~pcolor & 0x01;
				break;
			case 8:
				for(; curbp < 7; curbp++){
					bitArray[curbp] = pcolor;
				}
				pcolor = ~pcolor & 0x01;
				break;
			case 9:
				for(; curbp < 8; curbp++){
					bitArray[curbp] = pcolor;
				}
				pcolor = ~pcolor & 0x01;
				break;
			case 10:
				for(; curbp < 8; curbp++){
					bitArray[curbp] = pcolor;
				}
				pcolor = ~pcolor & 0x01;
				end = 1;
				break;
			default:
				break;
		}
	}
	return true;
}

unsigned char SBarcode::getBitArray(){
	return (bitArray[0] |
		bitArray[1] << 1 |
		bitArray[2] << 2 |
		bitArray[3] << 3 |
		bitArray[4] << 4 |
		bitArray[5] << 5 |
		bitArray[6] << 6 |
		bitArray[7] << 7);
}
