#ifndef __MESS_LIST__
#define __MESS_LIST__

#include<stdbool.h>

typedef struct MESS{
    char p_n[10]; //人名
    char mima[20];
    int V; //已结账时长
    double vue; //账号余额
    struct MESS* nxt;
}MESS; //账户

bool CreateUser(MESS*, char*);//新建用户

// MESS* Del_Di_chang(MESS*);//删除用户

void Print_User_List(MESS*, bool);//遍历用户链表

bool Fnd_di_chang_us_pnm(MESS*, char*);//使用用户名寻找用户

#endif
