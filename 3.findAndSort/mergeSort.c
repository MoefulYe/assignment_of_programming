#include<stdlib.h>
#include<stdio.h>
typedef int Elemtype;
void merge(Elemtype *src,Elemtype *dest,int bottom,int top){
    int m=(bottom+top)/2;
    for(int i=0,j=bottom,k=m+1;i<top-bottom+1;i++){
        if(j==m+1||src[j]>src[k]){
            dest[i]=src[k++];
        }else if(k==top+1||src[j]<=src[k]){
            dest[i]=src[j++];
        }
    }
    return;
}
void mergeSort(Elemtype *src,int bottom,int top){
    if(bottom>=top){
        return;
    }
    int m=(bottom+top)/2;
    mergeSort(src,bottom,m);
    mergeSort(src,m+1,top);
    Elemtype dest[top-bottom+1];
    merge(src,dest,bottom,top);
    for(int i=bottom;i<=top;i++){
        src[i]=dest[i-bottom];
    }
    return;
}