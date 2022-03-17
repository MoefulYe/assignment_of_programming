#ifndef _QUEUE_INCLUDED_
#define _QUEUE_INCLUDED_
typedef int ElemType;
typedef struct{
    ElemType *bottom;
    int top;
    int cap;
} _queue;
//创建一个容量为cap的队列
_queue create(int cap);
//查看队列的状态
int status(_queue *queue);
//销毁队列
void clear(_queue *queue);
//入队
void enqueue(_queue *queue,ElemType e);
//入队，如果容量不够，则扩容
void enqueueWithResize(_queue *queue,ElemType e);
//出队
ElemType dequeue(_queue *queue); 
//查看队首元素
ElemType get(_queue *queue);
//拷贝队列
void copy(_queue *queue1,_queue *queue2);
//重新调整大小
void resize(_queue *queue,int cap);
//打印队列
void print(_queue *queue);
#endif // _QUEUE_INCLUDED_