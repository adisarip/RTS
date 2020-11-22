
/* Standard includes. */
#include <stdio.h>
#include <stdlib.h>
#include "FreeRTOS.h"        /* RTOS firmware */
#include "task.h"            /* Task */
#include "timers.h"

#define ll long long
#define COMPUTE_COUNT 1000
#define MAX_COMPUTE_COUNT 5000

// Task Handles
static TaskHandle_t xTask1 = NULL;
static TaskHandle_t xTask2 = NULL;

// function declarations
void delay(int N);
void run_comp_task(void*);
void run_comm_task(void*);


// function definitions

// Performing some arithmentic computations to add some delay
void delay(int N)
{
    ll count = 0;
    for (ll h=1; h <= N; h++)
    {
        for (ll i=1; i <= N; i++)
        {
            for (ll j=1; j <= N; j++)
            {
                for (ll k=1; k <= N; k++)
                {
                    count += k;
                }
                count += j % count;
            }
            count += i % count;
        }
        count += h % count;
    }
}

// The computation task will run for longer duration
// resembling some huge computations.
// In here I will try to implement some long arithemetic computations loop
void run_comp_task(void* task_data)
{
    task_data = NULL;
    int n_count = COMPUTE_COUNT;
    int max_computations = MAX_COMPUTE_COUNT;
    int n_computations = 0;
    // Start task execution
    while (1)
    {
        if (n_computations < max_computations)
        {
            delay(n_count);
            n_computations += n_count;
            printf("[COMPUTATION]   Completed = %d : Remaining = %d\n", n_computations, max_computations - n_computations);
            fflush(stdout);
            xTaskNotifyGive(xTask2);
            ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        }
        else
        {
            printf("[COMPUTATION]   All Computations completed !!!\n");
            fflush(stdout);
            break;
        }
    }
    vTaskDelete(NULL);
}

// Communication Task
void run_comm_task(void* task_data)
{
    task_data = NULL;
    // Start task execution
    while (1)
    {
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        printf("[COMMUNICATION] Sending Data ...\n");
        delay(200); // a smaller delay loop for faster completion
        printf("[COMMUNICATION] Data Sent !!!\n");
        delay(200);
        xTaskNotifyGive(xTask1);
    }
    vTaskDelete(NULL);
}

int main (void)
{
    printf("\n");
    printf("Workflow Summary:\n");
    printf("-----------------\n");
    printf("- Computation   Task: 5000 Units\n");
    printf("- Communication Task:  200 Units\n");
    printf("- For every 1000 units of Computation work Communication task is executed\n");
    printf("-----------------\n");
    xTaskCreate(run_comp_task, "Task 1", 1024, NULL, tskIDLE_PRIORITY, &xTask1);
    xTaskCreate(run_comm_task, "Task 2", 1024, NULL, tskIDLE_PRIORITY, &xTask2);
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
