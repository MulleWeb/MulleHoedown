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
