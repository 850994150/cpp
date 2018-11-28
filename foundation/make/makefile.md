# /***********************************************************
# * Author       : M_Kepler
# * EMail        : m_kepler@foxmail.com
# * Last modified: 2017-07-27 16:53:15
# * Filename     : makefile
# * Description  : 预处理 -> 编译 -> 汇编 -> 链接
# http://www.cnblogs.com/Tan-sir/p/7280776.html
# http://www.cnblogs.com/vamei/archive/2013/04/29/3051062.html
# helloworld is a binary file
# target: prerequisite 为依赖关系
# 即目标文件依赖于前提文件。可以有多个前提文件，用空格分开。

# helloworld: test.o
	# echo "good"
	# gcc -o helloworld test.o

# test.o: test.c
	# gcc -c -o test.o test.c


# *************************宏
# CC = gcc
# helloworld: test.o
	# echo "good"
	# $(CC) -o helloworld test.o

# test.o: test.c
	# $(CC) -c -o test.o test.c

# *************************内部宏
# $@: 目标文件名
# $^: 所有前提文件
# $<: 第一个依赖文件
# ******************************/
# 
CC = gcc
helloworld: test.o
	echo $@
	$(CC) -o $@ $^

test.o: test.c
	$(CC) -c -o $@ $^


# *************************后缀依赖
# .SUFIXES: .c .o 来说明.c和.o是后缀
#
