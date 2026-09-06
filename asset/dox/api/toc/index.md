# MulleHoedown Library Documentation for AI
<!-- Keywords: markdown, hoedown, renderer, NSString, NSData -->
## 1. Introduction & Purpose

- MulleHoedown provides Markdown → HTML conversion for mulle-objc projects. It wraps the Hoedown C markdown engine and exposes convenient Objective-C categories on NSString and NSData while also shipping the underlying C API (buffers, document, HTML renderer).
- Solves: quick conversion of markdown text to HTML and programmatic rendering with extension flags and custom renderers.
- Key features: NSString/NSData categories for one-line conversion, fine-grained C API for custom rendering, Hoedown extension flags (tables, fenced code, autolink, etc.).

## 2. Key Concepts & Design Philosophy

- Two-layer design: a small C core (ported Hoedown) that performs parsing & rendering; an Objective-C shim exposing convenience methods to Cocoa types.
- Renderer callback model: the C API uses a mulle_hoedown_renderer struct with function pointers for block/span callbacks. Users supply callbacks to customize output.
- Buffers: mulle_hoedown_buffer is a lightweight mutable byte buffer used throughout for input/output to avoid repeated allocations.
- Extension-bitflags: feature selection is controlled by bitflags (mulle_hoedown_extensions) enabling/disabling fenced code, tables, autolink, etc.
- Obj-C vs. C: everything a category method does is a thin wrapper around the C core. To understand behavior fall back to the C functions.

## 3. Core API & Data Structures

### 3.1. [src/NSString+MulleHoedown.h]

- Method: - (NSString *) hoedownedString;
  - Purpose: Convert the NSString's Markdown content into an HTML NSString using default flags.
  - Usage: simplest entrypoint for Cocoa consumers (see test/20_features/minus.m / star.m).

### 3.2. [src/NSData+MulleHoedown.h]

- Methods:
  - - (NSData *) hoedownedData;
    - Purpose: Convert NSData containing UTF-8 Markdown to HTML NSData (defaults: flags 0x10000, extensions HOEDOWN_EXT_BLOCK|HOEDOWN_EXT_SPAN, tocIndent 0).
  - - (NSData *) hoedownedDataWithHTMLFlags:(NSUInteger) flags
                             extensions:(NSUInteger) extensions
                              tocIndent:(NSUInteger) indent;
    - Purpose: Full control conversion: render flags (escape, xhtml, hardwrap), extension bits and TOC indentation.
    - Note: The low 16 bits of `flags` are passed to the HTML renderer. Setting bit 0x10000 makes the renderer rewrite local ".md" links to ".html" (via a custom link callback).

### 3.3. [src/MulleHoedown.h]

- Umbrella header that imports "import.h", "NSData+MulleHoedown.h", "NSString+MulleHoedown.h".
- Macro MULLE_HOEDOWN_VERSION: (0.5.2) encoded as ((major << 20) | (minor << 8) | revision).
- Include this header (or the two category headers) for the Objective-C API.

### 3.4. [src/MulleObjCDeps+MulleHoedown.h]

- Objective-C only (guarded by __MULLE_OBJC__). Declares:
  - + (struct _mulle_objc_dependency *) dependencies;
  - Purpose: machinery used by other libraries that depend on MulleHoedown to declare their load in their MulleObjcLoader class. Not used by normal consumers.

### 3.5. [src/hoedown/document.h]

- Types:
  - mulle_hoedown_document: opaque document processor instance.
  - mulle_hoedown_renderer: struct of callbacks used to render parsed nodes (blockcode, header, list, link, image, emphasis, math, etc.). NULL callback pointer skips the block; for span callbacks NULL or return 0 prints the span verbatim.
  - mulle_hoedown_extensions: bitflags to enable features (HOEDOWN_EXT_TABLES, HOEDOWN_EXT_FENCED_CODE, HOEDOWN_EXT_AUTOLINK, etc.). Predefined groups: HOEDOWN_EXT_BLOCK, HOEDOWN_EXT_SPAN, HOEDOWN_EXT_FLAGS, HOEDOWN_EXT_NEGATIVE.

- Lifecycle functions:
  - mulle_hoedown_document *mulle_hoedown_document_new(const mulle_hoedown_renderer *renderer, mulle_hoedown_extensions extensions, size_t max_nesting);
  - void mulle_hoedown_document_render(mulle_hoedown_document *doc, mulle_hoedown_buffer *ob, const uint8_t *data, size_t size);
  - void mulle_hoedown_document_render_inline(mulle_hoedown_document *doc, mulle_hoedown_buffer *ob, const uint8_t *data, size_t size);
  - void mulle_hoedown_document_free(mulle_hoedown_document *doc);

- Core operations: construct renderer struct (fill callbacks), create document with desired extensions, render into a mulle_hoedown_buffer.
- Note: document.h includes buffer.h and autolink.h; the autolink helper functions (mulle_hoedown_autolink_is_safe, _www, _email, _url) are declared in autolink.h.

### 3.6. [src/hoedown/buffer.h]

- struct mulle_hoedown_buffer
  - Fields: data (uint8_t *), size (string length), asize (allocated size, 0 = volatile buffer), unit (realloc unit, 0 = read-only buffer), and allocator callbacks (data_realloc, data_free, buffer_free).
- API:
  - Allocation wrappers: mulle_hoedown_malloc, mulle_hoedown_calloc, mulle_hoedown_realloc (abort on OOM).
  - mulle_hoedown_buffer_init(mulle_hoedown_buffer *buffer, size_t unit, mulle_hoedown_realloc_callback data_realloc, mulle_hoedown_free_callback data_free, mulle_hoedown_free_callback buffer_free);
  - mulle_hoedown_buffer *mulle_hoedown_buffer_new(size_t unit);
  - void mulle_hoedown_buffer_reset(mulle_hoedown_buffer *buf);
  - void mulle_hoedown_buffer_grow(mulle_hoedown_buffer *buf, size_t neosz);
  - void mulle_hoedown_buffer_put(mulle_hoedown_buffer *buf, const uint8_t *data, size_t size);
  - void mulle_hoedown_buffer_puts(mulle_hoedown_buffer *buf, const char *str);
  - void mulle_hoedown_buffer_putc(mulle_hoedown_buffer *buf, uint8_t c);
  - void mulle_hoedown_buffer_set(mulle_hoedown_buffer *buf, const uint8_t *data, size_t size);
  - void mulle_hoedown_buffer_sets(mulle_hoedown_buffer *buf, const char *str);
  - int mulle_hoedown_buffer_eq(const mulle_hoedown_buffer *buf, const uint8_t *data, size_t size);
  - int mulle_hoedown_buffer_eqs(const mulle_hoedown_buffer *buf, const char *str);
  - int mulle_hoedown_buffer_prefix(const mulle_hoedown_buffer *buf, const char *prefix);
  - void mulle_hoedown_buffer_slurp(mulle_hoedown_buffer *buf, size_t size);
  - const char *mulle_hoedown_buffer_cstr(mulle_hoedown_buffer *buf);
  - void mulle_hoedown_buffer_printf(mulle_hoedown_buffer *buf, const char *fmt, ...);
  - void mulle_hoedown_buffer_free(mulle_hoedown_buffer *buf);
- Macros HOEDOWN_BUFPUTSL, HOEDOWN_BUFSETSL, HOEDOWN_BUFEQSL: optimized versions of put/puts/eqs for string literals.
- Semantics: chosen to minimize reallocations; assert requires buf->unit != 0 for mutating ops. Callers may pass NULL allocator callbacks to stack-allocated buffers only if they never grow.

### 3.7. [src/hoedown/html.h]

- HTML renderer flags: HOEDOWN_HTML_SKIP_HTML, HOEDOWN_HTML_ESCAPE, HOEDOWN_HTML_HARD_WRAP, HOEDOWN_HTML_USE_XHTML (enum mulle_hoedown_html_flags).
- Constructors:
  - mulle_hoedown_renderer *mulle_hoedown_html_renderer_new(mulle_hoedown_html_flags render_flags, int nesting_level);
  - mulle_hoedown_renderer *mulle_hoedown_html_toc_renderer_new(int nesting_level);
  - void mulle_hoedown_html_renderer_free(mulle_hoedown_renderer *renderer);
- Struct mulle_hoedown_html_renderer_state: holds render state (toc_data, flags, optional link_attributes callback).
- Utilities: void mulle_hoedown_html_smartypants(mulle_hoedown_buffer *ob, const uint8_t *data, size_t size); mulle_hoedown_html_tag mulle_hoedown_html_is_tag(const uint8_t *data, size_t size, const char *tagname).

## 4. Performance Characteristics

- Rendering complexity: O(n) in input size for parsing + rendering (single pass style, callbacks per node).
- Buffer operations: append (put/puts) amortized O(1) per byte; grow may reallocate (unit-driven).
- Memory: document_new allocates renderer-specific state; buffers can be made volatile (asize == 0) to avoid ownership costs.
- Thread-safety: not inherently thread-safe. Use separate document/buffer instances per thread or external synchronization.

## 5. AI Usage Recommendations & Patterns

- Best practice: For simple conversions prefer the Objective-C categories (NSString/NSData). For advanced customization use the C API to create renderer and supply callbacks.
- Lifecycle: Always free document instances with mulle_hoedown_document_free and free buffers with mulle_hoedown_buffer_free when allocated. Free the HTML renderer with mulle_hoedown_html_renderer_free.
- Ownership: mulle_hoedown_buffer_cstr() returns a NUL-terminated pointer owned by the buffer; do not free the pointer separately.
- Pitfalls:
  - Do not call callbacks that assume thread-shared state without synchronization.
  - Be cautious with extension bits; conflicting flags (negative flags) can disable behaviors.
  - Categories yield autoreleased Objective-C objects; manage memory according to project conventions.
  - mulle_hoedown_buffer_* mutating functions assert buf->unit; a buffer initialized with unit 0 is read-only and cannot be appended to.

## 6. Integration Examples

### Example 1: Converting NSString to HTML (like test/20_features/minus.m)

```objc
#import <MulleHoedown/MulleHoedown.h>

int   main( void)
{
   mulle_printf( "%@\n", [@"- line1\n- line2\n" hoedownedString]);
   return( 0);
}
```

### Example 2: Using NSData conversion with flags

```objc
#import <MulleHoedown/MulleHoedown.h>

int   main( void)
{
   NSData  *data;
   NSData  *html;

   data = [@"# Title\n\nParagraph." dataUsingEncoding:NSUTF8StringEncoding];
   html = [data hoedownedDataWithHTMLFlags:0x10000
                                extensions:HOEDOWN_EXT_BLOCK | HOEDOWN_EXT_SPAN
                                 tocIndent:2];
   fwrite( [html bytes], [html length], 1, stdout);
   fputc( '\n', stdout);
   return( 0);
}
```

### Example 3: Creating a custom C renderer

```c
#include "hoedown/document.h"
#include "hoedown/html.h"
#include "hoedown/buffer.h"
#include <string.h>

void   my_paragraph( mulle_hoedown_buffer *ob,
                     const mulle_hoedown_buffer *content,
                     const mulle_hoedown_renderer_data *data)
{
   /* wrap paragraphs with a custom class */
   mulle_hoedown_buffer_puts( ob, "<p class=\"my\">\n");
   mulle_hoedown_buffer_put( ob, content->data, content->size);
   mulle_hoedown_buffer_puts( ob, "</p>\n");
}

int   main( void)
{
   mulle_hoedown_renderer   *renderer;
   mulle_hoedown_buffer     *out;
   mulle_hoedown_document   *doc;

   renderer = mulle_hoedown_html_renderer_new( 0, 16);
   renderer->paragraph = my_paragraph;

   out = mulle_hoedown_buffer_new( 64);
   doc = mulle_hoedown_document_new( renderer,
                                     HOEDOWN_EXT_BLOCK | HOEDOWN_EXT_AUTOLINK,
                                     16);
   mulle_hoedown_document_render( doc, out, (const uint8_t *) "Paragraph text",
                                  strlen( "Paragraph text"));
   printf( "%s\n", mulle_hoedown_buffer_cstr( out));

   mulle_hoedown_document_free( doc);
   mulle_hoedown_html_renderer_free( renderer);
   mulle_hoedown_buffer_free( out);
   return( 0);
}
```

## 7. Dependencies

- MulleFoundationBase (amalgamates the Foundation projects used by the Objective-C parts; brings in mulle-objc-runtime and mulle-c11 transitively)
- mulle-objc-list (used at build/runtime for XCTest-like metadata)


---

References and pointers:
- README.md for installation and high-level overview
- test/10_markup/simple.m, test/20_features/*.m for minimal usage examples
- src/hoedown/*.h for full C API signatures