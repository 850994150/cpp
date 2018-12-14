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

int iCommitCnt = 500;
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

    debugLog(__FILE__, __LINE__, "%s", pcszSql);

    if (0 != iRetCode)
    {
        printf("insert failed! iRetCode:%d\n", iRetCode);
    }

    // 多进程与全局变量 (http://bbs.chinaunix.net/thread-3746905-1-1.html)
    g_nCommitCount++;
    if (g_nCommitCount % iCommitCnt == 0)
    {
        debugLog(__FILE__, __LINE__, "process:%d  - %d Commit", getpid(), g_nCommitCount);
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

    int status,i;	
    for (i = 0; i < vecFileList.size(); i++)
    {
        ReadFile(vecFileList[i].c_str(), iCommitCnt, SqlCommit);
        if (g_nCommitCount <  iCommitCnt || g_nCommitCount % iCommitCnt >0)
        {
            debugLog(__FILE__, __LINE__, "process:%d - %d Commit", getpid(), g_nCommitCount);
        }
        debugLog(__FILE__, __LINE__, "%d exit(0)", getpid());
        // exit(0);
    }
    return 0;
} 

/*
单进程：
Tue Dec  4 17:24:24 DST 2018
Tue Dec  4 17:25:19 DST 2018
6047条insert
*/