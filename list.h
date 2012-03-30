typedef struct _ListNode {
	void			 *data;
	struct _ListNode *next;
	struct _ListNode *previous;
} ListNode;

ListNode * newListNode();
void freeListNode(ListNode *l); // frees data also
void insertAfter(ListNode *node, void *data);
void insertBefore(ListNode *node, void *data);
void remove(ListNode *node);
void * takeAtListNode(ListNode *node);

typedef (ListNode *) ListIterator;
typedef struct {
	ListIterator begin;
	ListIterator rend;
} List;

List * newList();
void freeList(List *); // frees data also
int listCount(List *l);
ListNode * listNodeAtIndex(List *l, int i);
void * dataAtIndex(List *l, int i);
void * takeAtIndex(List *l, int i);
void insertAfterIndex(List *l, int i, void *data);
void insertBeforeIndex(List *l, int i, void *data);
void pushFront(List *l, void *data);
void pushBack(List *l, void *data);
void * popFront(List *l);
void * popBack(List *l);
