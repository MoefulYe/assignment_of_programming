#ifndef _OPERSTACK_INCLUDED_
#define _OPERSTACK_INCLUDED_
typedef char Operator;
typedef struct{
    Operator *bottom;
    int top;
    int cap;
} _stack_;
//创建一个容量为cap的栈
_stack_ _create(int cap);
//查看栈的状态
int _status(_stack_ *stack);
//销毁栈
void _clear(_stack_ *stack);
//入栈
void _push(_stack_ *stack,Operator e);
//入栈，如果容量不够，则扩容
void _pushWithResize(_stack_ *stack,Operator e);
//弹出栈顶元素
Operator _pop(_stack_ *stack);
//查看栈顶元素
Operator _get(_stack_ *stack);
//拷贝栈
void _copy(_stack_ *stack1,_stack_ *stack2);
//重新调整大小
void _resize(_stack_ *stack,int cap);
//打印栈
void _print(_stack_ *stack);
#endif // _OPERSTACK_INCLUDED_