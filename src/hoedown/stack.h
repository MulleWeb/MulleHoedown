//
//  stack.h
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
/* stack.h - simple stacking */

#ifndef HOEDOWN_STACK_H
#define HOEDOWN_STACK_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif


/*********
 * TYPES *
 *********/

struct mulle_hoedown_stack {
	void **item;
	size_t size;
	size_t asize;
};
typedef struct mulle_hoedown_stack mulle_hoedown_stack;


/*************
 * FUNCTIONS *
 *************/

/* mulle_hoedown_stack_init: initialize a stack */
void mulle_hoedown_stack_init(mulle_hoedown_stack *st, size_t initial_size);

/* mulle_hoedown_stack_uninit: free internal data of the stack */
void mulle_hoedown_stack_uninit(mulle_hoedown_stack *st);

/* mulle_hoedown_stack_grow: increase the allocated size to the given value */
void mulle_hoedown_stack_grow(mulle_hoedown_stack *st, size_t neosz);

/* mulle_hoedown_stack_push: push an item to the top of the stack */
void mulle_hoedown_stack_push(mulle_hoedown_stack *st, void *item);

/* mulle_hoedown_stack_pop: retrieve and remove the item at the top of the stack */
void *mulle_hoedown_stack_pop(mulle_hoedown_stack *st);

/* mulle_hoedown_stack_top: retrieve the item at the top of the stack */
void *mulle_hoedown_stack_top(const mulle_hoedown_stack *st);


#ifdef __cplusplus
}
#endif

#endif /** HOEDOWN_STACK_H **/
