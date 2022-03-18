#include "./stack/_stack.h"
#define MAX_CAP 50
void Hanoi(problem pb){
    _stack stack=create(MAX_CAP);
    push(&stack,pb);
    while(status(&stack)){
        problem temp=pop(&stack);
        if(temp.n==1);
        else{
            
        }
    }
}
int main(){
    
}
