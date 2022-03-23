#include "../stack/_stack.h"  //定义了栈和操作
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 200
//输入一个表达式，以#结束
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
    printf("%s=",exp);
    int result = parse(exp);
    printf("%d\n", result);
    return 0;
}