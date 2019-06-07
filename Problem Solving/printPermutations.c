/*#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>

void swap(char ch[],int i,int j)
{
	char temp;
	temp = ch[i];
	ch[i] = ch[j];
	ch[j] = temp;
}

void permutations(char ch[],int s, int l)
{
		if (s == l)
		{
			for (int i = 0; ch[i]; i++)
				printf("%c", ch[i]);
			printf("\n");
		}
		else
		{
			for (int i = s; i <= l; i++)
			{
				swap(ch,i,l);
				permutations(ch, s + 1, l);
				swap(ch,i,l);
			}
		}
}

int main()
{
	char ch[] = "abc";
	permutations(ch,0,2);
	_getch();
}*/