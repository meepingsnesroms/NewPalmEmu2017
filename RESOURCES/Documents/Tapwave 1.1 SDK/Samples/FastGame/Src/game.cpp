/*
	File:			game.cpp

	Description:	This is the game portion of the example.  Game specific code to take the input,
					update the world, and draw is in here.  

					Code that depends on the host operating system, like PalmOS, does not belong here.  
					Instead all such functionality is obtained through the host (HostPalm.c).

					At the same time, because this code is free of the OS  it simpler to read and 
					easier to compile.

					This file is in C++ to show how to interact with HostPalm.c
					
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

/*!
This example is as simple as possible.  It shows a map that can be scrolled in
two dimensions using a joystick.  This shows

1. How to get input.
2. How to update the world.
3. How to draw.

The game can be paused and resumed as well.

*/


#include "host.h"
#include "random.h"



//@{
/*! \brief Map terrain types.

These terrain types all have matching bitmaps for display by the host code.
*/

const int terrain_water_shallow = 0;
const int terrain_water_deep = 1;

//@}


//@{
/*! \brief Sound types.

These sound types all have matching streams for play by the host code.
*/

const int sound_bump = 2000;

//@}


//@{
/*! \brief Rumble types.

These rumble types all have matching streams for play by the host code.
*/

const int rumble_bump = 0;

//@}


/*! Everything needed for a game that scrolls a map.  The map is drawn
into an offscreen buffer, and later the visible portion of the buffer is
drawn to the screen.

All functionality to run on a machine is provided by the Host API.
*/
class Cgame
{
  private:
    //!  The width of the game map in tiles.
    int width;

    //!  The height of the game map in tiles.
    int height;

    //!  The game map.  It is allocated and initialized in the constructor.
    int *map;

    //!  The name of the game.
    char name[32];

    //!  The width of the screen, and the offscreen buffer.
    int screen_width;

    //!  The height of the screen, and the offscreen buffer.
    int screen_height;

    //@{
    /*!  The view's top left is at a fixed point offset from the top left of the screen buffer.  The 
       coordinates are 10 * tile, meaning the fraction has a range of ten and represents a portion
       of a tile. 
       So 25 is halfway in the third tile. */
    int view_x;
    int view_y;
    //@}


    //!  Paused games do not advance.  They do redraw though.
    bool paused;
	
	// DOLATER: track separate effects for both directions.  If
	// you're stuck at the top, and then move right, you should 
	// get a second rumble.
	
    // If true do some effect (sound/rumble).  Replace this 
    bool scroll_past_edge;
    
    // The effect should only be played once when the edge is reached.
    // Clear when the edge is left (by some threshold).
    bool scroll_past_edge_effect_displayed;
    
    void draw_all(void);

  public:
    Cgame(const char *gamename,
        int new_screen_width, 
        int new_screen_height,
        int random_number_seed);

    ~Cgame(void);
    
    int advance(uint32 keys, int32 joystick_x, int32 joystick_y);
    
    void update_all(uint32 keys, int32 joystick_x, int32 joystick_y);

    void set_pause(bool new_paused);

    bool get_pause(void);

};

Cgame *the_game = NULL;


extern void
game_set_pause(int value)
{
	if (the_game != NULL)
        the_game->set_pause(value == game_pause);
}

extern int
game_get_pause(void)
{
    int result;

	if (the_game == NULL)
		result = game_pause;
	else
		result = the_game->get_pause() ? game_pause : game_run;
	
	return result;
}


extern int
game_exists(void)
{
	return the_game != NULL;
}

extern void
game_new(int new_screen_width, int new_screen_height,
    int random_number_seed)
{
#if 0
    game_delete();
#endif
    the_game = new Cgame("", new_screen_width, new_screen_height, random_number_seed);
}


extern void
game_delete(void)
{
    if (game_exists())
    {
        delete the_game;

        the_game = NULL;
    }

}

int
game_advance(unsigned long int keys, long int joystickX, long int joystickY)
{
    return the_game->advance(keys, joystickX, joystickY);
}


/*! Create a game sized for the screen.
*/

Cgame::Cgame(const char *new_name, int new_screen_width, int new_screen_height,
    int new_random_number_seed)
{
    random_number_set_seed(new_random_number_seed);

    screen_width = new_screen_width;
    screen_height = new_screen_height;
    
    // Allocate a map for the water.
    width = 32;
    height = 32;
    map = new int[width * height];

    // Make the terrain for the water.
    for (int i = width * height - 1; i >= 0; i--)
    {
        map[i] = random_number(2) == 1 ? terrain_water_shallow : terrain_water_deep;
    }

    view_x = 0;
    view_y = 0;
    scroll_past_edge = false;
    scroll_past_edge_effect_displayed = false;
    
    paused = false;
    HostMaskKeys();

}

/*! Cleanup after the game.
*/

Cgame::~Cgame(void)
{
    delete map;
}

/*! \brief return the current pause status */

bool Cgame::get_pause(void)
{
    return paused;
}

/*! \brief Pause or unpause the game.

The effect from pausing a games is noticeable until the game advances.  A paused
game ignores the input, and does not advance.  It only redraws.  A paused game 
also may display a 
message that it is paused, or it may display a game menu.
*/


void
Cgame::set_pause(bool new_pause)
{
    paused = new_pause;
    
    if (new_pause)
        HostUnmaskKeys();
    else
        HostMaskKeys();
}


/*! \brief Draw everything in the view to the screen buffer.

The model is that the buffer is erased and then everything is drawn.
An alternative model is to undraw the objects (by restoring saved pixels) 
and then drawing all again.  The second is faster when the number of objects
is small or the background is expensive to raw.  The game could be tuned to
switch between both, depending on which should be faster.
*/

void
Cgame::draw_all(void)
{
    int object;
    int object_width;
    int object_height;

    int view_width;
    int view_height;
    int view_offset_x;
    int view_offset_y;
    int view_x_tiles;
    int view_y_tiles;


    object_width = HostGetBitmapWidth(terrain_water_shallow);
    object_height = HostGetBitmapHeight(terrain_water_shallow);

    view_x_tiles = view_x / 10;
    view_y_tiles = view_y / 10;

    view_offset_x = (view_x % 10 * object_width) / 10;
    view_offset_y = (view_y % 10 * object_height) / 10;


    HostOpenScreenBuffer();

    // Draw the map.  Drawing to the offscreen buffer is always aligned to tiles.  Subtile
    // scrolling is accomplished when copy the buffer to the screen.
    //
    // NOTE: the width and height are just enough to cover the screen width and height.
    // Usually an extra tile is drawn so that part of first and last one are used.
    view_width = (screen_width + view_offset_x + (object_width - 1)) / object_width;
    for (int x = 0; x < view_width; x++)
    {
        view_height = (screen_height + view_offset_y + (object_height - 1)) / object_height;
        for (int y = 0; y < view_height; y++)
        {
            object = map[(y + view_y_tiles) * height + x + view_x_tiles];
            HostDrawObject(object, x * object_width, y * object_height);
        }
    }

    if (paused)
        HostDrawGameMenu(view_offset_x, view_offset_y, screen_width, screen_height);

    HostCloseScreenBuffer();
}


/*! \brief Update all game objects one time unit, including input affects.

Update the position and state of all game objects.  Handle collisions.  
Incorporate input.  

No visual changes are performed by this routine, instead that is 
handled by the draw routines.  No dirty information is kept either,
as complete redraws are done for simplicity.

*/

void
Cgame::update_all(uint32 keys,  //!< mask of keys currently pressed for this cycle
    int32 joystick_x,       //!< current joystick position
    int32 joystick_y        //!< current joystick position
    )
{
    int object_width;
    int object_height;
    
    
    object_height = HostGetBitmapHeight(terrain_water_shallow);
    object_width = HostGetBitmapWidth(terrain_water_shallow);
    
    
    if (joystick_x > 500)
        view_x++;
    else if (joystick_x < -500)
        view_x--;
    
    if (joystick_y > 500)
        view_y++;
    else if (joystick_y < -500)
        view_y--;
    
    
    // Be sure the map hasn't scrolled too far.
    scroll_past_edge = false;
    
    // Handle horizontal scrolling
    if (view_x < 0)
    {
        scroll_past_edge = true;
        view_x = 0;
    }
    else if ((view_x * object_width) / 10 + screen_width >= width * object_width)
    {
        scroll_past_edge = true;
        view_x = ((width * object_width - screen_width) * 10) / object_width;
    }
    

    // Handle vertical scrolling
    if (view_y < 0)
    {
        scroll_past_edge = true;
        view_y = 0;
    }
    else if ((view_y * object_height) / 10 + screen_height >= height * object_height)
    {
        scroll_past_edge = true;
        view_y = ((height * object_height - screen_height) * 10) / object_height;
    }
    
    // The idea here to allow the edge notification effect once per edge visit.
    // The threshold for when an edge is no longer visited is currently one tile of distance.
    if (scroll_past_edge_effect_displayed &&
    	(object_width < view_x &&
    		((view_x * object_width) / 10 + screen_width < (width - 1) * object_width)) &&
    	(object_height < view_y &&
    		((view_y * object_height) / 10 + screen_height < (height - 1) * object_height)))
    {
    	scroll_past_edge_effect_displayed = false;
    }
}


/*! \brief Advance the game one cycle

This performs the normal work to advance the game.  It takes the input
and updates the world.  It then draws the results in an offscreen buffer.
The offscreen buffer is copied to the screen at the start of the next cycle.
By drawing at a consistent time interval the results appear smooth.  Some 
input latency is added because
the results appear one time period after the input is taken, but it is not 
noticeable.

*/

int
Cgame::advance(uint32 keys,  //!< mask of keys currently pressed for this cycle
    int32 joystick_x,       //!< current joystick position
    int32 joystick_y        //!< current joystick position
    )
{
    int object_width;
    int object_height;
    int view_offset_x;
    int view_offset_y;
    
    
    // get input
    
    // draw buffer
    object_height = HostGetBitmapHeight(terrain_water_shallow);
    object_width = HostGetBitmapWidth(terrain_water_shallow);
    view_offset_x = (view_x % 10 * object_width) / 10;
    view_offset_y = (view_y % 10 * object_height) / 10;
    HostDrawBuffer(0, 0, view_offset_x, view_offset_y, screen_width, screen_height);

	 // Send rumble effects.
    if (scroll_past_edge)
    {
        if (!scroll_past_edge_effect_displayed)
        	HostPlayRumble(rumble_bump);

        scroll_past_edge = false;
        scroll_past_edge_effect_displayed = true;
    }
    

    // update world.
    if (!paused)
    {
        update_all(keys, joystick_x, joystick_y);
    }


    // draw world.
    draw_all();

    // true get called again.
    return true;
}
