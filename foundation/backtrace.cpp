/***********************************************************
* Author       : M_Kepler
* EMail        : m_kepler@foxmail.com
* Last modified: 2017-12-15 14:14:38
* Filename     : backtrace.cpp
* Description  : linux下的backtrace记录程序运行堆栈信息
**********************************************************/

#include <execinfo.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SIZE 100

void myfunc3(void)
{
   int j, nptrs;
   void *buffer[100];
   char **strings;

   nptrs = backtrace(buffer, SIZE);
   printf("backtrace() returned %d addresses\n", nptrs);

   /* The call backtrace_symbols_fd(buffer, nptrs, STDOUT_FILENO)
      would produce similar output to the following: */

   strings = backtrace_symbols(buffer, nptrs);
   if (strings == NULL)
   {
      perror("backtrace_symbols");
      exit(EXIT_FAILURE);
   }

   for (j = 0; j < nptrs; j++)
   {
      printf("%s\n", strings[j]);
   }

   free(strings);
}

static void myfunc2(void)
{
   myfunc3();
}

void myfunc(int ncalls)
{
   if (ncalls > 1)
      myfunc(ncalls - 1);
   else
      myfunc2();
}

int main(int argc, char *argv[])
{
   if (argc != 2)
   {
      fprintf(stderr, "%s num-calls\n", argv[0]);
      exit(EXIT_FAILURE);
   }

   myfunc(atoi(argv[1]));
   exit(EXIT_SUCCESS);
}

/*
 * http://blog.csdn.net/yetyongjin/article/details/7759144
 * 编译：gcc backtrace.c -o backtrace
 * //会显示函数名：gcc -rdynamic backtrace.c -o backtrace
 * 运行：./a 0
 */
