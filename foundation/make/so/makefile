 # **********************************************************
 # * Author       : M_Kepler
 # * EMail        : m_kepler@foxmail.com
 # * Last modified: 2018-03-02 14:34:24
 # * Filename     : makefile
 # * Description  :
 # ***********************************************************

.PHONY: build all clean

CURR_PWD = $(shell pwd)

LIBS = -lmax
LDFLAGS= -L$(CURR_PWD)

# ***********************************************************

all: desc test.out

build: libmax.so

# libmax.so: max.c  # gcc -fpic -shared -o libmax.so max.c 

desc:
	@echo "*****************************************************"
	@echo "* 将 max.c  打包成动态库                            *"
	@echo "* 在 test.c 中使用动态库                            *"
	@echo "*****************************************************"


# 生成动态库-fpic -shared
libmax.so: max.o
	gcc -o $@ -shared $^
	# gcc -fpic -shared  max.c -o libmax.so

max.o: max.c
	gcc -c -fpic $^ -o $@

test.out: test.c libmax.so
	gcc $< $(LDFLAGS) $(LIBS) -o $@


clean:
ifeq ($(findstring /dao,$(CURR_PWD)),/dao)
	rm -f tp*
endif
	rm -f *.bnd *.lst *.C *.o *.so *.ibmcpp *.lis *.out

