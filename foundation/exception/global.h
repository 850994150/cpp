#if !defined(__kbss_global_h__)
#define __kbss_global_h__

#include <runtimemsg.h>
#include <context.h> 

extern char g_szRuntimeTrace[2048 + 1];
extern class CContext  g_clContext;

extern class CRuntimeMsgPlugin g_clRuntimeMsg_PlugIn;
extern class CRuntimeMsg g_clRuntimeMsg_NoPlugin;

#if defined(DLL_IS_PLUGIN) 
#define g_clRuntimeMsg g_clRuntimeMsg_PlugIn
#else
#define g_clRuntimeMsg g_clRuntimeMsg_NoPlugin
#endif

// #ifndef 
#if !defined(DBENGINE_IS_ODBC) && !defined(DBENGINE_IS_ESQL)
  #define DBENGINE_IS_ESQL
#endif  // !defined(DBENGINE_IS_ODBC) && !defined(DBENGINE_IS_ESQL)

#if defined(DBENGINE_IS_ESQL)
  #if !defined(OS_IS_AIX) && defined(DATABASE_IS_ORACLE)
    #define SQLCA_NONE
    #include <sqlca.h>
    #undef SQLCA_NONE
    extern struct sqlca sqlca;
  #endif  // !defined(OS_IS_AIX) && defined(DATABASE_IS_ORACLE)
#endif  // defined(DBENGINE_IS_ESQL)

#endif  // __kbss_global_h__

