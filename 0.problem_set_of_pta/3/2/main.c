/*
编写程序，读入矩阵行数、列数及所有矩阵元素，矩阵中所有元素均为正整数，计算并打印出矩阵中的最大连通块数。注：如果两个元素值相同，并且上、下、左、右四个方向之一相邻，则称两个元素是连通的;连通关系
是可传递的，一个元素的连通元素，也是与它连通元素的连通元素。最大连通块定义为所有连通元素组成的最大集，单个元素也可成为最大连通块。要求设计出求连通块数的递归或非递归算法。矩阵行数、列数不超出50。

输入格式:
行数、列数及所有矩阵元素，所有数据均为整型。

输出格式:
连通块数量。

输入样例:
7 6    
4   4   4   4   4   4
4   1   3   2   1   4
4   1   2   2   1   4
4   1   1   1   1   4
4   1   2   2   3   4
4   3   3   3   3   4
4   4   4   4   4   4
输出样例:
在这里给出相应的输出。例如：

6
*/
#include <stdio.h>
#include <stdlib.h>
#define MAX_LEN 50
int martix[MAX_LEN][MAX_LEN];
int mark[MAX_LEN][MAX_LEN]={0};
int col,row;
int max[10]={0};
void init(){
    scanf("%d %d",&row,&col);
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            scanf("%d",&martix[i][j]);
        }
    }
}
int find(int x,int y){
    int res=1;
    mark[x][y]=1;
    if(x-1>=0&&mark[x-1][y]==0&&martix[x-1][y]==martix[x][y]){
        res+=find(x-1,y);
    }
    if(x+1<row&&mark[x+1][y]==0&&martix[x+1][y]==martix[x][y]){
        res+=find(x+1,y);
    }
    if(y-1>=0&&mark[x][y-1]==0&&martix[x][y-1]==martix[x][y]){
        res+=find(x,y-1);
    }
    if(y+1<col&&mark[x][y+1]==0&&martix[x][y+1]==martix[x][y]){
        res+=find(x,y+1);
    }
    return res;
}
int main(){
    init();
    int count=0;
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            if(mark[i][j]==0){
                count++;
                int res=find(i,j);
                max[martix[i][j]]=res>max[martix[i][j]]?res:max[martix[i][j]]; 

            }
        }
    }
    for(int i=0;i<10;i++){
        printf("%d\n",max[i]);
    }
    printf("%d\n",count);
    return 0;
}
