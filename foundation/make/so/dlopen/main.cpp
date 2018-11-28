#include <iostream>
#include <dlfcn.h>
#include "test.h"
using namespace std;

//声明函数指针
typedef Test* (*so_init)();

//定义插件类来封装，句柄用完后需要释放
struct Plugin
{
    void *handle;
    Test *t;

    Plugin():handle(NULL), t(NULL) { }
    ~Plugin()
    {
        if(t)
        {
            delete t;
        }
        if (handle)
        {
            dlclose(handle);
        }
    }
};


int create_instance(const char *so_file, Plugin &p)
{
    //根据特定的模式打开so文件, 获取so文件句柄
    //RTLD_NOW：需要在dlopen返回前，解析出所有未定义符号
    //RTLD_DEEPBIND：在搜索全局符号前先搜索库内的符号，避免同名符号的冲突
    p.handle = dlopen(so_file, RTLD_NOW | RTLD_DEEPBIND);
    if (!p.handle)
    {
        cout << "Cannot open library: " << dlerror() << endl;
        return -1;
    }

    //根据字符串"create"读取库中对应到函数, 并返回函数地址，可以理解为一种间接的“反射机制”
    so_init create_fun = (so_init) dlsym(p.handle, "create");
    if (!create_fun)
    {
        cout << "Cannot load symbol" << endl;
        dlclose(p.handle);
        return -1;
    }

    //调用方法, 获取类实例 
    p.t = create_fun();

    return 0;
}


int main()
{
    Plugin p1;
    Plugin p2;

    if (0 != create_instance("./libtest_1.so", p1) || 0 != create_instance("./libtest_2.so", p2))
    {
        cout << "create_instance failed" << endl;
        return 0;
    }

    p1.t->set(1);   //对库1中到全局变量进行设置
    p2.t->set(2);   //对库2中到全局变量进行设置

    //输出两个库中的全局变量
    cout << "t1 g_num is " << p1.t->get() << endl;
    cout << "t2 g_num is " << p2.t->get() << endl;
    return 0;
}



// g++ -fPIC -shared test.cpp -o libtest_1.so
// g++ -fPIC -shared test.cpp -o libtest_2.so
// g++ -g -Wl,--no-as-needed -ldl main.cpp -rdynamic

