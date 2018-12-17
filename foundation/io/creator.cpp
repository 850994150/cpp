/*
 **********************************************************
 * Author       : M_Kepler
 * EMail        : m_kepler@foxmail.com
 * Last modified: 2018-08-20 14:06:23
 * Filename     : creator.cpp
 * Description  : 
 * 功能: 没ms毫秒往file_name写入一行; 使用uuid生成随机码  
 * 使用: [exec.out] file_name ms
 ***********************************************************
 */

#include <unistd.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <string> 
#include <iostream>
#include <time.h> 
#include <uuid/uuid.h>

using namespace std;

void uuid2string(const uuid_t uu, char* const str)
{
    for ( int i = 0; i < 16; ++i )
    {
        sprintf(str+i*2, "%02X", uu[i]);
    }
}

// void GenUuid(char* dest, int len)
char* GenUuid(int len)
{
    char* str;
    str = new char[len+1];
    uuid_t uuid;
    uuid_generate(uuid);
    // uuid_unparse(uuid, str);
    uuid2string(uuid, str);
    return str;
}

time_t GetCurrTimeMs()
{
    time_t currTime;
    currTime = time(NULL);
    return currTime*1000;
}


int main(int argc, const char *argv[])
{
    FILE *file;
    struct tm *t1;
    time_t t;

    char buf[100];
    char buf2[100];
    int line = 1;
    int c;

    memset(buf, 0, sizeof(buf));
    memset(buf2, 0, sizeof(buf2));
    string ReqBuf = "_ENDIAN=0&F_OP_USER=9999&F_OP_ROLE=2&F_SESSION=0123456789&F_OP_SITE=0050569e247d&F_OP_BRANCH=999&F_CHANNEL=0&USE_NODE_FUNC=522210&CUSTOMER=180022892&MARKET=0&BOARD=0&SECU_ACC=0139680203&NO_CHECK_STATUS=1";
    char* pReqBuf = (char*)ReqBuf.c_str();

    string AnsBuf = "&_1=0,0,取报表输入参数设置成功&_2=524100,RECORD_SN,记录序号,90,0,,L,,,,1,1,1,1,0";
    char* pAnsBuf = (char*)AnsBuf.c_str();

    if (argc != 3)
    {
        printf("请输入待处理的文件和时间(毫秒). e.g.: ./main file time_ms\n");
        return -1;
    }

    if ((file = fopen(argv[1], "a+")) < 0)
    {
        perror("failed to open test.txt");

        exit(-1);
    }

    while ((c = getc(file)) != EOF) //计算行数，用于下次打开时能够衔接上之前的行数 
        if (c == '\n')
            line++;

    while (1)
    {
        struct timeval tv;
        gettimeofday(&tv, NULL);
        long long utimems = tv.tv_usec/1000;

        time(&t);
        t1 = localtime(&t); //获取当前时间

        char * MsgId;
        MsgId = new char[24 + 1];
        MsgId =  GenUuid(24);

        //ok: sprintf(buf, "MsgId=%s,%d%02d%02d-%02d%02d%02d-%03lld,Req: LBM=L%d,Buf=%s\n", MsgId, t1->tm_year + 1900, t1->tm_mon + 1, t1->tm_mday, t1->tm_hour, t1->tm_min, t1->tm_sec, utimems, line++, pReqBuf);
        sprintf(buf, "MsgId=%s,%d%02d%02d-%02d%02d%02d-%03lld,Req: LBM=L%d\n", MsgId, t1->tm_year + 1900, t1->tm_mon + 1, t1->tm_mday, t1->tm_hour, t1->tm_min, t1->tm_sec, utimems, line++);
        fwrite(buf, sizeof(char), strlen(buf), file);
        fflush(file);

        //ok: sprintf(buf2, "MsgId=%s,%d%02d%02d-%02d%02d%02d-%03lld,Ans: LBM=L%d,Buf=%s\n", MsgId, t1->tm_year + 1900, t1->tm_mon + 1, t1->tm_mday, t1->tm_hour, t1->tm_min, t1->tm_sec, utimems, line++, pAnsBuf);
        sprintf(buf2, "MsgId=%s,%d%02d%02d-%02d%02d%02d-%03lld,Ans: LBM=L%d\n", MsgId, t1->tm_year + 1900, t1->tm_mon + 1, t1->tm_mday, t1->tm_hour, t1->tm_min, t1->tm_sec, utimems, line++);
        fwrite(buf2, sizeof(char), strlen(buf2), file); // 写到缓存
        fflush(file); // 刷新缓冲区
        // sleep(1); // 秒 
        int utime = atoi(argv[2]);
        usleep(utime * 1000); // 毫秒 
    }

    return 0;
}


// g++ creator.cpp -luuid
