#ifndef __CHA_LIST__
#define __CHA_LIST__

typedef struct CAR{
    char nm[10];
    time_t now_t; //来的时间
    struct {
        int x, y;
    }wer; //车辆位置
}CAR;

typedef struct CHA{
    CAR car;
    struct CHA* nxt;
}CHA; //停车场



bool Mak_Di_car(CHA*, bool*);//模拟车来停车场

bool Del_Di_car(CHA*, char*);//模拟车出停车场

void Print_Car_List(CHA*, bool);//遍历停车场车信息

bool Fnd_di_che_us_cnm(CHA* , char*);//使用车牌号找车

void Chang_car(CAR*, bool*);//为新来的车分配车位

int Fnd_chang(bool* P);//找到空车位，返回车位的抽象空间

int Print_List_Chang(bool*);//遍历停车场场地信息

#endif
