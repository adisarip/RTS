
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
    TickType_t   execution_time;
    TickType_t   deadline;
};

void init(Task* pTask,
          unsigned int _id,
          unsigned int _priority,
          TickType_t _release_time,
          TickType_t _execution_time,
          TickType_t _deadline)
{
    pTask->id = _id;
    pTask->priority = _priority;
    pTask->release_time = _release_time;
    pTask->execution_time = _execution_time;
    pTask->deadline = _deadline;
}

void print_task_data(Task* pTask)
{
    printf("\nTask %u: release_time(%.2f) | execution_time(%.2f) | deadline(%.2f) | priority(%u)",
           pTask->id,
           pTask->release_time/10.0,
           pTask->execution_time/10.0,
           pTask->deadline/10.0,
           pTask->priority);
}

void run_task(void* parameter)
{
    Task* pTask = (Task*) parameter;
    vTaskDelay(pTask->release_time); // Block the task till release time

    TickType_t tick_count;
    TickType_t current_tick_count = xTaskGetTickCount();
    printf("Task %u : priority(%u) : released at -> %.2f | Execution started at -> %.2f\n",
       pTask->id, pTask->priority, pTask->release_time/10.0, current_tick_count/10.0);

    // Start task execution
    while (1)
    {
        tick_count = xTaskGetTickCount();
        if (tick_count >= current_tick_count + pTask->execution_time)
        {
            printf("Task %u : %3.2f\n", pTask->id, tick_count/10.0);
            if (tick_count > pTask->deadline)
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
    Task sTask1, sTask2, sTask3;
    init(&sTask1, 1, 2, pdMS_TO_TICKS(40), pdMS_TO_TICKS(70), pdMS_TO_TICKS(130));
    init(&sTask2, 2, 1, pdMS_TO_TICKS(90), pdMS_TO_TICKS(20), pdMS_TO_TICKS(140));
    init(&sTask3, 3, 3, pdMS_TO_TICKS(30), pdMS_TO_TICKS(25), pdMS_TO_TICKS(200));
    print_task_data(&sTask1);
    print_task_data(&sTask2);
    print_task_data(&sTask3);
    printf("\n\nRunning the tasks in 'FIFO' execution model ...\n\n");

    // Scheduling the tasks
    xTaskCreate(run_task, "Task 1", 1024, (void*) &sTask1, sTask1.priority, NULL);
    xTaskCreate(run_task, "Task 2", 1024, (void*) &sTask2, sTask2.priority, NULL);
    xTaskCreate(run_task, "Task 3", 1024, (void*) &sTask3, sTask3.priority, NULL);
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
