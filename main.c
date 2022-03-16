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
        printf("panic:the stack is empty!");
        exit(-2);
    }
    ElemType e=stack->bottom[stack->top];
    stack->top--;
    return e;
}
ElemType get(_stack *stack){
    if(stack->top==-1){
        printf("panic:the stack is empty!");
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
        printf("%5d",stack->bottom[i]);
    }
    printf("\n");
}
int main(){
    _stack plusStack = create(MAX_LEN);
    _stack minusStack = create(MAX_LEN);
    int digit;
    for(;scanf("%d",&digit)==1;){
        digit>0?push(&plusStack,digit):push(&minusStack,digit);
    }
    for(;status(&plusStack);){
        printf("%5d",pop(&plusStack));
    }
    printf("\n");
    print(&minusStack);
    return 0;
}