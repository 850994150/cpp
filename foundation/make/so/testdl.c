#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include "max.h"

int main( int argc, char **argv )
{
    int a=10, b=20, c=30;
    /* printf( "Max number is:%d\n", max(a,b,c)); */

    char* error;
    typedef int (*pfunc)(); // 声明函数指针类型
    void * pHandle;

    /* 先回去环境变量LD_LIBRARY_PATH 查找 */
    pHandle = dlopen("libmax.so", RTLD_LAZY); /* 把库加载到内存 */

    if ( !pHandle  )
    {
        fprintf(stderr, "%s\n", dlerror());
        exit(1);
    }
    pfunc pf = (pfunc)dlsym(pHandle, "max");
    if ( (error = dlerror()) != NULL )
    {
        fprintf(stderr, "%s\n", error);
        exit(1);
    }
    int max = pf(a, b, c);
    printf( "Max number is:%d\n", max); // 通过指针pf的调用来调用动态库中的max函数
    dlclose(pHandle);

    return 0;
}
