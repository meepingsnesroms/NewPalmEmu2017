/*
  video.h

  (c) 1999-2000 Till Harbaum

  T.Harbaum@tu-bs.de - http://www.ibr.cs.tu-bs.de/~harbaum/pilot

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

*/

#ifndef __VIDEO_H__
#define __VIDEO_H__

extern Boolean VideoGreyscaleOn(void);
extern void    VideoGreyscaleOff(void);
extern void    VideoDrawBackground(unsigned int y);
extern void    VideoDrawTitleBg(void);
extern void    VideoFlip(void);
extern void    VideoInitLevel(void);

extern Boolean VideoSpriteCollide(int x1, int y1, int s1, int x2, int y2, int s2);
extern Boolean VideoSpriteBgCollide(unsigned int ypos, int x, int y, int s);
extern void    VideoDrawSprite(int x, int y, int spr);
extern void    VideoDrawText(int x, int y, unsigned char *str);
extern void    VideoDrawPartialText(int x, int y, unsigned char *str, 
				    int xs, int xe, int ys, int ye);

extern char    *VideoSin, *VideoCos;

/* foreground data */
#define FG_EMPTY    0
#define FG_FLASH0   6
#define FG_FLASH1   7
#define FG_FLASH2   8
#define FG_FLASH3   9

/* sprites */
#define SPR_SHIP  0x00  // players ship
#define SPR_BALL  0x01  // ball type enemy
#define SPR_SHOT1 0x02  // single shot
#define SPR_SHOT2 0x03  // double shot
#define SPR_SHOT3 0x12  // tripple shot
#define SPR_EXP_F 0x04  // explosion first
#define SPR_EXP_L 0x08  // explosion last
#define SPR_EBOMB 0x09  // enemies bomb

/* Argon V logo */
#define SPR_A  0x0a
#define SPR_r  0x0b
#define SPR_g  0x0c
#define SPR_o  0x0d
#define SPR_n  0x0e
#define SPR_V  0x0f

/* score */
#define SPR_SCORE10   0x10
#define SPR_SCORE100  0x11

/* text cursor */
#define SPR_CURSOR 0x13
#define SPR_CUREXT 0x14

#endif
