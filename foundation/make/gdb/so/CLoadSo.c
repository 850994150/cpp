#include <stdio.h>
#include <dlfcn.h> // 包含头文件
#include "CLoadSo.h"

int main(int argc, char **argv)
{

    void *soHandle;
    int (*fun)(); // 函数指针
    char *errorMsg;

    soHandle = dlopen("first.so", RTLD_LAZY); // 打开so文件返回handle
    errorMsg = dlerror();

    printf("A1---------loadSo  is %s \n", soHandle ? "success" : "failed");
    if (errorMsg)
    {
        printf("A2--------loadSo error, ErrMsg is: %s \n", errorMsg);
        return -1;
    }

    fun = dlsym(soHandle, "fun1"); // 函数指针
    errorMsg = dlerror();
    printf("B1---------fun1 , fun1 is %s \n", fun ? "success" : "Null");
    if (fun)
    {
        fun();
    }
    if (errorMsg)
    {
        printf("B2---------fun1 error , Msg is: %s \n", errorMsg);
    }

    fun = dlsym(soHandle, "fun2");
    errorMsg = dlerror();
    printf("B3---------fun2 , fun2 is %s \n", fun ? "success" : "Null");
    if (fun)
    {
        fun();
    }
    if (errorMsg)
    {
        printf("B4---------fun2 error , Msg is: %s \n", errorMsg);
    }

    fun = dlsym(soHandle, "fun3");
    errorMsg = dlerror();
    printf("B5---------fun3 , fun3 is %s \n", fun ? "success" : "Null");
    if (fun)
    {
        fun();
    }
    if (!errorMsg)
    {
        printf("B6---------fun3 error , Msg is: %s \n", errorMsg);
    }

    dlclose(soHandle);
    printf("C---------close LoadSo \n");

    return 0;
}
