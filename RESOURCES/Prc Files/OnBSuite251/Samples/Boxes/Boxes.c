/* Boxes.c */

/*
A two  player game with each player 
taking turns to fill in the edges of
small boxes. When a box is completed
the player's number (1 or 2) is entered
in the box and that player takes
another turn.

*/

// each box is 12 pixels wide
#define BOXSIZE 12
// the board is an 8 x 8 grid
#define BOXCOUNT 8

// insets for the board on the form
#define LEFTMARGIN 20
#define TOPMARGIN 20

// using 1 bit per completed wall
// for each box
typedef enum { NONE = 0x0, 
	NORTH = 0x1, 
	EAST = 0x2, 
	SOUTH = 0x4, 
	WEST = 0x8, 
	ALL = 0xF} Wall;

// the board
Wall boxes[BOXCOUNT][BOXCOUNT];

// which players turn, 0 or 1 for
// player 1 or 2
int pIndex = 0;

// used to mark completed boxes
char *plyrStr = "12";

// validates board co-ordinates
Boolean withinBounds(int x, int y)
{
	return ((x >= 0) 
		&& (x < BOXCOUNT)
		&& (y >= 0)
		&& (y < BOXCOUNT));
}

// draws the empty board and
// initializes the Boxes array
void drawDots()
{
	int i, j;
// draw one more dot than BOXCOUNT
	for (i = 0; i <= BOXCOUNT; i++) {
		for (j = 0; j <= BOXCOUNT; j++) {
			RectangleType r;
			r.topLeft.x = i *  BOXSIZE + LEFTMARGIN;
			r.topLeft.y = j *  BOXSIZE + TOPMARGIN;
// make each dot a 3 x 3 rect.
			r.extent.x = 3;
			r.extent.y = 3;
			WinDrawRectangle(&r, 0);
			if ((i < BOXCOUNT) && (j < BOXCOUNT))
				boxes[i][j] = NONE;
		}
	}
}

// When a box is completed, fill in
// with the players number
void fillBox(int x, int y)
{
	RectangleType r;
	r.topLeft.x = x * BOXSIZE + 1 + LEFTMARGIN;
	r.topLeft.y = y * BOXSIZE + 1 + TOPMARGIN;
	r.extent.x =  BOXSIZE + 1;
	r.extent.y =  BOXSIZE + 1;
	WinDrawChars(&plyrStr[pIndex], 1, r.topLeft.x + 4, r.topLeft.y + 1); 
}

// for box x,y - draw it's w wall
void drawWall(int x, int y, Wall w)
{
// pixel start and finish for the wall
	int fromX;
	int fromY;
	int toX;
	int toY;

	switch (w) {
	case NORTH :
		fromX = x * BOXSIZE + 1;
		fromY = y * BOXSIZE + 1;
		toX = fromX + BOXSIZE;
		toY = fromY;
	break;
	case SOUTH :
		fromX = x * BOXSIZE + 1;
		fromY = (y+ 1) * BOXSIZE + 1;
		toX = fromX + BOXSIZE;
		toY = fromY;
	break;
	case EAST :
		fromX = (x + 1) * BOXSIZE + 1;
		fromY = y * BOXSIZE + 1;
		toX = fromX;
		toY = fromY + BOXSIZE;
	break;
	case WEST :
		fromX = x * BOXSIZE + 1;
		fromY = y * BOXSIZE + 1;
		toX = fromX;
		toY = fromY + BOXSIZE;
	break;
	default : // shouldn't happen
		SndPlaySystemSound(sndAlarm);
		return;
	}
// offset by board's location on the form
	fromX +=  LEFTMARGIN;
	fromY+= TOPMARGIN;
	toX += LEFTMARGIN;
	toY += TOPMARGIN;
	WinDrawLine(fromX, fromY, toX, toY);
}

// Player has selected box x,y and wall w
// - validate that it is a legal box and
//	not an existing wall
// - draw the wall (return 'true' through pDrawn)
// - if the box is completed, fill it
// - return whether the box was filled
Boolean setWall(int x, int y, Wall w, Boolean *pDrawn)
{
	if (withinBounds(x, y)) {
		if ((boxes[x][ y] & w) != w) {
			*pDrawn |=  true;
			boxes[x][ y] |= w;
			drawWall(x, y, w);
			if (boxes[x][ y] == ALL) {
				fillBox(x, y);
				return true;
			}
		}
		else
// alert user for a pre-existing wall
			SndPlaySystemSound(sndError);
	}
	return false;
}

// Player has selected point x,y
// - validate that the point corresponds
//	to a box edge
// - set both walls of the 2 boxes
//	bordered by the edge
Boolean selectLine(int x, int y)
{
	x -=  LEFTMARGIN;
	y -= TOPMARGIN;
	if ((x < 0)
// allow a little slop
			|| (x >= ((BOXCOUNT * BOXSIZE) + 4))
			|| (y < 0)
			|| (y >= ((BOXCOUNT * BOXSIZE) + 4)))
		return false;

	int  ix = (x/ BOXSIZE);
	int iy = (y / BOXSIZE);
	int bx = ix * BOXSIZE;
	int by = iy * BOXSIZE;
	int lx = x - bx;
	int ly = y - by;

	Boolean filled = false;
	Boolean drawn = false;
// use the diagonal as the determinant
// for which edge was selected
	if (lx > ly ) {
		if ((BOXSIZE - lx) > ly) {
			filled |= setWall(ix, iy, NORTH, &drawn);
			filled |= setWall(ix,iy-1,SOUTH, &drawn);
		}
		else {
			filled |= setWall(ix, iy,EAST, &drawn);
			filled |= setWall(ix+1,iy,WEST, &drawn);
		}
	}
	else {
		if ((BOXSIZE - lx) < ly) {
			filled |= setWall(ix, iy,SOUTH, &drawn);
			filled |= setWall(ix,iy+1,NORTH, &drawn);
		}
		else {
			filled |= setWall(ix, iy,WEST, &drawn);
			filled |= setWall(ix-1,iy,EAST, &drawn);
		}
	}
// if the edge did not complete a
// box but was a valid edge, switch
// turns.
	if (drawn && !filled) 
		pIndex = 1 - pIndex;
	return true;
}

Boolean mainFormEventHandler(EventPtr evt)
{
	Boolean handled = false;
	FormPtr frm = FrmGetActiveForm();
	if (evt->eType == frmOpenEvent) {
		FrmDrawForm(frm);
		drawDots();
		handled = true;
	}
	else
// draw the selected line and toggle
// the turn button
		if (evt->eType == penUpEvent) {
			handled = selectLine(evt->data.penUp.start.x, evt->data.penUp.start.y);
			FrmSetControlGroupSelection (frm, 1, 1001 + pIndex);
		}
	return handled;				
}

