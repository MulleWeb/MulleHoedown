#include "buffer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void *
mulle_hoedown_malloc(size_t size)
{
	void *ret = malloc(size);

	if (!ret) {
		fprintf(stderr, "Allocation failed.\n");
		abort();
	}

	return ret;
}

void *
mulle_hoedown_calloc(size_t nmemb, size_t size)
{
	void *ret = calloc(nmemb, size);

	if (!ret) {
		fprintf(stderr, "Allocation failed.\n");
		abort();
	}

	return ret;
}

void *
mulle_hoedown_realloc(void *ptr, size_t size)
{
	void *ret = realloc(ptr, size);

	if (!ret) {
		fprintf(stderr, "Allocation failed.\n");
		abort();
	}

	return ret;
}

void
mulle_hoedown_buffer_init(
	mulle_hoedown_buffer *buf,
	size_t unit,
	mulle_hoedown_realloc_callback data_realloc,
	mulle_hoedown_free_callback data_free,
	mulle_hoedown_free_callback buffer_free)
{
	assert(buf);

	buf->data = NULL;
	buf->size = buf->asize = 0;
	buf->unit = unit;
	buf->data_realloc = data_realloc;
	buf->data_free = data_free;
	buf->buffer_free = buffer_free;
}

mulle_hoedown_buffer *
mulle_hoedown_buffer_new(size_t unit)
{
	mulle_hoedown_buffer *ret = mulle_hoedown_malloc(sizeof (mulle_hoedown_buffer));
	mulle_hoedown_buffer_init(ret, unit, mulle_hoedown_realloc, free, free);
	return ret;
}

void
mulle_hoedown_buffer_free(mulle_hoedown_buffer *buf)
{
	if (!buf) return;

	buf->data_free(buf->data);

	if (buf->buffer_free)
		buf->buffer_free(buf);
}

void
mulle_hoedown_buffer_reset(mulle_hoedown_buffer *buf)
{
	assert(buf && buf->unit);

	buf->data_free(buf->data);
	buf->data = NULL;
	buf->size = buf->asize = 0;
}

void
mulle_hoedown_buffer_grow(mulle_hoedown_buffer *buf, size_t neosz)
{
	size_t neoasz;
	assert(buf && buf->unit);

	if (buf->asize >= neosz)
		return;

	neoasz = buf->asize + buf->unit;
	while (neoasz < neosz)
		neoasz += buf->unit;

	buf->data = buf->data_realloc(buf->data, neoasz);
	buf->asize = neoasz;
}

void
mulle_hoedown_buffer_put(mulle_hoedown_buffer *buf, const uint8_t *data, size_t size)
{
	assert(buf && buf->unit);

	if (buf->size + size > buf->asize)
		mulle_hoedown_buffer_grow(buf, buf->size + size);

	memcpy(buf->data + buf->size, data, size);
	buf->size += size;
}

void
mulle_hoedown_buffer_puts(mulle_hoedown_buffer *buf, const char *str)
{
	mulle_hoedown_buffer_put(buf, (const uint8_t *)str, strlen(str));
}

void
mulle_hoedown_buffer_putc(mulle_hoedown_buffer *buf, uint8_t c)
{
	assert(buf && buf->unit);

	if (buf->size >= buf->asize)
		mulle_hoedown_buffer_grow(buf, buf->size + 1);

	buf->data[buf->size] = c;
	buf->size += 1;
}

void
mulle_hoedown_buffer_set(mulle_hoedown_buffer *buf, const uint8_t *data, size_t size)
{
	assert(buf && buf->unit);

	if (size > buf->asize)
		mulle_hoedown_buffer_grow(buf, size);

	memcpy(buf->data, data, size);
	buf->size = size;
}

void
mulle_hoedown_buffer_sets(mulle_hoedown_buffer *buf, const char *str)
{
	mulle_hoedown_buffer_set(buf, (const uint8_t *)str, strlen(str));
}

int
mulle_hoedown_buffer_eq(const mulle_hoedown_buffer *buf, const uint8_t *data, size_t size)
{
	if (buf->size != size) return 0;
	return memcmp(buf->data, data, size) == 0;
}

int
mulle_hoedown_buffer_eqs(const mulle_hoedown_buffer *buf, const char *str)
{
	return mulle_hoedown_buffer_eq(buf, (const uint8_t *)str, strlen(str));
}

int
mulle_hoedown_buffer_prefix(const mulle_hoedown_buffer *buf, const char *prefix)
{
	size_t i;

	assert(buf && buf->unit);

	for (i = 0; i < buf->size; ++i) {
		if (prefix[i] == 0)
			return 0;

		if (buf->data[i] != prefix[i])
			return buf->data[i] - prefix[i];
	}

	return 0;
}

void
mulle_hoedown_buffer_slurp(mulle_hoedown_buffer *buf, size_t size)
{
	assert(buf && buf->unit);

	if (size >= buf->size) {
		buf->size = 0;
		return;
	}

	buf->size -= size;
	memmove(buf->data, buf->data + size, buf->size);
}

const char *
mulle_hoedown_buffer_cstr(mulle_hoedown_buffer *buf)
{
	assert(buf && buf->unit);

	if (buf->size < buf->asize && buf->data[buf->size] == 0)
		return (char *)buf->data;

	mulle_hoedown_buffer_grow(buf, buf->size + 1);
	buf->data[buf->size] = 0;

	return (char *)buf->data;
}

void
mulle_hoedown_buffer_printf(mulle_hoedown_buffer *buf, const char *fmt, ...)
{
	va_list ap;
	int n;

	assert(buf && buf->unit);

	if (buf->size >= buf->asize)
		mulle_hoedown_buffer_grow(buf, buf->size + 1);

	va_start(ap, fmt);
	n = vsnprintf((char *)buf->data + buf->size, buf->asize - buf->size, fmt, ap);
	va_end(ap);

	if (n < 0) {
#ifndef _MSC_VER
		return;
#else
		va_start(ap, fmt);
		n = _vscprintf(fmt, ap);
		va_end(ap);
#endif
	}

	if ((size_t)n >= buf->asize - buf->size) {
		mulle_hoedown_buffer_grow(buf, buf->size + n + 1);

		va_start(ap, fmt);
		n = vsnprintf((char *)buf->data + buf->size, buf->asize - buf->size, fmt, ap);
		va_end(ap);
	}

	if (n < 0)
		return;

	buf->size += n;
}
