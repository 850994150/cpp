/***********************************************************
* Author       : M_Kepler
* EMail        : m_kepler@foxmail.com
* Last modified: 2017-08-05 23:30:59
* Filename     : stock10.h
* Description  : 头文件、类定义
**********************************************************/

#ifndef STOCK1_H_
#define STOCK1_H_
#include <string>
using namespace std;

class Stock
{
private:
    string company;
    long shares;
    double share_val;
    double total_val;
    void set_tot(){ total_val=shares * share_val; }
public:
    Stock();
    Stock(const string &co, long n=0, double pr=0.0);
    ~Stock();
    void buy(long num, double price);
    void sell(long num, double price);
    void update(double price);
    void show();
};
#endif

