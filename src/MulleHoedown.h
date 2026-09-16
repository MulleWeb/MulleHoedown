//
//  MulleHoedown.h
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
#import "NSData+MulleHoedown.h"
#import "NSString+MulleHoedown.h"

/*
 * MulleHoedown wraps hoedown 3.0.1, a pre-CommonMark Markdown parser that
 * Mulle kybernetiK extended and maintains.
 *
 * IMPORTANT: This is NOT a CommonMark or GitHub Flavored Markdown compliant
 * parser. It predates the CommonMark specification and its output can differ
 * from reference implementations for, among other things, emphasis and
 * strong emphasis, intraword underscores, list syntax, link destinations and
 * HTML blocks. Do not rely on byte-for-byte compatibility with GitHub or with
 * a CommonMark reference implementation.
 *
 * The following extensions are enabled by default: tables, fenced code,
 * footnotes, autolinks, strikethrough (~~ and ~), underline, highlight,
 * quote, superscript, math, emoji, no intra-word emphasis and space-required
 * headers. The HTML renderer additionally supports GFM task lists.
 *
 * Callers that need different rendering can select raw HTML handling and
 * other HTML renderer flags per conversion with the
 * hoedownedDataWithHTMLFlags:extensions:tocIndent: and
 * hoedownedStringWithHTMLFlags:extensions:tocIndent: methods.
 */

#define MULLE_HOEDOWN_VERSION ((0UL << 20) | (5 << 8) | 2)


#ifdef __has_include
# if __has_include( "_MulleHoedown-versioncheck.h")
#  include "_MulleHoedown-versioncheck.h"
# endif
#endif
