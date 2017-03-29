/*
	File:			XMatrix.cpp

	Description:	XMatrix source file.  This is where all the magic happens.

	Author:		

	Copyright:		Copyright © 2003 by Tapwave, Inc.

	Disclaimer:		IMPORTANT:  This Tapwave software is provided by Tapwave, Inc. ("Tapwave").  Your 
					use is subject to and governed by terms and conditions of the Software Development 
					Kit Agreement ("SDK Agreement") between you and Tapwave.  If you have not entered 
					into Tapwave’s standard SDK Agreement with Tapwave, you have no right or license 
					to use, reproduce, modify, distribute or otherwise exploit this Tapwave software.  
					You may obtain a copy of Tapwave’s standard SDK Agreement by calling 650-960-1817
					or visiting Tapwave at http://www.tapwave.com/developers/. 

	Change History (most recent first):
				
*/

/* xscreensaver, Copyright (c) 1999, 2001 Jamie Zawinski <jwz@jwz.org>
 *
 * Permission to use, copy, modify, distribute, and sell this software and its
 * documentation for any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that
 * copyright notice and this permission notice appear in supporting
 * documentation.  No representations are made about the suitability of this
 * software for any purpose.  It is provided "as is" without express or 
 * implied warranty.
 *
 * Matrix -- simulate the text scrolls from the movie "The Matrix".
 *
 * The movie people distribute their own Windows/Mac screensaver that does
 * a similar thing, so I wrote one for Unix.  However, that version (the
 * Windows/Mac version at http://www.whatisthematrix.com/) doesn't match my
 * memory of what the screens in the movie looked like, so my `xmatrix'
 * does things differently.
 *
 *
 *     ==========================================================
 *
 *         NOTE:
 *
 *         People just love to hack on this one.  I get sent
 *         patches to this all the time saying, ``here, I made
 *         it better!''  Mostly this hasn't been true.
 *
 *         If you've made changes to xmatrix, when you send me
 *         your patch, please explain, in English, both *what*
 *         your changes are, and *why* you think those changes
 *         make this screensaver behave more like the displays
 *         in the movie did.  I'd rather not have to read your
 *         diffs to try and figure that out for myself...
 *
 *         In particular, note that the characters in the movie
 *         were, in fact, low resolution and somewhat blurry/
 *         washed out.  They also definitely scrolled a
 *         character at a time, not a pixel at a time.
 *
 *     ==========================================================
 *
 */

#include <TapWave.h>

#include "XMatrixRsc.h"
#include "XMatrix.h"

//////////////////////////////////////////////////////////////////////////
// Assertion Support
static void
assert_check(int error, const char* message)
{
	if (error) {
		ErrDisplayFileLineMsg("PalmOS", (UInt16) error, message);
	}
}

#define xassert(error) assert_check(error, #error);

//////////////////////////////////////////////////////////////////////////
// Globals
TwGfxSurfaceType*   gTwSurface;         // Offscreen buffer
TwGfxType*          gTwGfx;             // TapWave gfx pointer

TwGfxSurfaceType*   gDimSurface;
TwGfxSurfaceType*   gBrightSurface;
UInt32              gRandomSeed;
Int32               gDelay;
TwGfxRectType       gSourceArea = {0, 0, 0, 0};

static void twFillRect(int dstX, int dstY, int dstW, int dstH);
static void twDrawGlyph(int dstX, int dstY, int srcX, int srcY, int srcW, int srcH, int map, bool doFlip);


#define CHAR_COLS 16
#define CHAR_ROWS 13
#define CHAR_MAPS 3

typedef struct {
	int glow    : 8;
	unsigned int glyph   : 9;  /* note: 9 bit characters! */
	unsigned int changed : 1;
	unsigned int spinner : 1;
} m_cell;

typedef struct {
	int remaining;
	int throttle;
	int y;
} m_feeder;

#define countof(x) (sizeof(x)/sizeof(*(x)))

static int matrix_encoding[] = { 16, 17, 18, 19, 20, 21, 22, 23, 24, 25,
192, 193, 194, 195, 196, 197, 198, 199,
200, 201, 202, 203, 204, 205, 206, 207 };
static int decimal_encoding[]  = { 16, 17, 18, 19, 20, 21, 22, 23, 24, 25 };
static int hex_encoding[]      = { 16, 17, 18, 19, 20, 21, 22, 23, 24, 25,
33, 34, 35, 36, 37, 38 };
static int binary_encoding[] = { 16, 17 };
static int dna_encoding[]    = { 33, 35, 39, 52 };
static unsigned char char_map[256] = {
    3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  /*   0 */
		3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  /*  16 */
		0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,  /*  32 */
		16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,  /*  48 */
		32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47,  /*  64 */
		48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63,  /*  80 */
		64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79,  /*  96 */
		80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95,  /* 112 */
		3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  /* 128 */
		3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  /* 144 */
		96, 97, 98, 99,100,101,102,103,104,105,106,107,108,109,110,111,  /* 160 */
		112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,  /* 176 */
		128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,  /* 192 */
		144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,  /* 208 */
		160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,  /* 224 */
		176,177,178,195,180,181,182,183,184,185,186,187,188,189,190,191   /* 240 */
};

// Do not reorder these unless you read the code and fix the bugs you
// just made
typedef enum { TRACE0, TRACE1, TRACE2,
KNOCKPRE0, KNOCK0, KNOCK1, KNOCK2, KNOCK3,
KNOCK4, KNOCK5, KNOCK6, KNOCK7,
MATRIX, DNA, BINARY, HEX } m_mode;

typedef struct {
	int grid_width, grid_height;
	int char_width, char_height;
	m_cell *cells;
	m_feeder *feeders;
	int nspinners;
	bool small_p;
	bool insert_top_p, insert_bottom_p;
	m_mode mode;
	int modeOffset;
	int modeOffsetLimit;
	signed char *tracing;
	int density;
	
	int delay;
	int timer;
	bool long_timer;
	
	bool mFlipped;
	int image_width, image_height;
	
	int nglyphs;
	int *glyph_map;
	
} m_state;

static m_state gState;



inline Int32 random() 
{
    UInt32 result;
	
    // Generate the new seed
    gRandomSeed *= 2147001325;
    gRandomSeed += 715136305;
	
    // Return the random number
    result = gRandomSeed >> 16;
	
    return (result);
}

static void flip_images (m_state *state)
{
	state->mFlipped = !state->mFlipped;
}

static void init_spinners (m_state *state)
{
	int i = state->nspinners;
	int x, y;
	m_cell *cell;
	
	for (y = 0; y < state->grid_height; y++)
		for (x = 0; x < state->grid_width; x++)
		{
			cell = &state->cells[state->grid_width * y + x];
			cell->spinner = 0;
		}
		
		while (--i > 0)
		{
			x = random() % state->grid_width;
			y = random() % state->grid_height;
			cell = &state->cells[state->grid_width * y + x];
			cell->spinner = 1;
		}
}

static void init_trace (m_state *state)
{
	char *s = "(212) 555-0690";
	char *s2, *s3;
	int i;
	
	state->tracing = (signed char *) MyMalloc (StrLen (s) + 1);
	s3 = (char*) state->tracing;
	
	for (s2 = s; *s2; s2++)
		if (*s2 >= '0' && *s2 <= '9')
			*s3++ = *s2;
    *s3 = 0;
    
    if (s3 == (char *) state->tracing)
        goto FAIL;
    
    for (i = 0; i < (int)StrLen((char*)state->tracing); i++)
        state->tracing[i] = (signed char) (-state->tracing[i]);
    
    state->glyph_map = decimal_encoding;
    state->nglyphs = countof(decimal_encoding);
    
    return;
		
FAIL:
    if (s) MemPtrFree (s);
    if (state->tracing) MemPtrFree (state->tracing);
    state->tracing = 0;
    state->mode = MATRIX;
}

static void init_matrix (int windowWidth, int windowHeight, m_state* state )
{
	state->delay = 40;
	state->small_p = true;
	state->image_width = BITMAP_WIDTH;
	state->image_height = BITMAP_HEIGHT;
	
	state->char_width =  state->image_width  / CHAR_COLS;
	state->char_height = state->image_height / CHAR_ROWS;
	
	state->grid_width  = windowWidth  / state->char_width;
	state->grid_height = windowHeight / state->char_height;
	state->grid_width++;
	state->grid_height++;
	
	state->glyph_map = matrix_encoding;
	state->nglyphs = countof(matrix_encoding);
	
	state->cells = (m_cell *)
		MyCalloc (sizeof(m_cell), state->grid_width * state->grid_height);
	state->feeders = (m_feeder *) MyCalloc (sizeof(m_feeder), state->grid_width);
	
	state->density = 40;
	state->insert_top_p = true;
	state->insert_bottom_p = true;
	
	state->nspinners = 5;
	state->mode = MATRIX;
	
	if (state->mode == DNA)
    {
		state->glyph_map = dna_encoding;
		state->nglyphs = countof(dna_encoding);
    }
	else if (state->mode == BINARY)
    {
		state->glyph_map = binary_encoding;
		state->nglyphs = countof(binary_encoding);
    }
	else if (state->mode == HEX)
    {
		state->glyph_map = hex_encoding;
		state->nglyphs = countof(hex_encoding);
    }
	else if (state->mode == TRACE0)
		init_trace (state);
	else if (state->mode == HEX)
    {
		state->glyph_map = hex_encoding;
		state->nglyphs = countof(hex_encoding);
    }
	else
    {
		flip_images (state);
		init_spinners (state);
    }
}

void destroy_matrix( m_state* state )
{
	MyFree(state->cells);
	MyFree(state->feeders);
}

static void insert_glyph(m_state *state, int glyph, int x, int y)
{
	bool bottom_feeder_p = (y >= 0);
	m_cell *from, *to;
	
	if (y >= state->grid_height)
		return;
	
	if (bottom_feeder_p)
    {
		to = &state->cells[state->grid_width * y + x];
    }
	else
    {
		for (y = state->grid_height-1; y > 0; y--)
        {
			from = &state->cells[state->grid_width * (y-1) + x];
			to   = &state->cells[state->grid_width * y     + x];
			to->glyph   = from->glyph;
			to->glow    = from->glow;
			to->changed = 1;
        }
		to = &state->cells[x];
    }
	
	to->glyph = glyph;
	to->changed = 1;
	
	if (!to->glyph)
		;
	else if (bottom_feeder_p)
		to->glow = 1 + (random() % 2);
	else
		to->glow = 0;
}


static void feed_matrix (m_state *state)
{
	int x;
	
	switch (state->mode)
    {
    case TRACE2: case MATRIX: case DNA: case BINARY: case HEX:
		break;
    default:
		return;
    }
	
	/* Update according to current feeders. */
	for (x = 0; x < state->grid_width; x++)
    {
		m_feeder *f = &state->feeders[x];
		
		if (f->throttle)    /* this is a delay tick, synced to frame. */
        {
			f->throttle--;
        }
		else if (f->remaining > 0)  /* how many items are in the pipe */
        {
			int g = state->glyph_map[(random() % state->nglyphs)] + 1;
			insert_glyph (state, g, x, f->y);
			f->remaining--;
			if (f->y >= 0)  /* bottom_feeder_p */
				f->y++;
        }
		else        /* if pipe is empty, insert spaces */
        {
			insert_glyph (state, 0, x, f->y);
			if (f->y >= 0)  /* bottom_feeder_p */
				f->y++;
        }
		
		if ((random() % 10) == 0)   /* randomly change throttle speed */
        {
			f->throttle = ((random() % 5) + (random() % 5));
        }
    }
}

static int densitizer (m_state *state)
{
/* Horrid kludge that converts percentages (density of screen coverage)
to the parameter that actually controls this.  I got this mapping
	empirically, on a 1024x768 screen.  Sue me. */
	if      (state->density < 10) return 85;
	else if (state->density < 15) return 60;
	else if (state->density < 20) return 45;
	else if (state->density < 25) return 25;
	else if (state->density < 30) return 20;
	else if (state->density < 35) return 15;
	else if (state->density < 45) return 10;
	else if (state->density < 50) return 8;
	else if (state->density < 55) return 7;
	else if (state->density < 65) return 5;
	else if (state->density < 80) return 3;
	else if (state->density < 90) return 2;
	else return 1;
}


static void hack_text (m_state *state)
{
	const char *s;
	switch (state->mode)
    {
    case TRACE0: s = "Call trans opt: received.\n"
                     "2-19-98 13:24:18 REC:Log>_"; break;
    case TRACE1: s = "Trace program: running_"; break;
		
    case KNOCKPRE0: // fall through to next statement
    case KNOCK0: s = "Wake up, Neo..."; break;
    case KNOCK1: s = ""; break;
    case KNOCK2: s = "The Matrix has you..."; break;
    case KNOCK3: s = ""; break;
    case KNOCK4: s = "Follow the white rabbit..."; break;
    case KNOCK5: s = ""; break;
    case KNOCK6: s = "Knock knock, Neo."; break;
    case KNOCK7: s = ""; break;
		
    default: break;
    }
	
	for (int i = 0; i < state->grid_height * state->grid_width; i++)
    {
		m_cell *cell = &state->cells[i];
		cell->changed = (cell->glyph != 0);
		cell->glyph = 0;
    }
	
	int cell;
	int x;
	if (state->mode == TRACE0 || state->mode == TRACE1)
    {
		x = cell = 0;
    }
	else
    {
		int y;
		//      x = ((int)state->grid_width - (int)StrLen(s)) / 2;
		//      y = (state->grid_height / 2) - 1;
		x = 2;
		y = 2;
		if (y < 0) y = 0;
		if (x < 0) x = 0;
		cell = (y * state->grid_width) + x;
    }
	
	state->modeOffsetLimit = StrLen(s);
	if (state->mode == KNOCKPRE0) return;
	
	const char* s0 = s;
	while (*s)
    {
		if (*s == '\n')
        {
			cell = ((cell / state->grid_width) + 1) * state->grid_width;
			x = 0;
        }
		else
        {
			m_cell *cellp = &state->cells[cell];
			if (x < state->grid_width-1)
            {
				cellp->glyph = char_map[(unsigned char) *s] + 1;
				if (*s == ' ' || *s == '\t') cellp->glyph = 0;
				cellp->changed = 1;
				cell++;
            }
			x++;
        }
		if ((state->mode != TRACE0) && (state->mode != TRACE1)) {
			if (s - s0 == state->modeOffset) {
				break;
			}
		}
		s++;
    }
}

static void roll_state (m_state *state)
{
	int delay = 0;
	switch (state->mode)
    {
    case TRACE0:
		delay = 3000;
		state->mode = TRACE1;
		break;
		
    case TRACE1:
		delay = 2000;
		state->mode = TRACE2;
		break;
		
    case TRACE2:
		{
			bool any = false;
			int i;
			for (i = 0; i < (int)StrLen((char*)state->tracing); i++)
				if (state->tracing[i] < 0) any = true;
				
				if (!any)
				{
					delay = 3000;
					state->mode = MATRIX;
					state->glyph_map = matrix_encoding;
					state->nglyphs = countof(matrix_encoding);
					flip_images (state);
					MyFree (state->tracing);
					state->tracing = 0;
				}
				else if ((random() % 10) == 0)
				{
					int x = random() % StrLen((char*)state->tracing);
					if (state->tracing[x] < 0)
						state->tracing[x] = (signed char) (-state->tracing[x]);
				}
				break;
		}
		
    case KNOCKPRE0:
		delay = 2000;
		state->mode = KNOCK0;
		state->modeOffset = 0;
		break;
		
    case KNOCK0:                        /* wake up neo */
		delay = 200;
		if (++state->modeOffset == state->modeOffsetLimit) {
			delay = 1000;
			state->mode = KNOCK1;
			state->modeOffset = 0;
		}
		break;
    case KNOCK1:
		delay = 4000;
		state->mode = KNOCK2;
		state->modeOffset = 0;
		break;
    case KNOCK2:                        /* the matrix has you */
		delay = 200;
		if (++state->modeOffset == state->modeOffsetLimit) {
			delay = 2000;
			state->mode = KNOCK3;
			state->modeOffset = 0;
		}
		break;
    case KNOCK3:
		delay = 4000;
		state->mode = KNOCK4;
		state->modeOffset = 0;
		break;
    case KNOCK4:                        /* follow the white rabbit */
		delay = 200;
		if (++state->modeOffset == state->modeOffsetLimit) {
			delay = 2000;
			state->mode = KNOCK5;
			state->modeOffset = 0;
		}
		break;
    case KNOCK5:
		delay = 4000;
		state->mode = KNOCK6;
		state->modeOffset = 0;
		break;
    case KNOCK6:                        /* knock knock neo */
		delay = 200;
		if (++state->modeOffset == state->modeOffsetLimit) {
			delay = 4000;
			state->mode = KNOCK7;
			state->modeOffset = 0;
		}
		break;
    case KNOCK7:
		state->mode = MATRIX;
		state->modeOffset = 0;
		state->glyph_map = matrix_encoding;
		state->nglyphs = countof(matrix_encoding);
		flip_images (state);
		break;
		
    case MATRIX:
		if (! (random() % 5000))
        {
			state->mode = KNOCK0;
			flip_images (state);
        }
		break;
		
    case DNA: case BINARY: case HEX:
		break;
		
    default:
		break;
    }
	
	if (delay)
    {
		state->long_timer = true;
		state->timer = delay;
    }
	else {
		state->timer = 0;
	}
	
}


static void hack_matrix (m_state *state)
{
	int x;
	
	switch (state->mode)
    {
    case TRACE0: case TRACE1:
    case KNOCKPRE0:
    case KNOCK0: case KNOCK1: case KNOCK2: case KNOCK3:
    case KNOCK4: case KNOCK5: case KNOCK6: case KNOCK7:
		hack_text (state);
		return;
    case TRACE2: case MATRIX: case DNA: case BINARY: case HEX:
		break;
    default:
		break;
    }
	
	/* Glow some characters. */
	if (!state->insert_bottom_p)
    {
		int i = random() % (state->grid_width / 2);
		while (--i > 0)
        {
			int x = random() % state->grid_width;
			int y = random() % state->grid_height;
			m_cell *cell = &state->cells[state->grid_width * y + x];
			if (cell->glyph && cell->glow == 0)
            {
				cell->glow = random() % 10;
				cell->changed = 1;
            }
        }
    }
	
	/* Change some of the feeders. */
	for (x = 0; x < state->grid_width; x++)
    {
		m_feeder *f = &state->feeders[x];
		bool bottom_feeder_p;
		
		if (f->remaining > 0) /* never change if pipe isn't empty */
			continue;
		
		if ((random() % densitizer(state)) != 0) /* then change N% of the time */
			continue;
		
		f->remaining = 3 + (random() % state->grid_height);
		f->throttle = ((random() % 5) + (random() % 5));
		
		if ((random() % 4) != 0)
			f->remaining = 0;
		
		if (state->mode == TRACE2)
			bottom_feeder_p = true;
		if (state->insert_top_p && state->insert_bottom_p)
			bottom_feeder_p = (random() & 1) ? true : false;
		else
			bottom_feeder_p = state->insert_bottom_p;
		
		if (bottom_feeder_p)
			f->y = random() % (state->grid_height / 2);
		else
			f->y = -1;
    }
	
	if (!(state->mode == TRACE2) && ! (random() % 500))
		init_spinners (state);
}


int draw_matrix ()
{
	m_state *state = &gState;
	int x, y;
	int count = 0;
	
	feed_matrix (state);
	hack_matrix (state);
	
	for (y = 0; y < state->grid_height; y++)
    {
		for (x = 0; x < state->grid_width; x++)
		{
			m_cell *cell = &state->cells[state->grid_width * y + x];
			
			if (cell->glyph)
				count++;
			
			if (state->mode == TRACE2)
			{
				int xx = x % StrLen((char*)state->tracing);
				bool dead_p = state->tracing[xx] > 0;
				
				if (y == 0 && x == xx)
					cell->glyph = (dead_p
					? state->glyph_map[state->tracing[xx]-'0'] + 1
					: 0);
				else if (y == 0)
					cell->glyph = 0;
				else
					cell->glyph = (dead_p ? 0 :
				(state->glyph_map[(random()%state->nglyphs)]
					+ 1));
				
				cell->changed = 1;
			}
			
			if (!cell->changed)
				continue;
			
			if (cell->glyph == 0) {
				twFillRect(x * state->char_width, y * state->char_height,
					state->char_width, state->char_height);
			}
			else
			{
				int cx = (cell->glyph - 1) % CHAR_COLS;
				int cy = (cell->glyph - 1) / CHAR_COLS;
				int map = (cell->glow > 0 || cell->spinner) ? GLOW_MAP : PLAIN_MAP;
				bool doFlip = state->mFlipped && (state->mode > KNOCK7);
				
				// Select proper ddb to use: if mFlipped && our state is
				// *not* one of the knock states...
				twDrawGlyph(x * state->char_width, y * state->char_height,
					cx * state->char_width, cy * state->char_height,
					state->char_width, state->char_height,
					map, doFlip);
			}
			
			cell->changed = 0;
			
			if (cell->glow > 0)
			{
				cell->glow--;
				cell->changed = 1;
			}
			else if (cell->glow < 0)
			{
				cell->glow++;
				if (cell->glow == 0)
					cell->glyph = 0;
				cell->changed = 1;
			}
			
			if (cell->spinner)
			{
				cell->glyph = (state->glyph_map[(random()%state->nglyphs)] + 1);
				cell->changed = 1;
			}
		}
    }
	
	roll_state (state);
	
	return state->timer ? state->timer : state->delay;
}


//////////////////////////////////////////////////////////////////////////
// Functions

TwGfxSurfaceType* twLoadBitmap(Int16 resID, TwGfxType* mGFX) 
{
    TwGfxSurfaceType* surf = NULL;
	
#ifdef __PALMOS_ARMLET__
    MemHandle resH = DmGetResource('Tbmp', resID );
#else
    MemHandle resH = DmGetResource('abmp', resID );
#endif
    if (resH != NULL) {
        BitmapType* resBmp = (BitmapType*) MemHandleLock(resH);
        if (resBmp) {
            UInt16 prevcs = WinSetCoordinateSystem(kCoordinatesNative);

            // Get information about bitmap
            Coord w, h;
            WinGetBitmapDimensions(resBmp, &w, &h);

            // Allocate a surface to hold the image
            TwGfxSurfaceInfoType surfInfo;
            surfInfo.size = sizeof(surfInfo);
            surfInfo.width = w;
            surfInfo.height = h;
            surfInfo.location = twGfxLocationAcceleratorMemory;
            surfInfo.pixelFormat = twGfxPixelFormatRGB565;
            xassert(TwGfxAllocSurface(mGFX, &surf, &surfInfo));

            TwGfxPointType dp = {0, 0};
            xassert(TwGfxDrawPalmBitmap(surf, &dp, resBmp));
            xassert(MemHandleUnlock(resH));

            WinSetCoordinateSystem(prevcs);
        } else {
            assert_check(resID, "MemHandleUnlock failed");
        }
        xassert(DmReleaseResource(resH));
    } else {
        assert_check(resID, "DmGetResource failed");
    }

    return surf;
}

static void twFillRect(int dstX, int dstY, int dstW, int dstH) 
{
    TwGfxRectType r;
    r.x = dstX;
    r.y = dstY;
    r.w = dstW;
    r.h = dstH;
    TwGfxFillRect(gTwSurface, &r, TwGfxComponentsToPackedRGB(0, 0, 0));
}

static void twDrawGlyph(int dstX, int dstY, int srcX, int srcY, int srcW, int srcH, int map, bool doFlip) 
{
    TwGfxSurfaceType* surf = (map == GLOW_MAP) ? gBrightSurface : gDimSurface;
	
    TwGfxRectType src;
    TwGfxMakeRect(src, srcX, srcY, srcW, srcH);
	
    TwGfxPointType dst;
    TwGfxMakePoint(dst, dstX, dstY);
    if (doFlip) {
        xassert(TwGfxTransformBlt(gTwSurface, &dst, surf, &src, twGfxRotateNone, twGfxMirrorHorizontal));
    } else {
        xassert(TwGfxBitBlt(gTwSurface, &dst, surf, &src));
    }
}

static void MatrixInit(void)
{
	UInt32 width, height;
	
	WinSetCoordinateSystem(kCoordinatesNative);
	xassert(WinScreenMode(winScreenModeGet, &width, &height, NULL, NULL));
	WinSetCoordinateSystem(kCoordinatesStandard);
	
	TwGfxSurfaceInfoType bmpsurfInfo;
	bmpsurfInfo.size = sizeof(bmpsurfInfo);
	bmpsurfInfo.width = width;
	bmpsurfInfo.height = height;
	bmpsurfInfo.location = twGfxLocationAcceleratorMemory;
	bmpsurfInfo.pixelFormat = twGfxPixelFormatRGB565;
	xassert(TwGfxAllocSurface(gTwGfx, &gTwSurface, &bmpsurfInfo));
	
	twFillRect(0, 0, width, height);
	
	gSourceArea.w = width;
	gSourceArea.h = height;
	
	// Initialize the matrix.
	init_matrix(width, height, &gState);
	gDelay = draw_matrix();
}

static void MatrixFini(void)
{
	destroy_matrix(&gState);
	xassert(TwGfxFreeSurface(gTwSurface));
}

SYSTEM_CALLBACK Boolean
AppHandleEvent(EventType * event)
{
	switch (event->eType)
	{
	case winDisplayChangedEvent:
    {
		RectangleType bounds;
		WinGetBounds(WinGetDisplayWindow(), &bounds);
		WinSetBounds(WinGetActiveWindow(), &bounds);
		MatrixFini();
		MatrixInit();
		break;
    }
	case nilEvent:
	case frmUpdateEvent:
	{
		TwGfxPointType destLocation = {0, 0};
		TwGfxSurfaceType* displaySurface;
		// Get palmos display surface:
		xassert(TwGfxGetPalmDisplaySurface(gTwGfx, &displaySurface));
		// Wait for vertical blank:
		xassert(TwGfxWaitForVBlank(gTwGfx));
		// Blit display buffer to screen:
		xassert(TwGfxBitBlt(displaySurface, &destLocation, gTwSurface, &gSourceArea));
		// Render stuff
		gDelay = draw_matrix();
		break;
	}
	case keyDownEvent:
		if (event->data.keyDown.chr == vchrFunction) {
			UInt32 visible;
			StatGetAttribute(statAttrBarVisible, &visible);
			if (visible) {
				PINSetInputAreaState(pinInputAreaClosed);
				StatHide();
			} else {
				StatShow();
				PINSetInputAreaState(pinInputAreaUser);
			}
            break;
		}
		return false;
	default:
		return false;
	}

	return true;
}

////////////////
// Main application loop
//
static void AppEventLoop(void)
{
	TwAppRun(&gDelay);
}


////////////////
// Set up palm app
//
static void AppStart(void)
{
	xassert(TwAppStart(&AppHandleEvent));
	xassert(TwGfxOpen(&gTwGfx, NULL));
	gDimSurface = twLoadBitmap(DimBitmapFamily, gTwGfx);
	gBrightSurface = twLoadBitmap(BrightBitmapFamily, gTwGfx);
	MatrixInit();
}

////////////////
// Shut down palm app
//
static void AppStop(void)
{
	MatrixFini();
	xassert(TwGfxFreeSurface(gDimSurface));
	xassert(TwGfxFreeSurface(gBrightSurface));
	xassert(TwGfxClose(gTwGfx));
	xassert(TwAppStop());
}

////////////////
// Palm entry point
//
extern "C" UInt32 PilotMain(UInt16 cmd, MemPtr cmdPBP, UInt16 launchFlags)
{
	if (cmd == sysAppLaunchCmdNormalLaunch) {
		AppStart();
		AppEventLoop();
		AppStop();
	}
	
	return 0;
}
