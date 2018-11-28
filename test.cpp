#include <iostream>
#include <string.h>
using namespace std;

int main(int argc, char const *argv[])
{
    /* code */
    int i = 5;
    int *p = &i;
    p++;
    cout << *p <<endl;

    char a[10] = "abc", b[10] = "012", c[10] = "xyz";
    strcpy( a+1,b+2);
    puts( strcat( a,c+1));
    return 0;
}

