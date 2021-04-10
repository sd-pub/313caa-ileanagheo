/* Gheorghisor Ileana-Teodora, 313CA*/
#include <stdlib.h>
#include <string.h>

#include "Queue.h"
#include "utils.h"


queue_t *
q_create(unsigned int data_size, unsigned int max_size)
{
	/* TODO */
	queue_t *q = malloc(sizeof(queue_t));
	q->buff = malloc(max_size * sizeof(void*));
	for(unsigned int i = 0; i < max_size; i++) {
		q->buff[i] = malloc(sizeof(data_size));
	}
	q->max_size = max_size;
	q->size = 0;
	q->data_size = data_size;
	q->read_idx = 0;
	q->write_idx = 0;

	return q;
}

unsigned int
q_get_size(queue_t *q)
{
	/* TODO */
	return q->size;
}

/*
 * Intoarce 1 daca coada este goala si 0 in caz contrar.
 */
unsigned int
q_is_empty(queue_t *q)
{
	/* TODO */
	DIE(!q, "NULL queue\n");
	DIE(!q->buff, "NULL buffer\n");

	if (q->size == 0) {
		return 1;
	}
	return 0;
}

void *
q_front(queue_t *q)
{
	/* TODO */
	return q->buff[q->read_idx];
}

/* Functia intoarce true daca operatia s-a efectuat si false in caz contrar */
bool
q_dequeue(queue_t *q)
{
	/* TODO */
	DIE(!q, "NULL queue\n");
	DIE(!q->buff, "NULL buffer\n");
	if (q->size == 0) {
		return false;
	}
	if (q->buff[q->read_idx] != NULL) {
		q->size--;
		q->read_idx = (q->read_idx + 1) % q->max_size; /*Pt. circularitate.*/
		return true;
	}
	return false;
}

/* Functia intoarce true daca operatia s-a efectuat si false in caz contrar */
bool
q_enqueue(queue_t *q, void *new_data)
{
	/* TODO */
	DIE(!q, "NULL queue\n");
	if (q->size == q->max_size) {
		printf("Queue is maxed!\n");
		return false;
	} else {
		memcpy(q->buff[q->write_idx], new_data, q->data_size);
		q->size++;
		q->write_idx = (q->write_idx + 1) % q->max_size; /* Pt. circularitate. */
		return true;
	}
}

void
q_clear(queue_t *q)
{
	/* TODO */
	DIE(!q, "NULL queue\n");
	DIE(!q->buff, "NULL buffer\n");
	for(unsigned int i = 0; i < q->max_size; i++) {
		free(q->buff[i]);
	}
	q->size = 0;
	q->read_idx = 0;
	q->write_idx = 0;
}

void
q_free(queue_t *q)
{
	/* TODO */
	DIE(!q, "NULL queue\n");
	q_clear(q);
	free(q->buff);
	free(q);
}
