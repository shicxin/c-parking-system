#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<time.h>

#define PZ_NUM 7      //�����ļ���Ŀ����

//DATA

int user_len = 6; //�û�������
int paswd_len = 6; //���볤��
int NOW = 0; //����״̬�ж�
int *init_con = NULL; //��ʼ�������洢λ��
int c_num_qu = 10; //ͣ������λ
int c_num_lang = 10; //ͣ������λ
int ten_mun; //ʮ���ӵļ�Ǯ
int hfh_mun; //��Сʱ�ļ�Ǯ
int hou_mun; //һСʱ�ļ�Ǯ

int p_num = 100; // ��Ա����


typedef struct CAR{
    char nm[10];
    time_t now_t; //����ʱ��
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

// CHA cha;
// MESS peo;


// DODODO

void init_sys(MESS*, CHA*, bool*); //��ʼ��ϵͳ
void Set_sys(); //����ϵͳ

bool Init_Di_mess(FILE*, MESS*);//��ʼ���û�
bool Mak_Di_chang(MESS*, char*);//�½��û�
// MESS* Del_Di_chang(MESS*);//ɾ���û�
void look_list_mess(MESS*);//�����û�����
bool Fnd_di_chang_us_pnm(MESS*, char*);//ʹ���û���Ѱ���û�

bool Init_Di_car(FILE*, CHA*, bool*);//��ʼ��ͣ����
bool Mak_Di_car(CHA*, bool*);//ģ�⳵��ͣ����
bool Del_Di_car(CHA*, char*);//ģ�⳵��ͣ����
void look_list_car(CHA*);//����ͣ��������Ϣ
bool Fnd_di_che_us_cnm(CHA* , char*);
void Chang_car(CAR*, bool*);//Ϊ�����ĳ����䳵λ
int Fnd_chang(bool* P);//�ҵ��ճ�λ�����س�λ�ĳ���ռ�
int look_list_chang(bool*);//����ͣ����������Ϣ

bool IsRight(); //�����жϣ�����0��1��
int read_f_num(FILE*); //��ȡ�����ļ��е����֣�
void He_init(MESS*, CHA*, bool*); //hello����

void Car_Com(CHA*, bool*); //�����ˣ���Ҫ���ƺţ���Ϊ���ƺŷ����Ӧ��ͣ��λ
void Car_Out(CHA*, MESS*); //������
void Car_Wer(CHA*); //������

time_t Read_C_Timt(time_t*);//��ȡʱ�䣬���ʱ�䣬�����뵱ǰʱ��Ĳ�ֵ
void Count_Money();//����ͣ����ӯ��
double Tran_Mony(time_t*);//��ͣ��������


int main()
{
    MESS mess_hand; CHA cha_hand;
    bool* chang;
    chang = (bool*)malloc(sizeof(bool) * (c_num_qu * c_num_lang));
    memset(chang, 0, (c_num_qu * c_num_lang));//��ʼ��
    mess_hand.nxt = NULL;
    cha_hand.nxt = NULL;
    init_sys(&mess_hand, &cha_hand, chang);//ȫ����ʼ��
    puts("�Ƿ�鿴ϵͳ�Լ�����");
    int a;
    scanf("%d", &a);
    if(a) 
    {
        puts("�û��˺�������");
        look_list_mess(&mess_hand);
        puts("ͣ�������г���Ϣ���£�");
        look_list_car(cha_hand.nxt);
        look_list_chang(chang);
        puts("ͣ����������3����");
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
    // ��ȡ���������ļ�
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
        puts("******��ǰϵͳ������Ϣ���£�*******");
        printf("**����Ա�˺ų���Ϊ%d, ���볤��Ϊ%d **\n",user_len, paswd_len);
        printf("********����ͣ������СΪ��%d *****\n", c_num_qu * c_num_lang);
        printf("*******ͣ��ÿʮ���ӵļ۸�Ϊ��%d  ***\n", ten_mun);
        printf("*******ͣ��ÿ��Сʱ�ļ۸�Ϊ��%d  ***\n", hfh_mun);
        printf("*******ͣ��ÿһСʱ�ļ۸�Ϊ��%d ***\n", hou_mun);
        puts("***********************************");
        puts("************0.�޸�*****************");
        puts("*****x.��������ֱ�ӽ���ϵͳ********");
        puts("***********************************");
        printf("*********�����룺  ****************\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
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
    puts("ϵͳ�������");
    // ������Ϣ������
    //��ʼ��ʼ��ϵͳ
    // ��ʼ��ʼ���û�
    puts("��ʼ��ʼ���û�");
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
    //��ʼ��ʼ��ͣ����
    puts("��ʼ��ʼ��ͣ����");

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
    // scanf("%c", k);//���������еĻس�
    for(int i = 1; i < PZ_NUM + 1; i++)
    {
        printf("��ǰ%sΪ%d���Ƿ���Ҫ�޸ģ�Y/N, Ĭ��N��:",a[i], num[i] );
        // printf("%s%d\n", a[0], num[0]);
        scanf("%s", k);
        // printf("%s%d\n", a[0], num[0]);
        num[0] = 6;
        if(k == "Y")
        {
            printf("��Ҫ��Ϊ��");
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
        // printf("���������%s \n���������%s \n������Ϊ%lf\n���Ѿ�ʹ��ʱ��Ϊ%d\n", s1, s2, a, b);
        strcpy(X->p_n, s1);
        strcpy(X->mima, s2);
        X->vue = a;
        X->V = b;
        // printf("���������%s \n���������%s \n������Ϊ%lf\n���Ѿ�ʹ��ʱ��Ϊ%d\n",q->p_n, q->mima, q->vue, q->V);
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
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo); // �����ں�ʱ���ʽ��Ϊ�ַ���
    printf("�������ʱ��Ϊ: %s\n", buffer); //��ӡ��ʽ�������ں�ʱ���ַ���
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
        puts("*************6.�鿴�û�***********");
        puts("*************7.�鿴����***********");
        puts("**********************************");
        puts("************10.����ϵͳ***********");
        puts("**********************************");
        printf("��ѡ������ܣ�");
        scanf("%d",&c);
        if(c == 0)//����
        {}
        else if(c == 1)//����
        {
            Car_Com(cha, P);
        }
        else if(c == 2)//����
        {
            Car_Out(cha, peo);
            system("pause");
        }
        else if(c == 3)//������
        {
            Car_Wer(cha);
        }
        else if(c == 4)//�˳���¼
        {
            NOW = 0;
        }
        else if(c == 5)//�˳�����
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

void Car_Com(CHA* q, bool* P)
{
    if(Mak_Di_car(q, P) == 1)
    {
        puts("��ĳ�����⣡");
    }
    else puts("������");
}
bool Init_Di_car(FILE* fp, CHA* cha, bool* P)
{
    CHA* x;
    x = (CHA*)malloc(sizeof(CHA));
    int i = 0;
    while(fscanf(fp, "%s %lld %d %d", x->car.nm, &x->car.now_t, &x->car.wer.x, &x->car.wer.y) != EOF)
    {
        // printf("���ƺ���%s \n����%d����\n����%d��%d��\n",x->car.nm, x->car.now_t, x->car.wer.x, x->car.wer.y);
        x->nxt = cha->nxt;
        cha->nxt = x;
        // printf("���ڣ�����������������������������������%d\n", x->car.wer.x * c_num_lang + x->car.wer.y);
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
    printf("��������ĳ��ƺţ�");
    scanf("%s", p->car.nm);
    Chang_car(&p->car, P);//ģ�⳵���
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
            int vue = Read_C_Timt(&q->car.now_t);
            vue = Tran_Mony((time_t*)&vue);
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
    if(strcmp(q->car.nm, nm) == 0) 
    {
        printf("��ĳ���%d����%d��ͣ��λ��\n", q->car.wer.x, q->car.wer.y);
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
            printf("��ĳ���%d����%d��ͣ��λ��\n", q->nxt->car.wer.x, q->nxt->car.wer.y);
            return 1;
        }
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
    // for(int i = 0; i < 3; i++)
    while(p->nxt != NULL)
    {
        printf("���������%s \n������Ϊ%llf\n���Ѿ�ʹ��ʱ��Ϊ%d\n", p->nxt->p_n, p->nxt->vue, p->nxt->V);
        p = p->nxt;
    }
}

void look_list_car(CHA* p)
{
    while(p != NULL)
    {
        char buffer[26]; // char���ͣ����ڴ洢��ʽ��������ں�ʱ���ַ���
        struct tm * timeinfo;
        timeinfo = localtime (&p->car.now_t); // ת��Ϊ�ֽ�ʱ���ʾ
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
        printf("���ƺ���%s \n����%s����\n����%d��%d��\n\n", p->car.nm, buffer, p->car.wer.x, p->car.wer.y);
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
    printf("������%d����\n", b1);
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
        printf("��ĳ���%d��%d��ͣ��λ", p->wer.x, p->wer.y);
        time(&p->now_t);
        Read_C_Timt(&p->now_t);
        system("pause");
        return ;
    }
    else puts("��ĳ�ûλ����");
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

