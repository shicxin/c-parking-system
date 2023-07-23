// // // // // #include <stdio.h>

// // // // // int main() {
// // // // //     FILE *file;
// // // // //     char buffer[1024];

// // // // //     file = fopen("123", "r"); // 以只读方式打开文件
// // // // //     if (file == NULL) {
// // // // //         printf("无法打开文件\n");
// // // // //         return 1;
// // // // //     }

// // // // //     while (fgets(buffer, sizeof(buffer), file) != NULL) { // 循环读取文件内容
// // // // //         printf("%s", buffer); // 输出每一行的内容
// // // // //     }

// // // // //     fclose(file); // 关闭文件
// // // // //     return 0;
// // // // // }
// // // // #include <stdio.h>

// // // // int main() {
// // // //     FILE *file;
// // // //     char buffer[1024];
// // // //     int a, b, c;
// // // //     float d;

// // // //     file = fopen("123", "r"); // 以只读方式打开文件
// // // //     if (file == NULL) {
// // // //         printf("无法打开文件\n");
// // // //         return 1;
// // // //     }
// // // //     char s[10];
// // // //     fscanf(file, "%s %d", s, &a); // 读取四个整数和一个浮点数
// // // //     fclose(file); // 关闭文件

// // // //     printf("%s %d\n", s, a); // 输出读取的数据

// // // //     return 0;
// // // // }


// // // #include <stdio.h>
// // // #include <time.h>

// // // int main() {
// // //     time_t rawtime; // time_t类型，表示自1970年1月1日以来的秒数
// // //     struct tm * timeinfo; // struct tm类型，用于存储日期和时间的结构体
// // //     int seconds; // int类型，表示当前时间距离1970年1月1日的秒数
// // //     char buffer[26]; // char类型，用于存储格式化后的日期和时间字符串

// // //     // time (&rawtime); // 获取自epoch以来的秒数
    
// // //     FILE* fp = NULL;
// // //     fp = fopen("sys", "r");
// // //     fscanf(fp, "%lld", &rawtime);


// // //     timeinfo = localtime (&rawtime); // 转换为分解时间表示
// // //     seconds = difftime(time(NULL), rawtime); // 以秒为单位获取now和epoch之间的差值
// // //     strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo); // 将日期和时间格式化为字符串

// // //     printf("Current time: %s\n", buffer); //打印格式化的日期和时间字符串
// // //     printf("Time since epoch: %d seconds\n", seconds); // 以秒为单位打印now和epoch之间的差值
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

// // ///7.19作业///////////////////////////////////////
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
// //     printf("最长的连续字符为：%d\n", ma);
// // }

// // void Del_S_U_S(char* str, char* f_str)
// // {
// //     if(strlen(f_str) > strlen(str)) 
// //     {
// //         puts("要删除字符串长度比原字符长！！！！");
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
// //     printf("删除后字符串为%s", str);
// // }

// // int main()
// // {
// //     char c[100];
// //     printf("测试功能1，字符串转整数，请输入一个字符串");
// //     scanf("%s", c);
// //     int x = S_To_I(c);
// //     printf("转换后为%d\n", x);
// //     printf("测试功能2，找到最长的子串，请输入一个字符串");
// //     scanf("%s", c);
// //     Long_S(c);
// //     // printf("转换后为%d\n", x);
// //     printf("测试功能3，字符串删除一个字符串，请输入一个字符串");
// //     scanf("%s", c);
// //     printf("测试功能3，字符串删除一个字符串，请输删除的字符串");
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