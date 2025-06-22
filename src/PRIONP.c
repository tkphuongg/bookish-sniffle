#include "../lib/PRIONP.h"

static queue_object* PRIONP_queue;
//You can add more global variables here

int add_PRIONP(process* process_to_add, queue_object* queue)
{
    queue_object* waiting_process = queue;
    while(waiting_process->next != NULL &&
        ((process*) waiting_process->next)->priority < process_to_add->priority)
    {
        waiting_process = waiting_process->next;
    }
    return queue_add(process_to_add, queue);
}

process* PRIONP_tick (process* running_process){
    // TODO
    // If no process running or waiting
    if(running_process == NULL && queue_peek(PRIONP_queue) == NULL){
		return NULL;
	}

    if(running_process == NULL || running_process->time_left == 0){
        running_process =  queue_poll(PRIONP_queue);
    }
    running_process->time_left--;
    return running_process;
}

int PRIONP_startup(){
    // TODO
    PRIONP_queue = new_queue();
    if(PRIONP_queue == NULL){
        return 1;
    }
    return 0;
}

process* PRIONP_new_arrival(process* arriving_process, process* running_process){
    // TODO
    if(arriving_process == NULL && running_process == NULL) return NULL;
    if(arriving_process == NULL) return running_process;
    if(running_process == NULL) return arriving_process;

    add_PRIONP(arriving_process, PRIONP_queue);
    return running_process;
}

void PRIONP_finish(){
    // TODO
    free_queue(PRIONP_queue);
}
