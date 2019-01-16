/*
 **********************************************************
 * Author       : M_Kepler
 * EMail        : m_kepler@foxmail.com
 * Last modified: 2019-01-14 17:44:41
 * Filename     : string_test.cpp
 * Description  :
 * ---- === --- === --- === --- === --- === --- === --- === --- === -- === --- ===
 * string 类方法
 * ---- === --- === --- === --- === --- === --- === --- === --- === -- === --- ===
 
    * str.find(str2, 7) // 在str中从指定位置从前向后查找子串,
                        // 成功返回str2首个字符在str中的地址, 否则返回npos, rfind则从后往前找
    * str.find_first_of(str2, 7) / str.find_first_not_of /  str.find_last_of / str.find_last_not_of
                        // 在str中指定位置开始查找str2, 只要str中找到str2的任意字符, 就返回该字符位置

 * ---- === --- === --- === --- === --- === --- === --- === --- === -- === --- ===
 * 字符处理函数 https://blog.csdn.net/frecon/article/details/79605941
 * #include <string.h>
 * ---- === --- === --- === --- === --- === --- === --- === --- === -- === --- ===
  
 * strlen /strnlen
    * int strlen ( const char *str )
    * 返回字符串的实际长度，不含 '\0'
    * int strlrn ( const char *str, size_t maxlen )
    * 区别: 能防止某些字符串不以'\0'结束而引发的错误
     
 * strcpy
    * char *strcpy( char *dest, const char *src )
        * 从源串的开始拷贝字符到目标串地址, 遇到’\0’结束;
        * 不安全: 如果src长度比dst长度大时, 会栈溢出或覆盖其他变量的内存
    * char *strncpy(char *dest, const char *src, size_t n)
        * 从源串的开始拷贝n个字符到目标串地址，n大于源串长度时，遇到 '\0' 结束;
            * 1. dst是否足够空间容纳src
            * 2. dst末尾是否补\0
            * 3. 一般定义 n = strlen(dst) = strlen(src) + 1
            * 4. strncpy不负责在目标串末尾补充'\0' 字符 
            * 5. 当strlen(dst)远大于n时效率低下, 不如用snprintf
        * strlen(dst) = n <= strlen(src), n小于源串长度时, 只拷贝到第n个, 如果是等式, 此时dst已经没有地方放\0了
        * strlen(dst) = n > strlen(src), n大于源串长度时，遇到’\0’结束; dst剩余字节都用’\0’填充
        * strlen(dst) > n >= strlen(src), n大于源串长度时，遇到’\0’结束; dst剩余字节都用’\0’填充
        * strlen(dst) < n, 会破坏dst后面的内存, 输出的值不确定
    * 入参错误的情况: 
    char * sss1;
    // char sss2[20] = "abcd1234"; // 运行时错误segment fault
    char *sss2 = "abcd1234";       // 运行正常
    strncpy(sss1, sss2, 4);
    printf("%s\n", sss2);
     
 * strcmp / strncmp
    * int strcmp( char *str1, char *str2 )
    * 相等返回0, str1大于str2返回1, str1小于str2返回-1
    * int strncmp( char *str1, char *str2, size_t n )
    * 区别: 只比较前n个
     
 * strcat / strncat
    * char *strcat(char *dest, const char *src)
    * 将参数src字符串拷贝到参数dest所指的字符串尾; 第一个参数dest要有足够的空间来容纳要拷贝的字符串
    * char *strncat(char *dest, const char *src, size_t n);
    * 区别: 只拷贝前n个
     
 * strchr / strrchr
 * strstr
 * strtok / strtok_r
 * memset / memcpy / memccpy / memmove
    * 都是拷贝一定长度的内存内容
    * 当内存发生重叠时, memcpy不能保证拷贝的正确性, memmove可以保证
 * 
 ***********************************************************
 */

#include <regex>
#include <vector>
#include <time.h>
#include <stdio.h>
#include <assert.h>
#include <stdarg.h>
#include <string.h>
#include <iostream>
using namespace std;

// http://blog.csdn.net/eager7/article/details/8131437

void debugLog(const char *, int , const char * , ...);


struct  stuff
{
    char job[20];
    int age;
    float height;
};


/* ---- === --- === --- === --- === --- === --- === --- === --- === -- === --- ===  */
/* ---- === --- === --- === --- == 字符处理库函数 == --- === --- === -- === --- ===  */
/* ---- === --- === --- === --- === --- === --- === --- === --- === -- === --- ===  */

// snprintf(char*res, sizeof(res), char*formate, ...);
int MySnprintf(char *dest, int size, char *formate, ...)
{
    int iRst;
    va_list ap;
    va_start(ap, formate);
    iRst = vsprintf(dest, formate, ap);
    va_end(ap);
    return iRst;
}


void MyStrcpy(char* dest, const char* src)
{
    while ((*dest++ = *src++) != '\0') ;
}

void MyStrncpy(char *dest, const char *src, int len)
{
    assert((dest!=NULL)&&(src!=NULL));
    char *cp = dest;
    int offset = len;

    // 当len = dest的时候, 需要手动给dest补充\0

    while( len && (*cp++ = *src++) != '\0')
    {
        len--;
    }
    // sizeof(dst) > len > sizeof(src) dst后面填\0
    if(len)
    {
        while(--len)
        *cp++='\0';
	}
    // len >= sizeof(dst) 会破坏dst后面的内存
    if (offset >= strlen(dest))
    {
        *(cp + len - 1) = '\0';
    }
    
}


/*
 * memcpy功能是将内存块的内容复制到另一个内存块, (dst和src内存区域不能重叠), 入参就是内存开始的地址和要复制的长度
 * 相对于strncpy, memcpy 可以拷贝任意类型, 按字节拷贝不会遇到\0而停止
 * Q: 如果把"001"字符串进行memcpy到一个int变量, 那么该变量是否就是001呢? 
 * A: 不是, 这里是对内存进行拷贝, 字符'0'拷贝到 unsigned long 后也并非数字0了, 而是0的ascii码
 * 1. 栈空间的生长方向是高地址向低地址生长的
 */
void *MyMemcpy(void *dest, const void *src, size_t n)
{
    char *dp = (char*)dest; // 不能对void*指针进行算术操作
    const char *sp = (const char*)src;

    bool flag1 = (sp >= dp && sp < dp + n); // dst地址比src地址低 且发生重叠 (安全)
    // <低地址> dst: [1][2][3][4][5] // 初始为null
    // <低地址>          src: [1][2][3][4][5]
    bool flag2 = (dp >= sp && dp < sp + n); // dst地址比src地址高 且发生重叠 (不安全)
    // <低地址>          dst: [1][2][3][1][2] // 末尾应为4,5, 现在为1,2了
    // <低地址> src: [1][2][3][4][5]

    if (flag2) // 倒序拷贝
    {
        printf("内存覆盖\n");
        dp += n - 1;
        sp += n - 1;
        while (n--)
        {
            *dp-- = *sp--;
        }
    }
    else // 正序拷贝
    {
        while (n--)
        {
            *dp++ = *sp++;
        }
    }
    return dest;
}

void *MyMemcpyOptimised(void *dest, const void *src, size_t n)
{
    assert(src != NULL);

    int wordnum = n / 4; // 
    int slice = n % 4;

    // 转化为整型, 这样一次性就可以拷贝四个字节(32位机器)
    int *psrc = (int*) src;
    int *pdest = (int*) dest;

    while(wordnum--)
        *pdest++ = *psrc++;

    while(slice--)
        *((char *)pdest++) = *((char *)psrc++);
    return dest;
}

void *MyMemmove(void *dst, const void *src, size_t n)
{
    char *pdst = (char *)dst;
    const char *psrc = (const char *)src;

    if (pdst < psrc) // 正序拷贝
    {
        while (n--)
        {
            *(pdst++) = *(psrc++);
        }
    }
    else // 倒序拷贝
    {
        pdst += n-1;
        psrc += n-1;
        while (n--)
        {
            *(pdst--) = *(psrc--);
        }
        
    }
    return pdst;
}

// char* strchr(const char* src, char c);
char* MyStrchr(const char* src, char ch)
{
    assert(src != nullptr);
    const char*cp = src;
    while(*cp++ !='\0')
    {
        if (*cp == ch)
        {
            return (char*)cp;
        }
    }
}


// char *strrchr_res = strrchr(ch_str, ch);
char* MyStrrchr(const char*src, char ch)
{
    assert(src != nullptr);
    const char*cp = src;
    char* ret = nullptr;
    while(*cp++ !='\0')
    {
        if (*cp == ch)
        {
            ret = (char*)cp;
        }
    }
    return ret;
}


// char* strstr(char* str1, const char* str2)
char* MyStrstr(char* str1, const char* str2)
{
    const char* s1 = str1;
    const char* s2 = str2;
    char * cur = str1;

    assert(str1 != NULL);
    assert(str2 != NULL);
    
    if (*str2 == '\0') return str1;
    
    while(cur)
    {
        s1 = cur;
        s2 = str2;
        while(*s1 == *s2){s1++; s2++; };
        if (*s2 == '\0') return cur;
        if (*s1 == '\0') return NULL;
        cur++;
    }
    return NULL;
}


// char *strcat_res = strcat(ch_str, "+strcat");
char* MyStrcat(char* dst, const char* src)
{
    assert(dst != NULL);
    if (src == NULL)
    {
        return dst;
    }
    int len = strlen(src);
    char * tmp = dst + strlen(dst);

    while ((*tmp++ = *src++) != '\0') ;
    return dst;
}


// int len = strlen(str);
int MyStrlen(const char*src)
{
    int iLen = 0;
    assert(src != NULL);
    while(*src++ != '\0' && ++iLen);
    return iLen;
}


// strtok
vector<string> ReadLineToVec(char* pLineBuffer)
{
	char *pFileBuffer = NULL;
	string sLine;
	vector<string> vecStringLine;
	vecStringLine.clear();

	// char *strDelim = (char*)"\n";
	char *strDelim = (char*)",";
	char *strToken = NULL;
	char *nextToken = NULL;

	strToken = strtok_r(pLineBuffer, strDelim, &nextToken);
	while (strToken != NULL)
	{
		sLine.assign(strToken);
		vecStringLine.push_back(sLine);
		strToken = strtok_r(NULL, strDelim, &nextToken);
	}
	return vecStringLine;
}


// char* strtok(char* str, const char* delimiters);
/*
 * 从str中把delimiters中**包含**的字符替换成'\0', 注意包含的字符都会被替换, 而不是替换整个delimiters
 * 第一次调用必需入参str, 往后调用则将该参数设置为NULL，因为第一次分割后str被破坏了, 变成了分割后的第一
 * 个字符串, 剩余的字符串保存到了static变量中(所以多线程不安全)
 * 每次调用成功返回指向被分割出的片段的指针
 * https://blogs.csdn.net/hustfoxy/article/details/23473805
 */
char* MyStrtok(char* str, const char* delimeter)
{
    static char* strStatic = NULL; // 保存str分割的后面部分
    const char* pDelimeter = NULL; // 始终指向分隔符的指针
    char* pRetStr = NULL;          // 保存结果
    bool bFind = false;            // 标志是否查找到分隔符
    
    if (str!=NULL)
    {
        strStatic  = str;
    }
    
    if (*strStatic == '\0')
    {
        return NULL;
    }
    pRetStr = strStatic;
    
    while(*strStatic != '\0')
    {
        for(pDelimeter = delimeter; *pDelimeter != '\0'; pDelimeter++)
        {
            if (*pRetStr == *pDelimeter)
            {
                pRetStr++;
                break;
            }
            if (*strStatic == *pDelimeter)
            {
                bFind = true;
                *strStatic = '\0';
            }
        }
        strStatic++;
        
        if (bFind)
        {
            break;
        }
    }
    return pRetStr;
}


/* ---- === --- === --- === --- === --- === --- === --- === --- === -- === --- ===  */
/* ---- === --- === --- === --- = string类成员函数 = --- === --- === -- === --- ===  */
/* ---- === --- === --- === --- === --- === --- === --- === --- === -- === --- ===  */

/*
 * @brief	: 去除string首尾空格
 * @param	: 原字符串
 * @return	: 去除空格后字符串 
 */
string& StringTrim( string &str)
{
    if (str.empty())
    {
        return str;
    }
    str.erase(0, str.find_first_not_of(" "));
    str.erase(str.find_last_not_of(" ") + 1);
    return str;
}

/*
 * @brief       切割字符串
 * @param[in]   strOrig			原始字符串
 * @param[in]   strSplit		分隔符/串
 * @return      vector<string>	返回子串
 */
vector<string> SplitString(string strOrig, string strSplit)
{
    char *pDelim = (char*)strSplit.c_str();
    char *strToken = NULL;
    char *nextToken = NULL;
    string sLine;
    vector <string> vecStringLine;
    vecStringLine.clear();

    strToken = strtok_r((char*)strOrig.c_str(), pDelim, &nextToken);
    while (strToken != NULL)
    {
        sLine.assign(strToken);
		vecStringLine.push_back(sLine);
		strToken = strtok_r(NULL, pDelim, &nextToken);
	}
	return vecStringLine;
}


/*
void email_check2(char * szEmail, const char * szEmailChkRegexp)
{
    if (strlen(szEmail) > 0)
    {
        regex_t reg;
        regmatch_t pmatch[1];
        int cflags = REG_EXTENDED;

        const char* pattern = szEmailChkRegexp;
        const size_t nmatch = 1;
        char * buf = szEmail;
        regcomp(&reg, pattern, cflags);
        if(regexec(&reg, szEmail, nmatch, pmatch, 0))
        {
            printf("Email格式[%s]无效\n", szEmail);
        }
        regfree(&reg);
    }
}
*/


void email_check(char str[])
{

    regex reg("\\w[-\\w.+]*@([a-za-z0-9][-a-za-z0-9]+\\.)+[a-za-z]{2,14}");
    // const char* pattern = "^[a-z0-9A-Z]+([a-z0-9A-Z._-]+)?[a-z0-9A-Z]+@([a-z0-9A-Z])+(-[a-z0-9A-Z]+)?.)+[a-zA-Z]{2,}$";
    // string str1="8701.31615@qq.com";
    smatch r1;
    if (regex_match(str,reg))
    {
        cout << "邮箱格式正确" <<endl;
    }
    else
    {
        cout << "邮箱格式有误" <<endl;
    }
}


/* 
 无符号数陷阱
 http://blog.csdn.net/jiejinquanil/article/details/51789682
 http://blog.csdn.net/songbai_pu/article/details/9172689
 */
void unsigned_test(string str)
{
    // 错误写法:
    if(str.find("xxx") < 0)
    {
        cout << "not found" << endl;
    }
    /* 正确写法: 
     * find 函数找不到指定值的时候，会返回string::npos,表示字符串的结束
     * npos也表示sizt_t的最大值
    if (str.find("xxx") == string::npos)
    {
        cout << "not found till npos" << endl;
    }
     */
    else // err
    {
        cout << "found" << endl;
    }
}


// 打印信息
void debugLog(const char * FileName, int Line, const char * msg, ...)
{
	FILE *fp;
	char ViewStr[4096] = { 0 };
	char bufStr[10240] = { 0 };
	char szOccurTime[32 + 1] = { 0 };

	va_list arg_ptr;
	va_start(arg_ptr, msg);
	vsprintf(ViewStr, msg, arg_ptr); // sprintf(ViewStr, msg, arg_ptr);
	va_end(arg_ptr);

	time_t timep;
	time(&timep);
	strftime(szOccurTime, sizeof(szOccurTime), "%Y-%m-%d %H:%M:%S", localtime(&timep));

	sprintf(bufStr, "[Time:%s][File:%s][Line:%d][%s]\n", szOccurTime, FileName, Line, ViewStr);

	fp = fopen("./debug.log", "a+");
	if (fp == NULL)
	{
		printf("open file error\n");
		return;
	}
	fprintf(fp, "%s\n", bufStr);
	fclose(fp);
	printf("%s", bufStr);
	return;
}


void string_stl()
{
    printf(" \n---------------------- 字符数组初始化 ---------------------------\n");
    /* 
    char str3[10] = {0};     // 元素均为'\0'
    char str4[10] = {'0'};   // 第一个元素为'0'，其他元素均为'\0'
    char str5[10] = {0,};    // 元素均为'\0'
    char str6[10] = {'\0'};  // 元素均为'\0'
    printf("str3[0]:%c,%c",str3[0],str3[1]);
    printf("str4[0]:%c,%c",str4[0],str4[1]);
    printf("str5[0]:%c,%c",str5[0],str5[1]);
    printf("str6[0]:%c,%c",str6[0],str6[1]);
    */
    printf(" \n---------------------- char* 加减 ---------------------------\n");
    // 不就是指针加减嘛

    printf(" \n---------------------- strchr / strrchr / strstr / strcat / strcmp ----------------------\n");
    char ch_str[] = "asdfasdzfasdfaz-=-=-=-=azsdfz-=";
    char ch = 'z';

    char *strchr_res = strchr(ch_str, ch);       // strchr 返回指向第一次出现字符ch的指针
    printf("strchr: %s\n", strchr_res);
    char *strchr_rest = MyStrchr(ch_str, ch);
    printf("MyStrchr: %s\n", strchr_rest);

    char *strrchr_res = strrchr(ch_str, ch);     // strrchr 返回指向最后出现字符ch的指针
    printf("strrchr: %s\n", strrchr_res);
    char *strrchr_rest = MyStrrchr(ch_str, ch);
    printf("MyStrrchr: %s\n", strrchr_rest);

    char *strstr_res = strstr(ch_str, "fz");     // strstr 返回str2中str1第一次出现的位置，返回指针，否则返回 NULL; strrstr返回最后一次出现
    printf("strstr: %s\n", strstr_res);
    char *strstr_rest = MyStrstr(ch_str, "fz");
    printf("Mystrstr: %s\n", strstr_rest);

    char *strcat_res = strcat(ch_str, "+strcat"); // strcat 字符串拼接, dst和src不能有内存重叠; dst必需有足够空间容纳src; 感觉不安全
    printf("strcat: %s\n", strcat_res);
    char *strcat_rest = MyStrcat(ch_str, "-strcat");
    printf("MyStrcat: %s\n", strcat_rest);

    char strsrc[] = "asdfasdzfasdfaz-=-=-=-=azsdfz-="; // strcmp
    char strdst[] = "asdfasdzfasdfaz-=-=-=-=azsdfz-=";
    if (strcmp(strsrc, strdst) != 0)
    {
        printf("不相等");
    }
    else
    {
        printf("相等");
    }
    
    printf(" \n----------------- strlen / strnlen / strcpy / strncpy -----------------\n");
    char sss[] = "aaaaaa";
    cout << "strlen: " << strlen(sss) << endl;
    cout << "strnlen: " << strnlen(sss, 1) << endl;
    cout << "MyStrlen: " << MyStrlen(sss) << endl;

    // const char* p_src = "asdfasdf\0 is a good boy";
    const char* p_src = "asdfasdf is a good boy"; // 用strcpy不安全
    char dest[20], Mydest[20], vardst[22 + 1];

    strcpy(dest, p_src);
    cout << "strcpy: " << dest << endl;
    MyStrcpy(Mydest, p_src);
    cout << "MyStrcpy: " << Mydest << endl;

    strncpy(vardst, p_src, strlen(p_src));
    cout << "strncpy: " << vardst << endl;
    MyStrncpy(vardst, p_src, strlen(p_src));
    cout << "MyStrncpy: " << vardst << endl;


    printf(" \n----------------- memset / memcpy / memmove -----------------\n");
    const char *src = "abcdefghijklmnopqrstuvwxyz";
    int len = strlen(src);
    char dst[64];
    memset((void *)dst, 0x00, sizeof(dst));

    memcpy(&dst, src, len);
    cout << "memcpy:\n\tsrc: " << src << "\t dst: " << dst << endl;
    MyMemcpy(&dst, src, len);
    cout << "MyMemcpy:\n\tsrc: " << src << "\t dst: " << dst << endl;
    MyMemcpyOptimised(&dst, src, len);
    cout << "MyMemcpyOptimised:\n\tsrc: " << src << "\t dst: " << dst << endl;

    printf("\n---===---===---=== strcpy/strcat/memcpy都会有内存重叠的情况 ===---===---===---\n");

    char c1[] = "0123456789";
    MyMemcpy(c1, c1 + 4, sizeof(char) * 5); // 对应flag1: 4567856789
    // MyMemcpy(c1 + 4, c1, sizeof(char) * 5); // 对应flag2
    // memcpy(c1 + 4, c1, sizeof(char) * 5);  // 把MyMemcpy防重叠部分注释掉就可重现了; 这里用memcpy函数无法重现
    // 重现的话应该是 0123012309; 正确的话和memmove一样是: 0123012349
    printf("memcpy 内存重叠: %p\t%p\t%s\n", c1, c1 + 4, c1);

    printf(" \n----------------- 格式化字符串 sprintf / snprintf / vsprintf ---------------------------\n");
    // char sprintf_str[10] = {0};
    // int sprintf_res  = sprintf(sprintf_str, "I'm %d years old!",10);
    // 返回实际写入的字符串长度，不会进行越界判断，会直接对之后的内存进行覆盖
    // printf("sprintf_str:%s\t sprintf_res:%d\n", sprintf_str, sprintf_res); 
    
    char snprintf_str[10] = {0};
    // int snprintf_res = snprintf(snprintf_str, sizeof(snprintf_str), "I'm %d years old!",10);
    // 相比snprintf多个第二个缓存的参数，返回欲写入的长度, 但是只拷贝了n-1个, 就在末尾自动加上'\0'
    int snprintf_res = snprintf(snprintf_str, 20, "I'm %d years old!", 10);
    // int snprintf_res = MySnprintf(snprintf_str, sizeof(snprintf_str), "I'm %d years old!",10);
    printf("snprintf_str:%s\t snprintf_res:%d\n", snprintf_str, snprintf_res);



    printf(" \n----------------- strlen / sizeof  ---------------------------\n");
    /* 
     * https://www.cnblogs.com/carekee/articles/1630789.html
     * strlen 函数，求字符串开始到结束符的长度（字符串以\0结尾）；运行时计算值，参数必须是char * 类型(当数组名作为参数，实际数组是退化成指针了)
     * sizeof 运算符，求类型所占大小；编译时计算值, 参数可以是数组、指针、类型、对象、函数等
    */
    char ch_str2[10] = "Wha\0t?";
    char *a = (char*)"abcdef";  // 字符指针指向常量字符串 // c语言允许直接将字符串赋值给字符指针，但是c++会报警告,这里用类型强转就没事了 
    char b[] = "abcdef";        // 字符数组，以字符串的形式给字符数组赋值,字符串末尾自动添加\0
    char c[] = {'a','b','c','d','e','f'}; // 字符数组，以单个元素的形式赋值,没有\0,strlen返回的值不确定
    printf("strlen(\"Wha\\0t?\"):%Zu\t sizeof(char str2[10]):%Zu\n", strlen(ch_str2), sizeof(ch_str2));
    printf("sizeof(字符指针):%Zu\t strlen(字符指针):%Zu\n", sizeof(a), strlen(a));
    printf("sizeof(字符数组):%Zu\t strlen(字符数组):%Zu\n", sizeof(b), strlen(b));
    printf("sizeof(字符数组):%Zu\t strlen(字符数组):%Zu\n", sizeof(c), strlen(c));



    printf(" \n-------------------------- strtok ---------------------------\n");
    char date[20] = "salfgdfogffhe";
    // char* result = strtok(date, "gd");
    char* result = MyStrtok(date, "gd");
    cout << result << endl; // 第一次分割
    
    while(result != NULL)
    {
        result = MyStrtok(NULL, "gd");
        // result = strtok(NULL, "gd");
        if (result != NULL)
        {
            cout << result << endl;
        }
    }

    printf(" \n--- === --- === --- === --- === --- === --- === --- === --- === -- === --- === ---\n");

    printf(" \n-------------------------- StringTrim ---------------------------\n");
    string strTest = " L0000504cpp ";
    cout << StringTrim(strTest) << endl;

    printf(" \n-------------------------- SplitString ---------------------------\n");
    // vector<string> vecstrResult;
    // char* pBuffer = "asdf1,asdf2,asdf3,asdf4,asdf5"; strtok 用char* 会报错
    // char pBuffer[] = "asdf1,asdf2,asdf3,asdf4,asdf5";
    // vecstrResult = ReadLineToVec(pBuffer);
    vector<string> vecstrResult;
    string strStrtok = "asdf1,asdf2,asdf3,asdf4,asdf5";
    vecstrResult = SplitString(strStrtok, ",");

    for(auto i : vecstrResult)
    {
        cout << i << "\t";
    }
    cout << endl;
}


int main( )
{
    cout << "----------- 正则表达式 -----------" << endl;
    char str_email[] = "fasdf2@aa.com";
    email_check(str_email);

    cout << "----------- string函数 -----------" << endl;
    string_stl();

    cout << "----------- 无符号陷阱 -----------" << endl;
    string str_src = "abcdefghijklmn";
    unsigned_test(str_src);


    unsigned int val = -1; 
    cout << val << endl;

    // debugLog(__FILE__, __LINE__, "TEST");

    return 0;
}
