#include<stdio.h>
#include<conio.h>


void sort1(int arr[], int size)
{
int sum = 0,i;
for (i = 0; i < size; i++)
sum += arr[i];
for (i = 0; i < size-sum; i++)
arr[i] = 0;
while (i < size)
arr[i++] = 1;
}

void sort2(int arr[], int size)
{
int count1 = 0, i;
for (i = 0; i < size; i++)
if (arr[i] == 1)
count1++;
for (i = 0; i < size - count1; i++)
arr[i] = 0;
while (i < size)
arr[i++] = 1;
}

void sort3(int* arr, int size)
{
int fp = 0;
int bp = size - 1;
while (fp < bp)
{
if (arr[fp] == 0)
fp++;
if (arr[bp] == 1)
bp--;
if (arr[fp] == 1 && arr[bp] == 0 && fp < bp)
{
arr[fp++] = 0;
arr[bp--] = 1;
}
}
}
int main()
{
int arr[] = { 0,0,1,1};
//sort1(arr,4);
//sort2(arr,4);
sort3(arr, 4);
for (int i = 0; i < 4; i++)
printf("%d ", arr[i]);
_getch();
}
