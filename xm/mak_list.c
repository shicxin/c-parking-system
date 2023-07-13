#include"hello.h"//界面函数
#include"right.h"//复杂的正误判断函数
#include"mak_list.h"//程序数据函数
#include"sys.h"//系统设置函数
#include"money.h"//账目统计相关函数

MESS* Mak_Di_chang(MESS* q, char * nm)
{
    MESS* p;
    if((p = (MESS*)malloc(sizeof(MESS))) == NULL)
    {
        puts("Malloc over wen make LIST!!!");
        return 0;
    }
    // printf("请输入你的名字：");
    // scanf("%s", p->p_n); //char* nm
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
        puts("两次密码不一样（请重新输入）");
    }
    // printf("你与几辆车："); //(最多两辆)：");
    // scanf("%d", p->c_num);
    // p->car = malloc(p->c_num * sizeof(CAR));
    // for(int j = 1; j <= p->c_num; j++)
    // {
    //     printf("第 %d 辆车辆的车牌：", j);
    //     scanf("%s", p->car[j].nm);
    //     p->car[j].now_t = 0;
    //     p->car[j].nx_t = 0;
    // }
    p->lst = NULL;
    p->nxt = q;
    q->lst = p;
    q = p;
    return ;
}

bool Fnd_di_chang_us_pnm(MESS* q, MESS* l)
{
    while(l->p_n != q->p_n && l->nxt->nxt != NULL) l = l->nxt;
    if(strcmp(l->p_n, q->p_n) && strcmp(l->mima, q->mima)) 
    {
        return 1;
    }
    return 0;
}

void look_list_mess(MESS* p)
{
    while(p != NULL)
    {
        printf("你的名字是%s \n你的余额为%llf\n你已经使用时长为%d", p->p_n, p->vue, p->V);
        p = p->nxt;
    }
}

CHA* Mak_Di_car(CHA* q)
{
    CHA* p;
    if((p = (CHA*)malloc(sizeof(CHA))) == NULL)
    {
        puts("Malloc over wen make LIST!!!");
        return 0;
    }
    printf("请输入你的车牌号：");
    scanf("%s", p->car.nm);
    p->nxt = q;
    q = p;
    return ;
}

void look_list_cha(CHA* p)
{
    while(p != NULL)
    {
        printf("车牌号是%s \n车是%点来的\n车在%d区%d号", p->car.nm, p->car.now_t, p->car.wer.x, p->car.wer.y);
        p = p->nxt;
    }
}
