#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include"right.h"
#include"hello.h"/

int IsRight()
{
    int key = 0;
    FILE* fp;
    char* user_name,*user_paswd;
    user_name = (char*)malloc(user_len * sizeof(char));
    user_paswd = (char*)malloc(paswd_len * sizeof(char));
    if((fp = fopen(".\\data\\user_file","r")) == NULL)
    {
        printf("Can not open user_file file\n");
        exit(0);
    }
    char*name, *paswd;
    name = (char*)malloc(100*sizeof(char));
    paswd = (char*)malloc(100*sizeof(char));
    puts("请输入用户名：");
    scanf("%s", name);
    puts("请输入密码：");
    scanf("%s", paswd);
    fgets(user_name, user_len, fp);
    fgets(user_paswd, paswd_len, fp);

    //puts(name);
    //puts(user_name);
    //puts(paswd);
    //puts(user_paswd);

    //puts(strcmp(name,user_name)==0?"1":"0");
    //puts(strcmp(paswd,user_paswd)==0?"1":"0");
    if(strcmp(paswd, user_paswd) == 0 && strcmp(name, user_name) == 0)key = 1;
    else key = 0;
    free(name);
    free(user_name);
    free(paswd);
    free(user_paswd);
    fclose(fp);
    key == 0 ? (NOW--) : (NOW = 1);
    //printf("%d",NOW);//输出错误次数
    return key;
}
