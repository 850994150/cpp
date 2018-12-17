/*
 **********************************************************
 * Author       : M_Kepler
 * EMail        : m_kepler@foxmail.com
 * Last modified: 2018-08-05 12:19:12
 * Filename     : io.c
 * Description  :
 * c语言操作文件是通过指针来完成的; 文件的读写等是通过库函数完成 
 ***********************************************************
 */
#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *fpin, *fpout;
    int a, i, mymax = -99999;
    fpin = fopen("myfile.dat", "w"); //以写的方式打开文件
    if (!fpin)                       //判断文件打开是否成功
    {
        printf("open wrong\n");
        exit(1);
    }
    printf("输入十个数字\n");
    for (i = 0; i < 10; i++) //向文件写入数据
    {
        scanf("%d", &a);
        fprintf(fpin, "%d\n", a);
    }
    printf("写入完成!\n");            //写入完成提示
    fclose(fpin);                     //关闭文件
    fpout = fopen("myfile.dat", "r"); //以读的方式打开文件
    if (!fpout)                       //判断文件是否打开成功
    {
        printf("open wrong\n");
        exit(1);
    }
    while (!feof(fpout)) //判断是否到文件尾
    {
        fscanf(fpout, "%d", &a); //从文件中读取数据
        if (a > mymax)           //找出文件数据中的最大者
            mymax = a;
    }
    fclose(fpout);             //关闭文件
    printf("Max=%d\n", mymax); //输出最大者
    return 0;
}