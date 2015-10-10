#include "Curve.h"

Curve::Curve(Drive *dr, Observer *ob, Motor *fm, Motor *rm, Motor *lm, Color *cl, LineTracer *ln){
	drive = dr;
	observer = ob;
	Fmotor = fm;
	Rmotor = rm;
	Lmotor = lm;
	color = cl;
	lineTracer = ln;
	pid = new PID(0.5, 0, 0);
	disOffset = 0;
	right = 0;
	left = 0;
	front = 0;
	distance = 0;
	phase = 0;
	bright = 0;
	turn = 0;
	curveSP = 20;
}

bool Curve::run(int ri, int lf, int32_t fr, int32_t dis){
	switch(phase){
		case 0:
			disOffset = observer->getDistance();
			Lmotor->setSpeed(0);
			Rmotor->setSpeed(0);
			Fmotor->setRotate((observer->Fangle + fr), 100, true);
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

bool Curve::run(int dif, int32_t fr, int32_t dis, int dir, int sp){
	switch(phase){
		case 0:
			disOffset = observer->getDistance();
			Lmotor->setSpeed(0);
			Rmotor->setSpeed(0);
			Fmotor->setRotate((observer->Fangle + fr), 100, true);
			phase++;
		break;
		case 1:
			if(dir == R){
				Lmotor->setSpeed(-sp);
				Rmotor->setSpeed(-sp + dif);

			}else{
				Rmotor->setSpeed(-sp);
				Lmotor->setSpeed(-sp + dif);
			}

			if((observer->getDistance() - disOffset) > dis && dis >= 0){
				phase++;
			}
			if((disOffset - observer->getDistance()) > -dis && dis < 0){
				phase++;
			}
		break;
		case 2:
			Lmotor->setSpeed(0);
			Rmotor->setSpeed(0);
			Fmotor->setRotate(observer->Fangle, 100, true);
			phase = 0;
			return true;
		break;
	}
	return false;
}

bool Curve::runPid(int dif, int32_t fr, int32_t dis, int dir){
	switch(phase){
		case 0:
			disOffset = observer->getDistance();
			Lmotor->setSpeed(0);
			Rmotor->setSpeed(0);
			Fmotor->setRotate((observer->Fangle + fr), 100, true);
			phase++;
		break;

		case 1:
			bright = color->getReflect();
			turn = dir * pid->calc(lineTracer->target, bright);
			if(turn > curveSP)	turn = curveSP;
			else if(turn < -curveSP)	turn = -curveSP;
			if(dir == R){
				Lmotor->setSpeed(-curveSP);
				Rmotor->setSpeed(-curveSP + dif - turn);

			}else{
				Rmotor->setSpeed(-curveSP);
				Lmotor->setSpeed(-curveSP + dif - turn);
			}

			if((observer->getDistance() - disOffset) > dis){
				phase++;
			}
		break;

		case 2:
			Lmotor->setSpeed(0);
			Rmotor->setSpeed(0);
			Fmotor->setRotate(observer->Fangle, 100, true);
			phase = 0;
			return true;
			
		break;
	}
	return false;
}

void Curve::changeGain(float p, float i, float d){
	pid->changeGain(p, i, d);
}

bool Curve::runPid(int dif, int32_t fr, int32_t dis, int dir, int sp){
	switch(phase){
		case 0:
			disOffset = observer->getDistance();
			Lmotor->setSpeed(0);
			Rmotor->setSpeed(0);
			Fmotor->setRotate((observer->Fangle + fr), 100, true);
			phase++;
		break;

		case 1:
			bright = color->getReflect();
			turn = dir * pid->calc(lineTracer->target, bright);
			if(dir == R){
				Lmotor->setSpeed(-sp);
				Rmotor->setSpeed(-sp + dif - turn);

			}else{
				Rmotor->setSpeed(-sp);
				Lmotor->setSpeed(-sp + dif - turn);
			}

			if((observer->getDistance() - disOffset) > dis){
				phase++;
			}
		break;

		case 2:
			Lmotor->setSpeed(0);
			Rmotor->setSpeed(0);
			Fmotor->setRotate(observer->Fangle, 100, true);
			phase = 0;
		return true;
		break;
	}
	return false;
}

bool Curve::curve(int dif, int angle, int dis, int dir, int sp, int edge){
	switch(phase){
		case 0:
			disOffset = observer->getDistance();
			Lmotor->setSpeed(0);
			Rmotor->setSpeed(0);
			Fmotor->setRotate((observer->Fangle + (int)700*((double)angle/90.0)), 100, true);
			phase++;
		break;

		case 1:
			bright = color->getReflect();
			turn = dir * pid->calc(lineTracer->target, bright);
			Fan = dir*angle - turn;
			if(dir == R){
				Lmotor->setSpeed(-sp);
				Rmotor->setSpeed(-sp + dif - (turn / 10));
				if(dir*angle+20 < Fan){
					Fan = angle + 20;
				}else if(dir*angle-20 > Fan){
					Fan = angle - 20;
				}
				drive->opeF(Fan);
			}else{
				Rmotor->setSpeed(-sp);
				Lmotor->setSpeed(-sp + dif - (turn / 10));
				if(dir*angle-20 > Fan){
					Fan = -angle - 20;
				}else if(dir*angle + 20 < Fan){
					Fan = -angle + 20;
				}
				drive->opeF(Fan);

			}

			if((observer->getDistance() - disOffset) > dis){
				phase++;
			}
		break;

		case 2:
			Lmotor->setSpeed(0);
			Rmotor->setSpeed(0);
			Fmotor->setRotate(observer->Fangle, 100, true);
			phase = 0;
		return true;
		break;
	}
	return false;
}
