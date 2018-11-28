/***********************************************************
* Author       : M_Kepler
* EMail        : m_kepler@foxmail.com
* Last modified: 2018-05-07 13:46:27
* Filename     : enum.cpp
* Description  :
 * 枚举(enumeration)
 * 枚举类型的定义、赋值, 一般放在头文件中
 * 没有为枚举定义算术运算
 * 取值范围
     * 找上下限方法: 找到最大/小的枚举值，再找到与这个枚举值最接近的2的幂
     * 上限:比如最大的枚举值是101,最接近的幂是128,所以上限就是127
     * 下限:比如最小的枚举值不小于0,则取值范围的下限为0;
     * 如果最小枚举值是-6,最接近的幂是-8，所以下限是 -7
**********************************************************/
#include <stdio.h>
#include <iostream>
using namespace std;



enum SPECTRUM
{
    red,
    orange,
    yellow,
    green,
    blue,
    violet,
    indigo,
    ultraviolet
}; // 让spectrum成为新类型的名称,将为每个枚举类型分配一个整型值，默认从0开始，逐个加1

enum BIGSTEP
{
    first,
    second = 100,
    third
}; // 可为其中某个枚举量赋值，也可全部赋初值。first默认为0, 未初始化的枚举量的值比前面的枚举量大1,因此third为101

enum STEPS
{
    zero,
    null = 0,
    one,
    numero_uno = 1
}; // 也可以创建多个值相同的枚举量

enum ERROR {
    CONF_ERROR			= 6000,       // 读取配置文件出错
    DATE_EMPTY			= 6001,       // 数据为空　　
    PERFORM_FAILED		= 6003,       //
    DOC_FAILED			= 6004,       // 序列化失败
	ERR_BAD_CB_COMMD	= 6005,       // bad callback commd
    INPUT_NULL          = 6006,       // 入参为空
    SUCCESS             = 7000        // 成功
};

enum EN_FLOW_CTRL
{
    FC_N_MANDFIELD = 1,
    FC_U_MANDFIELD = 2,
    FC_D_MANDFIELD = 4
}enFlowCtrl;


int main()
{
    SPECTRUM band;
    band = blue; // 枚举类型的变量的值只能是枚举类型中的其中之一,非enum值赋给enum变量视为错误
    int n = 100;
    n = band; // 枚举类型可隐式转化为int，反过来则不行: // band = n;
    cout << "band:" << band << "\tn:" << n << endl; // 得到结果是4
    band = SPECTRUM(9);// 5不属于枚举值，但在取值范围内
    cout << "band=spectrum(5)：" << band << endl; //得到结果是4

    int color = blue;
    band = green;
    color = 3+red;
    cout << color << endl;

    // 这个三元运算符...
    char p_refchValue='1';
    enFlowCtrl = p_refchValue == '2' ? FC_D_MANDFIELD : p_refchValue == '1' ? FC_U_MANDFIELD : FC_N_MANDFIELD; 
    cout << "enFlowCtrl: " << enFlowCtrl << endl;



    return 0;
}


