/*
 **********************************************************
 * Author       : M_Kepler
 * EMail        : m_kepler@foxmail.com
 * Last modified: 2018-12-31 22:39:42
 * Filename     : bitmap.c
 * Description  : 位图
 *      位图是把数据对应下标的位设置为1
 ***********************************************************
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define BITWORD 32
#define ARRNUM 100
#define BITS_PER_WORD 32
#define WORD_OFFSET(b) ((b) / BITS_PER_WORD)
#define BIT_OFFSET(b) ((b) % BITS_PER_WORD)
void SetBit(int *words, int n)
{
    words[WORD_OFFSET(n)] |= (1 << BIT_OFFSET(n));
}

// 将第n位设置为0
void ClearBit(int *words, int n)
{
    words[WORD_OFFSET(n)] &= ~(1 << BIT_OFFSET(n));
}

// 将第n位设置为1
int GetBit(int *words, int n)
{
    int bit = words[WORD_OFFSET(n)] & (1 << BIT_OFFSET(n));
    return bit != 0;
}


/*
 * @function: 
 * @brief	: 已知某文件包含一些电话号码，每个号码为8位数字，统计不同号码的个数
 *            8位整数可以表示的最大十进制数为99999999，如果每个数字对应位图中的
 *            一位，那么存储这些整数大约需要99999999个比特位即95.367M内存大小，
 *            因为1Bit(比特/字节) = 8bit, 所以用位图的话只需要 99/8 = 12.375M 内存 
 * @param	: 
 * @return	: 
 */

int main()
{
    int i, j;
    int count = 0;
    int n;
    printf("请输入随机数个数:\n");
    scanf("%d", &n);

    int *words = (int*) malloc (1 + n / BITS_PER_WORD); // 位图
    int *arr = (int *)malloc(n * sizeof(int));          // 原始数据

    if (words == NULL)
    {
        perror("new");
        exit(EXIT_FAILURE);
    }
    for (i = 0; i < n; i++)
    {
        ClearBit(words, i);
    }

    srand((unsigned)time(NULL));

    printf("数组大小:%d\n", n);

    for (j = 0; j < n; j++)
    {
        arr[j] = rand() % n;
        printf("%d\t", arr[j]);
    }

    for (j = 0; j < n; j++)
    {
        SetBit(words, arr[j]);
    }

    printf("\n排序后a为:\n");

    for (i = 0; i < n; i++)
    {
        if (GetBit(words, i))
        {
            printf("%d\t", i);
            count++;
        }
    }

    printf("\n总个数为:%d\n", count);
    free(words);
    words = NULL;
    free(arr);
    arr = NULL;
    return 0;
}
