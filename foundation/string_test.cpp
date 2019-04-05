/*
 **********************************************************
 * Author       : M_Kepler
 * EMail        : m_kepler@foxmail.com
 * Last modified: 2019-01-14 17:44:41
 * Filename     : string_test.cpp
 * Description  :

 * ---- === --- === --- === --- === --- === --- === --- === --- === -- === --- ===
 * 【字符处理函数】
 * https://blog.csdn.net/frecon/article/details/79605941
 * #include <string.h>
 * ---- === --- === --- === --- === --- === --- === --- === --- === -- === --- ===

 * memset  void *memset(void *s, int ch, size_t n);
    * 用来初始化内存, **逐字节拷贝**, 对于单字节数据类型（char）可以初始化为任意支持的值，都没有问题，
    * 但是对于非多字节数据类型只能初始化为0，而不能初始化成别的初值，
    * 因为对所有字节按任意顺序赋值0的结果都是0，而如果初始化为其他的值，就会一个字节一个字节的进行赋值，从而出现奇怪的结果
    * memset中的第三个参数一定要使用sizeof操作符，因为每个系统下对类型长度的定义可能不一样。
    * memset中的第一个参数一定要是一个已知的、已经被分配内存的地址，否则会出错。

 * strlen /strnlen / sizeof
    * https://www.cnblogs.com/carekee/articles/1630789.html
    * strlen 函数，求字符串开始到结束符的长度（字符串以\0结尾）, 运行时计算值，参数必须是char * 类型(当数组名作为参数，实际数组是退化成指针了)
    * sizeof 运算符，求类型所占大小; 编译时计算值, 参数可以是数组、指针、类型、对象、函数等
    *
    * int strlen ( const char *str )
        * 返回字符串的实际长度，不含 '\0'
        * int strnlen ( const char *str, size_t maxlen )
        * 区别: 能防止某些字符串不以'\0'结束而引发的错误
    * sizeof
        * 计算字符数组长度时, 会把\0计算进去

 * 【拷贝】
    * strcpy / strncpy / memcpy / memccpy / memmove / strdup / strndup
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

    *  memcpy / memccpy / memmove
        * 都是拷贝一定长度的内存内容
        * 当内存发生重叠时, memcpy不能保证拷贝的正确性, memmove可以保证

    * strdup / strndup /strdupa / strndupa
        * strdup 可以把src复制给没有初始化的dst, 而strcpy的dst一定是已分配内存的
        * strdup 不是标准C函数(不在stdio.h)里
        * strdup 在堆上申请了strlen(src)+1的内存, 用完需要释放内存
        * strdup 会在末尾加\0, strcpy也会把src的\0拷贝给dst
        * strndup 不需事先分配内存, 所以strndpy的n>strlen(src)时, 返回的行字符串末尾是有\0的; strncpy则不会
        * strdupa/strndupa 和strdupa一样, 只是内存分配是用 alloc 分配在栈上

 * 【比较】
    * strcmp / strncmp / strcasecmp / strncasecmp
    * int strcmp( char *str1, char *str2 )
        * 相等返回0, str1大于str2返回1, str1小于str2返回-1
        * linux下的strcasecmp 区别是: 不区分大小写 (windows下为stricmp)

    * int strncmp( char *str1, char *str2, size_t n )
        * 区别: 只比较前n个
 * 【定位】
    * strchr / strchrnul / strrchr / memchr / memrchr / strstr
        * strchr 如果找到指定字符, 则返回该字符所在地址, 否则返回NULL
        * memchr 区别是memchr针对内存操作不受\0的限制, strchr 针对字符串操作
        * strstr 在字符串中查找子串（不匹配'\0'），如果找到，返回needle第一次出现的位置的指针，如果没找到则返回NULL

    * size_t strspn(const char* key, const char* src); (span: 跨越)
        * 返回key中第一个不在src中的字符的下标, 如果全都在则返回key的长度
    * size_t strcspn(const char* key, const char* src); (complementary: 互补)
        * 返回key中第一个在src中的字符的[下标], 如果全都不在则返回key的长度
    * char *strpbrk(const char *s1, const char *s2);
        * strpbrk: string pointer break. because it returns a pointer to the first of the separator ("break") characters
        * 返回s1中第一个在s2中的字符的[指针] strpbrk("abczz", "deb"); // 返回czz
 * 【变化】
    * strfry (fry:炒)
        * 随机打乱字符串, 因为会改变原串, 所以用char* src = "xx" 会报错

    * strcat / strncat
        * char *strcat(char *dest, const char *src)
            * 将参数src字符拷贝到参数dest所指的字符串尾, 遇到src的\0则停止拷贝, 第一个参数dest要有足够的空间容纳src和末尾的\0; strlen(src)+1
            * strcat 字符串拼接, dst和src不能有内存重叠; dst必需有足够空间容纳src; 感觉不安全
        * char *strncat(char *dest, const char *src, size_t n);
            * 区别: 只拷贝前n个

    * strtok (token: 标记) / strtok_r / strsep (seperate: 分离)
        * char* strtok(char* str, const char* delimiters);
            * 维护一个静态变量(【线程不安全】的原因)来保存第一次传入的str; 后续如果发现传入str是NULL, 就继续处理上次的字符串(保存到静态变量中了);
            * 如果传入的str不为NULL，则知道要处理一个新的字符串, 所以静态变量始终保存着未处理完的字符串的剩下部分
            * 第一次调用入参str, 一次性把【str中包含的delimiters所有字符都替换成'\0'】(多个分割符算一个\0), 往后调用则将该参数设置为NULL, strtok会把NULL 换成\0
            * 因为第一次分割后str被破坏了, 变成了分割后的第一个字符串, 剩余的字符串保存到了static变量中(所以多线程不安全)
            * 每次调用成功【返回指向被分割出的片段的指针】
            * https://blog.csdn.net/hustfoxy/article/details/23473805

        * char *strtok_r(char *str, const char *delim, char **saveptr);
            * 知道了不安全的原因, 只要不使用静态变量就行了; 增加一个参数来指向分割后的字符串, 不同线程使用不同的saveptr指针即可

        * char *strsep(char **stringp, const char *delim);
            * strsep会挨个替换delim的字符，且几个分割字符连续的话(多个分隔符连续算n个\0)他会挨个返回空字符串
            * 第一个参数设为二级指针(所以不能是char str[] = "xx",
            * 但是因为strsep会破坏原串又不能用char*str = "xx") 可以用strdup/strcpy把字符常量拷贝到栈上的变量
            * 字符串中所有的第二个参数（子串）最后会被替代成'\0'

 * ---- === --- === --- === --- === --- === --- === --- === --- === -- === --- ===
 * string 类方法
 * #include <string>
 * ---- === --- === --- === --- === --- === --- === --- === --- === -- === --- ===

    * str.find(str2, "hello")
        * 在str中从指定位置从前向后查找整个子串, 成功返回str2首个字符在str中的地址, 否则返回npos, rfind则从后往前找
    * str.find_first_of(str2, 7) / str.find_first_not_of /  str.find_last_of / str.find_last_not_of
        * 在str中指定位置开始查找str2, 只要str中找到str2的任意字符, 就返回该字符位置
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
#include <ctype.h>
using namespace std;

// http://blog.csdn.net/eager7/article/details/8131437

void debugLog(const char *, int , const char * , ...);


struct stuff
{
    char job[20];
    int age;
    float height;
};


/* ---- === --- === --- === --- === --- === --- === --- === --- === -- === --- ===  */
/* ---- === --- === --- === --- == 字符处理库函数 == --- === --- === -- === --- ===  */
/* ---- === --- === --- === --- === --- === --- === --- === --- === -- === --- ===  */

// snprintf(char*res, sizeof(res), char*formate, ...);
int MyVsnprintf(char *dest, int size, char *formate, ...)
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
    assert((dest != NULL) && (src != NULL));
    while ((*dest++ = *src++) != '\0') ; // 先赋值, 再自增, 然后用dest作为while条件
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
            *cp++ = '\0';
    }
    // len >= sizeof(dst) 会破坏dst后面的内存
    /* error， strlen(dest)就有问题。。。如果要补\0需要在这个函数外补,或者实现把dest初始化为0
    if (offset >= strlen(dest))
    {
        *(cp + len - 1) = '\0';
    }
    */

}

/*
 * @function: strncpy的优化版
 * @brief	: 判断dest和需要拷贝的长度n，如果dest大，则后面补\0，如果n大，则只拷贝dest_len个字符
 * @param	: 
 * @return	: 
 */
char *mystrncpy(char *dest, const char *str, int dest_len, int len)
{
    int n;
    assert((dest != NULL) && (str != NULL));

    char *cp=dest;
    if (dest_len > len)
        n = len;
    if (dest_len <= len)
        n = dest_len; // 只拷贝dest_len个字符

    while ((*cp++ = *str++) != NULL && --n)
        ;
	return dest;
}



// 设置内存位置v开始的n个元素值为c
void *MyMemset(void *v, int c, size_t n)
{
    char*p;
    int m;
    while (--m >= 0)
        *p++ = c;
    return v;
}

void *MyMemcpy1(void *dest, const void *src, size_t n)
{
    char* dp = (char*) dest;
    const char* sp = (const char*) src;
    while((*dp++ = *sp++) && *dp && *sp && --n) ;
    return dest;
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

char* mymemcpy(char* dst, char* src, int n)
{
    // 判断是否存在内存重叠
    // src: [低地址] 1 2 3 4 5 6
    // dst: [低地址]         1 2 3 4 5 6
    bool flag = dst > src && dst <= src + n;
    if (flag)
    {
        // 倒序拷贝
        char *dst_cp = dst + n - 1;
        char *src_cp = src + n - 1;
        while ((*dst_cp-- = *src_cp--) != NULL && --n)
            ;
    }
    else
    {
        while ((*dst++ = *src++) && --n)
            ;
    }
    return dst;
}


/*
 * memcpy的效率优化(只优化, 没有加入内存重叠处理)
 * 原: 逐字节拷贝
 * 现: 按照计算机字长来进行整体拷贝, 不满足字长的才逐一拷贝
 */
void *MemcpyOptimised(void *dest, const void *src, size_t n)
{
    assert(src != NULL);

    int wordnum = n / 4;
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


char *MyStrdup(const char* src)
{
    int len = strlen(src) + 1;

    if (src == NULL)
    {
        return NULL;
    }
    char *newptr = (char *)malloc(len); // 用完后记得 delete
    strcpy(newptr, src);
    return newptr;
}

int MyStrcmp(const char* str1, const char* str2)
{
    if (str1 == NULL || str2 == NULL)
        return -1;
    while ((*str1++ == *str2++) && *str1 && *str2)
    {
        printf("%c\t%c\n", *str1, *str2);
    }
    // 循环结束后, *str1,*str2指向不同的那个字符的下一个字符的位置
    // 所以比较  前  的时候要先回退一位(--str1), 用str--结果是错的
    int result = *(--str1) == *(--str2) ? 0 : (*(--str1) > *(--str2) ? 1 : -1);
}

int MyStrncmp(const char *str1, const char *str2, size_t n)
{
    if (str1 == NULL || str2 == NULL)
        return -1;
    // 这里--n和n--是不一样的
    // 用--n是因为str的下标是到n-1比较到str[5]而不是str[6]
    while ((*str1++ == *str2++) && *str1 && *str2 && --n)
        ;
    // 由于循环退出时指针已指向str1和str2不相同的那个字符了, 所以要先--
    // 相等则返回0, 如果 str1 > str2 则返回1, 否则返回 -1
    return *(--str1) == *(--str2) ? 0 : (*(--str1) > *(--str2) ? 1 : -1);
}

// 实现和 MyStrcmp 一样, 只不过用了 tolower 把字符全转为小写
int MyStrcasecmp(const char* str1, const char* str2)
{
    if (str1 == NULL || str2 == NULL)
        return -1;

    while ((tolower(*str1++) == tolower(*str2++)) && *str1  && *str2)
        ;
    return tolower(*(--str1)) == tolower(*(str2--)) ? 0 : (tolower(*(--str1)) > tolower(*(--str2)) ? 1 : -1);
}


char* MyStrchr(const char* src, char ch)
{
    assert(src != nullptr);
    const char*cp = src;

    while ((*cp++ != ch) && *cp)
        ;
    return (char *)(--cp);
}

char* mystrchr(char* str, char ch)
{
    while ((*str++ != ch) != NULL)
        ;
    return --str; // 返回ch在str的地址, 所以要--
}


void* MyMemchr(const void* src, int chr, size_t n)
{

    while (n && (*(unsigned char *)src != (unsigned char)chr))
    {
        src = (unsigned char *)src + 1;
        n--;
    }
    return (n ? (void *)src : NULL);
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

char* MyStrstr(char* str1, const char* str2)
{
    assert(str1 != NULL);
    assert(str2 != NULL);

    if (*str2 == '\0')
        return str1;

    while(str1)
    {
        const char *cur = str2; // 每次不相等都从第一个字符重新开始
        while ((*str1++ == *cur++) && *str1 && *cur)
            ;
        // 循环退出, 指针指向不相等的字符的下一个字符
        if (*(--cur) == *(--str1))
            return str1 - strlen(str2) + 1;
        str1++;

        if (*str1 == '\0')
            return NULL;

    }
    return NULL;
}

char* MyStrstr2(char* str1, const char* str2)
{
    assert(str1 != NULL);
    assert(str2 != NULL);

    if (*str2 == '\0')
        return str1;

    while(str1)
    {
        const char *cur = str2; // 每次不相等都从第一个字符重新开始
        while (*str1 == *cur)
        {
            str1++;
            cur++;
        };
        if (*cur == '\0')
            return str1 - strlen(str2); // str1指向了第一个不相等的字符上, 回退到str2开头, 返回str2在str1第一个字符位置
        if (*str1 == '\0')
            return NULL;
        str1++;
    }
    return NULL;
}

/*
 * @function: 计算str1中有多少个str2
 * @brief	: 做法和strstr的实现一样, 只不过return的时候改为计数了
 * @param	:
 * @return	:
 */
int MyStrstrCnt(char* str1, const char* str2)
{
    int cnt = 0;
    assert(str1 != NULL);
    assert(str2 != NULL);

    if (*str2 == '\0')
        return 0;

    while(str1)
    {
        const char *cur = str2;
        // while ((*str1++ == *cur++) && *str1 && *cur) ;
        while (*str1 == *cur)
        {
            str1++;
            cur++;
        };
        if (*cur == '\0')
            cnt++;
        if (*str1 == '\0')
            break;
        str1++;
    }
    return cnt;
}

char* MyStrspn()
{

}


char* MyStrcat(char* dst, const char* src)
{
    assert(dst != NULL);
    if (src == NULL)
    {
        return dst;
    }
    int len = strlen(src);
    char * tmp = dst + strlen(dst); // tmp指向dst的\0字符处

    while ((*tmp++ = *src++) != '\0'); // 退出的时已经拷贝\0了, 和strcpy一样
    return dst;
}


// int len = strlen(str);
int MyStrlen(const char*src)
{
    int iLen = 0;
    assert(src != NULL);
    while ((*src++ != '\0') && ++iLen) ;
    return iLen;
}


char* MyStrtok(char* str, const char* delimeter)
{
    static char* strStatic = NULL;
    const char* pDelimeter = NULL; // 始终指向分隔符的指针
    char* pRetStr = NULL;          // 保存结果
    bool bFind = false;            // 标志是否查找到分隔符

    if (str != NULL)
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
 *              strtok会改变原串, 如果入参是char*的话会报错
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

// ------------------------------------------------------------ 字符翻转 ------------------------------------------------------------ 

/*
 * @function: 交换相邻字符
 * @brief	: HuangJinJie ---> uHnaJgniiJe
 * @param	: 
 * @return	: 
 */
void SwapNeighbourCharacters(string str_swap)
{
    int i = 0;
    char tmp = {0};
    char *pData = (char *)str_swap.c_str();
    char *pCur = (char *)str_swap.c_str();

    // 1.
    while (*pCur != '\0' && i != str_swap.length() - 1)
    {
        tmp = *pCur;
        *(pData + i) = *(pCur + 1);
        *(pData + i + 1) = tmp;
        pCur = pData + i + 2;
        i += 2;
    }
    std::string strResult;
    strResult = pData;
    printf("%s\n", (char *)strResult.c_str());

    int len = str_swap.length();
    char chTmp[len];
    str_swap.copy(chTmp, len, 0); // string装char数组

    // 2.
    for (size_t i = 0; i < len - 1; i = i + 2)
    {
        tmp = chTmp[i];
        chTmp[i] = chTmp[i + 1];
        chTmp[i + 1] = tmp;
    }
    chTmp[len] = '\0';
    strResult = chTmp;

    printf("%s\n", (char *)strResult.c_str());
}

/*
 * @function: 反转字符串
 * @brief	: hello --> olleh
 *            直接从两头往中间走，同时交换两边的字符即可
 * @param	:

 * @return	: 
 */
string reverseString(string s)
{
    int left = 0, right = s.size() - 1;
    while (left < right)
    {
        // swap(s[left++], s[right--]);
        char t = s[left];
        s[left++] = s[right];
        s[right--] = t;
    }
    return s;
}

/*
 * @function: 字符串翻转
 * @brief	: 方法和上面的一样
 *            huang jin jie --> eij nij gnauh
 * @param	: left起始点指针, right终点指针(msg + strlen(msg) -1)
 * @return	: 
 */
void reverseChar(char *left, char *right)
{
    assert(left != NULL && right != NULL);
    while (left < right)
    {
        *left = *left + *right;
        *right = *left - *right;
        *left = *left - *right;

        // *left ^= *right; // a = a + b; a = 1 + 2;
        // *right ^= *left; // b = a - b; b = 3 - 2;
        // *left ^= *right; // a = a - b; a = 3 - 1;
        left++, right--;
    }
}

/*
 * @function: 翻转单词
 * @brief	: 基于反转字符串, 先把整个字符串翻转, 然后再按照空格把一个个单词翻转(注意最后一个单词的后一位是\0)
 *            huang jin jie --> eij nij gnauh --> jie jin huang
 *            left始终记录翻转的起点, right始终记录翻转的终点(注意不算空格)
 * @param	: 
 * @return	: 
 */
void reverseWord(char *msg)
{
    int len = strlen(msg) - 1;
    reverseChar(msg, msg + len);
    int left = 0;
    int right = 0;
    char *cur = msg;
    // while (*cur != '\0')
    while (right <= strlen(msg))
    {
        if (*cur == ' ' || *cur == '\0')
        {
            reverseChar(msg + left, msg + right - 1); // -1 空格
            left = right + 1; // +1 指向空格后一个字符
        }
        right++;
        cur++;
    }
}

/*
 * @function: 左旋字符串
 * @brief	: 拿出首个字符h, 从前往后依次与后面的每个字符交换, 即可完成一次左旋
 *            huangjinjie --> uangjinjieh
 * @param	: 左旋，k为指定的左旋字符的个数
 * @return	: 
 */
void LRevolve_Words(char *Pword, int  k, int len)
{
	int i = len;                                         
	char temp;
    char *curr = Pword + 1;
    while (k--)
	{
		for ( i = 0; i < len - 1 ; i++)
        {
            // 首字符依次与后面的字符依次交换
            temp = *(Pword + i);
			*(Pword + i) = *(Pword + i + 1);
			*(Pword + i + 1) = temp;
		}
	}
}

/*
 * @function: 左旋字符串
 * @brief	: 先反转前cnt个字符, 然后再反转后len - cnt个字符, 最后再反转整个字符串
 *            huangjinjie --> auhngjinjie --> auheijnijgn --> ngjinjiehua
 * @param	: 
 * @return	: 
 */
void LReverStr(char* str, int cnt, int len)
{
    reverseChar(str, str + cnt - 1);
    reverseChar(str + cnt, str + len - 1);
    reverseChar(str, str + len - 1);
}

/*
 * @function: 右旋字符串
 * @brief	: 和左旋思路相反, 用最后的字符从后往前依次交换
 * @param	: 
 * @return	: 
 */
void RRevolve_Words(char *Pword, int  k, int len)
{
	int i = len;
	char temp;
	while (k--)
	{
		for ( i = len ; i > 1 ; i--) // 从后往前
		{
			temp = *(Pword + i - 1);
			*(Pword + i - 1) = *(Pword +  i - 2);
			*(Pword + i - 2) = temp;
		}
	}
}


/*
 * @function: 右旋字符串
 * @brief	: 先翻转后cnt个字符, 再翻转前len - cnt个字符, 最后整个字符串翻转
 *            huangjinjie --> huangjineij --> nijgnauheij --> jiehuangjin
 * @param	: 
 * @return	: 
 */

void RReverStr(char* str, int cnt, int len)
{
    // str + len - cnt  为倒数第k个字符
    reverseChar(str + len - cnt, str + len - 1);
    reverseChar(str, str + len - cnt - 1);
    reverseChar(str, str + len - 1);
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


void cString()
{
    printf(" \n---------------------- 字符数组初始化 ---------------------------\n");
    char str_ini1[] = "helloworld"; // 输出为helloworld
    char str_ini2[2] = {"a"}; // 输出为a
    // char str_ini3[2] = {"ab"}; // error, const char[3]类型不能用于初始化char[2]类型的实体, 因为字符串末尾会有一个'\0'结束符
    // char str_ini4[2] = {"a", "b"}; // error, 初始值设定项太对, 因为是一维数组, 只能赋值一个字符串, 字符串末尾会默认加上'\0'结束符

    // char str_ini5[2][3] = {{'a', 'b'}, {'e', 'd'}, {'e', 'f'}}; // error, 维度错误
    char str_ini6[2] = {'a', 'b'}; // 不能直接输出str_ini6, 因为字符串没有结尾, 这种方式赋值编译器不会加上'\0'
    char str_ini7[2] = {'a', '\0'}; // 输出为a
    // char str_ini8[] = {"a", "b"}; // error, 初始项设定太多, 这是一个以为数组, 只能放下一个字符串


    char str3[10] = {0};     // 元素均为'\0'
    char str4[10] = {'0'};   // 第一个元素为'0'，其他元素均为'\0'
    char str5[10] = {0,};    // 元素均为'\0'
    char str6[10] = {'\0'};  // 元素均为'\0'
    printf("str3[0]:%c,%c",str3[0],str3[1]);
    printf("str4[0]:%c,%c",str4[0],str4[1]);
    printf("str5[0]:%c,%c",str5[0],str5[1]);
    printf("str6[0]:%c,%c\n",str6[0],str6[1]);

    char octal[] = "123\0456"; // \0为字符串结束符, 但是\ddd中ddd是小于8, 则\ddd是一个8进制数
    cout << "octal & char: " << octal << endl;
    int octal_int = 010; // 0开头的是8进制 用%d(十进制输出)输出是8; 用%o(八进制输出):10
    printf("octal_int: %d", octal_int++);

    printf(" \n---------------------- char* 加减 ---------------------------\n");
    // 不就是指针加减嘛

    printf("\n---------------------- =========================================== ----------------------\n");
    printf("---------------------- strchr / strrchr / strstr / strspn / strpbrk / strcat / strcmp ----------------------\n");
    printf("---------------------- =========================================== ----------------------\n\n");
    char strchr_ch[] = "asdfasdzfasdfazazsdfz== ";
    char ch = 'z';

    char *strchr_res = strchr(strchr_ch, ch); // strchr 返回指向第一次出现字符ch的指针
    printf("strchr: %s\n", strchr_res);
    char *strchr_rest = MyStrchr(strchr_ch, ch);
    printf("MyStrchr: %s\n", strchr_rest);

    char *strrchr_res = strrchr(strchr_ch , ch);     // strrchr 返回指向最后出现字符ch的指针
    printf("strrchr: %s\n", strrchr_res);
    char *strrchr_rest = MyStrrchr(strchr_ch, ch);
    printf("MyStrrchr: %s\n", strrchr_rest);

    char *strstr_res = strstr(strchr_ch, "as");     // strstr 返回str2中str1第一次出现的位置，返回指针，否则返回 NULL; strrstr返回最后一次出现
    printf("strstr: %s\n", strstr_res);

    printf("orig    : %s\n", strchr_ch);
    char *strstr_rest = MyStrstr(strchr_ch, "df");
    printf("Mystrstr: %s\n", strstr_rest);
    printf("MystrstrCnt: %d\n", MyStrstrCnt(strchr_ch, "as"));

    char strfry_str[] = "huangjinjie";
    printf("strfry: %s\n", strfry(strfry_str));

    char *strspn_key = (char *)"xxhuangyyyyjinjie";
    char *strspn_source = (char *)"huang0jinjie";
    cout << "strspn: " << strspn(strspn_key, strspn_source) << endl;
    cout << "strpbrk: " << strpbrk(strspn_key, strspn_source) << endl;
    cout << "strcspn: " << strcspn(strspn_key, strspn_source) << endl;


    char *strcat_res = strcat(strchr_ch, "+strcat");
    printf("strcat: %s\n", strcat_res);
    char *strcat_rest = MyStrcat(strchr_ch, "-strcat");
    printf("MyStrcat: %s\n", strcat_rest);

    char strcmp1[] = "asdfasd=";
    char strcmp2[] = "asdfasd=";
    char strcasecmp1[] = "asdf=Aesd";
    char strcasecmp2[] = "asdf=ADsd";
    // if (strcmp(strcmp1, strcmp2) != 0)
    if (MyStrcmp(strcmp1, strcmp2) != 0)
    // if (strncmp(strcmp1, strcmp2, 6) != 0)
    // if (MyStrncmp(strcmp1, strcmp2, 6) != 0)
    // if (strcasecmp(strcasecmp1, strcasecmp2) != 0)
    // if (MyStrcasecmp(strcasecmp1, strcasecmp2) != 0)
        printf("不相等");
    else
        printf("相等");

    printf("\n----------------- =============== ---------------------------\n");
    printf("----------------- strlen / sizeof ---------------------------\n");
    printf("----------------- =============== ---------------------------\n\n");
    // strlen计算直到第一个\0的长度, sizeof 计算的是占用内存的大小

    char str[20] = "0123456789";
    cout << strlen(str) << endl;
    cout << sizeof(str) << endl;

    char strlen_str[] = "aaaaaa";
    cout << "strlen: " << strlen(strlen_str) << endl;
    cout << "sizeof: " << sizeof(strlen_str) << endl;
    cout << "strnlen: " << strnlen(strlen_str, 3) << endl;
    cout << "MyStrlen: " << MyStrlen(strlen_str) << endl;

    char ch_str2[10] = "Wha\0t?";
    printf("strlen(\"Wha\\0t?\"):%Zu\t sizeof(char str2[10]):%Zu\n", strlen(ch_str2), sizeof(ch_str2));

    char *a = (char *)"abcdef";                // 字符指针, sizeof大小为8(本机64位)
    char b[] = "abcdef";                       // 字符数组，以字符串的形式给字符数组赋值, 字符串末尾自动添加\0; 所以sizeof为 6 + 1, strlen为6
    char c[] = {'a', 'b', 'c', 'd', 'e', 'f'}; // 字符数组，以单个元素的形式赋值,没有\0, strlen会一直往后直到找到一个\0为止, 大小不确定

    printf("\nchar *a = (char*)\"abcdef\";\tsizeof:%Zu\t strlen:%Zu\n", sizeof(a), strlen(a));
    printf("char b[] = \"abcdef\";\tsizeof:%Zu\t strlen:%Zu\n", sizeof(b), strlen(b));
    printf("char c[] = {'a', 'b', 'c', 'd', 'e', 'f'};\tsizeof:%Zu\t strlen:%Zu\n\n", sizeof(c), strlen(c));



    printf("\n----------------- ======================================================== -----------------\n");
    printf("----------------- strcpy / strncpy / mmecpy / memccpy / memset / / memmove -----------------\n");
    printf("----------------- ======================================================== -----------------\n\n");

    // const char* p_src = "asdfasdf\0 is a good boy";
    const char* p_src = "huangjinjie is a good boy"; // 用strcpy不安全
    char dest[20], Mydest[20], vardst[22 + 1];

    strcpy(dest, p_src);
    cout << "strcpy: " << dest << endl;
    MyStrcpy(Mydest, p_src);
    cout << "MyStrcpy: " << Mydest << endl;

    strncpy(vardst, p_src, strlen(p_src));
    cout << "strncpy: " << vardst << endl;
    MyStrncpy(vardst, p_src, strlen(p_src));
    cout << "MyStrncpy: " << vardst << endl;


    const char *src = "abcdefghijklmnopqrstuvwxyz";
    int len = strlen(src);
    char dst[64];
    memset((void *)dst, 0x00, sizeof(dst)); // 因为是逐字节拷贝, 所以初始化为非0的值时会得到奇怪结果

    char *memset_pBuf = (char *)malloc(sizeof(char) * 10);
    memset(memset_pBuf, 0, sizeof(char) * 10); // 0或者'\0'是等价的
    // MyMemset((void *)memset_str, '1', sizeof(memset_str));
    printf("%s, strlen: %Zu, sizeof:%Zu\n", memset_pBuf, strlen(memset_pBuf), sizeof(memset_pBuf));

    memcpy(&dst, src, len);
    cout << "memcpy:\n\tsrc: " << src << "\t dst: " << dst << endl;
    // MyMemcpy1(&dst, src, len);
    MyMemcpy(&dst, src, len);
    cout << "MyMemcpy:\n\tsrc: " << src << "\t dst: " << dst << endl;
    MemcpyOptimised(&dst, src, len);
    cout << "MemcpyOptimised:\n\tsrc: " << src << "\t dst: " << dst << endl;


    printf("\n===---=== strcpy/strcat/memcpy都会有内存重叠的情况 ===---===\n");

    char c1[] = "0123456789";
    MyMemcpy(c1, c1 + 4, sizeof(char) * 5); // 对应flag1: 4567856789
    // MyMemcpy(c1 + 4, c1, sizeof(char) * 5); // 对应flag2
    // memcpy(c1 + 4, c1, sizeof(char) * 5);  // 把MyMemcpy防重叠部分注释掉就可重现了; 这里用memcpy函数无法重现
    // 重现的话应该是 0123012309; 正确的话和memmove一样是: 0123012349
    printf("memcpy 内存重叠: %p\t%p\t%s\n", c1, c1 + 4, c1);

    char c2[] = "abcdefghijklmn";
    char *c22 = strdup(c2);
    // char * c22 = MyStrdup(c2);
    // char *c22 = strndup(c2, strlen(c2) + 1);
    printf("strdup:%s\n", c22);
    free(c22);
    c22 = NULL;
    printf("strdup:%s\n", c22);


    printf("\n------------------- ========================================== ---------------------------\n");
    printf("------------------- 格式化字符串 sprintf / snprintf / vsprintf ---------------------------\n");
    printf("------------------- ========================================== ---------------------------\n\n");
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


    printf("\n------------------- ==== ---------------------------\n");
    printf("------------------- 其他 ---------------------------\n");
    printf("------------------- ==== ---------------------------\n\n");
    // 字符常量不可更改 // 如果想要修改应: char p[] = "qwertyuiop"; // 全局变量被拷贝到栈上的数组p
    char *p = (char *)"qwertyuiop";
    // p[3] = 'b'; // error
    // *p = 'b'; // error
    // (*p)++; // error
    // *p++; // success
    // p = "edf"; // success
    while (*p)
    {
        printf("%c ", *p);
        p++;
    }

    printf("\n\n-------------------------- =============== ---------------------------\n");
    printf("-------------------------- strtok / strsep ---------------------------\n");
    printf("-------------------------- =============== ---------------------------\n");
    char date[64] = "home/m_kepler/project:/home/m_kepler:/home/git:"; // 字符串不能为常量，所以strdup
    // char *date = "salfgdfogffhe"; // error
    char* token;
    char delim[] = ":/";

    /*
    token = MyStrtok(date, ":/");
    while(token != NULL)
    {
        token = MyStrtok(NULL, ":/");
        // token = strtok(NULL, "gd");
        if (token != NULL)
            printf("%s", token);
    }
    cout << endl;
    */

    for (token = strtok(date, delim); token != NULL; token = strtok(NULL, delim))
    {
        printf("%s", token);
		printf("+");
    }
    cout << endl;

    // strsep
    char *orgstr = strdup("home/m_kepler/project:/home/m_kepler:/home/git:"); // 字符串不能为常量，所以strdup
    // char orgstr[] = "In the galaxy far far away."; // 这是字符数组, 不是指针
    /*
    char *seps = NULL;
    while ((seps = strsep(&orgstr, ":/")) != NULL)
    {
        printf("%s+", seps);
    }
    free(orgstr);
    cout << endl;
    */

    for (token = strsep(&orgstr, delim); token != NULL; token = strsep(&orgstr, delim))
    {
        printf("%s", token);
        printf("+");
    }
    free(orgstr);
    cout << endl;


    vector<string> vecstrResult;
    char *pBuffer = (char *)"asdf1,asdf2,asdf3,asdf4,asdf5";
    // char pBuffer[] = "asdf1,asdf2,asdf3,asdf4,asdf5";
    string strStrtok = "asdf1,asdf2,asdf3,asdf4,asdf5";
    vecstrResult = SplitString(pBuffer, ",");

    for(auto i : vecstrResult)
    {
        cout << i << " ";
    }
    cout << endl;
}



/*
 * @brief	从行中查找key("="号左边)对应的value("="号右边)值; 非限定'='符,也可以是":"
 * @param	strOrig			待分割的字符串
 * @param	strKey			待查找的key
 * @param	strSplit		截取符(从key开始出现的第一个strSplit)
 * @return	strRetValue		查找成功返回value,查找失败返回空字符串;
							若从key到结束都没找到str_split,则返回key开始到字符串结束
 */
string GetMsgValue(string strOrig, string strKey, string strSplit = ",")
{
	int iStrOrigLen;
	int iStrKeyLen;
	size_t uiPosKeyBegin;
	size_t uiPosKeyEnd;
	size_t uiPosStrSplit;
	string strRetValue = "";

	iStrOrigLen = strOrig.length();
	iStrKeyLen = strKey.length();
	uiPosKeyBegin = strOrig.find(strKey);

	if (uiPosKeyBegin != string::npos)
	{
		// 从key的位置开始,第一次出现 str_split 的位置
		uiPosStrSplit =  strOrig.substr(uiPosKeyBegin).find(strSplit);
		if (uiPosStrSplit != string::npos)
		{
			uiPosKeyEnd = uiPosKeyBegin + uiPosStrSplit;
		}
		else
		{
			uiPosKeyEnd = iStrOrigLen;
		}
		int pos_begin = uiPosKeyBegin + iStrKeyLen + 1; // +1 跳过'='字符
		int value_len = uiPosKeyEnd - pos_begin;
		strRetValue = strOrig.substr(pos_begin, value_len);
		return strRetValue;
	}
	return strRetValue;
}

void cppString()
{
    string strReq = "20180202-091346-640257 18226    99 Req: LBM:L0301042,MsgId=0000000100F464531E4D4B4A,Len=283,Buf=_ENDIAN=0&F_OP_USER=9999&F_OP_ROLE=2&F_SESSION=0123456789&F_OP_SITE=0050569e247d&F_OP_BRANCH=999&F_CHANNEL=0&USE_NODE_FUNC=106127&CUST_CODE=150165853";
    string str = " L0000504cpp ";
    string str2(3,'a'); // 相当于 str3 = "aaa";
    char chs[20];
    str.copy(chs, str.size());
    cout << "copy: [" << chs << "] sizeof:" << sizeof(chs) << " strlen:" << strlen(chs) << endl;

    cout << str.at(1) << endl; // 类似数组下标, 越界报错
    cout << str[20] << endl; // 类似数组下标, 越界不报错

    // size和length是一样的, size是为了和其他容器保持一致, 都是返回字符串长度;
    // capacity(容量)返回该string对象已分配大小即string中不必增加内存即可存放的元素个数, max_size 返回string对象可容纳的最大字符串长度
    printf("size: %Zu, length: %Zu\nmax_size: %Zu, capacity: %Zu\n", str.size(), str.length(), str.max_size(), str.capacity());

    cout << "GetMsgValue: " << GetMsgValue(str, "LBM") << endl;
    cout << "StringTrim: " << StringTrim(str2) << endl;

    printf("\n-------------------------- ========= ---------------------------\n");
    printf("-------------------------- std::npos ---------------------------\n");
    printf("-------------------------- ========= ---------------------------\n\n");
    /* 无符号数陷阱
     http://blog.csdn.net/jiejinquanil/article/details/51789682
     http://blog.csdn.net/songbai_pu/article/details/9172689
     */
    // 错误写法:
    string str_npos = "abcdefghijklmn";
    if (str_npos.find("xxx") < 0)
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
    cout << str_npos.find("xxx") << endl;
    unsigned int val = -1;
    cout << val << endl;
}

// 柔性数组
// 变长结构体
typedef struct FlexiableStruct
{
    int a;
    char array[0]; //或char array[]; // 定义0长数组, 只是把一个符号放在结构体内, 不占用内存
}stFlexiable, *pstFlexiable;

void FlexiableArray()
{
    char szStr[] = "hellohuangjinjie";
    printf("sizeof struct: %Zu\n", sizeof(stFlexiable));

    pstFlexiable p_stFlexiable;
    p_stFlexiable = (pstFlexiable)malloc(sizeof(stFlexiable) + strlen(szStr) + 1);

    // 动态申请的内存只是申请给数组拓展所用，结构体的大小在创建时已经确定了
    // array明确来说不算是结构体成员，只是挂羊头卖狗肉而已
    printf("sizeof struct after malloc: %Zu\n", sizeof(stFlexiable));

    strcpy(p_stFlexiable->array, szStr);
    p_stFlexiable->a = 10;

    printf("struct.a:[%d]\nstruct.str:[%s]\n", p_stFlexiable->a, p_stFlexiable->array); // 为什么用cout不行?

}

/*
由于union只存储一个成员，若一个union有一个int变量和一个char变量，那么若前一个int变量被赋值后
此时union存储的就是该int变量;若此时读取char变量，由于char并没有被重写，所以读取的还是int变量的前8位

根据读取的的8位字节判断是否=int的值, 如果相等，则证明int的值保存在低地址
[低地址->] 00001111 00000000 00000000 00000000[高地址]
[高地址->] 00000000 00000000 00000000 00001111[低地址]
(高位) 0x12345678 (地位)
[低地址]: 12 34 56 78 (大端)
[低地址]: 78 56 34 12 (小端)
*/
bool IsLittleEndian()
{
    union {
        int a;
		char b;
    } u;

    int k = 15; //要在char范围内
    u.a = k;
    if ((int)u.b == k)
    {
        return true;
    }
    else
    {
        return false;
    }
}




int main( )
{
    char str_email[] = "fasdf2@aa.com";
    email_check(str_email);

    printf("\n\n-------------------------- ================== ---------------------------\n");
    printf("-------------------------- #inclde <string.h> ---------------------------\n");
    printf("-------------------------- ================== ---------------------------\n\n");

    cString();

    printf("\n\n-------------------------- ================ ---------------------------\n");
    printf("-------------------------- #inclde <string> ---------------------------\n");
    printf("-------------------------- ================ ---------------------------\n\n");

    cppString();


    printf("\n\n-------------------------- ================ ---------------------------\n");
    printf("-------------------------- 其他 ---------------------------\n");
    printf("-------------------------- ================ ---------------------------\n\n");
    printf("柔性数组: n");
    FlexiableArray();

    printf("大小端判断:\n");
    if (IsLittleEndian())
    {
        printf("小端\n");
    }
    else
    {
        printf("大端\n");
    }
    printf("\n\n-------------------------- ================ ---------------------------\n");
    printf("-------------------------- 字符翻转  ---------------------------\n");
    printf("-------------------------- ================ ---------------------------\n\n");

    printf("交换字符:\n");
    SwapNeighbourCharacters("HuangJinJie");

    // debugLog(__FILE__, __LINE__, "TEST");
    printf("反转字符串:\n");
    string res = reverseString("HuangJinJie");
    printf("%s\n", res.c_str());

    printf("翻转字符串\n");
    char rever[] = "huang jin jie";
    reverseChar(rever, rever+ strlen(rever) - 1);
    printf("%s\n", rever);

    printf("倒序单词\n");
    char word[] = "huang jin jie";
    reverseWord(word);
    printf("%s\n", word);

    printf("左旋3个字符\n");
    char lrwords[] = "huangjinjie";
    // LRevolve_Words(lrwords, 3, strlen(lrwords));
    LReverStr(lrwords, 3, strlen(lrwords));
    printf("%s\n", lrwords);

    printf("右旋3个字符\n");
    char rrwords[] = "huangjinjie";
    // RRevolve_Words(rrwords, 3, strlen(rrwords));
    RReverStr(rrwords, 3, strlen(lrwords));
    printf("%s\n", rrwords);

    return 0;
}
