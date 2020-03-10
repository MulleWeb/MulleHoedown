/* document.h - generic markdown parser */

#ifndef HOEDOWN_DOCUMENT_H
#define HOEDOWN_DOCUMENT_H

#include "buffer.h"
#include "autolink.h"

#ifdef __cplusplus
extern "C" {
#endif


/*************
 * CONSTANTS *
 *************/

typedef enum mulle_hoedown_extensions {
	/* block-level extensions */
	HOEDOWN_EXT_TABLES = (1 << 0),
	HOEDOWN_EXT_FENCED_CODE = (1 << 1),
	HOEDOWN_EXT_FOOTNOTES = (1 << 2),

	/* span-level extensions */
	HOEDOWN_EXT_AUTOLINK = (1 << 3),
	HOEDOWN_EXT_STRIKETHROUGH = (1 << 4),
	HOEDOWN_EXT_UNDERLINE = (1 << 5),
	HOEDOWN_EXT_HIGHLIGHT = (1 << 6),
	HOEDOWN_EXT_QUOTE = (1 << 7),
	HOEDOWN_EXT_SUPERSCRIPT = (1 << 8),
	HOEDOWN_EXT_MATH = (1 << 9),

	/* other flags */
	HOEDOWN_EXT_NO_INTRA_EMPHASIS = (1 << 11),
	HOEDOWN_EXT_SPACE_HEADERS = (1 << 12),
	HOEDOWN_EXT_MATH_EXPLICIT = (1 << 13),

	/* negative flags */
	HOEDOWN_EXT_DISABLE_INDENTED_CODE = (1 << 14)
} mulle_hoedown_extensions;

#define HOEDOWN_EXT_BLOCK (\
	HOEDOWN_EXT_TABLES |\
	HOEDOWN_EXT_FENCED_CODE |\
	HOEDOWN_EXT_FOOTNOTES )

#define HOEDOWN_EXT_SPAN (\
	HOEDOWN_EXT_AUTOLINK |\
	HOEDOWN_EXT_STRIKETHROUGH |\
	HOEDOWN_EXT_UNDERLINE |\
	HOEDOWN_EXT_HIGHLIGHT |\
	HOEDOWN_EXT_QUOTE |\
	HOEDOWN_EXT_SUPERSCRIPT |\
	HOEDOWN_EXT_MATH )

#define HOEDOWN_EXT_FLAGS (\
	HOEDOWN_EXT_NO_INTRA_EMPHASIS |\
	HOEDOWN_EXT_SPACE_HEADERS |\
	HOEDOWN_EXT_MATH_EXPLICIT )

#define HOEDOWN_EXT_NEGATIVE (\
	HOEDOWN_EXT_DISABLE_INDENTED_CODE )

typedef enum mulle_hoedown_list_flags {
	HOEDOWN_LIST_ORDERED = (1 << 0),
	HOEDOWN_LI_BLOCK = (1 << 1)	/* <li> containing block data */
} mulle_hoedown_list_flags;

typedef enum mulle_hoedown_table_flags {
	HOEDOWN_TABLE_ALIGN_LEFT = 1,
	HOEDOWN_TABLE_ALIGN_RIGHT = 2,
	HOEDOWN_TABLE_ALIGN_CENTER = 3,
	HOEDOWN_TABLE_ALIGNMASK = 3,
	HOEDOWN_TABLE_HEADER = 4
} mulle_hoedown_table_flags;

typedef enum mulle_hoedown_autolink_type {
	HOEDOWN_AUTOLINK_NONE,		/* used internally when it is not an autolink*/
	HOEDOWN_AUTOLINK_NORMAL,	/* normal http/http/ftp/mailto/etc link */
	HOEDOWN_AUTOLINK_EMAIL		/* e-mail link without explit mailto: */
} mulle_hoedown_autolink_type;


/*********
 * TYPES *
 *********/

struct mulle_hoedown_document;
typedef struct mulle_hoedown_document mulle_hoedown_document;

struct mulle_hoedown_renderer_data {
	void *opaque;
};
typedef struct mulle_hoedown_renderer_data mulle_hoedown_renderer_data;

/* mulle_hoedown_renderer - functions for rendering parsed data */
struct mulle_hoedown_renderer {
	/* state object */
	void *opaque;

	/* block level callbacks - NULL skips the block */
	void (*blockcode)(mulle_hoedown_buffer *ob, const mulle_hoedown_buffer *text, const mulle_hoedown_buffer *lang, const mulle_hoedown_renderer_data *data);
	void (*blockquote)(mulle_hoedown_buffer *ob, const mulle_hoedown_buffer *content, const mulle_hoedown_renderer_data *data);
	void (*header)(mulle_hoedown_buffer *ob, const mulle_hoedown_buffer *content, int level, const mulle_hoedown_renderer_data *data);
	void (*hrule)(mulle_hoedown_buffer *ob, const mulle_hoedown_renderer_data *data);
	void (*list)(mulle_hoedown_buffer *ob, const mulle_hoedown_buffer *content, mulle_hoedown_list_flags flags, const mulle_hoedown_renderer_data *data);
	void (*listitem)(mulle_hoedown_buffer *ob, const mulle_hoedown_buffer *content, mulle_hoedown_list_flags flags, const mulle_hoedown_renderer_data *data);
	void (*paragraph)(mulle_hoedown_buffer *ob, const mulle_hoedown_buffer *content, const mulle_hoedown_renderer_data *data);
	void (*table)(mulle_hoedown_buffer *ob, const mulle_hoedown_buffer *content, const mulle_hoedown_renderer_data *data);
	void (*table_header)(mulle_hoedown_buffer *ob, const mulle_hoedown_buffer *content, const mulle_hoedown_renderer_data *data);
	void (*table_body)(mulle_hoedown_buffer *ob, const mulle_hoedown_buffer *content, const mulle_hoedown_renderer_data *data);
	void (*table_row)(mulle_hoedown_buffer *ob, const mulle_hoedown_buffer *content, const mulle_hoedown_renderer_data *data);
	void (*table_cell)(mulle_hoedown_buffer *ob, const mulle_hoedown_buffer *content, mulle_hoedown_table_flags flags, const mulle_hoedown_renderer_data *data);
	void (*footnotes)(mulle_hoedown_buffer *ob, const mulle_hoedown_buffer *content, const mulle_hoedown_renderer_data *data);
	void (*footnote_def)(mulle_hoedown_buffer *ob, const mulle_hoedown_buffer *content, unsigned int num, const mulle_hoedown_renderer_data *data);
	void (*blockhtml)(mulle_hoedown_buffer *ob, const mulle_hoedown_buffer *text, const mulle_hoedown_renderer_data *data);

	/* span level callbacks - NULL or return 0 prints the span verbatim */
	int (*autolink)(mulle_hoedown_buffer *ob, const mulle_hoedown_buffer *link, mulle_hoedown_autolink_type type, const mulle_hoedown_renderer_data *data);
	int (*codespan)(mulle_hoedown_buffer *ob, const mulle_hoedown_buffer *text, const mulle_hoedown_renderer_data *data);
	int (*double_emphasis)(mulle_hoedown_buffer *ob, const mulle_hoedown_buffer *content, const mulle_hoedown_renderer_data *data);
	int (*emphasis)(mulle_hoedown_buffer *ob, const mulle_hoedown_buffer *content, const mulle_hoedown_renderer_data *data);
	int (*underline)(mulle_hoedown_buffer *ob, const mulle_hoedown_buffer *content, const mulle_hoedown_renderer_data *data);
	int (*highlight)(mulle_hoedown_buffer *ob, const mulle_hoedown_buffer *content, const mulle_hoedown_renderer_data *data);
	int (*quote)(mulle_hoedown_buffer *ob, const mulle_hoedown_buffer *content, const mulle_hoedown_renderer_data *data);
	int (*image)(mulle_hoedown_buffer *ob, const mulle_hoedown_buffer *link, const mulle_hoedown_buffer *title, const mulle_hoedown_buffer *alt, const mulle_hoedown_renderer_data *data);
	int (*linebreak)(mulle_hoedown_buffer *ob, const mulle_hoedown_renderer_data *data);
	int (*link)(mulle_hoedown_buffer *ob, const mulle_hoedown_buffer *content, const mulle_hoedown_buffer *link, const mulle_hoedown_buffer *title, const mulle_hoedown_renderer_data *data);
	int (*triple_emphasis)(mulle_hoedown_buffer *ob, const mulle_hoedown_buffer *content, const mulle_hoedown_renderer_data *data);
	int (*strikethrough)(mulle_hoedown_buffer *ob, const mulle_hoedown_buffer *content, const mulle_hoedown_renderer_data *data);
	int (*superscript)(mulle_hoedown_buffer *ob, const mulle_hoedown_buffer *content, const mulle_hoedown_renderer_data *data);
	int (*footnote_ref)(mulle_hoedown_buffer *ob, unsigned int num, const mulle_hoedown_renderer_data *data);
	int (*math)(mulle_hoedown_buffer *ob, const mulle_hoedown_buffer *text, int displaymode, const mulle_hoedown_renderer_data *data);
	int (*raw_html)(mulle_hoedown_buffer *ob, const mulle_hoedown_buffer *text, const mulle_hoedown_renderer_data *data);

	/* low level callbacks - NULL copies input directly into the output */
	void (*entity)(mulle_hoedown_buffer *ob, const mulle_hoedown_buffer *text, const mulle_hoedown_renderer_data *data);
	void (*normal_text)(mulle_hoedown_buffer *ob, const mulle_hoedown_buffer *text, const mulle_hoedown_renderer_data *data);

	/* miscellaneous callbacks */
	void (*doc_header)(mulle_hoedown_buffer *ob, int inline_render, const mulle_hoedown_renderer_data *data);
	void (*doc_footer)(mulle_hoedown_buffer *ob, int inline_render, const mulle_hoedown_renderer_data *data);
};
typedef struct mulle_hoedown_renderer mulle_hoedown_renderer;


/*************
 * FUNCTIONS *
 *************/

/* mulle_hoedown_document_new: allocate a new document processor instance */
mulle_hoedown_document *mulle_hoedown_document_new(
	const mulle_hoedown_renderer *renderer,
	mulle_hoedown_extensions extensions,
	size_t max_nesting
) __attribute__ ((malloc));

/* mulle_hoedown_document_render: render regular Markdown using the document processor */
void mulle_hoedown_document_render(mulle_hoedown_document *doc, mulle_hoedown_buffer *ob, const uint8_t *data, size_t size);

/* mulle_hoedown_document_render_inline: render inline Markdown using the document processor */
void mulle_hoedown_document_render_inline(mulle_hoedown_document *doc, mulle_hoedown_buffer *ob, const uint8_t *data, size_t size);

/* mulle_hoedown_document_free: deallocate a document processor instance */
void mulle_hoedown_document_free(mulle_hoedown_document *doc);


#ifdef __cplusplus
}
#endif

#endif /** HOEDOWN_DOCUMENT_H **/
