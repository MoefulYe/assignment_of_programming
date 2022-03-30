#include<stdio.h>
#include<stdlib.h>
#define MAX_N 500
typedef struct{
    int weight,value;
    double valuePerWeight;
}Good;//物品
typedef struct{
//选择状态和最大值
    int isSelected[MAX_N];
    int totalValue;
}solution;
typedef struct {
    int Cap,left;
    Good goods[MAX_N];
    int N;
    solution bestSolution,currentSolution;
}Problem;
Problem problem;
void sort();
void print();
void init();
void try(int i);
void init(){
    scanf("%d %d",&problem.N,&problem.Cap);//输入物品数量和容量
    problem.left=problem.Cap;
    for(int i=0;i<problem.N;i++){
        scanf("%d %d",&problem.goods[i].value,&problem.goods[i].weight);
        problem.goods[i].valuePerWeight=(double)problem.goods[i].value/problem.goods[i].weight;
        problem.currentSolution.isSelected[i]=0;
    }
    sort();
    problem.currentSolution.totalValue=0;
    problem.bestSolution=problem.currentSolution;
}
void print(){
    printf("the total valve is %d:\n",problem.bestSolution.totalValue);
    for(int i=0,j=0;i<problem.N;i++){
        if(problem.bestSolution.isSelected[i]){
            printf("%d. valve: %d weight: %d\n",j++,problem.goods[i].value,problem.goods[i].weight);
        }
    }
}
void sort(){
//排序
    for(int i=1;i<problem.N;i++){
        for(int j=0;j<i;j++){
            if(problem.goods[j].valuePerWeight<problem.goods[i].valuePerWeight){
                Good temp=problem.goods[i];
                problem.goods[i]=problem.goods[j];
                problem.goods[j]=temp;
            }
        }
    }
}
void try(int i){
    if(i==problem.N){
        if(problem.currentSolution.totalValue>problem.bestSolution.totalValue){
            problem.bestSolution=problem.currentSolution;
        }
        return;
    }//case1.已试探所有物品?如果现有解大于最优解?记得回溯
    for(int j=0;j<problem.N;j++){
        if(problem.currentSolution.isSelected[j]==0&&problem.left>=problem.goods[j].weight){
            problem.currentSolution.isSelected[j]=1;
            problem.left-=problem.goods[j].weight;
            problem.currentSolution.totalValue+=problem.goods[j].value;
            try(j+1);
            problem.currentSolution.isSelected[j]=0;
            problem.left+=problem.goods[j].weight;
            problem.currentSolution.totalValue-=problem.goods[j].value;
        }
    }
    if(problem.currentSolution.totalValue>problem.bestSolution.totalValue){
            problem.bestSolution=problem.currentSolution;
    }
    return;
}
int main(){
    init();//初始化问题
    try(0);
    print();
    return 0;
}
