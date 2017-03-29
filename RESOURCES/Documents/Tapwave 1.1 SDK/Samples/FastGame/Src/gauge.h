/*! file			gauge.h

	Description:	Display data on the screen in a bar graph presentation.

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

#ifdef __cplusplus
extern "C"
{
#endif

#define GAUGE_DATA_MAX 400
typedef struct
{
	// Store lots of data, but leave some room near the edge
	// of the screen.
	int data[GAUGE_DATA_MAX];
	
	// Use a FIFO structure to reduce data movement.
	int start;
	int end;
	
	// the FIFO structure is empty
	int used;
	
	int screen_width;
} GaugeFIFOType;



GaugeFIFOType * GaugeOpen(int screen_width);

void GaugeAdd(GaugeFIFOType * info, int value);

void GaugeDraw(GaugeFIFOType * info, TwGfxSurfaceType* aDestSurface, 
	TwGfxPackedRGBType aColor,
	int left, int top);
	
void GaugeClose(GaugeFIFOType * info);

#ifdef __cplusplus
}
#endif
