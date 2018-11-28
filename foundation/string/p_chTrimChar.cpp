#include <iostream>
#include <assert.h>
#include <string.h>
using namespace std;

const char p_chTrimChar = 0x00;

//滤除字符串首部的空格和制表符（或指定字符

char * __stdcall TrimLeft(char *p_pszString, char p_chTrimChar)
{
	long lIndex = 0L, lStringLen = 0L;

	assert(p_pszString != NULL);

	for (lIndex = 0L;
		p_pszString[lIndex] != 0x00
		&& ((p_chTrimChar == 0x00 && (p_pszString[lIndex] == ' ' || p_pszString[lIndex] == '\t'))
			|| (p_chTrimChar != 0x00 && p_pszString[lIndex] == p_chTrimChar));
		lIndex++)
	{
	}

	if (lIndex > 0L && p_pszString[lIndex] != 0x00)
	{
		lStringLen = (long)strlen(p_pszString + lIndex);
		memcpy((void *)p_pszString, p_pszString + lIndex, lStringLen + 1L);
	}
	else if (p_pszString[lIndex] == 0x00)
	{
		p_pszString[0] = 0x00;
	}

	return p_pszString;
}

int main()
{
	char str[5] = { ' ','a','b','/','c'};
	char(*p)[5] = &str;
	TrimLeft(*p, ' ');
	for (int i = 0; i < 4; i++)
	{
		cout << str[i] << ' ';
	}
	system("pause");
	return 0;
}
