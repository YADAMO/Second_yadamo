#include "Logger.h"

Logger::Logger(){
	bt = ev3_serial_open_file(EV3_SERIAL_BT);
	for(int i = 0; i < 16; i++){
		buff[i] = 0.0;
	}
	ptr = 0;
}

bool Logger::send(){
	sprintf(sendData, "%.3f", buff[0]);
	for(int i = 1; i < 16; i++){
		sprintf(sendData, "%s,%.3f", sendData, buff[i]);
	}
		sprintf(sendData, "%s\r", sendData);

		fprintf(bt , sendData);
		ptr = 0;

		return true;
}

void Logger::addData(double data){
	buff[ptr] = data;
	ptr++;
}

void Logger::end(){
	char tmp[20] = "EEEEEEEE";
	fprintf(bt , tmp);
}
