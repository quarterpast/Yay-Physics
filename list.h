#ifndef LIST_H
#define LIST_H

/*
Try to avoid using list nodes directly as this may throw the list out of sync.
The best way to interact with a list is through list iterators and the
corresponding list-centric functions.
*/

typedef struct _ListNode {
	void			 *data;
	struct _ListNode *next;
	struct _ListNode *previous;
} ListNode;

/* Allocates and initialises an empty list node. */
ListNode * newListNode();

/* Frees the list node including the data it points to. */
void freeListNode(ListNode *l);

/* Assumes node is not NULL. */
void insertAfter(ListNode *node, void *data);

/* Assumes node is not NULL. */
void insertBefore(ListNode *node, void *data);

/*
Removes the node from the list by setting pointers appropriately but does not
free anything.
*/
void remove(ListNode *node);

/*
Removes the node from the list, frees the node and returns the nodes
data.
*/
void * takeAtListNode(ListNode *node);

typedef (ListNode *) ListIterator;
typedef struct {
	ListIterator begin;
	ListIterator rend;
} List;

/* Allocates and initialises an empty list. */
List * newList();

/* Frees the list, list nodes and node data. */
void freeList(List *);

/* Returns the number of nodes in the list. */
int listCount(List *l);

/* Asserts if i is an invalid index. Indexing starts from 0. */
ListNode * listNodeAtIndex(List *l, int i);

/*
Asserts if i is an invalid index. Indexing starts from 0. Returns the data
pointer at node i.
*/
void * dataAtIndex(List *l, int i);

/*
Assumes l and it are not NULL. Returns the data at it, removes it from the list
and updates begin and end of l if needed.
*/
void * takeAtListIterator(List *l, ListIterator it);

/*
Asserts if i is an invalid index. Indexing starts from 0. Returns the data
pointer at node i, removes the node and deletes it.
*/
void * takeAtIndex(List *l, int i);

/* Asserts if i is an invalid index. Indexing starts from 0. */
void insertAfterIndex(List *l, int i, void *data);

/* Asserts if i is an invalid index. Indexing starts from 0. */
void insertBeforeIndex(List *l, int i, void *data);

/* Adds a node to the beginning of the list with the given data pointer */
void pushFront(List *l, void *data);

/* Adds a node to the end of the list with the given data pointer */
void pushBack(List *l, void *data);

/*
Removes the first node in the list, deletes it and returns its data pointer.
If the list is empty NULL is returned.
*/
void * popFront(List *l);

/*
Removes the last node in the list, deletes it and returns its data pointer.
If the list is empty NULL is returned.
*/
void * popBack(List *l);

#endif /* LIST_H */
