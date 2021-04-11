Scheduler Implementation 

**Data Structures used**

Task Struct:  this struct has 3 fields: the priority of the task, its delay, and a pointer to the function name.

Queue struct: it has 3 fields: the current size, the maximum size, and a task struct pointer pointing to the array of tasks the queue has.

Typedef fptr: void function pointer.


**Main Functions**

Init(): initializes ready queue and delay queue to some default values. Current size is set to 0 and max size is set to a specified value. Also priorities of tasks are set to -1 and delay is set to a very high value. Also, pointers to the tasks are set to a dummy function that does not do anything.

QueTask(): this function receives 2 arguments: the priority of the task and a pointer to the function that implements the tasks. It then increments the current size of the ready queue by 1 and sorts all the existing tasks in the queue according to their priorities. 

Insertintodelay(): this function receives 3 arguments: pointer to the task, delay and priority. It then increments the current size of the delay queue and sorts the existing tasks in the delay queue according to their delay (the higher the delay, the lower its priority). 

ReRun(): this function takes 1 argument which is the delay. If it is zero, then function is enqueued to the ready queue. If it is non-zero, it calls insertintodelay function.

Dispatch(): this function takes no arguments. It dequeues the first task in the ready queue after checking that the current size is greater than 0. It then checks the delay queue and if its size is not 0, then it proceeds to decrement the delays of all the existing tasks in the delay queue. Afterwards, it checks if the first task in the queue has a delay of 0, and enqueues it in the ready queue if it is.

DelayMs() : simulates 50 ms ticks

**Scheduler unit tests**

1st testcase: 
T1: Priority 1 and ReRun(0)
T2: Priority 3 and ReRun(1)
T3: Priority 2 and ReRun(2)

Expected Output:








