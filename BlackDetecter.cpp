#include "BlackDetecter.h"

BlackDetecter::BlackDetecter(Color *co){
	color = co;

	for(int i = 0; i < BUFFSIZE; i++){
		buff[i] = false;
	}
}

void BlackDetecter::update(){
	for(int i = 0; i < BUFFSIZE-1; i++){
		buff[i] = buff[i+1];
	}
	buff[BUFFSIZE-1] = (color->getReflect() < 7);
}

bool BlackDetecter::onBlack(){
	for(int i = 0; i < BUFFSIZE; i++){
		if(!buff[i]){
			return false;
		}
	}
	return true;
}
