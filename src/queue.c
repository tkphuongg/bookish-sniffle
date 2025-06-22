#include "../lib/queue.h"

int queue_add(void *new_object, queue_object *queue)
{
	// TODO
	if(queue == NULL)
	{
		return 1;
	}
	
	queue_object* new = malloc(sizeof(queue_object));
	if(new == NULL)
	{
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
	if(queue->next == NULL || queue == NULL)
	{
		return NULL;
	}

	queue_object* second_last_item = queue;
	queue_object* last_item = queue->next;

	while(last_item->next != NULL)
	{
		second_last_item = second_last_item->next;
		last_item = last_item->next;
	}

	void* obj =  last_item->object;
	free(last_item);
	second_last_item->next = NULL;
	return obj;
}

queue_object *new_queue()
{
	// TODO
	queue_object* queue = malloc(sizeof(queue_object));
	if(queue == NULL) return NULL;
	queue->object = NULL;
	queue->next = NULL;
	return queue;
}

void free_queue(queue_object *queue)
{
	// TODO
	if(queue == NULL){
		return;
	}
	queue_object* item_to_free = queue;
	while (item_to_free->next != NULL)
	{
		queue = queue->next;
		free(item_to_free);
		item_to_free = queue;
	}
	free(item_to_free);
}

void *queue_peek(queue_object *queue)
{
	// TODO
	if(queue == NULL){
		return NULL;
	}
	queue_object* tail = queue;
	while (tail->next != NULL)
	{
		tail = tail->next;
	}
	return tail->object;
}

void *queue_poll_tail(queue_object *queue) 
{
	// TODO
	if(queue == NULL || queue->next == NULL){
		return NULL;
	}
	void* obj = queue->next->object;
	if(queue->next->next == NULL)
	{
		free(queue->next);
		queue->next = NULL;
	}
	else
	{
		queue_object* second_item = queue->next->next;
		free(queue->next);
		queue->next = second_item;
	}
	return obj;
}