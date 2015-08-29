/**
 * @file queue.c
 * @brief Implementation of task queue
 * @author Nikos Papakonstantinou <npapak@gmail.com>
 * @version v1.0
 * @date 2015-08-29
 */
#include <stdlib.h>
#include <stdconst.h>
#include "queue.h"

void init_queue(){
	head.nodes = 0;
	head.head = NULL;
	tail.nodes = 0;
	tail.tail = NULL;
}

void enqueue(Event_T *e){

	if(head.head == NULL){
		head.head = e;
	}
	if(tail.tail == NULL){
		tail.tail = e;
	}
	else{
		tail.tail->next = e;
		e->previous = tail.tail;
		tail.tail = e;
	}
	head.nodes++;
	tail.nodes++;

}

Event_T* dequeue(){
	if(head.nodes == 0)
		return NULL;
	head.nodes--;
	tail.nodes--;
	Event_T *tmp = head.head;
	head.head = head.head->next;
	return tmp;
}

Boolean_T isEmpty(){
	return (head.nodes == 0 ? true : false);
}

ULONG get_lenght(){
	return head.nodes;
}
