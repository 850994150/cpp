/*
 **********************************************************
 * Author       : M_Kepler
 * EMail        : m_kepler@foxmail.com
 * Last modified: 2018-12-31 22:39:42
 * Filename     : bitmap.cpp
 * Description  : 位图
 ***********************************************************
 */

#include <iostream>
#include <time.h>
using namespace std;
#define BITWORD 32
#define ARRNUM 100

int mmin = 10000000;
int mmax = 99999999;
int N = (mmax - mmin + 1);
#define BITS_PER_WORD 32
#define WORD_OFFSET(b) ((b) / BITS_PER_WORD)
#define BIT_OFFSET(b) ((b) % BITS_PER_WORD)
void SetBit(int *words, int n)
{
    n -= mmin;
    words[WORD_OFFSET(n)] |= (1 << BIT_OFFSET(n));
}

void ClearBit(int *words, int n)
{
    words[WORD_OFFSET(n)] &= ~(1 << BIT_OFFSET(n));
}

int GetBit(int *words, int n)
{
    int bit = words[WORD_OFFSET(n)] & (1 << BIT_OFFSET(n));
    return bit != 0;
}

int main()
{
    int i;
    int j;
    int arr[ARRNUM];
    int *words = new int[1 + N / BITS_PER_WORD];
    if (words == NULL)
    {
        cout << "new error\n"
             << endl;
        exit(0);
    }
    int count = 0;
    for (i = 0; i < N; i++)
    {
        ClearBit(words, i);
    }

    srand((unsigned)time(NULL));
    printf("数组大小:%d\n", ARRNUM);
    for (j = 0; j < ARRNUM; j++)
    {
        arr[j] = rand() % N;
        arr[j] += mmin;
        printf("%d\t", arr[j]);
    }
    for (j = 0; j < ARRNUM; j++)
    {
        SetBit(words, arr[j]);
    }

    printf("排序后a为:\n");

    for (i = 0; i < N; i++)
    {
        if (GetBit(words, i))
        {
            printf("%d\t", i + mmin);
            count++;
        }
    }

    printf("总个数为:%d\n", count);
    delete[] words;
    words = NULL;
    return 0;
}
