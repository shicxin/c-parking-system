#include<stdio.h>
#include <stdlib.h>
#include"read_nfs_sfn.h"

/// @brief 从键盘读取一个字符串，并转换为一个int类型的值
/// @return int
int read_int(char* s)
{
    // char s[20]; // 定义一个字符串数组，用于存储输入的字符串
    int i; // 定义一个int类型的变量，用于存储转换后的值
    // printf("请输入一个整数：\n"); // 打印提示信息
    // scanf("%s", s); // 调用scanf函数，从键盘读取一个字符串，并存储在s中
    i = atoi(s); // 调用atoi函数，将字符串转换为int类型，并赋值给i
    return i; 
}

/// @brief  从键盘读取一个字符串，并转换为一个double类型的值
/// @return double
double read_double(char* s)
{
    // char s[20]; // 定义一个字符串数组，用于存储输入的字符串
    double d; // 定义一个double类型的变量，用于存储转换后的值
    // printf("请输入一个小数：\n"); // 打印提示信息
    // scanf("%s", s); // 调用scanf函数，从键盘读取一个字符串，并存储在s中
    d = atof(s); // 调用atof函数，将字符串转换为double类型，并赋值给d
    return d; // 返回d的值
}

/// @brief 用于将一个字符串转换为一个long long类型的值，并返回该值
/// @param s 存储位置
/// @return long long
long long read_longlong(char* s)
{
    long long ll; // 定义一个long long类型的变量，用于存储转换后的值
    ll = atoll(s); // 调用atoll函数，将字符串转换为long long类型，并赋值给ll
    return ll; // 返回ll的值
}


/// @brief 用于将一个int类型的值转换为一个字符串，并存储在传入的char*指针所指向的数组中
/// @param i 整数
/// @param s 保存字符串
void int_to_str(int i, char* s)
{
    sprintf(s, "%d", i); // 调用sprintf函数，将int类型的值按照%d的格式写入到s所指向的数组中
}

/// @brief 用于将一个double类型的值转换为一个字符串，并存储在传入的char*指针所指向的数组中
/// @param d double
/// @param s 保存字符串
void double_to_str(double d, char* s)
{
    sprintf(s, "%.02lf", d); // 调用sprintf函数，将double类型的值按照%lf的格式写入到s所指向的数组中
}

/// @brief 用于将一个long long类型的值转换为一个字符串，并存储在传入的char*指针所指向的数组中
/// @param ll 
/// @param s 
void longlong_to_str(long long ll, char* s)
{
    sprintf(s, "%lld", ll); // 调用sprintf函数，将long long类型的值按照%lld的格式写入到s所指向的数组中
}