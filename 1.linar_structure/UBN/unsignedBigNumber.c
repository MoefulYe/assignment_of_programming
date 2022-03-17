#include "./unsignedBigNumber.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

node* newNode(){
    node* p = (node*)malloc(sizeof(node));
    if(p == NULL){
        printf("out of space\n");
        exit(1);
    }
    return p;
}
void printUBN(unsignedBigNumber* ubn){
    node* p = ubn->phead->next;
    while(p != NULL){
        printf("%d",p->digit);
        p = p->next;
    }
    printf("\n");
}
void assign(unsignedBigNumber *ubn1,unsignedBigNumber *ubn2){
    node* p2 = ubn2->phead->next;
    while(p2!= NULL){
        appendDigit(ubn1,p2->digit);
        p2 = p2->next;
    }
}
void initUBN(unsignedBigNumber* ubn){
    node* p = newNode();
    ubn->phead =ubn->ptail =p;
    p->next=p->prev=NULL;
    ubn->digitCount = 0;
}
unsignedBigNumber inputUBN(){
    unsignedBigNumber ubn;
    initUBN(&ubn);
    int digit;
    char ch;
    while((ch=getchar())!='\n'){
        digit=ch-'0';
        appendDigit(&ubn,digit);
    }
    formatUBN(&ubn);
    return ubn;
}
void dropUBN(unsignedBigNumber* ubn){
    while(ubn->phead != NULL){
        node* p = ubn->phead;
        ubn->phead = ubn->phead->next;
        free(p);
    }
}
void appendDigit(unsignedBigNumber* ubn,int digit){
    if(ubn->digitCount == 1&&ubn->ptail->digit == 0){
        ubn->ptail->digit = digit;
        return;
    }
    node* p = newNode();
    p->digit = digit;
    p->next = NULL;
    p->prev = ubn->ptail;
    ubn->ptail->next = p;
    ubn->ptail = p;
    ++ubn->digitCount;
}
void appendFrontDigit(unsignedBigNumber* ubn,int digit){
    node* p = newNode();
    p->digit = digit;
    p->next = ubn->phead->next;
    if(p->next != NULL){
        p->next->prev = p;
    }
    p->prev=ubn->phead;
    ubn->phead->next = p;
    if(ubn->ptail == ubn->phead){
        ubn->ptail = p;
    }
    ++ubn->digitCount;
}
void formatUBN(unsignedBigNumber* ubn){
    if(ubn->digitCount == 0){
        appendDigit(ubn,0);
    }
    while (ubn->digitCount > 1 && ubn->phead->next->digit == 0) {
        node *p = ubn->phead->next;
        ubn->phead->next = p->next;
        p->next->prev = ubn->phead;
        free(p);
        ubn->digitCount--;
    }
}
unsignedBigNumber scaleUBN(unsignedBigNumber *ubn,int scale){
    if(scale == 0){
        return intToUBN(0);
    }
    unsignedBigNumber result;
    initUBN(&result);
    assign(&result,ubn);
    int digit;
    int remainer=0;
    node *p=result.ptail;
    while(p!=result.phead){
        digit = p->digit;
        p->digit = (digit*scale+remainer)%10;
        remainer = (digit*scale+remainer)/10;
        p = p->prev;
    }
    if(remainer != 0){
        appendFrontDigit(&result,remainer);
    }
    formatUBN(&result);
    return result;
}
unsignedBigNumber addUBN(unsignedBigNumber *u1,unsignedBigNumber *u2){
    unsignedBigNumber ubn;
    initUBN(&ubn);
    node* p1 = u1->ptail;
    node* p2 = u2->ptail;
    int remainer = 0;
    while(p1!=u1->phead && p2!=u2->phead){
        int digit = p1->digit + p2->digit + remainer;
        if(digit > 10){
            remainer = digit/10;
            digit = digit%10;
        }else{
            remainer = 0;
        }
        appendFrontDigit(&ubn,digit);
        p1 = p1->prev;
        p2 = p2->prev;
    }
    while(p1!=u1->phead){
        int digit = p1->digit + remainer;
        if(digit > 10){
            remainer = digit/10;
            digit = digit%10;
        }else{
            remainer = 0;
        }
        appendFrontDigit(&ubn,digit);
        p1 = p1->prev;
    }
    while(p2!=u2->phead){
        int digit = p2->digit + remainer;
        if(digit > 10){
            remainer = digit/10;
            digit = digit%10;
        }else{
            remainer = 0;
        }
        appendFrontDigit(&ubn,digit);
        p2 = p2->prev;
    }
    if(remainer != 0){
        appendFrontDigit(&ubn,remainer);
    }
    return ubn;
}
unsignedBigNumber subUBN(unsignedBigNumber *u1,unsignedBigNumber *u2){
    if(cmpUBN(u1,u2)<0){
        printf("panic: u1 < u2!\n");
        exit(1);
    }
    unsignedBigNumber ubn;
    initUBN(&ubn);
    node* p1 = u1->ptail;
    node* p2 = u2->ptail;
    int remainer = 0;
    while(p1!=u1->phead && p2!=u2->phead){
        int digit = p1->digit - p2->digit - remainer;
        if(digit < 0){
            remainer = 1;
            digit += 10;
        }else{
            remainer = 0;
        }
        appendFrontDigit(&ubn,digit);
        p1 = p1->prev;
        p2 = p2->prev;
    }
    while(p1!=u1->phead){
        int digit = p1->digit - remainer;
        if(digit < 0){
            remainer = 1;
            digit += 10;
        }else{
            remainer = 0;
        }
        appendFrontDigit(&ubn,digit);
        p1 = p1->prev;
    }
    while(p2!=u2->phead){
        int digit = p2->digit - remainer;
        if(digit < 0){
            remainer = 1;
            digit += 10;
        }else{
            remainer = 0;
        }
        appendFrontDigit(&ubn,digit);
        p2 = p2->prev;
    }
    formatUBN(&ubn);
    return ubn;
}
unsignedBigNumber mulUBN(unsignedBigNumber *u1,unsignedBigNumber *u2){
    unsignedBigNumber ubn=intToUBN(0);
    node* p1 = u1->ptail;
    node* p2 = u2->ptail;
    for(int i=0;p2!=u2->phead;i++){
        int digit = p2->digit;
        unsignedBigNumber temp = scaleUBN(u1,digit);
        shiftLeft(&temp,i);
        ubn = addUBN(&ubn,&temp);
        p2 = p2->prev;
    }
    formatUBN(&ubn);
    return ubn;
}
void shiftLeft(unsignedBigNumber *ubn,int i){
    for(;i>0;i--){
        appendDigit(ubn,0);
    }
    formatUBN(ubn);
}
unsignedBigNumber divUBN(unsignedBigNumber *u1,unsignedBigNumber *u2){
    unsignedBigNumber ubn;
    initUBN(&ubn);
    node* p1 = u1->ptail;
    node* p2 = u2->ptail;
    int remainer = 0;
    while(p1!=u1->phead){
        int digit = p1->digit + remainer*10;
        remainer = digit/p2->digit;
        digit = digit%p2->digit;
        appendFrontDigit(&ubn,digit);
        p1 = p1->prev;
    }
    
    formatUBN(&ubn);
    return ubn;
}
unsignedBigNumber modUBN(unsignedBigNumber *u1,unsignedBigNumber *u2){
    unsignedBigNumber ubn;
    initUBN(&ubn);
    node* p1 = u1->ptail;
    node* p2 = u2->ptail;
    int remainer = 0;
    while(p1!=u1->phead){
        int digit = p1->digit;
        while(p2!=u2->phead){
            digit += remainer*10;
            if(digit >= p2->digit){
                digit -= p2->digit;
                remainer = 1;
            }else{
                remainer = 0;
            }
            p2 = p2->prev;
        }
        p2 = u2->ptail;
        appendFrontDigit(&ubn,digit);
        p1 = p1->prev;
    }
    formatUBN(&ubn);
    return ubn;
}
int cmpUBN(unsignedBigNumber *u1,unsignedBigNumber *u2){
    if(u1->digitCount > u2->digitCount){
        return 1;
    }
    else if(u1->digitCount < u2->digitCount){
        return -1;
    }
    else{
        node* p1=u1->phead->next;
        node* p2=u2->phead->next;
        while(p1!=NULL && p2!=NULL){
            if(p1->digit > p2->digit){
                return 1;
            }
            else if(p1->digit < p2->digit){
                return -1;
            }
            p1 = p1->next;
            p2 = p2->next;
        }
        return 0;
    }
}
unsignedBigNumber intToUBN(int n){
    unsignedBigNumber ubn;
    initUBN(&ubn);
    while(n != 0){
        appendFrontDigit(&ubn,n%10);
        n = n/10;
    }
    formatUBN(&ubn);
    return ubn;
}
int UBNToInt(unsignedBigNumber *ubn){
    int n = 0;
    node* p = ubn->phead->next;
    while(p != NULL){
        n = n*10 + p->digit;
        p = p->next;
    }
    return n;
}
int main(){
    unsignedBigNumber u1=inputUBN(),u2=inputUBN();
    unsignedBigNumber ubn=divUBN(&u1,&u2);
    printUBN(&ubn);
    return 0;
}