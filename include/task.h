/*
 * Young
 * task.h: multitask scheduler
 */

#ifndef TASK_H_
#define TASK_H_

typedef struct task_s{
	unsigned int pid;
	unsigned int esp, ebp;
	unsigned int eip;
	struct task_s * next;
} task_struct;

#endif
