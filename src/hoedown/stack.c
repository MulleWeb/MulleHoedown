#include "stack.h"

#include "buffer.h"

#include <stdlib.h>
#include <string.h>
#include <assert.h>

void
mulle_hoedown_stack_init(mulle_hoedown_stack *st, size_t initial_size)
{
	assert(st);

	st->item = NULL;
	st->size = st->asize = 0;

	if (!initial_size)
		initial_size = 8;

	mulle_hoedown_stack_grow(st, initial_size);
}

void
mulle_hoedown_stack_uninit(mulle_hoedown_stack *st)
{
	assert(st);

	free(st->item);
}

void
mulle_hoedown_stack_grow(mulle_hoedown_stack *st, size_t neosz)
{
	assert(st);

	if (st->asize >= neosz)
		return;

	st->item = mulle_hoedown_realloc(st->item, neosz * sizeof(void *));
	memset(st->item + st->asize, 0x0, (neosz - st->asize) * sizeof(void *));

	st->asize = neosz;

	if (st->size > neosz)
		st->size = neosz;
}

void
mulle_hoedown_stack_push(mulle_hoedown_stack *st, void *item)
{
	assert(st);

	if (st->size >= st->asize)
		mulle_hoedown_stack_grow(st, st->size * 2);

	st->item[st->size++] = item;
}

void *
mulle_hoedown_stack_pop(mulle_hoedown_stack *st)
{
	assert(st);

	if (!st->size)
		return NULL;

	return st->item[--st->size];
}

void *
mulle_hoedown_stack_top(const mulle_hoedown_stack *st)
{
	assert(st);

	if (!st->size)
		return NULL;

	return st->item[st->size - 1];
}
