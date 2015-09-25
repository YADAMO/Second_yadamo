
#include "SBarcode.h"

SBarcode::SBarcode(LineTracer *lt, Observer *ob, Drive *dr){
	lineTracer = lt;
	observer = ob;
	drive = dr;
	distance = 0;
	preCol = COLOR_NONE;
	runtime = 0;
	wp = 0;
	bp = 0;
	calcend = false;
}

bool SBarcode::run(){
	bool end = false;
	double curDistance = 0;
	switch(phase){
		case 0:
			if(lineTracer->getBright() > 20){
				if(runtime > 1000){
					changeScenario();
					runtime = 0;
				}
				distance = observer->getDistance();
				preCol = observer->judgeColor();
				drive->straight(0);
			}else{
				lineTracer->trace(5,1,15);
			}
			break;
		case 1:
			curDistance = observer->getDistance();
			if(curDistance - distance > 30){
				if(runtime > 1000){
					changeScenario();
					runtime = 0;
				}
				blackStack[bp] = curDistance - distance;
				distance = observer->getDistance();
				drive->straight(0);
			}else{
				drive->straight(15);
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
		case 2:
			curDistance = observer->getDistance();
			if(curDistance - distance > 300){
				if(runtime > 1000){
					changeScenario();
					runtime = 0;
					end = true;
				}
				distance = observer->getDistance();
				drive->straight(0);
				if(!calcend){
					calcend = calcBarcode();
				}
			}else{
				drive->straight(15);
			}
			break;
		case 3:
			drive->straight(0);
			end = true;
			break;
		default:
			break;
	}
	runtime++;
	return end;
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
				pcolor = ~pcolor;
				break;
			case 6:
				for(; curbp < 1; curbp++){
					bitArray[curbp] = pcolor;
				}
				pcolor = ~pcolor;
				break;
			case 9:
				for(; curbp < 2; curbp++){
					bitArray[curbp] = pcolor;
				}
				pcolor = ~pcolor;
				break;
			case 12:
				for(; curbp < 3; curbp++){
					bitArray[curbp] = pcolor;
				}
				pcolor = ~pcolor;
				break;
			case 15:
				for(; curbp < 4; curbp++){
					bitArray[curbp] = pcolor;
				}
				pcolor = ~pcolor;
				break;
			case 18:
				for(; curbp < 5; curbp++){
					bitArray[curbp] = pcolor;
				}
				pcolor = ~pcolor;
				break;
			case 21:
				for(; curbp < 6; curbp++){
					bitArray[curbp] = pcolor;
				}
				pcolor = ~pcolor;
				break;
			case 24:
				for(; curbp < 7; curbp++){
					bitArray[curbp] = pcolor;
				}
				pcolor = ~pcolor;
				break;
			case 27:
				for(; curbp < 8; curbp++){
					bitArray[curbp] = pcolor;
				}
				pcolor = ~pcolor;
				break;
			case 30:
				for(; curbp < 8; curbp++){
					bitArray[curbp] = pcolor;
				}
				pcolor = ~pcolor;
				end = 1;
				break;
			default:
				break;
		}
	}
	return true;
}

unsigned char SBarcode::getBitArray(){
	return (bitArray[0] ||
		bitArray[1] << 1 ||
		bitArray[2] << 2 ||
		bitArray[3] << 3 ||
		bitArray[4] << 4 ||
		bitArray[5] << 5 ||
		bitArray[6] << 6 ||
		bitArray[7] << 7);
}
