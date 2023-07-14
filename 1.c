#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<time.h>

#define PZ_NUM 7      //配置文件条目数量

//DATA

int user_len = 6; //用户名长度
int paswd_len = 6; //密码长度
int NOW = 0; //程序状态判断
int *init_con = NULL; //初始化变量存储位置
int c_num_qu = 10; //停车场车位
int c_num_lang = 10; //停车场车位
int ten_mun; //十分钟的价钱
int hfh_mun; //半小时的价钱
int hou_mun; //一小时的价钱

int p_num = 100; // 会员数量


typedef struct CAR{
    char nm[10];
    time_t now_t; //来的时间
    struct {
        int x, y;
    }wer; //车辆位置
}CAR;

typedef struct MESS{
    char p_n[10]; //人名```````
    char mima[20];
    int V; //已结账时长
    double vue; //账号余额
    struct MESS* nxt;
}MESS; //账户

typedef struct CHA{
    CAR car;
    struct CHA* nxt;
}CHA; //停车场

// CHA cha;
// MESS peo;


// DODODO

void init_sys(MESS*, CHA*, bool*); //初始化系统
void Set_sys(); //设置系统

bool Init_Di_mess(FILE*, MESS*);//初始化用户
bool Mak_Di_chang(MESS*, char*);//新建用户
// MESS* Del_Di_chang(MESS*);//删除用户
void look_list_mess(MESS*);//遍历用户链表
bool Fnd_di_chang_us_pnm(MESS*, char*);//使用用户名寻找用户

bool Init_Di_car(FILE*, CHA*, bool*);//初始化停车场
bool Mak_Di_car(CHA*, bool*);//模拟车来停车场
bool Del_Di_car(CHA*, char*);//模拟车出停车场
void look_list_car(CHA*);//遍历停车场车信息
bool Fnd_di_che_us_cnm(CHA* , char*);
void Chang_car(CAR*, bool*);//为新来的车分配车位
int Fnd_chang(bool* P);//找到空车位，返回车位的抽象空间
int look_list_chang(bool*);//遍历停车场场地信息

bool IsRight(); //密码判断，返回0或1；
int read_f_num(FILE*); //读取配置文件中的数字，
void He_init(MESS*, CHA*, bool*); //hello界面

void Car_Com(CHA*, bool*); //车来了，需要车牌号，会为车牌号分配对应的停车位
void Car_Out(CHA*, MESS*); //车走了
void Car_Wer(CHA*); //车在哪

time_t Read_C_Timt(time_t*);//读取时间，输出时间，返回与当前时间的差值
void Count_Money();//计算停车场盈利
double Tran_Mony(time_t*);//出停车场结账


int main()
{
    MESS mess_hand; CHA cha_hand;
    bool* chang;
    chang = (bool*)malloc(sizeof(bool) * (c_num_qu * c_num_lang));
    memset(chang, 0, (c_num_qu * c_num_lang));//初始化
    mess_hand.nxt = NULL;
    cha_hand.nxt = NULL;
    init_sys(&mess_hand, &cha_hand, chang);//全部初始化
    puts("是否查看系统自检数据");
    int a;
    scanf("%d", &a);
    if(a) 
    {
        puts("用户账号有如下");
        look_list_mess(&mess_hand);
        puts("停车场现有车信息如下：");
        look_list_car(cha_hand.nxt);
        look_list_chang(chang);
        puts("停车场总收益3如下");
        system("pause");
    }
    while(NOW != 100)
    {
        He_init(&mess_hand, cha_hand.nxt, chang);
    }
    return 0;
}

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
            fscanf(sys, "%s %d", c,&init_con[i]);
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
        char k[1] = {'o'};
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
    // look_list_mess(peo);
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
    // puts("OVER!");
}

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
        fscanf(fp, "%s %d", a[i], &num[i]);
        printf("%s%d\n", a[i], num[i]);
    }
    fclose(fp);
    if((fp = fopen(".\\data\\system", "w")) == NULL)
    {
        printf("Can not open data file system\n");
        system("pause");
        return;
    }
    char k[1];
    // scanf("%c", k);//读缓冲区中的回车
    for(int i = 1; i < PZ_NUM + 1; i++)
    {
        printf("当前%s为%d，是否需要修改（Y/N, 默认N）:",a[i], num[i] );
        // printf("%s%d\n", a[0], num[0]);
        scanf("%s", k);
        // printf("%s%d\n", a[0], num[0]);
        num[0] = 6;
        if(k == "Y")
        {
            printf("需要改为：");
            scanf("%d", &num[i]);
            k[0] = 'O';
        }
        fprintf(fp, "%s  %d \n",a[i], num[i] );
    }
    fclose(fp);
}

bool Init_Di_mess(FILE* fp, MESS* q)
{
    // q->nxt = (MESS*)malloc(sizeof(MESS));
    // q = q->nxt;
    MESS* X = (MESS*)malloc(sizeof(MESS));
    X->nxt = NULL;
    char s1[10], s2[10];
    double a; int b;
    while(fscanf(fp, "%s %s %lf %d", s1, s2, &a, &b) != EOF)// q->p_n, q->mima, q->vue, q->V) != EOF)
    {
        // printf("你的名字是%s \n你的密码是%s \n你的余额为%lf\n你已经使用时长为%d\n", s1, s2, a, b);
        strcpy(X->p_n, s1);
        strcpy(X->mima, s2);
        X->vue = a;
        X->V = b;
        // printf("你的名字是%s \n你的密码是%s \n你的余额为%lf\n你已经使用时长为%d\n",q->p_n, q->mima, q->vue, q->V);
        X->nxt = q->nxt;
        q->nxt = X;
        X = (MESS*)malloc(sizeof(MESS));
        // system("pause");
    }
    return 1;
}

time_t Read_C_Timt(time_t* T)
{
    time_t x = time(NULL);
    struct tm * timeinfo;
    timeinfo = localtime (T);
    char buffer[26];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo); // 将日期和时间格式化为字符串
    printf("车辆入库时间为: %s\n", buffer); //打印格式化的日期和时间字符串
    return x - *T;
}

void Count_Money();
double Tran_Mony(time_t* T)
{
    int h, fh, m;
    h = *T / (60 * 60);
    fh = *T / 60 - h * 60;
    m = fh - 30;
    fh /= 30;
    if(m < 0) m = 0;
    else if(m > 10) fh++;

    return h * hou_mun + fh * hfh_mun + m * ten_mun;
}
void He_init(MESS* peo, CHA* cha, bool* P)
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
        puts("*************6.查看用户***********");
        puts("*************7.查看车辆***********");
        puts("**********************************");
        puts("************10.配置系统***********");
        puts("**********************************");
        printf("请选择程序功能：");
        scanf("%d",&c);
        if(c == 0)//结账
        {}
        else if(c == 1)//车来
        {
            Car_Com(cha, P);
        }
        else if(c == 2)//车走
        {
            Car_Out(cha, peo);
            system("pause");
        }
        else if(c == 3)//车在哪
        {
            Car_Wer(cha);
        }
        else if(c == 4)//退出登录
        {
            NOW = 0;
        }
        else if(c == 5)//退出程序
        {
            NOW = 100;
        }
        else if(c == 6)
        {
            look_list_mess(peo);
            system("pause");
        }
        else if(c == 7)
        {
            look_list_car(cha);
            system("pause");
        }
        else if(c == 10)
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
        printf("Cap_numotopenwritefile\n");
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

    if(strcmp(paswd, user_paswd)==0&&strcmp(name, user_name)==0)key=1;
    else key=0;

    free(name);
    free(user_name);
    free(paswd);
    free(user_paswd);
    fclose(fp);
    key==0?(NOW--):(NOW=1);

    return key;
}

void Car_Com(CHA* q, bool* P)
{
    if(Mak_Di_car(q, P) == 1)
    {
        puts("你的车以入库！");
    }
    else puts("有问题");
}
bool Init_Di_car(FILE* fp, CHA* cha, bool* P)
{
    CHA* x;
    x = (CHA*)malloc(sizeof(CHA));
    int i = 0;
    while(fscanf(fp, "%s %lld %d %d", x->car.nm, &x->car.now_t, &x->car.wer.x, &x->car.wer.y) != EOF)
    {
        // printf("车牌号是%s \n车是%d来的\n车在%d区%d号\n",x->car.nm, x->car.now_t, x->car.wer.x, x->car.wer.y);
        x->nxt = cha->nxt;
        cha->nxt = x;
        // printf("车在：：：：：：：：：：：：：：：：：：%d\n", x->car.wer.x * c_num_lang + x->car.wer.y);
        P[x->car.wer.x * c_num_lang + x->car.wer.y] = 1;
        x = (CHA*)malloc(sizeof(CHA));
    }
    // puts("Init_Di_car ok");
    return i;
}
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

void Car_Out(CHA* q, MESS* p)
{
    char ma[10], nm[10];
    puts("你是：");
    scanf("%s", nm);
    puts("你的密码是：");
    scanf("%s", ma);
    if(Fnd_di_chang_us_pnm(p, nm) == 0)
    {
        puts("你要创建账号吗(创建为0，否则为1)：");
        bool key = 0;
        scanf("%d", &key);
        if(key == 0)
        {
            Mak_Di_chang(p, nm);
        }
        else 
        {
            puts("你不能走，要付钱\n相付钱，必须创建账号");
            system("pause");
            return ;
        }
    }
    puts("车牌号是：");
    CAR x;
    scanf("%s", x.nm);
    bool Del_Di_car(q);
}

bool Fnd_di_chang_us_pnm(MESS* q, char* nm)
{
    while(q->nxt != NULL && strcmp(q->nxt->p_n, nm)) 
    {
        q = q->nxt;// , puts(q->nxt->p_n);
    }
    if(q->nxt != NULL && !strcmp(q->nxt->p_n, nm)) 
    {
        return 1;
    }
    return 0;
}

bool Del_Di_car(CHA* q, char* nm)
{
    if(q->nxt == NULL)
    {
        puts("停车场内没有车");
    }
    else 
    {
        while(q->nxt->nxt != NULL && strcmp(q->nxt->car.nm, nm))
        {
            q->nxt = q->nxt->nxt;
        }
        if(q->nxt->nxt != NULL && !strcmp(q->nxt->car.nm, nm))
        {
            int vue = Read_C_Timt(&q->car.now_t);
            vue = Tran_Mony((time_t*)&vue);
            CHA* x = q->nxt;
            q->nxt = q->nxt->nxt;
            free(x);
            puts("车出停车场了！");
            return 1;
        }
        else puts("没出去");
        system("pause");
    }
    return 0;
}

bool Fnd_di_che_us_cnm(CHA* q, char* nm)
{
    if(strcmp(q->car.nm, nm) == 0) 
    {
        printf("你的车在%d区的%d号停车位上\n", q->car.wer.x, q->car.wer.y);
        return 1;
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
            return 1;
        }
    }
    return 0;
}

void Car_Wer(CHA* q)
{
    char s[10];
    puts("你的车牌号是：");
    scanf("%s", s);
    if( Fnd_di_che_us_cnm(q, s) == 0)
    {
        puts("你的车不在车库");
    }
    system("pause");
}

bool Mak_Di_chang(MESS* q, char * nm)
{
    MESS* p;
    if((p = (MESS*)malloc(sizeof(MESS))) == NULL)
    {
        puts("Malloc over wen make LIST!!!");
        return 0;
    }
    char s[100], c[100];
    bool key = 0;
    while(key == 0)
    {
        printf("请输入你的密码：");
        scanf("%s", s);
        printf("确认你的密码：");
        scanf("%s", c);
        if(strcmp(s, c) == 0) 
        {
            key = 1;
            puts("密码修改成功");
        }
        else puts("两次密码不一样（请重新输入）");
    }
    strcpy(p->p_n,nm);
    strcpy(p->mima, s);
    p->V = 0;
    p->vue = 0;
    // if(strcmp(c, p->mima))puts("no OK");
    p->nxt = q->nxt;
    q->nxt = p;
    return 1;
}

void look_list_mess(MESS* p)
{
    // for(int i = 0; i < 3; i++)
    while(p->nxt != NULL)
    {
        printf("你的名字是%s \n你的余额为%llf\n你已经使用时长为%d\n", p->nxt->p_n, p->nxt->vue, p->nxt->V);
        p = p->nxt;
    }
}

void look_list_car(CHA* p)
{
    while(p != NULL)
    {
        char buffer[26]; // char类型，用于存储格式化后的日期和时间字符串
        struct tm * timeinfo;
        timeinfo = localtime (&p->car.now_t); // 转换为分解时间表示
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
        printf("车牌号是%s \n车是%s来的\n车在%d区%d号\n\n", p->car.nm, buffer, p->car.wer.x, p->car.wer.y);
        p = p->nxt;
    }
}
int look_list_chang(bool* a)
{
    int b1 = 0, b2 = 0;
    for(int i = 0; i < c_num_qu; i++)
    {
        for(int j = 0; j < c_num_lang; j++)
        {
            printf(a[i * c_num_lang + j] == 1 ? "* " : "# ");
            a[i * c_num_lang + j] == 1 ? b1++ : b2++;
        }
        printf("\n");
    }
    printf("现在有%d辆车\n", b1);
    return b2;
}

int read_f_num(FILE* fp)
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

void Chang_car(CAR* p, bool* chang)
{
    int x = Fnd_chang(chang);
    if(x != 0)
    {
        p->wer.x = x / 10;
        p->wer.y = x % 10;
        printf("你的车在%d区%d号停车位", p->wer.x, p->wer.y);
        time(&p->now_t);
        Read_C_Timt(&p->now_t);
        system("pause");
        return ;
    }
    else puts("你的车没位置了");
    return;
}

int Fnd_chang(bool* P)
{
    for(int i = 1; i <= 100; i++)
    {
        if(P[i] == 0)
        {
            P[i] = 1; 
            return i;
        }
    }
    return 0;
}

