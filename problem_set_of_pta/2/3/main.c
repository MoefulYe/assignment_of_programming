/*
1.8 无符号大数加、减运算。程序设计中经常遇到无符号大数加、减运算问题，请在样例程序Ex1.4基础上实现无符号大数减运算。
题目要求输入两个无符号大数，保证一个大数不小于第二个大数，输出它们的和、差。
*/
#include "../../../UBN/unsignedBigNumber.h"
int main(){
    unsignedBigNumber u1,u2,u3,u4;
    u1=inputUBN();
    u2=inputUBN();
    u3=addUBN(&u1,&u2);
    u4=subUBN(&u1,&u2);
    printUBN(&u3);
    printUBN(&u4);
    return 0;
}