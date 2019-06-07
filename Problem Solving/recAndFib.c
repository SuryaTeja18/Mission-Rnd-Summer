//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//
//long fact(int n)
//{
//	if (n == 1)
//		return n;
//	return n*fact(n - 1);
//}
//
//long fib(int n,int a[])
//{
//	int t1, t2;
//	if (n == 1)
//		return 1;
//	if (a[n-1] == 0 && (n-1)!=0)
//	{
//		t1 = fib(n-1,a);
//		a[n-1] = t1;
//	}
//	if (a[n - 2] == 0 && (n-2)!=0)
//	{
//		t2 = fib(n-2, a);
//		a[n - 2] = t2;
//	}
//	else
//	{
//		return a[n - 1] + a[n - 2];
//	}
//}
//
//int main()
//{
//	int n = 50;
//	int* a = (int*)calloc(sizeof(int),n);
//	printf("%d \n%d", fib(n,a), fact(n));
//	_getch();
//	return 0;
//}