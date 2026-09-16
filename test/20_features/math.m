#import <MulleHoedown/MulleHoedown.h>


int   main( void)
{
   mulle_printf( "%@\n", [@"inline $x^2$ and display $$y_1$$\n" hoedownedString]);
   return( 0);
}
