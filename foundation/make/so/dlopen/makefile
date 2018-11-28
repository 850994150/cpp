
.PHONY: all clean

all: main.out libtest_1.so libtest_2.so

# 生成动态库
libtest_1.so:test.cpp
	g++ -fPIC -shared test.cpp -o libtest_1.so

libtest_2.so:test.cpp
	g++ -fPIC -shared test.cpp -o libtest_2.so


# 使用动态库
main.out: main.cpp
	g++ -g -Wl,--no-as-needed -ldl main.cpp -rdynamic

clean:
	rm -f *.out *.so
