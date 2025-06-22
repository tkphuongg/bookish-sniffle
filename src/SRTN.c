#include "../lib/SRTN.h"

static queue_object *SRTN_queue;
//You can add more global variables here

process *SRTN_tick(process *running_process)
{
	// TODO
	if (running_process == NULL || running_process->time_left == 0) 
	{
		running_process = queue_poll(SRTN_queue);
	}
	if (running_process->time_left < ((process*) queue_peek(SRTN_queue))->time_left)
	{
		return queue_peek(SRTN_queue);
	}
	else
	{
		running_process->time_left--;
		return running_process;
	}
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

	queue_object* waiting_process = SRTN_queue;
	if(arriving_process->time_left < running_process->time_left)
	{
		if(SRTN_queue->next == NULL)
		{
        queue_add(running_process, SRTN_queue);
        return arriving_process;
    	}

		while(running_process->time_left < ((process*) waiting_process->next->object)->time_left)
		{
			waiting_process = waiting_process->next;
		}
		queue_add(running_process, waiting_process);
		return arriving_process;
	}

	if(SRTN_queue->next == NULL)
	{
        queue_add(arriving_process, SRTN_queue);
        return running_process;
    }
    while(arriving_process->time_left < ((process*) waiting_process->next->object)->time_left)
	{
        waiting_process = waiting_process->next;
	}
	queue_add(arriving_process, waiting_process);
	return running_process;
}

void SRTN_finish()
{
	// TODO
	free(SRTN_queue);
}
