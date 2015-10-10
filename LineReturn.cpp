
#include "LineReturn.h"

LineReturn::LineReturn(LineTracer *lt, Observer *ob, Drive *dr){
	lineTracer = lt;
	observer = ob;
	drive = dr;
	runtime = 0;
	phase = 0;
	reDis = 0.0;
	phase2 = 0;
}

bool LineReturn::run(){
	bool end = false;
	colorid_t color = observer->judgeColor();
	drive->turn(45, LEFT, 15);
	switch(phase){
		case 0:
			if(drive->turn(45, LEFT, 15)){
				phase = 2;
			}else{
				if(color == COLOR_BLACK){
					drive->stop(false);
					drive->opeF(70*LEFT);
					phase = 1;
					drive->turnReset();
				}
			}
			break;
		case 1:
			if(drive->turn(10, LEFT, -15)){
				phase = 4;
				drive->turnReset();
				end = true;
			}
			break;
		case 2:
			if(drive->turn(90, LEFT, -15)){
				phase = 0;
			}else{
				if(color == COLOR_BLACK){
					drive->stop(false);
					drive->opeF(70*LEFT);
					phase = 3;
					drive->turnReset();
				}
			}
			break;
		case 3:
			if(drive->turn(10, LEFT, 15)){
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

bool LineReturn::run2(int dir){
	switch(phase2){
		case 0:
			reDis = 0;
			phase2++;
			drive->init(true);
			drive->Frotate(-700*dir);
			distance = observer->getDistance();
		break;

		case 1:
			color = observer->judgeColor();
			if(dir == -1){
				drive->curve(-3, 0);
			}else{
				drive->curve(0, -3);
			}

			if(observer->getDistance() - distance > 4.5){
				phase2 = 2;
				distance = observer->getDistance();
				drive->stop(true);
			}else if(color == COLOR_BLACK){
				reDis = observer->getDistance() - distance;
				phase2 = 3;
				drive->stop(true);
				drive->init(true);				
				distance = observer->getDistance();
			}
		break;

		case 2:
			if(dir == -1){
				drive->curve(3, 0);
			}else{
				drive->curve(0, 3);
			}
			if(distance - observer->getDistance() > 4.5){
				drive->init(true);
				drive->stop(true);
				phase2 = 5;
				phase = 0;
			}

		break;

		case 3:
			color = observer->judgeColor();
			drive->curve(-3, -3);
			if(observer->getDistance() - distance > 9 && color == COLOR_WHITE){
				phase2 = 4;
				distance = observer->getDistance();
				drive->stop(true);
				drive->Frotate(300*dir);
			}
		break;

		case 4:
			color = observer->judgeColor();
			if(dir == -1){
				drive->curve(0, -3);
			}else{
				drive->curve(-3, 0);
			}

			if(color == COLOR_BLACK){
				phase2 = 6;
			}
		break;

		case 5:
			if(run(dir)){
				phase2 = 6;
			}
		break;

		case 6:
			return true;
		break;
	}

	return false;
}

bool LineReturn::run(int dir){
	colorid_t color = observer->judgeColor();
	switch(phase){
		case 0:
			drive->_drive(5*dir, 7);
			if(color == COLOR_BLACK){
				phase++;
				drive->curve(0, 0);
				drive->init(true);
				drive->Frotate(-400*dir);
			}
		break;

		case 1:
			if(dir == -1){
				drive->curve(-6, 0);
			}else{
				drive->curve(0, -6);
			}
			if(color == COLOR_WHITE){
				phase++;
				drive->curve(0, 0);
				drive->init(true);
			}
		break;

		case 2:
			phase = 0;
			return true;
		break;
	}
	return false;
}
