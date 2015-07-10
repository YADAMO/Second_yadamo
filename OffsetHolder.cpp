#include "OffsetHolder.h"

OffsetHolder::OffsetHolder(){
	black_bright = 0;
	white_bright = 0;
	black_dark = 0;
	white_dark = 0;
}

OffsetHolder::~OffsetHolder(){
}

void OffsetHolder::setBlack(S16 value, int place){
	if     (place == BRIGHT_PLACE) black_bright = value;
	else if(place == DARK_PLACE) black_dark = value;
}

S16 OffsetHolder::getBlack(int place){
	if     (place == BRIGHT_PLACE) return black_bright;
	else if(place == DARK_PLACE) return black_dark;
}

S16 OffsetHolder::getBlack(){
	return black_bright;
}

void OffsetHolder::setWhite(S16 value,int place){
	if     (place == BRIGHT_PLACE) white_bright = value;
	else if(place == DARK_PLACE) white_dark = value;
}

S16 OffsetHolder::getWhite(int place){
	if     (place == BRIGHT_PLACE) return white_bright;
	else if(place == DARK_PLACE) return white_dark;
}

S16 OffsetHolder::getWhite(){
	return white_bright;
}
