// // // #include <stdio.h>

// // // int main() {
// // //     FILE *file;
// // //     char buffer[1024];

// // //     file = fopen("123", "r"); // ��ֻ����ʽ���ļ�
// // //     if (file == NULL) {
// // //         printf("�޷����ļ�\n");
// // //         return 1;
// // //     }

// // //     while (fgets(buffer, sizeof(buffer), file) != NULL) { // ѭ����ȡ�ļ�����
// // //         printf("%s", buffer); // ���ÿһ�е�����
// // //     }

// // //     fclose(file); // �ر��ļ�
// // //     return 0;
// // // }
// // #include <stdio.h>

// // int main() {
// //     FILE *file;
// //     char buffer[1024];
// //     int a, b, c;
// //     float d;

// //     file = fopen("123", "r"); // ��ֻ����ʽ���ļ�
// //     if (file == NULL) {
// //         printf("�޷����ļ�\n");
// //         return 1;
// //     }
// //     char s[10];
// //     fscanf(file, "%s %d", s, &a); // ��ȡ�ĸ�������һ��������
// //     fclose(file); // �ر��ļ�

// //     printf("%s %d\n", s, a); // �����ȡ������

// //     return 0;
// // }


// #include <stdio.h>
// #include <time.h>

// int main() {
//     time_t rawtime; // time_t���ͣ���ʾ��1970��1��1������������
//     struct tm * timeinfo; // struct tm���ͣ����ڴ洢���ں�ʱ��Ľṹ��
//     int seconds; // int���ͣ���ʾ��ǰʱ�����1970��1��1�յ�����
//     char buffer[26]; // char���ͣ����ڴ洢��ʽ��������ں�ʱ���ַ���

//     // time (&rawtime); // ��ȡ��epoch����������
    
//     FILE* fp = NULL;
//     fp = fopen("sys", "r");
//     fscanf(fp, "%lld", &rawtime);


//     timeinfo = localtime (&rawtime); // ת��Ϊ�ֽ�ʱ���ʾ
//     seconds = difftime(time(NULL), rawtime); // ����Ϊ��λ��ȡnow��epoch֮��Ĳ�ֵ
//     strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo); // �����ں�ʱ���ʽ��Ϊ�ַ���

//     printf("Current time: %s\n", buffer); //��ӡ��ʽ�������ں�ʱ���ַ���
//     printf("Time since epoch: %d seconds\n", seconds); // ����Ϊ��λ��ӡnow��epoch֮��Ĳ�ֵ
//     return 0;
// }



// // #include<stdio.h>

// // int main()
// // {
// //     FILE *fp = fopen("data.txt", "r");
// //     if (fp == NULL) {
// //         printf("Failed to open file\n");
// //         return 1;
// //     }

// //     double x, y, z;
// //     while (fscanf(fp, "%lf %lf %lf", &x, &y, &z) == 3) {
// //         printf("x=%f y=%f z=%f\n", x, y, z);
// //     }

// //     fclose(fp);

// // }


// // #include<stdio.h>
// // int main()
// // {
// //     FILE* sys = NULL;
// //     if((sys = fopen(".\\data\\usr_ch", "r")) == NULL)
// //     {
// //         printf("Can not open data file usr_ch\n");
// //         // system("pause");
// //         sys = fopen(".\\data\\usr_ch", "w");
// //     }
// //     return 0;
// // }

///7.19��ҵ///////////////////////////////////////
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int S_To_I(char *x)
{
    int v = 0;
    int n = strlen(x);
    for(int i = 0; i < n; i++)
    {
        v*=10;
        v += (x[i] - '0');
    }
    return v;
}

void Long_S(char* s)
{
    char c = s[0];
    int ma = 1, tm = 1;
    for(int i = 1; i < strlen(s); i++)
    {
        if(c == s[i]) 
        {
            tm++;
            ma = ma > tm ? ma : tm;
        }
        else 
        {
            c = s[i];
            tm = 1;
        }
    }
    printf("��������ַ�Ϊ��%d\n", ma);
}

void Del_S_U_S(char* p, char* q)
{
    for(int i = 0; i < strlen(p); i++)
    {
        if(p[i] == q[0])
        {
            int key = 0;
            for(int j = 1; j < strlen(q) && key == 0; j++)
            {
                if(p[i + j] != q[j]) key = 1;
            }
            if(key == 0)
            {
                for(int j = 0; j < strlen(q); j++)
                {
                    p[i + j] = ' ';
                }
            }
        }
    }
    char* xy;
    int j = 0;
    xy = (char*)malloc(sizeof(p));
    for(int i = 0; i < strlen(p); i++)
    {
        if(p[i] != ' ')xy[j++] = p[i];
    }
    printf("ɾ�����ַ���Ϊ%s", xy);
}

int main()
{
    char c[100];
    printf("���Թ���1���ַ���ת������������һ���ַ���");
    scanf("%s", c);
    int x = S_To_I(c);
    printf("ת����Ϊ%d\n", x);
    printf("���Թ���2���ҵ�����Ӵ���������һ���ַ���");
    scanf("%s", c);
    Long_S(c);
    // printf("ת����Ϊ%d\n", x);
    printf("���Թ���3���ַ���ɾ��һ���ַ�����������һ���ַ���");
    scanf("%s", c);
    printf("���Թ���3���ַ���ɾ��һ���ַ���������ɾ�����ַ���");
    char s[20];
    scanf("%s", s);
    // int x = S_To_I(c);
    Del_S_U_S(c, s);
}