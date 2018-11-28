/***********************************************************
 * Author       : M_Kepler
 * EMail        : m_kepler@foxmail.com
 * Last modified: 2018-07-04 18:44:57
 * Filename     : vector.cpp
 * Description  :
 ************************************************************/

#include <vector>

#include <iostream>

using namespace std;

int main( int argc, char **argv )
{
    std::vector<int> astInt;
    astInt.clear();
    for ( int i = 0; i < 10; ++i )
    {
        astInt.push_back(i);
    }

    if ( astInt.size() <0 )
    {
        cout<<"no data"<<endl;
    }
    else
    {
        for ( int i = 0; i < astInt.size(); ++i )
        {
            cout<<astInt[i]<<endl;
        }
    }

    return 0;
}

