/***********************************************************
 * Author       : M_Kepler
 * EMail        : m_kepler@foxmail.com
 * Last modified: 2018-07-04 14:40:28
 * Filename     : class-template.cpp
 * Description  :
 *
 * 这是在定义一个类模板，其实，我发现,
 类模板和函数模板一样，都是模板；也就是，都是要加上那句template,还有就是
 都是把类或者模板里面原来是要确定数据类型的地方用T替换掉；
 另外，在使用模板的时候，
 对于函数模板，就是直接把定义好的参数放进去，就像
 函数的调用，对于类模板，  原来是这样的： myClass class1(3,5)；
 现在换成  myClass<int,int> class1(3,5);
 ************************************************************/

#include <iostream>
using namespace std;

template<typename T1,typename T2>
class myClass{
    private:
        T1 I;
        T2 J;
    public:
        myClass(T1 a, T2 b);//Constructor
        void show();
};
//注意成员函数在类外面定义的语法规则
template <typename T1,typename T2>
myClass<T1,T2>::myClass(T1 a,T2 b):I(a),J(b){}

    template <typename T1,typename T2>
void myClass<T1,T2>::show()
{
    cout<<"I="<<I<<", J="<<J<<endl;
}
int main(){
    myClass<int,int> class1(3,5);
    class1.show();
    myClass<int,char> class2(3,'a');
    class2.show();
    myClass<double,int> class3(2.9,10);
    class3.show();
}
