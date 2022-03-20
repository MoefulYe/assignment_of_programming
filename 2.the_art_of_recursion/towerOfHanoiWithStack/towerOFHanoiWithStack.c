#include "./stack/_stack.h"
#include<stdio.h>
int main(){
    int num;
    problem pb;
    scanf("%d",&num);
    init(&pb,num,'A','B','C');
    Hanoi(pb);
    return 0;
}