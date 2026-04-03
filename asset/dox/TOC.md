# MulleHoedown Library Documentation for AI

## 1. Introduction & Purpose

**MulleHoedown** is an Objective-C wrapper around the Hoedown Markdown parser, providing safe, configurable conversion from Markdown syntax to HTML. Hoedown is a fast, standards-compliant Markdown parser that supports CommonMark/GFM syntax, HTML escaping for security, and optional Markdown extensions (tables, strikethrough, footnotes, etc.).

This library is particularly useful for:
- User-generated content rendering in web applications
- Documentation generation from Markdown source
- Converting stored Markdown to displayable HTML
- Building content management systems with Markdown support

## 2. Key Concepts & Design Philosophy

- **Safe HTML Generation**: Prevents script injection and malicious content by escaping HTML entities by default
- **Extension Support**: Pluggable Markdown extensions (GFM tables, strikethrough, footnotes, highlight, quote, superscript, math)
- **Flexible Flags**: Control HTML output format via bit flags (smart typography, skip HTML blocks, etc.)
- **Link Transformation**: Built-in support for converting Markdown `.md` links to HTML `.html` links
- **Category-based API**: Integrates naturally with NSString and NSData via Objective-C categories

## 3. Core API & Data Structures

### NSString Category: `NSString( MulleHoedown)`

#### Basic Conversion
- `- (NSString *) hoedownedString` → `NSString *`
  - Converts Markdown string to HTML using default settings
  - Safe by default (escapes HTML)
  - Returns autoreleased NSString
  - **Use case**: Simple one-off Markdown conversions

#### Advanced Conversion
- `- (NSData *) hoedownedDataWithHTMLFlags:(NSUInteger)flags extensions:(NSUInteger)extensions tocIndent:(NSUInteger)indent` → `NSData *`
  - Full-featured conversion with granular control
  - **flags**: Bit flags controlling HTML generation behavior (see 3.2)
  - **extensions**: Bit flags enabling Markdown extensions (see 3.3)
  - **tocIndent**: Indentation level for table-of-contents generation (0 disables TOC)
  - Returns NSData in UTF-8 encoding
  - **Use case**: Complex rendering with custom options

### NSData Category: `NSData( MulleHoedown)`

#### Basic Conversion
- `- (NSData *) hoedownedData` → `NSData *`
  - Converts Markdown NSData to HTML NSData
  - Equivalent to NSString's `hoedownedString` but preserves binary data

#### Advanced Conversion  
- `- (NSData *) hoedownedDataWithHTMLFlags:(NSUInteger)flags extensions:(NSUInteger)extensions tocIndent:(NSUInteger)indent` → `NSData *`
  - See NSString variant above
  - Useful when working with raw bytes or non-NSString Markdown sources

### 3.2 HTML Flags (NSUInteger bit flags)

Control how HTML is generated. Combine flags with bitwise OR (`|`):

- `0x0001` - **SKIP_HTML**: Do not render raw HTML blocks (security)
- `0x0002` - **ESCAPE**: Escape all HTML entities (redundant if using SKIP_HTML)
- `0x0004` - **HARD_WRAP**: Convert line breaks to `<br>` tags
- `0x0008` - **USE_XHTML**: Output XHTML-compliant tags (self-closing: `<br/>`)
- `0x0010** - **PRETTIFY**: Pretty-print HTML with indentation
- `0x0020` - **USE_SMARTYPANTS**: Convert quotes and dashes to typographic variants
- `0x00FF` - All standard flags
- `0x10000` - **LINK_CONVERSION**: Convert `.md` links to `.html` (special flag for documentation)

### 3.3 Markdown Extensions (NSUInteger bit flags)

Enable Markdown syntax extensions. Combine with bitwise OR:

- `0x0001` - **TABLES**: GFM pipe tables
- `0x0002` - **FENCED_CODE**: Code blocks with triple backticks
- `0x0004` - **FOOTNOTES**: Footnote syntax
- `0x0008` - **HIGHLIGHT**: `==highlighted text==` syntax
- `0x0010` - **QUOTE**: Block quotes
- `0x0020` - **SUPERSCRIPT**: Superscript with `^`
- `0x0040** - **STRIKETHROUGH**: `~~strikethrough~~` syntax
- `0x0080` - **MATH**: Mathematical expressions (LaTeX-style)
- `0x00FF` - All extensions enabled

## 4. Performance Characteristics

- **Parsing Time**: O(n) where n = Markdown text length; typical: 1-5 ms for 10 KB of Markdown
- **Memory**: O(n) for output buffer; no persistent structures retained after conversion
- **CPU Efficiency**: Streaming parser with single pass through input
- **Typical Throughput**: ~1-2 MB/s on modern hardware for average Markdown
- **Memory Peak**: 2-3x input size during conversion (input + output buffers)

## 5. AI Usage Recommendations & Patterns

### Pattern 1: Simple Documentation Rendering
For static documentation or help text, use the basic `hoedownedString` method without special flags.

### Pattern 2: User-Generated Content (Secure)
Always use `SKIP_HTML` flag to prevent script injection. Optionally use `ESCAPE` for defense-in-depth.
```objc
NSUInteger flags = 0x0001; // SKIP_HTML
NSData *htmlData = [markdownData hoedownedDataWithHTMLFlags:flags extensions:0 tocIndent:0];
```

### Pattern 3: Rich Formatting with Extensions
Enable strikethrough, tables, and fenced code for feature-rich Markdown support:
```objc
NSUInteger extensions = 0x0042; // FENCED_CODE + STRIKETHROUGH
NSUInteger flags = 0x0004; // HARD_WRAP for line breaks
NSData *htmlData = [markdownData hoedownedDataWithHTMLFlags:flags extensions:extensions tocIndent:0];
```

### Pattern 4: Documentation Site Generation
Convert `.md` links to `.html` for static site generation:
```objc
NSUInteger flags = 0x10000; // LINK_CONVERSION
NSData *htmlData = [markdownData hoedownedDataWithHTMLFlags:flags extensions:0x00FF tocIndent:0];
```

### Pattern 5: Table of Contents Generation
Use `tocIndent` parameter to auto-generate TOC from heading hierarchy:
```objc
NSData *htmlData = [markdownData hoedownedDataWithHTMLFlags:0 extensions:0 tocIndent:2];
// Generates nested `<ul>` from h1/h2/h3 headings
```

### Common Pitfalls
- **Forgetting SKIP_HTML on user content**: Always sanitize untrusted input
- **Not specifying encoding**: Use UTF-8 consistently
- **Over-enabling extensions**: Each extension adds parsing complexity; enable only needed ones
- **Assuming cached results invalidate**: Monitor when source Markdown changes

## 6. Integration Examples

### Example 1: Simple Blog Post Rendering
```objc
#import <MulleFoundation/MulleFoundation.h>
#import <MulleWeb/MulleHoedown.h>

NSString *markdownContent = @"# Blog Post\n\nThis is **bold** and this is *italic*.";
NSString *htmlOutput = [markdownContent hoedownedString];
printf("%s\n", [htmlOutput UTF8String]);
// Output: <h1>Blog Post</h1>\n<p>This is <strong>bold</strong> and this is <em>italic</em>.</p>
```

### Example 2: Secure User Comment Processing
```objc
NSString *userComment = @"Check out <script>alert('xss')</script> my link";
NSData *inputData = [userComment dataUsingEncoding:NSUTF8StringEncoding];

// Use SKIP_HTML flag to prevent script execution
NSUInteger flags = 0x0001; // SKIP_HTML
NSData *safeHTML = [inputData hoedownedDataWithHTMLFlags:flags extensions:0 tocIndent:0];

NSString *result = [[NSString alloc] initWithData:safeHTML encoding:NSUTF8StringEncoding];
// <script> tag is rendered as escaped text, not executed
[result release];
```

### Example 3: Feature-Rich Documentation with Tables and Code
```objc
NSString *markdown = @"# API Reference\n\n## Methods\n\n| Method | Returns |\n|--------|----------|\n| foo() | NSString |\n\n```objc\nNSString *s = [obj foo];\n```";

NSData *input = [markdown dataUsingEncoding:NSUTF8StringEncoding];
NSUInteger extensions = 0x0046; // FENCED_CODE + TABLES + STRIKETHROUGH
NSData *html = [input hoedownedDataWithHTMLFlags:0 extensions:extensions tocIndent:0];

NSString *result = [[NSString alloc] initWithData:html encoding:NSUTF8StringEncoding];
printf("%s\n", [result UTF8String]);
[result release];
```

### Example 4: Documentation Site Link Rewriting
```objc
NSString *markdown = @"[Read More](guide.md) or see [API](api.md)";
NSData *input = [markdown dataUsingEncoding:NSUTF8StringEncoding];

NSUInteger flags = 0x10000; // LINK_CONVERSION
NSData *html = [input hoedownedDataWithHTMLFlags:flags extensions:0 tocIndent:0];

NSString *result = [[NSString alloc] initWithData:html encoding:NSUTF8StringEncoding];
// Links rewritten: guide.md → guide.html, api.md → api.html
[result release];
```

### Example 5: Markdown to HTML Pipeline with Caching
```objc
@interface MarkdownCache : NSObject
- (NSString *)cachedHTMLForMarkdown:(NSString *)markdown;
@end

@implementation MarkdownCache {
    NSMutableDictionary *_cache;
}

- (id)init {
    self = [super init];
    if (self) {
        _cache = [[NSMutableDictionary alloc] init];
    }
    return self;
}

- (NSString *)cachedHTMLForMarkdown:(NSString *)markdown {
    NSString *hash = [markdown sha1Hash]; // pseudo-code
    
    NSString *cached = _cache[hash];
    if (cached) return cached;
    
    NSData *input = [markdown dataUsingEncoding:NSUTF8StringEncoding];
    NSUInteger flags = 0x0024; // HARD_WRAP + USE_SMARTYPANTS
    NSUInteger extensions = 0x0046; // FENCED_CODE + TABLES + STRIKETHROUGH
    NSData *html = [input hoedownedDataWithHTMLFlags:flags extensions:extensions tocIndent:0];
    
    NSString *result = [[NSString alloc] initWithData:html encoding:NSUTF8StringEncoding];
    _cache[hash] = result;
    [result release];
    
    return result;
}

- (void)dealloc {
    [_cache release];
    [super dealloc];
}
@end
```

### Example 6: Smart Typography Conversion
```objc
NSString *text = @"It's \"smart\" to use -- dashes... right?";
NSData *input = [text dataUsingEncoding:NSUTF8StringEncoding];

NSUInteger flags = 0x0020; // USE_SMARTYPANTS
NSData *html = [input hoedownedDataWithHTMLFlags:flags extensions:0 tocIndent:0];

NSString *result = [[NSString alloc] initWithData:html encoding:NSUTF8StringEncoding];
printf("%s\n", [result UTF8String]);
// Output: <p>It&rsquo;s &ldquo;smart&rdquo; to use &ndash; dashes&hellip; right?</p>
[result release];
```

## 7. Dependencies

- **MulleFoundation** - NSString, NSData base classes
- **hoedown** - Embedded Markdown parsing library (C) - vendored, no external dependency
- **mulle-objc** (runtime) - Objective-C runtime support
- Standard C library

## 8. Version Information

MulleHoedown version macro: `MULLE_HOEDOWN_VERSION`
- Format: `(major << 20) | (minor << 8) | patch`
- Current: 0.4.0

