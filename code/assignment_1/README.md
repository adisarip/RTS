
Real Time Systems (Assigment-1):
================================

**Q1:** Write a piece of code for 3 tasks t1, t2, t3 in FreeRTOS with approximate execution times 𝑒1, 𝑒2, 𝑒3 (in msec) respectively as shown in the figure below. Schedule the tasks using the FIFO scheduling mechanism considering the following arrival times. Please show a screenshot of the task execution start times and end times as the result. **Additionally, you can record how many tasks violate the deadline.**

<h3>Q1 Execution Run:</h3>
```
FreeRTOSPosix$ ./FreeRTOSPosix

Task 1: release_time(4.00) | execution_time(7.00) | deadline(13.00) | priority(2)
Task 2: release_time(9.00) | execution_time(2.00) | deadline(14.00) | priority(1)
Task 3: release_time(3.00) | execution_time(2.50) | deadline(20.00) | priority(3)

Running the tasks in 'FIFO' execution model ...

Running as PID: 93274
Timer Resolution for Run TimeStats is 100 ticks per second.
Task 3 : priority(3) : released at -> 3.00 | Execution started at -> 3.00
Task 3 : 5.50
Task 1 : priority(2) : released at -> 4.00 | Execution started at -> 5.50
Task 1 : 12.50
Task 2 : priority(1) : released at -> 9.00 | Execution started at -> 12.50
Task 2 : 14.50
Task 2 : DEADLINE VIOLATION !!!
^Z
zsh: suspended  ./FreeRTOSPosix
FreeRTOSPosix$
FreeRTOSPosix$
```

==================================================================

**Q2:** For a task system {T1, T2, T3, T4}, with parameters (8,3), (15,8), (20,4) and (22,10) (Every value in msec and approximate the execution times to as close as what is required), find the minimum average response time possible with release times r1=0, r2=0, r3=0 and r4=0. Write the code for the tasks and please show the screenshot of the executions and also the response times of each task.

<h3>Q2 Execution Run:</h3>
```
FreeRTOSPosix$ ./FreeRTOSPosix

Task 1: release_time(0) | period( 8) | execution_time( 3) | priority(4)
Task 2: release_time(0) | period(15) | execution_time( 8) | priority(2)
Task 3: release_time(0) | period(20) | execution_time( 4) | priority(3)
Task 4: release_time(0) | period(22) | execution_time(10) | priority(1)

Running the tasks in 'Shortest Job First' execution model ...

Running as PID: 93718
Timer Resolution for Run TimeStats is 100 ticks per second.
Task 1 : priority(4) : released at -> 0 | Execution started at -> 0
Task 1 : Response Time : 3
Task 3 : priority(3) : released at -> 0 | Execution started at -> 3
Task 3 : Response Time : 7
Task 2 : priority(2) : released at -> 0 | Execution started at -> 7
Task 2 : Response Time : 15
Task 4 : priority(1) : released at -> 0 | Execution started at -> 15
Task 4 : Response Time : 25
Task 4 : DEADLINE VIOLATION !!!
^Z
zsh: suspended  ./FreeRTOSPosix
FreeRTOSPosix$
FreeRTOSPosix$
```

Based on the above response time results, Average response time of the Task-set can be computed as follows:

```
Minimum Average Response Time
    = (Sum Of Response Time of all tasks) / (Number of Tasks)
    = (3 + 7 + 15 + 25) / 4
    = 50 / 4
    = 12.5
```

**Minimum Average Response Time = 12.5**
