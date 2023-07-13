#include"hello.h"//界面函数
#include"right.h"//复杂的正误判断函数
#include"mak_list.h"//程序数据函数
#include"sys.h"//系统设置函数
#include"money.h"//账目统计相关函数

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