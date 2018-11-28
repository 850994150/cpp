#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define M 1000 /* 执行次数 */
#define N 500 /* 数组大小 */

void SelectSort(int *a,int r)
{
    int i,j,v;
    for (i=0;i<r;i++)
    {
        for (j=i+1;j<=r;j++)
        {
            if (*(a+i)>*(a+j))
                v=*(a+i),*(a+i)=*(a+j),*(a+j)=v;
        }
    }
}


int main()
{
    int a[N],i,j;
    double start,finish; /* 开始时间,结束时间 */
    start=(double)clock();
    for (j=0;j<M;j++)
    { /* 执行M次 */
        for (i=0;i<N;*(a+i++)=rand()%10); /* 每次重新赋值 */
        SelectSort(a,N-1);
    }
    finish=(double)clock();
    printf("%.4fms",(finish-start)/CLOCKS_PER_SEC);
    return 0;
}

