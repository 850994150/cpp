#include <stdio.h>
#include <stdlib.h>
#define min(a, b) ((a) < (b) ? (a) : (b))

int main(int argc, char *argv[])
{
    int f[105], n, cost;
    scanf("%d", &n);
    f[0] = 0;
    for (int i = 1; i <= n; i++)
    {
        cost = 999999;
        if (i - 1 >= 0)
            cost = min(cost, f[i - 1] + 1);
        if (i - 5 >= 0)
            cost = min(cost, f[i - 5] + 1);
        if (i - 11 >= 0)
            cost = min(cost, f[i - 11] + 1);
        f[i] = cost;
        printf("f(%d) = %d\n", i, f[i]);
    }
    return 0;
}