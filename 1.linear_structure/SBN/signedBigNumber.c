#include "./signedBigNumber.h"
#include<stdio.h>
#include<stdlib.h>
node* newNode(){
    node* p = (node*)malloc(sizeof(node));
    if(p == NULL){
        printf("out of space\n");
        exit(1);
    }
    return p;
}
void initSBN(signedBigNumber* sbn){
    node* p = newNode();
    sbn->phead =sbn->ptail =p;
    p->next=p->prev=NULL;
    sbn->sign = PLUS;
    sbn->digitCount = 0;
}
signedBigNumber inputSBN(){
    signedBigNumber sbn;
    initSBN(&sbn);
    int digit;
    char ch;
    if((ch=getchar())=='-'){
        sbn.sign = MINUS;
    }
    else if(ch=='+'){
        sbn.sign = PLUS;
    }
    else{
        sbn.sign = PLUS;
        digit=ch-'0';
        appendDigit(&sbn,digit);
    }
    while((ch=getchar())!='\n'){
        digit=ch-'0';
        appendDigit(&sbn,digit);
    }
    formatSBN(&sbn);
    return sbn;
}
void printSBN(signedBigNumber* sbn){
    if(sbn->sign == MINUS){
        printf("-");
    }
    node* p = sbn->phead->next;
    while(p != NULL){
        printf("%d",p->digit);
        p = p->next;
    }
    printf("\n");
}
void appendDigit(signedBigNumber* sbn,int digit){
    if(sbn->digitCount == 1&&sbn->ptail->digit == 0){
        sbn->ptail->digit = digit;
        return;
    }
    node* p = newNode();
    p->digit = digit;
    p->next = NULL;
    p->prev = sbn->ptail;
    sbn->ptail->next = p;
    sbn->ptail = p;
    ++sbn->digitCount;
}
void appendFrontDigit(signedBigNumber* sbn,int digit){
    node* p = newNode();
    p->digit = digit;
    p->next = sbn->phead->next;
    if(p->next != NULL){
        p->next->prev = p;
    }
    p->prev=sbn->phead;
    sbn->phead->next = p;
    if(sbn->ptail == sbn->phead){
        sbn->ptail = p;
    }
    ++sbn->digitCount;
}
void formatSBN(signedBigNumber* sbn){
    if(sbn->digitCount == 0){
        appendDigit(sbn,0);
    }
    while (sbn->digitCount > 1 && sbn->phead->next->digit == 0) {
        node *p = sbn->phead->next;
        sbn->phead->next = p->next;
    }
    while (sbn->digitCount > 1 && sbn->phead->next->digit == 0) {
        node *p = sbn->phead->next;
        sbn->phead->next = p->next;
        p->next->prev = sbn->phead;
        free(p);
        sbn->digitCount--;
    }
    node *p = sbn->phead->next;
    if(p->digit<0){
        sbn->sign = !sbn->sign;
        while(p!= NULL){
            p->digit= -p->digit;
            p = p->next;
        }
        p=sbn->phead->next;
        while(p->next->digit<0){
            p->digit--;
            p->next->digit+=10;
            p=p->next;
        }
    }
}
void dropSBN(signedBigNumber* sbn){
    while(sbn->phead != NULL){
        node* p = sbn->phead;
        sbn->phead = sbn->phead->next;
        free(p);
    }
}
void assign(signedBigNumber* dest,signedBigNumber* src){
    initSBN(dest);
    node* p = src->phead->next;
    node* p2 = src->phead->next;
    while(p2!= NULL){
        appendDigit(dest,p2->digit);
        p2 = p2->next;
    }
    dest->digitCount =src->digitCount;
}
signedBigNumber absSBN(signedBigNumber *sbn){
    signedBigNumber absSBN;
    assign(&absSBN,sbn);
    absSBN.sign = PLUS;
    return absSBN;
}
signedBigNumber getOppositeSBN(signedBigNumber *sbn){
    signedBigNumber oppositeSBN;
    assign(&oppositeSBN,sbn);
    oppositeSBN.sign = !sbn->sign;
    return oppositeSBN;
}
signedBigNumber addSBN(signedBigNumber *s1,signedBigNumber *s2){
    signedBigNumber sbn;
    initSBN(&sbn);
    if(s1->sign==s2->sign){
        sbn.sign = s1->sign;
        node* p1 = s1->ptail;
        node* p2 = s2->ptail;
        int remainer = 0;
        while(p1!=s1->phead && p2!=s2->phead){
            int digit = p1->digit + p2->digit + remainer;
            if(digit > 10){
                remainer = digit/10;
                digit = digit%10;
            }else{
                remainer = 0;
            }
            appendFrontDigit(&sbn,digit);
            p1 = p1->prev;
            p2 = p2->prev;
        }
        while(p1!=s1->phead){
            int digit = p1->digit + remainer;
            if(digit > 10){
                remainer = digit/10;
                digit = digit%10;
            }else{
                remainer = 0;
            }
            appendFrontDigit(&sbn,digit);
            p1 = p1->prev;
        }
        while(p2!=s2->phead){
            int digit = p2->digit + remainer;
            if(digit > 10){
                remainer = digit/10;
                digit = digit%10;
            }else{
                remainer = 0;
            }
            appendFrontDigit(&sbn,digit);
            p2 = p2->prev;
        }
        if(remainer != 0){
            appendFrontDigit(&sbn,remainer);
        }
        
    }
    else{
        sbn.sign = s1->sign;
        node* p1 = s1->ptail;
        node* p2 = s2->ptail;
        int remainer = 0;
        while(p1!=s1->phead && p2!=s2->phead){
            int digit = p1->digit - p2->digit - remainer;
            if(digit < 0){
                remainer = 1;
                digit += 10;
            }else{
                remainer = 0;
            }
            appendFrontDigit(&sbn,digit);
            p1 = p1->prev;
            p2 = p2->prev;
        }
        while(p1!=s1->phead){
            int digit = p1->digit - remainer;
            if(digit < 0){
                remainer = 1;
                digit += 10;
            }else{
                remainer = 0;
            }
            appendFrontDigit(&sbn,digit);
            p1 = p1->prev;
        }
        while(p2!=s2->phead){
            int digit = p2->digit - remainer;
            if(digit < 0){
                remainer = 1;
                digit += 10;
            }else{
                remainer = 0;
            }
            appendFrontDigit(&sbn,digit);
            p2 = p2->prev;
        }
    }
    return sbn;
}
signedBigNumber subSBN(signedBigNumber *s1,signedBigNumber *s2){
    signedBigNumber temp=getOppositeSBN(s2),temp2=addSBN(s1,&temp);
    dropSBN(&temp);
    return temp2;
}

int main(){
    signedBigNumber s1=inputSBN(),s2=inputSBN(),s3=addSBN(&s1,&s2);
    printSBN(&s3);
}