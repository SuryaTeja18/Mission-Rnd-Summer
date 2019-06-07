#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

struct node
{
	struct node *next;
	struct node* rand;
	int data;
}*head1 = NULL, *tail1=NULL,*head2=NULL;

void display(struct node* head)
{
	printf("\n");
	struct node* temp = head;
	while (temp)
	{
		printf("%d ", temp->data);
		temp = temp->next;
	}
}

struct node* deepClone(struct node* head)
{
	struct node* temp = head, *dup;
	while (temp)
	{
		dup = (struct node*)malloc(sizeof(struct node));
		dup->data = temp->data;
		dup->next = temp->next;
		temp->next = dup;
		temp = temp->next->next;
	}
	temp = head;
	while (temp)
	{
		temp->next->rand = temp->rand->next;
		temp = temp->next->next;
	}
	temp = head;
	head2 = temp->next;
	dup = head2;
	while (temp->next->next && dup->next)
	{
		temp->next = temp->next->next;
		dup->next = dup->next->next;
		temp = temp->next;
		dup = dup->next;
	}
	return head2;
}

void assignRandom(struct node* head)
{
	struct node* temp = head;
	while (temp)
	{
		if (temp->next)
			temp->rand = temp->next;
		else
			temp->rand = head;
		temp = temp->next;
	}
}

struct node* insertLL(int a[], int size)
{
	struct node * temp1;
	for (int i = 0; i < size; i++)
	{
		temp1 = (struct node*)malloc(sizeof(struct node));

		temp1->data = a[i];
		temp1->next = NULL;

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

void displayRand(struct node*head)
{
	struct node*temp=head;
	while (temp)
	{
		printf("%d ", temp->rand->data);
		temp = temp->next;
	}
}


int main()
{
	int a[] = { 1, 2, 3, 4, 5, 6, 7 };
	int size = 7;
	insertLL(a, size);
	assignRandom(head1);
	printf("Original LL Rands: ");
	displayRand(head1);
	printf("\nDeep Clone LL Rands: ");
	displayRand(deepClone(head1));
	getchar();
}