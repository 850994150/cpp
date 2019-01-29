#include <iostream>
#include <chrono>
#include <vector>
#include <assert.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>
#include <iostream>   // std::cout
#include <functional> // std::ref
#include <thread>     // std::thread
#include <future>     // std::promise, std::future
using namespace std;
// typedef void (*pLineCallback)(int iCnt, const char *pcszContent);
typedef void(pLineCallback)(string strContent);

const int iCommitCnt = 100;
#define MAX 40000

void SwapNeighbourCharacters(string str_swap)
{
    int i = 0;
    char tmp = {0};
    // string str_swap = "HuangJinJie";
    char *pData = (char *)str_swap.c_str();
    char *pCur = (char *)str_swap.c_str();

    // 1.
    while (*pCur != '\0' && i != str_swap.length() - 1)
    {
        tmp = *pCur;
        *(pData + i) = *(pCur + 1);
        *(pData + i + 1) = tmp;
        pCur = pData + i + 2;
        i += 2;
    }
    std::string strResult;
    strResult = pData;
    cout << strResult << endl;

    int len = str_swap.length();
    char chTmp[len];
    str_swap.copy(chTmp, len, 0);

    // 2.
    for (size_t i = 0; i < len - 1; i = i + 2)
    {
        tmp = chTmp[i];
        chTmp[i] = chTmp[i + 1];
        chTmp[i + 1] = tmp;
    }
    chTmp[len] = '\0';
    strResult = chTmp;

    cout << strResult << endl;
}

time_t GetCurrentTimeMs()
{
    time_t currTime;
    currTime = time(NULL);
    return currTime * 1000 + clock();
}

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
        pf(line);
    }

    if (line)
    {
        free(line);
    }
}

void test()
{
    vector<string> vecInt{"a", "b", "c", "d"};
    printf("%s\n", vecInt[0].c_str());
    vecInt.erase(vecInt.begin());
    printf("%s\n", vecInt[0].c_str());

    /* code */
    int i = 5;
    int *p = &i;
    p++;
    cout << *p << endl;

    char a[10] = "abc", b[10] = "012", c[10] = "xyz";
    strcpy(a + 1, b + 2);
    puts(strcat(a, c + 1));

    char szTest[14] = "ä¸­å›½";
    // cout << "length" << szTest.length() << endl;
    cout << "length: " << sizeof(szTest) / sizeof(char) << endl;
    cout << "length: " << strlen(szTest) << endl;

    time_t nowMs = GetCurrentTimeMs();
    cout << "nowMs: " << nowMs << endl;

    /* c++11 */
    auto time_now = chrono::system_clock::now();
    auto duration_in_ms = chrono::duration_cast<chrono::milliseconds>(time_now.time_since_epoch());
    cout << "chrono: " << duration_in_ms.count() << endl;

    char szLBM[32 + 1];
    memset((void *)szLBM, 0x00, sizeof(szLBM));
    string strLbm = "L1100125";
    char *p_szLbm = (char *)strLbm.c_str();
    cout << atol(p_szLbm) << endl;

    char szCurrTime[64] = {0};
    // char *F_RUNTIME = "123123";
    string strNowTime = "2018-12-20-14.11.42.333333";
    char *F_RUNTIME = (char *)strNowTime.c_str();
    cout << F_RUNTIME + 11 << endl;
    strncpy(szCurrTime, F_RUNTIME + 11, sizeof(szCurrTime));
    szCurrTime[8] = '\0';
    cout << szCurrTime << endl;
}

void print(string line)
{
    printf("%s\n", line.c_str());
}

void SetMsgText(char *szMsgText, int p_iMsgCode, ...)
{
    char szErrorMsg[4096];
    va_list lpvlArgPtr;
    va_start(lpvlArgPtr, p_iMsgCode);
    vsnprintf(szErrorMsg, sizeof(szErrorMsg) - 1, szMsgText, lpvlArgPtr);
    va_end(lpvlArgPtr);
    cout << szErrorMsg << endl;
}

int test20190124()
{
    char chstr[] = "abcde";
    cout << chstr << endl;
    cout << *chstr << endl;
    cout << *chstr + 1 << endl;
    cout << *(chstr + 1) << endl;

    /*字符常量不可更改*/
    char *p = (char *)"qwertyuiop";
    // p[3] = 'b'; // error
    // *p = 'b'; // error
    // *p++; // success
    // p = "edf"; // success

    while (*p)
    {
        printf("%c ", *p);
        p++;
    }

    cout << p << endl;

    int iRetCode = 100199;
    char szMsgText[] = "没有查询到客户[%lld]征信信息";
    cout << &szMsgText << endl;
    // SetMsgText(szMsgText, iRetCode, 170005578);
    SetMsgText(szMsgText, iRetCode, "打");

    int iArray[4] = {1, 2, 3, 4};
    cout << sizeof(iArray) / sizeof(int) << endl;

    int timems = 1548232725;
    cout << timems % 100 << endl;

    SwapNeighbourCharacters("HuangJinJie");

    int array[] = {2, 4, 6, 8};
    // 用引用会改变array里的值
    for (auto &x : array)
    {
        x++;
    }
    for (auto x : array)
    {
        cout << x;
    }
    cout << endl;

    // ReadFile("./sql_0000.sql", iCommitCnt, print);
    return 0;
}

void setValue(std::future<int> &fut, int value)
{
    std::promise<int> prom;  // 生成一个 std::promise<int> 对象.
    fut = prom.get_future(); // 和 future 关联.
    prom.set_value(value);   // 设置共享状态的值, 此处和线程t保持同步.
}

void printValue(std::future<int> &fut)
{
    int x = fut.get();                   // 获取共享状态的值.
    std::cout << "value: " << x << '\n'; // 打印 value: 10.
}

int test_future()
{
    std::future<int> fut;
    std::thread set_thread(setValue, std::ref(fut), 10); // 将 future 交给另外一个线程t.
    std::thread print_thread(printValue, std::ref(fut)); // 将 future 交给另外一个线程t.

    set_thread.join();
    print_thread.join();
    return 0;
}

struct node
{
    char name[30];
} que[MAX];
/*
BKDRHash函数的解析链接：
http://blog.csdn.net/djinglan/article/details/8812934
*/
unsigned int BKDRHash(char *str)
{
    unsigned int seed = 131313; //也可以乘以31、131、1313、13131、131313..
    unsigned int hash = 0;
    while (*str)
    {
        hash = hash * seed + (*str++);
    }

    return hash % 32767; //最好对一个大的素数取余
}
int test_bkdr()
{
    int i = 0, n, t, j;
    char a[MAX][30];
    char temp[300];
    memset(a, 0, sizeof(a));

    cin >> n;
    for (i = 0; i < n; i++)
    {
        cin >> que[i].name;
        strcpy(a[BKDRHash(que[i].name)], que[i].name);
    }
    cout << "请输入要查找的字符串:";
    while (~scanf("%s", temp))
    {
        if (strcmp(a[BKDRHash(temp)], temp) == 0)
            cout << "yes" << endl;
        else
        {
            cout << "no" << endl;
            strcpy(a[BKDRHash(temp)], temp);
            strcpy(que[i++].name, temp);
        }
    }
    for (j = 0; j <= i; j++)
    {
        cout << que[j].name << endl; //含有的所有字符串
    }
    return 0;
}

auto testsum(int a, int b) -> decltype(a)
{
    int sum ;
    sum = a + b;
    return sum;
}

int main(int argc, char const *argv[])
{
    // test_bkdr();
    vector<string> strvecMsg{"111", "222", "333", "444", "555", "666", "777", "888", "999"};
    cout << strvecMsg[1];
    return 0;
}

