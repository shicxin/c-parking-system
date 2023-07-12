#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"hello.h"

int* init_con=NULL;//初始化变量存储位置
int n=100;//停车场车位
int ten_mun;//十分钟的价钱
int hfh_mun;//半小时的价钱
int hou_mun;//一小时的价钱

int read_f_num();
void init_sys(char**plc);//初始化系统
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
    char** park;
    init_sys(park);
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

void init_sys(char**plc)
{
    FILE*sys = NULL;
    if((sys = fopen(".\\data\\system", "r")) == NULL)
    {
        printf("Can not open data file system\n");
        exit(0);
    }
    init_con = (int*)malloc(sizeof(int) * 6);
    for(int i = 0; i < 6; i++)
    {
        init_con[i] = read_f_num(sys);
    }
    user_len = init_con[0];
    paswd_len = init_con[1];
    n = init_con[2];
    ten_mun = init_con[3];
    hfh_mun = init_con[4];
    hou_mun = init_con[5];
    printf("%d\n", user_len);
    fclose(sys);
}

