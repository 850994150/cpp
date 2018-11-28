 # **********************************************************
 # */
 # * Author       : M_Kepler
 # * EMail        : m_kepler@foxmail.com
 # * Last modified: 2018-03-02 14:21:18
 # * Filename     : makefile
 # * Description  :
 # ***********************************************************

.PHONY: build clean

 
CURR_PWD = $(shell pwd)


LIBS=-ltest
LDFLAGS=-L$(CURR_PWD)
DEBUGOPS = -g

all: desc test.out

desc:
	@echo "*****************************************************"
	@echo "* 将 math.c print.c 打包成静态库, 在lib.h中暴露接口 *"
	@echo "* 在 test.c 中使用静态库                            *"
	@echo "*****************************************************"


build: libtest.a


# 生成静态库
libtest.a: print.o math.o
	ar crv libtest.a math.o print.o


math.o: math.c
	gcc -c math.c


print.o: print.c
	gcc -c print.c


# 使用静态库
test.out: test.c libtest.a
	gcc $< $(DEBUGOPS) $(LDFLAGS) $(LIBS) -o $@


clean:
ifeq ($(findstring /dao,$(CURR_PWD)),/dao)
	rm -f tp*
endif
	rm -f *.bnd *.lst *.C *.o *.so *.ibmcpp *.lis *.out *.a

