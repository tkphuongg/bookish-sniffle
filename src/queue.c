#include "../lib/queue.h"

int queue_add(void *new_object, queue_object *queue)
{
	// TODO
	if(queue == NULL){
		return 1;
	}
	queue_object* new = malloc(sizeof(queue_object));
	if(new == NULL){
		return 1;
	}
	new->object = new_object;
	new->next = queue->next;
	queue->next = new;
	return 0;
}

void *queue_poll(queue_object *queue)
{
	// TODO
	
}

queue_object *new_queue()
{
	// TODO
}

void free_queue(queue_object *queue)
{
	// TODO
}

void *queue_peek(queue_object *queue)
{
	// TODO
}

void *queue_poll_tail(queue_object *queue) 
{
	// TODO
}