#define _CRT_SECURE_NO_WARNINGS
/*#include<stdio.h>
#include<conio.h>

void sort(int arr[], int size)
{
int fp = 0;
int bp = size - 1;
int temp;
while (fp < bp)
{
if (arr[fp] == 0)
fp++;
if (arr[bp] != 0)
bp--;
if (arr[fp] !=0 && arr[bp] == 0)
{
temp = arr[fp];
arr[fp] = arr[bp];
arr[bp] = temp;
fp++;
bp--;
}
}
int i;
fp = i;
bp = size - 1;
while (fp <= bp)
{
if (arr[fp] == 1)
fp++;
if (arr[bp] == 2)
bp--;
if (arr[fp] == 2 && arr[bp] == 1 && fp <= bp)
{
arr[fp++] = 1;
arr[bp--] = 2;
}
}

}
int main()
{
int arr[] = {1,1,2,2,0,0,0,0,0};
sort(arr, 9);
for (int i = 0; i < 9; i++)
printf("%d ", arr[i]);
_getch();
}*/