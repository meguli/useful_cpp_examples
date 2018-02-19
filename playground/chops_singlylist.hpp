#ifndef CHOPS_SINGLYLIST_H
#define CHOPS_SINGLYLIST_H

/* 
    This file contains a C-style singly linked list data
    structure. We don't implement deletions for singly linked
    lists because they are O(n). If you need frequent insertions
    and deletions, use doubly linked list. The most important 
    part, maybe, of a singly linked list is structure-sharing
    ie. same node can be the head of many lists. In the case
    where our lists are immutable, this property makes it very
    easy to use with functional languages. cons lists in func.
    languages are mostly singly linked, immutable data
    structures.
    https://www.wikiwand.com/en/Linked_list#/Singly_linked_linear_lists_vs._other_lists
*/

#include <stdlib.h>
#include <stdio.h>

typedef struct node {
    float value;
    struct node *next;
}  node_t ;

typedef struct list {
   node_t *head;
}  list_t ;

list_t* make_list()
{
	// calloc 0 initializes, so lists have a NULL
	// head at creation, and length 0 
	return (list_t *) calloc(1, sizeof(list_t));
}

void destroy_list(list_t *list)
{
	if(list->head == NULL)
		free(list);
	else
	{
		node_t *cur = list->head;
		node_t *following;
		do
		{
			following = cur->next;
			free(cur);
			cur = following;
		}while(following != NULL);
		free(list);
	}
}

// O(1) push front, "the real" singly list inserter
void push_front(list_t *list, float val)
{
	node_t *node = (node_t *) calloc(1, sizeof(node_t));

	node->value = val;
	
	if(list->head == NULL)
		list->head = node;
	else
	{
		node_t *cur = list->head;
        node->next = cur;
        list->head = node;
	}
}

void push_back(list_t *list, float val)
{
	node_t *node = (node_t *) calloc(1, sizeof(node_t));

	node->value = val;
	
	if(list->head == NULL)
		list->head = node;
	else
	{
		node_t *cur = list->head;
		while(cur->next != NULL)
			cur = cur->next;
		cur->next = node;
	}
}

void push_sorted(list_t *list, float val)
{
	node_t *node = (node_t *) calloc(1, sizeof(node_t));

	node->value = val;
	
	if(list->head == NULL) // empty list
		list->head = node;
	else
	{
		node_t *cur = list->head;
		node_t *before = NULL;
		
		while(cur != NULL && cur->value <= val)
		{
			before = cur;
			cur = cur->next;
		}
		if(before == NULL) // if val falls into head
		{
			list->head = node;
			node->next = cur;
		}
		else // if val falls into tail
		{
			node->next = before->next;
			before->next = node;
		}
	}
}

/* 
    Note that car and cdr like this shares the underlying data
    with the callee. This means, we are actually using parts of 
    a persistent data structure. So, deleting this persistent
    thing using the tail pointer would be silly. This scheme 
    makes sense only when we use a persistent data structure
    and a garbage collector at times to reference count.
*/
node_t* car(list_t* list)
{
    return list->head;
}

list_t* cdr(list_t* list)
{
    list_t* tail = (list_t *) calloc(1, sizeof(list_t));
    tail->head = list->head->next;
    return tail;
}

// Some traverse helpers
void double_node(node_t *n)
{
    n->value *= 2;
}

void print_node(node_t *n)
{
    printf("%f ", n->value);
}

node_t* next_node(node_t *cur)
{
	return cur->next;
}

void map_each(list_t *list, void (*func)(node_t*))
{
	node_t *cur = list->head;
    while(cur != NULL)
    {
        func(cur);
        cur = cur->next;
    }
}

void print_list(list_t *list)
{
	map_each(list, print_node);
	printf("\n");
}

#endif