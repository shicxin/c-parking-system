// // #include <stdio.h>

// // int main() {
// //     FILE *file;
// //     char buffer[1024];

// //     file = fopen("123", "r"); // 以只读方式打开文件
// //     if (file == NULL) {
// //         printf("无法打开文件\n");
// //         return 1;
// //     }

// //     while (fgets(buffer, sizeof(buffer), file) != NULL) { // 循环读取文件内容
// //         printf("%s", buffer); // 输出每一行的内容
// //     }

// //     fclose(file); // 关闭文件
// //     return 0;
// // }
// #include <stdio.h>

// int main() {
//     FILE *file;
//     char buffer[1024];
//     int a, b, c;
//     float d;

//     file = fopen("123", "r"); // 以只读方式打开文件
//     if (file == NULL) {
//         printf("无法打开文件\n");
//         return 1;
//     }
//     char s[10];
//     fscanf(file, "%s %d", s, &a); // 读取四个整数和一个浮点数
//     fclose(file); // 关闭文件

//     printf("%s %d\n", s, a); // 输出读取的数据

//     return 0;
// }


// #include <stdio.h>
// #include <time.h>

// int main() {
//     time_t rawtime; // time_t类型，表示自1970年1月1日以来的秒数
//     struct tm * timeinfo; // struct tm类型，用于存储日期和时间的结构体
//     int seconds; // int类型，表示当前时间距离1970年1月1日的秒数
//     char buffer[26]; // char类型，用于存储格式化后的日期和时间字符串

//     time (&rawtime); // 获取自epoch以来的秒数
//     timeinfo = localtime (&rawtime); // 转换为分解时间表示
//     seconds = difftime(time(NULL), rawtime); // 以秒为单位获取now和epoch之间的差值
//     strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo); // 将日期和时间格式化为字符串

//     printf("Current time: %s\n", buffer); //打印格式化的日期和时间字符串
//     printf("Time since epoch: %d seconds\n", seconds); // 以秒为单位打印now和epoch之间的差值

//     return 0;
// }



#include<stdio.h>

int main()
{
    FILE *fp = fopen("data.txt", "r");
    if (fp == NULL) {
        printf("Failed to open file\n");
        return 1;
    }

    double x, y, z;
    while (fscanf(fp, "%lf %lf %lf", &x, &y, &z) == 3) {
        printf("x=%f y=%f z=%f\n", x, y, z);
    }

    fclose(fp);

}