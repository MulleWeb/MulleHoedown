/* html.h - HTML renderer and utilities */

#ifndef HOEDOWN_HTML_H
#define HOEDOWN_HTML_H

#include "document.h"
#include "buffer.h"

#ifdef __cplusplus
extern "C" {
#endif


/*************
 * CONSTANTS *
 *************/

typedef enum mulle_hoedown_html_flags {
	HOEDOWN_HTML_SKIP_HTML = (1 << 0),
	HOEDOWN_HTML_ESCAPE = (1 << 1),
	HOEDOWN_HTML_HARD_WRAP = (1 << 2),
	HOEDOWN_HTML_USE_XHTML = (1 << 3)
} mulle_hoedown_html_flags;

typedef enum mulle_hoedown_html_tag {
	HOEDOWN_HTML_TAG_NONE = 0,
	HOEDOWN_HTML_TAG_OPEN,
	HOEDOWN_HTML_TAG_CLOSE
} mulle_hoedown_html_tag;


/*********
 * TYPES *
 *********/

struct mulle_hoedown_html_renderer_state {
	void *opaque;

	struct {
		int header_count;
		int current_level;
		int level_offset;
		int nesting_level;
	} toc_data;

	mulle_hoedown_html_flags flags;

	/* extra callbacks */
	void (*link_attributes)(mulle_hoedown_buffer *ob, const mulle_hoedown_buffer *url, const mulle_hoedown_renderer_data *data);
};
typedef struct mulle_hoedown_html_renderer_state mulle_hoedown_html_renderer_state;


/*************
 * FUNCTIONS *
 *************/

/* mulle_hoedown_html_smartypants: process an HTML snippet using SmartyPants for smart punctuation */
void mulle_hoedown_html_smartypants(mulle_hoedown_buffer *ob, const uint8_t *data, size_t size);

/* mulle_hoedown_html_is_tag: checks if data starts with a specific tag, returns the tag type or NONE */
mulle_hoedown_html_tag mulle_hoedown_html_is_tag(const uint8_t *data, size_t size, const char *tagname);


/* mulle_hoedown_html_renderer_new: allocates a regular HTML renderer */
mulle_hoedown_renderer *mulle_hoedown_html_renderer_new(
	mulle_hoedown_html_flags render_flags,
	int nesting_level
) __attribute__ ((malloc));

/* mulle_hoedown_html_toc_renderer_new: like mulle_hoedown_html_renderer_new, but the returned renderer produces the Table of Contents */
mulle_hoedown_renderer *mulle_hoedown_html_toc_renderer_new(
	int nesting_level
) __attribute__ ((malloc));

/* mulle_hoedown_html_renderer_free: deallocate an HTML renderer */
void mulle_hoedown_html_renderer_free(mulle_hoedown_renderer *renderer);


#ifdef __cplusplus
}
#endif

#endif /** HOEDOWN_HTML_H **/
