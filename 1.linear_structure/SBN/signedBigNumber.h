#ifndef _SIGNED_BIG_NUMBER_INCLUDED_
#define _SIGNED_BIG_NUMBER_INCLUDED_
#define MINUS 1
#define PLUS 0
//TODO 取绝对值 取相反数
typedef struct node{
    int digit;
    struct node *next,*prev;
}node;
typedef struct{
    int sign;
    int digitCount;
    node *phead,*ptail;
} signedBigNumber;
//新建一个节点
node* newNode();
//初始化一个有符号大数
void initSBN(signedBigNumber *sbn);
//打印一个有符号大数
void printSBN(signedBigNumber* sbn);
//输入一个有符号大数
signedBigNumber inputSBN();
//销毁一个有符号大数
void dropSBN(signedBigNumber *sbn);
//在尾部追加一位
void appendDigit(signedBigNumber* sbn,int digit);
//在头部追加一位
void appendFrontDigit(signedBigNumber* sbn,int digit);
//格式化有符号大数
void formatSBN(signedBigNumber* sbn);
//取绝对值
signedBigNumber absSBN(signedBigNumber *sbn);
//取相反数
signedBigNumber getOpposite(signedBigNumber *sbn);
//有符号大数倍乘一个整形
signedBigNumber scaleSBN(signedBigNumber *sbn,int scale);
//两个有符号大数相加
signedBigNumber addSBN(signedBigNumber *s1,signedBigNumber *s2);
//两个有符号大数相减
signedBigNumber subSBN(signedBigNumber *s1,signedBigNumber *s2);
//两个有符号大数相乘
signedBigNumber mulSBN(signedBigNumber *s1,signedBigNumber *s2);
//两个有符号大数相除
signedBigNumber divSBN(signedBigNumber *s1,signedBigNumber *s2);
//有符号大数字取模
signedBigNumber modSBN(signedBigNumber *s1,signedBigNumber *s2);
//比较两个有符号大数的大小,s1>s2时返回1;s1=s2返回;s1<s2返回-1
int cmpSBN(signedBigNumber *s1,signedBigNumber *s2);
//int转有符号大数
signedBigNumber intToSBN(int n);
//有符号大数转int
int SBNToInt(signedBigNumber *sbn);
//把SBN2赋值给空有符号大数SBN1
void assign(signedBigNumber *s1,signedBigNumber *s2);
void shiftLeft(signedBigNumber *sbn,int i);
void split(signedBigNumber* src,int digitCount,signedBigNumber* dst1,signedBigNumber* dst2);
signedBigNumber KaratsubamulSBN(signedBigNumber *s1,signedBigNumber *s2);
#endif // _SIGNED_BIG_NUMBER_INCLUDED_