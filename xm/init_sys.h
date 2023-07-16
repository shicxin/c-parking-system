#ifndef __INIT_SYS__
#define __INIT_SYS__

#define PZ_NUM 7      //配置文件条目数量

int user_len = 6; //用户名长度
int paswd_len = 6; //密码长度
int NOW = 0; //程序状态判断
int *init_con = NULL; //初始化变量存储位置
int c_num_qu = 10; //停车场车位
int c_num_lang = 10; //停车场车位
int ten_mun; //十分钟的价钱
int hfh_mun; //半小时的价钱
int hou_mun; //一小时的价钱


void init_sys(MESS*, CHA*, bool*); //初始化系统



#endif
