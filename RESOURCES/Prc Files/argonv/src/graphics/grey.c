/*
  grey.c  image converter tool for 'Argon V'

  T.Harbaum@tu-bs.de - http://www.ibr.cs.tu-bs.de/~harbaum/pilot

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

*/

#include <stdio.h>

#define MAGIC 0x4d42

#pragma pack(1)

struct bmp16_hdr {
  unsigned short magic;
  unsigned short dummy0[4];
  unsigned long  offset;
  unsigned short dummy4[2];
  unsigned long  width, height;
  unsigned short dummy1;
  unsigned short bpp;
  unsigned long  dummy2;
  unsigned long  length;
  unsigned long  dummy3[2];
  unsigned long  colors;
  unsigned long  colors2;
};

struct color {
  unsigned char r,g,b,x;
};

#pragma pack(4)

int
main(int argc, char *argv[]) {
  FILE   *in, *out;
  struct bmp16_hdr bmphdr;
  struct color colors[256], col;
  int i, j, x, y, shade[256], width, height;
  unsigned char *pixels;

  if(argc!=3) {
    puts("usage: grey infile outfile");
    exit(1);
  }

  if((in = fopen(argv[1], "rb"))==0) {
    puts("unable to open input file");
    exit(1);
  }

  if((out = fopen(argv[2], "wb"))==0) {
    puts("unable to open output file");
    exit(1);
  }

  fread(&bmphdr, sizeof(struct bmp16_hdr), 1l, in);
  width  = bmphdr.width;
  height = bmphdr.height;

  /* this doesn't work on big endian, but the rest doesn't either */
  if(bmphdr.magic != MAGIC) {
    puts("illegal bitmap header magic");
    exit(1);
  }

  /* verify pixel depth */
  if(bmphdr.bpp!=8) {
    printf("illegal bitmap depth %d (8 bits required)\n", bmphdr.bpp);
    exit(1);
  }

  /* verify width */
  if((width&7) != 0) {
    printf("illegal bitmap width %d (multiple of 8 bits required)\n", width);
    exit(1);
  }

  printf("source: %d colors, mapping to 4 bit static map\n", bmphdr.colors);

  /* read colors */
  fread(colors, bmphdr.colors, sizeof(struct color), in);

  for(i=0;i<bmphdr.colors;i++) {
    /* calculate color assignment */
    shade[i] = ((colors[i].r + colors[i].g + colors[i].b)*15)/(3*0xf0);
  }

  /* write new header */
  bmphdr.colors = bmphdr.colors2 = 16;
  bmphdr.length += bmphdr.height*4;
  bmphdr.offset = sizeof(struct bmp16_hdr)+bmphdr.colors*sizeof(struct color);
  bmphdr.width += 2;
  fwrite(&bmphdr, sizeof(struct bmp16_hdr), 1l, out);

  /* write static colors */
  for(i=0;i<bmphdr.colors;i++) {
    if(i<16) col.r = col.g = col.b = i * 0x11;
    else     col.r = col.g = col.b = 0;

    col.x = 0;
    fwrite(&col, sizeof(struct color), 1l, out);
  }

  /* scan picture */
  for(y=0;y<height;y++) {
    for(x=0;x<width;x++)
      fputc(shade[fgetc(in)], out);

    if(height-y<32) { 
      fputc( (15-((height-y)/2)),out);
      fputc( (15-((height-y)/2)),out);
    } else {           
      fputc(0,out);
      fputc(0,out);
    }

    fputc(0,out);
    fputc(0,out);
  }
  
  fclose(in);
  fclose(out);
  exit(0);
}
