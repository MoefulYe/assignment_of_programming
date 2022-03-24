/*
2.4 汉诺（Hanoi）塔问题：假设有命名为A、B、C的三个塔柱，初始时，在塔柱A上插有n个直径大小各不相同的圆盘，从上往下，圆盘从小到大编号为1、2、3、···n，要求将A柱上的圆盘移至塔柱C，可借助塔柱B，用程序模拟搬盘子过程。本程序要求用非递归算法的程序实现 (n<=6)。 圆盘移动必须遵守下列规则： 1：每次只能移动一个圆盘； 2：圆盘可以插在任意一个塔柱上； 3：任何时刻都不能将一个较大的圆盘放在一个较小的圆盘上。

输入格式:
正整数n。

输出格式:
搬盘子过程，每行一次搬动。

输入样例:
3
输出样例:
A->C
A->B
C->B
A->C
B->A
B->C
A->C
*/
#include<stdio.h>
/*
#define MAX_CAP 100
int top[3]={0},num;
void init(){
    scanf("%d",&num);
    top[0]=num;
}
void move(int src,int dst,int start){
    printf("move %d-%d  %c -> %c\n",start,top[src]-1,src+'A',dst+'A');
    top[dst]+=top[src]-start;
    top[src]=start;   
}
void Hanoi(int t,int n){
    if(n==1){
        move(t,2,0);
    }
    else{
        move(t,1-t,1);
        move(t,2,0);
        Hanoi(1-t,n-1);
    }
}
int main(){
    init();
    Hanoi(0,num);
    return 0;    
}
*/
void Hanoi(int n,char x,char y,char z){
    if(n==1){
        printf("move %c -> %c\n",x,z);
    }
    else{
        Hanoi(n-1,x,z,y);
        printf("move %c -> %c\n",x,z);
        Hanoi(n-1,y,x,z);
    }
}
int main(){
    int num;
    scanf("%d",&num);
    Hanoi(num,'A','B','C');
    return 0;
}