/**
 * @file output.c
 * @brief Implementation of Motors actions
 * @author Nikos Papakonstantinou <npapak@gmail.com>
 * @version v1.0
 * @date 2015-08-29
 */
#include "output.h"
#include "arm2avr.h"
#include "i2c.h"

void      OutputInit(void){

	int i;

	IoToAvr.Power = NORMAL_OP;
	IoToAvr.PwmFreq = 8;
	for(i=0; i<4;++i){
		IoToAvr.PwmValue[i] = 0;
	}
	IoToAvr.OutputMode = 0;//break all
	IoToAvr.InputPower = 1;
}
void      OutputExit(void){
	return;
}

void      OutputSetSpeed (UBYTE MotorNr, SBYTE Speed)
{

	if(Speed == 0){
		IoToAvr.OutputMode = (1 << MotorNr);
		IoToAvr.PwmValue[MotorNr] = 0;
	}
	else{
		IoToAvr.OutputMode &= ( 0x07 & (~(1 << MotorNr)) ); // enable the right motor
		if(Speed > MAX_SPEED_FW)
			IoToAvr.PwmValue[MotorNr] = MAX_SPEED_FW;
		else if(Speed < MAX_SPEED_RW)
			IoToAvr.PwmValue[MotorNr] = MAX_SPEED_FW;
		else
			IoToAvr.PwmValue[MotorNr] = Speed;
	}

}
