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
//kara乘法的实现
unsignedBigNumber KaratsubamulUBN(unsignedBigNumber *u1,unsignedBigNumber *u2){
    if(u1->digitCount==1){
        return scaleUBN(u2,u1->phead->next->digit);
    }
    else if(u2->digitCount==1){
        return scaleUBN(u1,u2->phead->next->digit);
    }
    int h=u1->digitCount>u2->digitCount?u1->digitCount:u2->digitCount;
    h/=2;
    unsignedBigNumber A,B,C,D,APlusB,CPlusD,Z2,Z1,Z0,Z2PlusZ0,Z,result;
    initUBN(&result);
    //考虑大数位与小数位相乘的情况？？
    split(u1,h,&A,&B);
    split(u2,h,&C,&D);
    APlusB=addUBN(&A,&B);
    CPlusD=addUBN(&C,&D);
    Z2=KaratsubamulUBN(&A,&C);
    Z=KaratsubamulUBN(&APlusB,&CPlusD);
    Z0=KaratsubamulUBN(&B,&D);
    Z2PlusZ0=addUBN(&Z2,&Z0);
    Z1=subUBN(&Z,&Z2PlusZ0);
    shiftLeft(&Z2,h*2);
    shiftLeft(&Z1,h);
    result=addUBN(&Z0,&Z1);
    result=addUBN(&result,&Z2);
    dropUBN(&A);
    dropUBN(&B);
    dropUBN(&C);
    dropUBN(&D);
    dropUBN(&APlusB);
    dropUBN(&CPlusD);
    dropUBN(&Z);
    dropUBN(&Z0);
    dropUBN(&Z1);
    dropUBN(&Z2);
    dropUBN(&Z2PlusZ0);
    return result;
}
//split函数
void split(unsignedBigNumber *src,int digitCount,unsignedBigNumber *dst1,unsignedBigNumber *dst2){
    initUBN(dst1);
    initUBN(dst2);
    node *p=src->ptail;
    for(int i=0;p!=src->phead;i++,p=p->prev){
        if(i<digitCount){
            appendFrontDigit(dst2,p->digit);
        }else{
            appendFrontDigit(dst1,p->digit);
        }
    }
    //位数为零？？？
    formatUBN(dst2);
    formatUBN(dst1);
}
//大数除法
//取模
int main(){
    unsignedBigNumber u1=inputUBN(),u2=inputUBN(),u3;
    u3=KaratsubamulUBN(&u1,&u2);
    printUBN(&u3);
    return 0;
}