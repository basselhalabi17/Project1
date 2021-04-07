#include  <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef void (*fptr)();

struct taskQueue {
	int CURRENTSIZE;
	int MAXSIZE;
	struct task *tasks;
};
static struct taskQueue ready_queue;
static struct taskQueue delay_queue;
 
struct task {
    int priority;
    fptr pointer_to_func;
    int delay;
};
void Nothing(){
     
}

bool taskAlreadyInsertedINDelayQueue=false;
/*void  insertintodelay(fptr f, int delay, int prio){
    delay_queue.tasks[delay_queue.CURRENTSIZE].delay=delay;
    delay_queue.tasks[delay_queue.CURRENTSIZE].priority= prio;
    delay_queue.tasks[delay_queue.CURRENTSIZE].pointer_to_func =f;
    delay_queue.CURRENTSIZE++;


    for (int i=0; i<delay_queue.CURRENTSIZE;i++){
        for (int j=0; j<delay_queue.CURRENTSIZE;j++){
            if (delay_queue.tasks[i].delay < delay_queue.tasks[j].delay && i!=j){

                struct task temp = delay_queue.tasks[i];
	            delay_queue.tasks[i] = delay_queue.tasks[j];
	            delay_queue.tasks[j] = temp;
            }
        }
    }
}
*/

void QueTask(fptr f, int Priority)
{
    ready_queue.tasks[ready_queue.CURRENTSIZE].priority=Priority;
    ready_queue.tasks[ready_queue.CURRENTSIZE].pointer_to_func =f;
    ready_queue.CURRENTSIZE++;

    for (int i=0; i<ready_queue.CURRENTSIZE;i++){
        for (int j=0; j<ready_queue.CURRENTSIZE;j++){
            if (ready_queue.tasks[i].priority > ready_queue.tasks[j].priority && i!=j){

                struct task temp = ready_queue.tasks[i];
	            ready_queue.tasks[i] = ready_queue.tasks[j];
	            ready_queue.tasks[j] = temp;
            }
        }
    }

}
void delayMs(int n){
    int i, j;
    for(i = 0 ; i < n; i++)
     for(j = 0; j < 3180; j++)
        {} // do nothing for 1 ms
    printf(" Tick Finished\n");
}

void ReRunMe(int delay, fptr f, int Priority){
    if (delay==0) { //insert in ready queue
        QueTask(f, Priority);
    }
    else if (delay!=0){ //insert in delay queue
        
        //insertintodelay(ready_queue.tasks[0].pointer_to_func, delay, ready_queue.tasks[0].priority);
        
        //decrement delays of other tasks that were already in the delay queue then insert the new task in the delay queue
        for (int j=0;j<delay_queue.CURRENTSIZE;j++)//loop through delay queue to decrement the delay
                {
                    delay_queue.tasks[j].delay--; //decrement the delay of the task
                    if (delay_queue.tasks[j].delay == 0) //if a delay of any task in the delay queue reached 0
                    {
                        QueTask(delay_queue.tasks[j].pointer_to_func,delay_queue.tasks[j].priority); //add the task to the ready queue                      
                        //remove this task from delay queue
                        for (int i=0;i<delay_queue.CURRENTSIZE;i++) //shift the tasks to move 1 index to the left(approching the head of the queue)
                            delay_queue.tasks[i] = delay_queue.tasks[i+1];        
                        //last task 3la el ymeen initialize b null
                        delay_queue.CURRENTSIZE--;//decrement size of delay queue
                        delay_queue.tasks[delay_queue.CURRENTSIZE].priority = -1;
                        delay_queue.tasks[delay_queue.CURRENTSIZE].delay=99999;
                        delay_queue.tasks[delay_queue.CURRENTSIZE].pointer_to_func = &Nothing;
                        
                    }
            }
        //Add the new task to delay queue
        delay_queue.tasks[delay_queue.CURRENTSIZE].delay=delay;
        delay_queue.tasks[delay_queue.CURRENTSIZE].priority= Priority;
        delay_queue.tasks[delay_queue.CURRENTSIZE].pointer_to_func =f;
        delay_queue.CURRENTSIZE++;

        //sort the delay queue
        for (int i=0; i<delay_queue.CURRENTSIZE;i++){
            for (int j=0; j<delay_queue.CURRENTSIZE;j++){
                if (delay_queue.tasks[i].delay < delay_queue.tasks[j].delay && i!=j){

                    struct task temp = delay_queue.tasks[i];
                    delay_queue.tasks[i] = delay_queue.tasks[j];
                    delay_queue.tasks[j] = temp;
                }
            }
        }
    }
}

void dispatch(){
    
    bool enterReadyQueue=false;
    //bool NoTaskInReadyQueue=false;
    if(delay_queue.CURRENTSIZE>0)
        if(delay_queue.tasks[0].delay==1)
            enterReadyQueue=true;

    if (ready_queue.CURRENTSIZE > 0) {//if at this tick, there is a task that needs to get scheduled
        printf("Enter dispatch and readqqueue!=0 ");
        ready_queue.tasks[0].pointer_to_func(); //call the task to execute  
        //delay_queue.eltaskdi.delay --;

        for (int i=0;i<ready_queue.CURRENTSIZE;i++)
            ready_queue.tasks[i] = ready_queue.tasks[i+1];
        
        ready_queue.CURRENTSIZE--;
        ready_queue.tasks[ready_queue.CURRENTSIZE].priority = -1;
        ready_queue.tasks[ready_queue.CURRENTSIZE].delay=0;
        ready_queue.tasks[ready_queue.CURRENTSIZE].pointer_to_func = &Nothing;      
    }
    else if (ready_queue.CURRENTSIZE == 0 && enterReadyQueue==true) // if we have a task in the delay queue that has a delay of 1
    {
         ready_queue.tasks[0].priority=delay_queue.tasks[0].priority;
         ready_queue.tasks[0].pointer_to_func=delay_queue.tasks[0].pointer_to_func;
         ready_queue.tasks[0].delay=delay_queue.tasks[0].delay;   
         ready_queue.CURRENTSIZE++; 

         ready_queue.tasks[0].pointer_to_func(); //call the task to execute

         ready_queue.CURRENTSIZE--;
         ready_queue.tasks[ready_queue.CURRENTSIZE].priority = -1;
         ready_queue.tasks[ready_queue.CURRENTSIZE].delay=0;
         ready_queue.tasks[ready_queue.CURRENTSIZE].pointer_to_func = &Nothing;  
    }

    else if (ready_queue.CURRENTSIZE==0 && enterReadyQueue==false)//if no tasks in ready queue in this tick now
        {
            printf("No task scheduled lesa");
        }
    
    delayMs(50); //50ms after dispatch
    
}
void print(struct taskQueue *q, int size){
    printf(" bassel alby");
    ReRunMe(1,&print,324);  //should get executed every tick
    
}
void print2(struct taskQueue *q, int size){
    printf(" chris alby");
    ReRunMe(2,&print2,568);// should get exectued every 3 ticks
}

void print3(struct taskQueue *q, int size){
    printf(" task 3 print");
  //  ReRunMe(0);// should get exectued every 3 ticks
}

 void init(int size)
{
    //printf("fgdgfd ");
    ready_queue.CURRENTSIZE=0;
    ready_queue.MAXSIZE=size;
    ready_queue.tasks = (struct task*)malloc(size * sizeof(struct task));

    delay_queue.CURRENTSIZE=0;
    delay_queue.MAXSIZE=size;
    delay_queue.tasks = (struct task*)malloc(size * sizeof(struct task));

    for(int i=0;i< size; i++)
        {
            ready_queue.tasks[i].priority=-1;
            ready_queue.tasks[i].delay=0;
            ready_queue.tasks[i].pointer_to_func = &Nothing;

            delay_queue.tasks[i].priority=-1;
            delay_queue.tasks[i].delay=99999;
            delay_queue.tasks[i].pointer_to_func = &Nothing;
        }  
} 


int main(){
  struct task newtask;
  //task1 newtask;
  /*newtask.priority = 1;
  newtask.pointer_to_func= &print;
  newtask.delay =50;
  newtask.pointer_to_func();*/

  //struct taskQueue *ready_queue;
  //printf("dsfdsfo");
  init(20);
  //ready_queue->tasks[9].pointer_to_func();
  QueTask(&print,324);
  QueTask(&print2,568);
 /*  QueTask(&print2,5677);
  QueTask(&print,45);
  QueTask(&print2,3); */
  
  for (int p=0; p<15;p++){
   dispatch();
  }
  //dispatch();
  //dispatch();
    
  /* printf("%d\n", ready_queue->tasks[0].priority);
   ready_queue->tasks[0].pointer_to_func();*/
  /*printf("%d", ready_queue.tasks[0].priority);
  printf("%d", ready_queue.tasks[1].priority); 
  printf("%d", ready_queue.tasks[2].priority); 
  printf("\n%d", ready_queue.CURRENTSIZE);
 */
  return 0;  
}


