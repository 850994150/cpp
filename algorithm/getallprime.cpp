#include<iostream>
#include <string.h>
#include <math.h>
#include <list>
#include<cstring>
using namespace std;

std::string jabberwocky(std::string s)
{
    /* WHITE-RABBIT(2)
     * Let's warm up, MyTask class ought to be initialized with your name and stored
     * to name_, now let's do some magic to encode your name:
     * In a given string, change the position of each neighbour characters, each time
     * the character has been moved, it won't be moved again. If there's no neighbour
     * then just keep it.
     * For example: MuLei -> uMeLi
     */

    // solution1
    /*
    std::string strResult = "";
    s.swap(strResult);
    */
   // HuangJinJie
   // uHnaJgniiJe

    // solution2
    /*
    char tmp = {0};
    int i = 0;
    int len = s.length();
    char* pDate = (char*)s.c_str();
    char* pCur= (char*)s.c_str();

    while(*pCur!= '\0' && i != s.length() -1)
    {
        tmp = *pCur;
        *(pDate + i) = *(pCur+ 1);
        *(pDate + i + 1) = tmp;
        pCur = pDate + i + 2;
        i+=2;
        // *pDate = *(pDate+1);
    }
    // pDate[s.length() + 1] = '\0';
    std::string strResult;
    strResult= pDate;
    */

    // solution3
    int len = s.length();
    char tmp = {0};
    char chTmp[len];
    s.copy(chTmp, len, 0);
    
    for(size_t i = 0; i < len-1; i = i + 2 )
    {
        tmp = chTmp[i];
        chTmp[i] = chTmp[i+1]; 
        chTmp[i+1] = tmp;
    }
    chTmp[len] = '\0';
    std::string strResult;
    strResult = chTmp;
    

    // TODO

    /* When you finish, return your result and go for WHITE-RABBIT(3) */
    // return "You haven't killed Jabberwocky yet";

    return strResult;
}

std::list<uint64_t> get_all_prime_divisors(uint64_t n)
{
    /* WHITE-RABBIT(9)
     * For example:
     * get_all_prime_divisors(45) returns {5, 3} as a list.
     * HINT-1: The order matters, make sure it's sorted from max to min.
     * HINT-2: Don't include 1.
     */

    /* Go for WHITE-RABBIT(10) to implement is_prime(n) then come back.
     * WHITE-RABBIT(11)
     * Finish the rest task
     */

    // TODO
    // #error "Please finish get_all_prime_divisors(n) function"

    int i(0), k(0) ;
    int iTmp[100];
    std::list<uint64_t> uiResult;

	int count=0;
	for(int i=2; i<sqrt(n); i++)
	{ 
         if(n%i!=0)count++; 

        if(count==(int)sqrt(n)-1)//是素数
            cout << "is prime" << endl;
    }

    /*
    for (i = 2; i <= n; i++)
    {
        while(n % i == 0)
        {
            n /= i;
            iTmp[k] = i;
            k++;
        }
    } 
    */
    
    for(int i = 0; i < k; i++)
    {
        uiResult.push_back(iTmp[i]);
    }
    // When you finish, go for WHITE-RABBIT(12)
    // return your_result;
    uiResult.unique();
    uiResult.sort();
    uiResult.reverse();

        auto itor=uiResult.begin();
       while(itor!=uiResult.end())
       {
          std::cout<< *itor++<<std::endl;
       } 

    return uiResult;
}


int main()
{
    long a = 45;
    int k=0;
    int b[100];
    for(int i=2;i<=a;i++)
    {
        while(a%i==0)
        {
            a/=i;
            b[k]=i;
            k++;
        }
    } 
    for(int i=0;i<k;i++)
        cout<<b[i]<<' ';
    
    cout << "----" << endl;
    get_all_prime_divisors(45);
    cout << jabberwocky("HuangJinJie") << endl; // uMeLi
    return 0;
}
