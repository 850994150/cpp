/***********************************************************
* Author       : M_Kepler
* EMail        : m_kepler@foxmail.com
* Last modified: 2018-02-01 10:14:16
* Filename     : define.cpp
* Description  : 宏和内联函数 
**********************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
using namespace std;


#define PI 3.1415 // C++中更喜欢用const定义常量

#define SQR(x) (x * x) // 预处理替换后：a+2*a+2，所以应该加上括号
#define SQR2(y) ((y) * (y))

#define ARRAYCOUNT(a) (sizeof(a) / sizeof(a[0])) // 用宏实现计算数组元素个数

#define SAFEDELETE(p) \
	do                \
	{                 \
		delete p;     \
		p = NULL;     \
	} while (0);
	// 宏里使用do...while(0)可以放心使用分号风格的几个子句,
	// 在某些调用该宏的句子中不带分号也不会报错

#define MIN(a, b) (a < b ? a : b)
#define MAX(x, y) (((x) > (y)) ? (x) : (y))

template<class T>
inline T callWithMax(const T&a, const T&b)
{
	return a > b ? a : b;
}

#define CALL_WITH_MAX(a, b) ((a) > (b) ? (a) : (b))

#define STR(s) #s				  // 把参数转化为一个字符串
#define CONS(a, b) (int)(a##e##b) // 把两个宏参数粘合在一起,2##e##3就是2e3就是2000

#define WORD_LO(xxx) ((byte)((word)(xxx) & 255)
#define WORD_HI(xxx) ((byte)((word)(xxx) >> 8)

int main(int argc, char *argv[])
{
	int a = 4;
	int b = 5;
	double number1 = 0.001;
	double number2 = 1.021;
	cout << number1 << '\t' << number2 << endl;

#ifdef SQR
	cout << "参数没加括号得到错误的结果: SQR(a+2)应是(4+2*4+2) = " << SQR(a + 2) << endl;
#endif
	cout << "即使加了括号也不一定正确:SQR2(a++)应是(4++)*(4++) = " << SQR2(a++) << endl;
	// 可以看出a本来是4,(a++)后a变成了5，所以(a++)*(a++) = 4 * 5 = 20, 而后a++，a=6
	cout << a << endl;

#ifdef MIN
	cout << "MIN(number1, number2)" << MIN(number1, number2) << endl;
#endif

#ifdef MAX
	cout << "MAX(number1, number2) = " << MAX(number1, number2) << endl;
	cout << "MAX(number1++, number2++) = " << MAX(number1++, number2++) << endl;
#endif

#ifdef CONS
	cout << "CONS(a,b) (int)(a##e##b) = " << CONS(2, 3) << endl;
#endif // CONS

#ifdef _DEBUG // 等价于 #ifndef 意思是 if ! defined
	cerr << "Variable x = " << x << endl;
#else
	cout << "DEBUG  not define" << endl;
#endif // !DEBUG

	printf("a = %d, b = %d, callWithMax = %d\n", a, b, callWithMax(a, b));

	cout << "\n===---===---=== 宏计算数组元素个数 ===---===---===" << endl;
	char array[2] = {'a', 'b'};
	printf("count array with define：%d\n", ARRAYCOUNT(array));

	cout << "\n===---===---=== 宏与do...while(0) ===---===---===" << endl;
	char *ptr  = new char [10];
	ptr = "adfasdfadsf";

	cout << ptr << "\t" << &ptr << endl;
	SAFEDELETE(ptr);
	cout << &ptr << endl; // cored dump


	return 0;
}

