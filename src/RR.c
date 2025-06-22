#include "../lib/RR.h"
#include <stdio.h>

static queue_object *RR_queue;
static int quant;
static int used_quantum = 0;
//You can add more global variables

process *RR_tick(process *running_process)
{
	// TODO
	// If no running or waiting process
	if(running_process == NULL && queue_peek(RR_queue) == NULL){
		return NULL;
	}
	// If no running process or running process is done
	if(running_process == NULL || running_process->time_left == 0){
		running_process =  queue_poll(RR_queue);
		used_quantum = 1;
		printf("No running process, polled %c from queue.\n", running_process->id);
	}
	// Check if running process has used up quantum
	else if(used_quantum == quant){
		queue_add(running_process, RR_queue);
		running_process = queue_poll(RR_queue);
		used_quantum = 1;
		printf("Previous finished quantum, polled %c from queue.\n", running_process->id);
	}
	else{
		used_quantum++;
	}
	printf("Quantum: %i\n", quant);
	printf("Used quantum of %c: %i\n", running_process->id, used_quantum);
	running_process->time_left--;
    return running_process;
}

int RR_startup(int quantum)
{
	// TODO
	RR_queue = new_queue();
	if (RR_queue == NULL) {
		return 1;
	}
	quant = quantum;
	used_quantum = 0;
	return 0;
}

process *RR_new_arrival(process *arriving_process, process *running_process)
{
	// TODO
	if(arriving_process == NULL && running_process == NULL) return NULL;
    if(running_process == NULL) return arriving_process;
    if(arriving_process == NULL) return running_process;

	printf("Process %c arrived, process %c running. %c added to queue.", 
		arriving_process->id, running_process->id, arriving_process->id);

    queue_add(arriving_process, RR_queue);
    return running_process;
}

void RR_finish()
{
	// TODO
	free(RR_queue);
}
