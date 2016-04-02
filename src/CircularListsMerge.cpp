/*
Given two SORTED Circular Linked Lists ,
Write a function to merge those two linked lists .
The First Linked List head should point to the final merged linked list .
The Final merged linked list should also be in SORTED order and a Circular Linked List.
You need to return the Length of Final SLL.

*********
The First linked list head should now point to the Final sorted(Ascending) Linked list First Node
*********
Ex : A: 0->3->5->10->20 (and 20 now pointing back to 0,instead of Null )
B: 1->2->6->11->21->50->70 (70 Pointing back to 1).

The Final Linked List is A:0->1->2->3->5->6->10->11->20->21->50->70 .

Note : Dont use Malloc or create any new nodes ,Only pointers need to be interchanged,
You can use temp pointers although.
Note : The Final Linked List should be  also be a circular Linked List where Last node is
pointing towards the first node.
Note : Return -1 for Invalid Inputs like NULL;

Input : head1 and head2 are Addresses of Two Circular Linked Lists heads .
Output :Return Length of New SLL .Modify the head1 value, such that it now points to 
Merged Sorted Circular SLL .

Difficulty : Medium
*/
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

struct node{
	int data;
	struct node *next;
};
void MoveNode(struct node** dest, struct node** source)
{
	struct node* newNode = *source;
	assert(newNode != NULL);
	*source = newNode->next;
	newNode->next = *dest;
	*dest = newNode;
}

struct node* SortedMerge(struct node** a, struct node** b)
{
	struct node * x = *a;
	struct node * y = *b;
	struct node temp;

	struct node* tail = &temp;
	temp.next = NULL;
	while (1)
	{
		if (x == NULL)
		{

			tail->next = y;
			break;
		}
		else if (y == NULL)
		{
			tail->next = x;
			break;
		}
		if (x->data <= y->data)
			MoveNode(&(tail->next), &x);
		else
			MoveNode(&(tail->next), &y);

		tail = tail->next;
	}
	return(temp.next);
}


int tocircular(struct node **p)
{
	struct node *rear;
	int count = 0;
	rear = *p;
	while (rear->next != NULL)
	{
		count++;
		rear = rear->next;
	}
	rear->next = *p;
	/*After this the singly linked list is now circular*/
	return count+1;
}
void tosinglyLinkedList(struct node *p)
{
	struct node *rear;

	rear = p;
	while (rear->next != p)
	{
		rear = rear->next;
	}
	rear->next = NULL;
}
int merge_circularlists(struct node **head1, struct node **head2)
{
	if (*head1 == NULL && *head2 == NULL)
		return -1;
	else if (*head1 == NULL)
		return -1;
	else if (*head2 == NULL)
		return -1;
	int len = 0;
	tosinglyLinkedList(*head1);
	tosinglyLinkedList(*head2);
	*head1 = SortedMerge(head1, head2);
	len = tocircular(head1);
	return len;
	//Returns Length of merged Sorted circular SLL and also points *head1 to final SLL .
}