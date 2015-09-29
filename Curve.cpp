#include "Curve.h"

Curve::Curve(Drive *dr, Observer *ob, Motor *fm, Motor *rm, Motor *lm, Color *cl, LineTracer *ln){
	drive = dr;
	observer = ob;
	Fmotor = fm;
	Rmotor = rm;
	Lmotor = lm;
	color = cl;
	lineTracer = ln;
	pid = new PID(1.8, 0.03, 0);
	disOffset = 0;
	right = 0;
	left = 0;
	front = 0;
	distance = 0;
	phase = 0;
	bright = 0;
	turn = 0;
}

bool Curve::run(int ri, int lf, int32_t fr, int32_t dis){
	switch(phase){
		case 0:
			disOffset = observer->getDistance();
			Fmotor->setRotate((-observer->Fangle + fr), 100, false);
			phase++;
		break;
		case 1:
			drive->curve(ri, lf);
			if((observer->getDistance() - disOffset) > dis){
				phase++;
			}
		break;
		case 2:
			Fmotor->setRotate(observer->Fangle, 100, false);
			return true;
		break;
	}
	return false;
}

bool Curve::runPid(int sp, int32_t fr, int32_t dis, int dir){
	switch(phase){
		case 0:
			disOffset = observer->getDistance();
			Fmotor->setRotate((-observer->Fangle + fr), 100, false);
			phase++;
		break;

		case 1:
			bright = color->getReflect();
			turn = pid->calc(lineTracer->target, bright);
			if(turn > 40)	turn = 40;
			else if(turn < 0)	turn = 0;
			if(dir == R){
				Lmotor->setSpeed(-sp);
				Rmotor->setSpeed(-sp + turn);

			}else{
				Rmotor->setSpeed(-sp);
				Lmotor->setSpeed(-sp + turn);
			}

			if((observer->getDistance() - disOffset) > dis){
				phase++;
			}
		break;

		case 2:
			Fmotor->setRotate(observer->Fangle, 100, true);
			return true;
		break;
	}
	return false;
}