/***********************************************************
* Author       : M_Kepler
* EMail        : m_kepler@foxmail.com
* Last modified: 2018-02-05 21:58:47
* Filename     : access.cpp
* Description  : 虚函数、存虚函数、虚函数表
**********************************************************/

#include <iostream>
#include <string>
using namespace std;

class Student {
public:
    Student( int,string,float );
    ~Student();
    // virtual ~Student();
    void display();
    int pub_a = 10;
protected: // 受保护成员，派生类可以访问
    int _num;
    string _name;
    float _score;
};

// 试试不区分num和_num，会得到错误的结果
Student::Student( int num,string name,float score )
{
    _num = num;
    _name = name;
    _score = score;
    printf("Create BaseClass Student\n");
}

Student::~Student()
{
    printf("Destroy BaseClass Student\n");
}

void Student::display()
{
    cout << "num:" << _num  << "\nname:" << _name << "\nscore:" << _score << endl << endl;
}


// class Graduate:protected Student 基类非private全变成子类的protected
// class Graduate:private Student 基类非private 全编程子类的private 
// class Graduate:public Student  访问属性不变

class Graduate:public Student
{
public:
    Graduate(int,string,float,float);
    ~Graduate();
    void display();
protected:
    int proddd = 10;
private:
    float _pay;
};

Graduate::Graduate(int num, string name, float score, float pay):Student(num,name,score),_pay(pay)
{
    printf("Create BaseClass Graduate\n");
}

Graduate::~Graduate()
{
    printf("Destroy SubClass Graduate\n");
}
void Graduate::display()
{
    cout << "num:" << _num  << "\nname:" << _name << "\nscore:" << _score << "\npay:" << _pay << endl << endl;
}

int main( int argc, char **argv )
{
    /*
    Student stud1(1001, "Li", 87.5);
    Graduate grad1(2001, "Wang",98.4,532.5);
    Student *ptr;

    ptr = &stud1;
    ptr->display();

    ptr = &grad1;
    ptr->display();
    */

    // 基类析构需声明为虚函数
    Student *ptrNew = new  Graduate(3001, "Huang", 90, 550);
    ptrNew->display();
    delete ptrNew;

    return 0;
}
