#include "../lib/MLF.h"

static queue_object **MLF_queues;
//You can add more global variables here
static queue_object* q0;
static queue_object* q1;
static queue_object* q2;
static queue_object* q3;

static int quantum_table[4] = {1, 2, 6, 24};
static int quantum;
static int quantum_used;

process* poll_next_process(){
	for(int i = 0; i < 4; i++){
		if(MLF_queues[i]->next == NULL){
			continue;
		}
		if(i == 3)
		{
			process* p = queue_poll_tail(q3);
			if(p != NULL)
			{
				quantum = quantum_table[3];
				quantum_used = 0;
				return p;
			} 
		}
		else
		{
			process* p = queue_poll(MLF_queues[i]);
			if(p != NULL)
			{
				quantum = quantum_table[i];
				quantum_used = 0;
				return p;
			} 
		}
	}
	return NULL;
}

void move_next_level(process* p){
	int level = -1;
	for(int i = 0; i < 4; i++){
		if(quantum_table[i] == quantum){
			level = i;
			break;
		}
	}
	if(level < 3){
		level++;
	}
	queue_add(p, MLF_queues[level]);
}

process *MLF_tick(process *running_process)
{
	// TODO
	if(running_process == NULL || running_process->time_left == 0){
		running_process = poll_next_process();
		if(running_process == NULL) return NULL;	
	}
	
	if(quantum_used == quantum){
		move_next_level(running_process);
		running_process = poll_next_process;
	}

	running_process->time_left--;
	quantum_used++;
    return running_process;
}

int MLF_startup()
{
	// TODO
	MLF_queues = malloc(4 * sizeof(queue_object*));
	q0 = new_queue();
	q1 = new_queue();
	q2 = new_queue();
	q3 = new_queue();

	if(MLF_queues == NULL || q0 == NULL || q1 == NULL || q2 == NULL || q3 == NULL){
		return 1;
	}

	MLF_queues[0] = q0;
	MLF_queues[1] = q1;
	MLF_queues[2] = q2;
	MLF_queues[3] = q3;

    return 0;
}


process *MLF_new_arrival(process *arriving_process, process *running_process)
{
	// TODO
	if(arriving_process == NULL && running_process == NULL) return NULL;
    if(running_process == NULL) return arriving_process;
    if(arriving_process == NULL) return running_process;

	queue_add(arriving_process, MLF_queues[0]);
    return running_process;
}

void MLF_finish()
{
	// TODO
	free(MLF_queues);
	free(q0);
	free(q1);
	free(q2);
	free(q3);

}
