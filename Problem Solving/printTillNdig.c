#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

//void print(int n,int t)
//{
//	t++;
//	if ((int)(log10((double)t) + 1) == n)
//		return;
//	printf("%d ", t);
//	print(n,t);
//}

void print(int ch[],int chSize,int st,int l)
{
	for (int i = 0; i < 10; i++)
		ch[st] = i;
	if (st == l)
	{
		for (int i = 0; i < chSize; i++)
			printf("%d ", ch[i]);
	}
	else
	{
		for (int i = 0; i < 10; i++)
		{
			print(ch,chSize,st+1,l);
		}
	}
}

//int main()
//{
//	int t = 0;
//	int n = 4;
//	int* ch = (int*)malloc(sizeof(int)*(n-1));
//	print(ch,(n-1),0,(n-1));
//	_getch();
//	return 0;
//}