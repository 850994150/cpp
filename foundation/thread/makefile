# *****************************************
# * Author       : M_Kepler
# * EMail        : m_kepler@foxmail.com
# * Last modified: 2018-08-02 18:27:10
# * Filename     : makefile
# * Description  :
# *****************************************

INC_PATH = /usr/local/include
LIB_PATH = /usr/local/lib

.PHONY: all thread multi_thread clean

all: thread.out multi_thread.out

thread: thread.out
thread.out: thread.cpp
	g++ --std=c++11 -pthread $^ -o $@

multi_thread: multi_thread.out
multi_thread.out: multi_thread.cpp
	g++ --std=c++11 -pthread $^ -o $@


# make install
# install:
	# cp slog.h ${INC_PATH}
	# cp libslog.a ${LIB_PATH}

# uninstall:
	# rm ${INC_PATH}/slog.h
	# rm ${LIB_PATH}/libslog.a

clean:
	rm -f *.o *.out

