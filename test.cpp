#include <iostream>
#include <vector>
#include <string.h>
using namespace std;

int main(int argc, char const *argv[])
{
    vector<string> vecInt{"a", "b", "c", "d"};
    printf("%s\n", vecInt[0].c_str());
    vecInt.erase(vecInt.begin());
    printf("%s\n", vecInt[0].c_str());

    /* code */
    int i = 5;
    int *p = &i;
    p++;
    cout << *p <<endl;

    char a[10] = "abc", b[10] = "012", c[10] = "xyz";
    strcpy( a+1,b+2);
    puts( strcat( a,c+1));


    char szTest[14] = "??";
    // cout << "length" << szTest.length() << endl;
    cout << "length: " << sizeof(szTest)/sizeof(char) << endl;
    cout << "length: " << strlen(szTest) << endl;

    return 0;
}

