#include<stdio.h>
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