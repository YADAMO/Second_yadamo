
#include "LineReturn.h"

LineReturn::LineReturn(LineTracer *lt, Observer *ob, Drive *dr){
	lineTracer = lt;
	observer = ob;
	drive = dr;
	runtime = 0;
}

bool LineReturn::run(){
	bool end = false;
	switch(phase){
		case 0:
			
			break;
		case 1:
			
			break;
		case 2:
			
			break;
		case 3:
			
			break;
		default:
			break;
	}
	runtime++;
	return end;
}
