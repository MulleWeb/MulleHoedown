#import <MulleHoedown/MulleHoedown.h>


int   main( void)
{
   mulle_printf( "%@\n", [@"[a](foo>) and [b](<bar) and [c](<b c>)\n" hoedownedString]);
   return( 0);
}
