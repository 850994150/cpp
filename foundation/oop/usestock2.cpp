/***********************************************************
 * Author       : M_Kepler
 * EMail        : m_kepler@foxmail.com
 * Last modified: 2017-08-05 23:31:25
 * Filename     : usestock2.cpp
 * Description  : 使用类
 **********************************************************/

#include <iostream>
#include "stock10.h"
// using namespace std;

int main()
{
    {
        using std::cout;
        cout << "Using constructors to create new objects" << endl;
        Stock stock1("NanoSmart", 12, 20.0);
        stock1.show();
        Stock stock2 = Stock("Boffo Objects", 2, 2.0);
        stock2.show();

        cout << "Assigning stock1 to stock2:" << endl;
        stock2 = stock1;
        cout << "Listing stock1 and stock2:" << endl;
        stock1.show();
        stock2.show();

        cout << "Using a constructor to reset an object" << endl;
        stock1 = Stock("Nifty Foods", 10, 50.0);
        cout << "Revised stock1:" << endl;
        stock1.show();
        cout << "Done" << endl;
    }

    return 0;
}

/*
g++ -c stock10.cpp -o stock.o
g++ -c usestock2.cpp -o usestock2.o
g++ stock10.o usestock2.o -o usestock2.out
./usestock2.out
*/


