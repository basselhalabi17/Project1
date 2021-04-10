#include  <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "structsDeclaration.h"
//typedef void (*fptr)();
struct task tasktoberemoved;
/*struct taskQueue {
	int CURRENTSIZE;
	int MAXSIZE;
	struct task *tasks;
};

struct taskQueue ready_queue;
struct taskQueue delay_queue;
 
struct task {
    int priority;
    fptr pointer_to_func;
    int delay;
};
*/
extern struct taskQueue ready_queue;
extern struct taskQueue delay_queue;

bool flag=false;

bool test=true;

void  insertintodelay(fptr f, int delay, int prio){
    delay_queue.tasks[delay_queue.CURRENTSIZE].delay=delay+1;
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
    //dispatch();

}
void delayMs(int n){
    int i, j;
    for(i = 0 ; i < n; i++)
     for(j = 0; j < 3180; j++)
        {} // do nothing for 1 ms
    printf(" Tick Finished \n");
}

void ReRunMe(int delay){
    if (delay==0) {
        QueTask(tasktoberemoved.pointer_to_func, tasktoberemoved.priority);
        //ready_queue.CURRENTSIZE--;
    }
    else {
        insertintodelay(tasktoberemoved.pointer_to_func, delay, tasktoberemoved.priority);
        //insertintodelay(tasktoberemoved.pointer_to_func,tasktoberemoved.delay, tasktoberemoved.priority);
    }
}

/*
void task3(struct taskQueue *q, int size){
    printf(" task3");
    //QueTask(&print,200);
    //ReRunMe(5);
}
*/
void print2(struct taskQueue *q, int size){
    printf(" chris alby");
    //QueTask(&task3,100);
    ReRunMe(2);
}


void print(struct taskQueue *q, int size){
    printf(" bassel alby");
    //QueTask(&print2,500);
    ReRunMe(1);
}






void Nothing(){
    //printf("bassel alby ");  
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
void swap()
{
    struct task temp=ready_queue.tasks[1];
    ready_queue.tasks[1]=ready_queue.tasks[0];
    ready_queue.tasks[0]=temp;
}

void dispatch(){
    
    printf (" ready_queue size is = %d ", ready_queue.CURRENTSIZE);
    printf (" delay_queue size is = %d ", delay_queue.CURRENTSIZE);
    if (ready_queue.CURRENTSIZE > 0){
        printf("Enter dispatch and readqqueue!=0 ");
        
        tasktoberemoved = ready_queue.tasks[0];//fiha bassel fel awel

        for (int i=0;i<ready_queue.CURRENTSIZE;i++)
            ready_queue.tasks[i] = ready_queue.tasks[i+1];
        ready_queue.CURRENTSIZE--;
        ready_queue.tasks[ready_queue.CURRENTSIZE].priority = -1;
        ready_queue.tasks[ready_queue.CURRENTSIZE].delay=99999;
        ready_queue.tasks[ready_queue.CURRENTSIZE].pointer_to_func = &Nothing;

          
        tasktoberemoved.pointer_to_func();
        //if(ready_queue.tasks[0].priority>ready_queue.tasks[1].priority)  
        //    swap();
         
        
          
        //int initialqueuesize= delay_queue.CURRENTSIZE;
        //for (int j=0;j<delay_queue.CURRENTSIZE;j++)
         
    }
   else if (ready_queue.CURRENTSIZE==0)//if no tasks in ready queue in this tick now
        {
            printf("No task scheduled lesa");
 
        }

    delayMs(50); //50ms after dispatch
    int i=0;
    while(delay_queue.CURRENTSIZE!=0)
            {
                if(delay_queue.tasks[i].delay== 99999)
                        break;
                if(delay_queue.tasks[0].delay!= 99999)//there is a task
                {
                   if (delay_queue.tasks[0].delay==1 && i==0)
                        delay_queue.tasks[0].delay--;
                    else if (delay_queue.tasks[0].delay>1 && i==0)
                        delay_queue.tasks[0].delay--;
                    else if (delay_queue.tasks[i].delay==1 && i!=0)
                        delay_queue.tasks[i].delay--;                 
                    else if (delay_queue.tasks[i].delay>1 && i!=0)
                        delay_queue.tasks[i].delay--;             
                }
                if(delay_queue.tasks[0].delay==0)
                    {
                        QueTask(delay_queue.tasks[0].pointer_to_func,delay_queue.tasks[0].priority);
                        
                        for (int i=0;i<delay_queue.CURRENTSIZE;i++)
                            delay_queue.tasks[i] = delay_queue.tasks[i+1];                       
                        delay_queue.CURRENTSIZE--;
                        delay_queue.tasks[delay_queue.CURRENTSIZE].priority = -1;
                        delay_queue.tasks[delay_queue.CURRENTSIZE].delay=99999;
                        delay_queue.tasks[delay_queue.CURRENTSIZE].pointer_to_func = &Nothing;
                        i--;
                    } 
                i++;                    
            }

    
}

int main(){
  //struct task newtask;
  //task1 newtask;
  /*newtask.priority = 1;
  newtask.pointer_to_func= &print;
  newtask.delay =50;
  newtask.pointer_to_func();*/

  //struct taskQueue *ready_queue;
  //printf("dsfdsfo");
  init(20);
  //ready_queue->tasks[9].pointer_to_func();
  QueTask(&print,300);
  QueTask(&print2,568); 
  //QueTask(&task3,200);
 /*  QueTask(&print2,5677);
  QueTask(&print,45);
  QueTask(&print2,3); */
  
  for (int p=0; p<10;p++){
   dispatch();
  }
  
 
  
  
    
  /* printf("%d\n", ready_queue->tasks[0].priority);
   ready_queue->tasks[0].pointer_to_func();*/
  /*printf("%d", ready_queue.tasks[0].priority);
  printf("%d", ready_queue.tasks[1].priority); 
  printf("%d", ready_queue.tasks[2].priority); 
 
 */
  return 0;  
}


