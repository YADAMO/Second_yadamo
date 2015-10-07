
#include "LineReturn.h"

LineReturn::LineReturn(LineTracer *lt, Observer *ob, Drive *dr){
	lineTracer = lt;
	observer = ob;
	drive = dr;
	runtime = 0;
}

bool LineReturn::run(){
	bool end = false;
	colorid_t color = observer->judgeColor();
	switch(phase){
		case 0:
			if(drive->turn(45, -1, 5)){
				if(color == COLOR_BLACK){
					phase = 1;
					drive->turnReset();
				}
			}else{
				phase = 2;
				drive->turnReset();
			}
			break;
		case 1:
			if(drive->turn(10, -1, -8)){
			}else{
				phase = 4;
				drive->turnReset();
			}
			break;
		case 2:
			if(drive->turn(90, -1, -5)){
				if(color == COLOR_BLACK){
					phase = 3;
					drive->turnReset();
				}
			}else{
				phase = 0;
				drive->turnReset();
			}
			break;
		case 3:
			if(drive->turn(10, -1, 8)){
			}else{
				phase = 4;
				drive->turnReset();
				end = true;
			}
			break;
		case 4:

			break;
		default:
			break;
	}
	runtime++;
	return end;
}
