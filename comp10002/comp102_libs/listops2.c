#include <stdlib.h>
#include <assert.h>
typedef struct node NodeType;
typedef int DataType;

struct node {
	DataType data;
	NodeType *next;
};

typedef struct {
	NodeType *head;
	NodeType *tail;
	int itemCount;
} ListType;

ListType *createList() {
	ListType *list;
	list = (ListType*)malloc(sizeof(ListType));
	assert(list != NULL);
	list->head = list->tail = NULL;
	list->itemCount = 0;
	return list;
}

NodeType *nodeOffset(NodeType *node, int offset) {
	for (int i = 0; i < offset; i++) {
		if (node->next == NULL) {
			/** exception handling **/
		}
		node = node->next;
	}
	return node;
}

NodeType *getItem(ListType *list, int pos) {
	assert(pos >= 0 && pos < list->itemCount);
	NodeType *node = list->head;
	for (int i = 0; i < pos; i++){
		node = node->next;
	}
	return node;
}


static void popHead(ListType *list) {
	NodeType *node = list->head;
	list->head = list->head->next;
	list->itemCount--;
	free(node);
}

static void popTail(ListType *list) {
	NodeType *node = list->tail;
	list->tail = list->tail->next;
	(list->itemCount)--;
	free(node);
}

void popItem(ListType *list, int pos) {
	assert(pos >= 0 && pos < list->itemCount);
	if (pos == 0) {
		popHead(list);
	} else if (pos == list->itemCount - 1) {
		popTail(list);
	} else {
		NodeType *prev = getItem(list, pos-1);
		NodeType *node = prev->next;
		NodeType *nextNode = node->next;
		prev->next = nextNode;
		list->itemCount -= 1;
		free(node);
	}
}


void insertAtHead(ListType *list, DataType value) {
	NodeType *newNode = (NodeType*)malloc(sizeof(NodeType));
	assert(list != NULL && newNode != NULL);
	newNode->data = value;
	(list->itemCount)++;
	newNode->next = list->head;
	list->head = newNode;
	if (list->tail == NULL) {
		list->tail = newNode;
	}
}

void insertAtTail(ListType *list, DataType value){
	NodeType *newNode = (NodeType*)malloc(sizeof(NodeType));
	assert (list != NULL && newNode != NULL);
	newNode->data = value;
	(list->itemCount)++;
	newNode->next = list->head;
	list->head = newNode;
	if (list->head == NULL) {
		list->head = newNode;
	}
}

void insertItem(ListType *list, DataType value, int pos) {
	assert(pos >= 0 && pos < list->itemCount);
	NodeType *newNode = (NodeType*)malloc(sizeof(NodeType));
	assert(list != NULL && newNode != NULL);
	newNode->data = value;
	NodeType *prev = getItem(list, pos-1);
	newNode->next = prev->next;
	prev->next = newNode;
	(list->itemCount)++;
}

void fuckThisList(ListType *list){
	NodeType *node, *prev;
	node = list->head;
	while (node) {
		prev = node;
		node = node->next;
		free(node);
	}
	free(list);
}