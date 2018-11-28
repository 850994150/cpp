#include <iostream>
#include <new>
using namespace std;

extern "C" void spiff(int);
extern  void spoff(int);
extern "C++" void spaff(int);

typedef struct chaff
{
    char dross[20];
    int flag;
} *ptr;

char buffer1[50];
char buffer2[500];

namespace huangjinjie
{
    double pail;
    void fetch();
    int pa = 10;
    struct wall
    {
        int pr;
    };
}


int main()
{
    int pa = 2;
    chaff struct_a; // 以前的代码中必需struct 结构体名 对象名
    struct_a.flag  =  10; // 结构体对象可以直接用点来引用成员
    ptr ptr_a; // typedef struct  * ptr 等同ptr是指针类型为struct * 的别名
    ptr_a->flag= 100; // 指针则需要同构 -> 来引用成员

    chaff *p1, *p2;
    int *p3, *p4;
    p1 = new chaff;
    p1->flag  =  10;
    p3 = new int[20];
    p2 = new(buffer1) chaff;
    p4 = new(buffer2) int[20];
    cout << p1->flag  << '\t' << struct_a.flag << '\t' << p2 << '\t' << p3 << '\t' << p4 << endl;
    cout << pa << '\t' << huangjinjie::pa;

    free(p1);
    free(p2);
    free(p3);
    free(p4);
    return 0;
}

