/*
0. 一个字节8位; 32位表示cpu一次可以处理32位的二进制数据
1. 32/64位机器分别是按4/8字节对齐, 64位机器中long占8位
   32位 / 8位 = 4字节; 64位 / 8位 = 8字节
2. 32位一次可以放下4字节; 64位一次可以放下8字节, 放不下的就需要填充
   32位:
        ******** ******** ******** ********
        ******** ******** ******** ********
    64位:
        ******** ******** ******** ******** ******** ******** ******** ********
        ******** ******** ******** ******** ******** ******** ******** ********
3. 地址怎么对齐:
    一块内存,按照顺序存放变量, 如果一字节放不下系统会按照 1byte 4bit自动填充对齐
    对齐后继续在后面存放别的变量
*/
// "*" 表示一位, "#"表示填充

#include <stdlib.h>
#include <iostream>
#include <string.h>

using namespace std;

/*
// 64位系统下的结果, 无特殊说明则表示和32位计算结果一样
sizeof(bool)                = 1 字节
sizeof(char)                = 1 字节
sizeof(unsign char)         = 1 字节

sizeof(float)               = 4 字节
sizeof(double)              = 8 字节

sizeof(short)               = 2 字节
sizeof(short int)           = 2 字节
sizeof(int)                 = 4 字节
sizeof(long int)            = 4 字节
sizeof(long)                = 8 字节 // 32位系统里是4字节
sizeof(long long)           = 8 字节
sizeof(int*p)               = 8 字节 // 32位系统里是4字节

sizeof(unsigned int)        = 4 字节
sizeof(unsigned long)       = 8 字节 // 32位系统里是4字节
sizeof(unsigned long long)  = 8 字节
*/

/* 以下结果均基于64位机器 */



void sizeofStruct()
{
    typedef struct tagDBFHead
    {
        char			Mark;
        unsigned char	Year;
	    unsigned char	Month;
	    unsigned char	Day;
        // 4 + 4(补充) = 8
	    long			RecCount;
        // 8
	    unsigned short	DataOffset;
	    unsigned short	RecSize;
        // 4 + 4(补充) = 8
	    char 			Reserved[20];
        // 8 + 8 + 4 + 4(补充) = 24
    } DBFHEAD, *LPDBFHEAD;
    // 64位机器上 sizeof(DBFHEAD) = 40

    // 位域
    typedef struct
    {
        char a : 3; // 表示变量只是用其中的低3位，其他高5位不管
        char b : 3;
        char c : 3;
        char d : 3;
        char e : 3;
    } test1;
    // 3bit * 5 = 15bit(位), 应该是占用2byte(字节)啊
    // 需要考虑内存对齐的问题
    // ***|***|##, ***|***|##, ***#####

    typedef struct
    {
        char a : 3;
        char b : 4;
        char c : 5;
        char d : 6;
        char e : 7;
    } test2;
    // ***|****#, *****###, ******##, *******#

    typedef struct
    {
        char a : 1;
        char b : 2;
        char c : 3;
        char d : 4;
        char e : 5;
    } test3;
    // *|**|***##, ****####, *****###

    typedef struct
    {
        int  a;
        char b;
        char c;
        long d;
    } test4;
    /*
    // 对于32位机器:
    ********    ********    ********    ********(a)
    ********(b) ********(c) ########    ########
    ********    ********    ********    ********
    ********    ********    ********    ******** (d需要8个字节)
    // 对于64位机器:
    ********    ********    ********    ********(a) ********(b) ********(c) ########    ########
    ********    ********    ********    ********    ********    ********    ********    ******** (d需要8个字节)
    */

    typedef struct
    {
        int a;
        char b;
        long c;
        char d;
    } test5;
    // 对于32位机器:
    /*
    ********    ********    ********    ********(a)
    ********(b) ########    ########    ########
    ********    ********    ********    ********
    ********    ********    ********    ******** (c)
    ********(d) ########    ########    ########
    // 对于64位机器:
    ********    ********    ********    ********(a) ********(b) ########    ########    ########
    ********    ********    ********    ********    ********    ********    ********    ******** (c)
    ********(d) ########    ########    ########    ########    ########    ########    ########
    */

    typedef struct
    {
        int a;
        char b;
        int d[10];
        long c;
        char e;
    }test6;
    /*
    // 对于32位机器:
    ******** ******** ******** ********
    ******** ######## ######## ########
    ******** ******** ******** ******** × 10
    ******** ******** ******** ********
    ******** ******** ******** ********
    ******** ######## ######## ########
    4 + 4 + 40 + 8 + 4 = 60
    // 对于64位机器:
    ******** ******** ******** ******** ******** ######## ######## ########
    ******** ******** ******** ******** × 10
    ******** ******** ******** ******** ******** ******** ******** ********
    ******** ######## ######## ######## ######## ######## ######## ########
    4 + 1 + 7 + 4 * 10 + 8 + 1 + 7 = 64

    */


    cout << "sizeof(test1): " << sizeof(test1) << endl;
    cout << "sizeof(test2): " << sizeof(test2) << endl;
    cout << "sizeof(test3): " << sizeof(test3) << endl;
    cout << "sizeof(test4): " << sizeof(test4) << endl;
    cout << "sizeof(test5): " << sizeof(test5) << endl;
    cout << "sizeof(test6): " << sizeof(test6) << endl;
}

// 对于union来说大小为成员定义里面最大的那个
void sizeofUnion()
{
    union uu
    {
        char ul[5];
        int u2[2];
    } ua;
    cout << "sizeof(union) = " << sizeof(uu) << endl;
}

/*
===---=== sizeof struct ===---===
sizeof(test1): 3
sizeof(test2): 4
sizeof(test3): 3
sizeof(test4): 16
sizeof(test5): 24
sizeof(test6): 64
*/

void sizeofCharArray()
{
    string s = "hello world";
    char *s1 = (char*)"hello world";
    char s2[] = "hello world";
    char s3[100];
    char *s4 = (char *)malloc(100);
    void *s5 = (void *)malloc(100);

    cout << sizeof(s) << endl;  // string类型, 由编译器决定, 不管字符串多长, 分配的内存都是一定的
    cout << sizeof(s1) << endl; // 指针在32/64位系统中分别占用4/8字节, 与指向的内容无关
    cout << sizeof(s2) << endl; // 字符数组, 末尾有一个隐藏字符'\0'
    cout << sizeof(s3) << endl; // 字符数组, 在编译期被分配了 100*1个字节
    cout << sizeof(s4) << endl; // 指针, 同s2
    cout << sizeof(s5) << endl; // 指针, 同s2
}

/*
===---=== sizeof char x / char [] ===---===
32
8
12
100
8
8
*/

/*
 * 类所占内存大小由非静态成员变量决定的, 静态成员是存储在全局变量区, 和类不在一个地方, **与成员函数无关** (虚函数另说)
*/
// 空的类内存中要存在一个字节进行区分
class emptyClass1
{
public:
    emptyClass1(){}
    ~emptyClass1(){}
};

 // 有一个虚函数, 虚函数有个指针指向虚函数表的
/*
  类 emptyClass2 有一个虚函数，存在虚函数的类都有一个一维的虚函数表叫虚函数表, 虚函数表里存放的就是虚函数的地址了,
  因此，虚表是属于类的。这样的类对象的前四个字节是一个指向虚函数表的指针, 类内部必须得保存这个虚表的**起始指针**。
  所以这个空类还多占这一个指针的大小; 另外, 不管类里面有多少个虚函数， 类内部只要保存虚表的起始地址即可，虚函数地址都可以通过偏移等算法获得
 */
// Q: 这里为什么不是1+8=4+8=12呢?
// A: 从实践结果来看, 空的类才需要那一个字节, 非空类不需要
class emptyClass2
{
private:
    /* data */
public:
    emptyClass2() {} // 构造函数不能是虚函数
    virtual ~emptyClass2(){}
    static void func1(){};
    virtual void func2(){};
    void func();
};


// 和结构体一样, 要考虑内存对齐
class A
{
private:
    int a;
    char b;
public:
    A() { }
    ~A() { }
};


// 由于地址对齐:
/*
64位机器中:
******** ******** ******** ******** ######## ######## ######## ########
******** ******** ******** ******** ******** ******** ******** ********
*/
class baseClass
{
private:
    int iBase;
public:
    baseClass(){}
    virtual ~baseClass(){}
    virtual void func1(){}
};


/*
Q1: 继承的时候先分配父类的内存，那么父类里是先分配虚指针空间还是还是int呢？
A1: XXX 实践证明, 是先分配了子类的空间, 然后再分配父类的空间

Q2: 子类继承父类, 父类末尾本应该填充的内存可以继续使用吗
A2: ** 不可以 **

子类的内存大小等于父类的内存大小加上子类独有成员变量的内存大小

*/

class subClassFirst: baseClass
{
public:
    int a;
    subClassFirst() : baseClass() {}
    ~subClassFirst() {}
private:
    char b;
};
/*
sub:
******** ******** ******** ********(a)     ********(b) ######## ######## ########
base:
******** ******** ******** ********(iBase) ########    ######## ######## ########
******** ******** ******** ********        ********    ******** ******** ********(vptr)
*/


class subClassSec:baseClass
{
private:
    int sub;
    char sub2;
public:
    subClassSec() : baseClass() {}
    ~subClassSec(){}
};


/*
相对subClassSec, 多了个virtual函数;
如果基类中包含了虚函数(有虚函数表指针了), 则不需要新增虚函数表指针, 直接用基类的虚函数表指针
如果基类中没有虚函数, 则需要在该子类中创建虚函数表指针
*/
class subClassThird:baseClass
{
private:
    int a;
    char b;
    double c;
public:
    subClassThird() : baseClass() {}
    ~subClassThird(){}
    virtual void func3(){}
};
/*
sub:
******** ******** ******** ********(a)  ********(b) ######## ######## ########
******** ******** ******** ********     ********    ******** ******** ********
base:
******** ******** ******** ********(iBase)  ######## ######## ######## ########
******** ******** ******** ********         ******** ******** ******** ******** (vptr)
*/
class baseClass2
{
  public:
    virtual void baseFunc();
};

class subClassFour : baseClass, baseClass2
{
private:
public:
    subClassFour() : baseClass() {}
    ~subClassFour(){}
};

/*
===---=== sizeof class ===---===
sizeof empty class: 1
sizeof empty class's obj: 1
sizeof class with virtual destroy func: 8
sizeof class with one int and one char param : 8
sizeof base class: 16
sizeof subclassFirst: 24
sizeof subclassSec: 24
sizeof subclassThird: 32
*/

void strlenTest()
{
    char* a = (char*)"hello";
    char b[11] = "HelloWorld";
    char c[11] = "hello";
    char d[] = "HelloWorld";
    char *e = new char[11];
    char f[11];
    char g[] = {'A','B','C','D','E','F'};
    // char g[] = {'A','B','C','D','E','F', '\0'};

    cout << "sizeof(char*a = \"hello\") = " << sizeof(a) << endl;
    cout << "strlen(char*a = \"hello\") = " << strlen(a) << endl;

    cout << "sizeof(charb[11] = \"HelloWorld\") = " << sizeof(b) << endl;
    cout << "strlen(charb[11] = \"HelloWorld\") = " << strlen(b) << endl;

    cout << "sizeof(c[11] = \"hello\") = " << sizeof(c) << endl; // ***
    cout << "strlen(c[11] = \"hello\") = " << strlen(c) << endl;

    cout << "sizeof(d[]=\"HelloWorld\") = " << sizeof(d) << endl;
    cout << "sizeof(d[]=\"HelloWorld\") = " << strlen(d) << endl;

    cout << "sizeof(char*e=new char[11]) = " << sizeof(e) << endl;
    cout << "strlen(char*e=new char[11]) = " << strlen(e) << endl;

    cout << "sizeof(f[11]) = " << sizeof(f) << endl;
    cout << "strlen(f[11]) = " << strlen(f) << endl;

    cout << "sizeof(g[]) = " << sizeof(g) << endl;
    cout << "strlen(g[]) = " << strlen(g) << endl;  // 字符数组，以单个元素的形式赋值,没有\0, strlen会一直往后直到找到一个\0为止, 大小不确定

}
/*
===---=== sizeof & strlen ===---===
sizeof(char*a = "hello") = 8
strlen(char*a = "hello") = 5
sizeof(charb[11] = "HelloWorld") = 11
strlen(charb[11] = "HelloWorld") = 10
sizeof(c[11] = "hello") = 11
strlen(c[11] = "hello") = 5
sizeof(d[]="HelloWorld") = 11
sizeof(d[]="HelloWorld") = 10
sizeof(char*e=new char[11]) = 8
strlen(char*e=new char[11]) = 0
sizeof(f[11]) = 11
strlen(f[11]) = 1
*/


struct s
{
    int a;
    int b;
    bool operator == (const s &rhs);
};

bool s::operator == (const s &rhs)
{
    return ((a == rhs.a) && (b == rhs.b));
}

void compareStruct(s s1, s s2)
{

    // struct s s1, s2;
    s1.a = 1;
    s1.b = 2;
    s2.a = 1;
    s2.b = 2;
    if (s1 == s2)
        cout << "两个结构体相等" << endl;
    else
        cout << "两个结构体不相等" << endl;
}

int main(int argc, char const *argv[])
{
    int a = 10;
    int *p = &a;
    cout << "sizeof(bool) = \t" << sizeof(bool) << " 字节\t" << endl;
    cout << "sizeof(char) = \t" << sizeof(char) << " 字节\t" << endl;
    cout << "sizeof(unsign char) = \t" << sizeof(unsigned char) << " 字节\t" << endl;
    cout << "sizeof(int) = \t" << sizeof(int) << " 字节\t" << endl;
    cout << "sizeof(unsigned int) = \t" << sizeof(unsigned int) << " 字节\t" << endl;
    cout << "sizeof(long) = \t" << sizeof(long) << " 字节\t" << endl;
    cout << "sizeof(unsigned long) = \t" << sizeof(unsigned long) << " 字节\t" << endl;
    cout << "sizeof(long long) = \t" << sizeof(long long) << " 字节\t" << endl;
    cout << "sizeof(unsigned long long) = \t" << sizeof(unsigned long long) << " 字节\t" << endl;
    cout << "sizeof(float) = \t" << sizeof(float) << " 字节\t" << endl;
    cout << "sizeof(double) = \t" << sizeof(double) << " 字节\t" << endl;
    cout << "sizeof(int*p) = \t" << sizeof(p) << " 字节\t" << endl;

    cout << "\n===---=== sizeof struct ===---===" << endl;
    sizeofStruct();

    cout << "\n===---=== sizeof union ===---===" << endl;
    sizeofUnion();

    cout << "\n===---=== sizeof char*/char [] ===---===" << endl;
    sizeofCharArray();

    cout << "\n===---=== sizeof class ===---===" << endl;
    emptyClass1 clemptyClass1;
    cout << "sizeof empty class: " << sizeof(emptyClass1) << endl;
    cout << "sizeof empty class's obj: " << sizeof(clemptyClass1) << endl;
    cout << "sizeof class with virtual destroy func: " << sizeof(emptyClass2) << endl;
    cout << "sizeof class with one int and one char param : " << sizeof(A) << endl;
    cout << "sizeof base class: " << sizeof(baseClass) << endl;
    cout << "sizeof subclassFirst: " << sizeof(subClassFirst) << endl;
    cout << "sizeof subclassSec: " << sizeof(subClassSec) << endl;
    cout << "sizeof subclassThird: " << sizeof(subClassThird) << endl;
    cout << "sizeof subclassFour: " << sizeof(subClassFour) << endl;


    cout << "\n===---=== sizeof & strlen ===---===" << endl;
    strlenTest();

    cout << "\n===---=== 结构体比较 ===---===" << endl;
    struct s s1, s2;
    compareStruct(s1, s2);
    return 0;
}
