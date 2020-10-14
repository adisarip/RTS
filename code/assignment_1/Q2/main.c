
/* Standard includes. */
#include <stdio.h>
#include <stdlib.h>
#include "FreeRTOS.h"		/* RTOS firmware */
#include "task.h"			/* Task */
#include "timers.h"

/* Assignment-1: Q2 */
void vTask1(void*); // t1 -> (8, 3)   priority = 4
void vTask2(void*); // t2 -> (15, 8)  priority = 2
void vTask3(void*); // t3 -> (20, 4)  priority = 3
void vTask4(void*); // t4 -> (22, 10) priority = 1

int main ( void )
{
	xTaskCreate(vTask1, "Task 1", 1024, NULL, 4, NULL);
	xTaskCreate(vTask2, "Task 2", 1024, NULL, 2, NULL);
	xTaskCreate(vTask3, "Task 3", 1024, NULL, 3, NULL);
	xTaskCreate(vTask4, "Task 4", 1024, NULL, 1, NULL);
	printf("\nTask 1: release_time(%d) | period(%2d) | execution_time(%2d)\n",
		   pdMS_TO_TICKS(0), pdMS_TO_TICKS(8), pdMS_TO_TICKS(3));
	printf("Task 2: release_time(%d) | period(%2d) | execution_time(%2d)\n",
		   pdMS_TO_TICKS(0), pdMS_TO_TICKS(15), pdMS_TO_TICKS(8));
	printf("Task 3: release_time(%d) | period(%2d) | execution_time(%2d)\n",
		   pdMS_TO_TICKS(0), pdMS_TO_TICKS(20), pdMS_TO_TICKS(4));
	printf("Task 4: release_time(%d) | period(%2d) | execution_time(%2d)\n",
		   pdMS_TO_TICKS(0), pdMS_TO_TICKS(22), pdMS_TO_TICKS(10));
	printf("\nRunning the tasks in 'Shortest Job First' execution model ...\n\n");
	vTaskStartScheduler();
	printf("\n Before Return ... \n");
	return 0;
}

void vTask1(void* parameter)
{
	parameter = NULL;
	TickType_t period = pdMS_TO_TICKS(8);
	TickType_t execution_time = pdMS_TO_TICKS(3);
	TickType_t current_tick_count = xTaskGetTickCount();
	printf("Task 1 : released at r1 = 0 | Execution started at -> %d\n", current_tick_count);
    while (1)
	{
		TickType_t tick_count = xTaskGetTickCount();
		if (tick_count >= current_tick_count + execution_time)
		{
			printf("Task 1 : Response Time : %d\n", tick_count);
			if (tick_count > period)
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
	TickType_t period = pdMS_TO_TICKS(15);
	TickType_t execution_time = pdMS_TO_TICKS(8);
	TickType_t current_tick_count = xTaskGetTickCount();
	printf("Task 2 : released at r1 = 0 | Execution started at -> %d\n", current_tick_count);
    while (1)
	{
		TickType_t tick_count = xTaskGetTickCount();
		if (tick_count >= current_tick_count + execution_time)
		{
			printf("Task 2 : Response Time : %d\n", tick_count);
			if (tick_count > period)
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
	TickType_t period = pdMS_TO_TICKS(20);
	TickType_t execution_time = pdMS_TO_TICKS(4);
	TickType_t current_tick_count = xTaskGetTickCount();
	printf("Task 3 : released at r1 = 0 | Execution started at -> %d\n", current_tick_count);
    while (1)
	{
		TickType_t tick_count = xTaskGetTickCount();
		if (tick_count >= current_tick_count + execution_time)
		{
			printf("Task 3 : Response Time : %d\n", tick_count);
			if (tick_count > period)
			{
				printf("Task 3 : DEADLINE VIOLATION !!!\n");
			}
			break;
		}
	}
	vTaskDelete(NULL);
}

void vTask4(void* parameter)
{
	parameter = NULL;
	TickType_t period = pdMS_TO_TICKS(22);
	TickType_t execution_time = pdMS_TO_TICKS(10);
	TickType_t current_tick_count = xTaskGetTickCount();
	printf("Task 4 : released at r1 = 0 | Execution started at -> %d\n", current_tick_count);
    while (1)
	{
		TickType_t tick_count = xTaskGetTickCount();
		if (tick_count >= current_tick_count + execution_time)
		{
			printf("Task 4 : Response Time : %d\n", tick_count);
			if (tick_count > period)
			{
				printf("Task 4 : DEADLINE VIOLATION !!!\n");
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
