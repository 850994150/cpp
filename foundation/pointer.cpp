/***********************************************************
* Author       : M_Kepler
* EMail        : m_kepler@foxmail.com
* Last modified: 2017-07-27 13:53:20
* Filename     : pointer.cpp
* Description  :
*
 * 1、指针的类型: int *
     * 指针本身所具有的类型（指针声明语句里除指针名字以外）
     * int (*ptr)[3]; //指针类型是int(*) [3]

 * 2、指针所指向的类型：int
     * 指针所指向的内存区（把指针声明的名字和名字左边的指针声明符*去掉就行）
     * int *ptr; //指向的类型是int
     * int *(*ptr)[2]; //指向的类型是 int *()[4]

 * 3、指针的值：ptr
     * 指针本身存储的数值，比编译器当作一个地址
     * sizeof测出对象 自身类型的大小：32位系统的话sizeof(指针变量)得到的是4，而64位得到的是8
     * 指针的值是XX，相当于指针指向了以XX为首地址的一片内存区域

 * 4、指针本身所占的内存区
     * 一样可以用sizeof(指针类型)测出来,指针存的就是地址啊，一个字节8位，所以在32位系统里，是4个字节长度

 * 5、指针的算术运算 加减
     * 指针变量 +1 ; (p+1) 相当于变量所存地址向高方向加4字节
     * 指针的值 +1 ; (*p+1) 而*ptr是下一个数值
     * 一个指针ptrold加/减一个整数n后，结果是一个新的指针ptrnew

 * 6、运算符&(取地址)和*(间接运算符)
     * &a的结果是一个指针
     * *p的结果是p所指向的东西

 * 7、指针表达式
     * 即:表达式的结果是一个指针的表达式

 * 8、数组和指针的关系 char[] 与 char*
     * 数组是有指针来完成的。
     * 声明一个数组TYPE array[n], **数组名** 有两重含义，
     * 代表整个数组,类型是TYPE[n]或者代表一个指针,类型是TYPE*
     * 它与数组第0号单元占据的内存区是不同的，该指针是不能修改的,*str++是错的 *(str+1)是对的
     * 如果先访问第n个元素可使用: *(str+n) 
     * char str[3]={'a','b','c'}; '*str'是一个指向数组第0号单元的指针
     * 对空指针应用delete是安全的
     * 用指针创建动态数组（可在运行时选择数组长度）.
     * psome = psome + 1; //指针和数组名之间的区别，不能更改数组名的值; 但指针是变量，可以修改它的值
     * c++把数组名解释为第一个元素的地址,str[1]实际上是*(str+1),str[2]实际上是*(str+2),先算出了元素地址再去取存在那里的值
     * 【字符串指针变量指向的字符串常量的内容不允许修改】 char *p = "abcedfg";
        * 原因是 p指向的字符串的第一个字符地址, 指针存在栈上 而字符串的内容"abcedfg"存放在常量区, 常量区是不允许修改的
        * p[3] = "h";       // 错, 修改指针的值, 修改常量区的变量是错误的
        * p = "hijklmn";    // 对, 修改指针, 指针是可变的

 * 9、结构体与指针的关系
     * 掌握好通过指针访问成员变量的正确方法

 * 10、函数和指针的关系
     * 声明函数指针(指定函数的返回类型以及函数的参数列表):
         * 原型:double pam(int); 对应的指针类型声明：double (*pt)(int)
         * 用(*pf)把原函数名替换就行了, pf就是这个函数的指针,使用(*pf)把他当作函数名就可以了
     * 可以将一个函数的地址作为另一个函数的参数. >难道像python的装饰器?
     * 函数名就是函数的地址，process(think);//传递地址 process(think());//传递返回值
     *
     * 按值传递、引用传递
         * 按值传递:
             * 函数调用时传入的值初始化函数定义时的形参，函数退出、变量销毁，不会对函数的传入值产生影响；
             * 传递给函数的值被称为实参;用于接收传递值的变量称为形参
             * 意味着函数定义中的形参是新的变量，他被初始化为函数调用所提供的值.
             * C++将数组名参数视为数组地一个元素的地址,因为指针是原始地址的拷贝。
         * 引用传递
             * 不做拷贝，函数被调用时传入的是参数的别名，所以会影响原参数的值；
         * 指针传递
             * 传入的是地址，肯定会修改原参数的值

 * 11、指针与内存
     * 0、c++创建指针时，计算机分配用来存储地址的内存，但不分配用来存储指针所指向的数据所需的内存
     * 指针没有初始化(之前它可能是任何值)为一个确定的适当的地址就使用的话，很可能存在一些隐患
     * 为一个数据对象(可以是结构或基本类型)分配内存的通用格式如下:
         * typeName * pointer_name = new typeName; 指定需要什么样的内存和用来声明合适的指针
         * typeName * pointer_name = new typeName [num_elements]; 为数组分配内存

 * 12、结构体与指针
     * 访问成员变量时，如果结构标识符是结构名，则使用点运算符;
     * 如果标识符是指向结构的指针，则使用箭头运算符//(*ps).price也可以
     *
 * 13、自动存储、静态存储、动态存储
     * int a = 11;//自动存储，当其属于的函数活动时存在，程序控制权回到main时，a 使用的内存将被自动释放;通常存储在栈中
     * 静态存储：static，整个程序执行期间都存在的存储方式
     * 动态存储：new,delete，可以在一个函数中分配内存，而在另一个函数中释放它
 * 14、引用
     * int rats; int& rodents = rats;引用。
     * int&指的是指向int的引用,rat和rodents可以互换,他们指向相同的值和内存单元
     * &号和指针中的含义不一样. int * const pr = &rats; //const指针
     * 引用接近const指针,必须在创建时进行初始化，要一直跟着那个变量
 * 15、CONST
     * const在谁前面就是修饰谁。const在*后面，表示指针不变; 在*前面表示值不变
     * const关键字放在类型 或 变量名之前是等价的: const int n = 5; //int const n = 5;
     * char const * p 等同于: const char * p：p指向的内容(char类型)不能被修改
     * char * const p：p是一个指向char的静态指针,p本身的值不能被修改，但p所指向的内容可以被修改
     * const char *const Name：Name本身的值不能被修改，Name所指向的内容也不能被修改
     * const & static
**********************************************************/

#include <iostream>
using namespace std;

struct Mystruct
{
    int a;
    int b;
    int c;
};


void Invoke(char * s);

int main()
{
    int a[5] = {1,2,3,4,5};
    int *ptr = a;
    cout << "a数组的地址：" << ptr << endl;

    // 这个循环把数组里每个值加一
    // for (int i = 0; i < 5; ++i) {
        // (*ptr)++ ;
        // ptr++ ;
    // }
    // cout << a[2] << endl;

    ptr += 2 ;// 指针ptr的值加上5乘以sizeof(int)，指针想对于原来向高地址移动了20字节
    cout << "ptr+= 2 后：" << ptr << endl;
    cout << "*ptr的值：" << *ptr << endl;
    // ptr += 2;
    // cout << *ptr << endl;


    cout << "指针本身所占字节：" << sizeof(int * ) << endl;
    std::cout << sizeof(int) << std::endl;

    cout << sizeof(ptr) << endl;


    printf(" \n-------------------------- char *a / char a[] / string ---------------------------\n");
    char* tmpptr = "abcedfg";
    // tmpptr[4] = 'z';  // error  指针ptr存放在栈区, 指针指向的值"abcdefg"存放在常量区, 不允许修改常量区的值
                         // 如果是这样: char tmptr[] = "abcedfg" 则该操作是正确的, 因为此时“abcedfg”是存放在栈区
    tmpptr = "hijklmn";  // success 修改指针的值, 存放常量"hijklmn"的地址 
    cout << tmpptr << endl;
    // string str = "abcdef";
    // char *p_str = (char * )str.c_str();

    int array[10] = {0,1,2,3,4,5,6,7,8,9}, value;
    value = array[0]; //等同于value = *array;
    value = array[3]; //等同于value = *(array+3);

    // int (*q) [3];
    // int *(*p)[4];
    cout << "Hello World" << endl;


    Mystruct ss= {20,30,40};
    Mystruct *q = &ss; //指向结构体对象的指针,类型是Mystruct*, 指向的类型是Mystruct
    cout << q->a << endl; //通过q访问成员变量(正确)
    cout << (*q).a << endl; //通过q访问成员变量(正确)

    int *pstr = (int*)&ss; //指向结构对象ss的指针，但它指向的类型和ptr是不同的
    cout << q->a << endl; //通过q访问成员变量(正确)

    cout << *pstr << endl; //通过pstr访问成员变量(欠妥)

    // 指针运算
    cout << "++++++++" << endl;
    // char test[3] = {'a', 'b', 'c'};
    string test = "abcdef";
    char* pTest = (char*)test.c_str();
    cout << *pTest << endl; 
    cout << *(pTest+1) << endl; // 访问pTest + sizeof(char)地址的值
    cout << *pTest + 1 << endl; // 实际为ascii码+1


    cout << "----------------------------" << endl;

    // 这就是指针的初始化了吧
    int *pn = new int;//申请用来存储int类型的内存，并返回该内存块的地址
    cout << pn << endl;
    delete pn; //释放pn指向的内存(这些都是用new来分配的才行)但不会删除指针本身

    // 上下都是把int的地址赋值给指针
    int higgens;
    int *pt  =  &higgens; //这种可以通过名称higgens(上面的内存快就没有名称)来访问该int内存块
    cout << pt << endl;
    // delete pt;// 错误的用法

    int aa[11];//叫做静态联编。即数组的长度在编译时设置
    cout << aa << endl;

    int *psome = new int[4]; //用new关键字创建叫动态联编译。即运行是为数组分配空间.psome指向数组的地一个元素，*psome/psome[0]都是第一个元素的值,第二个元素就是psome[1]
    psome[0] = 11;
    psome[1] = 22;
    psome[2] = 33;
    psome[3] = 44;
    // 就int类型的不行?int的话输出的是十六进制
    // double *psome = new double[3];
    // psome[0] = 0.2;
    // psome[1] = 0.5;
    // psome[2] = 0.8;
    cout << "psome[1] is：" << psome[1] << endl;
    psome = psome + 1; //指针和数组名之间的区别，不能更改数组名的值; 但指针是变量，可以修改它的值
    cout << "now psome[0] is：" << psome[0] << "\nand psome[1] is：" << psome[1] << endl;
    psome = psome - 1;
    cout << *psome << endl;
    delete [] psome; // 释放指针指向的内存,[]表示释放整个数字，而不仅仅是指针指向的元素

    short tell[20];// tell an array of 20 bytes
    cout << tell << endl;//displays &tell[0],是两个字节的内存快的地址
    cout << &tell << endl;// displays address of whole array,是20个字节的内存块的地址


    char flower[10] = "rose";
    std::cout << flower << std::endl;

    const int con_a = 10;
    int const con_b = 10;
    // con_a = 101; //err
    cout << con_a + 1 << endl <<  con_b + 1 << endl;

    const int *p_con_a = 0; //指针指向的值*p_con_a的值不能被改变，指针初始化赋为0不会报错。 
    const int * const p_con = 0; //指针指向的值和指针本身保存的值都不能改变
    p_con_a = &con_b; 
    int c = 100;
    p_con_a = &c;
    // *p_con_a = 10; // err
    cout << p_con_a << endl <<  *p_con_a<< endl;

    cout << " ============== 函数指针: ============== " << endl;
    void (* fp)(char * ); // 声明一个函数指针
    fp = Invoke;          // 将Invoke函数入口地址赋值给fp指针
    fp((char * )("Hello World!\n")); // 函数指针fp实现函数调用

    return 0;
}

void Invoke(char * s)
{
    printf(s);
}

/*
 * 运行时决策:
 * 使用关键字new请求正确数量的内存以及使用指针来跟踪新分配的内存的位置
 * 在运行阶段非陪未命名的内存以存储值，在这种情况下可以通过指针来访问内存
 */
