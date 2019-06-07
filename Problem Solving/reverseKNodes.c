#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

struct node
{
	struct node *next;
	int data;
}*head1=NULL,*tail1 = NULL;

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

int size(struct node* head)
{
	struct node* temp = head;
	int l = 0;
	while (temp)
	{
		temp = temp->next;
		l++;
	}
	return l;
}

struct node* reverse(struct node* head)
{
	if (head->next == NULL)
		return head;
	struct node* temp = reverse(head->next);
	head->next->next = head;
	head->next = NULL;
	return temp;
}

struct node* getPrev(struct node* head)
{
	if (head == head1)
		return NULL;
	struct node* temp = head1;
	while (temp->next != head)
	{
		temp = temp->next;
	}
}

struct node* reverseNextK(struct node* head,int k)
{
	if (head==NULL ||head->next==NULL|| size(head) < k)
		return NULL;
	struct node* resthead,*temp=head,*temp1=head,*prev;
	int i = 1;
	while (i<k)
	{
		temp = temp->next;
		i++;
	}
	resthead = temp->next;
	temp->next = NULL;
	temp1=reverse(head);
	prev = getPrev(head);
	if (prev)
	{
		prev->next = temp1;
	}
	if (head == head1)
	{
		head1 = temp1;
	}
	head->next = resthead;
	return resthead;
}

struct node* reverseKnodes(struct node* head,int k)
{
	if (head->next == NULL || k > size || k<=0)
		return head;
	if (k == 1)
		return head;
	struct node *temp=head,*restHead=head;
	restHead = reverseNextK(temp,k);
	while (restHead)
	{
		restHead = reverseNextK(restHead, k);
	}
	return head1;
}

int main()
{
	int a[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 ,10};
	int size = 10;
	int k = 4;
	display(reverseKnodes(insertLL(a, size),k));
	getchar();
	return 0;
}