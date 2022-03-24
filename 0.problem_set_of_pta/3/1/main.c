/*
2.1 给定一个含n个整数顺序存储的线性表，按分治法思路，采用二分策略，设计一个求出其最大值和最小值算法，编写相
应测试程序。要求使用分治法设计出其中求最大值、最小值组合的递归算法。
输入格式:
若干整数，个数小于等于10000。
输出格式:
最小值,最大值。
输入样例:
100 2 3 -2 -8 -6 -9 -10 50 2 -1
输出样例:
-10,100
*/
#include <stdio.h>
#include <stdlib.h>
int dataSet[10000];
void find(int arr[],int left,int right,int *min,int *max){
    if(left==right){
        *min=*max=arr[left];
        return;
    }
    int mid=(left+right)/2;
    int leftMin,leftMax,rightMin,rightMax;
    find(arr,left,mid,&leftMin,&leftMax);
    find(arr,mid+1,right,&rightMin,&rightMax);
    *min=leftMin<rightMin?leftMin:rightMin;
    *max=leftMax>rightMax?leftMax:rightMax;
}
int init(){
    int i=0,digit;
    /*for(int digit;scanf("%d ",&digit)==0;i++){
        dataSet[i]=digit;
    }*/
    while(scanf("%d ",&digit)==1){
        dataSet[i++]=digit;
    }
    return i;
}
int main(){
    int n=init();
    int min,max;
    find(dataSet,0,n-1,&min,&max);
    printf("%d,%d\n",min,max);
    return 0;
}