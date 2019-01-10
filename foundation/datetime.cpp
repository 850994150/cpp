/*
 **********************************************************
 * Author       : M_Kepler
 * EMail        : m_kepler@foxmail.com
 * Last modified: 2018-12-06 09:51:03
 * Filename     : datetime.cpp
 * Description  :
 ***********************************************************
 */

#include <time.h>
#include <sys/timeb.h>
#include <string>
using namespace std;

/*
 * @brief			获取当前系统日期时间
 * @param[in]		pDataFormat				日期的格式
 * @param[in]		pTimeFormat				时间格式
 * @return			该函数在初始化类对象时, 即初始化类成员m_stCurrSysTime
 */
typedef struct CurrentSysTime
{
	char pDate[16];		//年月日
	char pTime[16];		//时分秒
	char pTimeMs[4];	//毫秒
}CurrentSysTime, *pCurrSysTime;
CurrentSysTime m_stCurrSysTime;
void SysNowTime(const char* pDataFormat, const char* pTimeFormat)
{
    time_t timep;
    time(&timep);
    struct timeb tb;
    /*
       string test = "20180929";
       char Date[16];
       test.copy(m_stCurrSysTime.pDate, 8, 0);
       *(m_stCurrSysTime.pDate + 8) = '\0';
     */

    strftime(m_stCurrSysTime.pDate, sizeof(m_stCurrSysTime.pDate), pDataFormat, localtime(&timep));
    strftime(m_stCurrSysTime.pTime, sizeof(m_stCurrSysTime.pTime), pTimeFormat, localtime(&timep));

    ftime(&tb);
    sprintf(m_stCurrSysTime.pTimeMs, "%03d", tb.millitm);
}

/*
 * @brief	行字符串转毫秒时间 (开始位置往后15位是日期时间,若>15位,则16-19为毫秒)
 * @param   strOrig			整个字符串
							时间格式为:YYYYMMDD-HHMMSS; formate = (char*)"%4d%2d%2d-%2d%2d%2d
 * @param   iStart			字符串中时间开始位置
 * @param   iLen			字符串中**秒级**时间结束位置
							例: runlog0.log 为iStart = 0, iLen = 15
 * @return	time_t			返回毫秒级时间
 */
time_t StringToMs(string strOrig, int iStart, int iEnd)
{
    tm tm_;
    string str;
    int iMsStart;
    int year, month, day, hour, minute, second;
    string strLogType = "UNIX";

    char * formate;
    int iLen = iEnd - iStart;

    formate = (char*)"%4d%2d%2d-%2d%2d%2d";
    str = strOrig.substr(iStart, iLen);

    sscanf(str.c_str(), formate, &year, &month, &day, &hour, &minute, &second);

    if (strLogType == "WIN")
    {
        iStart = iStart + 1;
        iEnd = iEnd + 1;
        iMsStart = 22;
    }
    else if (strLogType == "UNIX")
    {
        iMsStart = iEnd + 1;
    }

    tm_.tm_year = year - 1900;
    tm_.tm_mon = month - 1;
    tm_.tm_mday = day;
    tm_.tm_hour = hour;
    tm_.tm_min = minute;
    tm_.tm_sec = second;
    tm_.tm_isdst = 0;
    time_t tm_s = mktime(&tm_);
    if (strOrig.length() <= 15)
    {
        time_t tm_ms = tm_s * 1000;
        return tm_ms;
    } 
    else
    {
        // 20180202-091002-549327 取549为毫秒
        time_t tm_ms = (tm_s * 1000) + stoi(strOrig.substr(iMsStart, 3)); // 转化为毫秒
        return tm_ms;
    }
}

int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}
