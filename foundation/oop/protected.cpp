#include <iostream>
using namespace std;
class Base
{
  public:
    int ipub;
    Base(){};
    virtual ~Base(){};

  protected:
    int int_pro;
};

class A : protected Base
{
  public:
    A(){};
    A(int da) { int_pro = da; }
    void Print(A &obj) { obj.int_pro = 24; }
    void PrintPro() { cout << "The proteted data is " << int_pro << endl; }
};

int main()
{
    A aObj;
    A aObj2(5);
    aObj2.PrintPro();
    aObj.Print(aObj2);
    aObj2.PrintPro();
    // aObj.int_pro = 8;
    aObj.ipub = 8;
}
