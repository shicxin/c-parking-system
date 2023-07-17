#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<time.h>
#include"cha_list.h"
#include"mess_list.h"
#include"init_sys.h"
#include"sys.h"

int user_len = 6; //用户名长度
int paswd_len = 6; //密码长度
int NOW = 0; //程序状态判断
int *init_con = NULL; //初始化变量存储位置
int c_num_qu = 10; //停车场车位
int c_num_lang = 10; //停车场车位
int ten_mun; //十分钟的价钱
int hfh_mun; //半小时的价钱
int hou_mun; //一小时的价钱

int main(int argv, char** argc)
{
    MESS mess_hand; CHA cha_hand;
    bool* chang;
    chang = (bool*)malloc(sizeof(bool) * (c_num_qu * c_num_lang));
    memset(chang, 0, (c_num_qu * c_num_lang));//初始化


    return 0;
}
