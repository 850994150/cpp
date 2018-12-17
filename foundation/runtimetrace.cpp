/***********************************************************
* Author       : M_Kepler
* EMail        : m_kepler@foxmail.com
* Last modified: 2017-12-10 23:30:35
* Filename     : runtimetrace.cpp
* Description  :
* 最终要实现的是，在所有文件中都可以像如下语句般抛出异常:
    // g_clRuntimeMsg.SetMsg(RUNTIME_TRACE(), iRetCode, stCallLbmPara.chOperationType);
**********************************************************/

#include <iostream>
#include <string.h>
using namespace std;


#define RUNTIME_TRACE() RuntimeTrace(__FILE__, __FUNCTION__, __LINE__)

// extern char g_szRuntimeTrace[2048 + 1];
char g_szRuntimeTrace[2048 + 1];

char * RuntimeTrace(const char *p_pszFile, const char *p_pszFunction, int p_iLine)
{
  int iSize = 0;
  const unsigned int iMaxLevel = 6; 
  void * apSymbols[iMaxLevel] = {NULL, NULL, NULL, NULL, NULL, NULL};
  char ** ppszSymbols = NULL, szTemp[256] = {0};

  memset((void *)g_szRuntimeTrace, 0x00, sizeof(g_szRuntimeTrace));
  memset(apSymbols, 0x0, sizeof(apSymbols));

  snprintf(g_szRuntimeTrace, sizeof(g_szRuntimeTrace) - 1, 
    "<?xml version=\"1.0\" encoding=\"gb2312\" ?>"
    "<RUNTIME_TRACE>"
      "<TRACE_POS FILE=\"%s\" FUNCTION=\"%s\" LINE=\"%d\" />"
      "<CALL_STACK>", p_pszFile, p_pszFunction, p_iLine);

#if !defined(OS_IS_WINDOWS)
  for (int iIdx = 1; iIdx < iSize && (ppszSymbols[iIdx])[0] != 0x00; ++iIdx)
  {
    memset((void *)szTemp, 0x00, sizeof(szTemp));
    // snprintf(szTemp, sizeof(szTemp) - 1, "<CALL LEVEL=\"%d\" FUNCTION=\"%s\" />", iIdx - 1, FilterChar(FilterChar(ppszSymbols[iIdx], 0x0A), 0x0D));
    snprintf(szTemp, sizeof(szTemp) - 1, "<CALL LEVEL=\"%d\" FUNCTION=\"%s\" />", iIdx - 1, 0x0D);
    strncat(g_szRuntimeTrace, szTemp, (sizeof(g_szRuntimeTrace) - strlen(g_szRuntimeTrace) - 1));
  }
#endif  //!defined(OS_IS_WINDOWS)
  
  strncat(g_szRuntimeTrace, "</CALL_STACK></RUNTIME_TRACE>", (sizeof(g_szRuntimeTrace) - strlen(g_szRuntimeTrace) - 1));

#if defined(OS_IS_LINUX)
  free(ppszSymbols);
#else
  free(apSymbols[0]);
#endif  // defined(OS_IS_LINUX)

  return g_szRuntimeTrace;
}

int main()
{
    cout << RUNTIME_TRACE() << endl;
    return 0;
}

