#pragma once

#include "Messenger.h"

Messenger::Messenger(ColorSensor *colorSensor){
	this->colorSensor = colorSensor;
}

//実験用メソッド、必要なくなったら消してください
void Messenger::message(){
	char *color, *text;
	switch(colorSensor->getColorNumber()){
		case 1:
			color = "Black";
		case 2:
			color = "Blue";
		case 3:
			color = "Green";
		case 4:
			color = "Yellow";
		case 5:
			color = "Red";
		case 6:
			color = "White";
		case 7:
			color = "Brown";
		default:
			break;
	}

	strcpy(text, "Color is ");
    strcat(text, color);

	ev3_lcd_draw_string(text , 10, 10);
}