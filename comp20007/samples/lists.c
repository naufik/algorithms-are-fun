/*
 * List Operations - COMP20007 Tutorial 1
 * Author: Naufal Fikri
 * nauffik@gmail.com
 * 
 */

#include <stdlib.h>
#include <stdio.h>

typedef struct {
	char *value;
	node_t *next;
} node_t;

typedef struct {
	node_t *first;
	node_t *last;
} list_t;

list_t* new_list() {
	list_t* l = (list_t*)malloc(sizeof(list_t));
	l->first = NULL;
	l->last = NULL;
	return l;
}

void list_append(list_t *list, char *val) {
	node_t* node = (node_t*)malloc(sizeof(node_t));
	node->value = val;
	
	if (list->first == NULL) {
		list->first = node;
	} else {
		list->last->next = node;
	}

	list->last=node;
}

void list_traverse(list_t *list) {
	node_t* current = list->first;
	while (current != NULL) {
		printf("%s\n", current->value);
	}
}

int main(int argc, char **argv) {
	list_t* itemlist = new_list();
	list_append(itemlist, "study");
	list_append(itemlist, "practice");
	list_append(itemlist, "pass comp20007");
	list_append(itemlist, "overthrow capitalism");
	list_traverse(itemlist);
}
