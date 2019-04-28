#include <iostream>
#include <math.h>                //此为数学函数库。程序中要用到数学函数时必须包含此语句。
using namespace std;
void f(int n)                    //此函数只判断是否为素数。
{
    int i,j=0;
    for(i=2;i<=sqrt(n);i++)     
        if(n%i==0)
            j++;                //j在这里只起标识作用，若为0不变则说明是素数，否则为非素数。
    if(n==0||n<0) cout<<"数据错误!"<<"\a"<<endl;   //“0和负数”显然不是处理的对象。
    else if(n==1) cout<<"这个数不是素数。"<<endl;  //“1”要特殊处理。
    else
    {
        if(j==0) 
            cout<<"这个数是素数。"<<endl;
        else
            cout<<"这个数不是素数。"<<endl;
    }
}
int main()
{
    int n;
    cout<<"请输入要检验的整数:"<<endl;
    cin>>n;
    f(n);
    return 0;
}
