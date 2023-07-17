#ifndef __SYS__
#define __SYS__

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

#define PZ_NUM 7      //配置文件条目数量
#define CHAR_LONG 20


extern int user_len; //用户名长度
extern int paswd_len; //密码长度
extern int NOW; //程序状态判断
extern int *init_con; //初始化变量存储位置
extern int c_num_qu; //停车场车位
extern int c_num_lang; //停车场车位
extern int ten_mun; //十分钟的价钱
extern int hfh_mun; //半小时的价钱
extern int hou_mun; //一小时的价钱


// #ifndef __USER_LEN__
// #define __USER_LEN__
// int user_len = 6; //用户名长度
// #endif
// #ifndef __PASWD_LEN__
// #define __PASWD_LEN__
// int paswd_len = 6; //密码长度
// #endif
// #ifndef __NNOW__
// #define __NNOW__
// int NOW = 0; //程序状态判断
// #endif
// #ifndef __INIT_CON__
// #define __INIT_CON__
// int *init_con = NULL; //初始化变量存储位置
// #endif
// #ifndef __C_NUM_QU__
// #define __C_NUM_QU__
// int c_num_qu = 10; //停车场车位
// #endif
// #ifndef __C_NUM_LANG__
// #define __C_NUM_LANG__
// int c_num_lang = 10; //停车场车位
// #endif
// #ifndef __TEN__MUN__
// #define __TEN__MUN__
// int ten_mun; //十分钟的价钱
// #endif
// #ifndef __HFH_MUN__
// #define __HFH_MUN__
// int hfh_mun; //半小时的价钱
// #endif
// #ifndef __HOU_MUN
// #define __HOU_MUN
// int hou_mun; //一小时的价钱
// #endif

#endif