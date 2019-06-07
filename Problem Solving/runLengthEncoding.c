#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void getCount(int i, char* str, int* s, int* e)
{
	int k = i;
	*s = i;
	while (str[k] == str[k + 1])
		k++;
	*e = k;
	return;
}

void remove_symbol(char str[])
{
	char *s = (char*)malloc(strlen(str));
	int j = 0,i;
	for (i = 0; str[i]; i++)
		if (str[i] != '-')
			s[j++] = str[i];
	s[j] = '\0';
	for (i = 0; s[i]; i++)
		str[i] = s[i];
	str[i] = '\0';
}

int iToCharArr(int c, char s[])
{
	int i = 9;
	while (c)
	{
		s[i--] = c % 10+'0';
		c /= 10;
	}
	return i;
}


void runLength(char str[])
{
	int i,k,count,s,e;
	char ch[10];
	for (i = 0; str[i]; i++)
	{
		getCount(i,str, &s, &e);
		if (s != e)
		{
			count=e-s+1;
			if (count > 9)
			{
				s++;
				for (k = iToCharArr(count, ch) + 1; k < 10; k++)
				{
					str[s++] = ch[k];
				}
				for (k = s; k <= e; k++)
					str[s++] = '-';
			}
			else
			{
				str[s + 1] = count + '0';
				for (k = s + 2; k<=e; k++)
					str[k] = '-';
			}
		}
		i = e;
	}
	remove_symbol(str);
	return;
}
int main()
{
	char *str = (char*)malloc(1000);
	int n=0;
	char ch = getchar();
	while (ch != '\n')
	{
		str[n++] = ch;
	}
	str[n] = '\0';
	scanf("%[^\n]s", str);
	runLength(str);
	printf("%s", str);
	_getch();
}