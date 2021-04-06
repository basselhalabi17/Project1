#include  <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef void (*fptr)();

struct taskQueue {
	int CURRENTSIZE;
	int MAXSIZE;
	struct task *tasks;
};

struct task {
    int priority;
    fptr pointer_to_func;
    int delay;
};



void QueTask(fptr f, int Priority,struct taskQueue * q)
{
    q->tasks[q->CURRENTSIZE].priority=Priority;
    q->CURRENTSIZE++;

    for (int i=0; i<q->CURRENTSIZE;i++){
        for (int j=0; j<q->CURRENTSIZE;j++){
            if (q->tasks[i].priority > q->tasks[j].priority && i!=j){

                struct task temp = q->tasks[i];
	            q->tasks[i] = q->tasks[j];
	            q->tasks[j] = temp;
            }
        }
    }

}

void print(struct taskQueue *q, int size){
    printf("\nbassel alby ");  
}
void Nothing(){
    //printf("bassel alby ");  
}
 void init(struct taskQueue * q, int size )
{
    printf("fgdgfd ");
    q->CURRENTSIZE=0;
    q->MAXSIZE=size;
    q->tasks = (struct task*)malloc(size * sizeof(struct task));
    for(int i=0;i< size; i++)
        {
            q->tasks[i].priority=-1;
            q->tasks[i].delay=0;
            q->tasks[i].pointer_to_func = &Nothing;
        }  
} 


int main(){
  struct task newtask;
  //task1 newtask;
  /*newtask.priority = 1;
  newtask.pointer_to_func= &print;
  newtask.delay =50;
  newtask.pointer_to_func();*/

  struct taskQueue *ready_queue; 
  init(ready_queue,20);
  //ready_queue->tasks[9].pointer_to_func();
  QueTask(&print,324,ready_queue);
  QueTask(&print,5677,ready_queue);
  printf("%d\n", ready_queue->tasks[0].priority);
   ready_queue->tasks[0].pointer_to_func();
  printf("%d", ready_queue->tasks[1].priority);
  printf("%d", ready_queue->tasks[2].priority);
 
  return 0;  
}


