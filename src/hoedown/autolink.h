/* autolink.h - versatile autolinker */

#ifndef HOEDOWN_AUTOLINK_H
#define HOEDOWN_AUTOLINK_H

#include "buffer.h"

#ifdef __cplusplus
extern "C" {
#endif


/*************
 * CONSTANTS *
 *************/

typedef enum mulle_hoedown_autolink_flags {
	HOEDOWN_AUTOLINK_SHORT_DOMAINS = (1 << 0)
} mulle_hoedown_autolink_flags;


/*************
 * FUNCTIONS *
 *************/

/* mulle_hoedown_autolink_is_safe: verify that a URL has a safe protocol */
int mulle_hoedown_autolink_is_safe(const uint8_t *data, size_t size);

/* mulle_hoedown_autolink__www: search for the next www link in data */
size_t mulle_hoedown_autolink__www(size_t *rewind_p, mulle_hoedown_buffer *link,
	uint8_t *data, size_t offset, size_t size, mulle_hoedown_autolink_flags flags);

/* mulle_hoedown_autolink__email: search for the next email in data */
size_t mulle_hoedown_autolink__email(size_t *rewind_p, mulle_hoedown_buffer *link,
	uint8_t *data, size_t offset, size_t size, mulle_hoedown_autolink_flags flags);

/* mulle_hoedown_autolink__url: search for the next URL in data */
size_t mulle_hoedown_autolink__url(size_t *rewind_p, mulle_hoedown_buffer *link,
	uint8_t *data, size_t offset, size_t size, mulle_hoedown_autolink_flags flags);


#ifdef __cplusplus
}
#endif

#endif /** HOEDOWN_AUTOLINK_H **/
