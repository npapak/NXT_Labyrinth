/**
 * @file input.c
 * @brief Implementation of Input Sensor actions
 * @author Nikos Papakonstantinou <npapak@gmail.com>
 * @version v1.0
 * @date 2015-08-29
 */
#include "input.h"
#include "arm2avr.h"
#include "i2c.h"


void InputInit(void){
	return;
}

void InputExit(void){
	return;
}

enum input_states_t InputGetSensorValue(UBYTE port){
	UWORD value = IoFromAvr.AdValue[port];
	switch(port){
		case 0://port 1 light
			/*if(value > 0x234 && value < 0x3F0)*/
			if(value > 0x2A0 && value < 0x3F0)
				return LIGHT_BLACK;
			else
				return LIGHT_WHITE;
			return NO_VALUE;
		case 1://port 2 light
			/*if(value > 0x234 && value < 0x3F0)*/
			if(value > 0x2A0 && value < 0x3F0)
				return LIGHT_BLACK;
			else
				return LIGHT_WHITE;
			return NO_VALUE;
		case 2://port 3 touch
			if( value>0x3F0 && value<0x40F )
				return TOUCH_NOTPRESSED;
			else if( value>0x0A7 && value<0x0C7 )
				return TOUCH_PRESSED;
			return NO_VALUE;
		case 3://port 4
	    return NO_VALUE;
		default:
			return 0;
	}
}
