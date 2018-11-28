/*
 * 怎么知道so文件里有哪些函数可用? nm -D libname.so
 * nm (names)
 * 怎么知道这个函数的返回值类型和参数类型?
 */

#include <stdio.h>
#include <dlfcn.h>

typedef int (*lpFunc)(int, int); // 定义函数指针类型

int main(int argc, char const *argv[])
{
    void * soHandle;
    int iFuncRet;
    int iArg1 = 10, iArg2 = 20;
    soHandle = dlopen("libCaculator.so", RTLD_LAZY); // 打开so文件, 并加载到内存
    
    if (soHandle == NULL)
    {
        fprintf(stderr, "%s\n", dlerror());
    }
    else
    {
        dlerror(); // 返回dlopen/dlsym/dlclose的错误,并清空错误信息

        lpFunc pAddFunc= dlsym(soHandle, "add"); // 返回函数在内存中的位置(指针)
        iFuncRet = pAddFunc(iArg1, iArg2);
        printf("add function return: %d\n", iFuncRet);

        lpFunc pSubFunc= dlsym(soHandle, "subtract");
        iFuncRet = pSubFunc(iArg1, iArg2);
        printf("subttract function return: %d\n", iFuncRet);

        lpFunc pMultiFunc= dlsym(soHandle, "multiply");
        iFuncRet = pMultiFunc(iArg1, iArg2);
        printf("multiply function return: %d\n", iFuncRet);

        lpFunc pDiviFunc= dlsym(soHandle, "divide");
        iFuncRet = pDiviFunc(iArg1, iArg2);
        printf("divide function return: %d\n", iFuncRet);

        dlclose(soHandle); // 关闭so文件
    }
    
    return 0;
}

