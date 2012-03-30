#include "list.h"

#include <stdlib.h>
#include <assert.h>

ListNode * newListNode() {
	ListNode *ret = (ListNode *)malloc(sizeof(ListNode));
	ret->data = NULL;
	ret->next = NULL;
	ret->previous = NULL;
	return ret;
}

void freeListNode(ListNode *node) {
	if (node->data != NULL)
		free(node->data);
	free(node);
}

void insertAfter(ListNode *node, void *data) {
	ListNode *nextNode = makeNode();
	nextNode->data = data;
	nextNode->next = node->next;
	nextNode->previous = node;
	node->next = nextNode;
	if (nextNode->next != NULL)
		nextNode->next->previous = nextNode;
}

void insertBefore(ListNode *node, void *data) {
	ListNode *previousNode = makeNode();
	previousNode->data = data;
	previousNode->previous = node->previous;
	previousNode->next = node;
	node->previous = previousNode;
	if (previousNode->previous != NULL)
		previousNode->previous->next = previousNode;
}

void remove(ListNode *node) {
	if (node->next != NULL)
		node->next->previous = node->previous;
	if (node->previous != NULL)
		node->previous->next = node->next;
	node->next = NULL;
	node->previous = NULL;
}

void * takeAtListNode(ListNode *node) {
	void *data = node->data;
	remove(node);
	free(node);
	return data;
}

List * newList() {
	List *ret = (List *)malloc(sizeof(List));
	ret->begin = NULL;
	ret->rend = NULL;
	return ret;
}

void freeList(List *l) {
	ListIterator it;
	ListIterator next;
	for (it = l->begin; it != NULL; it = next) {
		next = it->next;
		freeListNode(it);
	}
	free(l);
}

int listCount(List *l) {
	ListIterator it;
	int count;
	for (it = l->begin, count = 0; it != NULL; it = it->next)
		++count;
	return count;
}

ListNode * listNodeAtIndex(List *l, int i) {
	ListNode *it = l->begin;
	int j;
	for (j=0; j!=i; ++j) {
		it = it->next;
		assert(it != NULL);
	}
	return it;
}

void * dataAtIndex(List *l, int i) {
	ListNode *node = listNodeAtIndex(l, i);
	if (node != NULL)
		return node->data;
	else
		return NULL;
}

void * takeAtIndex(List *l, int i) {
	ListNode *node = listNodeAtIndex(l, i);
	if (node == l->begin)
		l->begin = node->next;
	else if (node == l->rend)
		l->rend = node->previous;
	return takeAtListNode(node);
}

void insertAfterIndex(List *l, int i, void *data) {
	ListNode *node = listNodeAtIndex(l, i);
	insertAfter(node, data);
	if (node == l->rend)
		l->rend = node->next;
}

void insertBeforeIndex(List *l, int i, void *data) {
	ListNode *node = listNodeAtIndex(l, i);
	insertBefore(node, data);
	if (node == l->begin)
		l->begin = node->previous;
}

void pushFront(List *l, void *data) {
	insertBefore(l->begin, data);
	l->begin = l->begin->previous;
}

void pushBack(List *l, void *data) {
	insertAfter(l->rend, data);
	l->rend = l->rend->next;
}

void * popFront(List *l) {
	if (l->begin != null)
		return takeAtListNode(l->begin);
	else
		return NULL;
}
void * popBack(List *l) {
	if (l->rend != NULL)
		return takeAtListNode(l->rend);
	else
		return NULL;
}
