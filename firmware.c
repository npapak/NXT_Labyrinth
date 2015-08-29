/**
 * @file firmware.c
 * @brief Firmware file.
 * @author Nikos Papakonstantinou <npapak@gmail.com>
 * @version v1.0
 * @date 2015-08-29
 */
#include <stdlib.h>
#include <assert.h>
#include "AT91SAM7S256.h"
#include "hwinit.h"
#include "pit.h"
#include "aic.h"
#include "display.h"
#include "i2c.h"
#include "input.h"
#include "button.h"
#include "output.h"
#include "led.h"
#include "scheduler.h"
#include "queue.h"

void sensors(){
	static int motor_state = 0;
	enum input_states_t front_light_sensor, right_light_sensor, touch_sensor ;
	enum button_t button;

	DisplayErase();
	if(motor_state == 1)
		OutputSetSpeed(2,MAX_SPEED_FW);

	right_light_sensor = InputGetSensorValue(0);
	front_light_sensor = InputGetSensorValue(1);
	if( front_light_sensor == LIGHT_WHITE && right_light_sensor == LIGHT_BLACK){
		if( motor_state == 1 ){
			PITInterruptDisable();
			DisplayString(0, 16, "Go Forward!");
			OutputSetSpeed (0,70);
			OutputSetSpeed (1,70);
		}
		else{
			DisplayString(0, 16, "Motors Stopped!");
		}
	}
	else if( front_light_sensor == LIGHT_BLACK && right_light_sensor == LIGHT_BLACK){
		if( motor_state == 1 ){
			DisplayString(0, 16, "Go Left!");
			OutputSetSpeed (0,MAX_SPEED_FW);
			OutputSetSpeed (1,MAX_SPEED_RW);

		}
		else{
			DisplayString(0, 16, "Motors Stopped!");
		}
	}
	else if( front_light_sensor == LIGHT_WHITE && right_light_sensor == LIGHT_WHITE){
		if( motor_state == 1 ){
			PITInterruptDisable();
			DisplayString(0, 16, "Go Right!");
			OutputSetSpeed (0,0);
			OutputSetSpeed (1,MAX_SPEED_FW);
		}
		else{
			DisplayString(0, 16, "Motors Stopped!");
		}
	}

	touch_sensor = InputGetSensorValue(2);
	 if(touch_sensor == TOUCH_PRESSED){
		 if(motor_state == 0){
			 DisplayString(0,0, "PRESSED");
			 PITInterruptDisable();
			 DisplayString(0, 24, "Motors Starting");
			 LedSwitchOn(0);
			 LedSwitchOn(1);
			 motor_state = 1;
		 }
		 else{
			 DisplayString(0,0, "RE-PRESSED");
			 PITInterruptDisable();
			 DisplayString(0, 24, "Motors Stooping");
			 LedSwitchOff(0);
			 LedSwitchOff(1);
			 OutputSetSpeed (0,0);
			 OutputSetSpeed (1,0);
			 OutputSetSpeed (2,0);
			 motor_state = 0;
		 }
	 }
	 else{
			 DisplayString(0,0, "NOT PRESSED");
	 }

	button = ButtonRead();
	if( button == BUTTON_EXIT ){
		PITInterruptDisable();
		OutputSetSpeed (0,0);
		OutputSetSpeed (1,0);
		OutputSetSpeed (2,0);
		motor_state = 0;
		DisplayErase();
		DisplayString(40, 50, "Goodbye!!!");
		DisplayUpdateSync();
		I2CCtrl(REPROGRAM);
	}
	else if( button == BUTTON_ENTER){
		if(motor_state == 0){
			DisplayString(40, 50, "Welcome!!!");
		}
		else{
			DisplayString(40, 50, "Hello!!!");
		}
	}
	else if ( button == BUTTON_LEFT || button == BUTTON_RIGHT ){
		PITInterruptDisable();
		OutputSetSpeed (0,0);
		OutputSetSpeed (1,0);
		OutputSetSpeed (2,0);
		motor_state = 0;
		DisplayErase();
		DisplayString(40, 50, "Goodbye!!!");
		DisplayUpdateSync();
		I2CCtrl(POWERDOWN);
	}

	DisplayUpdateSync();
}

int main(void) {
	LedSwitchOn(0);
	LedSwitchOn(1);
	HardwareInit(); // need this to init PIOA clock
	DisplayInit();
	SchedulerInit();
	AICInit();
	PITEnable();
	I2CInit();
	InputInit();
	ButtonInit();
	OutputInit();
	//tasks
 	Event_T *e1 = SchedulerAllocateEvent(I2CTransfer,TRUE);
	Event_T *e2 = SchedulerAllocateEvent(sensors,TRUE);
 	enqueue(e1);
	enqueue(e2);

	while(1)
	{
		Scheduler();
	}

	ButtonExit();
	InputExit();
	I2CExit();
	SchedulerExit();
	DisplayExit();

	return 0;
}
