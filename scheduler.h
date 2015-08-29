#ifndef _SCHEDULER_H_
#define _SCHEDULER_H_
#include "queue.h"

void SchedulerInit();
void Scheduler(void);
Event_T* SchedulerAllocateEvent(void (*f)(void *), Boolean_T);
void SchedulerFreeEvent(Event_T *);
void SchedulerEnableEvent(Event_T * );
void SchedulerDisableEvent(Event_T * );
void SchedulerRun(Event_T *, void *, Time_T , Time_T , Boolean_T );
void SchedulerReset(void);
void SchedulerExit(void);

#endif
