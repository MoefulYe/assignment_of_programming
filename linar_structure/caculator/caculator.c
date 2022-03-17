#include "../stack/_stack.h"  //定义了操作数栈和操作
#include "./_stack/_stack_.h" //定义了运算符栈和操作
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 200
//输入一个表达式，以#结束
char *getExp()
{
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
int priority(char c)
{
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
int isDigit(char c)
{
    return c >= '0' && c <= '9';
}
int main()
{
    _stack_ operStack = _create(MAX_LEN);
    _stack numStack = create(MAX_LEN);
    char *exp = getExp();
    printf("%s=", exp);
    int temp = 0;
    for (int index = 0; exp[index] != '\0'; index++)
    {
        if (isDigit(exp[index])) //如果是数字
        {
            temp = temp * 10 + (exp[index] - '0');
        }
        else //如果是符号
        {
            push(&numStack, temp);
            temp = 0;
            if (exp[index] == '(')
            {
                _push(&operStack, exp[index]);
            }
            else if (exp[index] == ')')
            {
                Operator oper;
                while ((oper=_pop(&operStack)) != '(')
                {
                    int a = pop(&numStack);
                    int b = pop(&numStack);
                    switch (oper)
                    {
                    case '+':
                        push(&numStack, a + b);
                        break;
                    case '-':
                        push(&numStack, a - b);
                        break;
                    case '*':
                        push(&numStack, a * b);
                        break;
                    case '/':
                        push(&numStack, a / b);
                        break;
                    }
                }
            }
            else if (priority(exp[index]) > priority(_get(&operStack)))
            {
                _push(&operStack, exp[index]);
            }
            else
            {
                while (priority(exp[index]) <= priority(_get(&operStack)))
                {
                    char oper = _pop(&operStack);
                    int a = pop(&numStack);
                    int b = pop(&numStack);
                    switch (oper)
                    {
                    case '+':
                        push(&numStack, a + b);
                        break;
                    case '-':
                        push(&numStack, a - b);
                        break;
                    case '*':
                        push(&numStack, a * b);
                        break;
                    case '/':
                        push(&numStack, a / b);
                        break;
                    }
                }
                _push(&operStack, exp[index]);
            }
        }
    }
    if (temp != 0)
    {
        push(&numStack, temp);
    }
    while (_status(&operStack) != 0)
    {
        char oper = _pop(&operStack);
        int a = pop(&numStack);
        int b = pop(&numStack);
        switch (oper)
        {
        case '+':
            push(&numStack, a + b);
            break;
        case '-':
            push(&numStack, a - b);
            break;
        case '*':
            push(&numStack, a * b);
            break;
        case '/':
            push(&numStack, a / b);
            break;
        }
    }
    printf("%d\n", pop(&numStack));
    return 0;
}