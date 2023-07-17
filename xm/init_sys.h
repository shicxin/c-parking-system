#ifndef __INIT_SYS__
#define __INIT_SYS__

void init_sys(MESS*, CHA*, bool*); //初始化系统

void Init_Di_mess(FILE*, MESS*);//初始化用户

void Init_Di_car(FILE*, CHA*, bool*);//初始化停车场

bool Check_Login(); //密码判断，返回0或1；

void He_init(MESS*, CHA*, bool*); //hello界面


bool Check_Login(); //密码判断，返回0或1；

void He_init(MESS*, CHA*, bool*); //hello界面

void Car_Com(CHA*, bool*); //车来了，需要车牌号，会为车牌号分配对应的停车位

void Car_Out(CHA*, MESS*); //车走了

void Car_Wer(CHA*); //车在哪

#endif
