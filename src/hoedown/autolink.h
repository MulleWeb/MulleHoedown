//
//  autolink.h
//  MulleHoedown
//
//  Copyright (c) 2015 Nat! - Mulle kybernetiK.
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
