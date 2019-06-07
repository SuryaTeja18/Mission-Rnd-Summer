#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

int steps(int n,int a[])
{
	if (n == 1)
	{
		return 1;
	}
	if (a[n - 1] == 0 && (n - 1) != 0)
	{
		a[n-1]=steps(n - 1, a);
	}
	if (a[n - 2] == 0 && (n - 2) != 0)
	{
		a[n - 2] = steps(n - 2, a);
	}
	else
	return 1 + f(n - 1) + f(n - 2);
}

int main()
{
	int n = 5;
	int *a = (int*)calloc(n, sizeof(int));
	printf("%d ",steps(n, a));
	getch();
	return 0;
}