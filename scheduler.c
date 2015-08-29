/**
 * @file scheduler.c
 * @brief Implementation of scheduler
 * @author Nikos Papakonstantinou <npapak@gmail.com>
 * @version v1.0
 * @date 2015-08-29
 */
#include <stdlib.h>
#include <stdconst.h>
#include "scheduler.h"
#include "pit.h"
#include "display.h"

Time_T current_time = 0;

void scheduler_handler(void){
	Event_T *event = dequeue();
	SchedulerRun(event,NULL,2,0,event->periodic);
// 	SchedulerFreeEvent(event);
}

void SchedulerInit(){

// 	AICInit();
// 	PITEnable();
// 	PITInterruptEnable(scheduler_period,scheduler_handler);
	init_queue();
}

Event_T* SchedulerAllocateEvent(void (*f)(void *), Boolean_T periodic){
	Event_T *event = (Event_T *)malloc(sizeof(Event_T));
	event->task = f;
	event->last_time = 0;
	event->disable = false;
	event->periodic = periodic;
	event->previous = NULL;
	event->next = NULL;
	return event;
}

void SchedulerFreeEvent(Event_T* event){
	free(event);
}

void SchedulerEnableEvent(Event_T *e){
	e->disable = false;
	enqueue(e);
}

void SchedulerDisableEvent(Event_T* e){
	e->disable = true;
	SchedulerFreeEvent(e);
}

void SchedulerReset(){
	while(!isEmpty()){
		dequeue();
	}
}

void SchedulerRun(Event_T* e, void *arg, Time_T t, Time_T duration, Boolean_T periodic){
	if(e == NULL)	return;
	if(e->disable == false){
		if( current_time - e->last_time >= t ){
			if( duration == 0){
				PITInterruptDisable();
			}
			else{
				PITInterruptEnable(duration,scheduler_handler);
			}
			(*(e->task))(NULL);
			e->last_time = current_time;
			if(periodic == false){
				SchedulerDisableEvent(e);
			}
			else{
				e->periodic = true;
				enqueue(e);
			}
		}
		else{
			enqueue(e);
		}
	}
	else{
		enqueue(e);
	}

	current_time += PITRead();
	PITReadReset();
}

void Scheduler(void){
// 	current_time = 0;
	PITReadReset();
	Event_T *event = dequeue();
	SchedulerRun(event,NULL,2,0,event->periodic);
// 	SchedulerFreeEvent(event);
}

void SchedulerExit(void){
	PITInterruptDisable();
// 	PITDisable();
}
