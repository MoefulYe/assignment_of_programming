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
        sbn->sign=PLUS;
    }
    while (sbn->digitCount > 1 && sbn->phead->next->digit == 0) {
        node *p = sbn->phead->next;
        sbn->phead->next = p->next;
        p->next->prev = sbn->phead;
        free(p);
        sbn->digitCount--;
    }
    int remainer=0;
    for(node *p=sbn->ptail;p!=sbn->phead;p=p->prev){
        p->digit+=remainer;
        remainer=p->digit/10;
        p->digit%=10;
    }
    if(remainer>0){
        appendFrontDigit(sbn,remainer);
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
int cmpSBN(signedBigNumber *s1,signedBigNumber *s2){
    if(s1->phead->next->digit==0&&s2->phead->next->digit==0){
        return 0;
    }else if(s1->sign==PLUS&&s2->sign==MINUS){
        return 1;
    }else if(s1->sign==MINUS&&s2->sign==PLUS){
        return -1;
    }else if(s1->sign==PLUS){
        if(s1->digitCount > s2->digitCount){
            return 1;
        }
        else if(s1->digitCount < s2->digitCount){
            return -1;
        }
        else{
            node* p1=s1->phead->next;
            node* p2=s2->phead->next;
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
    }else if(s1->sign==MINUS){
        if(s1->digitCount > s2->digitCount){
            return -1;
        }
        else if(s1->digitCount < s2->digitCount){
            return 1;
        }
        else{
            node* p1=s1->phead->next;
            node* p2=s2->phead->next;
            while(p1!=NULL && p2!=NULL){
                if(p1->digit > p2->digit){
                    return -1;
                }
                else if(p1->digit < p2->digit){
                return 1;
                }
                p1 = p1->next;
                p2 = p2->next;
            }
            return 0;
        }
    }
}
signedBigNumber addSBN(signedBigNumber *s1,signedBigNumber *s2){
    signedBigNumber sbn;
    initSBN(&sbn);
    if(s1->sign^s2->sign){
        signedBigNumber absS1=absSBN(s1),absS2=absSBN(s2);
        if(cmpSBN(&absS1,&absS2)>=0){
            sbn.sign=s1->sign;
            node* p1 = absS1.ptail;
            node* p2 = absS2.ptail;
            int remainer = 0;
            while(p1!=absS1.phead && p2!=absS2.phead){
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
            while(p1!=absS1.phead){
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
            while(p2!=absS2.phead){
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
        else{
            sbn.sign=s2->sign;
            node* p1 = absS2.ptail;
            node* p2 = absS1.ptail;
            int remainer = 0;
            while(p1!=absS2.phead && p2!=absS1.phead){
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
            while(p1!=absS2.phead){
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
            while(p2!=absS1.phead){
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
        dropSBN(&absS1);
        dropSBN(&absS2);
    }
    else{
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
    formatSBN(&sbn);
    return sbn;
}
signedBigNumber subSBN(signedBigNumber *s1,signedBigNumber *s2){
    signedBigNumber temp=getOppositeSBN(s2),temp2=addSBN(s1,&temp);
    dropSBN(&temp);
    return temp2;
}
signedBigNumber scaleSBN(signedBigNumber *sbn,int scale){
    signedBigNumber result;
    initSBN(&result);
    if(scale==0){
        formatSBN(&result);
        return result;
    }
    int absScale=scale>0?scale:-scale;
    int sign=scale>0?PLUS:MINUS;
    assign(&result,sbn);
    result.sign^=sign;
    int digit;
    int remainer=0;
    node *p=result.ptail;
    while(p!=result.phead){
        digit = p->digit;
        p->digit = (digit*absScale+remainer)%10;
        remainer = (digit*absScale+remainer)/10;
        p = p->prev;
    }
    if(remainer != 0){
        appendFrontDigit(&result,remainer);
    }
    formatSBN(&result);
    return result;
}
void split(signedBigNumber *src,int digitCount,signedBigNumber *dst1,signedBigNumber *dst2){
    initSBN(dst1);
    initSBN(dst2);
    dst1->sign=dst2->sign=src->sign;
    node *p=src->ptail;
    for(int i=0;p!=src->phead;i++,p=p->prev){
        if(i<digitCount){
            appendFrontDigit(dst2,p->digit);
        }else{
            appendFrontDigit(dst1,p->digit);
        }
    }
    formatSBN(dst2);
    formatSBN(dst1);
}
signedBigNumber mulSBN(signedBigNumber *s1,signedBigNumber *s2){
    signedBigNumber result=KaratsubamulSBN(s1,s2);
    result.sign=result.sign=s1->sign^s2->sign;
    return result;
}
//直接调用有符号问题
signedBigNumber KaratsubamulSBN(signedBigNumber *s1,signedBigNumber *s2){
    if(s1->digitCount==1){
        return scaleSBN(s2,s1->phead->next->digit);
    }
    else if(s2->digitCount==1){
        return scaleSBN(s1,s2->phead->next->digit);
    }
    int h=s1->digitCount>s2->digitCount?s1->digitCount:s2->digitCount;
    h/=2;
    signedBigNumber A,B,C,D,APlusB,CPlusD,Z2,Z1,Z0,Z2PlusZ0,Z,result;
    initSBN(&result);
    split(s1,h,&A,&B);
    split(s2,h,&C,&D);
    APlusB=addSBN(&A,&B);
    CPlusD=addSBN(&C,&D);
    Z2=KaratsubamulSBN(&A,&C);
    Z=KaratsubamulSBN(&APlusB,&CPlusD);
    Z0=KaratsubamulSBN(&B,&D);
    Z2PlusZ0=addSBN(&Z2,&Z0);
    Z1=subSBN(&Z,&Z2PlusZ0);
    shiftLeft(&Z2,h*2);
    shiftLeft(&Z1,h);
    result=addSBN(&Z0,&Z1);
    result=addSBN(&result,&Z2);
    dropSBN(&A);
    dropSBN(&B);
    dropSBN(&C);
    dropSBN(&D);
    dropSBN(&APlusB);
    dropSBN(&CPlusD);
    dropSBN(&Z);
    dropSBN(&Z0);
    dropSBN(&Z1);
    dropSBN(&Z2);
    dropSBN(&Z2PlusZ0);
    return result;
}
void shiftLeft(signedBigNumber *sbn,int i){
    if(i<0){
        sbn->digitCount+=i;
        if(sbn->digitCount>0){
            node *p=sbn->ptail;
            for(;i<0;i++){
                node *temp=p;
                p=p->prev;
                free(temp);
            }
            sbn->ptail=p;
            p->next=NULL;
        }
        else{
            dropSBN(sbn);
            initSBN(sbn);
        }
    }
    else if(i>0){
        for(;i>0;i--){
            appendDigit(sbn,0);
        }
    }
    formatSBN(sbn);
    return;
}
signedBigNumber intToSBN(int n){
    signedBigNumber sbn;
    initSBN(&sbn);
    sbn.sign=n>=0?PLUS:MINUS;
    n=n>0?n:-n;
    while(n != 0){
        appendFrontDigit(&sbn,n%10);
        n = n/10;
    }
    formatSBN(&sbn);
    return sbn;
}
int SBNToInt(signedBigNumber *sbn){
    int n = 0;
    node* p = sbn->phead->next;
    while(p != NULL){
        n = n*10 + p->digit;
        p = p->next;
    }
    if(sbn->sign==MINUS){
        return -n;
    }
    return n;
}
int main(){
    signedBigNumber s1=inputSBN(),s2=inputSBN(),s3=mulSBN(&s1,&s2);
    printSBN(&s3);
    return 0;
}