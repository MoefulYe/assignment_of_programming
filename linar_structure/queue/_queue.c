#include "./_queue.h"
#include<stdio.h>
#include<stdlib.h>
_queue create(int cap){
    _queue queue;
    queue.cap=cap;
    queue.top=-1;
    queue.bottom=(ElemType*)malloc(sizeof(ElemType)*cap);
    return queue;
}
int status(_queue *queue){
    if(queue->top==-1){
        return 0;
    }
    else if(queue->top<queue->cap-1){
        return 1;
    }
    else if(queue->top=queue->cap-1){
        return 2;
    }
    else{
        return 3;
    }
}
void clear(_queue *queue){
    free(queue->bottom);
}
void enqueue(_queue *queue,ElemType e){
    if(queue->cap-1<=queue->top){
        printf("panic:overflow!");
        exit(-1);
    }
    queue->top++;
    queue->bottom[queue->top]=e;
}
void enqueueWithResize(_queue *queue,ElemType e){
    if(queue->cap-1==queue->top){
        resize(queue,queue->cap+1);
        enqueue(queue,e);
        return;
    }
    queue->top++;
    queue->bottom[queue->top]=e;
}
ElemType dequeue(_queue *queue){
    if(queue->top==-1){
        printf("panic:the queue is empty!");
        exit(-2);
    }
    ElemType e=queue->bottom[0];
    queue->top--;
    for(int i=0;i<=queue->top;i++){
        queue->bottom[i]=queue->bottom[i+1];
    }
    return e;
}
ElemType get(_queue *queue){
    if(queue->top==-1){
        printf("panic:the queue is empty!");
        exit(-3);
    }
    return queue->bottom[0];
}
void copy(_queue *queue1,_queue *queue2){
    if(queue1->top>queue2->cap-1){
        printf("panic:the queue2 is overflowed!");
        exit(-4);
    }
    for(int i=0;i<=queue1->top;i++){
        queue2->bottom[i]=queue1->bottom[i];
    }
    queue2->top=queue1->top>queue2->top?queue1->top:queue2->top;
}
void resize(_queue *queue,int cap){
    if(cap==queue->cap){
        return;
    }
    if(cap-1<queue->top){
        printf("panic:the new queue is unable to contain elements!");
        exit(1);
    }
    ElemType *new=(ElemType*)malloc(sizeof(ElemType)*cap);
    for(int i=0;i<=queue->top;i++){
        new[i]=queue->bottom[i];
    }
    clear(queue);
    queue->bottom=new;
    queue->cap=cap;
}
void print(_queue *queue){
    for(int i=0;i<=queue->top;i++){
        printf("%d ",queue->bottom[i]);
    }
    printf("\n");
}