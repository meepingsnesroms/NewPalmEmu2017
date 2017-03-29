/*
  one2four.c

  (c) 1999 Till Harbaum
*/

#include <stdio.h>

main(void) {
  int i,j;
  unsigned long c;
  char f[4];

  for(i=0;i<256;i++) {
    for(c=0,j=0;j<8;j++) {
      c <<= 4;
      if(i & (1<<(7-j)))
	c |= 0x0f;
    }

    f[3]= (c>> 0)&0xff;
    f[2]= (c>> 8)&0xff;
    f[1]= (c>>16)&0xff;
    f[0]= (c>>24)&0xff;

    fwrite(&f, 1, 4, stdout);
  }
  
  fflush(stdout);
  return 0;
}
