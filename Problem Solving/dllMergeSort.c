#include <stdio.h>
#include <stdlib.h>

struct node
{
struct node * next;
struct node * prev;
int val;
};

struct node * insert(struct node * head, int val)
{
if (head == NULL)
{
head = (struct node *)malloc(sizeof(struct node));
head->next = NULL;
head->prev = NULL;
head->val = val;
}
else
{
struct node * temp = (struct node *)malloc(sizeof(struct node));
struct node * t1 = head;
while (t1->next != NULL)
t1 = t1->next;
t1->next = temp;
temp->prev = t1;
temp->next = NULL;
temp->val = val;
}
return head;
}

struct node * merge_two_sorted_dlls(struct node * h1, struct node * h2)
{
struct node * head;
if (h1->val < h2->val)
{
head = h1;
h1 = h1->next;
}
else
{
head = h2;
h2 = h2->next;
}
struct node * temp = head;
while (h1 && h2)
{
if (h1->val < h2->val)
{
temp->next = h1;
temp = h1;
h1 = temp->next;
}
else
{
temp->next = h2;
temp = h2;
h2 = temp->next;
}
}
if (h1 == NULL)
temp->next = h2;
if (h2 == NULL)
temp->next = h1;
return head;
}
struct node * split(struct node * head)
{
struct node * mid, *temp1;
mid = temp1 = head;
while (temp1->next && temp1->next->next)
{
mid = mid->next;
temp1 = temp1->next->next;
}
if (temp1->next)
mid = mid->next;
return mid;

}
void merge_sort(struct node * head)
{
if (!head->next)
return;
struct node * mid = split(head);
mid->prev->next = NULL;
merge_sort(head);
merge_sort(mid);
merge_two_sorted_dlls(head, mid);
}
int main()
{
struct node * head = NULL;
head = insert(head,10);
head = insert(head, 50);
head = insert(head, 70);
head = insert(head, 90);
head = insert(head, 100);
head = insert(head, 20);
head = insert(head, 30);
head = insert(head, 40);
head = insert(head, 60);
head = insert(head, 80);
merge_sort(head);
struct node * t = head;
while (t)
{
printf("%d ", t->val);
t = t->next;
}
_getch();
}