
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
	phase = 1;
}

bool SBarcode::run(){
	bool end = false;
	double curDistance = 0;
	switch(phase){
		case 1:
			if(stepper->run(RIGHT)){
				if(runtime > 2000){
					changeScenario();
         			 ev3_speaker_play_tone(NOTE_C4, 100);
				}
				drive->init(true);
				drive->curve(0, 0);
				runtime++;
			}
			break;
		case 2:
			if(lineTracer->getBright() > 45){
				if(runtime > 1000){
					changeScenario();
     			     ev3_speaker_play_tone(NOTE_D4, 100);
				}
				preCol = observer->judgeColor();
				drive->curve(0, 0);
				runtime++;
			}else{
				lineTracer->trace(7,RIGHT,0);
			}
			break;
		case 3:
			curDistance = observer->getDistance();
			if(curDistance - distance > 30){
				if(runtime > 1000){
					changeScenario();
    			      ev3_speaker_play_tone(NOTE_C4, 100);
				}
				blackStack[bp] = curDistance - distance;
				drive->curve(0, 0);
				runtime++;
			}else{
				drive->curve(-2, -2);
				colorid_t curCol = observer->judgeColor();

				if(preCol != curCol){
					if(preCol == COLOR_WHITE){
						whiteStack[wp] = curDistance - distance;
						wp++;
					}else{
						blackStack[bp] = curDistance - distance;
						bp++;
					}
					preCol = curCol;
				}
			}
			break;
		case 4:
			curDistance = observer->getDistance();
			if(curDistance - distance > 300){
				if(runtime > 1000){
					changeScenario();
					end = true;
				}
				drive->curve(0, 0);
				if(!calcend){
					calcend = calcBarcode();
				}
				runtime++;
			}else{
				drive->curve(-5, -5);
			}
			break;
		case 5:
			drive->curve(0, 0);
			end = true;
			break;
		default:
			break;
	}
	// logger->addData((double)curDistance);
 //    logger->addData((double)preCol);
 //    logger->send();
	return end;
}

void SBarcode::changeScenario(){
	phase++;
	runtime = 0;
	distance = observer->getDistance();
}

bool SBarcode::calcBarcode(){
	int stackp = 0;
	int curbp = 0;
	char end = 0;
	char pcolor = 0;
	while(!end){
		int dis = 0;
		if(pcolor){
			dis = (int)(blackStack[stackp-1] + 0.5);
		}else{
			dis = (int)(whiteStack[stackp] + 0.5);
			stackp++;
		}
		switch(dis){
			case 3:
				pcolor = ~pcolor & 0x01;
				break;
			case 6:
				for(; curbp < 1; curbp++){
					bitArray[curbp] = pcolor;
				}
				pcolor = ~pcolor & 0x01;
				break;
			case 9:
				for(; curbp < 2; curbp++){
					bitArray[curbp] = pcolor;
				}
				pcolor = ~pcolor & 0x01;
				break;
			case 12:
				for(; curbp < 3; curbp++){
					bitArray[curbp] = pcolor;
				}
				pcolor = ~pcolor & 0x01;
				break;
			case 15:
				for(; curbp < 4; curbp++){
					bitArray[curbp] = pcolor;
				}
				pcolor = ~pcolor & 0x01;
				break;
			case 18:
				for(; curbp < 5; curbp++){
					bitArray[curbp] = pcolor;
				}
				pcolor = ~pcolor & 0x01;
				break;
			case 21:
				for(; curbp < 6; curbp++){
					bitArray[curbp] = pcolor;
				}
				pcolor = ~pcolor & 0x01;
				break;
			case 24:
				for(; curbp < 7; curbp++){
					bitArray[curbp] = pcolor;
				}
				pcolor = ~pcolor & 0x01;
				break;
			case 27:
				for(; curbp < 8; curbp++){
					bitArray[curbp] = pcolor;
				}
				pcolor = ~pcolor & 0x01;
				break;
			case 30:
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
