//  fprintf(file, "%s", buffer); 
#include <stdio.h>
#include"mak_list.h"

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
    if(l->p_n == q->p_n) return 1;
    return 0;
}


CHA* Mak_Di_car(CAR* q)
{
    CHA* p;
    if((p = (CHA*)malloc(sizeof(CHA))) == NULL)
    {
        puts("Malloc over wen make LIST!!!");
        return 0;
    }
    
    return ;
}
