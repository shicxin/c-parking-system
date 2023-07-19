#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<time.h>

#define PZ_NUM 7      //配置文件条目数量

#define CHAR_SIZE 20   //默认常量

//DATA

int user_len = 6; //用户名长度
int paswd_len = 6; //密码长度
int NOW = 0; //程序状态判断
int *init_con = NULL; //初始化变量存储位置
int c_num_qu = 10; //停车场车位x轴
int c_num_lang = 10; //停车场车位y轴
int ten_mun; //十分钟的价钱
int hfh_mun; //半小时的价钱
int hou_mun; //一小时的价钱

// int p_num = 100; // 会员数量

typedef struct CAR{
    char nm[CHAR_SIZE];
    time_t now_t; //来的时间
    struct {
        int x, y;
    }wer; //车辆位置
}CAR;
typedef struct CHA{
    CAR car;
    struct CHA* nxt;
}CHA; //停车场

typedef struct MESS{
    char p_n[CHAR_SIZE]; //人名```````
    char mima[CHAR_SIZE];
    int V; //已结账时长
    double vue; //账号余额
    struct MESS* nxt;
}MESS; //账户

typedef struct WRITEDO{
    char time[CHAR_SIZE];
    struct {
        char nm[CHAR_SIZE];
        bool P_O_C;//人0，车1
        char ADD[CHAR_SIZE];
    }DO; //车辆位置
}WTD;


// DODODO

int read_int(char*);
double read_double(char*);
long long read_longlong(char*);
void int_to_str(int, char*);
void double_to_str(double, char*);
void longlong_to_str(long long, char*);

void Write_Time_And_DO(WTD* );//写入操作
void Use_WTAD(time_t, char*, bool, int);//封装写入操作

void init_sys(MESS*, CHA*, bool*); //初始化系统
void Set_sys(); //设置系统
void Init_Di_mess(FILE*, MESS*);//初始化用户

MESS* Create_User(MESS*, char*);//新建用户
bool Del_User(MESS*, char*);//删除用户
bool Vue_User(MESS*, char*);//充值用户
void Print_User_List(MESS*, bool);//遍历用户链表
MESS* Fnd_di_chang_us_pnm(MESS*, char*);//使用用户名寻找用户

void Init_Di_car(FILE*, CHA*, bool*);//初始化停车场
bool Mak_Di_car(CHA*, bool*);//模拟车来停车场
bool Del_Di_car(MESS*, CHA*, char*);//模拟车出停车场
void Print_Car_List(CHA*, bool);//遍历停车场车信息
CHA* Fnd_di_che_us_cnm(CHA* , char*);
void Chang_car(CAR*, bool*);//为新来的车分配车位
int Fnd_chang(bool* P);//找到空车位，返回车位的抽象空间
int Print_List_Chang(bool*);//遍历停车场场地信息

bool Check_Login(); //密码判断，返回0或1；
bool admin_admin();//登录界面
void He_init(MESS*, CHA*, bool*); //hello界面
void user_hole(MESS*);//用户功能界面
void Car_Com(CHA*, bool*); //车来了，需要车牌号，会为车牌号分配对应的停车位
void Car_Out(CHA*, MESS*); //车走了
void Car_Wer(CHA*); //车在哪

int Read_Timt(time_t*);//读取时间，输出时间，返回与当前时间的差值
long long Now_Time();
// void Count_Money();//计算停车场盈利
double Tran_Mony(double);//出停车场结账


int main()
{
    MESS mess_hand; CHA cha_hand;
    bool* chang;
    chang = (bool*)malloc(sizeof(bool) * (c_num_qu * c_num_lang));
    memset(chang, 0, (c_num_qu * c_num_lang));//初始化
    mess_hand.nxt = NULL;
    cha_hand.nxt = NULL;
    init_sys(&mess_hand, &cha_hand, chang);//全部初始化
    puts("是否查看系统自检数据(0为否)");
    char s[CHAR_SIZE];
    scanf("%s", &s);
    int a = read_int(s);
    if(a) 
    {
        puts("用户账号有如下");
        Print_User_List(&mess_hand, 0);
        puts("停车场现有车信息如下：");
        Print_Car_List(cha_hand.nxt, 0);
        Print_List_Chang(chang);
        puts("停车场总收益3如下");
        system("pause");
    }
    while(NOW != 100)
    {
        He_init(&mess_hand, cha_hand.nxt, chang);
    }
    return 0;
}

/// @brief 用于将一个int类型的值转换为一个字符串，并存储在传入的char*指针所指向的数组中
/// @param i 整数
/// @param s 保存字符串
void int_to_str(int i, char* s)
{
    sprintf(s, "%d", i); 
}

/// @brief 用于将一个double类型的值转换为一个字符串，并存储在传入的char*指针所指向的数组中
/// @param d double
/// @param s 保存字符串
void double_to_str(double d, char* s)
{
    sprintf(s, "%.02lf", d);
}

/// @brief 用于将一个long long类型的值转换为一个字符串，并存储在传入的char*指针所指向的数组中
/// @param ll 
/// @param s 
void longlong_to_str(long long ll, char* s)
{
    sprintf(s, "%lld", ll); 
}

/// @brief 将执行的有关钱的操作写入data\\money
/// @param wtd 写入内容
void Write_Time_And_DO(WTD* wtd)
{
    FILE* fp;
    if((fp = fopen(".\\data\\money", "a")) == NULL)
    {
        printf("Can not open data file system\n");
        exit(0);
    }

    char c[2];
    strcpy(c, wtd->DO.P_O_C ? "1" : "0");

    fprintf(fp, "%s %s %s %s\n", wtd->time, wtd->DO.nm, c, wtd->DO.ADD);

    fclose(fp);
    puts("记账完成！");
    return;
}

/// @brief 封装写文件函数
/// @param T 
/// @param NM 
/// @param X 
/// @param Vue 
void Use_WTAD(time_t T, char* NM, bool X, int Vue)
{
    WTD w;
    longlong_to_str(T, w.time);
    strcpy(w.DO.nm, NM);
    w.DO.P_O_C = X;
    int_to_str(Vue, w.DO.ADD);

    Write_Time_And_DO(&w);
    return;
}

/// @brief 操作用户
/// @param head 用户链表
void user_hole(MESS* head)
{
    puts("**********************************");
    puts("*************1.增加用户************");
    puts("*************2.用户销户************");
    puts("*************3.用户充值************");
    puts("**********************************");

    char c[CHAR_SIZE];
    scanf("%s", c);
    if(strcmp(c, "1"))
    {
        puts("你的名字是");
        scanf("%s", c);
        Create_User(head, c);
    }
    else if(strcmp(c, "2"))
    {
        puts("你的名字是");
        scanf("%s", c);
        Del_User(head, c);
    }
    else if(strcmp(c, "3"))
    {
        puts("你的名字是");
        scanf("%s", c);
        Vue_User(head, c);
    }
    else puts("输入不合法");
    return;
}

/// @brief 从键盘读取一个字符串，并转换为一个int类型的值
/// @return int
int read_int(char* s)
{
    int i;
    i = atoi(s); 
    return i; 
}
/// @brief  从键盘读取一个字符串，并转换为一个double类型的值
/// @return double
double read_double(char* s)
{
    double d;
    // scanf("%s", s);
    d = atof(s);
    return d; // 返回d的值
}

/// @brief 用于将一个字符串转换为一个long long类型的值，并返回该值
/// @param s 存储位置
/// @return long long
long long read_longlong(char* s)
{
    long long ll; 
    ll = atoll(s); 
    return ll; 
}

/// @brief 初始化系统
/// @param peo 用户链表
/// @param cha 停车场的车的列表
/// @param chang 一维数组模拟的停车场
void init_sys(MESS* peo, CHA* cha, bool* chang)
{
    FILE * sys = NULL;
    bool key = 1;
    // 读取基础配置文件
    while(key != 0)
    {
        if((sys = fopen(".\\data\\system", "r")) == NULL)
        {
            printf("Can not open data file system\n");
            exit(0);
        }
        init_con = (int*)malloc(sizeof(int)*PZ_NUM);
        char c[100];
        for(int i = 0; i < PZ_NUM; i++)
        {
            char s[CHAR_SIZE];
            fscanf(sys, "%s %s", c, s);
            init_con[i] = read_int(s);
        }
        user_len = init_con[0];
        paswd_len = init_con[1];
        c_num_qu = init_con[2];
        c_num_lang = init_con[3];
        ten_mun = init_con[4];
        hfh_mun = init_con[5];
        hou_mun = init_con[6];
        free(init_con);
        system("cls");
        puts("******当前系统配置信息如下：*******");
        printf("**管理员账号长度为%d, 密码长度为%d **\n",user_len, paswd_len);
        printf("********现在停车场大小为：%d *****\n", c_num_qu * c_num_lang);
        printf("*******停车每十分钟的价格为：%d  ***\n", ten_mun);
        printf("*******停车每半小时的价格为：%d  ***\n", hfh_mun);
        printf("*******停车每一小时的价格为：%d ***\n", hou_mun);
        puts("***********************************");
        puts("************0.修改*****************");
        puts("*****x.输任意数直接进入系统********");
        puts("***********************************");
        printf("*********请输入：  ****************\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
        fclose(sys); 
        char k[CHAR_SIZE] = {'o'};
        scanf("%s", k);
        if(k[0] == '0')
        {
            Set_sys();
            k[0] = 'o';
        }
        else key = 0;
    }
    puts("系统设置完成");
    // 配置信息设置完
    //开始初始化系统
    // 开始初始化用户
    puts("开始初始化用户");
    if((sys = fopen(".\\data\\usr_p", "r")) == NULL)
    {
        printf("Can not open data file usr_p\n");
        system("pause");
        return;
    }
    int len = 0, i = 0;
    peo->nxt = NULL;
    Init_Di_mess(sys, peo);
    // Print_User_List(peo);
    fclose(sys);
    //开始初始化停车场
    puts("开始初始化停车场");

    if((sys = fopen(".\\data\\usr_ch", "r")) == NULL)
    {
        printf("Can not open data file usr_ch\n");
        system("pause");
        return;
    }
    Init_Di_car(sys, cha, chang);
}

/// @brief 设置系统
void Set_sys()
{
    FILE* fp = NULL;
    if((fp = fopen(".\\data\\system", "r")) == NULL)
    {
        printf("Can not open data file system\n");
        system("pause");
        return;
    }
    char a[PZ_NUM + 1][100];
    int num[PZ_NUM + 1], i = 0;
    for(int i = 1; i < PZ_NUM + 1; i++)
    {
        char s[CHAR_SIZE];
        fscanf(fp, "%s %s", a[i], s);
        num[i] = read_int(s);
        printf("%s %d\n", a[i], num[i]);
    }
    fclose(fp);
    if((fp = fopen(".\\data\\system", "w")) == NULL)
    {
        printf("Can not open data file system\n");
        system("pause");
        return;
    }
    char k[CHAR_SIZE];
    // scanf("%c", k);//读缓冲区中的回车
    for(int i = 1; i < PZ_NUM + 1; i++)
    {
        printf("当前%s为%d，是否需要修改（Y/N, 默认N）:",a[i], num[i] );
        // printf("%s%d\n", a[0], num[0]);
        scanf("%s", k);
        // printf("%s%d\n", a[0], num[0]);
        if(strcmp(k, "Y") == 0)
        {
            printf("需要改为：");
            char s[CHAR_SIZE];
            scanf("%s", s);
            num[i] = read_int(s);
            k[0] = 'O';
        }
        // int_to_str(num[i], s);
        // fprintf(fp, "%s  %s \n",a[i], s );
        fprintf(fp, "%s  %d \n",a[i], num[i] );
    }
    fclose(fp);
}
/// @brief 初始化用户
/// @param fp 用户配置文件
/// @param q 用户链表
/// @return 
void Init_Di_mess(FILE* fp, MESS* q)
{
    char s1[CHAR_SIZE], s2[CHAR_SIZE], s3[CHAR_SIZE], s4[CHAR_SIZE];
    while(fscanf(fp, "%s %s %s %s", s1, s2, s3, s4) != EOF)// q->p_n, q->mima, q->vue, q->V) != EOF)
    {
        // a /= 100;
        // printf("你的名字是%s \n你的密码是%s \n你的余额为%s\n你已经使用时长为%s\n", s1, s2, s3, s4);
        q->nxt = (MESS*)malloc(sizeof(MESS));
        if (q->nxt == NULL) {
            printf("Memory allocation failed.\n");
            break;
        }
        strcpy(q->nxt->p_n, s1);
        strcpy(q->nxt->mima, s2);
        q->nxt->vue = read_double(s3);
        q->nxt->V = read_int(s4);
        q->nxt->nxt = NULL;
        // 移动到下一个节点
        q = q->nxt;
    }
    return ;
}
/// @brief 读取时间
/// @param T 需要翻译的time_t
/// @return 需要翻译的时间与当前的时间差秒数，如果T为空指针，则返回-1
int Read_Timt(time_t* T)
{
    if(T == NULL) // 检查T是否为空指针
    {
        printf("无效的time_t指针\n");
        return -1; // 返回一个错误标志
    }
    struct tm * timeinfo;
    timeinfo = localtime (T);
    char buffer[26];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo); // 将日期和时间格式化为字符串
    printf("车辆入库时间为: %s\n", buffer); //打印格式化的日期和时间字符串
    time_t now = Now_Time();
    return difftime(now, *T); // 返回与当前时间的差值，单位是秒
}

/// @brief 输出并返回当前时间
/// @return 返回时间戳
long long Now_Time()
{
    time_t now = time(NULL); // 获取当前时间
    struct tm * timeinfo;
    timeinfo = localtime(&now);
    char buffer[26];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo); // 将日期和时间格式化为字符串
    printf("现在时间为: %s\n", buffer); //打印格式化的日期和时间字符串
    return now;
}

// void Count_Money();
double Tran_Mony(double T)
{
    int h, fh, m;
    h = T / (60 * 60);
    fh = T / 60 - h * 60;
    m = fh - 30;
    fh /= 30;
    if(m < 0) m = 0;
    else if(m > 10) fh++, m = 0;
    if(fh > 1) fh = 0, h++;

    printf("您的停车时间相当于%d个一小时， %d个半小时，%d个十分钟\n", h, fh, m);

    return h * hou_mun + fh * hfh_mun + m * ten_mun;
}
/// @brief 登录界面与选项界面
/// @param peo 用户链表
/// @param cha 车链表
/// @param P 停车场数组
void He_init(MESS* peo, CHA* cha, bool* P)
{
    char c[10];
    if(NOW <= -3)
    {
        system("cls");
        int i = 100;
        while(i--)
        {
            printf("爆炸爆炸爆炸密码错误爆炸爆炸爆炸爆炸爆炸爆炸爆炸爆炸密码错误爆炸爆炸爆炸爆炸爆炸爆炸爆炸爆炸密码错误爆炸爆炸爆炸爆炸爆炸爆炸爆炸爆炸密码错误爆炸爆炸爆炸爆炸爆炸爆炸爆炸爆炸密码错误爆炸爆炸爆炸爆炸爆炸爆炸爆炸爆炸密码错误爆炸爆炸爆炸爆炸爆炸爆炸爆炸爆炸密码错误爆炸爆炸爆炸爆炸爆炸爆炸爆炸爆炸密码错误爆炸爆炸爆炸爆炸爆炸爆炸爆炸爆炸密码错误爆炸爆炸爆炸爆炸爆炸爆炸爆炸爆炸密码错误爆炸爆炸爆炸爆炸爆炸");
        }
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
        scanf("%s",c);
        if(strcmp(c, "0") == 0)//登录
        {
            if(Check_Login() != 1)
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
        else if(strcmp(c, "1") == 0)
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
        scanf("%s",c);
        if(strcmp(c, "0") == 0)//登录
        {
            if(Check_Login()==0)
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
        puts("*************0.个人业务***********");
        puts("*************1.停车***************");
        puts("*************2.取车***************");
        puts("*************3.查车在哪***********");
        puts("*************4.退出***************");
        puts("*************5.退出程序***********");
        puts("*************6.查看用户***********");
        puts("*************7.查看车辆***********");
        puts("**********************************");
        puts("************10.配置系统***********");
        puts("**********************************");
        printf("请选择程序功能：");
        scanf("%s",c);
        if(strcmp(c, "0") == 0)//结账
        {
            user_hole(peo);
        }
        else if(strcmp(c, "1") == 0)//车来
        {
            Car_Com(cha, P);
        }
        else if(strcmp(c, "2") == 0)//车走
        {
            Car_Out(cha, peo);
            system("pause");
        }
        else if(strcmp(c, "3") == 0)//车在哪
        {
            Car_Wer(cha);
        }
        else if(strcmp(c, "4") == 0)//退出登录
        {
            NOW = 0;
        }
        else if(strcmp(c, "5") == 0)//退出程序
        {
            NOW = 100;
        }
        else if(strcmp(c, "6") == 0)
        {
            Print_User_List(peo, 0);
            system("pause");
        }
        else if(strcmp(c, "7") == 0)
        {
            Print_Car_List(cha, 0);
            system("pause");
        }
        else if(strcmp(c, "10") == 0)
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

/// @brief  该函数用于检查用户输入的用户名和密码
/// @return  是否正确
bool Check_Login()
{
    // 打开文件
    FILE* file = fopen(".\\data\\user_file","r");
    if(file == NULL) // 检查文件是否打开成功
    {
        printf("Can not open write file\n");
        exit(0);
    }
    
    // 读取文件中存储的用户名和密码
    char* username, * password;
    username = (char*)malloc(sizeof(char) * user_len);
    password = (char*)malloc(sizeof(char) * paswd_len);
    fgets(username, user_len, file);
    fgets(password, paswd_len, file);
    
    fclose(file);
    
    // 获取用户输入的用户名和密码
    char name[100], paswd[100];
    puts("请输入用户名：");
    scanf("%s", name);
    puts("请输入密码：");
    scanf("%s", paswd);
    
    // 比较用户名和密码是否匹配
    if(strcmp(paswd, password)==0 && strcmp(name, username)==0)
    {
        // 匹配成功，返回true，并将NOW设为1
        NOW = 1;
        return true;
    }
    else 
    {
        // 匹配失败，返回false，并将NOW减1
        NOW--;
        return false;
    }
}

/// @brief 车来停车场
/// @param q 停车场车辆链表
/// @param P 一维数组模拟的停车场
void Car_Com(CHA* q, bool* P)
{
    if(Mak_Di_car(q, P) == 1)
    {
        puts("你的车入库了！");
    }
    else puts("有问题");
}

/// @brief 初始化停车场
/// @param fp 停车场车辆信息文件
/// @param cha 车辆链表
/// @param P 一维数组模拟的停车场
void Init_Di_car(FILE* fp, CHA* cha, bool* P)
{
    CHA* x;
    // puts("Init_Di_car ing.....");
    x = (CHA*)malloc(sizeof(CHA));
    int i = 0;
    char s1[CHAR_SIZE], s2[CHAR_SIZE], s3[CHAR_SIZE];
    while(fscanf(fp, "%s %s %s %s", x->car.nm, s1, s2, s3) != EOF)
    {
        x->car.now_t = read_longlong(s1);
        x->car.wer.x = read_int(s2), x->car.wer.y = read_int(s3);
        // printf("车牌号是%s \n车是%d来的\n车在%d区%d号\n",x->car.nm, x->car.now_t, x->car.wer.x, x->car.wer.y);
        x->nxt = cha->nxt;
        cha->nxt = x;
        // printf("车在：：：：：：：：：：：：：：：：：：%d\n", x->car.wer.x * c_num_lang + x->car.wer.y);
        P[x->car.wer.x * c_num_lang + x->car.wer.y] = 1;
        x = (CHA*)malloc(sizeof(CHA));
    }
    // puts("Init_Di_car ok");

    return ;
}
/// @brief 模拟车来停车场
/// @param q 停车场车辆链表
/// @param P 一维数组模拟的停车场
/// @return 停车是否成功
bool Mak_Di_car(CHA* q, bool* P)
{
    CHA* p;
    if((p = (CHA*)malloc(sizeof(CHA))) == NULL)
    {
        puts("Malloc over wen make LIST!!!");
        return 0;
    }
    printf("请输入你的车牌号：");
    scanf("%s", p->car.nm);
    Chang_car(&p->car, P);//模拟车入库
    p->nxt = q->nxt;
    q->nxt = p;
    return 1;
}

/// @brief 全局控制车出停车场
/// @param q 停车场停放车链表
/// @param p 人链表
void Car_Out(CHA* car, MESS* peo)
{
    MESS* p = peo;
    CHA* q = car;
    char ma[CHAR_SIZE], nm[CHAR_SIZE];
    puts("你是：");
    scanf("%s", nm);
    MESS* x = Fnd_di_chang_us_pnm(p, nm);
    if(x == NULL)
    {
        puts("你要创建账号吗(创建为0，否则为1)：");
        bool key = 0;
        scanf("%d", &key);
        if(key == 0)
        {
            x = Create_User(p, nm);
            printf("你的密码是%s\n", x->mima);
            printf("账号金额为%.2lf\n", x->vue);
        }
        else 
        {
            puts("你不能走，要付钱\n相付钱，必须创建账号");
            system("pause");
            return ;
        }
    }
    puts("你的密码是：");
    scanf("%s", ma);
    // puts(ma);
    // puts(x->mima);
    if(strcmp(ma, x->mima) != 0)
    {
        puts("密码错误");
        return ;
    }
    puts("车牌号是：");
    CAR xx;
    scanf("%s", xx.nm);
    if(Del_Di_car(x, q, xx.nm)) 
    {
        Print_Car_List(car, 1);
        Print_User_List(peo, 1);
    }
}

/// @brief 使用用户名寻找用户
/// @param q 用户链表
/// @param nm 用户名
/// @return 是否找到
MESS* Fnd_di_chang_us_pnm(MESS* q, char* nm)
{
    while(q->nxt != NULL && strcmp(q->nxt->p_n, nm)) 
    {
        q = q->nxt;// , puts(q->nxt->p_n);
    }
    if(q->nxt != NULL && !strcmp(q->nxt->p_n, nm)) 
    {
        return q->nxt;
    }
    return NULL;
}

/// @brief 模拟车出停车场
/// @param peo 扣款人
/// @param q 停车场现在停着的车
/// @param nm 要出停车场的车
/// @return 出停车场是否成功
bool Del_Di_car(MESS*peo, CHA* k, char* nm)
{
    if(k == NULL) // 没有停车
    {
        puts("停车场内没有车");
        return 0;
    }
    CHA* p = k; // 用一个临时变量来遍历链表
    if(strcmp(p->car.nm, nm) == 0)
    {
        double vue;
        vue = Read_Timt(&p->car.now_t);
        vue = Tran_Mony(vue);
        printf("总金额为：%.02lf\n", vue);
        printf("你卡里还有：%.02lf,是否进行充值？(默认N，y/Y/1为充值)", peo->vue);
        char s[CHAR_SIZE];
        scanf("%s", s);
        if(strcmp(s, "y") == 0 || strcmp(s, "Y") == 0 || strcmp(s, "1") == 0)
        {
            puts("请输入充值金额");
            scanf("%s", s);
            peo->vue += read_int(s);
            Use_WTAD(time(NULL), peo->p_n, 0, vue);
        }
        if(vue > peo->vue)
        {
            puts("钱不够！");
            puts("没有出场！！！");
            return 0;
        }
        else
        {
            peo->vue -= vue;
        }
        free(p); // 释放内存
        Use_WTAD(time(NULL), nm, 1, -vue);//记录操作
        Use_WTAD(time(NULL),peo->p_n, 0, -vue);//记录操作
        printf("你现在还有%.2lf块\n", peo->vue);
        puts("车出停车场了！");
    }
    while(p->nxt != NULL && strcmp(p->nxt->car.nm, nm)) // 找到要出库的车辆或者到达链表尾部
    {
        p = p->nxt;
    }
    if(p->nxt != NULL && strcmp(p->nxt->car.nm, nm) == 0) // 找到了要出库的车辆
    {
        // puts("找到了");
        double vue, vv;
        vv = Read_Timt(&p->nxt->car.now_t); // 计算停车时间
        vue = Tran_Mony(vv); // 计算停车费用
        printf("总金额为：%.02lf\n", vue);
        printf("你卡里还有：%.02lf,是否进行充值？(默认N，y/Y/1为充值)", peo->vue);
        char s[CHAR_SIZE];
        scanf("%s", s);
        if(strcmp(s, "y") == 0 || strcmp(s, "Y") == 0 || strcmp(s, "1") == 0)
        {
            puts("请输入充值金额");
            scanf("%s", s);
            peo->vue += read_int(s);
            Use_WTAD(time(NULL), peo->p_n, 0, vue);
        }
        if(vue > peo->vue)
        {
            puts("钱不够！");
            puts("没有出场！！！");
            return 0;
        }
        else
        {
            peo->vue -= vue;
        }
        CHA* car = p->nxt;
        p->nxt = car->nxt; // 从链表中删除出库的车辆
        free(car); // 释放内存
        Use_WTAD(time(NULL), nm, 1, -vue);//记录操作
        Use_WTAD(time(NULL),peo->p_n, 0, -vue);//记录操作
        printf("你现在还有%.2lf块\n", peo->vue);
        puts("车出停车场了！");
        return 1;
    }
    else // 没有找到要出库的车辆
    {
        puts("没有找到要出库的车辆");
        return 0;
    }
}
/// @brief 使用车牌号找到停车场的车
/// @param q 停车场链表
/// @param nm 车牌号
/// @return 停车场找到的车
CHA* Fnd_di_che_us_cnm(CHA* q, char* nm)
{
    if(strcmp(q->car.nm, nm) == 0) 
    {
        printf("你的车在%d区的%d号停车位上\n", q->car.wer.x, q->car.wer.y);
        return q;
    }
    else 
    {
        while(q->nxt != NULL && strcmp(q->nxt->car.nm, nm)) 
        {
            q = q->nxt;
        }
        if(q->nxt != NULL && !strcmp(q->nxt->car.nm, nm)) 
        {
            printf("你的车在%d区的%d号停车位上\n", q->nxt->car.wer.x, q->nxt->car.wer.y);
            return q->nxt;
        }
    }
    return NULL;
}

void Car_Wer(CHA* q)
{
    char s[10];
    puts("你的车牌号是：");
    scanf("%s", s);
    if( Fnd_di_che_us_cnm(q, s) == NULL)
    {
        puts("你的车不在车库");
    }
    system("pause");
}

/// @brief 新建用户
/// @param head 用户链表
/// @param name 用户名
/// @return 新建成功
MESS* Create_User(MESS* head, char * name)
{
    MESS* node;
    // 分配内存空间
    if((node = (MESS*)malloc(sizeof(MESS))) == NULL)
    {
        puts("Malloc over wen make LIST!!!");
        return 0;
    }
    char password[100], confirm[100];
    bool match = 0;
    while(match == 0)
    {
        printf("请输入你的密码：");
        scanf("%s", password);
        printf("确认你的密码：");
        scanf("%s", confirm);
        if(strcmp(password, confirm) == 0) 
        {
            match = 1;
            puts("设置密码成功");
        }
        else 
        {
            puts("两次密码不一样（请重新输入）");
        }
    }
    // 复制用户名和密码
    strcpy(node->p_n,name);
    strcpy(node->mima, password);
    node->V = 0;
    node->vue = 0;
    printf("你想充值多少：");
    char s1[CHAR_SIZE], s2[CHAR_SIZE];
    scanf("%s", s1);
    node->vue = read_double(s1);
    Use_WTAD(time(NULL), name, 0, node->vue);//记录操作
    // 打开文件
    FILE* p_mess;
    if((p_mess = fopen(".\\data\\usr_p", "a")) == NULL)
    {
        printf("Can not open data file usr_p\n");
        exit(0);
    }

    // 将用户信息写入文件
    double_to_str(node->vue, s1);
    int_to_str(node->V, s2);
    fprintf(p_mess, "%s %s %s %s\n", node->p_n, node->mima, s1, s2);

    // 关闭文件
    fclose(p_mess);

    // 将用户节点插入链表
    node->nxt = head->nxt;
    head->nxt = node;
    // printf("你的密码是%s，账户金额为%.2lf\n", node->mima, node->vue);
    
    return node;
}

/// @brief 删除用户
/// @param head 头结点
/// @param nm 删除人姓名
/// @return 删除是否成功
bool Del_User(MESS* head, char* nm)
{
    if(head == NULL) return 0;
    if(strcmp(head->p_n, nm) == 0)
    {
        printf("一共返还金额%.2lf元", head->vue);
        free(head);
        return 1;
    }
    while(head->nxt != NULL && strcmp(head->p_n, nm) != 0)
    {
        head = head->nxt;
    }
    if(head->nxt != NULL && strcmp(head->p_n, nm) == 0)
    {
        printf("一共返还金额%.2lf元", head->vue);
        MESS* x = head->nxt;
        head->nxt = x->nxt;
        free(x);
        return 1;
    }
    return 0;
}

/// @brief 充值功能
/// @param head 用户链表
/// @param nm 充值人姓名
/// @return 充值是否成功
bool Vue_User(MESS* head, char* nm)
{
    MESS* x = Fnd_di_chang_us_pnm(head, nm);
    puts("你想充值多少：");
    int vue = 0;
    scanf("%d", &vue);
}

/// @brief 遍历用户信息
/// @param head 停车场现有的用户信息
/// @param BOL 判断是否打印到命令行
void Print_User_List(MESS* head, bool BOL)
{
    FILE* fp;
    if((fp = fopen(".\\data\\usr_p", "w")) == NULL)
    {
        printf("Can not open data file usr_p\n");
        exit(0);
    }
    // 遍历用户链表
    while(head->nxt != NULL)
    {
        // 打印用户信息
        char s1[CHAR_SIZE], s2[CHAR_SIZE];
        double_to_str(head->nxt->vue, s1);
        int_to_str(head->nxt->V, s2);
        fprintf(fp, "%s %s %s %s\n", head->nxt->p_n, head->nxt->mima, s1, s2);
        if(!BOL)
        printf("你的名字是%s \n你的余额为%.02llf\n你已经使用时长为%d\n", head->nxt->p_n, head->nxt->vue, head->nxt->V);
        // 移动到下一个节点
        head = head->nxt;
    }
    fclose(fp);
}

/// @brief 遍历停车场车信息
/// @param head 停车场现有的车辆信息
/// @param BOL 判断是否打印到命令行
void Print_Car_List(CHA* head, bool BOL)
{
    FILE* fp;
    if((fp = fopen(".\\data\\usr_ch", "w")) == NULL)
    {
        printf("Can not open data file usr_ch\n");
        exit(0);
    }
    // 遍历车辆链表
    while(head != NULL)
    {
        // 格式化车辆入库时间
        char buffer[26]; // char类型，用于存储格式化后的日期和时间字符串
        struct tm * timeinfo;
        timeinfo = localtime (&head->car.now_t); // 转换为分解时间表示
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
        
        char s1[CHAR_SIZE], s2[CHAR_SIZE], s3[CHAR_SIZE];
        longlong_to_str(head->car.now_t, s1);
        int_to_str(head->car.wer.x, s2);
        int_to_str(head->car.wer.y, s3);

        fprintf(fp, "%s %s %s %s\n", head->car.nm, s1, s2, s3);
        if(!BOL)
        printf("车牌号是%s \n车是%s来的\n车在%d区%d号\n\n", head->car.nm, buffer, head->car.wer.x, head->car.wer.y);

        // 移动到下一个节点
        head = head->nxt;
    }
    fclose(fp);
}
/// @brief 使用二维图形展示停车场
/// @param a 
/// @return 
int Print_List_Chang(bool* a)
{
    int b1 = 0, b2 = 0;
    for(int i = 0; i < c_num_qu; i++)
    {
        for(int j = 0; j < c_num_lang; j++)
        {
            printf(a[i * c_num_lang + j] == 1 ? "# " : "* ");
            a[i * c_num_lang + j] == 1 ? b1++ : b2++;
        }
        printf("\n");
    }
    printf("现在有%d辆车\n", b1);
    return b2;
}

/// @brief 该函数用于将车辆信息写入文件，并打印停车位和入库时间
/// @param car 停车场车辆链表
/// @param change 
void Chang_car(CAR* car, bool* change)
{
    // 调用Fnd_chang函数找到一个可用的停车位
    int index = Fnd_chang(change);
    if(index != 0)
    {
        // 更新车辆信息
        car->wer.x = index / 10;
        car->wer.y = index % 10;
        time(&car->now_t);
        // 打开文件
        FILE* file = fopen(".\\data\\usr_ch", "a");

        Use_WTAD(car->now_t, car->nm, 1, 0);//记录操作

        if(file == NULL) // 检查文件是否打开成功
        {
            printf("Can not open data file system\n");
            exit(0);
        }
        // 将车辆信息写入文件
        char s1[CHAR_SIZE], s2[CHAR_SIZE], s3[CHAR_SIZE];
        longlong_to_str(car->now_t, s1);
        // long long time = car->now_t;
        int_to_str(car->wer.x, s2);
        int_to_str(car->wer.y, s3);
        // int x = car->wer.x, y = car->wer.y;
        fprintf(file, "%s %s %s %s\n", car->nm, s1, s2, s3);
        // 关闭文件
        fclose(file);
        
        // 打印停车位信息
        printf("你的车在%d区%d号停车位\n", car->wer.x, car->wer.y);
        
        // 打印入库时间信息
        struct tm * timeinfo;
        timeinfo = localtime (&car->now_t);
        char buffer[26];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo); // 将日期和时间格式化为字符串
        printf("车辆入库时间为: %s\n", buffer); //打印格式化的日期和时间字符串
        
        system("pause");
        return ;
    }
    else 
    {
        puts("你的车没位置了");
        return;
    }
}
/// @brief 找到空车位
/// @param P 停车场抽象数组
/// @return 位置 X*Y
int Fnd_chang(bool* P)
{
    for(int i = 0; i < c_num_qu * c_num_lang; i++)
    {
        if(P[i] == 0)
        {
            P[i] = 1; 
            return i;
        }
    }
    return -1;
}

