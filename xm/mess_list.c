#include"mess_list.h"
#include"read_nfs_sfn.h"
#include"sys.h"


/// @brief 新建用户
/// @param head 用户链表
/// @param name 用户名
/// @return 新建成功
bool CreateUser(MESS* head, char * name)
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
            puts("密码修改成功");
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
    scanf("%llf", &node->vue);
    printf("你的密码是%s，账户金额为%.2lf", node->mima, node->vue);
    // 打开文件
    FILE* p_mess;
    if((p_mess = fopen(".\\data\\usr_p", "a")) == NULL)
    {
        printf("Can not open data file usr_p\n");
        exit(0);
    }

    // 将用户信息写入文件
    char s1[CHAR_LONG], s2[CHAR_LONG];
    double_to_str(node->vue, s1);
    int_to_str(node->V, s2);
    fprintf(p_mess, "%s %s %s %s", node->p_n, node->mima, s1, s2);

    // 关闭文件
    fclose(p_mess);

    // 将用户节点插入链表
    node->nxt = head->nxt;
    head->nxt = node;
    
    return 1;
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
        char s1[CHAR_LONG], s2[CHAR_LONG];
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

/// @brief 使用用户名寻找用户
/// @param q 用户链表
/// @param nm 用户名
/// @return 是否找到
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