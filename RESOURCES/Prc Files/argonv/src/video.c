/*
  video.c - (c) 1999 by Till Harbaum

  4 bits per pixel video routines for ArgonV

  T.Harbaum@tu-bs.de - http://www.ibr.cs.tu-bs.de/~harbaum/pilot

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

*/

#include <PalmOS.h>
#include <PalmCompatibility.h>

#include "video.h"
#include "argonv.h"
#include "graphics.h"

#define CHECK   // define for some internal checks

#define VIDEO_WIDTH  192u
#define VIDEO_HEIGHT 192u
#define VIDEO_BUFFER (VIDEO_HEIGHT*(VIDEO_WIDTH/2))

char *video_base = NULL, *draw_base;
void *video_old_base = NULL;
unsigned char lpxcd;

/* hardware allows direct video access */
Boolean direct_video;
BitmapType *offscreen_bitmap;

/* register for direct video hardware access on OS 3.1 */
#define LSSA  *((         void **)0xFFFFFA00)
#define VPW   *((unsigned char  *)0xFFFFFA05)
#define LYMAX *((unsigned short *)0xFFFFFA0A)
#define LCXP  *((unsigned short *)0xFFFFFA18)
#define LCYP  *((unsigned short *)0xFFFFFA1A)
#define LCWCH *((unsigned short *)0xFFFFFA1C)
#define LBLCK *((unsigned char  *)0xFFFFFA1F)
#define PICF  *((unsigned char  *)0xFFFFFA20)
#define LPXCD *((unsigned char  *)0xFFFFFA25)
#define CKCON *((unsigned char  *)0xFFFFFA27)
#define LLBAR *((unsigned char  *)0xFFFFFA29)
#define LPOSR *((unsigned char  *)0xFFFFFA2D)
#define FRCM  *((unsigned char  *)0xFFFFFA31)
#define LGPMR *((unsigned short *)0xFFFFFA32)

// size of level
#define LLENGTH  (50)             // length in screens (identical to argoned)
#define LENGTH   (LLENGTH*10)     // length in tiles
#define BSIZE    (LENGTH*10)      // buffer size
#define BEXTRA   (11*10)          // extra buffer
#define BTOTAL   (BSIZE+2*BEXTRA) // total buffer size
#define FG_LINES (LENGTH+10)      // length + 2*10 - 11

// image buffer
unsigned char foreground_state[BTOTAL];   /* tile state information */
unsigned char foreground_data[BTOTAL];    /* level data             */

#define PalmOS30   sysMakeROMVersion(3,0,0,sysROMStageRelease,0)
#define PalmOS35   sysMakeROMVersion(3,5,0,sysROMStageRelease,0)

static Boolean VideoDirect(void) {
  DWord id, chip;
  Err err;

  /* CPU type detection code from Geoff Richmond */
  err = FtrGet(sysFtrCreator, sysFtrNumProcessorID, &id);
  if (err) return false;
  chip = id & sysFtrNumProcessorMask;
  if(chip != sysFtrNumProcessorEZ) return false;

  /* set new video base address */
  if((video_base = MemPtrNew(VIDEO_BUFFER)) == NULL) {
    FrmCustomAlert(alt_err,"Out of memory allocating video buffer.",0,0);
    return false;
  }

  /* save old video base */
  video_old_base = LSSA;

  /* save old refresh value and set to full refresh */
  lpxcd = LPXCD;
  LPXCD = 0;

  CKCON &= ~0x80; /* display off */

  /* virtual page width now 80 bytes (160 greyscale pixels) */
  VPW   = 40;
  PICF |= 0x02;      /* switch to 4 bit grayscale mode */
  LLBAR = 40;        /* line buffer now 80 bytes */

  /* register to control grayscale pixel oscillations */
  FRCM = 0xB9;
  
  LSSA = video_base;
  
  /* let the LCD get to a 2 new frames (40ms delay) */
  SysTaskDelay(4);
  
  /* switch LCD back on */
  CKCON |= 0x80;

  return true;
}


void VideoAnimateForeground(int start) {
  int i, a=0;
  static cnt=0;
  unsigned long r = SysRandom(0);

  for(i=start;i<(start+110);i++) {

    /* electro flash */
    if(foreground_state[i] == 1) {
      if(cnt&0x1c) foreground_data[i]=0;
      else {
	foreground_data[i] = FG_FLASH0+(r&3);
	r >>= 2;
	a++;
      }
    }

    /* reload randomizer */
    if(a==16) {
      r = SysRandom(0);
      a = 0;
    }
  }
  cnt++;
}

/* information about locked resources */
struct LockedRsc {
  Handle ResH;
  unsigned long *ResP;
};

/* save buffer for locked resoures */
struct LockedRsc  BackRsc[GRAPHIC_BACK];
struct LockedRsc  ImagRsc[GRAPHIC_IMAG];
struct LockedRsc  SprtRsc[GRAPHIC_SPRT];
struct LockedRsc  FontRsc, ConvRsc, CSinRsc, LevlRsc;

/* sin and cos to export */
char *VideoSin, *VideoCos;

Boolean LockRsc(struct LockedRsc *LRsc, int len, unsigned long type) {
  int i;

  for(i=0;i<len;i++) {
    LRsc[i].ResH = (Handle)DmGetResource( type, i);
#ifdef CHECK
    if(!LRsc[i].ResH) {
      PRINTF("rsc err %s %d", &type, i);
      return false;
    }
#endif    
    LRsc[i].ResP = MemHandleLock((VoidHand)LRsc[i].ResH);
  }
  return true;
}

void UnlockRsc(struct LockedRsc *LRsc, int len) {
  int i;

  for(i=0;i<len;i++) {
    MemPtrUnlock(LRsc[i].ResP);
    DmReleaseResource((VoidHand) LRsc[i].ResH );
  }
}

Boolean VideoRscInit(void) {
  if(!LockRsc( BackRsc, GRAPHIC_BACK, 'back')||    // background image
     !LockRsc( ImagRsc, GRAPHIC_IMAG, 'imag')||    // foreground tiles
     !LockRsc( SprtRsc, GRAPHIC_SPRT, 'sprt')||    // sprite
     !LockRsc(&FontRsc,            1, 'font')||    // computer font
     !LockRsc(&ConvRsc,            1, 'conv')||    // 1->4 bit conversion
     !LockRsc(&CSinRsc,            1, 'csin')||    // sinus table
     !LockRsc(&LevlRsc,            1, 'levl'))     // level data
     return false;

  VideoSin = (char*)CSinRsc.ResP;
  VideoCos = (char*)CSinRsc.ResP + 64;

  return true;
}

void VideoInitLevel(void) {
  int i;

  char *s = (char*)LevlRsc.ResP;
  char *d = foreground_data;
  char *k = foreground_state;

  /* top of buffer */
  for(i=0;i<BEXTRA;i++)
    *d++ = *k++ = 0;

  /* init foreground state buffer */
  for(i=0;i<BSIZE;i++) {

    if((*s>=FG_FLASH0)&&(*s<=FG_FLASH3)) {
      *k++ = 1;  /* state 1 = blizzard */
    } else
      *k++ = 0;

    *d++ = *s++;
  }

  /* bottom of buffer */
  for(i=0;i<BEXTRA;i++)
    *d++ = *k++ = 0;
}

void VideoRscRelease(void) {
  UnlockRsc( BackRsc, GRAPHIC_BACK);
  UnlockRsc( ImagRsc, GRAPHIC_IMAG);
  UnlockRsc( SprtRsc, GRAPHIC_SPRT);
  UnlockRsc(&FontRsc,            1);
  UnlockRsc(&ConvRsc,            1);
  UnlockRsc(&CSinRsc,            1);
  UnlockRsc(&LevlRsc,            1);
}

void VideoDrawText(int x, int y, unsigned char *str) {
  unsigned long *dst= ((unsigned long*)draw_base)+ 2 + y*24 + x;
  unsigned long *d, *conv = (unsigned long*)ConvRsc.ResP;
  int i;
  unsigned char *s;

  while(*str!=0) {
    d = dst;
    s = &(((unsigned char*)FontRsc.ResP) [8 * *str]);
    
    for(i=0;i<8;i++) {
      *d |= conv[*s++];
      d  += 24;
    }
  
    str++;
    dst++;
  }
}

void VideoDrawPartialText(int x, int y, unsigned char *str, 
			  int xbeg, int xend, int ybeg, int yend) {

  unsigned long *dst= ((unsigned long*)draw_base)+ 2 + (ybeg+y)*24 + x + xbeg;
  unsigned long *d, *conv = (unsigned long*)ConvRsc.ResP;
  int i, n = xend - xbeg;
  unsigned char *s;

  str+=xbeg;

  while((*str!=0)&&(n-->=0)) {
    d = dst;
    s = &(((unsigned char*)FontRsc.ResP) [8 * *str + ybeg]);
    
    for(i=ybeg;i<=yend;i++) {
      *d |= conv[*s++];
      d  += 24;
    }
  
    str++;
    dst++;
  }
}

#ifdef ASM
asm("
.globl VideoDrawSprite
VideoDrawSprite:
	movem.l %d3-%d7/%a2-%a3/%a6,-(%sp)

	move.w 38(%sp),%d1           | Y
	muls.w #96,%d1               | 48*Y
	add.l draw_base@END.w(%a5),%d1 | drawbase+48*2*Y

        move.w 36(%sp),%d2           | X
	move.w %d2,%d0
	asr.w #2,%d0                 | /4
	move.w %d0,%a0
	add.l %a0,%a0                | *2

	lea (%a0,%d1.l),%a3          | dest addr0

	move.w 40(%sp),%d0
	asl.w #3,%d0                 | sprite no * 8

	lea SprtRsc@END.w(%a5),%a0
	move.l 4(%a0,%d0.w),%a1      | addr of sprite data

	lea ConvRsc@END.w(%a5),%a0
	move.l 4(%a0),%a6            | conversion table

	move.w %d2,%d4
	and.w #3,%d4
	asl.w #2,%d4                 | xoffset

	moveq.l #32,%d3
	sub.w %d4,%d3                | 32-(xoffset)

        move.w #15,%d6               | line counter

spr_next_line:
        tst.w (%a1)                  | test mask
        beq.s spr_skip               | skip this line

        clr.w  %d0
	move.b (%a1)+,%d0            | 8 bit mask
        asl.w #2,%d0
	move.l (%a6,%d0.w),%d1       | 8->32 bits

	clr.w %d0
	move.b (%a1)+,%d0            | next 8 bits
	asl.w #2,%d0
	move.l (%a6,%d0.w),%d2       | 8->32 bits

	move.l %d1,%d0
	lsr.l %d4,%d0                | shift mask
	not.l %d0
	and.l %d0,(%a3)              | dest &= ~(mask1>>xoffset)

	asl.l %d3,%d1                | <<
	move.l %d2,%d0               | mask2
	lsr.l %d4,%d0                | >>xoffset
	or.l %d0,%d1
	not.l %d1                    | ~
	and.l %d1,4(%a3)             | write

	asl.l %d3,%d2                | <<(32-xoffset)
	not.l %d2                    | ~
	and.l %d2,8(%a3)             | write

	move.l (%a1)+,%d1            | read sprite image
	move.l (%a1)+,%d2            | dito

	move.l %d1,%d0
	lsr.l %d4,%d0
	or.l %d0,(%a3)+              | shift data 1

	asl.l %d3,%d1
	move.l %d2,%d0
        lsr.l %d4,%d0
	or.l %d0,%d1
	or.l %d1,(%a3)+              | shift data 2

	asl.l %d3,%d2
	or.l %d2,(%a3)+              | shift data 3

	add.w #84,%a3                | next dest line

	dbra %d6, spr_next_line      | process next line
spr_end:
	movem.l (%sp)+,%d3-%d7/%a2-%a3/%a6
	rts

spr_skip:
        add.w #10,%a1
	add.w #96,%a3                | next dest line

	dbra %d6, spr_next_line      | process next line
        bra.s spr_end

");
#else
void VideoDrawSprite(int x, int y, int spr) {
  int i;
  unsigned long  *d, s, m0,m1;
  unsigned short *dest = ((unsigned short*)draw_base) + 48*y + x/4;
  void *src  = SprtRsc[spr].ResP;
  unsigned long *conv = (unsigned long*)ConvRsc.ResP;

  int n = (x&3)<<2;
  int m = 32 - n;

  for(i=0;i<16;i++) {
    d = (unsigned long*)dest;

    /* process four words per line */

    /* get mask */
    m0 = (unsigned long)conv[*((unsigned char*)src)++];
    m1 = (unsigned long)conv[*((unsigned char*)src)++];
    *(d+0) &= ~ (m0 >> n);
    *(d+1) &= ~((m0 << m)|(m1 >> n));
    *(d+2) &= ~ (m1 << m);

    /* get data */
    m0 = *((unsigned long*)src)++;
    m1 = *((unsigned long*)src)++;
    *(d+0) |=  (m0 >> n);
    *(d+1) |= ((m0 << m)|(m1 >> n));
    *(d+2) |=  (m1 << m);

    dest += 96/sizeof(unsigned short);
  }
}
#endif

/* collision with background object */
Boolean VideoHitBg(int index) {

  /* foregound_data[nnnn-1] == graphics/imagnnnn_gr.gif */
  switch(foreground_data[index]) {

    /* electro fizzle */
  case 0x06:
  case 0x07:
  case 0x08:
  case 0x09:
    damage(DAMAGE_FIZZLE);      /* damage ship */
    return false;   /* no wall contact (don't push ship) */
    break;
    
    /* boni (just collect) */
  case 0x0a: /* triangle (shot increase) */
    shot_mode++;
    if(shot_mode > SHOT_TRIPLE) shot_mode = SHOT_TRIPLE;
    else new_message("New Weapon");
    goto bonus_remove;
  case 0x0b: /* circle (shield reload) */
    new_message("Shields up");
    damage(DAMAGE_RELOAD);
    goto bonus_remove;
  case 0x0c: /* dot (bonus score) */
    score_inc(SCORE_100);
    new_message("Bonus score");
    goto bonus_remove;
  case 0x0d: /* star (faster shot) */
    shot_reload++;
    if(shot_reload > 2) shot_reload = 2;
    new_message("Fast shot");
    goto bonus_remove;
  case 0x0e: /* 's' (restart here) */
    new_message("Restart here");
    ship_save_position();
    goto bonus_remove;

bonus_remove:
    foreground_data[index] = 0x00;  /* remove bonus tile */
    return false;
    break;
  }

  /* hit something else: e.g. wall */
  return true;
}

/* this routine is ugly (but working) and might need to be replaced ... */
Boolean VideoSpriteBgCollide(unsigned int ypos, int x, int y, int s) {
  int i,k;
  int xo, yo, n, m;
  unsigned short *smask, *imask;

  /* sprite touches at most 4 background tiles */

  xo = x&0x0f;               /* x pos within block */
  yo = ypos&0x0f;            /* y pos within scroll pos block */

  /* calculate foreground buffer index of left top tile */
  k = 10*(FG_LINES-(ypos/16)%FG_LINES)+ 10*((y-yo)/16) + ((x-16)/16);

  yo = (y-yo)&0x0f;          /* y pos within block */

  smask = (unsigned short*)SprtRsc[s].ResP;   /* Pointer to sprite mask */

  /* sprite spans exactly one row */
  if(xo==0) {
    /* sprite spans exactly one line */

    if((m = foreground_data[k]) !=0) {
      imask = ((unsigned short*)ImagRsc[m-1].ResP) + 5*yo;
      
      /* just compare masks */
      for(n=yo;n<16;n++) {
	if(((*imask) & (*smask)) != 0)
	  if(VideoHitBg(k)) return true;   /* hit the wall? return true */

	imask += 5; smask += 5;
      }
    } else
      smask += (16-yo)*5;  /* just skip first block */

    /* were all lines in this first block? (sprite and bg are aligned) */
    if(yo!=0) {
      /* nope -> handle block below */
      if((m = foreground_data[k+10]) !=0) {
	imask = (unsigned short*)ImagRsc[m-1].ResP;

	/* just compare masks */
	for(n=0;n<yo;n++) {
	  if(((*imask) & (*smask)) != 0) 
	    if(VideoHitBg(k+10)) return true;

	  imask += 5; smask += 5;
	}
      }
    }
  } else {
    /* sprite overlaps several columns */

    /* check left row top */
    if((m = foreground_data[k]) !=0) {
      imask = ((unsigned short*)ImagRsc[m-1].ResP) + 5*yo;
      
      /* just compare masks */
      for(n=yo;n<16;n++) {
	if((*imask & ((*smask)>>xo)) != 0) 
	  if(VideoHitBg(k)) return true;

	imask += 5; smask += 5;
      }
    } else
      smask += (16-yo)*5;

    /* check left row bottom */
    if(yo!=0) {
      if((m = foreground_data[k+10]) !=0) {
	imask = (unsigned short*)ImagRsc[m-1].ResP;
      
	/* just compare masks */
	for(n=0;n<yo;n++) {
	  if((*imask & ((*smask)>>xo)) != 0) 
	    if(VideoHitBg(k+10)) return true;

	  imask += 5; smask += 5;
	}
      }
    }

    /* reload sprite pointer */
    smask = (unsigned short*)SprtRsc[s].ResP;   /* Pointer to sprite mask */
    xo = 16-xo;

    /* check right row top */
    if((m = foreground_data[k+1]) !=0) {
      imask = ((unsigned short*)ImagRsc[m-1].ResP) + 5*yo;
      
      /* just compare masks */
      for(n=yo;n<16;n++) {
	if((*imask & ((*smask)<<xo)) != 0) 
	  if(VideoHitBg(k+1)) return true;

	imask += 5; smask += 5;
      }
    } else
      smask += (16-yo)*5;

    /* check right row bottom */
    if(yo!=0) {
      if((m = foreground_data[k+11]) !=0) {
	imask = (unsigned short*)ImagRsc[m-1].ResP;
      
	/* just compare masks */
	for(n=0;n<yo;n++) {
	  if((*imask & ((*smask)<<xo)) != 0) 
	    if(VideoHitBg(k+11)) return true;

	  imask += 5; smask += 5;
	}
      }
    }
  }
  return false;
}

Boolean VideoSpriteCollide(int x1, int y1, int s1, int x2, int y2, int s2) {
  int xdiff, ydiff;
  unsigned short *mask1, *mask2;
  int n;

  /* handle vertical intersection */
  if(y2>y1) {                        // sprite 2 is lower
    ydiff = y2-y1;
    if(ydiff >= 16) return false;    // sprites don't overlap
    mask1 = &(((unsigned short*)SprtRsc[s1].ResP)[5*ydiff]);
    mask2 =    (unsigned short*)SprtRsc[s2].ResP;
  } else {                           // sprite 1 is lower
    ydiff = y1-y2;
    if(ydiff >= 16) return false;    // sprites don't overlap
    mask1 =    (unsigned short*)SprtRsc[s1].ResP;
    mask2 = &(((unsigned short*)SprtRsc[s2].ResP)[5*ydiff]);
  }

  /* handle horizontal intersection */
  if(x2>x1) {
    xdiff = x2-x1;
    if(xdiff >= 16) return false;    // sprites don't overlap

    for(n=0;n<(16-ydiff);n++) {
      if((( *mask2 >> xdiff ) & *mask1) ) return true;  // hit

      mask1 += 5;
      mask2 += 5;
    }

  } else {
    xdiff = x1-x2;
    if(xdiff >= 16) return false;    // sprites don't overlap

    for(n=0;n<(16-ydiff);n++) {
      if((( *mask1 >> xdiff ) & *mask2) ) return true;  // hit

      mask1 += 5;
      mask2 += 5;
    }
  }
  return false;
} 

#ifdef ASM
asm("
.globl VideoFgLine
VideoFgLine:
	movem.l %d4-%d6/%a2-%a3,-(%sp)
	move.l 24(%sp),%d6            | destination address
	move.w 28(%sp),%d5            | offset of tile in buffer

	lea ConvRsc@END.w(%a5),%a0
        move.l 4(%a0),%a2             | get address of 1->4 conversion table

        lea ImagRsc@END.w(%a5),%a3    | image data
        addq.l #4,%a3

	move.w #9,%d4                 | tile counter

next_tile:
	lea foreground_data@END.w(%a5),%a0
        clr.w %d0
	move.b (%a0,%d5.w),%d0        | read tile id
	addq.w #1,%d5                 | next tile

	tst.w %d0                     | no tile here?
	jbeq empty_tile

	subq.w #1,%d0
	asl.w #3,%d0                  | 2*(id-1)

	move.l (%a3,%d0.w),%a1        | ressource data pointer

	move.l %d6,%a0                | dest address
	move.w #15,%d2
	clr.w %d1

next_line:
        clr %d0
	move.b (%a1)+,%d0             | get 8 bits pixel mask
        not.b %d0
	asl #2,%d0                    | * 4

	move.l (%a2,%d0.w),%d0        | converted mask
        and.l (%a0),%d0

	clr %d1
	move.b (%a1)+,%d1             | get next mask byte
        not.b %d1
	asl #2,%d1                    | * 4

	move.l (%a2,%d1.w),%d1        | converted mask
        and.l 4(%a0),%d1 

        or.l (%a1)+, %d0              | combine with image data
        move.l %d0, (%a0)+            | and map to screen

        or.l (%a1)+, %d1              | combine with image data
        move.l %d1, (%a0)+            | and map to screen

	add.w #88,%a0                 | next screen line

        dbra %d2, next_line

empty_tile:
	addq.l #8,%d6                 | next dest tile address
	dbra %d4, next_tile           | once more

	movem.l (%sp)+,%d4-%d6/%a2-%a3
	rts
");
#else
void VideoFgLine(unsigned long *dst, int tile) {
  int i,j,k;
  unsigned long *d;
  void *s;
  unsigned long *conv = (unsigned long*)ConvRsc.ResP;

  /* ten tiles per line */
  for(i=0;i<10;i++) {
    k = foreground_data[tile++];

    /* tile contains data */
    if(k!=0) {
      s = ImagRsc[k-1].ResP;

      /* tile has 16 lines */
      for(d=dst,j=0;j<16;j++) {
	*d     &= ~conv[*((unsigned char*)s)++];
	*(d+1) &= ~conv[*((unsigned char*)s)++];
	
	*d++   |= *((unsigned long*)s)++;
	*d++   |= *((unsigned long*)s)++;
	
	d += (96-8)/sizeof(long);
      }
    }

    /* next row */
    dst+=2;
  }
}
#endif

void VideoDrawTitleBg(void) {
  static int y=10;

  /* generate background */
  MemMove(draw_base+VIDEO_WIDTH*8 + (160-(y/2))*96, 
	  BackRsc[0].ResP,      (y/2)*96);
  MemMove(draw_base+VIDEO_WIDTH*8,            
	  BackRsc[0].ResP+(y/2)*24, (VIDEO_WIDTH*80)-(y/2)*96);

  if(y-- == 0) y=320;
}

void VideoDrawBackground(unsigned int ypos) {
  int i,j,k;
  unsigned long *dst;
  extern void score_inc(int amount);

  /* generate background */
  i = 159-(ypos%320)/2;
  MemMove(draw_base+VIDEO_WIDTH*8 + (160-i)*96, 
	  BackRsc[0].ResP,      i*96);
  MemMove(draw_base+VIDEO_WIDTH*8,            
	  BackRsc[0].ResP+i*24, (VIDEO_WIDTH*80)-i*96);

  /* generate foreground */
  i = ypos & 0x0f;
  k = 10*(FG_LINES-(ypos/16)%FG_LINES);

  VideoAnimateForeground(k);

  if(i==0) {
    dst = (unsigned long*)(draw_base+VIDEO_WIDTH*8+8);

    for(j=0;j<10;j++) {
      k += 10;
      VideoFgLine(dst, k);
      dst += 16*24;
    }
  } else {

    dst = (unsigned long*)(draw_base - 64*24 + 8 + VIDEO_WIDTH*8 + i*96 );
    for(j=0;j<11;j++) {
      VideoFgLine(dst, k);
      k += 10;
      dst += 16*24;
    }

  }

  /* offset within this level */
  i = ypos%(16*FG_LINES);

  /* draw start and end messages */
  if(i == 0)              
    new_message(  "GET READY!");

  if(i == 16*(LENGTH+1)) {
    new_message("STAGE FINISHED");
    score_inc(SCORE_STAGE);
  }
}

void VideoFlip(void) {
  if(direct_video) {
    int  y;
    long *s = (long*)(draw_base+8+16*(192/2)), *d = (long*)video_base;

    for(y=0;y<160;y++) {
      *d++ = *s++; *d++ = *s++; *d++ = *s++; *d++ = *s++;
      *d++ = *s++; *d++ = *s++; *d++ = *s++; *d++ = *s++;
      *d++ = *s++; *d++ = *s++; *d++ = *s++; *d++ = *s++;
      *d++ = *s++; *d++ = *s++; *d++ = *s++; *d++ = *s++;
      *d++ = *s++; *d++ = *s++; *d++ = *s++; *d++ = *s++;
      
      s+=4;
    }
  } else {
    /* or let the palm os do the job */
    WinDrawBitmap(offscreen_bitmap, -16, -16);
  }
}

Boolean VideoGreyscaleOn(void) {
  int i,j;
  long  dwVer;
  DWord newDepth, depth;
  Err error;

  /* this game requires at least OS3.0 */
  FtrGet(sysFtrCreator, sysFtrNumROMVersion, &dwVer);
  if (dwVer < PalmOS30) {
    FrmCustomAlert(alt_err,"Argon V requires at least PalmOS 3.0.",0,0);
    return false;
  }

  direct_video = true;
  newDepth = 4;
  if(ScrDisplayMode(scrDisplayModeSet, NULL, NULL, &newDepth, NULL)) {

    /* try to access hardware directly */
    if(!VideoDirect()) {
      FrmCustomAlert(alt_err,"Grayscale video not supported on this machine.",
		     0,0);
      return false;
    }
  }

  /* if not direct hardware access get video buffer address from OS */
  if(video_old_base == NULL) {
    if(dwVer < PalmOS35)
      video_base = WinGetDrawWindow()->displayAddrV20;
    else {
      video_base = BmpGetBits(WinGetBitmap(WinGetDrawWindow()));

      /* check whether the video setup is fine */
      /* WinSetForeColor is only present on machines >= OS 3.5 */

      /* draw pixel with OS and verify directly video buffer layout */
      WinSetForeColor(1); WinDrawPixel(0,0);
      WinSetForeColor(2); WinDrawPixel(1,0);
      WinSetForeColor(3); WinDrawPixel(0,1);
      WinSetForeColor(4); WinDrawPixel(1,1);
    
      /* verify, that pixels show up at the right position in video memory */
      if(((video_base[0] != 0x12)||(video_base[80] != 0x34)))
	direct_video = false;
    }
  }

  if(direct_video) {
    /* allocate buffer memory */
    if((draw_base = MemPtrNew(VIDEO_BUFFER)) == NULL) {
      FrmCustomAlert(alt_err,"Out of memory allocating video buffer.",0,0);
      return false;
    }
  } else {
    /* create offscreen bitmap */
    offscreen_bitmap = BmpCreate(VIDEO_WIDTH, VIDEO_HEIGHT, 4, NULL, &error);

    if(!offscreen_bitmap) {
      FrmCustomAlert(alt_err, "Error creating offscreen bitmap.",0,0);
      return false;
    }

    /* get address of offscreen bitmap */
    draw_base = BmpGetBits(offscreen_bitmap);
  }

  MemSet(draw_base, VIDEO_BUFFER, 0);

  if(!VideoRscInit()) {
    video_base = NULL;
    return false;
  }

  return true;
}

void VideoGreyscaleOff(void) {

  if(video_base != NULL) {

    VideoRscRelease();

    if(direct_video) {
      /* free video buffer */
      if(draw_base)
	MemPtrFree(draw_base);
    } else {
      /* free offscreen bitmap */
      if(offscreen_bitmap)
	BmpDelete(offscreen_bitmap);
    }

    if(video_old_base != NULL) {

      MemPtrFree(video_base);
      /* switch off LCD update temporarily */
      CKCON &= ~0x80;
  
      /* virtual page width now 20 bytes (160 pixels) */
      VPW    = 10;
      PICF  &= ~0x03;  /* switch to black and white mode */
      LLBAR  = 10;     /* line buffer now 20 bytes */

      /* let the LCD get to a new frame (20ms delay) */
      SysTaskDelay(4);
  
      /* switch LCD back on in new mode */
      CKCON |= 0x80;

      /* stop hardware scrolling */
      LPOSR = 0;

      /* restore old video base */
      LSSA = video_old_base;

      /* restore old refresh value */
      LPXCD = lpxcd;
    } else {
      /* return to default video mode */
      ScrDisplayMode(scrDisplayModeSetToDefaults, NULL, NULL, NULL, NULL);
      video_base = NULL;
    }
  }
}

