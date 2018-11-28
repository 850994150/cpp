
.PHONY: clean all

all: getlastline.out

DEBUG_OPS = -g
CFLAGS=$(DEBUG_OPS) -Wall

CC=g++
CCSTD=--std=c++11

# 预处理
getlastline.i : getlastline.cpp
	@echo "预处理"
	$(CC) -E $(CCSTD) $^ -o $@

# 编译
# 在此过程加入调试选项
getlastline.s : getlastline.i
	@echo "编译"
	$(CC) -S $(CCSTD) $(CFLAGS) $^ -o $@

# 汇编
getlastline.o : getlastline.s
	@echo "汇编"
	$(CC) -c $(CCSTD) $^ -o $@

# 链接
getlastline.out : getlastline.o
	@echo "链接"
	$(CC) $(CCSTD) $^ -o $@


clean:
	rm -rf *.i *.s *.o *.out

