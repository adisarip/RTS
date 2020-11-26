
# Real Time Systems (Assignment-2):

### Q1
> Create the two tasks in FreeRTOS. The first task should occupy the processor for a long time – you can create a task with a very long delay in the task code. Generally, this can be considered as a computation task (such as a large matrix multiplication task) on an embedded system, which occupies the processor for most of the time. There is another task which is a communication task, which needs to send data every time a certain number of computations/time duration elapses (say 100 computations). Implement triggering of communication task from the computation task *(Hint: Use Notifications).*


#### Solution Approach

- Enable notifications by setting 'configUSE_TASK_NOTIFICATIONS' to 1 in FreeRTOSConfig.h
- Create two static tasks (T1 & T2) with IDLE priorities
- T1 will be the computation task which has a long computation workload
- T2 is a communication task which has a smaller work load.
- Both the task will be started in the scheduler
- After a fixed number of computational units of T1, T1 will notify T2 to execute and will wait for a notification from T2.
- T2 will be waiting for the notification from T1. Once received, it will execute and notify back to T1 after completion and wait.
- T1 will again execute for another fixed number of computational units and notify T2 and wait.
- T2 will again execute once it receives the notification from T1 and after completion notify back and wait.  
... and so on ...  
- Once T1 reaches it total computational units the execution halts


#### Compilation Run
```
FreeRTOSPosix$ make clean; make
--------------
CLEAN COMPLETE
--------------
>> Compiling croutine.c
>> Compiling event_groups.c
>> Compiling list.c
>> Compiling queue.c
>> Compiling tasks.c
>> Compiling timers.c
>> Compiling heap_3.c
>> Compiling port.c
>> Compiling main.c
>> Linking FreeRTOSPosix...
-------------------------
BUILD COMPLETE: FreeRTOSPosix
-------------------------
FreeRTOSPosix$
```


#### Execution Run
```
FreeRTOSPosix$ ./FreeRTOSPosix

Workflow Summary:
-----------------
- Computation   Task: 5000 Units
- Communication Task:  200 Units
- For every 1000 units of Computation work Communication task is executed
-----------------
Running as PID: 79062
Timer Resolution for Run TimeStats is 100 ticks per second.
[COMPUTATION]   Completed = 1000 : Remaining = 4000
[COMMUNICATION] Sending Data ...
[COMMUNICATION] Data Sent !!!
[COMPUTATION]   Completed = 2000 : Remaining = 3000
[COMMUNICATION] Sending Data ...
[COMMUNICATION] Data Sent !!!
[COMPUTATION]   Completed = 3000 : Remaining = 2000
[COMMUNICATION] Sending Data ...
[COMMUNICATION] Data Sent !!!
[COMPUTATION]   Completed = 4000 : Remaining = 1000
[COMMUNICATION] Sending Data ...
[COMMUNICATION] Data Sent !!!
[COMPUTATION]   Completed = 5000 : Remaining = 0
[COMMUNICATION] Sending Data ...
[COMMUNICATION] Data Sent !!!
[COMPUTATION]   All Computations completed !!!
^C
FreeRTOSPosix$
```


### Q2
>There are 3 tasks with priorities and execution times as shown in the figure below. Please implement the **priority inheritance** protocol. *(Hint: Use Notifications and Priority Changes).*


<p align="center">
  <img src="./images/a2q2.png" />
</p>

#### Solution Approach

- The Taskset contains of 3 Tasks {Task1, Task2, Task 3}.
- The priorities of the tasks are P1 > P2 > P3 {P1=3, P2=2, P3=1}.
- The release times of the Tasks are {T1=2, T2=5, T3=0}.
- Task 1 and Task 3 are having critical sections of [R;2] & [R;5] respectively.
- The priority of a task that holds a mutex (Task 3) will be raised if another task of higher priority (Task 1) attempts to obtain the same mutex. The task that already holds the mutex is said to ‘inherit’ the priority of the task that is attempting to ‘take’ the same mutex. The inherited priority will be ‘disinherited’ when the mutex is returned (the task that inherited a higher priority while it held a mutex will return to its original priority when the mutex is returned).
 - In the current implementation I have used Semaphore Mutex locks to acquire the shared resource.
 - Also the log messages are meticulously designed to display the whole scheduling flow with Priority Inheritance.
 - At t=3 one can clearly see the Inheritance of priority by the Task 3 (P3=1 -> P3=3).
 - At t=7 again the priority of Task 3 changes back to 1 (P3=3 -> P3=1).


#### Compilation Run
 ```
 FreeRTOSPosix$ make clean; make
 --------------
 CLEAN COMPLETE
 --------------
 >> Compiling croutine.c
 >> Compiling event_groups.c
 >> Compiling list.c
 >> Compiling queue.c
 >> Compiling tasks.c
 >> Compiling timers.c
 >> Compiling heap_3.c
 >> Compiling port.c
 >> Compiling main.c
 >> Linking FreeRTOSPosix...
 -------------------------
 BUILD COMPLETE: FreeRTOSPosix
 -------------------------
 FreeRTOSPosix$
 ```


#### Execution Run
 ```
 FreeRTOSPosix$ ./FreeRTOSPosix

 Priority Inheritance Protocol Using "Semaphore Mutex" in FreeRTOS:
 ------------------------------------------------------------------
 Running as PID: 11059
 Timer Resolution for Run TimeStats is 100 ticks per second.
 [Task 3] : [t=00] : [P1=3 P2=2 P3=1] Release Time (0)
 [Task 3] : [t=01] : [P1=3 P2=2 P3=1]
 [Task 3] : [t=01] : Resource Requested
 [Task 3] : [t=01] : Resource acquired : Set Resource Value in Task 3 : 1003
 [Task 1] : [t=02] : [P1=3 P2=2 P3=1] Release Time (2)
 [Task 1] : [t=03] : [P1=3 P2=2 P3=1]
 [Task 1] : [t=03] : Resource Requested
 [Task 3] : [t=03] : [P1=3 P2=2 P3=3]
 [Task 3] : [t=04] : [P1=3 P2=2 P3=3]
 [Task 3] : [t=05] : [P1=3 P2=2 P3=3]
 [Task 3] : [t=06] : [P1=3 P2=2 P3=3]
 [Task 3] : [t=07] : [P1=3 P2=2 P3=3]
 [Task 3] : [t=07] : Resource 1003 released
 [Task 1] : [t=07] : Resource acquired : Set Resource Value in Task 1 : 1001
 [Task 1] : [t=07] : [P1=3 P2=2 P3=1]
 [Task 1] : [t=08] : [P1=3 P2=2 P3=1]
 [Task 1] : [t=09] : [P1=3 P2=2 P3=1]
 [Task 1] : [t=09] : Resource 1001 released
 [Task 1] : [t=10] : [P1=3 P2=2 P3=1]
 [Task 1] : [t=10] : Execution ended.
 [Task 2] : [t=10] : [P1=3 P2=2 P3=1] Release Time (5)
 [Task 2] : [t=11] : [P1=3 P2=2 P3=1]
 [Task 2] : [t=12] : [P1=3 P2=2 P3=1]
 [Task 2] : [t=13] : [P1=3 P2=2 P3=1]
 [Task 2] : [t=14] : [P1=3 P2=2 P3=1]
 [Task 2] : [t=15] : [P1=3 P2=2 P3=1]
 [Task 2] : [t=15] : Execution ended.
 [Task 3] : [t=15] : [P1=3 P2=2 P3=1]
 [Task 3] : [t=16] : [P1=3 P2=2 P3=1]
 [Task 3] : [t=16] : Execution ended.
 ^C
 FreeRTOSPosix$

 ```
