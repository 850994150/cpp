#!/bin/sh
fun()
{
    sum=0
    for i in `seq $1 $2`
    do
        sum=`expr $i + $sum`
    done
    echo $sum
}
echo "Please input 2 number:"
read a b
expr $a + 0 1>/dev/null 2>&1
if [ $? -ne 0 ];then
    echo "wrong number"
    exit 1;
fi
expr $b + 0 1>/dev/null 2>&1
if [ $? -ne 0 ];then
    echo "wrong number"
    exit 1;
fi
if [ $a -ge $b ];then
    echo "wrong number"
    exit 1;
fi
fun $a $b
