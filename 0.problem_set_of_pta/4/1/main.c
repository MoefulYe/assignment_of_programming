/*
描述：输入一串整数算式（包含加、减、乘、除四则运算和括号运算），以#结尾，计算并输出算式结果。
输入格式:
四则运算（包括括号），以#结束算式。
输出格式:
算式计算结果。
输入样例
(10/2/5+1)*2#
输出样例:
4
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 200
//输入一个表达式，以#结束
//TODO 提供泛型支持
typedef int ElemType;
typedef struct{
    ElemType *bottom;
    int top;
    int cap;
} _stack;
//创建一个容量为cap的栈
_stack create(int cap);
//查看栈的状态
int status(_stack *stack);
//销毁栈
void clear(_stack *stack);
//入栈
void push(_stack *stack,ElemType e);
//入栈，如果容量不够，则扩容
void pushWithResize(_stack *stack,ElemType e);
//弹出栈顶元素
ElemType pop(_stack *stack);
//查看栈顶元素
ElemType get(_stack *stack);
//拷贝栈
void copy(_stack *stack1,_stack *stack2);
//重新调整大小
void resize(_stack *stack,int cap);
//打印栈
void print(_stack *stack);
_stack create(int cap){
    _stack stack;
    stack.cap=cap;
    stack.top=-1;
    stack.bottom=(ElemType*)malloc(sizeof(ElemType)*cap);
    return stack;
}
int status(_stack *stack){
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
void clear(_stack *stack){
    free(stack->bottom);
}
void push(_stack *stack,ElemType e){
    if(stack->cap-1<=stack->top){
        printf("panic:overflow!");
        exit(-1);
    }
    stack->top++;
    stack->bottom[stack->top]=e;
}
void pushWithResize(_stack *stack,ElemType e){
    if(stack->cap-1==stack->top){
        resize(stack,stack->cap+1);
        push(stack,e);
        return;
    }
    stack->top++;
    stack->bottom[stack->top]=e;
}
ElemType pop(_stack *stack){
    if(stack->top==-1){
        printf("pop() panic:the stack is empty!");
        exit(-3);
    }
    ElemType e=stack->bottom[stack->top];
    stack->top--;
    return e;
}
ElemType get(_stack *stack){
    if(stack->top==-1){
        printf("get() panic:the stack is empty!");
        exit(-3);
    }
    return stack->bottom[stack->top];
}
void copy(_stack *stack1,_stack *stack2){
    if(stack1->top>stack2->cap-1){
        printf("panic:the stack2 is overflowed!");
        exit(-4);
    }
    for(int i=0;i<=stack1->top;i++){
        stack2->bottom[i]=stack1->bottom[i];
    }
    stack2->top=stack1->top>stack2->top?stack1->top:stack2->top;
}
void resize(_stack *stack,int cap){
    if(cap==stack->cap){
        return;
    }
    if(cap-1<stack->top){
        printf("panic:the new stack is unable to contain elements!");
        exit(1);
    }
    ElemType *new=(ElemType*)malloc(sizeof(ElemType)*cap);
    for(int i=0;i<=stack->top;i++){
        new[i]=stack->bottom[i];
    }
    clear(stack);
    stack->bottom=new;
    stack->cap=cap;
}
void print(_stack *stack){
    for(int i=0;i<=stack->top;i++){
        printf("%d ",stack->bottom[i]);
    }
    printf("\n");
}
char *getExp(){
    char *exp = malloc(sizeof(char) * MAX_LEN);
    int i = 0;
    char c;
    while ((c = getchar()) != '#')
    {
        exp[i] = c;
        i++;
    }
    exp[i] = '\0';
    return exp;
}
//求操作符权重
int priority(char c){
    switch (c)
    {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    default:
        return 0;
    }
}
//判断是否是数字
int isDigit(char c){
    return c >= '0' && c <= '9';
}
//计算表达式
int parse(char* exp){
    _stack numStack=create(MAX_LEN);
    _stack opStack=create(MAX_LEN);
    int temp=0;
    for(char *p=exp;*p!='\0';p++){
     //解析
        if(isDigit(*p)){
            temp=temp*10+*p-'0';   
        }else{
            if(temp!=0){
                push(&numStack,temp);
                temp=0;
            }
            if(status(&opStack)==0||*p=='('||priority(*p)>priority(get(&opStack))){
                push(&opStack,*p);
            }else if(*p==')'){
                while(get(&opStack)!='('){
                    int num1=pop(&numStack),num2=pop(&numStack),res;
                    switch (pop(&opStack)){
                        case '+':res=num2+num1;break;
                        case '-':res=num2-num1;break;
                        case '*':res=num2*num1;break;
                        case '/':res=num2/num1;break;
                    }
                    push(&numStack,res);
                }
                pop(&opStack);
            }else if(priority(*p)<=priority(get(&opStack))){
                while (status(&opStack)!=0&&priority(*p)<=priority(get(&opStack))){
                    int num1=pop(&numStack),num2=pop(&numStack),res;
                    switch (pop(&opStack)){
                        case '+':res=num2+num1;break;
                        case '-':res=num2-num1;break;
                        case '*':res=num2*num1;break;
                        case '/':res=num2/num1;break;
                    }
                    push(&numStack,res);
                }
                push(&opStack,*p);
            }
        }
    }
    if(temp!=0){
        push(&numStack,temp);
    }
    while(status(&opStack)!=0){
        int num1=pop(&numStack),num2=pop(&numStack),res;
        switch(pop(&opStack)){
            case '+':res=num2+num1;break;
            case '-':res=num2-num1;break;
            case '*':res=num2*num1;break;
            case '/':res=num2/num1;break;
        }
        push(&numStack,res);
    }
    int res=pop(&numStack);//销毁栈和表达式
    clear(&numStack);
    clear(&opStack);
    free(exp);
    return res;
}
int main(){
    char *exp = getExp();
    int result = parse(exp);
    printf("%d\n", result);
    return 0;
}