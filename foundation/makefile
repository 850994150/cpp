# **********************************************************
# * Author       : M_Kepler
# * EMail        : m_kepler@foxmail.com
# * Last modified: 2018-10-09 13:20:27
# * Filename     : makefile
# * Description  : compile all %.c and %.cpp to .o
# ***********************************************************

CC = gcc
 
XX = g++
 
CFLAGS = -Wall -O -g
 
TARGET = ./main.out
 
###########################################################
 
%.o:%c
	$(CC) $(CFLAGS) -c $< -o $@
 
%.o:%.cpp
	$(XX) $(CFLAGS) -c $< -o $@

SOURCES = $(wildcard *.c *.cpp)
 
OBJS = $(patsubst %.c,%.o, $(patsubst %.cpp,%.o,$(SOURCES)))
 
$(TARGET):$(OBJS)
	$(XX) $(OBJS) -o $(TARGET)
	chmod a+x $(TARGET)

clean:
	rm -rf *.o main

