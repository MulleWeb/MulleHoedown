#import <MulleHoedown/MulleHoedown.h>
#import <MulleHoedown/html.h>


int   main( void)
{
   mulle_printf( "%@\n",
      [@"<b>raw</b> <script>x</script>\n"
         hoedownedStringWithHTMLFlags:HOEDOWN_HTML_ESCAPE
                            extensions:0
                             tocIndent:0]);
   return( 0);
}
