// // // // // #include <stdio.h>

// // // // // int main() {
// // // // //     FILE *file;
// // // // //     char buffer[1024];

// // // // //     file = fopen("123", "r"); // ��ֻ����ʽ���ļ�
// // // // //     if (file == NULL) {
// // // // //         printf("�޷����ļ�\n");
// // // // //         return 1;
// // // // //     }

// // // // //     while (fgets(buffer, sizeof(buffer), file) != NULL) { // ѭ����ȡ�ļ�����
// // // // //         printf("%s", buffer); // ���ÿһ�е�����
// // // // //     }

// // // // //     fclose(file); // �ر��ļ�
// // // // //     return 0;
// // // // // }
// // // // #include <stdio.h>

// // // // int main() {
// // // //     FILE *file;
// // // //     char buffer[1024];
// // // //     int a, b, c;
// // // //     float d;

// // // //     file = fopen("123", "r"); // ��ֻ����ʽ���ļ�
// // // //     if (file == NULL) {
// // // //         printf("�޷����ļ�\n");
// // // //         return 1;
// // // //     }
// // // //     char s[10];
// // // //     fscanf(file, "%s %d", s, &a); // ��ȡ�ĸ�������һ��������
// // // //     fclose(file); // �ر��ļ�

// // // //     printf("%s %d\n", s, a); // �����ȡ������

// // // //     return 0;
// // // // }


// // // #include <stdio.h>
// // // #include <time.h>

// // // int main() {
// // //     time_t rawtime; // time_t���ͣ���ʾ��1970��1��1������������
// // //     struct tm * timeinfo; // struct tm���ͣ����ڴ洢���ں�ʱ��Ľṹ��
// // //     int seconds; // int���ͣ���ʾ��ǰʱ�����1970��1��1�յ�����
// // //     char buffer[26]; // char���ͣ����ڴ洢��ʽ��������ں�ʱ���ַ���

// // //     // time (&rawtime); // ��ȡ��epoch����������
    
// // //     FILE* fp = NULL;
// // //     fp = fopen("sys", "r");
// // //     fscanf(fp, "%lld", &rawtime);


// // //     timeinfo = localtime (&rawtime); // ת��Ϊ�ֽ�ʱ���ʾ
// // //     seconds = difftime(time(NULL), rawtime); // ����Ϊ��λ��ȡnow��epoch֮��Ĳ�ֵ
// // //     strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo); // �����ں�ʱ���ʽ��Ϊ�ַ���

// // //     printf("Current time: %s\n", buffer); //��ӡ��ʽ�������ں�ʱ���ַ���
// // //     printf("Time since epoch: %d seconds\n", seconds); // ����Ϊ��λ��ӡnow��epoch֮��Ĳ�ֵ
// // //     return 0;
// // // }



// // // // #include<stdio.h>

// // // // int main()
// // // // {
// // // //     FILE *fp = fopen("data.txt", "r");
// // // //     if (fp == NULL) {
// // // //         printf("Failed to open file\n");
// // // //         return 1;
// // // //     }

// // // //     double x, y, z;
// // // //     while (fscanf(fp, "%lf %lf %lf", &x, &y, &z) == 3) {
// // // //         printf("x=%f y=%f z=%f\n", x, y, z);
// // // //     }

// // // //     fclose(fp);

// // // // }


// // // // #include<stdio.h>
// // // // int main()
// // // // {
// // // //     FILE* sys = NULL;
// // // //     if((sys = fopen(".\\data\\usr_ch", "r")) == NULL)
// // // //     {
// // // //         printf("Can not open data file usr_ch\n");
// // // //         // system("pause");
// // // //         sys = fopen(".\\data\\usr_ch", "w");
// // // //     }
// // // //     return 0;
// // // // }

// // ///7.19��ҵ///////////////////////////////////////
// // #include<stdio.h>
// // #include<string.h>
// // #include<stdlib.h>

// // int S_To_I(char *x)
// // {
// //     int v = 0;
// //     int n = strlen(x);
// //     for(int i = 0; i < n; i++)
// //     {
// //         v*=10;
// //         v += (x[i] - '0');
// //     }
// //     return v;
// // }

// // void Long_S(char* s)
// // {
// //     char c = s[0];
// //     int ma = 1, tm = 1;
// //     for(int i = 1; i < strlen(s); i++)
// //     {
// //         if(c == s[i]) 
// //         {
// //             tm++;
// //             ma = ma > tm ? ma : tm;
// //         }
// //         else 
// //         {
// //             c = s[i];
// //             tm = 1;
// //         }
// //     }
// //     printf("��������ַ�Ϊ��%d\n", ma);
// // }

// // void Del_S_U_S(char* str, char* f_str)
// // {
// //     if(strlen(f_str) > strlen(str)) 
// //     {
// //         puts("Ҫɾ���ַ������ȱ�ԭ�ַ�����������");
// //         return 0;
// //     }
// //     for(int i = 0; i < strlen(str); i++)
// //     {
// //         if(str[i] == f_str[0])
// //         {
// //             int key = 0;
// //             for(int j = 1; j < strlen(f_str) && key == 0; j++)
// //             {
// //                 if(str[i + j] != f_str[j]) key = 1;
// //             }
// //             if(key == 0)
// //             {
// //                 for(int j = 0; j < strlen(f_str); j++)
// //                 {
// //                     str[i + j] = ' ';
// //                 }
// //                 i += (strlen(f_str) - 1);
// //             }
// //         }
// //     }
// //     // char* xy;
// //     // xy = (char*)malloc(sizeof(str));
// //     int j = 0;
// //     for(int i = 0; i < strlen(str); i++)
// //     {
// //         if(str[i] != ' ')str[j++] = str[i];
// //     }
// //     str[j] = '\0';
// //     printf("ɾ�����ַ���Ϊ%s", str);
// // }

// // int main()
// // {
// //     char c[100];
// //     printf("���Թ���1���ַ���ת������������һ���ַ���");
// //     scanf("%s", c);
// //     int x = S_To_I(c);
// //     printf("ת����Ϊ%d\n", x);
// //     printf("���Թ���2���ҵ�����Ӵ���������һ���ַ���");
// //     scanf("%s", c);
// //     Long_S(c);
// //     // printf("ת����Ϊ%d\n", x);
// //     printf("���Թ���3���ַ���ɾ��һ���ַ�����������һ���ַ���");
// //     scanf("%s", c);
// //     printf("���Թ���3���ַ���ɾ��һ���ַ���������ɾ�����ַ���");
// //     char s[20];
// //     scanf("%s", s);
// //     // int x = S_To_I(c);
// //     Del_S_U_S(c, s);
// // }

// #include<stdio.h>
// #include<stdlib.h>
// #include<string.h>

// void BB_TO_B(int* a, int n)
// {
//     int j = 0;
//     int* arr = (int*)malloc(sizeof(int) * n);
//     memset(arr, 0, n);
//     arr[0] = a[0]; j = 1;
//     for(int i = 0; i < n; i++)
//     {
//         int tmp = a[i];
//         // printf("now :%d\t", tmp);
//         for(int k = 0; k < j; k++)
//         {
//             if(tmp > arr[k] && k == j - 1)
//             {
//                 arr[j++] = tmp;
//                 break;
//             }
//             else if(tmp == arr[k]) break;
//             else if(tmp < arr[k])
//             {
//                 for(int x = j; x > k; x--)
//                 {
//                     arr[x] = arr[x - 1];
//                 }
//                 arr[k] = tmp;
//                 j++;
//                 break;
//             }
//         }
//     }
//     for(int i = 0; i < j; i++)
//     {
//         printf("%d\t", arr[i]);
//     }
//     printf("\n");
// }

// int main()
// {
//     int a[] = {3, 3, 4, 4, 3, 9, 4, 1, 7, 0, 8, 2, 3, 4, 9, 6};
//     BB_TO_B(a, sizeof(a)/sizeof(int));
//     for(int i = 0; i < sizeof(a)/sizeof(int); i++)
//     {
//         printf("%d\t", a[i]);
//     }
//     return 0;
// }


#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int count_visible_chars(char *fnm) 
{
    FILE *fp = fopen(fnm, "r");
    if (fp == NULL) 
    {
        return -1;
    }
    int i = 0;
    char ch;
    while ((ch = fgetc(fp)) != EOF) 
    {
        if (isgraph(ch)) {
        i++;
        }
    }
    fclose(fp);
    return i;
}

void add_line_numbers(char *fnm) 
{
    FILE *src = fopen(fnm, "r");
    if (src == NULL) 
    {
        printf("Error: cannot open source file %s\n", fnm);
        return;
    }
    
    FILE *dest = fopen("dest", "w");
    if (dest == NULL) 
    {
        printf("Error: cannot open source file dest");
        return;
    }
    int line = 1;
    char *buffer = NULL;
    size_t len = 0;
    while (getline(&buffer, &len, src) != -1) 
    {
        fprintf(dest, "%d ", line);
        line++;
        fprintf(dest, "%s", buffer);
    }
    fclose(src);
    fclose(dest);
    free(buffer);

    src = fopen(fnm, "w");
    if (src == NULL) {
        printf("Error: cannot open source file %s\n", fnm);
        return;
    }
    dest = fopen("dest", "r");
    if (dest == NULL) {
        printf("Error: cannot open destination file %s\n", "dest");
        return;
    }
    char ch;
    while ((ch = fgetc(src)) != EOF) {
        fputc(ch, dest);
    }
    fclose(src);
    fclose(dest);
}

int main() 
{
    char *fnm = "123";
    int result = count_visible_chars(fnm);
    if (result == -1) {
        printf("Error: cannot open file %s\n", fnm);
    } else {
        printf("The number of visible characters in file %s is %d\n", fnm, result);
    }
    add_line_numbers(fnm);
    return 0;
}