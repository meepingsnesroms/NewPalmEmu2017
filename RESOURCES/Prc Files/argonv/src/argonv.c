/*

  argonv.c - (c) 1999 by Till Harbaum

  ArgonV, the ultimate space blaster

  T.Harbaum@tu-bs.de - http://www.ibr.cs.tu-bs.de/~harbaum/pilot

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

*/

#include <PalmOS.h>
#include <PalmCompatibility.h>
#include <System/DLServer.h>

#ifdef GAMEPAD
/* this type is required when using gamepad */
/* with sdk-3.1 and earlier */
#include <GPDLib.h>
#endif

#include "video.h"
#include "argonv.h"
#include "argonvRsc.h"

static Boolean StartApplication(void);
static Boolean MainFormHandleEvent(EventPtr event);
static void    EventLoop(void);

#define noFORCE_PREFS  // force regeneration of preferences 
#define MAX_Y  176     // sprites max y postition

/* preference stuff */
#define MAX_SCORES    6  /* save and display the six top scores */
#define MAX_NAMELEN  10

unsigned long score;

struct score {
  char name[MAX_NAMELEN+1];
  unsigned long  value;
};

struct {
  struct score score[MAX_SCORES];
  int last_name_index;
  Boolean sound;
} prefs;

/* some globals for overall control */
int game_state  = STATE_TITLE;
int sub_state   = 0;

/* save hard key state */
DWord last_state=0;

#ifdef GAMEPAD
/* gamepad library interface */
UInt gpdRef = 0;

/* special KeyCurrentState function including gamepad keys */
DWord KeyCurrentState_GPD(void) {
  DWord hardKeyState;
  unsigned char gpdBut;

  hardKeyState = KeyCurrentState();

  /* overlay gamepad buttons */
  if(gpdRef != 0) {

    /* read gamepad buttons */
    if(!GPDReadInstant(gpdRef, &gpdBut)) {

      /* avoid auto off */
      EvtResetAutoOffTimer();

      if(gpdBut & GAMEPAD_UP)    hardKeyState |= keyBitPageUp;
      if(gpdBut & GAMEPAD_DOWN)  hardKeyState |= keyBitPageDown;
      if(gpdBut & GAMEPAD_LEFT)  hardKeyState |= keyBitHard1;
      if(gpdBut & GAMEPAD_RIGHT) hardKeyState |= keyBitHard2;

      /* leftfire is quit */
      if(gpdBut & GAMEPAD_LEFTFIRE) hardKeyState |= keyBitHard3;

      /* all other buttons are mapped to fire/select  */
      if(gpdBut & (GAMEPAD_RIGHTFIRE|GAMEPAD_SELECT|GAMEPAD_START)) 
	hardKeyState |= keyBitHard4;
    }
  }
  return hardKeyState;
}
#endif

/************************************************************/
/* players ship position handling                           */

#define SHIP_START_Y 155

unsigned int scroll_y;
int ship_x_pos, ship_y_pos;

unsigned int ship_save_scroll;
int ship_save_x, ship_save_y;

/* save position for restore */
void ship_save_position(void) {
  ship_save_x = ship_x_pos;
  ship_save_y = ship_y_pos;
  ship_save_scroll = scroll_y;
}

/* save position for restore */
void ship_restore_position(void) {
  ship_x_pos = ship_save_x; 
  ship_y_pos = ship_save_y;
  scroll_y = ship_save_scroll;
}

/************************************************************/
/* player name input                                        */
char    current_name[MAX_NAMELEN+1];
Boolean name_init;
int     name_pos;

/* get hotsync user name */
void set_default_name(void) {
  char name[dlkUserNameBufSize];
  int i;

  DlkGetSyncInfo(0, 0, 0, name, 0, 0);

  /* remove weird characters */
  for(name_pos=0,i=0;(name[i]!=0)&&
	(name_pos<MAX_NAMELEN)&&(name[i]!=' ');i++) {

    /* convert lowercase to uppercase */
    if((name[i]>='a')&&(name[i]<='z'))
      current_name[name_pos++] = name[i] - 'a' + 'A'; 
    else if((name[i]>='A')&&(name[i]<='Z'))
      current_name[name_pos++] = name[i];
  }

  /* last char */
  current_name[name_pos]=0;

  if(name_pos>=MAX_NAMELEN) name_pos--;
}

void init_name_input(void) {
  name_init       = true;
}

/* compare function to sort hiscores */
Int name_compare(VoidPtr a, VoidPtr b, Long nix) {
  return ((struct score*)b)->value - ((struct score*)a)->value;
}

void name_add_char(char chr) {
  int i;

  switch(chr) {

    /* END */
  case 3:
    /* switch to title display */
    game_state = STATE_TITLE;
    sub_state  = 0;

    /* add hi score to prefs */
    StrCopy(prefs.score[MAX_SCORES-1].name, current_name);
    prefs.score[MAX_SCORES-1].value = score;
    SysQSort(prefs.score, MAX_SCORES, sizeof(struct score), name_compare, 0);

    /* remember that this was the last name entered */
    for(i=0;i<MAX_SCORES;i++) 
      if(StrCompare(prefs.score[i].name, current_name) == 0)
	prefs.last_name_index = i;

    break;

    /* RUB */
  case 2:
    if(name_pos>0) current_name[--name_pos] = '\0';
    break;

    /* CLR */
  case 1:
    name_pos = 0;
    current_name[name_pos] = '\0';
    break;

    /* SPC */
  case 0:
    chr = ' ';
  default:
    current_name[name_pos++] = chr;
    current_name[name_pos]   = '\0';    
  }
  if(name_pos>=MAX_NAMELEN) name_pos--;
}

void main_name_input(void) {
  DWord hardKeyState;
  static int cur_x, cur_y;

#ifdef GAMEPAD
  hardKeyState = KeyCurrentState_GPD();
#else
  hardKeyState = KeyCurrentState();
#endif

  if(name_init) {
    name_init  = false;

    /* default cursor position is 'END' */
    cur_x = 6;
    cur_y = 3;
  }

  /* draw scrolling background */
  VideoDrawTitleBg();
  VideoDrawSprite(53 + 8*name_pos, 57, SPR_CURSOR);

  if(cur_x <= 5) {
    /* cursor on characters */
    VideoDrawSprite(29 + 16*cur_x, 77 + 12*cur_y, SPR_CURSOR);
  } else {
    /* cursor on special entries */
    VideoDrawSprite(29 + 120, 77 + 12*cur_y, SPR_CURSOR);
    VideoDrawSprite(29 + 112, 77 + 12*cur_y, SPR_CUREXT);
    VideoDrawSprite(29 + 104, 77 + 12*cur_y, SPR_CUREXT);
  }

  VideoDrawText(2,  30, "New High Score!");
  VideoDrawText(2,  40, "Enter your name:");

  VideoDrawText(5,  60, current_name);
  VideoDrawText(5,  65, "----------");
  
  VideoDrawText(2,  80, "A B C D E F  SPC");
  VideoDrawText(2,  92, "G H I J K L  CLR");
  VideoDrawText(2, 104, "M N O P Q R  RUB");
  VideoDrawText(2, 116, "S T U V W X  END");
  VideoDrawText(2, 128, "Y Z");

  /* is currently a key pressed? */
  if((hardKeyState != 0) &&
     ((hardKeyState & last_state) != hardKeyState)) {

    /* cursor movement key */
    if((hardKeyState & keyBitPageUp)   != 0) cur_y -= 1;
    if((hardKeyState & keyBitPageDown) != 0) cur_y += 1;
    if((hardKeyState & keyBitHard1)    != 0) cur_x -= 1;
    if((hardKeyState & keyBitHard2)    != 0) cur_x += 1;	

    /* 'enter' key */ 
    if((hardKeyState & keyBitHard4)    != 0) {
      if(cur_x<6) name_add_char('A'+cur_x+cur_y*6);
      else        name_add_char(cur_y);
    }

    if((hardKeyState & keyBitHard3)    != 0) {
      /* switch to title display */
      game_state = STATE_TITLE;
      sub_state  = 0;
    }

    /* check limits */
    if(cur_x<0) cur_x=0;
    if(cur_x>6) cur_x=6;
    if(cur_y<0) cur_y=0;
    if(cur_y>4) cur_y=4;
    if((cur_y==4)&&(cur_x>1)) cur_y=3;
  }

  /* save last keystate */
  last_state = hardKeyState;
}

/************************************************************/
/** preference stuff                                        */

void get_preferences(void) {
  Word size, result;
  int i;

  SystemPreferencesType sysPrefs;

  size   = sizeof(prefs);
  result = PrefGetAppPreferences( CREATOR, 0, &prefs, &size, true);

  /* initialize default settings */
#ifndef FORCE_PREFS
  if(result == noPreferenceFound)
#endif
  {
    prefs.sound = true;
    prefs.last_name_index = -1;

    for(i=0;i<MAX_SCORES;i++) {
      StrCopy(prefs.score[i].name, "- empty -");
      prefs.score[i].value=0;
    }
  }

  /* preference is fine, get last entered name */
  if(prefs.last_name_index>=0) {
    StrCopy(current_name, prefs.score[prefs.last_name_index].name);
    name_pos = StrLen(current_name);
    if(name_pos>=MAX_NAMELEN) name_pos--;
  } else
    set_default_name();

  /* get system preferences for sound */
  PrefGetPreferences(&sysPrefs);
  if(sysPrefs.gameSoundLevelV20 == slOff) 
    prefs.sound = false;
}

void save_preferences(void) {
  PrefSetAppPreferences( CREATOR, 0, 1, &prefs, sizeof(prefs), true);
}

/************************************************************/
/* routie to handle messages during the game                */
unsigned char message_buffer[21];   /* at most 20 chars */
int msg_state, msg_offset,msg_len;
#define MSG_RELOAD 50

void init_message(void) {
  msg_state=0;    /* no message */
}

void new_message(char *str) {
  int i=0;

  msg_state = MSG_RELOAD;

  /* copy string */
  while(message_buffer[i++] = *str++);

  /* center message horizontally */
  msg_offset = (21-i)/2;
  msg_len = i-1;
}

void handle_message(void) {
  int i;

  if(msg_state>0) {
    if(msg_state>(MSG_RELOAD-8)) {
      i = MSG_RELOAD-msg_state;
      VideoDrawPartialText(msg_offset, 32, message_buffer, 
			     0, 20, (7-i)/2, (8+i)/2);
    } else if(msg_state<msg_len) {
      i = (msg_len-msg_state)/2;
      VideoDrawPartialText(msg_offset, 32, message_buffer, 
			     i, msg_len-i-1, 0, 7);
    } else
      VideoDrawText(msg_offset, 32, message_buffer);

    msg_state--;
  }
}

/************************************************************/
/* routines to update status line                           */
char score_str[21]="00000  \002\010\010\010\010\003  \001\001\001\001\001";

void score_inc(int amount) {
  unsigned int s;
  int i;

  score += amount;
  s = score;

  i=4;
  while(i>=0) {
    score_str[i--] = '0' + s%10;
    s/=10;
  }
}

/************************************************************/
/* shield and damage stuff                                  */

#define SHIP_EXPLODE_TIMER 50

#define SHIELD_MUL  (8)   /* shield muliplier */
#define MAX_SHIELDS (SHIELD_MUL*4*4)
#define MAX_LIFES   (5)
int shields, lifes;

void damage(int amount) {
  int i,k,p;

  /* game currently running */
  if(sub_state == 0) {

    /* total destruction */
    if(amount == DAMAGE_DESTROY) {
      shields = -1;
      amount  = 0;
    }

    /* reload/init shields */
    if(amount == DAMAGE_RELOAD) {
      shields = MAX_SHIELDS;
      amount  = 0;
    }

    /* shields are down -> explode ship */
    shields -= amount;

    /* shields just got below warning level */
    if((shields<(4*SHIELD_MUL))&&(shields+amount>=(4*SHIELD_MUL)))
      new_message("SHIELDS LOW!");

    if(shields < 0) {
      lifes--;
      shields = 0;
      sub_state = SHIP_EXPLODE_TIMER + 2*(SPR_EXP_L - SPR_EXP_F + 1);
    }
    
    /* draw shield bar */
    for(p = shields/SHIELD_MUL, k=11;k!=7;k--, p-=4) {
      if(p>4)       score_str[k] = 8;   /* 100%    */
      else if(p<0)  score_str[k] = 4;   /* 0%      */
      else          score_str[k] = 4+p; /* 25%-75% */
    }
    
    /* draw lifes */
    for(p = lifes, k=19; k!=19-MAX_LIFES; k--, p--)
      if(p>0) score_str[k]=1;
      else    score_str[k]=' ';
  }
}

/************************************************************/
/** explosion                                               */

#define MAX_EXP    8

struct explosion {
  int x, y;    /* position */
  int state;   /* timer */
};

struct explosion explosion[MAX_EXP];  /* current explosion position/state */

void init_exp(void) {
  int i;
  for(i=0;i<MAX_EXP;i++) explosion[i].y = -1;
}

void new_exp(int x, int y) {
  int i;

  /* find an empty explosion slot and use it */
  for(i=0;i<MAX_EXP;i++) {
    if(explosion[i].y < 0) {
      explosion[i].state = SPR_EXP_F;  /* first explosion sprite */
      explosion[i].x = x;
      explosion[i].y = y;
      return;
    }
  }
}

void handle_exp(void) {
  static reload=0;
  Boolean f;
  int i;

  /* draw explosions */
  for(i=0;i<MAX_EXP;i++) {
    if(explosion[i].y >= 0) {
      VideoDrawSprite(explosion[i].x, explosion[i].y, explosion[i].state);
      explosion[i].state += 1;
      if(explosion[i].state == (SPR_EXP_L+1))
	explosion[i].y = -1;
    }
  }
}

/************************************************************/
/** players shot                                            */

int shot_sprite[]={SPR_SHOT1, SPR_SHOT2, SPR_SHOT3 };

#define MAX_SHOTS   8
#define SHOT_STEP   3

const shot_reload_time[]={12,8,6};

int shot_mode, shot_reload;

struct shot {
  int x,y;  /* current shot position */
  int spr;  /* type of shot (single, double, tripple) */
};

struct shot shot[MAX_SHOTS];

void init_shot(void) {
  int i;

  shot_mode = SHOT_SINGLE;
  shot_reload = 0;

  for(i=0;i<MAX_SHOTS;i++) shot[i].y = -1;
}

void handle_shot(Boolean fire, int mode, int x, int y) {
  static reload=0;
  Boolean f;
  int i;

  /* it's time for a new shot */
  if((fire)&&(reload==0)) {

    /* find an empty shot slot and use it */
    for(f=false,i=0;(i<MAX_SHOTS)&&(!f);i++) {
      if(shot[i].y < 0) {
	shot[i].x   = x;
	shot[i].y   = y;
	shot[i].spr = shot_sprite[mode];
	f = true;
      }
    }

    if(f) reload = shot_reload_time[shot_reload];
  }

  if(reload>0) reload--;

  /* draw shots */
  for(i=0;i<MAX_SHOTS;i++) {
    if(shot[i].y >= 0) {
      VideoDrawSprite(shot[i].x, shot[i].y, shot[i].spr);
      shot[i].y -= SHOT_STEP;

      /* shot automatically disappears at pos < 0 */
    }
  }
}

/************************************************************/
/** enemies bomb                                            */

#define MAX_BOMBS  8
#define BOMB_STEP  2

/* all things we need to know about one bomb */
struct bomb {
  int x,y;     /* bomb position */
};

struct bomb bomb[MAX_BOMBS];  /* current bomb position */
int bomb_freq;

void init_bomb(void) {
  int i;
  for(i=0;i<MAX_BOMBS;i++) bomb[i].y=-1;
  bomb_freq = 10;
}

void new_bomb(int x, int y) {
  Boolean f;
  int i;

  /* find an empty bomb slot and use it */
  for(f=false,i=0;(i<MAX_BOMBS)&&(!f);i++) {
    if(bomb[i].y < 0) {
      bomb[i].x = x;
      bomb[i].y = y;
      f = true;
    }
  }
}
  
void handle_bomb(int x, int y) {
  int i;

  /* draw bombs */
  for(i=0;i<MAX_BOMBS;i++) {
    if(bomb[i].y >= 0) {
      VideoDrawSprite(bomb[i].x, bomb[i].y, SPR_EBOMB);
      bomb[i].y += BOMB_STEP;

      /* game still running? */
      if(sub_state == 0) {
	/* is our ship hit? */
	if(VideoSpriteCollide(x, y, SPR_SHIP, 
			      bomb[i].x, bomb[i].y, SPR_EBOMB)) {
	  damage(DAMAGE_BOMB);  /* cause damage to ship */
	  bomb[i].y = -1;       /* remove bomb */
	}
      }

      /* bomb disappears at pos > 176 (160+16) */
      if(bomb[i].y >= MAX_Y) bomb[i].y = -1;
    }
  }
}

/************************************************************/
/** extra (bonus score etc) stuff                           */

#define EXTRA_DURATION    20
#define MAX_EXTRA          8
#define EXTRA_STEP         1

struct extra {
  int x,y;      /* screen position */
  int spr;      /* sprite type     */
  int ttl;      /* time to live    */ 
};

struct extra extra[MAX_EXTRA];  /* current extra position/time/sprite */

void init_extra(void) {
  int i;
  for(i=0;i<MAX_EXTRA;i++) extra[i].y=-1;
}

void new_extra(int x, int y, int sprite) {
  int i, max=0;

  /* do score handling */
  if(sprite == SPR_SCORE10)       score_inc(SCORE_10);
  else if(sprite == SPR_SCORE100) score_inc(SCORE_100);

  /* find an empty extra slot and use it */
  for(i=0;i<MAX_EXTRA;i++) {
    if(extra[i].y < 0) {
      extra[i].x   = x;
      extra[i].y   = y;
      extra[i].spr = sprite;
      extra[i].ttl = EXTRA_DURATION;
      return;
    }
  }

  /* no empty slot? empty one! */
  /* ... */
}

void handle_extra(void) {
  int i;

  for(i=0;i<MAX_EXTRA;i++) {
    if(extra[i].y >= 0) {
      VideoDrawSprite(extra[i].x, extra[i].y, extra[i].spr);

      extra[i].y += EXTRA_STEP;

      /* timeout? */
      if((--extra[i].ttl==0)||(extra[i].y>=MAX_Y)) {
	/* remove sprite */
	extra[i].y = -1;
      }
    }
  }
}

/************************************************************/
/** enemy wave                                              */

#define PI2 6   /* this is precise enough */

/* horiz. center of display area */
#define CENTER  88
#define CENTER2 (2*CENTER)

/* wave states */
struct wave {
  char mode;       /* type of wave             */
  char len;        /* number of enemies        */
  unsigned char y; /* wave parameter (y-pos)   */
  char rad;        /* wave parameter (radius)  */
  char flip;       /* vertical flip            */
  char rev;        /* reverse wave             */
  char dist;       /* distance between enemies */
  char sprite;     /* enemy sprite             */
  char speed;      /* speed of sprites         */
};

#define WTYPE_PAUSE 0
#define WTYPE_LOOP  1
#define WTYPE_SLOOP 2

/* all waves ... */
struct wave wave[]={
  {  WTYPE_LOOP, 5, 120, 50,    -1,    -1, 30, SPR_BALL, 3 },
  { WTYPE_SLOOP, 5,  30, 25,    -1,    -1, 30, SPR_BALL, 3 },
  {          -1, 0,   0,  0,     0,     0,  0,        0, 0 }
};

int wave_state;  /* state of current wave */
int wave_wait, wave_type;
int wave_bits;
  
int wave_rad2;
struct wave wave_cur;

void init_wave(int type, int wait) {
  int r;

  if(wave[type].mode == -1) type = 0;

  /* waiting for next wave */
  wave_type = type;

  wave_wait  = wait;
  wave_state = 0;
  MemMove(&wave_cur, &wave[type], sizeof(struct wave));
  wave_bits  = 0xffff>>(16-wave_cur.len);  // all enemies alive 

  /* init some constants */
  switch(wave_cur.mode) {
  case WTYPE_LOOP:
  case WTYPE_SLOOP:
    r = SysRandom(0);
    if(wave_cur.rev  == -1) wave_cur.rev  = r&1;
    if(wave_cur.flip == -1) wave_cur.flip = r&2;
    
    wave_rad2 = PI2 * wave_cur.rad;
    break;
  }
}

void handle_wave(int sx, int sy) {
  int x, y, l, enemy, epos, i, bomb_r, bomb_e;

  if(wave_wait == 0) {

    /* bomb randomizer */
    bomb_r = SysRandom(0);
    bomb_e = bomb_r%wave_cur.len;   // enemy to drop bomb
    bomb_r >>= 4;                   // remaining random value
    
    /* draw all enemies */
    for(enemy=0;enemy<wave_cur.len;enemy++) {

      /* enemy still alive?? */
      if(wave_bits & (1<<enemy)) {

	epos = wave_state - (enemy * wave_cur.dist);
    
	x = y = 0;   /* default position (invisible) */
    
	switch(wave_cur.mode) {

	  /* here is the quite ugly wave form calculation stuff */
      
	  /* loop wave */
	case WTYPE_LOOP:
	  /* reverse flight */
	  if(wave_cur.rev)  epos = (CENTER2 + wave_rad2) - epos;
      
	  if((epos>0)&&(epos<CENTER)) {
	    /* flight to the center */
	    x = epos;
	    y = wave_cur.y;
	  } else if((epos >= CENTER)&&(epos < (CENTER + wave_rad2))) {
	    /* full circle */
	    l = (((long)epos - CENTER) * 256)/(wave_rad2);
	    x = CENTER + (VideoSin[l] * wave_cur.rad) / 128;
	    y = wave_cur.y - wave_cur.rad + 
	      (VideoCos[l] * wave_cur.rad) / 128;
	  } else if((epos >= (CENTER  + wave_rad2))&&
		    (epos <  (CENTER2 + wave_rad2))) {
	    /* leave from center */
	    x = epos - wave_rad2;
	    y = wave_cur.y;
	  }
	  
	  /* flip */
	  if((x!=0)&&(wave_cur.flip)) x = 176 - x;
//	  if((y!=0)&&(wave_cur.flip)) y = ((wave_cur.y - wave_cur.rad)<<1) - y;
	  
	  break;
	  
	  /* s wave */
	case WTYPE_SLOOP:
	  /* reverse flight */
	  if(wave_cur.rev)  epos = (CENTER2 + wave_rad2) - epos;
      
	  if((epos>0)&&(epos<CENTER)) {
	    /* enter screen and fly to the middle */
	    x = epos;
	    y = wave_cur.y;
	  } else if((epos >= CENTER)&&(epos < (CENTER + (wave_rad2/2)))) {
	    /* half circle */
	    l = (((long)epos - CENTER) * 256)/(wave_rad2);
	    x = CENTER + (VideoSin[l] * wave_cur.rad) / 128;
	    y = wave_cur.y + wave_cur.rad - 
	      (VideoCos[l] * wave_cur.rad) / 128;
	  } else if((epos >= CENTER+(wave_rad2/2))&&
		    (epos < (CENTER + wave_rad2))) {
	    /* another half circle */
	    l = (((long)epos - CENTER - (wave_rad2/2)) * 256)/(wave_rad2);
	    x = CENTER - (VideoSin[l] * wave_cur.rad) / 128;
	    y = wave_cur.y + 3*wave_cur.rad - 
	      (VideoCos[l] * wave_cur.rad) / 128;
	  } else if((epos >= (CENTER  + wave_rad2))&&
		    (epos <  (CENTER2 + wave_rad2))) {
	    /* leave screen */
	    x = epos - wave_rad2;
	    y = wave_cur.y + 4*wave_cur.rad;
	  }

	  /* flip */
	  if((x!=0)&&(wave_cur.flip)) x = 176 - x;
	  
	  break;
	}
	
	/* draw alien */
	VideoDrawSprite(x, y, wave_cur.sprite);

	if(sub_state == 0) {
	  /* did alien collide with our ship? */
	  if(VideoSpriteCollide(x, y, wave_cur.sprite,
				sx, sy, SPR_SHIP)) {

	    /* get score, anyway */
	    score_inc(SCORE_ALIEN);
	    
	    /* draw explosion */
	    new_exp(x, y);
	    
	    /* remove alien */
	    wave_bits &= ~(1<<enemy);
	    
	    /* add damage to ship */
	    damage(DAMAGE_ALIEN);
	    
	    /* whole wave removed? */
	    if(wave_bits == 0)
	      new_extra(x, y, SPR_SCORE10);
	  }
	}

	/* is this enemy to drop a bomb? */
	if((bomb_e == enemy)&&((bomb_r % bomb_freq) == 1))
	  new_bomb(x, y);
	
	/* check if enemy is hit */
	for(i=0;i<MAX_SHOTS;i++) {
	  if(shot[i].y >= 0) {
	    if(VideoSpriteCollide(x, y, wave_cur.sprite, 
				  shot[i].x, shot[i].y, shot[i].spr)) {

	      /* yupp, we got em */
	      score_inc(SCORE_ALIEN);
	      new_exp(x, y);

	      shot[i].y = -1;  /* remove shot */
	      wave_bits &= ~(1<<enemy);

	      /* whole wave removed */
	      if(wave_bits == 0)
		new_extra(x, y, SPR_SCORE10);
	    }	    
	  }
	}
      }
    }

    if(wave_state >= (CENTER2 + wave_rad2 + (wave_cur.len-1) * wave_cur.dist))
      wave_wait = WAVE_PAUSE;

    wave_state += wave_cur.speed;
  } else {
    /* still in wait state */
    wave_wait--;

    /* next wave is coming ... */
    if(wave_wait == 0) {
      init_wave(wave_type+1, 0);
    }
  }
}

#define OFFSET 65
void draw_Argon(int y) {
  VideoDrawSprite(OFFSET+0,  y,   SPR_A);
  VideoDrawSprite(OFFSET+13, y,   SPR_r);
  VideoDrawSprite(OFFSET+21, y+4, SPR_g);
  VideoDrawSprite(OFFSET+33, y,   SPR_o);
  VideoDrawSprite(OFFSET+45, y,   SPR_n);
  VideoDrawSprite(OFFSET+60, y,   SPR_V);
}  

/************************************************************/
/* main title animation routine                             */
void main_title(void) {
  unsigned int i;
  DWord hardKeyState;
  char str[6];

  /* draw scrolling background */
  VideoDrawTitleBg();

  /* draw messages */
  switch(game_state) {

    /* first title page */
  case STATE_TITLE:
    if(sub_state<28)
      draw_Argon(sub_state);
    else {
      draw_Argon(28);
      
      /*                                         ------------------ */
      if(sub_state>40)    VideoDrawText(4,50,       "Version 1.03");
      if(sub_state>60) {  VideoDrawText(5,70,       "\011 1999-2002");
                          VideoDrawText(3,80,    "by Till Harbaum"); }
      if(sub_state>80) {  VideoDrawText(2,100,   "www.harbaum.org/");
                          VideoDrawText(2,110,   "till/palm/argonv"); }
      if(sub_state>100)   VideoDrawText(2,130,   "palm@harbaum.org");
      /*                                         ------------------ */
    }
    break;
    
  case STATE_HISCORE:
    /*                                         ------------------ */
    VideoDrawText(5,40,       "High Scores");
    VideoDrawText(5,42,       "___________");

    for(i=0;i<MAX_SCORES;i++) {
      if(sub_state>(20+20*i)) {
	StrIToA(str, (long)prefs.score[i].value);
	VideoDrawText(2,60+12*i, prefs.score[i].name);
	VideoDrawText(18-StrLen(str),60+12*i, str);
      }
      /*                                         ------------------ */
    }
    break;
    
  case STATE_HELP:
    /*                                         ------------------ */
    VideoDrawText(4,40,      "We Want You!");
    VideoDrawText(3,42,     "______________");
    if(sub_state>20)    VideoDrawText(2,60,    "ArgonV is a work");
    if(sub_state>40)    VideoDrawText(2,70,    "in progress. If");
    if(sub_state>60)    VideoDrawText(2,80,    "you want to par-");
    if(sub_state>80)    VideoDrawText(2,90,    "ticipate in this");
    if(sub_state>100)   VideoDrawText(2,100,   "project, read the");
    if(sub_state>120)   VideoDrawText(2,110,   "file 'readme.txt'");
    if(sub_state>140)   VideoDrawText(2,120,   "which came with");
    if(sub_state>160)   VideoDrawText(2,130,   "this archive.");
    /*                                         ------------------ */
    break;
  }
  
  /* message printed on all pages */
  VideoDrawText(1,160, "Press key to start");

  /* animate titles */
  if(++sub_state == 300) {
    sub_state = 0;
    
    if(++game_state == STATE_WRAP)
      game_state = STATE_TITLE;
  }
  
#ifdef GAMEPAD
  hardKeyState = KeyCurrentState_GPD() & 
    (keyBitPageUp | keyBitPageDown | 
     keyBitHard1  | keyBitHard2 | 
     keyBitHard3  | keyBitHard4);
#else
  hardKeyState = KeyCurrentState() & 
    (keyBitPageUp | keyBitPageDown | 
     keyBitHard1  | keyBitHard2 | 
     keyBitHard3  | keyBitHard4);
#endif

  /* is currently a key pressed? */
  if((hardKeyState != 0) &&
     ((hardKeyState & last_state) != hardKeyState)) {

    /* initialize level */
    VideoInitLevel();
    
    /* start game engine */
    game_state = STATE_RUNNING;
    sub_state  = 0;
    
    /* init game parameteters */
    ship_x_pos = CENTER;
    ship_y_pos = SHIP_START_Y;
    scroll_y   = 0;

    ship_save_position();

    /* clear score */
    score = 0;
    
    /* re-init game elements */
    init_shot();
    init_exp();
    init_bomb();
    init_wave(0, WAVE_INIT);
    init_extra();
    init_message();
    
    /* recharge shields/lifes */
    lifes   = MAX_LIFES;
    damage(DAMAGE_RELOAD);
  }
  
  /* save last keystate */
  last_state = hardKeyState;
}

/////////////////////////
// EventLoop
/////////////////////////

static void EventLoop(void) {
  EventType event;
  Word      error;
  DWord hardKeyState;
  int new_x, new_y, i;

  do {
    EvtGetEvent(&event, 1);
    if (SysHandleEvent(&event))
      continue;

    FrmDispatchEvent(&event);

    /* currently running a game? */
    if(game_state == STATE_RUNNING) {

#ifdef GAMEPAD
      hardKeyState = KeyCurrentState_GPD();
#else
      hardKeyState = KeyCurrentState();
#endif

      /* draw background (both layers) */
      VideoDrawBackground(scroll_y++);

      /* ship isn't exploding */
      if(sub_state == 0) {
	/* push ship if hit by background */
	if(VideoSpriteBgCollide(scroll_y, ship_x_pos, ship_y_pos, SPR_SHIP)) {
	  damage(DAMAGE_WALL);  /* some little damage to the ship */

	  /* push it */
	  ship_y_pos += 2;
	  
	  /* ship pushed out of the screen */
	  if(ship_y_pos > 160) {
	    damage(DAMAGE_DESTROY);  /* destroy ship */
	    
	    /* xxxx */
	    ship_y_pos = SHIP_START_Y; /* restore demo position */
	  }
	}
	
	new_x = ship_x_pos;
	new_y = ship_y_pos;
	
	/* hard keys */
	if((hardKeyState & keyBitPageUp)   != 0) new_y -= 2;
	if((hardKeyState & keyBitPageDown) != 0) new_y += 2;

	if((hardKeyState & keyBitHard1)    != 0) new_x -= 2;
	if((hardKeyState & keyBitHard2)    != 0) new_x += 2;
	
	/* limit movement to screen area */
	if(new_x < 16)  new_x = 16;
	if(new_x > 160) new_x = 160;
	if(new_y < 16)  new_y = 16;
	if(new_y > 160) new_y = 160;
	
	if((new_x != ship_x_pos)||(new_y != ship_y_pos)) {
	  if(VideoSpriteBgCollide(scroll_y, new_x, new_y, SPR_SHIP)) {
	    /* we hit the wall */
	    damage(DAMAGE_WALL);
	    
	    /* let's try a small step */
	    new_x = (new_x + ship_x_pos)/2;
	    new_y = (new_y + ship_y_pos)/2;
	    
	    if(!VideoSpriteBgCollide(scroll_y, new_x, new_y, SPR_SHIP)) {
	      /* accept new ship position */
	      ship_x_pos = new_x;
	      ship_y_pos = new_y;
	    }
	  } else {
	    /* ok, accept new ship position */
	    ship_x_pos = new_x;
	    ship_y_pos = new_y;
	  }
	}
	
	/* finally draw ship */
	VideoDrawSprite(ship_x_pos, ship_y_pos, SPR_SHIP);
      } else {

	/* ship is currently exploding */
	if(sub_state>1) {

	  if(sub_state>SHIP_EXPLODE_TIMER) {

	    /* ship is currently exploding */
	    VideoDrawSprite(ship_x_pos, ship_y_pos, 
			    SPR_EXP_L - (sub_state - SHIP_EXPLODE_TIMER)/2);
	  } else {
	    #define MSG_Y  140

	    if(sub_state>SHIP_EXPLODE_TIMER-(MAX_Y-MSG_Y))
	      i = MSG_Y+(sub_state-(SHIP_EXPLODE_TIMER-(MAX_Y-MSG_Y)));
	    else
	      i = MSG_Y;

	    if(lifes==0) VideoDrawText(5,i,"GAME OVER!");
	  }

	  sub_state--;
	} else 
	  {
	  /* ship explosion finished, show title */

	  /* still lifes left? */
	  if(lifes==0) {
	    /* new hi score? */
	    if(score > prefs.score[MAX_SCORES-1].value) {
	      init_name_input();
	      game_state  = STATE_NAME;
	    } else
	      game_state  = STATE_TITLE;

	    sub_state   = 0;
	  } else {

	    /* explosion finished and still lifes left */

	    /* reinitialize ship */
	    init_shot();
	    init_exp();
	    init_bomb();
	    init_wave(0, WAVE_INIT);
	    init_extra();

	    /* restart ... */
	    new_message("GET READY");
	    sub_state = 0;

	    /* reload damage indicator */
	    damage(DAMAGE_RELOAD);

	    /* restore last saved ship position */
	    ship_restore_position();
	  }
	}
      }

      /* process different game objects */
      handle_shot(hardKeyState & keyBitHard4, 
      		  shot_mode, ship_x_pos, ship_y_pos);

      handle_exp();
      handle_bomb(ship_x_pos, ship_y_pos);
      handle_wave(ship_x_pos, ship_y_pos);
      handle_extra();
      handle_message();

      /* finally update screen */
      VideoDrawText(0, 16, score_str);
    } else if(game_state == STATE_NAME) {
      /* user is currently entering a name */
      main_name_input();
    } else {
      /* title/hiscore etc are currently shown */
      main_title();
    }
    VideoFlip();
  }
  while (event.eType != appStopEvent);
}

/************************************************************/
/** global init and cleanup                                 */
static Boolean StartApplication(void) {
#ifdef GAMEPAD
  Err err;
#endif

  if(!VideoGreyscaleOn()) return false;

#ifdef GAMEPAD
  /* try to use gamepad */
  err = SysLibFind(GPD_LIB_NAME, &gpdRef);
  if (err == sysErrLibNotFound)
    err = SysLibLoad('libr', GPD_LIB_CREATOR, &gpdRef); 
	  
  /* unable to open gamepad lib? */
  if(err) gpdRef = 0;
  else if(GPDOpen(gpdRef))
    gpdRef = 0;
#endif

  /* Mask hardware keys */
  KeySetMask(~(keyBitPageUp | keyBitPageDown | 
	       keyBitHard1  | keyBitHard2 | 
	       keyBitHard3  | keyBitHard4 ));

  SysRandom(TimGetTicks());

  get_preferences();

  return true;
}

static void StopApplication(void) {
#ifdef GAMEPAD
  UInt32 numapps;
#endif

  save_preferences();

#ifdef GAMEPAD
  /* close gamepad lib if in use */
  if(gpdRef != 0) {
    GPDClose(gpdRef, &numapps);

    /* no application left? close lib! */
    if (numapps == 0)
      SysLibRemove(gpdRef);
  }
#endif

  VideoGreyscaleOff();
}

/////////////////////////
// PilotMain
/////////////////////////

DWord PilotMain(Word cmd, Ptr cmdBPB, Word launchFlags) {
  if (cmd == sysAppLaunchCmdNormalLaunch) {
    if(StartApplication()) {
      EventLoop();
      StopApplication();
    }
  }
  return(0);
}

