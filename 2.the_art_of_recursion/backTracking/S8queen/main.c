#include<stdio.h>
#include<stdlib.h>
#define MAX_N 30
int n,solutionCount=0;
int colPerRow[MAX_N],MaxTrix[MAX_N][MAX_N]={0};;
int solutions[2000][MAX_N][MAX_N]={0};
void init(){
    scanf("%d",&n);
    for(int i=0;i<n;i++){
            colPerRow[i]=-1;
    }
}
//赋值
void assign(int (*src)[MAX_N],int (*dest)[MAX_N]){
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++){
            dest[i][j]=src[i][j];
        }
}
//打印
void print(){
    for(int i=0;i<solutionCount;i++){
        for(int j=0;j<n;j++){
            for(int k=0;k<n;k++){
                printf("%d ",solutions[i][j][k]);
            }
            printf("\n");
        }
    printf("\n");
    }
    printf("There are totally %d solutions\n",solutionCount);
}
//检查可行性,可行返回1
int check(int row){
    for(int i=0;i<=row;i++)
        for(int j=0;j<i;j++){
            if(colPerRow[i]==colPerRow[j])return 0;
            if(abs(i-j)==abs(colPerRow[i]-colPerRow[j]))return 0;            
        }
    return 1;
}
void try(int row){
    for(int i=0;i<n;i++){
        colPerRow[row]=i;
        MaxTrix[i][row]=1;
        if(check(row)){
            if(row<n-1){
                try(row+1);//尝试n+1行
            }else if(row=n-1){
                assign(MaxTrix,solutions[solutionCount++]);       
            }
        }
        colPerRow[row]=-1;//重置状态
        MaxTrix[i][row]=0;
    }
}
int main(){
    init();//初始化
    try(0);//开始回溯
    print();//打印所有解
}