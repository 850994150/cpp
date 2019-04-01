#include <iostream>
#include <chrono>
#include <vector>
#include <assert.h>
#include <string.h>
#include <string>
#include <time.h>
#include <stdarg.h>
#include <iostream>   // std::cout
#include <functional> // std::ref
#include <thread>     // std::thread
#include <future>     // std::promise, std::future
#include <map>
#include <unordered_map>
#include <math.h>
#include <memory>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
using namespace std;

// typedef void (*pLineCallback)(int iCnt, const char *pcszContent);
typedef void(pLineCallback)(string strContent);

const int iCommitCnt = 100;
const double eps = 1e-6;
#define MAX 40000

typedef char DataType;
typedef struct stBiTree
{
    DataType data;
    struct stBiTree *lchild, *rchild; // 未定义就先使用
} stTreeNode, *p_TreeNode;

typedef struct tagDBFHead
{
    char Mark;
    unsigned char Year;
    unsigned char Month;
    unsigned char Day;
    // 4 + 4 = 8
    long RecCount;
    // 8
    unsigned short DataOffset;
    unsigned short RecSize;
    // 4 + 4 = 8
    char Reserved[20];
    // 8 + 8 + 4 + 4 = 24
} DBFHEAD, *LPDBFHEAD;
// sizeof(DBFHEAD) = 40

typedef struct stDBFHead
{
    char szMark[1]; // 版本信息
    char szYear[1];
    char szMonth[1];
    char szDay[1];
    char szRecCount[4];   // 4字节保存记录数
    char szDataOffset[2]; // 2字节保存文件头字节数
    char szRecSize[2];    // 2字节保存每行数据的长度
    char Reserved[20];
} stDbfHead;

class Solution
{
  public:
    vector<int> twoSum(vector<int> &nums, int target)
    {
        unordered_map<int, int> mapping;
        vector<int> result;
        for (int i = 0; i < nums.size(); i++)
        {
            mapping[nums[i]] = i;
        }
        for (int i = 0; i < nums.size(); i++)
        {
            const int gap = target - nums[i];
            if (mapping.find(gap) != mapping.end() && mapping[gap] > i)
            {
                // result.push_back(i + 1);
                // result.push_back(mapping[gap] + 1);
                result.push_back(i);
                result.push_back(mapping[gap]);
                break;
            }
        }
        return result;
    }
};

string WString2String(const std::wstring &ws)
{
    std::string strLocale = setlocale(LC_ALL, "");
    const wchar_t *wchSrc = ws.c_str();
    size_t nDestSize = wcstombs(NULL, wchSrc, 0) + 1;
    char *chDest = new char[nDestSize];
    memset(chDest, 0, nDestSize);
    wcstombs(chDest, wchSrc, nDestSize);
    std::string strResult = chDest;
    delete[] chDest;
    setlocale(LC_ALL, strLocale.c_str());
    return strResult;
}

string GetMsgValue(string strOrig, string strKey, string strSplit)
{
    string strRetValue = "";
    int iStrOrigLen;
    int iStrKeyLen;
    size_t uiPosKeyBegin;
    size_t uiPosKeyEnd;
    size_t uiPosStrSplit;

    iStrOrigLen = strOrig.length();
    iStrKeyLen = strKey.length();
    uiPosKeyBegin = strOrig.find(strKey);

    if (uiPosKeyBegin != string::npos)
    {
        // 从key的位置开始,第一次出现 str_split 的位置
        uiPosStrSplit = strOrig.substr(uiPosKeyBegin).find(strSplit);
        if (uiPosStrSplit != string::npos)
        {
            uiPosKeyEnd = uiPosKeyBegin + uiPosStrSplit;
        }
        else
        {
            uiPosKeyEnd = iStrOrigLen;
        }
        int pos_begin = uiPosKeyBegin + iStrKeyLen + 1; // +1 跳过'='字符
        int value_len = uiPosKeyEnd - pos_begin;
        strRetValue = strOrig.substr(pos_begin, value_len);
        return strRetValue;
    }
    return strRetValue;
}

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

void swap(int &a, int &b)
{
    int tmp = a;
    a = b;
    b = tmp;
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
int test_hash()
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
    int sum;
    sum = a + b;
    return sum;
}

int test20190210(int argc, char const *argv[])
{
    // test_hash();
    int ii = 010;
    cout << ii + 1 << endl;

    int a = 1, b = 2, c = 2, t;
    while (a < b < c)
    {
        t = a;
        a = b;
        b = t;
        c--;
    }
    printf("%d,%d,%d\n", a, b, c);
    int n[3][3], i, j;
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            n[i][j] = i + j;

    for (i = 0; i < 2; i++)
        for (j = 0; j < 2; j++)
            n[i + 1][j + 1] += n[i][j];

    printf("%d\n", n[i][j]);

    if (strcmp("20160301", "20090624") == 0)
    {
        cout << "same" << endl;
    }
    else
    {
        cout << "diff" << endl;
    }
    stDbfHead dbfHead;
    memset(&dbfHead, 0x00, sizeof(stDbfHead));
    cout << sizeof(dbfHead) << endl;
    dbfHead.szMark[0] = 0x03;
    string msg = "NAME:YEAR,TYPE:C,LEN:20";
    cout << GetMsgValue(msg, "NAME", ",") << endl;

    time_t now;
    time(&now);
    tm *tp = localtime(&now);

    short offset = 161;
    memcpy(&dbfHead.szDataOffset, &offset, 2);

    memmove(&dbfHead.szYear, &tp->tm_year, sizeof(dbfHead.szYear));
    memmove(&dbfHead.szMonth, &tp->tm_mon, sizeof(dbfHead.szMonth));
    memmove(&dbfHead.szDay, &tp->tm_mday, sizeof(dbfHead.szDay));

    // 存在char数组里的数怎么进行加减读取
    uint8_t uinta = 0x03;
    cout << uinta << uinta++ << endl;

    uint8_t iLen;
    char aaa[1];
    string x = "LEN:20000";
    string strTmp = GetMsgValue(x, "LEN", ",");
    int iTmp = atoi(GetMsgValue(x, "LEN", ",").c_str());
    memcpy(aaa, &iTmp, sizeof(aaa)); // 从string到char[]
    // memcpy(aaa, strTmp.c_str(), sizeof(aaa));
    memcpy(&iLen, aaa, 1); // 从char[]到int
    printf("%d\n", iLen);

    union DataUnion {
        char buf[4];
        uint32_t number;
    };

    auto iiTmp = atoi(strTmp.c_str());
    char aa[4];
    memcpy(aa, &iiTmp, sizeof(iiTmp));
    printf("iiTmp = %d\n", iiTmp);
    printf("iTmp=%d, %x\t%x\t%x\t%x\n", iiTmp, aa[0], aa[1], aa[2], aa[3]);

    wstring cc = L"wstring中文";
    string strcc = WString2String(cc);
    wcout << cc << endl;
    cout << strcc << endl;

    return 0;
}

void createTree(p_TreeNode &T)
{
    DataType data;
    cin >> data;
    if (data == '#')
    {
        T = NULL;
    }
    else
    {
        T = (p_TreeNode)malloc(sizeof(p_TreeNode));
        T->data = data;
        createTree(T->lchild);
        createTree(T->rchild);
    }
}

void PreVisit(p_TreeNode T)
{
    if (T != NULL)
    {
        if (T->data != '#')
        {
            printf("%c ", T->data);
        }
        PreVisit(T->lchild);
        PreVisit(T->rchild);
    }
}

void DestroyBinTree(p_TreeNode T)
{
    if (T == NULL)
        return;
    DestroyBinTree(T->lchild);
    DestroyBinTree(T->rchild);
    T->lchild = NULL;
    T->rchild = NULL;
    free(T);
}

int BinSearch(int array[], int target, int len)
{
    int low = 0;
    size_t hight = len - 1; // XXX 这个len如果在函数内部计算的话, 效果是完全不一样的
    while (low <= hight)
    {
        int mid = (low + hight) / 2; //取中间值mid点位置
        if (array[mid] == target)    //寻找到目标数
        {
            return mid;
        }
        if (array[mid] > target) //如果中间值大于目标数，则将highr点位置移动mid位置左边
        {
            hight = mid - 1;
        }
        if (array[mid] < target) //如果中间值小于目标数，则将low点位置移动mid位置右边
        {
            low = mid + 1;
        }
    }
    return 0;
}

int test190314()
{
    printf("         A         \n");
    printf("        / \\       \n");
    printf("       B   #       \n");
    printf("     /   \\        \n");
    printf("   C       D       \n");
    printf("  / \\    /   \\   \n");
    printf(" #   #  E     F    \n");
    printf("       / \\   / \\ \n");
    printf("      #   G #   #  \n");
    printf("         / \\      \n");
    printf("        #   #	   \n");

    printf("         e          \n");
    printf("       /   \\       \n");
    printf("     b       f      \n");
    printf("   /   \\    / \\   \n");
    printf("  a     d  #   g    \n");
    printf(" / \\   / \\    / \\\n");
    printf("#   # c   #  #   #  \n");
    printf("     / \\           \n");
    printf("    #   #			\n");

    /*
    p_TreeNode p_Tree;
    createTree(p_Tree);
    PreVisit(p_Tree);
    DestroyBinTree(p_Tree);
    */
    int a = 10;
    float b = static_cast<float>(a);
    int i;
    cout << b << endl;
    // while (1 && NULL)
    while (1 && NULL)
    {
        cout << "in" << endl;
    }
    cout << "out" << endl;
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int len = sizeof(arr) / sizeof(arr[0]); // XXX 这个len如果在函数内部计算的话, 效果是完全不一样的
    cout << BinSearch(arr, 4, len) << endl;

    // printf字符串指针, 可以不加格式化字符%s; 但是printf一个非字符串指针或常量时则不行
    // 和printf("hello world"); 一样, "hello world" 入参的是该字符串的地址, 直接传char* 也一样
    char *p_print = "abcdef";
    cout << "with cout :" << p_print << endl;
    printf("with %%s: %s\n", p_print);
    cout << "without %%s:";
    printf(p_print);
    cout << endl;

    Solution clSolution;
    vector<int> nums = {2, 7, 11, 15};
    vector<int> results = clSolution.twoSum(nums, 13);
    for (auto x : results)
    {
        cout << x << endl;
    }
    float fa = 99.9f;
    double faa = 10.7;
    float fb = 99.9f;
    double fbb = 10.7;
    printf("%f\n", fa); // 99.900002
    // if (fabs(fa - fb) < eps)
    if (fa == fb)
    {
        cout << fa << " 和 " << fb << " 相等" << endl;
    }
    else
    {
        cout << fa << " 和 " << fb << " 不等" << endl;
    }
    return 0;
}

// 计算x二进制中1的数目
void count1num(int x)
{
    int countx = 0;
    while (x)
    {
        countx++;
        x = x & (x - 1);
    }
    cout << countx << endl;
}

void operator_test()
{
    /*
    【除号】的正负取舍和一般的算数一样，符号相同为正，相异为负
    【求余符号】的正负取舍和被除数符号相同
    -3/16=0     16/-3=-5     -3%16=-3      16%-3=1
    */
    int a = 5;
    int b = -5;
    printf(("%d,%d\n"), a % (-4), b % (-4));

    // 逗号表达式作为一个整体，它的值为最后一个表达式的值
    int c = (1, 2, 3, 4, 5);
    cout << c << endl;

    count1num(9999);
}

void memory_pointer()
{
    // auto_ptr
    /* shared_ptr */
    int a = 10;
    int *p = new int;
    shared_ptr<int> test(p);

    shared_ptr<int> ptra = make_shared<int>(a); // 智能指针

    shared_ptr<int> ptra2(ptra); // copy

    cout << ptra.use_count() << endl;

    int b = 20;
    int *pb = &a;
    // std::shared_ptr<int> ptrb = pb;  //error
    shared_ptr<int> ptrb = make_shared<int>(b);
    ptra2 = ptrb;    // assign
    pb = ptrb.get(); // 获取原始指针

    cout << ptra.use_count() << endl;
    cout << ptrb.use_count() << endl;

    /* unique_ptr */
    {
        unique_ptr<int> uptr(new int(10)); // 绑定动态对象
        // unique_ptr<int> uptr2 = uptr;    // 不能赋值
        // unique_ptr<int> uptr2(uptr);     // 不能拷贝
        unique_ptr<int> uptr2 = move(uptr); // 转换所有权
        uptr2.release();                    //释放所有权
    }
    // 超过作用域，指针自动释放

    /* weak_ptr */
}

// 下标从0开始
// i的子节点为2i+1和2i+2
// i的父节点为 i/2 i/2 -1

void sink(int *s, int len, int k)
{
    while (2 * k + 1 <= len)
    {
        int j = 2 * k + 1;
        if (j < len && s[j] < s[j + 1])
            j++;
        if (s[j] < s[k])
            break;
        swap(s[j], s[k]);
        k = j;
    }
}
void heapSort(int *s, int len)
{
    len -= 1;
    // 从最后一个叶子结点的父节点往前建堆
    for (int i = len / 2; i >= 0; i--)
        sink(s, len, i);
    // 调整
    for (; len > 0;)
    {
        swap(s[len], s[0]);
        len--;
        sink(s, len, 0);
    }
}

class CTest
{
  public:
    CTest(string name, int id);

  private:
    string _name;
    int _id;
};

CTest::CTest(string name, int id) : _name(name), _id(id) // 初始化列表
{
}

void mystrcpy(char *dst, const char *src)
{
    if (src == NULL)
    {
        return;
    }
    while ((*dst++ = *src++) != NULL)
        ;
}

char *mystrncpy(char *dest, const char *str, int dest_len, int str_len)
{
    int n;
    assert((dest != NULL) && (str != NULL));

    char *cp = dest;
    if (dest_len > str_len)
        n = str_len;
    if (dest_len <= str_len)
        n = dest_len; // 只拷贝dest_len个字符

    while ((*cp++ = *str++) != NULL && --n)
        ;
    return dest;
}

char *mystrchr(char *str, char ch)
{
    while ((*str++ != ch) != NULL)
        ;
    return --str;
}

char *mymemcpy(char *dst, char *src, int n)
{
    // 判断是否存在内存重叠
    bool flag = dst > src && dst <= src + n;
    if (flag)
    {
        // 倒序拷贝
        char *dst_cp = dst + n - 1;
        char *src_cp = src + n - 1;
        while ((*dst_cp-- = *src_cp--) != NULL && --n)
            ;
    }
    else
    {
        while ((*dst++ = *src++) && --n)
            ;
    }
    return dst;
}

std::vector<char *> vecRes;
void StringSplitC(const char *pszString, const char *pszFlag, std::vector<char *> &vecRes)
{
    const char *p = strtok((char *)pszString, pszFlag);
    while (p != NULL)
    {
        if (strlen(p) > 0)
        {
            vecRes.push_back((char *)p);
        }

        p = strtok(NULL, pszFlag);
    }
}

int test20190329()
{
    // memory_pointer();
    int s[] = {8, 6, 3, 1, 5, 2, 4, 9};
    int len = sizeof(s) / sizeof(s[0]);
    cout << len << endl;
    heapSort(s, len);
    for (size_t i = 0; i < len; i++)
    {
        cout << s[i] << " ";
    }
    cout << endl;
    long long test = 2019032500000079;
    printf("%07d\n", test % 100000000);

    char *str = "12345677890";
    char dst[4] = {0};
    mystrncpy(dst, str, sizeof(dst), 6);
    printf("%s\n", dst);

    char dst_test[] = "asdfghjkl";
    mymemcpy(dst_test, dst_test, 4);
    cout << dst_test << endl;

    string strDst = "1,2,3,4,5";
    StringSplitC(strDst.c_str(), ",", vecRes);
    for (auto x : vecRes)
    {
        cout << x << " " << endl;
    }

    return 0;
}

int count = 0; //初始化
int wrong = 0; //初始化

void handler(int s) //当闹钟信号发过来，执行这个函数，输出对错的个数
{
    printf("time out \n");
    printf("right = %d,wrong = %d\n ", count, wrong);
    exit(1);
}

int sigalrmTest()
{
    int i = 0;
    signal(SIGALRM, handler); // 定义信号函数接收信号

    alarm(30);               // 设置闹钟时间为30秒，30秒后执行handler函数
    srand(getpid());         // 用子进程id作为随机种子数
    for (i = 0; i < 10; i++) // 循环十次，输出随机数相加结果
    {
        int left = rand() % 10;
        int right = rand() % 10;
        printf("%d + %d = ", left, right);
        int ret;

        while (getchar() != '\n')
            ; //清空输入缓冲区，防止异常输入使得程序崩溃
        scanf("%d", &ret);
        if (left + right == ret) //判断对错
        {
            count++;
        }
        else
        {
            wrong++;
        }
    }
    printf("做完了\n");
    printf("right =%d,wrong = %d \n", count, wrong);
}


typedef void (*pFun)(void);
class Base1
{
  public:
    virtual void e() { cout << "B1:: e()       " << endl; }
    virtual void f() { cout << "B1:: f()       " << endl; }
    virtual void g() { cout << "B1:: g()       " << endl; }
};

class Base2
{
  public:
    virtual void h() { cout << "B2:: h()       " << endl; }
    virtual void i() { cout << "B2:: i()       " << endl; }
};

class Base3
{
  public:
    virtual void j() { cout << "B3:: j()       " << endl; }
};

class Derive : public Base1, Base2, Base3
{
  public:
    Derive() { cout << "sizeof(Derive) is : " << sizeof(Derive) << endl; }
    virtual void k() { cout << "D::k()" << endl; }
};

int main()
{
    /*
    Base1 base1;
    Base2 base2;
    Base3 base3;
    Derive derive;
    for (int i = 0; i < 4; i++)
    {
        pFun fun = (pFun) * ((int *)*(int *)&derive + i);
        fun();
    }
    */
    int i = 10;
    printf("%d%d", i);
    cout << endl;
    float a = 2.0;
    double b = 3.0;
    long int c = 1000000000; // long int 占4字节
    long int d = 1280079890;
    printf("%ld %ld %ld %ld", a, b, c, d);
    return 2;
}
