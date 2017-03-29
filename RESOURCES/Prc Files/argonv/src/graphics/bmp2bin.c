/*
  bmp2bin.c  image converter tool for 'Argon V'

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
  unsigned short dummy0[8];
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
  struct color colors[256];
  int i, j, colass[256], used[256], x, y, mask, colcnt, pwid, white;
  unsigned char *imgsrc, p;

  if(argc!=3) {
    puts("usage: bmp2bin infile outfile");
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

  /* this doesn't work on big endian, but the rest doesn't either */
  if(bmphdr.magic != MAGIC) {
    puts("illegal bitmap header magic");
    exit(1);
  }

  /* verify picture height */  
  if((bmphdr.width != bmphdr.height+2)&&
     ((bmphdr.width!=194)||(bmphdr.height!=160))) {
    if(bmphdr.width != 2*(bmphdr.height+2)) {
      printf("illegal bitmap size (%dx%d)\n", bmphdr.width, bmphdr.height);
      exit(1);
    } else {
      printf("converting with mask %dx%d\n", (bmphdr.width/2)-2, bmphdr.height);
      mask = 1;
    }
  } else
    mask = 0;
  
  /* pixel depth */
  if(bmphdr.bpp!=8) {
    printf("illegal picture depth %d\n", bmphdr.bpp);
    exit(1);
  }

  /* read colors */
  fread(colors, bmphdr.colors, sizeof(struct color), in);

  for(i=0;i<bmphdr.colors;i++) used[i]=0;

  for(colcnt=0,i=0;i<bmphdr.colors;i++) {

    /* calculate color assignment */
    j = ((colors[i].r + colors[i].g + colors[i].b)*15)/(3*0xf0);
    if(j>15) { puts("alarm"); exit(1); }
    
    if(!used[j]) colcnt++;

    colass[i] = j;
    used[j] = 1;

    if(j==15) white=i;
  }

  if(colcnt>16) {
    printf("too many colors in use (%d)\n", colcnt);
    exit(1);
  }

  pwid = (bmphdr.width+3)&~3;

  imgsrc = (unsigned char*)malloc(pwid*bmphdr.height);
  fread(imgsrc, pwid*bmphdr.height, 1l, in);

  if(!mask) {
    /* scan plain picture */
    for(y=0;y<bmphdr.height;y++) {
      for(x=0;x<(bmphdr.width-2)/2;x++) {
	
	/* get two pixels */
	i = imgsrc[((bmphdr.length/bmphdr.height)* (bmphdr.height-1-y)) + 2*x];
	j = imgsrc[((bmphdr.length/bmphdr.height)* (bmphdr.height-1-y)) + 2*x+1];
	
	/* write them into one byte */
	fputc(~((colass[i]<<4)|(colass[j])), out);
      }
    }
  } else {
    /* scan picture with mask */
    for(y=0;y<bmphdr.height;y++) {

      /* scan mask */
      for(p=0,x=0;x<(bmphdr.width-4)/4;x++) {

	/* get two pixels */
	i = imgsrc[(pwid * (bmphdr.height-1-y)) + 
		  2*x   + bmphdr.width/2];
	j = imgsrc[(pwid * (bmphdr.height-1-y)) + 
		  2*x+1 + bmphdr.width/2];

	if(((colass[i]!=0)&&(colass[i]!=15)) ||
	   ((colass[j]!=0)&&(colass[j]!=15))) {
	  printf("illegal color in mask\n");
	  exit(1);
	}

	/* write them into one byte */
	p <<= 2;
	if(!colass[i]) p |= 2;
	if(!colass[j]) p |= 1;

	if((x&3) == 3) {
	  /* write mask byte */
	  fputc(p, out);
	  p=0;
	}
      }

      /* scan image */
      for(x=0;x<(bmphdr.width-4)/4;x++) {

	/* get two pixels */
      	i = imgsrc[(pwid * (bmphdr.height-1-y)) + 2*x];
    	j = imgsrc[(pwid * (bmphdr.height-1-y)) + 2*x+1];
	
	/* verify mask */
	if(colass[imgsrc[(pwid * (bmphdr.height-1-y)) + 
			2*x   + bmphdr.width/2]] == 15) i = white;
	  
	if(colass[imgsrc[(pwid * (bmphdr.height-1-y)) + 
			2*x+1 + bmphdr.width/2]] == 15) j = white;
	  
	/* write them into one byte */
	fputc(~((colass[i]<<4)|(colass[j])), out);
      }
    }
  }

  free(imgsrc);
  
  fclose(in);
  fclose(out);
  exit(0);
}
