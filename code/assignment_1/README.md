
<h3>Assigment-1</h3>:


**Q1:** Write a piece of code for 3 tasks t1, t2, t3 in FreeRTOS with approximate execution times 𝑒1, 𝑒2, 𝑒3 (in msec) respectively as shown in the figure below. Schedule the tasks using the FIFO scheduling mechanism considering the following arrival times. Please show a screenshot of the task execution start times and end times as the result. **Additionally, you can record how many tasks violate the deadline.**

![Assigment-1-Q1](/Users/adisarip/Mtech/RTS/images/q1.jpeg)

Execution:
==========
FreeRTOSPosix$ ./FreeRTOSPosix
Running as PID: 64941

Task 1: start(4.00) | period(9.00)  | execution_time(7.00) | deadline(13.00)
Task 2: start(9.00) | period(5.00)  | execution_time(2.00) | deadline(14.00)
Task 3: start(3.00) | period(17.00) | execution_time(2.50) | deadline(20.00)

Running the tasks in 'Shortest Job Fist(FIFO)' execution model ...

Timer Resolution for Run TimeStats is 100 ticks per second.
Task 3 : released at -> 3.00 | Execution started at -> 3.00
Task 3 : 5.50
Task 1 : released at -> 4.00 | Execution started at -> 5.50
Task 1 : 12.50
Task 2 : released at -> 9.00 | Execution started at -> 12.50
Task 2 : 14.50
Task 2 : DEADLINE VIOLATION !!!


**Q2:** For a task system {T1, T2, T3, T4}, with parameters (8,3), (15,8), (20,4) and (22,10) (Every value in msec and approximate the execution times to as close as what is required), find the minimum average response time possible with release times r1=0, r2=0, r3=0 and r4=0. Write the code for the tasks and please show the screenshot of the executions and also the response times of each task.
