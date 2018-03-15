/**
 * Workshop 2 - COMP20007
 * author: Naufal Fikri
 */

#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void traverse(List *list);

int main(int argc, char **argv) {
	List *numbers = new_list();
	for (int i = 0; i < 100; i++) {
		list_add_end(numbers, (i*i)); 
	}
	traverse(numbers);
}

void traverse(List *list) {
	while (!list_is_empty(list)) {
		printf("%d\n", list_remove_start(list));
	}
}
