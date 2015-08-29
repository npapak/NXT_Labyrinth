#ifndef _QUEUE_H_
#define _QUEUE_H_

typedef enum Boolean_T{ false , true } Boolean_T;
typedef unsigned long Time_T;

typedef struct Event_T{
	void (*task)(void *);
	Time_T last_time;
	Boolean_T disable;
	Boolean_T periodic;
	struct Event_T *next;
	struct Event_T *previous;
} Event_T;

struct event_queue_head{
	ULONG nodes;
	Event_T *head;
}head;

struct event_queue_tail{
	ULONG nodes;
	Event_T *tail;
}tail;

void init_queue();

void enqueue(Event_T *e);

Event_T* dequeue();

Boolean_T isEmpty();

ULONG get_lenght();

#endif
