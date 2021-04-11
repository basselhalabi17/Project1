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
T1-> Priority 1 and ReRun(0), T2->Priority 3 and ReRun(1) and T3->Priority 2 and ReRun(2)


![image](https://user-images.githubusercontent.com/45502245/114321546-991a6c00-9b1b-11eb-9744-731f82c9dde9.png)
![image](https://user-images.githubusercontent.com/45502245/114321558-a9cae200-9b1b-11eb-9509-78f921cf6ee6.png)

2nd testcase: 
T1->priority 3 and rerun(2) , T2-> priority 2 and rerun(1), and T3->priority 1 and rerun(0)

![image](https://user-images.githubusercontent.com/45502245/114321580-d41c9f80-9b1b-11eb-9f5b-613f8d2a8060.png)
![image](https://user-images.githubusercontent.com/45502245/114321588-e0a0f800-9b1b-11eb-937e-746fa486164c.png)



3rd testcase: 
T1->priority 1 and rerun(1) , T2->priority 2 and rerun(2) , and T3->priority 3 and rerun(3)

![image](https://user-images.githubusercontent.com/45502245/114321601-f57d8b80-9b1b-11eb-956b-54bc6fd94ea8.png) 
![image](https://user-images.githubusercontent.com/45502245/114321620-0e863c80-9b1c-11eb-9d65-2d82e21d4b10.png)


**Systick Configurations**:
--HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()*0.05); 
--HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
-- HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);

The 0.05 in the first line is what makes the Systick generate interrupt every 50 ms (1 tick).


**1st application (Temperature sensor)**: In order to implement this application, we had 3 tasks. The first task is ReadTemperature() which reads the current temperature from the sensor every 30 seconds and this is given the highest priority. This function is given a ReRunMe(600) since every tick is 50 ms so we need 600 ticks to read every 30 seconds. The second task is CheckThreshold() and this compares the measured temperature with a certain threshold provided over the UART and this is given the second highest priority. If the temperature exceeds the threshold, it sets a flag to true. This function also is given a ReRunMe(600) since every tick is 50 ms so we need 600 ticks to check the threshold every 30 seconds. The third task is ToggleLed() and this is the lowest priority. This checks if the flag is true, then a LED is toggled. This is given a ReRunMe(1) as we need the toggling to keep happening every tick or stay turned off if the flag is false.

CubeMX Configurations for 1st application
SYS: Debug -> Serial Wire
RCC: LSE-> Crystal/Ceramic Resonator
UART-> UART1 enabled and set to Asynchronous
I2C-> enabled (set to I2C)
NVIC-> Preemption priority of UART1 handler set to 7 and enabled.

How to run the application: Generate code using the above configurations. Then in the main.c, put the code provided in the App1_main.c and in the stm32l4xx_it.c, put the code provided in App1_it.c. Connections are made like in the video and open Teraterm and change the baud rate to 115200 and type the threshold and press enter and wait for toggling if the read temperature (also displayed on TeraTerm) is higher than the threshold. 



**2nd application(Parking Sensor)**: In order to implement this function, we used 2 tasks. The first is HSCR04_Read() which reads the current distance of the object from the sensor and compares the distance read to certain thresholds and sets frequencies accordingly. This is given the highest priority. The second task is toggle buzzer() and this toggles the buzzer based on the frequencies set in the first task. 

CubeMX Configurations for 2nd application:
TIM1: Clock Source->Internal clock
	Channel1-> input capture direct mode
NVIC-> enable tim1 global interrupt
Set PB3 as GPIO_Output

How to run the application: Generate code using the above configurations. Then in the main.c, put the code provided in the App2_main.c and in the stm32l4xx_it.c, put the code provided in App2_it.c. Connections are made like in the video and have an object at a distance from the sensor and keep making it close and you will listen to the buzzer buzzing at a higher frequency. 













