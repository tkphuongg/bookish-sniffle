#include "../lib/LCFSPR.h"

static queue_object* LCFSPR_queue;
//You can add more global variables here

process* LCFSPR_tick (process* running_process){
    // TODO
    if(running_process == NULL && queue_peek(LCFSPR_queue) == NULL){
		return NULL;
	}

	if(running_process == NULL || running_process->time_left == 0){
		running_process =  queue_poll(LCFSPR_queue);
	}

    running_process->time_left--;
    return running_process;
}

int LCFSPR_startup(){
    // TODO
    LCFSPR_queue = new_queue();
	if (LCFSPR_queue == NULL) {
		return 1;
	}
	return 0;
}

process* LCFSPR_new_arrival(process* arriving_process, process* running_process){
    // TODO
    if(arriving_process == NULL && running_process == NULL) return NULL;
    if(running_process == NULL) return arriving_process;
    if(arriving_process == NULL) return running_process;

    queue_add(running_process, LCFSPR_queue);
    return arriving_process;
}

void LCFSPR_finish(){
	// TODO
    free(LCFSPR_queue);
}
