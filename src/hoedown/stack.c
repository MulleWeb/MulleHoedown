//
//  stack.c
//  MulleHoedown
//
//  Copyright (c) 2015 Nat! - Mulle kybernetiK.
//  All rights reserved.
//
//
//  Redistribution and use in source and binary forms, with or without
//  modification, are permitted provided that the following conditions are met:
//
//  Redistributions of source code must retain the above copyright notice, this
//  list of conditions and the following disclaimer.
//
//  Redistributions in binary form must reproduce the above copyright notice,
//  this list of conditions and the following disclaimer in the documentation
//  and/or other materials provided with the distribution.
//
//  Neither the name of Mulle kybernetiK nor the names of its contributors
//  may be used to endorse or promote products derived from this software
//  without specific prior written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
//  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
//  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
//  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
//  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
//  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
//  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
//  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
//  POSSIBILITY OF SUCH DAMAGE.
//
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
