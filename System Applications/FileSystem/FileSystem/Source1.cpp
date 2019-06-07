#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct node
{
	struct node* next;
	int data;
	int un1;
	int un2;
}*head1=NULL,*tail1=NULL;

struct node* insertLL(int a[], int size)
{
		struct node * temp1;
		for (int i = 0; i < size; i++)
		{
			temp1 = (struct node*)malloc(sizeof(struct node));
	
			temp1->data = a[i];
			temp1->next = NULL;
			temp1->un1 = 18;
			temp1->un2 = 19;
			if (head1 == NULL && tail1 == NULL)
			{
				head1 = temp1;
				tail1 = temp1;
			}
			else
			{
				tail1->next = temp1;
				tail1 = temp1;
			}
		}
		return head1;
}

struct node* write(FILE * fp)
{
	struct node* temp=head1;
	struct node temp1;
	if (fp)
	{
		int n = 0x444E524D;
		fwrite(&n, sizeof(n), 1, fp);
		while (temp)
		{
			memcpy(&temp1, temp, sizeof(temp1));
			fwrite(&temp1, sizeof(struct node), 1, fp);
			temp = temp->next;
		}
	}
	else{
		printf("cannot open hdd file");
	}
	return head1;
}


struct node *readLLFromFile(FILE *fileptr) 
{
	struct node temp;
	struct node *nodeptr;
	if (fread(&temp, sizeof(temp), 1, fileptr) == sizeof(temp)) {
		nodeptr = (struct node*)malloc(sizeof(struct node));	
		memcpy(nodeptr, &temp, sizeof(temp));
		printf("%d %d %d\n", temp.data, temp.un1, temp.un2);
		nodeptr->next = readLLFromFile(fileptr);
		return nodeptr;
	}
	else {
		return NULL;
	}
}

int main()
{
	FILE *fp = fopen("hardDisk.hdd", "rb+");
	if (fp)
	{
		int a[] = { 1, 2, 3, 4, 5, 6 };
		int size = 6;
		insertLL(a, size);
		write(fp);
		readLLFromFile(fp);
		fclose(fp);
	}
	else
	{
		printf("no hdd");
	}
	getchar();
}