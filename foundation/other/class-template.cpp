/***********************************************************
 * Author       : M_Kepler
 * EMail        : m_kepler@foxmail.com
 * Last modified: 2018-07-04 14:40:28
 * Filename     : class-template.cpp
 * Description  :
 *
 * �����ڶ���һ����ģ�壬��ʵ���ҷ���,
 ��ģ��ͺ���ģ��һ��������ģ�壻Ҳ���ǣ�����Ҫ�����Ǿ�template,���о���
 ���ǰ������ģ������ԭ����Ҫȷ���������͵ĵط���T�滻����
 ���⣬��ʹ��ģ���ʱ��
 ���ں���ģ�壬����ֱ�ӰѶ���õĲ����Ž�ȥ������
 �����ĵ��ã�������ģ�壬  ԭ���������ģ� myClass class1(3,5)��
 ���ڻ���  myClass<int,int> class1(3,5);
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
//ע���Ա�����������涨����﷨����
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
