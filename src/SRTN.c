#include "../lib/SRTN.h"

static queue_object *SRTN_queue;
//You can add more global variables here

int add_SRTN(process* process_to_add, queue_object* queue){
	queue_object* waiting_process = SRTN_queue;
	while(waiting_process->next != NULL && 
		((process*) waiting_process->next)->time_left > process_to_add->time_left)
	{
		waiting_process = waiting_process->next;
	}
	return queue_add(process_to_add, waiting_process);
}

process *SRTN_tick(process *running_process)
{
	// TODO
	// If no process running or waiting
	if(running_process == NULL && queue_peek(SRTN_queue) == NULL){
		return NULL;
	}

	if(running_process == NULL || running_process->time_left == 0){
		running_process =  queue_poll(SRTN_queue);
	}
	else if(queue_peek(SRTN_queue) != NULL && 
		running_process->time_left > ((process*) queue_peek(SRTN_queue))->time_left)
		{
			add_SRTN(running_process, SRTN_queue);
			running_process =  queue_poll(SRTN_queue);
		}
	running_process->time_left--;
	return running_process;
}

int SRTN_startup()
{
	// TODO
	SRTN_queue = new_queue();
	if (SRTN_queue == NULL) {
		return 1;
	}
	return 0;
}

process *SRTN_new_arrival(process *arriving_process, process *running_process)
{
	// TODO
	if(arriving_process == NULL && running_process == NULL) return NULL;
    if(running_process == NULL) return arriving_process;
    if(arriving_process == NULL) return running_process;

	if(arriving_process->time_left >= running_process->time_left)
	{
		add_SRTN(arriving_process, SRTN_queue);
		return running_process;
	}
	else
	{
		add_SRTN(running_process, SRTN_queue);
		return arriving_process;
	}
}

void SRTN_finish()
{
	// TODO
	free(SRTN_queue);
}
