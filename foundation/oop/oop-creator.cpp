/*
 **********************************************************
 * Author       : M_Kepler
 * EMail        : m_kepler@foxmail.com
 * Last modified: 2018-07-06 17:13:13
 * Filename     : oop-copy.cpp
 * Description  : 类构造函数
 ***********************************************************
 */
#include <stdio.h>
#include <iostream>  
#include <string.h>
using namespace std;  

class String  
{  
    public:  
        String(const char* str=NULL);   			// 普通构造函数  
        String(const String &other);     			// 拷贝构造函数  (深浅拷贝都是这个定义)
        String & operator=(const String &other);    // 赋值函数  
        ~String(void);                              // 析构函数  
        int length();
    public:  
        String & operator+(const String &str);  			// 改变本身的相加  
        friend ostream& operator<<(ostream&out,String& s);   // 友元函数
        friend istream& operator>>(iostream&in,String& s);   
    private:  
        char * m_string ;                           // 指针成员
};  


int String::length()
{
    return 0;
}


String::~String(void)  
{  
    cout << "Destrcutor" << endl;  
    if(m_string!=NULL)                   // 不为空，就释放内存  
    {  
        delete [] m_string;  
        m_string = NULL;  
    }  
}  


String::String(const char* str)    // 普通构造函数  
{  
    cout << "Constructor" << endl;  
    if(str==NULL)        // 如果 str 为 NULL，就存一个空字符串 ""  
    {  
        m_string=new char[1];  
        *m_string ='\0';  
    }  
    else  
    {
        m_string = new char[strlen(str)+1] ;   // 分配空间  
        strcpy(m_string,str);  
    }  
}   


String::String(const String& other)             // 拷贝构造函数  
{  
    cout<<"Deep copy Constructor"<<endl;  
    m_string=new char[strlen(other.m_string)+1] ; // 分配新空间并拷贝(深拷贝)  
    strcpy(m_string,other.m_string);  
}  

String & String::operator=(const String & other)  // 赋值函数
{  
    cout << "Operator = funtion" <<endl ;  
    if(this == &other) 				// 如果对象和 other 是用一个对象，直接返回本身  
    {  
        return *this;  
    }  
    delete []m_string; 			    // 先释放原来的内存  
    m_string = new char[strlen(other.m_string)+1]; // 申请空间并赋值  
    strcpy(m_string,other.m_string);  
    return * this;  
}  


String & String::operator+(const String & str)  
{  
    char * temp=m_string;  
    m_string=new char[strlen(m_string)+strlen(str.m_string)+1];  
    strcpy(m_string,temp);  
    delete[]temp;  
    strcat(m_string,str.m_string);  
    return *this;  
}   

ostream& operator<<(ostream& out,String& s)  
{  
    for (int i=0; i <s.length(); i++)  
    {
        out<<s<<"";  
    }
    return out;  
}  


istream& operator>>(istream& in,String& s)  
{  
    char p[50];  
    in.getline(p,50);  
    s=p;  
    return in;  
}  

/*
int main()
{  
    String a("hello"); // 调用普通构造函数  
    String b("world"); // 调用普通构造函数  
    String c(a); // 调用拷贝构造函数  
    c=b; // 调用赋值函数  
    return 0;  
} 
*/


class Person
{
public:
    Person(){}
    Person(const Person& p)
    {
        cout << "copy creator" << endl;
    }

    Person& operator=(const Person& p)
    {
        cout << "overwrite = operator" << endl;
        return *this;
    }
    ~Person(void){
        cout<< "destroy func"<<endl;
    }

private:
    int age;
    string name;
};

void f(Person p)
{
    return;
}

Person f1()
{
    Person p;
    return p;
}

int main()
{
    Person p;
    Person p1 = p;    // 1
    Person p2;

    p2 = p;           // 2
    f(p2);            // 3

    p2 = f1();        // 4

    Person p3 = f1(); // 5

    return 0;
}
