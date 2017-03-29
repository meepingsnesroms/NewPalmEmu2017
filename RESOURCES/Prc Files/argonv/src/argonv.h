/*
  argonv.h

  T.Harbaum@tu-bs.de - http://www.ibr.cs.tu-bs.de/~harbaum/pilot

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

*/

#ifndef __ARGONV_H__
#define __ARGONV_H__

#include "argonvRsc.h"
#include "video.h"

#define CREATOR 'ArgV'

/* various damages */
#define DAMAGE_WALL     1
#define DAMAGE_FIZZLE   1  // this applies multiple times
#define DAMAGE_ALIEN    5
#define DAMAGE_BOMB    10
#define DAMAGE_DESTROY -1
#define DAMAGE_RELOAD  -2
extern void damage(int amount);

/* shot modes */
#define SHOT_SINGLE     0
#define SHOT_DOUBLE     1
#define SHOT_TRIPLE     2
extern int shot_mode, shot_reload;

/* title/game state */
#define STATE_RUNNING   0
#define STATE_NAME      1
#define STATE_TITLE     2
#define STATE_HISCORE   3
#define STATE_HELP      4
#define STATE_WRAP      5

/* wave stuff */
#define WAVE_PAUSE  20
#define WAVE_INIT   100

/* scores */
#define SCORE_ALIEN   1
#define SCORE_10      10     // wave completed
#define SCORE_100     100    // bonus
#define SCORE_STAGE   1000   // stage finished 
extern void score_inc(int amount);

/* player ship functions */
extern void ship_save_position(void);

/* all kinds of prototypes */
extern void init_shot(void);
extern void init_exp(void);
extern void init_bomb(void);
extern void init_wave(int type, int time);
extern void init_extra(void);
extern void new_message(char *s);

#define ALERTF(format, args...) { char tmp[64]; StrPrintF(tmp, format, ## args); FrmCustomAlert(alt_err, tmp,0,0); }
#define PRINTF(format, args...) { char tmp[64]; StrPrintF(tmp, format, ## args); VideoDrawText(0,32,tmp); }

#endif
