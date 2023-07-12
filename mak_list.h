#ifndef __MAK_LIST__
#define __MAK_LIST__
#include<stdbool.h>
#include<time.h>

typedef struct 
{
    char nm[10];
    time_t nx_t, now_t;//上次走的时间，这次来的时间
    struct 
    {
        int x, y;
    }wer;//车辆位置
}CAR;
typedef struct
{
    char p_n[5]; //人名
    // CAR* car; //名下车辆信息
    // int c_num;//车辆数量
    int V; //已结账时长
    double vue; //账号余额
    MESS* nxt, lst;
}MESS;//账户
typedef struct
{
    CAR car;
    CAR* nxt;
}CHA;//停车场
MESS* Mak_Di_chang(MESS* q);//创造链节点（尾插法）
// MESS* Del_Di_chang(MESS* q);//删除链节点
bool Fnd_di_chang_us_pnm(MESS* q, MESS* l);//寻找链节点

MESS* Mak_Di_car(MESS* q);
MESS* Del_Di_car(MESS* q);


#endif