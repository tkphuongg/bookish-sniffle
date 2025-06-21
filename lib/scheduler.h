#ifndef SCHEDULER_H
#define SCHEDULER_H

#include"process.h"

typedef enum scheduling_strategy {
	PRIONP, HRRN, LCFSPR, SRTN, RR, MLF
} scheduling_strategy;

unsigned int overlapping_time(unsigned int p_id);
unsigned int end_time(unsigned int p_id);

char *scheduler(process processes[], unsigned int processcount,
		scheduling_strategy strategy, int RR_quantum);

#endif
