## 0.6.0







* Document the backend-neutral `markdownedString`/`markdownedData` methods and their full-control variants in NSString and NSData categories.
* Document the ``MULLE_MARKDOWN_*`` HTML and extension flags as backend-neutral equivalents of the ``HOEDOWN_*`` flags.
* Note new HTML renderer flags `(`MULLE_MARKDOWN_HTML_USE_TASK_LIST`,` ``HOEDOWN_HTML_USE_TASK_LIST`)` and the ``mulle_hoedown_emoji_lookup`` utility.
* Clarify that the wrapped hoedown 3.0.1 parser is pre-CommonMark and document default extensions.




* Document the backend-neutral `markdownedString`/`markdownedData` methods and their full-control variants in NSString and NSData categories.
* Document the ``MULLE_MARKDOWN_*`` HTML and extension flags as backend-neutral equivalents of the ``HOEDOWN_*`` flags.
* Note new HTML renderer flags `(`MULLE_MARKDOWN_HTML_USE_TASK_LIST`,` ``HOEDOWN_HTML_USE_TASK_LIST`)` and the ``mulle_hoedown_emoji_lookup`` utility.
* Clarify that the wrapped hoedown 3.0.1 parser is pre-CommonMark and document default extensions.



feature: add backend-neutral markdown conversion API shared with MulleCMarkGFM

* new `markdownedString` and `markdownedData` methods on NSString and NSData
* flagged variants `markdownedStringWithHTMLFlags:extensions:tocIndent:` and `markdownedDataWithHTMLFlags:extensions:tocIndent:`
* new ``MULLE_MARKDOWN_HTML_*`` and ``MULLE_MARKDOWN_EXT_*`` flag constants, numerically compatible with the existing ``HOEDOWN_*`` flags so either spelling works
* source can now be moved between MulleHoedown and MulleCMarkGFM; each backend still renders with its own native rules, so output is not identical





* add GFM task lists and single tilde strikethrough (~text~)
* add backslash hard line breaks and space-required headers
* add curated emoji shortcodes (:smile:) as a new extension
* enable no-intra-word emphasis and single dollar math by default
* add per conversion HTML flags via hoedownedStringWithHTMLFlags:extensions:tocIndent:
* import hoedown 3.0.2-3.0.5 fixes for empty table cells, enclosing link angle brackets, codespans at end of input and inline callback rewind
* document that the parser is not CommonMark/GFM compliant
* add tests and expected output for all new behaviour


### 0.5.2



* add standard BSD license headers to all source files
* correct file header comments in src that wrongly said MulleScion instead of MulleHoedown
* move API docs from asset/dox/TOC.md to asset/dox/api/toc/index.md
* README now links to the API summary

### 0.5.1

Various small improvements
