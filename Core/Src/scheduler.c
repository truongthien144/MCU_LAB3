/*
 * scheduler.c
 *
 *  Created on: Nov 29, 2024
 *      Author: TruongThien
 */
#include "scheduler.h"

sTasks SCH_tasks_G[SCH_MAX_TASKS];

uint8_t tasks_queue_size = 0;

void SCH_Init(void){
	tasks_queue_size = 0;
	for (int i = 0; i < SCH_MAX_TASKS; i++) {
		SCH_tasks_G[i].pTask = 0x0000;
		SCH_tasks_G[i].Delay = 0;
		SCH_tasks_G[i].Period = 0;
		SCH_tasks_G[i].RunMe = 0;
	}
}

uint32_t SCH_Add_Task(
		void (*pFunction)(),
		uint32_t DELAY,
		uint32_t PERIOD
		){
	if(tasks_queue_size < SCH_MAX_TASKS){
		SCH_tasks_G[tasks_queue_size].pTask = pFunction;
		SCH_tasks_G[tasks_queue_size].Delay = DELAY;
		SCH_tasks_G[tasks_queue_size].Period = PERIOD;
		SCH_tasks_G[tasks_queue_size].RunMe = 0;

		return tasks_queue_size++;
	}

	return SCH_MAX_TASKS;;
}

void SCH_Update(void){
	for(int i = 0; i < tasks_queue_size; i++){
		if(SCH_tasks_G[i].Delay > 0){
			SCH_tasks_G[i].Delay--;
		}else{
			/* Period - 1 -> 0 count Period times */
			SCH_tasks_G[i].Delay = SCH_tasks_G[i].Period - 1;
			SCH_tasks_G[i].RunMe++;
		}
	}
}

void SCH_Dispatch_Tasks(void){
	for(int i = 0; i < tasks_queue_size; i++){
		if(SCH_tasks_G[i].RunMe > 0){
			SCH_tasks_G[i].RunMe--;
			(*SCH_tasks_G[i].pTask)();
			// For One shot task
			if(SCH_tasks_G[i].Period == 0 ){
				SCH_Delete_Task(i);
				i--;
			}
		}
	}
}

uint8_t SCH_Delete_Task(uint32_t taskID){
	if (taskID >= tasks_queue_size) return 0; // Invalid index
	for (int i = taskID + 1; i < tasks_queue_size; i++) {
		SCH_tasks_G[i - 1] = SCH_tasks_G[i];
	}
	tasks_queue_size--;
	return 1;
}

