//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//
//struct boundary
//{
//	int i;
//	int j;
//};
//
//void spiral()
//{
//	int a[4][4] = { { 1, 2, 3, 4 }, { 5, 6, 7, 8 }, { 9, 10, 11, 12 }, { 13, 14, 15, 16 } };
//	int i,m=4,n=4;
//	int startRow= 0, startCol = 0;
//	while (startRow < m && startCol < n)
//	{
//		for (i = startCol; i < n; ++i)
//		{
//			printf("%d ", a[startRow][i]);
//		}
//		startRow++;
//		for (i = startRow; i < m; ++i)
//		{
//			printf("%d ", a[i][n - 1]);
//		}
//		n--;
//		if (startRow < m)
//		{
//			for (i = n - 1; i >= startCol; --i)
//			{
//				printf("%d ", a[m - 1][i]);
//			}
//			m--;
//		}
//		if (startCol < n)
//		{
//			for (i = m - 1; i >= startRow; --i)
//			{
//				printf("%d ", a[i][startCol]);
//			}
//			startCol++;
//		}
//	}
//}
//
//int main()
//{
//	spiral();
//	_getch();
//}