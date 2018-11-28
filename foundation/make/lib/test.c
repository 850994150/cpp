#include "lib.h"
#include <stdio.h>
#include <stdlib.h>

int main( int argc, char **argv ) {
    printf( "argc:%d\n", argc);
    if ( argc != 3 )
    {
        printf( "输入形式为: %s arg1 arg2", argv[0] );
    }
    int c = add(atoi(argv[1]), atoi(argv[2]));
    char strc[25];
    sprintf(strc, "%d", c); // linux下没有itoa函数.

    printf( "%s + %s = %s\n", argv[1], argv[2], strc);

    cout("调用lib的输出函数");
    return 0;
}
