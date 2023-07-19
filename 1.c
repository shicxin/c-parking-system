#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<time.h>

#define PZ_NUM 7      //�����ļ���Ŀ����

#define CHAR_SIZE 20   //Ĭ�ϳ���

//DATA

int user_len = 6; //�û�������
int paswd_len = 6; //���볤��
int NOW = 0; //����״̬�ж�
int *init_con = NULL; //��ʼ�������洢λ��
int c_num_qu = 10; //ͣ������λx��
int c_num_lang = 10; //ͣ������λy��
int ten_mun; //ʮ���ӵļ�Ǯ
int hfh_mun; //��Сʱ�ļ�Ǯ
int hou_mun; //һСʱ�ļ�Ǯ

// int p_num = 100; // ��Ա����

typedef struct CAR{
    char nm[CHAR_SIZE];
    time_t now_t; //����ʱ��
    struct {
        int x, y;
    }wer; //����λ��
}CAR;
typedef struct CHA{
    CAR car;
    struct CHA* nxt;
}CHA; //ͣ����

typedef struct MESS{
    char p_n[CHAR_SIZE]; //����```````
    char mima[CHAR_SIZE];
    int V; //�ѽ���ʱ��
    double vue; //�˺����
    struct MESS* nxt;
}MESS; //�˻�

typedef struct WRITEDO{
    char time[CHAR_SIZE];
    struct {
        char nm[CHAR_SIZE];
        bool P_O_C;//��0����1
        char ADD[CHAR_SIZE];
    }DO; //����λ��
}WTD;


// DODODO

int read_int(char*);
double read_double(char*);
long long read_longlong(char*);
void int_to_str(int, char*);
void double_to_str(double, char*);
void longlong_to_str(long long, char*);

void Write_Time_And_DO(WTD* );//д�����
void Use_WTAD(time_t, char*, bool, int);//��װд�����

void init_sys(MESS*, CHA*, bool*); //��ʼ��ϵͳ
void Set_sys(); //����ϵͳ
void Init_Di_mess(FILE*, MESS*);//��ʼ���û�

MESS* Create_User(MESS*, char*);//�½��û�
bool Del_User(MESS*, char*);//ɾ���û�
bool Vue_User(MESS*, char*);//��ֵ�û�
void Print_User_List(MESS*, bool);//�����û�����
MESS* Fnd_di_chang_us_pnm(MESS*, char*);//ʹ���û���Ѱ���û�

void Init_Di_car(FILE*, CHA*, bool*);//��ʼ��ͣ����
bool Mak_Di_car(CHA*, bool*);//ģ�⳵��ͣ����
bool Del_Di_car(MESS*, CHA*, char*);//ģ�⳵��ͣ����
void Print_Car_List(CHA*, bool);//����ͣ��������Ϣ
CHA* Fnd_di_che_us_cnm(CHA* , char*);
void Chang_car(CAR*, bool*);//Ϊ�����ĳ����䳵λ
int Fnd_chang(bool* P);//�ҵ��ճ�λ�����س�λ�ĳ���ռ�
int Print_List_Chang(bool*);//����ͣ����������Ϣ

bool Check_Login(); //�����жϣ�����0��1��
bool admin_admin();//��¼����
void He_init(MESS*, CHA*, bool*); //hello����
void user_hole(MESS*);//�û����ܽ���
void Car_Com(CHA*, bool*); //�����ˣ���Ҫ���ƺţ���Ϊ���ƺŷ����Ӧ��ͣ��λ
void Car_Out(CHA*, MESS*); //������
void Car_Wer(CHA*); //������

int Read_Timt(time_t*);//��ȡʱ�䣬���ʱ�䣬�����뵱ǰʱ��Ĳ�ֵ
long long Now_Time();
// void Count_Money();//����ͣ����ӯ��
double Tran_Mony(double);//��ͣ��������


int main()
{
    MESS mess_hand; CHA cha_hand;
    bool* chang;
    chang = (bool*)malloc(sizeof(bool) * (c_num_qu * c_num_lang));
    memset(chang, 0, (c_num_qu * c_num_lang));//��ʼ��
    mess_hand.nxt = NULL;
    cha_hand.nxt = NULL;
    init_sys(&mess_hand, &cha_hand, chang);//ȫ����ʼ��
    puts("�Ƿ�鿴ϵͳ�Լ�����(0Ϊ��)");
    char s[CHAR_SIZE];
    scanf("%s", &s);
    int a = read_int(s);
    if(a) 
    {
        puts("�û��˺�������");
        Print_User_List(&mess_hand, 0);
        puts("ͣ�������г���Ϣ���£�");
        Print_Car_List(cha_hand.nxt, 0);
        Print_List_Chang(chang);
        puts("ͣ����������3����");
        system("pause");
    }
    while(NOW != 100)
    {
        He_init(&mess_hand, cha_hand.nxt, chang);
    }
    return 0;
}

/// @brief ���ڽ�һ��int���͵�ֵת��Ϊһ���ַ��������洢�ڴ����char*ָ����ָ���������
/// @param i ����
/// @param s �����ַ���
void int_to_str(int i, char* s)
{
    sprintf(s, "%d", i); 
}

/// @brief ���ڽ�һ��double���͵�ֵת��Ϊһ���ַ��������洢�ڴ����char*ָ����ָ���������
/// @param d double
/// @param s �����ַ���
void double_to_str(double d, char* s)
{
    sprintf(s, "%.02lf", d);
}

/// @brief ���ڽ�һ��long long���͵�ֵת��Ϊһ���ַ��������洢�ڴ����char*ָ����ָ���������
/// @param ll 
/// @param s 
void longlong_to_str(long long ll, char* s)
{
    sprintf(s, "%lld", ll); 
}

/// @brief ��ִ�е��й�Ǯ�Ĳ���д��data\\money
/// @param wtd д������
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
    puts("������ɣ�");
    return;
}

/// @brief ��װд�ļ�����
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

/// @brief �����û�
/// @param head �û�����
void user_hole(MESS* head)
{
    puts("**********************************");
    puts("*************1.�����û�************");
    puts("*************2.�û�����************");
    puts("*************3.�û���ֵ************");
    puts("**********************************");

    char c[CHAR_SIZE];
    scanf("%s", c);
    if(strcmp(c, "1"))
    {
        puts("���������");
        scanf("%s", c);
        Create_User(head, c);
    }
    else if(strcmp(c, "2"))
    {
        puts("���������");
        scanf("%s", c);
        Del_User(head, c);
    }
    else if(strcmp(c, "3"))
    {
        puts("���������");
        scanf("%s", c);
        Vue_User(head, c);
    }
    else puts("���벻�Ϸ�");
    return;
}

/// @brief �Ӽ��̶�ȡһ���ַ�������ת��Ϊһ��int���͵�ֵ
/// @return int
int read_int(char* s)
{
    int i;
    i = atoi(s); 
    return i; 
}
/// @brief  �Ӽ��̶�ȡһ���ַ�������ת��Ϊһ��double���͵�ֵ
/// @return double
double read_double(char* s)
{
    double d;
    // scanf("%s", s);
    d = atof(s);
    return d; // ����d��ֵ
}

/// @brief ���ڽ�һ���ַ���ת��Ϊһ��long long���͵�ֵ�������ظ�ֵ
/// @param s �洢λ��
/// @return long long
long long read_longlong(char* s)
{
    long long ll; 
    ll = atoll(s); 
    return ll; 
}

/// @brief ��ʼ��ϵͳ
/// @param peo �û�����
/// @param cha ͣ�����ĳ����б�
/// @param chang һά����ģ���ͣ����
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
        char k[CHAR_SIZE] = {'o'};
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
    // Print_User_List(peo);
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
}

/// @brief ����ϵͳ
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
    // scanf("%c", k);//���������еĻس�
    for(int i = 1; i < PZ_NUM + 1; i++)
    {
        printf("��ǰ%sΪ%d���Ƿ���Ҫ�޸ģ�Y/N, Ĭ��N��:",a[i], num[i] );
        // printf("%s%d\n", a[0], num[0]);
        scanf("%s", k);
        // printf("%s%d\n", a[0], num[0]);
        if(strcmp(k, "Y") == 0)
        {
            printf("��Ҫ��Ϊ��");
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
/// @brief ��ʼ���û�
/// @param fp �û������ļ�
/// @param q �û�����
/// @return 
void Init_Di_mess(FILE* fp, MESS* q)
{
    char s1[CHAR_SIZE], s2[CHAR_SIZE], s3[CHAR_SIZE], s4[CHAR_SIZE];
    while(fscanf(fp, "%s %s %s %s", s1, s2, s3, s4) != EOF)// q->p_n, q->mima, q->vue, q->V) != EOF)
    {
        // a /= 100;
        // printf("���������%s \n���������%s \n������Ϊ%s\n���Ѿ�ʹ��ʱ��Ϊ%s\n", s1, s2, s3, s4);
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
        // �ƶ�����һ���ڵ�
        q = q->nxt;
    }
    return ;
}
/// @brief ��ȡʱ��
/// @param T ��Ҫ�����time_t
/// @return ��Ҫ�����ʱ���뵱ǰ��ʱ������������TΪ��ָ�룬�򷵻�-1
int Read_Timt(time_t* T)
{
    if(T == NULL) // ���T�Ƿ�Ϊ��ָ��
    {
        printf("��Ч��time_tָ��\n");
        return -1; // ����һ�������־
    }
    struct tm * timeinfo;
    timeinfo = localtime (T);
    char buffer[26];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo); // �����ں�ʱ���ʽ��Ϊ�ַ���
    printf("�������ʱ��Ϊ: %s\n", buffer); //��ӡ��ʽ�������ں�ʱ���ַ���
    time_t now = Now_Time();
    return difftime(now, *T); // �����뵱ǰʱ��Ĳ�ֵ����λ����
}

/// @brief ��������ص�ǰʱ��
/// @return ����ʱ���
long long Now_Time()
{
    time_t now = time(NULL); // ��ȡ��ǰʱ��
    struct tm * timeinfo;
    timeinfo = localtime(&now);
    char buffer[26];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo); // �����ں�ʱ���ʽ��Ϊ�ַ���
    printf("����ʱ��Ϊ: %s\n", buffer); //��ӡ��ʽ�������ں�ʱ���ַ���
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

    printf("����ͣ��ʱ���൱��%d��һСʱ�� %d����Сʱ��%d��ʮ����\n", h, fh, m);

    return h * hou_mun + fh * hfh_mun + m * ten_mun;
}
/// @brief ��¼������ѡ�����
/// @param peo �û�����
/// @param cha ������
/// @param P ͣ��������
void He_init(MESS* peo, CHA* cha, bool* P)
{
    char c[10];
    if(NOW <= -3)
    {
        system("cls");
        int i = 100;
        while(i--)
        {
            printf("��ը��ը��ը�������ը��ը��ը��ը��ը��ը��ը��ը�������ը��ը��ը��ը��ը��ը��ը��ը�������ը��ը��ը��ը��ը��ը��ը��ը�������ը��ը��ը��ը��ը��ը��ը��ը�������ը��ը��ը��ը��ը��ը��ը��ը�������ը��ը��ը��ը��ը��ը��ը��ը�������ը��ը��ը��ը��ը��ը��ը��ը�������ը��ը��ը��ը��ը��ը��ը��ը�������ը��ը��ը��ը��ը��ը��ը��ը�������ը��ը��ը��ը��ը");
        }
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
        scanf("%s",c);
        if(strcmp(c, "0") == 0)//��¼
        {
            if(Check_Login() != 1)
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
        else if(strcmp(c, "1") == 0)
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
        scanf("%s",c);
        if(strcmp(c, "0") == 0)//��¼
        {
            if(Check_Login()==0)
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
        puts("*************0.����ҵ��***********");
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
        scanf("%s",c);
        if(strcmp(c, "0") == 0)//����
        {
            user_hole(peo);
        }
        else if(strcmp(c, "1") == 0)//����
        {
            Car_Com(cha, P);
        }
        else if(strcmp(c, "2") == 0)//����
        {
            Car_Out(cha, peo);
            system("pause");
        }
        else if(strcmp(c, "3") == 0)//������
        {
            Car_Wer(cha);
        }
        else if(strcmp(c, "4") == 0)//�˳���¼
        {
            NOW = 0;
        }
        else if(strcmp(c, "5") == 0)//�˳�����
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
            puts("����������");
            system("pause");
        }
    } 
}

/// @brief  �ú������ڼ���û�������û���������
/// @return  �Ƿ���ȷ
bool Check_Login()
{
    // ���ļ�
    FILE* file = fopen(".\\data\\user_file","r");
    if(file == NULL) // ����ļ��Ƿ�򿪳ɹ�
    {
        printf("Can not open write file\n");
        exit(0);
    }
    
    // ��ȡ�ļ��д洢���û���������
    char* username, * password;
    username = (char*)malloc(sizeof(char) * user_len);
    password = (char*)malloc(sizeof(char) * paswd_len);
    fgets(username, user_len, file);
    fgets(password, paswd_len, file);
    
    fclose(file);
    
    // ��ȡ�û�������û���������
    char name[100], paswd[100];
    puts("�������û�����");
    scanf("%s", name);
    puts("���������룺");
    scanf("%s", paswd);
    
    // �Ƚ��û����������Ƿ�ƥ��
    if(strcmp(paswd, password)==0 && strcmp(name, username)==0)
    {
        // ƥ��ɹ�������true������NOW��Ϊ1
        NOW = 1;
        return true;
    }
    else 
    {
        // ƥ��ʧ�ܣ�����false������NOW��1
        NOW--;
        return false;
    }
}

/// @brief ����ͣ����
/// @param q ͣ������������
/// @param P һά����ģ���ͣ����
void Car_Com(CHA* q, bool* P)
{
    if(Mak_Di_car(q, P) == 1)
    {
        puts("��ĳ�����ˣ�");
    }
    else puts("������");
}

/// @brief ��ʼ��ͣ����
/// @param fp ͣ����������Ϣ�ļ�
/// @param cha ��������
/// @param P һά����ģ���ͣ����
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
        // printf("���ƺ���%s \n����%d����\n����%d��%d��\n",x->car.nm, x->car.now_t, x->car.wer.x, x->car.wer.y);
        x->nxt = cha->nxt;
        cha->nxt = x;
        // printf("���ڣ�����������������������������������%d\n", x->car.wer.x * c_num_lang + x->car.wer.y);
        P[x->car.wer.x * c_num_lang + x->car.wer.y] = 1;
        x = (CHA*)malloc(sizeof(CHA));
    }
    // puts("Init_Di_car ok");

    return ;
}
/// @brief ģ�⳵��ͣ����
/// @param q ͣ������������
/// @param P һά����ģ���ͣ����
/// @return ͣ���Ƿ�ɹ�
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

/// @brief ȫ�ֿ��Ƴ���ͣ����
/// @param q ͣ����ͣ�ų�����
/// @param p ������
void Car_Out(CHA* car, MESS* peo)
{
    MESS* p = peo;
    CHA* q = car;
    char ma[CHAR_SIZE], nm[CHAR_SIZE];
    puts("���ǣ�");
    scanf("%s", nm);
    MESS* x = Fnd_di_chang_us_pnm(p, nm);
    if(x == NULL)
    {
        puts("��Ҫ�����˺���(����Ϊ0������Ϊ1)��");
        bool key = 0;
        scanf("%d", &key);
        if(key == 0)
        {
            x = Create_User(p, nm);
            printf("���������%s\n", x->mima);
            printf("�˺Ž��Ϊ%.2lf\n", x->vue);
        }
        else 
        {
            puts("�㲻���ߣ�Ҫ��Ǯ\n�ึǮ�����봴���˺�");
            system("pause");
            return ;
        }
    }
    puts("��������ǣ�");
    scanf("%s", ma);
    // puts(ma);
    // puts(x->mima);
    if(strcmp(ma, x->mima) != 0)
    {
        puts("�������");
        return ;
    }
    puts("���ƺ��ǣ�");
    CAR xx;
    scanf("%s", xx.nm);
    if(Del_Di_car(x, q, xx.nm)) 
    {
        Print_Car_List(car, 1);
        Print_User_List(peo, 1);
    }
}

/// @brief ʹ���û���Ѱ���û�
/// @param q �û�����
/// @param nm �û���
/// @return �Ƿ��ҵ�
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

/// @brief ģ�⳵��ͣ����
/// @param peo �ۿ���
/// @param q ͣ��������ͣ�ŵĳ�
/// @param nm Ҫ��ͣ�����ĳ�
/// @return ��ͣ�����Ƿ�ɹ�
bool Del_Di_car(MESS*peo, CHA* k, char* nm)
{
    if(k == NULL) // û��ͣ��
    {
        puts("ͣ������û�г�");
        return 0;
    }
    CHA* p = k; // ��һ����ʱ��������������
    if(strcmp(p->car.nm, nm) == 0)
    {
        double vue;
        vue = Read_Timt(&p->car.now_t);
        vue = Tran_Mony(vue);
        printf("�ܽ��Ϊ��%.02lf\n", vue);
        printf("�㿨�ﻹ�У�%.02lf,�Ƿ���г�ֵ��(Ĭ��N��y/Y/1Ϊ��ֵ)", peo->vue);
        char s[CHAR_SIZE];
        scanf("%s", s);
        if(strcmp(s, "y") == 0 || strcmp(s, "Y") == 0 || strcmp(s, "1") == 0)
        {
            puts("�������ֵ���");
            scanf("%s", s);
            peo->vue += read_int(s);
            Use_WTAD(time(NULL), peo->p_n, 0, vue);
        }
        if(vue > peo->vue)
        {
            puts("Ǯ������");
            puts("û�г���������");
            return 0;
        }
        else
        {
            peo->vue -= vue;
        }
        free(p); // �ͷ��ڴ�
        Use_WTAD(time(NULL), nm, 1, -vue);//��¼����
        Use_WTAD(time(NULL),peo->p_n, 0, -vue);//��¼����
        printf("�����ڻ���%.2lf��\n", peo->vue);
        puts("����ͣ�����ˣ�");
    }
    while(p->nxt != NULL && strcmp(p->nxt->car.nm, nm)) // �ҵ�Ҫ����ĳ������ߵ�������β��
    {
        p = p->nxt;
    }
    if(p->nxt != NULL && strcmp(p->nxt->car.nm, nm) == 0) // �ҵ���Ҫ����ĳ���
    {
        // puts("�ҵ���");
        double vue, vv;
        vv = Read_Timt(&p->nxt->car.now_t); // ����ͣ��ʱ��
        vue = Tran_Mony(vv); // ����ͣ������
        printf("�ܽ��Ϊ��%.02lf\n", vue);
        printf("�㿨�ﻹ�У�%.02lf,�Ƿ���г�ֵ��(Ĭ��N��y/Y/1Ϊ��ֵ)", peo->vue);
        char s[CHAR_SIZE];
        scanf("%s", s);
        if(strcmp(s, "y") == 0 || strcmp(s, "Y") == 0 || strcmp(s, "1") == 0)
        {
            puts("�������ֵ���");
            scanf("%s", s);
            peo->vue += read_int(s);
            Use_WTAD(time(NULL), peo->p_n, 0, vue);
        }
        if(vue > peo->vue)
        {
            puts("Ǯ������");
            puts("û�г���������");
            return 0;
        }
        else
        {
            peo->vue -= vue;
        }
        CHA* car = p->nxt;
        p->nxt = car->nxt; // ��������ɾ������ĳ���
        free(car); // �ͷ��ڴ�
        Use_WTAD(time(NULL), nm, 1, -vue);//��¼����
        Use_WTAD(time(NULL),peo->p_n, 0, -vue);//��¼����
        printf("�����ڻ���%.2lf��\n", peo->vue);
        puts("����ͣ�����ˣ�");
        return 1;
    }
    else // û���ҵ�Ҫ����ĳ���
    {
        puts("û���ҵ�Ҫ����ĳ���");
        return 0;
    }
}
/// @brief ʹ�ó��ƺ��ҵ�ͣ�����ĳ�
/// @param q ͣ��������
/// @param nm ���ƺ�
/// @return ͣ�����ҵ��ĳ�
CHA* Fnd_di_che_us_cnm(CHA* q, char* nm)
{
    if(strcmp(q->car.nm, nm) == 0) 
    {
        printf("��ĳ���%d����%d��ͣ��λ��\n", q->car.wer.x, q->car.wer.y);
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
            printf("��ĳ���%d����%d��ͣ��λ��\n", q->nxt->car.wer.x, q->nxt->car.wer.y);
            return q->nxt;
        }
    }
    return NULL;
}

void Car_Wer(CHA* q)
{
    char s[10];
    puts("��ĳ��ƺ��ǣ�");
    scanf("%s", s);
    if( Fnd_di_che_us_cnm(q, s) == NULL)
    {
        puts("��ĳ����ڳ���");
    }
    system("pause");
}

/// @brief �½��û�
/// @param head �û�����
/// @param name �û���
/// @return �½��ɹ�
MESS* Create_User(MESS* head, char * name)
{
    MESS* node;
    // �����ڴ�ռ�
    if((node = (MESS*)malloc(sizeof(MESS))) == NULL)
    {
        puts("Malloc over wen make LIST!!!");
        return 0;
    }
    char password[100], confirm[100];
    bool match = 0;
    while(match == 0)
    {
        printf("������������룺");
        scanf("%s", password);
        printf("ȷ��������룺");
        scanf("%s", confirm);
        if(strcmp(password, confirm) == 0) 
        {
            match = 1;
            puts("��������ɹ�");
        }
        else 
        {
            puts("�������벻һ�������������룩");
        }
    }
    // �����û���������
    strcpy(node->p_n,name);
    strcpy(node->mima, password);
    node->V = 0;
    node->vue = 0;
    printf("�����ֵ���٣�");
    char s1[CHAR_SIZE], s2[CHAR_SIZE];
    scanf("%s", s1);
    node->vue = read_double(s1);
    Use_WTAD(time(NULL), name, 0, node->vue);//��¼����
    // ���ļ�
    FILE* p_mess;
    if((p_mess = fopen(".\\data\\usr_p", "a")) == NULL)
    {
        printf("Can not open data file usr_p\n");
        exit(0);
    }

    // ���û���Ϣд���ļ�
    double_to_str(node->vue, s1);
    int_to_str(node->V, s2);
    fprintf(p_mess, "%s %s %s %s\n", node->p_n, node->mima, s1, s2);

    // �ر��ļ�
    fclose(p_mess);

    // ���û��ڵ��������
    node->nxt = head->nxt;
    head->nxt = node;
    // printf("���������%s���˻����Ϊ%.2lf\n", node->mima, node->vue);
    
    return node;
}

/// @brief ɾ���û�
/// @param head ͷ���
/// @param nm ɾ��������
/// @return ɾ���Ƿ�ɹ�
bool Del_User(MESS* head, char* nm)
{
    if(head == NULL) return 0;
    if(strcmp(head->p_n, nm) == 0)
    {
        printf("һ���������%.2lfԪ", head->vue);
        free(head);
        return 1;
    }
    while(head->nxt != NULL && strcmp(head->p_n, nm) != 0)
    {
        head = head->nxt;
    }
    if(head->nxt != NULL && strcmp(head->p_n, nm) == 0)
    {
        printf("һ���������%.2lfԪ", head->vue);
        MESS* x = head->nxt;
        head->nxt = x->nxt;
        free(x);
        return 1;
    }
    return 0;
}

/// @brief ��ֵ����
/// @param head �û�����
/// @param nm ��ֵ������
/// @return ��ֵ�Ƿ�ɹ�
bool Vue_User(MESS* head, char* nm)
{
    MESS* x = Fnd_di_chang_us_pnm(head, nm);
    puts("�����ֵ���٣�");
    int vue = 0;
    scanf("%d", &vue);
}

/// @brief �����û���Ϣ
/// @param head ͣ�������е��û���Ϣ
/// @param BOL �ж��Ƿ��ӡ��������
void Print_User_List(MESS* head, bool BOL)
{
    FILE* fp;
    if((fp = fopen(".\\data\\usr_p", "w")) == NULL)
    {
        printf("Can not open data file usr_p\n");
        exit(0);
    }
    // �����û�����
    while(head->nxt != NULL)
    {
        // ��ӡ�û���Ϣ
        char s1[CHAR_SIZE], s2[CHAR_SIZE];
        double_to_str(head->nxt->vue, s1);
        int_to_str(head->nxt->V, s2);
        fprintf(fp, "%s %s %s %s\n", head->nxt->p_n, head->nxt->mima, s1, s2);
        if(!BOL)
        printf("���������%s \n������Ϊ%.02llf\n���Ѿ�ʹ��ʱ��Ϊ%d\n", head->nxt->p_n, head->nxt->vue, head->nxt->V);
        // �ƶ�����һ���ڵ�
        head = head->nxt;
    }
    fclose(fp);
}

/// @brief ����ͣ��������Ϣ
/// @param head ͣ�������еĳ�����Ϣ
/// @param BOL �ж��Ƿ��ӡ��������
void Print_Car_List(CHA* head, bool BOL)
{
    FILE* fp;
    if((fp = fopen(".\\data\\usr_ch", "w")) == NULL)
    {
        printf("Can not open data file usr_ch\n");
        exit(0);
    }
    // ������������
    while(head != NULL)
    {
        // ��ʽ���������ʱ��
        char buffer[26]; // char���ͣ����ڴ洢��ʽ��������ں�ʱ���ַ���
        struct tm * timeinfo;
        timeinfo = localtime (&head->car.now_t); // ת��Ϊ�ֽ�ʱ���ʾ
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
        
        char s1[CHAR_SIZE], s2[CHAR_SIZE], s3[CHAR_SIZE];
        longlong_to_str(head->car.now_t, s1);
        int_to_str(head->car.wer.x, s2);
        int_to_str(head->car.wer.y, s3);

        fprintf(fp, "%s %s %s %s\n", head->car.nm, s1, s2, s3);
        if(!BOL)
        printf("���ƺ���%s \n����%s����\n����%d��%d��\n\n", head->car.nm, buffer, head->car.wer.x, head->car.wer.y);

        // �ƶ�����һ���ڵ�
        head = head->nxt;
    }
    fclose(fp);
}
/// @brief ʹ�ö�άͼ��չʾͣ����
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
    printf("������%d����\n", b1);
    return b2;
}

/// @brief �ú������ڽ�������Ϣд���ļ�������ӡͣ��λ�����ʱ��
/// @param car ͣ������������
/// @param change 
void Chang_car(CAR* car, bool* change)
{
    // ����Fnd_chang�����ҵ�һ�����õ�ͣ��λ
    int index = Fnd_chang(change);
    if(index != 0)
    {
        // ���³�����Ϣ
        car->wer.x = index / 10;
        car->wer.y = index % 10;
        time(&car->now_t);
        // ���ļ�
        FILE* file = fopen(".\\data\\usr_ch", "a");

        Use_WTAD(car->now_t, car->nm, 1, 0);//��¼����

        if(file == NULL) // ����ļ��Ƿ�򿪳ɹ�
        {
            printf("Can not open data file system\n");
            exit(0);
        }
        // ��������Ϣд���ļ�
        char s1[CHAR_SIZE], s2[CHAR_SIZE], s3[CHAR_SIZE];
        longlong_to_str(car->now_t, s1);
        // long long time = car->now_t;
        int_to_str(car->wer.x, s2);
        int_to_str(car->wer.y, s3);
        // int x = car->wer.x, y = car->wer.y;
        fprintf(file, "%s %s %s %s\n", car->nm, s1, s2, s3);
        // �ر��ļ�
        fclose(file);
        
        // ��ӡͣ��λ��Ϣ
        printf("��ĳ���%d��%d��ͣ��λ\n", car->wer.x, car->wer.y);
        
        // ��ӡ���ʱ����Ϣ
        struct tm * timeinfo;
        timeinfo = localtime (&car->now_t);
        char buffer[26];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo); // �����ں�ʱ���ʽ��Ϊ�ַ���
        printf("�������ʱ��Ϊ: %s\n", buffer); //��ӡ��ʽ�������ں�ʱ���ַ���
        
        system("pause");
        return ;
    }
    else 
    {
        puts("��ĳ�ûλ����");
        return;
    }
}
/// @brief �ҵ��ճ�λ
/// @param P ͣ������������
/// @return λ�� X*Y
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

