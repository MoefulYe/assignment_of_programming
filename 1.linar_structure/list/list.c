#include<stdlib.h>
#include<stdio.h>
typedef int datatype;
typedef struct node{
    datatype data;
    struct node *next;
}node;
typedef struct {
    node *head;
    node *tail;
}list;
list create(){
    list instance;
    instance.head=instance.tail=(node*)malloc(sizeof(node));
    instance.tail->next=NULL;
    return instance;
}
/*求长*/
int length(list *l){
    int len=0;
    node *p=l->head->next;
    while(p!=NULL){
        len++;
        p=p->next;
    }
    return len;
}
/*清除*/ 
void clear(list *l){
    node *p=l->head->next,*q;
    while(p!=NULL){
        q=p;
        p=p->next;
        free(q);
    }
    l->head->next=NULL;
    l->tail=l->head;
}
/*销毁*/
void destroy(list *l){
    clear(l);
    free(l->head);
    l->head=l->tail=NULL;
}
/*追加*/
void append(list *l,datatype x){
    node *p=(node*)malloc(sizeof(node));
    if(p==NULL){
        printf("out of space\n");
        return;
    }
    p->data=x;
    p->next=NULL;
    l->tail->next=p;
    l->tail=p;
}
/*插入*/
void insert(list *l,datatype x,int i){
    node *p=(node*)malloc(sizeof(node));
    if(p==NULL){
        printf("out of space\n");
        return;
    }
    p->data=x;
    node *q=l->head;
    while(i>0){
        q=q->next;
        i--;
    }
    p->next=q->next;
    q->next=p;
}
/*拷贝*/
list copy(list *l){
    list instance=create();
    node *p=l->head->next,*q=instance.head;
    while(p!=NULL){
        q->next=(node*)malloc(sizeof(node));
        q=q->next;
        q->data=p->data;
        q->next=NULL;
        p=p->next;
    }
    instance.tail=q;
    return instance;
}
/*从数组创建链表*/
list createFromArray(datatype *a,int n){
    list instance=create();
    if(instance.head==NULL)
        return instance;
    node *p=instance.head,*q;
    for(int i=0;i<n;i++){
        q=(node*)malloc(sizeof(node));
        if(q==NULL){
            destroy(&instance);
            return instance;
        }
        q->data=a[i];
        p->next=q;
        p=q;
    }
    instance.tail=p;
    return instance;
}
/*反转*/
void reverse(list *l){
    node *p=l->head->next,*q=NULL,*r;
    while(p!=NULL){
        r=p->next;
        p->next=q;
        q=p;
        p=r;
    }
    l->tail=l->head;
    l->head->next=q;
}
/*排序*/
void sort(list *l){
	node *p1,*p2,*p,*temp;
	int count=0,len=length(l);
	p = l->head->next, p1 =p->next, p2 = p1->next;
	while(count < len){
			while (p2->next != 0){
				if (p1->data > p2->data){
					p1->next = p2->next;
			        p2->next = p->next;
			        p->next = p2;
			        temp = p2;
                    p2 = p1;
			        p1 = temp;
				}
				p = p->next, p1 = p1->next, p2 = p2->next;
			}
			if ((p1->data>p2->data)&&p2->next == 0){
                p1->next = p2->next;
			    p2->next = p->next;
			    p->next = p2;
			      temp = p2;
			      p2 = p1;
			      p1 = temp;
			}
			p = l->head->next;
            p1 = p->next;
            p2 = p1->next;
            count++;
	    }
}
/*返回第i个元素的数据*/
datatype get(list *l,int i){
    node *p=l->head->next;
    while(i>0){
        p=p->next;
        i--;
    }
    return p->data;
}
/*替换第i个元素的数据*/
void set(list *l,int i,datatype x){
    node *p=l->head->next;
    while(i>0){
        p=p->next;
        i--;
    }
    p->data=x;
}
/*查找第一个值为x的元素*/
int find(list *l,datatype x){
    node *p=l->head->next;
    int i=0;
    while(p!=NULL){
        if(p->data==x)
            return i;
        p=p->next;
        i++;
    }
    return -1;
}
/*删除第i个元素*/
void removeAt(list *l,int i){
    node *p=l->head;
    while(i-->0){
        p=p->next;
    }
    node *temp=p->next;
    p->next=p->next->next;
    free(temp);
    if(p==l->tail)
        l->tail=p;
}
/*删除指定值的元素*/
void removeValue(list *l,datatype x){
    node *p=l->head->next,*q=l->head;
    while(p!=NULL){
        if(p->data==x){
            node *temp=p;
            p=p->next;       
            q->next=p;
            free(temp);
            if(q==l->tail)
                l->tail=q;
                return;
        }else{
            q=p;
            p=p->next;
        }
    }
}
/*由链表转数组*/
datatype *toArray(list *l){
    node *p=l->head->next;
    int n=0;
    while(p!=NULL){
        n++;
        p=p->next;
    }
    datatype *a=(datatype*)malloc(sizeof(datatype)*n);
    if(a==NULL){
        printf("out of space\n");
        return NULL;
    }
    p=l->head->next;
    for(int i=0;i<n;i++){
        a[i]=p->data;
        p=p->next;
    }
    return a;
}
/*打印链表*/
void print(list *l){
    node *p=l->head->next;
    while(p!=NULL){
        printf("%d ",p->data);
        p=p->next;
    }
    printf("\n");
}
/*销毁链表*/
void drop(list *l){
    node *p=l->head->next,*q;
    while(p!=NULL){
        q=p;
        p=p->next;
        free(q);
    }
    free(l->head);
    l->head=NULL;
    l->tail=NULL;
}
int main(){
    int arr[6]={1,2,3,6,5,4};
    list l=createFromArray(arr,6);
    sort(&l);
    removeValue(&l,5);
    print(&l);
    return 0;
}
