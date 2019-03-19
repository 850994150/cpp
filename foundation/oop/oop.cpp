/***********************************************************
* Author       : M_Kepler
* EMail        : m_kepler@foxmail.com
* Last modified: 2017-08-04 17:14:14
* Filename     : oop.cpp
* Description  : 本文件主要记录oop中多态的实现
* 类的声明和类函数的实现
    * 定义成员函数时，用作用域解析运算符(::)来标识函数所属类
      void class_name::func_name(args...);也意味着在另一个类里也可以定义一个名称一样的函数
    * 类声明常将短小的成员函数作为内联inline函数,也可以在实现成员函数体的时候指定为内联函数
* 构造、析构函数
    * 构造函数: class_name::class_name(...){...};
      为了让类对象在创造时就初始化其成员,不用构造函数的话就只是创建对象，没有初始化
      成员变量构造函数名和类名一样,没有返回值，不用声明返回类型,
      构造函数参数表示的是赋给类成员的值，参数名不能和类成员相同,可在类成员加个后缀_,然后构造函数用类成员名称就很清晰了
      显式调用构造函数: Stock food = Stock("Wrold", 240, 2.31); 隐式调用: Stock grament("Furry", 40, 2.1);
      两种都不是的话就调用默认构造函数:Stock fully_the_cat;
      肯定不能通过对象调用构造函数啊，因为构造函数调用前，对象是不存在的
      如果只初始化了部分元素，则剩下的元素将使用默认构造函数进行初始化。
    * 析构函数: class_name::~class_name(...){...};
      用来完成清理工作的，如果构造函数是new分配内存，析构函数将使用delete来释放这些内存
      自动调用析构函数
    * 派生类的构造、析构函数
    * 拷贝构造函数
        * 深拷贝、浅拷贝
        *
* This指针
    * 有时候方法可能涉及两个对象,就需要用到this.（比如两个类对象都调用同一个类方法）
    * 每个成员函数都有一个this指针，this指针指向调用对象. *this是对象本身
* 对象数组
    * const int STKS= 4;
      Stock stocks[STKS] = {Stock{"a",12,20.0"},Stock("b",10,32.2"...};//初始化对象数组
* 类作用域
    * 在类里面定义的变量作用域是整个类，类外是不可知的
    * 作用域为类的常量
        * 作用域为全部类空间的常量(就是说这个常量可以由所有对象共享)
        * http://www.cnblogs.com/90zeng/p/cpp_scop_const_enum_static.html
        *
* 抽象数据类型(Abstract Data Type)
    * typedef
    *
* 访问控制
    * 默认访问控制是private
    * 类防范可以访问类的privae成员
**********************************************************/

#include <iostream>
using namespace std;

class World
{
  private: //private by default
    double m_total;
    float m_fmass;
    int m_imiss;

  public:
    World();
    World(const World &w) = delete;            // 拷贝构造函数
    World &operator=(const World &w) = delete; // 赋值
    ~World();

    void Hi_();
    void set_ot_();
    inline void total() { m_total = m_fmass + m_imiss; };
    void set_mass_();
};

World::World()
{
    cout << "Creator" << endl;
}

World::~World()
{
    cout << "Destroy" << endl;
}

inline void World::set_ot_()
{
    cout << "inline function" << endl;
}

void World::Hi_()
{
    m_imiss = 2.1; //可以直接访问私有变量
    cout << m_imiss << '\n'
         << "Hello World in class World" << endl;
}

class D
{
  public:
    D(double d) : d_(d) {}

    /* “(int)D”类型转换 */
    operator int() const
    {
        std::cout << "(int)d called!" << std::endl;
        return static_cast<int>(d_);
    }

  private:
    double d_;
};

int add(int a, int b)
{
    return a + b;
}

int main()
{
    World w;
    World *p_w = new World;
    w.Hi_();
    cout << "Func_main end!" << endl;
    delete p_w;
    p_w = NULL;

    D d1 = 1.1;
    D d2 = 2.2;
    std::cout << add(d1, d2) << std::endl;

    return 0;
}
