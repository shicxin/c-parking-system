#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"hello.h"//界面函数
#include"right.h"//复杂的正误判断函数
#include"mak_list.h"//程序数据函数
#include"sys.h"//系统设置函数
#include"money.h"//账目统计相关函数



int read_f_num();

void Car_Com();//车来了，需要车牌号，会为车牌号分配对应的停车位
void Car_Out();//车走了
void Car_Wer();//车在哪


//
int main()
{
    while(NOW!=100)
    {
        He_init();
    }
    //puts("欢迎管理员");
    //system("pause");
    //IsRight();
    //He_init();
    // char** park;
    // init_sys(park);
    
    return 0;
}

int read_f_num(FILE*fp)
{
    char s[100];
    int num = 0;
    fgets(s, 100, fp);
    //printf("%s\t", s);
    int n = strlen(s);
    if(s[0] != '\n')
    {
    //if(s[n-1] == '\n')n -= 1;
    //printf("thisis%d:\t", n);
    for(int i = 0; i <= n; i++, num *= 10)
    {
    if(s[i] <= '9' && s[i] >= '0')
    {
    num += (s[i] - '0');
    //printf("the %d is %c\t", i, s[i]);
    }
    else num /= 10;
    }
    num /= 10;
    }
    //printf("%d\n", num);
    return num;
}