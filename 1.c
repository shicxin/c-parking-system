#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<time.h>

#define PZ_NUM 6      //�����ļ���Ŀ����

//DATA

int user_len = 6; //�û�������
int paswd_len = 6; //���볤��
int NOW = 0; //����״̬�ж�
int *init_con = NULL; //��ʼ�������洢λ��
int c_num = 100; //ͣ������λ
int ten_mun; //ʮ���ӵļ�Ǯ
int hfh_mun; //��Сʱ�ļ�Ǯ
int hou_mun; //һСʱ�ļ�Ǯ

int p_num = 100; // ��Ա����

bool chang[101] = {1};

typedef struct CAR{
    char nm[10];
    time_t nx_t, now_t; //�ϴ��ߵ�ʱ�䣬�������ʱ��
    struct {
        int x, y;
    }wer; //����λ��
}CAR;

typedef struct MESS{
    char p_n[10]; //����```````
    char mima[20];
    int V; //�ѽ���ʱ��
    double vue; //�˺����
    struct MESS* nxt;
}MESS; //�˻�

typedef struct CHA{
    CAR car;
    struct CHA* nxt;
}CHA; //ͣ����

CHA cha;
MESS peo;


// DODODO

void init_sys(MESS*, CHA*); //��ʼ��ϵͳ
void Set_sys(CHA*); //����ϵͳ

bool Mak_Di_chang(MESS*, char*);//�½��û�
bool Init_Di_chang(FILE*, MESS*);
// MESS* Del_Di_chang(MESS*);//ɾ���û�
bool Fnd_di_chang_us_pnm(MESS*, char*);//Ѱ�����ڵ�

bool Mak_Di_car(CHA*);//ģ�⳵��ͣ����
bool Del_Di_car(CHA*, char*);//ģ�⳵��ͣ����
void look_list_mess(MESS*);//�����û�����

bool IsRight(); //�����жϣ�����0��1��
int read_f_num(FILE*); //��ȡ�����ļ��е����֣�
void He_init(); //hello����

void Car_Com(CHA*); //�����ˣ���Ҫ���ƺţ���Ϊ���ƺŷ����Ӧ��ͣ��λ
void Car_Out(CHA*, MESS*); //������
void Car_Wer(CHA*); //������
void Chang_car(CAR*);//Ϊ�����ĳ����䳵λ
int Fnd_chang();//�ҵ��ճ�λ�����س�λ�ĳ���ռ�


int main()
{
    MESS p; CHA q;
    p.nxt = NULL;
    q.nxt = NULL;
    init_sys(&p, &q);
    // while(NOW != 100)
    // {
    //     He_init();
    // }
    // return 0;
}

void init_sys(MESS* peo, CHA* cha)
{
    FILE * sys = NULL;
    // ��ȡ���������ļ�
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
    c_num = init_con[2];
    ten_mun = init_con[3];
    hfh_mun = init_con[4];
    hou_mun = init_con[5];
    system("cls");
    puts("******��ǰϵͳ������Ϣ���£�*******");
    printf("**����Ա�˺ų���Ϊ%d, ���볤��Ϊ%d **\n",user_len, paswd_len);
    printf("********����ͣ������СΪ��%d *****\n", c_num);
    printf("*******ͣ��ÿʮ���ӵļ۸�Ϊ��%d  ***\n", ten_mun);
    printf("*******ͣ��ÿ��Сʱ�ļ۸�Ϊ��%d  ***\n", hfh_mun);
    printf("*******ͣ��ÿһСʱ�ļ۸�Ϊ��%d ***\n", hou_mun);
    puts("***********************************");
    puts("************0.�޸�*****************");
    puts("*****x.��������ֱ�ӽ���ϵͳ********");
    puts("***********************************");
    printf("*********�����룺  ****************\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
    int k = 0;
    scanf("%d", &k);
    if(k == 0)
    {}
    puts("ϵͳ�������");
    fclose(sys); 
    // ������Ϣ������
    //��ʼ��ʼ��ϵͳ
    if((sys = fopen(".\\data\\usr_p", "r")) == NULL)
    {
        printf("Can not open data file usr_p\n");
        system("pause");
        return;
    }
    int len = 0, i = 0;
    peo->nxt = NULL;
    Init_Di_chang(sys, peo);
    // look_list_mess(peo);
    for(i = 0; i < len; i++)
    {
        // printf("�û�����%s ������%s �ϴ�����ʱ�䣺%d �������ʱ�䣨����ͣ����ʱ��Ϊ0����%d ��ͣʱ����%d  �˻���%llf λ��x��%d λ��y��%d", peo[i].peo, peo[i].car.nm, peo[i].car.nx_t, peo[i].car.now_t, peo[i].V, peo[i].vue, peo[i].wer.x, peo[i].wer.y); //��ȡ �û��� ���� �ϴ�����ʱ�� �������ʱ�䣨����ͣ����ʱ��Ϊ0�� ��ͣʱ�� �˻���� λ��x λ��y
    }
}

bool Init_Di_chang(FILE* fp, MESS* q)
{
    q->nxt = (MESS*)malloc(sizeof(MESS));
    q = q->nxt;
    q->nxt = NULL;
    char s1[10], s2[10];
    double a; int b;
    while(fscanf(fp, "%s %s %lf %d", s1, s2, &a, &b) != EOF)// q->p_n, q->mima, q->vue, q->V) != EOF)
    {
        // printf("���������%s \n���������%s \n������Ϊ%lf\n���Ѿ�ʹ��ʱ��Ϊ%d\n", s1, s2, a, b);
        strcpy(q->p_n, s1);
        strcpy(q->mima, s2);
        q->vue = a;
        q->V = b;
        // printf("���������%s \n���������%s \n������Ϊ%lf\n���Ѿ�ʹ��ʱ��Ϊ%d\n",q->p_n, q->mima, q->vue, q->V);
        q->nxt = (MESS*)malloc(sizeof(MESS));
        q = q->nxt;
        q->nxt = NULL;
        system("pause");
    }
    return 1;
}

void He_init()
{
    int c;
    if(NOW <= -3)
    {
        system("cls");
        puts("��ը��ը��ը�������ը��ը��ը��ը��ը");
        puts("��ը��ը��ը�������ը��ը��ը��ը��ը");
        puts("��ը��ը��ը�������ը��ը��ը��ը��ը");
        puts("��ը��ը��ը�������ը��ը��ը��ը��ը");
        puts("��ը��ը��ը�������ը��ը��ը��ը��ը");
        puts("��ը��ը��ը�������ը��ը��ը��ը��ը");
        puts("��ը��ը��ը�������ը��ը��ը��ը��ը");
        puts("��ը��ը��ը�������ը��ը��ը��ը��ը");
        puts("��ը��ը��ը�������ը��ը��ը��ը��ը");
        puts("��ը��ը��ը�������ը��ը��ը��ը��ը");
        NOW = 100;
        return;
    }
    else if(NOW ==0)
    {
        system("cls");
        puts("***********************************");
        puts("***********0.���¼****************");
        puts("***********1.�˳�******************");
        puts("***********************************");
        printf("��ѡ������ܣ�");
        scanf("%d",&c);
        if(c==0)//��¼
        {
            if(IsRight() != 1)
            {
                puts("�������");
                system("pause");
                //system("pause");
            }
            else
            {
                puts("��ӭ����Ա");
                system("pause");
            }
        }
        else if(c==1)
        {
            NOW=100;
        }
        else
        {
            puts("�����ʽ������");
            system("pause");
        }
    }
    else if(NOW<0)
    {
        system("cls");
        puts("*******����������ν���ը***********");
        puts("***********0.���¼****************");
        puts("***********0.���¼****************");
        puts("***********�������****************");
        printf("***********�Ѵ���%d��***************\n",-NOW);
        printf("��ѡ������ܣ�");
        scanf("%d",&c);
        if(c==0)//��¼
        {
            if(IsRight()==0)
            {
                puts("�������");
                system("pause");
            }
            else
            {
                puts("��ӭ����Ա");
                system("pause");
            }
        }
        else
        {
            puts("����������");
            system("pause");
        }
    }
    else
    {
        system("cls");
        puts("**********************************");
        puts("*************0.���ڳ�ֵ***********");
        puts("*************1.ͣ��***************");
        puts("*************2.ȡ��***************");
        puts("*************3.�鳵����***********");
        puts("*************4.�˳�***************");
        puts("*************5.�˳�����***********");
        puts("*************6.����ϵͳ***********");
        puts("**********************************");
        printf("��ѡ������ܣ�");
        scanf("%d",&c);
        if(c == 0)//����
        {}
        else if(c == 1)//����
        {
            Car_Com(&cha);
        }
        else if(c == 2)//����
        {
            Car_Out(&cha, &peo);
        }
        else if(c == 3)//������
        {
            Car_Wer(&cha);
        }
        else if(c == 4)//�˳���¼
        {
            NOW = 0;
        }
        else if(c == 5)//�˳�����
        {
            NOW = 100;
        }
        // else if(c == 6)
        // {
        //     Set_sys();
        // }
        else
        {
            puts("����������");
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
    puts("�������û�����");
    scanf("%s", name);
    puts("���������룺");
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

void Car_Com(CHA* q)
{
    if(Mak_Di_car(q) == 1)
    {
        puts("��ĳ�����⣡");
    }
    else puts("������");
}

bool Mak_Di_car(CHA* q)
{
    CHA* p;
    if((p = (CHA*)malloc(sizeof(CHA))) == NULL)
    {
        puts("Malloc over wen make LIST!!!");
        return 0;
    }
    printf("��������ĳ��ƺţ�");
    scanf("%s", p->car.nm);
    Chang_car(&p->car);//ģ�⳵���
    p->nxt = q->nxt;
    q->nxt = p;
    return 1;
}

void Car_Out(CHA* q, MESS* p)
{
    char ma[10], nm[10];
    puts("���ǣ�");
    scanf("%s", nm);
    puts("��������ǣ�");
    scanf("%s", ma);
    if(Fnd_di_chang_us_pnm(p, nm) == 0)
    {
        puts("��Ҫ�����˺���(����Ϊ0������Ϊ1)��");
        bool key = 0;
        scanf("%d", &key);
        if(key == 0)
        {
            Mak_Di_chang(p, nm);
        }
        else 
        {
            puts("�㲻���ߣ�Ҫ��Ǯ\n�ึǮ�����봴���˺�");
            system("pause");
            return ;
        }
    }
    puts("���ƺ��ǣ�");
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
        puts("ͣ������û�г�");
    }
    else 
    {
        while(q->nxt->nxt != NULL && strcmp(q->nxt->car.nm, nm))
        {
            q->nxt = q->nxt->nxt;
        }
        if(q->nxt->nxt != NULL && !strcmp(q->nxt->car.nm, nm))
        {
            ////////////??????????????????????????����Ǯ
            CHA* x = q->nxt;
            q->nxt = q->nxt->nxt;
            free(x);
            puts("����ͣ�����ˣ�");
            return 1;
        }
        else puts("û��ȥ");
        system("pause");
    }
    return 0;
}

bool Fnd_di_che_us_cnm(CHA* q, char* nm)
{
    while(q->nxt != NULL && strcmp(q->nxt->car.nm, nm)) 
    {
        q = q->nxt;
    }
    if(q->nxt != NULL && !strcmp(q->nxt->car.nm, nm)) 
    {
        printf("��ĳ���%d����%d��ͣ��λ��\n", q->nxt->car.wer.x, q->nxt->car.wer.y);
        return 1;
    }
    return 0;
}

void Car_Wer(CHA* q)
{
    char s[10];
    puts("��ĳ��ƺ��ǣ�");
    scanf("%s", s);
    if( Fnd_di_che_us_cnm(q, s) == 0)
    {
        puts("��ĳ����ڳ���");
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
        printf("������������룺");
        scanf("%s", s);
        printf("ȷ��������룺");
        scanf("%s", c);
        if(strcmp(s, c) == 0) 
        {
            key = 1;
            puts("�����޸ĳɹ�");
        }
        else puts("�������벻һ�������������룩");
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
    for(int i = 0; i < 3; i++)
    // while(p->nxt != NULL)
    {
        printf("���������%s \n������Ϊ%llf\n���Ѿ�ʹ��ʱ��Ϊ%d\n", p->nxt->p_n, p->nxt->vue, p->nxt->V);
        p = p->nxt;
    }
}

void look_list_cha(CHA* p)
{
    while(p != NULL)
    {
        printf("���ƺ���%s \n����%d����\n����%d��%d��", p->car.nm, p->car.now_t, p->car.wer.x, p->car.wer.y);
        p = p->nxt;
    }
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

void Chang_car(CAR* p)
{
    int x = Fnd_chang();
    if(x != 0)
    {
        p->wer.x = x / 10;
        p->wer.y = x % 10;
        printf("��ĳ���%d��%d��ͣ��λ", p->wer.x, p->wer.y);
        system("pause");
        return ;
    }
    else puts("��ĳ�ûλ����");
    return;
}

int Fnd_chang()
{
    for(int i = 1; i <= 100; i++)
    {
        if(chang[i] == 0)
        {
            chang[i] = 1; 
            return i;
        }
    }
    return 0;
}

