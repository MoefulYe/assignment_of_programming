#ifndef UNSIGNEDBIGNUMBER_INCLUDED
 #define UNSIGNEDBIGNUMBER_INCLUDED
typedef struct node{
    int digit;
    struct node *next,*prev;
} node;
 
typedef struct{
    int digitCount;
    node *phead,*ptail;
} unsignedBigNumber;
//新建一个节点
node* newNode();
//初始化一个无符号大数
void initUBN(unsignedBigNumber *ubn);
//打印一个无符号大数
void printUBN(unsignedBigNumber* ubn);
//输入一个无符号大数
unsignedBigNumber inputUBN();
//销毁一个无符号大数
void dropUBN(unsignedBigNumber *ubn);
//在尾部追加一位
void appendDigit(unsignedBigNumber* ubn,int digit);
//在头部追加一位
void appendFrontDigit(unsignedBigNumber* ubn,int digit);
//格式化无符号大数
void formatUBN(unsignedBigNumber* ubn);
//无符号大数倍乘一个整形
unsignedBigNumber scaleUBN(unsignedBigNumber *ubn,int scale);
//两个无符号大数相加
unsignedBigNumber addUBN(unsignedBigNumber *u1,unsignedBigNumber *u2);
//两个无符号大数相减
unsignedBigNumber subUBN(unsignedBigNumber *u1,unsignedBigNumber *u2);
//两个无符号大数相乘
unsignedBigNumber mulUBN(unsignedBigNumber *u1,unsignedBigNumber *u2);
//两个无符号大数相除
unsignedBigNumber divUBN(unsignedBigNumber *u1,unsignedBigNumber *u2);
//无符号大数字取模
unsignedBigNumber modUBN(unsignedBigNumber *u1,unsignedBigNumber *u2);
//比较两个无符号大数的大小,u1>u2时返回1;u1=u2返回;u1<u2返回-1
int cmpUBN(unsignedBigNumber *u1,unsignedBigNumber *u2);
//int转无符号大数
unsignedBigNumber intToUBN(int n);
//无符号大数转int
int UBNToInt(unsignedBigNumber *ubn);
//把ubn2赋值给空无符号大数ubn1
void assign(unsignedBigNumber *ubn1,unsignedBigNumber *ubn2);
void shiftLeft(unsignedBigNumber *ubn,int i);
//
void split(unsignedBigNumber* src,unsignedBigNumber* dst1,unsignedBigNumber* dst2);
//
unsignedBigNumber KaratsubamulUBN(unsignedBigNumber *u1,unsignedBigNumber *u2);
#endif //UNSIGNEDBIGNUMBER_INCLUDED