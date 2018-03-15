/**
 * another fucking queue implementation
 * COMP20007
 *
 * by Naufal Fikri Setiawan
 */

#include <stdlib.h>
#include "list.h"

typedef struct queue Queue;

Queue *new_queue();

struct queue {
	List *qlist
}

Queue *new_queue() {
	Queue *q = malloc(sizeof *queue);
	assert(q);

	q->qlist = new_list();
	assert(q->qlist);
	
	return q;
}

void free_queue(Queue *queue) {
	free_list(queue->qlist);
	free(queue);
}

void queue_enqueue(Queue *queue, int item) {
	list_add_end(queue->qlist, item);
}

int queue_dequeue(Queue *queue, int item) {
	return list_remove_start(queue->qlist);
}

int queue_size(Queue *queue) {
	return list_size(queue->qlist);
}
