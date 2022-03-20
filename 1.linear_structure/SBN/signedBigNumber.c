#include "./signedBigNumber.h"
#include<stdio.h>
#include<stdlib.h>
signedBigNumber absSBN(signedBigNumber *sbn){
    signedBigNumber result;
    initSBN(&result);
    assign();
}
void assign(signedBigNumber *s1,signedBigNumber *s2){
    
    node* p2 = s2->phead->next;
    while(p2!= NULL){
        appendDigit(s1,p2->digit);
        p2 = p2->next;
    }
}