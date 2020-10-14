
/* Standard includes. */
#include <stdio.h>
#include <stdlib.h>
#include "FreeRTOS.h"		/* RTOS firmware */
#include "task.h"			/* Task */
#include "timers.h"

/* Examples */
void vTask1(void*); // t1 -> (9, 7)    priority = 2
void vTask2(void*); // t2 -> (5, 2)    priority = 1
void vTask3(void*); // t3 -> (17, 2.5) priority = 3

int main ( void )
{
	xTaskCreate(vTask1, "Task 1", 1000, NULL, 2, NULL);
	xTaskCreate(vTask2, "Task 2", 1000, NULL, 1, NULL);
	xTaskCreate(vTask3, "Task 3", 1000, NULL, 3, NULL);
	printf("\nTask 1: release_time(%.2f) | period(%.2f)  | execution_time(%.2f) | deadline(%.2f)\n",
		   pdMS_TO_TICKS(40)/10.0, pdMS_TO_TICKS(90)/10.0, pdMS_TO_TICKS(70)/10.0, pdMS_TO_TICKS(130)/10.0);
	printf("Task 2: release_time(%.2f) | period(%.2f)  | execution_time(%.2f) | deadline(%.2f)\n",
		   pdMS_TO_TICKS(90)/10.0, pdMS_TO_TICKS(50)/10.0, pdMS_TO_TICKS(20)/10.0, pdMS_TO_TICKS(140)/10.0);
	printf("Task 3: release_time(%.2f) | period(%.2f) | execution_time(%.2f) | deadline(%.2f)\n",
		   pdMS_TO_TICKS(30)/10.0, pdMS_TO_TICKS(170)/10.0, pdMS_TO_TICKS(25)/10.0, pdMS_TO_TICKS(200)/10.0);
	printf("\nRunning the tasks in 'FIFO' execution model ...\n\n");
	vTaskStartScheduler();
	return 0;
}

void vTask1(void* parameter)
{
	parameter = NULL;
	TickType_t task_start = pdMS_TO_TICKS(40);
	TickType_t execution_time = pdMS_TO_TICKS(70);
	TickType_t deadline = pdMS_TO_TICKS(130);

	TickType_t tick_count;
	vTaskDelay(task_start);
	TickType_t current_tick_count = xTaskGetTickCount();
	printf("Task 1 : released at -> %.2f | Execution started at -> %.2f\n", task_start/10.0, current_tick_count/10.0);
    while (1)
	{
		tick_count = xTaskGetTickCount();
		if (tick_count >= current_tick_count + execution_time)
		{
			printf("Task 1 : %3.2f\n", tick_count/10.0);
			if (tick_count > deadline)
			{
				printf("Task 1 : DEADLINE VIOLATION !!!\n");
			}
			break;
		}
	}
	vTaskDelete(NULL);
}

void vTask2(void* parameter)
{
	parameter = NULL;
	TickType_t task_start = pdMS_TO_TICKS(90);
	TickType_t execution_time = pdMS_TO_TICKS(20);
	TickType_t deadline = pdMS_TO_TICKS(140);

	TickType_t tick_count;
	vTaskDelay(task_start);
	TickType_t current_tick_count = xTaskGetTickCount();
	printf("Task 2 : released at -> %.2f | Execution started at -> %.2f\n", task_start/10.0, current_tick_count/10.0);
	while (1)
	{
		tick_count = xTaskGetTickCount();
		if (tick_count >= current_tick_count + execution_time)
		{
			printf("Task 2 : %3.2f\n", tick_count/10.0);
			if (tick_count > deadline)
			{
				printf("Task 2 : DEADLINE VIOLATION !!!\n");
			}
			break;
		}
	}
	vTaskDelete(NULL);
}

void vTask3(void* parameter)
{
	parameter = NULL;
	TickType_t task_start = pdMS_TO_TICKS(30);
	TickType_t execution_time = pdMS_TO_TICKS(25);
	TickType_t deadline = pdMS_TO_TICKS(200);

	TickType_t tick_count;
	vTaskDelay(task_start);
	TickType_t current_tick_count = xTaskGetTickCount();
	printf("Task 3 : released at -> %.2f | Execution started at -> %.2f\n", task_start/10.0, current_tick_count/10.0);
	while (1)
	{
		tick_count = xTaskGetTickCount();
		if (tick_count >= current_tick_count + execution_time)
		{
			printf("Task 3 : %3.2f\n", tick_count/10.0);
			if (tick_count > deadline)
			{
				printf("Task 3 : DEADLINE VIOLATION !!!\n");
			}
			break;
		}
	}
	vTaskDelete(NULL);
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
