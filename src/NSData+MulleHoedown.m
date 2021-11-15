//
//  NSData+MulleHoedown.m
//  MulleScion
//
//  Created by Nat! on 17.02.15.
//  Copyright (c) 2015 Mulle kybernetiK. All rights reserved.
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
#import "NSData+MulleHoedown.h"

#include "document.h"
#include "html.h"


//#define READ_UNIT     1024
#define OUTPUT_UNIT   256


@implementation NSData( MulleHoedown)

- (NSData *) hoedownedDataWithHTMLFlags:(NSUInteger) flags
                             extensions:(NSUInteger) extensions
                              tocIndent:(NSUInteger) indent
{
   struct mulle_hoedown_buffer   *ob;
   mulle_hoedown_renderer        *renderer;
   mulle_hoedown_document        *document;
   NSData                        *data;

   /* performing markdown parsing */
   ob = mulle_hoedown_buffer_new( OUTPUT_UNIT);

   renderer = mulle_hoedown_html_renderer_new( flags, indent); // HOEDOWN_HTML_SKIP_HTML, 0);
   document = mulle_hoedown_document_new( renderer,
                                          extensions,
                                          16);

   mulle_hoedown_document_render( document, ob, [self bytes], [self length]);

   data = [[[NSData alloc] initWithBytesNoCopy:ob->data
                                        length:ob->size
                                  freeWhenDone:YES] autorelease];
   ob->data = NULL;
   ob->size = 0;

   mulle_hoedown_document_free( document);
   mulle_hoedown_html_renderer_free( renderer);
   mulle_hoedown_buffer_free( ob);

   return( data);
}


- (NSData *) hoedownedData
{
   return( [self hoedownedDataWithHTMLFlags:0
                                 extensions:HOEDOWN_EXT_BLOCK|HOEDOWN_EXT_SPAN
                                  tocIndent:0]);
}


@end

