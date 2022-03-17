#include "./_stack_.h"
#include<stdio.h>
#include<stdlib.h>
_stack_ _create(int cap){
    _stack_ stack;
    stack.cap=cap;
    stack.top=-1;
    stack.bottom=(Operator*)malloc(sizeof(Operator)*cap);
    return stack;
}
int _status(_stack_ *stack){
    if(stack->top==-1){
        return 0;
    }
    else if(stack->top<stack->cap-1){
        return 1;
    }
    else if(stack->top=stack->cap-1){
        return 2;
    }
    else{
        return 3;
    }
}
void _clear(_stack_ *stack){
    free(stack->bottom);
}
void _push(_stack_ *stack,Operator e){
    if(stack->cap-1<=stack->top){
        printf("panic:overflow!");
        exit(-1);
    }
    stack->top++;
    stack->bottom[stack->top]=e;
}
void _pushWithResize(_stack_ *stack,Operator e){
    if(stack->cap-1==stack->top){
        _resize(stack,stack->cap+1);
        _push(stack,e);
        return;
    }
    stack->top++;
    stack->bottom[stack->top]=e;
}
Operator _pop(_stack_ *stack){
    if(stack->top==-1){
        printf("panic:the stack is empty!");
        exit(-2);
    }
    Operator e=stack->bottom[stack->top];
    stack->top--;
    return e;
}
Operator _get(_stack_ *stack){
    if(stack->top==-1){
        printf("panic:the stack is empty!");
        exit(-3);
    }
    return stack->bottom[stack->top];
}
void _copy(_stack_ *stack1,_stack_ *stack2){
    if(stack1->top>stack2->cap-1){
        printf("panic:the stack2 is overflowed!");
        exit(-4);
    }
    for(int i=0;i<=stack1->top;i++){
        stack2->bottom[i]=stack1->bottom[i];
    }
    stack2->top=stack1->top>stack2->top?stack1->top:stack2->top;
}
void _resize(_stack_ *stack,int cap){
    if(cap==stack->cap){
        return;
    }
    if(cap-1<stack->top){
        printf("panic:the new stack is unable to contain elements!");
        exit(1);
    }
    Operator *new=(Operator*)malloc(sizeof(Operator)*cap);
    for(int i=0;i<=stack->top;i++){
        new[i]=stack->bottom[i];
    }
    _clear(stack);
    stack->bottom=new;
    stack->cap=cap;
}
void _print(_stack_ *stack){
    for(int i=0;i<=stack->top;i++){
        printf("%c",stack->bottom[i]);
    }
}