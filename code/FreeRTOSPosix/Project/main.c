
/* Standard includes. */
#include <stdio.h>
#include <stdlib.h>
#include "FreeRTOS.h"		/* RTOS firmware */
#include "task.h"			/* Task */
#include "timers.h"

typedef struct TaskData Task;
void init(Task*,unsigned int,unsigned int,TickType_t,TickType_t,TickType_t);
void print_task_data(Task*);
void run_task(void*);

struct TaskData
{
	// Data
	unsigned int id;
	unsigned int priority;
	TickType_t   release_time;
	TickType_t   period;
	TickType_t   execution_time;
};

void init(Task* pTask,
		  unsigned int _id,
		  unsigned int _priority,
		  TickType_t _release_time,
		  TickType_t _period,
		  TickType_t _execution_time)
{
	pTask->id             = _id;
	pTask->priority       = _priority;
	pTask->release_time   = _release_time;
	pTask->period         = _period;
	pTask->execution_time = _execution_time;
}

void print_task_data(Task* pTask)
{
	printf("\nTask %u: release_time(%d) | period(%2d) | execution_time(%2d) | priority(%u)",
		   pTask->id,
		   pTask->release_time,
		   pTask->period,
		   pTask->execution_time,
		   pTask->priority);
}

void run_task(void* parameter)
{
	Task* pTask = (Task*) parameter;
	TickType_t current_tick_count = xTaskGetTickCount();
	printf("Task %u : priority(%u) : released at -> %d | Execution started at -> %d\n",
		   pTask->id, pTask->priority, pTask->release_time, current_tick_count);

	// Start task execution
    while (1)
	{
		TickType_t tick_count = xTaskGetTickCount();
		if (tick_count >= current_tick_count + pTask->execution_time)
		{
			printf("Task %u : Response Time : %d\n", pTask->id, tick_count);
			if (tick_count > pTask->period)
			{
				printf("Task %u : DEADLINE VIOLATION !!!\n", pTask->id);
			}
			break;
		}
	}
	vTaskDelete(NULL);
}

int main ( void )
{
	// Create 4 task objects
	Task sTask1, sTask2, sTask3, sTask4;
	init(&sTask1, 1, 4, pdMS_TO_TICKS(0), pdMS_TO_TICKS(8),  pdMS_TO_TICKS(3));
	init(&sTask2, 2, 2, pdMS_TO_TICKS(0), pdMS_TO_TICKS(15), pdMS_TO_TICKS(8));
	init(&sTask3, 3, 3, pdMS_TO_TICKS(0), pdMS_TO_TICKS(20), pdMS_TO_TICKS(4));
	init(&sTask4, 4, 1, pdMS_TO_TICKS(0), pdMS_TO_TICKS(22), pdMS_TO_TICKS(10));
	print_task_data(&sTask1);
	print_task_data(&sTask2);
	print_task_data(&sTask3);
	print_task_data(&sTask4);
	printf("\n\nRunning the tasks in 'Shortest Job First' execution model ...\n\n");

	// Scheduling the tasks
	xTaskCreate(run_task, "Task 1", 1024, (void*) &sTask1, sTask1.priority, NULL);
	xTaskCreate(run_task, "Task 2", 1024, (void*) &sTask2, sTask2.priority, NULL);
	xTaskCreate(run_task, "Task 3", 1024, (void*) &sTask3, sTask3.priority, NULL);
	xTaskCreate(run_task, "Task 4", 1024, (void*) &sTask4, sTask4.priority, NULL);
	vTaskStartScheduler();

	return 0;
}

/*-----------------------------------------------------------*/

void vAssertCalled( unsigned long ulLine, const char * const pcFileName )
{
 	taskENTER_CRITICAL();
	{
        printf("[ASSERT] %s:%lu\n", pcFileName, ulLine);
        fflush(stdout);
	}
	taskEXIT_CRITICAL();
	exit(-1);
}
