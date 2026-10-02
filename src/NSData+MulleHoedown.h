//
//  NSData+MulleHoedown.h
//  MulleHoedown
//
//  Copyright (c) 2020 Nat! - Mulle kybernetiK.
//  Copyright (c) 2015 Mulle kybernetiK. All rights reserved.
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
#import "import.h"


/*
 * The MULLE_MARKDOWN_* flags and the markdowned... methods are the API shared
 * with MulleCMarkGFM, so source can be moved between the two. Each backend
 * renders with its own native rules, so the output is not meant to be
 * identical. They use the same numeric values as the HOEDOWN_* flags, so
 * either spelling can be passed to the conversion methods.
 *
 * The definitions are guarded, so a translation unit that includes both this
 * header and MulleCMarkGFM's can not get conflicting definitions.
 */
#ifndef MULLE_MARKDOWN_HTML_SKIP_HTML
# define MULLE_MARKDOWN_HTML_SKIP_HTML            (1UL << 0)
# define MULLE_MARKDOWN_HTML_ESCAPE               (1UL << 1)
# define MULLE_MARKDOWN_HTML_HARD_WRAP            (1UL << 2)
# define MULLE_MARKDOWN_HTML_USE_XHTML            (1UL << 3)
# define MULLE_MARKDOWN_HTML_USE_TASK_LIST        (1UL << 4)
# define MULLE_MARKDOWN_HTML_USE_EMOJI            (1UL << 5)

/* convert local markdown (.md) links to HTML links (.html) */
# define MULLE_MARKDOWN_HTML_LOCAL_LINKS          (1UL << 16)

/* document extensions */
# define MULLE_MARKDOWN_EXT_TABLES                (1UL << 0)
# define MULLE_MARKDOWN_EXT_FENCED_CODE           (1UL << 1)
# define MULLE_MARKDOWN_EXT_FOOTNOTES             (1UL << 2)
# define MULLE_MARKDOWN_EXT_AUTOLINK              (1UL << 3)
# define MULLE_MARKDOWN_EXT_STRIKETHROUGH         (1UL << 4)
# define MULLE_MARKDOWN_EXT_UNDERLINE             (1UL << 5)
# define MULLE_MARKDOWN_EXT_HIGHLIGHT             (1UL << 6)
# define MULLE_MARKDOWN_EXT_QUOTE                 (1UL << 7)
# define MULLE_MARKDOWN_EXT_SUPERSCRIPT           (1UL << 8)
# define MULLE_MARKDOWN_EXT_MATH                  (1UL << 9)
# define MULLE_MARKDOWN_EXT_EMOJI                 (1UL << 10)
# define MULLE_MARKDOWN_EXT_NO_INTRA_EMPHASIS     (1UL << 11)
# define MULLE_MARKDOWN_EXT_SPACE_HEADERS         (1UL << 12)
# define MULLE_MARKDOWN_EXT_MATH_EXPLICIT         (1UL << 13)
# define MULLE_MARKDOWN_EXT_DISABLE_INDENTED_CODE (1UL << 14)
# define MULLE_MARKDOWN_EXT_TAGFILTER             (1UL << 15)

# define MULLE_MARKDOWN_EXT_BLOCK \
   (MULLE_MARKDOWN_EXT_TABLES | MULLE_MARKDOWN_EXT_FENCED_CODE | \
    MULLE_MARKDOWN_EXT_FOOTNOTES)

# define MULLE_MARKDOWN_EXT_SPAN \
   (MULLE_MARKDOWN_EXT_AUTOLINK | MULLE_MARKDOWN_EXT_STRIKETHROUGH | \
    MULLE_MARKDOWN_EXT_UNDERLINE | MULLE_MARKDOWN_EXT_HIGHLIGHT | \
    MULLE_MARKDOWN_EXT_QUOTE | MULLE_MARKDOWN_EXT_SUPERSCRIPT | \
    MULLE_MARKDOWN_EXT_MATH | MULLE_MARKDOWN_EXT_EMOJI)

# define MULLE_MARKDOWN_EXT_GFM \
   (MULLE_MARKDOWN_EXT_TABLES | MULLE_MARKDOWN_EXT_STRIKETHROUGH | \
    MULLE_MARKDOWN_EXT_AUTOLINK | MULLE_MARKDOWN_EXT_FOOTNOTES | \
    MULLE_MARKDOWN_EXT_TAGFILTER)
#endif


@interface NSData( MulleHoedown)

/* the backend-neutral API shared with MulleCMarkGFM */
- (NSData *) markdownedData;

// add MULLE_MARKDOWN_HTML_LOCAL_LINKS on flags to convert local markdown
// (.md) links to HTML links (.html)
- (NSData *) markdownedDataWithHTMLFlags:(NSUInteger) flags
                              extensions:(NSUInteger) extensions
                               tocIndent:(NSUInteger) indent;

- (NSData *) hoedownedData;

// add 0x10000 on flags to convert local markdown (.md) links to HTML links
// (.html)
- (NSData *) hoedownedDataWithHTMLFlags:(NSUInteger) flags
                             extensions:(NSUInteger) extensions
                              tocIndent:(NSUInteger) indent;
@end

