/***********************************************************
* Author       : M_Kepler
* EMail        : hellohuangjinjie@gmail.com
* Last modified: 2016-04-11 16:16:02
* Filename     : stack-stl.cpp
* Description  :
    * push()\pop()\top()\empty()\size()
**********************************************************/

#include <stack>
#include <iostream>
using namespace std;

int main( )
{
    int n;
    double item;
    stack<double> stack_stl; // declares and initializes a stack of numbers
    cout << "Type in an integer n followed by n decimal numbers.\n";
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> item;
        stack_stl.push(item);
    }
    cout << endl;
    while (!stack_stl.empty( )) {
        cout << stack_stl.top( ) << " ";
        stack_stl.pop( );
    }
    cout << endl;
}
