/***********************************************************
* Author       : M_Kepler
* EMail        : m_kepler@foxmail.com
* Last modified: 2017-08-05 23:30:49
* Filename     : stock10.cpp
* Description  : 类实现
**********************************************************/

#include <iostream>
#include "stock10.h"
using namespace std;

Stock::Stock()
{
    cout << "Default constructor closed" << endl;
    company = "no name";
    shares= 0;
    share_val = 0.0;
    total_val = 0.0;
}

Stock::Stock(const string &co, long n, double pr)
{
    cout << "Constructor using " << co << " called" << endl;
    company = co;
    if (n<0) {
        cout << "Number of shares can't be negative." << company << " shares set to 0." << endl;
        shares= 0;
    }
    else
        shares= n;
    share_val = pr;
    set_tot();
}
Stock::~Stock()
{
    cout << "Bye. " << company << endl;
}

void Stock::buy(long num, double price)
{
    if (num<0) {
        cout << "Number of shares purchased can't be negative. " << "Transaction is aborted." << endl;
    }
    else
    {
        shares += num;
        share_val = price;
        set_tot();
    }
}

void Stock::sell(long num, double price)
{
    if (num<0) {
        cout << "Number of shares sold can't be negative. " << "Transaction is aborted." << endl;
    }
    else if(num>shares)
    {
        cout << "You can't shell more than you have! " << "Transaction is aborted." << endl;
    }
    else
    {
        shares -= num;
        share_val = price;
        set_tot();
    }
}

void Stock::update(double price)
{
    share_val = price;
    set_tot();
}

void Stock::show()
{
    // using std::ios_base;
    ios_base::fmtflags orig = cout.setf(ios_base::fixed, ios_base::floatfield);
    streamsize prec = cout.precision(3);
    cout << "Company: "  << company << " Shares: " << shares<< endl;
    cout << " Share Price: $" << share_val;
    cout.precision(2);
    cout << " Total Worth: $" << total_val << endl;
    cout.setf(orig,ios_base::floatfield);
    cout.precision(prec);
}


