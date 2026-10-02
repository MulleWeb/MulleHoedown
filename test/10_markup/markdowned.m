#import <MulleHoedown/MulleHoedown.h>


int   main( void)
{
   printf( "%s\n", [[@"# Headline" markdownedString] UTF8String]);
   return( 0);
}
