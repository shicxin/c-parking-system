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
