/*
7-5 程序设计综合实践 1.10 (100 分)
1.10 编写程序选用顺序存储结构和链式存储结构实现抽象数据类型栈和队列，再利用栈和队列，
输入若干个整数，将输入后的正整数和负整数分别保存起来，输入完成后，首先将以输入相反的次序
输出所有保存的正整数，再以输入相同次序输出所有保存的负整数，。
*/
#include<stdio.h>
#include<stdlib.h>
#include "../../../stack/_stack.h"
#define MAX_LEN 10
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