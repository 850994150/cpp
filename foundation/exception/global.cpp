#include <global.h>

char g_szRuntimeTrace[2048 + 1];
class CContext g_clContext;

CRuntimeMsgPlugin g_clRuntimeMsg_PlugIn;
CRuntimeMsg g_clRuntimeMsg_NoPlugin;

#if !defined(OS_IS_AIX) && defined(DATABASE_IS_ORACLE)
struct sqlca sqlca
#ifdef SQLCA_INIT
= {
    {'S', 'Q', 'L', 'C', 'A', ' ', ' ', ' '},
    sizeof(struct sqlca),
    0,
    {0, {0}},
    {'N', 'O', 'T', ' ', 'S', 'E', 'T', ' '},
    {0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}
  }
#endif  // SQLCA_INIT
;
#endif  // !defined(OS_IS_AIX) && defined(DATABASE_IS_ORACLE)
