#!/bin/bash
#declare -a array

array=(var1 var2 var3 var4)
echo $1
shift
echo $1
echo ${#array[@]}
echo ""
filename=(`ls`) #把ls命令得到的放到filename里
for var in ${array[@]};do
    echo $var
done
