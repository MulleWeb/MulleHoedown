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
#include "buffer.h"
#include "escape.h"
#include <string.h>


//#define READ_UNIT     1024
#define OUTPUT_UNIT   256


@implementation NSData( MulleHoedown)


// Custom link rendering function
// Custom link rendering function
static int
   custom_link_renderer( mulle_hoedown_buffer *ob,
                         const mulle_hoedown_buffer *content,
                         const mulle_hoedown_buffer *link,
                         const mulle_hoedown_buffer *title,
                         const mulle_hoedown_renderer_data *data)
{
   struct mulle_hoedown_buffer *new_link;
   size_t link_size;
   int is_local;

   if (!link || !link->size)
      return(0);

   link_size = link->size;
   is_local  = (strstr((char *)link->data, "://") == NULL);

   new_link = mulle_hoedown_buffer_new(64);

   if (is_local && link_size > 3 && strncmp((char *)link->data + link_size - 3, ".md", 3) == 0)
   {
      mulle_hoedown_buffer_put(new_link, link->data, link_size - 3);
      mulle_hoedown_buffer_puts(new_link, ".html");
   }
   else
   {
      mulle_hoedown_buffer_put(new_link, link->data, link_size);
   }

   HOEDOWN_BUFPUTSL(ob, "<a href=\"");
   mulle_hoedown_escape_href(ob, new_link->data, new_link->size);
   HOEDOWN_BUFPUTSL(ob, "\"");

   if (title && title->size)
   {
      HOEDOWN_BUFPUTSL(ob, " title=\"");
      mulle_hoedown_escape_html(ob, title->data, title->size, 0);
      HOEDOWN_BUFPUTSL(ob, "\"");
   }

   HOEDOWN_BUFPUTSL(ob, ">");
   if (content && content->size)
   {
      mulle_hoedown_buffer_put(ob, content->data, content->size);
   }
   HOEDOWN_BUFPUTSL(ob, "</a>");

   mulle_hoedown_buffer_free(new_link);

   return(1);
}

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

   renderer = mulle_hoedown_html_renderer_new( flags & 0xFFFF, indent); // HOEDOWN_HTML_SKIP_HTML, 0);
   if( flags & 0x10000)
      renderer->link = custom_link_renderer;

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
   return( [self hoedownedDataWithHTMLFlags:0x10000
                                 extensions:HOEDOWN_EXT_BLOCK|HOEDOWN_EXT_SPAN
                                  tocIndent:0]);
}


@end

