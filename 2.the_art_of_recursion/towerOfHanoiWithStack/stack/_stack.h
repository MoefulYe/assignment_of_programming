#ifndef _STACK_INCLUDED_
#define _STACK_INCLUDED_
typedef struct {
    int n;
    char A,B,C;
}problem;
typedef struct{
    problem *bottom;
    int top;
    int cap;
} _stack;
void init(problem *pb,int num,char x,char y,char z);
void Hanoi(problem pb);
//创建一个容量为cap的栈
_stack create(int cap);
//查看栈的状态
int status(_stack *stack);
//销毁栈
void clear(_stack *stack);
//入栈
void push(_stack *stack,problem e);
//入栈，如果容量不够，则扩容
void pushWithResize(_stack *stack,problem e);
//弹出栈顶元素
problem pop(_stack *stack);
//查看栈顶元素
problem get(_stack *stack);
//拷贝栈
void copy(_stack *stack1,_stack *stack2);
//重新调整大小
void resize(_stack *stack,int cap);
//打印栈
//void print(_stack *stack);
#endif // _STACK_INCLUDED_