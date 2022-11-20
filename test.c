#include <stdio.h>
int main( ) {

   int c;

   printf( "Enter a value :");
   c = getchar( );

   if(c == '\n') {
    printf( "\nYou entered %d: ", c);
    main();
   } else {
    printf( "\nYou entered %d: ", c);
    putchar( c );
   }


   return 0;
}