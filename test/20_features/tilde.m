#import <MulleHoedown/MulleHoedown.h>


int   main( void)
{
   mulle_printf( "%@\n", [@"~single~ and ~~double~~ and foo~bar~baz\n" hoedownedString]);
   return( 0);
}
