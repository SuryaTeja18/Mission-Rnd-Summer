//#define _CRT_SECURE_NO_WARNINGS
//#include<stdio.h>
//#include<stdlib.h>
//
//struct node
//{
//	struct node* next;
//	int data;
//}*head=NULL,*tail1=NULL;
//
//struct node* insertLL(int a[], int size)
//{
//	struct node * temp1;
//	for (int i = 0; i < size; i++)
//	{
//		temp1 = (struct node*)malloc(sizeof(struct node));
//
//		temp1->data = a[i];
//		temp1->next = NULL;
//
//		if (head ==NULL && tail1 == NULL)
//		{
//			head = temp1;
//			tail1 = temp1;
//		}
//		else
//		{
//			tail1->next = temp1;
//			tail1 = temp1;
//		}
//	}
//	tail1->next = head->next->next;
//	return head;
//}
//
//
//struct node* loopDetect(struct node* head)
//{
//	int flag = -1;
//	struct node*slow = head, *fast = head,*temp=head;
//	while (slow != NULL && fast != NULL)
//	{
//		slow = slow->next;
//		if (fast->next)
//		{
//			fast = fast->next->next;
//			if (slow == fast)
//			{
//				flag = 1;
//				break;
//			}
//		}
//		else
//		{
//			break;
//		}
//	}
//	if (flag)
//	{
//		while (temp != slow)
//		{
//			temp = temp->next;
//			slow = slow->next;
//		}
//		printf("%d", temp->data);
//		return temp;
//	}
//	else
//	{
//		return NULL;
//	}
//}
//
//int main()
//{
//	int a[] = { 1, 2, 3, 4, 5 };
//	int size = 5;
//	insertLL(a, size);
//	_getch();
//	return 0;
//}