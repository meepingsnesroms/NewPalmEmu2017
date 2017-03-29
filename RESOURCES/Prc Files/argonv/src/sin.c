/*
  sinus table generator

*/

#include <stdio.h>
#include <math.h>

main(void) {
  int  i;
  char z;

  for(i=0;i<256+64;i++) {
    z = 128 * sin((i * 2 * 3.1415926) / 256); 
    putchar(z);
  }
  return 0;
}
