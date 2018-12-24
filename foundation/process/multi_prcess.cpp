#include <stdio.h> 
#include <string>
#include <vector>
#include <unistd.h> 
#include <dirent.h>
#include <stdarg.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include <sys/types.h> 
using namespace std;

FILE* fpInsert;
int iCommitCnt = 2000;
int g_nCommitCount =0;

typedef void (*pLineCallback)(int iCnt, const char *pcszContent);

void debugLog(const char * FileName, int Line, const char * msg, ...)
{
	FILE *fp;
	char ViewStr[4096] = { 0 };
	char bufStr[10240] = { 0 };
	char szOccurTime[32 + 1] = { 0 };

	va_list arg_ptr;
	va_start(arg_ptr, msg);
	vsprintf(ViewStr, msg, arg_ptr); // sprintf(ViewStr, msg, arg_ptr);
	va_end(arg_ptr);

	time_t timep;
	time(&timep);
	strftime(szOccurTime, sizeof(szOccurTime), "%Y-%m-%d %H:%M:%S", localtime(&timep));

	sprintf(bufStr, "[Time:%s][File:%s][Line:%d][%s]\n", szOccurTime, FileName, Line, ViewStr);

	fp = fopen("./debug.log", "a+");
	if (fp == NULL)
	{
		printf("open file error\n");
		return;
	}
	fprintf(fp, "%s\n", bufStr);
	fclose(fp);
	// printf("%s", bufStr);
	return;
}
// 获取文件夹下所有extenStr后缀的文件名列表
// void GetAllFile(const char *dirPath, vector<string> &vecFileList, const char *extenStr = "sql")
void GetAllFile(const char *dirPath, vector<string> &vecFileList)
{
    const char *extenStr = "sql";
    DIR *dir = opendir(dirPath);
    string strSplit  =  "/";
    dirent *pDirent = NULL;

    while ((pDirent = readdir(dir)) != NULL)
    {
        if (strstr(pDirent->d_name, extenStr))
        {
            string pathFile = dirPath + strSplit  +  string(pDirent->d_name);
            vecFileList.push_back(pathFile);
        }
    }
    closedir(dir);
}



// 执行sql语句
void SqlCommit(int iCommitCnt, const char* pcszSql)
{
    int iRetCode = 0;

    fprintf(fpInsert, "%s", pcszSql);
    fflush(fpInsert);

    if (0 != iRetCode)
    {
        printf("insert failed! iRetCode:%d\n", iRetCode);
    }

    // 多进程还有这个吗?
    // TODO write
    g_nCommitCount++;
    // TODO read
    if (g_nCommitCount % iCommitCnt == 0)
    {
        fprintf(fpInsert, "sub process %d - g_nCommitCount = %d commit\n", getpid(), g_nCommitCount);
        fflush(fpInsert);
    }
}

// 读入strFile文件行交给pf函数处理
void ReadFile(const std::string &strFile, int iCommitCnt, pLineCallback pf)
{
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    size_t read;

    fp = fopen(strFile.c_str(), "r");
    assert(fp);

    while ((read = getline(&line, &len, fp)) != -1)
    {
        pf(iCommitCnt, line);
    }

    if (line)
    {
        free(line);
    }
}

int main(int argc, char const *argv[])
{ 
    vector<string>vecFileList;
    string path = "./file";
    GetAllFile(path.c_str(), vecFileList);

    fpInsert = fopen("./insert.log", "w+");
    if (!fpInsert)
    {
        return -1;
    }

    int status,i;	
    for (i = 0; i < vecFileList.size(); i++)
    {
        status = fork();
        // 每次循环时，假设发现是子进程就直接从创建子进程的循环中跳出来。不让你进入循环，这样就保证了每次仅仅有父进程来做循环创建子进程的工作	
        // 每次循环时, 假设发现是子进程就从创建子进程的循环跳出;
        // 直接fork() 2次的话, 最终会产生4个进程, 其中3个子进程
        // 保证每次都是由父进程来做创建子进程的工作
        if (status == 0 || status == -1) break;
    }
    if (status == -1)
    {
        // error	
        printf("fork error\n");
    }
    else if (status == 0) // 每一个子进程都会运行的代码	
    {
        // sub process
        // 每次fork完成i会加一, 所以这里i就是要处理的那个文件的编号
        printf("sub process:%d\t%d\t%s\n", getpid(), i, vecFileList[i].c_str());
        ReadFile(vecFileList[i].c_str(), iCommitCnt, SqlCommit);

        // TODO read
        if (g_nCommitCount <  iCommitCnt || g_nCommitCount % iCommitCnt >0)
        {
            fprintf(fpInsert, "sub process %d - g_nCommitCount = %d commit\n", getpid(), g_nCommitCount);
            fflush(fpInsert);
        }
        printf("sub process %d exited - par process is: %d\n", getpid(), getppid());
        exit(0);
    }
    else
    {
        // parent process
        // 这里父进程先于子进程退出, 子进程会编程孤儿进程, 并被init进程接管, 来完成后续清理工作
        printf("par process:%d\t%d\t\n", getpid(), i);
        printf("par process %d exited\n", getpid());
    }
    return 0;
} 

/*
多进程：
Tue Dec  4 17:27:51 DST 2018
Tue Dec  4 17:28:10 DST 2018
6047条insert
*/

/*
Q1: 俗话说的fork之后是拷贝一份父进程, 难道子进程重新从main函数执行?
A1: 当然不是, 如果是这样, 那岂不是会死循环创建进程? 事实是, 子进程会继续fork()之后的代码

Q2: 怎么一次创建多个子进程? 如果是fork(); fork();是错误的
A1: https://blog.csdn.net/AJDJ26/article/details/84322198

Q3: 怎么让进程结束? 比如我的程序是一个进程处理一个文件. 那么怎么让子进程处理完自己的文件就退出呢?
A3:

Q4: 父进程下的子进程提交数据库, 不能共用父进程中打开的那个连接,必须每个进程单独打开一个连接, 否则会导致锁表 

*/