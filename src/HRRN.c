#include "../lib/HRRN.h"

static queue_object *HRRN_queue;
static int global_time = 0;
//You can add more global variables and structs here

double calc_return_rate(process* p)
{
	if (p == NULL) return 0;

	double rr = 1.0 + ((double)(global_time - p->start_time) / p->time_left);

	return rr;
}

void* poll_HRR(queue_object* queue)
{
	if(queue->next == NULL){
		return NULL;
	}

	queue_object* compare_object = queue;
	queue_object* HRR_prev = queue;
	queue_object* HRR = queue->next;

	double RR = calc_return_rate(HRR->object);
	while (compare_object->next != NULL)
	{
		if(RR < calc_return_rate(compare_object->next->object))
		{
			RR = calc_return_rate(compare_object->next->object);
			HRR = compare_object->next;
			HRR_prev = compare_object;
		}
		compare_object = compare_object->next;
	}

	HRR_prev->next = HRR->next;
	void* p = HRR->object;
	free(HRR);
	return p;
}

process *HRRN_tick(process *running_process)
{
	// TODO
	global_time++;
	if(running_process == NULL && queue_peek(HRRN_queue) == NULL){
		return NULL;
	}
	if(running_process == NULL || running_process->time_left == 0){
		running_process =  poll_HRR(HRRN_queue);
	}
	running_process->time_left--;
    return running_process;
}

int HRRN_startup()
{
	// TODO
	HRRN_queue = new_queue();
	if (HRRN_queue == NULL) {
		return 1;
	}
	return 0;
}

process *HRRN_new_arrival(process *arriving_process, process *running_process)
{
	// TODO
	if(arriving_process == NULL && running_process == NULL) return NULL;
    if(running_process == NULL) return arriving_process;
    if(arriving_process == NULL) return running_process;

	queue_add(arriving_process, HRRN_queue);

	return running_process;
}

void HRRN_finish()
{
	// TODO
	free(HRRN_queue);
}
