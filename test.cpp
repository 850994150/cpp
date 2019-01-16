#include <iostream>
#include <chrono>
#include <vector>
#include <assert.h>
#include <string.h>
#include <time.h>
using namespace std;
// typedef void (*pLineCallback)(int iCnt, const char *pcszContent);
typedef void (pLineCallback)(string strContent);

const int iCommitCnt = 100;

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
    cout << *p <<endl;

    char a[10] = "abc", b[10] = "012", c[10] = "xyz";
    strcpy( a+1,b+2);
    puts( strcat( a,c+1));


    char szTest[14] = "中国";
    // cout << "length" << szTest.length() << endl;
    cout << "length: " << sizeof(szTest)/sizeof(char) << endl;
    cout << "length: " << strlen(szTest) << endl;

    time_t nowMs = GetCurrentTimeMs();
    cout << "nowMs: " << nowMs << endl;

    /* c++11  */
    auto time_now = chrono::system_clock::now();
    auto duration_in_ms = chrono::duration_cast<chrono::milliseconds>(time_now.time_since_epoch());
    cout << "chrono: " << duration_in_ms.count() << endl;

    char szLBM[32 + 1];
    memset((void *)szLBM, 0x00, sizeof(szLBM));
    string strLbm = "L1100125";
    char * p_szLbm = (char*)strLbm.c_str();
    cout << atol(p_szLbm) << endl;

    char szCurrTime[64] = {0};
    // char *F_RUNTIME = "123123";
    string strNowTime = "2018-12-20-14.11.42.333333";
    char *F_RUNTIME = (char*)strNowTime.c_str();
    cout << F_RUNTIME + 11 << endl;
    strncpy(szCurrTime, F_RUNTIME + 11, sizeof(szCurrTime));
    szCurrTime[8] = '\0';
    cout << szCurrTime << endl;

}

void print(string line)
{
    printf("%s\n", line.c_str());
}


int main(int argc, char const *argv[])
{
    char chstr[] = "abcde";
    cout << chstr << endl;
    cout << *chstr << endl;
    cout << *chstr+1 << endl;
    cout << *(chstr+1) << endl;

    char *p ="abcdef";
    // p[3] = 'b'; // error
    p = "edf"; // succ
    cout << p << endl;



    // ReadFile("./sql_0000.sql", iCommitCnt, print);
    return 0;
}
