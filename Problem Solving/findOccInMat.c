#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int R = 2, c = 5;

int  findFromInd(int i,int j,char mat[2][5],int r,int c,char* str)
{
	char *temp = (char*)malloc(strlen(str));
	int l = strlen(str);
	int t1,t2,t3=0,res = 0;
	//left to right
	if (j + l - 1 < c)
	{
		t1 = i;
		while (str[t1] && str[t1] == mat[i][t1])
		{
			t1++;
		}
		if (str[t1] == '\0')
		{
			printf("start: %d %d\tend:%d %d\n",i,j,i,t1-1 );
			res++;
		}
	}
	//top to bot
	if (i + l - 1 < r)
	{
		t2 = i;
		while (str[t2] && str[t2] == mat[t2][j])
		{
			t2++;
		}
		if (str[t2] == '\0')
		{
			printf("start: %d %d\tend:%d %d\n", i, j, t2, j);
			res++;
		}
	}
	//bot to top
	if (i - l >= 0)
	{
		t1 = i;
		t2 = 0;
		while (t1>=0 && str[t2] == mat[i][t1])
		{
			t1--;
			t2++;
		}
		if (t1 == i - l + 1)
		{
			printf("start: %d %d\tend:%d %d\n", i, j, t1, j);
			res++;
		}
	}
	//right to left
	if (j - l +1>= 0)
	{
		t1 = j;
		t2 = 0;
		while (t1 >= 0 && str[t2] == mat[i][t1])
		{
			t1--;
			t2++;
		}
		if (str[t2]=='\0')
		{
			printf("start: %d %d\tend:%d %d\n", i, j, i, t1+1);
			res++;
		}
	}
	//ne diag.
	if (i - l + 1 >= 0 && j + l  <c)
	{
		t1 = i;
		t2 = j;
		t3 = 0;
		while (str[t3]==mat[t1][t2])
		{
			t3++;
			t1--;
			t2++;
		}
		if (str[t3]=='\0')
		{
			printf("start: %d %d\tend:%d %d\n", i, j, t1+1, t2+1);
			res++;
		}
	}
	//nw diag
	if (i - l + 1 >= 0 && j - l + 1 >= 0)
	{
		t1 = i;
		t2 = j; t3 = 0;
		while (str[t3] == mat[t1][t2])
		{
			t3++;
			t1--;
			t2--;
		}
		if (str[t3]=='\0')
		{
			printf("start: %d %d\tend:%d %d\n", i, j, t1+1, t2+1);
			res++;
		}
	}
	//se diag
	if (i + l <= r - 1 && j - l + 1 >= 0)
	{
		t1 = i;
		t2 = j; t3 = 0;
		while (str[t3] == mat[t1][t2])
		{
			t1++;
			t2--;
			t3++;
		}
		if (t1 == i + l && t2 == j - l + 1)
		{
			printf("start: %d %d\tend:%d %d\n", i, j, t1, t2);
			res++;
		}
	}
	//sw diag
	if (i + l <= (r - 1) && j + l - 1 <= c - 1)
	{
		t1 = i;
		t2 = j; t3 = 0;
		while (str[t3] == mat[t1][t2])
		{
			t1++;
			t2++;
			t3++;
		}
		if (t1 == i + l && t2 == j + l)
		{
			printf("start: %d %d\tend:%d %d\n", i, j, t1, t2);
			res++;
		}
	}
	return res;
}

int findOccurences(char mat[2][5],char* str,int r,int c)
{
	int i, j,res=0;
	for (i = 0; i < r; i++)
	{
		for (j = 0; j < c; j++)
		{
			if (mat[i][j] == str[0])
			{
				res+=findFromInd(i,j, mat, r,c,str);
			}
		}
	}
	return res;
}

//int main()
//{
//	int r = 2, c = 5;
//	char mat[2][5] = { { 'h', 'i', 'h', 'i', 'h' }, { 'e', 'e', 'h', 'e', 'e' } };
//	char *str = "hi";
//	printf("%d ",findOccurences(mat, str, r, c));
//	_getch();
//	return 0;
//}