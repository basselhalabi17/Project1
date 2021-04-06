#include  <stdio.h>
#include <stdlib.h>
#include <stdint.h>

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

void  insertintodelay(fptr f, int delay, int prio){
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
    printf("Tick Finished");
}
void ReRunMe(int delay){
    if (delay==0) {
        QueTask(ready_queue.tasks[0].pointer_to_func, ready_queue.tasks[0].priority);
        //ready_queue.CURRENTSIZE--;
    }
    else {
        insertintodelay(ready_queue.tasks[0].pointer_to_func, delay, ready_queue.tasks[0].priority);
    }
}

void print(struct taskQueue *q, int size){
    printf("\nbassel alby ");
    ReRunMe(0);  
}
void print2(struct taskQueue *q, int size){
    printf("\nchris alby");
    ReRunMe(5);
}
void Nothing(){
    //printf("bassel alby ");  
}
 void init(int size)
{
    printf("fgdgfd ");
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

void dispatch(){
    if (ready_queue.CURRENTSIZE > 0){
        printf("Enter dispatch");
    ready_queue.tasks[0].pointer_to_func();  
   for (int i=0;i<ready_queue.CURRENTSIZE;i++){
       ready_queue.tasks[i] = ready_queue.tasks[i+1];

   } 
   ready_queue.CURRENTSIZE--;
   ready_queue.tasks[ready_queue.CURRENTSIZE].priority = -1;
   ready_queue.tasks[ready_queue.CURRENTSIZE].delay=0;
   ready_queue.tasks[ready_queue.CURRENTSIZE].pointer_to_func = &Nothing;
   for (int j=0;j<delay_queue.CURRENTSIZE;j++){
       delay_queue.tasks[j].delay--;
       if (delay_queue.tasks[j].delay == 0) 
       {
            QueTask(delay_queue.tasks[j].pointer_to_func,delay_queue.tasks[j].priority);
            for (int i=0;i<delay_queue.CURRENTSIZE;i++)
                delay_queue.tasks[i] = delay_queue.tasks[i+1];        
            delay_queue.CURRENTSIZE--;
            delay_queue.tasks[delay_queue.CURRENTSIZE].priority = -1;
            delay_queue.tasks[delay_queue.CURRENTSIZE].delay=99999;
            delay_queue.tasks[delay_queue.CURRENTSIZE].pointer_to_func = &Nothing;
       }

   }
    delayMs(50);
    }
   else 
    printf("Ready Queue empty");
    
}

int main(){
  struct task newtask;
  //task1 newtask;
  /*newtask.priority = 1;
  newtask.pointer_to_func= &print;
  newtask.delay =50;
  newtask.pointer_to_func();*/

  //struct taskQueue *ready_queue;
  printf("dsfdsfds");
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


