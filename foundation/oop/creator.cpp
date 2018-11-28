/*
 **********************************************************
 * Author       : M_Kepler
 * EMail        : m_kepler@foxmail.com
 * Last modified: 2018-10-28 11:31:05
 * Filename     : creator.cpp
 * Description  : 构造函数
 ***********************************************************
 */

#include <iostream>
using namespace std;

static int objectCount = 0;

class HowMany {
public:
    HowMany();
    HowMany(int i);
    HowMany(const HowMany &h);
    ~HowMany();
    void print(const string & msg="");
private:
};

HowMany::HowMany()
{
    objectCount++;
    cout << "create a obj: " << objectCount << endl;
}

HowMany::HowMany(int i)
{
    objectCount++;
    print("create a obj(int i)");
}

HowMany::HowMany(const HowMany & h)
{
    objectCount++;
    cout << "copy create a obj: " << objectCount << endl;
}

HowMany::~HowMany() {
    objectCount --;
    cout << "~delete a obj: " << objectCount << endl;
}

void HowMany::print(const string & msg)
{
    cout << msg << endl
         << "objectCount = " << objectCount << endl;
}

HowMany f(HowMany x)
{
    cout << "begin of func f" <<endl;
    x.print();
    cout << "end of func f"<<endl;
    return x;
}


int main( int argc, char **argv ) {
    HowMany h;
    h.print("after construction of h ");
    // HowMany h2 = h; // 调用拷贝构造
    HowMany h2 = f(h); // 拷贝构造函数
    // HowMany h2(10); // HowMany h2=10;
    h2.print( "after call of f()" );
    return 0;
}
