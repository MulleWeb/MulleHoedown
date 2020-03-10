/* buffer.h - simple, fast buffers */

#ifndef HOEDOWN_BUFFER_H
#define HOEDOWN_BUFFER_H

#include <stdio.h>
#include <stddef.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(_MSC_VER)
#define __attribute__(x)
#define inline __inline
#define __builtin_expect(x,n) x
#endif


/*********
 * TYPES *
 *********/

typedef void *(*mulle_hoedown_realloc_callback)(void *, size_t);
typedef void (*mulle_hoedown_free_callback)(void *);

struct mulle_hoedown_buffer {
	uint8_t *data;	/* actual character data */
	size_t size;	/* size of the string */
	size_t asize;	/* allocated size (0 = volatile buffer) */
	size_t unit;	/* reallocation unit size (0 = read-only buffer) */

	mulle_hoedown_realloc_callback data_realloc;
	mulle_hoedown_free_callback data_free;
	mulle_hoedown_free_callback buffer_free;
};

typedef struct mulle_hoedown_buffer mulle_hoedown_buffer;


/*************
 * FUNCTIONS *
 *************/

/* allocation wrappers */
void *mulle_hoedown_malloc(size_t size) __attribute__ ((malloc));
void *mulle_hoedown_calloc(size_t nmemb, size_t size) __attribute__ ((malloc));
void *mulle_hoedown_realloc(void *ptr, size_t size) __attribute__ ((malloc));

/* mulle_hoedown_buffer_init: initialize a buffer with custom allocators */
void mulle_hoedown_buffer_init(
	mulle_hoedown_buffer *buffer,
	size_t unit,
	mulle_hoedown_realloc_callback data_realloc,
	mulle_hoedown_free_callback data_free,
	mulle_hoedown_free_callback buffer_free
);

/* mulle_hoedown_buffer_new: allocate a new buffer */
mulle_hoedown_buffer *mulle_hoedown_buffer_new(size_t unit) __attribute__ ((malloc));

/* mulle_hoedown_buffer_reset: free internal data of the buffer */
void mulle_hoedown_buffer_reset(mulle_hoedown_buffer *buf);

/* mulle_hoedown_buffer_grow: increase the allocated size to the given value */
void mulle_hoedown_buffer_grow(mulle_hoedown_buffer *buf, size_t neosz);

/* mulle_hoedown_buffer_put: append raw data to a buffer */
void mulle_hoedown_buffer_put(mulle_hoedown_buffer *buf, const uint8_t *data, size_t size);

/* mulle_hoedown_buffer_puts: append a NUL-terminated string to a buffer */
void mulle_hoedown_buffer_puts(mulle_hoedown_buffer *buf, const char *str);

/* mulle_hoedown_buffer_putc: append a single char to a buffer */
void mulle_hoedown_buffer_putc(mulle_hoedown_buffer *buf, uint8_t c);

/* mulle_hoedown_buffer_set: replace the buffer's contents with raw data */
void mulle_hoedown_buffer_set(mulle_hoedown_buffer *buf, const uint8_t *data, size_t size);

/* mulle_hoedown_buffer_sets: replace the buffer's contents with a NUL-terminated string */
void mulle_hoedown_buffer_sets(mulle_hoedown_buffer *buf, const char *str);

/* mulle_hoedown_buffer_eq: compare a buffer's data with other data for equality */
int mulle_hoedown_buffer_eq(const mulle_hoedown_buffer *buf, const uint8_t *data, size_t size);

/* mulle_hoedown_buffer_eq: compare a buffer's data with NUL-terminated string for equality */
int mulle_hoedown_buffer_eqs(const mulle_hoedown_buffer *buf, const char *str);

/* mulle_hoedown_buffer_prefix: compare the beginning of a buffer with a string */
int mulle_hoedown_buffer_prefix(const mulle_hoedown_buffer *buf, const char *prefix);

/* mulle_hoedown_buffer_slurp: remove a given number of bytes from the head of the buffer */
void mulle_hoedown_buffer_slurp(mulle_hoedown_buffer *buf, size_t size);

/* mulle_hoedown_buffer_cstr: NUL-termination of the string array (making a C-string) */
const char *mulle_hoedown_buffer_cstr(mulle_hoedown_buffer *buf);

/* mulle_hoedown_buffer_printf: formatted printing to a buffer */
void mulle_hoedown_buffer_printf(mulle_hoedown_buffer *buf, const char *fmt, ...) __attribute__ ((format (printf, 2, 3)));

/* mulle_hoedown_buffer_free: free the buffer */
void mulle_hoedown_buffer_free(mulle_hoedown_buffer *buf);


/* HOEDOWN_BUFPUTSL: optimized mulle_hoedown_buffer_puts of a string literal */
#define HOEDOWN_BUFPUTSL(output, literal) \
	mulle_hoedown_buffer_put(output, (const uint8_t *)literal, sizeof(literal) - 1)

/* HOEDOWN_BUFSETSL: optimized mulle_hoedown_buffer_sets of a string literal */
#define HOEDOWN_BUFSETSL(output, literal) \
	mulle_hoedown_buffer_set(output, (const uint8_t *)literal, sizeof(literal) - 1)

/* HOEDOWN_BUFEQSL: optimized mulle_hoedown_buffer_eqs of a string literal */
#define HOEDOWN_BUFEQSL(output, literal) \
	mulle_hoedown_buffer_eq(output, (const uint8_t *)literal, sizeof(literal) - 1)


#ifdef __cplusplus
}
#endif

#endif /** HOEDOWN_BUFFER_H **/
