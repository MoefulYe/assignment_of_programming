#include<stdlib.h>
#include<stdio.h>
typedef int Elemtype;
int getPivotPosition(Elemtype *src,int bottom,int top){
    Elemtype x=src[bottom];
    for(;bottom<top;){
        for(;bottom<top&&x<src[top];){
            top--;
        }
        if(bottom==top){
            break;
        }
        src[bottom++]=src[top];
        for(;bottom<top&&x>src[bottom];){
            bottom++;
        }
        if(bottom==top){
            break;
        }
        src[top--]=src[bottom];
    }
    src[bottom]=x;
    return bottom;
} 
void quickSort(Elemtype *src,int bottom,int top){
    if(bottom>=top){
        return;
    }
    int pivotPos=getPivotPosition(src,bottom,top);
    quickSort(src,bottom,pivotPos-1);
    quickSort(src,pivotPos+1,top);
}
int main(){
    int arr[5]={1,3,5,2,4};
    quickSort(arr,0,4);
    return 0;
}