#include <stdlib.h>

#include "Stack.h"
#include "utils.h"

stack_t *
st_create(unsigned int data_size)
{
	/* TODO */
	stack_t *st = malloc(sizeof(stack_t));
	st->list = ll_create(data_size);
	return st;
}

unsigned int
st_get_size(stack_t *st)
{
	/* TODO */
	return st->list->size;
}

/*
 * Intoarce 1 daca stiva este goala si 0 in caz contrar.
 */
unsigned int
st_is_empty(stack_t *st)
{
	/* TODO */
	DIE(!st, "NULL stack");
	DIE(!st->list, "NULL list");

	if (st->list->size == 0) {
		return 1;
	}
	return 0;
}

void *
st_peek(stack_t *st)
{
	/* TODO */
	return st->list->head->data;
}

void
st_pop(stack_t *st)
{
	/* TODO */
	ll_node_t *pop;
	DIE(!st, "NULL stack");
	DIE(!st->list, "NULL list");
	pop = ll_remove_nth_node(st->list, 0);
	free(pop->data);
	free(pop);
}

void
st_push(stack_t *st, void *new_data)
{
	/* TODO */
	ll_add_nth_node(st->list, 0, new_data);
}

void
st_clear(stack_t *st)
{
	/* TODO */
	ll_free(&st->list);
}

void
st_free(stack_t *st)
{
	/* TODO */
	st_clear(st);
	free(st->list);
	free(st);
}
