#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<time.h>

#define PZ_NUM 6      //配置文件条目数量

int user_len = 6; //用户名长度
int paswd_len = 6; //密码长度
int NOW = 0; //程序状态判断
int *init_con = NULL; //初始化变量存储位置
int n = 100; //停车场车位
int ten_mun; //十分钟的价钱
int hfh_mun; //半小时的价钱
int hou_mun; //一小时的价钱

int nn = 100; // 会员数量

typedef struct
{
    char*peo,*car; //人名、车牌号
    bool V; //会员
    double vue;
    struct 
    {
        int x, y;
    }wer;
}mess;


bool IsRight(); //密码判断，返回0或1；
void init_sys(char**plc); //初始化系统
int read_f_num(FILE*fp); //读取配置文件中的数字，
void He_init(); //hello界面

void Car_Com(); //车来了，需要车牌号，会为车牌号分配对应的停车位
void Car_Out(); //车走了
void Car_Wer(); //车在哪
void Set_sys(); //设置系统


//
int main()
{
    //while(NOW != 100)
    //{
        //He_init();
    //}
    //puts("欢迎管理员");
    //system("pause");
    //IsRight();
    //He_init();
    char**park;
    init_sys(park);
    return 0;
}

void Car_Com()
{

}

int read_f_num(FILE*fp)
{
    char s[100];
    int num=0;
    fgets(s, 100, fp);
    //printf("%s\t",s);
    int n = strlen(s);
    if(s[0] != '\n')
    {
        //if(s[n-1]=='\n')n-=1;
        //printf("thisis%d:\t",n);
        for(int i=0; i <= n; i++, num *= 10)
        {
            if(s[i] <= '9'&&s[i] >= '0')
            {
                num += (s[i]-'0');
                //printf("the%dis%c\t",i,s[i]);
            }
            else num /= 10;
        }
        num /= 10;
    }
    //printf("%d\n",num);
    return num;
}

void init_sys(char**plc)
{
    FILE * sys = NULL;
    if((sys = fopen(".\\data\\system", "r")) == NULL)
    {
        printf("Can not open data file system\n");
        exit(0);
    }
    init_con = (int*)malloc(sizeof(int)*PZ_NUM);
    for(int i = 0; i < PZ_NUM; i++)
    {
        init_con[i] = read_f_num(sys);
    }
    user_len = init_con[0];
    paswd_len = init_con[1];
    n = init_con[2];
    ten_mun = init_con[3];
    hfh_mun = init_con[4];
    hou_mun = init_con[5];
    // printf("%d\n",user_len);
    fclose(sys); // 配置信息读完

    if((sys = fopen(".\\data\\usr_p", "r")) == NULL)
    {
        printf("Can not open data file usr_p\n");
        exit(0);
    }
    int i = 0;
    while(fscanf(sys, "%s %d", s, &a) != EOF)
    {}
}

void He_init()
{
    int c;
    if(NOW <= -3)
    {
        system("cls");
        puts("爆炸爆炸爆炸密码错误爆炸爆炸爆炸爆炸爆炸");
        puts("爆炸爆炸爆炸密码错误爆炸爆炸爆炸爆炸爆炸");
        puts("爆炸爆炸爆炸密码错误爆炸爆炸爆炸爆炸爆炸");
        puts("爆炸爆炸爆炸密码错误爆炸爆炸爆炸爆炸爆炸");
        puts("爆炸爆炸爆炸密码错误爆炸爆炸爆炸爆炸爆炸");
        puts("爆炸爆炸爆炸密码错误爆炸爆炸爆炸爆炸爆炸");
        puts("爆炸爆炸爆炸密码错误爆炸爆炸爆炸爆炸爆炸");
        puts("爆炸爆炸爆炸密码错误爆炸爆炸爆炸爆炸爆炸");
        puts("爆炸爆炸爆炸密码错误爆炸爆炸爆炸爆炸爆炸");
        puts("爆炸爆炸爆炸密码错误爆炸爆炸爆炸爆炸爆炸");
        NOW = 100;
        return;
    }
    else if(NOW ==0)
    {
        system("cls");
        puts("***********************************");
        puts("***********0.请登录****************");
        puts("***********1.退出******************");
        puts("***********************************");
        printf("请选择程序功能：");
        scanf("%d",&c);
        if(c==0)//登录
        {
            if(IsRight() != 1)
            {
                puts("密码错误");
                system("pause");
                //system("pause");
            }
            else
            {
                puts("欢迎管理员");
                system("pause");
            }
        }
        else if(c==1)
        {
            NOW=100;
        }
        else
        {
            puts("输入格式有问题");
            system("pause");
        }
    }
    else if(NOW<0)
    {
        system("cls");
        puts("*******密码错误三次将爆炸***********");
        puts("***********0.请登录****************");
        puts("***********0.请登录****************");
        puts("***********密码错误****************");
        printf("***********已错误%d次***************\n",-NOW);
        printf("请选择程序功能：");
        scanf("%d",&c);
        if(c==0)//登录
        {
            if(IsRight()==0)
            {
                puts("密码错误");
                system("pause");
            }
            else
            {
                puts("欢迎管理员");
                system("pause");
            }
        }
        else
        {
            puts("输入有问题");
            system("pause");
        }
    }
    else
    {
        system("cls");
        puts("**********************************");
        puts("*************0.卡内充值***********");
        puts("*************1.停车***************");
        puts("*************2.取车***************");
        puts("*************3.查车在哪***********");
        puts("*************4.退出***************");
        puts("*************5.退出程序***********");
        puts("*************6.配置系统***********");
        puts("**********************************");
        printf("请选择程序功能：");
        scanf("%d",&c);
        if(c == 0)//结账
        {}
        else if(c == 1)//车来
        {
            Car_Com();
        }
        else if(c == 2)//车走
        {
            Car_Out();
        }
        else if(c == 3)//车在哪
        {
            Car_Wer();
        }
        else if(c == 4)//退出登录
        {
            NOW=0;
        }
        else if(c == 5)//退出程序
        {
            NOW=100;
        }
        else if(c == 6)
        {
            Set_sys();
        }
        else
        {
            puts("输入有问题");
            system("pause");
        }
    } 
}

bool IsRight()
{
    bool key = 0;
    FILE* fp;
    char* user_name,* user_paswd;
    user_name = (char*)malloc(user_len*sizeof(char));
    user_paswd = (char*)malloc(paswd_len*sizeof(char));
    if((fp = fopen(".\\data\\user_file","r")) == NULL)
    {
        printf("Cannotopenwritefile\n");
        exit(0);
    }
    char* name,* paswd;
    name = (char*)malloc(100*sizeof(char));
    paswd = (char*)malloc(100*sizeof(char));
    puts("请输入用户名：");
    scanf("%s", name);
    puts("请输入密码：");
    scanf("%s", paswd);
    fgets(user_name, user_len, fp);
    fgets(user_paswd, paswd_len, fp);

    //puts(name);
    //puts(user_name);
    //puts(paswd);
    //puts(user_paswd);

    //puts(strcmp(name,user_name)==0?"1":"0");
    //puts(strcmp(paswd,user_paswd)==0?"1":"0");
    if(strcmp(paswd, user_paswd)==0&&strcmp(name, user_name)==0)key=1;
    else key=0;
    free(name);
    free(user_name);
    free(paswd);
    free(user_paswd);
    fclose(fp);
    key==0?(NOW--):(NOW=1);
    //printf("%d", NOW);//输出错误次数
    return key;
}