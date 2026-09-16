#import <MulleHoedown/MulleHoedown.h>


int   main( void)
{
   mulle_printf( "%@\n", [@"Text with a footnote.[^footnote]\n\n[^footnote]: The footnote text.\n" hoedownedString]);
   return( 0);
}
